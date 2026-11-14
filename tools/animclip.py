"""DK64 (US) animation clips (asset table 11, uncompressed): decode to per-frame bone transforms.

Source of truth: the hand-written sampler in asm/global/1E2D0.s (`func_80619C2C` decodes a
frame row, `func_80619B44` turns Euler angles into a quaternion, `func_8061A7F0` scales the
root translation) and the loader `controllerAnimCacheGetOrLoad` (src/global/17B90.c,
`asset->unk6 += 6`). Every one of the 1731 clips parses to its exact end.

Header (big-endian):
  0x00 f32 speed
  0x04 u16 flags: 1 advances at gFrameDelta * 0.5 per tick, 2 loop, 4 ping-pong, 8 jump,
       0x10 layer fade, 0x20 quaternion blend
  0x06 u16 frame-data offset minus 6 (data starts at value + 6)
  0x08 s16[3] root translation base X, Y, Z
  0x0E u8[3] root translation bit widths
  0x11 u8 channels + 1
  0x12 u8 frame count (1..255)
  0x13 u8 row stride in bytes
  0x14 u16 descriptors: per channel, per component X, Y, Z: `d` (`d & 0xF` angle bits,
       `d & 0xFFF0` angle base, bit 4 kept); if `d & 0x10` a second u16 `d2` follows:
       0 = scale base 0 / 16 bits, else scale base `d2 & 0xFFF0`, bits `d2 & 0xF`.
       The descriptors end exactly at the data offset.

Frame row k (data + k * stride), one big-endian integer read MSB first: root X, Y, Z fields,
then per channel, per component: angle field, then scale field when the component has a
scale descriptor.
  angle u16 = (abase + (v << 5)) & 0xFFFF (abase when 0 bits); the rotation is
              R = Rz * Ry * Rx (column vectors, as glTF) of the angles & 0xFFE0
  scale u16 = sbase when 0 bits, else (sbase + (v << 4)) & 0xFFFF; no descriptor = 0;
              float = 1.0 for 0, else u16 / 32768
  root      = f32(f32((base + v) << 10) * D_80757490) per axis (~ raw / 32 model units),
              added once to the root bone's offset
A model's bone record byte 2 names its channel; bone local = T(offset) R(channel) S(channel).
"""

import math
import struct
from dataclasses import dataclass

ROOT_SCALE = struct.unpack(">f", bytes.fromhex("38000001"))[0]  # D_80757490
FRAME_RATE = 30.0  # flag-1 rate: gFrameDelta * 0.5 per tick at the 60 Hz VI


def f32(x: float) -> float:
    return struct.unpack(">f", struct.pack(">f", x))[0]


def parse(clip: bytes) -> dict:
    """Parse header + track descriptors; raises ValueError if the clip is inconsistent."""
    speed, flags, data_off_m6, bx, by, bz = struct.unpack_from(">fHHhhh", clip, 0)
    tbits = tuple(clip[0x0E:0x11])
    nchan_field, nframes, stride = clip[0x11], clip[0x12], clip[0x13]
    tracks = []  # per channel: 3 x (angle_base, angle_bits, scale_base or None, scale_bits)
    p = 0x14
    rowbits = sum(tbits)
    for _ in range(nchan_field - 1):
        comps = []
        for _ in range(3):
            d = struct.unpack_from(">H", clip, p)[0]
            p += 2
            abits = d & 0xF
            abase = d & 0xFFF0  # bit 4 (scale-follows flag) stays in the angle, as in the asm
            sbase = sbits = None
            if d & 0x10:
                d2 = struct.unpack_from(">H", clip, p)[0]
                p += 2
                if d2 == 0:
                    sbase, sbits = 0, 16
                else:
                    sbase, sbits = d2 & 0xFFF0, d2 & 0xF
            comps.append((abase, abits, sbase, sbits or 0))
            rowbits += abits + (sbits or 0)
        tracks.append(comps)
    data = data_off_m6 + 6  # controllerAnimCacheGetOrLoad: asset->unk6 += 6
    if p != data:
        raise ValueError(f"descriptors end at {p:#x}, header says {data:#x}")
    if (rowbits + 7) // 8 != stride:
        raise ValueError(f"row needs {rowbits} bits, stride {stride}")
    end = data + nframes * stride
    slack = len(clip) - end
    if slack not in (0, 1) or (slack == 1 and (end % 2 == 0 or clip[-1] != 0)):
        raise ValueError(f"end {end:#x} vs size {len(clip):#x}")
    return dict(speed=speed, flags=flags, tbase=(bx, by, bz), tbits=tbits,
                channels=nchan_field - 1, frames=nframes, stride=stride,
                data=data, rowbits=rowbits, tracks=tracks, slack=slack)


class _Bits:
    """MSB-first bit reader over one frame row (the asm's ldl/ldr 64-bit window)."""

    def __init__(self, clip: bytes, start: int, stride: int):
        self.row = int.from_bytes(clip[start:start + stride], "big")
        self.left = stride * 8  # bits not yet consumed

    def read(self, n: int) -> int:
        self.left -= n
        if self.left < 0:
            raise ValueError("read past the end of the frame row")
        return (self.row >> self.left) & ((1 << n) - 1)


def decode_row(clip: bytes, info: dict, k: int):
    """Frame row k (no interpolation): per-channel raw u16 angles (x, y, z), per-channel scales
    (x, y, z floats) and the root translation in model units."""
    bits = _Bits(clip, info["data"] + k * info["stride"], info["stride"])
    root = tuple(f32(f32(float((base + bits.read(n)) << 10)) * ROOT_SCALE) for base, n in zip(info["tbase"], info["tbits"]))
    angles, scales = [], []
    for comps in info["tracks"]:
        ang, sc = [], []
        for abase, abits, sbase, sbits in comps:
            ang.append((abase + (bits.read(abits) << 5)) & 0xFFFF if abits else abase)
            if sbase is None:
                raw = 0
            elif sbits:
                raw = (sbase + (bits.read(sbits) << 4)) & 0xFFFF
            else:
                raw = sbase
            sc.append(1.0 if raw == 0 else raw / 32768.0)
        angles.append(tuple(ang))
        scales.append(tuple(sc))
    if not 0 <= bits.left < 8:  # every row bit but the final byte's padding consumed
        raise ValueError(f"{bits.left} unread bits left in row {k}")
    return angles, scales, root


def euler_quat(ax: int, ay: int, az: int):
    """func_80619B44 + 98E4..9904 (exact trig instead of the 2048-step sine table): (w, x, y, z)."""
    hx, hy, hz = (a * math.pi / 65536.0 for a in (ax, ay, az))
    cx, sx, cy, sy, cz, sz = math.cos(hx), math.sin(hx), math.cos(hy), math.sin(hy), math.cos(hz), math.sin(hz)
    return (cx * cy * cz + sx * sy * sz, sx * cy * cz - cx * sy * sz,
            cx * sy * cz + sx * cy * sz, cx * cy * sz - sx * sy * cz)


@dataclass
class DecodedClip:
    index: int
    speed: float
    flags: int
    frames: int
    times: bytes  # little-endian f32 key times (seconds)
    rotations: list  # per channel: LE f32 x, y, z, w per key
    rotation_constant: list  # per channel: every angle component has 0 bits
    scales: list  # per channel: LE f32 x, y, z per key, or None (no scale descriptor)
    scale_constant: list  # per channel: every present scale component has 0 bits
    root: list  # per key: root translation (x, y, z) in model units
    root_constant: bool  # every root translation axis has 0 bits


def decode(index: int, clip: bytes) -> DecodedClip:
    """Every frame as one key, at frame / (30 * speed) seconds; looping clips (flag 2) get a
    closing key equal to frame 0 (`controllerApplyMotionWindow` wraps from the last frame to 0).
    Quaternion keys keep sign continuity so linear interpolation takes the short path."""
    info = parse(clip)
    rows = [decode_row(clip, info, k) for k in range(info["frames"])]
    keys = list(range(info["frames"]))
    if info["flags"] & 2 and info["frames"] > 1:
        keys.append(0)
    rate = FRAME_RATE * info["speed"]
    if not rate > 0:
        raise ValueError(f"speed {info['speed']} is not positive")
    times = struct.pack(f"<{len(keys)}f", *(k / rate for k in range(len(keys))))
    rotations, rotation_constant, scales, scale_constant = [], [], [], []
    for c, comps in enumerate(info["tracks"]):
        quats = []
        for k in keys:
            w, x, y, z = euler_quat(*(a & 0xFFE0 for a in rows[k][0][c]))
            q = (x, y, z, w)
            if quats and sum(p * v for p, v in zip(quats[-1], q)) < 0:
                q = tuple(-v for v in q)
            quats.append(q)
        rotations.append(struct.pack(f"<{4 * len(quats)}f", *(v for q in quats for v in q)))
        rotation_constant.append(all(abits == 0 for _ab, abits, _sb, _sn in comps))
        if all(sbase is None for _ab, _an, sbase, _sn in comps):
            scales.append(None)
            scale_constant.append(True)
        else:
            scales.append(struct.pack(f"<{3 * len(keys)}f", *(v for k in keys for v in rows[k][1][c])))
            scale_constant.append(all(sbits == 0 for _ab, _an, sbase, sbits in comps if sbase is not None))
    return DecodedClip(
        index=index,
        speed=info["speed"],
        flags=info["flags"],
        frames=info["frames"],
        times=times,
        rotations=rotations,
        rotation_constant=rotation_constant,
        scales=scales,
        scale_constant=scale_constant,
        root=[rows[k][2] for k in keys],
        root_constant=not any(info["tbits"]),
    )

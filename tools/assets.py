#!/usr/bin/env python3
"""Dump DK64 (US) ROM assets from the runtime asset pointer tables.

The asset region starts at ROM 0x101C50 (segment table entry 11, `D_8000DDCC`).
Layout, as read by the game (src/global/6AD90.c):

  base + 0x00   u32[32] table starts, relative to base (`collisionInitTables`
                DMAs them into `D_807F9520`); 0 = no table
  table start   u32[n + 1] entry offsets, relative to base; the first offset
                ends the offset array (`assetEnsureTableLoaded`); entry k spans
                [off[k], off[k + 1]) (`assetResolveRomRange`)
                bit 31 set: the entry is a redirect, whose first s16 is the
                index of another entry of the same table
  data          gzip member when the table's flag `D_80748E18[table]` is set
                (`assetLoad` inflates through `assetInflateAndFree`); table 26
                entry t holds table t's inflated sizes rounded up to even
                (`D_807FB1A0`, `assetGetCachedSizeOrResolve`)

Output (`dump`):
  <out>/raw/<TT>/<IIII>.bin   inflated entry (redirects are written once, at their target)
  <out>/index.json            per entry: ROM range, packed/inflated size, redirect target

Output (`models`, formats in the `*_parts` docstrings below):
  <out>/<kind>/<IIII>.obj     map (table 1), model2 (table 4) or actor (table 5, bind pose) geometry,
                              with vertex colours; .mtl beside it
  <out>/actor/<IIII>.glb      actors as skinned binary glTF, with every table-11 clip whose channel
                              count equals the model's as an animation (`tools/animclip.py`)
  <out>/textures/*.png        textures the models use (tables 25 and 7)
"""

import argparse
import hashlib
import json
import struct
import sys
import zlib
from pathlib import Path

import animclip
import n64gfx

US_SHA1 = "cf806ff2603640a748fca5026ded28802f1f4a50"
ASSET_BASE = 0x101C50  # D_8000DDCC: segment table entry 11 romStart
TABLE_SLOTS = 32
SIZE_TABLE = 26  # entry t: inflated sizes of table t's entries
# D_80748E18: per-table gzip flag (global data, 0x80748E18)
COMPRESSED = (1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0)
# Tables 2 and 3 are inflated per map when the map geometry header's flags (byte 9, bit 0/1) say so
# (70FD0.c / 6AD90.c); their entries carry the gzip magic exactly then.
MAP_GZIP = (2, 3)


def load_rom(path: Path) -> bytes:
    data = path.read_bytes()
    if hashlib.sha1(data).hexdigest() != US_SHA1:
        sys.exit(f"error: {path} is not the big-endian DK64 US ROM (run tools/extract.py first)")
    return data


def inflate(packed: bytes) -> bytes:
    stream = zlib.decompressobj(31)
    data = stream.decompress(packed)
    if not stream.eof:
        raise ValueError("truncated gzip member")
    return data


class AssetRom:
    """Resolves (table, index) to ROM ranges and inflated bytes exactly as `assetLoad` does."""

    def __init__(self, rom: bytes):
        self.rom = rom
        self.tables: dict[int, list[int]] = {}
        for t in range(TABLE_SLOTS):
            start = self._u32(ASSET_BASE + 4 * t)
            if start == 0:
                continue
            first = self._u32(ASSET_BASE + start) & 0x7FFFFFFF
            count = (first - start) // 4
            self.tables[t] = [self._u32(ASSET_BASE + start + 4 * k) for k in range(count)]
        self._cache: dict[tuple[int, int], bytes] = {}

    def _u32(self, offset: int) -> int:
        return struct.unpack_from(">I", self.rom, offset)[0]

    def count(self, table: int) -> int:
        return len(self.tables[table]) - 1

    def resolve(self, table: int, index: int) -> tuple[int, int, int]:
        """Return (final index, ROM start, ROM end) following redirects."""
        offsets = self.tables[table]
        seen = set()
        while offsets[index] & 0x80000000:
            if index in seen:
                raise ValueError(f"table {table}: redirect loop at {index}")
            seen.add(index)
            start = ASSET_BASE + (offsets[index] & 0x7FFFFFFF)
            index = struct.unpack_from(">h", self.rom, start)[0]
        start = ASSET_BASE + (offsets[index] & 0x7FFFFFFF)
        end = ASSET_BASE + (offsets[index + 1] & 0x7FFFFFFF)
        return index, start, end

    def packed(self, table: int, index: int) -> bytes:
        _, start, end = self.resolve(table, index)
        return self.rom[start:end]

    def get(self, table: int, index: int) -> bytes:
        """Inflated entry bytes (empty for an empty entry)."""
        final, start, end = self.resolve(table, index)
        key = (table, final)
        if key not in self._cache:
            data = self.rom[start:end]
            if (COMPRESSED[table] or table in MAP_GZIP) and data[:2] == b"\x1f\x8b":
                data = inflate(data)
            self._cache[key] = data
        return self._cache[key]

    def inflated_sizes(self, table: int) -> list[int] | None:
        if not COMPRESSED[table] or table >= self.count(SIZE_TABLE):
            return None
        raw = self.get(SIZE_TABLE, table)
        return list(struct.unpack(f">{len(raw) // 4}I", raw))


def cmd_dump(args: argparse.Namespace) -> None:
    assets = AssetRom(load_rom(args.rom))
    out: Path = args.out
    tables = args.table or sorted(assets.tables)
    index: dict[str, list[dict]] = {}
    errors = 0
    for t in tables:
        sizes = assets.inflated_sizes(t)
        tdir = out / "raw" / f"{t:02d}"
        tdir.mkdir(parents=True, exist_ok=True)
        entries = []
        for k in range(assets.count(t)):
            final, start, end = assets.resolve(t, k)
            entry = {"index": k, "rom_start": start, "rom_end": end}
            if final != k:
                entry["redirect"] = final
                entries.append(entry)
                continue
            data = assets.get(t, k)
            entry["size"] = len(data)
            entry["gzip"] = bool(COMPRESSED[t] or t in MAP_GZIP) and assets.rom[start : start + 2] == b"\x1f\x8b"
            if sizes is not None and end > start and sizes[k] != (len(data) + 1) & ~1:
                print(f"table {t} entry {k}: inflated 0x{len(data):X}, size table says 0x{sizes[k]:X}", file=sys.stderr)
                errors += 1
            if data:
                (tdir / f"{k:04d}.bin").write_bytes(data)
            entries.append(entry)
        index[str(t)] = entries
        written = sum(1 for e in entries if e.get("size"))
        print(f"table {t:2d}: {assets.count(t):5d} entries, {written:5d} written")
    (out / "index.json").write_text(json.dumps(index, indent=1) + "\n")
    if errors:
        sys.exit(f"error: {errors} entries disagree with the size table")


# ---------------------------------------------------------------------------
# Models

TEXTURE_TABLE = 25  # G_SETTIMG with segment 0: w1 is a table-25 index (controllerCommandRelocateAssets)
ANIMATION_TABLE = 11  # animation clips (`controllerAnimCacheGetOrLoad`)
MAP_ANIMATED_TEXTURE_TABLE = 7  # map texture animations bind table-7 frames to segments


class BlobSource(n64gfx.Source):
    """DL addresses inside one inflated asset, as described by one part dict:

    `addr`: maps a 32-bit DL address to a blob offset or None (runtime segment);
    `matrix_fn` (optional): returns the matrix a G_MTX address loads, or None;
    `joint_fn` (optional): returns the skeleton joint a G_MTX address loads, or None;
    `seg_textures` (optional): segment -> texture indices (table `seg_texture_table`) laid out back to
    back in the buffer the segment points at; the address's low 24 bits are an offset into it.
    """

    def __init__(self, assets: AssetRom, blob: bytes, part: dict):
        self.assets = assets
        self.blob = blob
        self.addr = part["addr"]
        self.matrix_fn = part.get("matrix_fn")
        self.joint_fn = part.get("joint_fn")
        self.seg_textures = part.get("seg_textures", {})
        self.seg_texture_table = part.get("seg_texture_table", TEXTURE_TABLE)

    def resolve(self, a: int):
        off = self.addr(a)
        if off is None or not 0 <= off < len(self.blob):
            return None
        return self.blob, off

    def matrix(self, a: int):
        if self.matrix_fn is not None:
            return self.matrix_fn(a)
        return super().matrix(a)

    def joint(self, a: int):
        return self.joint_fn(a) if self.joint_fn is not None else None

    def _table_texture(self, table: int, indices: list[int], offset: int = 0):
        if not all(0 <= i < self.assets.count(table) for i in indices):
            return None
        data = b"".join(self.assets.get(table, i) for i in indices)
        if offset >= len(data):
            return None
        key = f"t{table}_{indices[0]:04d}" + (f"+{offset:X}" if offset else "")
        return key, data[offset:]

    def texture(self, a: int):
        seg = a >> 24
        if seg == 0:
            return self._table_texture(TEXTURE_TABLE, [a])
        if seg in self.seg_textures:
            return self._table_texture(self.seg_texture_table, self.seg_textures[seg], a & 0xFFFFFF)
        found = self.resolve(a)
        if found is None:
            return None
        blob, off = found
        return f"inline_{zlib.crc32(blob) & 0xFFFFFFFF:08x}_{off:X}", blob[off:]


def model2_parts(blob: bytes) -> list[dict]:
    """Table 4 ('model 2' objects): `modelSlotInitFromAsset` / `renderModelAnimatedSlot` (36880.c).

    Header offsets are already blob offsets: 0x40 DL0 (segment 10), 0x44 DL1 (= DL0 end),
    0x48 vertex block (segment 8, = DL1 end), 0x4C vertex end; byte 0x1C = 1 for models
    (2: no geometry). Both DLs are drawn, in order. Segment 9 holds bone matrices of a
    linked animated actor at run time; the blob has no rest pose, so they stay identity.
    """
    if len(blob) < 0x50 or blob[0x1C] != 1:
        return []
    dl0, dl1, vtx, vtx_end = struct.unpack_from(">4I", blob, 0x40)

    def addr(a: int) -> int | None:
        seg, off = a >> 24, a & 0xFFFFFF
        if seg == 8 and vtx + off < vtx_end:
            return vtx + off
        if seg == 10:
            return dl0 + off
        return None  # 6: runtime material/fog DLs

    def matrix(a: int):
        return n64gfx.IDENTITY if a >> 24 == 9 else None

    return [
        {"name": "dl0", "dl": dl0, "dl_end": dl1, "addr": addr, "matrix_fn": matrix, "matrix": None},
        {"name": "dl1", "dl": dl1, "dl_end": vtx, "addr": addr, "matrix_fn": matrix, "matrix": None},
    ]


THIRD_SCALE = ((1 / 3, 0.0, 0.0, 0.0), (0.0, 1 / 3, 0.0, 0.0), (0.0, 0.0, 1 / 3, 0.0), (0.0, 0.0, 0.0, 1.0))


def map_parts(blob: bytes) -> list[dict]:
    """Table 1 (map geometry, index = map id): `MapFileHeader` (include/map.h); offsets are blob offsets.

    0x30 tree node (always 0x78), 0x34 dlBase (segment 7: every G_DL), 0x38 vtxBase (segment 6 for
    tree/portal DLs), 0x48 texture animations, 0x58 cells, 0x64 chunk bounds (first word = chunk
    count), 0x68 chunk records (0x34 bytes), 0x70 portals. Stored DL pointers are dlBase offsets
    (-1 = none). Chunk maps (tree kind 2) draw under guScale(1/3) (`D_807F7074`, `mapChunksRender`,
    55B20.c), leaf maps under the identity (`mapTreeRender`, 2F550.c).
    """
    u8 = lambda o: blob[o]  # noqa: E731
    s16 = lambda o: struct.unpack_from(">h", blob, o)[0]  # noqa: E731
    s32 = lambda o: struct.unpack_from(">i", blob, o)[0]  # noqa: E731

    tree, dlb, vtx = s32(0x30), s32(0x34), s32(0x38)
    nchunks = s32(s32(0x64))
    matrix = THIRD_SCALE if nchunks else None

    # Texture animations (`mapChunkEmitSegmentCommands`/`mapChunkAnimateTextures`, 2F550.c): s32 count, then
    # 0x7C-byte records: u8 segment, u8 chunk (0xFF = tree), ..., s32 table-7 frame indices at 0xC.
    # Frame 0 is bound. A segment a chunk never binds keeps the value an earlier chunk set: fall back
    # to the map-wide binding.
    anims: dict = {}
    any_chunk: dict = {}
    ao = s32(0x48)
    for i in range(s32(ao)):
        e = ao + 4 + i * 0x7C
        anims.setdefault(u8(e + 1), {})[u8(e)] = [s32(e + 0xC)]
        any_chunk.setdefault(u8(e), [s32(e + 0xC)])

    def part(name: str, dl: int, dl_end: int | None, vbase: int, chunk: int) -> dict:
        def addr(a: int) -> int | None:
            seg, off = a >> 24, a & 0xFFFFFF
            if seg == 7:
                return dlb + off
            if seg == 6:
                return vbase + off
            return None

        textures = {**any_chunk, **anims.get(chunk, {})}
        return {
            "name": name,
            "dl": dl,
            "dl_end": dl_end,
            "addr": addr,
            "matrix": matrix,
            "seg_textures": textures,
            "seg_texture_table": MAP_ANIMATED_TEXTURE_TABLE,
        }

    parts = []
    # Tree node (`mapTreeRelocate`/`mapTreeRender`/`mapViewDrawPass`): leaf (kind 1) draws +8, +C, +14,
    # +10, +18; a chunk root (kind 2) draws +8 only. Then the surface DLs (count at +0xC5).
    for o in (0x08,) if u8(tree + 0xB8) == 2 else (0x08, 0x0C, 0x14, 0x10, 0x18):
        d = s32(tree + o)
        if d != -1:
            parts.append(part(f"node_{o:02x}", dlb + d, None, vtx, 0xFF))
    for i in range(u8(tree + 0xC5)):
        parts.append(part(f"surface{i}", dlb + s32(tree + 0x1C + 4 * i), None, vtx, 0xFF))
    # Portals (`gMapPortals`, header 0x70): s32 count, 0x10-byte entries with dl0/dl1 at +8/+0xC.
    po = s32(0x70)
    for i in range(s32(po)):
        for k in (8, 12):
            d = s32(po + 4 + i * 0x10 + k)
            if d != -1:
                parts.append(part(f"portal{i}_{k // 4 - 2}", dlb + d, None, vtx, 0xFF))
    # Chunks (`mapChunksInitFromMapData`, 55B20.c): layer L DL offset/size at 0xC + 8L, vertex block at
    # 0x2C (from vtxBase). Kind 2 layers are runs of cells: a marker (w0 0, w1 cell id) starts each
    # cell DL; segment 6 = chunk vertices + cell.vtxOffset[L] * 16 (`mapChunkBuildCellTable`,
    # `mapChunkEmitLayerDisplayLists`); the first cell with the id wins.
    cells: dict = {}
    co = s32(0x58)
    for i in range(s32(co)):
        c = co + 4 + i * 0x1C
        cells.setdefault(s16(c + 2), c)
    for n in range(nchunks):
        e = s32(0x68) + n * 0x34
        kind = u8(e + 4)
        cvtx = vtx + s32(e + 0x2C)
        for layer in range(4):
            d, size = s32(e + 0x0C + 8 * layer), s32(e + 0x10 + 8 * layer)
            if d == -1:
                continue
            start, end = dlb + d, dlb + d + size
            if kind != 2:
                parts.append(part(f"chunk{n}_layer{layer}", start, end, cvtx, n))
                continue
            marks = [p for p in range(start, end, 8) if blob[p] == 0]
            for m, p in enumerate(marks):
                cid = s32(p + 4)
                cvbase = cvtx + s16(cells[cid] + 8 + 2 * layer) * 16
                nxt = marks[m + 1] if m + 1 < len(marks) else end
                parts.append(part(f"chunk{n}_layer{layer}_cell{cid}", p + 8, nxt, cvbase, n))
    return parts


def translation(x: float, y: float, z: float) -> tuple:
    return ((1.0, 0.0, 0.0, 0.0), (0.0, 1.0, 0.0, 0.0), (0.0, 0.0, 1.0, 0.0), (x, y, z, 1.0))


def actor_skeleton(blob: bytes) -> tuple[list[n64gfx.Joint], list[int]]:
    """Table-5 bone table (header 0x08, [0x20] records of 16 bytes; NULL: the default single root
    bone `D_80746B64`, channel 0): u8 parent bone id (0xFF root), u8 bone id (matrix slot: segment 4
    offset id * 0x40), u8 animation channel, pad, f32 x, y, z offset from the parent. `func_806195D0`
    (1E2D0.s) chains slot[id] = local * slot[parent] in table order (parents come first), where
    local = the channel's rotation plus this offset; the bind pose (zero rotation) is the sum of the
    offsets along the chain. Returns the joints in table order and each one's bone id."""
    base, _array_p, bones_p = struct.unpack_from(">3I", blob, 0)
    if not bones_p:
        return [n64gfx.Joint("bone00", None, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), {"bone_id": 0, "channel": 0})], [0]
    joints: list[n64gfx.Joint] = []
    ids: list[int] = []
    for i in range(blob[0x20]):
        o = bones_p - base + 0x28 + 16 * i
        parent, bid, channel = blob[o], blob[o + 1], blob[o + 2]
        offset = struct.unpack_from(">3f", blob, o + 4)
        pidx = None if parent == 0xFF else ids.index(parent)
        origin = (0.0, 0.0, 0.0) if pidx is None else joints[pidx].world
        world = tuple(origin[k] + offset[k] for k in range(3))
        joints.append(n64gfx.Joint(f"bone{bid:02d}", pidx, offset, world, {"bone_id": bid, "channel": channel}))
        ids.append(bid)
    return joints, ids


def actor_parts(blob: bytes, hide_segments: tuple = ()) -> list[dict]:
    """Table 5 (actor models): `controllerAnimStateLoadAsset` (17B90.c).

    Header: stored pointers P map to blob offsets P - [0x00] + 0x28. 0x00 vertex base (segment 3,
    blob 0x28), 0x04 array of [0x21] DL pointers (the DL ends where it starts), 0x08 bone table
    (`actor_skeleton`), 0x10 animated-texture list (`animListInit`, 8CA50.c). Vertices are
    bone-local: every G_MTX loads a bone's matrix (segment 4); parts carry the bind-pose matrix and
    `joint_fn`, which binds the vertices loaded after it to that bone.

    The DL is cut into consecutive slices at each bone G_MTX (walk them with one walker: triangles
    reuse vertices loaded under the previous bone). `DE 01 0X000000` (X >= 7) branches skip an
    optional section up to its marker `00000000 0000000X` unless bit X-7 of `actor->unk146` is set
    (`controllerBuildSubcommandList`); every section is drawn unless X is in `hide_segments`.
    """
    if len(blob) < 0x28:
        return []
    base, array_p, _bones_p, _unkc_p, anim_p = struct.unpack_from(">5I", blob, 0)

    def rel(p: int) -> int:
        return p - base + 0x28

    vtx = 0x28
    end = rel(array_p)
    dl0 = rel(struct.unpack_from(">I", blob, end)[0])

    skeleton, bone_ids = actor_skeleton(blob)
    joint_of = {bid: i for i, bid in enumerate(bone_ids)}  # bone id (matrix slot) -> skeleton index
    mats = {bid: translation(*skeleton[i].world) for bid, i in joint_of.items()}

    # Animated textures (`animListInit`/`animSetSegments`, 8CA50.c): s16 count, then {s16 frames,
    # s16 segment, s16 flag, s16 table-25 index[frames]}; a node with a nonzero flag points its
    # segment at its current frame. The unflagged nodes after it address their textures as offsets
    # into that segment, equal to the preceding textures' sizes (models 140 and 142), so the segment
    # binds the frame-0 textures of the group back to back.
    seg_tex: dict = {}
    group = None
    o = rel(anim_p)
    for _ in range(struct.unpack_from(">h", blob, o)[0]):
        num, seg, flag = struct.unpack_from(">3h", blob, o + 2)
        frames = struct.unpack_from(f">{num}h", blob, o + 8)
        o += 6 + 2 * num
        if not num:
            continue
        if flag:
            group = seg_tex.setdefault(seg, []) if seg not in seg_tex else None
        if group is not None:
            group.append(frames[0])

    def addr(a: int) -> int | None:
        seg, off = a >> 24, a & 0xFFFFFF
        if seg == 3 and vtx + off < dl0:
            return vtx + off
        return None  # 4 bone matrices (matrix_fn), 5 runtime highlight DL, 7+ optional-section branches

    def matrix_fn(a: int):
        if a >> 24 == 4 and a & 0x3F == 0:
            return mats.get((a & 0xFFFFFF) >> 6)
        return None

    def joint_fn(a: int) -> int | None:
        if a >> 24 == 4 and a & 0x3F == 0:
            return joint_of.get((a & 0xFFFFFF) >> 6)
        return None

    sections = {}  # branch pc -> (segment, marker pc)
    for pc in range(dl0, end, 8):
        w0, w1 = struct.unpack_from(">II", blob, pc)
        if w0 >> 24 == 0xDE and (w0 >> 16) & 0xFF == 1:
            seg = (w1 >> 24) & 0xF
            for q in range(dl0, end, 8):
                if blob[q] == 0 and struct.unpack_from(">I", blob, q + 4)[0] == seg:
                    sections[pc] = (seg, q)
                    break

    parts: list[dict] = []
    bone = None
    start = dl0
    section = None

    def close(stop: int) -> None:
        if stop > start:
            name = f"bone{bone:02d}" if bone is not None else "setup"
            if section is not None:
                name += f"_seg{section[0]:X}"
            parts.append(
                {
                    "name": name,
                    "dl": start,
                    "dl_end": stop,
                    "addr": addr,
                    "matrix_fn": matrix_fn,
                    "joint_fn": joint_fn,
                    "matrix": mats.get(bone) if bone is not None else None,
                    "seg_textures": seg_tex,
                }
            )

    pc = dl0
    while pc < end:
        w0, w1 = struct.unpack_from(">II", blob, pc)
        if section is not None and pc == section[1]:  # the marker ends the section
            close(pc)
            start, section = pc, None
        if pc in sections:
            close(pc)
            seg, marker = sections[pc]
            if seg in hide_segments:
                start = pc = marker
                continue
            section, start = (seg, marker), pc + 8
        elif w0 >> 24 == 0xDA and w1 >> 24 == 4:
            if bone is not None:  # setup commands before the first G_MTX join its slice
                close(pc)
                start = pc
            bone = (w1 & 0xFFFFFF) >> 6
        elif w0 >> 24 == 0xDF:
            pc += 8
            break
        pc += 8
    close(pc)
    return parts


# kind -> (table, parts function, skeleton function or None)
MODEL_KINDS = {
    "map": (1, map_parts, None),
    "model2": (4, model2_parts, None),
    "actor": (5, actor_parts, actor_skeleton),
}


def actor_animations(assets: AssetRom, skeleton: list[n64gfx.Joint], clip_cache: dict) -> list[n64gfx.Animation]:
    """Every table-11 clip whose channel count equals the skeleton's (max channel + 1), as glTF
    animations: a rotation track per joint, a scale track where the clip has scale descriptors, and
    the root joint's translation (bone offset + clip root translation). `clip_cache` maps clip index
    to its `animclip.DecodedClip`, or to the `ValueError` of a clip that does not decode (skipped)."""
    channels = max(j.extras["channel"] for j in skeleton) + 1
    animations = []
    for i in range(assets.count(ANIMATION_TABLE)):
        if i not in clip_cache:
            clip = assets.get(ANIMATION_TABLE, i)
            if len(clip) < 0x14 or clip[0x11] == 0:
                clip_cache[i] = ValueError(f"header too short or no channels ({len(clip)} bytes)")
            elif clip[0x11] - 1 != channels:
                continue  # decoded lazily, once a model with its channel count asks for it
            else:
                try:
                    clip_cache[i] = animclip.decode(i, clip)
                except ValueError as e:
                    clip_cache[i] = e
        dc = clip_cache[i]
        if not isinstance(dc, animclip.DecodedClip) or len(dc.rotations) != channels:
            continue
        tracks = []
        for s, joint in enumerate(skeleton):
            c = joint.extras["channel"]
            tracks.append(n64gfx.Track(s, "rotation", dc.rotations[c], dc.rotation_constant[c]))
            if dc.scales[c] is not None:
                tracks.append(n64gfx.Track(s, "scale", dc.scales[c], dc.scale_constant[c]))
        base = skeleton[0].translation
        root = struct.pack(f"<{3 * len(dc.root)}f", *(base[k] + r[k] for r in dc.root for k in range(3)))
        tracks.append(n64gfx.Track(0, "translation", root, dc.root_constant))
        animations.append(
            n64gfx.Animation(
                f"clip{i:04d}", dc.times, tracks, {"clip": i, "speed": dc.speed, "flags": dc.flags, "frames": dc.frames}
            )
        )
    return animations


def export_model(
    assets: AssetRom, kind: str, index: int, out: Path, texture_cache: dict, clip_cache: dict
) -> tuple[n64gfx.Mesh | None, int]:
    """Writes one model; returns its mesh (None: no geometry) and the number of animations attached."""
    table, parts_fn, skeleton_fn = MODEL_KINDS[kind]
    blob = assets.get(table, index)
    parts = parts_fn(blob) if blob else []
    if not parts:
        return None, 0
    mesh = n64gfx.Mesh()
    texture_dir = out / "textures"
    walker = n64gfx.Walker(None, mesh, texture_dir, texture_cache)
    for part in parts:
        walker.src = BlobSource(assets, blob, part)
        walker.set_object(part["name"], part.get("matrix"))
        walker.run(blob, part["dl"], part.get("dl_end"))
    if mesh.triangle_count == 0:
        return mesh, 0
    n64gfx.write_obj(out / kind / f"{index:04d}.obj", mesh, "../textures")
    if skeleton_fn is None:
        return mesh, 0
    skeleton = skeleton_fn(blob)[0]
    animations = actor_animations(assets, skeleton, clip_cache)
    n64gfx.write_gltf(out / kind / f"{index:04d}.glb", mesh, "../textures", skeleton, animations)
    return mesh, len(animations)


def cmd_models(args: argparse.Namespace) -> None:
    assets = AssetRom(load_rom(args.rom))
    out: Path = args.out
    (out / "textures").mkdir(parents=True, exist_ok=True)
    texture_cache: dict = {}
    clip_cache: dict = {}
    for kind in args.kind or list(MODEL_KINDS):
        table = MODEL_KINDS[kind][0]
        (out / kind).mkdir(parents=True, exist_ok=True)
        indices = args.index or range(assets.count(table))
        written = triangles = with_problems = animated = 0
        for k in indices:
            if assets.resolve(table, k)[0] != k:
                continue  # redirect: exported at its target
            mesh, attached = export_model(assets, kind, k, out, texture_cache, clip_cache)
            animated += attached
            if mesh is None or mesh.triangle_count == 0:
                continue
            written += 1
            triangles += mesh.triangle_count
            if mesh.problems:
                with_problems += 1
                if args.verbose:
                    print(f"{kind} {k}: " + "; ".join(mesh.problems[:5]), file=sys.stderr)
        print(f"{kind}: {written} models, {triangles} triangles ({with_problems} with problems) -> {out / kind}")
        if MODEL_KINDS[kind][2] is not None:
            decoded = sum(1 for v in clip_cache.values() if isinstance(v, animclip.DecodedClip))
            failed = sorted(i for i, v in clip_cache.items() if not isinstance(v, animclip.DecodedClip))
            print(f"animations: {animated} attached from {decoded} clips ({len(failed)} failed to decode)")
            if args.verbose:
                for i in failed:
                    print(f"clip {i}: {clip_cache[i]}", file=sys.stderr)
    print(f"textures: {sum(1 for v in texture_cache.values() if v)} -> {out / 'textures'}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--rom", type=Path, default=Path("baserom.us.z64"), help="big-endian US ROM (default: baserom.us.z64)")
    sub = parser.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("dump", help="write every table entry, inflated, to <out>/raw/")
    p.add_argument("--out", type=Path, default=Path("bin/assets"))
    p.add_argument("--table", type=int, action="append", help="only these tables (repeatable)")
    p.set_defaults(func=cmd_dump)
    p = sub.add_parser("models", help="export models as OBJ/MTL (actors also as skinned, animated glTF) with PNG textures")
    p.add_argument("--out", type=Path, default=Path("bin/assets/models"))
    p.add_argument("--kind", choices=list(MODEL_KINDS), action="append", help="only these kinds (repeatable)")
    p.add_argument("--index", type=int, action="append", help="only these entries (repeatable)")
    p.add_argument("-v", "--verbose", action="store_true", help="print each model's walker problems")
    p.set_defaults(func=cmd_models)
    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()

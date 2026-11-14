"""F3DEX2 display-list walker, N64 texture decoder and OBJ/MTL, glTF and PNG writers (stdlib only).

Used by tools/assets.py to export models. The walker simulates the parts of the RSP
that decide geometry: the vertex buffer, the modelview matrix stack, texture state
(G_TEXTURE scale, tile descriptors, TLUT loads) and the lighting bit of the geometry
mode. It does not rasterise; it emits triangles with positions, texture coordinates
and vertex colours (normals when lighting is on).
"""

import json
import struct
import zlib
from dataclasses import dataclass, field
from pathlib import Path

# F3DEX2 opcodes
G_VTX, G_MODIFYVTX, G_CULLDL, G_BRANCH_Z, G_TRI1, G_TRI2, G_QUAD = 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
G_TEXTURE, G_POPMTX, G_GEOMETRYMODE, G_MTX, G_DL, G_ENDDL = 0xD7, 0xD8, 0xD9, 0xDA, 0xDE, 0xDF
G_RDPHALF_1, G_SETOTHERMODE_H = 0xE1, 0xE3
G_MDSFT_TEXTLUT, G_TT_IA16 = 14, 3
G_LOADTLUT, G_SETTILESIZE, G_LOADBLOCK, G_LOADTILE, G_SETTILE, G_SETTIMG = 0xF0, 0xF2, 0xF3, 0xF4, 0xF5, 0xFD
G_LIGHTING = 0x00020000  # include/PR/gbi.h (0x00200000 is F3DEX2's G_SHADING_SMOOTH)
VTX_BUFFER = 64  # F3DEX2 holds 32; larger indices are reported, not silently wrapped
MAX_DEPTH = 18  # RSP display-list stack depth (F3DEX2: 18)

IDENTITY = ((1.0, 0.0, 0.0, 0.0), (0.0, 1.0, 0.0, 0.0), (0.0, 0.0, 1.0, 0.0), (0.0, 0.0, 0.0, 1.0))
Matrix = tuple  # 4x4 row-major, row-vector convention (v' = v * M), as the N64 uses


def mat_mul(a: Matrix, b: Matrix) -> Matrix:
    return tuple(tuple(sum(a[i][k] * b[k][j] for k in range(4)) for j in range(4)) for i in range(4))


def mat_from_fixed(data: bytes, offset: int) -> Matrix:
    """N64 `Mtx`: 16 s16 integer parts, then 16 u16 fractions, row-major."""
    ints = struct.unpack_from(">16h", data, offset)
    fracs = struct.unpack_from(">16H", data, offset + 32)
    vals = [ints[i] + fracs[i] / 65536.0 for i in range(16)]
    return tuple(tuple(vals[4 * r : 4 * r + 4]) for r in range(4))


def transform(m: Matrix, x: float, y: float, z: float) -> tuple[float, float, float]:
    return (
        x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0],
        x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1],
        x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2],
    )


# ---------------------------------------------------------------------------
# Textures

FMT_RGBA, FMT_YUV, FMT_CI, FMT_IA, FMT_I = 0, 1, 2, 3, 4
FMT_NAMES = {FMT_RGBA: "rgba", FMT_YUV: "yuv", FMT_CI: "ci", FMT_IA: "ia", FMT_I: "i"}
SIZ_BITS = (4, 8, 16, 32)


def rgba5551(v: int) -> tuple[int, int, int, int]:
    return ((v >> 11) & 31) * 255 // 31, ((v >> 6) & 31) * 255 // 31, ((v >> 1) & 31) * 255 // 31, 255 if v & 1 else 0


def ia16(v: int) -> tuple[int, int, int, int]:
    i = v >> 8
    return i, i, i, v & 0xFF


def decode_texture(data: bytes, fmt: int, siz: int, width: int, height: int, palette: list | None) -> bytes | None:
    """RGBA8 pixels, or None for an unsupported format. Missing source bytes decode as 0."""
    bits = SIZ_BITS[siz]
    need = (width * height * bits + 7) // 8
    if len(data) < need:
        data = data + bytes(need - len(data))
    out = bytearray(width * height * 4)

    def texel(n: int) -> int:
        if bits == 4:
            b = data[n >> 1]
            return (b >> 4) if (n & 1) == 0 else (b & 15)
        if bits == 8:
            return data[n]
        if bits == 16:
            return (data[2 * n] << 8) | data[2 * n + 1]
        return struct.unpack_from(">I", data, 4 * n)[0]

    for n in range(width * height):
        v = texel(n)
        if fmt == FMT_RGBA and bits == 16:
            px = rgba5551(v)
        elif fmt == FMT_RGBA and bits == 32:
            px = (v >> 24, (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF)
        elif fmt == FMT_CI and bits in (4, 8):
            if palette is None or v >= len(palette) or palette[v] is None:
                return None
            px = palette[v]
        elif fmt == FMT_IA and bits == 4:
            i = (v >> 1) * 255 // 7
            px = (i, i, i, 255 if v & 1 else 0)
        elif fmt == FMT_IA and bits == 8:
            i = (v >> 4) * 17
            px = (i, i, i, (v & 15) * 17)
        elif fmt == FMT_IA and bits == 16:
            px = ia16(v)
        elif fmt == FMT_I and bits == 4:
            px = (v * 17,) * 4
        elif fmt == FMT_I and bits == 8:
            px = (v,) * 4
        else:
            return None
        out[4 * n : 4 * n + 4] = bytes(px)
    return bytes(out)


def write_png(path: Path, width: int, height: int, rgba: bytes) -> None:
    rows = b"".join(b"\x00" + rgba[y * width * 4 : (y + 1) * width * 4] for y in range(height))

    def chunk(kind: bytes, body: bytes) -> bytes:
        return struct.pack(">I", len(body)) + kind + body + struct.pack(">I", zlib.crc32(kind + body) & 0xFFFFFFFF)

    png = b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0))
    png += chunk(b"IDAT", zlib.compress(rows, 9)) + chunk(b"IEND", b"")
    path.write_bytes(png)


# ---------------------------------------------------------------------------
# Display-list walker


@dataclass
class Tile:
    fmt: int = 0
    siz: int = 0
    line: int = 0
    tmem: int = 0
    palette: int = 0
    cms: int = 0
    cmt: int = 0
    shifts: int = 0
    shiftt: int = 0
    uls: int = 0
    ult: int = 0
    lrs: int = 0
    lrt: int = 0


@dataclass
class Material:
    name: str
    texture: str | None  # PNG file name, relative to the texture directory
    clamp_s: bool = False
    clamp_t: bool = False


@dataclass
class Mesh:
    positions: list = field(default_factory=list)  # (x, y, z)
    colors: list = field(default_factory=list)  # (r, g, b, a) floats, per position
    joints: list = field(default_factory=list)  # skeleton joint index per position (None: unskinned)
    uvs: list = field(default_factory=list)  # (u, v)
    groups: dict = field(default_factory=dict)  # (object name, material name) -> [((p, t) * 3)]
    materials: dict = field(default_factory=dict)  # name -> Material
    problems: list = field(default_factory=list)

    @property
    def triangle_count(self) -> int:
        return sum(len(f) for f in self.groups.values())


class Source:
    """Where the walker gets bytes from. Subclasses map DL addresses to (bytes, offset)."""

    def resolve(self, addr: int) -> tuple[bytes, int] | None:
        raise NotImplementedError

    def dl(self, addr: int, branch: bool) -> tuple[bytes, int] | None:
        return self.resolve(addr)

    def matrix(self, addr: int) -> Matrix | None:
        found = self.resolve(addr)
        return mat_from_fixed(*found) if found else None

    def joint(self, addr: int) -> int | None:
        """Skeleton joint a G_MTX address loads (vertices loaded under it are bound to it), or None."""
        return None

    def texture(self, addr: int) -> tuple[str, bytes] | None:
        """Texture image: (key naming this texture in every source; the walker caches by it, bytes)."""
        found = self.resolve(addr)
        if found is None:
            return None
        data, off = found
        return f"{zlib.crc32(data) & 0xFFFFFFFF:08x}_{off:X}", data[off:]


class Walker:
    def __init__(self, source: Source, mesh: Mesh, texture_dir: Path | None, texture_cache: dict):
        self.src = source
        self.mesh = mesh
        self.texture_dir = texture_dir
        self.texture_cache = texture_cache  # (key, fmt, siz, w, h, palette) -> png name | None
        self.vbuf: list = [None] * VTX_BUFFER  # (position index, s, t, color index)
        self.stack: list = [IDENTITY]
        self.geometry_mode = 0
        self.othermode_h = 0
        self.tex_on = False
        self.tex_scale = (1.0, 1.0)
        self.tex_tile = 0
        self.tiles = [Tile() for _ in range(8)]
        self.timg: tuple | None = None  # (addr, fmt, siz, width)
        self.tmem_images: dict = {}  # tmem word address -> (addr, fmt, siz, width)
        self.tlut: list = [None] * 256  # raw 16-bit TLUT entries
        self.object = "root"
        self.material: Material | None = None
        self.uv_cache: dict = {}
        self.calls = 0
        self.rdphalf1 = 0
        self.joint: int | None = None

    # -- helpers -----------------------------------------------------------
    def problem(self, msg: str) -> None:
        if len(self.mesh.problems) < 50:
            self.mesh.problems.append(msg)

    def set_object(self, name: str, matrix: Matrix | None = None) -> None:
        self.object = name
        self.stack = [matrix or IDENTITY]

    def current_material(self) -> Material:
        if self.material is None:
            self.material = self.build_material()
            self.mesh.materials.setdefault(self.material.name, self.material)
        return self.material

    def build_material(self) -> Material:
        if not self.tex_on:
            return Material("untextured", None)
        tile = self.tiles[self.tex_tile]
        width = ((tile.lrs - tile.uls) >> 2) + 1
        height = ((tile.lrt - tile.ult) >> 2) + 1
        image = self.tmem_images.get(tile.tmem)
        if image is None or width <= 0 or height <= 0 or width > 1024 or height > 1024:
            return Material("untextured", None)
        addr = image[0]
        # With a TLUT type set in the other mode, the RDP reads every 4/8-bit texel as an index.
        tlut_type = (self.othermode_h >> G_MDSFT_TEXTLUT) & 3
        fmt = FMT_CI if tile.fmt == FMT_CI or (tlut_type and tile.siz <= 1) else tile.fmt
        palette = None
        if fmt == FMT_CI:
            raw = self.tlut[tile.palette * 16 : tile.palette * 16 + 16] if tile.siz == 0 else self.tlut
            colour = ia16 if tlut_type == G_TT_IA16 else rgba5551
            palette = tuple(None if v is None else colour(v) for v in raw)
        # The same segmented address names different textures in different models or parts, so the
        # shared cache is keyed by the texture the source resolves it to.
        found = self.src.texture(addr)
        if found is None:
            self.problem(f"texture {addr:08X}: unresolved")
            return Material("untextured", None)
        source_key, data = found
        key = (source_key, fmt, tile.siz, width, height, palette)
        if key not in self.texture_cache:
            self.texture_cache[key] = self.export_texture(source_key, data, fmt, tile.siz, width, height, palette)
        png = self.texture_cache[key]
        clamp_s, clamp_t = bool(tile.cms & 2), bool(tile.cmt & 2)
        if png is None:
            return Material("untextured", None)
        return Material(png[:-4], png, clamp_s, clamp_t)

    def export_texture(self, key: str, data: bytes, fmt: int, siz: int, width: int, height: int, palette) -> str | None:
        rgba = decode_texture(data, fmt, siz, width, height, palette)
        if rgba is None:
            self.problem(f"texture {key}: unsupported {FMT_NAMES.get(fmt)}{SIZ_BITS[siz]}")
            return None
        name = f"{key}_{FMT_NAMES[fmt]}{SIZ_BITS[siz]}_{width}x{height}"
        if fmt == FMT_CI:
            name += f"_p{zlib.crc32(repr(palette).encode()) & 0xFFFFFFFF:08x}"
        name += ".png"
        if self.texture_dir is not None and not (self.texture_dir / name).exists():
            write_png(self.texture_dir / name, width, height, rgba)
        return name

    def uv(self, s: int, t: int) -> int:
        tile = self.tiles[self.tex_tile]
        width = ((tile.lrs - tile.uls) >> 2) + 1
        height = ((tile.lrt - tile.ult) >> 2) + 1
        fs = s * self.tex_scale[0] / 32.0
        ft = t * self.tex_scale[1] / 32.0
        for shift, idx in ((tile.shifts, 0), (tile.shiftt, 1)):
            if shift:
                factor = 1 / (1 << shift) if shift <= 10 else float(1 << (16 - shift))
                if idx == 0:
                    fs *= factor
                else:
                    ft *= factor
        u = (fs - tile.uls / 4.0) / max(width, 1)
        v = 1.0 - (ft - tile.ult / 4.0) / max(height, 1)
        key = (round(u, 6), round(v, 6))
        if key not in self.uv_cache:
            self.uv_cache[key] = len(self.mesh.uvs)
            self.mesh.uvs.append(key)
        return self.uv_cache[key]

    # -- commands ----------------------------------------------------------
    def load_vertices(self, addr: int, count: int, first: int) -> None:
        found = self.src.resolve(addr)
        if found is None:
            self.problem(f"G_VTX {addr:08X}: unresolved")
            return
        data, off = found
        if off + 16 * count > len(data):
            self.problem(f"G_VTX {addr:08X} x{count}: past end of data")
            return
        m = self.stack[-1]
        lit = bool(self.geometry_mode & G_LIGHTING)
        for i in range(count):
            x, y, z, _flag, s, t, r, g, b, a = struct.unpack_from(">hhhHhhBBBB", data, off + 16 * i)
            slot = first + i
            if slot >= VTX_BUFFER:
                self.problem(f"G_VTX slot {slot} out of range")
                return
            self.mesh.positions.append(transform(m, x, y, z))
            self.mesh.joints.append(self.joint)
            if lit:
                self.mesh.colors.append((1.0, 1.0, 1.0, a / 255.0))
            else:
                self.mesh.colors.append((r / 255.0, g / 255.0, b / 255.0, a / 255.0))
            self.vbuf[slot] = (len(self.mesh.positions) - 1, s, t)

    def triangle(self, a: int, b: int, c: int) -> None:
        verts = []
        for idx in (a, b, c):
            if idx >= VTX_BUFFER or self.vbuf[idx] is None:
                self.problem(f"triangle uses unloaded vertex {idx}")
                return
            verts.append(self.vbuf[idx])
        mat = self.current_material()
        face = []
        for pos, s, t in verts:
            face.append((pos, self.uv(s, t) if mat.texture else None))
        self.mesh.groups.setdefault((self.object, mat.name), []).append(tuple(face))

    def run(self, data: bytes, offset: int, end: int | None = None, depth: int = 0) -> None:
        if depth > MAX_DEPTH:
            self.problem("display-list nesting too deep")
            return
        while True:
            if end is not None and offset >= end:
                return
            if offset + 8 > len(data):
                self.problem(f"DL ran off the data at 0x{offset:X}")
                return
            w0, w1 = struct.unpack_from(">II", data, offset)
            offset += 8
            self.calls += 1
            if self.calls > 2_000_000:
                self.problem("command limit reached")
                return
            op = w0 >> 24
            if op == G_VTX:
                n = (w0 >> 12) & 0xFF
                last = (w0 >> 1) & 0x7F
                self.load_vertices(w1, n, last - n)
            elif op == G_TRI1:
                self.triangle(((w0 >> 16) & 0xFF) // 2, ((w0 >> 8) & 0xFF) // 2, (w0 & 0xFF) // 2)
            elif op in (G_TRI2, G_QUAD):
                self.triangle(((w0 >> 16) & 0xFF) // 2, ((w0 >> 8) & 0xFF) // 2, (w0 & 0xFF) // 2)
                self.triangle(((w1 >> 16) & 0xFF) // 2, ((w1 >> 8) & 0xFF) // 2, (w1 & 0xFF) // 2)
            elif op == G_RDPHALF_1:
                self.rdphalf1 = w1
            elif op == G_BRANCH_Z:
                # Taken when the vertex is nearer than the threshold: the first one selects the
                # highest level of detail; the walk never returns, like the RSP's branch.
                target = self.src.dl(self.rdphalf1, True)
                if target is not None:
                    self.run(target[0], target[1], None, depth + 1)
                    return
            elif op == G_DL:
                branch = ((w0 >> 16) & 0xFF) == 1
                target = self.src.dl(w1, branch)
                if target is not None:
                    self.run(target[0], target[1], None, depth + 1)
                if branch:
                    return
            elif op == G_ENDDL:
                return
            elif op == G_MTX:
                params = (w0 & 0xFF) ^ 1  # G_MTX_PUSH is stored inverted
                if params & 4:  # projection
                    continue
                m = self.src.matrix(w1)
                joint = self.src.joint(w1)
                if joint is not None:
                    self.joint = joint
                if m is None:
                    self.problem(f"G_MTX {w1:08X}: unresolved")
                    continue
                if not params & 2:  # multiply
                    m = mat_mul(m, self.stack[-1])
                if params & 1:
                    self.stack.append(m)
                else:
                    self.stack[-1] = m
            elif op == G_POPMTX:
                for _ in range(max(1, w1 // 64)):
                    if len(self.stack) > 1:
                        self.stack.pop()
            elif op == G_SETOTHERMODE_H:
                length = (w0 & 0xFF) + 1
                shift = 32 - ((w0 >> 8) & 0xFF) - length
                mask = ((1 << length) - 1) << shift
                self.othermode_h = (self.othermode_h & ~mask) | (w1 & mask)
                self.state_changed()
            elif op == G_GEOMETRYMODE:
                self.geometry_mode = (self.geometry_mode & (w0 | 0xFF000000)) | w1
            elif op == G_TEXTURE:
                self.tex_on = bool((w0 >> 1) & 0x7F)
                self.tex_tile = (w0 >> 8) & 7
                self.tex_scale = (((w1 >> 16) or 0x10000) / 65536.0, ((w1 & 0xFFFF) or 0x10000) / 65536.0)
                self.state_changed()
            elif op == G_SETTIMG:
                self.timg = (w1, (w0 >> 21) & 7, (w0 >> 19) & 3, (w0 & 0xFFF) + 1)
            elif op == G_SETTILE:
                tile = self.tiles[(w1 >> 24) & 7]
                tile.fmt, tile.siz = (w0 >> 21) & 7, (w0 >> 19) & 3
                tile.line, tile.tmem = (w0 >> 9) & 0x1FF, w0 & 0x1FF
                tile.palette = (w1 >> 20) & 0xF
                tile.cmt, tile.shiftt = (w1 >> 18) & 3, (w1 >> 10) & 0xF
                tile.cms, tile.shifts = (w1 >> 8) & 3, w1 & 0xF
                self.state_changed()
            elif op == G_SETTILESIZE:
                tile = self.tiles[(w1 >> 24) & 7]
                tile.uls, tile.ult = (w0 >> 12) & 0xFFF, w0 & 0xFFF
                tile.lrs, tile.lrt = (w1 >> 12) & 0xFFF, w1 & 0xFFF
                self.state_changed()
            elif op in (G_LOADBLOCK, G_LOADTILE):
                tile = self.tiles[(w1 >> 24) & 7]
                if self.timg is not None:
                    self.tmem_images[tile.tmem] = self.timg
                self.state_changed()
            elif op == G_LOADTLUT:
                tile = self.tiles[(w1 >> 24) & 7]
                count = ((w1 >> 14) & 0x3FF) + 1
                self.load_tlut(tile.tmem - 256, count)
                self.state_changed()
            # every other command (RDP modes, colours, sync, moveword/movemem) does not change geometry

    def state_changed(self) -> None:
        self.material = None

    def load_tlut(self, first: int, count: int) -> None:
        if self.timg is None or first < 0:
            return
        found = self.src.texture(self.timg[0])
        if found is None:
            self.problem(f"TLUT {self.timg[0]:08X}: unresolved")
            return
        _, data = found
        for i in range(count):
            if first + i < 256 and 2 * i + 2 <= len(data):
                self.tlut[first + i] = struct.unpack_from(">H", data, 2 * i)[0]


# ---------------------------------------------------------------------------
# Model writers


def write_obj(path: Path, mesh: Mesh, texture_rel: str, scale: float = 1.0) -> None:
    """Wavefront OBJ + MTL; vertex colours as the common `v x y z r g b` extension."""
    mtl_path = path.with_suffix(".mtl")
    lines = [f"mtllib {mtl_path.name}"]
    for (x, y, z), (r, g, b, _a) in zip(mesh.positions, mesh.colors):
        lines.append(f"v {x * scale:.4f} {y * scale:.4f} {z * scale:.4f} {r:.4f} {g:.4f} {b:.4f}")
    for u, v in mesh.uvs:
        lines.append(f"vt {u:.6f} {v:.6f}")
    current_obj = None
    for (obj, mat), faces in mesh.groups.items():
        if obj != current_obj:
            lines.append(f"o {obj}")
            current_obj = obj
        lines.append(f"usemtl {mat}")
        for face in faces:
            refs = [f"{p + 1}/{t + 1}" if t is not None else f"{p + 1}" for p, t in face]
            lines.append("f " + " ".join(refs))
    path.write_text("\n".join(lines) + "\n")
    mtl = []
    for mat in mesh.materials.values():
        mtl += [f"newmtl {mat.name}", "Kd 1.000 1.000 1.000"]
        if mat.texture:
            mtl.append(f"map_Kd {texture_rel}/{mat.texture}")
        mtl.append("")
    mtl_path.write_text("\n".join(mtl) + "\n")


@dataclass
class Joint:
    name: str
    parent: int | None  # index into the skeleton list; parents come first
    translation: tuple  # bind-pose offset from the parent (from the origin for a root)
    world: tuple  # bind-pose position in model space
    extras: dict = field(default_factory=dict)  # written to the glTF node's `extras`


@dataclass
class Track:
    joint: int  # index into the skeleton list
    path: str  # glTF target path: "rotation", "translation" or "scale"
    values: bytes  # little-endian f32 per key: x, y, z, w for rotation, else x, y, z
    constant: bool  # every key equals the first: written as one key


@dataclass
class Animation:
    name: str
    times: bytes  # little-endian f32 key times (seconds)
    tracks: list[Track]
    extras: dict = field(default_factory=dict)  # written to the glTF animation's `extras`


GLTF_FLOAT, GLTF_UBYTE, GLTF_UINT = 5126, 5121, 5125
GLTF_REPEAT, GLTF_CLAMP = 10497, 33071


def write_gltf(
    path: Path, mesh: Mesh, texture_rel: str, skeleton: list[Joint] | None = None, animations: list[Animation] | None = None
) -> None:
    """Binary glTF 2.0 (.glb): one mesh, a primitive per material, textures referenced as external
    PNGs, vertex colours as COLOR_0. With a skeleton, the mesh is skinned rigidly: every vertex is
    bound with weight 1 to the joint whose matrix was loaded when the vertex was (`Mesh.joints`),
    and the joints form a node hierarchy in the bind pose (translation only). `animations` (with a
    skeleton) become glTF animations with LINEAR samplers targeting the joint nodes."""
    # glTF has one index per vertex: unify (position, uv) pairs.
    unified: dict = {}
    order: list = []
    primitives_faces: dict = {}
    for (_obj, mat), faces in mesh.groups.items():
        out = primitives_faces.setdefault(mat, [])
        for face in faces:
            for ref in face:
                if ref not in unified:
                    unified[ref] = len(order)
                    order.append(ref)
                out.append(unified[ref])

    blob = bytearray()
    views: list = []
    accessors: list = []

    def add(data: bytes, comp: int, kind: str, count: int, target: int | None = None, minmax=None) -> int:
        while len(blob) % 4:
            blob.append(0)
        view = {"buffer": 0, "byteOffset": len(blob), "byteLength": len(data)}
        if target is not None:
            view["target"] = target
        views.append(view)
        blob.extend(data)
        acc = {"bufferView": len(views) - 1, "componentType": comp, "count": count, "type": kind}
        if minmax:
            acc["min"], acc["max"] = minmax
        accessors.append(acc)
        return len(accessors) - 1

    positions = [mesh.positions[p] for p, _t in order]
    attrs = {
        "POSITION": add(
            struct.pack(f"<{3 * len(order)}f", *(c for p in positions for c in p)),
            GLTF_FLOAT, "VEC3", len(order), 34962,
            ([min(p[i] for p in positions) for i in range(3)], [max(p[i] for p in positions) for i in range(3)]),
        ),
        "COLOR_0": add(
            struct.pack(f"<{4 * len(order)}f", *(c for p, _t in order for c in mesh.colors[p])),
            GLTF_FLOAT, "VEC4", len(order), 34962,
        ),
        "TEXCOORD_0": add(
            # glTF puts the texture origin top-left; the walker's v is OBJ's (bottom-left)
            struct.pack(f"<{2 * len(order)}f", *(c for _p, t in order for c in ((0.0, 0.0) if t is None else (mesh.uvs[t][0], 1.0 - mesh.uvs[t][1])))),
            GLTF_FLOAT, "VEC2", len(order), 34962,
        ),
    }
    if skeleton:
        joints = [mesh.joints[p] or 0 for p, _t in order]
        attrs["JOINTS_0"] = add(bytes(b for j in joints for b in (j, 0, 0, 0)), GLTF_UBYTE, "VEC4", len(order), 34962)
        attrs["WEIGHTS_0"] = add(struct.pack("<4f", 1.0, 0.0, 0.0, 0.0) * len(order), GLTF_FLOAT, "VEC4", len(order), 34962)

    images: list = []
    textures: list = []
    samplers: list = []
    materials: list = []
    material_index: dict = {}
    for name, mat in mesh.materials.items():
        entry = {"name": name, "pbrMetallicRoughness": {"metallicFactor": 0.0, "roughnessFactor": 1.0}}
        if mat.texture:
            sampler = {
                "wrapS": GLTF_CLAMP if mat.clamp_s else GLTF_REPEAT,
                "wrapT": GLTF_CLAMP if mat.clamp_t else GLTF_REPEAT,
            }
            if sampler not in samplers:
                samplers.append(sampler)
            images.append({"uri": f"{texture_rel}/{mat.texture}"})
            textures.append({"source": len(images) - 1, "sampler": samplers.index(sampler)})
            entry["pbrMetallicRoughness"]["baseColorTexture"] = {"index": len(textures) - 1}
            entry["alphaMode"] = "MASK"
        material_index[name] = len(materials)
        materials.append(entry)

    primitives = []
    for mat, indices in primitives_faces.items():
        acc = add(struct.pack(f"<{len(indices)}I", *indices), GLTF_UINT, "SCALAR", len(indices), 34963)
        primitives.append({"attributes": attrs, "indices": acc, "material": material_index[mat]})

    nodes: list = [{"name": path.stem, "mesh": 0}]
    gltf: dict = {
        "asset": {"version": "2.0", "generator": "tools/n64gfx.py"},
        "scene": 0,
        "scenes": [{"nodes": [0]}],
        "nodes": nodes,
        "meshes": [{"name": path.stem, "primitives": primitives}],
    }
    if skeleton:
        first = len(nodes)
        for joint in skeleton:
            node = {"name": joint.name, "translation": list(joint.translation)}
            if joint.extras:
                node["extras"] = joint.extras
            nodes.append(node)
        for i, joint in enumerate(skeleton):
            if joint.parent is None:
                gltf["scenes"][0]["nodes"].append(first + i)
            else:
                nodes[first + joint.parent].setdefault("children", []).append(first + i)
        # inverse bind matrices (column-major): the bind pose is a pure translation
        ibm = b"".join(
            struct.pack("<16f", 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -j.world[0], -j.world[1], -j.world[2], 1) for j in skeleton
        )
        roots = [first + i for i, j in enumerate(skeleton) if j.parent is None]
        skin = {"joints": [first + i for i in range(len(skeleton))], "inverseBindMatrices": add(ibm, GLTF_FLOAT, "MAT4", len(skeleton))}
        if len(roots) == 1:
            skin["skeleton"] = roots[0]
        gltf["skins"] = [skin]
        nodes[0]["skin"] = 0
        gltf_animations = []
        for anim in animations or ():
            keys = len(anim.times) // 4
            times = struct.unpack(f"<{keys}f", anim.times)
            full_input = add(anim.times, GLTF_FLOAT, "SCALAR", keys, minmax=([min(times)], [max(times)]))
            single_input = None
            samplers_a: list = []
            channels: list = []
            for track in anim.tracks:
                width = 4 if track.path == "rotation" else 3
                if track.constant:
                    if single_input is None:
                        single_input = add(struct.pack("<f", 0.0), GLTF_FLOAT, "SCALAR", 1, minmax=([0.0], [0.0]))
                    source, data, count = single_input, track.values[: 4 * width], 1
                else:
                    source, data, count = full_input, track.values, keys
                output = add(data, GLTF_FLOAT, "VEC4" if width == 4 else "VEC3", count)
                samplers_a.append({"input": source, "output": output, "interpolation": "LINEAR"})
                channels.append({"sampler": len(samplers_a) - 1, "target": {"node": first + track.joint, "path": track.path}})
            entry = {"name": anim.name, "samplers": samplers_a, "channels": channels}
            if anim.extras:
                entry["extras"] = anim.extras
            gltf_animations.append(entry)
        if gltf_animations:
            gltf["animations"] = gltf_animations
    for key, value in (("materials", materials), ("textures", textures), ("images", images), ("samplers", samplers)):
        if value:
            gltf[key] = value
    while len(blob) % 4:
        blob.append(0)
    gltf["buffers"] = [{"byteLength": len(blob)}]
    gltf["bufferViews"] = views
    gltf["accessors"] = accessors

    text = json.dumps(gltf, separators=(",", ":")).encode()
    text += b" " * (-len(text) % 4)
    body = struct.pack("<II", len(text), 0x4E4F534A) + text + struct.pack("<II", len(blob), 0x004E4942) + bytes(blob)
    path.write_bytes(struct.pack("<III", 0x46546C67, 2, 12 + len(body)) + body)


#!/usr/bin/env python3
import sys
import os
import subprocess
import difflib

def get_section_bytes(obj_path, sec_name):
    tmp = f"/tmp/{os.getpid()}_{sec_name}.bin"
    cmd = ["mips-linux-gnu-objcopy", "-O", "binary", f"--only-section={sec_name}", obj_path, tmp]
    subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if os.path.exists(tmp):
        b = open(tmp, "rb").read()
        try:
            os.remove(tmp)
        except OSError:
            pass
        return b
    return b""

def get_relocations(obj_path):
    try:
        out = subprocess.check_output(["mips-linux-gnu-objdump", "-r", obj_path], stderr=subprocess.DEVNULL).decode(errors="replace")
    except subprocess.CalledProcessError:
        return []
    lines = out.splitlines()
    if len(lines) >= 3 and ":" in lines[1]:
        lines = lines[3:]
    return lines

def get_section_sizes(obj_path):
    try:
        out = subprocess.check_output(["mips-linux-gnu-size", "-A", "-d", obj_path], stderr=subprocess.DEVNULL).decode(errors="replace")
    except subprocess.CalledProcessError:
        return {}
    sizes = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) >= 2 and parts[0].startswith("."):
            try:
                sizes[parts[0]] = int(parts[1])
            except ValueError:
                pass
    return sizes

DATA_SECTIONS = (".data", ".rodata", ".bss", ".sdata", ".sbss")

def get_text_relocs(obj_path):
    """(offset, type, target) of .text relocations."""
    out = subprocess.check_output(["mips-linux-gnu-objdump", "-r", "-j", ".text", obj_path],
                                  stderr=subprocess.DEVNULL).decode(errors="replace")
    relocs = []
    for line in out.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[1].startswith("R_MIPS_"):
            target = parts[2].split("+")[0].split("-")[0]
            relocs.append((int(parts[0], 16), parts[1], target))
    return sorted(relocs)

def text_symbols(obj_path):
    """{offset: name} for symbols defined in .text."""
    out = subprocess.check_output(["mips-linux-gnu-nm", "-n", obj_path],
                                  stderr=subprocess.DEVNULL).decode(errors="replace")
    syms = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[1] in "tT":
            syms.setdefault(int(parts[0], 16), parts[2])
    return syms

def masked_text(text, relocs):
    """.text bytes with every relocated field zeroed; targets are compared separately."""
    text = bytearray(text)
    for off, rtype, _ in relocs:
        if off + 4 > len(text):
            continue
        word = int.from_bytes(text[off:off + 4], "big")
        if rtype == "R_MIPS_26":
            word &= 0xFC000000
        elif rtype in ("R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_GPREL16"):
            word &= 0xFFFF0000
        else:
            word = 0
        text[off:off + 4] = word.to_bytes(4, "big")
    return bytes(text)

def resolve_branches(obj_path, text, relocs):
    """Resolve R_MIPS_PC16 branches to labels in the object's own .text (splat's global `jlabel`s)
    into the branch offset, as IDO emits them without a relocation; return (text, remaining relocs)."""
    # readelf, not nm: nm hides `.L`-prefixed names even when they are global symbols.
    out = subprocess.check_output(["mips-linux-gnu-readelf", "-sW", obj_path],
                                  stderr=subprocess.DEVNULL).decode(errors="replace")
    labels = {}
    for line in out.splitlines():
        p = line.split()
        # Num: Value Size Type Bind Vis Ndx Name; .text is identified by section index below.
        if len(p) == 8 and p[0].endswith(":") and p[6].isdigit():
            labels.setdefault((int(p[6]), p[7]), int(p[1], 16))
    text_ndx = text_section_index(obj_path)
    labels = {name: value for (ndx, name), value in labels.items() if ndx == text_ndx}
    text = bytearray(text)
    remaining = []
    for off, rtype, target in relocs:
        if rtype != "R_MIPS_PC16" or target not in labels:
            remaining.append((off, rtype, target))
            continue
        word = int.from_bytes(text[off:off + 4], "big")
        field = ((labels[target] - (off + 4)) >> 2) & 0xFFFF
        text[off:off + 4] = ((word & 0xFFFF0000) | field).to_bytes(4, "big")
    return bytes(text), remaining

def section_name_map(obj_path):
    """{ndx: sec_name} from section headers."""
    out = subprocess.check_output(["mips-linux-gnu-readelf", "-SW", obj_path],
                                  stderr=subprocess.DEVNULL).decode(errors="replace")
    names = {}
    for line in out.splitlines():
        line = line.replace("[ ", "[")
        p = line.split()
        if len(p) > 2 and p[0].startswith("[") and p[0].endswith("]"):
            ndx = p[0].strip("[]")
            if ndx.isdigit():
                names[int(ndx)] = p[1]
    return names

def text_section_index(obj_path):
    return next((ndx for ndx, name in section_name_map(obj_path).items() if name == ".text"), -1)

def object_section_vrams(obj_path, absolute):
    """{sec_name: vram_base} for sections in obj_path, determined from defined symbols."""
    out = subprocess.check_output(["mips-linux-gnu-readelf", "-sW", obj_path],
                                  stderr=subprocess.DEVNULL).decode(errors="replace")
    sec_ndx = section_name_map(obj_path)
    vrams = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) >= 8 and p[0].endswith(":") and p[6].isdigit():
            ndx = int(p[6])
            sec = sec_ndx.get(ndx)
            if sec in DATA_SECTIONS or sec == ".text":
                off = int(p[1], 16)
                name = p[7]
                addr = splat_address(name)
                if addr is None and name.startswith("func_"):
                    try:
                        addr = int(name[5:], 16)
                    except ValueError:
                        pass
                if addr is None and name in absolute:
                    addr = absolute[name]
                if addr is not None:
                    vrams.setdefault(sec, (addr - off) & 0xFFFFFFFF)
    return vrams

def normalise_own_section_relocs(obj_path, text, relocs, absolute, vrams=None):
    """Normalise relocations against absolute symbols that lie inside the object's own
    .rodata/.data section to section+offset, matching IDO's C output."""
    if vrams is None:
        vrams = object_section_vrams(obj_path, absolute)
    sec_sizes = get_section_sizes(obj_path)
    original = text
    text = bytearray(text)
    addends = pair_addends(original, relocs)
    norm_relocs = []
    for off, rtype, target in relocs:
        addr = splat_address(target)
        if addr is None and target in absolute:
            addr = absolute[target]
        matched_sec = None
        offset = 0
        if addr is not None and rtype in ("R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_32"):
            for sec in (".rodata", ".data"):
                if sec in vrams:
                    base = vrams[sec]
                    size = sec_sizes.get(sec, 0)
                    if base <= addr < base + size:
                        matched_sec = sec
                        offset = addr - base
                        break
        if matched_sec is not None:
            word = int.from_bytes(original[off:off + 4], "big")
            if rtype == "R_MIPS_LO16":
                value = (offset + addends.get(off, 0)) & 0xFFFFFFFF
                field = value & 0xFFFF
                text[off:off + 4] = ((word & 0xFFFF0000) | field).to_bytes(4, "big")
            elif rtype == "R_MIPS_HI16":
                value = (offset + addends.get(off, 0)) & 0xFFFFFFFF
                field = ((value + 0x8000) >> 16) & 0xFFFF
                text[off:off + 4] = ((word & 0xFFFF0000) | field).to_bytes(4, "big")
            elif rtype == "R_MIPS_32":
                value = (offset + word) & 0xFFFFFFFF
                text[off:off + 4] = value.to_bytes(4, "big")
            norm_relocs.append((off, rtype, matched_sec))
        else:
            norm_relocs.append((off, rtype, target))
    return bytes(text), norm_relocs

def resolve_targets(text, relocs, syms):
    """Replace `.text`-section jal targets with the function name at the addend."""
    resolved = []
    for off, rtype, target in relocs:
        if target == ".text" and rtype == "R_MIPS_26":
            field = int.from_bytes(text[off:off + 4], "big") & 0x03FFFFFF
            target = syms.get(field << 2, f".text+0x{field << 2:X}")
        resolved.append((off, rtype, target))
    return resolved

ABSOLUTE_SYMBOL_FILES = ("undefined_syms.us.txt", "build/undefined_syms_auto.us.txt")

def absolute_symbols():
    """{name: value} of linker-script absolute symbols: hardware registers, libultra low-memory
    globals, and splat's auto-generated labels outside every segment (e.g. D_80000000 = UT_VEC)."""
    syms = {}
    for path in ABSOLUTE_SYMBOL_FILES:
        if not os.path.exists(path):
            continue
        for line in open(path):
            parts = line.split("=")
            if len(parts) == 2 and parts[1].strip().endswith(";"):
                try:
                    syms[parts[0].strip()] = int(parts[1].strip().rstrip(";"), 0)
                except ValueError:
                    pass
    return syms

def apply_absolute(text, relocs, absolute):
    """Resolve HI16/LO16 relocations against absolute symbols into the instruction fields, as C
    constant addresses compile with no relocation; return (text, remaining relocs)."""
    original = text
    text = bytearray(text)
    remaining = []
    for i, (off, rtype, target) in enumerate(relocs):
        if target not in absolute or rtype not in ("R_MIPS_HI16", "R_MIPS_LO16"):
            remaining.append((off, rtype, target))
            continue
        word = int.from_bytes(original[off:off + 4], "big")
        if rtype == "R_MIPS_LO16":
            lo = word & 0xFFFF
        else:  # addend comes from the paired LO16 of the same symbol
            pair = next((o for o, t, s in relocs[i + 1:] if t == "R_MIPS_LO16" and s == target), None)
            lo = int.from_bytes(original[pair:pair + 4], "big") & 0xFFFF if pair is not None else 0
        value = (absolute[target] + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
        field = ((value + 0x8000) >> 16) & 0xFFFF if rtype == "R_MIPS_HI16" else value & 0xFFFF
        text[off:off + 4] = ((word & 0xFFFF0000) | field).to_bytes(4, "big")
    return bytes(text), remaining

def word_at(text, off):
    return int.from_bytes(text[off:off + 4], "big")

def splat_address(name):
    """Address of a splat `D_XXXXXXXX` label, else None."""
    if len(name) == 10 and name.startswith("D_"):
        try:
            return int(name[2:], 16)
        except ValueError:
            return None
    return None

def sext16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v

def pair_addends(text, relocs):
    """{offset: full addend} for HI16/LO16 relocations (REL: addends sit in the instructions).
    Per the MIPS ABI a HI16 pairs with the next LO16 of the same target, and a LO16 with the
    latest HI16 of its target; the full addend is (hi << 16) + sext(lo)."""
    addends = {}
    pending = {}  # target -> HI16 offsets awaiting their LO16
    last_hi = {}  # target -> latest HI16 immediate
    for off, rtype, tgt in relocs:
        imm = word_at(text, off) & 0xFFFF
        if rtype == "R_MIPS_HI16":
            pending.setdefault(tgt, []).append(off)
            last_hi[tgt] = imm
            addends[off] = imm << 16
        elif rtype == "R_MIPS_LO16":
            for hi_off in pending.pop(tgt, []):
                addends[hi_off] = ((word_at(text, hi_off) & 0xFFFF) << 16) + sext16(imm)
            addends[off] = (last_hi.get(tgt, 0) << 16) + sext16(imm)
    return addends

def same_splat_address(b_tgt, e_tgt, b_addend, e_addend):
    """False only when both targets are splat labels whose relocations resolve to different
    addresses (label + paired HI16/LO16 addend). Named targets have no known address: accepted."""
    b_addr, e_addr = splat_address(b_tgt), splat_address(e_tgt)
    if b_addr is None or e_addr is None:
        return True
    return (b_addr + b_addend) & 0xFFFFFFFF == (e_addr + e_addend) & 0xFFFFFFFF

def text_matches(built_o, expected_o):
    """Code matches if .text equals modulo relocated fields and every relocation hits the same target,
    except relocations the built object points at its own data sections (static data the C now
    defines, which expected reaches through the shared data blob); those must not hit expected code."""
    absolute = absolute_symbols()
    e_vrams = object_section_vrams(expected_o, absolute)
    b_vrams = object_section_vrams(built_o, absolute)
    for k, v in e_vrams.items():
        b_vrams.setdefault(k, v)

    b_text = get_section_bytes(built_o, ".text")
    e_text = get_section_bytes(expected_o, ".text")
    e_syms = text_symbols(expected_o)

    b_text, b_relocs = normalise_own_section_relocs(built_o, b_text, get_text_relocs(built_o), absolute, b_vrams)
    e_text, e_relocs = normalise_own_section_relocs(expected_o, e_text, get_text_relocs(expected_o), absolute, e_vrams)

    b_text, b_relocs = apply_absolute(b_text, b_relocs, absolute)
    e_text, e_relocs = apply_absolute(e_text, e_relocs, absolute)
    b_text, b_relocs = resolve_branches(built_o, b_text, b_relocs)
    e_text, e_relocs = resolve_branches(expected_o, e_text, e_relocs)
    b_relocs = resolve_targets(b_text, b_relocs, text_symbols(built_o))
    e_relocs = resolve_targets(e_text, e_relocs, e_syms)
    if len(b_relocs) != len(e_relocs) or masked_text(b_text, b_relocs) != masked_text(e_text, e_relocs):
        return False
    e_code = set(e_syms.values()) | {".text"}
    b_addends = pair_addends(b_text, b_relocs)
    e_addends = pair_addends(e_text, e_relocs)
    for (b_off, b_type, b_tgt), (e_off, e_type, e_tgt) in zip(b_relocs, e_relocs):
        if (b_off, b_type) != (e_off, e_type):
            return False
        if b_tgt in DATA_SECTIONS:
            if e_tgt in e_code:
                return False
            if e_tgt in DATA_SECTIONS:
                if b_tgt != e_tgt or b_addends.get(b_off, 0) != e_addends.get(e_off, 0):
                    return False
        elif b_tgt != e_tgt:
            # Expected may reach named data through an unnamed splat label (e.g. an array end
            # bound `sym + size` becomes D_<addr>); accept only for non-code targets, and when
            # both sides are splat labels only if they resolve to the same address (two swapped
            # externs, `D_807FBB4C == D_807FDC94` vs the reverse, passed here once).
            if not e_tgt.startswith("D_") or b_tgt in e_code:
                return False
            if not same_splat_address(b_tgt, e_tgt, b_addends.get(b_off, 0), e_addends.get(e_off, 0)):
                return False
    return True

def main():
    if len(sys.argv) < 3:
        print("Usage: objdiff.py <built.o> <expected.o> [func_name]", file=sys.stderr)
        sys.exit(1)

    built_o = sys.argv[1]
    expected_o = sys.argv[2]
    func_name = sys.argv[3] if len(sys.argv) > 3 and sys.argv[3] else None

    if not os.path.exists(built_o):
        print(f"Error: {built_o} not found", file=sys.stderr)
        sys.exit(1)
    if not os.path.exists(expected_o):
        print(f"Error: {expected_o} not found", file=sys.stderr)
        sys.exit(1)

    # 1. Compare sizes
    b_sizes = get_section_sizes(built_o)
    e_sizes = get_section_sizes(expected_o)

    mismatches = []

    # 2. Compare bytes for text, data, rodata
    for sec in [".text", ".data", ".rodata"]:
        b_bytes = get_section_bytes(built_o, sec)
        e_bytes = get_section_bytes(expected_o, sec)
        if b_bytes != e_bytes:
            mismatches.append(f"Section {sec} content mismatch (built: {len(b_bytes)} bytes, expected: {len(e_bytes)} bytes)")

    # 3. Compare BSS sizes
    if b_sizes.get(".bss", 0) != e_sizes.get(".bss", 0):
        mismatches.append(f"Section .bss size mismatch (built: {b_sizes.get('.bss', 0)}, expected: {e_sizes.get('.bss', 0)})")

    # 4. Compare relocations
    b_relocs = get_relocations(built_o)
    e_relocs = get_relocations(expected_o)
    if b_relocs != e_relocs:
        mismatches.append("Relocations mismatch")

    if not mismatches:
        print("OK")
        sys.exit(0)

    # Code matches; only this file's own static data differs from the shared-blob stub. Not a full
    # match: the full build is the gate once the file's data sections are split out. The file's
    # .rodata bytes are its own ROM bytes in both objects (REL keeps addends in place), so a
    # content difference there is a real mismatch (e.g. a C jump table losing the late_rodata pad).
    if text_matches(built_o, expected_o):
        if get_section_bytes(built_o, ".rodata") != get_section_bytes(expected_o, ".rodata"):
            print("FAILED: code matches but .rodata bytes differ (literal order/padding): "
                  "compare `objdump -s -j .rodata` of both objects", file=sys.stderr)
            sys.exit(1)
        for m in mismatches:
            print(f"note: {m}")
        print("TEXT OK (code and code/extern relocation targets match; own data sections differ)")
        sys.exit(3)

    # Mismatch found: print details
    for m in mismatches:
        print(f"FAILED: {m}", file=sys.stderr)

    # Try asm-differ if available
    diff_py = "/opt/asm-differ/diff.py"
    if not func_name:
        try:
            nm_out = subprocess.check_output(["mips-linux-gnu-nm", built_o], stderr=subprocess.DEVNULL).decode(errors="replace")
            funcs = [line.split()[-1] for line in nm_out.splitlines() if " T " in line or " t " in line]
            if funcs:
                func_name = funcs[0]
        except Exception:
            pass

    if os.path.exists(diff_py) and func_name:
        # -n: the caller already compiled built_o; asm-differ's own `make` only prints a misleading "Nothing to be done".
        cmd = [sys.executable, diff_py, "-o", "-n", "-f", built_o, "-F", expected_o, "--no-pager", func_name]
        subprocess.run(cmd)
    else:
        # Fallback to objdump diff
        d1 = subprocess.check_output(["mips-linux-gnu-objdump", "-d", "-r", built_o]).decode(errors="replace").splitlines()
        d2 = subprocess.check_output(["mips-linux-gnu-objdump", "-d", "-r", expected_o]).decode(errors="replace").splitlines()
        for line in difflib.unified_diff(d2, d1, fromfile="expected", tofile="built", lineterm=""):
            print(line)

    sys.exit(1)

if __name__ == "__main__":
    main()

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
        cmd = [sys.executable, diff_py, "-o", "-f", built_o, "-F", expected_o, "--no-pager", func_name]
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

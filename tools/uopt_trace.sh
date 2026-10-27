#!/usr/bin/env bash
#
# tools/uopt_trace.sh [-l LEVEL] [-n|--non-matching] [-s SRC_FILE] <file.c> [FUNC]
#
# Compiles a C source file (or private copy) using the trace compiler at
# /opt/ido5.3-trace/cc with IDO uopt debug flags:
#   -Wo,-l,<abs_list_path> -Wo,-zdbug:LEVEL
#
# When run on the host outside Docker, re-executes itself inside the container.
#
# Arguments:
#   -l LEVEL             uopt debug level (default: 6)
#                        5: live ranges, active candidates, interference graph, cycle savings
#                        6: priority-based register coloring trace (which register gets assigned)
#   -n, --non-matching   Compile with -DNON_MATCHING to trace C implementations parked
#                        behind #ifdef NON_MATCHING (automatically enabled if FUNC sits
#                        inside an #ifdef NON_MATCHING block).
#   -s SRC_FILE          Original source file in src/ to inherit compile flags from
#                        (required if <file.c> is a private copy outside src/ and not given as 2nd arg)
#   <file.c>             C source file to compile (under src/ or a private copy)
#   [FUNC]               Optional function name. If provided, prints only the trace
#                        section for that function. If omitted, prints the full list file.
# Outputs:
#   Object file:  build/.scratch/trace/<file_escaped>.o
#   Listing file: .scratch/trace/<file_escaped>.list (and .scratch/trace/<file_basename>.list)
#
# ==============================================================================
# HOW TO READ IDO uopt REGISTER ALLOCATION TRACES
# ==============================================================================
#
# IDO's global optimizer (uopt) performs priority-based graph coloring register
# allocation. The trace printed by -Wo,-zdbug:6 (and -Wo,-zdbug:5) provides
# detailed visibility into candidate selection, interference, and register assignment.
#
# 1. Candidate Table (between 'REMOVAL OF REDUNDANT STORES' and 'CODE MOTION'):
#    Inventories all variables and expression trees considered for register allocation:
#
#      index      bit kind    op      l      r  
#     {1296|0}      0 isvar   M   21    -4vreg
#     """           1
#     { 657|0}      2 isop    uilod{ 922|0} 
#     {1232|0}      6 isvar   M   21    -8vreg
#     {1168|0}     10 isvar   M   21   -12vreg
#     { 765|0}     16 isvar   P   21     0vreg
#
#    - 'bit': Candidate bit index (0, 1, 2, ...), which acts as the candidate ID
#      in the global coloring trace.
#    - 'kind':
#        'isvar': Program variables (locals, parameters, return registers).
#        'isop': Computed expressions / load operations (e.g. uilod, uadd, ucvt).
#    - Variable locations:
#        'M ... <offset>vreg': Local stack variable at byte offset (e.g. -4vreg, -8vreg).
#          Offsets correspond to declaration order and local frame layout.
#        'P ... <offset>vreg': Incoming parameter at byte offset (0vreg = 1st arg, 4vreg = 2nd arg).
#        'R ... <offset>vreg': Dedicated return register candidate.
#
# 2. Priority Ordering and Savings (-l 5 vs -l 6):
#    Candidates are colored in strict priority order (printed top to bottom).
#    Priority is determined by estimated execution cycle savings: the benefit of
#    keeping a variable in a register rather than loading/storing it to stack.
#    In Level 5 (-l 5), the exact savings value appears on the 'adjsave' line:
#
#      >>>active<<<{1024|0}  16   14
#      adjsave, hasstore: 2.05000000e+01  true
#      forbidden: [  1  3]
#
#    Candidates with higher 'adjsave' (e.g. 20.5 > 10.5 > 6.0) are processed first.
#    In Level 6 (-l 6), lines appear in this exact descending priority sequence:
#
#      <bit_index>:   <live_range_id> <status>  <uopt_reg_id>
#
#    Status values:
#      'assigned (constrained|unconstrained)': successfully allocated to a register.
#      'not colored (-ve save)': spilled to stack (insufficient savings or registers).
#      'live range X: Y split out Z': live range was split across basic blocks.
#
# 3. Verified uopt Register Numbering Table (uopt internal ID -> MIPS hardware register):
#    uopt uses its own 1-based internal register IDs (1..35), mapped through its
#    internal lookup table ('coloroffset' at VMA 0x10001ae0 in IDO 5.3 uopt):
#
#    Caller-Saved Integer Registers (GPRs):
#       1 -> $v0 ($2)
#       2 -> $v1 ($3)
#       3 -> $a0 ($4)
#       4 -> $a1 ($5)
#       5 -> $a2 ($6)
#       6 -> $a3 ($7)
#       7 -> $t0 ($8)
#       8 -> $t1 ($9)
#       9 -> $t2 ($10)
#      10 -> $t3 ($11)
#      11 -> $t4 ($12)
#      12 -> $t5 ($13)
#      13 -> $ra ($31)   [link register]
#
#    Callee-Saved Integer Registers (GPRs):
#      14 -> $s0 ($16)
#      15 -> $s1 ($17)
#      16 -> $s2 ($18)
#      17 -> $s3 ($19)
#      18 -> $s4 ($20)
#      19 -> $s5 ($21)
#      20 -> $s6 ($22)
#      21 -> $s7 ($23)
#      22 -> $fp / $s8 ($30)
#      23 -> $ra ($31)
#
#    Floating-Point Registers (FPU Coprocessor 1, 32-bit even pairs):
#      24 -> $f0         30 -> $f20 (callee-saved)
#      25 -> $f2         31 -> $f22 (callee-saved)
#      26 -> $f12        32 -> $f24 (callee-saved)
#      27 -> $f14        33 -> $f26 (callee-saved)
#      28 -> $f16        34 -> $f28 (callee-saved)
#      29 -> $f18        35 -> $f30 (callee-saved)
#
#    Excluded from uopt allocation:
#      - $at ($1), $k0 ($26), $k1 ($27), $gp ($28), $sp ($29) are reserved system registers.
#      - $t6 ($14), $t7 ($15), $t8 ($24), $t9 ($25) are NOT allocated by uopt; they are
#        reserved as scratch temporaries for the code generator (ugen).
#
# 4. Worked Examples:
#
#    Example A: triggerZoneInit (src/global/684C0.c)
#      Candidate Table:
#        bit 16: {1024|0} isvar M  4 -4vreg   -> var_s0
#        bit  0: { 960|0} isvar M  4 -8vreg   -> var_s1
#        bit  3: { 896|0} isvar M  4 -12vreg  -> temp_s2
#        bit 11: { 832|0} isvar M  4 -16vreg  -> temp_s3
#        bit  5: { 493|0} isvar P  4  0vreg   -> arg0
#      Coloring Trace:
#        16:   16 assigned (constrained)  14  -> var_s0  gets uopt 14 = $s0 (priority #1, adjsave 20.5)
#         0:    0 assigned (constrained)  15  -> var_s1  gets uopt 15 = $s1 (priority #2, adjsave 10.5)
#         3:    3 assigned (constrained)  16  -> temp_s2 gets uopt 16 = $s2 (priority #3, adjsave 6.0)
#        11:   11 assigned (constrained)  17  -> temp_s3 gets uopt 17 = $s3 (priority #4, adjsave 5.5)
#         5:    5 assigned (constrained)   3  -> arg0    gets uopt  3 = $a0 (priority #6, adjsave 2.0)
#
#    Example B: func_80663BE8 (draft in src/global/684C0.c)
#      Candidate Table:
#        bit 10: {1168|0} isvar M 21 -12vreg  -> subNode
#        bit  6: {1232|0} isvar M 21  -8vreg  -> subListPtr
#        bit 16: { 765|0} isvar P 21   0vreg  -> arg0
#        bit  0: {1296|0} isvar M 21  -4vreg  -> node
#      Coloring Trace:
#        10:   10 assigned (constrained)   3  -> subNode    gets uopt 3 = $a0 (passed to heapFree)
#         6:    6 assigned (constrained)   1  -> subListPtr gets uopt 1 = $v0
#        16:   16 assigned (constrained)   4  -> arg0       gets uopt 4 = $a1 (moved out of $a0)
#         0:    0 assigned (constrained)   2  -> node       gets uopt 2 = $v1
#      This trace proves why the draft allocated $v1 for node instead of $a2.
#
# 5. What Remains Unreadable / Opaque:
#    - Expression node IDs like { 657|0 } and U-Code opcodes (ucg1, uilod, ustr, uixa,
#      ules) represent compiler intermediate representation nodes and do not carry C names.
#    - Live range split IDs (e.g. 'split out 25') are compiler-generated virtual IDs.
# ==============================================================================

set -e

# Re-exec inside the toolchain container (tools/dk honours DK64_IMAGE) if run on the host
if [ ! -f /.dockerenv ] && [ ! -d /opt/ido5.3-trace ]; then
    exec "$(dirname "$0")/dk" tools/uopt_trace.sh "$@"
fi

LEVEL=6
SRC_FILE=""
NON_MATCHING=0

while [ $# -gt 0 ]; do
    case "$1" in
        -l)
            if [ -z "$2" ]; then
                echo "Error: -l requires a LEVEL argument" >&2
                exit 1
            fi
            LEVEL="$2"
            shift 2
            ;;
        -s)
            if [ -z "$2" ]; then
                echo "Error: -s requires a source file path" >&2
                exit 1
            fi
            SRC_FILE="$2"
            shift 2
            ;;
        -n|--non-matching)
            NON_MATCHING=1
            shift
            ;;
        --)
            shift
            break
            ;;
        -*)
            echo "Error: unknown option '$1'" >&2
            echo "Usage: tools/uopt_trace.sh [-l LEVEL] [-n|--non-matching] [-s SRC_FILE] <file.c> [FUNC]" >&2
            exit 1
            ;;
        *)
            break
            ;;
    esac
done

if [ $# -lt 1 ]; then
    echo "Usage: tools/uopt_trace.sh [-l LEVEL] [-n|--non-matching] [-s SRC_FILE] <file.c> [FUNC]" >&2
    exit 1
fi

FILE="${1#./}"
shift

# Mirror fdiff.sh syntax: tools/uopt_trace.sh <copy.c> <src/.../orig.c> [FUNC]
if [ -z "$SRC_FILE" ] && [ $# -ge 1 ] && [[ "$1" == *.c ]] && [[ "$1" == src/* ]]; then
    SRC_FILE="${1#./}"
    shift
fi

FUNC="$1"

if [ -z "$SRC_FILE" ]; then
    if [[ "$FILE" == src/* ]]; then
        SRC_FILE="$FILE"
    else
        echo "Error: private copy '$FILE' requires '-s src/<segment>/<file>.c' to determine compiler flags" >&2
        exit 1
    fi
fi

if [ ! -f "$FILE" ]; then
    echo "Error: input file '$FILE' not found" >&2
    exit 1
fi

if [ ! -f "$SRC_FILE" ]; then
    echo "Error: source file '$SRC_FILE' not found" >&2
    exit 1
fi

if [ ! -x /opt/ido5.3-trace/cc ]; then
    echo "Error: /opt/ido5.3-trace/cc not found or not executable" >&2
    exit 1
fi

python3 - << "EOF_PYTHON" "$FILE" "$SRC_FILE" "$LEVEL" "$NON_MATCHING" "$FUNC"
import sys, os, shlex, subprocess, re

file_c = sys.argv[1]
src_c = sys.argv[2]
level = sys.argv[3]
non_matching_flag = sys.argv[4] == "1"
func = sys.argv[5] if len(sys.argv) > 5 and sys.argv[5] else None

escaped_name = file_c.replace("/", "_")
if escaped_name.endswith(".c"):
    stem = escaped_name[:-2]
else:
    stem = escaped_name

obj_path = f"build/.scratch/trace/{stem}.o"
list_path = f".scratch/trace/{stem}.list"
abs_list = os.path.abspath(list_path)

base_stem = os.path.splitext(os.path.basename(file_c))[0]
base_list_path = f".scratch/trace/{base_stem}.list"

os.makedirs(os.path.dirname(abs_list), exist_ok=True)
os.makedirs(os.path.dirname(obj_path), exist_ok=True)

# Recover compile command from make -n
try:
    src_stem = src_c[:-2] if src_c.endswith(".c") else src_c
    p = subprocess.run(
        ["make", "-n", "-W", src_c, f"build/{src_stem}.o"],
        capture_output=True, text=True, check=True
    )
except subprocess.CalledProcessError as e:
    sys.stderr.write(f"Error running make -n for {src_c}:\n{e.stderr}\n")
    sys.exit(1)

cmd_lines = [l for l in p.stdout.splitlines() if "asm-processor" in l or "ido5.3/cc" in l]
if not cmd_lines:
    sys.stderr.write(f"Error: no compile rule found for {src_c}\n")
    sys.exit(1)
cmd = cmd_lines[-1]

# Check if target file uses GLOBAL_ASM / INCLUDE_ASM
with open(file_c, "r", errors="ignore") as f:
    content = f.read()
has_global_asm = ("GLOBAL_ASM" in content) or ("INCLUDE_ASM" in content)

def func_in_non_matching(text, fn):
    stack = []
    for line in text.splitlines():
        stripped = line.strip()
        if re.match(r"#\s*ifdef\s+NON_MATCHING\b", stripped) or re.search(r"#\s*if\s+.*defined\s*\(\s*NON_MATCHING\s*\)", stripped):
            stack.append("NM_TRUE")
        elif re.match(r"#\s*ifndef\s+NON_MATCHING\b", stripped):
            stack.append("NM_FALSE")
        elif re.match(r"#\s*if", stripped):
            stack.append("OTHER")
        elif re.match(r"#\s*else", stripped):
            if stack:
                top = stack.pop()
                if top == "NM_TRUE":
                    stack.append("NM_FALSE")
                elif top == "NM_FALSE":
                    stack.append("NM_TRUE")
                else:
                    stack.append("OTHER")
        elif re.match(r"#\s*endif", stripped):
            if stack:
                stack.pop()
        else:
            if "NM_TRUE" in stack:
                pattern = r"\b" + re.escape(fn) + r"\s*\("
                if re.search(pattern, line):
                    return True
    return False

auto_non_matching = False
if func and not non_matching_flag:
    auto_non_matching = func_in_non_matching(content, func)

use_non_matching = non_matching_flag or auto_non_matching

tokens = shlex.split(cmd)
trace_cc = "/opt/ido5.3-trace/cc"
# Note: -Wo,-l must precede -Wo,-zdbug. If -zdbug is parsed first, uopt's option
# handler immediately initializes the listfile before -l is parsed; because uopt's
# default listfile buffer is space-initialized (' '), it creates a file named " ".
zdbug_flags = [f"-Wo,-l,{abs_list}", f"-Wo,-zdbug:{level}"]
try:
    o_idx = tokens.index("-o")
except ValueError:
    sys.stderr.write(f"Error: could not find -o in compile command: {cmd}\n")
    sys.exit(1)

if "asm-processor" in cmd:
    try:
        sep1 = tokens.index("--")
        sep2 = tokens.index("--", sep1 + 1)
        as_args = tokens[sep1 + 1 : sep2]
        cflags = tokens[sep2 + 1 : o_idx]
        opt_arg = tokens[2]
        prelude = tokens[4]
    except (ValueError, IndexError):
        sys.stderr.write(f"Error: unexpected asm-processor command structure: {cmd}\n")
        sys.exit(1)
else:
    cflags = tokens[1:o_idx]
    as_args = ["mips-linux-gnu-as", "-EB", "-march=vr4300", "-mabi=32", "-mgp32", "-mfp32", "-I", "include", "-W"]
    opt_arg = "-O1" if "-O1" in cflags else "-O2"
    prelude = "include/asm_prelude.inc"

if use_non_matching and "-DNON_MATCHING" not in cflags:
    cflags.append("-DNON_MATCHING")
if has_global_asm:
    new_cmd = [
        "python3", "/opt/asm-processor/build.py", opt_arg, "--asm-prelude", prelude,
        trace_cc, "--"
    ] + as_args + ["--"] + cflags + zdbug_flags + ["-o", obj_path, file_c]
else:
    new_cmd = [trace_cc] + cflags + zdbug_flags + ["-o", obj_path, file_c]

# Run compilation
res = subprocess.run(new_cmd)
if res.returncode != 0:
    sys.stderr.write(f"Error: compilation failed with exit code {res.returncode}\n")
    sys.exit(res.returncode)

if not os.path.exists(abs_list):
    sys.stderr.write(f"Error: expected trace listing not produced at {abs_list}\n")
    sys.exit(1)

# Ensure base name list file is also updated
if os.path.abspath(base_list_path) != abs_list:
    try:
        with open(abs_list, "rb") as sf, open(base_list_path, "wb") as df:
            df.write(sf.read())
    except Exception:
        pass

# If FUNC specified, extract and print only that function's section
if func:
    start_marker = f"IN LOCAL OPTIMIZATION OF {func}"
    end_marker = f"IN REEMISSION OF {func}"
    
    matched_lines = []
    recording = False
    found = False
    
    with open(abs_list, "r", errors="replace") as f:
        for line in f:
            if not recording:
                if start_marker in line:
                    recording = True
                    found = True
                    matched_lines.append(line)
            else:
                matched_lines.append(line)
                if end_marker in line:
                    break
                    
    if not found:
        sys.stderr.write(f"Error: function '{func}' not found in trace output ({abs_list})\n")
        sys.exit(1)
        
    if use_non_matching:
        print(f"Traced NON_MATCHING definition of {func}")
    sys.stdout.write("".join(matched_lines))
else:
    # Print full listing
    if use_non_matching:
        print("Traced NON_MATCHING side (-DNON_MATCHING)")
    with open(abs_list, "r", errors="replace") as f:
        sys.stdout.write(f.read())
EOF_PYTHON

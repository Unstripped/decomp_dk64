#!/usr/bin/env python3
"""asm-differ (/opt/asm-differ/diff.py) restricted to one function: `python3 tools/asmdiff_func.py [diff.py
args] FUNC`. diff.py's `-o` mode cuts the disassembly at FUNC's start only, so with several functions in one
object it also diffs every function after it; this adds objdump's `--disassemble=FUNC` (it ends at the
symbol's size) to each objdump call that targets FUNC. tools/objdiff.py runs it when FUNC was given."""
import sys

DIFF_DIR = "/opt/asm-differ"


def function_flags(flags, restrict, func):
    """objdump flags for the dump `restrict` (the function name diff.py later cuts the dump at)."""
    return flags + [f"--disassemble={func}"] if restrict == func else flags


def main(argv):
    if not argv:
        print("Usage: asmdiff_func.py [diff.py args] FUNC", file=sys.stderr)
        return 1
    func = argv[-1]
    sys.path.insert(0, DIFF_DIR)
    import diff

    run_objdump = diff.run_objdump

    def run_func_objdump(cmd, config, project):
        flags, target, restrict = cmd
        return run_objdump((function_flags(flags, restrict, func), target, restrict), config, project)

    diff.run_objdump = run_func_objdump
    sys.argv = ["diff.py"] + argv
    diff.main()
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

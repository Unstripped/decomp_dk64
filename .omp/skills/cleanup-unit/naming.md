# Naming (phase 4 and round end)

The rules of `skill://decomp-unit/namer-brief.md`, as `tools/rename.py` subcommands. Every
subcommand takes `--dry-run` (prints `file:line:col old→new`, writes nothing); run it first.

## Who renames what

|What|Command|Who|
|---|---|---|
|local or parameter of FUNC|`uv run tools/rename.py local <copy.c> <FUNC> <old> <new>`|agent, on its copy|
|field of a struct defined in the agent's `.c` file|`uv run tools/rename.py field <copy.c> <Struct> <field> <new>`|agent, on its copy|
|field of a struct in `include/`|`uv run tools/rename.py field include/<h>.h <Struct> <field> <new>`|orchestrator, round end|
|`func_XXXXXXXX` or other function name|`uv run tools/rename.py func <seg> <old> <new>`|orchestrator, round end|
|`D_XXXXXXXX` or other global|`uv run tools/rename.py global <seg> <old> <new>`|orchestrator, round end|

Agents propose cross-file names in their report (`old -> new` + one line of evidence: what
the code does with it, from the code they read). The orchestrator applies them only once
every agent of the round is idle (a rename touches other agents' files).

## Rules (rename.py enforces the starred ones; exit 1, nothing written)

- * No name that encodes an address, offset or parameter number: `new` must not contain
  `[0-9A-F]{3,}` nor match `^(func|D|unk|sp|var|temp|arg)_?[0-9A-Fa-f]`
  (`actorTable5D0`, `setCSPPlayerField84`, `n_alSynSetParam10` are rejected).
- * `new` must not already name a symbol, macro or field in scope.
- * No reference inside a macro expansion (rename the macro instead, by hand, through the gate).
- * A function declared in `include/PR/` or `include/libultra/` is not renamed
  (`header-prototyped: <header>`): its header prototype steers -O2 callers.
- Name only what the code confirms; an uncertain behaviour keeps its splat name.
- Overlay functions and globals rename only inside `src/<seg>/` (overlay addresses collide);
  global/boot names rename in every non-libultra `src/` file. `rename.py` picks the file set
  and also renames `D_<VRAM>` references of the same address.
- `func`/`global` also update the segment's symbol file (keeping `= 0x...;` and the comment),
  point `#pragma GLOBAL_ASM` paths at `<new>.s`, `git mv` the draft, and run `protos.py gen`.
- Token renames only: never reformat, re-indent, join lines or delete code.
- Never `#pragma weak` aliases; never edit other segments' symbol files.
- Local names: describe the role (`count`, `slot`, `player`), not the register or stack slot
  (`sp34`, `var_s1`, `temp_v0`, `arg0` are what phase 4 removes). A local kept only for frame
  size is `pad` / `padN`.

## Round-end check

After the renames: `tools/dk make split`, `find src -name '*.c' -exec touch {} +`,
`tools/dk make` OK, `tools/dk make expected`, `python3 tools/unit_check.py vanished` must print
`vanished OK`, `git diff --stat` vs `git diff -w --stat` per file (a reformatted file shows
as a large difference). Commit `<seg>: name N symbols`.

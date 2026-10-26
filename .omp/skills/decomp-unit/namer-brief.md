# Naming-agent brief template

One naming agent per segment, after the matching rounds (it may run while a last agent works
on one file if it skips that agent's functions). Fill `<...>`, write it to
`local://namer-brief.md`, and give the task `context` "Read `local://namer-brief.md` FIRST
and follow it exactly". Afterwards run the checks in SKILL.md §4.

````
# Goal
Name matched functions of segment <seg> in the DK64 decomp, repo <repo root> (ALWAYS absolute
paths). Read AGENTS.md first; run build tools only via `tools/dk <cmd>`. Never commit, never
edit ok-fine. The matching agents' reports, with proposed names: `local://all-reports.md`.

# Rules
- Name only matched-C functions whose behaviour you confirmed from the code:
  `name = 0xADDR; // type:func` in `symbol_addrs.<seg>.us.txt`. Reject names that encode
  addresses, offsets or parameter numbers (`actorEnqueueTableD5D0`, `setCSPPlayerField84`,
  `n_alSynSetParam10`): leave those `func_`.
- Rename the old `func_` name in EVERY `src/` C file that uses it (overlays included). Never
  add `#pragma weak` aliases.
- Rename agent-prefixed types (`Act8CA_Node` → `AnimNode`) in the unit's files.
- Token renames only: never reformat, re-indent, join lines or delete code.
- A function prototyped by a header (`PR/libaudio.h`): renaming it drops that prototype at
  -O2 callers (missing `andi`): declare the new name with the old prototype in each caller
  file.
- Never edit `tools/`, `Makefile`, other segments' symbol files.
- Check: re-split your segment only (`tools/dk python3 -m splat split dk64.<seg>.us.yaml`),
  build `build/<seg>.text.bin build/<seg>.data.bin`, `sha1sum -c dk64.<seg>.us.sha1`.
  Renamed functions differ from `expected/` by name only; the orchestrator's full build is
  the final check.
<functions to skip: those a still-running agent owns>

# Report (final message)
Names given (`func_X -> name` + one-line reason), names rejected and why, files touched.
````

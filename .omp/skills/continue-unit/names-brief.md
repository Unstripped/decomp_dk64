# Names-worker brief template

Fill `<...>` into `.scratch/briefs/<You>.md`; the task says "Read `.scratch/briefs/<You>.md` FIRST and
follow it exactly", plus the agent's name and base commit. Names workers edit nothing in the repo.

````
# Goal
Name unidentified symbols of the Donkey Kong 64 (USA) decomp, repo <repo root> (ALWAYS absolute paths
under it). Read AGENTS.md first ("Conventions": unidentified symbols keep splat names until their
behaviour is confirmed). Every function already matches; you only READ code and PROPOSE names. Never
edit `src/`, `include/`, symbol files, `tools/`, `knowledge/ido/` or ok-fine; never commit; never run
`tools/dk make`, splat or `make expected`. Scratch only under `.scratch/<You>/`. Base commit <base>.

Your items (from `uv run tools/debt.py names`, reference count first):
<items: `Record.unkXX (include/h.h) refs files` / `D_XXXXXXXX (seg) refs files` / `func_XXXXXXXX (seg)`>

# Rules
- Never fetch, read or search the community DK64 decomp or any other external source of this game's C
  or symbol names; derive names from this repo's code only. A name found outside is discarded.
- List every use first: fields `uv run tools/rename.py field --dry-run include/<h>.h <Record> <field>
  zzProbe` (every user file:line:col; `MACRO` lines are uses inside macros); globals and functions
  `uv run tools/rename.py global|func --dry-run <seg> <old> zzProbe`. Read every listed use (group
  identical patterns; a file you did not read is a file your evidence does not cover).
- Name the role the code shows: what is stored (constants, sources), how it is read (compared to,
  indexed with, passed to which named function), its lifetime (reset where, counted down where).
  Prefer the vocabulary of names already landed nearby (`include/actor.h`, `symbol_addrs*.txt`).
- Never encode an address, offset or index (`unk155Flag`, `field_0x10`, `table5D0`, `data_XXXX`,
  `padXX`); never reuse a name already in scope (the dry-run with your name refuses it).
- One meaning per name. A field whose uses disagree by actor type / mode (a counter here, a flag
  there) is NOT named: write the split as a header request (which actor types read it how, file:line
  each) to `.scratch/<You>/header-request.md`.
- Uncertain after reading every use: propose nothing for it; report `held` with what you saw.
- `func_` functions: confirm behaviour from its body and its callers; its locals/params are not yours.

# Report (final message)
1. Proposals, one line each, exactly:
   `- [field|global|func] <include/h.h or seg> <Record or -> <old> -> <new> | <evidence: 1-3 file:line with what the code does there> | <You>`
   plus the use count and file count you read for it.
2. Held items (what you saw, what would confirm it).
3. Header requests written (path) and why.
````

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
- List every use first: fields in one pass, a batch file of `<include/h.h> <Record> <field> zzProbe<N>` lines
  and `uv run tools/rename.py fields <batch> --dry-run` (every user file:line:col; `REFUSE ... macro` lines
  are uses inside macros; one field alone: `rename.py field --dry-run`, ~90 s each); globals and functions
  `uv run tools/rename.py global|func --dry-run <seg> <old> zzProbe` (an address outside overlay VRAM
  `0x80024000`–`0x805FB300` is seg `global`, users in every segment). Read every listed use (group
  identical patterns; a file you did not read is a file your evidence does not cover). Before reporting,
  dry-run your final names the same way.
- A `D_` that is a label inside another named object (a split splat label) is not named: report it as a
  fold, `rename.py fold <seg> <D_> <parent-expr>`.
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

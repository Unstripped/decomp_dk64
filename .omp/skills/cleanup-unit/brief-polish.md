# Polish-worker brief template (file-level)

Fill `<...>` into `.scratch/briefs/<You>.md`; the task says "Read `.scratch/briefs/<You>.md` FIRST
and follow it exactly", plus the agent's name, file and base commit.

````
# Goal
Code-quality cleanup of matched C in the Donkey Kong 64 (USA) decomp, repo <repo root>
(ALWAYS absolute paths under it). Read AGENTS.md first: IDO 5.3 `-O2 -mips2`, build tools only
via `tools/dk <cmd>`, never commit, never edit `knowledge/ido/`, `include/` or ok-fine (report
instead). Every function already matches; your job is to make your file read like ordinary C
(types, names, reviews) and keep it byte-identical. Hack sites are not yours: hack workers take
them. Your file: <src/seg/file.c>, base commit <base>.
<file-specific facts: shared headers, key globals, `rank --polish` row, pending.md items for this file>

Start state (`uv run tools/quality.py status --file <file>` at the base):
<status output>

# Rules
- PRIVATE COPY: `git show <base>:<src> > .scratch/<You>/<file>.c` ONCE; never re-copy, never
  `cp` over `src`. Check: `tools/fdiff.sh .scratch/<You>/<file>.c <src>` (exit 0 = whole-object
  match; required for every kept change). Scratch only under `.scratch/<You>/`. A copy that differs
  only in relocation symbol names (exit 3 `TEXT OK` with a `relocation-equivalent` note, e.g.
  `D_807506D0[i].unk5` for a split splat label `D_807506D5[i * 6]`) passes with
  `tools/fdiff.sh --reloc-ok ...` (`RELOC-EQUIV OK`, exit 0): retire such split labels, don't keep them.
- NEVER run `tools/dk make` (any target), `make split`, splat, `./diff.sh`, `make expected`.
  A `dk: waiting for ... lock` pause is normal: wait. Never kill by pattern.
- No read left uninitialised: `uv run tools/clint.py uninit .scratch/<You>/<file>.c --base <src>`
  must exit 0 before you report. A read uninitialised in the ORIGINAL control flow (a switch
  without default, a pointer first set on a loop's first pass) that cannot be initialised without
  changing codegen is not a blocker: `review nohit` with `uninit=<n> pre-existing (original control
  flow)`. `review blocked` only when another workstream must deliver something (header, owner type).
- Never edit a line carrying `// FAKE`, `// ORIG` or `// PROTO:`.
- An untagged hack found in review gets `// FAKE: <what it steers>` on its line, reported as
  "pre-existing, now tagged" with its FINAL key (`sweep <copy> --copy-of <src>` prints it);
  it then enters the hack queue. Hidden steers count as hacks: an odd spelling chosen only for
  codegen (`(*p).f` for `p->f`, a re-read through another pointer, a value-named constant local).
- Unused locals that only reproduce a frame size are `pad`/`pad[N]`, untagged.
- Never grow or shift a shared struct. Header changes: write the exact hunk to
  `.scratch/<You>/header-request.md` and message the orchestrator (it forwards it to `TypesOwner`);
  continue with other work. A function DEFINED in your file whose prototype needs another type is
  not a header request: retype the definition and fdiff a stand-in copy (`#define PROTO_SKIP_<f>` +
  the new declaration after the includes); the orchestrator regenerates the header at merge.
  Retyping a definition other files call: deliver a bundle (owner copy + stand-in copies of the
  callers that fdiff). For a header change you need now, put a shadow header beside your copies
  (quoted includes find it first), fdiff against it, and deliver the hunk as a `.patch`.
- A `warning` site whose fix needs another file's prototype: `retype blocked` naming that owner
  file and the exact prototype change; never a silencing cast.
- Shared types to retire views with: `CamState`/`CamTargetBlock`, `SpawnNode`/`Zone`,
  `BehaviourWorkState` (0x40), `KongInventory`, PlayerStruct/PlayerState/ActorGlobalState carves
  (ok-fine `conventions/actor-struct-field-evidence`).
- Knowledge lookups: `python3 tools/quirks.py func <FUNC>` before changing a function; cite IDs.
- `lsp` (clangd, `compile_commands.json` at the repo root) resolves definitions and references.
- Keys: a removed site keeps its base key; a changed key goes in `.scratch/<You>/keymap.txt`
  (`<base key> -> <final key>` lines); a site only in your copy goes to `ledger-copy-only.txt` with
  its FINAL key (the orchestrator records at the base, re-records at the merge, then carries).
- A retyped definition: a stand-in copy (`#define PROTO_SKIP_<f>` + declaration) that fdiffs, plus
  `standin_<file>.c` for every caller file the new prototype changes; list the callers.
- File-scope edits (types, views, renamed fields, shared helpers) stale the review of every
  function that reaches them: record a fresh `review` for EVERY such function, or leave the edit
  out (header-request.md).
- A turn ends only when all three phases are done for EVERY function in scope. The budget stop
  applies only to 100+ function files and only once the request budget is really spent (then
  report a valid LEDGER for the functions done and name the phases left).
- Checkpoint as you go: append each LEDGER line to `.scratch/<You>/ledger_<file>.txt` as soon as it
  is final, and at every function boundary refresh `.scratch/<You>/status.md` (copy path, fdiff,
  uninit, ledger event count, key map, functions left), so a budget stop is mergeable as is.
- IDO findings go in the report only (rule + function + evidence + related Q-IDs).

# Phases (in order, one pass over the file each)
1. types: a file-local struct view of a shared global becomes the shared type (`include/actor.h`
   etc.); a cast becomes a real field; a missing field → header request. Fix every `warning`
   site (`retype`): change the declared type (local, parameter, return, struct field via header
   request, callee prototype via a retyped definition/bundle) so the warning disappears and fdiff
   exits 0; a cast that only silences the mismatch is not a fix (a cast is fine only where the
   value really changes type, e.g. integer address arithmetic to a pointer, or a polymorphic
   member per AGENTS.md's shared-globals rule). `python3 tools/cwarn.py list --as <src>
   .scratch/<You>/<file>.c` lists the copy's warnings; the copy must not add warnings (the merge
   gate fails). Record `views` per function changed (`func:<seg>:<name> views fixed|blocked`).
2. names: m2c names (`sp34`, `var_s1`, `temp_v0`, `phi_*`, and `argN` params too) of locals and
   params and `unkXX` fields of structs defined in your `.c` file, via
   `uv run tools/rename.py local|field ...` on the copy (`--dry-run` first); fdiff after each
   batch. Cross-file names (functions, globals, `include/` fields): propose only.
3. review: every function of the file whose state is `next=review` (or never reviewed), and every
   function your phases 1–2 touched, read top to bottom. Check: hidden steering (needless temps,
   redundant copies, odd operand order, value-named constant locals, self-assignments, re-reads
   with no purpose); casts and views a shared type would replace; control flow (gotos,
   `do {} while (0)`, fall-through tricks); declarations it calls through; m2c-shaped names;
   `clint uninit` warnings. Fix what is not a hack now (fdiff); tag a hack (rule above). Then one
   `review` LEDGER line per function, for a function you actually read in this task; never derive
   a review from a diff or an earlier note.

# Report (final message)
1. Copy path, base commit, final `fdiff` and `clint uninit` results, FAKE/goto/cfe-warning counts before → after.
2. Per function: what you changed.
3. A fenced block tagged `LEDGER`: `review`, `views`, `names` and `retype` lines only, as in
   `ladder.md` (`<site-key|func:<seg>:<name>> <method> <outcome> [note="..."]`). `retype`: `fixed`,
   `kept` with `note="tried <change>; fdiff=<1|3>"`, or `blocked` naming the missing header/owner
   change. Every reviewed function: `func:<seg>:<name> review <fixed|nohit|blocked> note="fake=<kept>/<removed>
   goto=<n> casts=<n kept> views=<ok|n left> protos=<ok|n steer> temps=<ok|n> names=<n m2c left>
   uninit=<0|n> warn=<n left>"`. Validate with `uv run tools/quality.py record --dry-run --unit U
   --agent <you> --base <base> --batch <file>` (never writes `drafts/quality/`).
4. Proposed cross-file names: `old -> new` + one-line evidence each.
5. New IDO findings (rule + evidence); header requests made; hacks tagged (keys).
````

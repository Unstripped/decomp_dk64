# Hack-worker brief template (function-level)

Fill `<...>` into `.scratch/briefs/<You>.md`; the task says "Read `.scratch/briefs/<You>.md` FIRST
and follow it exactly", plus the agent's name, functions, file and base commit.

````
# Goal
Code-quality cleanup of matched C in the Donkey Kong 64 (USA) decomp, repo <repo root>
(ALWAYS absolute paths under it). Read AGENTS.md first: IDO 5.3 `-O2 -mips2`, build tools only
via `tools/dk <cmd>`, never commit, never edit `knowledge/ido/`, `include/` or ok-fine (report
instead). Every function already matches; your job is to remove the hacks of the functions below
and keep the file byte-identical. File: <src/seg/file.c>, base commit <base>.
Functions: <FUNC (hacks, kinds) ...>
<facts: shared headers, key globals; `uv run tools/quality.py history <FUNC>` output per function;
dossier paths drafts/quality/dossiers/<seg>/<FUNC>.md>

Start state (`uv run tools/quality.py status --func <FUNC>` at the base):
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
- Never swap a hack for another hack. A new `// FAKE` only when the file's net tag count
  strictly drops.
- Drop a tag only from a construct that is ordinary C (a named temp, normal statement order).
  Dead ifs, no-op arithmetic, `volatile`, comma expressions, `do {} while (0)`, punned casts
  and value-named constant locals keep their tag while they stay.
- An untagged hack you cannot remove gets `// FAKE: <what it steers>` on its line (`kept`);
  report it as "pre-existing, now tagged" (the hack count, tagged + untagged, never rises).
  Hidden steers count as hacks: an odd spelling chosen only for codegen (`(*p).f` for `p->f`,
  a re-read through another pointer, a value-named constant local) is tagged like any other.
- Unused locals that only reproduce a frame size are `pad`/`pad[N]`, untagged (in 201B0 an
  inline ternary plus `pad[2]` replaced two FAKE temps).
- Never grow or shift a shared struct. Header changes: write the exact hunk to
  `.scratch/<You>/header-request.md` and message the orchestrator; continue with other work.
  A function DEFINED in your file whose prototype needs another type is not a header request:
  retype the definition and fdiff a stand-in copy (`#define PROTO_SKIP_<f>` + the new
  declaration after the includes); the orchestrator regenerates the header at merge.
  Retyping a definition other files call: deliver a bundle (owner copy + stand-in copies of the
  callers that fdiff). For a header change you need now, put a shadow header beside your copies
  (quoted includes find it first), fdiff against it, and deliver the hunk as a `.patch`.
- Relocation-only differences (a split splat label vs parent+offset, `D_x+4` vs `D_x4`) are
  accepted only with raw-word proof: `objdump -drz` of both objects shows equal instruction words
  except LO16/HI16 symbol+addend resolving to the same address. deadsweep's normalisation hides
  displacement and sp-offset differences; it is not proof.
- goto `kept` only with shared-tail evidence (Q0591: the target's blocks are one shared tail).
- A permuter result is a hint: rewrite it into natural C; never paste it.
- Knowledge lookups (mandatory) at every site: `python3 tools/quirks.py func <FUNC>`,
  `python3 tools/quirks.py search --symptom <tag> <words from the site or diff>`
  (`python3 tools/quirks.py tags` lists tags); cite the IDs you used.
- `lsp` (clangd, `compile_commands.json` at the repo root) resolves definitions and references.
- Start each function with `uv run tools/quality.py history <FUNC>` and its dossier
  `drafts/quality/dossiers/<seg>/<FUNC>.md` (if any). Never repeat an attempt listed there.
- Every `diagnose`/`permute`/`reconstruct`/`goto-hand` line on a site tried before carries
  `new="..."`: what this attempt tried that the dossier/history does not list (a hypothesis, a
  recipe, a spelling). `record` refuses a retry without it.
- `diagnose`/`permute`/`reconstruct` notes: concrete register/offset terms (`$s1 keeps sp+0x34`),
  not generic words (`steer`, `comma`, `re-read`).
- Score candidate bodies with `tools/dk python3 tools/variants.py try .scratch/<You>/<file>.c <src>
  FUNC <body.c>...` (no private trial scripts), and after each removal attempt run `tools/dk python3
  tools/variants.py scan <copy> <src> FUNC` (swapped comparisons, float suffixes, local widths,
  declaration order) before writing variants by hand.
- The permuter is optional. If used: `tools/permute.py run <dir> -j 2 --seconds 900` (hack-free
  weights, no stop-on-zero); record it only with `seconds>=600`.
- When the target really performs the construct (cite the asm offset: a read or store it executes,
  an empty `else` it keeps), replace `// FAKE: ...` with `// ORIG: <what the target does at 0x..>`
  and record `<base key> diagnose fixed quirks=... note="ORIG: ..."`.
- A `warning` site whose fix needs another file's prototype: `retype blocked` naming that owner
  file and the exact prototype change; never a silencing cast.
- Before keeping regalloc hacks: a named pointer local for a repeated `p->a->b` load (Q0601),
  removing coupled steers together (Q0602), an inner `switch` for a reused selector (Q0600), a
  callee's real return width (Q0486), a compare operand swap after a field rewrite (Q0604).
- Shared types to retire views with: `CamState`/`CamTargetBlock`, `SpawnNode`/`Zone`,
  `BehaviourWorkState` (0x40), `KongInventory`, PlayerStruct/PlayerState/ActorGlobalState carves
  (ok-fine `conventions/actor-struct-field-evidence`).
- Keys: a removed site keeps its base key; a changed key goes in `.scratch/<You>/keymap.txt`
  (`<base key> -> <final key>` lines); a site only in your copy goes to `ledger-copy-only.txt` with
  its FINAL key (the orchestrator records at the base, re-records at the merge, then carries).
- A retyped definition: a stand-in copy (`#define PROTO_SKIP_<f>` + declaration) that fdiffs, plus
  `standin_<file>.c` for every caller file the new prototype changes; list the callers.
- Before tagging or removing a "dead" store as a hack, read the target object: a store the target
  really performs twice is behaviour, not a steer (E4090 451398/78d921, BDEE0 unk155).
- Checkpoint as you go: append each LEDGER line to `.scratch/<You>/ledger_<file>.txt` as soon as its
  run finishes, and refresh `.scratch/<You>/status.md` (copy path, fdiff, uninit, ledger event
  count, key map, still-OPEN sites) after each function, so a budget stop is mergeable as is.
- IDO findings go in the report only (rule + function + evidence + related Q-IDs); the
  orchestrator queues them and files them once at session close.
- Touch only your functions' bodies (file-scope edits only when a site needs one; they stale
  other functions' rungs: list them).

# Phases (per assigned function, in order)
1. Dossier/history: read both; list the untried ideas.
2. `uv run tools/quality.py sweep .scratch/<You>/<file>.c --copy-of <src> -j 2`: read its `HIT`
   lines (remove/plain/cond/classify/recipe; apply by hand, fdiff each).
3. Diagnose: `tools/uopt_trace.sh -s <src> .scratch/<You>/<file>.c FUNC` for regalloc,
   `tools/dk python3 tools/as1probe.py keep|scan` for schedule; name the IDs (`quirks=`). libaudio
   (Makefile `GLOBAL_G_FILES`: 13E160…145D70, IDO 7.1 `-g`) has no uopt: compare the `-g` asm by hand.
4. Variants and natural rewrites: `variants.py scan`/`try`; `consolidate` for proto steers (delete
   the local declaration/skip define so `include/proto/` applies; fdiff); gotos with structured
   control flow (`goto-hand`; a shared tail stays `kept` citing Q0591 only with that evidence).
5. `reconstruct` when the function has 3+ non-kept sites: rewrite the body from its asm behaviour
   in natural C; fdiff; record the outcome.
6. Review of the assigned functions only, each read top to bottom (hidden steers, casts, control
   flow, names, `clint uninit`); one `review` line each.
Update the dossier `.scratch/<You>/dossier_<seg>_<FUNC>.md` (seeded from drafts/quality/dossiers/):
```
# <FUNC> (<seg>, <src>)
## Sites
<key> <kind>: what it steers in register/offset terms
## Attempts
<date> <unit> <agent> <model>: what was tried -> fdiff exit or score
## Untried ideas
<idea> (source)
## Evidence
<target asm facts with offsets>
```

# Report (final message)
1. Copy path, base commit, final `fdiff` and `clint uninit` results, FAKE/goto/cfe-warning counts before → after.
2. Per site: key, what you did, result.
3. A fenced block tagged `LEDGER`, one line per (site or function, method), exactly as in
   `ladder.md` (`<site-key|func:<seg>:<name>> <method> <outcome> [quirks=] [seconds=] [base=]
   [best=] [note="..."] [new="..."]`). A site still present uses its key in the FINAL copy (`sweep
   <copy> --copy-of <src>`), a removed site its base key; copy-only sites go to
   `.scratch/<You>/ledger-copy-only.txt`, changed keys to `keymap.txt`. `reconstruct` and `review`
   are function-level (`func:<seg>:<name>`). Rules: `diagnose` needs `quirks=`; `permute` needs
   `base= best=` and `seconds>=600` (shorter only at `best=0`); `kept` only for `classify` (`note="class
   1"`), `goto-hand` (note cites Q0591) or `retype`; a diagnosis that keeps the site is `diagnose
   nohit` (never `hit`); a site you fixed: `fixed` on the method that fixed it. Every function:
   `func:<seg>:<name> review <fixed|nohit|blocked> note="fake=<kept>/<removed> goto=<n> casts=<n kept>
   views=<ok|n left> protos=<ok|n steer> temps=<ok|n> names=<n m2c left> uninit=<0|n> warn=<n left>"`.
   Validate with `uv run tools/quality.py record --dry-run --unit U --agent <you> --base <base>
   --batch <file>` (never writes `drafts/quality/`; never copy or restore that file yourself).
4. The dossier path(s); proposed cross-file names (`old -> new` + evidence).
5. New IDO findings (rule + evidence) for the orchestrator to file; header requests made.
````

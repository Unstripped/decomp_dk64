# Cleanup-agent brief template

Fill `<...>` into `local://cleanup-brief.md`; each task says "Read `local://cleanup-brief.md`
FIRST and follow it exactly", plus the agent's name, file and base commit.

````
# Goal
Code-quality cleanup of matched C in the Donkey Kong 64 (USA) decomp, repo <repo root>
(ALWAYS absolute paths under it). Read AGENTS.md first: IDO 5.3 `-O2 -mips2`, build tools only
via `tools/dk <cmd>`, never commit, never edit `knowledge/ido/`, `include/` or ok-fine (report
instead). Every function already matches; your job is to make your file read like ordinary C
and keep it byte-identical. Your file: <src/seg/file.c>, base commit <base>.
<file-specific facts: shared headers, key globals, earlier rounds' findings for this file>

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
- Every `tools/permute.py run` with `-j 2 --seconds <600..1800>`.
- Knowledge lookups (mandatory) at every site: `python3 tools/quirks.py func <FUNC>`,
  `python3 tools/quirks.py search --symptom <tag> <words from the site or diff>`
  (`python3 tools/quirks.py tags` lists tags); cite the IDs you used.
- `lsp` (clangd, `compile_commands.json` at the repo root) resolves definitions and references.
- Never re-stamp old evidence: each LEDGER line comes from a run on THIS copy (uopt_trace,
  as1probe, permute); cite an earlier round's IDs only alongside your own fresh run. Keep the
  permute dirs and trace files under `.scratch/<You>/` (the orchestrator spot-checks them).
- `diagnose`/`permute`/`reconstruct` notes: concrete register/offset terms (`$s1 keeps sp+0x34`),
  not generic words (`steer`, `comma`, `re-read`): a later knowledge entry sharing the words stales them.
- A `warning` site whose fix needs another file's prototype: `retype blocked` naming that owner
  file and the exact prototype change; never a silencing cast.
- Before keeping regalloc hacks: a named pointer local for a repeated `p->a->b` load (Q0601),
  removing coupled steers together (Q0602), an inner `switch` for a reused selector (Q0600), a
  callee's real return width (Q0486), a compare operand swap after a field rewrite (Q0604).
- Shared types to retire views with: `CamState`/`CamTargetBlock`, `SpawnNode`/`Zone`,
  `BehaviourWorkState` (0x40), `KongInventory`, PlayerStruct/PlayerState/ActorGlobalState carves
  (ok-fine `conventions/actor-struct-field-evidence`).
- Keys: a removed site keeps its base key; a changed key goes in the base→final map; a site only in
  your copy goes to `ledger-copy-only.txt` with its FINAL key (the orchestrator records at the base,
  re-records at the merge, then carries).
- A retyped definition: a stand-in copy (`#define PROTO_SKIP_<f>` + declaration) that fdiffs, plus
  `standin_<file>.c` for every caller file the new prototype changes; list the callers.
- Re-review tasks: keep file-scope edits (types, views, renamed fields) out unless you re-read every
  function they reach; each one you leave stale goes into the next re-review pass. Rev11B/C/D kept
  edits body-only and left no stale reviews: do the same; file-scope changes go to header-request.md.
- Before tagging or removing a "dead" store as a hack, read the target object: a store the target
  really performs twice is behaviour, not a steer (E4090 451398/78d921, BDEE0 unk155).
- A turn ends only when all five phases are done for EVERY function. Workers stopping after
  ~10 requests with "partial" on 54–86-function files was wrong: the budget stop applies only to
  100+ function files and only once the request budget is really spent (then report a valid
  LEDGER for the functions done and name the phases left).

# Phases (in order, one pass over the file each)
1. types: a file-local struct view of a shared global becomes the shared type (`include/actor.h`
   etc.); a cast becomes a real field; a missing field → header request. Fix every `warning`
   site (`retype`): change the declared type (local, parameter, return, struct field via header
   request, callee prototype via a retyped definition/bundle) so the warning disappears and fdiff
   exits 0; a cast that only silences the mismatch is not a fix (a cast is fine only where the
   value really changes type, e.g. integer address arithmetic to a pointer, or a polymorphic
   member per AGENTS.md's shared-globals rule). `python3 tools/cwarn.py list --as <src>
   .scratch/<You>/<file>.c` lists the copy's warnings; the copy must not add warnings (the merge
   gate fails). Then `uv run tools/quality.py sweep .scratch/<You>/<file>.c --copy-of <src> -j 2`
   and read its `HIT` lines (apply hits by hand, fdiff each); its `WARN` lines are the copy's
   warning-site keys.
2. defake: for each OPEN site in `status` order (tagged and untagged), climb the ladder until
   the site is fixed or every required method is fresh (`ladder.md` table, printed below):
   <paste the "Required fresh methods per kind" table from ladder.md>
   - `remove`/`plain`/`cond`/`classify`: done by the sweep; re-run it after phase 1 changes.
   - `diagnose`: `tools/uopt_trace.sh -s <src> .scratch/<You>/<file>.c FUNC` for regalloc,
     `tools/dk python3 tools/as1probe.py keep|scan` for schedule; name the IDs (`quirks=`).
   - `permute`: `tools/permute.py setup <seg> FUNC --from .scratch/<You>/<file>.c --src <src>
     --out .scratch/<You>/perm_<FUNC>` after removing the site, then `run ... -j 2 --seconds 900`,
     `best ...`; record `seconds= base= best=`. Start each `run` as its own background command
     (several `&` jobs in one shell loop ran only the last one).
   - `reconstruct` (functions with 3+ non-kept sites): rewrite the function body from its
     asm behaviour in natural C; fdiff; record the outcome.
   - `consolidate` (`proto-steer`/`implicit-steer`): delete the local declaration/skip define
     so the shared `include/proto/` prototype applies; fdiff.
3. gotos: rewrite with structured control flow (`goto-hand`); a shared tail the compiler
   produced from one block stays (`kept`, cite Q0591) only with that evidence.
4. names: m2c names (`sp34`, `var_s1`, `temp_v0`, `phi_*`, and `argN` params too) of locals and params and
   `unkXX` fields of structs defined in your `.c` file, via
   `uv run tools/rename.py local|field ...` on the copy (`--dry-run` first); fdiff after each
   batch. Cross-file names (functions, globals, `include/` fields): propose only.
5. review: read EVERY function top to bottom, also those with no sites. Check:
   hidden steering (needless temps, redundant copies, odd operand order, value-named constant
   locals, self-assignments, re-reads with no purpose); casts and views a shared type would
   replace; control flow (gotos, `do {} while (0)`, fall-through tricks); declarations it
   calls through; m2c-shaped names; `clint uninit` warnings. Each problem: fix it now (fdiff)
   or make it a site (`other`; its key is in the output of `uv run tools/quality.py sweep
   .scratch/<You>/<file>.c --copy-of <src>`: `status` reads `src/` only) and take it through
   phases 2–4. Then one `review` LEDGER line per function, for a function you actually read in
   this task; never derive a review from a diff or an earlier note.

# Report (final message)
1. Copy path, base commit, final `fdiff` and `clint uninit` results, FAKE/goto/cfe-warning counts before → after.
2. Per site: key, what you did, result.
3. A fenced block tagged `LEDGER`, one line per (site or function, method), exactly as below.
   Keys hash the site's code, local names included: a site still present uses its key in the
   FINAL copy (`sweep <copy> --copy-of <src>`), a site you removed uses its base key; sites that
   exist only in your copy resolve after the merge: put their lines in `.scratch/<You>/ledger-copy-only.txt`
   and give a `base key -> final key` map for every site whose key changed (required). `views`, `names`,
   `reconstruct` and `review` are function-level: key `func:<seg>:<name>`. Finish
   every permute run before reporting (an OPEN rung reopens the file next round):
   `<site-key|func:<seg>:<name>> <method> <outcome> [quirks=Q1,Q2] [seconds=N] [base=N] [best=N] [note="..."]`
   methods `remove plain cond classify consolidate diagnose permute reconstruct goto-hand
   views names review retype`; outcomes `hit fixed nohit kept blocked`. Rules: `diagnose` needs
   `quirks=`; `permute` needs `base= best=` and `seconds>=600` (shorter only when it stopped at `best=0`); `kept` only for `classify`
   (`note="class 1"`), `goto-hand` (note cites Q0591) or `retype`. `warning` sites take only
   `retype`: `fixed`, `kept` with `note="tried <change>; fdiff=<1|3>"` (the attempted fix and its
   fdiff exit), or `blocked` with a note naming the missing header/owner change. A diagnosis that keeps the site is
   `diagnose nohit` (never `hit`: `hit` reopens the site as next=apply). A site you fixed:
   `fixed` on the method that fixed it. Every function: `func:<seg>:<name> review <fixed|nohit|blocked>
   note="fake=<kept>/<removed> goto=<n> casts=<n kept> views=<ok|n left> protos=<ok|n steer>
   temps=<ok|n> names=<n m2c left> uninit=<0|n> warn=<n left>"`.
   Validate the block before reporting with `uv run tools/quality.py record --dry-run --unit U
   --agent <you> --base <base> --batch <file>` (never writes `drafts/quality.jsonl`; never copy
   or restore that file yourself).
4. Proposed cross-file names: `old -> new` + one-line evidence each.
5. New IDO findings (rule + evidence) for the orchestrator to file; header requests made.
````

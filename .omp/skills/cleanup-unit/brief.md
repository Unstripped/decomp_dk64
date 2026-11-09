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
  match; required for every kept change). Scratch only under `.scratch/<You>/`.
- NEVER run `tools/dk make` (any target), `make split`, splat, `./diff.sh`, `make expected`.
  A `dk: waiting for ... lock` pause is normal: wait. Never kill by pattern.
- No read left uninitialised: `uv run tools/clint.py uninit .scratch/<You>/<file>.c --base <src>`
  must exit 0 before you report.
- Never swap a hack for another hack. A new `// FAKE` only when the file's net tag count
  strictly drops.
- Drop a tag only from a construct that is ordinary C (a named temp, normal statement order).
  Dead ifs, no-op arithmetic, `volatile`, comma expressions, `do {} while (0)`, punned casts
  and value-named constant locals keep their tag while they stay.
- An untagged hack you cannot remove gets `// FAKE: <what it steers>` on its line (`kept`).
- Never grow or shift a shared struct. Header changes: write the exact hunk to
  `.scratch/<You>/header-request.md` and message the orchestrator; continue with other work.
- goto `kept` only with shared-tail evidence (Q0591: the target's blocks are one shared tail).
- A permuter result is a hint: rewrite it into natural C; never paste it.
- Every `tools/permute.py run` with `-j 2 --seconds <600..1800>`.
- Knowledge lookups (mandatory) at every site: `python3 tools/quirks.py func <FUNC>`,
  `python3 tools/quirks.py search --symptom <tag> <words from the site or diff>`
  (`python3 tools/quirks.py tags` lists tags); cite the IDs you used.
- `lsp` (clangd, `compile_commands.json` at the repo root) resolves definitions and references.

# Phases (in order, one pass over the file each)
1. types: a file-local struct view of a shared global becomes the shared type (`include/actor.h`
   etc.); a cast becomes a real field; a missing field → header request. Then
   `uv run tools/quality.py sweep .scratch/<You>/<file>.c --copy-of <src> -j 2` and read its
   `HIT` lines (apply hits by hand, fdiff each).
2. defake: for each OPEN site in `status` order (tagged and untagged), climb the ladder until
   the site is fixed or every required method is fresh (`ladder.md` table, printed below):
   <paste the "Required fresh methods per kind" table from ladder.md>
   - `remove`/`plain`/`cond`/`classify`: done by the sweep; re-run it after phase 1 changes.
   - `diagnose`: `tools/uopt_trace.sh -s <src> .scratch/<You>/<file>.c FUNC` for regalloc,
     `tools/dk python3 tools/as1probe.py keep|scan` for schedule; name the IDs (`quirks=`).
   - `permute`: `tools/permute.py setup <seg> FUNC --from .scratch/<You>/<file>.c --src <src>
     --out .scratch/<You>/perm_<FUNC>` after removing the site, then `run ... -j 2 --seconds 900`,
     `best ...`; record `seconds= base= best=`.
   - `reconstruct` (functions with 3+ non-kept sites): rewrite the function body from its
     asm behaviour in natural C; fdiff; record the outcome.
   - `consolidate` (`proto-steer`/`implicit-steer`): delete the local declaration/skip define
     so the shared `include/proto/` prototype applies; fdiff.
3. gotos: rewrite with structured control flow (`goto-hand`); a shared tail the compiler
   produced from one block stays (`kept`, cite Q0591) only with that evidence.
4. names: m2c names (`sp34`, `var_s1`, `temp_v0`, `phi_*`, `argN`) of locals and params and
   `unkXX` fields of structs defined in your `.c` file, via
   `uv run tools/rename.py local|field ...` on the copy (`--dry-run` first); fdiff after each
   batch. Cross-file names (functions, globals, `include/` fields): propose only.
5. review: read EVERY function top to bottom, also those with no sites. Check:
   hidden steering (needless temps, redundant copies, odd operand order, value-named constant
   locals, self-assignments, re-reads with no purpose); casts and views a shared type would
   replace; control flow (gotos, `do {} while (0)`, fall-through tricks); declarations it
   calls through; m2c-shaped names; `clint uninit` warnings. Each problem: fix it now (fdiff)
   or make it a site (`other`, key from `uv run tools/quality.py status --func FUNC` on the
   copy) and take it through phases 2–4. Then one `review` LEDGER line per function.

# Report (final message)
1. Copy path, base commit, final `fdiff` and `clint uninit` results, FAKE/goto counts before → after.
2. Per site: key, what you did, result.
3. A fenced block tagged `LEDGER`, one line per (site or function, method), exactly:
   `<site-key|func:<seg>:<name>> <method> <outcome> [quirks=Q1,Q2] [seconds=N] [base=N] [best=N] [note="..."]`
   methods `remove plain cond classify consolidate diagnose permute reconstruct goto-hand
   views names review`; outcomes `hit fixed nohit kept blocked`. Rules: `diagnose` needs
   `quirks=`; `permute` needs `seconds>=600 base= best=`; `kept` only for `classify`
   (`note="class 1"`) or `goto-hand` (note cites Q0591). A site you fixed: `fixed` on the
   method that fixed it. Every function: `func:<seg>:<name> review <fixed|nohit|blocked>
   note="fake=<kept>/<removed> goto=<n> casts=<n kept> views=<ok|n left> protos=<ok|n steer>
   temps=<ok|n> names=<n m2c left> uninit=<0|n>"`.
4. Proposed cross-file names: `old -> new` + one-line evidence each.
5. New IDO findings (rule + evidence) for the orchestrator to file; header requests made.
````

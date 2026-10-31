# Troubleshooting (SKILL.md: read on a failure listed here)

## Lost or interrupted agents

- **Subagent usage limit** (`usage_limit_reached`, or OpenRouter `402 ... requires more
  credits`): every running agent fails at its next wake, every queued or new `task` within
  ~1 s. Salvage as after a crash (below), probe with a
  one-line task before relaunching, and meanwhile finish naming / ROADMAP / ok-fine inline
  (mechanically obvious names, e.g. matrix builders read straight off the C, need no agent).
  ROADMAP must say the rounds stopped early (not by the stop rule) and which files still
  have unattempted functions. When quota returns, regenerate `local://brief.md` from the
  template and resume rolling dispatch from HEAD; finish with a second status refresh.
- **Aborted dispatch** (interrupt, crash, usage limit): whole-file `fdiff` of a mid-edit copy
  says nothing (other functions broken or uncompilable); score each assigned function with
  `tools/dk python3 tools/deadsweep.py score .scratch/<A>/<f>.c src/<seg>/<f>.c FUNC`. For
  `full=0` ones, revert the copy's other assigned functions to their pragmas in a new
  `.scratch/<A>Salv/` copy and gate it (`--base <its commit>`); save the rest as drafts when
  their copy score beats the stored draft's (`score --body drafts/...`), score in the note
  (effect unit: 3 matches out of 4 dead copies). Or relaunch fresh copies from HEAD telling
  the agent to harvest its C from the `.old` copy (bonus/race unit: 30 functions matched).
- **Orchestrator session disposed**: subagents die with it. Keep the unclaimed dispatch
  queue in `.scratch/queue.md` (lists, large functions) so a new session resumes from disk.
  `local://` files of the old session stay on disk (`~/.omp/.../sessions/<id>/local/`): copy
  brief/findings/tasks into the new session. Relaunch every task with "continue from your
  existing copy"; give each surviving copy's base (the recent commit whose file differs
  least from it: `git show <c>:<f> | diff - copy | wc -l`), and finish a half-merged gate first.
- Check `git status` for unrelated work (a parallel session in the same tree): stage only the
  unit's files, never `git add -A`. A gate failing while `git status` shows a modified `src`
  file outside the merge is that session mid-edit: `git checkout` nothing of it; re-run
  `tools/merge_gate.sh - - <your file>` once `tools/dk make` passes again (boss 6240.c).

## Namer broke the build

Find the object that changed: `git stash`, `tools/dk make`, copy `build/global.map` aside,
`git stash pop`, rebuild, and compare section sizes between the two maps. Usual causes: a
lost header prototype (missing `andi` at callers), a deleted function
(`unit_check.py vanished`), or a partial re-split (run the whole `tools/dk make split`).
An `undefined reference to D_<addr>` in an overlay link after naming: some C file takes the
function's address as data (`extern u8 D_8071A038[]`); grep `D_<addr>` for every new name
and point it at the function (`void name(); p = (s32)name;`).

## Missing asm while agents run

`make split` (yours, the namer's, or a parallel session's) deletes
`asm/<seg>/nonmatchings/<file>/<FUNC>.s` of every function matched since the agents' base
commit, so their copies stop compiling. Run
`tools/restore_split_asm.sh <oldest running base or split commit> dk64.<seg>.us.yaml` right
after it (copies back every missing `.s`, never overwrites; after your own split run both under
one lease: `tools/dk --hold sh -c 'tools/dk make split && tools/restore_split_asm.sh <base> <yaml>'`),
then tell running agents not to re-copy from `src`.

## Environment

- `tools/dk` fails with `no space left on device`: Docker's disk is full. Ask the user before
  pruning anything; after a prune rebuild the image (`docker build -t dk64-decomp .`, ~75 s).
- Each `tools/dk` call gets its own fresh `/tmp`, which does not survive between calls, so
  objdump-and-diff must be one `tools/dk sh -c '...'`.
- `dk: ...` with exit 125 is a dkd error, not the command's: `tools/dk --status` shows the
  server, lock holders and queue; `tools/dk --stop` stops it (the next call starts a new one). After a
  `docker build` the next `tools/dk` call (image id cached ≤5 s) restarts the server once
  running locked jobs finish. A stuck holder shows in `--status`: never kill other agents'
  jobs, ask the user.
- The persistent shell keeps `set -e` between calls: use it only inside `sh -c`.
- Probe/test files belong in `.scratch/`. Agents still write probes to the repo root (`s.s`,
  `cur.s`) and once overwrote the tracked `t.s`: `git status` after each gate, restore
  tracked probes from HEAD, move untracked strays into `.scratch/`.
- fdiff does not resolve symbols: a misspelled extern passes fdiff and breaks the link; the
  gate catches it.

## Tools

- `tools/permute.py setup global FUNC --src .scratch/<A>/<f>.c` fails with a type
  redeclaration when the stored draft repeats a typedef the copy has: pass `--from` a file
  with only the function body, or drop the typedef from the draft. Without a draft and with
  `--src src/...`, base.c is the asm (score 0 at once, nothing searched).
- `drafts.py collect` can replace a noted draft with a note-less `_best.c`: `git diff drafts/`
  after it.
- `drafts.py prune` prunes every segment (it deleted another session's global drafts):
  scope pruning with `unit_check.py drafts --prune src/<seg>/*.c`.
- ok-fine from Python eval: `r = await tool.write({'path': 'xd://mcp__ok_fine_read_concept',
  'content': json.dumps({...})})`; the payload is `r['details']['xdev']['inner']['structuredContent']`
  (`r['text']` is elided past ~90 KB). `write_concept` takes `frontmatter` (object) and `body`:
  copy both from the read, drop `verified`/`generated`, append sources and body, pass
  `expectedRevision`. `cp` into `xd://` fails; `cp` into `local://` works.
- `local://` paths resolve in the bash tool only: Python `subprocess` (e.g. `ledger.py record
  --task`) needs the session's real local dir (the path `write('local://x')` returns).
- `make NON_MATCHING=1` ending in `global.gz ... exceed segment size` is expected (parks
  change code size); only its compile and link errors matter.

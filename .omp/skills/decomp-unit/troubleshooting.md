# Troubleshooting (SKILL.md: read on a failure listed here)

## Lost or interrupted agents

- **Subagent usage limit** (`usage_limit_reached`): every running agent fails at its next
  wake and every new `task` within ~2 s. Salvage as after a crash (below), probe with a
  one-line task before relaunching, and meanwhile finish naming / ROADMAP / ok-fine inline
  (mechanically obvious names, e.g. matrix builders read straight off the C, need no agent).
  ROADMAP must say the rounds stopped early (not by the stop rule) and which files still
  have unattempted functions. When quota returns, regenerate `local://brief.md` from the
  template and resume rolling dispatch from HEAD; finish with a second status refresh.
- **Aborted dispatch** (interrupt or crash): `tools/fdiff.sh` every surviving
  `.scratch/<Name>/` copy. Merge the passing ones (`--base <its commit>`; check the stage of
  anything parked); move the others to `.scratch/<Name>.old/` and relaunch fresh copies from
  HEAD telling the agent to harvest its per-function C from the `.old` copy. Mid-edit copies
  rarely pass as they are.
- Check `git status` for unrelated work (a parallel session in the same tree): stage only the
  unit's files, never `git add -A`.

## Namer broke the build

Find the object that changed: `git stash`, `tools/dk make`, copy `build/global.map` aside,
`git stash pop`, rebuild, and compare section sizes between the two maps. Usual causes: a
lost header prototype (missing `andi` at callers), a deleted function
(`unit_check.py vanished`), or a partial re-split (run the whole `tools/dk make split`).

## Missing asm while agents run

`make split` (yours, the namer's, or a parallel session's) deletes
`asm/<seg>/nonmatchings/<file>/<FUNC>.s` of every function matched since the agents' base
commit, so their copies stop compiling. Run
`tools/restore_split_asm.sh <oldest running base or split commit> dk64.<seg>.us.yaml` right
after it (copies back every missing `.s`, never overwrites), then tell running agents not to
re-copy from `src`.

## Environment

- `tools/dk` fails with `no space left on device`: Docker's disk is full. Ask the user before
  pruning anything; after a prune rebuild the image (`docker build -t dk64-decomp .`, ~75 s).
- Each `tools/dk` call is a fresh container: `/tmp` does not survive between calls, so
  objdump-and-diff must be one `tools/dk sh -c '...'`.
- The persistent shell keeps `set -e` between calls: use it only inside `sh -c`.
- Probe/test files belong in `.scratch/`. Older tracked probes in the repo root (`test_*.c`,
  `t.s`, `tl.c`): ask the user before removing them.
- fdiff does not resolve symbols: a misspelled extern passes fdiff and breaks the link; the
  gate catches it.

## Tools

- `tools/permute.py setup global FUNC --src .scratch/<A>/<f>.c` fails with a type
  redeclaration when the stored draft repeats a typedef the copy has: pass `--from` a file
  with only the function body, or drop the typedef from the draft. Without a draft and with
  `--src src/...`, base.c is the asm (score 0 at once, nothing searched).
- `drafts.py collect` can replace a noted draft with a note-less `_best.c`: `git diff drafts/`
  after it.
- ok-fine writes with large bodies, from Python eval:
  `r = await tool.write({'path': 'xd://mcp__ok_fine_read_concept', 'content': json.dumps(...)})`;
  the payload is `r['details']['xdev']['inner']['structuredContent']` (`r['text']` is elided).
  `write_concept` takes `frontmatter` (object) and `body`: copy both from the read, drop
  `verified`/`generated`, append sources and body, pass `expectedRevision`. `cp` into `xd://`
  fails; `cp` into `local://` works.

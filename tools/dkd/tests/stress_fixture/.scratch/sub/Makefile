# Worktree-style sub-build: cwd is /dk64/.scratch/sub, so dkd must NOT lock it (classify_make -> none).
ID ?= x
SLEEP ?= 0.1

all:
	@python3 /dk64/fx/ev.py run unlocked $(ID) $(SLEEP)

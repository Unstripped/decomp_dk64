# schedStartTask (global, src/global/13980.c)
## Sites
global:8060F960:other:6090eb other: `task = sc->audioListHead; if (sc->audioListHead == NULL) return;` tested the field just copied into task so the head load stays an expression in v0 (lw v0,0x264(a0) +0x18, beqz v0 +0x1c, move s1,v0 in the delay slot +0x20, lw t6,0(v0) +0x24). FIXED 2026-11-17: NULL test on task, pop written through the field (`sc->audioListHead = sc->audioListHead->next;`, the idiom schedTaskDone uses for the gfx list), fdiff 0.
## Attempts
2026-11-10 round 10 CleanGlobal13980 anthropic/claude-opus-5-5:low: task == NULL without the head copy (fdiff 1), permuter (best=0 only via the head copy), uopt_trace -l6 (task == NULL swaps sc/task between s0/s1) -> nohit
2026-11-12 round 26 CleanGlobal13980 anthropic/claude-opus-5-5: uopt_trace -l6 (kept form branches on the ilod expression so as1 puts move s1,v0 in the beqz delay slot), permuter 148 iterations (best=0 only restores the field re-read) -> nohit
2026-11-13 round 38 CleanGlobal13980 anthropic/claude-opus-5-5:xhigh: uopt l5/l6 (ilod cand 8 -> v0, adjsave 3.0), permuter from task == NULL (best=0 restores the field test + dead if (sc) {}) -> nohit
2026-11-17 2026-11-17: cleanup CleanschedStartTask CleanschedStartTask anthropic/claude-opus-5-5: variants.py try with task->next as the pop base: task == NULL / !task / (task = head) == NULL / nested task != NULL full 15 (lw s0,0x264(a0): task coloured straight into the single-use load, sc/task swap s0/s1); field guard first then task = head full 14 (beqzl v0 + lw ra, move after the branch, sc/task swap); field guard first + inline pop full 4 (only beqzl, move s1,v0 after lw t6) -> nohit
2026-11-17 same unit: copy first, test on task, pop through the field (`sc->audioListHead = sc->audioListHead->next`) with task == NULL / !task / (task = head) == NULL: full 0 -> FIXED (task == NULL kept), fdiff 0, uninit 0, cwarn 0
## Untried ideas
Retype SchedStruct.audioListTail/gfxListTail to `TaskNode **` (append `*tail = task; tail = &task->next;`): would drop the (TaskNode *)&sc->xListHead sentinel casts in schedCreate/schedStartTask/schedTaskDone; header + 4 functions, a types item, not a hack (this unit)
## Evidence
0xce0 frame 0x38, s0 = sc (move s0,a0 at +0x8), s1 = task (both arms), a1 tested at +0x10 (bnez a1 -> gfx arm at +0x50)
Audio arm before osGetTime uses the argument/temp registers, not the saved copies: lw v0,0x264(a0) +0x18, lw t6,0(v0) +0x24, addiu t8,a0,0x264 +0x28, sw t6,0x264(a0) +0x30 (delay slot of bnez t6), sw t8,0x26c(a0) +0x34
The head load needs two occurrences of `sc->audioListHead` across the copy block and the pop block to become an expression candidate (v0) with task as its copy; one occurrence (task->next) colours task straight into the load
Gfx arm: lw s1,0x268(s0) +0x58 scheduled between lbu t9 (D_80746828) and beqzl t9 (+0x5c, li t3,1 in the likely slot)

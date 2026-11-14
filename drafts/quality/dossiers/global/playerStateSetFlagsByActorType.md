# playerStateSetFlagsByActorType (global, src/global/EFDC0.c)

## Sites
global:806F03C4:dead-if:3a645f .. 3a645f#8 dead-if: eight `if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}` right after the switch join. Each survives uopt as one fjp and reaches ugen as `beq $4,0,Lnext; Lnext:` ($4 = a0 = gActivePlayerActor loaded at 0x5304/0x5308). as1 counts each as an XBB source block, then deletes it. Eight of them push the default arm (0x5470) out of the entry block's XBB candidate window, so the entry block's load-use stall at 0x5318 (after `lw t6,88(a0)`) stays unfilled. Without them as1 hoists the default arm's `lui t9,%hi(gCurrentPlayerIndex)` into 0x5318 (full=4, text 2/reloc 2).

## Attempts
2026-11-14 HackplayerStateSetFlagsByActorType anthropic/claude-opus-5-5:high: quality sweep of copy -> 0 hits (remove/cond/classify/recipe nohit, class 2).
2026-11-14 same: uopt_trace -l5 base vs natural -> identical candidate table and coloring; the guard reads are candidate {1521|0} (already in a0). Only a0's live range grows from 8 to 32 bbs. A Q0601 named-local route therefore cannot replace them: they have no ring/priority effect.
2026-11-14 same: guard count/placement: 4/6/7 guards after switch full=4 (8 minimal); one guard in default arm full=4 (lui still hoists from the split block); guard before switch full=104; one guard per case arm full=46; `if (X) {}`, `X && X`, `(void)(X && X && X)` in default/after switch full=4; nested triple / else-if chain full=10.
2026-11-14 same: reconstruct: Actor* local 52, PlayerState* local 182, PlayerStruct* slot local 116/140 (after/before switch), per-case yaw call 275, ternary case5 4, no default 179, default first 132, default before case6 22, case6 falls through to default 161. variants scan of natural body: best 4 (swap x2, ev u32).

## Untried ideas
- A C construct that ugen emits as several as1-visible, later-deleted blocks from one statement (would let one tagged line replace eight). No candidate known: nested/else-if/4+-term chains leave real code (Q0548).
- Raising the default arm's XBB rank through weight (control depth) without code change: no C producer known; do-while(0) wrapper changes registers (ido-backend-record-pipeline#7).

## Evidence
- Target 0x5304-0x5554 (expected/build/src/global/EFDC0.o): entry `lw t6,88(a0)` at 0x5314, `addiu t7,t6,-2` at 0x5318 (stall unfilled); default arm 0x5470 `lui t9 / lbu t9 gCurrentPlayerIndex / lui t6 / lw t6 gPlayerSlots ... addu v1` falls into join 0x5498.
- Natural body: `lui t9,%hi(gCurrentPlayerIndex)` moved to 0x5318, every later address +4 until 0x5474.
- .rodata jump table 0x244-0x254 (5 entries: 0x533c, 0x5370, 0x53a0, 0x53f0, 0x543c); no default entry, so the default label has one predecessor.

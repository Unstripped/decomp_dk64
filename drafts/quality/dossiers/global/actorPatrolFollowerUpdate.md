# actorPatrolFollowerUpdate (global, src/global/B1F60.c)

## Sites
global:806AD260:dead-if:8d0120 dead-if: `if (gCurrentActor->state) {}` put the first switch in its own basic block, so the second switch's PRE temp of `gCurrentActor->state` (uopt cand 23, v0, `move v0,a0` at 0x90) avoided interfering with the bb6 gCurrentActor load (cand 14). Without it 23 took v1, `&gCurrentActor` (cand 73) took a3, and targetId (cand 0) went uncoloured: it reloaded with `lh a1,34(sp)` instead of `move a3,t6` at 0xc and `move a1,a3` at 0x64. FIXED.
global:806AD260:other:1ae4f9 other: in case 1, `actor = gCurrentActor;` re-read before `actor->unk155++`, which put the reloaded pointer in a2 (`lw a2,0(v1)` at 0x1f0). FIXED.

## Attempts
2026-11-14 U HackactorPatrolFollowerUpdate anthropic/claude-opus-5-5: dropped the `Actor *actor` local entirely and read gCurrentActor at every use (Q0132). That fixed both sites, with whole-file fdiff OK and clint uninit 0. Other bodies scored with variants.py try (full lines):
- removing only the dead if: 248
- `s32`/`s16` state selector local: 248 and 236
- `u8`/`u16` state selector local: 46
- `switch (actor->state)`: 102
- actor hoisted to the entry: 252
- first block merged into one `&&` test, through actor or gCurrentActor: 252 and 266
- `if (skipStep)`: 248
- case-1 stores through actor: 181
- gCurrentActor only in case 1: 248
- actor local kept but gCurrentActor used in the switch cases: 26 or 68
- no actor anywhere: 0

## Untried ideas
none (function clean)

## Evidence
targetId sign-extends into a3 (`sll a3,a0,16; sra t6,a3,16; move a3,t6`, 0x4-0xc) and is passed as `move a1,a3` at 0x64. The gCurrentActor value sits in a2 at 0x4c and 0x7c and is used in the cases: `lhu t1,106(a2)`, `lbu t8,341(a2)`, `move a0,a2`, and `sb t3,340(a2)`. After the speedY store (`swc1 $f10,192(t6)` at 0x1ec), case 1 reloads it with `lw a2,0(v1)` at 0x1f0.

# menuCharacterSelectUpdateActor (menu, src/menu/3E10.c)
## Sites
menu:8002CB18:dead-if:60c986 dead-if: `if (gCurrentActor->state != 0) {}` kept the state PRE reload coloured to t0 beside the 3b7dc3 test (with 3b7dc3 alone the shared A->unk154 candidate moves t0->v1). FIXED (removed).
menu:8002CB18:dead-if:3b7dc3 dead-if: `if (sub174->parent->flags && sub174->parent->flags) {}` emitted ugen `lw $24,0($17); lw $2,96($24)` after the state reload (both deleted by as1 as dead) = one hidden $24 step in the ugen scratch ring. FIXED (removed).
## Attempts
2026-11-14 U HackmenuCharacterSelectUpdateActor anthropic/claude-opus-5-5:high: both tests removed (72 = ring-only diff after the if(idx != unk155) join); ringfifo sim: target join queue t9 t7 t1 t2 t3 t4 t5 t6 t8, copy t8 t9 t7 ... -> one $24 allocation needed after the reload's `lw $14`. Statement-order permutations of the spawn block (>=77), sel/idx/shouldDespawn widths, inline q/sub blocks (24..104), row spellings `[(u8)]`/`[(s32)]`/`+ state` (72): no. `f32 *row = &gMenuKongSlotPositions[gCurrentActor->state * 2]` on a flat `f32` table: ugen `mul $24,$8,2; mul $25,$24,4` (as1 folds to `sll 3`) -> fdiff 0, uninit 0.
## Untried ideas
none needed.
## Evidence
target 4f18 `lui t7,%hi(gMenuKongSlotPositions)` / 4f20 `sll t9,t0,0x3` (index t9, base t7); 4fc4 `lw t8,0(v1)` = $24 last in the queue. kf/t.s line 245-248: `mul $24,$8,2; mul $25,$24,4; la $15,...; addu $2,$25,$15`.

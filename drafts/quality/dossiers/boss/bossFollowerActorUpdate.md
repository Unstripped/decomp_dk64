# bossFollowerActorUpdate (boss, src/boss/DAA0.c)
## Sites
boss:80032B08:dead-if:37830d `if (anim->animId == 1) {}` in the 37/26-frame arm: only needed while 2cf154 is present. Removed alone: 373 diff lines (frame 0x38 -> 0x40, gCurrentActor address s1 -> s0 at 0x106c, parentState/anim spilled to 56/52(sp)). Removed together with 2cf154: 3 lines (only the 0x23 colour, same as 2cf154 alone).
boss:80032B08:dead-if:9bbff8 `if (D_80035B18) {}` between the x and z stores of the mirrored arm: class 1 kept (terminal). It lowers the oppSide*2 index candidate (umpy{oppSide}{2}) from adjsave 4.0 to 2.0 (an extra block in its range, Q0523), so oppSide (2.5) is coloured first into v0 and the index into v1 (0x1520-0x1564). Removed (with the other two): oppSide v1 / index v0, 9 lines.
boss:80032B08:dead-if:2cf154 `if (link->unk5 && link->unk5) {}` between the tintR and tintG stores: makes the link->unk5 load (uilod{477}, bit 15, adjsave 1.5) a candidate coloured v0 across the mirrored arm, so the hoisted 0x23 constant finds v0/v1/a0 forbidden and takes a1 (li a1,35 at 0x156c; sb a1,362/363 at 0x15c0/0x15c8). Removed: li v0,35 / sb v0 (3 lines).
## Attempts
2026-11-11 round 16 Rev16E opus:low: sweep rungs; diagnose ef8234/a4a11d (old keys); permute from v_rfo (both colouring guards removed): copy temps / no-op mask only; reconstruct v_rfo (const 35 in v0).
2026-11-12 round 29 CleanBossDAA0 opus:low: views (Actor), names (link/anim), diagnose 37830d/2cf154, permute best=0 only with copy temps (new_var = anim, new_var = oppSide).
2026-11-14 HackbossFollowerActorUpdate opus:high (base 33e47a4e, after the sfx prototype change):
- 7-subset ablation: anim 373, B18 12, unk5 3, anim+B18 12, anim+unk5 3, B18+unk5 9, all 9.
- uopt_trace -l 5 on base / anim+unk5 removed / all removed: priorities above.
- 0x23 colour (anim+unk5 removed): u8/s32 `tint` local (3), chained tintR = tintG (18), tintB spelled 0x23 * 2 (3), link->unk5 read once into a local at the top (u8 44, s8 184, s32 180) or before the second test (115), oppSide spellings (3); variants.py scan (53 recipes) all 3.
- oppSide/index swap (all removed): oppSide widths (s16/s8/u8/u16 51, u32 9), declared at function top or block start (9), `> 3` (9), `oppSide - 4`, `+= -4`, `2 +`, split `+= 2`, assignment in the condition (9), operand order of the x/z sums (9), parentState->unk14 - 2 (8), while (3 but adds a loop); variants.py scan all 9.
- Q0498 check: D_80035B10/18/20 are used only in this file (B18/B20 only here, B10 only here), but as function-local statics they would be emitted at the function position, after D_80035B60, breaking the .data order (0x80035B10-0x80035B27 sit before D_80035B28); not applicable without carving the whole table block.
- Permuter perm_all3 from the all-three-removed body: 900 s, baseline 65, best 15 (output-15-1 re-adds a dead `if (!parentState->unk14) {}` at the 9bbff8 position; same 3-line const 35 diff as keeping 9bbff8); no zero.
## Untried ideas
Merging BossSpawnState and BossFollowerLink (same layout, bossSpawnerUpdate's view) is a file-scope edit outside this function; it would not change codegen here.
## Evidence
Target 0x1518-0x15d0: lb v0,20(t2); addiu v0,v0,2; slti at,v0,4; bnezl at,0x153c / sll v1,v0,1; addiu v0,v0,-4; sll v1,v0,1; li a1,35 at 0x156c; sb a1,362(t4) 0x15c0; sb a1,363(t5) 0x15c8; li t6,70 / sb t6,364(t9).
Second unk5 test reloads link->unk5 into t6 (lb t6,5(t0) at 0x132c/0x134c), so the dead test adds no code.

# arcadeUpdateOilDrumEntity (arcade, src/arcade/0_game.c)
## Sites
arcade:8002E3D4:other:61428a other (kept): `s32 n` is the only declared word. Case 2: the barrel-count limit
  `n = arcadeMinFloat(gArcadeLevel, 5.0f)` (trunc.w.s, mfc1 v0 0xa4c8, move a2,v0 0xa4d4), stored to its home 0x24
  across arcadeCountEntitiesByType (sw a2,0x24(sp) 0xa530, lw 0xa534). Case 3: the new fireball slot
  (`n = arcadeFindFreeEntitySlot36()`: v0, sll t4,v0,5 / addu v1 at 0xa5bc/0xa5c0, register only). A separate slot local
  keeps frame 0x28 but moves the a1 (&gArcadeEntities[entIndex]) temp spill 0x1c -> 0x18 (rulings.md near miss).
## Attempts
2026-11-18b Polisharcade0b anthropic/claude-opus-5-5:xhigh: pre-existing untagged reuse, tagged by lead ruling; separate slot local moves the a1 spill 0x1c -> 0x18.
2026-11-24 2026-11-24: cleanup CleanarcadeUpdateDonkeyKongStage4 CleanarcadeUpdateDonkeyKongStage4 anthropic/claude-opus-5-5 (base 2e593510, re-measure after 05c5a664):
  - s32 slot after n -> 8 (a1 spill 0x1c -> 0x18 at 0xa414/0xa418, 0xa4b4/0xa4cc, 0xa528/0xa538, 0xa59c/0xa5dc only);
    slot first -> 10; slot block-scoped in the `animTimer++ > 40.0f` block -> 8; n block-scoped in the
    gArcadeFrozen block plus block slot -> 8.
  - `ArcadeEntity *fireball = &gArcadeEntities[arcadeFindFreeEntitySlot36()]; *fireball = gArcadeFireballTemplate;`
    with `fireball->` for every slot access (Q0601), function or block scope -> 8 (case-3 code identical, v1 = fireball);
    declared before n -> 10.
  - width grid n x slot (s32/u32/s16/u16/s8/u8, both orders, 72 bodies): best 8; narrow slot adds conversions (>= 43),
    narrow n (>= 73).
## Untried ideas
- none from the local asm: the frame (0x28, n home 0x24, a1 spill 0x1c) admits one declared word, and both roles need
  a 32-bit holder. Open for a director ruling only (rulings.md near miss: count stored to its own home, slot register only).
## Evidence
0xa3dc addiu sp,sp,-40; ra 0x14; a1 spill sw/lw 0x1c (0xa414/0xa418, 0xa4b4/0xa4cc, 0xa528/0xa538, 0xa59c/0xa5dc);
0xa4d4 move a2,v0 (n); 0xa530 sw a2,0x24(sp) / 0xa534 lw a2,0x24(sp) around arcadeCountEntitiesByType; 0xa540 slt at,v0,a2;
case 3: 0xa5bc sll t4,v0,0x5, 0xa5c0 addu v1,t4,t5 (slot base for the template copy and every field store).

# arcadeUpdateOilDrumEntity (arcade, src/arcade/0_game.c)
## Sites
arcade:8002E3D4:other:61428a other (removed 2026-11-25c, R-oildrum census: the reuse is ordinary C, tag dropped, base key):
  `s32 n` is the only declared word. Case 2: the barrel-count limit
  `n = arcadeMinFloat(gArcadeLevel, 5.0f)` (trunc.w.s, mfc1 v0 0xa4c8, move a2,v0 0xa4d4), stored to its home 0x24
  across arcadeCountEntitiesByType (sw a2,0x24(sp) 0xa530, lw 0xa534). Case 3: the new fireball slot
  (`n = arcadeFindFreeEntitySlot36()`: v0, sll t4,v0,5 / addu v1 at 0xa5bc/0xa5c0, register only). A separate slot local
  keeps frame 0x28 but moves the a1 (&gArcadeEntities[entIndex]) temp spill 0x1c -> 0x18 at every position.
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
2026-11-25c continue-lead-2 CleanarcadeUpdateOilDrumEntity anthropic/claude-opus-5-5 (base 9fb6f661):
  - frame census from the cfe ucode (as1probe keep + ucode --cfe): the target's 0x20 word is cfe's shared vreg -8,
    not a free word (see Evidence); every extra declared word pushes that vreg to -12 and the a1 spill to 0x18.
  - `s32 n; register s32 slot;` -> 8 (`register` keeps the home), `register s32 slot; s32 n;` -> 10,
    block `register s32 slot` in the `animTimer++ > 40.0f` block -> 8 (cfe: slot -8, vreg -12, a1 spill sw $5,24($sp)),
    `register s32 n; s32 slot;` -> 8.
  - entity pointer local `ArcadeEntity *entity = &gArcadeEntities[entIndex]` for every entIndex access, n + slot,
    six placements (n/slot/entity, n/entity/slot, slot/n/entity, init at declaration, entity first, entity block-scoped)
    -> 8 each: entity is copy-propagated (the a1 value stays a uopt spill temp at 0x1c), its own home adds a word:
    frame 0x28 -> 0x30, n 0x24 -> 0x2c, plus `li t3,2` / `sw a1` / `swc1 $f18` reorder at 0xa578-0xa5a4.
  - variants.py scan --max 0 over the split base (`s32 n; s32 slot;`, 87 variants: truth, switch, swap, arith, elem,
    float, width, declswap) -> best 8 (no variant below the split's 8).
  - R-oildrum three-part census (director 2026-11-25c, `.scratch/lead3/rule_reuse_census.md`): all three parts hold,
    `// FAKE` comment removed from `s32 n;` (no other change), fdiff 0, clint uninit exit 0, cwarn 0. Table below.
## R-oildrum census (bodies in .scratch/CleanarcadeUpdateOilDrumEntity/census/, scores `variants.py try`, frame/slots from
## `as1probe keep` t.s, cfe offsets from `as1probe ucode --cfe`; target: frame 40, a1 spill $5@28, n $6@36, cfe vreg -8)
Part 1, frame proof (a separate `slot` local for the case-3 role; `n` keeps the case-2 role):
| body | position | score | frame | a1 spill | n home | cfe shared vreg |
|---|---|---|---|---|---|---|
| F1 | function scope, after n | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| F2 | function scope, before n | 10 | 0x28 | 0x1c -> 0x18 | 0x24 -> 0x20 | -8 -> -12 |
| F3 | `register`, after n | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 (slot -8) |
| F4 | `register`, before n | 10 | 0x28 | 0x1c -> 0x18 | 0x24 -> 0x20 | -8 -> -12 (slot -4) |
| K1 | block: `if (gArcadeFrozen == 0)` block | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| K2 | same, `register` | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| K3 | block: head of the state switch body | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| K4 | same, `register` | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| K5 | block: braced `case 3:` arm | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| K6 | same, `register` | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| K7 | block: `animTimer++ > 40.0f` block | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| K8 | same, `register` | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| N1 | n in braced case-2 arm, slot in braced case-3 arm (siblings) | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| N2 | n then slot in the gArcadeFrozen block | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| N3 | slot then n in the gArcadeFrozen block | 10 | 0x28 | 0x1c -> 0x18 | 0x24 -> 0x20 | -8 -> -12 |
| N4 | n in braced case-2 arm, slot in the `> 40.0f` block | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
| N5 | slot at function scope, n in braced case-2 arm | 10 | 0x28 | 0x1c -> 0x18 | 0x24 -> 0x20 | -8 -> -12 |
| N6 | n then slot at the head of the state switch body | 8 | 0x28 | 0x1c -> 0x18 | 0x24 | -8 -> -12 |
Earlier units (same signature): width grid n x slot 72 bodies best 8; slot block-scoped -> 8; n + slot in the frozen block -> 8.
Every split keeps frame 0x28 but adds a cfe home, pushes cfe's shared vreg -8 -> -12 and the a1 spill 0x1c -> 0x18;
the slot's own home is never touched in the asm. Holds at every position.
Part 2, no-local proof (no separate integer local for the case-3 slot):
| body | spelling | score | what differs |
|---|---|---|---|
| X1 | `gArcadeEntities[arcadeFindFreeEntitySlot36()]` inline at each of the 9 uses | 187 | 9 calls, different slots (behaviour) |
| X2 | slot written into the drum's `param2` field, `gArcadeEntities[gArcadeEntities[entIndex].param2]` at each use | 139 | extra sb/lbu, clobbers the flicker toggle (behaviour) |
| X3 | function-local `static s32 slot;` (no stack word) | 4 | frame/spills kept, extra `sw v0,slot` to .bss after the call (target stores nothing) |
| X4 | `ArcadeEntity *fireball = &gArcadeEntities[call]`, function scope after n | 8 | a1 spill 0x1c -> 0x18, vreg -12 |
| X5 | same pointer, before n | 10 | a1 spill 0x1c -> 0x18, n 0x24 -> 0x20 |
| X6 | same pointer, block-scoped in the `> 40.0f` block | 8 | a1 spill 0x1c -> 0x18 |
| X7 | `fireball = gArcadeEntities + call` | 8 | a1 spill 0x1c -> 0x18 |
(also entity pointer `ArcadeEntity *entity = &gArcadeEntities[entIndex]`, 6 placements: 8, frame 0x30.)
Part 3, plausibility (copy lines): n is `s32`; role 1 = arcadeMinFloat's f32 (proto 0_game.h:34) truncated to s32
(trunc.w.s 0xa4b8, used signed: `0x64 - n * 0x14`, `slt at,v0,a2` 0xa540); role 2 = arcadeFindFreeEntitySlot36's s32
(proto 0_game.h:49, index: sll t4,v0,5 0xa5bc). Role 1: def 2865, uses 2867/2868, all inside `case 2:` (2856-2874),
which ends in `break;` 2874. Role 2: def 2879, uses 2880-2893, all inside `case 3:`'s `animTimer++ > 40.0f` block
(2876-2895). No loop; the state switch (2855) runs one case per call; each role is read only after its own def on the
same path, so neither role's value reaches the other's region, and n is dead at exit. Target regions: case 2
0xa454-0xa558, case 3 0xa55c-0xa6cc (dispatch beq 0xa43c / beql 0xa444).
Hidden-reuse check (director item 2026-11-25c): no other local or parameter takes a second value (entIndex is never
reassigned; n is the censused site above). None.
## Untried ideas
- none: the census is complete (frame 0x28 = args 0x00-0x0f, save area 0x10-0x17 with ra 0x14, local area 0x18-0x27:
  n -4 (0x24), cfe vreg -8 (0x20), a1 spill -12 (0x1c), round-up 0x18).
## Evidence
0xa3dc addiu sp,sp,-40; ra 0x14; a1 spill sw/lw 0x1c (0xa414/0xa418, 0xa4b4/0xa4cc, 0xa528/0xa538, 0xa59c/0xa5dc);
0xa4d4 move a2,v0 (n); 0xa530 sw a2,0x24(sp) / 0xa534 lw a2,0x24(sp) around arcadeCountEntitiesByType; 0xa540 slt at,v0,a2;
case 3: 0xa5bc sll t4,v0,0x5, 0xa5c0 addu v1,t4,t5 (slot base for the template copy and every field store).
cfe ucode (base 9fb6f661): n = M -4; one `vreg s32 Mmt off -8 lexlev 1` first declared at the `param2 = !param2` line and
reused for the outer switch selector, both param2 switch selectors, the `0x64 - n * 0x14 == animTimer++` and
`animTimer++ > 40.0f` compare results (str/lod -8); cfe assigns it after every declared home (block-scoped included),
so the uopt spill temps start at -12 = 0x1c. Words 0x18 (local-area round-up) and 0x10 (save-area pad) are below the
spill temps / outside the local area and cannot host a declared local.

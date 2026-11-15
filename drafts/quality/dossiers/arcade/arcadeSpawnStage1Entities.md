# arcadeSpawnStage1Entities (arcade, src/arcade/0.c)
## Sites
arcade:80027F0C:other:b3e1d6 other: oilDrumY = 110.0f constant local; steers as1 order of the D_8004A718 struct-copy lw/sw pairs around swc1 $f0 (0x4384) / $f2 (0x43d4).
arcade:80027F0C:other:6ec87d other: i = 0 early + i = i + 0x24 keeps i in v1 (li v1,36 at 0x41b4) instead of constant-folded addresses.
## Attempts
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: i = 0x24 at entry -> 122; s8/u8/s16/u16 i -> 348-406; u32 i -> 159; i = 0x25 with D[i--] / D[i]; i-- / i -= 1 -> 159 (folded); i as one earlier spawn index (7 placements) -> 159-185
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: oilDrumY at entry -> 0 (same steer moved); before D_8004A638 copy -> 39; at use -> 39; inline y store before x -> 45
## Untried ideas
uopt_trace -l 3/4 on i = 0 + i += 0x24 vs i = 0x24 to see why a constant first def blocks propagation into the D_8004BCD0 indices; a loop over the four D_8004A718 entities (param n, x = 48 if n & 1, y = 65 if n & 2) in case IDO unrolls and hoists the 48.0f/65.0f constants ($f0/$f2 at 0x4148/0x4158)
## Evidence
0x4198 addiu t1,t1,1184 (D_8004BCD0[0x25] folded); 0x41b4 li v1,36 then addiu v1,v1,-1 per entity; 0x42d8/0x42e0 68.0f/110.0f loaded just before swc1 0x42f0/0x42f4.

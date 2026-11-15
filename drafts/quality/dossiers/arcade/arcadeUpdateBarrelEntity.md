# arcadeUpdateBarrelEntity (arcade, src/arcade/0.c)
## Sites
arcade:8002CD64:other:3b7b19 other: FIXED (e pointer removed, all-indexed).
arcade:8002CD64:other:01fb7f other: FIXED (separate idx local).
## Attempts
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: all-indexed, floorY reused -> 88; all-indexed + idx -> 66; e kept + idx -> 17 (v1 spill 0x2c -> 0x28)
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: + case 7 sum reordered (-vx * 0.2 first) -> 4; + y += vy in cases 3/5/7 -> 0; + compound assignments and 18 redundant casts dropped -> fdiff 0
## Untried ideas
none (function hack-free)
## Evidence
frame 0x40: declared words 0x38/0x3c (floorY at 0x3c, sw v0 at 0x8df0); temps v1 (&D_8004BCD0[entIndex]) 0x2c, arcadeMinFloat result 0x30 (0x9020), arcadeRand result 0x34 (0x93b8).
case 7: target calls arcadeRand (0x937c) before arcadeMinFloat (0x93b4); this order comes from the -vx * 0.2 term written first.
y += vy: add.s $f4,$f16,$f2 at 0x912c, lwc1 0xc(v1) before 4(v1) at 0x91f4, add.s $f18,$f16,$f2 at 0x92d4.

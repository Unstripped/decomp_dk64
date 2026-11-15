# arcadeUpdateDonkeyKongStage3 (arcade, src/arcade/0.c)
## Sites
- arcade:80030044:other:56b8d0 (fixed): `tmp = 0;` before the D_8004C71D test was a dead first def of the reused temp; it gave the case-2 path a candidate ahead of the animTimer trunc so D_8004C6DC lands in a0 and the trunc in a1. Replaced by a named `frame` local for the D_8004C6DC read; `tmp` renamed `timer`.
## Attempts
- 2026-11-15 U HackarcadeUpdateDonkeyKongStage3 anthropic/claude-opus-5-5:high: plain removal 19; if/else-if chain instead of switch 63; u8 tmp 75; flash from tmp 29; no tmp 79; separate `state` local for the switch 19 (all decl orders); `tmp = D_8004C6DC % 120` 36; `tmp = D_8004C71D` 33; `tmp = D_8004C6DC; tmp % 120` 0 (reuse); separate `frame = D_8004C6DC; frame % 120` 0 in all three decl orders -> applied.
## Untried ideas
- none (function clean).
## Evidence
- 0xc08c `lw a0,0(a0)` (D_8004C6DC) reused by `andi t9,a0,0x1` at 0xc1d8 on the case-2 path; 0xc130 `mfc1 a1,$f8` is the animTimer trunc shared by `andi t3,a1,0xff` (0xc138) and `andi v0,a1,0x20` (0xc144).

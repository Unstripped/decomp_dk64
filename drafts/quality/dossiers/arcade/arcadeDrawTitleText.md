# arcadeDrawTitleText (arcade, src/arcade/0.c)
## Sites
- none (FAKE). One `// LAYOUT` (tagged 2026-11-17 HackarcadeDrawHud): `if (D_8004C6DC & 0x182) D_8004C6D0 = D_80032C20;`
  keeps the then-arm store on the if line.
## Attempts
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawHud HackarcadeDrawHud anthropic/claude-opus-5-5:
  - `s32 titleBitmap[12] = { ... };` local initialiser replaces the ArcadeTitleBitmap struct view + D_8004A798 global:
    RELOC-EQUIV OK (template stays at .data+8, `addiu t7,t7,%lo(.data+8)` at 0x2698).
  - `(s32)((f64)(i * 8 + 0x3F) * 4.0)` -> `(i * 8 + 0x3F) * 4.0`: fdiff 0 (s16 parameter conversion).
  - if/else layout: then-arm on its own line (braces, four-line, braced then + one-line else) text=2; whole if/else on one
    line text=2; ternary `D_8004C6D0 = (D_8004C6DC & 0x182) ? D_80032C20 : D_80032DF8;` text=2; only the then-store on the
    if line matches (else arm may be braced or not).
## Untried ideas
- none for the LAYOUT: as1probe shows a pure .loc effect.
## Evidence
- as1probe scan of the split form: `delete 100` (`.loc 2 224`, the then-store's line) or `swap 99,100` -> full 2 text 0
  (reloc 2 = the .data template name only); split form schedules `addiu v0,v0,%lo(D_8004C6D0)` after
  `addiu t8,t8,%lo(D_80032C20)` instead of before it.

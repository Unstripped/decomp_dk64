# arcadeUpdatePlayerEntity (arcade, src/arcade/0.c)
## Sites
- arcade:8002B89C:dead-if:5f684d (kept until the .bss carve lands): the dead read of D_8004BC84 stretches the &D_8004BC84 address web, so uopt does not colour it. The target rematerialises `lui` for the load at 0x8924 and the store at 0x8944. Real cause: D_8004BC84 is a function-local `static` (uopt isvar S, no lda web, one lui/%lo pair per access, Q0761/Q0922).
- arcade:8002B89C:dead-if:e534b2 (kept until the .bss carve lands): the same for &D_8004BC80 (0x797c-0x79a8, 0x79fc-0x7a28, 0x8370-0x8388, 0x83d8-0x83f0, 0x8908-0x892c). Real cause: D_8004BC80 is a function-local `static` too.
## Attempts
- 2026-11-14 opus:high (full=):
  - removal: 14 / 27 / 37
  - phase spellings: 19-121
  - early phase read: 335
  - coll call moved before the counter block: 27
- 2026-11-15 U HackarcadeUpdateDonkeyKongStage3 opus:high: file-local struct view `{s32 timer; s32 phase;}` at D_8004BC80 (D_8004BC84 -> .phase, one address web): both guards kept 20, both removed 36, 5f684d removed alone 20, e534b2 removed alone 36.
- 2026-11-15 U HackarcadeUpdatePlayerEntity anthropic/claude-opus-5-5:high: function-local `static s32` for both counters, both guards removed:
  - original phase spelling (`phase = D_8004BC84 + 1; if (phase == 7) phase = 0; D_8004BC84 = phase;`): text=7 (uopt folds the compare to `load == 6`, li a1 not in the bne delay slot);
  - `D_8004BC84++; if (D_8004BC84 == 7) D_8004BC84 = 0; phase = D_8004BC84;` (and the `if (++D_8004BC84 == 7)` form): text=0, reloc=24 (only the .bss relocations);
  - other spellings: `phase = X; phase++;` / `if ((phase = X + 1) == 7)` / `if (++phase == 7)` text=7; ternary text=90; no `phase` temp text=43;
  - the same text=0 spelling with the extern globals: no guards text=70, block-scope extern text=70, guard 5f684d only text=70, guard e534b2 only text=47.
  - stand-in `standin_carve_0.c` (statics named sStepTimer/sStepPhase, `ArcadeLift D_8004BC88[6];` defined in the TU): fdiff exit 3 TEXT OK; raw objdump -drz: 14472/14472 .text words equal except 24 .bss HI16/LO16 words that resolve to .bss+0 (D_8004BC80) / .bss+4 (D_8004BC84). TU .bss = 0x50 bytes: statics at +0/+4, D_8004BC88 at +8 (72 bytes).
  - probe: `ArcadeLift D_8004BC88[3]; ArcadeLift D_8004BCAC[3];` gives .bss 0x60 (D_8004BCAC 8-aligned to +0x30, Q0967): D_8004BCAC is a splat label inside one `ArcadeLift D_8004BC88[6]` (the lift loop runs i < 6).
## Untried ideas
- None for the C side. Landing needs the yaml .bss carve 0x8004BC80-0x8004BCD0 (lead's call), then paste standin_carve_0.c's hunks.
## Evidence
- Target accesses of D_8004BC80/84 each use their own `lui` (e.g. 0x8908 `lui t4,%hi(D_8004BC80)` / 0x890c lw; 0x8914 `lui v0,%hi(D_8004BC84)` / 0x8924 lw; 0x8928 `lui at` / 0x892c sw zero; 0x8944 `lui at` / 0x8950 sw v0) with no shared address register: the Q0922 signature of a function-local static.
- Only users of D_8004BC80/84 in the repo: arcadeUpdatePlayerEntity (src/arcade/0.c); data in asm/arcade/data/26C00.bss.s.
## Proposed names
- D_8004BC80 -> sStepTimer (function-local static): +3 per walking frame (0x797c-0x79a8 left, 0x79fc-0x7a28 right), +2 per climbing frame (0x8370-0x8388, 0x83d8-0x83f0); at >= 0x24 (0x8908-0x891c) reset and play sound 0x40.
- D_8004BC84 -> sStepPhase (function-local static): cycles 0..6 on each step sound; odd -> pitch 1.0, even -> 0.7071 (posted as event 0x10).

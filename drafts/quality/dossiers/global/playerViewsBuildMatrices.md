# playerViewsBuildMatrices (global, src/global/450.c)
## Sites
global:805FCA94:dead-if:862f4b dead-if: entry use of &D_807445CC kept the address web across all calls so the final D_807445CC[0]++ re-materialises %hi/%lo (0x183c/0x1848) instead of a v0 base (FIXED)
## Attempts
2026-11-10..13 Clean103AB0 / CleanGlobal450 / Rev17M / Rev20A opus-5-5:low: remove/cond/classify class 2, uopt_trace -l 6 (candidate 207 coloured v0), permute best 28 (zero-valued local)
2026-11-14 HackplayerViewsBuildMatrices opus-5-5:high: function-local static (address in v0), cc set early + increment via global (7), cc set early + cc[0]++ / (*cc)++ (0), s32 *cc = D_807445CC initialiser + cc[0]++ (0, applied)
## Untried ideas
none (fixed)
## Evidence
Loop: lui t8 / lw t8,%lo(D_807445CC) per use (0x1580/0x15a8, 0x15ec/0x15f0, 0x1648/0x1660); end: lui t6 / lw t6 (0x183c/0x1840), lui at / sw t7 (0x1848/0x187c). D_807445CC is the last .data item (.data+0x15c), used only here.

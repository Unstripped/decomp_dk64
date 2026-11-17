# viModeSetup (global, src/global/450.c)
## Sites
global:805FB944:dead-if:e921cd (formerly 86a8e0) dead-if: removed. The entry dead test `if (sViModeFirstSetup && sViModeFirstSetup) {}` kept the address of sViModeFirstSetup (was D_807445A4) uncoloured, so the lb at 0x3dc and the sb zero at 0x480 each used their own lui. Fixed by `s8 *firstSetupFlag = &sViModeFirstSetup;` initialised at its declaration, with both accesses through it (Q0601, lead ruling 2026-11-16).
## Attempts
2026-11-10..13 CleanGlobal450 / Rev17M / Rev20A / Rev21B opus-5-5:low: uopt_trace, permute (dead test moved, s8 *new_var = &D_807445A4 before loadOverlay, single-access address temp: rejected)
2026-11-14 HackplayerViewsBuildMatrices opus-5-5:high: function-local static (code identical, .data reordered: static emitted at 0x170, D_807445A8.. shift), one-case switch (7), bare test (7), arm swap (67), store first in else (12), pointer local s8 *firstBoot = &D_807445A4 initialised at declaration after overlayParam (0) / before overlayId (10) / assigned after overlayParam = 0 (0)
2026-11-16 HackviModeSetup opus-5-5: applied the lead-ruled pointer local `s8 *firstSetupFlag = &sViModeFirstSetup;` declared after overlayParam, `if (*firstSetupFlag == 0)` / `*firstSetupFlag = 0;`; dead test removed; fdiff OK whole-object and function; clint uninit exit 0. Review: fake=0/1, no other steers.
## Untried ideas
none (function clean)
## Evidence
0x3dc lui t4 / 0x3e0 lb t4,%lo(sViModeFirstSetup); 0x478 lui at / 0x480 sb zero,%lo(sViModeFirstSetup) (jal viModeApplyHighRes delay slot). sViModeFirstSetup = s8 1 at .data+0x134, used only by viModeSetup.

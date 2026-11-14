# viModeSetup (global, src/global/450.c)
## Sites
global:805FB944:dead-if:86a8e0 dead-if: entry use of &D_807445A4 keeps the address uncoloured, so the lb at 0x3dc and the sb zero at 0x480 each use their own lui
## Attempts
2026-11-10..13 CleanGlobal450 / Rev17M / Rev20A / Rev21B opus-5-5:low: uopt_trace, permute (dead test moved, s8 *new_var = &D_807445A4 before loadOverlay)
2026-11-14 HackplayerViewsBuildMatrices opus-5-5:high: function-local static (code identical, .data reordered: static emitted at 0x170, D_807445A8.. shift), one-case switch (7), bare test (7), arm swap (67), store first in else (12), pointer local s8 *firstBoot = &D_807445A4 initialised at declaration after overlayParam (0) / before overlayId (10) / assigned after overlayParam = 0 (0)
## Untried ideas
decision owed: the firstBoot pointer local (fdiff 0) is the round-34-rejected address-temp construct; playerViewsBuildMatrices' accepted fix is an already-existing pointer local initialised at declaration
## Evidence
0x3dc lui t4 / 0x3e0 lb t4,%lo(D_807445A4); 0x478 lui at / 0x480 sb zero,%lo(D_807445A4) (jal viModeApplyHighRes delay slot). D_807445A4 = s8 1 at .data+0x134, used only by viModeSetup.

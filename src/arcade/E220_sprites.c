#include "common.h"
#include "arcade.h"

// Data-only TU linked ahead of 0.c: its .data is 0x80032220-0x8004A790 and 0.c's .data starts at the
// 16-aligned 0x8004A790. Defining these objects in 0.c instead reorders 0.c's .bss (IDO orders a TU's
// .bss by symbol number, and every definition shifts them).

// Sprite pixels: RGBA16 (arcadeRenderEntity passes G_IM_FMT_RGBA, G_IM_SIZ_16b to dlInitTextureDescriptor),
// each block ending in the 8 bytes 0xDF000000 0x00000000. The bytes are extracted from the ROM
// (data_inc.us.txt, tools/data_inc.py).

u16 D_80032220[0x4] = {
#include "arcade/D_80032220.inc.c"
};
u16 gArcadeOilFireSprite[0x124] = {
#include "arcade/gArcadeOilFireSprite.inc.c"
};
u16 gArcadeOilFireFlickerSprite[0x124] = {
#include "arcade/gArcadeOilFireFlickerSprite.inc.c"
};
u16 gArcadeOilFireFlareSprite[0x124] = {
#include "arcade/gArcadeOilFireFlareSprite.inc.c"
};
u16 gArcadeOilFireFlareFlickerSprite[0x124] = {
#include "arcade/gArcadeOilFireFlareFlickerSprite.inc.c"
};
u16 gArcadeLadderSprite[0x24] = {
#include "arcade/gArcadeLadderSprite.inc.c"
};
u16 gArcadeLadderStage2Sprite[0x24] = {
#include "arcade/gArcadeLadderStage2Sprite.inc.c"
};
u16 gArcadeLadderStage4Sprite[0x24] = {
#include "arcade/gArcadeLadderStage4Sprite.inc.c"
};
u16 gArcadeBlockSprite[0x44] = {
#include "arcade/gArcadeBlockSprite.inc.c"
};
u16 gArcadeConveyorSprite[0x54] = {
#include "arcade/gArcadeConveyorSprite.inc.c"
};
u16 gArcadeStage4GirderSprite[0x54] = {
#include "arcade/gArcadeStage4GirderSprite.inc.c"
};
u16 gArcadeBlockFlashSprite[0x44] = {
#include "arcade/gArcadeBlockFlashSprite.inc.c"
};
u16 D_80032E80[0x4C] = {
#include "arcade/D_80032E80.inc.c"
};
u16 gArcadeStage2PostSprite[0x14] = {
#include "arcade/gArcadeStage2PostSprite.inc.c"
};
u16 gArcadeLiftCableSprite[0x14] = {
#include "arcade/gArcadeLiftCableSprite.inc.c"
};
u16 D_80032F68[0x338] = {
#include "arcade/D_80032F68.inc.c"
};
u16 gArcadeBonusBoxStage2Sprite[0x338] = {
#include "arcade/gArcadeBonusBoxStage2Sprite.inc.c"
};
u16 gArcadeBonusBoxStage4Sprite[0x338] = {
#include "arcade/gArcadeBonusBoxStage4Sprite.inc.c"
};
u16 gArcadeCrossBraceSprite[0x54] = {
#include "arcade/gArcadeCrossBraceSprite.inc.c"
};
u16 D_80034360[0x104] = {
#include "arcade/D_80034360.inc.c"
};
u16 gArcadeGirderSprite[0x54] = {
#include "arcade/gArcadeGirderSprite.inc.c"
};
u16 gArcadeBarrelRollTopLeftSprite[0x104] = {
#include "arcade/gArcadeBarrelRollTopLeftSprite.inc.c"
};
u16 gArcadeBarrelRollBottomLeftSprite[0x104] = {
#include "arcade/gArcadeBarrelRollBottomLeftSprite.inc.c"
};
u16 gArcadeBarrelRollBottomRightSprite[0x104] = {
#include "arcade/gArcadeBarrelRollBottomRightSprite.inc.c"
};
u16 gArcadeBarrelRollTopRightSprite[0x104] = {
#include "arcade/gArcadeBarrelRollTopRightSprite.inc.c"
};
u16 gArcadeBarrelBlueRollTopLeftSprite[0x104] = {
#include "arcade/gArcadeBarrelBlueRollTopLeftSprite.inc.c"
};
u16 gArcadeBarrelBlueRollBottomLeftSprite[0x104] = {
#include "arcade/gArcadeBarrelBlueRollBottomLeftSprite.inc.c"
};
u16 gArcadeBarrelBlueRollBottomRightSprite[0x104] = {
#include "arcade/gArcadeBarrelBlueRollBottomRightSprite.inc.c"
};
u16 gArcadeBarrelBlueRollTopRightSprite[0x104] = {
#include "arcade/gArcadeBarrelBlueRollTopRightSprite.inc.c"
};
u16 gArcadeBarrelSideDarkBandSprite[0x124] = {
#include "arcade/gArcadeBarrelSideDarkBandSprite.inc.c"
};
u16 gArcadeBarrelSideLightBandSprite[0x124] = {
#include "arcade/gArcadeBarrelSideLightBandSprite.inc.c"
};
u16 gArcadeBarrelBlueSideDarkBandSprite[0x104] = {
#include "arcade/gArcadeBarrelBlueSideDarkBandSprite.inc.c"
};
u16 gArcadeBarrelBlueSideLightBandSprite[0x104] = {
#include "arcade/gArcadeBarrelBlueSideLightBandSprite.inc.c"
};
u16 gArcadeFireballSprite[0x124] = {
#include "arcade/gArcadeFireballSprite.inc.c"
};
u16 gArcadeFireballFlickerSprite[0x124] = {
#include "arcade/gArcadeFireballFlickerSprite.inc.c"
};
u16 gArcadeFireballStage2Sprite[0x124] = {
#include "arcade/gArcadeFireballStage2Sprite.inc.c"
};
u16 gArcadeFireballStage2FlickerSprite[0x124] = {
#include "arcade/gArcadeFireballStage2FlickerSprite.inc.c"
};
u16 gArcadeFireballStage2BlueSprite[0x124] = {
#include "arcade/gArcadeFireballStage2BlueSprite.inc.c"
};
u16 gArcadeFireballStage2BlueFlickerSprite[0x124] = {
#include "arcade/gArcadeFireballStage2BlueFlickerSprite.inc.c"
};
u16 gArcadeFireballBlueSprite[0x124] = {
#include "arcade/gArcadeFireballBlueSprite.inc.c"
};
u16 gArcadeFireballBlueFlickerSprite[0x124] = {
#include "arcade/gArcadeFireballBlueFlickerSprite.inc.c"
};
u16 D_80037130[0x104] = {
#include "arcade/D_80037130.inc.c"
};
u16 D_80037338[0x124] = {
#include "arcade/D_80037338.inc.c"
};
u16 D_80037580[0x104] = {
#include "arcade/D_80037580.inc.c"
};
u16 gArcadeSpringExtendedSprite[0x104] = {
#include "arcade/gArcadeSpringExtendedSprite.inc.c"
};
u16 gArcadeSpringCompressedSprite[0x104] = {
#include "arcade/gArcadeSpringCompressedSprite.inc.c"
};
u16 gArcadeConveyorPulleyTiltRightSprite[0x104] = {
#include "arcade/gArcadeConveyorPulleyTiltRightSprite.inc.c"
};
u16 gArcadeConveyorPulleyFlatSprite[0x104] = {
#include "arcade/gArcadeConveyorPulleyFlatSprite.inc.c"
};
u16 gArcadeConveyorPulleyTiltLeftSprite[0x104] = {
#include "arcade/gArcadeConveyorPulleyTiltLeftSprite.inc.c"
};
u16 D_800381B0[0x104] = {
#include "arcade/D_800381B0.inc.c"
};
u16 gArcadeScoreThreeHundredSprite[0x104] = {
#include "arcade/gArcadeScoreThreeHundredSprite.inc.c"
};
u16 gArcadeScoreFiveHundredSprite[0x104] = {
#include "arcade/gArcadeScoreFiveHundredSprite.inc.c"
};
u16 gArcadeScoreEightHundredSprite[0x104] = {
#include "arcade/gArcadeScoreEightHundredSprite.inc.c"
};
u16 gArcadeHeartSprite[0x104] = {
#include "arcade/gArcadeHeartSprite.inc.c"
};
u16 gArcadeBrokenHeartSprite[0x104] = {
#include "arcade/gArcadeBrokenHeartSprite.inc.c"
};
u16 D_80038DE0[0x104] = {
#include "arcade/D_80038DE0.inc.c"
};
u16 gArcadePurseSprite[0x104] = {
#include "arcade/gArcadePurseSprite.inc.c"
};
u16 gArcadeUmbrellaSprite[0x104] = {
#include "arcade/gArcadeUmbrellaSprite.inc.c"
};
u16 gArcadeHammerUpSprite[0x124] = {
#include "arcade/gArcadeHammerUpSprite.inc.c"
};
u16 gArcadeHammerDownSprite[0x124] = {
#include "arcade/gArcadeHammerDownSprite.inc.c"
};
u16 gArcadeHammerUpFlashSprite[0x124] = {
#include "arcade/gArcadeHammerUpFlashSprite.inc.c"
};
u16 gArcadeHammerDownFlashSprite[0x124] = {
#include "arcade/gArcadeHammerDownFlashSprite.inc.c"
};
u16 gArcadeSmashRingSprite[0x124] = {
#include "arcade/gArcadeSmashRingSprite.inc.c"
};
u16 gArcadeSmashSmallRingSprite[0x124] = {
#include "arcade/gArcadeSmashSmallRingSprite.inc.c"
};
u16 gArcadeSmashDotSprite[0x124] = {
#include "arcade/gArcadeSmashDotSprite.inc.c"
};
u16 gArcadeSmashBurstSprite[0x124] = {
#include "arcade/gArcadeSmashBurstSprite.inc.c"
};
u16 D_8003A638[0x104] = {
#include "arcade/D_8003A638.inc.c"
};
u16 D_8003A840[0x104] = {
#include "arcade/D_8003A840.inc.c"
};
u16 D_8003AA48[0x104] = {
#include "arcade/D_8003AA48.inc.c"
};
u16 D_8003AC50[0x104] = {
#include "arcade/D_8003AC50.inc.c"
};
u16 gArcadeCoinSprite[0x194] = {
#include "arcade/gArcadeCoinSprite.inc.c"
};
u16 gArcadePlayerStandSprite[0x124] = {
#include "arcade/gArcadePlayerStandSprite.inc.c"
};
u16 gArcadePlayerWalkFrontLegUpSprite[0x124] = {
#include "arcade/gArcadePlayerWalkFrontLegUpSprite.inc.c"
};
u16 gArcadePlayerWalkBackLegUpSprite[0x124] = {
#include "arcade/gArcadePlayerWalkBackLegUpSprite.inc.c"
};
u16 gArcadePlayerClimbSprite[0x124] = {
#include "arcade/gArcadePlayerClimbSprite.inc.c"
};
u16 gArcadePlayerClimbOverHunchSprite[0x124] = {
#include "arcade/gArcadePlayerClimbOverHunchSprite.inc.c"
};
u16 gArcadePlayerClimbOverCrawlSprite[0x124] = {
#include "arcade/gArcadePlayerClimbOverCrawlSprite.inc.c"
};
u16 gArcadePlayerClimbEndSprite[0x124] = {
#include "arcade/gArcadePlayerClimbEndSprite.inc.c"
};
u16 gArcadePlayerHammerUpSprite[0x124] = {
#include "arcade/gArcadePlayerHammerUpSprite.inc.c"
};
u16 gArcadePlayerHammerDownSprite[0x124] = {
#include "arcade/gArcadePlayerHammerDownSprite.inc.c"
};
u16 gArcadePlayerHammerUpWalkFrontLegUpSprite[0x124] = {
#include "arcade/gArcadePlayerHammerUpWalkFrontLegUpSprite.inc.c"
};
u16 gArcadePlayerHammerDownWalkFrontLegUpSprite[0x124] = {
#include "arcade/gArcadePlayerHammerDownWalkFrontLegUpSprite.inc.c"
};
u16 gArcadePlayerHammerUpWalkBackLegUpSprite[0x124] = {
#include "arcade/gArcadePlayerHammerUpWalkBackLegUpSprite.inc.c"
};
u16 gArcadePlayerHammerDownWalkBackLegUpSprite[0x124] = {
#include "arcade/gArcadePlayerHammerDownWalkBackLegUpSprite.inc.c"
};
u16 gArcadePlayerJumpSprite[0x124] = {
#include "arcade/gArcadePlayerJumpSprite.inc.c"
};
u16 gArcadePlayerLandSprite[0x124] = {
#include "arcade/gArcadePlayerLandSprite.inc.c"
};
u16 gArcadePlayerSpinFrontSprite[0x124] = {
#include "arcade/gArcadePlayerSpinFrontSprite.inc.c"
};
u16 gArcadePlayerSpinSideSprite[0x124] = {
#include "arcade/gArcadePlayerSpinSideSprite.inc.c"
};
u16 gArcadePlayerDeadSprite[0x124] = {
#include "arcade/gArcadePlayerDeadSprite.inc.c"
};
u16 gArcadeLifeIconSprite[0x44] = {
#include "arcade/gArcadeLifeIconSprite.inc.c"
};
u16 gArcadePaulineUpperSprite[0x124] = {
#include "arcade/gArcadePaulineUpperSprite.inc.c"
};
u16 gArcadePaulineUpperFrontSprite[0x36C] = {
#include "arcade/gArcadePaulineUpperFrontSprite.inc.c"
};
u16 gArcadePaulineLowerSprite[0x124] = {
#include "arcade/gArcadePaulineLowerSprite.inc.c"
};
u16 gArcadeHelpSprite[0xF4] = {
#include "arcade/gArcadeHelpSprite.inc.c"
};
u16 gArcadeHelpBlueSprite[0xC4] = {
#include "arcade/gArcadeHelpBlueSprite.inc.c"
};
u16 gArcadeKongSideSprite[0x7E4] = {
#include "arcade/gArcadeKongSideSprite.inc.c"
};
u16 D_8003F9B8[0x5C4] = {
#include "arcade/D_8003F9B8.inc.c"
};
u16 gArcadeKongStandSprite[0x7E4] = {
#include "arcade/gArcadeKongStandSprite.inc.c"
};
u16 gArcadeKongGrinSprite[0x7E4] = {
#include "arcade/gArcadeKongGrinSprite.inc.c"
};
u16 gArcadeKongStompSprite[0x7E4] = {
#include "arcade/gArcadeKongStompSprite.inc.c"
};
u16 gArcadeKongHoldBarrelSprite[0x7E4] = {
#include "arcade/gArcadeKongHoldBarrelSprite.inc.c"
};
u16 gArcadeKongCarryClimbReachSprite[0x7E4] = {
#include "arcade/gArcadeKongCarryClimbReachSprite.inc.c"
};
u16 gArcadeKongCarryClimbPullSprite[0x7E4] = {
#include "arcade/gArcadeKongCarryClimbPullSprite.inc.c"
};
u16 gArcadeKongClimbSprite[0x7E4] = {
#include "arcade/gArcadeKongClimbSprite.inc.c"
};
u16 gArcadeKongDazedEyesRightSprite[0x7E4] = {
#include "arcade/gArcadeKongDazedEyesRightSprite.inc.c"
};
u16 gArcadeKongDazedEyesUpLeftSprite[0x7E4] = {
#include "arcade/gArcadeKongDazedEyesUpLeftSprite.inc.c"
};
u16 gArcadeKongDazedEyesDownSprite[0x7E0] = {
#include "arcade/gArcadeKongDazedEyesDownSprite.inc.c"
};

// Game tables, entity templates (copied into gArcadeEntities) and game state used by 0.c.
s32 gArcadeConveyorSpeeds[4] = { 0 };
s32 gArcadeFireballSpawnPoints[8] = { 244, 132, 252, 170, 260, 208, 268, 247 };
u8 gArcadeTypeDrawFlags[32] = {
    0, 0, 0, 1, 3, 3, 0, 0, 2, 3, 3, 3, 3, 0, 3, 3,
    2, 3, 3, 0, 3, 3, 3, 2, 3, 3, 2, 2, 3, 3, 3, 0,
};
u8 gArcadeTypeOriginX[32] = {
    0, 8, 8, 8, 8, 8, 8, 8, 0, 0, 3, 4, 0, 8, 0, 8,
    0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 gArcadeTypeOriginY[32] = {
    0, 12, 16, 12, 12, 17, 17, 17, 0, 0, 17, 1, 0, 17, 0, 12,
    0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
ArcadeEntity gArcadePlayerTemplate = { 96.0f, 247.0f, 0.0f, 0.0f, 0.0f, NULL, 0x0D, 0, 3, 0, 0, 0, 16, 18 };
ArcadeEntity gArcadeBarrelTemplate = { 64.0f, 79.0f, 1.0f, 0.0f, 0.0f, gArcadeBarrelRollTopLeftSprite, 0x01, 0, 0, 0, 0, 0, 16, 15 };
ArcadeEntity gArcadeFireballTemplate = { 76.0f, 230.0f, 1.0f, 0.0f, 0.0f, NULL, 0x02, 2, 0, 0, 0, 0, 16, 17 };
ArcadeEntity gArcadeOilFireTemplate = { 64.0f, 216.0f, 1.0f, 0.0f, 0.0f, gArcadeOilFireSprite, 0x13, 2, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeSpringTemplate = { -24.0f, 81.0f, 2.0f, -3.5f, 0.0f, NULL, 0x03, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeBonusBoxTemplate = { 219.0f, 38.0f, 2.0f, -3.5f, 0.0f, D_80032F68, 0x0E, 0, 0, 0, 0, 0, 43, 19 };
ArcadeEntity gArcadeOilDrumTemplate = { 64.0f, 231.0f, 0.0f, 0.0f, 0.0f, D_80037338, 0x10, 0, 0, 0, 0, 0, 16, 17 };
ArcadeEntity gArcadeLiftMotorTemplate = { 80.0f, 88.0f, 0.0f, 0.0f, 0.0f, D_80037580, 0x11, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeConveyorPulleyTemplate = { 48.0f, 84.0f, 0.0f, 0.0f, 0.0f, gArcadeConveyorPulleyTiltRightSprite, 0x12, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadePaulineLowerTemplate = { 136.0f, 26.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1B, 0, 0, 0, 0, 0, 16, 17 };
ArcadeEntity gArcadePaulineUpperTemplate = { 136.0f, 42.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1A, 0, 0, 0, 0, 0, 16, 17 };
ArcadeEntity gArcadeCoinTemplate = { 136.0f, 42.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1E, 0, 0, 0, 0, 0, 20, 20 };
ArcadeEntity gArcadeHelpBubbleTemplate = { 152.0f, 33.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1D, 0, 0, 0, 0, 0, 24, 10 };
ArcadeEntity gArcadeKongIntroTemplate = { 148.0f, 200.0f, 0.0f, 0.0f, 0.0f, NULL, 0x15, 0, 0, 0, 0, 0, 48, 41 };
ArcadeEntity gArcadeKongStage1Template = { 68.0f, 38.0f, 0.0f, 0.0f, 0.0f, gArcadeKongStandSprite, 0x16, 12, 0, 0, 1, 0, 48, 41 };
ArcadeEntity gArcadeKongStage2Template = { 136.0f, 53.0f, 0.0f, 0.0f, 0.0f, gArcadeKongStandSprite, 0x17, 2, 0, 0, 0, 0, 48, 41 };
ArcadeEntity gArcadeKongStage3Template = { 68.0f, 42.0f, 0.0f, 0.0f, 0.0f, gArcadeKongStandSprite, 0x18, 2, 0, 0, 0, 0, 48, 41 };
ArcadeEntity gArcadeKongStage4Template = { 68.0f, 42.0f, 1.0f, 0.0f, 0.0f, gArcadeKongStandSprite, 0x19, 2, 0, 0, 0, 0, 48, 41 };
ArcadeEntity gArcadeKongHeadTemplate = { 138.0f, 198.0f, 0.0f, 0.0f, 0.0f, D_8003F9B8, 0x08, 0, 0, 0, 0, 0, 46, 32 };
ArcadeEntity gArcadeScorePopupTemplate = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, D_800381B0, 0x14, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeBonusItemTemplate = { 180.0f, 247.0f, 0.0f, 0.0f, 0.0f, D_80038DE0, 0x05, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeHammerTemplate = { 220.0f, 200.0f, 0.0f, 0.0f, 0.0f, gArcadeHammerUpSprite, 0x06, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeRivetTemplate = { 108.0f, 208.0f, 0.0f, 0.0f, 0.0f, D_80032E80, 0x0B, 0, 0, 0, 1, 0, 8, 9 };
ArcadeEntity gArcadeRetractableLadderTemplate = { 60.0f, 97.0f, 0.0f, 0.0f, 0.0f, D_8003A638, 0x0C, 0, 0, 0, 244, 0, 16, 16 };
ArcadeEntity gArcadeNameCursorTemplate = { 60.0f, 97.0f, 0.0f, 0.0f, 0.0f, D_8003A840, 0x09, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadePanelTileTemplate = { 60.0f, 97.0f, 0.0f, 0.0f, 0.0f, D_80034360, 0x1C, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeCementPanTemplate = { 60.0f, 207.0f, 0.0f, 0.0f, 0.0f, D_8003AA48, 0x04, 0, 0, 0, 3, 0, 16, 16 };
ArcadeEntity gArcadeKongStarsTemplate = { 160.0f, 214.0f, 0.0f, 0.0f, 0.0f, D_8003AC50, 0x0F, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity gArcadeBarrelStackTemplate = { 58.0f, 83.0f, 0.0f, 0.0f, 0.0f, D_80037130, 0x0A, 0, 0, 0, 0, 0, 16, 16 };
u32 gArcadeRandSeed = 1;
u8 gArcadeExitRequested = 0;
u8 gArcadeAdventureMode = 0;
u8 gArcadeHighScoresDeleted = 0;
s32 gArcadeScore = 3700;
s32 gArcadeHighScores[5] = { 7650, 6100, 5950, 5050, 4300 };
s32 gArcadeTopScore = 7650;
u8 gArcadeGameOver = 0;
s8 gArcadePauseSelection = 0;
u8 gArcadeLevel = 0;
u8 gArcadeLevelCleared = 0;
u8 gArcadeEntryInitials[3] = { 0x20, 0x20, 0x20 };
u8 gArcadeHighScoreInitials[5][3] = {
    { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 },
};
u8 gArcadeRoundStages[4] = { 1, 4, 3, 2 };
s32 gArcadeInitPending[1] = { 1 }; // 0.c's gArcadeInitPending[1]++ is 0.c's own gArcadeDispatchFrames, the first word of its .data

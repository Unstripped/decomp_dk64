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
u16 D_80032228[0x124] = {
#include "arcade/D_80032228.inc.c"
};
u16 D_80032470[0x124] = {
#include "arcade/D_80032470.inc.c"
};
u16 D_800326B8[0x124] = {
#include "arcade/D_800326B8.inc.c"
};
u16 D_80032900[0x124] = {
#include "arcade/D_80032900.inc.c"
};
u16 D_80032B48[0x24] = {
#include "arcade/D_80032B48.inc.c"
};
u16 D_80032B90[0x24] = {
#include "arcade/D_80032B90.inc.c"
};
u16 D_80032BD8[0x24] = {
#include "arcade/D_80032BD8.inc.c"
};
u16 D_80032C20[0x44] = {
#include "arcade/D_80032C20.inc.c"
};
u16 D_80032CA8[0x54] = {
#include "arcade/D_80032CA8.inc.c"
};
u16 D_80032D50[0x54] = {
#include "arcade/D_80032D50.inc.c"
};
u16 D_80032DF8[0x44] = {
#include "arcade/D_80032DF8.inc.c"
};
u16 D_80032E80[0x4C] = {
#include "arcade/D_80032E80.inc.c"
};
u16 D_80032F18[0x14] = {
#include "arcade/D_80032F18.inc.c"
};
u16 D_80032F40[0x14] = {
#include "arcade/D_80032F40.inc.c"
};
u16 D_80032F68[0x338] = {
#include "arcade/D_80032F68.inc.c"
};
u16 D_800335D8[0x338] = {
#include "arcade/D_800335D8.inc.c"
};
u16 D_80033C48[0x338] = {
#include "arcade/D_80033C48.inc.c"
};
u16 D_800342B8[0x54] = {
#include "arcade/D_800342B8.inc.c"
};
u16 D_80034360[0x104] = {
#include "arcade/D_80034360.inc.c"
};
u16 D_80034568[0x54] = {
#include "arcade/D_80034568.inc.c"
};
u16 D_80034610[0x104] = {
#include "arcade/D_80034610.inc.c"
};
u16 D_80034818[0x104] = {
#include "arcade/D_80034818.inc.c"
};
u16 D_80034A20[0x104] = {
#include "arcade/D_80034A20.inc.c"
};
u16 D_80034C28[0x104] = {
#include "arcade/D_80034C28.inc.c"
};
u16 D_80034E30[0x104] = {
#include "arcade/D_80034E30.inc.c"
};
u16 D_80035038[0x104] = {
#include "arcade/D_80035038.inc.c"
};
u16 D_80035240[0x104] = {
#include "arcade/D_80035240.inc.c"
};
u16 D_80035448[0x104] = {
#include "arcade/D_80035448.inc.c"
};
u16 D_80035650[0x124] = {
#include "arcade/D_80035650.inc.c"
};
u16 D_80035898[0x124] = {
#include "arcade/D_80035898.inc.c"
};
u16 D_80035AE0[0x104] = {
#include "arcade/D_80035AE0.inc.c"
};
u16 D_80035CE8[0x104] = {
#include "arcade/D_80035CE8.inc.c"
};
u16 D_80035EF0[0x124] = {
#include "arcade/D_80035EF0.inc.c"
};
u16 D_80036138[0x124] = {
#include "arcade/D_80036138.inc.c"
};
u16 D_80036380[0x124] = {
#include "arcade/D_80036380.inc.c"
};
u16 D_800365C8[0x124] = {
#include "arcade/D_800365C8.inc.c"
};
u16 D_80036810[0x124] = {
#include "arcade/D_80036810.inc.c"
};
u16 D_80036A58[0x124] = {
#include "arcade/D_80036A58.inc.c"
};
u16 D_80036CA0[0x124] = {
#include "arcade/D_80036CA0.inc.c"
};
u16 D_80036EE8[0x124] = {
#include "arcade/D_80036EE8.inc.c"
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
u16 D_80037788[0x104] = {
#include "arcade/D_80037788.inc.c"
};
u16 D_80037990[0x104] = {
#include "arcade/D_80037990.inc.c"
};
u16 D_80037B98[0x104] = {
#include "arcade/D_80037B98.inc.c"
};
u16 D_80037DA0[0x104] = {
#include "arcade/D_80037DA0.inc.c"
};
u16 D_80037FA8[0x104] = {
#include "arcade/D_80037FA8.inc.c"
};
u16 D_800381B0[0x104] = {
#include "arcade/D_800381B0.inc.c"
};
u16 D_800383B8[0x104] = {
#include "arcade/D_800383B8.inc.c"
};
u16 D_800385C0[0x104] = {
#include "arcade/D_800385C0.inc.c"
};
u16 D_800387C8[0x104] = {
#include "arcade/D_800387C8.inc.c"
};
u16 D_800389D0[0x104] = {
#include "arcade/D_800389D0.inc.c"
};
u16 D_80038BD8[0x104] = {
#include "arcade/D_80038BD8.inc.c"
};
u16 D_80038DE0[0x104] = {
#include "arcade/D_80038DE0.inc.c"
};
u16 D_80038FE8[0x104] = {
#include "arcade/D_80038FE8.inc.c"
};
u16 D_800391F0[0x104] = {
#include "arcade/D_800391F0.inc.c"
};
u16 D_800393F8[0x124] = {
#include "arcade/D_800393F8.inc.c"
};
u16 D_80039640[0x124] = {
#include "arcade/D_80039640.inc.c"
};
u16 D_80039888[0x124] = {
#include "arcade/D_80039888.inc.c"
};
u16 D_80039AD0[0x124] = {
#include "arcade/D_80039AD0.inc.c"
};
u16 D_80039D18[0x124] = {
#include "arcade/D_80039D18.inc.c"
};
u16 D_80039F60[0x124] = {
#include "arcade/D_80039F60.inc.c"
};
u16 D_8003A1A8[0x124] = {
#include "arcade/D_8003A1A8.inc.c"
};
u16 D_8003A3F0[0x124] = {
#include "arcade/D_8003A3F0.inc.c"
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
u16 D_8003AE58[0x194] = {
#include "arcade/D_8003AE58.inc.c"
};
u16 D_8003B180[0x124] = {
#include "arcade/D_8003B180.inc.c"
};
u16 D_8003B3C8[0x124] = {
#include "arcade/D_8003B3C8.inc.c"
};
u16 D_8003B610[0x124] = {
#include "arcade/D_8003B610.inc.c"
};
u16 D_8003B858[0x124] = {
#include "arcade/D_8003B858.inc.c"
};
u16 D_8003BAA0[0x124] = {
#include "arcade/D_8003BAA0.inc.c"
};
u16 D_8003BCE8[0x124] = {
#include "arcade/D_8003BCE8.inc.c"
};
u16 D_8003BF30[0x124] = {
#include "arcade/D_8003BF30.inc.c"
};
u16 D_8003C178[0x124] = {
#include "arcade/D_8003C178.inc.c"
};
u16 D_8003C3C0[0x124] = {
#include "arcade/D_8003C3C0.inc.c"
};
u16 D_8003C608[0x124] = {
#include "arcade/D_8003C608.inc.c"
};
u16 D_8003C850[0x124] = {
#include "arcade/D_8003C850.inc.c"
};
u16 D_8003CA98[0x124] = {
#include "arcade/D_8003CA98.inc.c"
};
u16 D_8003CCE0[0x124] = {
#include "arcade/D_8003CCE0.inc.c"
};
u16 D_8003CF28[0x124] = {
#include "arcade/D_8003CF28.inc.c"
};
u16 D_8003D170[0x124] = {
#include "arcade/D_8003D170.inc.c"
};
u16 D_8003D3B8[0x124] = {
#include "arcade/D_8003D3B8.inc.c"
};
u16 D_8003D600[0x124] = {
#include "arcade/D_8003D600.inc.c"
};
u16 D_8003D848[0x124] = {
#include "arcade/D_8003D848.inc.c"
};
u16 D_8003DA90[0x44] = {
#include "arcade/D_8003DA90.inc.c"
};
u16 D_8003DB18[0x124] = {
#include "arcade/D_8003DB18.inc.c"
};
u16 D_8003DD60[0x36C] = {
#include "arcade/D_8003DD60.inc.c"
};
u16 D_8003E438[0x124] = {
#include "arcade/D_8003E438.inc.c"
};
u16 D_8003E680[0xF4] = {
#include "arcade/D_8003E680.inc.c"
};
u16 D_8003E868[0xC4] = {
#include "arcade/D_8003E868.inc.c"
};
u16 D_8003E9F0[0x7E4] = {
#include "arcade/D_8003E9F0.inc.c"
};
u16 D_8003F9B8[0x5C4] = {
#include "arcade/D_8003F9B8.inc.c"
};
u16 D_80040540[0x7E4] = {
#include "arcade/D_80040540.inc.c"
};
u16 D_80041508[0x7E4] = {
#include "arcade/D_80041508.inc.c"
};
u16 D_800424D0[0x7E4] = {
#include "arcade/D_800424D0.inc.c"
};
u16 D_80043498[0x7E4] = {
#include "arcade/D_80043498.inc.c"
};
u16 D_80044460[0x7E4] = {
#include "arcade/D_80044460.inc.c"
};
u16 D_80045428[0x7E4] = {
#include "arcade/D_80045428.inc.c"
};
u16 D_800463F0[0x7E4] = {
#include "arcade/D_800463F0.inc.c"
};
u16 D_800473B8[0x7E4] = {
#include "arcade/D_800473B8.inc.c"
};
u16 D_80048380[0x7E4] = {
#include "arcade/D_80048380.inc.c"
};
u16 D_80049348[0x7E0] = {
#include "arcade/D_80049348.inc.c"
};

// Game tables, entity templates (copied into D_8004BCD0) and game state used by 0.c.
s32 gArcadeConveyorSpeeds[4] = { 0 };
s32 D_8004A318[8] = { 244, 132, 252, 170, 260, 208, 268, 247 };
u8 D_8004A338[32] = {
    0, 0, 0, 1, 3, 3, 0, 0, 2, 3, 3, 3, 3, 0, 3, 3,
    2, 3, 3, 0, 3, 3, 3, 2, 3, 3, 2, 2, 3, 3, 3, 0,
};
u8 D_8004A358[32] = {
    0, 8, 8, 8, 8, 8, 8, 8, 0, 0, 3, 4, 0, 8, 0, 8,
    0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 D_8004A378[32] = {
    0, 12, 16, 12, 12, 17, 17, 17, 0, 0, 17, 1, 0, 17, 0, 12,
    0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
ArcadeEntity D_8004A398 = { 96.0f, 247.0f, 0.0f, 0.0f, 0.0f, NULL, 0x0D, 0, 3, 0, 0, 0, 16, 18 };
ArcadeEntity D_8004A3B8 = { 64.0f, 79.0f, 1.0f, 0.0f, 0.0f, D_80034610, 0x01, 0, 0, 0, 0, 0, 16, 15 };
ArcadeEntity D_8004A3D8 = { 76.0f, 230.0f, 1.0f, 0.0f, 0.0f, NULL, 0x02, 2, 0, 0, 0, 0, 16, 17 };
ArcadeEntity D_8004A3F8 = { 64.0f, 216.0f, 1.0f, 0.0f, 0.0f, D_80032228, 0x13, 2, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A418 = { -24.0f, 81.0f, 2.0f, -3.5f, 0.0f, NULL, 0x03, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A438 = { 219.0f, 38.0f, 2.0f, -3.5f, 0.0f, D_80032F68, 0x0E, 0, 0, 0, 0, 0, 43, 19 };
ArcadeEntity D_8004A458 = { 64.0f, 231.0f, 0.0f, 0.0f, 0.0f, D_80037338, 0x10, 0, 0, 0, 0, 0, 16, 17 };
ArcadeEntity D_8004A478 = { 80.0f, 88.0f, 0.0f, 0.0f, 0.0f, D_80037580, 0x11, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A498 = { 48.0f, 84.0f, 0.0f, 0.0f, 0.0f, D_80037B98, 0x12, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A4B8 = { 136.0f, 26.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1B, 0, 0, 0, 0, 0, 16, 17 };
ArcadeEntity D_8004A4D8 = { 136.0f, 42.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1A, 0, 0, 0, 0, 0, 16, 17 };
ArcadeEntity D_8004A4F8 = { 136.0f, 42.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1E, 0, 0, 0, 0, 0, 20, 20 };
ArcadeEntity D_8004A518 = { 152.0f, 33.0f, 0.0f, 0.0f, 0.0f, NULL, 0x1D, 0, 0, 0, 0, 0, 24, 10 };
ArcadeEntity D_8004A538 = { 148.0f, 200.0f, 0.0f, 0.0f, 0.0f, NULL, 0x15, 0, 0, 0, 0, 0, 48, 41 };
ArcadeEntity D_8004A558 = { 68.0f, 38.0f, 0.0f, 0.0f, 0.0f, D_80040540, 0x16, 12, 0, 0, 1, 0, 48, 41 };
ArcadeEntity D_8004A578 = { 136.0f, 53.0f, 0.0f, 0.0f, 0.0f, D_80040540, 0x17, 2, 0, 0, 0, 0, 48, 41 };
ArcadeEntity D_8004A598 = { 68.0f, 42.0f, 0.0f, 0.0f, 0.0f, D_80040540, 0x18, 2, 0, 0, 0, 0, 48, 41 };
ArcadeEntity D_8004A5B8 = { 68.0f, 42.0f, 1.0f, 0.0f, 0.0f, D_80040540, 0x19, 2, 0, 0, 0, 0, 48, 41 };
ArcadeEntity D_8004A5D8 = { 138.0f, 198.0f, 0.0f, 0.0f, 0.0f, D_8003F9B8, 0x08, 0, 0, 0, 0, 0, 46, 32 };
ArcadeEntity D_8004A5F8 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, D_800381B0, 0x14, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A618 = { 180.0f, 247.0f, 0.0f, 0.0f, 0.0f, D_80038DE0, 0x05, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A638 = { 220.0f, 200.0f, 0.0f, 0.0f, 0.0f, D_800393F8, 0x06, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A658 = { 108.0f, 208.0f, 0.0f, 0.0f, 0.0f, D_80032E80, 0x0B, 0, 0, 0, 1, 0, 8, 9 };
ArcadeEntity D_8004A678 = { 60.0f, 97.0f, 0.0f, 0.0f, 0.0f, D_8003A638, 0x0C, 0, 0, 0, 244, 0, 16, 16 };
ArcadeEntity D_8004A698 = { 60.0f, 97.0f, 0.0f, 0.0f, 0.0f, D_8003A840, 0x09, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A6B8 = { 60.0f, 97.0f, 0.0f, 0.0f, 0.0f, D_80034360, 0x1C, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A6D8 = { 60.0f, 207.0f, 0.0f, 0.0f, 0.0f, D_8003AA48, 0x04, 0, 0, 0, 3, 0, 16, 16 };
ArcadeEntity D_8004A6F8 = { 160.0f, 214.0f, 0.0f, 0.0f, 0.0f, D_8003AC50, 0x0F, 0, 0, 0, 0, 0, 16, 16 };
ArcadeEntity D_8004A718 = { 58.0f, 83.0f, 0.0f, 0.0f, 0.0f, D_80037130, 0x0A, 0, 0, 0, 0, 0, 16, 16 };
u32 D_8004A738 = 1;
u8 D_8004A73C = 0;
u8 D_8004A740 = 0;
u8 D_8004A744 = 0;
s32 gArcadeScore = 3700;
s32 D_8004A74C[5] = { 7650, 6100, 5950, 5050, 4300 };
s32 D_8004A760 = 7650;
u8 gArcadeGameOver = 0;
s8 gArcadePauseSelection = 0;
u8 gArcadeLevel = 0;
u8 D_8004A770 = 0;
u8 D_8004A774[3] = { 0x20, 0x20, 0x20 };
u8 D_8004A778[5][3] = {
    { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 }, { 0x20, 0x20, 0x20 },
};
u8 D_8004A788[4] = { 1, 4, 3, 2 };
s32 D_8004A78C[1] = { 1 }; // 0.c's D_8004A78C[1]++ is 0.c's own D_8004A790, the first word of its .data

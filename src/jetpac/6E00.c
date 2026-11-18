#include "common.h"
#include "proto/global/100180.h"
#include "proto/jetpac/6E00.h"

// .data 0x8002E9C0-0x8002E9D0: highlight colour (jetpacSetTextHighlightColor).
u8 D_8002E9C0 = 0;
u8 D_8002E9C4 = 0;
u8 D_8002E9C8 = 0;
u8 D_8002E9CC = 0xFF;
// .bss 0x80045BE0: text colour (jetpacSetTextColor).
u8 D_80045BE0;
u8 D_80045BE1;
u8 D_80045BE2;
u8 D_80045BE3;

void jetpacSetupTextRdp(Gfx **pGlist) {
    Gfx *g = *pGlist;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCombineLERP(g++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0);
    gDPSetRenderMode(g++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    *pGlist = g;
}

void jetpacSetTextColor(u8 r, u8 g, u8 b, u8 a) {
    D_80045BE0 = r;
    D_80045BE1 = g;
    D_80045BE2 = b;
    D_80045BE3 = a;
}

void jetpacSetTextHighlightColor(s8 r, s8 g, s8 b, s8 a) {
    D_8002E9C0 = r;
    D_8002E9C4 = g;
    D_8002E9C8 = b;
    D_8002E9CC = a;
}

void jetpacDrawString(Gfx **pGlist, char *str, s32 x, s32 y, s32 highlight) {
    Gfx *g = *pGlist;

    if (highlight != 0) {
        gDPSetPrimColor(g++, 0, 0, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
        gDPSetEnvColor(g++, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
    } else {
        gDPSetPrimColor(g++, 0, 0, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
        gDPSetEnvColor(g++, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
    }
    *pGlist = textDrawString(g, 4, x, y, str);
}

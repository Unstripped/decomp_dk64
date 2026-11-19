#include "common.h"
#include "proto/global/100180.h"
#include "proto/jetpac/6E00.h"

// .data 0x8002E9C0-0x8002E9D0: highlight colour (jetpacSetTextHighlightColor).
u8 jetpacTextHighlightR = 0;
u8 jetpacTextHighlightG = 0;
u8 jetpacTextHighlightB = 0;
u8 jetpacTextHighlightA = 0xFF;
// .bss 0x80045BE0: text colour (jetpacSetTextColor).
u8 jetpacTextColorR;
u8 jetpacTextColorG;
u8 jetpacTextColorB;
u8 jetpacTextColorA;

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
    jetpacTextColorR = r;
    jetpacTextColorG = g;
    jetpacTextColorB = b;
    jetpacTextColorA = a;
}

void jetpacSetTextHighlightColor(s8 r, s8 g, s8 b, s8 a) {
    jetpacTextHighlightR = r;
    jetpacTextHighlightG = g;
    jetpacTextHighlightB = b;
    jetpacTextHighlightA = a;
}

void jetpacDrawString(Gfx **pGlist, char *str, s32 x, s32 y, s32 highlight) {
    Gfx *g = *pGlist;

    if (highlight != 0) {
        gDPSetPrimColor(g++, 0, 0, jetpacTextHighlightR, jetpacTextHighlightG, jetpacTextHighlightB, jetpacTextHighlightA);
        gDPSetEnvColor(g++, jetpacTextColorR, jetpacTextColorG, jetpacTextColorB, jetpacTextColorA);
    } else {
        gDPSetPrimColor(g++, 0, 0, jetpacTextColorR, jetpacTextColorG, jetpacTextColorB, jetpacTextColorA);
        gDPSetEnvColor(g++, jetpacTextHighlightR, jetpacTextHighlightG, jetpacTextHighlightB, jetpacTextHighlightA);
    }
    *pGlist = textDrawString(g, 4, x, y, str);
}

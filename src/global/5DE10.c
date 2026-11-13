#include "common.h"
#include "actor.h"
#include "proto/global/5DE10.h"

extern s32 gCurrentMap;
extern u8 gFogEnabled;
extern u8 gFogColorR;
extern u8 gFogColorG;
extern u8 gFogColorB;
extern u8 gFogColorA;
extern s16 gFogNear;
extern s16 gFogFar;

void fogSetParams(u8 enable) {
    gFogEnabled = enable;
    if (gCurrentMap == 0x26) {
        gFogColorR = 0x8A;
        gFogColorG = 0x52;
        gFogColorB = 0x16;
    } else {
        gFogColorR = 0;
        gFogColorG = 0;
        gFogColorB = 0;
    }
    gFogColorA = 0;
    gFogNear = 0x3DE;
    gFogFar = 0x3E7;
}

u8 fogGetEnabled(void) {
    return gFogEnabled;
}

Gfx *fogApply(Gfx *gdl) {
    gSPFogPosition(gdl++, gFogNear, gFogFar);
    gDPPipeSync(gdl++);
    gDPSetFogColor(gdl++, gFogColorR, gFogColorG, gFogColorB, gFogColorA);
    return gdl;
}
Gfx *fogRender(Gfx *gdl) {
    if (gFogEnabled) {
        gSPSetGeometryMode(gdl++, G_FOG);
        gdl = fogApply(gdl);
    } else {
        gSPClearGeometryMode(gdl++, G_FOG);
    }
    return gdl;
}

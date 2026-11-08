#include "common.h"
#include "actor.h"

extern s32 gCurrentMap;
extern u8 D_807F7360;
extern u8 D_807F7361;
extern u8 D_807F7362;
extern u8 D_807F7363;
extern u8 D_807F7364;
extern s16 D_807F7366;
extern s16 D_807F7368;

void fogSetParams(u8 enable) {
    D_807F7360 = enable;
    if (gCurrentMap == 0x26) {
        D_807F7361 = 0x8A;
        D_807F7362 = 0x52;
        D_807F7363 = 0x16;
    } else {
        D_807F7361 = 0;
        D_807F7362 = 0;
        D_807F7363 = 0;
    }
    D_807F7364 = 0;
    D_807F7366 = 0x3DE;
    D_807F7368 = 0x3E7;
}

u8 fogGetEnabled(void) {
    return D_807F7360;
}

Gfx *fogApply(Gfx *gdl) {
    gSPFogPosition(gdl++, D_807F7366, D_807F7368);
    gDPPipeSync(gdl++);
    gDPSetFogColor(gdl++, D_807F7361, D_807F7362, D_807F7363, D_807F7364);
    return gdl;
}
Gfx *fogRender(Gfx *gdl) {
    if (D_807F7360) {
        gSPSetGeometryMode(gdl++, G_FOG);
        gdl = fogApply(gdl);
    } else {
        gSPClearGeometryMode(gdl++, G_FOG);
    }
    return gdl;
}

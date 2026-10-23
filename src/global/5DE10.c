#include "common.h"
#include "actor.h"

extern s32 D_8076A0A8;
extern u8 D_807F7360;
extern u8 D_807F7361;
extern u8 D_807F7362;
extern u8 D_807F7363;
extern u8 D_807F7364;
extern s16 D_807F7366;
extern s16 D_807F7368;

void func_80659110(u8 arg0) {
    D_807F7360 = arg0;
    if (D_8076A0A8 == 0x26) {
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

u8 func_80659190(void) {
    return D_807F7360;
}

Gfx *func_8065919C(Gfx *gdl) {
    gSPFogPosition(gdl++, D_807F7366, D_807F7368);
    gDPPipeSync(gdl++);
    gDPSetFogColor(gdl++, D_807F7361, D_807F7362, D_807F7363, D_807F7364);
    return gdl;
}
Gfx *func_806592B4(Gfx *gdl) {
    if (D_807F7360) {
        gSPSetGeometryMode(gdl++, G_FOG);
        gdl = func_8065919C(gdl);
    } else {
        gSPClearGeometryMode(gdl++, G_FOG);
    }
    return gdl;
}

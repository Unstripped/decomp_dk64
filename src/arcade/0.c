#include "common.h"
#define PROTO_SKIP_dlInitTextureDescriptor // FAKE: callee prototype steer
#include "proto/arcade/0.h"
#include "proto/boot/3D20.h"
#include "proto/boot/6690.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/104F0.h"
#include "proto/global/1135F0.h"
#include "proto/global/135D30.h"
#include "proto/global/13A7A0.h"
#include "proto/global/14CF0.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/F600.h"

typedef struct ArcadeEntity {
    f32 x;
    f32 y;
    f32 vx;
    f32 vy;
    f32 animTimer;
    void *sprite;
    u8 type;
    u8 state;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
} ArcadeEntity;

extern ArcadeEntity D_8004BCD0[];

/* One double-buffered texture descriptor slot (0x18 bytes) for dlInitTextureDescriptor. */
typedef struct ArcadeGfxSlot {
    u8 data[0x18];
} ArcadeGfxSlot;
extern void *D_8004C6D0;
typedef union ArcadeTexScale {
    s32 word;
    s16 half[2];
} ArcadeTexScale;
extern ArcadeTexScale D_8004C6D4;

extern s8 D_8004C71E;
extern u8 D_8004C71D;
extern u8 D_8004C71F;
extern u8 D_8004C721;
extern u8 D_8004C722;
extern u8 D_8004C724;
extern s32 D_8004C708;
extern s32 D_8004C6DC;
extern u8 D_8004A740;
extern u8 D_8004A76C;
extern s32 D_8004A308[];

extern s16 D_8004C72E;
extern s16 D_8004C732;
extern u8 D_8004C725;
extern u8 D_8004C726;
extern u8 D_8004C727;
extern u8 D_8004C728;


extern u8 gGfxBufferIndex;
extern Gfx *gGfxTaskBuffers[];
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern u8 *gGfxCurrentFrameBuffer;
extern u8 D_80767CE8[];
extern u8 gScreenRenderFlags;
extern f32 gScreenFadeProgress;
extern u8 gGameMode;
extern void *D_8076A080;
extern Gfx D_1000090;
extern Gfx D_1000040;

void arcadeRunFrame(void) {
    Gfx *glist;
    Gfx *subList;

    controllerStartRead();
    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], D_8076A088, 3, 1, 0x4D2, 1);
    gGfxBufferIndex ^= 1;
    gFrameCounter++;
    gGfxCurrentFrameBuffer = D_80767CE8 + gGfxBufferIndex * 0x11B0;
    controllerUpdate();
    if ((gScreenRenderFlags & 1) && gScreenFadeProgress == 31.0f) {
        glist = gGfxTaskBuffers[gGfxBufferIndex];
    } else {
        arcadeBuildDisplayList(gGfxCurrentFrameBuffer, &glist);
    }
    glist = screenFadeUpdate(glist, 0);
    if (gGameMode != 3) {
        subList = (Gfx *)(gGfxCurrentFrameBuffer + 0xDB0);
        gfxEndDisplayList(glist, gGfxBufferIndex, &D_8076A088, 0);
        gfxEndSubDisplayList(subList, gGfxCurrentFrameBuffer, &D_8076A08C, 1);
    } else {
        gfxEndDisplayList(glist, gGfxBufferIndex, &D_8076A088, 1);
    }
}

void arcadeBuildDisplayList(u8 *frameBuf, Gfx **glistp) {
    Gfx *glist = gGfxTaskBuffers[gGfxBufferIndex];

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(frameBuf));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));
    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist++, &D_1000040);
    gDPPipeSync(glist++);
    glist = gfxSetFrameBufferColorImage(glist);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 6, 2, 0);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 4, 2, 0);
    gDPSetFillColor(glist++, 0x00050005);
    gDPFillRectangle(glist++, 0, 0, 319, 239);
    arcadeDispatchState(&glist);
    *glistp = glist;
}
extern s32 D_8004A74C[5];
extern u8 D_8004A778[5][3];
extern s32 D_8004A760;

void arcadeSaveHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        eepromSetField(0x15, 0, i, 0, D_8004A74C[i]);
        eepromSetField(0x12, 0, i, 0, D_8004A778[i][0]);
        eepromSetField(0x13, 0, i, 0, D_8004A778[i][1]);
        eepromSetField(0x14, 0, i, 0, D_8004A778[i][2]);
    }
    D_8004A760 = D_8004A74C[0];
    func_8060DEA8();
}

void arcadeLoadHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_8004A74C[i] = eepromGetField(0x15, 0, i, 0);
        D_8004A778[i][0] = eepromGetField(0x12, 0, i, 0);
        D_8004A778[i][1] = eepromGetField(0x13, 0, i, 0);
        D_8004A778[i][2] = eepromGetField(0x14, 0, i, 0);
    }
    D_8004A760 = D_8004A74C[0];
}

extern u8 D_8004C725;
extern u8 D_8004C726;
extern u8 D_8004C727;
extern u8 D_8004C728;
void arcadeSetTextColor(s32 r, s32 g, s32 b, s32 a) {
    D_8004C725 = r;
    D_8004C726 = g;
    D_8004C727 = b;
    D_8004C728 = a;
}

extern s32 D_8004C72C;
extern s32 D_8004C730;
void arcadeSetTextPosition(s32 xPos, s32 yPos) {
    D_8004C72C = xPos;
    D_8004C730 = yPos;
}

void arcadeDrawString(Gfx **glistp, u8 *str) {
    Gfx *g = *glistp;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200004);
    gDPSetPrimColor(g++, 0, 0, D_8004C725, D_8004C726, D_8004C727, D_8004C728);
    gDPSetCombine(g++, 0x119623, 0xFF2FFFFF);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    *glistp = textDrawString(g, 2, D_8004C72E, D_8004C732, str);
}

extern u32 D_8004A738;
s32 arcadeRand(void) {
    D_8004A738 = D_8004A738 * 0x41C64E6D + 0x3039;
    return (D_8004A738 >> 16) & 0x7FFF;
}

extern s32 D_8004A748;
extern u8 D_8004C71B;
extern u8 D_8004C71C;
void arcadeAddScore(s32 points) {
    s32 old = D_8004A748;
    D_8004A748 += points;
    if (D_8004A748 >= 0x2710 && old < 0x2710) {
        D_8004C71B++;
        D_8004C71C++;
    }
}

f32 arcadeMinFloat(f32 a, f32 b) {
    if (b < a) {
        return b;
    }
    return a;
}


s32 arcadeFindFreeEntity(void) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (D_8004BCD0[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindFreeEntityAfterPlayer(void) {
    s32 i;
    for (i = D_8004C71F + 1; i < 0x50; i++) {
        if (D_8004BCD0[i].type == 0) {
            return i;
        }
    }
    return 0;
}
s32 arcadeFindFreeEntityReverse(void) {
    s32 i;
    for (i = 0x4F; i >= 0; i--) {
        if (D_8004BCD0[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindFreeEntitySlot39(void) {
    s32 i;
    for (i = 0x27; i >= 0; i--) {
        if (D_8004BCD0[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindFreeEntitySlot36(void) {
    s32 i;
    for (i = 0x24; i >= 0; i--) {
        if (D_8004BCD0[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindEntityByType(s32 type) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (type == D_8004BCD0[i].type) {
            return i;
        }
    }
    return -1;
}

s32 arcadeCountEntitiesByType(s32 type) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < 0x50; i++) {
        if (type == D_8004BCD0[i].type) {
            count++;
        }
    }
    return count;
}
extern s32 D_8004A78C[];
extern s32 D_8004A790;
extern s32 D_8004C6D8;

void arcadeDispatchState(Gfx **glistp) {
    Gfx *glist = *glistp;

    if (D_8004A78C[0] != 0) {
        D_8004A78C[0] = 0;
        D_8004C722 = 1;
        arcadeInitTitleScreen();
        arcadeLoadHighScores();
    }
    switch (D_8004C724) {
    case 0:
        arcadeTitleLoop(&glist);
        break;
    case 1:
        arcadeStageIntroLoop(&glist);
        break;
    case 5:
        arcadeGameplayLoop(&glist);
        break;
    case 4:
        arcadePauseMenuLoop(&glist);
        break;
    case 3:
        arcadeAttractLoop(&glist);
        break;
    default:
        arcadeDemoLoop(&glist);
        break;
    }
    arcadeDrawHud(&glist);
    D_8004C6D8++;
    glist--;
    *glistp = glist;
    D_8004A78C[1]++;
}


extern u8 D_8004A794;
void arcadeInsertHighScore(s32 rank) {
    s32 i;
    s32 j;
    u16 initial[2];  // FAKE: address-taken storage preserves the byte at sp+0xC

    *(u8 *)initial = D_8004A794;
    for (i = 4; i > rank; i--) {
        D_8004A74C[i] = D_8004A74C[i - 1];
        for (j = 0; j < 3; j++) {
            D_8004A778[i][j] = D_8004A778[i - 1][j];
        }
    }
    D_8004A74C[rank] = D_8004A748;
    if (((u8 *)initial)[i % 1]) {}  // FAKE: read only the initialized byte, retaining its memory slot
    if ((u32)i < 0 && initial[0]) {}  // FAKE: unsigned < 0 is always false; the halfword is never read
    if (D_8004A778[rank] && D_8004A778[rank]) {}  // FAKE: finish the row address before reusing a0
    if (((u8 *)initial)[i % 1]) {}  // FAKE: split the reload live range from the row index
    i = 0; do {  // LAYOUT: init joined on the do line
        D_8004A778[rank][i] = *(u8 *)initial;
        i++;
    } while (i < 3);
}

extern ArcadeEntity D_8004A698;
extern u8 D_8004A774[3];
extern u8 D_8004C720;
void arcadeCheckGameOver(void) {
    u8 rank;
    u8 i;

    for (rank = 0; rank < 5; rank++) {
        if (D_8004A74C[rank] < D_8004A748) {
            arcadeInsertHighScore(rank);
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        D_8004A774[i] = 0x20;
    }
    D_8004C724 = 3;
    D_8004C722 = 0;
    D_8004C6DC = 0;
    for (i = 0; i < 0x50; i++) {
        D_8004C720 = 0;
        D_8004BCD0[i].type = 0;
        D_8004BCD0[0] = D_8004A698;
        D_8004BCD0[0].unk1C = rank;
    }
}

extern u8 D_8004A73C;
extern u8 D_8004A770;
void arcadeExit(void) {
    if (D_8004A73C == 0) {
        if (D_8004A770 != 0 && D_8004A740 != 0 && flagGet(0x84, 0) == 0) {
            if (flagGet(0x82, 0) != 0) {
                flagSet(0x11, 1, 2);
            } else {
                flagSet(0x10, 1, 2);
            }
        }
        if (D_8004A740 != 0) {
            mapTransitionToPreviousOrExit();
        } else {
            mapRequestTransition(0x50, 0);
        }
        D_8004A73C = 1;
    }
}
void arcadeAttractLoop(Gfx **glistp) {
    Gfx *glist = *glistp;
    D_8004C6DC++;
    arcadeDrawBackground(&glist);
    arcadeDispatchEntities();
    arcadeRenderEntities(&glist);
    if (D_8004C6DC >= 0x7BD) {
        if (D_8004A740 != 0) {
            arcadeExit();
        } else {
            arcadeInitTitleScreen();
        }
    }
    *glistp = glist;
}
extern ArcadeEntity D_8004A538;
extern u8 D_800424D0[];
void arcadeInitTitleScreen(void) {
    ArcadeEntity *e;
    s32 idx;

    D_8004C724 = 0;
    D_8004A740 = flagGet(0x63, 2);
    D_8004C722 = 0;
    D_8004C6DC = 0x200;
    D_8004C71D = 1;
    for (e = D_8004BCD0; e < &D_8004BCD0[80]; e++) {
        e->type = 0;
    }
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A538;
    D_8004BCD0[idx].sprite = D_800424D0;
    D_8004BCD0[idx].x = 138.0f;
    D_8004BCD0[idx].y = 180.0f;
}

extern ArcadeEntity D_8004A4B8;
extern ArcadeEntity D_8004A4D8;
extern ArcadeEntity D_8004A4F8;
extern u8 D_8004C723;
extern u16 D_807ECD48;
void arcadeTitleLoop(Gfx **glistp) {
    Gfx *glist;
    s32 i;
    s32 idx;

    glist = *glistp;
    D_8004C6DC++;
    arcadeDrawBackground(&glist);
    if (D_8004C6DC & 0x200) {
        arcadeRenderEntities(&glist);
    }
    if ((D_8004A740 != 0 && D_8004C6DC == 0x5FE) || (D_807ECD48 & 0x9000)) {
        D_8004A748 = 0;
        D_8004C723 = 0;
        D_8004C71B = 2;
        if (D_8004A740 != 0) {
            D_8004C71B = 0;
            if (flagGet(0x84, 0) != 0) {
                D_8004C723 = 8;
            } else if (flagGet(0x82, 0) != 0) {
                D_8004C723 = 4;
            }
        }
        if (D_8004C723 / 4 + 1 >= 10) {
            D_8004A76C = 9;
        } else {
            D_8004A76C = D_8004C723 / 4 + 1;
        }
        D_8004C71C = D_8004C71B + 1;
        D_8004C722 = 1;
        D_8004C724 = 1;
        D_8004C6DC = 0;
        D_8004C71D = 1;
        D_8004C721 = 0;
        for (i = 0; i < 0x50; i++) {
            D_8004BCD0[i].type = 0;
        }
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A4D8;
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A4B8;
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A538;
        if (D_8004A76C == 2 && D_8004A740 != 0) {
            idx = arcadeFindFreeEntity();
            D_8004BCD0[idx] = D_8004A4F8;
        }
        D_8004C708 = 0;
    }
    *glistp = glist;
}

void arcadeStageIntroLoop(Gfx **glistp) {
    Gfx *glist = *glistp;
    arcadeDispatchEntities();
    arcadeDrawBackground(&glist);
    arcadeRenderEntities(&glist);
    if (D_8004C6DC++ >= 0x2F9) {
        arcadeFinishStageIntro();
    }
    *glistp = glist;
}

extern s32 D_8004C714;
void arcadeSetStageMusic(void) {
    if (D_8004C722 == 1) {
        D_8004C714 = 0x4D;
    } else if (D_8004C722 == 2) {
        D_8004C714 = 0x4F;
    } else if (D_8004C722 == 4) {
        D_8004C714 = 0x4E;
    } else {
        D_8004C714 = -1;
    }
}

extern struct GfSndState *D_80770DF8;
void arcadeStopSound(s32 soundId) {
    D_8004C714 = soundId;
    if (D_80770DF8 != 0) {
        n_alSndpStop(D_80770DF8);
    }
}

extern ALBank *D_8076D1F8;
void arcadeGameplayLoop(Gfx **glistp) {
    Gfx *glist = *glistp;

    arcadeDrawBackground(&glist);
    if ((D_8004C71E < 0xA) && ((D_8004C714 == 0x4D) || (D_8004C714 == 0x4E) || (D_8004C714 == 0x4F) || (D_8004C714 == -1))) {
        arcadeStopSound(0x48);
    }
    if ((D_80770DF8 == 0) && (D_8004C714 > 0)) {
        n_alSndpPlay(D_8076D1F8, (s16)D_8004C714, 0x7FFF, 0x3F, 1.0f, 0, &D_80770DF8);
    }
    if (D_8004A760 < D_8004A748) {
        D_8004A760 = D_8004A748;
    }
    if (D_8004C6DC++ == 0x3C) {
        D_8004C71C = D_8004C71B;
        D_8004C71D = 0;
        D_8004BCD0[arcadeFindEntityByType(0xD)].state = 2;
    }
    arcadeDispatchEntities();
    arcadeRenderEntities(&glist);
    if (D_8004C71D == 0) {
        if (D_8004C722 == 2) {
            arcadeSpawnStage2Enemies();
        }
        if (D_8004C722 == 4) {
            arcadeSpawnStage4Enemies();
        }
        if (D_807ECD48 & 0x1000) {
            arcadeOpenPauseMenu();
            D_8004C724 = 4;
        }
    }
    *glistp = glist;
}
extern ArcadeEntity D_8004A6B8;
extern OSContPad *D_807ECDE8;
extern s8 D_8004A768;
extern s32 D_8004C70C;
extern u8 D_8004A744;

void arcadeOpenPauseMenu(void) {
    s32 col;
    s32 row;
    f32 colX;

    for (col = 0x60; col != 0xE0; col += 0x10) {
        colX = col;
        for (row = 0x8C; row != 0xCC; row += 0x10) {
            s32 index = arcadeFindFreeEntityReverse();
            D_8004BCD0[index] = D_8004A6B8;
            D_8004BCD0[index].x = colX;
            D_8004BCD0[index].y = row;
        }
    }
    D_8004A768 = 0;
    D_8004C70C = D_807ECDE8->stick_y;
    D_8004A744 = 0;
}

void arcadeClearEntitiesByType1C(void) {
    s32 index;
    do {
        index = arcadeFindEntityByType(0x1C);
        if (index >= 0) {
            D_8004BCD0[index].type = 0;
        }
    } while (index >= 0);
}

void arcadePauseMenuLoop(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawBackground(&glist);
    arcadeRenderEntities(&glist);
    if ((D_807ECD48 & 0x800) || (D_807ECDE8->stick_y >= 0x1F && D_8004C70C < 0x1F)) {
        D_8004A768--;
    }
    if ((D_807ECD48 & 0x400) || (D_807ECDE8->stick_y < -0x1E && D_8004C70C >= -0x1E)) {
        D_8004A768++;
    }
    if (D_8004A768 >= 3) {
        D_8004A768 = 0;
    }
    if (D_8004A768 < 0) {
        D_8004A768 = 2;
    }
    D_8004C70C = D_807ECDE8->stick_y;
    if (D_807ECD48 & 0x1000) {
        arcadeClearEntitiesByType1C();
        D_8004C724 = 5;
    }
    if (D_807ECD48 & 0xC000) {
        switch (D_8004A768) {
        case 0:
            arcadeClearEntitiesByType1C();
            D_8004C724 = 5;
            break;
        case 1:
            if (D_8004A744 == 0) {
                eepromInitConfigs(2);
                arcadeLoadHighScores();
                arcadeSaveHighScores();
                if (D_8004A760 < D_8004A748) {
                    D_8004A760 = D_8004A748;
                }
                D_8004A744 = 1;
            }
            break;
        case 2:
            arcadeExit();
            break;
        }
    }
    *glistp = glist;
}

extern ArcadeEntity D_8004A5D8;
extern f32 D_8004BCD4;
void arcadeFinishStageIntro(void) {
    ArcadeEntity *e;
    s32 i;
    s32 idx;
    s32 rank;

    for (e = (ArcadeEntity *)((u8 *)&D_8004BCD4 - 4);;) { // FAKE: offset-symbol bases (Q0028) steer the loop pointer (natural &D_8004BCD0[80]: text=16)
        e->type = 0;
        e++;
        if ((u8 *)e >= (u8 *)&D_8004C6D4 - 4) { // FAKE: offset-symbol bases (Q0028) steer the loop pointer (natural &D_8004BCD0[80]: text=16)
            break;
        }
    }
    for (i = 0; i < (D_8004C723 & 3) + 1; i++) {
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A5D8;
        D_8004BCD0[idx].y -= i * 0x20;
    }
    D_8004C6DC = 0;
    rank = D_8004C723 / 4 + 1;
    if (rank >= 10) {
        D_8004A76C = 9;
    } else {
        D_8004A76C = rank;
    }
    n_alSndpPlay(D_8076D1F8, 0x47, 0x7FFF, 0x3F, 1.0f, 0, 0);
    D_8004C724 = 2;
    D_8004C71D = 1;
}

void arcadeDemoLoop(Gfx **glistp) {
    Gfx *glist = *glistp;
    arcadeDrawBackground(&glist);
    arcadeRenderEntities(&glist);
    if (D_8004C6DC++ >= 0xA1) {
        arcadeInitStage();
        D_8004C724 = 5;
    }
    *glistp = glist;
}

extern u8 D_80032B48[];
extern u8 D_80032B90[];
extern u8 D_80032BD8[];
extern ArcadeGfxSlot D_8004BB30[];
extern ArcadeGfxSlot D_8004BB60[];
extern ArcadeGfxSlot D_8004BB90[];
extern ArcadeGfxSlot D_8004BBC0[];
typedef struct ArcadeTitleBitmap {
    s32 words[12];
} ArcadeTitleBitmap;
extern ArcadeTitleBitmap D_8004A798;
extern u8 D_8004C719;
extern u8 D_8004C71A;
extern u8 gGfxBufferIndex;
extern ArcadeGfxSlot D_8004BB00[];
extern u8 D_80032C20[];
extern u8 D_80032DF8[];
void dlInitTextureDescriptor(void *, void *, s32, u8, u8, u8, s32, s32, s32, s32); // FAKE: callee prototype steer
void arcadeDrawBackground(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    gDPSetAlphaCompare(glist++, G_AC_NONE);
    gDPSetTexturePersp(glist++, G_TP_NONE);
    gDPSetTextureFilter(glist++, G_TF_BILERP);
    gDPSetTextureConvert(glist++, G_TC_FILT);
    gDPSetTextureDetail(glist++, G_TD_CLAMP);
    gDPSetTextureLOD(glist++, G_TL_TILE);
    gDPSetTextureLUT(glist++, G_TT_NONE);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    gDPSetCombine(glist++, 0x11FE23, 0xFFFFF3F9);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, 48, 36, 272, 232);

    switch (D_8004C724) {
    case 0:
        if (D_8004C6DC & 0x200) {
            arcadeDrawTitleText(&glist);
        }
        break;
    case 1:
    case 4:
    case 5:
        switch (D_8004C722) {
        case 1:
            arcadeDrawStage1Background(&glist);
            break;
        case 2:
            arcadeDrawStage2Background(&glist);
            break;
        case 3:
            arcadeDrawStage3Background(&glist);
            break;
        default:
            arcadeDrawStage4Background(&glist);
            break;
        }
        break;
    }
    *glistp = glist;
}

void arcadeDrawLadder(Gfx **glistp, s32 x, s32 y, s32 height) {
    s32 i;
    Gfx *glist;

    D_8004C719 = 8;
    D_8004C71A = 4;
    D_8004C6D4.word = 0x400;
    if (D_8004C722 == 2) D_8004C6D0 = D_80032B90;
    else if (D_8004C722 == 4) D_8004C6D0 = D_80032BD8;
    else D_8004C6D0 = D_80032B48;
    dlInitTextureDescriptor(&D_8004BB30[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlInitTextureDescriptor(&D_8004BB60[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, 1, 0, 2, 0, 0);
    dlInitTextureDescriptor(&D_8004BB90[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, 2, 0, 2, 0, 0);
    dlInitTextureDescriptor(&D_8004BBC0[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, 3, 0, 2, 0, 0);
    glist = *glistp;
    dlAppendTextureLoad(&glist, &D_8004BB30[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    for (i = 0; i < height / 4; i++) {
        dlAppendTextureRectangle(&glist, x * 4, (s32)((f64)(i * 4 + y + 8) * 4.0));
    }
    D_8004C71A = height % 4;
    if (D_8004C71A != 0) {
        switch (D_8004C71A) {
        case 1:
            dlAppendTextureLoad(&glist, &D_8004BB60[gGfxBufferIndex]);
            break;
        case 2:
            dlAppendTextureLoad(&glist, &D_8004BB90[gGfxBufferIndex]);
            break;
        case 3:
            dlAppendTextureLoad(&glist, &D_8004BBC0[gGfxBufferIndex]);
            break;
        }
        dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
        dlAppendTextureRectangle(&glist, x * 4, (s32)((f64)(i * 4 + y + 8) * 4.0));
    }
    *glistp = glist;
}

void arcadeDrawStage1Ladders(Gfx **glistp) {
    Gfx *glist;
    s32 height;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x70, 0x1C, 0x2E);
    arcadeDrawLadder(&glist, 0x80, 0x1C, 0x2E);
    arcadeDrawLadder(&glist, 0xB0, 0x38, 0x12);
    if (D_8004C724 == 1) {
        if (D_8004C6DC < 0x190) {
            height = 0x82 - (((s32) (D_8004C6DC - 0x3C) / 20) * 8);
            if (height >= 0x83) {
                height = 0x82;
            }
            if (height < 0x22) {
                height = 0x22;
            }
            arcadeDrawLadder(&glist, 0xA0, 0x51, height);
            arcadeDrawLadder(&glist, 0xB0, 0x51, height);
        }
    } else {
        arcadeDrawLadder(&glist, 0x88, 0x50, 4);
        arcadeDrawLadder(&glist, 0x88, 0x5B, 0xC);
        arcadeDrawLadder(&glist, 0xE8, 0x53, 0xE);
        arcadeDrawLadder(&glist, 0x50, 0x70, 0xE);
        arcadeDrawLadder(&glist, 0x78, 0x6E, 0x12);
        arcadeDrawLadder(&glist, 0xD8, 0x69, 8);
        arcadeDrawLadder(&glist, 0xD8, 0x7D, 8);
        arcadeDrawLadder(&glist, 0x70, 0x87, 5);
        arcadeDrawLadder(&glist, 0x70, 0x99, 8);
        arcadeDrawLadder(&glist, 0xA8, 0x89, 0x16);
        arcadeDrawLadder(&glist, 0xE8, 0x8D, 0xE);
        arcadeDrawLadder(&glist, 0x50, 0xAA, 0xE);
        arcadeDrawLadder(&glist, 0x90, 0xA6, 0x15);
        arcadeDrawLadder(&glist, 0x80, 0xC1, 4);
        arcadeDrawLadder(&glist, 0x80, 0xD1, 8);
        arcadeDrawLadder(&glist, 0xE8, 0xC7, 0xE);
    }
    *glistp = glist;
}

void arcadeDrawStage2Ladders(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x38, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x100, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x40, 0x9B, 0x1C);
    arcadeDrawLadder(&glist, 0xF8, 0x9B, 0x1C);
    arcadeDrawLadder(&glist, 0x48, 0x7A, 0x1A);
    arcadeDrawLadder(&glist, 0xF0, 0x7A, 0x1A);
    arcadeDrawLadder(&glist, 0x50, 0x58, 0x1C);
    arcadeDrawLadder(&glist, 0xE8, 0x58, 0x1C);
    if (D_8004C708 == 0) {
        arcadeDrawLadder(&glist, 0x98, 0xBD, 0x1C);
        arcadeDrawLadder(&glist, 0x78, 0x9B, 0x1C);
        arcadeDrawLadder(&glist, 0xC0, 0x9B, 0x1C);
        arcadeDrawLadder(&glist, 0x98, 0x7A, 0x1A);
        arcadeDrawLadder(&glist, 0x70, 0x58, 0x1C);
        arcadeDrawLadder(&glist, 0xC8, 0x58, 0x1C);
    }
    *glistp = glist;
}

void arcadeDrawStage3Ladders(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x70, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0x80, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0xB0, 0x38, 0x15);
    arcadeDrawLadder(&glist, 0xD0, 0x54, 0x15);
    arcadeDrawLadder(&glist, 0x100, 0x62, 0x1C);
    arcadeDrawLadder(&glist, 0xB8, 0x77, 0x15);
    arcadeDrawLadder(&glist, 0x40, 0x7E, 0x2A);
    arcadeDrawLadder(&glist, 0x70, 0x7E, 0x38);
    arcadeDrawLadder(&glist, 0x80, 0x7E, 0x38);
    arcadeDrawLadder(&glist, 0xE8, 0x85, 0x15);
    arcadeDrawLadder(&glist, 0x100, 0xA8, 0xE);
    arcadeDrawLadder(&glist, 0x38, 0xAF, 0x1C);
    *glistp = glist;
}

void arcadeDrawStage4Ladders(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x70, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0x80, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0xB0, 0x38, 0x15);
    arcadeDrawLadder(&glist, 0x48, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x80, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0xB8, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0xF0, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x70, 0x9A, 0x1C);
    arcadeDrawLadder(&glist, 0xC0, 0x9A, 0x1C);
    arcadeDrawLadder(&glist, 0x48, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0x80, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0xB8, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0xF0, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0x40, 0x62, 0xE);
    arcadeDrawLadder(&glist, 0xF8, 0x62, 0xE);
    *glistp = glist;
}

void arcadeDrawTitleText(Gfx **glistp) {
    s32 row;
    s32 j;
    Gfx *glist;
    ArcadeTitleBitmap titleBitmap;
    s32 i;

    titleBitmap = D_8004A798;
    glist = *glistp;
    D_8004C719 = 8;
    D_8004C71A = 8;
    D_8004C6D4.word = 0x400;
    if (D_8004C6DC & 0x182) D_8004C6D0 = D_80032C20;
    else D_8004C6D0 = D_80032DF8;
    dlInitTextureDescriptor(&D_8004BB00[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &D_8004BB00[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    for (i = 0; i < 12; i++) {
        row = titleBitmap.words[i];
        for (j = 0; j < 25; j++) {
            if ((1 << j) & row) {
                dlAppendTextureRectangle(&glist, 0x3E0 - (j << 5), (s32)((f64)(i * 8 + 0x3F) * 4.0));
            }
        }
    }
    *glistp = glist;
}

extern u8 D_80034568[];
void arcadeDrawStage1Background(Gfx **glistp) {
    s32 i;
    Gfx *glist;

    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4.word = 0x492;
    D_8004C6D0 = D_80034568;
    dlInitTextureDescriptor(&D_8004BB00[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    glist = *glistp;
    dlAppendTextureLoad(&glist, &D_8004BB00[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    for (i = 0; i < 6; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0x220, 0xE0);
    }
    if (D_8004C708 >= 6) {
        for (i = 0; i < 0xE; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x380);
        }
        for (i = 0xE; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, (s32)((((f64)(0xF7 - ((i - 0xC) / 2)) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x368);
        }
    }
    if (D_8004C708 >= 5) {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, (s32)((((f64)((i / 2) + 0xCF) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x2F4);
        }
    }
    if (D_8004C708 >= 4) {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, (s32)((((f64)(0xBB - (i / 2)) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x281);
        }
    }
    if (D_8004C708 >= 3) {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, (s32)((((f64)((i / 2) + 0x8D) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x20D);
        }
    }
    if (D_8004C708 >= 2) {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, (s32)((((f64)(0x79 - (i / 2)) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x19A);
        }
    }
    if (D_8004C708 > 0) {
        for (i = 0; i < 0x12; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x142);
        }
        for (i = 0x12; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, (s32)((((f64)(((i - 0x10) / 2) + 0x53) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x142);
        }
    }
    arcadeDrawStage1Ladders(&glist);
    *glistp = glist;
}

extern u8 D_80032F18[];
extern ArcadeGfxSlot D_8004BC50[];
void arcadeDrawStage2Background(Gfx **glistp) {
    s32 i;
    Gfx *glist;

    glist = *glistp;
    if (D_8004C708 < 2) {
        D_8004C719 = 2;
        D_8004C71A = 8;
        D_8004C6D4.word = 0x400;
        D_8004C6D0 = D_80032F18;
        dlInitTextureDescriptor(&D_8004BC50[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
        dlAppendTextureLoad(&glist, &D_8004BC50[gGfxBufferIndex]);
        dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
        for (i = 0; i < 4; i++) {
            dlAppendTextureRectangle(&glist, 0x1DC, (s32)((f64)(s32)((f64)(i * 8) + 51.625 + 8.0) * 4.0));
        }
        for (i = 0; i < 4; i++) {
            dlAppendTextureRectangle(&glist, 0x31C, (s32)((f64)(s32)((f64)(i * 8) + 51.625 + 8.0) * 4.0));
        }
    }
    D_8004C719 = 8;
    D_8004C71A = 8;
    D_8004C6D4.word = 0x400;
    D_8004C6D0 = D_80032C20;
    dlInitTextureDescriptor(&D_8004BB00[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &D_8004BB00[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    for (i = 0; i < 0x1C; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x380);
    }
    if (D_8004C708 == 0) {
        for (i = 1; i < 0x1B; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x2F8);
            }
        }
        for (i = 2; i < 0x1A; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x270);
            }
        }
        for (i = 3; i < 0x19; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x1EC);
            }
        }
        for (i = 4; i < 0x18; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x164);
            }
        }
    } else {
        for (i = 8; i < 0x14; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x360);
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x340);
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x320);
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x300);
        }
        for (i = 1; i < 0x1B; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x2F8);
            }
        }
        for (i = 2; i < 0x1A; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x270);
            }
        }
        for (i = 3; i < 0x19; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x1EC);
            }
        }
        for (i = 4; i < 0x18; i++) {
            if (i < 7 || i >= 0x15 || D_8004C708 == 2) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x164);
            }
        }
    }
    if (D_8004C708 < 2) {
        for (i = 0; i < 0xE; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0x1A0, 0xD8);
        }
    }
    arcadeDrawStage2Ladders(&glist);
    *glistp = glist;
}

void arcadeDrawGirderSpan(Gfx **glistp, u8 startX, u8 endX, s16 yVal) {
    u8 i;
    Gfx *glist;

    glist = *glistp;
    for (i = startX; i < endX; i++) {
        dlAppendTextureRectangle(&glist, ((i << 5) + 0xC0), (s32)((((f64) yVal * 0.875) + 8.0) * 4.0));
    }
    *glistp = glist;
}

typedef struct ArcadeGirderSpan {
    u8 x;
    u8 y;
    s16 z;
} ArcadeGirderSpan;
typedef struct ArcadeLift {
    f32 x;
    f32 y;
    f32 vy;
} ArcadeLift;
extern ArcadeLift D_8004BC88[];
extern u8 D_80032F40[];
extern ArcadeGirderSpan D_8004A7C8[];
void arcadeDrawStage3Background(Gfx **glistp) {
    s32 i;
    s32 j;
    s32 pad[1];
    Gfx *glist;
    ArcadeGirderSpan *pt;
    ArcadeLift *bar;

    glist = *glistp;
    D_8004C719 = 2;
    D_8004C71A = 8;
    D_8004C6D4.word = 0x400;
    D_8004C6D0 = D_80032F40;
    dlInitTextureDescriptor(&D_8004BC50[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &D_8004BC50[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    for (j = 5; j < 0x14; j++) {
        dlAppendTextureRectangle(&glist, 0x15C, (s32)((f64)(s32)((f64)(j * 8) + 51.625 + 8.0) * 4.0));
    }
    for (j = 5; j < 0x14; j++) {
        dlAppendTextureRectangle(&glist, 0x25C, (s32)((f64)(s32)((f64)(j * 8) + 51.625 + 8.0) * 4.0));
    }
    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4.word = 0x492;
    D_8004C6D0 = D_80034568;
    dlInitTextureDescriptor(&D_8004BB00[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &D_8004BB00[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    pt = D_8004A7C8;
    do {
        arcadeDrawGirderSpan(&glist, pt->x, pt->y, pt->z);
        pt++;
    } while (pt < (ArcadeGirderSpan *)((s32)D_8004A7C8 + 0x54)); // FAKE: (s32) address arithmetic end pointer steers codegen (&D_8004A7C8[21]: text=16)
    for (bar = D_8004BC88;;) {
        if (D_8004C71D == 0 && D_8004C724 == 5) {
            bar->y = bar->y + bar->vy;
            if (bar->y < 99.0f) {
                bar->y = bar->y + 144.0f;
            }
            if (bar->y > 243.0f) {
                bar->y = bar->y - 144.0f;
            }
        }
        for (j = 0; j < 2; j++) {
            dlAppendTextureRectangle(&glist, (s32)((bar->x + 40.0f + (f32)(j * 8)) * 4.0f), (s32)(((f64)bar->y * 0.875 + 8.0) * 4.0));
        }
        bar++;
        if (bar == (ArcadeLift *)D_8004BCD0) break; // FAKE: end pointer via D_8004BCD0 symbol steers codegen (&D_8004BC88[6]: text=17)
    }
    arcadeDrawStage3Ladders(&glist);
    *glistp = glist;
}

extern u8 D_80032CA8[];
extern u8 D_80032D50[];
extern u8 D_800342B8[];
extern ArcadeGfxSlot D_8004BC20[];
void arcadeDrawStage4Background(Gfx **glistp) {
    s32 step;
    s32 one;
    Gfx *glist;
    s32 x;
    s32 i;

    glist = *glistp;
    step = 0x20; // FAKE: value-named constant local steers regalloc (literal: text=15)
    one = 1; // FAKE: value-named constant local steers regalloc
    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4.word = 0x492;
    D_8004C6D0 = D_80032D50;
    dlInitTextureDescriptor(&D_8004BB00[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &D_8004BB00[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    x = 0x220;
    do {
        dlAppendTextureRectangle(&glist, x, 0xE0);
        x += step;
    } while (x < 0x2E0);
    x = 0xC0;
    do {
        dlAppendTextureRectangle(&glist, x, 0x380);
        x += step;
    } while (x < 0x440);
    i = 1;
    do {
        if (i != 6 && i != 7 && i != 0x13 && i != 0x14) {
            dlAppendTextureRectangle(&glist, ((i << 5) + 0xC0), 0x268);
        }
        i += one;
    } while (i < 0x1B);
    D_8004C6D0 = D_80032CA8;
    dlInitTextureDescriptor(&D_8004BC20[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &D_8004BC20[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    x = 0xE0;
    do {
        dlAppendTextureRectangle(&glist, x, 0x150);
        x += step;
    } while (x < 0x420);
    i = 0;
    do {
        if (i < 0xC || i >= 0x10) {
            dlAppendTextureRectangle(&glist, ((i << 5) + 0xC0), 0x1DC);
        }
        i += one;
    } while (i < 0x1C);
    x = 0xE0;
    do {
        dlAppendTextureRectangle(&glist, x, 0x2F4);
        x += step;
    } while (x < 0x420);
    D_8004C6D0 = D_800342B8;
    dlInitTextureDescriptor(&D_8004BC50[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &D_8004BC50[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    x = 0x240;
    do {
        for (i = 0x9F; (i ^ 0) != 0x87; i -= 8) { // FAKE: no-op `^ 0` steers codegen
            dlAppendTextureRectangle(&glist, x, (s32)((((f64)i * 0.875) + 8.0) * 4.0));
        }
        x += step;
    } while (x != 0x2C0);
    arcadeDrawStage4Ladders(&glist);
    *glistp = glist;
}

void arcadeKillPlayer(void) {
    arcadeStopSound(0);
    n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
    D_8004BCD0[D_8004C71F].state = 8;
    D_8004BCD0[D_8004C71F].vx = 0.0f;
    D_8004BCD0[D_8004C71F].animTimer = 0.0f;
    D_8004C71D = 1;
}

extern ArcadeEntity D_8004A398;
extern ArcadeEntity D_8004A438;
extern ArcadeEntity D_8004A458;
extern ArcadeEntity D_8004A518;
extern ArcadeEntity D_8004A558;
extern ArcadeEntity D_8004A638;
extern ArcadeEntity D_8004A718;
extern ArcadeEntity D_8004C170;
void arcadeSpawnStage1Entities(void) {
    float oilDrumY;
    s32 i;

    i = 0;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    oilDrumY = 110.0f; // FAKE: value-named constant local steers the float constant load (inline 110.0f: score 2900)
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A558;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A438;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004C170 = D_8004A458;
    i = i + 0x24;
    D_8004BCD0[i--] = D_8004A638;
    D_8004BCD0[i] = D_8004A638;
    D_8004BCD0[i].x = 68.0f;
    D_8004BCD0[i].y = oilDrumY;
    i--;
    D_8004BCD0[i] = D_8004A718;
    i--;
    D_8004BCD0[i] = D_8004A718;
    D_8004BCD0[i].unk1C = 1;
    D_8004BCD0[i].x = 48.0f;
    i--;
    D_8004BCD0[i] = D_8004A718;
    D_8004BCD0[i].unk1C = 2; D_8004BCD0[i].y = 65.0f; i--;
    D_8004BCD0[i] = D_8004A718;
    D_8004BCD0[i].unk1C = 3;
    D_8004BCD0[i].x = 48.0f;
    D_8004BCD0[i].y = 65.0f;
    D_8004C708 = 7;
}

typedef struct ArcadePosTable {
    u8 b[16];
} ArcadePosTable;
extern ArcadePosTable D_8004A81C;
extern ArcadeEntity D_8004A578;
extern ArcadeEntity D_8004A618;
extern ArcadeEntity D_8004A658;
extern ArcadeEntity D_8004C150;
extern ArcadeEntity D_8004C130;
extern ArcadeEntity D_8004C110;
extern ArcadeEntity D_8004C0F0;
extern u8 D_800335D8[];
extern u8 D_80038FE8[];
extern u8 D_800391F0[];
void arcadeSpawnStage2Entities(void) {
    s32 bit;
    s32 idx;
    s32 i;
    ArcadePosTable tbl;

    tbl = D_8004A81C;
    bit = 1;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A578;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    for (i = 0; i < 8; i++) {
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A658;
        D_8004BCD0[idx].x = (u32)tbl.b[i * 2];
        D_8004BCD0[idx].y = (u32)tbl.b[i * 2 + 1];
        D_8004BCD0[idx].unk1C = bit;
        bit = bit * 2;
    }
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A438;
    D_8004BCD0[idx].sprite = D_800335D8;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004C170 = D_8004A618;
    D_8004BCD0[0x25].sprite = D_80038FE8;
    D_8004C150 = D_8004A618;
    D_8004BCD0[0x24].x = 252.0f;
    D_8004BCD0[0x24].y = 208.0f;
    D_8004C130 = D_8004A618;
    D_8004BCD0[0x23].sprite = D_800391F0;
    D_8004BCD0[0x23].x = 84.0f;
    D_8004BCD0[0x23].y = 93.0f;
    D_8004C110 = D_8004A638;
    D_8004BCD0[0x22].x = 60.0f;
    D_8004BCD0[0x22].y = 152.0f;
    D_8004C0F0 = D_8004A638;
    D_8004BCD0[0x21].x = 156.0f;
    D_8004BCD0[0x21].y = 114.0f;
}

extern s32 D_8004C6E0;
extern s32 D_8004C6E4;
extern s32 D_8004C6E8;
extern s32 D_8004C6EC;
extern s32 D_8004C6F0;
extern s32 D_8004C6F4;
extern s32 D_8004C6F8;

extern u8 D_8004A338[];
extern u8 D_8004A358[];
extern u8 D_8004A378[];
extern ArcadeGfxSlot D_8004AC00[][80];
extern u8 gGfxBufferIndex;

extern f32 D_8004BCF4;

extern u8 D_80034610[];
extern u8 D_80034818[];
extern u8 D_80034A20[];
extern u8 D_80034C28[];
extern u8 D_80034E30[];
extern u8 D_80035038[];
extern u8 D_80035240[];
extern u8 D_80035448[];
extern u8 D_80035650[];
extern u8 D_80035898[];
extern u8 D_80035AE0[];
extern u8 D_80035CE8[];


extern u8 D_8004A788[];
extern s32 D_8004C710;
extern u8 D_8004C718;
extern u8 D_8004A764;


extern ArcadeEntity D_8004A478;
extern ArcadeEntity D_8004A598;
extern ArcadeEntity D_8004A3D8;
void arcadeSpawnStage3Entities(void) {
    s32 i;
    ArcadeEntity *p;
    f32 t;

    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A598;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    i = 0;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A438;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004BCD0[D_8004C71F].x = 56.0f;
    D_8004BCD0[D_8004C71F].y = 231.0f;
    D_8004C170 = D_8004A478;
    i = i + 0x24;
    p = &D_8004BCD0[i];
    *p = D_8004A478;
    p->x = 144.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A478;
    p->unk1B = 1;
    p->y = 238.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A478;
    p->unk1B = 1;
    p->x = 144.0f;
    p->y = 238.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A618;
    p->sprite = D_80038FE8;
    p->x = 260.0f;
    p->y = 103.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A618;
    p->sprite = D_800391F0;
    p->x = 60.0f;
    p->y = 135.0f;
    i = arcadeFindFreeEntity();
    p = &D_8004BCD0[i];
    *p = D_8004A3D8;
    p->unk1A = 1;
    p->vx = 0.5f;
    p->x = 114.0f;
    p->y = 135.0f;
    i = arcadeFindFreeEntity();
    p = &D_8004BCD0[i];
    *p = D_8004A3D8;
    p->unk1A = 1;
    p->vx = 0.5f;
    p->x = 260.0f;
    p->y = 103.0f;
    D_8004BC88[0].x = 40.0f;
    D_8004BC88[1].x = 40.0f;
    D_8004BC88[2].x = 40.0f;
    D_8004BC88[3].x = 104.0f;
    D_8004BC88[4].x = 104.0f;
    D_8004BC88[5].x = 104.0f;
    D_8004BC88[0].y = 95.0f;
    D_8004BC88[3].y = 95.0f;
    D_8004BC88[1].y = 143.0f;
    D_8004BC88[4].y = 143.0f;
    D_8004BC88[2].y = 191.0f;
    D_8004BC88[5].y = 191.0f;
    t = (arcadeMinFloat((f32)(u32)D_8004A76C, 4.0f) - 2.0) / 16 + 0.5;
    D_8004BC88[3].vy = t;
    D_8004BC88[0].vy = -t;
    D_8004BC88[1].vy = -t;
    D_8004BC88[2].vy = -t;
    D_8004BC88[4].vy = t;
    D_8004BC88[5].vy = t;
}

extern ArcadeEntity D_8004A678;
extern ArcadeEntity D_8004A5B8;
extern ArcadeEntity D_8004A3F8;
extern ArcadeEntity D_8004A498;
extern ArcadeEntity D_8004C0D0;
extern ArcadeEntity D_8004C0B0;
extern ArcadeEntity D_8004C090;
extern ArcadeEntity D_8004C070;
extern ArcadeEntity D_8004C050;
extern ArcadeEntity D_8004C030;
extern ArcadeEntity D_8004C010;
extern ArcadeEntity D_8004BFF0;
extern u8 D_80033C48[];
void arcadeSpawnStage4Entities(void) {
    s32 idx;

    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A678;
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A678;
    D_8004BCD0[idx].x = 244.0f;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A5B8;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A438;
    D_8004BCD0[idx].sprite = D_80033C48;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004C170 = D_8004A458;
    D_8004BCD0[0x25].x = 152.0f;
    D_8004BCD0[0x25].y = 127.0f;
    D_8004C150 = D_8004A3F8;
    D_8004BCD0[0x24].x = 152.0f;
    D_8004BCD0[0x24].y = 113.0f;
    D_8004C130 = D_8004A618;
    D_8004BCD0[0x23].sprite = D_80038FE8;
    D_8004BCD0[0x23].x = 172.0f;
    D_8004C110 = D_8004A618;
    D_8004BCD0[0x22].y = 167.0f;
    D_8004BCD0[0x22].x = 116.0f;
    D_8004C0F0 = D_8004A618;
    D_8004BCD0[0x21].sprite = D_800391F0;
    D_8004BCD0[0x21].y = 167.0f;
    D_8004BCD0[0x21].x = 252.0f;
    D_8004C0D0 = D_8004A638;
    D_8004BCD0[0x20].x = 68.0f;
    D_8004BCD0[0x20].y = 148.0f;
    D_8004C0B0 = D_8004A638;
    D_8004BCD0[0x1F].x = 156.0f;
    D_8004BCD0[0x1F].y = 188.0f;
    D_8004C090 = D_8004A498;
    D_8004C070 = D_8004A498;
    D_8004BCD0[0x1D].unk1A = 1;
    D_8004BCD0[0x1D].unk1B = 1;
    D_8004BCD0[0x1D].unk1C = 0;
    D_8004BCD0[0x1D].x = 256.0f;
    D_8004BCD0[0x1D].y = 84.0f;
    D_8004C050 = D_8004A498;
    D_8004BCD0[0x1C].unk1A = 1;
    D_8004BCD0[0x1C].unk1B = 1;
    D_8004BCD0[0x1C].unk1C = 1;
    D_8004BCD0[0x1C].y = 124.0f;
    D_8004BCD0[0x1C].x = 139.0f;
    D_8004C030 = D_8004A498;
    D_8004BCD0[0x1B].y = 124.0f;
    D_8004BCD0[0x1B].unk1C = 2;
    D_8004BCD0[0x1B].x = 165.0f;
    D_8004C010 = D_8004A498;
    D_8004BCD0[0x1A].y = 204.0f;
    D_8004BCD0[0x1A].unk1C = 3;
    D_8004BCD0[0x1A].x = 48.0f;
    D_8004BFF0 = D_8004A498;
    D_8004BCD0[0x19].unk1A = 1;
    D_8004BCD0[0x19].unk1B = 1;
    D_8004BCD0[0x19].x = 256.0f;
    D_8004BCD0[0x19].y = 204.0f;
    D_8004BCD0[0x19].unk1C = 3;
}

void arcadeInitStage(void) {
    s32 i;
    s32 temp;

    D_8004C708 = 0;
    D_8004C722 = D_8004A788[D_8004C723 & 3];
    for (i = 0; i < 80; i++) {
        D_8004BCD0[i].type = 0;
    }
    switch (D_8004C722) {
    case 1:
        arcadeSpawnStage1Entities();
        break;
    case 2:
        arcadeSpawnStage2Entities();
        break;
    case 3:
        arcadeSpawnStage3Entities();
        break;
    default:
        arcadeSpawnStage4Entities();
        break;
    }
    arcadeSetStageMusic();
    temp = D_8004A76C * 10 + 40;
    if (temp >= 91) {
        D_8004C71E = 90;
    } else {
        D_8004C71E = temp;
    }
    D_8004C710 = 0;
    D_8004C718 = 0xFF;
    D_8004A764 = 0;
    D_8004C6DC = 0;
    D_8004C71D = 1;
    D_8004C6F8 = 1;
    D_8004C721 = 1;
    D_8004A308[0] = 0;
    D_8004A308[1] = 0;
    D_8004A308[2] = 0;
    D_8004A308[3] = 0;
}

s32 arcadeCheckStage1Collision(s32 posX, s32 posY) {
    s32 ret;
    s32 temp;

    if (posY < 0x5D) {
        D_8004C6F0 = 0x88;
    } else {
        D_8004C6F0 = 0x36;
    }
    D_8004C6F4 = 0x10A;

    if (posY < 0x3F) {
        D_8004C6F8 = 0;
        if (posX >= 0x85 && posX < 0xBC) {
            ret = 0x37;
        } else {
            ret = 0xF8;
        }
    } else if (posY < 0x5D) {
        D_8004C6F8 = 1;
        temp = posX / 16;
        ret = temp;
        if (temp < 0xB) {
            ret = 0xB;
        }
        ret += 0x48;
        if (posX >= 0x105) {
            ret = 0xF8;
        }
    } else if (posY < 0x7F) {
        D_8004C6F8 = 2;
        ret = 0x7C - (posX / 16);
        if (posX < 0x3C) {
            ret = 0xF8;
        }
    } else if (posY < 0xA0) {
        D_8004C6F8 = 3;
        ret = (posX / 16) + 0x8A;
        if (posX >= 0x105) {
            ret = 0xF8;
        }
    } else if (posY < 0xC3) {
        D_8004C6F8 = 4;
        ret = 0xBE - (posX / 16);
        if (posX < 0x3C) {
            ret = 0xF8;
        }
    } else if (posY < 0xE1) {
        D_8004C6F8 = 5;
        ret = (posX / 16) + 0xCC;
        if (posX >= 0x105) {
            ret = 0xF8;
        }
    } else {
        D_8004C6F8 = 6;
        ret = 0x100 - (posX / 16);
        if (ret >= 0xF8) {
            ret = 0xF7;
        }
    }

    if (ret < posY) {
        D_8004C6F8++;
    }
    return ret;
}

s32 arcadeCheckStage2Collision(s32 posX, s32 posY) {
    s32 ret;

    D_8004C6F0 = 0x36;
    D_8004C6F4 = 0x10A;
    if (posY < 0x6E) {
        D_8004C6F8 = 1;
        if (posX >= 0x4D && posX < 0xF4 &&
            (posX < 0x6C || posX >= 0x6D || (D_8004C718 & 0x40)) &&
            (posX < 0xD4 || posX >= 0xD5 || (D_8004C718 & 0x80))) {
            ret = 0x5D;
        } else {
            ret = 0xF7;
        }
    } else if (posY < 0x8C) {
        D_8004C6F8 = 2;
        if (posX >= 0x45 && posX < 0xFC &&
            (posX < 0x6C || posX >= 0x6D || (D_8004C718 & 0x10)) &&
            (posX < 0xD4 || posX >= 0xD5 || (D_8004C718 & 0x20))) {
            ret = 0x84;
        } else {
            ret = 0xF7;
        }
    } else if (posY < 0xBE) {
        D_8004C6F8 = 3;
        if (posX >= 0x3D && posX < 0x104 &&
            (posX < 0x6C || posX >= 0x6D || (D_8004C718 & 4)) &&
            (posX < 0xD4 || posX >= 0xD5 || (D_8004C718 & 8))) {
            ret = 0xAA;
        } else {
            ret = 0xF7;
        }
    } else if (posY < 0xDC) {
        D_8004C6F8 = 4;
        if ((posX < 0x6C || posX >= 0x6D || (D_8004C718 & 1)) &&
            (posX < 0xD4 || posX >= 0xD5 || (D_8004C718 & 2))) {
            ret = 0xD0;
        } else {
            ret = 0xF7;
        }
    } else {
        D_8004C6F8 = 5;
        ret = 0xF7;
    }

    if (ret < posY) {
        D_8004C6F8++;
    }
    return ret;
}

extern ArcadeLift D_8004BCAC[];

s32 arcadeCheckStage3Collision(s32 posX, s32 posY) {
    s32 ret;
    ArcadeLift *bar;
    ArcadeLift *end;

    if (posY < 0x5D) {
        D_8004C6F0 = 0x88;
    } else {
        D_8004C6F0 = 0x36;
    }
    D_8004C6F4 = 0x10A;
    D_8004C6F8 = 1;
    if (posY < 0x3F) {
        if (posX >= 0x85 && posX < 0xBC) {
            ret = 0x37;
            D_8004C6F8 = 0;
        } else {
            ret = 0xF8;
        }
    } else if (posY < 0x62) {
        if (posX < 0xDC) {
            ret = 0x57;
        } else {
            ret = 0xF8;
        }
    } else if (posY < 0x8C) {
        if (posX >= 0xFD) {
            ret = 0x67;
        } else if (posX >= 0xE5 && posX < 0xFC) {
            ret = 0x6F;
        } else if (posX >= 0xCD && posX < 0xE4) {
            ret = 0x77;
        } else if (posX >= 0xAD && posX < 0xCC) {
            ret = 0x7F;
        } else if ((posX >= 0x65 && posX < 0x8C) || posX < 0x4C) {
            ret = 0x87;
        } else {
            ret = 0xF8;
        }
    } else if (posY < 0x94) {
        if (posX >= 0xE5) {
            ret = 0x8F;
        } else {
            ret = 0xF7;
        }
    } else if (posY < 0xC6) {
        if (posX >= 0xFD) {
            ret = 0xB7;
        } else if (posX >= 0xE5 && posX < 0xFC) {
            ret = 0xAF;
        } else if (posX >= 0xCD && posX < 0xE4) {
            ret = 0xA7;
        } else if (posX >= 0xB5 && posX < 0xCC) {
            ret = 0x9F;
        } else if (posX < 0x4C) {
            ret = 0xBF;
        } else {
            ret = 0xF8;
        }
    } else {
        if (posY < 0xF0) {
            if ((posX >= 0x6D && posX < 0x8C) || posX >= 0xF5) {
                ret = 0xCF;
            } else if (posX >= 0xDD && posX < 0xF4) {
                ret = 0xD7;
            } else if (posX >= 0xC5 && posX < 0xDC) {
                ret = 0xDF;
            } else if ((posX >= 0xA5 && posX < 0xC4) || posX < 0x4C) {
                ret = 0xE7;
            } else {
                ret = 0xF8;
            }
        } else {
            ret = 0xF7;
        }
    }
    if (posX >= 0x4D && posX < 0x64) {
        end = (ArcadeLift *)(s32)&D_8004BCAC; // FAKE: (s32) cast end pointer steers codegen (D_8004BCAC: text=18)
        for (bar = D_8004BC88; ; ) {
            f32 y = bar->y;
            bar++;
            if (y < (f32)(posY + 4) && (f32)(posY - 0x10) < y) {
                ret = (s32)y;
            }
            if (bar == end) {
                break;
            }
        }
    }
    if (posX >= 0x8D && posX < 0xA4) {
        end = &D_8004BC88[6];
        for (bar = D_8004BCAC; ; ) {
            f32 y = bar->y;
            bar++;
            if (y < (f32)(posY + 4) && (f32)(posY - 0x10) < y) {
                ret = (s32)y;
            }
            if (bar == end) {
                break;
            }
        }
    }
    return ret;
}

s32 arcadeCheckStage4Collision(s32 posX, s32 posY) {
    s32 ret;

    D_8004C6F0 = 0x36;
    D_8004C6F4 = 0x10A;
    if (posY < 0x6E) {
        D_8004C6F8 = 0;
        ret = 0x57;
    } else if (posY < 0x8C) {
        if (posX < 0x9C) {
            ret = 0x7F;
            D_8004C6F8 = 1;
        } else if (posX >= 0xA5) {
            ret = 0x7F;
            D_8004C6F8 = 2;
        } else {
            ret = 0xF7;
        }
    } else if (posY < 0xBE) {
        D_8004C6F8 = 4;
        if ((posX < 0x64 || posX >= 0x6D) && (posX < 0xCC || posX >= 0xD5)) {
            ret = 0xA7;
        } else {
            ret = 0xF7;
        }
    } else if (posY < 0xDC) {
        D_8004C6F8 = 3;
        ret = 0xCF;
    } else {
        D_8004C6F8 = 5;
        ret = 0xF7;
    }
    if (ret < posY) {
        D_8004C6F8++;
    }
    return ret;
}

s32 arcadeCheckPlayerCollision(s32 posX, s32 posY) {
    if (D_8004C722 == 1) {
        return arcadeCheckStage1Collision(posX, posY);
    } else if (D_8004C722 == 2) {
        return arcadeCheckStage2Collision(posX, posY);
    } else if (D_8004C722 == 3) {
        return arcadeCheckStage3Collision(posX, posY);
    } else {
        return arcadeCheckStage4Collision(posX, posY);
    }
}

s32 arcadeCheckLadderBounds(s32 posX, s32 posY, s32 ladderX, s32 topY, s32 height, s32 bottomY) {
    if ((posY >= topY) & (bottomY >= posY) & ((ladderX - 4) < posX) & (posX < (ladderX + 3))) {
        D_8004C6E0 = ladderX;
        D_8004C6E4 = topY;
        D_8004C6E8 = bottomY;
        D_8004C6EC = height;
        return 1;
    }
    return 0;
}

s32 arcadeCheckStage1Ladders(s32 posX, s32 posY) {
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0xD4, 0xEB, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0xDA, 0xDA, 0xF2)) {
        return 2;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x94, 0xB5, 0xB5, 0xD5)) {
        return 3;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x54, 0xB9, 0xB9, 0xD1)) {
        return 4;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0x91, 0xAB, 0xB7)) {
        return 5;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xAC, 0x94, 0x94, 0xB4)) {
        return 6;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x98, 0x98, 0xB0)) {
        return 7;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xDC, 0x6F, 0x8B, 0x97)) {
        return 8;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x7C, 0x75, 0x75, 0x91)) {
        return 9;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x54, 0x77, 0x77, 0x8F)) {
        return 10;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x8C, 0x53, 0x64, 0x74)) {
        return 11;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x56, 0x56, 0x6E)) {
        return 12;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xB4, 0x37, 0x37, 0x53)) {
        return 13;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStage2Ladders(s32 posX, s32 posY) {
    if (arcadeCheckLadderBounds(posX, posY, 0x3C, 0xD0, 0xD0, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x9C, 0xD0, 0xD0, 0xF7)) {
        return 2;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x104, 0xD0, 0xD0, 0xF7)) {
        return 3;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x44, 0xAA, 0xAA, 0xD0)) {
        return 4;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x7C, 0xAA, 0xAA, 0xD0)) {
        return 5;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xC4, 0xAA, 0xAA, 0xD0)) {
        return 6;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xFC, 0xAA, 0xAA, 0xD0)) {
        return 7;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x4C, 0x84, 0x84, 0xAA)) {
        return 8;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x9C, 0x84, 0x84, 0xAA)) {
        return 9;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xF4, 0x84, 0x84, 0xAA)) {
        return 10;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x54, 0x5D, 0x5D, 0x84)) {
        return 11;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0x5D, 0x5D, 0x84)) {
        return 12;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xCC, 0x5D, 0x5D, 0x84)) {
        return 13;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x5D, 0x5D, 0x84)) {
        return 14;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStage3Ladders(s32 posX, s32 posY) {
    if (arcadeCheckLadderBounds(posX, posY, 0xB4, 0x37, 0x37, 0x57)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xD4, 0x57, 0x57, 0x77)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x104, 0x67, 0x67, 0x8F)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xBC, 0x7F, 0x7F, 0x9F)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x8F, 0x8F, 0xAF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x104, 0xB7, 0xB7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x44, 0x87, 0x87, 0xBF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x3C, 0xBF, 0xBF, 0xE7)) {
        return 1;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStage4Ladders(s32 posX, s32 posY) {
    s32 ladderY;
    if (arcadeCheckLadderBounds(posX, posY, 0x4C, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xBC, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xF4, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xC4, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x4C, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xBC, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xF4, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    ladderY = (s32)D_8004BCD0[0].y;
    if (ladderY == 0x61) {
        ladderY = 0x57;
    } else {
        ladderY = 0x74;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x44, 0x57, ladderY, 0x7F)) {
        return 1;
    }
    ladderY = (s32)D_8004BCD0[1].y;
    if (ladderY == 0x61) {
        ladderY = 0x57;
    } else {
        ladderY = 0x74;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xFC, 0x57, ladderY, 0x7F)) {
        return 1;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStageLadders(s32 posX, s32 posY) {
    if (D_8004C722 == 1) {
        return arcadeCheckStage1Ladders(posX, posY);
    } else if (D_8004C722 == 2) {
        return arcadeCheckStage2Ladders(posX, posY);
    } else if (D_8004C722 == 3) {
        return arcadeCheckStage3Ladders(posX, posY);
    } else {
        return arcadeCheckStage4Ladders(posX, posY);
    }
}

void arcadeRenderEntity(Gfx **glistp, s32 entIndex) {
    Gfx *glist;
    s32 yOffset;
    f32 scale;

    if (D_8004A338[D_8004BCD0[entIndex].type] & 1) {
        scale = 1024.0f;
    } else {
        scale = 1170.2858f;
    }
    dlInitTextureDescriptor(&D_8004AC00[gGfxBufferIndex][entIndex], D_8004BCD0[entIndex].sprite, 0, D_8004BCD0[entIndex].unk1E, D_8004BCD0[entIndex].unk1E, D_8004BCD0[entIndex].unk1F, 0, 2, 0, 0);
    glist = *glistp;
    dlAppendTextureLoad(&glist, &D_8004AC00[gGfxBufferIndex][entIndex]);
    dlSetTextureScaleAndFlip(0x400, (s32)scale, (u8)(D_8004BCD0[entIndex].unk1A & 1), D_8004BCD0[entIndex].unk1B);
    if (D_8004A338[D_8004BCD0[entIndex].type] & 2) {
        dlAppendTextureRectangle(&glist, (s32)(D_8004BCD0[entIndex].x - (f32)(u32)D_8004A358[D_8004BCD0[entIndex].type]) * 4, (s32)((f64)(D_8004BCD0[entIndex].y - (f32)(u32)D_8004A378[D_8004BCD0[entIndex].type]) * 0.875 + 8.0) * 4);
    } else {
        if (D_8004BCD0[entIndex].type == 2) {
            yOffset = (s32)D_8004BCD0[entIndex].animTimer;
            if (yOffset >= 3) {
                yOffset = 5 - yOffset;
            }
        } else {
            yOffset = 0;
        }
        dlAppendTextureRectangle(&glist, (s32)(D_8004BCD0[entIndex].x - (f32)(u32)D_8004A358[D_8004BCD0[entIndex].type]) * 4, (s32)(((f64)(D_8004BCD0[entIndex].y - (f32)yOffset - (f32)(u32)D_8004A378[D_8004BCD0[entIndex].type]) * 0.875 + 8.0) * 4.0));
    }
    *glistp = glist;
}

void arcadeRenderEntities(Gfx **glistp) {
    s32 i;
    Gfx *glist;
    glist = *glistp;
    for (i = 0; i < 80; i++) {
        if (D_8004BCD0[i].type != 0 && D_8004BCD0[i].sprite != 0) {
            if (D_8004BCD0[i].type >= 8 || D_8004C71D < 2) {
                arcadeRenderEntity(&glist, i);
            }
        }
    }
    *glistp = glist;
}

s32 arcadeAbs(s32 val) {
    if (val >= 0) {
        return val;
    }
    return -val;
}

extern u8 D_8003B180[];
extern u8 D_8003B3C8[];
extern u8 D_8003B610[];
extern u8 D_8003B858[];
extern u8 D_8003BAA0[];
extern u8 D_8003BCE8[];
extern u8 D_8003BF30[];
extern u8 D_8003C178[];
extern u8 D_8003C3C0[];
extern u8 D_8003C608[];
extern u8 D_8003C850[];
extern u8 D_8003CA98[];
extern u8 D_8003CCE0[];
extern u8 D_8003CF28[];
extern u8 D_8003D170[];
extern u8 D_8003D3B8[];
extern u8 D_8003D600[];
extern u8 D_8003D848[];

void arcadeUpdatePlayerAnimation(s32 entIndex) {
    s32 val;
    s32 b;
    s32 col;
    s32 row;
    f32 colX;
    f32 y;

    b = D_8004BCD0[entIndex].unk1A & 2;
    D_8004BCD0[entIndex].unk1A = b / 2 | b;
    D_8004BCD0[entIndex].unk1B = 0;
    val = (s32)D_8004BCD0[entIndex].animTimer;
    if (D_8004BCD0[entIndex].state == 2) {
        if (D_8004A764 && D_8004A764) {} // FAKE: empty guard steers regalloc
        if (D_8004C710 != 0) {
            if (D_8004C710 & 8) {
                switch (val & 3) {
                case 0:
                case 2:
                    D_8004BCD0[entIndex].sprite = D_8003C178;
                    break;
                case 1:
                    D_8004BCD0[entIndex].sprite = D_8003C608;
                    break;
                case 3:
                    D_8004BCD0[entIndex].sprite = D_8003CA98;
                    break;
                }
            } else {
                switch (val & 3) {
                case 0:
                case 2:
                    D_8004BCD0[entIndex].sprite = D_8003C3C0;
                    break;
                case 1:
                    D_8004BCD0[entIndex].sprite = D_8003C850;
                    break;
                case 3:
                    D_8004BCD0[entIndex].sprite = D_8003CCE0;
                    break;
                }
            }
        } else {
            switch (val & 3) {
            case 0:
            case 2:
                D_8004BCD0[entIndex].sprite = D_8003B180;
                break;
            case 1:
                D_8004BCD0[entIndex].sprite = D_8003B3C8;
                break;
            case 3:
                D_8004BCD0[entIndex].sprite = D_8003B610;
                break;
            }
        }
    } else if (D_8004BCD0[entIndex].state == 3) {
        D_8004BCD0[entIndex].sprite = D_8003CF28;
    } else if (D_8004BCD0[entIndex].state == 5) {
        y = D_8004BCD0[entIndex].y;
        if ((f32)D_8004C6E8 - y < 1.0f || (y - (f32)D_8004C6E4 < 1.0f)) {
            D_8004BCD0[entIndex].sprite = D_8003BF30;
        } else if (y - (f32)D_8004C6E4 < 6.0f) {
            D_8004BCD0[entIndex].sprite = D_8003B858;
        } else if (y - (f32)D_8004C6E4 < 10.0f) {
            D_8004BCD0[entIndex].sprite = D_8003BCE8;
        } else if (y - (f32)D_8004C6E4 < 14.0f) {
            D_8004BCD0[entIndex].sprite = D_8003BAA0;
        } else {
            D_8004BCD0[entIndex].sprite = D_8003B858;
        }
        D_8004BCD0[entIndex].unk1A = (s32)((f64)D_8004BCD0[entIndex].animTimer / 4.5) & 1;
    } else if (D_8004BCD0[entIndex].state == 8) {
        if (D_8004BCD0[entIndex].animTimer > 38.0f) {
            if (D_8004C71B == 0) {
                if (D_8004BCD0[entIndex].animTimer > 48.0f) {
                    if (D_8004A74C[4] < D_8004A748) {
                        arcadeCheckGameOver();
                        return;
                    }
                    if (D_8004A740 != 0) {
                        arcadeExit();
                        return;
                    }
                    arcadeInitTitleScreen();
                    return;
                }
                if (D_8004A764 == 0) {
                    D_8004A764 = 1;
                    for (col = 0x6C; col != 0xCC; col += 0x10) {
                        colX = col;
                        for (row = 0xA6; row != 0xC6; row += 0x10) {
                            s32 index = arcadeFindFreeEntitySlot39();
                            D_8004BCD0[index] = D_8004A6B8;
                            D_8004BCD0[index].x = colX;
                            D_8004BCD0[index].y = row;
                        }
                    }
                }
            } else {
                D_8004C71B--;
                arcadeFinishStageIntro();
            }
        } else if (D_8004BCD0[entIndex].animTimer > 20.0f) {
            D_8004BCD0[entIndex].sprite = D_8003D848;
        } else if (D_8004BCD0[entIndex].animTimer > 8.0f) {
            D_8004C71D = 2;
            if ((s32)D_8004BCD0[entIndex].animTimer & 1) {
                D_8004BCD0[entIndex].sprite = D_8003D3B8;
            } else {
                D_8004BCD0[entIndex].sprite = D_8003D600;
            }
            if (((s32)D_8004BCD0[entIndex].animTimer & 3) == 2) {
                D_8004BCD0[entIndex].unk1A ^= 1;
            }
            if (((s32)D_8004BCD0[entIndex].animTimer & 3) == 1) {
                D_8004BCD0[entIndex].unk1B = !D_8004BCD0[entIndex].unk1B;
            }
        }
    } else {
        D_8004BCD0[entIndex].sprite = D_8003D170;
    }
}

extern s32 D_8004BC80;
extern s32 D_8004BC84;
extern s32 D_8004C6FC;
extern s32 D_8004C700;
extern s32 D_8004C704;
extern struct GfSndState *D_80770DFC;
extern ArcadeEntity D_8004A5F8;
extern u8 D_800383B8[];
extern u8 D_800385C0[];
extern u8 D_8003B180[];
#define E D_8004BCD0[entIndex]
#define P D_8004BCD0[D_8004C71F]
void arcadeUpdatePlayerEntity(s32 entIndex) {
    union {
        f32 f;
        s32 bits;
    } soundPitch;
    s32 coll;
    s32 i;
    s32 n;
    s32 phase;

    if (E.state == 8 || D_8004C71D == 0) {
        if (D_8004BC84 == 0) {} // FAKE: empty guard steers regalloc
        if (E.state == 2) {
            arcadeCheckPlayerCollision((s32)E.x, (s32)E.y);
            if (E.vx < 0.0f) {
                E.unk1A = E.unk1A & 1;
            } else if (E.vx > 0.0f) {
                E.unk1A = E.unk1A | 2;
            }
            if (((D_807ECDE8->button & 0x200) || D_807ECDE8->stick_x < -0x14) && (f32)D_8004C6F0 < E.x) {
                D_8004BC80 += 3;
                E.vx = -0.7f;
                E.animTimer = (f32)((f64)E.animTimer + 0.3);
            } else if (((D_807ECDE8->button & 0x100) || D_807ECDE8->stick_x >= 0x15) && E.x < (f32)D_8004C6F4) {
                D_8004BC80 += 3;
                E.vx = 0.7f;
                E.animTimer = (f32)((f64)E.animTimer + 0.3);
            } else {
                E.vx = 0.0f;
            }
            if ((D_807ECD48 & 0xE000) && D_8004C710 == 0) {
                n_alSndpPlay(D_8076D1F8, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.animTimer = 0.0f;
                E.vy = -1.2f;
                E.vx = (f32)((f64)E.vx * 0.65);
                E.unk1D = (u32)E.y;
                E.state = 3;
            }
        }
        if (E.y < (f32)(arcadeCheckPlayerCollision((s32)(E.x + E.vx), (s32)E.y) + 3)) {
            E.x = E.vx + E.x;
        } else {
            E.vx = 0.0f;
        }
        if (E.state != 8 && D_8004C722 == 3 &&
            ((76.0f < E.x && E.x < 100.0f) || (140.0f < E.x && E.x < 164.0f)) &&
            ((E.y < 116.0f && 90.0f < E.y) || 239.0f < E.y)) {
            arcadeKillPlayer();
            return;
        }
        D_8004C700 = arcadeCheckStageLadders((s32)E.x, (s32)E.y);
        coll = arcadeCheckPlayerCollision((s32)E.x, (s32)E.y);
        D_8004C6FC = D_8004C6F8;
        switch (E.state) {
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_8004C6F8 == i) {
                    P.x += (f32)D_8004A308[i];
                }
            }
            if (E.x <= (f32)(D_8004C6F0 - 1)) {
                E.x = (f32)D_8004C6F0;
            }
            if ((f32)(D_8004C6F4 + 1) <= E.x) {
                E.x = (f32)D_8004C6F4;
            }
            if ((f32)D_8004C6EC < E.y &&
                (((D_807ECDE8->stick_y >= 0x15) | (*(u16 *)D_807ECDE8 & 0x800)) != 0) && // FAKE: u16 cast read of the pad steers codegen (->button mismatches in this | chain)
                D_807ECDE8->stick_x < 0x29 && D_807ECDE8->stick_x >= -0x28 &&
                !(D_807ECDE8->button & 0x300) && D_8004C710 == 0) {
                E.state = 5;
                E.vx = 0.0f;
                E.y = E.y - 1.0f;
                E.x = (f32)D_8004C6E0;
                break;
            } else if (E.y < (f32)D_8004C6E8 && (f32)D_8004C6EC <= E.y &&
                       !(D_807ECDE8->button & 0x300) &&
                       D_807ECDE8->stick_x < 0x29 && D_807ECDE8->stick_x >= -0x28 &&
                       (((D_807ECDE8->stick_y < -0x14) | (*(u16 *)D_807ECDE8 & 0x400)) != 0) && // FAKE: u16 cast read of the pad steers codegen (->button mismatches in this | chain)
                       D_8004C710 == 0) {
                E.state = 5;
                E.vx = 0.0f;
                E.y = E.y + 1.0f;
                E.x = (f32)D_8004C6E0;
                break;
            } else {
                if ((f32)coll - E.y < 2.0f) {
                    E.y = (f32)coll;
                } else {
                    E.state = 3;
                    E.vx = 0.0f;
                    E.vy = 0.0f;
                    E.unk1D = (u32)E.y;
                }
            }
            break;
        case 5:
            if ((f32)coll == E.y &&
                ((((D_807ECDE8->stick_x >= 0x15) | (D_807ECDE8->stick_x < -0x14)) | (*(u16 *)D_807ECDE8 & 0x300)) || // FAKE: u16 cast read of the pad steers codegen (->button mismatches in this | chain)
                 (D_8004C6F8 == 2 && D_8004A308[2] != 0) ||
                 (D_8004C6F8 == 1 && D_8004A308[1] != 0) ||
                 (D_8004C6F8 == 3 && D_8004A308[3] != 0))) {
                E.state = 2;
            } else if ((f32)coll == E.y && (D_807ECD48 & 0xE000)) {
                n_alSndpPlay(D_8076D1F8, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.animTimer = 0.0f;
                E.vy = -1.2f;
                E.vx = (f32)((f64)E.vx * 0.65);
                E.state = 3;
                E.unk1D = (u32)E.y;
            } else {
                if (E.y < (f32)D_8004C6EC) {
                    E.y = (f32)((f64)E.y + 0.2);
                    if ((f32)D_8004C6EC - E.y > 10.0f) {
                        E.y = (f32)(D_8004C6EC - 10);
                    }
                    if ((f32)D_8004C6EC < E.y) {
                        E.y = (f32)D_8004C6EC;
                    }
                } else {
                    if ((f32)D_8004C6EC < E.y &&
                        (((D_807ECDE8->stick_y >= 0x15) | (*(u16 *)D_807ECDE8 & 0x800)) != 0)) { // FAKE: u16 cast read of the pad steers codegen (->button mismatches in this | chain)
                        E.vy = -0.5f;
                        D_8004BC80 += 2;
                    } else if (E.y < (f32)D_8004C6E8 &&
                               (((D_807ECDE8->stick_y < -0x14) | (*(u16 *)D_807ECDE8 & 0x400)) != 0)) { // FAKE: u16 cast read of the pad steers codegen (->button mismatches in this | chain)
                        E.vy = 0.5f;
                        D_8004BC80 += 2;
                    } else {
                        E.vy = 0.0f;
                    }
                    E.y = E.vy + E.y;
                    E.animTimer = E.vy + E.animTimer;
                }
            }
            break;
        case 3:
            if ((f32)D_8004C6F4 < E.x) {
                E.x = (f32)D_8004C6F4;
                if ((f64)E.vy < 1.8) {
                    E.unk1A = E.unk1A & 1;
                    E.vx = -E.vx;
                    E.vy = -E.vy;
                }
            } else if (E.x < (f32)D_8004C6F0) {
                E.x = (f32)D_8004C6F0;
                if ((f64)E.vy < 1.8) {
                    E.unk1A = E.unk1A | 2;
                    E.vx = -E.vx;
                    E.vy = -E.vy;
                }
            }
            E.y = E.vy + E.y;
            E.vy = (f32)((f64)E.vy + 0.06);
            if (0.0f <= E.vy && (f64)E.vy < 0.06) {
                n = 0;
                for (i = 0; i < 0x50; i++) {
                    if (D_8004BCD0[i].type == 1 || D_8004BCD0[i].type == 2) {
                        if (arcadeAbs((s32)(D_8004BCD0[i].x - E.x)) < 0xD) {
                            if (D_8004BCD0[i].y - E.y < 24.0f && E.y < D_8004BCD0[i].y) {
                                n++;
                            }
                        }
                    }
                }
                if (n != 0) {
                    i = arcadeFindFreeEntitySlot39();
                    D_8004BCD0[i] = D_8004A5F8;
                    D_8004BCD0[i].x = E.x;
                    D_8004BCD0[i].y = E.y + 9.0f;
                    if (n == 1) {
                        arcadeAddScore(0x64);
                    } else if (n == 2) {
                        D_8004BCD0[i].sprite = D_800383B8;
                        arcadeAddScore(0x12C);
                    } else {
                        D_8004BCD0[i].sprite = D_800385C0;
                        arcadeAddScore(0x1F4);
                    }
                }
            }
            if (E.y - (f32)(u32)E.unk1D > 15.0f) {
                n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.unk1D = 0xFF;
            }
            if ((f64)E.vy > 2.5) {
                E.vy = 2.5f;
            }
            if ((f32)coll < E.y && E.y - (f32)coll < 3.0f) {
                E.y = (f32)coll;
                if (E.unk1D == 0xFF) {
                    arcadeKillPlayer();
                } else {
                    E.state = 4;
                    E.vy = 0.0f;
                    E.vx = 0.0f;
                    E.animTimer = 4.0f;
                }
            }
            break;
        case 4:
            E.y = (f32)coll;
            E.animTimer = E.animTimer - 1.0f;
            if (E.animTimer == 0.0f) {
                E.state = 2;
            }
            break;
        case 8:
            E.animTimer = (f32)((f64)E.animTimer + 0.125);
            if (E.animTimer == 8.0f) {
                n_alSndpPlay(D_8076D1F8, 0x54, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
            break;
        }
        if (D_8004BC80 >= 0x24) {
            D_8004BC80 = 0;
            phase = D_8004BC84 + 1;
            if (phase == 7) {
                phase = 0;
            }
            D_8004BC84 = phase;
            if (phase & 1) {
                soundPitch.f = 1.0f;
            } else {
                soundPitch.f = 0.7071120143f;
            }
            n_alSndpPlay(D_8076D1F8, 0x40, 0x7FFF, 0x3F, 1.0f, 0, &D_80770DFC);
            n_alSndpPostEvent(D_80770DFC, 0x10, soundPitch.bits);
        }
        coll = arcadeCheckPlayerCollision((s32)E.x, (s32)E.y);
        if (D_8004BC80 && D_8004BC80) {} // FAKE: empty guard steers regalloc
        E.unk1C = D_8004C6F8;
        D_8004C704 = (s32)(E.y - (f32)D_8004C6E4);
        if (D_8004C71E < 0 && E.state != 8) {
            arcadeKillPlayer();
        }
        if (D_8004C6F8 == 0 && (f32)coll == E.y) {
            n_alSndpPlay(D_8076D1F8, 0x4C, 0x7FFF, 0x3F, 1.0f, 0, 0);
            arcadeStopSound(0);
            if (D_8004C722 == 1) {
                i = arcadeFindEntityByType(0x16);
            } else if (D_8004C722 == 3) {
                i = arcadeFindEntityByType(0x18);
            } else if (D_8004C722 == 4) {
                i = arcadeFindEntityByType(0x19);
            }
            D_8004BCD0[i].state = 5;
            if (D_8004C722 != 4) {
                D_8004BCD0[i].type = 0x16;
            }
            D_8004BCD0[i].animTimer = 0.0f;
            D_8004C71D = 3;
            E.sprite = D_8003B180;
            E.unk1A = 0;
            return;
        }
        if (E.state != 0) {
            arcadeUpdatePlayerAnimation(entIndex);
        }
    }
}
#undef E
#undef P

void arcadeUpdateEntitySprite(s32 entIndex) {
    ArcadeEntity *ptr = &D_8004BCD0[entIndex];
    s32 val = (s32)ptr->animTimer;

    if (ptr->state == 5 || ptr->state == 7 || ptr->state == 1) {
        if (ptr->unk1D != 0) {
            switch (val & 1) {
            case 0:
                ptr->sprite = D_80035AE0;
                return;
            case 1:
                ptr->sprite = D_80035CE8;
                return;
            }
        } else {
            switch (val & 1) {
            case 0:
                ptr->sprite = D_80035650;
                return;
            case 1:
                ptr->sprite = D_80035898;
                return;
            }
        }
    } else {
        if (ptr->unk1D != 0) {
            switch (val & 3) {
            case 0:
                ptr->sprite = D_80035448;
                return;
            case 1:
                ptr->sprite = D_80035240;
                return;
            case 2:
                ptr->sprite = D_80035038;
                return;
            case 3:
                ptr->sprite = D_80034E30;
                return;
            }
        } else {
            switch (val & 3) {
            case 0:
                ptr->sprite = D_80034C28;
                return;
            case 1:
                ptr->sprite = D_80034A20;
                return;
            case 2:
                ptr->sprite = D_80034818;
                return;
            case 3:
                ptr->sprite = D_80034610;
                return;
            }
        }
    }
}


void arcadeUpdateBarrelEntity(s32 entIndex) {
    s32 floorY;
    ArcadeEntity *e;

    if (D_8004C71D == 0) {
        if (D_8004BCD0[entIndex].state == 0 || D_8004BCD0[entIndex].state == 1) {
            arcadeUpdateEntitySprite(entIndex);
            return;
        }
        D_8004BCD0[entIndex].x += D_8004BCD0[entIndex].vx;
        floorY = arcadeCheckPlayerCollision((s32)D_8004BCD0[entIndex].x, (s32)D_8004BCD0[entIndex].y);
        arcadeCheckStageLadders((s32)D_8004BCD0[entIndex].x, (s32)D_8004BCD0[entIndex].y);
        e = &D_8004BCD0[entIndex];
        switch (D_8004BCD0[entIndex].state) {
        case 2:
            D_8004BCD0[entIndex].animTimer = (f32)((f64)e->animTimer + 0.2);
            e->vx = (f32)(1 - D_8004BCD0[entIndex].unk1A * 2);
            if (e->y < (f32)D_8004C6E8 &&
                (D_8004C6F8 + 1 < D_8004C6FC ||
                 (D_8004C6FC == D_8004C6F8 + 1 && (D_8004C704 >= 0x12 || D_8004BCD0[D_8004C71F].state != 5)))) {
                if (e->unk1C & 0x80) {
                    break;
                }
                D_8004BCD0[entIndex].unk1C = e->unk1C & 0xF;
                if (e->unk1C > 0) {
                    D_8004BCD0[entIndex].unk1C = D_8004BCD0[entIndex].unk1C - 1;
                    D_8004BCD0[entIndex].state = 5;
                    D_8004BCD0[entIndex].vx = 0.0f;
                    D_8004BCD0[entIndex].y = e->y + 1.0f;
                    D_8004BCD0[entIndex].vy = 1.0f;
                    D_8004BCD0[entIndex].x = (f32)D_8004C6E0;
                    break;
                }
                e->unk1C = D_8004BCD0[entIndex].unk1C | 0x80;
            } else if (!(e->unk1C & 0x47)) {
                e->unk1C = (4096.0f + arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 1512.0f > (f32)arcadeRand()) | 0x40;
            }
            if ((f32)floorY - e->y < 3.0f) {
                D_8004BCD0[entIndex].y = (f32)floorY;
            } else {
                D_8004BCD0[entIndex].state = 3;
                D_8004BCD0[entIndex].vy = 0.0f;
                D_8004BCD0[entIndex].vx = D_8004BCD0[entIndex].vx / 2;
            }
            break;
        case 3:
            e->animTimer = (f32)((f64)D_8004BCD0[entIndex].animTimer + 0.2);
            e->y = D_8004BCD0[entIndex].y + e->vy;
            e->vy = (f32)((f64)e->vy + 0.06);
            if ((f32)floorY < e->y && e->y - (f32)floorY < 3.0f) {
                D_8004BCD0[entIndex].y = (f32)floorY;
                D_8004BCD0[entIndex].vy = -D_8004BCD0[entIndex].vy / 3.0f;
                if ((f64)e->vy > -0.2) {
                    D_8004BCD0[entIndex].state = 2;
                }
            }
            break;
        case 5:
            D_8004BCD0[entIndex].animTimer = (f32)((f64)D_8004BCD0[entIndex].animTimer + 0.3);
            e->y = D_8004BCD0[entIndex].y + e->vy;
            if ((f32)(D_8004C6E8 - 1) < e->y) {
                e->y = (f32)floorY;
                e->unk1A = 1 - e->unk1A;
                e->vx = (f32)(1 - D_8004BCD0[entIndex].unk1A * 2);
                e->state = 2;
            }
            break;
        case 7:
            e->animTimer = (f32)((f64)D_8004BCD0[entIndex].animTimer + 0.3);
            e->y = D_8004BCD0[entIndex].y + e->vy;
            D_8004BCD0[entIndex].vy = (f32)((f64)e->vy + 0.06);
            floorY = arcadeCheckPlayerCollision((s32)e->x, (s32)e->y);
            if ((f32)floorY < D_8004BCD0[entIndex].y && e->y - (f32)floorY < 8.0f && D_8004BCD0[entIndex].unk1C < D_8004C6F8) {
                D_8004BCD0[entIndex].unk1C = D_8004C6F8;
                e->y = (f32)floorY;
                D_8004BCD0[entIndex].vy = 0.0f;
                if (D_8004BCD0[entIndex].unk1D != 2) {
                    e->vx = (f32)((((f64)arcadeRand() - 16384.0) * arcadeMinFloat(3.0f, (f32)(u32)D_8004A76C)) / 40000.0 + (f64)(-e->vx) * 0.2);
                }
                if (D_8004BCD0[entIndex].y > 230.0f) {
                    D_8004BCD0[entIndex].state = 3;
                    e->unk1A = 1;
                    e->vx = -1.0f;
                    D_8004BCD0[entIndex].vy = -0.7f;
                }
            }
            break;
        }
        if (D_8004BCD0[D_8004C71F].unk1C >= D_8004C6F8 || D_8004BCD0[entIndex].unk1D != 0) {
            if (270.0f < e->x) {
                D_8004BCD0[entIndex].unk1A = 1;
                D_8004BCD0[entIndex].vx = (f32)(1 - D_8004BCD0[entIndex].unk1A * 2);
            } else if (D_8004BCD0[entIndex].x < 50.0f) {
                D_8004BCD0[entIndex].unk1A = 0;
                D_8004BCD0[entIndex].vx = (f32)(1 - e->unk1A * 2);
            }
        }
        if (278.0f < D_8004BCD0[entIndex].x || D_8004BCD0[entIndex].x < 2.0f) {
            D_8004BCD0[entIndex].type = 0;
        }
        if ((e->y > 242.0f) & (D_8004BCD0[entIndex].x < 74.0f)) {
            if (e->unk1D != 0) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                floorY = arcadeFindEntityByType(0x13);
                if (floorY < 0) {
                    floorY = arcadeFindFreeEntity(); // FAKE: floorY reused as entity index steers regalloc (separate local mismatches)
                    D_8004BCD0[floorY] = D_8004A3F8;
                }
                D_8004BCD0[floorY].state = 3;
                e->type = 0;
            } else {
                D_8004BCD0[entIndex].type = 0;
            }
        }
        if (D_8004BCD0[entIndex].x - D_8004BCD0[D_8004C71F].x < 8.0f && D_8004BCD0[D_8004C71F].x - D_8004BCD0[entIndex].x < 8.0f) {
            if (e->y - D_8004BCD0[D_8004C71F].y < 3.0f && D_8004BCD0[D_8004C71F].y - D_8004BCD0[entIndex].y < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(entIndex);
    }
}

extern s8 D_8004A768;
extern u8 D_80037B98[];
extern u8 D_80037DA0[];
extern u8 D_80037FA8[];
extern u8 D_8003E438[];
extern u8 D_800383B8[];
extern u8 D_800385C0[];
extern u8 D_800387C8[];
extern u8 D_80039D18[];
extern u8 D_80039F60[];
extern u8 D_8003A1A8[];
extern u8 D_8003A3F0[];
extern u8 D_8003AE58[];
extern u8 D_800389D0[];
extern u8 D_8003DB18[];
extern u8 D_8003DD60[];
extern u8 D_80038BD8[];
extern u8 D_8003E680[];
extern u8 D_8003E868[];
extern ArcadeEntity D_8004A5F8;
extern s32 D_8004A318[];

extern u8 D_80035EF0[];
extern u8 D_80036138[];
extern u8 D_80036380[];
extern u8 D_800365C8[];
extern u8 D_80036810[];
extern u8 D_80036A58[];
extern u8 D_80036CA0[];
extern u8 D_80036EE8[];
void arcadeUpdateBouncingBarrel(s32 entIndex) {
    s32 floorY;
    s32 bias;

    if (D_8004C71D == 0) {
        D_8004BCD0[entIndex].animTimer = (f32)((f64)D_8004BCD0[entIndex].animTimer + 0.15);
        if (D_8004BCD0[entIndex].animTimer >= 5.0f) {
            D_8004BCD0[entIndex].animTimer = D_8004BCD0[entIndex].animTimer - 5.0f;
        }
        if (D_8004C722 == 2) {
            if (D_8004C710 != 0) {
                if ((D_8004C6DC / 4) & 1) {
                    D_8004BCD0[entIndex].sprite = D_80036810;
                } else {
                    D_8004BCD0[entIndex].sprite = D_80036A58;
                }
            } else if ((D_8004C6DC / 4) & 1) {
                D_8004BCD0[entIndex].sprite = D_80036380;
            } else {
                D_8004BCD0[entIndex].sprite = D_800365C8;
            }
        } else if (D_8004C710 != 0) {
            if ((D_8004C6DC / 4) & 1) {
                D_8004BCD0[entIndex].sprite = D_80036CA0;
            } else {
                D_8004BCD0[entIndex].sprite = D_80036EE8;
            }
        } else if ((D_8004C6DC / 4) & 1) {
            D_8004BCD0[entIndex].sprite = D_80035EF0;
        } else {
            D_8004BCD0[entIndex].sprite = D_80036138;
        }
        floorY = arcadeCheckPlayerCollision((s32)D_8004BCD0[entIndex].x, (s32)D_8004BCD0[entIndex].y);
        arcadeCheckStageLadders((s32)D_8004BCD0[entIndex].x, (s32)D_8004BCD0[entIndex].y);
        switch (D_8004BCD0[entIndex].state) {
        case 2:
            if ((f32)arcadeRand() < arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 60.0f + 256.0f) {
                bias = D_8004BCD0[entIndex].x < D_8004BCD0[D_8004C71F].x;
                bias += ((D_8004BCD0[D_8004C71F].unk1A & 2) * 3) / 2;
                D_8004BCD0[entIndex].unk1A = (arcadeRand() + bias * 0xFB8) - 0x1F70 >= 0x4001;
            }
            if ((f32)arcadeCheckPlayerCollision((s32)(D_8004BCD0[entIndex].x + D_8004BCD0[entIndex].vx * 8.0f), (s32)D_8004BCD0[entIndex].y) - D_8004BCD0[entIndex].y > 5.0f) {
                if (D_8004BCD0[entIndex].unk1A == 0) {}  // FAKE: dead test makes the unk1A load a candidate (a0)
                D_8004BCD0[entIndex].unk1A = D_8004BCD0[entIndex].unk1A == 0;
            } else {
                D_8004BCD0[entIndex].x += D_8004BCD0[entIndex].vx;
            }
            D_8004BCD0[entIndex].vx = (f32)(((f64)(u32)D_8004BCD0[entIndex].unk1A - 0.5) * (((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 15.0) + 1.0));
            bias = (s32)((D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y) * arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 3.0f);
            if (D_8004BCD0[entIndex].y < (f32)D_8004C6E8 && arcadeRand() < 0x400 - bias) {
                D_8004BCD0[entIndex].state = 5;
                D_8004BCD0[entIndex].vx = 0.0f;
                D_8004BCD0[entIndex].y = D_8004BCD0[entIndex].y + 1.0f;
                D_8004BCD0[entIndex].vy = (f32)(2.0 * (((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 30.0) + 0.2));
                D_8004BCD0[entIndex].x = (f32)D_8004C6E0;
            } else if ((f32)D_8004C6E4 < D_8004BCD0[entIndex].y && arcadeRand() < bias + 0x400) {
                D_8004BCD0[entIndex].state = 6;
                D_8004BCD0[entIndex].vx = 0.0f;
                D_8004BCD0[entIndex].y = D_8004BCD0[entIndex].y - 1.0f;
                D_8004BCD0[entIndex].vy = (f32)-(((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 30.0) + 0.2);
                D_8004BCD0[entIndex].x = (f32)D_8004C6E0;
            } else if ((f32)floorY - D_8004BCD0[entIndex].y < 3.0f) {
                D_8004BCD0[entIndex].y = (f32)floorY;
            } else {
                if (D_8004BCD0[entIndex].unk1A == 0) {}  // FAKE: dead test makes the unk1A load a candidate
                D_8004BCD0[entIndex].unk1A = D_8004BCD0[entIndex].unk1A == 0;
            }
            break;
        case 3:
            D_8004BCD0[entIndex].x = D_8004BCD0[entIndex].vx + D_8004BCD0[entIndex].x;
            D_8004BCD0[entIndex].y = D_8004BCD0[entIndex].vy + D_8004BCD0[entIndex].y;
            D_8004BCD0[entIndex].vy = (f32)((f64)D_8004BCD0[entIndex].vy + 0.06);
            if ((f32)floorY < D_8004BCD0[entIndex].y && D_8004BCD0[entIndex].y - (f32)floorY < 3.0f) {
                D_8004BCD0[entIndex].y = (f32)floorY;
                D_8004BCD0[entIndex].vy = -D_8004BCD0[entIndex].vy / 3.0f;
                if ((f64)D_8004BCD0[entIndex].vy > -0.2) {
                    D_8004BCD0[entIndex].state = 2;
                }
            }
            break;
        case 5:
            D_8004BCD0[entIndex].y = D_8004BCD0[entIndex].vy + D_8004BCD0[entIndex].y;
            if ((f32)(D_8004C6E8 - 1) < D_8004BCD0[entIndex].y) {
                D_8004BCD0[entIndex].y = (f32)floorY;
                D_8004BCD0[entIndex].unk1A = 1 - D_8004BCD0[entIndex].unk1A;
                D_8004BCD0[entIndex].vx = (f32)(1 - D_8004BCD0[entIndex].unk1A * 2);
                D_8004BCD0[entIndex].state = 2;
            }
            break;
        case 6:
            D_8004BCD0[entIndex].y = D_8004BCD0[entIndex].vy + D_8004BCD0[entIndex].y;
            if (D_8004BCD0[entIndex].y < (f32)(D_8004C6E4 + 1)) {
                D_8004BCD0[entIndex].y = (f32)floorY;
                D_8004BCD0[entIndex].unk1A = 1 - D_8004BCD0[entIndex].unk1A;
                D_8004BCD0[entIndex].vx = (f32)(1 - D_8004BCD0[entIndex].unk1A * 2);
                D_8004BCD0[entIndex].state = 2;
            }
            break;
        }
        if (270.0f < D_8004BCD0[entIndex].x) {
            D_8004BCD0[entIndex].unk1A = 0;
            D_8004BCD0[entIndex].vx = (f32)((f64)(u32)D_8004BCD0[entIndex].unk1A - 0.5);
        } else if (D_8004BCD0[entIndex].x < 50.0f) {
            D_8004BCD0[entIndex].unk1A = 1;
            D_8004BCD0[entIndex].vx = (f32)((f64)(u32)D_8004BCD0[entIndex].unk1A - 0.5);
        }
        if (D_8004BCD0[entIndex].x - D_8004BCD0[D_8004C71F].x < 8.0f && D_8004BCD0[D_8004C71F].x - D_8004BCD0[entIndex].x < 8.0f) {
            if (D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y < 3.0f && D_8004BCD0[D_8004C71F].y - D_8004BCD0[entIndex].y < 8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

extern u8 D_80037788[];
extern u8 D_80037990[];

void arcadeUpdateSpringEntity(s32 entIndex) {
    s32 sw;

    if (D_8004C71D == 0) {
        D_8004BCD0[entIndex].x += D_8004BCD0[entIndex].vx;
        D_8004BCD0[entIndex].animTimer += 0.1;
        sw = (s32)D_8004BCD0[entIndex].animTimer;
        switch (sw & 1) {
        case 0:
            D_8004BCD0[entIndex].sprite = D_80037788;
            break;
        case 1:
            D_8004BCD0[entIndex].sprite = D_80037990;
            break;
        }
        D_8004BCD0[entIndex].y += D_8004BCD0[entIndex].vy;
        if (D_8004BCD0[entIndex].vy < 5.0f) {
            D_8004BCD0[entIndex].vy += 0.3;
        }
        if (D_8004BCD0[entIndex].y > 81.0f) {
            if (D_8004BCD0[entIndex].x < 220.0f) {
                D_8004BCD0[entIndex].y = 81.0f;
                D_8004BCD0[entIndex].vy = -3.5f;
                if (D_8004BCD0[entIndex].x > 40.0f) {
                    n_alSndpPlay(D_8076D1F8, 0x43, 0x7FFF, 0x3F, 1.0f, 0, 0);
                }
            } else if (D_8004BCD0[entIndex].vx != 0.0f) {
                D_8004BCD0[entIndex].vx = 0.0f;
                n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
        }
        if (D_8004BCD0[entIndex].y > 271.0f) {
            D_8004BCD0[entIndex].type = 0;
        }
        if (arcadeAbs(D_8004BCD0[entIndex].x - D_8004BCD0[D_8004C71F].x) < 7) {
            if (D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y < 4.0f && D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

extern u8 D_80032228[];
extern u8 D_80032470[];
extern u8 D_800326B8[];
extern u8 D_80032900[];

void arcadeUpdateOilDrumEntity(s32 entIndex) {
    s32 n;

    if (D_8004C71D == 0) {
        if (--D_8004BCD0[entIndex].unk1C >= 0x15) {
            D_8004BCD0[entIndex].unk1C = arcadeRand() & 0xF;
            D_8004BCD0[entIndex].unk1D = !D_8004BCD0[entIndex].unk1D;
        }
        switch (D_8004BCD0[entIndex].state) {
        case 2:
            switch (D_8004BCD0[entIndex].unk1D) {
            case 0:
                D_8004BCD0[entIndex].sprite = D_80032228;
                break;
            case 1:
                D_8004BCD0[entIndex].sprite = D_80032470;
                break;
            }
            n = arcadeMinFloat((u32)D_8004A76C, 5.0f);
            if (D_8004C722 == 4) {
                if ((f32)(0x64 - n * 0x14) == D_8004BCD0[entIndex].animTimer++) {
                    if (arcadeCountEntitiesByType(2) < n) {
                        D_8004BCD0[entIndex].state = 3;
                        D_8004BCD0[entIndex].animTimer = 0.0f;
                    }
                }
            }
            break;
        case 3:
            if (D_8004BCD0[entIndex].animTimer++ > 40.0f) {
                D_8004BCD0[entIndex].state = 2;
                D_8004BCD0[entIndex].animTimer = 0.0f;
                n = arcadeFindFreeEntitySlot36();
                D_8004BCD0[n] = D_8004A3D8;
                D_8004BCD0[n].state = 3;
                D_8004BCD0[n].vy = -1.0f;
                if (D_8004C722 == 1) {
                    D_8004BCD0[n].vx = 0.4f;
                } else {
                    if (D_8004BCD0[D_8004C71F].x < 160.0f) {
                        D_8004BCD0[n].vx = -0.5f;
                    } else {
                        D_8004BCD0[n].vx = 0.5f;
                    }
                    D_8004BCD0[n].unk1A = 0;
                    D_8004BCD0[n].x = 160.0f;
                    D_8004BCD0[n].y = 135.0f;
                }
            }
            switch (D_8004BCD0[entIndex].unk1D) {
            case 0:
                D_8004BCD0[entIndex].sprite = D_800326B8;
                return;
            case 1:
                D_8004BCD0[entIndex].sprite = D_80032900;
                break;
            }
            break;
        }
    }
}

void arcadeUpdatePaulineLower(s32 entIndex) {
    ArcadeEntity *entry = &D_8004BCD0[entIndex];

    if (D_8004C722 == 2) {
        entry->unk1A = D_8004BCD0[D_8004C71F].x < 160.0f;
        entry->x = 152.0f;
        if (D_8004C708 == 2) {
            entry->unk1A = 0;
            entry->y = 63.0f;
        }
    }
    if (D_8004C721 == 0) {
        entry->sprite = NULL;
    } else {
        entry->sprite = D_8003E438;
    }
}

void arcadeUpdatePaulineUpper(s32 entIndex) {
    ArcadeEntity *entry = &D_8004BCD0[entIndex];

    if (D_8004C722 == 2) {
        entry->unk1A = D_8004BCD0[D_8004C71F].x < 160.0f;
        entry->x = 152.0f;
        if (D_8004C708 == 2) {
            entry->unk1A = 0;
            entry->y = 79.0f;
        }
    }
    if (D_8004C721 == 0) {
        entry->sprite = NULL;
        return;
    }
    if (entry->sprite == NULL) {
        entry->sprite = D_8003DB18;
    }
    if (D_8004C71D == 0) {
        if ((entry->unk1C++ & 0xC8) || (D_8004C724 == 1)) {
            entry->sprite = D_8003DB18;
        } else {
            entry->sprite = D_8003DD60;
        }
    }
}

void arcadeUpdateHeartEntity(s32 entIndex) {
    D_8004BCD0[entIndex].sprite = D_8003AE58;
    if (D_8004C721 != 0) {
        D_8004BCD0[entIndex].y = D_8004BCD0[arcadeFindEntityByType(0x1A)].y - 8.0f;
        D_8004BCD0[entIndex].x = D_8004BCD0[arcadeFindEntityByType(0x1A)].x;
    } else {
        if (D_8004BCD0[entIndex - 1].sprite == NULL) {
            D_8004BCD0[entIndex].sprite = NULL;
        }
        D_8004BCD0[entIndex].y = D_8004BCD0[entIndex - 1].y + 20.0f;
        D_8004BCD0[entIndex].x = D_8004BCD0[entIndex - 1].x + 30.0f;
    }
    D_8004BCD0[arcadeFindEntityByType(0x1A)].sprite = NULL;
    D_8004BCD0[arcadeFindEntityByType(0x1B)].sprite = NULL;
    if (arcadeFindEntityByType(0x1D) >= 0 && D_8004BCD0[arcadeFindEntityByType(0x1D)].sprite != D_800389D0) {
        D_8004BCD0[arcadeFindEntityByType(0x1D)].sprite = NULL;
    }
}

void arcadeUpdateHelpSpeechBubble(s32 entIndex) {
    if (D_8004C722 == 2) {
        D_8004BCD0[entIndex].x = (D_8004BCD0[D_8004C71F].x >= 160.0f) * 0x28 + 0x80;
        if (D_8004C708 == 2) {
            D_8004BCD0[entIndex].unk1A = 0;
            D_8004BCD0[entIndex].y = 63.0f;
        }
    }
    if (D_8004C71D == 3) {
        if (D_8004C721 == 0) {
            D_8004BCD0[entIndex].sprite = D_80038BD8;
        } else {
            D_8004BCD0[entIndex].sprite = D_800389D0;
        }
        D_8004BCD0[entIndex].unk1E = 0x10;
        D_8004BCD0[entIndex].unk1F = 0x10;
        return;
    }
    if (D_8004C721 == 0) {
        D_8004BCD0[entIndex].sprite = NULL;
        return;
    }
    if (D_8004C71D == 0) {
        if (!(D_8004BCD0[entIndex].unk1C++ & 0xC0)) {
            if (D_8004C722 == 2 || D_8004C722 == 4) {
                D_8004BCD0[entIndex].sprite = D_8003E868;
                return;
            }
            D_8004BCD0[entIndex].sprite = D_8003E680;
            return;
        }
        D_8004BCD0[entIndex].sprite = NULL;
    }
}

void arcadeUpdateConveyorPulleys(s32 entIndex) {
    s32 val;
    ArcadeEntity *entity;

    if (D_8004C71D == 0) {
        entity = &D_8004BCD0[entIndex];
        entity->unk1D += D_8004A308[entity->unk1C];
        val = entity->unk1D;
        if (val < 0) {
            entity->unk1D = val + 0x2EE00;
            val = entity->unk1D;
        }
        switch ((val / 8) % 3) {
        case 0:
            entity->sprite = D_80037B98;
            return;
        case 1:
            entity->sprite = D_80037DA0;
            return;
        case 2:
            entity->sprite = D_80037FA8;
            break;
        }
    }
}
extern u8 D_80041508[];
extern u8 D_80040540[];
extern u8 D_80044460[];
extern u8 D_80045428[];

void arcadeUpdateDonkeyKongIntro(s32 entIndex) {
    if (D_8004C6DC == 0x3C) {
        n_alSndpPlay(D_8076D1F8, 0x46, 0x7FFF, 0x3F, 1.0f, 0, 0);
    }
    if (D_8004C6DC >= 0x3C) {
        if (D_8004C6DC >= 0x169) {
            D_8004BCD0[entIndex].vy += 0.05;
            D_8004BCD0[entIndex].y += D_8004BCD0[entIndex].vy;
            D_8004BCD0[entIndex].x += D_8004BCD0[entIndex].vx;
            if (D_8004BCD0[entIndex].vy > 0.0f && D_8004BCD0[entIndex].y >= 38.0f) {
                D_8004C721 = 1;
                D_8004BCD0[entIndex].y = 38.0f;
                if (D_8004C6DC == 0x26C) {
                    n_alSndpPlay(D_8076D1F8, 0x53, 0x7FFF, 0x3F, 1.0f, 0, 0);
                    D_8004BCD0[entIndex].sprite = D_80041508;
                }
                if (D_8004C6DC == 0x2D0 || D_8004C6DC < 0x26C) {
                    D_8004BCD0[entIndex].sprite = D_80040540;
                }
                if (D_8004BCD0[entIndex].vy > 0.06) {
                    D_8004C708 += 1;
                    n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                }
                if (D_8004BCD0[entIndex].x > 74.0f && D_8004C6DC >= 0x1A5) {
                    D_8004BCD0[entIndex].vx = -0.5f;
                    D_8004BCD0[entIndex].vy = -0.81f;
                    return;
                }
                D_8004BCD0[entIndex].vx = 0.0f;
                D_8004BCD0[entIndex].vy = 0.0f;
            }
        } else {
            if (D_8004BCD0[entIndex].y > 74.0f) {
                D_8004BCD0[entIndex].vy = -2.0f;
                D_8004BCD0[entIndex].vx = 0.0f;
                D_8004BCD0[entIndex].y = 0xC5 - ((D_8004C6DC - 0x3C) / 2);
                if (D_8004C6DC & 8) {
                    D_8004BCD0[entIndex].sprite = D_80044460;
                    return;
                }
                D_8004BCD0[entIndex].sprite = D_80045428;
            }
        }
    }
}

extern u8 D_8003E9F0[];
extern u8 D_80043498[];
extern u8 D_800463F0[];
extern ArcadeEntity D_8004A3B8;
void arcadeUpdateDonkeyKongStage1(s32 entIndex) {
    s32 idx;
    s32 n;

    if (D_8004C71D == 0 || D_8004BCD0[entIndex].state == 5) {
        switch (D_8004BCD0[entIndex].state) {
        case 12:
            D_8004BCD0[entIndex].unk1C -= 1;
            if (D_8004BCD0[entIndex].unk1C == 0) {
                D_8004BCD0[entIndex].unk1C = 0x14;
                D_8004BCD0[entIndex].state = 9;
                D_8004BCD0[entIndex].sprite = D_8003E9F0;
                D_8004BCD0[entIndex].unk1A = 0;
                idx = arcadeFindFreeEntity();
                D_8004BCD0[entIndex].unk1D = idx;
                n = (s32)D_8004BCD0[entIndex].animTimer++;
                D_8004BCD0[idx] = D_8004A3B8;
                if (!(n & 7)) {
                    D_8004BCD0[idx].unk1D = 1;
                }
                if (n == 2 && D_8004C723 != 0) {
                    D_8004BCD0[idx].unk1C = 2;
                    return;
                }
                if (n == 1) {
                    if (D_8004C723 == 0) {
                        D_8004BCD0[idx].unk1C = 2;
                        return;
                    }
                    D_8004BCD0[idx].unk1C = 5;
                    return;
                }
                if (n != 0) {
                    if (!((f32)arcadeRand() < arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 2000.0f + 2048.0f)) {
                        return;
                    }
                }
                D_8004BCD0[idx].animTimer = 1.0f;
                if (n == 0) {
                    D_8004BCD0[idx].unk1D = 2;
                    if (D_8004A76C == 1) {
                        D_8004BCD0[idx].vx = 0.0f;
                        return;
                    }
                    if (D_8004A76C == 2) {
                        D_8004BCD0[idx].vx = 0.65f;
                        return;
                    }
                    D_8004BCD0[idx].vx = 0.77f;
                    return;
                }
                D_8004BCD0[idx].vx = (((f64)D_8004BCD0[D_8004C71F].x - 92.0) / 200.0 + ((f64)arcadeRand() - 16384.0) / 30000.0) * arcadeMinFloat(3.0f, (f32)D_8004A76C);
                if ((f32)arcadeRand() < arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 2000.0f + 4096.0f) {
                    D_8004BCD0[idx].unk1C = 6;
                    if (D_80040540 == 0) {} // FAKE: empty guard steers regalloc
                    return;
                }
            } else if (D_8004BCD0[entIndex].unk1C == 0x14) {
                D_8004C71E -= 1;
                return;
            }
            break;
        case 9:
            D_8004BCD0[entIndex].unk1C -= 1;
            if (D_8004BCD0[entIndex].unk1C == 0) {
                idx = D_8004BCD0[entIndex].unk1D;
                D_8004BCD0[idx].x = 92.0f;
                if (D_8004BCD0[idx].animTimer != 0.0f) {
                    D_8004BCD0[entIndex].unk1C = 0x1E;
                    D_8004BCD0[entIndex].state = 0xB;
                    D_8004BCD0[entIndex].sprite = D_80040540;
                    D_8004BCD0[entIndex].unk1A = 0;
                    D_8004BCD0[idx].state = 7;
                    D_8004BCD0[idx].unk1C = 2;
                    return;
                }
                D_8004BCD0[entIndex].unk1C = 0x3C;
                D_8004BCD0[entIndex].state = 0xA;
                D_8004BCD0[entIndex].sprite = D_80043498;
                D_8004BCD0[entIndex].unk1A = 0;
                D_8004BCD0[idx].state = 1;
                if (D_80040540 == 0) {} // FAKE: empty guard steers regalloc
                return;
            }
            break;
        case 11:
            D_8004BCD0[entIndex].unk1C -= 1;
            if (D_8004BCD0[entIndex].unk1C == 0) {
                D_8004BCD0[entIndex].unk1C = (u8)(u32)((51.0f - arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 5.0f) + (f32)(arcadeRand() & 0xF));
                D_8004BCD0[entIndex].state = 0xC;
                D_8004BCD0[entIndex].sprite = D_800424D0;
                D_8004BCD0[entIndex].unk1A = 0;
                if (D_80040540 == 0) {} // FAKE: empty guard steers regalloc
                return;
            }
            break;
        case 10:
            idx = D_8004BCD0[entIndex].unk1D;
            D_8004BCD0[entIndex].unk1C -= 1;
            if ((f32)(u32)D_8004BCD0[entIndex].unk1C == arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 3.0f) {
                D_8004BCD0[entIndex].unk1C = (u8)(u32)((51.0f - arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 5.0f) + (f32)(arcadeRand() & 0xF));
                D_8004BCD0[entIndex].state = 0xC;
                D_8004BCD0[entIndex].sprite = D_80040540;
                D_8004BCD0[entIndex].unk1A = 0;
                return;
            }
            if (D_8004BCD0[entIndex].unk1C == 0x28) {
                D_8004BCD0[entIndex].sprite = D_8003E9F0;
                D_8004BCD0[entIndex].unk1A = 1;
                D_8004BCD0[idx].state = 0;
                D_8004BCD0[idx].x = 122.0f;
                D_8004BCD0[idx].y = 83.0f;
                return;
            }
            if (D_8004BCD0[entIndex].unk1C == 0x14) {
                D_8004BCD0[idx].state = 2;
                return;
            }
            break;
        case 5:
            if (D_8004BCD0[entIndex].animTimer++ > 60.0f) {
                if (D_8004C721 != 0) {
                    D_8004BCD0[entIndex].sprite = D_800463F0;
                    D_8004BCD0[entIndex].unk1A = (s32)(D_8004BCD0[entIndex].animTimer / 8) & 1;
                } else {
                    D_8004BCD0[entIndex].unk1A = 0;
                    if ((s32)(D_8004BCD0[entIndex].animTimer / 8) & 1) {
                        D_8004BCD0[entIndex].sprite = D_80045428;
                    } else {
                        D_8004BCD0[entIndex].sprite = D_80044460;
                    }
                }
                if (D_8004C722 != 4) {
                    D_8004BCD0[entIndex].x = 100.0f;
                }
                D_8004BCD0[entIndex].y = D_8004BCD0[entIndex].y - 0.4;
                if (D_8004BCD0[entIndex].y < 23.0f) {
                    D_8004C721 = 0;
                }
                if (D_8004BCD0[entIndex].animTimer > 280.0f) {
                    D_8004C723 += 1;
                    arcadeFinishStageIntro();
                    return;
                }
                if (D_8004BCD0[entIndex].animTimer == 200.0f && D_8004C71E > 0) {
                    arcadeAddScore(D_8004C71E * 0x64);
                    return;
                }
            } else {
                D_8004BCD0[entIndex].unk1A = 1;
                D_8004BCD0[entIndex].sprite = D_8003E9F0;
            }
            break;
        }
    }
}

extern u8 D_800473B8[];
extern u8 D_80048380[];
extern u8 D_80049348[];
extern ArcadeEntity D_8004A6F8;

void arcadeUpdateDonkeyKongStage4(s32 entIndex) {
    s32 cnt;

    switch (D_8004BCD0[entIndex].state) {
    case 2:
        if (D_8004C71D == 0) {
            if (D_8004C6DC % 120 == 0) {
                D_8004C71E -= 1;
            }
            if (D_8004BCD0[D_8004C71F].y < 95.0f && D_8004BCD0[D_8004C71F].y > 76.0f) {
                if (D_8004BCD0[D_8004C71F].x > 135.0f && D_8004BCD0[D_8004C71F].x < 186.0f) {
                    arcadeKillPlayer();
                }
            }
            cnt = ++D_8004BCD0[entIndex].unk1C;
            if ((u8)cnt < 0xA0) {
                D_8004BCD0[entIndex].sprite = D_80040540;
                return;
            }
            if (!(cnt & 0x1F)) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                cnt = D_8004BCD0[entIndex].unk1C;
            }
            D_8004BCD0[entIndex].sprite = D_800424D0;
            D_8004BCD0[entIndex].unk1A = ((cnt & 0x20) / 32) == (((cnt & 0x20) / 32) * 0); // FAKE: `x == x * 0` steers scheduling (x == 0)
        }
        break;
    case 8:
        if (D_8004BCD0[entIndex].animTimer++ == 720.0f) {
            D_8004C723 += 1;
            if (D_8004A740 != 0) {
                D_8004A770 = 1;
                if (D_8004A74C[4] < D_8004A748) {
                    arcadeCheckGameOver();
                } else {
                    arcadeExit();
                }
            } else {
                arcadeFinishStageIntro();
            }
        } else {
            if (D_8004BCD0[entIndex].animTimer > 480.0f) {
                break;
            }
            if (D_8004BCD0[entIndex].animTimer == 400.0f) {
                if (D_8004C71E > 0) {
                    arcadeAddScore(D_8004C71E * 0x64);
                }
            } else if (D_8004BCD0[entIndex].animTimer > 200.0f) {
                if (D_8004BCD0[entIndex].y < 178.0f) {
                    D_8004BCD0[entIndex].unk1B = 1;
                    D_8004BCD0[entIndex].y += 1.0f;
                    if (D_8004BCD0[entIndex].y >= 178.0f) {
                        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A6F8;
                    }
                } else {
                    if (D_8004C708 != 2) {
                        D_8004C708 = 2;
                        n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                    }
                    D_8004BCD0[entIndex].y = 178.0f;
                    D_8004BCD0[entIndex].unk1A = 0;
                    if (((s32)(D_8004BCD0[entIndex].animTimer / 6.0f) % 3) == 0) {
                        D_8004BCD0[entIndex].sprite = D_800473B8;
                    } else if (((s32)(D_8004BCD0[entIndex].animTimer / 6.0f) % 3) == 1) {
                        D_8004BCD0[entIndex].sprite = D_80048380;
                    } else if (((s32)(D_8004BCD0[entIndex].animTimer / 6.0f) % 3) == (0, 2)) { // FAKE: comma operand steers codegen (== 2 does not match)
                        D_8004BCD0[entIndex].sprite = D_80049348;
                    }
                    if (D_8004BCD0[entIndex].animTimer == 350.0f) {
                        n_alSndpPlay(D_8076D1F8, 0x50, 0x7FFF, 0x3F, 1.0f, 0, 0);
                        D_8004BCD0[D_8004C71F].sprite = D_8003B180;
                        D_8004BCD0[D_8004C71F].unk1A = 0;
                        D_8004BCD0[D_8004C71F].x = 190.0f;
                        D_8004BCD0[D_8004C71F].y = 93.0f;
                        D_8004C71D = 3;
                    }
                }
            } else if (D_8004BCD0[entIndex].animTimer > 180.0f) {
                D_8004BCD0[entIndex].unk1A = 0;
                D_8004BCD0[entIndex].sprite = D_80040540;
            } else if (D_8004BCD0[entIndex].animTimer > 30.0f) {
                D_8004BCD0[entIndex].unk1A = (s32)(D_8004BCD0[entIndex].animTimer / 6.0f) & 1;
                D_8004BCD0[entIndex].sprite = D_800424D0;
            }
        }
        if (D_8004BCD0[entIndex].animTimer == 2.0f) {
            n_alSndpPlay(D_8076D1F8, 0x52, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        if (D_8004BCD0[entIndex].animTimer == 200.0f) {
            n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        break;
    }
}

extern ArcadeEntity D_8004A418;

void arcadeUpdateDonkeyKongStage2(s32 entIndex) {
    s32 cnt;

    if (D_8004C71D == 0) {
        D_8004BCD0[entIndex].animTimer += 1.0f;
        cnt = (s32)D_8004BCD0[entIndex].animTimer;
        if ((u8)cnt < 0xA0) {
            D_8004BCD0[entIndex].sprite = D_80040540;
        } else {
            if (!(cnt & 0x1F)) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                cnt = (s32)D_8004BCD0[entIndex].animTimer;
            }
            D_8004BCD0[entIndex].sprite = D_800424D0;
            D_8004BCD0[entIndex].unk1A = ((cnt & 0x20) / 32) == (((cnt & 0x20) / 32) * 0); // FAKE: `x == x * 0` steers scheduling (x == 0)
        }
        if ((s32)D_8004BCD0[entIndex].animTimer % (0x72 - (s32)arcadeMinFloat((u32)D_8004A76C, 4.0f) * 0xC) == 0) {
            D_8004C71E -= 1;
            entIndex = arcadeFindFreeEntity(); // FAKE: parameter reused as new entity index steers regalloc
            D_8004BCD0[entIndex] = D_8004A418;
            D_8004BCD0[entIndex].x = (arcadeRand() & 0xF) - 0x1C;
            D_8004BCD0[entIndex].state = 2;
        }
    }
}

void arcadeUpdateDonkeyKongStage3(s32 entIndex) {
    s32 tmp;
    s32 flash;

    switch (D_8004BCD0[entIndex].state) {
    case 2:
        tmp = 0; // FAKE: tmp holds 0 then the frame count; the reuse steers regalloc
        if (D_8004C71D != tmp) {
            return;
        }
        if (D_8004C6DC % 120 == 0) {
            D_8004C71E -= 1;
        }
        if (D_8004BCD0[entIndex].x > 204.0f) {
            D_8004BCD0[entIndex].vx = -1.0f;
        }
        if (D_8004BCD0[entIndex].x < 68.0f) {
            D_8004BCD0[entIndex].vx = 1.0f;
        }
        D_8004BCD0[entIndex].animTimer += 1.0f;
        tmp = D_8004BCD0[entIndex].animTimer;
        if ((u8)tmp < 0xA0) {
            D_8004BCD0[entIndex].sprite = D_80040540;
        } else {
            D_8004BCD0[entIndex].sprite = D_800424D0;
            flash = (((s32)D_8004BCD0[entIndex].animTimer & 0x20) / 32) == 0;
            D_8004BCD0[entIndex].unk1A = flash;
        }
        break;
    case 5:
        if (D_8004BCD0[entIndex].x > 100.0f) {
            D_8004BCD0[entIndex].vx = -1.0f;
        } else if (D_8004BCD0[entIndex].x < 100.0f) {
            D_8004BCD0[entIndex].vx = 1.0f;
        } else {
            D_8004BCD0[entIndex].type = 0x16;
            D_8004BCD0[entIndex].vx = 0.0f;
            D_8004BCD0[entIndex].animTimer = 41.0f;
        }
        break;
    }
    if (!(D_8004C6DC & 1)) {
        D_8004A308[0] = (s32)D_8004BCD0[entIndex].vx;
        D_8004BCD0[entIndex].x += D_8004BCD0[entIndex].vx;
    }
}

void arcadeUpdateScorePopup(s32 entIndex) {
    if (0.0f == D_8004BCD0[entIndex].animTimer) {
        n_alSndpPlay(D_8076D1F8, 0x45, 0x7FFF, 0x3F, 1.0f, 0, 0);
    }
    if (D_8004BCD0[entIndex].animTimer++ > 40.0f) {
        D_8004BCD0[entIndex].type = 0;
    }
}

void arcadeUpdateCollectibleItem(s32 entIndex) {
    if (D_8004BCD0[entIndex].x == (f32)(s32)D_8004BCD0[D_8004C71F].x &&
        D_8004BCD0[entIndex].y == (f32)(s32)D_8004BCD0[D_8004C71F].y) {
        D_8004BCD0[entIndex].type = 0x14;
        if (D_8004A76C == 1) {
            D_8004BCD0[entIndex].sprite = D_800383B8;
            arcadeAddScore(0x12C);
        } else if (D_8004A76C == 2) {
            D_8004BCD0[entIndex].sprite = D_800385C0;
            arcadeAddScore(0x1F4);
        } else {
            D_8004BCD0[entIndex].sprite = D_800387C8;
            arcadeAddScore(0x320);
        }
    }
}

extern u8 D_800393F8[];
extern u8 D_80039640[];
extern u8 D_80039888[];
extern u8 D_80039AD0[];

void arcadeUpdateHammerEntity(u8 entIndex) {
    s32 i;
    s32 idx;

    if (D_8004C71D == 0) {
        switch (D_8004BCD0[entIndex].state) {
        case 0:
            if (D_8004BCD0[entIndex].x - D_8004BCD0[D_8004C71F].x < 8.0f && D_8004BCD0[entIndex].x - D_8004BCD0[D_8004C71F].x > -8.0f) {
                if (D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y < 8.0f && D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y > -8.0f) {
                    arcadeStopSound(0x49);
                    D_8004C710 = 0x258;
                    D_8004BCD0[entIndex].state = 2;
                }
            }
            break;
        case 2:
            D_8004BCD0[entIndex].unk1A = D_8004BCD0[D_8004C71F].unk1A;
            if ((D_8004C710 & 8) || D_8004BCD0[D_8004C71F].state != 2) {
                if (D_8004C710 >= 0xF1 || (D_8004C710 & 4)) {
                    D_8004BCD0[entIndex].sprite = D_800393F8;
                } else {
                    D_8004BCD0[entIndex].sprite = D_80039888;
                }
                D_8004BCD0[entIndex].x = D_8004BCD0[D_8004C71F].x;
                D_8004BCD0[entIndex].y = D_8004BCD0[D_8004C71F].y - 16.0f;
            } else {
                if (D_8004C710 >= 0xF1 || (D_8004C710 & 4)) {
                    D_8004BCD0[entIndex].sprite = D_80039640;
                } else {
                    D_8004BCD0[entIndex].sprite = D_80039AD0;
                }
                if (D_8004BCD0[entIndex].unk1A != 0) {
                    D_8004BCD0[entIndex].x = D_8004BCD0[D_8004C71F].x + 15.0f;
                } else {
                    D_8004BCD0[entIndex].x = D_8004BCD0[D_8004C71F].x - 15.0f;
                }
                D_8004BCD0[entIndex].y = D_8004BCD0[D_8004C71F].y;
            }
            i = 0;
            do {
                if (D_8004BCD0[i].type == 1 || D_8004BCD0[i].type == 4 || D_8004BCD0[i].type == 2) {
                    if (arcadeAbs(D_8004BCD0[i].x - D_8004BCD0[entIndex].x) < 0xD) {
                        if (arcadeAbs(D_8004BCD0[i].y - D_8004BCD0[entIndex].y) < 8) {
                            n_alSndpPlay(D_8076D1F8, 0x4B, 0x7FFF, 0x3F, 1.0f, 0, 0);
                            idx = (u8)arcadeFindFreeEntitySlot39();
                            D_8004BCD0[idx] = D_8004A618;
                            D_8004BCD0[idx].type = 7;
                            D_8004BCD0[idx].unk1D = D_8004BCD0[i].type;
                            D_8004BCD0[idx].x = D_8004BCD0[entIndex].x;
                            D_8004BCD0[idx].y = D_8004BCD0[entIndex].y;
                            D_8004BCD0[i].type = 0;
                            D_8004C71D = 1;
                        }
                    }
                }
            } while ((i = (u8)(i + 1)) < 0x50);
            if (D_8004C710-- == 1) {
                D_8004BCD0[entIndex].type = 0;
                arcadeStopSound(0);
                arcadeSetStageMusic();
            }
            break;
        }
    }
}

void arcadeUpdateHammerSmash(u8 entIndex) {
    ArcadeEntity *entity = &D_8004BCD0[entIndex];
    u8 temp;
    u8 rand;

    if (entity->unk1C >= 0x37) {
        entity->sprite = D_8003A3F0;
    } else {
        temp = (entity->unk1C / 6) % 3;
        if (temp == 0) {
            entity->sprite = D_80039D18;
        } else if (temp == 1) {
            entity->sprite = D_80039F60;
        } else {
            entity->sprite = D_8003A1A8;
        }
    }
    if (entity->unk1C++ == 0x42) {
        entity->type = 0x14;
        rand = arcadeRand();
        if (entity->unk1D == 2 && (rand & 3) == 0) {
            entity->sprite = D_800387C8;
            arcadeAddScore(0x320);
        } else if (entity->unk1D == 2 && (rand & 3) == 1) {
            entity->sprite = D_800385C0;
            arcadeAddScore(0x1F4);
        } else {
            entity->sprite = D_800383B8;
            arcadeAddScore(0x12C);
        }
        entity->animTimer = 0.0f;
        D_8004C71D = 0;
    }
}

void arcadeUpdateRivetEntity(u8 entIndex) {
    if (D_8004BCD0[entIndex].x == (f32)(s32)D_8004BCD0[D_8004C71F].x) {
        f32 diff = D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y;
        if (diff < 20.0f && diff > -2.0f) {
            D_8004BCD0[entIndex].unk1D = 1;
            return;
        }
    }
    if (D_8004BCD0[entIndex].unk1D != 0) {
        D_8004BCD0[entIndex].type = 0;
        D_8004C718 = D_8004BCD0[entIndex].unk1C ^ D_8004C718;
        if (D_8004C718) {
            ArcadeEntity *new_entity = &D_8004BCD0[(u8)arcadeFindFreeEntitySlot39()];
            *new_entity = D_8004A5F8;
            new_entity->x = D_8004BCD0[D_8004C71F].x;
            new_entity->y = D_8004BCD0[D_8004C71F].y + 14.0f;
            new_entity->animTimer = 0.0f;
            arcadeAddScore(0x64);
        }
    }
}

void arcadeUpdateRetractableLadder(u8 entIndex) {
    f32 step;

    if (D_8004C71D == 0) {
        D_8004BCD0[entIndex].animTimer -= 1.0f;
        step = D_8004BCD0[entIndex].animTimer;
        if (step < 0.0f) {
            D_8004BCD0[entIndex].animTimer = (arcadeRand() & 0x7F) + 0x1C2;
        }
        step = D_8004BCD0[entIndex].animTimer < 200.0f ? 0.2f : -0.2f;
        D_8004BCD0[entIndex].y += step;
        if (D_8004BCD0[entIndex].y < 97.0f) {
            D_8004BCD0[entIndex].y = 97.0f;
        }
        if (D_8004BCD0[entIndex].y > 110.0f) {
            D_8004BCD0[entIndex].y = 110.0f;
        }
    }
}

void arcadeUpdateCementPanEntity(u8 entIndex) {
    if (D_8004C71D == 0) {
        D_8004BCD0[entIndex].x += D_8004A308[D_8004BCD0[entIndex].unk1C];
        if (D_8004BCD0[entIndex].x > 288.0f || D_8004BCD0[entIndex].x < 32.0f || (D_8004BCD0[entIndex].x == 160.0f && D_8004BCD0[entIndex].y == 127.0f)) {
            D_8004BCD0[entIndex].type = 0;
        }
        if (arcadeAbs(D_8004BCD0[entIndex].x - D_8004BCD0[D_8004C71F].x) < 12) {
            if (D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y < 4.0f && D_8004BCD0[entIndex].y - D_8004BCD0[D_8004C71F].y > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

void arcadeUpdateVictoryPauline(u8 entIndex) {
    if (460.0f < D_8004BCD0[arcadeFindEntityByType(0x17)].animTimer) {
        return;
    }
    D_8004BCD0[entIndex].unk1A = (D_8004BCD0[entIndex].unk1C++ / 8) & 1;
}

extern u8 *D_80746800;

void arcadeUpdateNameEntryCursor(u8 entIndex) {
    if (D_8004BCD0[entIndex].state != 4) {
        if ((D_807ECDE8->button & 0x200) || D_807ECDE8->stick_x < -0x14) {
            switch (--D_8004C720) {
            case 0:
                D_8004C720 = 8;
            case 0xB:
                D_8004BCD0[entIndex].unk1D--;
                if (D_8004BCD0[entIndex].unk1D >= 0x29) {
                    D_8004BCD0[entIndex].unk1D = 0x1D;
                }
                break;
            }
        } else if ((D_807ECDE8->button & 0x100) || D_807ECDE8->stick_x >= 0x15) {
            switch (--D_8004C720) {
            case 0:
                D_8004C720 = 8;
            case 0xB:
                D_8004BCD0[entIndex].unk1D++;
                if (D_8004BCD0[entIndex].unk1D >= 0x1E) {
                    D_8004BCD0[entIndex].unk1D -= 0x1E;
                }
                break;
            }
        } else {
            D_8004C720 = 0xC;
        }
        D_8004BCD0[entIndex].x = (D_8004BCD0[entIndex].unk1D % 10) * 0x10 + 0x54;
        D_8004BCD0[entIndex].y = ((D_8004BCD0[entIndex].unk1D / 10) << 7) / 7 + 0x4A;
        if (D_807ECD48 & 0x8000) {
            if (D_8004BCD0[entIndex].unk1D == 0x1D || D_8004C6DC == 0x708) {
                D_8004C6DC = 0x744;
                D_8004A778[D_8004BCD0[entIndex].unk1C][0] = D_8004A774[0];
                D_8004A778[D_8004BCD0[entIndex].unk1C][1] = D_8004A774[1];
                D_8004A778[D_8004BCD0[entIndex].unk1C][2] = D_8004A774[2];
                D_8004BCD0[entIndex].state = 4;
                arcadeSaveHighScores();
                return;
            }
            if (D_8004BCD0[entIndex].unk1D == 0x1C) {
                if (D_8004BCD0[entIndex].state != 0) {
                    D_8004A774[--D_8004BCD0[entIndex].state] = D_80746800[0x1C];
                    return;
                }
            }
            if (D_8004BCD0[entIndex].state < 3) {
                D_8004A774[D_8004BCD0[entIndex].state] = D_80746800[D_8004BCD0[entIndex].unk1D];
                D_8004BCD0[entIndex].state++;
            }
        }
    }
}

void arcadeUpdateBonusBox(u8 entIndex) {
    if (D_8004BCD0[entIndex].unk1C >= D_8004C71E) {
        D_8004BCD0[entIndex].type = 0;
    }
}


void arcadeDispatchEntities(void) {
    u8 i = 0;

    do {
        switch (D_8004BCD0[i].type) {
        case 1:
            arcadeUpdateBarrelEntity(i);
            break;
        case 2:
            arcadeUpdateBouncingBarrel(i);
            break;
        case 3:
            arcadeUpdateSpringEntity(i);
            break;
        case 19:
            arcadeUpdateOilDrumEntity(i);
            break;
        case 13:
            arcadeUpdatePlayerEntity(i);
            break;
        case 26:
            arcadeUpdatePaulineUpper(i);
            break;
        case 30:
            arcadeUpdateHeartEntity(i);
            break;
        case 29:
            arcadeUpdateHelpSpeechBubble(i);
            break;
        case 27:
            arcadeUpdatePaulineLower(i);
            break;
        case 18:
            arcadeUpdateConveyorPulleys(i);
            break;
        case 21:
            arcadeUpdateDonkeyKongIntro(i);
            break;
        case 22:
            arcadeUpdateDonkeyKongStage1(i);
            break;
        case 23:
            arcadeUpdateDonkeyKongStage4(i);
            break;
        case 24:
            arcadeUpdateDonkeyKongStage2(i);
            break;
        case 25:
            arcadeUpdateDonkeyKongStage3(i);
            break;
        case 20:
            arcadeUpdateScorePopup(i);
            break;
        case 5:
            arcadeUpdateCollectibleItem(i);
            break;
        case 6:
            arcadeUpdateHammerEntity(i);
            break;
        case 7:
            arcadeUpdateHammerSmash(i);
            break;
        case 11:
            arcadeUpdateRivetEntity(i);
            break;
        case 12:
            arcadeUpdateRetractableLadder(i);
            break;
        case 9:
            arcadeUpdateNameEntryCursor(i);
            break;
        case 4:
            arcadeUpdateCementPanEntity(i);
            break;
        case 15:
            arcadeUpdateVictoryPauline(i);
            break;
        case 10:
            arcadeUpdateBonusBox(i);
            break;
        }
    } while (++i < 0x50);
}

extern ArcadeEntity D_8004A6D8;

void arcadeSpawnStage4Enemies(void) {
    u8 i;

    i = 0;
    if ((D_8004C6DC & 1) == 0) {
        D_8004A308[1] = 1;
        D_8004A308[2] = -1;
        if ((D_8004C6DC / 350) & 1) {
            D_8004A308[3] = 1;
        } else {
            D_8004A308[3] = -1;
        }
    } else {
        do {
            D_8004A308[i++] = 0;
        } while (i < 4);
    }
    if (D_8004C6DC % 120 == 0 && arcadeCountEntitiesByType(4) < 5) {
        i = arcadeFindFreeEntityAfterPlayer();
        D_8004BCD0[i] = D_8004A6D8;
        if (arcadeRand() > 0x4000) {
            if ((D_8004C6DC / 350) & 1) {
                D_8004BCD0[i].x = 40.0f;
            } else {
                D_8004BCD0[i].x = 280.0f;
            }
        } else {
            D_8004BCD0[i].y = 127.0f;
            if (arcadeRand() > 0x4000) {
                D_8004BCD0[i].unk1C = 1;
                D_8004BCD0[i].x = 40.0f;
            } else {
                D_8004BCD0[i].unk1C = 2;
                D_8004BCD0[i].x = 280.0f;
            }
        }
    }
}

void arcadeSpawnStage2Enemies(void) {
    u8 idx;
    u8 r;

    if (D_8004C6DC % 200 == 0 && arcadeCountEntitiesByType(2) < 5) {
        idx = arcadeFindFreeEntityAfterPlayer();
        D_8004BCD0[idx] = D_8004A3D8;
        D_8004BCD0[idx].unk1A = 0;
        D_8004BCD0[idx].vx = -0.5f;
        D_8004BCD0[idx].x = 244.0f;
        r = arcadeRand() & 7;
        if (r >= 4) {
            r = 1;
        }
        D_8004BCD0[idx].x = D_8004A318[r * 2];
        D_8004BCD0[idx].y = D_8004A318[r * 2 + 1];
        if (160.0f < D_8004BCD0[D_8004C71F].x) {
            D_8004BCD0[idx].unk1A = 1 - D_8004BCD0[idx].unk1A;
            D_8004BCD0[idx].vx = -D_8004BCD0[idx].vx;
            D_8004BCD0[idx].x = 320.0f - D_8004BCD0[idx].x;
        }
    }
    if (D_8004C718 == 0) {
        arcadeStopSound(0);
        D_8004C718 = 1;
        D_8004C708 = 1;
        D_8004C71D = 2;
        D_8004BCD0[arcadeFindEntityByType(0x17)].state = 8;
    }
}

extern u8 D_8004A82C[5][3];
extern u8 D_8004BCEC;

void arcadeDrawNameRegistration(Gfx **glistp) {
    s32 i;
    Gfx *g;
    u8 buf[0x50];

    g = *glistp;
    if (D_8004C724 == 3) {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
        arcadeSetTextPosition(0x78, 0x3B);
        _sprintf(buf, "NAME %.3s", D_8004A774);
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0xA0, 0x41);
        _sprintf(buf, "---");
        arcadeDrawString(&g, buf);
        if (D_8004C6DC < 0x708) {
            arcadeSetTextPosition(0x60, 0x7B);
            _sprintf(buf, "REGI TIME <%02d>", 0x1E - D_8004C6DC / 0x3C);
        } else {
            arcadeSetTextPosition(0x40, 0x7B);
            _sprintf(buf, "YOUR NAME WAS");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0xB0, 0x7B);
            _sprintf(buf, "REGISTERED.");
        }
        arcadeDrawString(&g, buf);
        arcadeSetTextColor(0xFF, 0, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x2B);
        _sprintf(buf, "NAME REGISTRATION");
        arcadeDrawString(&g, buf);
        arcadeSetTextColor(0, 0xFF, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x4B);
        _sprintf(buf, "A B C D E F G H I J");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0x5B);
        _sprintf(buf, "K L M N O P Q R S T");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0x6B);
        _sprintf(buf, "U V W X Y Z . -");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0xD4, 0x6B);
        _sprintf(buf, "ba");
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextColor(0xFF, 0, 0, 0xFF);
    for (i = 0; i < 5; i++) {
        if (i == 3) {
            arcadeSetTextColor(0xFF, 0xFF, 0, 0xFF);
        }
        arcadeSetTextPosition(0x38, 0x8B + i * 0x10);
        if (i == D_8004BCD0[0].unk1C && (D_8004C6DC & 0x20) && D_8004C724 == 3) {
            _sprintf(buf, "%.3s", D_8004A82C[i]);
        } else {
            _sprintf(buf, "%.3s  %06d  %.3s", D_8004A82C[i], D_8004A74C[i], D_8004A778[i]);
        }
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextColor(0, 0xFF, 0, 0xFF);
    arcadeSetTextPosition(0xB8, 0xDB);
    _sprintf(buf, "CREDIT 00");
    arcadeDrawString(&g, buf);
    *glistp = g;
}

void arcadeSetStageTextColor(s8 stageIndex) {
    if (stageIndex == D_8004A768) {
        arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else if (D_8004C722 == 2) {
        arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
    } else {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
    }
}

extern s32 D_8004A83C;
extern u8 D_8003DA90[];
extern ArcadeGfxSlot D_8004BBF0[];

void arcadeDrawHud(Gfx **glistp) {
    s32 i;
    Gfx *g;
    u8 buf[0x50];

    g = *glistp;
    gDPSetScissor(g++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    D_8004C6D4.word = 0x400;
    D_8004C719 = 8;
    D_8004C6D0 = D_8003DA90;
    D_8004C71A = 8;
    dlInitTextureDescriptor(&D_8004BBF0[gGfxBufferIndex], D_8004C6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&g, &D_8004BBF0[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, D_8004C6D4.half[1], 0, 0);
    if (D_8004A83C == 0) { // FAKE: empty guard steers regalloc
    }
    for (i = 0; i < D_8004C71C; i++) {
        dlAppendTextureRectangle(&g, i * 0x20 + 0x360, 0x4C);
    }
    arcadeSetTextColor(0xFF, 0, 0, 0xFF);
    if ((D_8004C6D8 & 0x10) || D_8004C724 == 0) {
        arcadeSetTextPosition(0x48, 0x13);
        _sprintf(buf, "1UP");
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextPosition(0x78, 0x13);
    _sprintf(buf, "HIGH SCORE");
    arcadeDrawString(&g, buf);
    arcadeSetTextColor(0, 0, 0xFF, 0xFF);
    arcadeSetTextPosition(0xD8, 0x1B);
    _sprintf(buf, "L=%02d", D_8004A76C);
    arcadeDrawString(&g, buf);
    arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    arcadeSetTextPosition(0x38, 0x1B);
    _sprintf(buf, "%06d    %06d", D_8004A748, D_8004A760);
    arcadeDrawString(&g, buf);
    if (D_8004C724 == 5 || D_8004C724 == 4) {
        if (D_8004A764 != 0) {
            if (D_8004C722 == 2) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else if (D_8004C722 == 4) {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetTextPosition(0x78, 0xA3);
            _sprintf(buf, "GAME OVER");
            arcadeDrawString(&g, buf);
        }
        if (D_8004C724 == 4) {
            if (D_8004A768 == 0 || D_8004C722 == 4) {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else if (D_8004C722 == 2) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else {
                arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetStageTextColor(0);
            arcadeSetTextPosition(0x88, 0x8B);
            _sprintf(buf, "RETURN");
            arcadeDrawString(&g, buf);
            arcadeSetStageTextColor(1);
            arcadeSetTextPosition(0x68, 0x9B);
            _sprintf(buf, "DELETE HISCORE");
            arcadeDrawString(&g, buf);
            arcadeSetStageTextColor(2);
            arcadeSetTextPosition(0x68, 0xAB);
            _sprintf(buf, "EXIT DK ARCADE");
            arcadeDrawString(&g, buf);
        }
        if (D_8004C722 == 2) {
            if (D_8004C71E < 0xA) {
                arcadeSetTextColor(0, 0, 0xFF, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            }
        } else if (D_8004C722 == 4) {
            if (D_8004C71E < 0xA) {
                arcadeSetTextColor(0xF0, 0x30, 0, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            }
        } else {
            if (D_8004C71E < 0xA) {
                arcadeSetTextColor(0xFF, 0, 0, 0xFF);
            } else {
                arcadeSetTextColor(0x60, 0xE0, 0xFF, 0xFF);
            }
        }
        arcadeSetTextPosition(0xE0, 0x30);
        if (D_8004C71E > 0) {
            i = D_8004C71E;
        } else {
            i = 0;
        }
        _sprintf(buf, "%02d00", i);
        arcadeDrawString(&g, buf);
    }
    if (D_8004C724 == 2) {
        u8 n;

        n = (D_8004C723 & 3) + 1;
        arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
        arcadeSetTextPosition(0x48, 0xD7);
        _sprintf(buf, "HOW HIGH CAN YOU GET ?");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0xC9);
        _sprintf(buf, "@%% m");
        arcadeDrawString(&g, buf);
        if (n >= 2) {
            arcadeSetTextPosition(0x58, 0xAD);
            _sprintf(buf, "%%) m");
            arcadeDrawString(&g, buf);
        }
        if (n >= 3) {
            arcadeSetTextPosition(0x58, 0x91);
            _sprintf(buf, "&%% m");
            arcadeDrawString(&g, buf);
        }
        if (n >= 4) {
            arcadeSetTextPosition(0x50, 0x75);
            _sprintf(buf, "!)) m");
            arcadeDrawString(&g, buf);
        }
    }
    if (D_8004C724 == 3) {
        arcadeDrawNameRegistration(&g);
    }
    if (D_8004C724 == 0) {
        if (!(D_8004C6DC & 0x200)) {
            arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            arcadeSetTextPosition(0x70, 0x33);
            _sprintf(buf, "INSERT COIN");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0x68, 0x43);
            _sprintf(buf, "PLAYER    COIN");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0x78, 0x53);
            _sprintf(buf, "1        1");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0x38, 0x7B);
            _sprintf(buf, "RANK  SCORE  NAME");
            arcadeDrawString(&g, buf);
            arcadeDrawNameRegistration(&g);
            arcadeSetTextColor(0xFF, 0, 0, 0xFF);
            arcadeSetTextPosition(0x78, 0x63);
            _sprintf(buf, "2        2");
            arcadeDrawString(&g, buf);
        } else {
            if (D_8004C6DC & 0x182) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetTextPosition(0x68, 0xD7);
            _sprintf(buf, "c NINTENDO 1981");
            arcadeDrawString(&g, buf);
        }
    }
    *glistp = g;
    D_8004A83C++;
}


// effectSpriteRenderPool (src/global/114270.c): stage 5: loop-entry guard FIXED: 'i = 0x80;' before the unrelated 'if (TEX==1)' then 'while (--i >= 0 && processed != count)' gives li s5,127 + bltzl s5. Only remaining diff: count spill sw s0,0x5C(sp) vs 0x64 (and its reload lw t6): spill slot 8 bytes lower than target; frame/regs/insns identical (551 lines). Tried ~400 decl-order permutations of i/count/processed/entry/player/flags, posX drop, pad words: slot never moved.
#include "common.h"
#include "actor.h"

extern void *D_807FC924;
extern u16 *D_807550E0;
extern u8 D_807FDA1A;
extern u8 D_807FDA1C;
extern u8 D_807FDA30;
Gfx *func_807105D4(Gfx *, u8);
typedef struct L10CA0Entry {
    s16 unk0; u8 pad2[6]; f32 unk8; f32 unkC; f32 unk10; u8 pad14[0xC];
    s16 unk20; s16 unk22; s16 unk24; u8 pad26[2]; f32 unk28; u8 pad2C[0x84];
    u8 unkB0; u8 unkB1; u8 unkB2; u8 padB3[5];
} L10CA0Entry;
typedef struct L10CA0Header { u16 count; u8 pad2[2]; L10CA0Entry *entries; } L10CA0Header;
typedef struct L10CA0CamView { u8 pad0[0xB4]; f32 unkB4; } L10CA0CamView;
typedef struct L10CA0PlayerView { u8 pad0[0x90]; f32 unk90; u8 pad94[0x66]; u8 unkFA; u8 padFB[0x119]; f32 unk214; } L10CA0PlayerView;
typedef struct L10CA0TimerView { u8 pad0[0xBC]; s16 unkBC; } L10CA0TimerView;

extern void *D_807FD580;
extern void *D_807FDAB0;
extern s16 D_807FDAB4;
extern u8 D_807444FC;
extern u8 D_807FDA1B;
extern u8 D_1000020, D_1000118, D_20000C0;
void matrixMakeRotationZ(f32 (*)[4], f32);
s32 mapChunkContainsPoint(s16, s16, s16);

#define L10CA0_POOL ((L10CA0Header *)D_807550E0)
#define L10CA0_TEX (&D_80755264)[D_807FDA1C * 0x14]

Gfx *effectSpriteRenderPool(Gfx *arg0, Actor *arg1) {
    f64 scaleSize;
    f32 mtxScale[4][4];
    f32 mtxTemp[4][4];
    f64 posX;
    u8 skipNearPlayer;
    u8 skipTimer;
    s16 i;
    u16 count = L10CA0_POOL->count;
    u16 processed = 0;
    L10CA0Entry *entry;
    L10CA0PlayerView *player = (L10CA0PlayerView *)gCamActor->unk174;

    skipTimer = 0;
    skipNearPlayer = 0;

    if ((D_807FBB4C->unk154 == 3) || (D_807FBB4C->unk154 == 5)) {
        f32 rem = (((L10CA0CamView *)gCamActor)->unkB4 > 180.0f) ? 0.0f : 180.0f - ((L10CA0CamView *)gCamActor)->unkB4;
        D_807FD9EC = (f32)((f64)rem * 0.02 * 240.0);
    } else {
        D_807FD9EC = 240.0f;
    }
    if ((D_807FBB4C->unk154 == 0x42) && ((((L10CA0TimerView *)D_807FD580)->unkBC == 0x62) || (((L10CA0TimerView *)D_807FD580)->unkBC == 0x88))) {
        skipTimer = 1;
    }
    if ((player->unkFA != 0) && (((L10CA0PlayerView *)D_807FC924)->unk214 < player->unk90 + 3.0f)) {
        skipNearPlayer = 1;
    }
    gDPPipeSync(arg0++);
    gSPDisplayList(arg0++, &D_1000118);
    gSPDisplayList(arg0++, &D_1000020);
    gSPMatrix(arg0++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPTexture(arg0++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(arg0++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureFilter(arg0++, G_TF_BILERP);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    i = 0x80;
    if (L10CA0_TEX == 1) {
        arg0 = func_807105D4(arg0, 0);
    }
    while (--i >= 0 && processed != count) {  // i = 0x80 above: pre-decrement while with i set before an unrelated if keeps the entry guard
        entry = &L10CA0_POOL->entries[i];
        D_807FDAB0 = entry;
        D_807FDAB4 = D_807FDA1E;
        if ((entry->unkB0 != 0) && ((entry->unk0 == -1) || mapChunkContainsPoint((s16)entry->unk8, (s16)entry->unkC, entry->unk0)) && !skipNearPlayer && !skipTimer) {
            gDPSetPrimColor(arg0++, 0, 0, D_807FDA1B, D_807FDA1B, D_807FDA1B, entry->unkB1);
            if (D_807FDA1C == 4) {
                switch (entry->unk20) {
                case 8: case 10: case 12: arg0 = func_807105D4(arg0, ((entry->unkB2++ >> 2) % 8) + 2); break;
                case 15: case 18: case 22: arg0 = func_807105D4(arg0, 0); break;
                default: arg0 = func_807105D4(arg0, 1); break;
                }
            } else if (L10CA0_TEX >= 2) {
                arg0 = func_807105D4(arg0, entry->unkB2++ % L10CA0_TEX);
            }
            scaleSize = (f64)entry->unk10 * 4.0;
            guScaleF(mtxScale, (f32)scaleSize, (f32)(scaleSize > 0.0 ? scaleSize : -scaleSize), 1.0f);
            switch (D_807FDA1C) {
            case 3:
                entry->unk22 = (s16)((f32)entry->unk22 + entry->unk28);
                matrixMakeRotationZ(mtxTemp, (f32)entry->unk22);
                break;
            case 4:
                matrixMakeRotationZ(mtxTemp, (f32)entry->unk24);
                break;
            default:
                matrixMakeRotationZ(mtxTemp, (f32)D_807FDA1E);
                break;
            }
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guTranslateF(mtxTemp, (f32)((f64)entry->unk8 * 4.0), (f32)((f64)entry->unkC * 4.0), -50.0f);
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guMtxF2L(mtxScale, (Mtx *)((u8 *)entry + (D_807444FC << 6) + 0x30));
            gSPMatrix(arg0++, (u8 *)entry + (D_807444FC << 6) + 0x30, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPVertex(arg0++, osVirtualToPhysical((void *)D_807FDA20), 4, 0);
            gSP2Triangles(arg0++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(arg0++);
        }
        if (entry->unkB0 != 0) {
            processed++;
            if ((((s32 (*)(L10CA0Entry *))D_807FDA24)(entry) != 0) || ((f64)entry->unk10 < 0.01)) {
                entry->unkB0 = 0;
                (&D_807FDA30)[D_807FDA1A = D_807FDA1A + 1] = i;
                L10CA0_POOL->count--;
            }
        }
    }
    return arg0;
}

#undef L10CA0_POOL
#undef L10CA0_TEX

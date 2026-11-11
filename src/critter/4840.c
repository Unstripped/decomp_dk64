#include "common.h"
#define PROTO_SKIP_actorSpawn // FAKE: callee prototype steer
#define PROTO_SKIP_textGetStringWidth // FAKE: callee prototype steer
#include "proto/boot/3630.h"
#include "proto/critter/4840.h"
#include "proto/global/100180.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"

typedef struct TextData {
    s16 unk0;
    s16 unk2;
    s16 *unk4;
    s16 *unk8;
    char padC[0x90 - 0xC];
    Mtx mtx[15][2];
    u8 timers[16];
    char text[32];
} TextData;


extern u8 D_1000118[];

// Actor plus its component pointers (0x174 on).
typedef struct Actor_4840 {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ TextData* unk174;
} Actor_4840;

s32 textGetStringWidth(s16, s32); // FAKE: callee prototype steer
void actorSpawn(s32, s32); // FAKE: callee prototype steer
extern s16 gScreenWidth;
extern Actor *gSpawnedActor;

extern Actor *gCurrentActor;

extern s32 D_8002A1C0;
extern Actor *D_8002A1C4;
extern u16 *D_8002A1C8;
extern u16 D_8002A1CC;
extern u16 D_8002A1CE;

void critterInitText(void) {
    D_8002A1C0 = assetLoad(0x13, 4, 1, 1);
    D_8002A1C8 = (u16 *)assetLoad(0x13, 5, 1, 1);
    D_8002A1C4 = 0;
    D_8002A1CE = 0;
    D_8002A1CC = 1;
}

s16 critterLayoutWords(TextData *textData, char *text, s16 xOffset) {
    s16 wordMidXs[18];
    s16 wordStartXs[18];
    char textCopy[36];
    u8 wordCount;
    s16 v1;

    _strcpy(textCopy, text);
    text = _strtok(textCopy, " ");
    v1 = (s32)(textGetStringWidth(6, (s32)text) * 0.5 * 4.0);
    wordStartXs[0] = xOffset;
    wordCount = 1;
    wordMidXs[0] = xOffset + v1;
    xOffset = xOffset + v1 * 2 + 0x14;
    while ((text = _strtok(NULL, " ")) != NULL) {
        v1 = (s32)(textGetStringWidth(6, (s32)text) * 0.5 * 4.0);
        wordStartXs[wordCount] = xOffset;
        wordMidXs[wordCount++] = xOffset + v1;
        xOffset = xOffset + v1 * 2 + 0x14;
    }
    textData->unk2 = wordCount;
    textData->unk8 = (s16 *)heapAlloc(wordCount * 2);
    textData->unk4 = (s16 *)heapAlloc(wordCount * 2);
    for (v1 = 0; v1 < wordCount; v1++) {
        textData->unk4[v1] = wordStartXs[v1];
        textData->unk8[v1] = wordMidXs[v1];
    }
    return wordMidXs[0];
}

extern u8 gGfxBufferIndex;

Gfx *critterDrawWord(Gfx *glistp, TextData *textData, char *word, u8 wordIndex) {
    f32 modelMtx[4][4];
    f32 tempMtx[4][4];
    u8 alpha;
    f32 timerNorm;
    s16 wordHalfWidth;

    alpha = 100;
    guMtxIdentF(modelMtx);
    if (textData->timers[wordIndex] != 0) {
        timerNorm = (f32)(u32)textData->timers[wordIndex] / 12.0f;
        textData->timers[wordIndex]--;
        wordHalfWidth = textData->unk8[wordIndex] - textData->unk4[wordIndex];
        guTranslateF(modelMtx, -wordHalfWidth, -26.0f, 0.0f);
        guScaleF(tempMtx, mathSinF((s16)(timerNorm * 2048.0f)) * 0.5 + 1.0, mathSinF((s16)(timerNorm * 2048.0f)) * 0.8 + 1.0, 1.0f);
        guMtxCatF(modelMtx, tempMtx, modelMtx);
        guTranslateF(tempMtx, wordHalfWidth, 26.0f, 0.0f);
        guMtxCatF(modelMtx, tempMtx, modelMtx);
        alpha = (u32)(mathSinF((s16)(timerNorm * 2048.0f)) * 127.0f + 128.0f);
    }
    guTranslateF(tempMtx, textData->unk4[wordIndex], textData->unk0, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guMtxF2L(modelMtx, &textData->mtx[wordIndex][gGfxBufferIndex]);
    gSPMatrix(glistp++, &textData->mtx[wordIndex][gGfxBufferIndex], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, alpha);
    return textDrawStringVtx(glistp, 6, 0, 0, (s32)word, 0);
}

Gfx *critterRenderText(Gfx *glistp, Actor *actor) {
    TextData *s2 = ((Actor_4840 *)actor)->unk174;
    u8 wordIndex;
    char *token;
    char textCopy[28];

    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    _strcpy(textCopy, s2->text);
    wordIndex = 0;
    glistp = critterDrawWord(glistp, s2, _strtok(textCopy, " "), wordIndex++);
    while ((token = _strtok(NULL, " ")) != NULL) {
        glistp = critterDrawWord(glistp, s2, token, wordIndex++);
    }
    return glistp;
}

void critterShowText(u8 fontIndex, s32 unused, s16 yPos, u8 textIndex, s16 unused2, u16 duration) {
    TextData *s0;
    s16 startX;
    s16 i;

    startX = (gScreenWidth - textGetStringWidth(fontIndex, (s32)D_8002A1C0 + (textIndex << 5))) * 2;
    if (D_8002A1C4 != NULL) {
        s0 = ((Actor_4840 *)D_8002A1C4)->unk174;
        heapFree(s0->unk8);
        heapFree(s0->unk4);
    } else {
        actorSpawn(0x10A, 0);
        s0 = ((Actor_4840 *)gSpawnedActor)->unk174;
        ((Actor_4840 *)gSpawnedActor)->unk174->unk0 = yPos * 4;
        D_8002A1C4 = gSpawnedActor;
        D_8002A1C4->unkEC = 0;
    }
    D_8002A1C4->x = (f32)critterLayoutWords(s0, (char *)((s32)D_8002A1C0 + (textIndex << 5)), startX);
    D_8002A1C4->moveYaw = 0;
    D_8002A1C4->yawSpeed = duration + 0xE;
    _strcpy(s0->text, (char *)((s32)D_8002A1C0 + (textIndex << 5)));
    for (i = 1; i < 0x10; i++) {
        s0->timers[i] = 0;
    }
    s0->timers[0] = 0xC;
}

void critterUpdateText(void) {
    Actor *actor;
    TextData *textData;
    s16 nextWordIndex;

    actor = gCurrentActor;
    textData = ((Actor_4840 *)actor)->unk174;

    if (D_8002A1CC < 0xF0) {
        if (D_8002A1CE >= D_8002A1C8[D_8002A1CC]) {
            D_8002A1CC++;
            nextWordIndex = actor->moveYaw + 1;
            actor->moveYaw = nextWordIndex;
            textData->timers[nextWordIndex] = 0xC;
            actor = gCurrentActor;
        }
    }
    if (actor->yawSpeed != 0) {
        actor->yawSpeed--;
        renderCallbacksRegister(critterRenderText, gCurrentActor, 3);
    }
    D_8002A1CE++;
}

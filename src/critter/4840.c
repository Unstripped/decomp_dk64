#include "common.h"
#include "proto/boot/3630.h"
#include "proto/critter/4840.h"
#include "proto/global/100180.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"


typedef struct TextData {
    s16 y;
    s16 wordCount;
    s16 *wordStartXs;
    s16 *wordMidXs;
    char padC[0x90 - 0xC];
    Mtx mtx[15][2];
    u8 timers[16];
    u8 text[32];
} TextData;

extern u8 D_1000118[];

extern s16 gScreenWidth;
extern Actor *gSpawnedActor;

extern Actor *gCurrentActor;

extern u8 (*critterTextTable)[32];
extern Actor *critterTextActor;
extern u16 *critterWordTimings;
extern u16 critterWordCursor;
extern u16 critterTextFrame;

void critterInitText(void) {
    critterTextTable = assetLoad(0x13, 4, 1, 1);
    critterWordTimings = assetLoad(0x13, 5, 1, 1);
    critterTextActor = NULL;
    critterTextFrame = 0;
    critterWordCursor = 1;
}

s16 critterLayoutWords(TextData *textData, u8 *text, s16 xOffset) {
    s16 wordMidXs[18];
    s16 wordStartXs[18];
    u8 textCopy[36];
    u8 wordCount;
    s16 halfWidth;

    _strcpy(textCopy, text);
    text = _strtok(textCopy, " ");
    halfWidth = (s32)(textGetStringWidth(6, text) * 0.5 * 4.0);
    wordStartXs[0] = xOffset;
    wordCount = 1;
    wordMidXs[0] = xOffset + halfWidth;
    xOffset = xOffset + halfWidth * 2 + 0x14;
    while ((text = _strtok(NULL, " ")) != NULL) {
        halfWidth = (s32)(textGetStringWidth(6, text) * 0.5 * 4.0);
        wordStartXs[wordCount] = xOffset;
        wordMidXs[wordCount++] = xOffset + halfWidth;
        xOffset = xOffset + halfWidth * 2 + 0x14;
    }
    textData->wordCount = wordCount;
    textData->wordMidXs = heapAlloc(wordCount * 2);
    textData->wordStartXs = heapAlloc(wordCount * 2);
    for (halfWidth = 0; halfWidth < wordCount; halfWidth++) {
        textData->wordStartXs[halfWidth] = wordStartXs[halfWidth];
        textData->wordMidXs[halfWidth] = wordMidXs[halfWidth];
    }
    return wordMidXs[0];
}

extern u8 gGfxBufferIndex;

Gfx *critterDrawWord(Gfx *glistp, TextData *textData, u8 *word, u8 wordIndex) {
    f32 modelMtx[4][4];
    f32 tempMtx[4][4];
    u8 alpha;
    f32 timerNorm;
    s16 wordHalfWidth;

    alpha = 100;
    guMtxIdentF(modelMtx);
    if (textData->timers[wordIndex] != 0) {
        timerNorm = (f32)textData->timers[wordIndex] / 12.0f;
        textData->timers[wordIndex]--;
        wordHalfWidth = textData->wordMidXs[wordIndex] - textData->wordStartXs[wordIndex];
        guTranslateF(modelMtx, -wordHalfWidth, -26.0f, 0.0f);
        guScaleF(tempMtx, mathSinF((s16)(timerNorm * 2048.0f)) * 0.5 + 1.0, mathSinF((s16)(timerNorm * 2048.0f)) * 0.8 + 1.0, 1.0f);
        guMtxCatF(modelMtx, tempMtx, modelMtx);
        guTranslateF(tempMtx, wordHalfWidth, 26.0f, 0.0f);
        guMtxCatF(modelMtx, tempMtx, modelMtx);
        alpha = mathSinF((s16)(timerNorm * 2048.0f)) * 127.0f + 128.0f;
    }
    guTranslateF(tempMtx, textData->wordStartXs[wordIndex], textData->y, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guMtxF2L(modelMtx, &textData->mtx[wordIndex][gGfxBufferIndex]);
    gSPMatrix(glistp++, &textData->mtx[wordIndex][gGfxBufferIndex], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, alpha);
    return textDrawStringVtx(glistp, 6, 0, 0, word, 0);
}

Gfx *critterRenderText(Gfx *glistp, Actor *actor) {
    TextData *textData = actor->customState;
    u8 wordIndex;
    u8 *token;
    u8 textCopy[28];

    gSPDisplayList(glistp++, D_1000118);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    _strcpy(textCopy, textData->text);
    wordIndex = 0;
    glistp = critterDrawWord(glistp, textData, _strtok(textCopy, " "), wordIndex++);
    while ((token = _strtok(NULL, " ")) != NULL) {
        glistp = critterDrawWord(glistp, textData, token, wordIndex++);
    }
    return glistp;
}

void critterShowText(u8 fontIndex, s32 unused, s16 yPos, u8 textIndex, s16 unused2, u16 duration) {
    TextData *textData;
    s16 startX;
    s16 i;

    startX = (gScreenWidth - textGetStringWidth(fontIndex, critterTextTable[textIndex])) * 2;
    if (critterTextActor != NULL) {
        textData = critterTextActor->customState;
        heapFree(textData->wordMidXs);
        heapFree(textData->wordStartXs);
    } else {
        actorSpawn(0x10A, 0);
        textData = gSpawnedActor->customState;
        textData->y = yPos * 4;
        critterTextActor = gSpawnedActor;
        critterTextActor->unkEC = 0;
    }
    critterTextActor->x = critterLayoutWords(textData, critterTextTable[textIndex], startX);
    critterTextActor->moveYaw = 0;
    critterTextActor->yawSpeed = duration + 0xE;
    _strcpy(textData->text, critterTextTable[textIndex]);
    for (i = 1; i < 0x10; i++) {
        textData->timers[i] = 0;
    }
    textData->timers[0] = 0xC;
}

void critterUpdateText(void) {
    Actor *actor;
    TextData *textData;

    actor = gCurrentActor;
    textData = actor->customState;

    if (critterWordCursor < 0xF0) {
        if (critterTextFrame >= critterWordTimings[critterWordCursor]) {
            critterWordCursor++;
            textData->timers[++actor->moveYaw] = 0xC;
            actor = gCurrentActor;
        }
    }
    if (actor->yawSpeed != 0) {
        actor->yawSpeed--;
        renderCallbacksRegister(critterRenderText, gCurrentActor, 3);
    }
    critterTextFrame++;
}

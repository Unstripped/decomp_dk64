#include "common.h"

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

void *heapAlloc(s32);
s16 critterLayoutWords(TextData *textData, char *text, s16 xOffset);

extern u8 D_1000118[];
char *_strcpy(char *, const char *);
char *_strtok(char *, const char *);
Gfx *critterDrawWord(Gfx *, TextData *, char *, u8);

typedef struct Actor_4840 {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[0xEC - 0x80];
    s16 unkEC;
    s16 unkEE;
    char padF0[0x168 - 0xF0];
    s16 unk168;
    char pad16A[0x174 - 0x16A];
    TextData *unk174;
} Actor_4840;

s32 textGetStringWidth(s16, s32);
void heapFree(void *);
void actorSpawn(s32, s32);
extern s16 gScreenWidth;
extern Actor_4840 *gSpawnedActor;

extern Actor_4840 *gCurrentActor;
void renderCallbacksRegister(void *, void *, s32);
Gfx *critterRenderText(Gfx *, Actor_4840 *);

s32 assetLoad(s32, s32, s32, s32);
extern s32 D_8002A1C0;
extern Actor_4840 *D_8002A1C4;
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

f32 func_80612794(s16);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, s32, s32);
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
        guScaleF(tempMtx, func_80612794((s16)(timerNorm * 2048.0f)) * 0.5 + 1.0, func_80612794((s16)(timerNorm * 2048.0f)) * 0.8 + 1.0, 1.0f);
        guMtxCatF(modelMtx, tempMtx, modelMtx);
        guTranslateF(tempMtx, wordHalfWidth, 26.0f, 0.0f);
        guMtxCatF(modelMtx, tempMtx, modelMtx);
        alpha = (u32)(func_80612794((s16)(timerNorm * 2048.0f)) * 127.0f + 128.0f);
    }
    guTranslateF(tempMtx, textData->unk4[wordIndex], textData->unk0, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guMtxF2L(modelMtx, &textData->mtx[wordIndex][gGfxBufferIndex]);
    gSPMatrix(glistp++, &textData->mtx[wordIndex][gGfxBufferIndex], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, alpha);
    return textDrawStringVtx(glistp, 6, 0, 0, (s32)word, 0);
}

Gfx *critterRenderText(Gfx *glistp, Actor_4840 *actor) {
    TextData *s2 = actor->unk174;
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
        s0 = D_8002A1C4->unk174;
        heapFree(s0->unk8);
        heapFree(s0->unk4);
    } else {
        actorSpawn(0x10A, 0);
        s0 = gSpawnedActor->unk174;
        gSpawnedActor->unk174->unk0 = yPos * 4;
        D_8002A1C4 = gSpawnedActor;
        D_8002A1C4->unkEC = 0;
    }
    D_8002A1C4->unk7C = (f32)critterLayoutWords(s0, (char *)((s32)D_8002A1C0 + (textIndex << 5)), startX);
    D_8002A1C4->unkEE = 0;
    D_8002A1C4->unk168 = duration + 0xE;
    _strcpy(s0->text, (char *)((s32)D_8002A1C0 + (textIndex << 5)));
    for (i = 1; i < 0x10; i++) {
        s0->timers[i] = 0;
    }
    s0->timers[0] = 0xC;
}

void critterUpdateText(void) {
    Actor_4840 *actor;
    TextData *textData;
    s16 nextWordIndex;

    actor = gCurrentActor;
    textData = actor->unk174;

    if (D_8002A1CC < 0xF0) {
        if (D_8002A1CE >= D_8002A1C8[D_8002A1CC]) {
            D_8002A1CC++;
            nextWordIndex = actor->unkEE + 1;
            actor->unkEE = nextWordIndex;
            textData->timers[nextWordIndex] = 0xC;
            actor = gCurrentActor;
        }
    }
    if (actor->unk168 != 0) {
        actor->unk168--;
        renderCallbacksRegister(critterRenderText, gCurrentActor, 3);
    }
    D_8002A1CE++;
}

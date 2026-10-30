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
s16 critterLayoutWords(TextData *arg0, char *arg1, s16 arg2);

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
extern s16 D_80744490;
extern Actor_4840 *D_807FBB44;

extern Actor_4840 *D_807FBB40;
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

s16 critterLayoutWords(TextData *arg0, char *arg1, s16 arg2) {
    s16 sp94[18];
    s16 sp70[18];
    char sp4C[36];
    u8 var_s1;
    s16 v1;

    _strcpy(sp4C, arg1);
    arg1 = _strtok(sp4C, " ");
    v1 = (s32)(textGetStringWidth(6, (s32)arg1) * 0.5 * 4.0);
    sp70[0] = arg2;
    var_s1 = 1;
    sp94[0] = arg2 + v1;
    arg2 = arg2 + v1 * 2 + 0x14;
    while ((arg1 = _strtok(NULL, " ")) != NULL) {
        v1 = (s32)(textGetStringWidth(6, (s32)arg1) * 0.5 * 4.0);
        sp70[var_s1] = arg2;
        sp94[var_s1++] = arg2 + v1;
        arg2 = arg2 + v1 * 2 + 0x14;
    }
    arg0->unk2 = var_s1;
    arg0->unk8 = (s16 *)heapAlloc(var_s1 * 2);
    arg0->unk4 = (s16 *)heapAlloc(var_s1 * 2);
    for (v1 = 0; v1 < var_s1; v1++) {
        arg0->unk4[v1] = sp70[v1];
        arg0->unk8[v1] = sp94[v1];
    }
    return sp94[0];
}

f32 func_80612794(s16);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, s32, s32);
extern u8 D_807444FC;

Gfx *critterDrawWord(Gfx *glistp, TextData *arg1, char *arg2, u8 arg3) {
    f32 sp98[4][4];
    f32 sp58[4][4];
    u8 sp57;
    f32 sp50;
    s16 sp4E;

    sp57 = 100;
    guMtxIdentF(sp98);
    if (arg1->timers[arg3] != 0) {
        sp50 = (f32)(u32)arg1->timers[arg3] / 12.0f;
        arg1->timers[arg3]--;
        sp4E = arg1->unk8[arg3] - arg1->unk4[arg3];
        guTranslateF(sp98, -sp4E, -26.0f, 0.0f);
        guScaleF(sp58, func_80612794((s16)(sp50 * 2048.0f)) * 0.5 + 1.0, func_80612794((s16)(sp50 * 2048.0f)) * 0.8 + 1.0, 1.0f);
        guMtxCatF(sp98, sp58, sp98);
        guTranslateF(sp58, sp4E, 26.0f, 0.0f);
        guMtxCatF(sp98, sp58, sp98);
        sp57 = (u32)(func_80612794((s16)(sp50 * 2048.0f)) * 127.0f + 128.0f);
    }
    guTranslateF(sp58, arg1->unk4[arg3], arg1->unk0, 0.0f);
    guMtxCatF(sp98, sp58, sp98);
    guMtxF2L(sp98, &arg1->mtx[arg3][D_807444FC]);
    gSPMatrix(glistp++, &arg1->mtx[arg3][D_807444FC], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, sp57);
    return textDrawStringVtx(glistp, 6, 0, 0, (s32)arg2, 0);
}

Gfx *critterRenderText(Gfx *glistp, Actor_4840 *actor) {
    TextData *s2 = actor->unk174;
    u8 var_s0;
    char *token;
    char sp38[28];

    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    _strcpy(sp38, s2->text);
    var_s0 = 0;
    glistp = critterDrawWord(glistp, s2, _strtok(sp38, " "), var_s0++);
    while ((token = _strtok(NULL, " ")) != NULL) {
        glistp = critterDrawWord(glistp, s2, token, var_s0++);
    }
    return glistp;
}

void critterShowText(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s16 arg4, u16 arg5) {
    TextData *s0;
    s16 sp2A;
    s16 i;

    sp2A = (D_80744490 - textGetStringWidth(arg0, (s32)D_8002A1C0 + (arg3 << 5))) * 2;
    if (D_8002A1C4 != NULL) {
        s0 = D_8002A1C4->unk174;
        heapFree(s0->unk8);
        heapFree(s0->unk4);
    } else {
        actorSpawn(0x10A, 0);
        s0 = D_807FBB44->unk174;
        D_807FBB44->unk174->unk0 = arg2 * 4;
        D_8002A1C4 = D_807FBB44;
        D_8002A1C4->unkEC = 0;
    }
    D_8002A1C4->unk7C = (f32)critterLayoutWords(s0, (char *)((s32)D_8002A1C0 + (arg3 << 5)), sp2A);
    D_8002A1C4->unkEE = 0;
    D_8002A1C4->unk168 = arg5 + 0xE;
    _strcpy(s0->text, (char *)((s32)D_8002A1C0 + (arg3 << 5)));
    for (i = 1; i < 0x10; i++) {
        s0->timers[i] = 0;
    }
    s0->timers[0] = 0xC;
}

void critterUpdateText(void) {
    Actor_4840 *actor;
    TextData *unk174;
    s16 temp_v1;

    actor = D_807FBB40;
    unk174 = actor->unk174;

    if (D_8002A1CC < 0xF0) {
        if (D_8002A1CE >= D_8002A1C8[D_8002A1CC]) {
            D_8002A1CC++;
            temp_v1 = actor->unkEE + 1;
            actor->unkEE = temp_v1;
            unk174->timers[temp_v1] = 0xC;
            actor = D_807FBB40;
        }
    }
    if (actor->unk168 != 0) {
        actor->unk168--;
        renderCallbacksRegister(critterRenderText, D_807FBB40, 3);
    }
    D_8002A1CE++;
}

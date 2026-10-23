#include "common.h"

typedef struct TextData {
    char pad0[2];
    s16 unk2;
    s16 *unk4;
    s16 *unk8;
} TextData;

void *func_80610FE8(s32);
s16 func_800288A8(TextData *arg0, char *arg1, s16 arg2);

extern u8 D_1000118[];
char *_strcpy(char *, const char *);
char *_strtok(char *, const char *);
Gfx *func_80028A9C(Gfx *, u8 *, char *, u8);

typedef struct Actor_4840 {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[0xEC - 0x80];
    s16 unkEC;
    s16 unkEE;
    char padF0[0x168 - 0xF0];
    s16 unk168;
    char pad16A[0x174 - 0x16A];
    u8 *unk174;
} Actor_4840;

s32 func_806FBD5C(s16, s32);
void heapFree(void *);
void actorSpawn(s32, s32);
extern s16 D_80744490;
extern Actor_4840 *D_807FBB44;

extern Actor_4840 *D_807FBB40;
void renderCallbacksRegister(void *, void *, s32);
Gfx *func_80028DE8(Gfx *, Actor_4840 *);

s32 func_8066B0F8(s32, s32, s32, s32);
extern s32 D_8002A1C0;
extern Actor_4840 *D_8002A1C4;
extern s32 D_8002A1C8;
extern u16 D_8002A1CC;
extern u16 D_8002A1CE;

void func_80028840(void) {
    D_8002A1C0 = func_8066B0F8(0x13, 4, 1, 1);
    D_8002A1C8 = func_8066B0F8(0x13, 5, 1, 1);
    D_8002A1C4 = 0;
    D_8002A1CE = 0;
    D_8002A1CC = 1;
}

/* Non-matching draft: frame size 0xE8 vs 0xB8 due to loop unrolling */
#if 0
s16 func_800288A8(TextData *arg0, char *arg1, s16 arg2) {
    s16 sp94[18];
    s16 sp70[18];
    char sp4C[36];
    char *space;
    f64 half_width;
    s16 var_s0;
    s32 var_s1;
    s32 step;
    char *token;
    s32 v1;

    _strcpy(sp4C, arg1);
    half_width = func_806FBD5C(6, (s32)_strtok(sp4C, " ")) * 0.5;
    sp70[0] = arg2;
    space = " ";
    var_s1 = 1;
    step = (s32)(half_width * 4.0);
    sp94[0] = arg2 + step;
    var_s0 = (s16)(arg2 + step * 2 + 0x14);
    token = _strtok(NULL, space);
    while (token != NULL) {
        half_width = func_806FBD5C(6, (s32)token) * 0.5;
        sp70[var_s1] = var_s0;
        step = (s32)(half_width * 4.0);
        sp94[var_s1] = var_s0 + step;
        var_s0 = (s16)(var_s0 + step * 2 + 0x14);
        var_s1 = (var_s1 + 1) & 0xFF;
        token = _strtok(NULL, space);
    }
    arg0->unk2 = var_s1;
    arg0->unk8 = (s16 *)func_80610FE8(var_s1 * 2);
    arg0->unk4 = (s16 *)func_80610FE8(var_s1 * 2);
    if (var_s1 > 0) {
        for (v1 = 0; v1 < var_s1; v1++) {
            arg0->unk4[v1] = sp70[v1];
            arg0->unk8[v1] = sp94[v1];
        }
    }
    return sp94[0];
}
#endif
#pragma GLOBAL_ASM("asm/critter/nonmatchings/4840/func_800288A8.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/4840/func_80028A9C.s")

/* Non-matching draft: frame size 0x70 vs 0x60 (16 bytes extra locals stack) */
#if 0
Gfx *func_80028DE8(Gfx *glistp, Actor_4840 *actor) {
    char sp38[40];
    char *space;
    u8 *s2 = actor->unk174;
    u8 var_s0;
    char *token;

    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    _strcpy(sp38, (char *)s2 + 0x820);
    space = " ";
    glistp = func_80028A9C(glistp, s2, _strtok(sp38, " "), 0);
    var_s0 = 1;
    token = _strtok(NULL, space);
    while (token != NULL) {
        glistp = func_80028A9C(glistp, s2, token, var_s0++);
        token = _strtok(NULL, space);
    }
    return glistp;
}
#endif
#pragma GLOBAL_ASM("asm/critter/nonmatchings/4840/func_80028DE8.s")

/* Non-matching draft: frame size 0x38 vs 0x30 (8 bytes extra locals) */
#if 0
void func_80028EE8(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5) {
    s16 sp2A;
    s32 sp24;
    u8 *s0;
    s16 v1;

    sp24 = arg3 << 5;
    sp2A = (D_80744490 - func_806FBD5C(arg0, D_8002A1C0 + sp24)) * 2;
    if (D_8002A1C4 != NULL) {
        s0 = D_8002A1C4->unk174;
        heapFree(*(void **)(s0 + 8));
        heapFree(*(void **)(s0 + 4));
    } else {
        actorSpawn(0x10A, 0);
        s0 = D_807FBB44->unk174;
        *(s16 *)s0 = arg2 * 4;
        D_8002A1C4 = D_807FBB44;
        D_807FBB44->unkEC = 0;
    }
    D_8002A1C4->unk7C = (f32)func_800288A8(s0, D_8002A1C0 + sp24, sp2A);
    D_8002A1C4->unkEE = 0;
    D_8002A1C4->unk168 = arg5 + 0xE;
    _strcpy((char *)s0 + 0x820, (char *)(D_8002A1C0 + sp24));
    v1 = 1;
    do {
        s0[0x810 + v1] = 0;
        v1++;
    } while (v1 < 0x10);
    s0[0x810] = 0xC;
}
#endif
#pragma GLOBAL_ASM("asm/critter/nonmatchings/4840/func_80028EE8.s")

void func_8002904C(void) {
    Actor_4840 *actor;
    u8 *unk174;
    s16 temp_v1;

    actor = D_807FBB40;
    unk174 = actor->unk174;

    if (D_8002A1CC < 0xF0) {
        if (D_8002A1CE >= ((u16 *)D_8002A1C8)[D_8002A1CC]) {
            D_8002A1CC++;
            temp_v1 = actor->unkEE + 1;
            actor->unkEE = temp_v1;
            unk174[temp_v1 + 0x810] = 0xC;
            actor = D_807FBB40;
        }
    }
    if (actor->unk168 != 0) {
        actor->unk168--;
        renderCallbacksRegister(func_80028DE8, D_807FBB40, 3);
    }
    D_8002A1CE++;
}

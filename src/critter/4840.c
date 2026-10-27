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

#pragma GLOBAL_ASM("asm/critter/nonmatchings/4840/func_800288A8.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/4840/func_80028A9C.s")

Gfx *func_80028DE8(Gfx *glistp, Actor_4840 *actor) {
    u8 *s2 = actor->unk174;
    u8 var_s0;
    char *token;
    char sp38[28];

    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    _strcpy(sp38, (char *)s2 + 0x820);
    var_s0 = 0;
    glistp = func_80028A9C(glistp, s2, _strtok(sp38, " "), var_s0++);
    while ((token = _strtok(NULL, " ")) != NULL) {
        glistp = func_80028A9C(glistp, s2, token, var_s0++);
    }
    return glistp;
}

#ifdef NON_MATCHING
void func_80028EE8(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s16 arg4, u16 arg5) {
    u8 *s0;
    s16 sp2A;
    s32 sp24;

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
    D_8002A1C4->unk7C = (f32)func_800288A8((TextData *)s0, (char *)(D_8002A1C0 + sp24), sp2A);
    D_8002A1C4->unkEE = 0;
    D_8002A1C4->unk168 = arg5 + 0xE;
    _strcpy((char *)s0 + 0x820, (char *)(D_8002A1C0 + sp24));
    arg4 = 1;
    do {
        s0[0x810 + arg4] = 0;
        arg4++;
    } while (arg4 < 0x10);
    s0[0x810] = 0xC;
}
#else

#pragma GLOBAL_ASM("asm/critter/nonmatchings/4840/func_80028EE8.s")
#endif

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

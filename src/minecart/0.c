#include "common.h"

typedef struct Struct_807FBB40_11C {
    char pad0[0x154];
    u8 unk154;
} Struct_807FBB40_11C;

struct MinecartStruct_174;

typedef struct Struct_807FBB40_4 {
    char pad0[0x38];
    f32 unk38;
    char pad3C[0x64 - 0x3C];
    u16 unk64;
} Struct_807FBB40_4;

typedef struct Struct_807FBB40 {
    char pad0[0x4];
    Struct_807FBB40_4 *unk4;
    char pad8[4];
    float unkC[4][4];
    char pad4C[0x60 - 0x4C];
    s32 unk60;
    char pad64[10];
    s16 unk6E;
    char pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xA4 - 0x88];
    f32 unkA4;
    char padA8[0xB8 - 0xA8];
    f32 unkB8;
    char padBC[0xC0 - 0xBC];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    char padCC[0xE4 - 0xCC];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0xF0 - 0xEA];
    s16 unkF0;
    char padF2[0x11C - 0xF2];
    Struct_807FBB40_11C *unk11C;
    char pad120[0x144 - 0x120];
    u8 unk144;
    char pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    char pad156[0x168 - 0x156];
    s16 unk168;
    char pad16A[0x174 - 0x16A];
    struct MinecartStruct_174 *unk174;
} Struct_807FBB40;

typedef struct Struct_807FC924_4_174 {
    char pad0[0x104];
    void *unk104;
    char pad108[0x1F0 - 0x108];
    s32 unk1F0;
} Struct_807FC924_4_174;

typedef struct Struct_807FC924_4 {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x174 - 0x88];
    Struct_807FC924_4_174 *unk174;
} Struct_807FC924_4;

typedef struct Struct_807FC924 {
    char pad0[0x4];
    Struct_807FC924_4 *unk4;
    char pad8[0x214 - 0x8];
    f32 unk214;
} Struct_807FC924;
typedef struct MinecartStruct_174 {
    s16 unk0;
    s16 unk2;
    Struct_807FC924_4 *unk4;
    u8 unk8;
    char pad9[0x10 - 0x9];
    s16 unk10;
    char pad12[0x24 - 0x12];
    f32 unk24;
    f32 unk28;
    char pad2C[0x30 - 0x2C];
    s32 unk30;
    s32 unk34;
    char pad38[0x3E - 0x38];
    u8 unk3E;
} MinecartStruct_174;

extern Struct_807FC924 *D_807FC924;
extern s16 D_80750AC4;
extern s32 D_8076A0A8;

void slotQueueUpdate(s32, s32, s32);
void func_806319C4(void *, s32);
void func_800253C0(void *, s16, u8);
void func_8061C6A8(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_8061CB50(void);
void func_8068ECF4(s32, s32);
void func_8072177C(void *, s16, s16, s16, s32, s32, s32, s32, s32);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void lightSetDistanceThreshold(s32);
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
typedef struct MinecartStruct_3E {
    char pad0[0x3E];
    u8 unk3E;
} MinecartStruct_3E;

typedef struct Struct_807FBB4C {
    char pad0[0x12C];
    s16 unk12C;
    char pad12E[0x174 - 0x12E];
    Struct_807FC924_4_174 *unk174;
} Struct_807FBB4C;

extern Struct_807FBB40 *D_807FBB40;
extern Struct_807FBB4C *D_807FBB4C;

void func_80609140(s32, s32, f32, f32, s32, s32);
s32 func_8070E750();
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
s32 playerStateQueueCallback();
void func_8061CC40();

void func_80024000(u8 arg0, u8 arg1) {
    func_80609140(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, arg1, 1), 0, 0x28, 8, 8);
    D_807FBB40->unk11C->unk154 = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    D_807FBB40->unk154++;
    if (arg0 != 0) {
        func_8061CC40(D_807FBB4C, 5, 5);
    }
}

void func_800240DC(u8 arg0, u8 arg1) {
    s32 temp = func_8070E750(0x1A, arg1, 1);
    textSpawnMarkerChecked(0x81, 0, 0x78, temp, 0, 0x28, 8, 8);
    D_807FBB40->unk11C->unk154 = 0;
    sfxAllocateChannel(0x2A, 1.0f);
    playerStateQueueCallback(0x43, 0, 0);
    D_807FBB40->unk154++;
    if (arg0 != 0) {
        func_8061CC40(D_807FBB4C, 5, 5);
    }
}

extern s32 D_80028C30;
extern s32 D_8071A440;
extern s32 D_8072006C;

s32 func_806119A0();
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_80714950(void *);
void func_8071498C(void *);
s32 func_80714C08(void *, s32, void *, s32, s32);

void func_800241A0(s16 *arg0, u8 arg1, u8 arg2) {
    if ((u32)(u8)func_806119A0() >= (u32)arg2) {
        if (*arg0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8A, 0x96, 0x7F, 0x32);
            func_80714950(D_807FBB40);
            func_8071498C(&D_8071A440);
            D_80028C30 = func_80714C08(&D_8072006C, 0x3ECCCCCD, D_807FBB40, arg1 + 7, 2);
        }
    }
}

void func_80024254(MinecartStruct_174 *arg0) {
    u32 temp_v0 = arg0->unk3E;
    f32 temp_fa0;
    f32 var_fv0 = temp_v0;

    if (var_fv0 != D_807FBB40->unkB8) {
        if (D_807FBB40->unkB8 < var_fv0) {
            temp_fa0 = D_807FBB40->unkB8 + 8.0f;
            if (var_fv0 < temp_fa0) {
                D_807FBB40->unkB8 = var_fv0;
                return;
            }
            D_807FBB40->unkB8 = temp_fa0;
            return;
        }
        if (var_fv0 < D_807FBB40->unkB8) {
            temp_fa0 = D_807FBB40->unkB8 - 8.0f;
            if (temp_fa0 < var_fv0) {
                D_807FBB40->unkB8 = var_fv0;
                return;
            }
            D_807FBB40->unkB8 = temp_fa0;
        }
    }
}

void func_8002430C(u8 arg0, s32 arg1, s16 arg2, u8 arg3) {
    s32 pad94;
    Struct_807FC924_4_174 *sp90;
    MinecartStruct_174 *s1;
    s32 temp_v1;
    s32 pad0, pad1, pad2, pad3, pad4, pad5, pad6, pad7, pad8;
    f32 sp58[3];

    s1 = D_807FBB40->unk174;
    sp90 = D_807FC924->unk4->unk174;
    temp_v1 = D_807FBB40->unk60;
    if (!(temp_v1 & 0x10)) {
        D_807FBB40->unk60 = temp_v1 | 0x1400;
        if (D_8076A0A8 == 6 || D_8076A0A8 == 0x37 || D_8076A0A8 == 0x6A) {
            slotQueueUpdate(0xB, 1, 0);
            D_80750AC4 = 0;
        }
    }
    if (s1->unk4 == NULL) {
        s1->unk4 = D_807FC924->unk4;
        s1->unk8 = 0;
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if ((s1->unk4->unk7C - D_807FBB40->unk7C) * (s1->unk4->unk7C - D_807FBB40->unk7C) +
            (s1->unk4->unk80 - D_807FBB40->unk80) * (s1->unk4->unk80 - D_807FBB40->unk80) +
            (s1->unk4->unk84 - D_807FBB40->unk84) * (s1->unk4->unk84 - D_807FBB40->unk84) < 400.0f) {
            s1->unk34 = arg1;
            s1->unk10 = arg0;
            s1->unk30 = arg1;
            playerStateQueueCallback(0x45, D_807FBB40, s1->unk8);
            D_807FBB40->unk154++;
            goto case_1;
        }
        func_806319C4(D_807FBB40, 0);
        break;

    case 1:
    case_1:
        func_800253C0(s1, arg2, arg3);
        func_8061C6A8(sp90->unk104, D_807FBB40, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
        D_807FBB40->unk154++;
        break;

    case 2:
        actorGetNodePos(D_807FBB40, 9, &s1->unk4->unk7C, &s1->unk4->unk80, &s1->unk4->unk84);
        D_807FBB40->unk154++;
        if (D_807FBB40->unk168 == 0 && D_8076A0A8 != 6) {
            D_807FBB40->unk168 = 2;
        }
        /* fallthrough */
    case 3:
    case 5:
        if (D_807FBB40->unk168 == 0 && func_8061CB50() != 0) {
            D_807FBB40->unk168 = 1;
        }
        if (D_807FBB40->unk168 == 1 && D_807FBB40->unk155 == 0) {
            if (func_8061CB50() != 0) {
                sp90->unk1F0 |= 8;
            } else {
                func_8061C6A8(sp90->unk104, D_807FBB40, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                sp90->unk1F0 &= ~8;
                s1->unk3E = 0x3C;
                D_807FBB40->unk155++;
            }
        }
        func_8068ECF4(6, 0xFF);
        func_80024254(s1);
        func_800253C0(s1, arg2, arg3);
        actorGetNodePos(D_807FBB40, 5, &sp58[0], &sp58[1], &sp58[2]);
        func_8072177C(D_807FBB40, (s16)(s32)sp58[0], (s16)(s32)sp58[1], (s16)(s32)sp58[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        func_8072177C(s1->unk4, (s16)(s32)sp58[0], (s16)(s32)sp58[1], (s16)(s32)sp58[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        break;

    default:
        break;
    }
}

typedef struct Struct_807FD580 {
    char pad0[0x1F0];
    s32 unk1F0;
    char pad1F4[0x1FC - 0x1F4];
    u8 unk1FC;
} Struct_807FD580;
extern Struct_807FD580 *D_807FD580;


void func_80024768(void) {
    f32 sp44[3];
    f32 sp38[3];

    if (D_807FD580->unk1F0 & 0x10000002) {
        actorGetNodePos(D_807FBB40, 2, &sp38[0], &sp38[1], &sp38[2]);
        actorGetNodePos(D_807FBB40, 1, &sp44[0], &sp44[1], &sp44[2]);
    } else {
        actorGetNodePos(D_807FBB40, 1, &sp38[0], &sp38[1], &sp38[2]);
        actorGetNodePos(D_807FBB40, 2, &sp44[0], &sp44[1], &sp44[2]);
    }
    lightSetDistanceThreshold(0xC8);
    lightSetFovAngles(20.0f, 40.0f);
    lightAdd(sp38[0], sp38[1], sp38[2], sp44[0], sp44[1], sp44[2], 0.0f, 1, 0xFF, 0xFF, 0xFF);
}

extern s32 D_80028C34;
extern s32 D_80028C3C;

void func_80024890(void) {
    MinecartStruct_174 *temp_v1 = D_807FBB40->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_v1->unk24 = 0.1f;
        temp_v1->unk28 = 5.0f;
    }
    func_8002430C(1, (s32)((D_8076A0A8 == 6) ? &D_80028C34 : &D_80028C3C), 0x7FFF, 0x23);
    func_80024768();
}

extern s16 D_807502D0;
extern f32 D_807502F8;
extern s16 D_80750338;
extern s32 D_80028C40;

void actorApplyGravity(void);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);

void func_80024914(void) {
    s32 pad0;
    s32 pad1;
    s16 temp_a1;
    s16 pad_2C;
    MinecartStruct_174 *temp_s0;

    f32 temp_fv0 = (f32)((f64)D_807FBB40->unk4->unk38 * 0.16666666675);
    temp_s0 = D_807FBB40->unk174;
    temp_a1 = temp_s0->unk0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkC8 = (f32) D_807502D0;
        temp_s0->unk24 = 3.0f;
        temp_s0->unk28 = 12.0f;
    }
    if (temp_s0->unk10 == 0x90) {
        D_807FBB40->unkB8 = 130.0f;
        D_807FBB40->unkC4 = (f32) ((f64) D_807502F8 * 0.6);
        if (temp_s0->unk0 == 0) {
            D_807FBB40->unkC0 = (f32) ((f64) D_80750338 * 1.6);
        }
    } else {
        D_807FBB40->unkC4 = (f32) D_807502F8;
    }
    temp_s0->unk0 = (s16)((f32)temp_s0->unk0 + D_807FBB40->unkC0 * temp_fv0);
    actorApplyGravity();
    if (temp_s0->unk0 < 0) {
        temp_s0->unk0 = 0;
        if (temp_a1 != 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    func_8002430C(3, (s32)&D_80028C40, temp_s0->unk2, 0x19);
    if (D_807FBB4C->unk12C != 0x12 && D_807FBB4C->unk12C != 0xB) {
        func_80024768();
    }
    if (D_807FBB40->unk154 != 0) {
        actorGetNodePos(D_807FBB40, 9, &temp_s0->unk4->unk7C, &temp_s0->unk4->unk80, &temp_s0->unk4->unk84);
    }
}

#pragma GLOBAL_ASM("asm/minecart/nonmatchings/0/func_80024B00.s")

typedef struct MinecartElem {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} MinecartElem;

typedef struct MinecartStruct_E78 {
    char pad0[0x10];
    s16 unk10;
    char pad12[0x30 - 0x12];
    u8 *unk30;
    u8 *unk34;
    char pad38[0x41 - 0x38];
    u8 unk41;
    u8 unk42;
} MinecartStruct_E78;

void heapFree(void *);
void *func_80610FE8(s32);

void func_80024E78(MinecartStruct_E78 *arg0, MinecartElem **arg1, u8 arg2, u8 arg3) {
    u8 i = 0;
    s32 found = 0;
    u8 temp_s5 = *arg0->unk34;

    for (; i < 4 && found == 0; i++) {
        if (((arg0->unk42 == 1 && i < 2) || (arg0->unk42 == 2 && i >= 2))) {
            MinecartElem *temp_s1 = &arg1[temp_s5 - arg2][i];

            if (temp_s5 >= arg2 && temp_s5 <= arg3 && arg0->unk10 == temp_s1->unk0) {
                heapFree(arg0->unk30);
                found = 1;
                arg0->unk30 = func_80610FE8(3);
                arg0->unk34 = arg0->unk30;
                arg0->unk30[0] = temp_s1->unk3;
                arg0->unk34[1] = temp_s1->unk1;
                arg0->unk34[2] = 0xFF;
                arg0->unk41 = temp_s1->unk2;
                arg0->unk10 = 1;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/minecart/nonmatchings/0/func_80024FD0.s")
typedef struct {
    char pad0[0x20];
    f32 unk20;
    f32 unk24;
    f32 unk28;
} MinecartStruct_20;

void func_8002538C(MinecartStruct_20 *arg0) {
    f32 temp = arg0->unk28;
    arg0->unk20 += arg0->unk24;
    if (temp < arg0->unk20) {
        arg0->unk20 = temp;
    }
}

#pragma GLOBAL_ASM("asm/minecart/nonmatchings/0/func_800253C0.s")

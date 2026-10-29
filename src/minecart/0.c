#include "common.h"

typedef struct Struct_807FBB40_11C {
    char pad0[0x154];
    u8 unk154;
} Struct_807FBB40_11C;

struct MinecartCart;

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
    struct MinecartCart *unk174;
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
typedef struct MinecartTrackPoint {
    f32 x;
    f32 y;
    f32 z;
} MinecartTrackPoint;

typedef struct MinecartCart {
    s16 unk0;
    s16 unk2;
    Struct_807FC924_4 *unk4;
    u8 unk8;
    char pad9[3];
    MinecartTrackPoint *unkC;
    s16 unk10;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 *unk30;
    u8 *unk34;
    char pad38[1];
    u8 unk39;
    char pad3A[4];
    u8 unk3E;
    u8 unk3F;
    u8 unk40;
    u8 unk41;
    u8 unk42;
} MinecartCart;

extern Struct_807FC924 *D_807FC924;
extern s16 D_80750AC4;
extern s32 D_8076A0A8;

void slotQueueUpdate(s32, s32, s32);
void actorUpdateModelMatrix(void *, s32);
void minecartFollowTrack(struct MinecartCart *, s16, u8);
void camSetTargetScaled(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 camIsCutsceneActive(void);
void actorSpawnNodeEffectFacingCamera(s32, s32);
void commandQueuePush(void *, s16, s16, s16, s32, s32, s32, s32, s32);
s32 actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void lightSetDistanceThreshold(s32);
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

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
void camStartPath();

void func_80024000(u8 arg0, u8 arg1) {
    func_80609140(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, arg1, 1), 0, 0x28, 8, 8);
    D_807FBB40->unk11C->unk154 = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    D_807FBB40->unk154++;
    if (arg0 != 0) {
        camStartPath(D_807FBB4C, 5, 5);
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
        camStartPath(D_807FBB4C, 5, 5);
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

void minecartSpawnWheelEffect(MinecartCart *arg0, u8 arg1, u8 arg2) {
    if ((u32)(u8)func_806119A0() >= (u32)arg2) {
        if (arg0->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8A, 0x96, 0x7F, 0x32);
            func_80714950(D_807FBB40);
            func_8071498C(&D_8071A440);
            D_80028C30 = func_80714C08(&D_8072006C, 0x3ECCCCCD, D_807FBB40, arg1 + 7, 2);
        }
    }
}

void minecartStepSpeedToTarget(MinecartCart *arg0) {
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

void minecartPlayerCartUpdate(u8 arg0, s32 arg1, s16 arg2, u8 arg3) {
    s32 pad94;
    Struct_807FC924_4_174 *sp90;
    MinecartCart *s1;
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
            s1->unk34 = (u8 *)arg1;
            s1->unk10 = arg0;
            s1->unk30 = (u8 *)arg1;
            playerStateQueueCallback(0x45, D_807FBB40, s1->unk8);
            D_807FBB40->unk154++;
        } else {
            actorUpdateModelMatrix(D_807FBB40, 0);
            break;
        }
    case 1:
        minecartFollowTrack(s1, arg2, arg3);
        camSetTargetScaled(sp90->unk104, D_807FBB40, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
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
        if (D_807FBB40->unk168 == 0 && camIsCutsceneActive() != 0) {
            D_807FBB40->unk168 = 1;
        }
        if (D_807FBB40->unk168 == 1 && D_807FBB40->unk155 == 0) {
            if (camIsCutsceneActive() != 0) {
                sp90->unk1F0 |= 8;
            } else {
                camSetTargetScaled(sp90->unk104, D_807FBB40, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                sp90->unk1F0 &= ~8;
                s1->unk3E = 0x3C;
                D_807FBB40->unk155++;
            }
        }
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        minecartStepSpeedToTarget(s1);
        minecartFollowTrack(s1, arg2, arg3);
        actorGetNodePos(D_807FBB40, 5, &sp58[0], &sp58[1], &sp58[2]);
        commandQueuePush(D_807FBB40, (s16)(s32)sp58[0], (s16)(s32)sp58[1], (s16)(s32)sp58[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        commandQueuePush(s1->unk4, (s16)(s32)sp58[0], (s16)(s32)sp58[1], (s16)(s32)sp58[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
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


void minecartUpdateHeadlight(void) {
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
    MinecartCart *temp_v1 = D_807FBB40->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_v1->unk24 = 0.1f;
        temp_v1->unk28 = 5.0f;
    }
    minecartPlayerCartUpdate(1, (s32)((D_8076A0A8 == 6) ? &D_80028C34 : &D_80028C3C), 0x7FFF, 0x23);
    minecartUpdateHeadlight();
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
    MinecartCart *temp_s0;

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
    minecartPlayerCartUpdate(3, (s32)&D_80028C40, temp_s0->unk2, 0x19);
    if (D_807FBB4C->unk12C != 0x12 && D_807FBB4C->unk12C != 0xB) {
        minecartUpdateHeadlight();
    }
    if (D_807FBB40->unk154 != 0) {
        actorGetNodePos(D_807FBB40, 9, &temp_s0->unk4->unk7C, &temp_s0->unk4->unk80, &temp_s0->unk4->unk84);
    }
}


typedef struct MinecartPlayerActorFlags {
    char pad0[0x6A];
    u16 unk6A;
} MinecartPlayerActorFlags;

extern s32 D_807F5FD0;
extern MinecartTrackPoint **D_807F5FD4;
extern s32 D_80028C48;
extern s32 D_80028C50;
void actorSetUniformScale(void *, f32);

void minecartReverseTrackBehaviour(void) {
    s32 padA;
    f32 temp_fv0;
    s16 sp4E;
    s16 i;
    s16 j;
    s16 n;
    MinecartTrackPoint tmp;
    MinecartCart *s0;

    temp_fv0 = (f32)((f64)D_807FBB40->unk4->unk38 * 0.16666666675);
    s0 = D_807FBB40->unk174;
    sp4E = s0->unk0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorSetUniformScale(D_807FBB4C, 0.12f);
        D_807FBB40->unkC4 = D_807502F8;
        D_807FBB40->unkC8 = D_807502D0;
        s0->unk24 = 0.1f;
        s0->unk28 = 5.0f;
    }
    s0->unk0 = (s16)((f32)s0->unk0 + D_807FBB40->unkC0 * temp_fv0);
    actorApplyGravity();
    if (s0->unk0 < 0) {
        s0->unk0 = 0;
        if (sp4E != 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    if (((MinecartPlayerActorFlags *)D_807FBB4C)->unk6A & 0x100) {
        ((MinecartPlayerActorFlags *)D_807FBB4C)->unk6A &= ~0x100;
        D_807FBB40->unk168 = 2;
    }
    minecartPlayerCartUpdate(1, (s32)&D_80028C48, 0x7FFF, 0x23);
    minecartUpdateHeadlight();
    if (*s0->unk34 >= 7 && camIsCutsceneActive() != 0 && D_807FBB40->unk154 != 5) {
        D_807FBB40->unkB8 = 300.0f;
    }
    if (D_807FBB40->unk154 == 4) {
        for (i = 0; i < D_807F5FD0; i++) {
            n = D_807F5FD4[i + 1] - D_807F5FD4[i];
            for (j = 0; j < n / 2; j++) {
                tmp = D_807F5FD4[i][j];
                D_807F5FD4[i][j] = D_807F5FD4[i][n - j - 1];
                D_807F5FD4[i][n - j - 1] = tmp;
            }
        }
        s0->unk34 = (u8 *)&D_80028C50;
        s0->unk10 = 2;
        D_807FBB40->unk154 = 5;
        s0->unkC = 0;
    }
    if (D_807FBB40->unk154 != 0) {
        actorGetNodePos(D_807FBB40, 9, &s0->unk4->unk7C, &s0->unk4->unk80, &s0->unk4->unk84);
    }
}

typedef struct MinecartElem {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} MinecartElem;


void heapFree(void *);
void *func_80610FE8(s32);

void minecartApplyJunction(MinecartCart *arg0, MinecartElem **arg1, u8 arg2, u8 arg3) {
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

extern s32 D_80028C20;
void actorScriptStart(void *, s32);
void actorSetStateTwo(void *);
void func_806A2A10(s32, s32, u8);
void func_80726EE0(s32);
void camSetFixedView(void *, f32, f32, f32, f32, f32, f32, s32);

void minecartPlayerCartJunctionBehaviour(void) {
    MinecartCart *sp44;
    Struct_807FC924_4_174 *sp40;
    f32 diff;
    f32 sp28;

    sp44 = D_807FBB40->unk174;
    sp40 = D_807FBB4C->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp44->unk30 = func_80610FE8(3);
        sp44->unk30[0] = 0x10;
        sp44->unk30[1] = 0xFF;
        sp44->unk24 = 3.0f;
        sp44->unk28 = 12.0f;
        D_807FBB40->unk168 = 3;
        sp40->unk1F0 |= 8;
        camStartPath(D_807FBB40, 0, 1, sp44);
        actorScriptStart(D_807FBB40, 0);
    }
    if (D_807FBB40->unk154 != 5 && D_807FBB40->unk154 != 6) {
        diff = (D_807FC924->unk214 - D_807FBB40->unk80) - 100.0f;
        sp28 = (f32)(((f64)diff / 650.0 * 0.15) + .15);
        actorSetUniformScale(D_807FBB40, sp28);
        actorSetUniformScale(D_807FBB4C, sp28);
    }
    if (sp40->unk1F0 & 8) {
        sp44->unk3E = 3;
    }
    if (D_807FBB40->unk154 < 5) {
        minecartPlayerCartUpdate(0x16, (s32)sp44->unk30, 0, 0x19);
    }
    if (camIsCutsceneActive() == 0) {
        camSetFixedView(sp40->unk104, 322.0f, 900.0f, 268.0f, 325.0f, -9000.0f, 500.0f, 0);
    }
    switch (D_807FBB40->unk154) {
    case 1:
    case 2:
    case 3:
        if (D_807FBB40->unk4->unk64 == 0x292) {
            func_800240DC(1, 0x14);
            D_807FBB40->unk154 = 5;
        } else if (D_807FBB40->unk11C != NULL && D_807FBB40->unk11C->unk154 == 5) {
            func_80726EE0(0);
            func_80024000(1, 0xE);
            D_807FBB40->unk154 = 5;
            break;
        }
        minecartApplyJunction(sp44, (MinecartElem **)&D_80028C20, 0x10, 0x13);
        actorGetNodePos(D_807FBB40, 9, &sp44->unk4->unk7C, &sp44->unk4->unk80, &sp44->unk4->unk84);
        return;
    case 4:
        D_807FBB40->unk154 = 3;
        sp44->unk34--;
        break;
    case 5:
        actorSetUniformScale(D_807FBB40, 0.15f);
        actorSetUniformScale(D_807FBB4C, 0.225f);
        D_807FBB40->unkE4 = 0;
        D_807FBB40->unk154++;
        break;
    case 10:
        sfxAllocateChannel(0x5A, 1.0f);
        func_806A2A10(0x78, 0x78, (D_8076A0A8 == 0x4D) ? 0x1E : (D_8076A0A8 == 0x81) ? 0x2D : 0x3C);
        actorSetStateTwo(D_807FBB40->unk11C);
        sp40->unk1F0 &= ~8;
        D_807FBB40->unk154 = 3;
        break;
    }
}


void minecartRampTiltRate(MinecartCart *arg0) {
    f32 temp = arg0->unk28;
    arg0->unk20 += arg0->unk24;
    if (temp < arg0->unk20) {
        arg0->unk20 = temp;
    }
}


extern s32 D_807457E4[];
extern s16 D_80770628[];
extern f32 D_80770B68[];
extern s32 D_8076A064;
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathPickCloserTargetPoint3D(f32, f32, f32, MinecartTrackPoint *, MinecartTrackPoint *, MinecartTrackPoint *, MinecartTrackPoint *, f32 *, f32 *, f32 *);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
s16 func_806CC190(s16, s16, f32);
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8067ACB4(void *);
void matrixMakeRotationZ(f32 (*)[4], f32);
void actorUpdateFloorContactAndTilt(void *, f32);
void minecartFollowTrack(MinecartCart *arg0, s16 arg1, u8 arg2) {
    u8 i;
    u8 cnt;
    s8 sp12D;
    MinecartTrackPoint *sp128;
    MinecartTrackPoint *sp124;
    f32 sp118[3];
    f32 sp10C[3];
    f32 sp100[3];
    f32 spF4[3];
    s32 limit;
    f32 prev;
    s16 spEA;
    s16 n;
    f32 diff;
    f32 spE0, spDC, spD8;
    f32 spD4;
    f32 lim;
    f64 t;
    f32 sp88[4][4];
    u8 i2;
    u8 cnt2;
    s16 sp84;
    s8 sp83;
    u8 sp82;
    s16 v1;
    f32 sp7C, sp78, sp74;
    MinecartTrackPoint *q;
    MinecartTrackPoint *p;

    sp124 = arg0->unkC;
    sp84 = D_807FBB40->unkE6;
    sp83 = 0;
    sp82 = (*arg0->unk34 + arg0->unk3F) & 0xFF3F;
    func_8067ACB4(D_807FBB40);
    if (arg0->unk34 != NULL && sp124 == NULL) {
        D_807FBB40->unk144 = 0x24;
        sp128 = &D_807F5FD4[sp82][arg0->unk10++];
        D_807FBB40->unk7C = sp128->x;
        sp128++;
        D_807FBB40->unk80 = sp128[-1].y;
        D_807FBB40->unk84 = sp128[-1].z;
        D_807FBB40->unkA4 = sp128[-1].y;
        D_807FBB40->unkE6 = mathAngleBetweenPoints2D(sp128->x, sp128->z, D_807FBB40->unk7C, D_807FBB40->unk84);
        D_807FBB40->unkE8 = (s16)(s32)(((f64)func_80611BB4(D_807FBB40->unk80 - sp128->y,
                                sqrtf((D_807FBB40->unk7C - sp128->x) * (D_807FBB40->unk7C - sp128->x) + (D_807FBB40->unk84 - sp128->z) * (D_807FBB40->unk84 - sp128->z))) * 2048.0) / 3.1415927410125732);
        arg0->unkC = sp128 - 2;
        sfxPlayActorSound(D_807FBB40, 0x113, 0, 1, 0, 0xFF, 1.0f, 0);
        arg0->unk41 = 1;
    }
    sp128 = &D_807F5FD4[sp82][arg0->unk10];
    if (arg0->unk10 >= 2) {
        sp124 = sp128 - 2;
    }
    if (D_807FBB40->unkB8 < 0.0f && D_807FBB40->unk7C == sp128[-1].x && D_807FBB40->unk84 == sp128[-1].z && arg0->unk10 >= 2) {
        arg0->unk10--;
        sp128--;
    }
    actorGetNodePos(D_807FBB40, 3, &spF4[0], &spF4[1], &spF4[2]);
    actorGetNodePos(D_807FBB40, 4, &sp100[0], &sp100[1], &sp100[2]);
    spD4 = (f64)(D_807FBB40->unk4->unk38 * D_807FBB40->unkB8) * 0.16666666675;
    if (D_8076A0A8 == 0x4D || D_8076A0A8 == 0x81 || D_8076A0A8 == 0x82) {
        spD4 = (f64)spD4 * 1.8;
    } else {
        if ((2.0 * (f64)func_80612794(D_807FBB40->unkE8)) + 1.0 < 0.6) {
            t = 0.6;
        } else {
            t = (2.0 * (f64)func_80612794(D_807FBB40->unkE8)) + 1.0;
        }
        spD4 = (f64)spD4 * (2.5 * t);
    }
    spEA = mathAngleBetweenPoints2D(sp128->x, sp128->z, sp128[-1].x, sp128[-1].z);
    if (arg0->unk0 == 0) {
        D_80770B68[D_80770628[D_807FBB40->unk6E]] = ((f64)spD4 / 15.0) + 0.7;
    } else {
        D_80770B68[D_80770628[D_807FBB40->unk6E]] = 0.0f;
    }
    if (D_807FBB40->unkF0 != 0) {
        D_807FBB40->unkF0 = D_807FBB40->unkF0 - 1;
        mathPickCloserTargetPoint3D(spF4[0], spF4[1], spF4[2], sp128, sp128 + 1, sp128 + 1, sp128 + 2, &sp10C[0], &sp10C[1], &sp10C[2]);
        mathPickCloserTargetPoint3D(sp100[0], sp100[1], sp100[2], sp128 - 1, sp128, sp128, sp128 + 1, &sp118[0], &sp118[1], &sp118[2]);
    } else {
        mathPickCloserTargetPoint3D(spF4[0], spF4[1], spF4[2], sp128 - 1, sp128, sp128, sp128 + 1, &sp10C[0], &sp10C[1], &sp10C[2]);
        mathPickCloserTargetPoint3D(sp100[0], sp100[1], sp100[2], sp124, sp124 + 1, sp128 - 1, sp128, &sp118[0], &sp118[1], &sp118[2]);
    }
    D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, (s16)(f32)mathAngleBetweenPoints2D(sp10C[0], sp10C[2], sp118[0], sp118[2]), 1.7f);
    diff = sqrtf((sp10C[0] - sp118[0]) * (sp10C[0] - sp118[0]) + (sp10C[2] - sp118[2]) * (sp10C[2] - sp118[2]));
    prev = D_807FBB40->unkE8;
    D_807FBB40->unkE8 = (s16)(s32)(((f64)func_80611BB4(sp118[1] - sp10C[1], diff) * 2048.0) / 3.1415927410125732);
    prev = prev - (f32)D_807FBB40->unkE8;
    if (prev > 2048.0f) {
        prev -= 4096.0f;
    }
    if (prev <= -2048.0f) {
        prev += 4096.0f;
    }
    if (prev > 25.0f) {
        cnt = 0;
        for (i = 0; i < 0x14; i++) {
            if (D_807457E4[i] != 0) {
                cnt++;
            }
        }
        if (cnt < 5) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x20, 0xFF, 0x7F, 0x14);
        }
    }
    spE0 = func_80612794(spEA) * spD4 + D_807FBB40->unk7C;
    spD8 = func_80612790(spEA) * spD4 + D_807FBB40->unk84;
    spDC = D_807FBB40->unkA4;
    if (mathPickCloserTargetPoint3D(spE0, spDC, spD8, sp128 - 1, sp128, sp128, sp128 + 1, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84) != 0) {
        arg0->unk10++;
    }
    D_807FBB40->unk80 = D_807FBB40->unk80 + (f32)arg0->unk0;
    n = D_807F5FD4[sp82 + 1] - D_807F5FD4[sp82];
    if (D_807F5FD0 == sp82 + 1) {
        limit = n - 1;
    } else {
        limit = n;
    }
    if (arg0->unk10 >= limit) {
        arg0->unk34++;
        if (*arg0->unk34 == 0xFF) {
            D_807FBB40->unk154++;
        }
        if (D_807FD580->unk1FC != 0 && arg0->unk4 == (void *)D_807FBB4C) {
            arg0->unk3F = D_807FD580->unk1FC;
            D_807FD580->unk1FC = 0;
        } else if (D_8076A0A8 == 0x6A) {
            D_807FBB40->unkF0 = 0x1E;
            arg0->unk2C = 0.0f;
            if (*arg0->unk34 & 0x80) {
                arg0->unk3F = (u32)arg0->unk3F >> 1;
            } else if (!(*arg0->unk34 & 0x40)) {
                arg0->unk3F = 0;
            } else {
                arg0->unk3F = arg0->unk3F << 1;
            }
            if (arg0->unk3F & 0x80) {
                arg0->unk3F = 0;
            }
        } else {
            arg0->unk3F = 0;
        }
        arg0->unk10 = arg0->unk41;
        arg0->unkC = sp128 - 1;
        arg0->unk41 = 1;
    }
    if (arg0->unk2C != 0.0f) {
        i = (*arg0->unk34 + arg0->unk40) & 0x3F;
        q = &D_807F5FD4[i][arg0->unk10];
        mathPickCloserTargetPoint3D(spE0, spDC, spD8, q - 1, q, q, q + 1, &sp7C, &sp78, &sp74);
        D_807FBB40->unk7C = D_807FBB40->unk7C + (sp7C - D_807FBB40->unk7C) * arg0->unk2C;
        D_807FBB40->unk84 = D_807FBB40->unk84 + (sp74 - D_807FBB40->unk84) * arg0->unk2C;
        arg0->unk2C = (f64)arg0->unk2C - 0.06;
        if (arg0->unk2C < 0.0f) {
            arg0->unk2C = 0.0f;
        }
    }
    sp12D = (arg0->unk14 > 0.0f) ? 1 : ((arg0->unk14 < 0.0f) ? -1 : 0);
    if (arg1 == 0x7FFF) {
        v1 = D_807FBB40->unkE6 - sp84;
        if (v1 >= 0x801) {
            v1 -= 0x1000;
        }
    } else {
        v1 = arg1;
    }
    lim = ((f64)arg2 < (f64)((f32)(v1 > 0 ? v1 : -v1) * spD4) * 0.25) ? (f64)arg2 : (f64)((f32)(v1 > 0 ? v1 : -v1) * spD4) * 0.25;
    arg0->unk18 = (f64)arg0->unk18 + (f64)(lim - arg0->unk18) * 0.2;
    if (v1 >= 0x1F && v1 < 0x5A) {
        if (arg0->unk14 < lim) {
            minecartRampTiltRate(arg0);
            arg0->unk14 = arg0->unk14 + arg0->unk20;
            if (lim < arg0->unk14) {
                arg0->unk14 = lim;
            }
        }
    } else if (v1 < -0x1E && v1 >= -0x59) {
        if (-lim < arg0->unk14) {
            minecartRampTiltRate(arg0);
            arg0->unk14 = arg0->unk14 - arg0->unk20;
            if (arg0->unk14 < -lim) {
                arg0->unk14 = -lim;
            }
        }
    }
    if (arg0->unk14 > 1.0f) {
        sp83 = 0x20;
        minecartSpawnWheelEffect(arg0, 1, 0xE6);
    } else if (arg0->unk14 < -1.0f) {
        sp83 = -0x20;
        minecartSpawnWheelEffect(arg0, 0, 0xE6);
    } else {
        minecartSpawnWheelEffect(arg0, D_8076A064 & 1, 0xFA);
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
    if (sp83 != 0) {
        if (arg0->unk18 < 10.0f) {
            arg0->unk20 = 0.0f;
            if (arg0->unk14 > 0.0f) {
                arg0->unk14 = arg0->unk14 - arg0->unk1C;
                if (arg0->unk14 < 0.0f) {
                    arg0->unk14 = 0.0f;
                }
            } else if (arg0->unk14 < 0.0f) {
                arg0->unk14 = arg0->unk14 + arg0->unk1C;
                if (arg0->unk14 > 0.0f) {
                    arg0->unk14 = 0.0f;
                }
            }
            arg0->unk1C = ((f64)arg0->unk1C + 0.5 < 10.0) ? (f64)arg0->unk1C + 0.5 : 10.0;
        } else {
            arg0->unk1C = 0.0f;
            cnt2 = 0;
            i2 = 0;
            do {
                if (D_807457E4[i2] != 0) {
                    cnt2++;
                }
                i2++;
            } while (i2 < 0x14);
            if (cnt2 < 5) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x21, 0xFF, 0x7F, 0x14);
            }
        }
        guTranslateF(D_807FBB40->unkC, (f32)sp83, 0.0f, 0.0f);
        matrixMakeRotationZ(sp88, arg0->unk14);
        guMtxCatF(D_807FBB40->unkC, sp88, D_807FBB40->unkC);
        guTranslateF(sp88, (f32)-sp83, 0.0f, 0.0f);
        guMtxCatF(D_807FBB40->unkC, sp88, D_807FBB40->unkC);
        actorUpdateModelMatrix(D_807FBB40, 1);
        lim = (arg0->unk14 > 0.0f) ? arg0->unk14 : -arg0->unk14;
        if ((f32)arg0->unk39 < lim) {
            if (arg0->unk14 > 0.0f) {
                arg0->unk39 = arg0->unk14;
            } else {
                arg0->unk39 = -arg0->unk14;
            }
        }
    }
    if (((arg0->unk14 > 0.0f) ? 1 : ((arg0->unk14 < 0.0f) ? -1 : 0)) != sp12D) {
        if (arg0->unk39 != 0 && arg0->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8B, ((arg0->unk39 / arg2) * 0x7F + 0x80) & 0xFF, 0x7F, 0x1E);
            arg0->unk39 = 0;
        }
    }
    actorUpdateFloorContactAndTilt(D_807FBB40, 0);
}

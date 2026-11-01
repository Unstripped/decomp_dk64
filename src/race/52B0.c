#include "common.h"

extern s32 D_8002FC5C[];
void func_8002CAC8(s32, void *, void *);
void func_8002D0B0(void);
s32 func_8002E8EC(s32, s32, s32);

typedef struct {
    u8 pad0[0x4];
    f32 unk4;
    u8 pad8[0x10 - 0x8];
    f32 unk10;
    u8 pad14[0x1C - 0x14];
    u16 unk1C;
    u8 pad1E[0x25 - 0x1E];
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 pad29[0x30 - 0x29];
    void *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 pad37[0x44 - 0x37];
    u8 unk44;
    u8 pad45[0x104 - 0x45];
    s32 unk104;
} RaceC_State;

typedef struct RaceC_Actor RaceC_Actor;

typedef struct {
    RaceC_Actor *unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9;
    u16 unkA;
} RaceC_Target;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0xB8 - 0x12];
    f32 unkB8;
} RaceC_Obj;

typedef struct {
    RaceC_Obj *unk0;
    u8 pad4[0x64 - 0x4];
    u16 unk64;
} RaceC_Sub;

struct RaceC_Actor {
    u8 pad0[0x4];
    RaceC_Sub *unk4;
    u8 pad8[0x60 - 0x8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x6E - 0x6C];
    s16 unk6E[2];
    u8 pad72[0x7C - 0x72];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xE4 - 0xBC];
    s16 unkE4;
    u8 padE6[0xE8 - 0xE6];
    s16 unkE8;
    u8 padEA[0x12A - 0xEA];
    s16 unk12A;
    u8 pad12C[0x144 - 0x12C];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    RaceC_State *unk174;
    RaceC_State *unk178;
    void *unk17C;
    RaceC_Target *unk180;
};

typedef struct {
    u8 pad0[4];
    RaceC_Actor *unk4;
    u8 pad8[0x2F0 - 8];
} RaceC_Player;

#define RC_A ((RaceC_Actor *)D_807FBB40)

extern u8 gPlayerCount;
extern void *D_807FBB40;
extern RaceC_Actor *D_807FBB44;
void func_8002BBD0(void *, s32);
void actorSpawn(s32, s32);
void func_8002BC2C(void *, s32, void *, void *);
RaceC_Actor *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);
void func_8002BCB0(void *, s32, void *, void *);
void actorInitFromSpawnPoint(void *, void *);

void func_800292B0(s32 arg0, RaceC_Actor *arg1) {
    func_8002CAC8(arg0, arg1, arg1->unk174);
}

void func_800292D0(RaceC_Actor *arg0) {
    RaceC_State *sp5C;
    RaceC_State *sp58;
    RaceC_Actor *sp54;
    s32 var_s1;
    s32 var_s0;
    s32 var_s5;

    var_s5 = gPlayerCount;
    var_s1 = 0;
    sp5C = arg0->unk174;
    if (var_s5 == 1) {
        var_s5++;
    }
    func_8002BBD0(arg0, var_s5);
    for (var_s0 = 0; var_s0 < gPlayerCount; var_s0++) {
        actorSpawn(0x133, 0x9F);
        sp54 = D_807FBB44;
        sp58 = sp54->unk174;
        sp58->unk27 = 0;
        func_8002BC2C(arg0, var_s1, sp54, sp58);
        var_s1++;
        sp58->unk28 = var_s0;
    }
    var_s0 = 0;
    if (gPlayerCount == 1) {
        sp54 = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        sp58 = sp54->unk178;
        sp58->unk27 = 1;
        func_8002BC2C(arg0, var_s1, sp54, sp58);
        func_8002BCB0(arg0, 0, sp54->unk180, &sp54->unk180->unk4);
        sp5C->unk25 = 1;
    } else {
        sp5C->unk25 = 0;
    }
    if (var_s5 > 0) {
        do {
            func_8002BCB0(arg0, var_s0, &sp54, &sp58);
            sp58->unk36 = var_s0;
            sp58->unk30 = arg0;
            if (sp58->unk27 == 0) {
                actorInitFromSpawnPoint(sp54, sp58);
            }
            var_s0++;
        } while (var_s0 != var_s5);
    }
    sp5C->unk26 = 0;
}

void func_80029488(void) {
    func_8002D0B0();
}

extern RaceC_Player *gPlayerSlots;
void actorInitAnimations(void *, void *);
void actorOrNodeFlags(void *, s32, s32);
void func_80690190(void *, void *);
void slotQueueUpdate(s32, s32, s32);
void slotQueueCancel(s32, s32);
void camSetTargetScaled(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
f32 func_8002D2C0(void *);
void func_8068F72C(void *, void *, s32, s32);
s32 func_807142D8(void);
void renderCallbacksRegister(void *, void *, s32);
void sfxStopSlotSound(void *, u8);
void actorInterpolateAngles(u8, void *, void *);
void actorUpdateModelMatrix(void *, s32);

void func_800294A8(void) {
    s32 v34;
    RaceC_State *sp68;
    RaceC_State *s4;
    RaceC_State *s1;
    RaceC_State *s0;
    s32 i;
    RaceC_Actor *tmp;
    u8 pad53;
    u8 sp52;

    s4 = RC_A->unk174;
    sp68 = RC_A->unk178;
    s1 = gPlayerSlots[s4->unk28].unk4->unk174;
    sp52 = RC_A->unk6A & 1;
    if (!(RC_A->unk60 & 0x10)) {
        actorInitAnimations(RC_A, gPlayerSlots[s4->unk28].unk4);
        RC_A->unk144 |= 0x10;
        RC_A->unk60 &= 0xFFFDFFFF;
        s4->unk44 = 5;
        actorOrNodeFlags(RC_A, 2, 0xC);
    }
    func_80690190(s4, sp68);
    v34 = s4->unk34;
    if (v34 < 5) {
        if (v34 == 1) {
            tmp = s4->unk30;
            s0 = tmp->unk174;
            if (s4->unk35 == 0) {
                slotQueueUpdate(0xB, 1, 0);
                s4->unk35 += 1;
            }
            if (s0->unk1C == 0x3C) {
                camSetTargetScaled(s1->unk104, D_807FBB40, 4, 0x800, 0x32, 0, 0x28, 0x1E, 0x14, 0, 0.4f);
            }
        }
        if (s4->unk34 == 2) {
            if (s4->unk26 != 0) {
                s4->unk4 = func_8002D2C0(s4) * 2;
                if (s4->unk4 > 1.0) {
                    s4->unk25 = 0x14;
                }
                s4->unk26 = 0;
            }
            if (s4->unk25 != 0) {
                s4->unk25 -= 1;
            }
        }
        func_8068F72C(s4, sp68, 1, 1);
        if (func_807142D8() == 0) {
            renderCallbacksRegister(func_800292B0, D_807FBB40, 3);
        }
    } else if (v34 == 5 && s4->unk35 == 0) {
        RC_A->unk60 &= ~4;
        RC_A->unkB8 = 0.0f;
        slotQueueCancel(0xB, 0);
        s4->unk35 += 1;
        for (i = 0; i < 2; i++) {
            if (RC_A->unk6E[i] != -1) {
                sfxStopSlotSound(D_807FBB40, i);
            }
        }
    }
    actorInterpolateAngles(sp52, s4, sp68);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/52B0/func_8002978C.s")

typedef struct {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x24 - 8];
    f32 unk24;
} RaceC_Inner;

typedef struct {
    u8 pad0[4];
    RaceC_Inner **unk4;
} RaceC_Holder;

void scriptSetActorRampTarget(void *, f32, f32);

void func_80029F88(RaceC_Holder *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    RaceC_Inner *v;
    f32 a;
    f32 b;
    f64 d;
    f32 c;

    v = *arg0->unk4;
    c = v->unk4;
    if (arg2 != 0) {
        b = (s32)(arg3 / arg2);
        if (!(b <= 0)) {
            a = (arg4 - c) / b;
            if (a < 0.0f) {
                a = 0.01f;
            }
            d = v->unk24 < 0.01 ? 0.01 : v->unk24;
            a = (f64)a / d;
            if (a > 2.0f) {
                a = 2.0f;
            }
            scriptSetActorRampTarget(arg0, a, 0.0f);
        }
    }
}

s32 func_8002A080(s32 arg0, s32 arg1) {
    return D_8002FC5C[func_8002E8EC(arg0, arg1, 10)];
}

typedef struct {
    u8 pad0[0x25];
    u8 unk25;
    u8 pad26[2];
    u8 unk28;
} RaceC_DC90;

typedef struct {
    u8 pad0[0x20];
    u8 *unk20;
} RaceC_DC98;

typedef struct {
    u8 pad0[0x11];
    u8 unk11;
} RaceC_DC9C;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[4];
} RaceC_Waypoint;

typedef struct {
    u8 pad0[0x14];
    RaceC_Waypoint *unk14;
} RaceC_DCA0;

extern RaceC_DC90 *D_807FDC90;
extern RaceC_DC98 *D_807FDC98;
extern RaceC_DC9C *D_807FDC9C;
extern RaceC_DCA0 *D_807FDCA0;
extern s16 D_80750AC8;
extern u8 D_8002FC20[];
extern u8 D_8002FC50[];
extern f32 D_8002FC30;
void behaviourFrameBegin(void);
void camRequestPathLength(void);
s32 camStartPath(void *, s32, s32);
void camResumePath(void);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
f32 func_8002978C(void);
void func_8002DE78(void *, s32, void *, void *);
void func_8002E644(void *);
void func_805FF544(void);
void csModelStateSetFirstByte(s32, s32);
void func_8070D8C0(void *, s32, s32);
void func_8072881C(s32, void *);
void hudSpawnTextScreen(s32);
void playerStateQueueCallback(s32, s32, s32);
void actorScriptStart(void *, s32);

void func_8002A0AC(void) {
    RaceC_State *s0;
    void *sp50;
    RaceC_Target *sp4C;
    f32 sp48;
    f64 dv;
    RaceC_State *sp3C;
    RaceC_Actor *tmp;
    s32 sp34;
    u8 idx;
    s32 sp2C;
    s32 v;
    f32 fv1;

    s0 = RC_A->unk178;
    sp50 = RC_A->unk17C;
    sp4C = RC_A->unk180;
    sp48 = 0.0f;
    behaviourFrameBegin();
    if (!(RC_A->unk60 & 0x10)) {
        tmp = s0->unk30;
        sp3C = tmp->unk174;
        s0->unk10 = 1.0f;
        RC_A->unk60 &= 0xFFFDFFFE;
        RC_A->unk12A = 0x5DC;
        func_8002DE78(sp4C, 5, D_8002FC20, D_8002FC50);
        s0->unk34 = 0;
        camRequestPathLength();
        v = camStartPath(D_807FBB40, 1, 1) - 0x3C;
        sp3C->unk1C = v;
        sp4C->unkA = v;
        s0->unk4 = 1.0f;
        D_807FDC90->unk25 = D_807FDC9C->unk11 - 5;
        idx = D_807FDC98->unk20[D_807FDC90->unk25 * 2];
        RC_A->unk7C = D_807FDCA0->unk14[idx].unk0;
        RC_A->unk80 = D_807FDCA0->unk14[idx].unk2;
        RC_A->unk84 = D_807FDCA0->unk14[idx].unk4;
        D_80750AC8 = 0xA;
    }
    if (sp4C->unkA != 0) {
        sp4C->unkA -= 1;
    }
    if (s0->unk34 < 5) {
        sp48 = func_8002978C();
        if (s0->unk34 == 2) {
            func_8002E644(sp4C);
        } else if (s0->unk34 == 4 && sp4C->unk8 == 0) {
            sp4C->unk8 = 1;
            if (flagGet(0xA5, 0) == 0) {
                camStartPath(sp4C->unk0, 0, 1);
                currentActorClearFlag();
            } else {
                func_805FF544();
            }
        }
        func_8068F72C(s0, sp50, 0, 0);
    } else if (s0->unk34 == 5) {
        switch (s0->unk35) {
        case 0:
            if (flagGet(0xA5, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                RC_A->unkE4 = 0;
                RC_A->unkE8 = 0;
                actorScriptStart(D_807FBB40, 0x29A);
            }
            s0->unk35 += 1;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                sp34 = sp4C->unk4;
                currentActorClearFlag();
                func_8070D8C0(D_807FBB40, 0x12, func_8002A080((s32)s0, sp34) & 0xFF);
                s0->unk35 += 1;
            }
            break;
        case 2:
            if (!(RC_A->unk60 & 0x02000000)) {
                camResumePath();
                s0->unk35 += 1;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                sp2C = sp4C->unk4;
                sp2C = func_8002A080((s32)s0, sp2C);
                currentActorClearFlag();
                if (sp2C == 0) {
                    csModelStateSetFirstByte(0x3B, 0xA);
                    flagSet(0xA5, 1, 0);
                } else {
                    hudSpawnTextScreen(1);
                    s0->unk35 += 1;
                }
                s0->unk35 += 1;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                func_805FF544();
                s0->unk35 += 1;
            }
            break;
        }
    }
    switch (RC_A->unk4->unk64) {
    case 0x29E:
    case 0x2A2:
        fv1 = RC_A->unkB8 * 0.0025f;
        fv1 = fv1 < 0.1 ? 0.1 : fv1;
        scriptSetActorRampTarget(D_807FBB40, fv1, 10.0f);
        break;
    case 0x2A0:
        if (RC_A->unk4->unk0->unk10 == 0x4A7) {
            func_80029F88(D_807FBB40, s0, RC_A->unkB8 - sp4C->unk0->unkB8, (sp48 - D_8002FC30) * 40.0f, 23.0f);
            break;
        }
    default:
        if (RC_A->unk4->unk0->unk10 != 0x49B) {
            scriptSetActorRampTarget(D_807FBB40, 1.0f, 10.0f);
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    func_8072881C(0, &D_807FDC90->unk28);
}

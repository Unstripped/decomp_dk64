#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern u16 D_807FD63C;

void func_806CA5F8(s32);
void func_806F3190(Actor *, s32);
void actorOrNodeFlags(Actor *, s32, s32);

void func_806C9DE0(void) {
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 0);
}

void func_806C9E10(void) {
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 2);
}

void func_806C9E40(void) {
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 3);
}

void func_806C9E70(void) {
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 4);
}

void func_806C9EA0(void) {
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 6);
}

void func_806C9ED0(void) {
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 1);
}

void func_806C9F00(void) {
    actorOrNodeFlags(D_807FBB40, 3, 8);
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 7);
}

void func_806C9F44(void) {
    func_806CA5F8(0);
    func_806F3190(D_807FBB40, 5);
}

extern s16 D_80750B54[][4];
void func_806EAB44(Actor *, u8);

#ifdef NON_MATCHING
void func_806E9964(Struct807FD580 *, s32);

void func_806C9F74(Actor *arg0) {
    u8 temp_v0 = arg0->unk154;
    s16 flags = D_80750B54[temp_v0][0];

    if (flags & 0x200) {
        func_806EAB44(arg0, temp_v0 != 2);
    } else if (flags & 0x100) {
        func_806E9964(D_807FD580, temp_v0 != 2);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9F74.s")
#endif

Actor *func_806C9FD8(Actor *arg0) {
    Actor *temp_v1 = arg0;

    if (arg0 == NULL) {
        return arg0;
    }
    switch (arg0->unk5C) {
        case 4:
            arg0 = (Actor *)arg0->unk11C;
            break;
        case 8:
            arg0 = (Actor *)arg0->unk11C;
            break;
    }
    if (arg0 != NULL && (arg0->unk5C == 1 || arg0->unk5C == 2)) {
        return arg0;
    }
    return temp_v1;
}

typedef struct G02ModelRef {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G02ModelRef;

typedef struct G02PlayerState {
    /* 0x000 */ u8 pad0[0x2C];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x48 - 0x34];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0xC2 - 0x4A];
    /* 0x0C2 */ s16 unkC2;
    /* 0x0C4 */ u8 padC4[4];
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 padCA[0x1A4 - 0xCA];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x246 - 0x1A5];
    /* 0x246 */ s8 unk246;
    /* 0x247 */ s8 unk247;
    /* 0x248 */ s8 unk248;
    /* 0x249 */ u8 unk249;
    /* 0x24A */ u8 unk24A;
    /* 0x24B */ u8 pad24B;
    /* 0x24C */ u16 unk24C;
    /* 0x24E */ u16 unk24E;
} G02PlayerState;

#define G02_P ((G02PlayerState *)D_807FD580)
#define G02_ACTOR_P(a) ((G02PlayerState *)(a)->unk174)
#define G02_MODEL(a) (*(G02ModelRef **)(a)->unk4)

void sfxStopSlotSound(Actor *, s32);
s8 func_80727194(Actor *);

void func_806CA048(Actor *arg0, G02PlayerState *arg1) {
    s32 flag = 0;
    G02PlayerState *p;

    if (arg0 == NULL) {
        flag = 1;
    } else if (arg0->unk5C & 1) {
        p = G02_ACTOR_P(arg0);
        arg1->unk248 = p->unk1A4;
        arg1->unk249 = 0;
    } else if (arg0->unk5C & 2) {
        arg1->unk248 = -1;
        arg1->unk249 = func_80727194(arg0);
    } else {
        flag = 1;
    }
    if (flag != 0) {
        G02_P->unk246 = 0;
        G02_P->unk247 = -1;
    }
    arg1->unk24A = 5;
}

void func_806CA0E8(Actor *arg0, Actor *arg1, s32 arg2) {
    G02PlayerState *temp_v1 = G02_ACTOR_P(arg0);
    G02PlayerState *p;
    s32 bad;
    s32 ok;

    ok = 0;
    bad = 0;
    if (arg1 == NULL) {
        bad = 1;
    } else if (arg1->unk5C == 1) {
        ok = 1;
        p = G02_ACTOR_P(arg1);
        temp_v1->unk247 = p->unk1A4;
        temp_v1->unk246 = 0;
    } else if (arg1->unk5C == 2) {
        temp_v1->unk246 = func_80727194(arg1);
        ok = 1;
        temp_v1->unk247 = -1;
    } else {
        bad = 1;
    }
    if (bad != 0) {
        temp_v1->unk246 = 0;
        temp_v1->unk247 = -1;
    }
    if (ok != 0) {
        temp_v1->unk24C = G02_MODEL(arg1)->unk10;
        temp_v1->unk24E = arg2;
    }
}

typedef struct G03PlayerSlot {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G03PlayerSlot;

extern G03PlayerSlot *D_807FC924;
s32 func_806CA1B4(s32);

#ifdef NON_MATCHING
typedef struct G02PlayerSlot {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} G02PlayerSlot;

Actor *func_807270C0(s32, s32);

s32 func_806CA1B4(s32 arg0) {
    s8 idx = G02_P->unk247;
    s32 ret = 1;
    Actor *actor = NULL;

    if (idx >= 0) {
        actor = ((G02PlayerSlot *)D_807FC924)[idx].unk4;
    } else {
        s8 temp = G02_P->unk246;

        if (temp > 0) {
            actor = func_807270C0(temp, 0);
        }
    }
    if (actor != NULL && G02_MODEL(actor)->unk10 == G02_P->unk24C && (s32)G02_P->unk24E >= arg0) {
        ret = 0;
    }
    return ret;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA1B4.s")
#endif

void func_806CA26C(void) {
    if (func_806CA1B4(-1) != 0) {
        G02_P->unk247 = -1;
        G02_P->unk246 = 0;
    }
}

void func_806CA2AC(void) {
    G02_P->unkC8 = -1;
    sfxStopSlotSound(D_807FBB40, 1);
}

typedef struct G02ActorView {
    /* 0x00 */ u8 pad0[0x6A];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ u8 pad70[8];
    /* 0x78 */ u8 unk78;
    /* 0x79 */ u8 pad79[0xB8 - 0x79];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0xC8 - 0xBC];
    /* 0xC8 */ f32 unkC8;
    /* 0xCC */ u8 padCC[0xD8 - 0xCC];
    /* 0xD8 */ s16 unkD8;
    /* 0xDA */ u8 padDA[0xDE - 0xDA];
    /* 0xDE */ s16 unkDE;
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[0xE6 - 0xE4];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0xEE - 0xE8];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x154 - 0xF0];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G02ActorView;

#define G02_A ((G02ActorView *)D_807FBB40)

extern s32 D_8076A064;
extern s32 D_807FBB64;
extern u16 D_807FD63A[][0x1A];
s32 func_8073110C(s32, s32);
s32 func_806F8AD4(s32, u8);
void effectSpawnBurst(s32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void func_806F8BC4(s32, s32, s32);
s32 func_806FA7A4(s32);
void func_806F91B4(s32, u8, s16);
void func_80614E78(Actor *, s32);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void func_806CA2E4(void) {
    if (G02_P->unkC8 != -1 && (func_8073110C(0x179, 0) == 0 || G02_A->unkE0 != 0.0f || (D_807FBB64 & 0x800000) || func_806F8AD4(5, G02_P->unk1A4) == 0)) {
        func_806CA2AC();
        G02_P->unkC8 = -1;
        return;
    }
    if (G02_P->unkC8 != -1) {
        if (D_807FD63A[D_807FC929][0] & 0x4000) {
            if (G02_P->unkC8 > 0) {
                if (G02_P->unkC8 < 0x1E && !(D_8076A064 & 3)) {
                    effectSpawnBurst(0);
                }
                G02_P->unkC8 = G02_P->unkC8 - 1;
                if (G02_P->unkC8 == 0x1E) {
                    sfxPlayActorSound(D_807FBB40, 0x104, 0x3C, 1, 1, 0xFF, 1.0f, 0);
                }
            } else if (!(D_8076A064 & 1)) {
                effectSpawnBurst(1);
            }
        } else {
            if (G02_P->unkC8 == 0 && (G02_A->unk6A & 1)) {
                G02_A->unk154 = 0x2D;
                G02_A->unk155 = 0;
                func_806F8BC4(5, 0, 0);
                func_806F91B4(5, G02_P->unk1A4, -func_806FA7A4(5));
                func_80614E78(D_807FBB40, 0x42);
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF2, 0xFF, 0x7F, 0);
                G02_A->unkB8 = 0.0f;
            }
            func_806CA2AC();
        }
    }
}

void func_806CA540(void) {
    if ((G02_A->unk6A & 0x221) == 1) {
        if (G02_A->unkE0 != 0.0f) {
            if (!(G02_A->unk6C & 1) || G02_A->unkDE < 0x226 || (G02_A->unk78 == 0xC && G02_A->unkB8 > 40.0f)) {
                G02_P->unkC2 = 0x32;
            }
            G02_P->unkC2 = G02_P->unkC2 + 1;
        } else {
            G02_P->unkC2 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA5F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CB53C.s")

s32 func_806EB0C0(s32, Actor *, u8);

void func_806CBE44(void) {
    if (D_807FBB70.unk2 != 0 && D_807FBB70.unk3[0x11] == 1) {
        func_806EB0C0(0x20, NULL, D_807FC929);
    }
}

extern f32 D_80753234[];
extern f32 D_80753250[];
extern s16 D_8075326C[];
s32 func_806CC14C(s16, s16);
void func_80614D90(Actor *);

void func_806CBE90(void) {
    if ((G02_A->unk6A & 0x21) == 1) {
        if (G02_A->unk6A & 0x200) {
            if (G02_A->unk6E == -1) {
                sfxPlayActorSound(D_807FBB40, 0x10D, 0, 1, 0, 0xFF, 1.0f, 0);
            }
            G02_A->unk154 = 0xF;
            G02_A->unk155 = 0;
            G02_A->unkC8 = -900.0f;
            G02_P->unk48 = D_8075326C[D_807FD584];
            G02_P->unk30 = D_80753250[D_807FD584];
            G02_P->unk2C = D_80753234[D_807FD584];
            func_80614E78(D_807FBB40, 0x5E);
            G02_A->unk6A |= 0x20;
            func_80614D90(D_807FBB40);
            return;
        }
        if (G02_A->unkE0 != 0.0f && G02_P->unkC2 >= 0x15 && G02_A->unk154 != 0x17) {
            if (func_806CC14C(G02_A->unkD8, G02_A->unkE6) < 0x200) {
                if (D_80750B54[D_807FBB48->unk154][0] & 0x200) {
                    func_806EAB44(D_807FBB40, 0);
                }
                func_806EB0C0(0x21, NULL, D_807FC929);
                return;
            }
            if (func_806CC14C(G02_A->unkD8, G02_A->unkEE) < 0x400 || G02_A->unkB8 < 15.0f) {
                if (D_80750B54[D_807FBB48->unk154][0] & 0x200) {
                    func_806EAB44(D_807FBB40, 0);
                }
                func_806EB0C0(0x22, NULL, D_807FC929);
            }
        }
    }
}

s16 func_806CC10C(arg0, arg1) s16 arg0; s16 arg1; {
    s16 d = arg1 - arg0;
    s16 temp = d & 0xFFF;
    s16 var_v1 = temp;

    if (temp > 0x800) {
        var_v1 = temp - 0x1000;
    }
    return var_v1;
}

s32 func_806CC14C(arg0, arg1) s16 arg0; s16 arg1; {
    s16 d = arg1 - arg0;
    s16 temp = d & 0xFFF;
    s16 var_v1 = temp;

    if (temp > 0x800) {
        var_v1 = 0x1000 - temp;
    }
    return var_v1;
}

s16 func_806CC190(s16 arg0, s16 arg1, f32 arg2) {
    s16 diff;
    s16 absd;
    s16 sign;
    f32 dist;

    diff = arg1 - arg0;
    if (diff > 0) {
        absd = diff;
    } else {
        absd = -diff;
    }
    if (arg2 != 0.0f && (diff & 0xFFF)) {
        if (diff >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        if (absd >= 0x801) {
            absd = 0x1000 - absd;
            sign = -sign;
        }
        dist = absd;
        if (dist < arg2) {
            arg2 = dist;
        }
        arg0 += sign * (s16)(dist / arg2);
    }
    return arg0 & 0xFFF;
}

s16 func_806CC284(s16 arg0, s16 arg1, f32 arg2) {
    s16 diff;
    s16 absd;
    s16 sign;

    diff = arg1 - arg0;
    if (diff > 0) {
        absd = diff;
    } else {
        absd = -diff;
    }
    if (arg2 != 0.0f && (diff & 0xFFF)) {
        if (diff >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        if (absd >= 0x801) {
            absd = 0x1000 - absd;
            sign = -sign;
        }
        arg0 += sign * (s16)(absd * arg2);
    }
    return arg0 & 0xFFF;
}

typedef struct G03ActorView {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ ActorSub4 *unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[6];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 pad8C[4];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x10];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[4];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ f32 unkC8;
    /* 0xCC */ u8 padCC[0xE];
    /* 0xDA */ s16 unkDA;
    /* 0xDC */ u8 padDC[0xA];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[4];
    /* 0xEE */ s16 unkEE;
} G03ActorView;

typedef struct G03PlayerView {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 pad14[0xC];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x14];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[0x84];
    /* 0xD6 */ s16 unkD6;
} G03PlayerView;

#define G03_A ((G03ActorView *)D_807FBB40)
#define G03_P ((G03PlayerView *)D_807FD580)

void func_806CCC54(s32);
void func_806CBE90(void);
void func_806CC970(void);
void func_806CCB0C(void);
f32 func_806CD898(f32, f32, f32);

extern s16 D_80753A3C[];
extern s16 D_80753A4C[];
f32 func_80612790(s16);
f32 func_80612794(s16);

#define G03_ABS(x) ((x) > 0.0f ? (x) : -(x))

void func_806CC364(u8 arg0) {
    f32 sum;
    f32 a;

    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        a = D_80753A3C[D_807FD584];
    } else {
        a = D_80753A4C[D_807FD584];
    }
    sum = G03_ABS(func_80612794(G03_A->unkE8) * a) + 1.5;
    sum += G03_ABS(func_80612790(G03_A->unkDA) * a);
    if (G03_A->unkB4 < sum) {
        if (G03_A->unkDA < 500) {
            G03_A->unkB8 = (G03_A->unkB8 < 50.0f) ? G03_A->unkB8 : 50.0f;
        }
        if (arg0) {
            if (G03_A->unkC0 < 0.0f) {
                G03_A->unkC0 = 0.0f;
            }
        }
        if (a < G03_A->unkAC - G03_A->unk80) {
            G03_A->unk80 = G03_A->unkA4 + sum;
        }
    }
}

extern f32 D_807539C0[];

void func_806CC5DC(void) {
    D_807FBB40->unkB8 = func_806CD898(D_807FBB40->unkB8, 0.0f, D_807539C0[D_807FD584]);
    func_806CC970();
    func_806CC364(1);
}

extern s16 D_80753A2C[];
extern f32 D_80753A5C[];
void actorApplyVelocityCustom(Actor *, f32, f32);
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocity(Actor *);
void func_80665564(Actor *, f32);

void func_806CC638(f32 arg0) {
    f32 vx;
    f32 vz;
    f32 adj;
    f32 rate;
    f32 sn;
    f32 cs;

    if (G03_P->unk10 != 0) {
        G03_P->unk10--;
        sn = func_80612790(G03_P->unk12);
        cs = func_80612794(G03_P->unk12);
        vx = G03_P->unk38 * sn;
        cs = G03_P->unk38 * -cs;
        vz = cs;
        adj = 0.0f;
        if (G03_P->unk38 < G03_A->unkB8) {
            rate = G03_P->unk2C * 8.0f;
        } else {
            rate = G03_P->unk2C;
        }
    } else {
        cs = func_80612794(G03_A->unkE8);
        vz = G03_A->unkB8 * -cs;
        G03_A->unkC0 = func_806CD898(G03_A->unkC0, vz, 2.0f);
        vx = 0.0f;
        adj = 0.0f;
        rate = G03_P->unk30;
    }
    if (0.0f <= vz) {
        if (G03_A->unkAC - G03_A->unk80 < D_80753A2C[D_807FD584]) {
            adj = G03_ABS(D_80753A5C[D_807FD584]);
        }
    }
    vz += adj;
    if (G03_A->unkB4 == 0.0f) {
        if (G03_A->unkC0 < -0.1) {
            G03_A->unkC0 = -0.1f;
        }
    }
    G03_A->unkC0 = func_806CD898(G03_A->unkC0, vz, rate * 2.0);
    G03_A->unkB8 = func_806CD898(G03_A->unkB8, vx, rate);
    G03_A->unkEE = G03_A->unkE6;
    actorStepPhysics(D_807FBB40, G03_A->unkEE, G03_A->unkE6);
    actorApplyVelocityCustom(D_807FBB40, G03_A->unkB8, G03_A->unkC0);
    func_80665564(D_807FBB40, 0.0f);
    func_806CC364(0);
}

extern u8 D_807FD586;

void func_806CC8A8(void) {
    D_807FD586 = 1;
}

void func_806CC8B8(void) {
    func_806CCB0C();
    func_806CBE90();
    func_806CCC54(1);
    func_806CC970();
}

void func_806CC8F0(void) {
    func_806CBE90();
    func_806CCC54(1);
    func_806CC970();
}

void func_806CC920(void) {
    func_806CCC54(1);
    func_806CC970();
}

void func_806CC948(void) {
    func_806CCB0C();
    func_806CC970();
}

f32 sqrtf(f32);
extern u32 D_80744478;

#define G03_MAX(a, b) ((a) < (b) ? (b) : (a))

void func_806CC970(void) {
    s16 angle;
    f32 dx;
    f32 dz;

    func_806CCC54(0);
    if (func_806CC14C(G03_A->unkE6, G03_A->unkEE) < 0x400) {
        angle = G03_A->unkE6;
    } else {
        angle = (G03_A->unkE6 + 0x800) & 0xFFF;
    }
    actorStepPhysics(D_807FBB40, angle, angle);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, G03_MAX(-G03_P->unkD6 * 0.125, -6.0));
    G03_A->unk60 |= 1;
    dx = G03_A->unk7C - G03_A->unk88;
    dz = G03_A->unk84 - G03_A->unk90;
    G03_P->unk20 = sqrtf(dx * dx + dz * dz) / D_80744478 * 80.0 * 0.15 / G03_A->unk4->unk34;
}

void func_806CCB0C(void) {
    if (G03_P->unk50 != 0) {
        G03_P->unk50--;
        return;
    }
    G03_A->unkC0 += G03_A->unkC4;
    if (G03_A->unkC0 < G03_A->unkC8) {
        G03_A->unkC0 = G03_A->unkC8;
    }
    if (-G03_A->unkC8 < G03_A->unkC0) {
        G03_A->unkC0 = -G03_A->unkC8;
    }
}

f32 func_806DFFA0(f32, s16, s16);
void func_806CD424(s16, f32, f32);
void func_806CD8EC(void);

void func_806CCB94(void) {
    f32 temp = func_806DFFA0(G03_P->unk4, G03_P->unkA, G03_A->unkE6);

    if (temp > 0.0f) {
        func_806CD424(G03_A->unkE6, temp, G03_P->unk38);
    } else {
        func_806CD8EC();
    }
}

s32 func_806CCC10(void) {
    switch (D_807FBB48->unk154) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCC54.s")

f32 func_80611BB4(f32, f32);

void func_806CD424(s16 arg0, f32 arg1, f32 arg2) {
    f32 vA;
    f32 vB;
    f32 cur;
    f32 tgt;
    f32 dist;
    f32 rate;
    f32 lim1;
    f32 lim2;
    f32 f;
    s16 d;
    s16 prev;
    s16 wrap;

    if (G03_A->unkB8 == 0.0f) {
        G03_A->unkEE = arg0;
    }
    prev = G03_A->unkEE;
    f = 0.0f;
    if (G03_A->unk6A & 1) {
        rate = G03_P->unk2C * (G03_P->unk26 * 3 + 100) / 400.0f;
        if (G03_P->unk28 != 0) {
            d = (arg0 - prev) & 0xFFF;
            wrap = d;
            if (d > 0x800) {
                wrap = 0x1000 - d;
            }
            f = G03_P->unk26 * ((f32)wrap / 2048) / 100.0f;
        }
    } else {
        rate = G03_P->unk2C;
    }
    cur = func_80612794(prev) * G03_A->unkB8;
    tgt = func_80612794(arg0) * arg1;
    if (f != 0.0f) {
        if (cur < tgt) {
            dist = tgt - cur;
        } else {
            dist = -(tgt - cur);
        }
        dist = dist * ((G03_P->unk26 * 63.0 + 100.0) / 6400.0);
        lim1 = (dist - rate) * f + rate;
    } else {
        if (0.0f < func_80612794(arg0) * rate) {
            lim1 = func_80612794(arg0) * rate;
        } else {
            lim1 = -(func_80612794(arg0) * rate);
        }
        if (0.0f < func_80612790(arg0) * rate) {
            lim2 = func_80612790(arg0) * rate;
        } else {
            lim2 = -(func_80612790(arg0) * rate);
        }
    }
    vA = func_806CD898(cur, tgt, lim1);
    cur = func_80612790(prev) * G03_A->unkB8;
    tgt = func_80612790(arg0) * arg1;
    if (f != 0.0f) {
        if (cur < tgt) {
            dist = tgt - cur;
        } else {
            dist = -(tgt - cur);
        }
        dist = dist * ((G03_P->unk26 * 63.0 + 100.0) / 6400.0);
        lim2 = (dist - rate) * f + rate;
    }
    vB = func_806CD898(cur, tgt, lim2);
    G03_A->unkB8 = sqrtf(vA * vA + vB * vB);
    if (arg2 < G03_A->unkB8) {
        G03_A->unkB8 = arg2;
    }
    if (G03_A->unkB8 != 0.0) {
        G03_A->unkEE = func_80611BB4(vA, vB) * 4096.0 / 6.2831855f;
    }
}

f32 func_806CD898(f32 arg0, f32 arg1, f32 arg2) {
    if (arg0 < arg1) {
        arg0 += arg2;
        if (arg1 < arg0) {
            arg0 = arg1;
        }
    } else {
        arg0 -= arg2;
        if (arg0 < arg1) {
            arg0 = arg1;
        }
    }
    return arg0;
}

void func_806CD8EC(void) {
    f32 sub;

    if ((G03_A->unk6A & 1) && !(G03_A->unk6A & 0x200)) {
        sub = G03_P->unk30 * (G03_P->unk26 * 15 + 100) / 1600.0f;
    } else {
        sub = G03_P->unk30;
    }
    G03_A->unkB8 -= sub;
    if (G03_A->unkB8 < 0.0f) {
        G03_A->unkB8 = 0.0f;
    }
}


s16 func_806CD988(Actor *arg0) {
    s16 ret = D_80750B54[arg0->unk154][0];
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD9A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CDD24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE4E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE7A0.s")

typedef struct G05PlayerView {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[0x4C - 2];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ u8 pad4E[0x78 - 0x4E];
    /* 0x078 */ f32 unk78;
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ u8 pad82[2];
    /* 0x084 */ u32 unk84;
    /* 0x088 */ u8 pad88[0xD0 - 0x88];
    /* 0x0D0 */ u32 unkD0;
    /* 0x0D4 */ u8 padD4[0x1AC - 0xD4];
    /* 0x1AC */ Actor *unk1AC;
    /* 0x1B0 */ Actor *unk1B0;
    /* 0x1B4 */ u8 pad1B4[4];
    /* 0x1B8 */ u16 unk1B8;
    /* 0x1BA */ u8 pad1BA[2];
    /* 0x1BC */ f32 unk1BC;
} G05PlayerView;

#define G05_P ((G05PlayerView *)D_807FD580)

typedef struct G05Model {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} G05Model;

s32 func_806CEB44(f32, f32);
void func_806D03BC(void);
void func_80614EBC(Actor *, s32);
void func_80614D00(Actor *, f32, f32);

s16 func_806CE928(Actor *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 sp26;
    s16 sp24;
    f32 scale;
    s16 sp1E;
    s16 sel;

    sp26 = arg0->unk154;
    sp1E = G05_P->unk4C;
    sel = func_806CEB44(arg1, arg2);
    if (sp1E < 0) {
        func_806D03BC();
    }
    if (sp1E != sel) {
        switch (sel) {
            case 0:
                switch ((u32)G05_P->unk1AC->unk58) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x55:
                    case 0x82:
                        func_80614EBC(D_807FBB48, 0x1C9);
                        break;
                    default:
                        func_80614E78(arg0, 0x2E);
                        break;
                }
                G05_P->unk4C = 0;
                sp26 = 0x48;
                break;
            case 1:
                switch ((u32)G05_P->unk1AC->unk58) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x43:
                    case 0x55:
                    case 0x82:
                        func_80614EBC(D_807FBB48, 0x1CA);
                        break;
                    default:
                        func_80614E78(arg0, 0x2F);
                        break;
                }
                G05_P->unk4C = 1;
                sp26 = 0x49;
                break;
        }
    }
    if (G05_P->unk4C > 0) {
        scale = arg0->unkB8 * 0.025;
        scale = scale * 0.75 + 0.25;
        if ((*(G05Model **)arg0->unk4)->unk24 != 0.0f) {
            func_80614D00(arg0, scale, 2.0f);
        }
    }
    return sp26;
}

#ifdef NON_MATCHING
extern f32 D_807532B8[];

s32 func_806CEB44(f32 arg0, f32 arg1) {
    s32 ret;

    switch (G05_P->unk4C) {
        case 0:
            ret = 0;
            if (arg1 != 0.0f) {
                return 1;
            }
            break;
        case 1:
            ret = 1;
            if (arg1 == 0.0f && arg0 < D_807532B8[D_807FD584]) {
                return 0;
            }
            break;
        default:
            ret = 1;
            if (arg0 < D_807532B8[D_807FD584]) {
                return 0;
            }
            break;
    }
    return ret;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEB44.s")
#endif

extern s16 D_807532A8[];
f32 mathAngleBetweenPointsDeg(s16, s16, s16, s16);

void func_806CEC04(Actor *arg0) {
    f32 radius;
    f32 ang;
    f32 sp40[4][4];
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    s32 div = 15;

    switch ((u32)arg0->unk58) {
        case 0x3D:
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x55:
        case 0x82:
            radius = 30.0f;
            break;
        default:
            radius = D_807532A8[D_807FD584];
            break;
    }
    if (D_807FD580->unk1F0 & 0x01000000) {
        ang = D_807FBB40->unkE6 * 0x168 / 4096;
    } else {
        ang = mathAngleBetweenPointsDeg(arg0->unk7C, arg0->unk84, D_807FBB40->unk7C, D_807FBB40->unk84);
        ang = 360.0 - ang;
    }
    G05_P->unk80 = ang * 4095.0 / 360.0;
    guRotateF(sp40, ang, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp40, 0.0f, 0.0f, radius, &sp3C, &sp38, &sp34);
    G05_P->unk78 = ((arg0->unk7C - sp3C) - D_807FBB40->unk7C) / (f32)div;
    G05_P->unk7C = ((arg0->unk84 - sp34) - D_807FBB40->unk84) / (f32)div;
}

typedef struct G05Node {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ Actor *unkC;
    /* 0x10 */ Actor *unk10;
} G05Node;

void func_806CEFBC();
void *func_80610FE8(s32);
void actorRegisterGlobalCallback(void *);

void func_806CEE64(f32 arg0) {
    G05Node *node;

    if (G05_P->unk1AC != NULL) {
        node = func_80610FE8(0x14);
        node->unk0 = func_806CEFBC;
        node->unk8 = arg0;
        node->unkC = D_807FBB40;
        node->unk10 = G05_P->unk1AC;
        node->unk4 = 0;
        actorRegisterGlobalCallback(node);
    }
}

s32 func_806CF2EC(s32 *, s32 *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);

void func_806CEED8(void) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 dist;
    f32 sp28;
    s32 sp24;
    s32 sp20;

    func_806CF2EC(&sp24, &sp20);
    actorGetNodePos(D_807FBB40, sp24, &sp40, &sp38, &sp30);
    actorGetNodePos(D_807FBB40, sp20, &sp44, &sp3C, &sp34);
    sp28 = sp3C - sp38;
    dist = sqrtf((sp34 - sp30) * (sp34 - sp30) + (sp44 - sp40) * (sp44 - sp40));
    G05_P->unk1BC = 0.0 - func_80611BB4(sp28, dist) * 57.29577637f + 270.0;
}

#ifdef NON_MATCHING
typedef struct G05CbArg {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ Actor *unk8;
} G05CbArg;

void func_8067A70C(Actor *, Actor *, f32, f32, f32, s32, s32);

void func_806CEFBC(G05CbArg *arg0) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp34;
    s32 sp30;

    func_806CF2EC(&sp34, &sp30);
    actorGetNodePos(arg0->unk4, sp34, &sp60, &sp58, &sp50);
    actorGetNodePos(arg0->unk4, sp30, &sp64, &sp5C, &sp54);
    sp4C = (sp64 + sp60) / 2;
    sp48 = (sp5C + sp58) / 2;
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = (sp48 - arg0->unk8->unk80) * arg0->unk0 + arg0->unk8->unk80;
    sp38 = (sp44 - arg0->unk8->unk84) * arg0->unk0 + arg0->unk8->unk84;
    func_8067A70C(arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEFBC.s")
#endif

typedef struct G05Node2 {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ Actor *unk8;
    /* 0x0C */ Actor *unkC;
    /* 0x10 */ s32 unk10;
} G05Node2;

void func_806CF138();

void func_806CF0D0(void) {
    G05Node2 *node;

    if (G05_P->unk1AC != NULL) {
        node = func_80610FE8(0x14);
        node->unk0 = func_806CF138;
        node->unk8 = D_807FBB40;
        node->unkC = G05_P->unk1AC;
        node->unk4 = 0;
        actorRegisterGlobalCallback(node);
    }
}

#ifdef NON_MATCHING
typedef struct G05CbArg2 {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
} G05CbArg2;

f32 func_80611850(f32);
f32 func_806118FC(f32);
void func_8067AA58(Actor *, Actor *, f32, f32);

void func_806CF138(G05CbArg2 *arg0) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    s32 sp30;
    s32 sp2C;

    func_806CF2EC(&sp30, &sp2C);
    actorGetNodePos(arg0->unk0, sp30, &sp70, &sp68, &sp60);
    actorGetNodePos(arg0->unk0, sp2C, &sp74, &sp6C, &sp64);
    sp5C = sp6C - sp68;
    sp58 = sqrtf((sp64 - sp60) * (sp64 - sp60) + ((sp74 - sp70) * (sp74 - sp70) + sp5C * sp5C));
    sp54 = func_806118FC(sp5C / sp58) * 57.29577637f;
    sp48 = func_80612794(arg0->unk0->unkE6) * 50.0f;
    sp4C = func_80612790(arg0->unk0->unkE6) * 50.0f;
    sp44 = sp64 - sp60;
    sp40 = sp74 - sp70;
    sp3C = sp44 * sp4C + sp48 * sp40;
    sp38 = sqrtf(sp4C * sp4C + sp48 * sp48);
    sp34 = sqrtf(sp44 * sp44 + sp40 * sp40);
    func_8067AA58(arg0->unk0, arg0->unk4, sp54, 90.0 - func_80611850(sp3C / (sp38 * sp34)) * 57.29577637f);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF138.s")
#endif

s32 func_806CF2EC(s32 *arg0, s32 *arg1) {
    s32 ret = 0;

    if (D_807FBB40->unk58 == 6) {
        switch (G05_P->unk1B8) {
            case 0x82:
                *arg0 = 0x13;
                *arg1 = 0x14;
                ret = 1;
                break;
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x55:
                *arg0 = 0x12;
                *arg1 = 0x11;
                ret = 1;
                break;
                return ret;
        }
    }
    if (ret == 0) {
        *arg0 = 2;
        *arg1 = 3;
    }
}

extern s32 D_80753428[];
extern f32 D_8075340C[];
void func_8067A784(Actor *, Actor *, s16, s32, s32);

void func_806CF398(Actor *arg0) {
    G05PlayerView *p;

    if (arg0->unk5C & 1) {
        p = arg0->unk174;
        if (p->unk1AC != NULL) {
            func_8067A784(D_807FBB40, p->unk1AC, D_807FBB48->unkE6, D_80753428[D_807FD584], (s32)D_8075340C[D_807FD584]);
            p->unk1AC = NULL;
            p->unk1B0 = NULL;
        }
    }
}

void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);

void func_806CF42C(Actor *arg0) {
    G05PlayerView *p;

    if (arg0->unk5C & 1) {
        p = arg0->unk174;
        if (p->unk1AC != NULL) {
            actorAppendCallback(p->unk1AC, (s32)arg0, 8, 0, 0, NULL);
        } else if (p->unk1B0 != NULL) {
            actorAppendCallback(p->unk1B0, (s32)arg0, 8, 0, 0, NULL);
        }
        p->unk1AC = NULL;
        p->unk1B0 = NULL;
    }
}

typedef struct G05Slot {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad1[3];
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} G05Slot;

#define G05_SLOTS ((G05Slot *)D_807FC924)

void func_806CFF9C(Actor *);

void func_806CF4B8(Actor *arg0) {
    s32 i;
    G05PlayerView *p;

    for (i = 0; i < D_807FC928; i++) {
        if (G05_SLOTS[i].unk0 != 0) {
            p = G05_SLOTS[i].unk4->unk174;
            if ((arg0 == p->unk1AC && p->unk1AC != NULL) || (arg0 == p->unk1B0 && p->unk1B0 != NULL)) {
                p->unk1AC = NULL;
                p->unk1B0 = NULL;
                func_806CFF9C(G05_SLOTS[i].unk4);
            }
        }
    }
}

extern u8 D_8074E77C[];
extern u8 D_80750AD0;
extern u8 D_8071FC40;
void func_80718BF4(void);
void animSetSpeed(void *, s32, f32);
void animSetLoopMode(void *, s32, s32);
void animSetDirection(void *, s32, s32);
void animResetEndFrame(void *, s32);
void animSetStartFrame(void *, s32, s32);
void animSetLoopLimit(void *, s32, s32);
void animSetFrameAndSubframe(void *, s32, s16, f32);
s32 func_8072881C(s32, void *);
u32 func_806119A0(void);
void func_8071498C(void *);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714C08(void *, f32, void *, s32, s32);

void func_806CF580(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        G05_P->unk84 = D_8076A064;
        G05_P->unkD0 = D_8076A064;
    }
    if (D_8074E77C[D_807FC929] == 1) {
        if (D_807FBB40->unk154 == 0x36 && G05_P->unk0 != 0x36) {
            animSetFrameAndSubframe(D_807FBB40, 1, 0, 6.0f);
        }
        if (D_807FBB40->unk154 == 0x36) {
            animSetSpeed(D_807FBB40, 0, 0.5f);
            animSetLoopMode(D_807FBB40, 0, 0);
            animSetDirection(D_807FBB40, 0, 0);
            animResetEndFrame(D_807FBB40, 0);
            animSetStartFrame(D_807FBB40, 0, 4);
            animSetLoopLimit(D_807FBB40, 0, 2);
            animSetSpeed(D_807FBB40, 1, 0.5f);
            animSetLoopMode(D_807FBB40, 1, 0);
            animSetDirection(D_807FBB40, 1, 0);
            animResetEndFrame(D_807FBB40, 1);
            animSetStartFrame(D_807FBB40, 1, 4);
            animSetLoopLimit(D_807FBB40, 1, 2);
        }
        if (D_807FBB40->unk154 != 0x36) {
            if (G05_P->unk0 == 0x36) {
                G05_P->unk84 = 0;
            }
        }
    }
    if (D_807FBB40->unk154 != 0x36 && func_8072881C(0, &G05_P->unk84) != 0 &&
        (D_8074E77C[D_807FC929] == 1 || (D_807FC928 == 1 && D_8074E77C[D_807FC929] == 3))) {
        func_8072881C(0x81, &G05_P->unk84);
    }
    if ((D_807FBB40->unk154 == 0x4F || D_807FBB40->unk154 == 0x7F) && D_80750AD0 == 0 &&
        (u32)(G05_P->unkD0 + 9) < (u32)D_8076A064 && func_806119A0() % 2500 / 200 == 0) {
        func_8071498C(func_80718BF4);
        func_807149B8(1);
        func_807149FC(-1);
        func_80714C08(&D_8071FC40, 0, D_807FBB40, 4, 0);
        G05_P->unkD0 = D_8076A064;
    }
}

void func_80714998(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
extern s32 D_8071FB08;
extern s32 func_80716FB4;

void func_806CF878(void) {
    if (!(D_8076A064 & 3) && G02_A->unk155 >= 5 && G03_A->unkC0 > 30.0f) {
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(&func_80716FB4);
        func_80714CC0(&D_8071FB08, 0.8f, G03_A->unk7C, G03_A->unk80, G03_A->unk84);
    }
}

void func_80714950(s32);
extern s32 D_8071FF40;
extern s32 func_807195D4;

void func_806CF918(void) {
    s32 i;

    for (i = 0; i != 0xC8; i += 0x28) {
        func_8071498C(&func_807195D4);
        func_807149B8(1);
        func_80714950(i);
        func_807149FC(0x45);
        func_80714C08(&D_8071FF40, 0.05f, D_807FBB40, 6, 2);
    }
}

typedef struct G06PlayerView {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x20];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A[2];
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 pad4E[2];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[0x36];
    /* 0x88 */ Actor *unk88;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[0xE8 - 0x8D];
    /* 0xE8 */ u8 unkE8;
    /* 0xE9 */ u8 padE9[0xF0 - 0xE9];
    /* 0xF0 */ f32 unkF0;
    /* 0xF4 */ u8 padF4[0x10C - 0xF4];
    /* 0x10C */ u8 unk10C;
    /* 0x10D */ u8 pad10D[0x1AC - 0x10D];
    /* 0x1AC */ s32 unk1AC;
    /* 0x1B0 */ u8 pad1B0[0x1F0 - 0x1B0];
    /* 0x1F0 */ s32 unk1F0;
} G06PlayerView;

#define G06_P ((G06PlayerView *)D_807FD580)

u8 func_806CFC90(Actor *, f32 *, u8, f32);
s32 func_806725A0(Actor *, s16);
s32 func_80666AEC(void);
void collisionGetCoords(void *, s16 *);
extern s32 D_8076A0A8;
extern f32 D_80753E10[];
extern s16 D_80753E00[];

void func_806CF9CC(void) {
    f32 sp3C;
    u8 sp3B;
    s16 sp38;
    s16 sp36;
    u8 notWall;
    u8 hit;
    u8 flag;
    s32 pad[2];

    if (!(D_807FBB64 & 0x20000) && D_807FBB40->unkFC != 0 && G06_P->unk8C == 0 && !(D_807FBB40->unk6A & 1) && G06_P->unkE8 != 0) {
        flag = (D_8076A0A8 == 0x53 || D_8076A0A8 == 0xC5) ? 1 : 0;
        notWall = func_806725A0(D_807FBB40, D_807FBB40->unkE6) == 0;
        if (notWall || !(D_80753E10[D_807FD584] < D_807FBB40->unkB8) || flag != 0) {
            sp3B = func_806CFC90(D_807FBB40, &sp3C, notWall, flag ? 30.0 : 15.0);
            collisionGetCoords(&sp38, &sp36);
            hit = 0;
            if (sp3B != 0 && G03_A->unkC0 < 0.0 && sp36 >= 0x385) {
                hit = 0;
                if (func_80666AEC() != 0) {
                    if (D_807FBB40->unk80 - D_807FBB40->unkA4 > 15.0f) {
                        if (flag != 0) {
                            if (D_80753E00[D_807FD584] + D_807FBB40->unk80 < sp3C + 15.0f && sp3C - D_80753E00[D_807FD584] - D_807FBB40->unk80 < 80.0f) {
                                hit = 1;
                            }
                        } else {
                            if (D_80753E00[D_807FD584] + D_807FBB40->unk80 < sp3C - 5.0f && sp3C - D_80753E00[D_807FD584] - D_807FBB40->unk80 < 15.0f) {
                                hit = 1;
                            }
                        }
                    }
                }
            }
            if (hit != 0 && func_806EB0C0(0xA, NULL, D_807FC929) != 0) {
                G06_P->unkF0 = sp3C;
            }
        }
    }
}

u8 collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
u8 func_80666AE0(void);

u8 func_806CFC90(Actor *arg0, f32 *arg1, u8 arg2, f32 arg3) {
    f32 dx;
    f32 dz;
    s16 angle;
    u8 ret;

    angle = arg0->unkE6;
    if (!arg2) {
        angle = (angle + 0x800) & 0xFFF;
    }
    dx = func_80612794(angle) * arg3;
    dz = func_80612790(angle) * arg3;
    ret = collisionCheckActorFloor(arg0, arg0->unk7C + dx, arg0->unk80 + 30.0f, arg0->unk84 + dz, arg1);
    ((G02ActorView *)arg0)->unk78 = func_80666AE0();
    return ret;
}

void func_806CFE7C(void);

void func_806CFD68(void) {
    if (G03_A->unkC0 < 0.0f) {
        func_806CFE7C();
    }
}

extern f32 D_80753700[];

void func_806CFDA8(void) {
    if (G03_A->unkC0 < 0.0f) {
        ((G03ActorView *)D_807FBB40)->unkC4 = D_80753700[D_807FD584];
    }
}

extern f32 D_80753658[];

void func_806CFDEC(void) {
    if (G03_A->unkC0 < 0.0f) {
        ((G03ActorView *)D_807FBB40)->unkC4 = D_80753658[D_807FD584];
    }
}

extern f32 D_80753754[];

void func_806CFE30(void) {
    if (G03_A->unkC0 < 0.0f) {
        ((G03ActorView *)D_807FBB48)->unkC4 = D_80753754[D_807FD584];
    }
}

extern f32 D_80753578[];

void func_806CFE7C(void) {
    ((G03ActorView *)D_807FBB48)->unkC4 = D_80753578[D_807FD584];
}

extern f32 D_80753594[];

void func_806CFEA4(void) {
    ((G03ActorView *)D_807FBB48)->unkC4 = D_80753594[D_807FD584];
}

extern f32 D_807535B0[];

void func_806CFECC(void) {
    ((G03ActorView *)D_807FBB48)->unkC4 = D_807535B0[D_807FD584];
}

extern f32 D_807536E4[];

void func_806CFEF4(void) {
    ((G03ActorView *)D_807FBB48)->unkC4 = D_807536E4[D_807FD584];
}

void func_806CFF1C(Actor *arg0) {
    G03_A->unkC0 = 0.0f;
    func_80614E78(arg0, 0x1B);
    func_80614D90(arg0);
    D_807FBB40->unk9C = D_807FBB40->unk80;
    if (G06_P->unk8C) {
        arg0->unk154 = 0x1F;
        arg0->unk155[0] = 0;
    } else {
        arg0->unk154 = 0x1E;
        arg0->unk155[0] = 0;
    }
}

s8 func_806CDD24(Actor *, f32, f32, s32);
s8 func_806CE174(Actor *, f32, f32, s32);
s8 func_806CE4E4(Actor *, f32, f32, s32);
void func_806C8D20(Actor *);
void func_806D0150(Actor *);

void func_806CFF9C(Actor *arg0) {
    G06PlayerView *p = arg0->unk174;
    u8 temp;

    arg0->unk6A &= ~0x20;
    p->unk4C = -1;
    p->unk10C = 0;
    if (arg0->unk144 == 1) {
        func_806C8D20(arg0);
    }
    if (D_807FBB64 & 0x80000) {
        if (p->unk88 != NULL && p->unk88->unk58 == 0x1D) {
            func_806D0150(arg0);
            return;
        }
    }
    if (D_8074E77C[D_807FC929] == 7) {
        arg0->unk154 = 0x7E;
        arg0->unk155[0] = 0;
        return;
    }
    if ((p->unk1F0 & 0x20) && D_807FC928 == 1) {
        temp = func_806CE4E4(arg0, arg0->unkB8, p->unk4, 1);
        arg0->unk154 = temp;
        arg0->unk155[0] = 0;
        if (temp == 0x3F) {
            arg0->unk155[0] = 1;
        }
    } else if (p->unk1AC != 0) {
        arg0->unk154 = func_806CE928(arg0, arg0->unkB8, p->unk4, 1);
        arg0->unk155[0] = 0;
    } else if (p->unk8C != 0) {
        temp = func_806CE174(arg0, arg0->unkB8, p->unk4, 1);
        if (arg0->unk154 != 2) {
            arg0->unk154 = temp;
            arg0->unk155[0] = 0;
        }
    } else {
        temp = func_806CDD24(arg0, arg0->unkB8, p->unk4, 1);
        if (arg0->unk154 != 2) {
            arg0->unk154 = temp;
            arg0->unk155[0] = 0;
        }
    }
}

void func_806D0150(Actor *arg0) {
    arg0->unk6A &= ~0x20;
    G06_P->unk4C = -1;
    G06_P->unk10C = 0;
    func_80614E78(arg0, 0x7A);
    arg0->unk154 = 7;
    arg0->unk155[0] = 0;
}

extern s16 D_80753328[];
extern f32 D_807532F0[];
extern f32 D_8075330C[];
extern f32 D_807532B8[];
extern f32 D_807532D4[];

void func_806D01AC(void) {
    G06_P->unk48 = D_80753328[D_807FD584];
    G06_P->unk2C = D_807532F0[D_807FD584];
    G06_P->unk30 = D_8075330C[D_807FD584];
    G06_P->unk34 = D_807532B8[D_807FD584];
    G06_P->unk38 = D_807532D4[D_807FD584];
}

extern f32 D_80753170[];
extern f32 D_80753338[];
extern f32 D_80753218[];
extern f32 D_807531FC[];
extern u8 D_807463B8;

void func_806D024C(void) {
    G06_P->unk48 = D_8075326C[D_807FD584];
    G06_P->unk2C = D_80753234[D_807FD584];
    G06_P->unk30 = D_80753250[D_807FD584];
    G06_P->unk34 = D_80753170[D_807FD584];
    if (G06_P->unk8C != 0) {
        G06_P->unk38 = D_80753338[D_807FD584];
        return;
    }
    if ((D_807FD580->unk1F0 & 0x20) || D_807463B8 == 3) {
        if (D_8076A0A8 == 0x30) {
            G06_P->unk38 = 200.0f;
            return;
        }
        G06_P->unk38 = D_80753218[D_807FD584];
        return;
    }
    G06_P->unk38 = D_807531FC[D_807FD584];
}

void func_806D0378(void) {
    ((G03ActorView *)D_807FBB48)->unkC4 = D_80753578[D_807FD584];
    G06_P->unk50 = 0;
    G06_P->unk28 = 1;
}

void func_806D024C(void);

void func_806D03BC(void) {
    if (G06_P->unk1AC != 0) {
        func_806D01AC();
    } else {
        func_806D024C();
    }
    func_806D0378();
}

void func_806D0408(void) {
    func_806D024C();
    func_806D0378();
}

extern f32 D_80750FA8;

void func_806D0430(f32 arg0) {
    if (arg0 != 0.0f) {
        D_80750FA8 = arg0;
    } else {
        D_80750FA8 = 0.3f;
    }
}

typedef struct G07PlayerSlot {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x2B8];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G07PlayerSlot;

typedef struct G07StateB {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ void *unk104;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1C0 - 0x1A5];
    /* 0x1C0 */ f32 unk1C0[3];
    /* 0x1CC */ f32 unk1CC[3];
    /* 0x1D8 */ f32 unk1D8;
    /* 0x1DC */ f32 unk1DC;
    /* 0x1E0 */ f32 unk1E0;
    /* 0x1E4 */ s32 unk1E4;
} G07StateB;

void func_8062217C(void *, s32);

void func_806D0468(Actor *arg0, u8 arg1) {
    G07StateB *state = arg0->unk174;
    u8 slot = state->unk1A4;
    s32 i;
    f32 diff;
    f32 temp;

    state->unk1DC = 0.4f;
    state->unk1D8 = 0.004f;
    switch (arg1) {
        case 0:
            state->unk1C0[0] = 0.05f;
            state->unk1C0[1] = 0.05f;
            state->unk1C0[2] = 0.05f;
            break;
        case 2:
            state->unk1C0[0] = D_80750FA8;
            state->unk1C0[1] = D_80750FA8;
            state->unk1C0[2] = D_80750FA8;
            break;
        default:
            state->unk1C0[0] = 0.15f;
            state->unk1C0[1] = 0.15f;
            state->unk1C0[2] = 0.15f;
            if (((G07PlayerSlot *)D_807FC924)[slot].unk2C0 == 0) {
                state->unk1DC = 0.05f;
                state->unk1D8 = 0.001f;
            }
            break;
    }
    if (arg1 != 1) {
        if (D_807FC928 == 1) {
            for (i = 0; i < 3; i++) {
                state->unk1CC[i] = state->unk1C0[i];
                (&arg0->unk4->unk34)[i] = state->unk1C0[i];
            }
        }
    }
    ((G07PlayerSlot *)D_807FC924)[slot].unk2C0 = arg1;
    ((G07PlayerSlot *)D_807FC924)[slot].pad2C1[0] = 1;
    state->unk1E4 = 0;
    if (arg1 == 1 || D_807FC928 >= 2) {
        if (state->unk1CC[0] < state->unk1C0[0]) {
            diff = state->unk1C0[0] - state->unk1CC[0];
        } else {
            diff = -(state->unk1C0[0] - state->unk1CC[0]);
        }
        temp = diff / state->unk1D8;
        if (temp != 0.0f) {
            state->unk1E0 = state->unk1DC / temp;
        } else {
            state->unk1E0 = 99999.0f;
        }
    }
    func_8062217C(state->unk104, 2);
}

#define G07_P ((G07StateB *)D_807FD580)

f32 func_80612D1C(f32);

void func_806D06A0(void) {
    if (G07_P->unk1CC[0] < G07_P->unk1C0[0]) {
        G07_P->unk1CC[0] = G07_P->unk1CC[0] + G07_P->unk1D8;
        G07_P->unk1CC[1] = G07_P->unk1CC[1] + G07_P->unk1D8;
        G07_P->unk1CC[2] = G07_P->unk1CC[2] + G07_P->unk1D8;
        if (G07_P->unk1C0[0] < G07_P->unk1CC[0]) {
            G07_P->unk1CC[0] = G07_P->unk1C0[0];
            G07_P->unk1CC[1] = G07_P->unk1C0[1];
            G07_P->unk1CC[2] = G07_P->unk1C0[2];
        }
    } else {
        G07_P->unk1CC[0] = G07_P->unk1CC[0] - G07_P->unk1D8;
        G07_P->unk1CC[1] = G07_P->unk1CC[1] - G07_P->unk1D8;
        G07_P->unk1CC[2] = G07_P->unk1CC[2] - G07_P->unk1D8;
        if (G07_P->unk1CC[0] < G07_P->unk1C0[0]) {
            G07_P->unk1CC[0] = G07_P->unk1C0[0];
            G07_P->unk1CC[1] = G07_P->unk1C0[1];
            G07_P->unk1CC[2] = G07_P->unk1C0[2];
        }
    }
    if (G07_P->unk1CC[0] == G07_P->unk1C0[0]) {
        D_807FBB40->unk4->unk34 = G07_P->unk1CC[0];
        D_807FBB40->unk4->unk38 = G07_P->unk1CC[1];
        D_807FBB40->unk4->unk3C = G07_P->unk1CC[2];
        return;
    }
    D_807FBB40->unk4->unk34 = G07_P->unk1CC[0] + func_80612D1C(G07_P->unk1E4 * 0.11) * G07_P->unk1DC;
    D_807FBB40->unk4->unk38 = G07_P->unk1CC[1] + func_80612D1C(G07_P->unk1E4 * 0.2352) * G07_P->unk1DC;
    D_807FBB40->unk4->unk3C = G07_P->unk1CC[2] + func_80612D1C(G07_P->unk1E4 * 0.176) * G07_P->unk1DC;
    G07_P->unk1DC = G07_P->unk1DC - G07_P->unk1E0;
    if (G07_P->unk1DC < 0.0) {
        G07_P->unk1DC = 0.0f;
    }
    G07_P->unk1E4 = G07_P->unk1E4 + 1;
}

s32 func_806D0964(s32 arg0, u8 arg1) {
    s16 type = *(s16 *)((u8 *)((G07PlayerSlot *)D_807FC924)[arg1].unk4 + 0x5A);

    if (type != 6) {
        if (type == 8) {
            if (arg0 & 2) {
                return 1;
            }
        }
    } else {
        if ((arg0 & 1) && ((G07PlayerSlot *)D_807FC924)[arg1].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

extern s32 D_807FBB68;
s32 collisionGetHitStatus();

typedef struct G07ActorD1 {
    /* 0x00 */ u8 pad0[0xD1];
    /* 0xD1 */ u8 unkD1;
} G07ActorD1;

void func_806D09E8(Actor *arg0) {
    u8 id;

    if (arg0->unk58 == 4) {
        id = arg0->unk154;
        if (id == 0x3F || id == 0x40) {
            if (!(D_807FBB68 & 0x40)) {
                if (collisionGetHitStatus() == 0) {
                    ((G07ActorD1 *)arg0)->unkD1 = 0x10;
                }
            }
        }
    }
}

void func_806D0A54(Actor *arg0, s32 arg1, s32 arg2) {
    if (arg1) {
        arg0->unk60 |= 4;
    } else {
        arg0->unk60 &= ~4;
    }
}

typedef struct G07TargetRef {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} G07TargetRef;

typedef struct G07Target {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ G07TargetRef *unk4;
    /* 0x08 */ u8 pad8[0x4C];
    /* 0x54 */ s32 unk54;
} G07Target;

typedef struct G07StateA {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ G07Target *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ f32 unk10;
} G07StateA;

typedef struct G07ActorA {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x90];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x13];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[6];
    /* 0x170 */ s32 pad170;
    /* 0x174 */ G07StateA *unk174;
} G07ActorA;

#define G07_A ((G07ActorA *)D_807FBB40)

void actorDespawn(Actor *);
s32 actorTableContains(void *);
s32 func_80611A44();
void func_8067B238(void *, void *, s32, void *);
void func_806319C4(Actor *, s32);

void func_806D0A84(void) {
    G07StateA *state = G07_A->unk174;
    G07Target *target = state->unk4;
    f32 speed;
    s32 pad[1];
    f32 temp;

    if (!(G07_A->unk60 & 0x10)) {
        func_80614EBC(D_807FBB40, state->unk0);
        G07_A->unk60 |= 0x400;
        G07_A->unk168 = (func_80611A44() >> 15) % 4096;
    }
    speed = (G07_A->unk4 != NULL ? G07_A->unk4->unk38 : 0.15f) * 6.66666667;
    if (actorTableContains(target) == 0 || target->unk54 != state->unk8) {
        actorDespawn(D_807FBB40);
        return;
    }
    switch (G07_A->unk154) {
        case 0:
            if (target->unk4->unk64 != state->unkC) {
                func_80614EBC(D_807FBB40, state->unk2);
            } else {
                func_8067B238(D_807FBB40, target, *(s32 *)&G07_A->unk4->unk34, state);
                G07_A->unk80 += state->unk10;
            }
            break;
        case 1:
            G07_A->unkC0 = G07_A->unkC0 + 0.2;
            G07_A->unk80 = G07_A->unk80 + speed * G07_A->unkC0;
            break;
        case 2:
            G07_A->unkC0 = G07_A->unkC0 - 0.2;
            G07_A->unk80 = G07_A->unk80 + speed * G07_A->unkC0;
            break;
        case 3:
            G07_A->unk168 += 0x28;
            G07_A->unk168 &= 0xFFF;
            if (G07_A->unkB8 < 1.2) {
                G07_A->unkB8 = G07_A->unkB8 + 0.15;
            }
            temp = G07_A->unkB8 * speed;
            G07_A->unk7C += temp * func_80612794(G07_A->unk168);
            G07_A->unk84 += temp * func_80612790(G07_A->unk168);
            if (G07_A->unkC0 < 2.5) {
                G07_A->unkC0 = G07_A->unkC0 + 0.2;
            }
            G07_A->unk80 = G07_A->unk80 + speed * G07_A->unkC0;
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

#ifdef NON_MATCHING
typedef struct G07StateView {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} G07StateView;

u8 func_806D0DE4(Actor *arg0, Actor *arg1) {
    s32 var_a0;
    s32 var_a2;
    u16 temp_a1;
    u16 temp_t0;
    u8 var_v0;
    u8 var_v1;

    var_v0 = 1;
    var_v1 = 1;
    var_a2 = 1;
    if ((D_807FC928 < 2) || (temp_a1 = arg0->unk5C, ((temp_a1 & 4) != 0)) || (temp_t0 = arg1->unk5C, ((temp_t0 & 4) != 0))) {
        return 0;
    }
    if (temp_a1 & 1) {
        var_v0 = ((G07PlayerSlot *)D_807FC924)[((G07StateView *)arg0->unk174)->unk1A4].unk2C0;
    }
    if (temp_t0 & 1) {
        var_v1 = ((G07PlayerSlot *)D_807FC924)[((G07StateView *)arg1->unk174)->unk1A4].unk2C0;
        var_a2 = arg1->unk154 != 0x7C;
    }
    var_a0 = var_v0 < var_v1;
    if (var_a0 != 0) {
        var_a0 = var_a2 != 0;
    }
    return var_a0 & 0xFF;
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0DE4.s")
#endif

extern s16 D_8075388C[];
extern s16 D_807538C8[];
extern s16 D_8075387C[];
extern s16 D_807538B8[];

void func_806D0EBC(s32 arg0) {
    f32 height;
    f32 limit;
    s32 pad[1];
    u8 type;

    type = ((G07PlayerSlot *)D_807FC924)[D_807FC929].unk2C0;
    if (type == 1) {
        height = D_8075388C[D_807FD584];
    } else {
        height = D_807538C8[D_807FD584];
    }
    if (type == 1) {
        limit = D_8075387C[D_807FD584];
    } else {
        limit = D_807538B8[D_807FD584];
    }
    if (G03_A->unkAC - G03_A->unkA4 < limit) {
        func_806EB0C0(2, NULL, D_807FC929);
        return;
    }
    if (G03_A->unkAC < G03_A->unk80 + height) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x10, 0xFF, 0x7F, 1);
        G03_A->unk80 = G03_A->unkAC - height;
        G03_A->unkC0 = 0.0f;
        func_80614E78(D_807FBB40, 0x3D);
        G06_P->unk30 = D_80753250[D_807FD584];
        D_807FBB40->unk154 = 0x4E;
        G02_A->unk155 = 0;
    }
}

s16 func_806D1080(f32 arg0, f32 arg1) {
    s16 angle = (s32)(func_80611BB4(arg0, arg1) * 4096.0f / 6.2831855f);

    angle -= 0x400;
    return angle & 0xFFF;
}

s32 func_806D10D0(Actor *arg0) {
    s32 ret = 1;

    if (arg0->unk5C & 1) {
        if (D_80750B54[arg0->unk154][0] & 0x400) {
            ret = 0;
        }
    }
    return ret;
}

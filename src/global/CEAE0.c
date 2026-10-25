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

void func_806EB0C0(s32, Actor *, u8);

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE928.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEB44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEC04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEE64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEED8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEFBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF0D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF138.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF2EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF398.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF42C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF4B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF580.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF878.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF918.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF9CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFC90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFD68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFDA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFDEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFE30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFE7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFEA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFECC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFEF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFF1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFF9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0150.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D01AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D024C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0378.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D03BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0408.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0468.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D06A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0964.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D09E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0A54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0A84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0DE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0EBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D1080.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D10D0.s")

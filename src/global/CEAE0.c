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

s32 func_806CA1B4(s32);

#ifdef NON_MATCHING
typedef struct G02PlayerSlot {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} G02PlayerSlot;

extern G02PlayerSlot *D_807FC924;
Actor *func_807270C0(s32, s32);

s32 func_806CA1B4(s32 arg0) {
    s8 idx = G02_P->unk247;
    s32 ret = 1;
    Actor *actor = NULL;

    if (idx >= 0) {
        actor = D_807FC924[idx].unk4;
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC14C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC190.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC284.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC364.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC5DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC638.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC8A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC8B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC8F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC920.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC948.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC970.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCB0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCB94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCC10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCC54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD424.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD898.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD8EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD988.s")

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

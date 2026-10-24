#include "common.h"
#include "actor.h"

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 func_80611BB4(f32, f32);

void func_80699070(s16 *arg0, s16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 dx;
    f32 dz;

    *arg1 = mathAngleBetweenPoints2D(arg2, arg4, arg5, arg7);
    dx = arg5 - arg2;
    dz = arg7 - arg4;
    *arg0 = (s16)(s32)(((f64)func_80611BB4(arg6 - arg3, sqrtf((dx * dx) + (dz * dz))) * 2048.0) / 3.1415927410125732);
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern u8 D_807444FC;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern Gfx D_2000180;
Gfx *renderSetSegment6AndFog(Gfx *, s16, u8);
Gfx *func_80614B34(Gfx *, Actor *);

void func_80699128(Gfx *arg0, Actor *arg1) {
    WRITE_GFX(arg0++, 0xDA380007, osVirtualToPhysical((void *)((u8 *)D_807FC924 + (D_807FC929 * 0x2F0) + (D_807444FC << 6) + 0x88)));
    WRITE_GFX(arg0++, 0xDA380005, osVirtualToPhysical((void *)((u8 *)D_807FC924 + (D_807FC929 * 0x2F0) + (D_807444FC << 6) + 8)));
    WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xD9FDFFFF, 0);
    WRITE_GFX(arg0++, 0xFA0000FF, 0xFFFFFFFF);
    func_80614B34(renderSetSegment6AndFog(arg0, arg1->unk128, 1), arg1);
}

#ifdef NON_MATCHING
typedef struct L1_PlayerState {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ s32 unk88;
    /* 0x08C */ u8 pad8C[0x1A4 - 0x8C];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1EC - 0x1A5];
    /* 0x1EC */ u8 unk1EC;
    /* 0x1ED */ u8 pad1ED[0x1F0 - 0x1ED];
    /* 0x1F0 */ u32 unk1F0;
} L1_PlayerState;

typedef struct L1_Sub174 {
    /* 0x00 */ L1_PlayerState *unk0;
    /* 0x04 */ s16 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u16 unk10;
} L1_Sub174;

typedef struct L1_CamState {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
} L1_CamState;

#define L1_MIN(a, b) (((a) < (b)) ? (a) : (b))

extern Actor *D_807FBB40;
extern s32 D_807FC924;
extern u8 D_807444FC;
extern L1_PlayerState *D_807FD580;

s32 func_806FFF88(void);
void func_80613C48(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void func_807002AC(s16 *, s32 *, f32);
void animSetNodeItem(void *, s32, s16, s32);
void func_806F91B4(s32, u8, s32);
void sfxAllocateChannel(s32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);
void func_80699070(s16 *, s16 *, f32, f32, f32, f32, f32, f32);
s32 func_806EB0C0(s32, s32, s32, void *);
void assetFreeBuffer(s32, s32, s32);
void heapFreeDeferred(Mtx *);
void actorDespawn(Actor *);
void func_806319C4(Actor *, s32);
void func_80699128(Gfx *, Actor *);
void func_806FF628(void);

void func_80699284(void) {
    /* 1-element array: forces the target's spilled-pointer codegen (loads from
       0xEC(sp) with per-block reuse) instead of a callee-saved s1. */
    L1_Sub174 *spEC[1];
    s16 spEA;
    s16 spE8;
    f32 mtx1[4][4];
    f32 mtx2[4][4];
    s16 sp66;
    s16 l1Angle;
    s32 *l1Dest;
    u8 sp5F;
    f32 t;

    sp5F = 0;
    spEC[0] = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        spEC[0]->unk10 = 0x5A;
        D_807FBB40->unk60 |= 0x400;
        D_807FBB40->unk12A = 0x3E8;
        spEC[0]->unk4 = (s16 *)func_806FFF88();
        func_80613C48(D_807FBB40, 0x40B, 0, 0);
        func_80614D00(D_807FBB40, 0.15f, 0);
    }
    D_807FBB40->unk60 &= ~4;
    sp66 = 0x5A - spEC[0]->unk10;
    if (sp66 == 0xD) {
        sfxPlayActorSound(D_807FBB40, 0x222, 0, 0, 0, 0xFF, 1.0f, -1);
    }
    if (sp66 == 0x1B) {
        sfxStopSlotSound(D_807FBB40, 0);
    }
    t = L1_MIN(1.0, ((sp66 - 0x1E) < 0 ? 0 : (sp66 - 0x1E)) / 60.0f * 5.0);
    if (t < 1.0 && D_807FBB40->unk58 != 0xD9) {
        l1Dest = &(&spEC[0]->unk8)[D_807444FC];
        func_807002AC((s16 *)spEC[0]->unk4, l1Dest, t);
        animSetNodeItem(D_807FBB40, 0, 0, (&spEC[0]->unk8)[D_807444FC]);
    } else {
        animSetNodeItem(D_807FBB40, 0, 0, (s32)spEC[0]->unk4);
        if (D_807FBB40->unk155[0] == 0) {
            if (D_807FD580->unk1EC == 1) {
                func_806F91B4(0xC, D_807FD580->unk1A4, 1);
                sfxAllocateChannel(0x2E, 1.0f);
            } else if (D_807FD580->unk1EC == 2) {
                func_80609140(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
            }
            D_807FBB40->unk155[0]++;
        }
        if (D_807FD580->unk1EC != 0xFF && spEC[0]->unk10 != 0) {
            renderCallbacksRegister(&func_806FF628, D_807FBB40, 3);
        }
    }
    func_80699070(&spE8, &spEA, ((L1_CamState *)D_807FC924)->unk210, ((L1_CamState *)D_807FC924)->unk214, ((L1_CamState *)D_807FC924)->unk218, ((L1_CamState *)D_807FC924)->unk228, ((L1_CamState *)D_807FC924)->unk22C, ((L1_CamState *)D_807FC924)->unk230);
    t = L1_MIN(30.0, sp66) / 30.0;
    D_807FBB40->unkE6 = spEA;
    l1Angle = (f32)spE8 - (2048.0f + -2048.0f * t);
    *(s16 *)D_807FBB40->unkE8 = l1Angle;
    guRotateF(mtx1, spE8 / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, spEA / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, ((L1_CamState *)D_807FC924)->unk210, ((L1_CamState *)D_807FC924)->unk214, ((L1_CamState *)D_807FC924)->unk218);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -30.0f * t, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    if (spEC[0]->unk10 != 0) {
        spEC[0]->unk10--;
    } else {
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 -= 0xA;
        if (D_807FBB40->unk128 <= 0) {
            sp5F = 1;
        }
    }
    if (sp5F || !(spEC[0]->unk0->unk1F0 & 0x8000)) {
        if (spEC[0]->unk0->unk1EC == 1) {
            func_806EB0C0(0x58, 0, 0, (void *)spEC[0]);
        }
        sfxStopSlotSound(D_807FBB40, 0);
        spEC[0]->unk0->unk1F0 &= ~0x8000;
        spEC[0]->unk0->unk1EC = 0xFF;
        if (D_807FBB40->unk58 == 0xD9) {
            assetFreeBuffer((s32)spEC[0]->unk4, 0xF6, 0x45);
        } else {
            heapFreeDeferred((Mtx *)spEC[0]->unk4);
        }
        spEC[0]->unk0->unk88 = 0;
        actorDespawn(D_807FBB40);
    } else {
        guTranslateF((f32 (*)[4])((u8 *)D_807FBB40 + 0xC), 0.0f, -70.0f, 0.0f);
        func_806319C4(D_807FBB40, 1);
        renderCallbacksRegister(&func_80699128, D_807FBB40, 3);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699284.s")
#endif

void func_80699284(void);

void func_806998C8(void) {
    func_80699284();
}

/* Empty stub: the 8 bytes after func_806998C8 (a bare `jr ra; nop`) are a second
   function that splat merged into func_806998C8 for lack of a symbol. */
void func_806998E8(void) {
}

void func_80699958(s32, s32);

void func_806998F0(void) {
    func_80699958(8, 0);
}

extern Actor *D_807FBB40;

void func_80699914(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x3E8;
    }
    func_80699958(0x1C, 1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699958.s")

#ifdef NON_MATCHING
/* Behaviourally equivalent: the original also stores the incoming a1 to its
   home slot (4(sp)) at entry; that store is never read. 79 vs 78 insns. */
typedef struct {
    u8 pad0[0x98];
    f32 unk98[4];
    f32 unkA8[4];
    u8 unkB8[4];
} M1ActorSlots;

void func_8069A614(f32 arg0, s32 arg1) {
    M1ActorSlots *slots = (M1ActorSlots *)D_807FBB40->unk174;
    s16 i;
    s32 found;
    f64 temp;

    arg1 &= 0xFF;
    found = 0;
    i = 0;
    do {
        if (slots->unkB8[i] == 0) {
            found = 1;
        } else {
            i++;
        }
    } while (i < 4 && found == 0);
    if (found != 0) {
        slots->unkB8[i] = 1;
        switch (arg1) {
        case 0:
            slots->unkA8[i] = 10.0f;
            temp = (f64)arg0 / 843.0;
            if (temp > 0.0) {
                slots->unk98[i] = (f32)temp;
                return;
            }
            slots->unk98[i] = (f32)-temp;
            return;
        case 1:
            slots->unkA8[i] = 12.0f;
            temp = (f64)arg0 / 480.0;
            if (temp > 0.0) {
                slots->unk98[i] = (f32)temp;
                return;
            }
            slots->unk98[i] = (f32)-temp;
            break;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069A614.s")
#endif

extern ActorGlobalState D_807FBB70;

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069A750.s")

#ifdef NON_MATCHING
/* Behaviourally equivalent, same blocks/frame/saved regs; remaining diff is FP
   temporary allocation (and one insn): 235 vs 236 insns. */
typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
} M1Sub4Node;

typedef struct {
    u8 pad0[0x24];
    M1Sub4Node *unk24;
} M1Sub4;

typedef struct {
    f32 unk0;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    s32 unkC;
} M1ProximityState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} M1ProximityEntry;

typedef struct {
    u8 pad0[0xB8];
    f32 unkB8;
} M1ProximityNode;

typedef struct {
    u8 pad0[0x3C];
    M1ProximityEntry entries[4];
    u8 pad6C[0x10];
    M1ProximityNode *nodes[4];
} M1ProximityGlobal;

Mtx *func_80610FE8(s32);
f32 func_80612D1C(f32);
void func_806319C4(Actor *, s32);

void func_8069A7C8(void) {
    M1ProximityGlobal *globals;
    M1ProximityState *state;
    f32 acc;
    f32 dist;
    f32 limit;
    f32 value;
    s32 flags;
    s32 i;

    flags = D_807FBB40->unk60;
    acc = 0.0f;
    state = (M1ProximityState *)D_807FBB40->unk174;
    if (!(flags & 0x10)) {
        D_807FBB40->unk60 = flags | 0x400;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24 = (M1Sub4Node *)func_80610FE8(0x20);
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk0 = 1;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk1 = 0xFF;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk4 = 0.0f;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unkC = 0.0f;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk8 = 0.0f;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk10 = 0xFF;
        D_807FBB40->unk12A = 0x3E8;
        state->unk4 = 0;
        state->unkC = 0;
        state->unk0 = 0.0f;
        state->unk8 = 0.0f;
    }
    globals = (M1ProximityGlobal *)&D_807FBB70;
    i = 0;
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            dist = sqrtf((globals->entries[i].unk8 * globals->entries[i].unk8) + (globals->entries[i].unk0 * globals->entries[i].unk0));
            if (dist > 1347.0f) {
                dist = 1347.0f;
            }
            acc += 1347.0f - dist;
            value = (f32)((f64)globals->nodes[i]->unkB8 * 0.1);
            if (state->unk8 < value) {
                state->unk8 = value;
            }
            i++;
        } while (i < (s32)D_807FBB70.unk39);
    }
    if (acc > 1347.0f) {
        acc = 1347.0f;
    }
    limit = (f32)((f64)acc / 10.0);
    if (state->unk0 < limit) {
        state->unk0 = (f32)((f64)state->unk0 + ((f64)(limit - state->unk0) * 0.25));
        if (limit < state->unk0) {
            state->unk0 = limit;
        }
    }
    if (limit < state->unk0) {
        state->unk0 = (f32)((f64)state->unk0 - ((f64)(state->unk0 - limit) * 0.5));
        if (state->unk0 < limit) {
            state->unk0 = limit;
        }
    }
    state->unkC++;
    if ((f64)state->unk8 == 0.0) {
        state->unkC = 0;
    }
    if (D_807FBB70.unk39 != state->unk4) {
        state->unk8 = 12.0f;
    }
    state->unk8 = (f32)((f64)state->unk8 - ((f64)state->unk8 / 40.0));
    if ((f64)state->unk8 < 0.5) {
        state->unk8 = 0.0f;
    }
    ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk8 = (f32)(0.0 - ((f64)(func_80612D1C((f32)((f64)state->unkC * 0.5)) * state->unk8) + state->unk0));
    state->unk4 = D_807FBB70.unk39;
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069A7C8.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069AB74.s")

void func_8069AB74(void);

void func_8069AFF0(void) {
    func_8069AB74();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069B010.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069B3FC.s")

extern s32 D_8076A068;
extern s16 D_80744490;
s32 actorTableContains();
void func_8069B908(void);
void func_80689114(s16, f32, f32, f32, s16, f32, s32);
s32 func_8073110C(s32, s32);

s32 func_8069B85C(void) {
    ActorCallbackNode *node = D_807FBB40->unk13C;

    while (node != NULL) {
        if ((u32)node->callback == 0x8000) {
            Actor *actor;
            void *sub;
            if (actorTableContains(node->unk8) != 0) {
                actor = (Actor *)node->unk8;
                if (actor->unk5C & 1) {
                    sub = actor->unk174;
                    if ((u32)(D_8076A068 - *(s32 *)((u8 *)sub + 0x120)) < 2) {
                        return 1;
                    }
                }
            }
        }
        node = node->next;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069B908.s")

#ifdef NON_MATCHING
typedef struct M2_CamState {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} M2_CamState;

void func_8069CD9C(void) {
    f32 frac;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 dist;
    u32 val;

    if (!(D_807FBB40->unk60 & 0x10)) {
        frac = D_807FBB40->unk4->unk34 / 0.15;
        frac = frac - 1.0;
        if (frac < 0.0) {
            frac = 0.0f;
        }
        val = (u32)(80.0f * frac);
        D_807FBB40->unk12C[4] = val;
        D_807FBB40->unk12C[5] = val;
        D_807FBB40->unk12A = 0x2BC;
    }
    dx = D_807FBB40->unk7C - ((M2_CamState *)D_807FC924)->unk210;
    dz = D_807FBB40->unk84 - ((M2_CamState *)D_807FC924)->unk218;
    dy = D_807FBB40->unk80 - ((M2_CamState *)D_807FC924)->unk214;
    dist = dx * dx + dy * dy;
    if (dz * dz + dist < 18000.0) {
        D_807FBB40->unk60 |= 0x400;
    } else {
        D_807FBB40->unk60 &= ~0x400;
    }
    func_8069B908();
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069CD9C.s")
#endif

void func_8069CF54(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12C[4] = 0x3C;
        D_807FBB40->unk12C[5] = 0x3C;
        func_80689114(0x83, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84,
                      0, 1.0f, (s32)D_807FBB40);
    }
    func_8069B908();
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (*(s32 *)((u8 *)D_807FBB40->unk124 + 0x8) == 1) {
            if (func_8073110C(0xFD, 0) != 0) {
                D_807FBB40->unk132 = 4;
            }
        }
    }
}

void func_8069D018(void) {
    Actor *actor = D_807FBB40;

    if (!(actor->unk60 & 0x10)) {
        actor->unk12A = 0x2BC;
    }
    func_8069B908();
}

void func_8069D058(void) {
    func_8069D018();
}

void func_8069D078(void) {
    func_8069D018();
}

void func_8069D098(void) {
    func_8069D018();
}

void func_8069D0B8(void) {
    func_8069D018();
}

void func_8069D0D8(void) {
    func_8069B908();
}

Mtx *func_80610FE8(s32);

#ifdef NON_MATCHING
typedef struct M2_Sub {
    void *unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} M2_Sub;

s32 actorSpawn(s32, s32);
s32 func_806FDB8C(s16, s32, s32, f32, f32, f32);
s32 func_806FBD5C(s16, s32);
extern Actor *D_807FBB44;

void func_8069D0F8(u8 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u8 arg6, u8 arg7) {
    s32 len;
    M2_Sub *sub;

    if (actorSpawn(0xE8, 0) != 0) {
        sub = D_807FBB44->unk174;
        if (arg0 & 0x80) {
            f32 f = (f32)arg2;
            sub->unkA = func_806FDB8C((s16)(arg0 & 0xFF7F), arg3, 2, 160.0f, f, 0.0f);
            *(s16 *)((u8 *)D_807FBB44 + 0xEE) = 1;
            D_807FBB44->unk80 = f;
            return;
        }
        if (arg1 == 0) {
            D_807FBB44->unk7C = (f32)((D_80744490 - func_806FBD5C((s16)arg0, arg3)) * 2);
        } else {
            D_807FBB44->unk7C = (f32)(arg1 * 4);
        }
        D_807FBB44->unk80 = (f32)(arg2 * 4);
        D_807FBB44->unk84 = (f32)arg0;
        D_807FBB44->unk16A = 0xFF;
        D_807FBB44->unk16B = 0xFF;
        D_807FBB44->unk16C = 0xFF;
        len = strlen((char *)arg3) + 1;
        sub->unk0 = func_80610FE8(len);
        _strcpy((char *)sub->unk0, (char *)arg3);
        sub->unk4 = arg4;
        sub->unk6 = arg5;
        sub->unk8 = arg6;
        sub->unk9 = arg7;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069D0F8.s")
#endif

extern u8 D_807FC928;
s32 func_80714450();
s32 func_807142D8();
s32 func_8071432C();
s32 func_80712658();
void func_8069D0F8(u8, s16, s16, s32, u16, u16, u8, u8);

void func_8069D2AC(u8 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u8 arg6, u8 arg7) {
    if (D_807FC928 < 2) {
        if (func_80714450() == 0) {
            if (func_807142D8() == 0) {
                if (func_8071432C() != 0 || func_80712658() != 0) {
                    func_8069D0F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                }
            }
        }
    }
}

typedef struct M2_Pos {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
} M2_Pos;

void heapFreeDeferred(Mtx *);

void *func_8069D358(void *arg0, M2_Pos *arg1, s16 arg2, f32 arg3) {
    Mtx *temp;
    f32 mtxA[4][4];
    f32 mtxB[4][4];

    temp = func_80610FE8(0x40);
    heapFreeDeferred(temp);
    guScaleF(mtxA, arg3, arg3, 1.0f);
    guTranslateF(mtxB, (f32)((f64)arg1->unk7C + 2.0 * (f64)arg2), arg1->unk80, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, temp);
    ((u32 *)arg0)[0] = 0xDA380003;
    ((u32 *)arg0)[1] = (u32)temp;
    return (u8 *)arg0 + 8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069D424.s")

#define M3_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern Gfx D_1000118;
void func_806319C4(Actor *, s32);
Gfx *func_806FE078(Gfx *, s32, s32, f32, f32, f32, f32);

Gfx *func_8069D930(Gfx *gfx, Actor *actor) {
    void *model;

    model = actor->unk174;
    M3_WRITE_GFX(gfx++, 0xDE000000, &D_1000118);
    M3_WRITE_GFX(gfx++, 0xE7000000, 0);
    M3_WRITE_GFX(gfx++, 0xFA000000, 0xFFFFFFFF);
    M3_WRITE_GFX(gfx++, 0xFC11FE23, 0xFFFFF3F9);
    M3_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
    if (actor->unk168++ < 100) {
        gfx = func_806FE078(gfx, *(u8 *)((u8 *)model + 0xA), 2, 160.0f, actor->unk80, 0.0f, 1.0f);
    } else {
        gfx = func_806FE078(gfx, *(u8 *)((u8 *)model + 0xA), 1, 160.0f, actor->unk80, 0.0f, 1.0f);
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DA54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DC10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DC80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DD40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DF58.s")

void func_8069E018(void) {
    func_806319C4(D_807FBB40, 0);
}

void func_80614EBC(Actor *, s32);

void func_8069E040(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80614EBC(D_807FBB40, 0x299);
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069E088.s")

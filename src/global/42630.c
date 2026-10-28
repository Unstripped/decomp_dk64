#include "common.h"
#include "actor.h"
#include "cutscene.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

extern s16 D_807F6240[];
extern s8 D_807F6902;

#ifdef NON_MATCHING
u8 D_807F66F0[0x212]; // TU-local definition: as1 then shares one `lui at` between sb 0/1 (matches text); the bss blob must be split out of the asm first

void func_8063D930(void) {
    s32 i = 0;
    s32 j;

    do {
        D_807F6240[i] = -1;
        i++;
    } while (&D_807F6240[i] < (s16 *)D_807F66F0);
    for (j = 0; j < 0x212; j++) { D_807F66F0[j] = 0; }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/42630/func_8063D930.s")
#endif

struct CsModelSlot;
extern struct CsModelSlot *D_807F6000;
s32 hashTableLookup();

typedef struct CsA0Node {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ u8 unk2[0x28];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ u8 unk2C[0x20];
    /* 0x4C */ struct CsA0Node *unk4C;
} CsA0Node;

typedef struct CsA0Obj {
    /* 0x00 */ u8 unk0[0x9C];
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ u8 pad9E[2];
    /* 0xA0 */ CsA0Node *unkA0;
} CsA0Obj;

typedef struct CsA0Slot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ CsA0Obj *unk7C;
    /* 0x80 */ u8 pad80[0xA];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsA0Slot; /* 0x90 */

s16 func_8063D990(s16 arg0) {
    return ((CsA0Slot *)D_807F6000)[hashTableLookup(arg0)].unk8A;
}

s16 func_8063D9D0(s16 arg0, u8 arg1) {
    s32 i;

    if (arg1 == 0) {
        i = 0x226;
    } else {
        i = 0;
    }
    while (D_807F6240[i] != -1) {
        i++;
    }
    D_807F6240[i] = arg0;
    return i;
}

void func_8063DA78(s16, s16, s16);

void func_8063DA40(s16 arg0, s16 arg1) {
    func_8063DA78(arg0, arg1, 0);
}

void func_8063DA78(s16 arg0, s16 arg1, s16 arg2) {
    s16 slot;

    slot = hashTableLookup(D_807F6240[arg0]);
    if (slot != -1) {
        ((CsA0Slot *)D_807F6000)[slot].unk7C->unk0[arg2 + 0x48] = arg1;
        ((CsA0Slot *)D_807F6000)[slot].unk7C->unk0[0x54] = 1;
    }
}

typedef struct CsA0Timer {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 pad7;
} CsA0Timer;

extern CsA0Timer D_807F61B0[8];
extern struct CsSpawnReq D_807F61F0;

void func_8063DB0C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_807F61B0[i].unk6 = 0;
    }
}

void func_8063DB3C(s16 arg0, s16 arg1, s16 arg2) {
    s16 i = 0;
    s32 found = 0;

    while (!found && i < 8) {
        if (D_807F61B0[i].unk6 == 0) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found) {
        D_807F61B0[i].unk6 = 1;
        D_807F61B0[i].unk0 = arg0;
        D_807F61B0[i].unk2 = arg1;
        D_807F61B0[i].unk4 = arg2;
    }
}

void func_8063DBD8(s16 arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_807F61B0[i].unk6 != 0 && arg0 == D_807F61B0[i].unk0) {
            func_8063DA40(D_807F61B0[i].unk2, D_807F61B0[i].unk4);
            D_807F61B0[i].unk6 = 0;
        }
    }
}

extern s8 D_807F6903;
extern s16 D_807F693C;
extern u8 D_807F693E;
extern s8 D_807F693F;
void *func_80610FE8(s32);
struct CsA1State;
void func_8063DED0(struct CsA1State *);
void *memcpy(void *, const void *, unsigned int);

typedef struct CsA0Spawn {
    /* 0x0 */ void *unk0;
    /* 0x4 */ void *unk4;
    /* 0x8 */ u8 unk8;
} CsA0Spawn;

void func_8063DC58(s16 *arg0) {
    s16 n;
    s16 *p;
    s32 slot;
    s16 id;
    s16 m;
    s16 c1;
    s16 c2;
    s32 len1;
    s32 len2;
    CsA0Node **tail;
    CsA0Node *node;

    n = *arg0;
    p = arg0 + 1;
    if (n != 0) {
        do {
            id = *p;
            p++;
            slot = hashTableLookup(D_807F6240[id]);
            if (slot != -1) {
                ((CsA0Slot *)D_807F6000)[slot].unk7C = func_80610FE8(0xA4);
                func_8063DED0(((CsA0Slot *)D_807F6000)[slot].unk7C);
                ((CsA0Slot *)D_807F6000)[slot].unk7C->unkA0 = NULL;
                m = p[0];
                tail = &((CsA0Slot *)D_807F6000)[slot].unk7C->unkA0;
                ((CsA0Slot *)D_807F6000)[slot].unk7C->unk9C = p[1];
                p += 2;
                while (m != 0) {
                    node = func_80610FE8(0x50);
                    *tail = node;
                    node->unk4C = NULL;
                    c1 = *p;
                    p++;
                    len1 = c1 * 4;
                    tail = &node->unk4C;
                    node->unk0 = c1;
                    memcpy(node->unk2, p, len1 * 2);
                    p += len1;
                    c2 = *p;
                    p++;
                    len2 = c2 * 4;
                    node->unk2A = c2;
                    memcpy(node->unk2C, p, len2 * 2);
                    p += len2;
                    m--;
                }
            } else {
                m = p[0];
                p += 2;
                while (m != 0) {
                    c1 = *p;
                    p++;
                    p += c1 * 4;
                    c2 = *p;
                    p++;
                    p += c2 * 4;
                    m--;
                }
            }
            n--;
        } while (n != 0);
    }
    D_807F693F = 0;
    D_807F693E = 0;
    D_807F6902 = 0;
    D_807F6903 = 0;
    D_807F693C = 0;
    ((CsA0Spawn *)&D_807F61F0)->unk0 = NULL;
    ((CsA0Spawn *)&D_807F61F0)->unk4 = NULL;
    ((CsA0Spawn *)&D_807F61F0)->unk8 = 0;
}

void heapFree(void *);

void func_8063DE68(CsA0Obj *arg0) {
    CsA0Node *node;
    CsA0Node *next;

    if (*(void **)arg0 != NULL) {
        heapFree(*(void **)arg0);
    }
    node = arg0->unkA0;
    while (node != NULL) {
        next = node->unk4C;
        heapFree(node);
        node = next;
    }
    heapFree(arg0);
}

// Cutscene condition/command list node (one script step).
typedef struct CsA1Node {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ CsCmd unk2[5];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ CsCmd unk2C[4];
    /* 0x4C */ struct CsA1Node *unk4C;
} CsA1Node;

// Whole-state view of CsState (include/cutscene.h only knows part of it).
typedef struct CsA1State {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14[8];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40[2];
    /* 0x44 */ s16 unk44[2];
    /* 0x48 */ u8 unk48[3];
    /* 0x4B */ u8 unk4B[3];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 pad55[7];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D[3];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 pad61;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 unk67;
    /* 0x68 */ u8 pad68[6];
    /* 0x6E */ u8 unk6E;
    /* 0x6F */ u8 unk6F;
    /* 0x70 */ u8 unk70;
    /* 0x71 */ u8 unk71;
    /* 0x72 */ u8 pad72[2];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ Actor *unk94;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ u8 unk9A;
    /* 0x9B */ u8 unk9B;
    /* 0x9C */ u8 pad9C[4];
    /* 0xA0 */ CsA1Node *unkA0;
} CsA1State;

void func_8063DED0(CsA1State *cs) {
    s32 i;

    for (i = 0; i < 8; i++) {
        cs->unk14[i] = 1.0f;
    }
    cs->unk10 = -1;
    cs->unk12 = -1;
    cs->unk38 = -1;
    cs->unk0 = 0;
    cs->unk40[0] = 0;
    cs->unk40[1] = 0;
    cs->unk44[0] = 0;
    cs->unk44[1] = 0;
    cs->unk48[0] = 0;
    cs->unk48[1] = 0;
    cs->unk48[2] = 0;
    cs->unk4B[0] = 0;
    cs->unk4B[1] = 0;
    cs->unk4B[2] = 0;
    cs->unk4E = 0;
    cs->unk4F = 0;
    cs->unk50 = 0;
    cs->unk51 = 0;
    cs->unk52 = 0;
    cs->unk53 = 0;
    cs->unk80 = 0;
    cs->unk82 = 0;
    cs->unk84 = 0x7FFF;
    cs->unk86 = 0x7FFF;
    cs->unk88 = 0;
    cs->unk8A = 0xFFF;
    cs->unk94 = NULL;
    cs->unk54 = 0;
    cs->unk5C = 0;
    cs->unk67 = 0;
    cs->unk6E = 1;
    cs->unk6F = 0;
    cs->unk62 = 0;
    cs->unk64 = 0;
    cs->unk60 = 0;
    cs->unk66 = 0xFF;
    cs->unk70 = 1;
    cs->unk71 = 1;
    cs->unk9A = 0;
    cs->unk9B = 0;
    cs->unk98 = 0;
    cs->unk4 = 0xFFFFFFFF;
    cs->unk8 = 0.0f;
    cs->unkC = 0.0f;
    cs->unk34 = 0.0f;
    cs->unk3C = 0.0f;
    cs->unk74 = 0.0f;
    cs->unk78 = 0.0f;
    cs->unk7C = 0.0f;
    cs->unk8C = 0.0f;
    cs->unk90 = 0.0f;
}

typedef struct CsA1ModelSlot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[0x10];
} CsA1ModelSlot; /* 0x90 */

struct CsModelSlot;
extern u8 D_807F66F0[];

void func_8063DFEC(s32 arg0, u8 *arg1) {
    s16 slot;

    slot = hashTableLookup(D_807F6240[arg0]);
    if (slot != -1) {
        memcpy(((CsA1ModelSlot *)D_807F6000)[slot].unk7C + 0x14, arg1, 0x20);
        D_807F66F0[arg0] = 1;
    }
}

void func_8063E078(CsA1State *cs) {
    u8 i;

    for (i = 0; i < 2; i++) {
        if (cs->unk44[i] != 0) {
            cs->unk44[i]--;
        }
    }
    for (i = 0; i < 3; i++) {
        cs->unk4B[i] = cs->unk48[i];
    }
    cs->unk4E = 0;
}

extern f32 D_807F61FC;
extern f32 D_807F6200;
extern f32 D_807F6204;
extern f32 D_807F6208;
extern f32 D_807F620C;
extern f32 D_807F6210;
extern f32 D_807F6214;
extern f32 D_807F6218;
extern f32 D_807F621C;
extern f32 D_807F6220;
extern f32 D_807F6224;
extern f32 D_807F6228;
extern f32 D_807F622C;
extern f32 D_807F6230;
extern f32 D_807F6234;
extern f32 D_807F6238;
extern s16 D_807F6904;
extern s16 D_807F6906;
extern s16 D_807F6908;
extern f32 D_807F690C;
extern f32 D_807F6910;
extern f32 D_807F6914;
void modelSlotGetTransformVectors(s32, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, u8);
void func_8063E5B4(CsA1State *);
void func_8063E72C(CsA1State *);
s32 func_8063EA14(CsCmd *, CsState *, s16);
void func_8063FA48(CsCmd *, CsState *, s16);
s32 modelSlotStepAnimations(s16);
void modelSlotUpdateGroundCoords(s16, u8);
void func_806358E8(s32, f32, f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8, u8);

void func_8063E0D4(CsA1State *cs, s16 csId) {
    CsA1Node *node;
    s32 i;
    s32 j;
    s32 ok;
    s32 stepped;
    u8 moved;
    u8 rotated;
    u8 scaleXZ;
    u8 scaleY;

    node = cs->unkA0;
    if (node != NULL) {
        modelSlotGetTransformVectors(csId, &D_807F61FC, &D_807F6200, &D_807F6204, &D_807F6208, &D_807F620C,
                                     &D_807F6210, &D_807F6214, &D_807F6218, 1);
        modelSlotGetTransformVectors(csId, &D_807F621C, &D_807F6220, &D_807F6224, &D_807F6228, &D_807F622C,
                                     &D_807F6230, &D_807F6234, &D_807F6238, 1);
        func_8063E72C(cs);
        D_807F6904 = 0;
        D_807F6908 = 0x7FFF;
        D_807F6906 = D_807F6908;
        D_807F690C = D_807F61FC;
        D_807F6910 = D_807F6200;
        D_807F6914 = D_807F6204;
        while (node != NULL) {
            i = 0;
            ok = 1;
            while (i < node->unk0 && ok) {
                ok = func_8063EA14(&node->unk2[i], (CsState *)cs, csId) & 0xFF;
                i++;
            }
            if (ok) {
                for (j = 0; j < node->unk2A; j++) {
                    func_8063FA48(&node->unk2C[j], (CsState *)cs, csId);
                }
            }
            node = node->unk4C;
        }
        stepped = modelSlotStepAnimations(csId);
        if (D_807F61FC != D_807F621C || D_807F6200 != D_807F6220 || D_807F6204 != D_807F6224 ||
            D_807F6208 != D_807F6228 || D_807F620C != D_807F622C || D_807F6210 != D_807F6230 ||
            D_807F6214 != D_807F6234 || stepped != 0) {
            moved = D_807F61FC != D_807F621C || D_807F6200 != D_807F6220 || D_807F6204 != D_807F6224;
            rotated = D_807F6208 != D_807F6228 || D_807F620C != D_807F622C || D_807F6210 != D_807F6230;
            scaleXZ = D_807F6214 != D_807F6234;
            scaleY = D_807F6218 != D_807F6238;
            func_806358E8(csId, D_807F621C, D_807F6220, D_807F6224, D_807F6228, D_807F622C, D_807F6230, D_807F6234,
                          D_807F6238, moved, rotated, scaleXZ, scaleY, 1);
            cs->unk4E = 1;
        }
        if (D_807F6904 != 0) {
            modelSlotUpdateGroundCoords(csId, 1);
        }
        func_8063E5B4(cs);
    }
}

extern u32 D_807FBB60;
void actorDespawn(Actor *);

void func_8063E5B4(CsA1State *cs) {
    Actor *actor;
    u32 flags;

    cs->unk34 = D_807F622C - D_807F620C;
    cs->unk48[0] = cs->unk4B[0];
    cs->unk48[1] = cs->unk4B[1];
    cs->unk48[2] = cs->unk4B[2];
    cs->unk53 = cs->unk52;
    actor = cs->unk94;
    cs->unk51 = 0;
    cs->unk52 = 0;
    cs->unk5C = 0;
    cs->unk9A |= 1;
    if (actor != NULL) {
        cs->unk94->unk7C = D_807F621C;
        actor->unk80 = D_807F6220;
        actor->unk84 = D_807F6224;
        actor->unkE6 = D_807F622C * 4096.0f / 360.0f;
        flags = D_807FBB60;
        if (flags & 0x1000) {
            D_807FBB60 = flags & ~0x1000;
            actorDespawn(cs->unk94);
            cs->unk94 = NULL;
        }
    }
    D_807F693F = 0;
}

extern u32 D_8076A064;

void func_8063E6B4(CsA1State *cs) {
    s16 a;
    s16 b;

    if (D_8076A064 != cs->unk4) {
        b = cs->unk64;
        a = cs->unk62;
        cs->unk4 = D_8076A064;
        if (b < a) {
            cs->unk64 = b + cs->unk66;
            if (a < cs->unk64) {
                cs->unk64 = a;
            }
        } else {
            cs->unk64 = b - cs->unk66;
            if (cs->unk64 < a) {
                cs->unk64 = a;
            }
        }
    }
}

void func_8063E72C(CsA1State *cs) {
    switch (cs->unk50) {
        case 0:
            break;
        case 1:
            if (cs->unk52 != 0) {
                cs->unk74 += cs->unk7C;
                if (cs->unk78 < cs->unk74) {
                    cs->unk74 = cs->unk78;
                }
            } else {
                cs->unk74 -= cs->unk7C;
                if (cs->unk74 < 0.0) {
                    cs->unk74 = 0.0f;
                }
            }
            if (cs->unk74 > 0.01) {
                D_807F621C += cs->unk8C * cs->unk74;
                D_807F6224 += cs->unk90 * cs->unk74;
                if (D_807F621C < cs->unk80) {
                    D_807F621C = cs->unk80;
                }
                if (D_807F6224 < cs->unk82) {
                    D_807F6224 = cs->unk82;
                }
                if (cs->unk84 < D_807F621C) {
                    D_807F621C = cs->unk84;
                }
                if (cs->unk86 < D_807F6224) {
                    D_807F6224 = cs->unk86;
                }
            }
            break;
        case 2:
            if (cs->unk52 != 0) {
                switch (cs->unk52) {
                    case 1:
                        cs->unk74 += cs->unk7C;
                        break;
                    case 2:
                        cs->unk74 -= cs->unk7C;
                        break;
                }
                if (cs->unk78 < cs->unk74) {
                    cs->unk74 = cs->unk78;
                }
                if (cs->unk74 < -cs->unk78) {
                    cs->unk74 = -cs->unk78;
                }
                D_807F622C += cs->unk74;
            } else {
                if (cs->unk74 > 0.0) {
                    cs->unk74 -= cs->unk7C;
                    if (cs->unk74 < 0.0) {
                        cs->unk74 = 0.0f;
                    }
                } else {
                    cs->unk74 += cs->unk7C;
                    if (cs->unk74 > 0.0) {
                        cs->unk74 = 0.0f;
                    }
                }
                D_807F622C += cs->unk74;
            }
            break;
    }
}

// Cutscene condition evaluator (func_8063EA14): one CsCmd per call, nonzero = condition holds.
// Matched. Operand-order notes: `field == ((s16 *)cmd)[N]` (instead of `== cmd->a/b`) emits `bne field,arg`
// (a plain cmd->x leaf is canonicalised to the left operand and its ring temp comes first); the actor loops
// use their own pointer local `b` (not `a`, the player-loop pointer) and index `h` (not `k`).
typedef struct CsEAState {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ f32 unk14[9];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[8];
    /* 0x44 */ s16 unk44[2];
    /* 0x48 */ u8 unk48[9];
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 pad53[9];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u8 pad60[0x3A];
    /* 0x9A */ u8 unk9A;
} CsEAState;

typedef struct CsEAAct {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x10C - 0x64];
    /* 0x10C */ s16 unk10C;
    /* 0x10E */ u8 unk10E;
    /* 0x10F */ u8 pad10F;
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[0x12F - 0x111];
    /* 0x12F */ u8 unk12F;
    /* 0x130 */ u8 pad130[0x154 - 0x130];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} CsEAAct;

typedef struct CsEAPlayer {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ CsEAAct *unk4;
    /* 0x008 */ u8 pad8[0x288];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[0x2C0 - 0x292];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 unk2C1;
    /* 0x2C2 */ u8 pad2C2[0x2F0 - 0x2C2];
} CsEAPlayer; /* 0x2F0 */

typedef struct CsEACam {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ s32 unk1F8;
} CsEACam;

typedef struct CsEAObj {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ u8 unk48[1];
} CsEAObj;

typedef struct CsEASlot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[0xA];
} CsEASlot; /* 0x90 */

typedef struct CsEAActorD {
    /* 0x00 */ u8 pad0[0xD0];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 unkD1;
} CsEAActorD;

typedef struct CsEASpawn {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} CsEASpawn;

typedef struct CsEARow {
    /* 0x000 */ u8 e[8][0x5E];
    /* 0x2F0 */ u8 pad2F0[0x16];
} CsEARow; /* 0x306 */

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern CsPlayer *D_807FC924;
extern u8 *D_807FD568;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[];
extern u8 D_807444EC;
extern u8 D_8074E77C;
extern s16 D_8076AEF2;
extern s32 (*D_80748048[])(CsState *, s16, s16, s16);

void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
s32 modelAnimEntryIsActive(s16, s16);
s32 actorListGetOrSetState(s16, u8, u8);
s32 flagGet();
s32 func_80689BAC(s16);
u16 func_8067ACC0(u16);
s32 func_806419F8(void);
void func_80641724(s16);
s16 func_80650A70(s16, s16);
Actor *spawnNodeActivate(s16, u16);
u8 spawnNodeHasActor(u8);
s32 spawnNodeIsInCooldown(u8);
s32 listContainsS16(s16);
f32 func_80614A54(void *);
s32 func_806C8D2C(s16);
s32 func_80723C98(s32);
u8 func_80641F70(s16);
s32 func_80642204(s16);
s32 func_806422D8(s16);
s32 func_806423A8(s16, s16, s16);
s32 func_80642500(f32 *, s16, s16);
s32 func_806425FC(s16, s16);

#define CsEAS ((CsEAState *)cs)
#define CsEAP ((CsEAPlayer *)D_807FC924)

s32 func_8063EA14(CsCmd *cmd, CsState *cs, s16 csId) {
    u8 neg;
    u8 ret;
    s16 type;
    CsEAAct *a;
    CsEAPlayer *p;
    u8 found;
    s32 count;
    s32 k;
    s32 h;
    s16 sAnim;
    f32 fAnim;
    u8 uAnim;
    u8 i;
    f32 height;
    u8 *q;
    CsEACam *cam;
    u32 mask;
    CsEAAct *b;

    if (*(s16 *)cmd & 0x8000) {
        neg = 1;
    } else {
        neg = 0;
    }
    type = *(s16 *)cmd & 0x7FFF;
    switch (type) {
    case 0x0:
        ret = 1;
        break;
    case 0x3D:
        ret = *(u8 *)&D_807F6903;
        break;
    case 0x3C:
        ret = cmd->a == CsEAP->unk290;
        break;
    case 0x3A:
        if ((1 << cmd->a) & D_807F693E) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x39:
        if (cmd->a & D_807FBB4C->unk132) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x38:
        ret = D_8074E77C < 5;
        break;
    case 0x37:
        modelAnimEntryGetState(csId, cmd->a, &sAnim, &fAnim, &uAnim);
        if (sAnim == cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x32:
        ret = cmd->a == D_8076AEF2;
        break;
    case 0x30:
        if (cmd->a == ((CsEAActorD *)D_807FBB4C)->unkD1) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x35:
        if (cmd->a == ((CsEAActorD *)D_807FBB4C)->unkD0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2E:
        if (actorListGetOrSetState(cmd->a, 0, 0) == cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2D:
        ret = flagGet(cmd->a, 0);
        break;
    case 0x36:
        ret = flagGet(cmd->a, 2);
        break;
    case 0x3B:
        ret = flagGet(cmd->a, 1);
        break;
    case 0x2C:
        if (func_80689BAC(cmd->a) != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x28:
        if (CsEAS->unk9A & 1) {
            ret = 0;
        } else {
            ret = 1;
        }
        break;
    case 0x26:
        cam = D_807FC924->unk4->unk174;
        if ((cmd->b + (cmd->a << 16)) & cam->unk1F0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x27:
        cam = D_807FC924->unk4->unk174;
        if ((cmd->b + (cmd->a << 16)) & cam->unk1F8) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x25:
        if (D_807FD568[1] >= cmd->a) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x34:
        h = func_806C8D2C(cmd->a) * 0x5E;
        q = &D_807FC950[D_807FC929 * 0x306 + h];
        if (*q >= cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x24:
        a = (CsEAAct *)spawnNodeActivate(cmd->a, 0);
        if (cmd->b == a->unk154) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x23:
        if (D_807444EC == 1) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1D:
        if ((cmd->a == 0 && CsEAS->unk48[cmd->c] < cmd->b) || (cmd->a == 1 && cmd->b < CsEAS->unk48[cmd->c])) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1C:
        h = func_80650A70(csId, cmd->a);
        if ((cmd->b == 0 && h < cmd->c) || (cmd->b == 1 && cmd->c < h)) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x16:
        mask = cmd->b + (cmd->a << 16);
        if (D_807FBB60 & mask) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x15:
        ret = modelAnimEntryIsActive(csId, cmd->a);
        break;
    case 0xC:
        if (D_807F61FC != D_807F621C || D_807F6200 != D_807F6220 || D_807F6204 != D_807F6224 ||
            D_807F6208 != D_807F6228 || D_807F620C != D_807F622C || D_807F6210 != D_807F6230 ||
            D_807F6214 != D_807F6234) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x8:
        ret = CsEAS->unk51;
        break;
    case 0x9:
        if (CsEAS->unk52 != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x7:
        ret = func_80642500(CsEAS->unk14, cmd->a, cmd->b);
        break;
    case 0x31:
        if (((CsEASlot *)D_807F6000)[hashTableLookup(D_807F6240[cmd->a])].unk7C[cmd->c + 0x48] == ((s16 *)cmd)[2]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1:
        k = CsEAS->unk48[cmd->b] - cmd->a;
        if (k == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x5:
        ret = func_806425FC(cmd->a, cmd->b);
        break;
    case 0x4:
        if (CsEAS->unk44[cmd->b] == ((s16 *)cmd)[1]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 1 && csId == a->unk10C) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xD:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 1 && csId == a->unk10C && cmd->a == a->unk10E) {
                    ret = 1;
                }
            }
        }
        break;
    case 0x11:
        found = 0;
        for (h = 0; h < gActiveActorCount && !found; h++) {
            b = (CsEAAct *)gActiveActors[h].actor;
            if (!(b->unk60 & 0x2000) && cmd->a == b->unk58 && b->unk110 == 1 && csId == b->unk10C) {
                found = 1;
            }
        }
        if (found) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x12:
        found = 0;
        for (h = 0; h < gActiveActorCount && !found; h++) {
            b = (CsEAAct *)gActiveActors[h].actor;
            if (!(b->unk60 & 0x2000) && cmd->a == b->unk58 && b->unk110 == 1 && csId == b->unk10C &&
                cmd->b == b->unk10E) {
                found = 1;
            }
        }
        if (found) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x14:
        count = 0;
        for (h = 0; h < gActiveActorCount; h++) {
            b = (CsEAAct *)gActiveActors[h].actor;
            if (!(b->unk60 & 0x2000) && cmd->a == b->unk58 && csId == b->unk10C && cmd->b == b->unk10E) {
                count++;
            }
        }
        if (count == cmd->c) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0xB:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 3 && cmd->a == a->unk12F && csId == a->unk10C) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xA:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 2 && csId == a->unk10C) {
                    ret = 1;
                } else {
                    ret = 0;
                }
            }
        }
        break;
    case 0xE:
        ret = func_80641F70(cmd->a);
        break;
    case 0x13:
        ret = func_80642204(cmd->a);
        break;
    case 0x20:
        ret = func_806422D8(cmd->a);
        break;
    case 0x29:
        ret = func_806423A8(cmd->a, cmd->b, cmd->c);
        break;
    case 0x6:
        ret = D_80748048[cmd->a](cs, csId, cmd->b, cmd->c);
        break;
    case 0xF:
        ret = func_80723C98(CsEAS->unk38);
        break;
    case 0x10:
        if (CsEAS->unk5C != 0 && (cmd->b == -1 || CsEAS->unk5C == ((s16 *)cmd)[2]) &&
            (func_8067ACC0(CsEAS->unk5E) & cmd->a) && func_806419F8() != 0) {
            func_80641724(((CsEASlot *)D_807F6000)[hashTableLookup(csId)].unk84);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x18:
        if (CsEAS->unk5C != 0 && (cmd->b == -1 || CsEAS->unk5C == ((s16 *)cmd)[2]) && cmd->a == CsEAS->unk5E &&
            func_806419F8() != 0) {
            func_80641724(((CsEASlot *)D_807F6000)[hashTableLookup(csId)].unk84);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x17:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (cmd->a == a->unk154) {
                    if (cmd->b != 0) {
                        if (a->unk155 == cmd->b) {
                            ret = 1;
                        }
                    } else {
                        ret = 1;
                    }
                }
            }
        }
        break;
    case 0x21:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0 && p->unk4->unk155 == ((s16 *)cmd)[1]) {
                ret = 1;
            }
        }
        break;
    case 0x19:
        if (cmd->a == D_807FBB4C->unk58) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1A:
        ret = CsEAP->unk2C0 == ((s16 *)cmd)[1];
        break;
    case 0x1B:
        ret = CsEAP->unk2C1;
        break;
    case 0x1E:
        ret = spawnNodeHasActor(CMDB(cmd)->a);
        break;
    case 0x2F:
        ret = spawnNodeIsInCooldown(CMDB(cmd)->a);
        break;
    case 0x1F:
        ret = 0;
        break;
    case 0x22:
        ret = listContainsS16(cmd->a);
        break;
    case 0x2A:
        if (((CsEASpawn *)&D_807F61F0)->unk8 != 0) {
            if (((CsEASpawn *)&D_807F61F0)->unk0->unk154 == 5) {
                ret = 1;
            } else {
                ret = 0;
            }
        } else {
            ret = 1;
        }
        break;
    case 0x2B:
        ret = ((CsEASpawn *)&D_807F61F0)->unk8;
        break;
    case 0x33:
        height = func_80614A54(D_807FBB4C);
        ret = 0;
        if (cmd->a == 0 && cmd->b < (s16)height) {
            ret = 1;
        }
        if (cmd->a == 1 && (s16)height < cmd->b) {
            ret = 1;
        }
        break;
    default:
        ret = 0;
        break;
    }
    if (neg) {
        ret = 1 - ret;
    }
    return ret;
}

// Cutscene script command interpreter (func_8063FA48): one 8-byte command per call.
// Parked NON_MATCHING: 1836 of 1847 insns, frame 0xC8, s0/s1 and block order match; the
// remaining diff is register allocation in the sfx cases (0xE/0x7D/0xF/0x7E: the original
// copies cmd->c into a second register before masking it), case 0x8D (map in s1, exit spilled
// to sp+0x70), the two actor loops (cursor v0 / count v1 / i t0) and ugen scratch numbering.

// Object hanging off the player actor's unk174.
typedef struct CsCamState {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x1F0 - 0x108];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ u8 pad1F8[0x22C - 0x1F8];
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
} CsCamState;

typedef struct CsModelSlot {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ u8 unk28[0x20];
    /* 0x48 */ u8 unk48[0x34];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[0xA];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsModelSlot; /* 0x90 */

typedef struct CsModelSlot2 {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ s8 unk3C;
    /* 0x3D */ u8 pad3D[0x90 - 0x3D];
} CsModelSlot2;

typedef struct CsSpawnReq {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} CsSpawnReq;

extern CsCmdFunc D_80747E70[];
extern u8 D_80744824;
extern s8 D_80748094;
extern s16 D_8074809C[];
extern s16 D_807480AC[];
extern s16 D_807480BC[];
extern s32 D_8076A0A8;
extern CsModelSlot *D_807F6000;
extern CsSpawnReq D_807F61F0;
extern Actor *D_807F61F4;
extern s16 D_807F6918[16];
extern u8 D_807F6938;
extern s16 D_807F693A;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern u32 D_807FBB68;

void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorSetStateTwo(Actor *);
void actorSetTargetSlotByte(s32, u8);
s32 actorSpawn(s32, s32);
void dynamicBufferFree(void *);
void effectNodeAddTargetAndStep(s32, f32, f32);
void effectNodeSetSubVal(s32, u8);
void effectNodeSetTargetAndStep(s32, f32, f32);
s32 func_805FEF74(s32);
u8 func_805FF030(u8, u8);
void func_805FF158(u8);
void func_805FF378(s32, s32);
void func_805FF628(s16, s16);
void func_805FF898(void);
void func_805FF9AC(s16, s16, s16, s16);
s32 func_805FFE50(s16, s16, s16);
void func_80600044(s32);
void func_80605380(s16);
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
s16 func_80609140(s16, s32, s32, f32, s32, s32);
void func_8060B49C(Actor *, s16);
void func_8060DEC8(void);
void camStartShakeFromPoint(s32, u8, u16, f32, f32, f32, f32, f32);
void camSetZoneWeight(u8, u8);
void mapOffsetSlotSetEnabled(s16, u8);
void mapOffsetSlotSetTarget(s16, f32, f32);
void mapOffsetSlotAddTarget(s16, f32, f32);
void func_8062D1A8(void);
void modelSkipListAdd(s16);
s16 modelSlotAppend(s16, f32, f32, f32, f32, s32);
void modelSlotGetNodePos(s16, s32, s32, f32 *, f32 *, f32 *);
void modelSlotUpdateTailKey(s16, s32, u8, u8);
void modelSlotTriBufferRelease(void *);
void modelSlotSetNodeScrollSpeed(s16, s16, s16, s16);
void modelSlotSetNodeAnimMode(s16, s16, u8);
void modelSlotSetNodeFrame(s16, s16, s16, s16);
void func_80636014(s16, s32, u8);
void func_8063A8C4(s16, s32, f32);
void func_8063DB3C(s16, s16, s16);
void func_806417BC(s16, s16);
void func_80641874(s16, s16);
s32 func_806418E8(s16, s16, s16);
void func_8064199C(void *, s16, s16);
void func_80641B00(s16, s16, s16);
void func_80641BCC(s16, s16, s16);
void func_80641C98(s16, s16, s16);
void func_80641DA0(void *, s16, s16, s16);
void func_80642480(s16, s16);
void func_80642748(s16, s16, void *, s16, u8);
void func_80642844(s16, s16, void *, s16, u8);
void func_80650794(s16, s16, u8, f32);
void func_8067A9F0(s32, Actor *, f32, f32, f32);
void func_8067ABC0(s32, Actor *, u8, s16, s32, f32, f32, f32);
s32 func_8068ABE0(s16);
void func_8068B830(s16, s16, s16);
void func_8068B8FC(void);
void func_806A2A10(s32, s32, u8, void *);
void func_806C92C4(s16);
void func_806CF398(Actor *);
void playerStateQueueCallback(s16, s32, s32);
void playerStateSetCallbackParameters(s32, s16, s16, s16);
void func_806F4F50(s16, f32, f32, f32);
void func_806FB370(u8, u8, u8);
void func_8070B308(s32);
s32 func_807146A4(s16);
void func_807149B8(s32);
void func_80714B84(s32, f32, s16, s16, s32);
s32 func_80723020(s32, s16, u8, f32, f32, f32, s32);
void func_80723284(s32, u8);
void func_807232EC(s32, u8);
void func_80723320(s32, s16);
void func_8072334C(s32, u8);
void func_80723380(s32, u8);
void func_80723428(s32);
void func_80723484(s32);
void func_807238D4(s32, f32 *, f32 *, f32 *);
void func_80724994(s32, s16, s16, s32, s32);
void zoneEntrySetDisabled(u8, u8, u8);
void volumeTriggerSetEnabled(s16, u8);
void volumeTriggerSetPosition(s16, s16, s16, s16);
void proxPathSetEnabled(s16, u8, u8);
void func_8072EE0C(s16, u8, u8);
void flagSet(s16, u8, s32);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void lightSetColor(f32, f32, f32, s16);
void mapByteArraySet(s16, u8);
void mapObjectSetByte(s16, u8, u8);
void modelAnimEntryClearTime(s16, s16);
void modelAnimEntryResetFrame(s16, s16, s16);
void modelAnimEntrySetTime(s16, s16, s16, f32);
void modelAnimEntrySetUnk10(s16, s16, s16);
void modelAnimEntrySetUnk12(s16, s16, s16);
void modelAnimEntrySetUnkC();
void modelAnimEntrySetUnkF(s16, s16, s16);
void modelAnimEntryStart(s16, s16, s16);
void modelAnimEntryStop(s16, s16);
void seqRouteChannelVolume(s32, f32);
void sfxAllocateChannel(s32, f32);
void sfxPlayFromTargetSlot(s16, s16, u8, u8, s32, s32, f32);
void sfxSetChannelTempo(s32, f32);
void sfxSetVolumeAndPan(u8, f32, f32);
u8 sfxSlotAllocateSource(s16, s16, s32, s32, u8, f32, s8);
void sfxStopChannel(s32, s32);

#ifdef NON_MATCHING
void func_8063FA48(CsCmd *cmd, CsState *cs, s16 csId) {
    void *dm = &csId; // unused: address-taken csId, keeps found at sp+0xC3
    u8 found;
    s32 i;
    s32 slot;
    s32 h;
    u8 sel;
    f32 x;
    f32 y;
    f32 z;
    f32 px;
    f32 py;
    f32 pz;
    f32 cr;
    f32 cg;
    f32 cb;
    s16 idx;
    CsCamState *cam;
    Actor *actor;
    s32 map;
    s32 b;
    s32 c;
    s32 exit;
    s16 flag;
    s32 pad68; // unused: keep sx..sz at sp+0x60..0x58
    s32 pad64;
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pan;
    u8 vol;
    volatile u8 pitch;
    f32 cx;
    f32 cy;
    f32 cz;

    found = 0; 
    switch (cmd->op) {
    case 0x95:
        D_807F693C = 0x80;
        break;
    case 0x92:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F0 |= 0x40000800;
        break;
    case 0x91:
        D_807FBB4C->unkB8 = cmd->a;
        break;
    case 0x93:
        camSetZoneWeight(CMDB(cmd)->a, CMDB(cmd)->b);
        break;
    case 0x94:
        func_80724994(2, cmd->a, 0, 0, 0);
        break;
    case 0x90:
        D_807F6902 = cmd->a;
        break;
    case 0x96:
        D_807F6903 = cmd->a;
        break;
    case 0x8E:
        dynamicBufferFree(&D_807F6000[hashTableLookup(csId)].unk28);
        break;
    case 0x8F:
        modelSlotTriBufferRelease(&D_807F6000[hashTableLookup(csId)].unk48);
        break;
    case 0x85:
        func_8062D1A8();
        break;
    case 0x83:
        func_806FB370(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x80:
        func_8060DEC8();
        break;
    case 0x81:
        D_807F693E |= 1 << cmd->a;
        break;
    case 0x82:
        D_807F693E &= ~(1 << cmd->a);
        break;
    case 0x7F:
        switch (cmd->b) {
        case 0:
            sel = 0;
            break;
        case 1:
            sel = 1;
            break;
        case 2:
            sel = 2;
            break;
        case 3:
            sel = 3;
            break;
        }
        func_8072EE0C(csId, CMDB(cmd)->a, sel);
        break;
    case 0x7C:
        D_80748094 = cmd->a;
        break;
    case 0x7B:
        modelSlotGetNodePos(csId, 1, cmd->b, &x, &y, &z);
        volumeTriggerSetPosition(cmd->a, x, y, z);
        break;
    case 0x7A:
        effectNodeSetSubVal(cmd->a, CMDB(cmd)->b);
        break;
    case 0x76:
        i = 0;
        for (; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->unk60 & 0x2000) && actor->unk110 == 1 && csId == actor->unk10C) {
                actorAppendCallback(actor, 0, 8, 0, 0, 0);
            }
        }
        break;
    case 0x75:
        volumeTriggerSetEnabled(cmd->a, CMDB(cmd)->b);
        break;
    case 0x78:
        modelSlotGetNodePos(csId, 1, cmd->a, &px, &py, &pz);
        cam = D_807FC924->unk4->unk174;
        cam->unk22C = px;
        cam->unk230 = py;
        cam->unk234 = pz;
        break;
    case 0x74:
        cs->unk9B |= cmd->a;
        break;
    case 0x73:
        playerStateSetCallbackParameters(0, cmd->a, cmd->b, cmd->c);
        break;
    case 0x72:
        actorListGetOrSetState(cmd->a, CMDB(cmd)->b, 1);
        break;
    case 0x6E:
        D_807F693F = cmd->a;
        break;
    case 0x6D:
        func_8063A8C4(csId, 1, cmd->a / 100.0);
        break;
    case 0x6C:
        modelSkipListAdd(cmd->a);
        break;
    case 0x6B:
        flagSet(cmd->a, CMDB(cmd)->b, 0);
        break;
    case 0x79:
        flagSet(cmd->a, CMDB(cmd)->b, 2);
        break;
    case 0x84:
        flagSet(cmd->a, CMDB(cmd)->b, 1);
        break;
    case 0x66:
        if (D_807F61F0.unk8 == 0) {
            actorSpawn(0xB1, 0);
            actor = D_807FBB40;
            D_807F61F0.unk4 = D_807FBB44;
            D_807FBB40 = D_807FBB44;
            func_806A2A10(0xDC, 0x2A, CMDB(cmd)->a, &D_807F61F0);
            D_807F61F0.unk0 = D_807FBB44;
            D_807F61F0.unk8 = 1;
            D_807FBB40 = actor;
        }
        break;
    case 0x67:
        if (D_807F61F0.unk8 != 0) {
            actorSetStateTwo(D_807F61F0.unk0);
        }
        break;
    case 0x68:
        if (D_807F61F0.unk8 != 0) {
            actorDespawn(D_807F61F0.unk0);
            actorDespawn(D_807F61F4);
            D_807F61F0.unk8 = 0;
        }
        break;
    case 0x62:
        D_807F693A = cmd->a;
        break;
    case 0x60:
        actorSetTargetSlotByte(csId, CMDB(cmd)->a);
        break;
    case 0x5F:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F0 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x3B:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F0 &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x8C:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F4 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x8B:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F4 &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x5D:
        func_805FF158(CMDB(cmd)->a);
        break;
    case 0x5C:
        zoneEntrySetDisabled(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x5B:
        func_806C92C4(cmd->a);
        break;
    case 0x5A:
        cs->unk68 = cmd->a;
        cs->unk6A = cmd->b;
        cs->unk6C = cmd->c;
        break;
    case 0x57:
        lightGetColor(&cr, &cg, &cb, D_807F693A);
        lightSetColor(cmd->a / 1000.0 + cr, cmd->b / 1000.0 + cg, cmd->c / 1000.0 + cb, D_807F693A);
        break;
    case 0x4F:
        if (D_807F6938 != 16) {
            if (cmd->a != -2) {
                D_807F6918[D_807F6938] = cmd->a;
                D_807F6938++;
            } else {
                D_807F6918[D_807F6938] = D_807F6000[hashTableLookup(csId)].unk8A;
                D_807F6938++;
            }
        }
        break;
    case 0x50:
        if (D_807F6240[cmd->a] != -1) {
            modelSlotGetNodePos(D_807F6240[cmd->a], 1, cmd->b, &D_807F690C, &D_807F6910, &D_807F6914);
        }
        break;
    case 0x4E:
        slot = func_807146A4(cmd->a);
        func_807149B8(1);
        func_80714B84(slot, cmd->b / 100.0, csId, cmd->c, 0);
        break;
    case 0x4C:
        h = (s16)(func_80650A70(csId, cmd->a) + cmd->b);
        if (h < 0) {
            h = 0;
        }
        modelAnimEntrySetUnkC(csId, cmd->a, h);
        break;
    case 0x4B:
        proxPathSetEnabled(csId, CMDB(cmd)->a, CMDB(cmd)->b);
        break;
    case 0x46:
        cs->unk70 = cmd->a;
        break;
    case 0x47:
        cs->unk71 = cmd->a;
        break;
    case 0x4A:
        modelSlotUpdateTailKey(csId, 1, CMDB(cmd)->a, CMDB(cmd)->b);
        break;
    case 0x45:
        cs->unk60 = cmd->a;
        cs->unk62 = cmd->b;
        cs->unk66 = cmd->c;
        break;
    case 0x40:
        D_807FBB60 |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x88:
        D_807FBB68 |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x89:
        D_807FBB68 &= ~(((u16)cmd->a << 16) + (u16)cmd->b);
        break;
    case 0x3F:
        cs->unk6E = cmd->a;
        break;
    case 0x3E:
        cs->unk6F = cmd->a;
        break;
    case 0x3D:
        cs->unk67 = cmd->a;
        break;
    case 0x39:
        cs->unk4F = cmd->a;
        break;
    case 0x36:
        func_80641BCC(cmd->a, cmd->b, csId);
        break;
    case 0x35:
        func_80641C98(cmd->a, cmd->b, csId);
        break;
    case 0x33:
        mapOffsetSlotSetTarget(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x55:
        mapOffsetSlotSetEnabled(cmd->a, CMDB(cmd)->b);
        break;
    case 0x34:
        mapOffsetSlotAddTarget(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x6A:
        effectNodeAddTargetAndStep(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x69:
        effectNodeSetTargetAndStep(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x26:
        func_8064199C(cs, cmd->a, cmd->b);
        break;
    case 0x54:
        slot = hashTableLookup(D_807F6240[cmd->a]);
        if (slot != -1) {
            func_8064199C(D_807F6000[slot].unk7C, cmd->b, cmd->c);
        }
        break;
    case 0x25:
        func_80641DA0(cs, cmd->a, cmd->b, cmd->c);
        break;
    case 0x3C:
        if (cs->unk94 != NULL) {
            actorDespawn(cs->unk94);
            cs->unk94 = NULL;
        }
        break;
    case 0x30:
        func_805FF378(cmd->a, 0);
        break;
    case 0x86:
        func_806CF398(D_807FBB48);
        func_805FF9AC(0x2A, 0, cmd->a, 2);
        break;
    case 0x87:
        func_805FF898();
        break;
    case 0x8D:
        D_80744824 = 2;
        func_806CF398(D_807FBB48);
        slot = func_805FF030(D_8076A0A8, 0);
        if (func_805FEF74(D_8076A0A8) != 0) {
            map = D_8074809C[slot];
            exit = D_807480AC[slot];
            if (map && map) {}
            if (flagGet(D_807480BC[slot], 0, exit) == 0) {
                if (map == 0x57) {
                    exit = 0x15;
                } else {
                    exit = 0;
                }
            }
            if (func_8068ABE0(map) == 0) {
                func_805FF378(map, exit);
            }
        } else {
            func_80600044(slot);
        }
        break;
    case 0x31:
        if (cmd->c & 0x100) {
            func_8070B308(2);
            func_805FF158(0);
        }
        switch (cmd->c & 0xFF) {
        case 0:
            flag = 0;
            break;
        case 1:
            flag = 1;
            break;
        case 2:
            flag = 3;
            break;
        }
        func_805FF9AC(cmd->a, cmd->b, 0, flag);
        break;
    case 0x32:
        func_805FF628(cmd->a, cmd->b);
        break;
    case 0x2F:
        func_8060B49C(D_807FBB48, cmd->a);
        break;
    case 0x11:
        modelAnimEntryStart(csId, cmd->a, cmd->b);
        break;
    case 0x12:
        modelAnimEntryStop(csId, cmd->a);
        break;
    case 0x13:
        modelAnimEntryClearTime(csId, cmd->a);
        break;
    case 0x14:
        modelAnimEntrySetUnkC(csId, cmd->a, cmd->b);
        break;
    case 0x15:
        modelAnimEntrySetUnkF(csId, cmd->a, cmd->b);
        break;
    case 0x16:
        modelAnimEntrySetUnk10(csId, cmd->a, cmd->b);
        break;
    case 0x17:
        modelAnimEntryResetFrame(csId, cmd->a, cmd->b);
        break;
    case 0x18:
        modelAnimEntrySetUnk12(csId, cmd->a, cmd->b);
        break;
    case 0x1A:
        modelAnimEntrySetTime(csId, cmd->a, cmd->b, cmd->c / 100.0);
        break;
    case 0xE:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        b = cmd->b;
        b &= 0xFF;
        if (cs->unk10[i] < 0) {
            b &= 2;
            cs->unk10[i] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, 0);
        }
        break;
    case 0x7D:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        b = cmd->b;
        b &= 0xFF;
        if (cs->unk10[i] < 0) {
            b &= 2;
            cs->unk10[i] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, D_80748094);
        }
        break;
    case 0xF:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 0x7F;
        sfxPlayFromTargetSlot(csId, cmd->a, vol, pan, i, c, 0.3f);
        break;
    case 0x7E:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (!vol) {
            vol = 0xFF;
        }
        i = cmd->b & 0x7F;
        if (D_80748094 > 0) {
            pitch = c;
            modelSlotGetNodePos(csId, 1, D_80748094, &sx, &sy, &sz);
            func_806086CC(sx, sy, sz, cmd->a, vol, pan, i, pitch, 0.3f, 0);
        } else {
            func_80609140(cmd->a, 0x7FFF, 0x427C0000, (u32)pan / 127.0, 0, 0);
        }
        break;
    case 0x10:
        if (cs->unk10[cmd->b] >= 0) {
            func_80605380(cs->unk10[cmd->b]);
            cs->unk10[cmd->b] = -1;
        }
        break;
    case 0x48:
        sfxSetVolumeAndPan(cs->unk10[cmd->a], cmd->b * 0.0001220703125, cmd->c);
        break;
    case 0xA:
        cs->unk50 = cmd->a;
        cs->unk78 = cmd->b / 100.0f;
        cs->unk7C = cmd->c / 100.0f;
        break;
    case 0xB:
        cs->unk80 = (f32)cmd->a;
        cs->unk82 = (f32)cmd->b;
        break;
    case 0xC:
        cs->unk84 = (f32)cmd->a;
        cs->unk86 = (f32)cmd->b;
        break;
    case 0xD:
        cs->unk88 = (f32)cmd->a;
        cs->unk8A = (f32)cmd->b;
        break;
    case 0x9:
        if (D_807F61FC != D_807F621C || D_807F6204 != D_807F6224) {
            func_80642480(cmd->a, csId);
        }
        break;
    case 0x41:
        D_807F6904 = 1;
        break;
    case 0x6:
        cs->unk14[cmd->a] = cmd->b / 10.0f;
        break;
    case 0x0:
        func_80642748(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x8:
        func_80642844(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x1E:
        func_80642748(cmd->a, cmd->b, cs, csId, 0);
        break;
    case 0x1D:
        func_80642844(cmd->a, cmd->b, cs, csId, 0);
        break;
    case 0x3:
        if (cmd->a == 0) {
            cs->unk44[cmd->c] = cmd->b;
        } else {
            cs->unk44[cmd->c] = cs->unk14[cmd->b];
        }
        break;
    case 0x65:
        cs->unk4B[cmd->b] += cmd->a;
        break;
    case 0x1:
        cs->unk4B[cmd->b] = cmd->a;
        break;
    case 0x5:
        if (func_806418E8(cmd->a, cmd->b, cmd->c) == 0) {
            return;
        }
        break;
    case 0x2D:
        i = 0;
        for (; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->unk60 & 0x2000) && actor->unk110 == 1 && csId == actor->unk10C) {
                if (cmd->a != 0) {
                    actor->unk68 |= 4;
                } else {
                    actor->unk68 &= ~4;
                }
            }
        }
        break;
    case 0x7:
        D_80747E70[cmd->a](cs, csId, cmd->b, cmd->c);
        break;
    case 0x37:
        actorAppendCallback(D_807FC924->unk4, 0, 0x400000, CMDB(cmd)->a, 0, 0);
        break;
    case 0x19:
        playerStateQueueCallback(cmd->a, 0, 0);
        break;
    case 0x2C:
        modelSlotGetNodePos(csId, 1, cmd->a, &cx, &cy, &cz);
        func_8067A9F0(0, D_807FC924->unk4, cx, cy, cz);
        break;
    case 0x2B:
        func_80636014(csId, 1, CMDB(cmd)->a);
        break;
    case 0x1B:
        if (D_807F6240[cmd->a] != -1) {
            modelSlotGetNodePos(D_807F6240[cmd->a], 1, cmd->b, &D_807F621C, &D_807F6220, &D_807F6224);
        }
        break;
    case 0x1C:
        if (D_807F6240[cmd->a] != -1) {
            idx = hashTableLookup(D_807F6240[cmd->a]);
            if (idx != -1) {
                if (D_807F6000[idx].unk7C != NULL) {
                    found = 1;
                    D_807F6000[idx].unk7C[cmd->b + 0x48] += cmd->c;
                }
            }
        }
        if (found == 0) {
            return;
        }
        break;
    case 0x2:
        func_80723284(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x1F:
        func_807232EC(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x20:
        func_80723380(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x21:
        func_80723320(cs->unk38, cmd->a);
        break;
    case 0x24:
        func_8072334C(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x22:
        cs->unk38 = func_80723020(0, cmd->a, CMDB(cmd)->b, D_807F621C, D_807F6220, D_807F6224, cmd->c);
        break;
    case 0x23:
        func_80723428(cs->unk38);
        cs->unk38 = -1;
        break;
    case 0x4:
        func_80723484(cs->unk38);
        func_807238D4(cs->unk38, &D_807F621C, &D_807F6220, &D_807F6224);
        break;
    case 0x27:
        modelSlotSetNodeAnimMode(csId, cmd->a, CMDB(cmd)->b);
        break;
    case 0x28:
        modelSlotSetNodeFrame(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x42:
        modelSlotSetNodeScrollSpeed(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x29:
        cam = D_807FC924->unk4->unk174;
        camStartShakeFromPoint(cam->unk104, CMDB(cmd)->a, cmd->b, D_807F621C, D_807F6220, D_807F6224, D_807F6906, D_807F6908);
        break;
    case 0x44:
        D_807F6906 = cmd->a;
        D_807F6908 = cmd->b;
        break;
    case 0x2A:
        ((CsModelSlot2 *)D_807F6000)[hashTableLookup(csId)].unk3C = cmd->a;
        break;
    case 0x2E:
        mapByteArraySet(cmd->a, CMDB(cmd)->b);
        break;
    case 0x38:
        mapObjectSetByte(cmd->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x61:
        if (cmd->c != 0) {
            sfxAllocateChannel(cmd->a, cmd->c / 255.0);
        } else {
            sfxAllocateChannel(cmd->a, 1.0f);
        }
        break;
    case 0x6F:
        sfxStopChannel(cmd->a, CMDB(cmd)->b);
        break;
    case 0x70:
        seqRouteChannelVolume(cmd->a, cmd->b / 255.0);
        break;
    case 0x71:
        sfxSetChannelTempo(cmd->a, cmd->b * 0.0001220703125);
        break;
    case 0x43:
        if (cmd->a == 1) {
            cs->unk8 = cs->unk14[cmd->b];
            cs->unkC = cs->unk14[cmd->c];
        } else {
            cs->unk8 = cmd->b / 10.0f;
            cs->unkC = cmd->c / 10.0f;
        }
        break;
    case 0x49:
        func_8067ABC0(0, D_807FC924->unk4, CMDB(cmd)->a, cmd->b, cmd->c, D_807F621C, D_807F6220, D_807F6224);
        break;
    case 0x4D:
        idx = modelSlotAppend(cmd->a, D_807F690C, D_807F6910, D_807F6914, D_807F6910 - D_807F6218, 0);
        if (cmd->b == 0) {
            func_80641B00(idx, csId, cmd->c);
        }
        break;
    case 0x51:
        func_806F4F50(csId, D_807F621C, D_807F6220, D_807F6224);
        break;
    case 0x5E:
        func_80641874(cmd->a, cmd->b);
        break;
    case 0x8A:
        func_806417BC(cmd->a, cmd->b);
        break;
    case 0x63:
        func_8068B830(cmd->a, cmd->b, cmd->c);
        break;
    case 0x64:
        func_8068B8FC();
        break;
    case 0x56:
        func_80724994(1, cmd->a, 0, 0, 0);
        break;
    case 0x59:
        func_80724994(3, cmd->a, cmd->b, 0, 0);
        break;
    case 0x58:
        if (func_805FFE50(cmd->a, cmd->b, cmd->c) == 0) {
            func_8063DB3C(cmd->a, cmd->b, cmd->c);
        }
        break;
    case 0x77:
        func_80650794(csId, cmd->a, CMDB(cmd)->b, cmd->c / 1000.0);
        break;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/42630/func_8063FA48.s")
#endif

typedef struct CsA1Cam {
    /* 0x000 */ u8 pad0[0x245];
    /* 0x245 */ u8 unk245;
} CsA1Cam;

void func_80641724(s16 arg0) {
    CsA1Cam *cam;

    cam = D_807FC924->unk4->unk174;
    switch (arg0) {
        case 0x33:
        case 0xBC:
        case 0x125:
        case 0x126:
        case 0x127:
        case 0x128:
        case 0x129:
        case 0x229:
        case 0x22A:
        case 0x22B:
            cam->unk245 = 0x3C;
            break;
    }
}

void func_8067AB20(void *, void *, s32, s32, s16 *, s32);

void func_806417BC(s16 arg0, s16 arg1) {
    s32 i;
    Actor *actor;
    s16 sp44[2];

    sp44[0] = 0;
    sp44[1] = arg1;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if ((u32)actor->unk58 == arg0) {
            func_8067AB20(0, actor, 0x01000000, 1, sp44, 0);
        }
    }
}

void heapFreeDeferred(void *);
void actorFindActiveByType(s32, void *);

void func_80641874(s16 arg0, s16 arg1) {
    s16 *sp24;
    void *sp20;

    sp24 = func_80610FE8(4);
    heapFreeDeferred(sp24);
    sp24[1] = arg0;
    sp24[0] = arg1;
    actorFindActiveByType(0xE, &sp20);
    func_8067AB20(0, sp20, 0x01000000, 1, sp24, 0);
}

s32 func_806418E8(s16 a, s16 b, s16 c) {
    s16 t = D_807F6240[a];
    s16 slot;

    if (t != -1) {
        slot = hashTableLookup(t);
        if (slot != -1 && D_807F6000[slot].unk7C != NULL) {
            D_807F6000[slot].unk7C[c + 0x48] = b;
            return 1;
        }
    }
    return 0;
}

typedef struct CsA2Obj54 {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 pad55[3];
    /* 0x58 */ s32 unk58;
} CsA2Obj54;

void func_8064199C(void *obj, s16 b, s16 c) {
    CsA2Obj54 *o = obj;

    o->unk54 = b;
    switch (b & 0xFF) {
    case 3:
    case 4:
    case 6:
        o->unk58 = c * c;
        break;
    case 5:
        o->unk58 = c;
        break;
    }
}

typedef struct CsA2Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x29C - 8];
    /* 0x29C */ s16 unk29C;
} CsA2Player;
typedef struct CsA2Cam {
    /* 0x00 */ u8 pad0[0xBC];
    /* 0xBC */ s16 unkBC;
} CsA2Cam;

s32 func_806419F8(void) {
    CsA2Cam *cam = D_807FC924->unk4->unk174;

    if ((D_807FBB4C->unk154 == 0x42 && (cam->unkBC == 0x62 || cam->unkBC == 0x88 || cam->unkBC == 0x17)) || D_807FBB4C->unk154 == 0x52 ||
        D_807FBB4C->unk154 == 0x67 || ((CsA2Player *)D_807FC924)->unk29C == 0x1C || ((CsA2Player *)D_807FC924)->unk29C == 0x53) {
        return 0;
    }
    return 1;
}

void modelSlotFreeByIndex(s16, s32);

void func_80641A78(void) {
    s32 i;

    for (i = 0; i < D_807F6938; i++) {
        modelSlotFreeByIndex(D_807F6240[D_807F6918[i]], 1);
    }
}

typedef struct CsA2Aux {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 pad49[0x57];
    /* 0xA0 */ s32 unkA0;
} CsA2Aux;

void func_80641B00(s16 a, s16 b, s16 c) {
    a = hashTableLookup(a);
    b = hashTableLookup(b);
    D_807F6000[a].unk7C = func_80610FE8(0xA4);
    func_8063DED0(D_807F6000[a].unk7C);
    ((CsA2Aux *)D_807F6000[a].unk7C)->unk48 = c;
    ((CsA2Aux *)D_807F6000[a].unk7C)->unkA0 = ((CsA2Aux *)D_807F6000[b].unk7C)->unkA0;
}

void func_80641BCC(s16 a, s16 b, s16 csId) {
    s32 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->unk60 & 0x2000) && actor->unk58 == a && csId == actor->unk10C) {
            if (b != 0) {
                actor->unk68 |= 4;
            } else {
                actor->unk68 &= ~4;
            }
        }
    }
}

void func_80641C98(s16 a, s16 b, s16 csId) {
    s32 x;
    s32 i;
    Actor *actor;

    switch (b) {
    case 0:
        x = 1;
        break;
    case 1:
        x = 2;
        break;
    case 2:
        x = 0x3C;
        break;
    }
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->unk60 & 0x2000) && actor->unk58 == a && csId == actor->unk10C) {
            actorAppendCallback(actor, 0, 0x800, x, 0, 0);
        }
    }
}

s32 func_80678014(s32);
u16 camStartPath(void *, s16, s32);

void func_80641DA0(void *cs, s16 camIdx, s16 mode, s16 c) {
    s32 flag;

    if (((CsState *)cs)->unk94 == NULL && func_80678014(0x14) != 0) {
        ((CsState *)cs)->unk94 = D_807FBB44;
        D_807FBB44->unk144 = 1;
        D_807FBB44->unk7C = D_807F621C;
        D_807FBB44->unk80 = D_807F6220;
        D_807FBB44->unk84 = D_807F6224;
        D_807FBB44->unkE6 = D_807F622C * 4096.0f / 360.0f;
        if (*(u8 *)&D_807F693F != 0) {
            D_807FBB44->unk15E = c;
        }
        if (*(u8 *)&D_807F693F != 0) {
            flag = 4;
        } else {
            flag = 0;
        }
        switch (mode) {
        case 0:
            camStartPath(((CsState *)cs)->unk94, camIdx, (flag | 1 | D_807F693C) & 0xFF);
            return;
        case 1:
            camStartPath(NULL, camIdx, (flag | 1 | D_807F693C) & 0xFF);
            return;
        case 2:
            camStartPath(spawnNodeActivate(c, 0x400), camIdx, (flag | 1 | D_807F693C) & 0xFF);
            break;
        }
    }
}

void func_80641F68(void) {
}

extern u8 D_80750AB4;
f32 sqrtf(f32);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

typedef struct CsA2Ply {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x270 - 8];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ u8 pad278[0x2F0 - 0x278];
} CsA2Ply;
#define CSA2_PLY ((CsA2Ply *)D_807FC924)

u8 func_80641F70(s16 radius) {
    f32 sx;
    f32 sy;
    u8 i;
    Actor *a;
    f32 dx;
    f32 dy;
    f32 dz;
    u8 ret = 0;

    for (i = 0; i < D_80750AB4; i++) {
        if (CSA2_PLY[i].unk0 != 0) {
            a = CSA2_PLY[i].unk4;
            dx = D_807F621C - a->unk7C;
            dy = D_807F6220 - a->unk80;
            dz = D_807F6224 - a->unk84;
            dx *= dx;
            dy *= dy;
            dz *= dz;
            if (sqrtf(dx + dy + dz) < radius) {
                camProjectToScreen(D_807F621C, D_807F6220, D_807F6224, &sx, &sy, 0, 1.0f, i);
                if ((s16)sx >= CSA2_PLY[i].unk270 + 0x14 && (s16)sy >= CSA2_PLY[i].unk272 + 0x14 &&
                    CSA2_PLY[i].unk274 - 0x14 >= (s16)sx && CSA2_PLY[i].unk276 - 0x14 >= (s16)sy) {
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

s32 func_8064216C(s16 radius, f32 x, f32 y, f32 z) {
    f32 dx = D_807F621C - x;
    f32 dy = D_807F6220 - y;
    f32 dz = D_807F6224 - z;

    dx *= dx;
    dy *= dy;
    dz *= dz;
    return (u8)(sqrtf(dx + dy + dz) < radius);
}

typedef struct CsA3Player {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x2F0 - 0x21C];
} CsA3Player; // size = 0x2F0

s32 func_8064216C(s16, f32, f32, f32);

s32 func_80642204(s16 arg0) {
    u8 i;
    CsA3Player *p;

    for (i = 0; i < D_80750AB4; i++) {
        p = (CsA3Player *)D_807FC924 + i;
        if (p->unk0 != 0) {
            Actor *a = p->unk4;
            if (func_8064216C(arg0, a->unk7C, a->unk80, a->unk84)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_806422D8(s16 arg0) {
    u8 i;
    CsA3Player *p;

    for (i = 0; i < D_80750AB4; i++) {
        p = (CsA3Player *)D_807FC924 + i;
        if (p->unk0 != 0 && func_8064216C(arg0, p->unk210, p->unk214, p->unk218)) {
            return 1;
        }
    }
    return 0;
}


s32 func_806423A8(s16 arg0, s16 arg1, s16 arg2) {
    s16 i;
    Actor *a;

    for (i = arg1; i <= arg2; i++) {
        if (spawnNodeHasActor(i)) {
            a = spawnNodeActivate(i, 0);
            if (a != NULL) {
                if (func_8064216C(arg0, a->unk7C, a->unk80, a->unk84)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);

void func_80642480(s16 arg0, s16 arg1) {
    s32 pad;
    f32 y;

    switch (arg0) {
    case 0:
        y = D_807F6220;
        if (collisionCheckGroundAtPoint(D_807F621C, D_807F6224, &y)) {
            D_807F6220 = y + D_807F6238;
        }
        break;
    case 1:
        break;
    }
}

s32 func_80642500(f32 *arg0, s16 arg1, s16 arg2) {
    u8 idx;
    u8 mode;
    s32 ret;
    f32 v;
    f32 th;

    ret = 0;
    mode = arg1 & 0xFF;
    idx = (arg1 >> 8) & 0xFF;
    v = arg0[idx];
    switch (mode) {
    case 0:
        th = arg2 / 10.0f;
        if (((th < v) ? (v - th) : (th - v)) < 0.05) {
            ret = 1;
        }
        break;
    case 1:
        if (arg2 / 10.0f < v) {
            ret = 1;
        }
        break;
    case 2:
        if (v < arg2 / 10.0f) {
            ret = 1;
        }
        break;
    }
    return ret;
}


s32 func_806425FC(s16 arg0, s16 arg1) {
    f32 v;
    f32 th;
    s32 ret;
    u8 mode;

    ret = 0;
    switch ((u8)((arg0 >> 8) % 255)) {
    case 0:
        if (D_807F6208 && D_807F6208) {
        }
        v = D_807F6208;
        break;
    case 1:
        v = D_807F620C;
        break;
    case 2:
        v = D_807F6210;
        break;
    }
    mode = arg0 & 0xFF;
    switch (mode) {
    case 0:
        th = arg1 / 10.0f;
        if (((th < v) ? (v - th) : (th - v)) != 0.1) {
            ret = 1;
        }
        break;
    case 1:
        if (arg1 / 10.0f < v) {
            ret = 1;
        }
        break;
    case 2:
        if (v < arg1 / 10.0f) {
            ret = 1;
        }
        break;
    }
    return ret;
}


void func_80642748(s16 arg0, s16 arg1, void *cs, s16 arg3, u8 arg4) {
    f32 v;
    u8 lo;
    u8 hi;

    lo = arg0 & 0xFF;
    hi = (arg0 >> 8) & 0xFF;
    v = arg1 / 10.0f;
    if (lo == 1) {
        v = ((CsState *)cs)->unk14[arg1];
    }
    switch (hi) {
    case 0:
        if (arg4 == 1) {
            D_807F6228 += v;
        } else {
            D_807F6228 = v;
        }
        break;
    case 1:
        if (arg4 == 1) {
            D_807F622C += v;
        } else {
            D_807F622C = v;
        }
        break;
    case 2:
        if (arg4 == 1) {
            D_807F6230 += v;
        } else {
            D_807F6230 = v;
        }
        break;
    }
}

void func_80642844(s16 arg0, s16 arg1, void *cs, s16 arg3, u8 arg4) {
    f32 v;
    u8 lo;
    u8 hi;

    lo = arg0 & 0xFF;
    hi = (arg0 >> 8) & 0xFF;
    v = arg1 / 10.0f;
    if (lo == 1) {
        v = ((CsState *)cs)->unk14[arg1];
    }
    switch (hi) {
    case 0:
        if (arg4 == 1) {
            D_807F621C += v;
        } else {
            D_807F621C = v;
        }
        break;
    case 1:
        if (arg4 == 1) {
            D_807F6220 += v;
        } else {
            D_807F6220 = v;
        }
        break;
    case 2:
        if (arg4 == 1) {
            D_807F6224 += v;
        } else {
            D_807F6224 = v;
        }
        break;
    }
}

u32 func_806119A0(void);
void func_807149FC(s32);
void func_80714950(s32);
void func_8071498C(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80717D4C(void);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
extern u8 D_8071FC58[];

void func_80642940(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i != 1U; i++) {
        x = (func_806119A0() / 10000 % 200) / 10.0 - 10.0;
        y = (func_806119A0() / 10000 % 200) / 10.0 - 7.0;
        z = (func_806119A0() / 10000 % 200) / 10.0 - 10.0;
        func_807149B8(1);
        func_807149FC(2);
        func_80714950(0x64);
        func_8071498C(func_80717D4C);
        func_80714CC0(D_8071FC58, 0.5f, D_807F621C + x, D_807F6220 + y, D_807F6224 + z);
    }
    lightAdd(D_807F621C, D_807F6220, D_807F6224, 0.0f, 0.0f, 0.0f, 300.0f, 0, 0xA6, 0x30, 0xFF);
}

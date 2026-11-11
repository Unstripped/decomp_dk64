#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "cutscene.h"
#include "sched.h"
#define PROTO_SKIP_hudSpawnCountdownTimer // PROTO: The number of arguments doesn't agree with the number in the
#define PROTO_SKIP_modelAnimEntrySetUnkC // FAKE: callee prototype steer
#define PROTO_SKIP_sfxSlotAllocateSource // FAKE: callee prototype steer
#define PROTO_SKIP_effectSetDepth // FAKE: callee prototype steer
#include "proto/global/10130.h"
#include "proto/global/104F0.h"
#include "proto/global/10E1D0.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/127B00.h"
#include "proto/global/1295B0.h"
#include "proto/global/1332B0.h"
#include "proto/global/133A90.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/36880.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/54150.h"
#include "proto/global/55B20.h"
#include "proto/global/5E020.h"
#include "proto/global/5E2F0.h"
#include "proto/global/63810.h"
#include "proto/global/63EC0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8D3E0.h"
#include "proto/global/8F4B0.h"
#include "proto/global/A7710.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
void effectSetDepth(s8); // FAKE: callee prototype steer (shared header has u8)

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;

typedef struct CsTimer {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 pad7;
} CsTimer;

typedef struct CsSpawnReq {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} CsSpawnReq;

// .bss 0x807F61B0-0x807F6940
CsTimer gCsTimerQueue[8];
CsSpawnReq D_807F61F0;
f32 D_807F61FC;
f32 D_807F6200;
f32 D_807F6204;
f32 D_807F6208;
f32 D_807F620C;
f32 D_807F6210;
f32 D_807F6214;
f32 D_807F6218;
f32 gCsPosX;
f32 gCsPosY;
f32 gCsPosZ;
f32 gCsRotX;
f32 gCsRotY;
f32 gCsRotZ;
f32 gCsScale;
f32 gCsGroundOffset;
s32 D_807F623C;
s16 gCsModelIds[600];
u8 gCsVarsDirty[0x212];
s8 D_807F6902;
s8 D_807F6903;
s16 D_807F6904;
s16 D_807F6906;
s16 D_807F6908;
s16 D_807F690A;
f32 D_807F690C;
f32 D_807F6910;
f32 D_807F6914;
s16 gCsTrackedModels[16];
u8 gCsTrackedModelCount;
u8 D_807F6939;
s16 D_807F693A;
s16 D_807F693C;
u8 D_807F693E;
u8 D_807F693F;

void csModelIdTableReset(void) {
    s32 i = 0;
    s32 j;

    do {
        gCsModelIds[i] = -1;
        i++;
    } while (&gCsModelIds[i] < &gCsModelIds[600]);
    for (j = 0; j < 0x212; j++) { gCsVarsDirty[j] = 0; } // LAYOUT: one-line loop keeps the as1 unroll schedule (Q0364)
}

struct CsModelSlot;
extern struct CsModelSlot *gModelSlots;

typedef struct CsLoadNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ u8 unk2[0x28];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ u8 unk2C[0x20];
    /* 0x4C */ struct CsLoadNode *unk4C;
} CsLoadNode;

typedef struct CsLoadState {
    /* 0x00 */ u8 unk0[0x9C];
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ u8 pad9E[2];
    /* 0xA0 */ CsLoadNode *unkA0;
} CsLoadState;

typedef struct CsLoadSlot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ CsLoadState *unk7C;
    /* 0x80 */ u8 pad80[0xA];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsLoadSlot; /* 0x90 */

s16 csModelSlotGetTableIndex(s16 modelId) {
    return ((CsLoadSlot *)gModelSlots)[hashTableLookup(modelId)].unk8A;
}

s16 csModelIdTableAlloc(s16 modelId, u8 isLowTable) {
    s32 i;

    if (isLowTable == 0) {
        i = 0x226;
    } else {
        i = 0;
    }
    while (gCsModelIds[i] != -1) {
        i++;
    }
    gCsModelIds[i] = modelId;
    return i;
}


void csModelStateSetFirstByte(s16 modelIndex, s16 val) {
    csModelStateSetByte(modelIndex, val, 0);
}

void csModelStateSetByte(s16 modelIndex, s16 val, s16 byteOffset) {
    s16 slot;

    slot = hashTableLookup(gCsModelIds[modelIndex]);
    if (slot != -1) {
        ((CsLoadSlot *)gModelSlots)[slot].unk7C->unk0[byteOffset + 0x48] = val;
        ((CsLoadSlot *)gModelSlots)[slot].unk7C->unk0[0x54] = 1;
    }
}


extern CsTimer gCsTimerQueue[8];
extern struct CsSpawnReq D_807F61F0;

void csTimerQueueClear(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        gCsTimerQueue[i].unk6 = 0;
    }
}

void csTimerQueueAdd(s16 timerId, s16 modelIndex, s16 val) {
    s16 i = 0;
    s32 found = 0;

    while (!found && i < 8) {
        if (gCsTimerQueue[i].unk6 == 0) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found) {
        gCsTimerQueue[i].unk6 = 1;
        gCsTimerQueue[i].unk0 = timerId;
        gCsTimerQueue[i].unk2 = modelIndex;
        gCsTimerQueue[i].unk4 = val;
    }
}

void csTimerQueueFire(s16 timerId) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCsTimerQueue[i].unk6 != 0 && timerId == gCsTimerQueue[i].unk0) {
            csModelStateSetFirstByte(gCsTimerQueue[i].unk2, gCsTimerQueue[i].unk4);
            gCsTimerQueue[i].unk6 = 0;
        }
    }
}

extern s8 D_807F6903;
extern s16 D_807F693C;
extern u8 D_807F693E;
extern u8 D_807F693F;

void csScriptLoad(s16 *scriptData) {
    s16 n;
    s16 *p;
    s32 slot;
    s16 id;
    s16 m;
    s16 c1;
    s16 c2;
    s32 len1;
    s32 len2;
    CsLoadNode **tail;
    CsLoadNode *node;

    n = *scriptData;
    p = scriptData + 1;
    if (n != 0) {
        do {
            id = *p;
            p++;
            slot = hashTableLookup(gCsModelIds[id]);
            if (slot != -1) {
                ((CsLoadSlot *)gModelSlots)[slot].unk7C = heapAlloc(0xA4);
                csStateInit(((CsLoadSlot *)gModelSlots)[slot].unk7C);
                ((CsLoadSlot *)gModelSlots)[slot].unk7C->unkA0 = NULL;
                m = p[0];
                tail = &((CsLoadSlot *)gModelSlots)[slot].unk7C->unkA0;
                ((CsLoadSlot *)gModelSlots)[slot].unk7C->unk9C = p[1];
                p += 2;
                while (m != 0) {
                    node = heapAlloc(0x50);
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
    D_807F61F0.unk0 = NULL;
    D_807F61F0.unk4 = NULL;
    D_807F61F0.unk8 = 0;
}


void csStateFree(CsStateFull *loadState) {
    CsNode *node;
    CsNode *next;

    if (loadState->unk0 != NULL) {
        heapFree(loadState->unk0);
    }
    node = loadState->unkA0;
    while (node != NULL) {
        next = node->unk4C;
        heapFree(node);
        node = next;
    }
    heapFree(loadState);
}

void csStateInit(CsStateFull *cs) {
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

typedef struct CsStateSlot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[0x10];
} CsStateSlot; /* 0x90 */

struct CsModelSlot;
extern u8 gCsVarsDirty[];

void csModelStateSetVars(s32 modelIndex, u8 *varsData) {
    s16 slot;

    slot = hashTableLookup(gCsModelIds[modelIndex]);
    if (slot != -1) {
        memcpy(((CsStateSlot *)gModelSlots)[slot].unk7C + 0x14, varsData, 0x20);
        gCsVarsDirty[modelIndex] = 1;
    }
}

void csStateTickTimers(CsStateFull *cs) {
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
extern f32 gCsPosX;
extern f32 gCsPosY;
extern f32 gCsPosZ;
extern f32 gCsRotX;
extern f32 gCsRotY;
extern f32 gCsRotZ;
extern f32 gCsScale;
extern f32 gCsGroundOffset;
extern s16 D_807F6904;
extern s16 D_807F6906;
extern s16 D_807F6908;
extern f32 D_807F690C;
extern f32 D_807F6910;
extern f32 D_807F6914;

void csStateUpdate(CsStateFull *cs, s16 csId) {
    CsNode *node;
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
        modelSlotGetTransformVectors(csId, &gCsPosX, &gCsPosY, &gCsPosZ, &gCsRotX, &gCsRotY,
                                     &gCsRotZ, &gCsScale, &gCsGroundOffset, 1);
        csStateIntegrateMotion(cs);
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
                ok = csCondEval(&node->unk2[i], (CsState *)cs, csId) & 0xFF;
                i++;
            }
            if (ok) {
                for (j = 0; j < node->unk2A; j++) {
                    csCmdExec(&node->unk2C[j], (CsState *)cs, csId);
                }
            }
            node = node->unk4C;
        }
        stepped = modelSlotStepAnimations(csId);
        if (D_807F61FC != gCsPosX || D_807F6200 != gCsPosY || D_807F6204 != gCsPosZ ||
            D_807F6208 != gCsRotX || D_807F620C != gCsRotY || D_807F6210 != gCsRotZ ||
            D_807F6214 != gCsScale || stepped != 0) {
            moved = D_807F61FC != gCsPosX || D_807F6200 != gCsPosY || D_807F6204 != gCsPosZ;
            rotated = D_807F6208 != gCsRotX || D_807F620C != gCsRotY || D_807F6210 != gCsRotZ;
            scaleXZ = D_807F6214 != gCsScale;
            scaleY = D_807F6218 != gCsGroundOffset;
            modelSlotTransformBoundsAndNodes(csId, gCsPosX, gCsPosY, gCsPosZ, gCsRotX, gCsRotY, gCsRotZ, gCsScale,
                          gCsGroundOffset, moved, rotated, scaleXZ, scaleY, 1);
            cs->unk4E = 1;
        }
        if (D_807F6904 != 0) {
            modelSlotUpdateGroundCoords(csId, 1);
        }
        csStateEndUpdate(cs);
    }
}

extern u32 gGlobalPauseFlags;

void csStateEndUpdate(CsStateFull *cs) {
    Actor *actor;

    cs->unk34 = gCsRotY - D_807F620C;
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
        cs->unk94->x = gCsPosX; // FAKE: re-read through cs (not actor) steers the address register
        actor->y = gCsPosY;
        actor->z = gCsPosZ;
        actor->yaw = gCsRotY * 4096.0f / 360.0f;
        if (gGlobalPauseFlags & 0x1000) {
            gGlobalPauseFlags &= ~0x1000;
            actorDespawn(cs->unk94);
            cs->unk94 = NULL;
        }
    }
    D_807F693F = 0;
}

extern u32 gFrameCounter;

void csUpdateStepAndInterpolation(CsStateFull *cs) {
    s16 a;
    s16 b;

    if (gFrameCounter != cs->unk4) {
        b = cs->unk64;
        a = cs->unk62;
        cs->unk4 = gFrameCounter;
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

void csStateIntegrateMotion(CsStateFull *cs) {
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
                gCsPosX += cs->unk8C * cs->unk74;
                gCsPosZ += cs->unk90 * cs->unk74;
                if (gCsPosX < cs->unk80) {
                    gCsPosX = cs->unk80;
                }
                if (gCsPosZ < cs->unk82) {
                    gCsPosZ = cs->unk82;
                }
                if (cs->unk84 < gCsPosX) {
                    gCsPosX = cs->unk84;
                }
                if (cs->unk86 < gCsPosZ) {
                    gCsPosZ = cs->unk86;
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
                gCsRotY += cs->unk74;
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
                gCsRotY += cs->unk74;
            }
            break;
    }
}

// Cutscene condition evaluator (csCondEval): one CsCmd per call, nonzero = condition holds.
// Operand-order notes: two cases still need `field == ((s16 *)cmd)[N]` (instead of `== cmd->a/b`) for `bne field,arg`
// (a plain cmd->x leaf is canonicalised to the left operand and its ring temp comes first); the actor loops
// use their own pointer local `b` (not `a`, the player-loop pointer) and index `h` (not `k`).
typedef struct CsCondState {
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
} CsCondState;

// Stride view of gPlayerSlots (PlayerStruct): indexing the shared type directly swaps the
// `addu base,off` operands of the player loops; this record type reproduces the target.
typedef struct CsCondPlayer {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x2F0 - 0x8];
} CsCondPlayer; /* 0x2F0 */

typedef struct CsCondObj {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ u8 unk48[1];
} CsCondObj;

typedef struct CsCondSlot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[0xA];
} CsCondSlot; /* 0x90 */

typedef struct CsCondRow {
    /* 0x000 */ u8 e[8][0x5E];
    /* 0x2F0 */ u8 pad2F0[0x16];
} CsCondRow; /* 0x306 */

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern PlayerStruct *gPlayerSlots;
extern u8 *D_807FD568;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerInventory gPlayerInventoryTable[];
extern u8 gGameMode;
extern u8 gPlayerCharacterId;
extern s16 D_8076AEF2;
extern s32 (*gCsCondTable[])(CsState *, s16, s16, s16);

#define CS_COND_STATE ((CsCondState *)cs)
#define CS_COND_PLAYER ((CsCondPlayer *)gPlayerSlots)

s32 csCondEval(CsCmd *cmd, CsState *cs, s16 csId) {
    u8 neg;
    u8 ret;
    s16 type;
    Actor *a;
    CsCondPlayer *p;
    u8 found;
    s32 count;
    s32 k;
    s32 h;
    s16 sAnim;
    f32 fAnim;
    u8 uAnim;
    u8 i;
    f32 animProgress;
    u8 *q;
    PlayerState *playerState;
    u32 mask;
    Actor *b;

    if ((s16)cmd->op & 0x8000) {
        neg = 1;
    } else {
        neg = 0;
    }
    type = (s16)cmd->op & 0x7FFF;
    switch (type) {
    case 0x0:
        ret = 1;
        break;
    case 0x3D:
        ret = D_807F6903;
        break;
    case 0x3C:
        ret = cmd->a == gPlayerSlots->unk290;
        break;
    case 0x3A:
        if ((1 << cmd->a) & D_807F693E) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x39:
        if (cmd->a & gPrimaryPlayerActor->interactionType) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x38:
        ret = gPlayerCharacterId < 5;
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
        if (cmd->a == gPrimaryPlayerActor->floorSlopeType) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x35:
        if (cmd->a == gPrimaryPlayerActor->floorSurfaceType) {
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
        if (actorListIsIdActive(cmd->a) != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x28:
        if (CS_COND_STATE->unk9A & 1) {
            ret = 0;
        } else {
            ret = 1;
        }
        break;
    case 0x26:
        playerState = gPlayerSlots->actor->customState;
        if ((cmd->b + (cmd->a << 16)) & playerState->stateFlags) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x27:
        playerState = gPlayerSlots->actor->customState;
        if ((cmd->b + (cmd->a << 16)) & playerState->prevStateFlags) {
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
        h = playerLookupKongByActorType(cmd->a);
        q = gPlayerInventoryTable[gCurrentPlayerIndex].kong[h].unk0;
        if (*q >= cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x24:
        a = spawnNodeActivate(cmd->a, 0);
        if (cmd->b == a->state) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x23:
        if (gGameMode == 1) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1D:
        if ((cmd->a == 0 && CS_COND_STATE->unk48[cmd->c] < cmd->b) || (cmd->a == 1 && cmd->b < CS_COND_STATE->unk48[cmd->c])) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1C:
        h = modelAnimEntryGetUnkC(csId, cmd->a);
        if ((cmd->b == 0 && h < cmd->c) || (cmd->b == 1 && cmd->c < h)) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x16:
        mask = cmd->b + (cmd->a << 16);
        if (gGlobalPauseFlags & mask) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x15:
        ret = modelAnimEntryIsActive(csId, cmd->a);
        break;
    case 0xC:
        if (D_807F61FC != gCsPosX || D_807F6200 != gCsPosY || D_807F6204 != gCsPosZ ||
            D_807F6208 != gCsRotX || D_807F620C != gCsRotY || D_807F6210 != gCsRotZ ||
            D_807F6214 != gCsScale) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x8:
        ret = CS_COND_STATE->unk51;
        break;
    case 0x9:
        if (CS_COND_STATE->unk52 != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x7:
        ret = csCompareVar(CS_COND_STATE->unk14, cmd->a, cmd->b);
        break;
    case 0x31:
        if (((CsCondSlot *)gModelSlots)[hashTableLookup(gCsModelIds[cmd->a])].unk7C[cmd->c + 0x48] == ((s16 *)cmd)[2]) { // FAKE: punned cmd->b read keeps bne field,arg operand order
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1:
        k = CS_COND_STATE->unk48[cmd->b] - cmd->a;
        if (k == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x5:
        ret = csEvaluateParamCondition(cmd->a, cmd->b);
        break;
    case 0x4:
        if (CS_COND_STATE->unk44[cmd->b] == ((s16 *)cmd)[1]) { // FAKE: punned cmd->a read keeps bne field,arg operand order
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->attachMode == 1 && csId == a->cutsceneId) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xD:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->attachMode == 1 && csId == a->cutsceneId && cmd->a == a->unk10E) {
                    ret = 1;
                }
            }
        }
        break;
    case 0x11:
        found = 0;
        for (h = 0; h < gActiveActorCount && !found; h++) {
            b = gActiveActors[h].actor;
            if (!(b->flags & 0x2000) && cmd->a == b->actorType && b->attachMode == 1 && csId == b->cutsceneId) {
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
            b = gActiveActors[h].actor;
            if (!(b->flags & 0x2000) && cmd->a == b->actorType && b->attachMode == 1 && csId == b->cutsceneId &&
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
            b = gActiveActors[h].actor;
            if (!(b->flags & 0x2000) && cmd->a == b->actorType && csId == b->cutsceneId && cmd->b == b->unk10E) {
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
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->attachMode == 3 && cmd->a == a->unk12F && csId == a->cutsceneId) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xA:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->attachMode == 2 && csId == a->cutsceneId) {
                    ret = 1;
                } else {
                    ret = 0;
                }
            }
        }
        break;
    case 0xE:
        ret = csPosOnScreenOfNearPlayer(cmd->a);
        break;
    case 0x13:
        ret = csPlayerNearPos(cmd->a);
        break;
    case 0x20:
        ret = csPlayerSavedPosNearPos(cmd->a);
        break;
    case 0x29:
        ret = csSpawnNodeNearPos(cmd->a, cmd->b, cmd->c);
        break;
    case 0x6:
        ret = gCsCondTable[cmd->a](cs, csId, cmd->b, cmd->c);
        break;
    case 0xF:
        ret = pathPlaybackIsActive(CS_COND_STATE->unk38);
        break;
    case 0x10:
        if (CS_COND_STATE->unk5C != 0 && (cmd->b == -1 || cmd->b == CS_COND_STATE->unk5C) &&
            (actorLookupClass(CS_COND_STATE->unk5E) & cmd->a) && csIsPlayerInCutsceneState() != 0) {
            csSetCameraFollowModel(((CsCondSlot *)gModelSlots)[hashTableLookup(csId)].unk84);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x18:
        if (CS_COND_STATE->unk5C != 0 && (cmd->b == -1 || cmd->b == CS_COND_STATE->unk5C) && cmd->a == CS_COND_STATE->unk5E &&
            csIsPlayerInCutsceneState() != 0) {
            csSetCameraFollowModel(((CsCondSlot *)gModelSlots)[hashTableLookup(csId)].unk84);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x17:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (cmd->a == a->state) {
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
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
            if (p->unk0 != 0 && cmd->a == p->unk4->unk155) {
                ret = 1;
            }
        }
        break;
    case 0x19:
        if (cmd->a == gPrimaryPlayerActor->actorType) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1A:
        ret = cmd->a == gPlayerSlots->unk2C0;
        break;
    case 0x1B:
        ret = gPlayerSlots->sizeModeDirty;
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
        if (D_807F61F0.unk8 != 0) {
            if (D_807F61F0.unk0->state == 5) {
                ret = 1;
            } else {
                ret = 0;
            }
        } else {
            ret = 1;
        }
        break;
    case 0x2B:
        ret = D_807F61F0.unk8;
        break;
    case 0x33:
        animProgress = actorGetAnimProgress(gPrimaryPlayerActor);
        ret = 0;
        if (cmd->a == 0 && cmd->b < (s16)animProgress) {
            ret = 1;
        }
        if (cmd->a == 1 && (s16)animProgress < cmd->b) {
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

// Cutscene script command interpreter (csCmdExec): one 8-byte command per call.

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

extern CsCmdFunc gCsCmdTable[];
extern u8 D_80744824;
extern s8 D_80748094;
extern s16 D_8074809C[];
extern s16 D_807480AC[];
extern s16 D_807480BC[];
extern s32 gCurrentMap;
extern CsModelSlot *gModelSlots;
extern CsSpawnReq D_807F61F0;
extern s16 gCsTrackedModels[16];
extern u8 gCsTrackedModelCount;
extern s16 D_807F693A;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern u32 gGlobalCutsceneFlags;

void hudSpawnCountdownTimer(s32, s32, u8, void *);
void modelAnimEntrySetUnkC(); // FAKE: callee prototype steer
u8 sfxSlotAllocateSource(s16, s16, s32, s32, u8, f32, s8);  // FAKE: callee prototype steer

void csCmdExec(CsCmd *cmd, CsState *cs, s16 csId) {
    void *dm = &csId; // FAKE: address-taken csId keeps sel at sp+0xB3 (Q0174)
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
    PlayerState *cam;
    Actor *actor;
    s32 map;
    s32 b;
    s32 c;
    s32 exit;
    s16 flag;
    s32 pad[2];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pan;
    u8 vol;
    u8 pitch;
    f32 cx;
    f32 cy;
    f32 cz;
    u8 pan7;
    u8 vol7;

    found = 0;
    if (found) {} // FAKE: block boundary keeps found off a2
    switch (cmd->op) {
    case 0x95:
        D_807F693C = 0x80;
        break;
    case 0x92:
        ((PlayerState *)gPlayerSlots->actor->customState)->stateFlags |= 0x40000800;
        break;
    case 0x91:
        gPrimaryPlayerActor->speedXZ = cmd->a;
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
        dynamicBufferFree(&gModelSlots[hashTableLookup(csId)].unk28);
        break;
    case 0x8F:
        modelSlotTriBufferRelease(&gModelSlots[hashTableLookup(csId)].unk48);
        break;
    case 0x85:
        func_8062D1A8();
        break;
    case 0x83:
        slotQueueSetDisplayMode(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x80:
        eepromSavePlayerData();
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
        proxPathSetEndBehavior(csId, CMDB(cmd)->a, sel);
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
            if (!(actor->flags & 0x2000) && actor->attachMode == 1 && csId == actor->cutsceneId) {
                actorAppendCallback(actor, 0, 8, 0, 0, 0);
            }
        }
        break;
    case 0x75:
        volumeTriggerSetEnabled(cmd->a, CMDB(cmd)->b);
        break;
    case 0x78:
        modelSlotGetNodePos(csId, 1, cmd->a, &px, &py, &pz);
        cam = gPlayerSlots->actor->customState;
        cam->savedX = px;
        cam->savedY = py;
        cam->savedZ = pz;
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
            actor = gCurrentActor;
            D_807F61F0.unk4 = gSpawnedActor;
            gCurrentActor = gSpawnedActor;
            hudSpawnCountdownTimer(0xDC, 0x2A, CMDB(cmd)->a, &D_807F61F0);
            D_807F61F0.unk0 = gSpawnedActor;
            D_807F61F0.unk8 = 1;
            gCurrentActor = actor;
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
            b = (s32)D_807F61F0.unk4; if (b) {} // FAKE: live range of b (a3) splits the &D_807F61F0 piece (v0)
            actorDespawn(D_807F61F0.unk4);
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
        ((PlayerState *)gPlayerSlots->actor->customState)->stateFlags |= (cmd->a << 16) + cmd->b;
        break;
    case 0x3B:
        ((PlayerState *)gPlayerSlots->actor->customState)->stateFlags &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x8C:
        ((PlayerState *)gPlayerSlots->actor->customState)->stateFlags2 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x8B:
        ((PlayerState *)gPlayerSlots->actor->customState)->stateFlags2 &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x5D:
        screenSetTransitionFadeType(CMDB(cmd)->a);
        break;
    case 0x5C:
        zoneEntrySetDisabled(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x5B:
        playerRespawnResetPhysics(cmd->a);
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
        if (gCsTrackedModelCount != 16) {
            if (cmd->a != -2) {
                gCsTrackedModels[gCsTrackedModelCount] = cmd->a;
                gCsTrackedModelCount++;
            } else {
                gCsTrackedModels[gCsTrackedModelCount] = gModelSlots[hashTableLookup(csId)].unk8A;
                gCsTrackedModelCount++;
            }
        }
        break;
    case 0x50:
        if (gCsModelIds[cmd->a] != -1) {
            modelSlotGetNodePos(gCsModelIds[cmd->a], 1, cmd->b, &D_807F690C, &D_807F6910, &D_807F6914);
        }
        break;
    case 0x4E:
        slot = effectGridFindByTargetId(cmd->a);
        effectSetDepth(1);
        effectCreateAtModelNode(slot, cmd->b / 100.0, csId, cmd->c, 0);
        break;
    case 0x4C:
        h = (s16)(modelAnimEntryGetUnkC(csId, cmd->a) + cmd->b);
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
        gGlobalPauseFlags |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x88:
        gGlobalCutsceneFlags |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x89:
        gGlobalCutsceneFlags &= ~(((u16)cmd->a << 16) + (u16)cmd->b);
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
        csSetActorAlphaByType(cmd->a, cmd->b, csId);
        break;
    case 0x35:
        csSetActorScaleFadeByType(cmd->a, cmd->b, csId);
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
        csSetObjectTrackParam(cs, cmd->a, cmd->b);
        break;
    case 0x54:
        slot = hashTableLookup(gCsModelIds[cmd->a]);
        if (slot != -1) {
            csSetObjectTrackParam(gModelSlots[slot].unk7C, cmd->b, cmd->c);
        }
        break;
    case 0x25:
        csStartCamPath(cs, cmd->a, cmd->b, cmd->c);
        break;
    case 0x3C:
        if (cs->unk94 != NULL) {
            actorDespawn(cs->unk94);
            cs->unk94 = NULL;
        }
        break;
    case 0x30:
        mapRequestTransition(cmd->a, 0);
        break;
    case 0x86:
        playerThrowHeldActor(gActivePlayerActor);
        mapSaveSlotAndTransition(0x2A, 0, cmd->a, 2);
        break;
    case 0x87:
        mapTransitionToPreviousOrExit();
        break;
    case 0x8D:
        D_80744824 = 2;
        playerThrowHeldActor(gActivePlayerActor);
        slot = mapGetHubWorldIndex(gCurrentMap, 0);
        if (func_805FEF74(gCurrentMap) != 0) {
            map = D_8074809C[slot];
            exit = D_807480AC[slot];
            if (flagGet(D_807480BC[slot], 0) == 0) {
                if (map == 0x57) {
                    exit = 0x15;
                } else {
                    exit = 0;
                }
            }
            if (cutsceneTriggerCheck(map) == 0) {
                mapRequestTransition(map, exit);
            }
        } else {
            mapTransitionToWorldHub(slot);
        }
        break;
    case 0x31:
        if (cmd->c & 0x100) {
            transitionSetState(2);
            screenSetTransitionFadeType(0);
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
        mapSaveSlotAndTransition(cmd->a, cmd->b, 0, flag);
        break;
    case 0x32:
        mapTransitionExitCurrent(cmd->a, cmd->b);
        break;
    case 0x2F:
        func_8060B49C(gActivePlayerActor, cmd->a);
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
        c &= 0xFF; // FAKE: redundant mask keeps the in-place andi copy (Q0186)
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        b = cmd->b;
        if (cs->unk10[i] < 0) {
            if (b && b && b) {} // FAKE: deadsweep: keeps b a real variable (move a3,v1)
            b &= 2;
            cs->unk10[i] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, 0);
        }
        break;
    case 0x7D:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF; // FAKE: redundant mask keeps the in-place andi copy (Q0186)
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        b = cmd->b;
        if (cs->unk10[i] < 0) {
            if (b && b && b) {} // FAKE: deadsweep: keeps b a real variable (move a3,v1)
            b &= 2;
            cs->unk10[i] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, D_80748094);
        }
        break;
    case 0xF:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF; // FAKE: redundant mask keeps the in-place andi copy (Q0186)
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
        pan7 = (cmd->b / 128) & 0xFF;
        vol7 = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        pitch = c & 0x7F;
        if (pan7 == 0) {
            pan7 = 0x7F;
        }
        if (!vol7) {
            vol7 = 0xFF;
        }
        i = cmd->b & 0x7F;
        if (D_80748094 > 0) {
            modelSlotGetNodePos(csId, 1, D_80748094, &sx, &sy, &sz);
            sfxPlayAtPositionPooled(sx, sy, sz, cmd->a, vol7, pan7, i, pitch, 0.3f, 0);
        } else {
            sfxPlayOnFreeSlot(cmd->a, 0x7FFF, 63.0f, (u32)pan7 / 127.0, 0, 0);
        }
        break;
    case 0x10:
        if (cs->unk10[cmd->b] >= 0) {
            sfxSlotFreeSource(cs->unk10[cmd->b]);
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
        if (D_807F61FC != gCsPosX || D_807F6204 != gCsPosZ) {
            csSnapToGround(cmd->a, csId);
        }
        break;
    case 0x41:
        D_807F6904 = 1;
        break;
    case 0x6:
        cs->unk14[cmd->a] = cmd->b / 10.0f;
        break;
    case 0x0:
        csSetRot(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x8:
        csSetPos(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x1E:
        csSetRot(cmd->a, cmd->b, cs, csId, 0);
        break;
    case 0x1D:
        csSetPos(cmd->a, cmd->b, cs, csId, 0);
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
        if (csModelStateTrySetByte(cmd->a, cmd->b, cmd->c) == 0) {
            return;
        }
        break;
    case 0x2D:
        i = 0;
        for (; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->flags & 0x2000) && actor->attachMode == 1 && csId == actor->cutsceneId) {
                if (cmd->a != 0) {
                    actor->flags2 |= 4;
                } else {
                    actor->flags2 &= ~4;
                }
            }
        }
        break;
    case 0x7:
        gCsCmdTable[cmd->a](cs, csId, cmd->b, cmd->c);
        break;
    case 0x37:
        actorAppendCallback(gPlayerSlots->actor, 0, 0x400000, CMDB(cmd)->a, 0, 0);
        break;
    case 0x19:
        playerStateQueueCallback(cmd->a, 0, 0);
        break;
    case 0x2C:
        modelSlotGetNodePos(csId, 1, cmd->a, &cx, &cy, &cz);
        actorAppendCallbackVec3f(0, gPlayerSlots->actor, cx, cy, cz);
        break;
    case 0x2B:
        func_80636014(csId, 1, CMDB(cmd)->a);
        break;
    case 0x1B:
        if (gCsModelIds[cmd->a] != -1) {
            modelSlotGetNodePos(gCsModelIds[cmd->a], 1, cmd->b, &gCsPosX, &gCsPosY, &gCsPosZ);
        }
        break;
    case 0x1C:
        if (gCsModelIds[cmd->a] != -1) {
            idx = hashTableLookup(gCsModelIds[cmd->a]);
            if (idx != -1) {
                if (gModelSlots[idx].unk7C != NULL) {
                    found = 1;
                    gModelSlots[idx].unk7C[cmd->b + 0x48] += cmd->c;
                }
            }
        }
        if (found == 0) {
            return;
        }
        break;
    case 0x2:
        pathPlaybackSetSpeed(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x1F:
        pathPlaybackSetLoopMode(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x20:
        pathPlaybackSetDirection(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x21:
        pathPlaybackSetLoopLimit(cs->unk38, cmd->a);
        break;
    case 0x24:
        pathPlaybackSetActive(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x22:
        cs->unk38 = pathPlaybackStart(0, cmd->a, CMDB(cmd)->b, gCsPosX, gCsPosY, gCsPosZ, cmd->c);
        break;
    case 0x23:
        pathPlaybackFree(cs->unk38);
        cs->unk38 = -1;
        break;
    case 0x4:
        pathPlaybackAdvance(cs->unk38);
        pathPlaybackGetPosition(cs->unk38, &gCsPosX, &gCsPosY, &gCsPosZ);
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
        cam = gPlayerSlots->actor->customState;
        camStartShakeFromPoint(cam->camActor, CMDB(cmd)->a, cmd->b, gCsPosX, gCsPosY, gCsPosZ, D_807F6906, D_807F6908);
        break;
    case 0x44:
        D_807F6906 = cmd->a;
        D_807F6908 = cmd->b;
        break;
    case 0x2A:
        ((CsModelSlot2 *)gModelSlots)[hashTableLookup(csId)].unk3C = cmd->a;
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
        actorAppendCallbackPayloadABC0(0, gPlayerSlots->actor, CMDB(cmd)->a, cmd->b, cmd->c, gCsPosX, gCsPosY, gCsPosZ);
        break;
    case 0x4D:
        idx = modelSlotAppend(cmd->a, D_807F690C, D_807F6910, D_807F6914, D_807F6910 - D_807F6218, 0);
        if (cmd->b == 0) {
            csStateShareScript(idx, csId, cmd->c);
        }
        break;
    case 0x51:
        gridMoveNode(csId, gCsPosX, gCsPosY, gCsPosZ);
        break;
    case 0x5E:
        csSendActorMessagePayload(cmd->a, cmd->b);
        break;
    case 0x8A:
        csSendMsgByActorType(cmd->a, cmd->b);
        break;
    case 0x63:
        func_8068B830(cmd->a, cmd->b, cmd->c);
        break;
    case 0x64:
        enemyAggroDespawnBB();
        break;
    case 0x56:
        func_80724994(1, cmd->a, 0, 0, 0);
        break;
    case 0x59:
        func_80724994(3, cmd->a, cmd->b, 0, 0);
        break;
    case 0x58:
        if (func_805FFE50(cmd->a, cmd->b, cmd->c) == 0) {
            csTimerQueueAdd(cmd->a, cmd->b, cmd->c);
        }
        break;
    case 0x77:
        modelAnimEntrySetUnk13(csId, cmd->a, CMDB(cmd)->b, cmd->c / 1000.0);
        break;
    }
}


void csSetCameraFollowModel(s16 modelId) {
    PlayerState *cam;

    cam = gPlayerSlots->actor->customState;
    switch (modelId) {
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
            cam->damageCooldown = 0x3C;
            break;
    }
}


void csSendMsgByActorType(s16 actorType, s16 msgParam) {
    s32 i;
    Actor *actor;
    s16 msgPayload[2];

    msgPayload[0] = 0;
    msgPayload[1] = msgParam;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->actorType == actorType) {
            actorAppendCallbackMemcpy8(0, actor, 0x01000000, 1, msgPayload, 0);
        }
    }
}


void csSendActorMessagePayload(s16 paramA, s16 paramB) {
    s16 *msgPayload;
    Actor *targetActor;

    msgPayload = heapAlloc(4);
    heapFreeDeferred(msgPayload);
    msgPayload[1] = paramA;
    msgPayload[0] = paramB;
    actorFindActiveByType(0xE, &targetActor);
    actorAppendCallbackMemcpy8(0, targetActor, 0x01000000, 1, msgPayload, 0);
}

s32 csModelStateTrySetByte(s16 modelIndex, s16 val, s16 byteOffset) {
    s16 modelId = gCsModelIds[modelIndex];
    s16 slot;

    if (modelId != -1) {
        slot = hashTableLookup(modelId);
        if (slot != -1 && gModelSlots[slot].unk7C != NULL) {
            gModelSlots[slot].unk7C[byteOffset + 0x48] = val;
            return 1;
        }
    }
    return 0;
}

typedef struct CsObjView {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 pad55[3];
    /* 0x58 */ s32 unk58;
} CsObjView;

void csSetObjectTrackParam(void *obj, s16 b, s16 c) {
    CsObjView *o = obj;

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


s32 csIsPlayerInCutsceneState(void) {
    PlayerState *cam = gPlayerSlots->actor->customState;

    if ((gPrimaryPlayerActor->state == 0x42 && (cam->hitActorType == 0x62 || cam->hitActorType == 0x88 || cam->hitActorType == 0x17)) || gPrimaryPlayerActor->state == 0x52 ||
        gPrimaryPlayerActor->state == 0x67 || gPlayerSlots->queuedState == 0x1C || gPlayerSlots->queuedState == 0x53) {
        return 0;
    }
    return 1;
}


void csFreeTrackedModels(void) {
    s32 i;

    for (i = 0; i < gCsTrackedModelCount; i++) {
        modelSlotFreeByIndex(gCsModelIds[gCsTrackedModels[i]], 1);
    }
}

typedef struct CsAuxView {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 pad49[0x57];
    /* 0xA0 */ s32 unkA0;
} CsAuxView;

void csStateShareScript(s16 dstModelId, s16 srcModelId, s16 val) {
    dstModelId = hashTableLookup(dstModelId);
    srcModelId = hashTableLookup(srcModelId);
    gModelSlots[dstModelId].unk7C = heapAlloc(0xA4);
    csStateInit(gModelSlots[dstModelId].unk7C);
    ((CsAuxView *)gModelSlots[dstModelId].unk7C)->unk48 = val;
    ((CsAuxView *)gModelSlots[dstModelId].unk7C)->unkA0 = ((CsAuxView *)gModelSlots[srcModelId].unk7C)->unkA0;
}

void csSetActorAlphaByType(s16 actorType, s16 enable, s16 csId) {
    s32 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && actor->actorType == actorType && csId == actor->cutsceneId) {
            if (enable != 0) {
                actor->flags2 |= 4;
            } else {
                actor->flags2 &= ~4;
            }
        }
    }
}

void csSetActorScaleFadeByType(s16 actorType, s16 mode, s16 csId) {
    s32 fadeArg;
    s32 i;
    Actor *actor;

    switch (mode) {
    case 0:
        fadeArg = 1;
        break;
    case 1:
        fadeArg = 2;
        break;
    case 2:
        fadeArg = 0x3C;
        break;
    }
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && actor->actorType == actorType && csId == actor->cutsceneId) {
            actorAppendCallback(actor, 0, 0x800, fadeArg, 0, 0);
        }
    }
}


void csStartCamPath(CsState *cs, s16 camIdx, s16 mode, s16 c) {
    s32 flag;

    if (cs->unk94 == NULL && func_80678014(0x14) != 0) {
        cs->unk94 = gSpawnedActor;
        gSpawnedActor->unk144 = 1;
        gSpawnedActor->x = gCsPosX;
        gSpawnedActor->y = gCsPosY;
        gSpawnedActor->z = gCsPosZ;
        gSpawnedActor->yaw = gCsRotY * 4096.0f / 360.0f;
        if (D_807F693F != 0) {
            gSpawnedActor->eyeHeight = c;
        }
        if (D_807F693F != 0) {
            flag = 4;
        } else {
            flag = 0;
        }
        switch (mode) {
        case 0:
            camStartPath(cs->unk94, camIdx, flag | 1 | D_807F693C);
            return;
        case 1:
            camStartPath(NULL, camIdx, flag | 1 | D_807F693C);
            return;
        case 2:
            camStartPath(spawnNodeActivate(c, 0x400), camIdx, flag | 1 | D_807F693C);
            break;
        }
    }
}

void func_80641F68(void) {
}

extern u8 gViewportCount;
f32 sqrtf(f32);


u8 csPosOnScreenOfNearPlayer(s16 radius) {
    f32 sx;
    f32 sy;
    u8 i;
    Actor *a;
    f32 dx;
    f32 dy;
    f32 dz;
    u8 ret = 0;

    for (i = 0; i < gViewportCount; i++) {
        if (gPlayerSlots[i].unk0 != 0) {
            a = gPlayerSlots[i].actor;
            dx = gCsPosX - a->x;
            dy = gCsPosY - a->y;
            dz = gCsPosZ - a->z;
            dx *= dx;
            dy *= dy;
            dz *= dz;
            if (sqrtf(dx + dy + dz) < radius) {
                camProjectToScreen(gCsPosX, gCsPosY, gCsPosZ, &sx, &sy, 0, 1.0f, i);
                if ((s16)sx >= gPlayerSlots[i].rect[0] + 0x14 && (s16)sy >= gPlayerSlots[i].rect[1] + 0x14 &&
                    gPlayerSlots[i].rect[2] - 0x14 >= (s16)sx && gPlayerSlots[i].rect[3] - 0x14 >= (s16)sy) {
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

// Stride view of gPlayerSlots (PlayerStruct camX/camY/camZ at 0x210): as CsCondPlayer, the
// shared type swaps the `addu base,off` operands of the loops below.
typedef struct CsPlayerPosView {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x2F0 - 0x21C];
} CsPlayerPosView; // size = 0x2F0

s32 csPosWithinRadius(s16 radius, f32 x, f32 y, f32 z) {
    f32 dx = gCsPosX - x;
    f32 dy = gCsPosY - y;
    f32 dz = gCsPosZ - z;

    dx *= dx;
    dy *= dy;
    dz *= dz;
    return (u8)(sqrtf(dx + dy + dz) < radius);
}



s32 csPlayerNearPos(s16 radius) {
    u8 i;
    CsPlayerPosView *p;

    for (i = 0; i < gViewportCount; i++) {
        p = (CsPlayerPosView *)gPlayerSlots + i;
        if (p->unk0 != 0) {
            Actor *a = p->unk4;
            if (csPosWithinRadius(radius, a->x, a->y, a->z)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 csPlayerSavedPosNearPos(s16 radius) {
    u8 i;
    CsPlayerPosView *p;

    for (i = 0; i < gViewportCount; i++) {
        p = (CsPlayerPosView *)gPlayerSlots + i;
        if (p->unk0 != 0 && csPosWithinRadius(radius, p->unk210, p->unk214, p->unk218)) {
            return 1;
        }
    }
    return 0;
}


s32 csSpawnNodeNearPos(s16 radius, s16 minNodeIndex, s16 maxNodeIndex) {
    s16 i;
    Actor *a;

    for (i = minNodeIndex; i <= maxNodeIndex; i++) {
        if (spawnNodeHasActor(i)) {
            a = spawnNodeActivate(i, 0);
            if (a != NULL) {
                if (csPosWithinRadius(radius, a->x, a->y, a->z)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


void csSnapToGround(s16 mode, s16 csId) {
    s32 pad;
    f32 y;

    switch (mode) {
    case 0:
        y = gCsPosY;
        if (collisionCheckGroundAtPoint(gCsPosX, gCsPosZ, &y)) {
            gCsPosY = y + gCsGroundOffset;
        }
        break;
    case 1:
        break;
    }
}

s32 csCompareVar(f32 *varsArray, s16 packedParam, s16 compareValue) {
    u8 idx;
    u8 mode;
    s32 ret;
    f32 v;
    f32 th;

    ret = 0;
    mode = packedParam & 0xFF;
    idx = (packedParam >> 8) & 0xFF;
    v = varsArray[idx];
    switch (mode) {
    case 0:
        th = compareValue / 10.0f;
        if (((th < v) ? (v - th) : (th - v)) < 0.05) {
            ret = 1;
        }
        break;
    case 1:
        if (compareValue / 10.0f < v) {
            ret = 1;
        }
        break;
    case 2:
        if (v < compareValue / 10.0f) {
            ret = 1;
        }
        break;
    }
    return ret;
}


s32 csEvaluateParamCondition(s16 packedParam, s16 compareValue) {
    f32 v;
    f32 th;
    s32 ret;
    u8 mode;

    th = compareValue / 10.0f;
    ret = 0;
    switch ((u8)((packedParam >> 8) % 255)) {
    case 0:
        v = D_807F6208;
        break;
    case 1:
        v = D_807F620C;
        break;
    case 2:
        v = D_807F6210;
        break;
    }
    mode = packedParam & 0xFF;
    switch (mode) {
    case 0:
        if (((th < v) ? (v - th) : (th - v)) != 0.1) {
            ret = 1;
        }
        break;
    case 1:
        if (th < v) {
            ret = 1;
        }
        break;
    case 2:
        if (v < th) {
            ret = 1;
        }
        break;
    }
    return ret;
}


void csSetRot(s16 modeAndAxis, s16 rotValue, CsState *cs, s16 csId, u8 isRelative) {
    f32 v;
    u8 lo;
    u8 hi;

    lo = modeAndAxis & 0xFF;
    hi = (modeAndAxis >> 8) & 0xFF;
    v = rotValue / 10.0f;
    if (lo == 1) {
        v = cs->unk14[rotValue];
    }
    switch (hi) {
    case 0:
        if (isRelative == 1) {
            gCsRotX += v;
        } else {
            gCsRotX = v;
        }
        break;
    case 1:
        if (isRelative == 1) {
            gCsRotY += v;
        } else {
            gCsRotY = v;
        }
        break;
    case 2:
        if (isRelative == 1) {
            gCsRotZ += v;
        } else {
            gCsRotZ = v;
        }
        break;
    }
}

void csSetPos(s16 modeAndAxis, s16 posValue, CsState *cs, s16 csId, u8 isRelative) {
    f32 v;
    u8 lo;
    u8 hi;

    lo = modeAndAxis & 0xFF;
    hi = (modeAndAxis >> 8) & 0xFF;
    v = posValue / 10.0f;
    if (lo == 1) {
        v = cs->unk14[posValue];
    }
    switch (hi) {
    case 0:
        if (isRelative == 1) {
            gCsPosX += v;
        } else {
            gCsPosX = v;
        }
        break;
    case 1:
        if (isRelative == 1) {
            gCsPosY += v;
        } else {
            gCsPosY = v;
        }
        break;
    case 2:
        if (isRelative == 1) {
            gCsPosZ += v;
        } else {
            gCsPosZ = v;
        }
        break;
    }
}

extern u8 D_8071FC58[];

void csCmdSpawnSparkAndLight(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < 1; i++) {
        x = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
        y = (randomLcgNext() / 10000 % 200) / 10.0 - 7.0;
        z = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
        effectSetDepth(1);
        effectSetDuration(2);
        effectSetSpeed(0x64);
        effectSetCallback(func_80717D4C);
        effectCreateAtPosition(D_8071FC58, 0.5f, gCsPosX + x, gCsPosY + y, gCsPosZ + z);
    }
    lightAdd(gCsPosX, gCsPosY, gCsPosZ, 0.0f, 0.0f, 0.0f, 300.0f, 0, 0xA6, 0x30, 0xFF);
}

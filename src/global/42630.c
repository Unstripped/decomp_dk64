#include "common.h"
#include "actor.h"
#include "cutscene.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gBossFightPhase;

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
s8 D_807F693F;

void csModelIdTableReset(void) {
    s32 i = 0;
    s32 j;

    do {
        gCsModelIds[i] = -1;
        i++;
    } while (&gCsModelIds[i] < (s16 *)gCsVarsDirty);
    for (j = 0; j < 0x212; j++) { gCsVarsDirty[j] = 0; }
}

struct CsModelSlot;
extern struct CsModelSlot *gModelSlots;
s32 hashTableLookup();

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

void csModelStateSetByte(s16, s16, s16);

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
extern s8 D_807F693F;
void *heapAlloc(s32);
struct CsStateFull;
void csStateInit(struct CsStateFull *);
void *memcpy(void *, const void *, unsigned int);

typedef struct CsLoadSpawn {
    /* 0x0 */ void *unk0;
    /* 0x4 */ void *unk4;
    /* 0x8 */ u8 unk8;
} CsLoadSpawn;

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
    ((CsLoadSpawn *)&D_807F61F0)->unk0 = NULL;
    ((CsLoadSpawn *)&D_807F61F0)->unk4 = NULL;
    ((CsLoadSpawn *)&D_807F61F0)->unk8 = 0;
}

void heapFree(void *);

void csStateFree(CsLoadState *loadState) {
    CsLoadNode *node;
    CsLoadNode *next;

    if (*(void **)loadState != NULL) {
        heapFree(*(void **)loadState);
    }
    node = loadState->unkA0;
    while (node != NULL) {
        next = node->unk4C;
        heapFree(node);
        node = next;
    }
    heapFree(loadState);
}

// Cutscene condition/command list node (one script step).
typedef struct CsNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ CsCmd unk2[5];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ CsCmd unk2C[4];
    /* 0x4C */ struct CsNode *unk4C;
} CsNode;

// Whole-state view of CsState (include/cutscene.h only knows part of it).
typedef struct CsStateFull {
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
    /* 0xA0 */ CsNode *unkA0;
} CsStateFull;

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
void modelSlotGetTransformVectors(s32, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, u8);
void csStateEndUpdate(CsStateFull *);
void csStateIntegrateMotion(CsStateFull *);
s32 csCondEval(CsCmd *, CsState *, s16);
void csCmdExec(CsCmd *, CsState *, s16);
s32 modelSlotStepAnimations(s16);
void modelSlotUpdateGroundCoords(s16, u8);
void modelSlotTransformBoundsAndNodes(s32, f32, f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8, u8);

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
void actorDespawn(Actor *);

void csStateEndUpdate(CsStateFull *cs) {
    Actor *actor;
    u32 flags;

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
        cs->unk94->x = gCsPosX;
        actor->y = gCsPosY;
        actor->z = gCsPosZ;
        actor->yaw = gCsRotY * 4096.0f / 360.0f;
        flags = gGlobalPauseFlags;
        if (flags & 0x1000) {
            gGlobalPauseFlags = flags & ~0x1000;
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
// Matched. Operand-order notes: `field == ((s16 *)cmd)[N]` (instead of `== cmd->a/b`) emits `bne field,arg`
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

typedef struct CsCondActor {
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
} CsCondActor;

typedef struct CsCondPlayer {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ CsCondActor *unk4;
    /* 0x008 */ u8 pad8[0x288];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[0x2C0 - 0x292];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 unk2C1;
    /* 0x2C2 */ u8 pad2C2[0x2F0 - 0x2C2];
} CsCondPlayer; /* 0x2F0 */

typedef struct CsCondCam {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ s32 unk1F8;
} CsCondCam;

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

typedef struct CsCondActorData {
    /* 0x00 */ u8 pad0[0xD0];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 unkD1;
} CsCondActorData;

typedef struct CsCondSpawn {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} CsCondSpawn;

typedef struct CsCondRow {
    /* 0x000 */ u8 e[8][0x5E];
    /* 0x2F0 */ u8 pad2F0[0x16];
} CsCondRow; /* 0x306 */

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern CsPlayer *gPlayerSlots;
extern u8 *D_807FD568;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 gPlayerInventoryTable[];
extern u8 gGameMode;
extern u8 gPlayerCharacterId;
extern s16 D_8076AEF2;
extern s32 (*gCsCondTable[])(CsState *, s16, s16, s16);

void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
u8 modelAnimEntryIsActive(s16, s16);
s32 actorListGetOrSetState(s16, u8, u8);
s32 flagGet();
s32 actorListIsIdActive(s16);
u16 actorLookupClass(u16);
s32 csIsPlayerInCutsceneState(void);
void csSetCameraFollowModel(s16);
s16 modelAnimEntryGetUnkC(s16, s16);
Actor *spawnNodeActivate(s16, u16);
u8 spawnNodeHasActor(u8);
u8 spawnNodeIsInCooldown(u8);
s32 listContainsS16(s16);
f32 actorGetAnimProgress(void *);
u8 playerLookupKongByActorType(s16);
u8 pathPlaybackIsActive(s32);
u8 csPosOnScreenOfNearPlayer(s16);
s32 csPlayerNearPos(s16);
s32 csPlayerSavedPosNearPos(s16);
s32 csSpawnNodeNearPos(s16, s16, s16);
s32 csCompareVar(f32 *, s16, s16);
s32 csEvaluateParamCondition(s16, s16);

#define CS_COND_STATE ((CsCondState *)cs)
#define CS_COND_PLAYER ((CsCondPlayer *)gPlayerSlots)

s32 csCondEval(CsCmd *cmd, CsState *cs, s16 csId) {
    u8 neg;
    u8 ret;
    s16 type;
    CsCondActor *a;
    CsCondPlayer *p;
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
    CsCondCam *cam;
    u32 mask;
    CsCondActor *b;

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
        ret = cmd->a == CS_COND_PLAYER->unk290;
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
        if (cmd->a == ((CsCondActorData *)gPrimaryPlayerActor)->unkD1) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x35:
        if (cmd->a == ((CsCondActorData *)gPrimaryPlayerActor)->unkD0) {
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
        cam = gPlayerSlots->unk4->customState;
        if ((cmd->b + (cmd->a << 16)) & cam->unk1F0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x27:
        cam = gPlayerSlots->unk4->customState;
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
        h = playerLookupKongByActorType(cmd->a) * 0x5E;
        q = &gPlayerInventoryTable[gCurrentPlayerIndex * 0x306 + h];
        if (*q >= cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x24:
        a = (CsCondActor *)spawnNodeActivate(cmd->a, 0);
        if (cmd->b == a->unk154) {
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
        if (((CsCondSlot *)gModelSlots)[hashTableLookup(gCsModelIds[cmd->a])].unk7C[cmd->c + 0x48] == ((s16 *)cmd)[2]) {
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
        if (CS_COND_STATE->unk44[cmd->b] == ((s16 *)cmd)[1]) {
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
                if (a->unk110 == 1 && csId == a->unk10C) {
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
                if (a->unk110 == 1 && csId == a->unk10C && cmd->a == a->unk10E) {
                    ret = 1;
                }
            }
        }
        break;
    case 0x11:
        found = 0;
        for (h = 0; h < gActiveActorCount && !found; h++) {
            b = (CsCondActor *)gActiveActors[h].actor;
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
            b = (CsCondActor *)gActiveActors[h].actor;
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
            b = (CsCondActor *)gActiveActors[h].actor;
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
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
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
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
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
        if (CS_COND_STATE->unk5C != 0 && (cmd->b == -1 || CS_COND_STATE->unk5C == ((s16 *)cmd)[2]) &&
            (actorLookupClass(CS_COND_STATE->unk5E) & cmd->a) && csIsPlayerInCutsceneState() != 0) {
            csSetCameraFollowModel(((CsCondSlot *)gModelSlots)[hashTableLookup(csId)].unk84);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x18:
        if (CS_COND_STATE->unk5C != 0 && (cmd->b == -1 || CS_COND_STATE->unk5C == ((s16 *)cmd)[2]) && cmd->a == CS_COND_STATE->unk5E &&
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
        for (i = 0; i < gPlayerCount; i++) {
            p = &CS_COND_PLAYER[i];
            if (p->unk0 != 0 && p->unk4->unk155 == ((s16 *)cmd)[1]) {
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
        ret = CS_COND_PLAYER->unk2C0 == ((s16 *)cmd)[1];
        break;
    case 0x1B:
        ret = CS_COND_PLAYER->unk2C1;
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
        if (((CsCondSpawn *)&D_807F61F0)->unk8 != 0) {
            if (((CsCondSpawn *)&D_807F61F0)->unk0->state == 5) {
                ret = 1;
            } else {
                ret = 0;
            }
        } else {
            ret = 1;
        }
        break;
    case 0x2B:
        ret = ((CsCondSpawn *)&D_807F61F0)->unk8;
        break;
    case 0x33:
        height = actorGetAnimProgress(gPrimaryPlayerActor);
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

// Cutscene script command interpreter (csCmdExec): one 8-byte command per call.

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

extern CsCmdFunc gCsCmdTable[];
extern u8 D_80744824;
extern s8 D_80748094;
extern s16 D_8074809C[];
extern s16 D_807480AC[];
extern s16 D_807480BC[];
extern s32 gCurrentMap;
extern CsModelSlot *gModelSlots;
extern CsSpawnReq D_807F61F0;
extern Actor *D_807F61F4;
extern s16 gCsTrackedModels[16];
extern u8 gCsTrackedModelCount;
extern s16 D_807F693A;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern u32 gGlobalCutsceneFlags;

void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorSetStateTwo(Actor *);
void actorSetTargetSlotByte(s32, u8);
s32 actorSpawn(s32, s32);
void dynamicBufferFree(void *);
void effectNodeAddTargetAndStep(s32, f32, f32);
void effectNodeSetSubVal(s32, u8);
void effectNodeSetTargetAndStep(s32, f32, f32);
s32 func_805FEF74(s32);
u8 mapGetHubWorldIndex(u8, u8);
void screenSetTransitionFadeType(u8);
void mapRequestTransition(s32, s32);
void mapTransitionExitCurrent(s32, s32);
void mapTransitionToPreviousOrExit(void);
void func_805FF9AC(s32, s32, s32, s16);
s32 func_805FFE50(s32, s16, s16);
void mapTransitionToWorldHub(s32);
void sfxSlotFreeSource(s16);
s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
s16 sfxPlayOnFreeSlot(s16, s32, s32, f32, s32, s32);  // FAKE: callee prototype steer
void func_8060B49C(Actor *, s16);
void eepromSavePlayerData(void);
void camStartShakeFromPoint(s32, u8, u16, f32, f32, f32, f32, f32);
void camSetZoneWeight(u8, u8);
void mapOffsetSlotSetEnabled(s16, u8);
void mapOffsetSlotSetTarget(s32, f32, f32);
void mapOffsetSlotAddTarget(s32, f32, f32);
void func_8062D1A8(void);
void modelSkipListAdd(s16);
s16 modelSlotAppend(s32, f32, f32, f32, f32, u8);
void modelSlotGetNodePos(s32, u8, s32, f32 *, f32 *, f32 *);
void modelSlotUpdateTailKey(s32, u8, u8, u8);
void modelSlotTriBufferRelease(void *);
void modelSlotSetNodeScrollSpeed(s32, s16, s16, s16);
void modelSlotSetNodeAnimMode(s32, s16, u8);
void modelSlotSetNodeFrame(s32, s16, s32, s32);
void func_80636014(s32, u8, u8);
void func_8063A8C4(s16, u8, f32);
void csTimerQueueAdd(s16, s16, s16);
void csSendMsgByActorType(s16, s16);
void csSendActorMessagePayload(s16, s16);
s32 csModelStateTrySetByte(s16, s16, s16);
void csSetObjectTrackParam(void *, s16, s16);
void csStateShareScript(s16, s16, s16);
void csSetActorAlphaByType(s16, s16, s16);
void csSetActorScaleFadeByType(s16, s16, s16);
void csStartCamPath(void *, s16, s16, s16);
void csSnapToGround(s16, s16);
void csSetRot(s16, s16, void *, s16, u8);
void csSetPos(s16, s16, void *, s16, u8);
void modelAnimEntrySetUnk13(s16, s16, u8, f32);
void actorAppendCallbackVec3f(s32, Actor *, f32, f32, f32);
void actorAppendCallbackPayloadABC0(s32, Actor *, u8, s16, s16, f32, f32, f32);
s32 cutsceneTriggerCheck(s16);
void func_8068B830(s16, s16, s16);
void enemyAggroDespawnBB(void);
void hudSpawnCountdownTimer(s32, s32, u8, void *);
void playerRespawnResetPhysics(s32);
void playerThrowHeldActor(Actor *);
s32 playerStateQueueCallback(s16, void *, u8);
void playerStateSetCallbackParameters(s32, s32, s32, s32);
void gridMoveNode(s16, f32, f32, f32);
void slotQueueSetDisplayMode(u8, u8, u8);
void transitionSetState(u8);
s32 effectGridFindByTargetId(s32);
void effectSetDepth(s8);
void effectCreateAtModelNode(s32, f32, s32, s32, u8);
s32 pathPlaybackStart(s32, s32, u8, f32, f32, f32, u8);
void pathPlaybackSetSpeed(s32, u8);
void pathPlaybackSetLoopMode(s32, u8);
void pathPlaybackSetLoopLimit(s32, s32);
void pathPlaybackSetActive(s32, u8);
void pathPlaybackSetDirection(s32, u8);
void pathPlaybackFree(s32);
void pathPlaybackAdvance(s32);
void pathPlaybackGetPosition(s32, f32 *, f32 *, f32 *);
void func_80724994(u8, s16, s16, s16, s16);
void zoneEntrySetDisabled(u8, u8, u8);
void volumeTriggerSetEnabled(s32, u8);
s32 volumeTriggerSetPosition(s32, s16, s16, s16);
void proxPathSetEnabled(Actor *, u8, u8);
void proxPathSetEndBehavior(Actor *, u8, u8);
void flagSet(s16, u8, u8);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void lightSetColor(f32, f32, f32, s16);
void mapByteArraySet(s16, u8);  // FAKE: callee prototype steer
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
void sfxPlayFromTargetSlot(s16, s16, u8, u8, u8, u8, f32);
void sfxSetChannelTempo(s32, f32);
void sfxSetVolumeAndPan(u8, f32, f32);
u8 sfxSlotAllocateSource(s16, s16, s32, s32, u8, f32, s8);  // FAKE: callee prototype steer
void sfxStopChannel(s32, s32);

void csCmdExec(CsCmd *cmd, CsState *cs, s16 csId) {
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
        ((CsCamState *)gPlayerSlots->unk4->customState)->unk1F0 |= 0x40000800;
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
        cam = gPlayerSlots->unk4->customState;
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
        ((CsCamState *)gPlayerSlots->unk4->customState)->unk1F0 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x3B:
        ((CsCamState *)gPlayerSlots->unk4->customState)->unk1F0 &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x8C:
        ((CsCamState *)gPlayerSlots->unk4->customState)->unk1F4 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x8B:
        ((CsCamState *)gPlayerSlots->unk4->customState)->unk1F4 &= ~((cmd->a << 16) + cmd->b);
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
        func_805FF9AC(0x2A, 0, cmd->a, 2);
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
            if (map && map) {}
            if (flagGet(D_807480BC[slot], 0, exit) == 0) {
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
        func_805FF9AC(cmd->a, cmd->b, 0, flag);
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
            sfxPlayOnFreeSlot(cmd->a, 0x7FFF, 0x427C0000, (u32)pan7 / 127.0, 0, 0);
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
        actorAppendCallback(gPlayerSlots->unk4, 0, 0x400000, CMDB(cmd)->a, 0, 0);
        break;
    case 0x19:
        playerStateQueueCallback(cmd->a, 0, 0);
        break;
    case 0x2C:
        modelSlotGetNodePos(csId, 1, cmd->a, &cx, &cy, &cz);
        actorAppendCallbackVec3f(0, gPlayerSlots->unk4, cx, cy, cz);
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
        cam = gPlayerSlots->unk4->customState;
        camStartShakeFromPoint(cam->unk104, CMDB(cmd)->a, cmd->b, gCsPosX, gCsPosY, gCsPosZ, D_807F6906, D_807F6908);
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
        actorAppendCallbackPayloadABC0(0, gPlayerSlots->unk4, CMDB(cmd)->a, cmd->b, cmd->c, gCsPosX, gCsPosY, gCsPosZ);
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

typedef struct CsCamView {
    /* 0x000 */ u8 pad0[0x245];
    /* 0x245 */ u8 unk245;
} CsCamView;

void csSetCameraFollowModel(s16 modelId) {
    CsCamView *cam;

    cam = gPlayerSlots->unk4->customState;
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
            cam->unk245 = 0x3C;
            break;
    }
}

void actorAppendCallbackMemcpy8(s32, Actor *, s32, u8, void *, u8);

void csSendMsgByActorType(s16 actorType, s16 msgParam) {
    s32 i;
    Actor *actor;
    s16 msgPayload[2];

    msgPayload[0] = 0;
    msgPayload[1] = msgParam;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if ((u32)actor->actorType == actorType) {
            actorAppendCallbackMemcpy8(0, actor, 0x01000000, 1, msgPayload, 0);
        }
    }
}

void heapFreeDeferred(void *);
s32 actorFindActiveByType(s16, Actor **);

void csSendActorMessagePayload(s16 paramA, s16 paramB) {
    s16 *msgPayload;
    void *targetActor;

    msgPayload = heapAlloc(4);
    heapFreeDeferred(msgPayload);
    msgPayload[1] = paramA;
    msgPayload[0] = paramB;
    actorFindActiveByType(0xE, &targetActor);
    actorAppendCallbackMemcpy8(0, targetActor, 0x01000000, 1, msgPayload, 0);
}

s32 csModelStateTrySetByte(s16 a, s16 b, s16 c) {
    s16 t = gCsModelIds[a];
    s16 slot;

    if (t != -1) {
        slot = hashTableLookup(t);
        if (slot != -1 && gModelSlots[slot].unk7C != NULL) {
            gModelSlots[slot].unk7C[c + 0x48] = b;
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

typedef struct CsPlayerView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x29C - 8];
    /* 0x29C */ s16 unk29C;
} CsPlayerView;
typedef struct CsCamStateView {
    /* 0x00 */ u8 pad0[0xBC];
    /* 0xBC */ s16 unkBC;
} CsCamStateView;

s32 csIsPlayerInCutsceneState(void) {
    CsCamStateView *cam = gPlayerSlots->unk4->customState;

    if ((gPrimaryPlayerActor->state == 0x42 && (cam->unkBC == 0x62 || cam->unkBC == 0x88 || cam->unkBC == 0x17)) || gPrimaryPlayerActor->state == 0x52 ||
        gPrimaryPlayerActor->state == 0x67 || ((CsPlayerView *)gPlayerSlots)->unk29C == 0x1C || ((CsPlayerView *)gPlayerSlots)->unk29C == 0x53) {
        return 0;
    }
    return 1;
}

void modelSlotFreeByIndex(s16, s32);

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

void csStateShareScript(s16 a, s16 b, s16 c) {
    a = hashTableLookup(a);
    b = hashTableLookup(b);
    gModelSlots[a].unk7C = heapAlloc(0xA4);
    csStateInit(gModelSlots[a].unk7C);
    ((CsAuxView *)gModelSlots[a].unk7C)->unk48 = c;
    ((CsAuxView *)gModelSlots[a].unk7C)->unkA0 = ((CsAuxView *)gModelSlots[b].unk7C)->unkA0;
}

void csSetActorAlphaByType(s16 a, s16 b, s16 csId) {
    s32 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && actor->actorType == a && csId == actor->cutsceneId) {
            if (b != 0) {
                actor->flags2 |= 4;
            } else {
                actor->flags2 &= ~4;
            }
        }
    }
}

void csSetActorScaleFadeByType(s16 a, s16 b, s16 csId) {
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
        if (!(actor->flags & 0x2000) && actor->actorType == a && csId == actor->cutsceneId) {
            actorAppendCallback(actor, 0, 0x800, x, 0, 0);
        }
    }
}

s32 func_80678014(s32);
u16 camStartPath(void *, s16, s32);  // FAKE: callee prototype steer

void csStartCamPath(void *cs, s16 camIdx, s16 mode, s16 c) {
    s32 flag;

    if (((CsState *)cs)->unk94 == NULL && func_80678014(0x14) != 0) {
        ((CsState *)cs)->unk94 = gSpawnedActor;
        gSpawnedActor->unk144 = 1;
        gSpawnedActor->x = gCsPosX;
        gSpawnedActor->y = gCsPosY;
        gSpawnedActor->z = gCsPosZ;
        gSpawnedActor->yaw = gCsRotY * 4096.0f / 360.0f;
        if (*(u8 *)&D_807F693F != 0) {
            gSpawnedActor->eyeHeight = c;
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

extern u8 gViewportCount;
f32 sqrtf(f32);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, Mtx *, f32, u8);

typedef struct CsPlayerScreenView {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x270 - 8];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ u8 pad278[0x2F0 - 0x278];
} CsPlayerScreenView;
#define CS_PLAYERS_SCREEN ((CsPlayerScreenView *)gPlayerSlots)

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
        if (CS_PLAYERS_SCREEN[i].unk0 != 0) {
            a = CS_PLAYERS_SCREEN[i].unk4;
            dx = gCsPosX - a->x;
            dy = gCsPosY - a->y;
            dz = gCsPosZ - a->z;
            dx *= dx;
            dy *= dy;
            dz *= dz;
            if (sqrtf(dx + dy + dz) < radius) {
                camProjectToScreen(gCsPosX, gCsPosY, gCsPosZ, &sx, &sy, 0, 1.0f, i);
                if ((s16)sx >= CS_PLAYERS_SCREEN[i].unk270 + 0x14 && (s16)sy >= CS_PLAYERS_SCREEN[i].unk272 + 0x14 &&
                    CS_PLAYERS_SCREEN[i].unk274 - 0x14 >= (s16)sx && CS_PLAYERS_SCREEN[i].unk276 - 0x14 >= (s16)sy) {
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

s32 csPosWithinRadius(s16 radius, f32 x, f32 y, f32 z) {
    f32 dx = gCsPosX - x;
    f32 dy = gCsPosY - y;
    f32 dz = gCsPosZ - z;

    dx *= dx;
    dy *= dy;
    dz *= dz;
    return (u8)(sqrtf(dx + dy + dz) < radius);
}

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

s32 csPosWithinRadius(s16, f32, f32, f32);

s32 csPlayerNearPos(s16 targetPosIndex) {
    u8 i;
    CsPlayerPosView *p;

    for (i = 0; i < gViewportCount; i++) {
        p = (CsPlayerPosView *)gPlayerSlots + i;
        if (p->unk0 != 0) {
            Actor *a = p->unk4;
            if (csPosWithinRadius(targetPosIndex, a->x, a->y, a->z)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 csPlayerSavedPosNearPos(s16 targetPosIndex) {
    u8 i;
    CsPlayerPosView *p;

    for (i = 0; i < gViewportCount; i++) {
        p = (CsPlayerPosView *)gPlayerSlots + i;
        if (p->unk0 != 0 && csPosWithinRadius(targetPosIndex, p->unk210, p->unk214, p->unk218)) {
            return 1;
        }
    }
    return 0;
}


s32 csSpawnNodeNearPos(s16 targetPosIndex, s16 minNodeIndex, s16 maxNodeIndex) {
    s16 i;
    Actor *a;

    for (i = minNodeIndex; i <= maxNodeIndex; i++) {
        if (spawnNodeHasActor(i)) {
            a = spawnNodeActivate(i, 0);
            if (a != NULL) {
                if (csPosWithinRadius(targetPosIndex, a->x, a->y, a->z)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);

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

    ret = 0;
    switch ((u8)((packedParam >> 8) % 255)) {
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
    mode = packedParam & 0xFF;
    switch (mode) {
    case 0:
        th = compareValue / 10.0f;
        if (((th < v) ? (v - th) : (th - v)) != 0.1) {
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


void csSetRot(s16 modeAndAxis, s16 rotValue, void *cs, s16 csId, u8 isRelative) {
    f32 v;
    u8 lo;
    u8 hi;

    lo = modeAndAxis & 0xFF;
    hi = (modeAndAxis >> 8) & 0xFF;
    v = rotValue / 10.0f;
    if (lo == 1) {
        v = ((CsState *)cs)->unk14[rotValue];
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

void csSetPos(s16 modeAndAxis, s16 posValue, void *cs, s16 csId, u8 isRelative) {
    f32 v;
    u8 lo;
    u8 hi;

    lo = modeAndAxis & 0xFF;
    hi = (modeAndAxis >> 8) & 0xFF;
    v = posValue / 10.0f;
    if (lo == 1) {
        v = ((CsState *)cs)->unk14[posValue];
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

u32 randomLcgNext(void);
void effectSetDuration(s32);
void effectSetSpeed(s32);
void effectSetCallback(void *);
void effectCreateAtPosition(void *, f32, f32, f32, f32);
void func_80717D4C(void);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8);
extern u8 D_8071FC58[];

void csCmdSpawnSparkAndLight(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i != 1U; i++) {
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

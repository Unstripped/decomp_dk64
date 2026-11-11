#include "common.h"
#define PROTO_SKIP_sfxStopSlotSound // FAKE: callee prototype steer
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/race/1770.h"
#include "proto/race/7BD0.h"

s32 raceGetNextWaypointIndex(s32 pathLength, s32 curWaypoint) {
    s32 next = curWaypoint + 1;
    if (pathLength != next) {
        return curWaypoint + 1;
    }
    return 0;
}

s32 raceGetPrevWaypointIndex(s32 pathLength, s32 curWaypoint) {
    if (curWaypoint == 0) {
        return pathLength - 1;
    }
    return curWaypoint - 1;
}

typedef struct TargetVec3f {
    f32 x, y, z;
} RaceAPoint3f;

struct RaceActor;

/* Per-participant checkpoint path state (RaceActor.unk178). */
typedef struct RacePathState {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[4];
    void *unk30;
    void *unk34;
    u8 pad38;
    u8 unk39;
    u8 pad3A[2];
} RacePathState;

/* Participant state (RaceActor.unk174). */
typedef struct RaceParticipant {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x14];
    u16 unk1C;
    u8 pad1E[7];
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 pad2B;
    struct RaceActor *unk2C;
    struct RaceActor *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    s8 unk37;
    u8 pad38[2];
    u16 unk3A;
    u8 pad3C[4];
    f32 unk40;
} RaceParticipant;

/* Auxiliary state (RaceActor.unk17C). */
typedef struct {
    u16 unk0;
    u8 pad2[6];
    s32 unk8;
    struct RaceActor *unkC;
} RaceAuxState;

typedef struct RaceActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0xA];
    s16 unk6E[2];
    u8 pad72[2];
    f32 unk74;
    u8 pad78[4];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    f32 unk88;
    u8 pad8C[4];
    f32 unk90;
    u8 pad94[0x24];
    f32 unkB8;
    u8 padBC[0x28];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[4];
    s16 unkEE;
    u8 padF0[0x54];
    u8 unk144;
    u8 pad145[0x2F];
    RaceParticipant *unk174;
    RacePathState *unk178;
    RaceAuxState *unk17C;
    u8 pad180[4];
    void *unk184;
} RaceActor;

typedef struct {
    RaceActor *actor;
    RaceParticipant *participant;
} RaceNodeLinks;

/* Effect node actor spawned by spawnNodeSpawnById. */
typedef struct {
    u8 pad0[0x178];
    RaceParticipant *unk178;
    RacePathState *unk17C;
    u8 pad180[4];
    RaceNodeLinks *unk184;
} RaceNodeActor;

extern RaceAPoint3f **D_807F5FD4;
extern RaceActor *gCurrentActor;
f32 mathSinF(s16);

void raceInterpolateWaypointPos(RacePathState *pathState, f32 *outPos, f32 *inPos, s32 nextWaypoint, s32 nextNextWaypoint) {
    s32 padA;
    s32 padB;
    RaceAPoint3f *points;
    s32 i;
    f32 closerTarget[3];
    s32 padM;
    s8 laneDiff;
    RaceAPoint3f *curPoint;

    points = D_807F5FD4[pathState->unk1];
    curPoint = &points[pathState->unk2];
    laneDiff = pathState->unk0 - pathState->unk1;
    mathPickCloserTargetPoint3D(inPos[0], inPos[1], inPos[2], curPoint, &points[nextWaypoint], &points[nextWaypoint], &points[nextNextWaypoint], &closerTarget[0], &closerTarget[1], &closerTarget[2]);
    pathState->unk8 += 0.01 * gCurrentActor->unkB8;
    if (pathState->unk8 >= 1.0f) {
        pathState->unk8 = 1.0f;
        pathState->unk0 = pathState->unk1;
    }
    pathState->unkC = mathSinF(pathState->unk8 * 2048.0f) * (laneDiff * 300);
    for (i = 0; i < 3; i++) {
        outPos[i] = outPos[i] + pathState->unk8 * (closerTarget[i] - outPos[i]);
    }
}

extern s32 D_807F5FD0;
void *memcpy(void *, const void *, unsigned int);

void raceInitSplinePoints(void) {
    RaceAPoint3f *buf;
    u8 *src;
    RaceAPoint3f **tbl;
    u32 lo; /* byte length first, then the upper table pointer (one slot reused) */
    s32 i;
    s32 count;

    count = (D_807F5FD4[1] - D_807F5FD4[0]) / 2;
    buf = heapAlloc(count * 0x24);
    tbl = heapAlloc(0x10);
    for (i = 0; i < 4; i++) {
        tbl[i] = buf + i * count;
    }
    src = (u8 *)D_807F5FD4[0];
    lo = count * 12;
    buf = tbl[0];
    memcpy(buf, src, lo);
    buf = tbl[2];
    memcpy(buf, lo + src, lo);
    buf = tbl[1];
    src = (u8 *)tbl[0];
    lo = (u32)tbl[2];
    for (i = 0; i < count; i++) {
        buf[i].x = (((RaceAPoint3f *)lo)[i].x + ((RaceAPoint3f *)src)[i].x) * 0.5;
        buf[i].y = (((RaceAPoint3f *)lo)[i].y + ((RaceAPoint3f *)src)[i].y) * 0.5;
        buf[i].z = (((RaceAPoint3f *)lo)[i].z + ((RaceAPoint3f *)src)[i].z) * 0.5;
    }
    D_807F5FD0 = 3;
    D_807F5FD4 = tbl;
}

extern s16 D_80750AC4;
extern RaceActor *gSpawnedActor;

void raceInitOpponentEntities(RaceActor *parent) {
    RaceParticipant *parentPart;
    RaceActor *s2;
    RacePathState *s1;
    RaceParticipant *s0;
    RaceNodeLinks *temp;
    RaceNodeActor *spawnedNode;
    RaceActor *spawnedActor;
    u8 *pad;

    parentPart = parent->unk174;
    raceInitParticipantArray(parent, 2);
    actorSpawn(0x12E, 0x95);
    s2 = gSpawnedActor;
    s0 = s2->unk174;
    raceRegisterParticipant(parent, 1, s2, s0);
    s0->unk37 = 0;
    s0->unk27 = 0;
    s0->unk30 = parent;
    s0->unk36 = 1;
    s0->unk28 = 0;
    s1 = s2->unk178;
    spawnedNode = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
    s1->unk30 = spawnedNode;
    temp = spawnedNode->unk184;
    temp->participant = s0;
    temp->actor = s2;
    actorSpawn(0x130, 0);
    spawnedActor = gSpawnedActor;
    s1->unk34 = spawnedActor;
    s0 = spawnedNode->unk178;
    raceRegisterParticipant(parent, 0, spawnedNode, s0);
    s0->unk37 = 0;
    s0->unk27 = 1;
    s0->unk30 = parent;
    s0->unk36 = 0;
    s1 = spawnedNode->unk17C;
    s1->unk30 = s2;
    s1->unk34 = spawnedActor;
    s0 = spawnedActor->unk174;
    s0->unk30 = parent;
    s1 = spawnedActor->unk178;
    s1->unk30 = s2;
    D_80750AC4 = 0;
    parentPart->unk25 = 1;
}


void raceInitSplineAndOpponent(void) {
    raceInitSplinePoints();
    raceInitCarRaceManager();
}


void racePlayCheckpointSfx(RacePathState *pathState, u8 timer, f32 volume) {
    pathState->unk10 = timer;
    pathState->unk14 = volume;
    sfxPlayOnFreeSlot(0x1EB, 0x7FFF, 64.0f, 1.0f, 0, 0);
}

void raceAdvanceCheckpoint(RacePathState *pathState, RaceParticipant *participant, s32 pathLength) {
    if (pathState->unk2 + 1 != pathLength) {
        pathState->unk2++;
    } else {
        pathState->unk2 = 0;
        if (participant != NULL) {
            participant->unk37++;
        }
    }
    if (participant != NULL) {
        participant->unk3A = pathState->unk2 + 1;
    }
}

f32 mathCosF(s16);
extern u8 D_8072006C[];
extern void *D_8002FBB0[4];
extern u8 gLightSlotsEnd;
void raceApplyPositionOffset(f32 *tgt, f32 *pos) {
    s16 angle;
    s32 pad;
    f32 offsetDist;
    f32 dz;
    f32 dx;

    angle = mathAngleBetweenPointsRad(tgt[0], tgt[2], pos[0], pos[2]) * 2048.0 / 3.1415927f;
    dz = pos[2] - tgt[2];
    dx = pos[0] - tgt[0];
    offsetDist = sqrtf((dz * dz) + (dx * dx)) * (*(f32 *)&gCurrentActor->unkB8 * 0.03);
    gCurrentActor->unk7C = pos[0] + (mathSinF(angle) * offsetDist);
    gCurrentActor->unk84 = pos[2] + (mathCosF(angle) * offsetDist);
    gCurrentActor->unk80 = gCurrentActor->unk80 + (tgt[1] - gCurrentActor->unk80) * 0.8;
}


void raceUpdateOrientation(RacePathState *pathState) {
    s16 pad;
    s16 rollOffset;
    f32 sinVal;
    s16 yawOffset;
    f32 rollScaled;
    f32 cosVal;

    yawOffset = pathState->unk18 + pathState->unkC;
    rollOffset = mathAngleSignedDistance(0, (s16)pathState->unk1C);
    yawOffset &= 0xFFF;
    sinVal = mathCosF(yawOffset);
    cosVal = mathSinF(yawOffset);
    gCurrentActor->unkE6 = gCurrentActor->unkEE + yawOffset;
    gCurrentActor->unkE6 &= 0xFFF;
    rollScaled = rollOffset;
    gCurrentActor->unkE8 = rollScaled * sinVal;
    gCurrentActor->unkE8 = gCurrentActor->unkE8 + pathState->unk20;
    gCurrentActor->unkE8 &= 0xFFF;
    gCurrentActor->unkE4 = rollScaled * cosVal;
    gCurrentActor->unkE4 = gCurrentActor->unkE4 + pathState->unk24;
    gCurrentActor->unkE4 &= 0xFFF;
}


void racePathFollowStep(RacePathState *pathState, RaceParticipant *participant, u8 spawnSparks) {
    s32 count;
    s32 next;
    s32 next2;
    RaceAPoint3f *points;
    RaceAPoint3f *cur;
    RaceAPoint3f *nxt;
    RaceAPoint3f *nxt2;
    f32 pos[3];
    f32 tgt[3];
    f32 ang;
    f32 thrust;
    f32 oldAng;
    f32 spd;
    f32 dist;
    u8 flag;
    s16 yawDelta;
    f32 hx;
    f32 hy;
    f32 hz;

    count = D_807F5FD4[pathState->unk0 + 1] - D_807F5FD4[pathState->unk0];
    next = raceGetNextWaypointIndex(count, pathState->unk2);
    next2 = raceGetNextWaypointIndex(count, next);
    points = D_807F5FD4[pathState->unk0];
    cur = &points[pathState->unk2];
    nxt2 = &points[next2];
    nxt = &points[next];
    oldAng = gCurrentActor->unkEE;
    flag = pathState->unk39;
    if (!(gCurrentActor->unk60 & 0x10)) {
        gCurrentActor->unk7C = cur->x;
        gCurrentActor->unk80 = cur->y;
        gCurrentActor->unk84 = cur->z;
        gCurrentActor->unkB8 = 0.0f;
        gCurrentActor->unkE6 = mathAngleBetweenPointsRad(nxt->x, nxt->z, gCurrentActor->unk7C, gCurrentActor->unk84) * 2048.0 / 3.1415927f;
        gCurrentActor->unkEE = gCurrentActor->unkE6;
        pathState->unk18 = 0.0f;
    }
    if (flag != 0) {
        thrust = 0.0f;
        pathState->unk39--;
        gCurrentActor->unkB8 = 0.0f;
        pathState->unk14 = 0.0f;
        pathState->unk10 = 0;
    } else {
        thrust = participant->unk4;
    }
    if (pathState->unk10 != 0) {
        pathState->unk10--;
    } else {
        pathState->unk14 = pathState->unk14 * 0.7;
    }
    spd = gCurrentActor->unkB8 * gCurrentActor->unkB8 * 0.0033333334f + 0.2;
    gCurrentActor->unkB8 = gCurrentActor->unkB8 + (thrust - spd);
    if (gCurrentActor->unkB8 < 0.0f) {
        gCurrentActor->unkB8 = 0.0f;
    }
    ang = mathAngleBetweenPointsRad(nxt->x, nxt->z, cur->x, cur->z) * 2048.0 / 3.1415927f;
    pos[0] = mathSinF(gCurrentActor->unkEE) * gCurrentActor->unkB8 + gCurrentActor->unk7C;
    pos[2] = mathCosF(gCurrentActor->unkEE) * gCurrentActor->unkB8 + gCurrentActor->unk84;
    pos[1] = gCurrentActor->unk80;
    dist = sqrtf((cur->x - nxt->x) * (cur->x - nxt->x) + (cur->z - nxt->z) * (cur->z - nxt->z));
    pathState->unk1C = mathAngleEaseToward(pathState->unk1C, mathAtan2(cur->y - nxt->y, dist) * 2048.0 / 3.1415927f, 3.0f);
    if (gCurrentActor->unkB8 > 0.001) {
        gCurrentActor->unkEE = mathAngleEaseToward(gCurrentActor->unkEE, ang, 50.0f / gCurrentActor->unkB8);
    }
    if (mathPickCloserTargetPoint3D(pos[0], pos[1], pos[2], cur, nxt, nxt, nxt2, &tgt[0], &tgt[1], &tgt[2]) != 0) {
        raceAdvanceCheckpoint(pathState, participant, count);
        next = raceGetNextWaypointIndex(count, pathState->unk2);
        next2 = raceGetNextWaypointIndex(count, next);
        cur = &points[pathState->unk2];
        nxt2 = &points[next2];
    }
    if (pathState->unk0 != pathState->unk1) {
        raceInterpolateWaypointPos(pathState, tgt, pos, next, next2);
    } else if (pathState->unk4 != 0) {
        pathState->unk4--;
    }
    raceApplyPositionOffset(tgt, pos);
    yawDelta = mathAngleSignedDistance(gCurrentActor->unkEE, (s16)oldAng);
    pathState->unk28 += -0.04f * gCurrentActor->unkB8 * yawDelta * mathCosF(pathState->unk18);
    pathState->unk28 -= 10.0f * gCurrentActor->unkB8 * mathSinF(pathState->unk18);
    pathState->unk28 = pathState->unk28 * 0.7f;
    pathState->unk18 = pathState->unk18 + pathState->unk28;
    raceUpdateOrientation(pathState);
    if (spawnSparks != 0) {
        if ((randomLcgNext() & 0xFF) < gCurrentActor->unkB8 * 0.3 && pathState->unk0 == pathState->unk1) {
            mathPickCloserTargetPoint3D(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, cur, &points[next], &points[next], nxt2, &hx, &hy, &hz);
            effectSetSpeed((s32)gCurrentActor);
            effectSetCallback(timedLightOrbitUpdate);
            D_8002FBB0[gLightSlotsEnd] = effectCreateAtPosition(D_8072006C, 0.4f, hx, hy, hz);
            gLightSlotsEnd++;
            gLightSlotsEnd = gLightSlotsEnd % 4;
            sfxPlayAtPositionPooled(hx, hy, hz, 0x8A, 0x96, 0x7F, 0x14, 0x50, 0.3f, 0);
        }
    }
    if (participant != NULL) {
        nxt = &points[next];
        participant->unk40 = (gCurrentActor->unk7C - nxt->x) * (gCurrentActor->unk7C - nxt->x) + (gCurrentActor->unk80 - nxt->y) * (gCurrentActor->unk80 - nxt->y) + (gCurrentActor->unk84 - nxt->z) * (gCurrentActor->unk84 - nxt->z);
    }
}


void raceSpawnProjectile(RaceParticipant *participant) {
    RacePathState *projPath;
    RacePathState *actorPath;
    RaceAuxState *projAux;

    if (participant->unk2C == NULL && participant->unk2A != 0) {
        actorPath = gCurrentActor->unk178;
        participant->unk2A--;
        actorSpawn(0x131, 0x96);
        projPath = gSpawnedActor->unk178;
        projAux = gSpawnedActor->unk17C;
        projAux->unkC = gCurrentActor;
        projAux->unk8 = raceFindNearestParticipant(gCurrentActor);
        participant->unk2C = gSpawnedActor;
        gSpawnedActor->unk7C = gCurrentActor->unk7C;
        gSpawnedActor->unk80 = gCurrentActor->unk80;
        gSpawnedActor->unk84 = gCurrentActor->unk84;
        gSpawnedActor->unkEE = gCurrentActor->unkEE;
        gSpawnedActor->unkE6 = gCurrentActor->unkE6;
        gSpawnedActor->unkB8 = gCurrentActor->unkB8;
        *projPath = *actorPath;
        sfxPlayOnFreeSlot(0x18B, 0x7FFF, 64.0f, 1.0f, 0, 0);
    } else {
        sfxPlayOnFreeSlot(0xE2, 0x7FFF, 64.0f, 1.0f, 0, 0);
    }
    participant->unk29 = 0;
}


void racePlayEngineSfx(void) {
    sfxPlayActorSound(gCurrentActor, 0x12D, 0, 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(gCurrentActor, 0x12E, 0, 1, 1, 0xFF, 1.0f, 0);
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void raceUpdateEngineSoundPitch(f32 moveSpeed) {
    s32 pad;
    s16 idx;

    idx = D_80770628[gCurrentActor->unk6E[0]];
    D_80770B68[idx] = moveSpeed / 20.0 + 1.0;
    D_80770BC0[idx] = 1.0f;
    idx = D_80770628[gCurrentActor->unk6E[1]];
    gCurrentActor->unk74 = moveSpeed / 20.0;
    if (gCurrentActor->unk74 > 1.0) {
        gCurrentActor->unk74 = 1.0f;
    }
    if (gCurrentActor->unk74 < 0.0) {
        gCurrentActor->unk74 = 0.0f;
    }
    if (D_80770BC0[idx] == 0.0f) {
        D_80770B68[idx] = ((u32)randomLcgNext() / 4294967295.0 * 0.05 + 0.975) * (0.2 + moveSpeed / 15.0);
        D_80770BC0[idx] = 3.0f;
    }
}


void raceVehicleRenderCallback(void *glist, RaceActor *actor) {
    raceRenderHud(glist, actor, actor->unk174);
}

extern u8 gBossFightPhase;
extern void *gPrimaryPlayerActor;
void sfxStopSlotSound(void *, s32); // FAKE: callee prototype steer

void raceVehicleBehaviorUpdate(void) {
    s32 len;
    RacePathState *pathState;
    RaceParticipant *s1;
    s16 sv;
    f32 off;
    f32 pad; /* unused: its stack home is needed for the frame layout */
    RaceActor *o;
    RaceParticipant *o2;
    s32 i;
    f32 bumpX;
    f32 bumpY;
    f32 bumpZ;

    s1 = gCurrentActor->unk174;
    pathState = gCurrentActor->unk178;
    if (!(gCurrentActor->unk60 & 0x10)) {
        len = D_807F5FD4[pathState->unk0 + 1] - D_807F5FD4[pathState->unk0];
        s1->unk2A = 3;
        gCurrentActor->unk144 = 0x3C;
        pathState->unk2 = raceGetPrevWaypointIndex(len, 0);
        racePathFollowStep(pathState, s1, 1);
        if (func_807142D8() != 0 || flagGet(0x12, 2) != 0) {
            playerStateQueueCallback(0x4B, gCurrentActor, s1->unk28);
        } else {
            playerWaypointPathStartPacked(gPrimaryPlayerActor, gCurrentActor, 0, 0x4B);
        }
        actorClearNodeFlag(gCurrentActor, 2);
        racePlayEngineSfx();
    }
    if (gBossFightPhase == 5 && pathState->unk39 == 0) {
        if (s1->unk34 == 2) {
            behaviourAddSlotQueueValueB(3);
        }
        pathState->unk39 = 0x1E;
    }
    if (s1->unk35 == 0) {
        if (s1->unk34 == 1) {
            slotQueueUpdate(0xB, 1, 0);
            s1->unk35++;
        } else if (s1->unk34 == 5) {
            slotQueueCancel(0xB, 0);
            s1->unk35++;
        }
    }
    if (s1->unk34 == 1) {
        o = s1->unk30;
        o2 = o->unk174;
        if (o2->unk1C == 8 || o2->unk1C == 0x13) {
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x187, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        raceUpdateEngineSoundPitch(s1->unk26 * 1.5);
    } else if (s1->unk34 < 5) {
        sv = 0;
        if (s1->unk26 != 0) {
            bumpZ = raceGetHandicapSpeedBonus(s1);
            if (bumpZ != 0) {
                bumpZ = 1.5f * bumpZ + 1.5f;
                racePlayCheckpointSfx(pathState, 0x1E, bumpZ);
            }
            s1->unk26 = 0;
        }
        if (pathState->unk39 != 0) {
            bumpX = pathState->unk39;
            if (bumpX > 10.0f) {
                sv = (bumpX - 10.0f) * 204.8f;
                bumpX = 300.0f;
                pathState->unk20 = mathSinF(sv) * bumpX;
                pathState->unk24 = mathSinF(sv * 2) * bumpX;
            } else {
                pathState->unk20 = 0.0f;
                pathState->unk24 = 0.0f;
            }
        }
        racePathFollowStep(pathState, s1, 1);
        gCurrentActor->unk80 += 20.0f * mathSinF(sv * 0.5f);
        raceUpdateEngineSoundPitch(gCurrentActor->unkB8);
    } else if (s1->unk34 == 5) {
        gCurrentActor->unk60 &= ~4;
        gCurrentActor->unkB8 = 0.0f;
        for (i = 0; i != 2; i++) {
            if (gCurrentActor->unk6E[i] != -1) {
                sfxStopSlotSound(gCurrentActor, i & 0xFF);
            }
        }
    }
    if (s1->unk29 != 0) {
        raceSpawnProjectile(s1);
    }
    if (s1->unk34 < 5) {
        if (s1->unk34 == 2) {
            off = 10.0;
        } else {
            off = -200.0f;
        }
        bumpX = gCurrentActor->unk7C;
        bumpZ = gCurrentActor->unk84;
        bumpY = gCurrentActor->unk80 + off;
        gridSetNodeBounds(s1->unk28, bumpX, bumpY, bumpZ, 12.0f);
        bumpX += gCurrentActor->unk88;
        bumpX *= 0.5;
        bumpZ += gCurrentActor->unk90;
        bumpZ *= 0.5;
        gridAppendPositionNode(s1->unk28, bumpX, bumpY, bumpZ, 12.0f);
    }
    if (gCurrentActor->unk60 & 4) {
        actorSpawnNodeEffectFacingCamera(1, 0xC8);
        actorSpawnNodeEffectFacingCamera(2, 0xC8);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (s1->unk34 > 0 && s1->unk34 < 5) {
        renderCallbacksRegister(raceVehicleRenderCallback, gCurrentActor, 3);
    }
}

extern ActorGlobalState gActorGlobalState;

extern u8 D_80720340[];
extern u8 sEffectSparkConfig[];


void raceProjectileBehaviorUpdate(void) {
    RaceParticipant *participant;
    RacePathState *pathState;
    s32 pad[3];
    u8 hasCollided;
    RaceAuxState *s1;
    u16 t3;

    hasCollided = 0;
    participant = gCurrentActor->unk174;
    pathState = gCurrentActor->unk178;
    s1 = gCurrentActor->unk17C;
    if (!(gCurrentActor->unk60 & 0x10)) {
        s1->unk0 = 0x78;
        gCurrentActor->unk60 |= 0x10;
        gCurrentActor->unk144 = 0x3C;
        participant->unk4 = 5.0f;
    }
    if ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0) || (gActorGlobalState.bossFightPhase == 5)) {
        effectSetDepth(1);
        effectCreateAtPosition(D_80720340, 3.0f, gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84);
        sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0xF6, 0xFF, 0x7F, 0x14, 0x32, 0.3f, 0);
        hasCollided = 1;
    }
    racePathFollowStep(pathState, participant, 0);
    gCurrentActor->unk80 += 5.0f;
    if (s1->unk0 != 0) {
        effectSetDepth(1);
        effectCreateAtPosition(sEffectSparkConfig, 1.0f, gCurrentActor->unk7C, gCurrentActor->unk80 + 10.0f, gCurrentActor->unk84);
        if (--s1->unk0 == 0) {
            hasCollided = 1;
        }
    }
    if (hasCollided != 0) {
        raceDespawnProjectile(gCurrentActor, s1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

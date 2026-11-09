#include "common.h"

typedef struct {
    f32 x, y, z;
} Point3f;

typedef struct RaceActor RaceActor;

typedef struct RaceCursor {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[8];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0xC];
    /* 0x30 */ RaceActor *unk30;
    /* 0x34 */ u8 pad34[5];
    /* 0x39 */ u8 unk39;
} RaceCursor;

typedef struct RaceState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x14];
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u8 pad1E[6];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[7];
    /* 0x30 */ RaceActor *unk30;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ s8 unk37;
    /* 0x38 */ u8 pad38[2];
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u8 pad3C[9];
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 pad46[0xBE];
    /* 0x104 */ void *unk104;
} RaceState;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[7];
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
} RaceAux;

typedef struct {
    /* 0x174 */ void *unk174;
    /* 0x178 */ RaceState *unk178;
    /* 0x17C */ RaceCursor *unk17C;
    /* 0x180 */ u8 *unk180;
    /* 0x184 */ RaceAux *unk184;
} RaceViewA;

typedef struct {
    /* 0x174 */ RaceState *unk174;
    /* 0x178 */ RaceCursor *unk178;
} RaceViewB;

struct RaceActor {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[0xA];
    /* 0x6E */ s16 unk6E[2];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x28];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ u8 padE6[2];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[0x5A];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ union {
        RaceViewA a;
        RaceViewB b;
    } view;
};

extern Point3f **D_807F5FD4;
extern RaceActor *gCurrentActor;

s32 raceGetNextWaypointIndex(s32, s32);

s32 raceGetWaypointDiff(s32 pathLength, RaceCursor *curA, RaceCursor *curB) {
    s32 diff;
    s32 abs_diff;
    s32 sign;

    diff = curB->unk2 - curA->unk2;
    abs_diff = (diff > 0) ? diff : -diff;
    if ((pathLength / 2) < abs_diff) {
        sign = (diff >= 0) ? 1 : -1;
        diff -= sign * pathLength;
    }
    return diff;
}

void mathPickCloserTargetPoint3D(f32, f32, f32, Point3f *, Point3f *, Point3f *, Point3f *, f32 *, f32 *, f32 *);

#define RB_SQ(v) ((v) * (v))
f32 raceGetWaypointSegmentFraction(s32 pathLength, RaceActor *actor, RaceCursor *cursor) {
    s32 idx1;
    s32 idx2;
    Point3f *base;
    Point3f *cur;
    Point3f *p1;
    Point3f *p2;
    Point3f out;
    f32 d2;
    f32 e2;

    idx1 = raceGetNextWaypointIndex(pathLength, cursor->unk2);
    idx2 = raceGetNextWaypointIndex(pathLength, idx1);
    base = D_807F5FD4[cursor->unk0];
    p1 = &base[idx1];
    p2 = &base[idx2];
    cur = &base[cursor->unk2];
    mathPickCloserTargetPoint3D(actor->unk7C, actor->unk80, actor->unk84, cur, p1, p1, p2, &out.x, &out.y, &out.z);
    d2 = RB_SQ(cur->x - p1->x) + RB_SQ(cur->y - p1->y) + RB_SQ(cur->z - p1->z);
    return sqrtf((e2 = RB_SQ(cur->z - out.z) + (RB_SQ(cur->x - out.x) + RB_SQ(cur->y - out.y))) / d2);
}

f32 raceGetPathDistance(s32 pathLength, u16 laneIndex, u16 waypointIndex) {
    s32 index;
    Point3f *points;
    Point3f *p1;
    Point3f *p2;
    f32 dx;
    f32 dy;
    f32 dz;

    index = raceGetNextWaypointIndex(pathLength, waypointIndex);
    points = D_807F5FD4[laneIndex];
    p1 = &points[waypointIndex];
    p2 = &points[index];
    dx = p1->x - p2->x;
    dy = p1->y - p2->y;
    dz = p1->z - p2->z;
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

f32 raceGetPathDistanceBetweenRacers(RaceActor *actorA, RaceCursor *curA, RaceActor *actorB, RaceCursor *curB) {
    s32 count;
    s32 dir;
    f32 fracA;
    f32 fracB;
    f32 distA;
    f32 distB;
    f32 total;
    s32 cur;
    s32 sign;
    s32 end;

    count = D_807F5FD4[curB->unk0 + 1] - D_807F5FD4[curB->unk0];
    dir = raceGetWaypointDiff(count, curA, curB);
    fracA = raceGetWaypointSegmentFraction(count, actorA, curA);
    fracB = raceGetWaypointSegmentFraction(count, actorB, curB);
    distA = raceGetPathDistance(count, curB->unk0, curA->unk2);
    distB = raceGetPathDistance(count, curB->unk0, curB->unk2);
    if (dir == 0) {
        total = fracB * distB - fracA * distA;
    } else {
        if (dir > 0) {
            total = fracB * distB + (1.0f - fracA) * distA;
            cur = raceGetNextWaypointIndex(count, curA->unk2);
            end = curB->unk2;
        } else {
            total = fracA * distA + (1.0f - fracB) * distB;
            cur = raceGetNextWaypointIndex(count, curB->unk2);
            end = curA->unk2;
        }
        while (cur != end) {
            total += raceGetPathDistance(count, curB->unk0, cur);
            cur = raceGetNextWaypointIndex(count, cur);
        }
        sign = (dir >= 0) ? 1 : -1;
        total = sign * total;
    }
    return total;
}

u32 randomLcgNext(void);

void raceChangeLaneRelative(RaceCursor *cursor, s8 dir) {
    if (dir > 0) {
        cursor->unk1++;
    } else {
        cursor->unk1--;
    }
    cursor->unk8 = 0.0f;
}

void raceChangeLaneRandom(RaceCursor *cursor) {
    switch (cursor->unk0) {
    case 0:
        cursor->unk1++;
        break;
    case 1:
        if ((randomLcgNext() & 0xFF) >= 0x80) {
            cursor->unk1++;
        } else {
            cursor->unk1--;
        }
        break;
    case 2:
        cursor->unk1--;
        break;
    }
    cursor->unk8 = 0.0f;
}

f32 raceGetCompletionFraction(RaceCursor *cursor, RaceState *state, RaceState *leaderState) {
    f32 result;
    s8 lap;
    s32 count;
    f32 num;
    f32 den;

    lap = state->unk37;
    result = 0.0f;
    if (lap > 0) {
        count = D_807F5FD4[cursor->unk0 + 1] - D_807F5FD4[cursor->unk0];
        num = (lap - 1) * count + state->unk3A;
        den = leaderState->unk24 * count;
        result = num / den;
    }
    return result;
}

extern void *D_80720120;
void effectSetDepth(s32);
void effectCreateAtActorBone(void *, f32, void *, s32, s32);

void raceTriggerBoostParticles(void) {
    s32 idx;

    for (idx = 1; idx < 3; idx++) {
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720120, 1.0f, gCurrentActor, idx, 0);
    }
}

extern f32 D_8002FBD0[];
extern u8 D_8002FC00[];
f32 raceEvaluateCurveTargetSpeed(RaceAux *, f32, f32 *, u8 *);
void raceSetPiecewiseCurveMode(RaceAux *, s32, f32 *, u8 *);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(void *, u8);
s32 spawnNodeHasActor(u8);
void *spawnNodeActivate(s16, s32);

void raceAiUpdateSpeedAndLane(void) {
    RaceState *state;
    RaceCursor *cursor;
    RaceActor *targetActor;
    RaceCursor *targetCursor;
    s32 pad44;
    RaceAux *aux;
    f32 distToTarget;
    f32 targetSpeed;
    u8 flag;
    u32 randVal;
    s32 nodeIndex;
    s32 foundCompetitor;
    RaceActor *competitorActor;
    RaceActor *leaderActor;
    RaceState *targetState;
    RaceCursor *competitorCursor;
    f32 competitorDist;

    state = gCurrentActor->view.a.unk178;
    cursor = gCurrentActor->view.a.unk17C;
    targetActor = cursor->unk30;
    targetCursor = targetActor->view.b.unk178;
    aux = gCurrentActor->view.a.unk184;
    distToTarget = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, targetActor, targetCursor);
    targetSpeed = raceEvaluateCurveTargetSpeed(aux, distToTarget, D_8002FBD0, D_8002FC00);
    flag = (cursor->unk0 == cursor->unk1) && (cursor->unk4 == 0);
    if (aux->unkF != 0) {
        leaderActor = state->unk30;
        if (raceGetCompletionFraction(cursor, state, leaderActor->view.b.unk174) > 0.8) {
            raceSetPiecewiseCurveMode(aux, 0, D_8002FBD0, D_8002FC00);
        }
    }
    switch (aux->unkF) {
    case 5:
        raceTriggerBoostParticles();
    case 0:
    case 1:
        if (flag) {
            randVal = randomLcgNext();
            if ((D_8002FBD0[2] < distToTarget) && (distToTarget < D_8002FBD0[4]) && (cursor->unk0 != targetCursor->unk0) && ((u8)((randVal & 0xFF) < 0x14))) {
                raceChangeLaneRelative(cursor, targetCursor->unk0 - cursor->unk0);
            } else if ((D_8002FBD0[6] < distToTarget) && (distToTarget < D_8002FBD0[8]) && (cursor->unk0 == targetCursor->unk0) && ((u8)((randVal & 0xFF) < 0x14))) {
                raceChangeLaneRandom(cursor);
            }
            flag = (cursor->unk0 == cursor->unk1) && (cursor->unk4 == 0);
            if (flag) {
                nodeIndex = 2;
                if ((distToTarget < D_8002FBD0[2]) || (D_8002FBD0[4] < distToTarget)) {
                    foundCompetitor = 0;
                    do {
                        if (spawnNodeHasActor(nodeIndex) != 0) {
                            competitorActor = spawnNodeActivate(nodeIndex, 0);
                            competitorCursor = competitorActor->view.b.unk178;
                            if (competitorCursor->unk0 == cursor->unk0) {
                                competitorDist = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, competitorActor, competitorCursor);
                                if ((competitorDist > 20.0f) && (competitorDist < 300.0f)) {
                                    foundCompetitor = 1;
                                    raceChangeLaneRandom(cursor);
                                }
                            }
                        }
                        nodeIndex++;
                    } while ((nodeIndex < 7) && (foundCompetitor == 0));
                }
            }
        }
        break;
    }
    state->unk4 = targetSpeed;
    if ((distToTarget < 0.0f) && (aux->unk14 > 0.0f)) {
        if (gCurrentActor->unk6E[1] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x130, 0, 1, 1, 0xFF, 1.0f, 0);
        }
        gCurrentActor->unk72 = 0x14;
    }
    if (gCurrentActor->unk72 > 0) {
        gCurrentActor->unk72--;
    } else if (gCurrentActor->unk6E[1] != -1) {
        sfxStopSlotSound(gCurrentActor, 1);
    }
    if (distToTarget < -7000.0f) {
        targetState = targetActor->view.b.unk174;
        targetState->unk45 = 1;
    }
    aux->unk14 = distToTarget;
}

void rumbleRequest(s32, u8, s32, u8 *);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);

void raceHandleCollisionRumble(RaceCursor *cursor) {
    RaceActor *v1;
    s32 pad[2];
    RaceAux *aux;
    f32 y;
    u8 *flag;

    v1 = cursor->unk30;
    flag = gCurrentActor->view.a.unk180;
    aux = gCurrentActor->view.a.unk184;
    if (gCurrentActor->unkB8 > v1->unkB8) {
        y = gCurrentActor->unkB8 - v1->unkB8;
    } else {
        y = -(gCurrentActor->unkB8 - v1->unkB8);
    }
    if (*flag == 0) {
        y *= 1.5;
        y = (y > 10.0) ? 10.0 : y;
        *flag = 3;
        rumbleRequest(0, 255.0f * y * 0.1f, *flag, flag);
        sfxPlayOnFreeSlot(0x18A, 0x7FFF, 64.0f, 1.0f, 0xA, 0);
        if (aux->unk14 < 0.0f) {
            v1->unkB8 -= y;
            gCurrentActor->unkB8 += y;
        } else {
            v1->unkB8 += y;
            gCurrentActor->unkB8 -= y;
        }
    }
}

void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, u8, s32, s32, f32, s32);

void racePlayTireScreechSfx(void) {
    RaceState *state;
    RaceActor *targetActor;
    RaceState *targetState;

    state = gCurrentActor->view.a.unk178;
    targetActor = state->unk30;
    targetState = targetActor->view.b.unk174;
    switch (targetState->unk1C) {
    case 0x5A:
        sfxPlayActorSound(gCurrentActor, 0x107, 0, 1, 0, 0xFF, 1.0f, 0);
    case 0x1D:
    case 0x25:
    case 0x2C:
    case 0x30:
    case 0x38:
    case 0x3F:
    case 0x43:
    case 0x47:
    case 0x4E:
    case 0x54:
        sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x187, 0xFF, (s32)(((f64)(targetState->unk1C - 0x1D) * 0.5) + 157.0), 0, 0, 0.3f, 0);
        break;
    }
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void raceUpdateOpponentEnginePitch(f32 moveSpeed) {
    s16 idx;

    idx = D_80770628[gCurrentActor->unk6E[0]];
    gCurrentActor->unk74 = 1.0f;
    D_80770B68[idx] = (f64)(moveSpeed * 0.05f) + 1.0;
    D_80770BC0[idx] = 1.0f;
}

extern u8 gBossFightPhase;
extern s16 D_80750AC8;
extern s32 D_8002FC0C[];
s32 raceGetPrevWaypointIndex(s32, s32);
void behaviourFrameBegin(void);
void actorClearNodeFlag(void *, s32);
void actorUpdateModelMatrix(void *, s32);
void racePathFollowStep(RaceCursor *, RaceState *, s32);
void raceSetIntroCutscenePhase(void *);
void raceClearIntroCutscenePhase(void *);
s32 raceCheckLapCompletionThreshold(RaceState *, void *, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void camStartPath(void *, s16, s32);
void camResumePath(void);
void mapCheckAutoTransition(void);
void csModelStateSetFirstByte(s32, s32);
s32 slotQueueGetValue(s32, s32);
void hudSpawnTextScreen(s32);
s32 playerStateQueueCallback(s32, s32, s32);
void spawnNodeSpawnById(s16, s32, s32, s32, s32, s32, s32);
f32 mathSinF(s16);
s32 func_807142D8(void);

void raceOpponentCarBehaviorUpdate(void) {
    s32 pad70[2];
    u8 *flagPtr;
    RaceAux *aux;
    s32 count;
    RaceActor *targetActor;
    RaceState *state;
    RaceCursor *cursor;
    u32 cursorVal;
    f32 unclampedVal;
    s32 phase;
    s32 idx;
    s32 statePhase;
    s32 endPhase;
    s32 pad38[1];
    s32 cam;
    s32 audioSlot;
    s32 pad30;

    state = gCurrentActor->view.a.unk178;
    cursor = gCurrentActor->view.a.unk17C;
    flagPtr = gCurrentActor->view.a.unk180;
    aux = gCurrentActor->view.a.unk184;
    targetActor = state->unk30;
    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        count = D_807F5FD4[cursor->unk0 + 1] - D_807F5FD4[cursor->unk0];
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->unk60 &= ~1;
        cursor->unk0 = cursor->unk1 = 2;
        aux->unk14 = 0.0f;
        cursor->unk2 = raceGetPrevWaypointIndex(count, 0);
        aux->unk10 = 1;
        raceSetPiecewiseCurveMode(aux, 5, D_8002FBD0, D_8002FC00);
        state->unk34 = 0;
        if ((flagGet(0x12, 2) == 0) && (flagGet(0x8B, 0) == 0) && (func_807142D8() == 0)) {
            camStartPath(gCurrentActor, 0, 1);
            flagSet(0x12, 1, 2);
        } else {
            state->unk35 = 3;
        }
        currentActorClearFlag();
        D_80750AC8 = 0xA;
        actorClearNodeFlag(gCurrentActor, 4);
    }
    if (gBossFightPhase == 4) {
        raceHandleCollisionRumble(cursor);
    } else if (gBossFightPhase == 5) {
        cursor->unk39 = 0x1E;
        cursor->unk20 = 0.0f;
    }
    if (*flagPtr != 0) {
        (*flagPtr)--;
    }
    cursorVal = cursor->unk39;
    if (cursorVal != 0) {
        unclampedVal = (f32)cursorVal;
        if (unclampedVal > 10.0f) {
            cursor->unk20 = (unclampedVal - 10.0f) * 204.8f;
        } else {
            cursor->unk20 = 0.0f;
        }
    } else if ((state->unk34 >= 2) && (state->unk34 < 4)) {
        raceAiUpdateSpeedAndLane();
    }
    if (state->unk34 == 1) {
        racePlayTireScreechSfx();
    }
    if (state->unk34 < 5) {
        racePathFollowStep(cursor, state, 1);
        gCurrentActor->unk80 += 50.0f * mathSinF((s16)(cursor->unk20 * 0.5f));
    } else {
        gCurrentActor->unkB8 = 0.0f;
    }
    raceUpdateOpponentEnginePitch(gCurrentActor->unkB8);
    if (state->unk34 == 0) {
        phase = state->unk35;
        statePhase = state->unk35;
        cursorVal = statePhase;
        switch (cursorVal) {
        case 0:
            if (gCurrentActor->unk60 & 0x02000000) {
                state->unk35 = state->unk35 + 1;
                phase = state->unk35;
            }
            break;
        case 1:
            if (!(gCurrentActor->unk60 & 0x02000000)) {
                camResumePath();
                state->unk35++;
                phase = state->unk35;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                state->unk35++;
            }
            phase = state->unk35;
            break;
        }
        if (phase < 3) {
            raceSetIntroCutscenePhase(targetActor);
        } else {
            raceClearIntroCutscenePhase(targetActor);
            idx = 2;
            do {
                spawnNodeSpawnById(idx, 0, 0, 0, 0, 0, 0);
                idx += 1;
            } while (idx < 7);
        }
    } else if (state->unk34 == 4) {
        if (state->unk35 == 0) {
            if (flagGet(0x8B, 0) == 0) {
                cam = D_8002FC0C[raceCheckLapCompletionThreshold(state, aux->unk4, 0xA)];
                camStartPath(gCurrentActor, cam, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
            state->unk35++;
        }
    } else if (state->unk34 == 5) {
        endPhase = state->unk35;
        switch (endPhase) {
        case 0:
            if (flagGet(0x8B, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                idx = 0;
                gCurrentActor->unkE4 = 0;
                audioSlot = 0;
                gCurrentActor->unkE8 = 0;
                do {
                    if (*(s16 *)((u8 *)gCurrentActor + audioSlot + 0x6E) != -1) {
                        sfxStopSlotSound(gCurrentActor, idx);
                    }
                    idx += 1;
                    audioSlot += 2;
                } while (idx != 2);
            }
            state->unk35++;
            break;
        case 1:
            if (gCurrentActor->unk60 & 0x02000000) {
                state->unk35++;
            }
            break;
        case 2:
            if (!(gCurrentActor->unk60 & 0x02000000)) {
                camResumePath();
                if ((state->unk36 == 0) || (slotQueueGetValue(0xB, 0) < 0xA)) {
                    state->unk35 = 3;
                }
                state->unk35++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                csModelStateSetFirstByte(0x62, 0xA);
                state->unk35++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (flagGet(0x8B, 0) != 0) {
                    mapCheckAutoTransition();
                } else {
                    hudSpawnTextScreen(1);
                }
                state->unk35++;
            }
            break;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad0[4];
    RaceActor *unk4;
    char pad8[0x2F0 - 8];
} RaceBStructPlayer;
extern RaceBStructPlayer *gPlayerSlots;
void camSetFixedView(void *, f32, f32, f32, f32, f32, f32, s32);

void raceCameraBehaviorUpdate(void) {
    s32 pad54[3];
    RaceActor *targetActor;
    RaceState *targetState;
    RaceCursor *targetCursor;
    s32 pad44;
    RaceState *playerState;
    s32 pad3C;
    int pathLength;
    f32 distToTarget;
    f32 offsetSign;
    f32 dist;
    f32 camYOffset;
    f32 distNorm;
    int prevWaypoint;
    u8 tgtStateMode;
    u8 tgtCursorSub;
    RaceCursor *cursor;
    RaceState *state;
    RaceActor *playerActor;

    cursor = gCurrentActor->view.b.unk178;
    state = gCurrentActor->view.b.unk174;
    targetActor = cursor->unk30;
    targetState = targetActor->view.b.unk174;
    targetCursor = targetActor->view.b.unk178;
    playerActor = gPlayerSlots[targetState->unk28].unk4;
    playerState = playerActor->view.b.unk174;
    pathLength = D_807F5FD4[cursor->unk0 + 1] - D_807F5FD4[cursor->unk0];
    offsetSign = 1.0f;
    if (!(gCurrentActor->unk60 & 0x10)) {
        prevWaypoint = raceGetPrevWaypointIndex(pathLength, targetCursor->unk2);
        cursor->unk2 = prevWaypoint;
        cursor->unk2 = raceGetPrevWaypointIndex(pathLength, (u16)prevWaypoint);
        cursor->unk0 = cursor->unk1 = 1;
        racePathFollowStep(cursor, state, 0);
    }
    tgtStateMode = targetState->unk34;
    if (state->unk34 != tgtStateMode) {
        state->unk34 = tgtStateMode;
        state->unk35 = 0;
    }
    dist = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, targetActor, targetCursor);
    distToTarget = dist;
    tgtCursorSub = targetCursor->unk1;
    if (cursor->unk1 != tgtCursorSub) {
        cursor->unk1 = tgtCursorSub;
        cursor->unk8 = 0.0f;
    }
    if ((state->unk34 >= 2) && (state->unk34 < 4)) {
        if ((u32)targetCursor->unk10 > 24.0) {
            offsetSign = -2.5f;
        } else if (targetCursor->unk14 > 0.5f) {
            offsetSign = 2.5f;
        }
        cursor->unk39 = targetCursor->unk39;
        cursor->unk10 = targetCursor->unk10;
        state->unk4 = targetState->unk4 + ((dist - (90.0f * offsetSign)) * 0.006f);
        if (dist < 30.0f) {
            if (targetActor->unkB8 < gCurrentActor->unkB8) {
                gCurrentActor->unkB8 = targetActor->unkB8;
            }
        }
        racePathFollowStep(cursor, state, 0);
    }
    if ((state->unk34 < 4) && (state->unk34 > 0)) {
        distNorm = distToTarget / 90.0f;
        if (distNorm < 0.0f) {
            camYOffset = 0.0f;
        } else {
            if (distNorm > 1.0f) {
                dist = 1.0f;
            } else {
                dist = distNorm;
            }
            camYOffset = dist;
        }
        camYOffset = (20.0f * camYOffset) + 20.0f;
        camSetFixedView(playerState->unk104, gCurrentActor->unk7C, gCurrentActor->unk80 + camYOffset, gCurrentActor->unk84, targetActor->unk7C, targetActor->unk80 + 20.0f, targetActor->unk84, 1);
    }
}


void raceFindNearestWaypoint(RaceCursor *cursor) {
    Point3f *p;
    s32 count;
    s32 i;
    s32 j;
    f32 best;
    f32 px;
    f32 py;
    f32 pz;
    f32 d;

    count = D_807F5FD4[1] - D_807F5FD4[0];
    p = D_807F5FD4[0];
    best = 10000000.0f;
    px = gCurrentActor->unk7C;
    py = gCurrentActor->unk80;
    pz = gCurrentActor->unk84;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < count; j++) {
            d = RB_SQ(px - p->x) + RB_SQ(py - p->y) + RB_SQ(pz - p->z);
            if (d < best) {
                cursor->unk2 = j;
                cursor->unk0 = i;
                cursor->unk1 = i;
                best = d;
            }
            p++;
        }
    }
}

typedef struct {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x200 - 0x16];
    u8 unk200;
} StructBB70_Race;
typedef struct {
    u8 pad0[0x14];
    u8 unk14;
} RaceDC9C;
extern StructBB70_Race gActorGlobalState;
extern RaceDC9C *gBehaviourExtraState;
void tagBarrelSpawnActorSmokePuffs(s32, s32);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void commandQueuePush(void *, s16, s16, s16, s32, s32, s32, s32, s32);

void raceObstacleCarBehaviorUpdate(void) {
    RaceActor *targetActor;
    RaceCursor *cursor;
    RaceState *state;
    RaceState *targetState;
    f32 nodeZ;
    f32 nodeY;
    f32 nodeX;

    state = gCurrentActor->view.a.unk178;
    cursor = gCurrentActor->view.a.unk17C;
    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        raceFindNearestWaypoint(cursor);
        gCurrentActor->unk144 = 0x3C;
        state->unk4 = 0.5f;
        actorClearNodeFlag(gCurrentActor, 1);
        cursor->unk30 = spawnNodeActivate(1, 0);
        gCurrentActor->unk60 &= ~1;
    }
    targetActor = cursor->unk30;
    targetState = targetActor->view.a.unk178;
    if ((gActorGlobalState.unk200 == 9) || (gActorGlobalState.unk15 != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        gCurrentActor->unk154 = 0x40;
    }
    actorGetNodePos(gCurrentActor, 6, &nodeX, &nodeY, &nodeZ);
    commandQueuePush(gCurrentActor, (s16)nodeX, (s16)nodeY, (s16)nodeZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    actorGetNodePos(gCurrentActor, 0xB, &nodeX, &nodeY, &nodeZ);
    commandQueuePush(gCurrentActor, (s16)nodeX, (s16)nodeY, (s16)nodeZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    racePathFollowStep(cursor, state, 1);
    if ((state->unk34 == 0) && (targetState->unk34 == 5)) {
        gBehaviourExtraState->unk14 = 0;
        gCurrentActor->unk154 = 0x40;
        state->unk34++;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

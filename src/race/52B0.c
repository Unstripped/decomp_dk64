#include "common.h"
#include "actor.h"
#include "proto/global/117190.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/FCCD0.h"
#include "proto/race/52B0.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

extern s32 D_8002FC5C[];

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

struct RaceC_Actor {
    u8 pad0[0x4];
    ActorSub4 *unk4;
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

#define RC_A ((RaceC_Actor *)gCurrentActor)

extern u8 gPlayerCount;
extern void *gCurrentActor;
extern RaceC_Actor *gSpawnedActor;
s32 actorSpawn(s32, s32);
Actor *spawnNodeSpawnById(s16, s16, s16, s16, s16, s16, s16);
void actorInitFromSpawnPoint(void *, void *);

void raceRacerRenderCallback(s32 renderContext, RaceC_Actor *actor) {
    raceRenderHud(renderContext, actor, actor->unk174);
}

void raceSpawnCompetitors(Actor *actor) {
    RaceC_State *managerState;
    RaceC_State *racerState;
    RaceC_Actor *spawnedActor;
    s32 slotIndex;
    s32 i;
    s32 numCompetitors;

    numCompetitors = gPlayerCount;
    slotIndex = 0;
    managerState = actor->customState;
    if (numCompetitors == 1) {
        numCompetitors++;
    }
    raceInitParticipantArray(actor, numCompetitors);
    for (i = 0; i < gPlayerCount; i++) {
        actorSpawn(0x133, 0x9F);
        spawnedActor = gSpawnedActor;
        racerState = spawnedActor->unk174;
        racerState->unk27 = 0;
        raceRegisterParticipant(actor, slotIndex, spawnedActor, racerState);
        slotIndex++;
        racerState->unk28 = i;
    }
    i = 0;
    if (gPlayerCount == 1) {
        spawnedActor = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        racerState = spawnedActor->unk178;
        racerState->unk27 = 1;
        raceRegisterParticipant(actor, slotIndex, spawnedActor, racerState);
        raceGetParticipantPair(actor, 0, spawnedActor->unk180, &spawnedActor->unk180->unk4);
        managerState->unk25 = 1;
    } else {
        managerState->unk25 = 0;
    }
    if (numCompetitors > 0) {
        do {
            raceGetParticipantPair(actor, i, &spawnedActor, &racerState);
            racerState->unk36 = i;
            racerState->unk30 = actor;
            if (racerState->unk27 == 0) {
                actorInitFromSpawnPoint(spawnedActor, racerState);
            }
            i++;
        } while (i != numCompetitors);
    }
    managerState->unk26 = 0;
}

void raceInitCompetitorsAndManager(void) {
    raceInitCompetitorRaceManager();
}

extern RaceC_Player *gPlayerSlots;
void actorInitAnimations(void *, void *);
void actorOrNodeFlags(Actor *, s32, u8);
void func_80690190(void *, void *);
void camSetTargetScaled(struct CamActor *, struct CamActor *, u8, s16, s16, s16, s16, s16, s16, s16, f32);
void func_8068F72C(void *, void *, s32, s32);
void renderCallbacksRegister(void *, void *, u8);
void sfxStopSlotSound(void *, u8);
void actorInterpolateAngles(u8, void *, void *);

void raceCompetitorMotionUpdate(void) {
    s32 v34;
    RaceC_State *nextState;
    RaceC_State *s4;
    RaceC_State *s1;
    RaceC_State *s0;
    s32 i;
    RaceC_Actor *tmp;
    u8 pad53;
    u8 subFlag;

    s4 = RC_A->unk174;
    nextState = RC_A->unk178;
    s1 = gPlayerSlots[s4->unk28].unk4->unk174;
    subFlag = RC_A->unk6A & 1;
    if (!(RC_A->unk60 & 0x10)) {
        actorInitAnimations(RC_A, gPlayerSlots[s4->unk28].unk4);
        RC_A->unk144 |= 0x10;
        RC_A->unk60 &= 0xFFFDFFFF;
        s4->unk44 = 5;
        actorOrNodeFlags(RC_A, 2, 0xC);
    }
    func_80690190(s4, nextState);
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
                camSetTargetScaled(s1->unk104, gCurrentActor, 4, 0x800, 0x32, 0, 0x28, 0x1E, 0x14, 0, 0.4f);
            }
        }
        if (s4->unk34 == 2) {
            if (s4->unk26 != 0) {
                s4->unk4 = raceGetHandicapSpeedBonus(s4) * 2;
                if (s4->unk4 > 1.0) {
                    s4->unk25 = 0x14;
                }
                s4->unk26 = 0;
            }
            if (s4->unk25 != 0) {
                s4->unk25 -= 1;
            }
        }
        func_8068F72C(s4, nextState, 1, 1);
        if (func_807142D8() == 0) {
            renderCallbacksRegister(raceRacerRenderCallback, gCurrentActor, 3);
        }
    } else if (v34 == 5 && s4->unk35 == 0) {
        RC_A->unk60 &= ~4;
        RC_A->unkB8 = 0.0f;
        slotQueueCancel(0xB, 0);
        s4->unk35 += 1;
        for (i = 0; i < 2; i++) {
            if (RC_A->unk6E[i] != -1) {
                sfxStopSlotSound(gCurrentActor, i);
            }
        }
    }
    actorInterpolateAngles(subFlag, s4, nextState);
    actorUpdateModelMatrix(gCurrentActor, 0);
}
extern s16 D_80750AC8;
extern u8 D_8002FC20[];
extern u8 D_8002FC50[];
extern f32 D_8002FC30;

void actorScriptStart(void *, s32);

extern f32 D_8002FC28;
extern f32 D_8002FC58;
s16 mathAngleSignedDistance(s16, s16);
s16 mathAngleEaseToward(s16, s16, f32);
s16 mathAngleDiscrete(f32, f32, f32, f32, f32);
extern f32 sqrtf(f32);

typedef struct {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x20];
    void *unk30;
    u8 unk34;
    u8 unk35;
} RaceRacerState;

typedef struct {
    RaceC_Actor *unk0;
    void *unk4;
    u8 pad8[7];
    u8 unkF;
    u8 unk10;
} RaceTargetView;


#define G2_F(o) (*(f32 *)((u8 *)gCurrentActor + (o)))

f32 raceRacerSteerTowardWaypoint(void) {
    s32 idx;
    RaceRacerState *s0;
    RaceTargetView *targetView;
    RaceC_Actor *tmp;
    RaceC_State *managerState;
    void *route;
    s32 pad_g64;
    s32 pad_g60;
    f32 leadDistance;
    f32 targetSpeed;
    f32 dx;
    f32 dz;
    f32 distToWaypoint;
    s32 pad_g48;
    u8 subFlag;
    u8 prevTargetState;
    u8 prevSubPhase;
    f32 lo;
    f32 thr;
    f32 fr;
    s16 ang;

    s0 = (RaceRacerState *)RC_A->unk178;
    targetView = (RaceTargetView *)RC_A->unk180;
    tmp = s0->unk30;
    managerState = tmp->unk174;
    route = raceGetRoute(managerState->unk26);
    leadDistance = raceGetPathDistanceBetweenTrackers(route, s0, targetView->unk4);
    targetSpeed = 0.0f;
    subFlag = RC_A->unk6A & 1;
    prevSubPhase = s0->unk35;
    idx = gBehaviourAnimState->path[gBehaviourWorkState->unk25][0];
    dx = (f32)D_807FDCA0->entries[idx].x - RC_A->unk7C;
    dz = (f32)D_807FDCA0->entries[idx].z - RC_A->unk84;
    distToWaypoint = sqrtf(dx * dx + dz * dz);
    if (distToWaypoint < (f32)D_807FDCA0->entries[idx].radius) {
        gBehaviourWorkState->unk25 += 1;
        gBehaviourWorkState->unk25 = gBehaviourWorkState->unk25 % gBehaviourExtraState->pathCount;
        targetView->unk10 = (D_807FDCA0->entries[idx].height == 0) && (targetView->unkF != 0);
        switch (D_807FDCA0->entries[idx].height) {
            case 2:
                if (leadDistance < 0.0f) {
                    actorScriptStart(gCurrentActor, 0x29E);
                    if (targetView->unkF >= 2) {
                        raceSetPiecewiseCurveMode(targetView, 1, D_8002FC20, D_8002FC50);
                    }
                    s0->unk35 = 1;
                }
                break;
            case 3:
                actorScriptStart(gCurrentActor, 0x2A1);
                break;
        }
    }
    ang = mathAngleDiscrete((f32)D_807FDCA0->entries[idx].x, (f32)D_807FDCA0->entries[idx].z, RC_A->unk7C, RC_A->unk84, distToWaypoint);
    ang = mathAngleSignedDistance(ang, s0->unk0);
    thr = D_807FDCA0->entries[idx].radius * 1.2;
    if (distToWaypoint < thr) {
        lo = distToWaypoint - (f32)D_807FDCA0->entries[idx].radius;
        dz = thr - (f32)D_807FDCA0->entries[idx].radius;
        fr = lo / dz;
        ang = ang * (1.0 + (1.0f - fr) * 1.5 * (2.0f * s0->unk4));
    }
    s0->unkC = s0->unkC + (ang * 0.0033333334f - s0->unkC) * 0.5f;
    if (s0->unk34 < 2 || s0->unk34 >= 5) {
        return leadDistance;
    }
    if (targetView->unkF != 0 && raceGetProgressPercent(route, s0, managerState) > 0.75) {
        raceSetPiecewiseCurveMode(targetView, 0, D_8002FC20, D_8002FC50);
    }
    switch (targetView->unkF) {
        case 0:
        case 1:
            switch (s0->unk35) {
                case 0:
                    if (RC_A->unk4->animId == 0x29E && targetView->unk10 != 0 && D_8002FC28 < leadDistance && leadDistance < D_8002FC30 && (randomLcgNext() & 0xFF) < 0xFU) {
                        actorScriptStart(gCurrentActor, 0x29F);
                    }
                    break;
                case 1:
                    targetSpeed = D_8002FC58;
                    G2_F(0xC4) = -50.0f;
                    break;
                case 2:
                    G2_F(0xC0) = 500.0f;
                    s0->unk35 += 1;
                    break;
                case 4:
                    if (subFlag) {
                        actorScriptStart(gCurrentActor, 0x2A2);
                        s0->unk35 += 1;
                        G2_F(0xC4) = -30.0f;
                    }
                    break;
                case 5:
                    if (RC_A->unk80 <= G2_F(0xAC)) {
                        actorScriptStart(gCurrentActor, 0x29D);
                        s0->unk35 = 0;
                        targetView->unk10 = targetView->unkF != 0;
                    }
                    break;
            }
            break;
        case 4:
            ang = 0;
            switch (s0->unk35) {
                case 1:
                    s0->unk35 += 1;
                    break;
                case 2:
                    ang = mathAngleBetweenPoints2D(RC_A->unk7C, RC_A->unk84, targetView->unk0->unk7C, targetView->unk0->unk84) - s0->unk0;
                    ang = ang & 0xFFF;
                    break;
                case 4:
                    raceSetPiecewiseCurveMode(targetView, 5, D_8002FC20, D_8002FC50);
                    s0->unk2 = 0;
                    break;
            }
            s0->unk2 = mathAngleEaseToward(s0->unk2, ang, 5.0f);
            break;
    }
    if (targetSpeed == 0.0f) {
        prevTargetState = targetView->unkF;
        targetSpeed = raceEvaluateCurveWithRubberband(targetView, leadDistance, D_8002FC20, D_8002FC50);
        if (prevTargetState == 2 && targetView->unkF == 3) {
            actorScriptStart(gCurrentActor, 0x2A0);
        }
        if (prevTargetState == 3 && targetView->unkF == 4) {
            s0->unk35 = prevSubPhase;
        }
    }
    if (subFlag != 0) {
        targetSpeed = targetSpeed * 0.9;
        s0->unk8 = 0.1f;
        if (RC_A->unkB8 < 350.0f) {
            RC_A->unkB8 = RC_A->unkB8;
        } else {
            RC_A->unkB8 = 350.0f;
        }
    } else {
        s0->unk8 = 0.0f;
    }
    s0->unk4 = targetSpeed;
    return leadDistance;
}




typedef struct {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x24 - 8];
    f32 unk24;
} RaceC_Inner;

typedef struct RaceC_Holder {
    u8 pad0[4];
    RaceC_Inner **unk4;
} RaceC_Holder;

void scriptSetActorRampTarget(void *, f32, f32);

void raceAdjustRubberbandTargetSpeed(RaceC_Holder *actorHolder, void *racerState, f32 relSpeed, f32 leadDelta, f32 targetDist) {
    RaceC_Inner *v;
    f32 a;
    f32 b;
    f64 d;
    f32 c;

    v = *actorHolder->unk4;
    c = v->unk4;
    if (relSpeed != 0) {
        b = (s32)(leadDelta / relSpeed);
        if (!(b <= 0)) {
            a = (targetDist - c) / b;
            if (a < 0.0f) {
                a = 0.01f;
            }
            d = v->unk24 < 0.01 ? 0.01 : v->unk24;
            a = (f64)a / d;
            if (a > 2.0f) {
                a = 2.0f;
            }
            scriptSetActorRampTarget(actorHolder, a, 0.0f);
        }
    }
}

s32 raceGetFinishCutsceneCam(s32 state, s32 index) {
    return D_8002FC5C[raceCheckLapCompletionThreshold(state, index, 10)];
}

void behaviourFrameBegin(void);
void camRequestPathLength(void);
u16 camStartPath(void *, s16, u8);
void camResumePath(void);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
void csModelStateSetFirstByte(s16, s16);
u8 func_8072881C(u8, u32 *);
void hudSpawnTextScreen(u8);
s32 playerStateQueueCallback(s16, void *, u8);

void raceOpponentRacerBehaviorUpdate(void) {
    RaceC_State *s0;
    void *racerData;
    RaceC_Target *targetView;
    f32 leadDistance;
    f64 dv;
    RaceC_State *managerState;
    RaceC_Actor *tmp;
    s32 finishPlacement;
    u8 idx;
    s32 raceResult;
    s32 v;
    f32 fv1;

    s0 = RC_A->unk178;
    racerData = RC_A->unk17C;
    targetView = RC_A->unk180;
    leadDistance = 0.0f;
    behaviourFrameBegin();
    if (!(RC_A->unk60 & 0x10)) {
        tmp = s0->unk30;
        managerState = tmp->unk174;
        s0->unk10 = 1.0f;
        RC_A->unk60 &= 0xFFFDFFFE;
        RC_A->unk12A = 0x5DC;
        raceSetPiecewiseCurveMode(targetView, 5, D_8002FC20, D_8002FC50);
        s0->unk34 = 0;
        camRequestPathLength();
        v = camStartPath(gCurrentActor, 1, 1) - 0x3C;
        managerState->unk1C = v;
        targetView->unkA = v;
        s0->unk4 = 1.0f;
        gBehaviourWorkState->unk25 = gBehaviourExtraState->pathCount - 5;
        idx = gBehaviourAnimState->path[gBehaviourWorkState->unk25][0];
        RC_A->unk7C = D_807FDCA0->entries[idx].x;
        RC_A->unk80 = D_807FDCA0->entries[idx].y;
        RC_A->unk84 = D_807FDCA0->entries[idx].z;
        D_80750AC8 = 0xA;
    }
    if (targetView->unkA != 0) {
        targetView->unkA -= 1;
    }
    if (s0->unk34 < 5) {
        leadDistance = raceRacerSteerTowardWaypoint();
        if (s0->unk34 == 2) {
            raceHandleRacerCollision(targetView);
        } else if (s0->unk34 == 4 && targetView->unk8 == 0) {
            targetView->unk8 = 1;
            if (flagGet(0xA5, 0) == 0) {
                camStartPath(targetView->unk0, 0, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
        }
        func_8068F72C(s0, racerData, 0, 0);
    } else if (s0->unk34 == 5) {
        switch (s0->unk35) {
        case 0:
            if (flagGet(0xA5, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                RC_A->unkE4 = 0;
                RC_A->unkE8 = 0;
                actorScriptStart(gCurrentActor, 0x29A);
            }
            s0->unk35 += 1;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                finishPlacement = targetView->unk4;
                currentActorClearFlag();
                resQueueAttachActor(gCurrentActor, 0x12, raceGetFinishCutsceneCam((s32)s0, finishPlacement) & 0xFF);
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
                raceResult = targetView->unk4;
                raceResult = raceGetFinishCutsceneCam((s32)s0, raceResult);
                currentActorClearFlag();
                if (raceResult == 0) {
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
                mapCheckAutoTransition();
                s0->unk35 += 1;
            }
            break;
        }
    }
    switch (RC_A->unk4->animId) {
    case 0x29E:
    case 0x2A2:
        fv1 = RC_A->unkB8 * 0.0025f;
        fv1 = fv1 < 0.1 ? 0.1 : fv1;
        scriptSetActorRampTarget(gCurrentActor, fv1, 10.0f);
        break;
    case 0x2A0:
        if (RC_A->unk4->model->animId == 0x4A7) {
            raceAdjustRubberbandTargetSpeed(gCurrentActor, s0, RC_A->unkB8 - targetView->unk0->unkB8, (leadDistance - D_8002FC30) * 40.0f, 23.0f);
            break;
        }
    default:
        if (RC_A->unk4->model->animId != 0x49B) {
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 10.0f);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    func_8072881C(0, &gBehaviourWorkState->unk28);
}

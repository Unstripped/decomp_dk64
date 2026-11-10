#include "common.h"
#include "actor.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/FCCD0.h"
#include "proto/race/0.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"
s16 sfxPlayFromActorWithAltitudeCheck(struct Actor *, s16, u8, s16, u8);

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6;
    u8 radius;
    u8 targetSpeed;
    u8 pad9;
} RaceC_Entry;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0x14 - 0x12];
    RaceC_Entry *unk14;
} RaceC_DCA0;


typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    u8 unk8;
    u8 pad9[3];
} RaceC_Row;

typedef struct {
    u8 pad0[0x6A];
    u16 unk6A;
    u8 pad6C[0x7C - 0x6C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xC0 - 0xBC];
    f32 unkC0;
    f32 unkC4;
    u8 padC8[0xDC - 0xC8];
    s16 unkDC;
    u8 padDE[0xE0 - 0xDE];
    f32 unkE0;
    u8 padE4[0xEE - 0xE4];
    s16 unkEE;
    u8 padF0[0x154 - 0xF0];
    u8 unk154;
} RaceC_Act;

extern s32 gCurrentMap;
extern void *gCurrentActor;
extern void *gActivePlayerActor;
extern RaceC_DCA0 *D_807FDCA0;
extern RaceC_Row D_8002FB10[];
extern RaceC_Row D_8002FB70[];
#define RC_A ((RaceC_Act *)gCurrentActor)
#define RC_B ((RaceC_Act *)gActivePlayerActor)
f32 mathCosF(s16);
f32 mathSinF(s16);
void actorScriptStart(void *, s32);

void raceOpponentFollowWaypoints(void) {
    f32 speedDelta;
    f32 turnDelta;
    f32 fs0;
    f32 fs1;
    f32 curSpeed;
    f32 oscSpeed;
    RaceC_Entry *a0;
    f32 fv0;
    u8 routeRowIdx;
    RaceC_Row *routeRows;
    f32 q;
    BehaviourWorkState **pp;
    s16 v1;

    pp = &gBehaviourWorkState;
    routeRowIdx = gBehaviourWorkState->unk24;
    if (gCurrentMap == 0x52) {
        routeRows = D_8002FB10;
    } else {
        routeRows = D_8002FB70;
    }
    curSpeed = RC_A->unkB8;
    oscSpeed = mathSinF((s16)(s32)(RC_A->unkE0 * 11.4)) * 20.0f;
    a0 = &D_807FDCA0->unk14[gBehaviourWorkState->unk25];
    fs0 = RC_A->unk7C - a0->x;
    fs1 = RC_A->unk84 - a0->z;
    if (sqrtf(fs1 * fs1 + fs0 * fs0) < (a0 = &D_807FDCA0->unk14[gBehaviourWorkState->unk25])->radius) {
        if ((a0->y < RC_A->unk80 ? RC_A->unk80 - a0->y : -(RC_A->unk80 - a0->y)) < 80.0f && gBehaviourWorkState->unk25 < D_807FDCA0->unk10 - 1) {
            RaceC_Row *row = (RaceC_Row *)((u8 *)routeRows + routeRowIdx * 12);
            if (row->unk0 == gBehaviourWorkState->unk25) {
                if (row) {}  // FAKE: dead test steers uopt FP callee-saved colouring (fs0/fs1)
                RC_A->unkC4 = row->unk4;
                if (row->unk8 == 1) {
                    actorScriptStart(gCurrentActor, 0x286);
                    RC_A->unkC0 = 200.0f;
                    RC_A->unk154 += 1;
                }
                gBehaviourWorkState->unk24 += 1;
            }
            gBehaviourWorkState->unk25++;
            a0 = &D_807FDCA0->unk14[(*pp)->unk25];
        }
        a0 = &D_807FDCA0->unk14[gBehaviourWorkState->unk25];
    }
    speedDelta = (f64)(a0->targetSpeed - RC_A->unkB8 / 10.0f) * 0.8;
    fv0 = (f64)(RC_A->unk80 - RC_B->unk80) * 0.25;
    if (fv0 > 6.0f) {
        fv0 = 6.0f;
    }
    if (fv0 < -6.0f) {
        fv0 = -6.0f;
    }
    speedDelta = speedDelta + fv0;
    v1 = (s32)((f64)mathAtan2(-fs0, -fs1) * 4096.0 / 6.2831854820251465);
    v1 = v1 - RC_A->unkEE;
    if (v1 >= 0x800) {
        v1 = (f64)v1 - 4096.0;
    }
    if (v1 < -0x800) {
        v1 = (f64)v1 + 4096.0;
    }
    turnDelta = (f64)(RC_A->unkB8 * v1) / 10000.0;
    fs0 = mathSinF(RC_A->unkEE) * curSpeed;
    fs1 = mathCosF(RC_A->unkEE) * curSpeed;
    if (RC_A->unk6A & 1) {
        fs0 += mathSinF(RC_A->unkDC) * oscSpeed;
        fs1 += mathCosF(RC_A->unkDC) * oscSpeed;
    }
    fs0 += mathSinF(RC_A->unkEE) * speedDelta;
    fs1 += mathCosF(RC_A->unkEE) * speedDelta;
    fs0 += mathCosF(RC_A->unkEE) * turnDelta;
    fs1 -= mathSinF(RC_A->unkEE) * turnDelta;
    curSpeed = sqrtf(fs0 * fs0 + fs1 * fs1);
    fv0 = mathAtan2(fs0, fs1);
    if (RC_A->unkC4 != -20.0f && RC_A->unkC4 != -360.0f) {
        RC_A->unkB8 = D_807FDCA0->unk14[gBehaviourWorkState->unk25].targetSpeed * 10.0;
    } else {
        RC_A->unkB8 = curSpeed;
    }
    RC_A->unkEE = (f64)fv0 * 4096.0 / 6.2831854820251465;
    if (RC_A->unk6A & 1) {
        fv0 = RC_A->unkB8;
        q = (f32)((f64)(fv0 * fv0) / 15000.0);
        RC_A->unkB8 = fv0 - q;
        fv0 = q;
        fv0 = q;
        if (RC_A->unkB8 < 0.0f) {
            RC_A->unkB8 = 0.0f;
        }
    }
}

typedef struct RaceC_Arg1 {
    u8 pad0[0x1A];
    s16 rewardFlag;
    s32 requiredCoins;
} RaceC_Arg1;

typedef struct RaceC_Arg0 {
    u8 pad0[0x36];
    u8 active;
} RaceC_Arg0;

extern u16 D_80750AC4;

int raceCheckCoinRequirement(RaceC_Arg0 *controller, RaceC_Arg1 *config) {
    return controller->active != 0 && flagGet(config->rewardFlag, 0) == 0 && D_80750AC4 >= config->requiredCoins;
}

typedef struct {
    u8 pad0[0x1C];
    u16 unk1C;
} LargeR4_Child;

typedef struct {
    u8 pad0[0x30];
    struct LargeR4_Kid *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 pad37[0xD0 - 0x37];
    s16 unkD0;
} LargeR4_Ctl;

struct LargeR4_Kid {
    u8 pad0[0x174];
    LargeR4_Child *unk174;
};

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x18 - 0x8];
    union {
        s32 w;
        struct {
            s16 hi;
            s16 lo;
        } h;
    } unk18;
    s32 unk1C;
} LargeR4_Cfg;

typedef struct {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[4];
    u16 unk68;
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x7C - 0x6E];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xDC - 0xCC];
    s16 unkDC;
    u8 padDE[0xE6 - 0xDE];
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0xEE - 0xEA];
    s16 unkEE;
    u8 padF0[0xFC - 0xF0];
    u8 unkFC;
    u8 padFD[0x12A - 0xFD];
    s16 unk12A;
    u8 pad12C[0x132 - 0x12C];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
    u8 pad160[0x178 - 0x160];
    LargeR4_Ctl *unk178;
    LargeR4_Cfg *unk17C;
} LargeR4_Act;


typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6;
    u8 unk7;
    u8 unk8;
    u8 pad9;
} LargeR4_Entry;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[2];
    LargeR4_Entry *unk14;
} LargeR4_Path;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    u8 unk8;
    u8 pad9[3];
} LargeR4_Row;

extern LargeR4_Act *gPrimaryPlayerActor;
extern u8 gBossFightPhase;
extern u16 D_80750AC8;
extern s32 D_8002FB94[];

#define L4_D ((LargeR4_Act *)gCurrentActor)
#define L4_P ((LargeR4_Path *)D_807FDCA0)

void actorApplyGravity(void);
void actorApplyVelocity(void *);
void actorApproachTargetSpeed(u16);
void actorSetTargetSpeed(void *, s32);
void actorStepPhysics(void *, s16, s16);
void behaviourFrameBegin(void *);
void camResumePath(void);
u16 camStartPath(void *, s16, u8);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
void csModelStateSetFirstByte(s16, s16);
f32 sqrtf(f32);
void actorUpdateFloorContactAndTilt(void *, f32);
void billboardSubmit(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 playerIsDamageOrKnockbackState(void);
void hudSpawnTextScreen(u8);
s32 mathAngleStepToward(s16 *, s16, s32);  // FAKE: callee prototype steer
s32 playerStateQueueCallback(s16, void *, u8);
s32 sfxStopSlotSound(void *, s32);

void raceOpponentBehaviourUpdate(void) {
    f32 dx;
    f32 dz;
    s16 ang16;
    s32 tmp;
    LargeR4_Entry *e;
    u8 rowIdx;
    LargeR4_Ctl *controller;
    LargeR4_Cfg *config;
    struct LargeR4_Kid *kid;
    LargeR4_Child *child;
    LargeR4_Row *routeRows;
    s32 flag;
    f32 fv1;
    s32 sel;
    u32 x;
    s32 y;
    f32 dist;
    u16 angU; // FAKE: u16 raw copy of the angle (ring temp, no sll/sra); steers t-register allocation

    controller = L4_D->unk178;
    config = L4_D->unk17C;
    kid = controller->unk30;
    child = NULL;
    if (gCurrentMap == 0x52) {
        routeRows = (LargeR4_Row *)D_8002FB10;
    } else {
        routeRows = (LargeR4_Row *)D_8002FB70;
    }
    if (kid != NULL) {
        child = kid->unk174;
    }
    behaviourFrameBegin(kid);
    if (!(L4_D->unk60 & 0x10)) {
        L4_D->unk144 = 0x1C;
        L4_D->unk60 |= 0x10400;
        L4_D->unk60 &= 0xFFFDFFFF;
        L4_D->unk154 = 0;
        L4_D->unk155 = 0;
        L4_D->unkB8 = 0.0f;
        L4_D->unkC4 = -20.0f;
        L4_D->unkC8 = -900.0f;
        L4_D->unk12A = 0x7D0;
        gBehaviourWorkState->unk35 = 0;
        gBehaviourWorkState->timer = 0x64;
        gBehaviourWorkState->timer = 0;
        gBehaviourWorkState->unk24 = 0;
        L4_D->unk68 &= 0xFFBF;
        if (gCurrentMap == 0x52) {
            config->unk1C = D_80750AC8 = 0x32;
            config->unk18.w = 0x103;
            flag = 0x65;
        } else {
            config->unk1C = D_80750AC8 = 0x32;
            config->unk18.w = 0x4B;
            flag = 0x66;
        }
        if (flagGet(flag, 2) == 0 && flagGet(config->unk18.h.lo, 0) == 0) {
            camStartPath(gCurrentActor, 0, 1);
            currentActorClearFlag();
            flagSet(flag, 1, 2);
        } else {
            controller->unk35 = 3;
        }
    }
    rowIdx = gBehaviourWorkState->unk24;
    if (child != NULL && controller->unk34 < 3 && gBossFightPhase == 4) {
        playerStateQueueCallback(0x33, gCurrentActor, 0);
    }
    if (controller->unk34 < 3 && L4_D->unk154 == 2 && gBossFightPhase == 5) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CA, 0xFF, 0x7F, 0xA);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x209, 0xFF, 0x7F, 0xA);
        L4_D->unkB8 = 0.0f;
        L4_D->unk154 = 0x14;
        L4_D->unkC4 = -40.0f;
        L4_D->unkC0 = 400.0f;
    }
    if (playerIsDamageOrKnockbackState() != 0) {
        L4_D->unk132 = 1;
    } else {
        L4_D->unk132 = 2;
    }
    switch (L4_D->unk154) {
    case 20:
        L4_D->unkE8 = (L4_D->unkE8 - 0xC8) & 0xFFF;
        if ((L4_D->unk6A & 1) && L4_D->unkC0 <= 0.0f) {
            L4_D->unk154 = 2;
            L4_D->unkE8 = 0;
        }
        break;
    case 0:
        if (child != NULL && child->unk1C == 0) {
            L4_D->unk154 = L4_D->unk154 + 1;
            L4_D->unk155 = 0;
            L4_D->unk6A |= 0x200;
        }
        break;
    case 1:
        if (controller->unk34 == 2) {
            if (gCurrentMap == 0x52) {
                actorSetTargetSpeed(gCurrentActor, 0x10E);
            } else {
                actorSetTargetSpeed(gCurrentActor, 0xAA);
            }
            gBehaviourWorkState->unk35 = 0xA;
            actorScriptStart(gCurrentActor, 0x282);
            L4_D->unk154 = L4_D->unk154 + 1;
            break;
        }
    case 2:
        actorApproachTargetSpeed(0);
        dx = L4_D->unk7C - (f32)L4_P->unk14[gBehaviourWorkState->unk25].unk0;
        dz = L4_D->unk84 - (f32)L4_P->unk14[gBehaviourWorkState->unk25].unk4;
        dist = sqrtf(dz * dz + dx * dx);
        if (dist < (f32)L4_P->unk14[gBehaviourWorkState->unk25].unk7) {
            fv1 = L4_D->unk80;
            if ((f32)L4_P->unk14[gBehaviourWorkState->unk25].unk2 < fv1) {
                dist = fv1 - (f32)L4_P->unk14[gBehaviourWorkState->unk25].unk2;
            } else {
                dist = -(fv1 - (f32)L4_P->unk14[gBehaviourWorkState->unk25].unk2);
            }
            if (dist < 80.0f) {
                if (gBehaviourWorkState->unk25 < L4_P->unk10 - 1) {
                    if (L4_P->unk14[gBehaviourWorkState->unk25].unk8 == 0) {
                        actorScriptStart(gCurrentActor, 0x283);
                        L4_D->unk154 = L4_D->unk154 + 1;
                    }
                    if (gBehaviourWorkState->unk25 == routeRows[rowIdx].unk0) {
                        L4_D->unkC4 = routeRows[rowIdx].unk4;
                        gBehaviourWorkState->unk24 = gBehaviourWorkState->unk24 + 1;
                    }
                    gBehaviourWorkState->unk25++;
                }
            }
        }
        ang16 = angU = (s32)((f64)mathAtan2(-dx, -dz) * 4096.0 / 6.2831854820251465);
        mathAngleStepToward(&L4_D->unkE6, (angU + angU - L4_D->unkEE) & 0xFFF, 0x32);
        mathAngleStepToward(&L4_D->unkEE, ang16, 0xF);
        if (gBehaviourWorkState == 0) {} // FAKE: dead pointer test, steers t-register allocation
        if (gBehaviourWorkState->unk25 == routeRows[gBehaviourWorkState->unk24].unk0 && routeRows[gBehaviourWorkState->unk24].unk8 == 2 && controller->unk34 == 3) {
            if (controller->unk36 == 1) {
                L4_D->unk154 = 0xA;
            } else {
                L4_D->unk154 = 9;
            }
            actorScriptStart(gCurrentActor, 0);
            L4_D->unk155 = 0;
        }
        break;
    case 3:
        actorApproachTargetSpeed(0x200);
        break;
    case 4:
        actorApproachTargetSpeed(0x200);
        L4_D->unkC0 = 200.0f;
        L4_D->unk154 = L4_D->unk154 + 1;
        break;
    case 5:
        actorApproachTargetSpeed(0x200);
        break;
    case 6:
        if (gBehaviourWorkState->unk2E != 0) {
            gBehaviourWorkState->unk2E = gBehaviourWorkState->unk2E - 1;
        } else if (L4_D->unkFC != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, 0x46, 0x7F, 2);
            gBehaviourWorkState->unk2E = 0x14;
        }
        if (gBehaviourWorkState->unk25 == routeRows[gBehaviourWorkState->unk24].unk0 && routeRows[gBehaviourWorkState->unk24].unk8 == 1) {
            fv1 = (f32)(L4_D->unkEE - L4_D->unkE6);
            if (fv1 > 2048.0f) {
                fv1 -= 4096.0f;
            }
            if (fv1 < -2048.0f) {
                fv1 += 4096.0f;
            }
            if (fv1 > 50.0f) {
                fv1 = 50.0f;
            }
            if (fv1 < -50.0f) {
                fv1 = -50.0f;
            }
            gBehaviourWorkState->timer = (s32)((f32)gBehaviourWorkState->timer + fv1);
            gBehaviourWorkState->timer = (s32)((f64)gBehaviourWorkState->timer - (f64)gBehaviourWorkState->timer * 0.3);
        } else {
            if ((L4_D->unk6A & 1) && !(L4_D->unk6C & 1)) {
                actorScriptStart(gCurrentActor, 0x285);
                L4_D->unkC4 = -20.0f;
            }
            fv1 = (f32)(L4_D->unkEE - L4_D->unkDC);
            if (fv1 > 2048.0f) {
                fv1 -= 4096.0f;
            }
            if (fv1 < -2048.0f) {
                fv1 += 4096.0f;
            }
            gBehaviourWorkState->timer = (s32)((f64)gBehaviourWorkState->timer + (f64)(fv1 * L4_D->unkB8) / 8000.0);
            if (gBehaviourWorkState->timer > 500) {
                gBehaviourWorkState->timer = 500;
            }
            if (gBehaviourWorkState->timer < -500) {
                gBehaviourWorkState->timer = -500;
            }
        }
        L4_D->unkE6 = (L4_D->unkE6 + gBehaviourWorkState->timer) & 0xFFF;
        raceOpponentFollowWaypoints();
        break;
    case 7:
        if (gCurrentMap == 0xE) {
            actorSetTargetSpeed(gCurrentActor, 0xB4);
        }
        raceOpponentFollowWaypoints();
        break;
    case 8:
        L4_D->unk154 = 2;
        L4_D->unkE6 = L4_D->unkEE;
        break;
    case 9:
        gBehaviourWorkState->unk35 = 8;
        actorSetTargetSpeed(gCurrentActor, 0);
        actorApproachTargetSpeed(0x200);
        if (L4_D->unk155 == 0) {
            actorScriptStart(gCurrentActor, 0x287);
            L4_D->unk155 = L4_D->unk155 + 1;
        }
        break;
    case 10:
        x = L4_D->unk155;
        switch (x) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            gBehaviourWorkState->unk35 = 8;
            L4_D->unk155 = 1;
            break;
        case 1:
            if (L4_D->unkB8 == 0.0f) {
                L4_D->unk155 = L4_D->unk155 + 1;
            }
            break;
        case 2:
            gBehaviourWorkState->unk35 = 0;
            actorScriptStart(gCurrentActor, 0x288);
            L4_D->unk155 = L4_D->unk155 + 1;
            break;
        }
        actorApproachTargetSpeed(0x200);
        break;
    }
    switch (controller->unk34) {
    case 0:
        y = controller->unk35;
        if (y) {} // FAKE: dead test, steers y/sel copy order
        sel = controller->unk35;
        if (sel) {} // FAKE: dead test, steers y/sel copy order
        switch (sel) {
        case 0:
            if (L4_D->unk60 & 0x02000000) {
                controller->unk35 = controller->unk35 + 1;
                y = controller->unk35;
            }
            break;
        case 1:
            if (!(L4_D->unk60 & 0x02000000)) {
                camResumePath();
                controller->unk35 = controller->unk35 + 1;
                y = controller->unk35;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                controller->unk35 = controller->unk35 + 1;
            }
            y = controller->unk35;
            break;
        }
        if (y < 3) {
            raceSetIntroCutscenePhase(kid);
        }
        break;

    case 1:
        if (controller->unk35 == 0) {
            slotQueueUpdate(0xB, 1, 0);
            controller->unk35 = controller->unk35 + 1;
        }
        break;
    case 3:
        if (controller->unk35 == 0) {
            flag = 0x55;
            if (gPrimaryPlayerActor->unk6A & 0x200) {
                flag = 0x56;
            }
            playerStateQueueCallback(flag, NULL, 0);
            controller->unk35 = controller->unk35 + 1;
        }
        break;
    case 4:
        if (controller->unk35 == 0) {
            slotQueueCancel(0xB, 0);
            controller->unkD0 = 0;
            if (flagGet(config->unk18.h.lo, 0) == 0) {
                tmp = D_8002FB94[raceCheckLapCompletionThreshold(controller, config->unk4, config->unk1C)];
                camStartPath(gCurrentActor, tmp, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
            controller->unk35 = controller->unk35 + 1;
        }
        break;
    case 5:
        tmp = controller->unk35;
        switch (tmp) {
        case 0:
            if (flagGet(config->unk18.h.lo, 0) == 0) {
                sfxStopSlotSound(gActivePlayerActor, 0);
                playerStateQueueCallback(0x55, NULL, 0);
                L4_D->unkB8 = 0.0f;
                if (raceCheckCoinRequirement((void *)controller, (void *)config) != 0) {
                    L4_D->unk154 = 0xA;
                    L4_D->unk155 = 0;
                } else {
                    L4_D->unk154 = 9;
                    L4_D->unk155 = 0;
                }
            }
            controller->unk35 = controller->unk35 + 1;
            break;
        case 1:
            if (L4_D->unk60 & 0x02000000) {
                controller->unk35 = tmp + 1;
            }
            break;
        case 2:
            if (!(L4_D->unk60 & 0x02000000)) {
                camResumePath();
                if (raceCheckCoinRequirement((void *)controller, (void *)config) == 0) {
                    controller->unk35 = 4;
                }
                controller->unk35 = controller->unk35 + 1;
                L4_D->unk15F = 0;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (gCurrentMap == 0xE) {
                    csModelStateSetFirstByte(0x48, 0xA);
                } else {
                    csModelStateSetFirstByte(1, 0xA);
                }
                controller->unk35 = controller->unk35 + 1;
            }
            break;
        case 4:
            if (flagGet(config->unk18.h.lo, 0) != 0) {
                controller->unk35 = controller->unk35 + 1;
            }
            break;
        case 5:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (flagGet(config->unk18.h.lo, 0) != 0) {
                    mapCheckAutoTransition();
                } else {
                    hudSpawnTextScreen(1);
                }
                controller->unk35 = controller->unk35 + 1;
            }
            break;
        }
        break;
    }
    actorApplyGravity();
    actorStepPhysics(gCurrentActor, L4_D->unkEE, L4_D->unkEE);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    if (controller->unk34 == 2) {
        raceUpdateLapAndWaypointTracker(controller);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/10E1D0.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/131B0.h"
#include "proto/global/133A90.h"
#include "proto/global/135D30.h"
#include "proto/global/13A7A0.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2DE90.h"
#include "proto/global/36880.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/5650.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;

void playerHolsterGun(Actor *actor, PlayerState *state, u8 isFirstPerson) {
    s32 id;

    id = 0x4A;
    if (isFirstPerson) {
        id = 0x4C;
    }
    state->isHoldingObject = 0;
    actorScriptStartByIndex(actor, id);
}

void playerDrawGun(Actor *actor, PlayerState *state, u8 isFirstPerson) {
    s32 id;
    s32 a;

    id = 0x4B;
    a = 2;
    if (slotQueueGetValue(3, state->playerIndex)) {
        a = 3;
    }
    slotQueueUpdate(a, 0, 0);
    if (isFirstPerson) {
        id = 0x4D;
    }
    actorScriptStartByIndex(actor, id);
}

void playerToggleGun(Actor *actor, PlayerState *state, u8 isFirstPerson) {
    if (state->gunDrawn) {
        playerHolsterGun(actor, state, isFirstPerson);
    } else {
        playerDrawGun(actor, state, isFirstPerson);
    }
}

void mathAngleStepToward(s16 *angle, s16 target, s16 rate) {
    s16 delta;
    s16 dist;
    s32 absStep;
    s16 step;

    target &= 0xFFF;
    delta = target - *angle;
    if (delta != 0) {
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        step = rate;
        delta = delta / dist;
        if (dist > 0x800) {
            dist = 0x1000 - dist;
            delta = delta * -1;
        }
        if (step > 0) {
            absStep = step;
        } else {
            absStep = -step;
        }
        if (dist < absStep) {
            *angle = target;
            return;
        }
        *angle = *angle + (delta * step);
        *angle &= 0xFFF;
    }
}

void mathAngleStepTowardThreshold(s16 *angle, s16 target, s16 step, s16 threshold) {
    s16 delta;
    s16 dist;

    target = target & 0xFFF;
    delta = target - *angle;
    if (delta != 0) {
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        delta = delta & 0xFFF;
        if (dist > 0x800) {
            dist = 0x1000 - dist;
        }
        if (step >= dist) {
            *angle = target;
        } else if (threshold < delta) {
            *angle = *angle - step;
        } else {
            *angle = *angle + step;
        }
        *angle &= 0xFFF;
    }
}

void mathAngleStepForward(s16 *angle, s16 target, s16 step) {
    s16 delta;

    delta = target - *angle;
    if (delta != 0) {
        if (((s16) (delta & 0xFFF) + step) >= 0x1000) {
            *angle = target;
            return;
        }
        *angle = (*angle + step) & 0xFFF;
    }
}

typedef struct PadInputState {
    /* 0x00 */ s32 stickHeldFrames;
    /* 0x04 */ f32 stickMag;
    /* 0x08 */ f32 stickMagNorm;
    /* 0x0C */ f32 stickMagDelta;
    /* 0x10 */ f32 stickMagHistory[4];
    /* 0x20 */ s16 stickAngleHistory[4];
    /* 0x28 */ s16 stickAngle;
    /* 0x2A */ u16 heldButtons;
    /* 0x2C */ u16 pressedButtons;
    /* 0x2E */ s8 stickX;
    /* 0x2F */ s8 stickY;
    /* 0x30 */ u8 stickAbsX;
    /* 0x31 */ u8 stickAbsY;
    /* 0x32 */ u8 pad32[2];
} PadInputState; // size = 0x34

extern PadInputState gPlayerPadState[];

f32 sqrtf(f32);

typedef struct PadRawInput {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ s8 unk2;
    /* 0x3 */ s8 unk3;
} PadRawInput;

typedef struct PlayerButtonState {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u8 pad2[0x32];
} PlayerButtonState;

extern PlayerButtonState D_807FD63A[]; // gPlayerPadState[].heldButtons



typedef struct PlayerInputHandlers {
    void (*fn[17])(void);
} PlayerInputHandlers;

#define INPUT_MAX(a, b) ((a) > (b) ? (a) : (b))
#define INPUT_MIN(a, b) ((a) < (b) ? (a) : (b))


extern PlayerStruct *gPlayerSlots;
extern PadRawInput *D_807ECDEC;
extern u16 D_807ECDF0;
extern u16 D_80750FF0[];
extern PlayerInputHandlers gPlayerInputHandlers[];

s32 playerInputUpdate(s32 handlerSet) {
    f32 a;
    f32 b;
    f32 hi;
    f32 mag;
    s32 pad;
    s32 i;
    s32 old;
    s16 ang;

    old = gActivePlayerActor->state;
    D_807FD63A[gCurrentPlayerIndex].unk0 = inputRemapButtons(D_807ECDEC->unk0, D_80750FF0);
    gPlayerPadState[gCurrentPlayerIndex].pressedButtons = inputRemapButtons(D_807ECDF0, D_80750FF0);
    if (gActivePlayerState->stateFlags2 & 0x20) {
        gPlayerPadState[gCurrentPlayerIndex].heldButtons = 0;
        gPlayerPadState[gCurrentPlayerIndex].pressedButtons = 0;
    }
    D_807ECDEC->unk2 = INPUT_MIN(INPUT_MAX(D_807ECDEC->unk2, -80), 80);
    D_807ECDEC->unk3 = INPUT_MIN(INPUT_MAX(D_807ECDEC->unk3, -80), 80);
    gPlayerPadState[gCurrentPlayerIndex].stickX = D_807ECDEC->unk2;
    gPlayerPadState[gCurrentPlayerIndex].stickY = D_807ECDEC->unk3;
    if (gActivePlayerState->stateFlags2 & 0x20) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickY = 0;
    }
    if (gActivePlayerState->stateFlags & 0x100) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = gPlayerPadState[gCurrentPlayerIndex].stickX * 0.5;
        gPlayerPadState[gCurrentPlayerIndex].stickY = gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5;
    }
    if (gActivePlayerState->stateFlags & 0x80) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = -gPlayerPadState[gCurrentPlayerIndex].stickX;
        gPlayerPadState[gCurrentPlayerIndex].stickY = -gPlayerPadState[gCurrentPlayerIndex].stickY;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickX > 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = gPlayerPadState[gCurrentPlayerIndex].stickX;
    } else {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = -gPlayerPadState[gCurrentPlayerIndex].stickX;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickY > 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = gPlayerPadState[gCurrentPlayerIndex].stickY;
    } else {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = -gPlayerPadState[gCurrentPlayerIndex].stickY;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX < 5 && gPlayerPadState[gCurrentPlayerIndex].stickAbsY < 5) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickY = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = 0;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX < 2) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = 0;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsY < 2) {
        gPlayerPadState[gCurrentPlayerIndex].stickY = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = 0;
    }
    a = gPlayerPadState[gCurrentPlayerIndex].stickAbsX * gPlayerPadState[gCurrentPlayerIndex].stickAbsX;
    b = gPlayerPadState[gCurrentPlayerIndex].stickAbsY * gPlayerPadState[gCurrentPlayerIndex].stickAbsY;
    mag = sqrtf(a + b);
    if (b < a) {
        hi = a;
        a = b;
        b = hi;
    }
    if (b != 0.0f) {
        hi = 1.0 - (a / b) * 0.15;
        mag = mag * hi;
    }
    if (mag > 70.0f) {
        mag = 70.0f;
    }
    gPlayerPadState[gCurrentPlayerIndex].stickMagDelta = mag - gPlayerPadState[gCurrentPlayerIndex].stickMag;
    gPlayerPadState[gCurrentPlayerIndex].stickMag = mag;
    if (mag != 0.0f) {
        gPlayerPadState[gCurrentPlayerIndex].stickHeldFrames = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickMagNorm = (mag - 5.0f) / 65.0f;
    } else {
        gPlayerPadState[gCurrentPlayerIndex].stickMagNorm = 0.0f;
        gPlayerPadState[gCurrentPlayerIndex].stickHeldFrames = gPlayerPadState[gCurrentPlayerIndex].stickHeldFrames + 1;
    }
    if (mag != 0.0f) {
        ang = mathAtan2(gPlayerPadState[gCurrentPlayerIndex].stickX, -gPlayerPadState[gCurrentPlayerIndex].stickY) * 4096.0f / 6.2831855f;
        gPlayerPadState[gCurrentPlayerIndex].stickAngle = (gPlayerSlots[gCurrentPlayerIndex].unk2C8 + ang) & 0xFFF;
    } else {
        ang = gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[0];
    }
    for (i = 3; i != 0; i--) {
        gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[i] = gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[i - 1];
        gPlayerPadState[gCurrentPlayerIndex].stickMagHistory[i] = gPlayerPadState[gCurrentPlayerIndex].stickMagHistory[i - 1];
    }
    gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[0] = ang;
    gPlayerPadState[gCurrentPlayerIndex].stickMagHistory[0] = mag;
    gPlayerInputHandlers[handlerSet].fn[1]();
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 0x1000) {
        gPlayerInputHandlers[handlerSet].fn[0]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 0x8000) {
        gPlayerInputHandlers[handlerSet].fn[2]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[5]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 0x4000) {
        gPlayerInputHandlers[handlerSet].fn[3]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[6]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 0x2000) {
        gPlayerInputHandlers[handlerSet].fn[4]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[7]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 0x10) {
        gPlayerInputHandlers[handlerSet].fn[9]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[11]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 0x20) {
        gPlayerInputHandlers[handlerSet].fn[8]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 8) {
        gPlayerInputHandlers[handlerSet].fn[12]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 4) {
        gPlayerInputHandlers[handlerSet].fn[15]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 2) {
        gPlayerInputHandlers[handlerSet].fn[13]();
    }
    if (D_807FD63A[gCurrentPlayerIndex].unk0 & 1) {
        gPlayerInputHandlers[handlerSet].fn[14]();
    }
    if (gPlayerPadState) {} // FAKE: keeps &gPlayerPadState live to the tail (const-hoist register order)
    gPlayerInputHandlers[handlerSet].fn[16]();
    return gActivePlayerActor->state - old;
}

u16 inputRemapButtons(u16 buttons, u16 *map) {
    u32 mask;
    u16 seen;
    u16 mapped;
    u32 ghost0;
    u32 ghost1;

    mask = *map;
    seen = 0;
    mapped = 0;
    if (mask != 0) {
        ghost0 = mask; // FAKE: pre-loop def, holds a0 across the loop so buttons spills and the mask load takes t0
        do {
            ghost1 = seen; // FAKE: loop-head def, holds a3 against the mask load (steers its colour to t0)
            seen |= mask;
            if (ghost1) {} // FAKE: dead test keeping ghost1 a coloured web
            map++;
            if ((u32)mask & buttons) {} // FAKE: makes the and-result a uopt candidate
            if (ghost0) {} // FAKE: dead test keeping ghost0 a coloured web
            if ((u32)mask & buttons) {
                mapped |= map[0];
            }
            mask = map[1];
            map++;
        } while (mask != 0);
    }
    return mapped | (buttons & ~seen);
}


f32 mathScaleByAngleDeltaCos(f32 value, s16 from, s16 to) {
    return mathCosF(to - from) * value;
}


void playerProjectMoveSpeedOntoAngle(s16 angle) {
    f32 speed;

    speed = mathScaleByAngleDeltaCos(gActivePlayerState->maxSpeed, gActivePlayerState->targetYaw, angle);
    if (speed > 0.0f) {
        gActivePlayerState->maxSpeed = speed;
    } else {
        gActivePlayerState->maxSpeed = 0.0f;
    }
    gActivePlayerState->targetYaw = angle;
}

void playerClearMoveTarget(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->targetYaw = gCurrentActor->yaw;
}


void playerUpdateMoveTargetFromStick(void) {
    f32 prevSpeed;
    f32 speed;
    PadInputState *pad;

    speed = gActivePlayerState->targetSpeed;
    if (gActivePlayerState->unkC8 == 0) {
        speed = speed * 0.5;
    }
    if (gActivePlayerState->breathTimer != 0) {
        speed = speed * 0.5;
    }
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if ((pad->stickMag != 0.0f) && !(gActivePlayerState->stateFlags2 & 8)) {
        prevSpeed = gActivePlayerState->unk34;
        gActivePlayerState->maxSpeed = (pad->stickMagNorm * (speed - prevSpeed)) + prevSpeed;
        gActivePlayerState->targetYaw = gPlayerPadState[gCurrentPlayerIndex].stickAngle;
        return;
    }
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->targetYaw = gCurrentActor->yaw;
}


void playerInputUpdateStickFacingYaw(void) {
    f32 dist;
    f32 scale;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
    if ((f64)scale < 0.3) {
        scale = 0.3f;
    }
    delta = gCurrentActor->moveYaw - gActivePlayerState->targetYaw;
    if (delta > 0) {
        dist = (f32)delta;
    } else {
        dist = (f32)-delta;
    }
    if (dist > 2048.0f) {
        dist = 4096.0f - dist;
    }
    if (dist > 400.0f) {
        dist = 400.0f;
    }
    dist = dist * 0.2;
    mathAngleStepToward(&gCurrentActor->moveYaw, gActivePlayerState->targetYaw, (s16)(s32)(dist * scale));
}

void playerInputUpdateStickFacingYawSlow(void) {
    f32 dist;
    f32 scale;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
    if ((f64)scale < 0.3) {
        scale = 0.3f;
    }
    delta = gCurrentActor->moveYaw - gActivePlayerState->targetYaw;
    if (delta > 0) {
        dist = (f32)delta;
    } else {
        dist = (f32)-delta;
    }
    if (dist > 2048.0f) {
        dist = 4096.0f - dist;
    }
    if (dist > 400.0f) {
        dist = 400.0f;
    }
    dist = dist * ((f64)gActivePlayerState->turnRate / 400.0);
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, (s16)(s32)(dist * scale));
}

f32 inputLerpByStickAbsX(f32 from, f32 to) {
    f32 t;
    u8 stickAbs;

    stickAbs = gPlayerPadState[gCurrentPlayerIndex].stickAbsX;
    if (stickAbs != 0) {
        stickAbs = gPlayerPadState[gCurrentPlayerIndex].stickAbsX; // FAKE: re-read forces a second lbu after the branch
        if (stickAbs >= 0x47) {
            t = 70.0f;
        } else {
            t = (s32)stickAbs;
        }
        t -= 2.0f;
        t /= 68.0f;
        return ((to - from) * t) + from;
    }
    return 0.0f;
}

f32 inputLerpByStickAbsY(f32 from, f32 to) {
    f32 t;
    u8 stickAbs;

    stickAbs = gPlayerPadState[gCurrentPlayerIndex].stickAbsY;
    if (stickAbs != 0) {
        stickAbs = gPlayerPadState[gCurrentPlayerIndex].stickAbsY; // FAKE: re-read forces a second lbu after the branch
        if (stickAbs >= 0x47) {
            t = 70.0f;
        } else {
            t = (s32)stickAbs;
        }
        t -= 2.0f;
        t /= 68.0f;
        return ((to - from) * t) + from;
    }
    return 0.0f;
}

void playerInputUpdateStickMoveTarget(void) {
    f32 magDelta;
    f32 dist;
    f32 scale;
    s32 delta;
    PadInputState *pad;

    playerUpdateMoveTargetFromStick();
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    magDelta = pad->stickMagDelta;
    if (magDelta > 0.0f) {
        scale = magDelta;
    } else {
        scale = -magDelta;
    }
    if (scale < 14.0f) {
        scale = (pad->stickMagNorm * 0.7) + 0.3;
        delta = gCurrentActor->yaw - gActivePlayerState->targetYaw;
        if (delta > 0) {
            dist = (f32)delta;
        } else {
            dist = (f32)-delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * ((f64)gActivePlayerState->turnRate / 400.0);
        mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, (s16)(s32)(dist * scale));
    }
}

void playerStepYawTowardTarget(void) {
    playerUpdateMoveTargetFromStick();
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->unkEA, gActivePlayerState->turnRate);
}

void playerStepYawTowardAngle(void) {
    playerUpdateMoveTargetFromStick();
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
    gActivePlayerState->maxSpeed = 0.0f;
}

void playerInputUpdateFacingYawNormal(void) {
    s16 targetYaw;

    if (gCurrentActor->floorTiltPitch < 0x3C7) {
        targetYaw = gCurrentActor->floorTiltYaw + 0x800;
    } else {
        targetYaw = gCurrentActor->moveYaw + 0x800;
    }
    mathAngleStepToward(&gCurrentActor->yaw, targetYaw, gActivePlayerState->turnRate / 4);
    gActivePlayerState->maxSpeed = 0.0f;
}

void playerInputUpdateFacingYawOffset(void) {
    s16 targetYaw;

    if (gCurrentActor->floorTiltPitch < 0x3C7) {
        targetYaw = gCurrentActor->floorTiltYaw;
    } else {
        targetYaw = gCurrentActor->moveYaw;
    }
    mathAngleStepToward(&gCurrentActor->yaw, targetYaw, gActivePlayerState->turnRate / 4);
    gActivePlayerState->maxSpeed = 0.0f;
}



extern f32 D_80753BA4[];
extern f32 D_80753BC0[];
extern f32 D_80753BDC[];
extern f32 D_80753BF8[];
extern f32 D_80753DC8[];
extern f32 D_80753DE4[];
extern u16 *gActorScriptIndexTable;

extern u8 gPlayerCharacterId[];

void playerInputUpdateMoveTargetClamped(void) {
    f32 dist;
    s16 moveYaw;
    s32 delta;
    PadInputState *pad;

    playerUpdateMoveTargetFromStick();
    moveYaw = gCurrentActor->moveYaw;
    delta = gCurrentActor->yaw - moveYaw;
    if (delta > 0) {
        dist = delta;
    } else {
        dist = -delta;
    }
    if (dist > 2048.0f) {
        dist = 4096.0f - dist;
    }
    if (dist > 400.0f) {
        dist = 400.0f;
    }
    dist = dist * (0.25 + 0.75 * (gCurrentActor->speedXZ / gActivePlayerState->targetSpeed));
    if (dist > 1.0f) {} // FAKE: keeps the scaled dist chain alive (Q0200)
    mathAngleStepToward(&gCurrentActor->yaw, moveYaw, gActivePlayerState->turnRate / 4);
    if (gCurrentActor->state != 0x14) {
        if (gCurrentActor->state == 0xF && (gCurrentActor->sub4->model->animId == 0x1F2 || gCurrentActor->sub4->model->animId == 0x1B3)) {
            pad = &gPlayerPadState[gCurrentPlayerIndex];
            if (pad->stickX < -0x1E) {
                actorScriptStartByIndex(gCurrentActor, 0x61);
                gCurrentActor->state = 0x10;
                gCurrentActor->unk155 = 0;
            } else if (pad->stickX >= 0x1F) {
                actorScriptStartByIndex(gCurrentActor, 0x5F);
                gCurrentActor->state = 0x11;
                gCurrentActor->unk155 = 0;
            } else {
                if (pad->stickY >= 0x1F) {
                    actorScriptStartByIndex(gCurrentActor, 0x63);
                    gCurrentActor->state = 0x12;
                    gCurrentActor->unk155 = 0;
                } else if (pad->stickY < -0x1E) {
                    actorScriptStartByIndex(gCurrentActor, 0x65);
                    gCurrentActor->state = 0x13;
                    gCurrentActor->unk155 = 0;
                }
            }
        }
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        if ((pad->stickX < 0x1E && gCurrentActor->state == 0x11) || (pad->stickY >= -0x1D && gCurrentActor->state == 0x13) || (pad->stickY < 0x1E && gCurrentActor->state == 0x12) || (pad->stickX >= -0x1D && gCurrentActor->state == 0x10)) {
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 2 && gCurrentActor->state != 0x12) {
                actorScriptStart(gCurrentActor, 0x191);
            } else if (gCurrentActor->unk155 == 1) {
                switch (gCurrentActor->state) {
                    case 0x11:
                        actorScriptStartByIndex(gCurrentActor, 0x60);
                        break;
                    case 0x10:
                        actorScriptStartByIndex(gCurrentActor, 0x62);
                        break;
                    case 0x12:
                        actorScriptStartByIndex(gCurrentActor, 0x64);
                        break;
                    case 0x13:
                        actorScriptStartByIndex(gCurrentActor, 0x66);
                        break;
                }
            } else {
                actorScriptStartByIndex(gCurrentActor, 0x68);
            }
            gCurrentActor->state = 0xF;
            gCurrentActor->unk155 = 0;
        }
    }
}

void playerInputUpdateMoveTargetWithDeadzone(void) {
    f32 dist;
    f32 scale;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
        scale = scale * scale;
        if ((f64)scale < 0.2) {
            scale = 0.2f;
        }
        delta = gCurrentActor->yaw - gActivePlayerState->targetYaw;
        if (delta > 0) {
            dist = (f32)delta;
        } else {
            dist = (f32)-delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * ((f64)gActivePlayerState->turnRate / 400.0);
        mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, (s16)(s32)(dist * scale));
    }
}

void playerTurnByStickX(void) {
    f32 turn;
    s16 yaw;
    s32 delta;
    PadInputState *pad;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        if (1) {} // FAKE: steers uopt candidate priority (yaw before delta)
        if (1) {} // FAKE: steers uopt candidate priority (yaw before delta)
        if (1) {} // FAKE: steers uopt candidate priority (yaw before delta)
        if (1) {} // FAKE: steers uopt candidate priority (yaw before delta)
        yaw = gCurrentActor->yaw;
        delta = yaw - gActivePlayerState->targetYaw;
        if (delta > 0) {
            turn = delta;
        } else {
            turn = -delta;
        }
        if (turn > 2048.0f) {
            turn = 4096.0f - turn;
        }
        if (turn > 400.0f) {
            turn = 400.0f;
            if (delta && delta) {} // FAKE: steers uopt candidate priority
        }
        if (turn > 1.0f) {} // FAKE: keeps the 2048/4096/400 compare chain
        turn = (pad->stickX * gActivePlayerState->turnRate) / 400;
        gCurrentActor->yaw = yaw - turn;
        if (1) {} // FAKE: steers uopt candidate priority
        if (gCurrentActor->yaw >= 0x1000) {
            if (!gCurrentActor && !gCurrentActor && !gCurrentActor) {} // FAKE: steers uopt candidate priority
            if (delta) {} // FAKE: steers uopt candidate priority
            gCurrentActor->yaw -= 0x1000;
        }
        if (gCurrentActor->yaw < 0) {
            gCurrentActor->yaw += 0x1000;
        }
    }
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if (!(pad->heldButtons & 0x2000)) {
        gActivePlayerState->unk1A0 = pad->stickY * 0xCC * 0.6 + 63000.0;
    }
}

void playerInputUpdateMoveTargetWithDeadzone2(void) {
    f32 turn;
    f32 scale;
    s16 targetYaw;
    u16 script;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f && !gCurrentActor->speedXZ) {
        scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
        scale = scale * scale;
        if ((f64)scale < 0.2) {
            scale = 0.2f;
        }
        targetYaw = gActivePlayerState->targetYaw;
        turn = (f32)(gCurrentActor->yaw - targetYaw);
        if (turn >= 2048.0f) {
            turn -= 4096.0f;
        }
        if (turn <= -2048.0f) {
            turn += 4096.0f;
        }
        if (turn > 400.0f) {
            turn = 400.0f;
        }
        if (turn < -400.0f) {
            turn = -400.0f;
        }
        turn = (f32)((f64)turn * ((f64)gActivePlayerState->turnRate / 400.0));
        turn = turn * scale;
        if (turn > 0.0f) {
            scale = turn;
        } else {
            scale = -turn;
        }
        mathAngleStepToward(&gCurrentActor->yaw, targetYaw, (s16)(s32)scale);
        if (turn != 0.0f) {
            if (gCurrentActor->state != 0x3C) {
                if (gCurrentActor->state == 0x62) {
                    script = gActorScriptIndexTable[gCurrentActor->actorType + 0x23C];
                    if (gCurrentActor->sub4->animId != script) {
                        actorScriptStart(gCurrentActor, script);
                    }
                    scriptSetActorRampTarget(gCurrentActor, (f32)((f64)turn / 80.0), 0.0f);
                }
            } else {
                script = gActorScriptIndexTable[gCurrentActor->actorType + 0x52];
                if (gCurrentActor->sub4->animId != script) {
                    actorScriptStart(gCurrentActor, script);
                }
                scriptSetActorRampTarget(gCurrentActor, (f32)((f64)turn / 80.0), 0.0f);
            }
        }
    } else {
        if (gCurrentActor->state != 0x3C) {
            if (gCurrentActor->state == 0x62) {
                script = gActorScriptIndexTable[gCurrentActor->actorType + 0x243];
                if (gCurrentActor->sub4->animId != script) {
                    actorScriptStart(gCurrentActor, script);
                }
            }
        } else if (gCurrentActor->unk155 == 1) {
            script = gActorScriptIndexTable[gCurrentActor->actorType + 0x4B];
            if (gCurrentActor->sub4->animId != script) {
                actorScriptStart(gCurrentActor, script);
            }
        }
    }
    gActivePlayerState->maxSpeed = 0.0f;
}

void playerPathMoveByStickYAndTurn(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].stickY < 0) {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(D_80753BDC[gCurrentCharacterIndex], D_80753BF8[gCurrentCharacterIndex]);
    } else {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(D_80753BA4[gCurrentCharacterIndex], D_80753BC0[gCurrentCharacterIndex]);
    }
    if (gActivePlayerState->maxSpeed != 0.0f) {
        gActivePlayerState->unk8 = gActivePlayerState->maxSpeed > 0.0f ? 1 : -1;
    } else {
        gActivePlayerState->unk8 = 0;
    }
    proxPathAdvance(gPlayerPadState[gCurrentPlayerIndex].stickY / 80.0);
    gCurrentActor->yaw += gPlayerPadState[gCurrentPlayerIndex].stickX;
    gCurrentActor->yaw &= 0xFFF;
    playerClampYawToArc();
}

void playerPathMoveByStickY(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].stickY < 0) {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(D_80753BDC[gCurrentCharacterIndex], D_80753BF8[gCurrentCharacterIndex]);
    } else {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(D_80753BA4[gCurrentCharacterIndex], D_80753BC0[gCurrentCharacterIndex]);
    }
    if (gActivePlayerState->maxSpeed != 0.0f) {
        gActivePlayerState->unk8 = gActivePlayerState->maxSpeed > 0.0f ? 1 : -1;
    } else {
        gActivePlayerState->unk8 = 0;
    }
    proxPathAdvance(gPlayerPadState[gCurrentPlayerIndex].stickY / 80.0);
}

void playerClampYawToArc(void) {
    s16 lo;
    s16 distLo;
    s16 hi;
    s16 cur;
    s32 outside = 0;

    hi = gActivePlayerState->pathYawMax;
    lo = gActivePlayerState->pathYawMin;
    if (lo < hi) {
        cur = gCurrentActor->yaw;
        if (cur < lo || hi < cur) {
            outside = 1;
        }
    } else {
        cur = gCurrentActor->yaw;
        if (hi < cur && cur < lo) {
            outside = 1;
        }
    }
    if (outside) {
        distLo = mathAngleDistance(cur, lo);
        if (distLo < mathAngleDistance(gCurrentActor->yaw, gActivePlayerState->pathYawMax)) {
            gCurrentActor->yaw = gActivePlayerState->pathYawMin;
        } else {
            gCurrentActor->yaw = gActivePlayerState->pathYawMax;
        }
    }
}

void playerSetMoveSpeedFromStickX(void) {
    f32 v = inputLerpByStickAbsX(D_80753DC8[gCurrentCharacterIndex], D_80753DE4[gCurrentCharacterIndex]);

    if (gPlayerPadState[gCurrentPlayerIndex].stickX < 0) {
        gActivePlayerState->maxSpeed = -v;
        gActivePlayerState->unk8 = -1;
    } else {
        gActivePlayerState->maxSpeed = v;
        if (v != 0.0f) {
            gActivePlayerState->unk8 = 1;
        } else {
            gActivePlayerState->unk8 = 0;
        }
    }
}

void playerStepYawAndProjectSpeed(void) {
    playerUpdateMoveTargetFromStick();
    mathAngleStepToward(&gCurrentActor->moveYaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    playerProjectMoveSpeedOntoAngle(gCurrentActor->yaw);
}

void playerInputNoop(void) {
}


extern SchedStruct gScheduler;
extern f32 gKongTurnDecelRates[];
extern f32 gKongCannonInitialPitch[];
extern f32 D_807535CC[];

void playerInputCheckBButton(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    gCurrentActor->roll = 0;
    gCurrentActor->pitch = 0;
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (gActivePlayerState->unkC8 == -1)) {
        if (gCurrentActor->floorSlopeFactor != 0.0f) {
            gCurrentActor->moveYaw = gCurrentActor->floorSlopeYaw;
            gCurrentActor->speedXZ = 200.0f;
            gActivePlayerState->approachTimer = 0x1E;
            gActivePlayerState->approachYaw = gCurrentActor->floorSlopeYaw;
            gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex] * 0.5;
        } else {
            gActivePlayerState->airTimer = 0;
            gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        }
        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
        gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
        gCurrentActor->state = 0x17;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x10);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}

void playerInputHandleAButtonState0(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (!(gCurrentActor->contactFlags & 1) || (gCurrentActor->floorSlopeFactor == 0.0f))) {
        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
        gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
        gCurrentActor->state = 0x17;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStart(gCurrentActor, 0xB0);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}

void playerInputHandleAButtonJump(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (!(gCurrentActor->contactFlags & 1) || (gCurrentActor->floorSlopeFactor == 0.0f))) {
        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
        gCurrentActor->speedXZ = INPUT_MIN(gCurrentActor->speedXZ, gActivePlayerState->targetSpeed);
        gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
        gActivePlayerState->airAccel = 20.0f;
        gCurrentActor->state = 0x17;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x10);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
        if (!gActivePlayerState->targetSpeed) {} // FAKE: dead test, steers uopt candidate priority
    }
}

void playerInputHandleAButtonState17(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (!(gCurrentActor->contactFlags & 1) || (gCurrentActor->floorSlopeFactor == 0.0f))) {
        gCurrentActor->state = 0x17;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStart(gCurrentActor, 0xAF);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}


void playerInputHandleAButtonGravity(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if (gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) {
        if (gCurrentActor->accelY == -260.0f) {
            gCurrentActor->accelY = -31.0f;
        } else {
            playerSetBaseGravity();
        }
        gCurrentActor->state = 0x14;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x67);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}

void playerInputHandleAButtonState41(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (gActivePlayerState->hitStatus == 0)) {
        gCurrentActor->state = 0x41;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStart(gCurrentActor, 0x156);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}

extern s32 gCurrentMap;
extern u8 D_807FCA6A[];

void playerInputCheckBButtonChargeCallback(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) && (D_807FCA6A[gCurrentPlayerIndex * 0x306] >= 2) && (gCurrentMap != 0xE)) {
        playerStateQueueCallback(9, 0, gCurrentPlayerIndex);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}

void playerInputHandleAButtonState61(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (!(gCurrentActor->contactFlags & 1) || (gCurrentActor->floorSlopeFactor == 0.0f))) {
        gCurrentActor->state = 0x61;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x50);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}

f32 sqrtf(f32);


extern u8 D_8071FBC8;
extern u8 D_807200D4;
extern f32 D_80753E2C[];
extern u8 *D_807FD568;
f32 cosApprox(f32);
f32 sinApprox(f32);
extern s16 D_80753E64[];


void playerFireWeapon(u8 isFirstPerson, u8 force) {
    s16 spawnId;
    f32 scale;
    u16 sfx;
    u8 vol;
    f32 dz;
    f32 dx;
    f32 ang2;
    f32 speedXZ;
    f32 speedY;
    s32 flags;
    s32 sel;
    s16 ang;
    s32 hasFlag;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) || force) {
        flags = D_807FD568[2];
        if ((flags & 2) && slotQueueGetValue(3, gCurrentPlayerIndex)) {
            sel = 3;
        } else {
            flags &= ~2;
            sel = 2;
        }
        if (!isFirstPerson) {
            flags &= ~4;
        }
        slotQueueUpdate(sel, 0, 0);
        if (slotQueueGetValue(sel, gCurrentPlayerIndex)) {
            if (actorCountOwnedByClass(gCurrentActor, 4, actorIsActiveType2B) < D_80753E64[gCurrentCharacterIndex]) {
                hasFlag = flags & 2;
                slotQueueAddValue(sel, gCurrentPlayerIndex, -1);
                if (!isFirstPerson) {
                    s32 v = gActivePlayerState->unk8F + 1;
                    if (v >= 0x15) {
                        gActivePlayerState->unk8F = 0x14;
                    } else {
                        gActivePlayerState->unk8F = v;
                    }
                }
                rumbleRequest(gActivePlayerState->playerIndex, 0xFF, 3);
                switch (gCurrentActor->actorType) {
                    case 7:
                        spawnId = 0xAB;
                        scale = 0.5f;
                        gActivePlayerState->unk8E = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!isFirstPerson) {
                            camStartShake(gActivePlayerState->camActor, 7, 7);
                        }
                        break;
                    case 6:
                        spawnId = 0x26;
                        scale = 0.5f;
                        gActivePlayerState->unk8E = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!isFirstPerson) {
                            camStartShake(gActivePlayerState->camActor, 7, 7);
                        }
                        break;
                    case 4:
                        sfx = 0x77;
                        vol = 2;
                        spawnId = 0x2A;
                        scale = 0.5f;
                        break;
                    case 5:
                        spawnId = 0x2B;
                        scale = 0.36f;
                        sfx = 0xEF;
                        vol = 0;
                        gActivePlayerState->unk8E = 4;
                        break;
                    case 2:
                        spawnId = 0x30;
                        scale = 0.3f;
                        sfx = 0x7B;
                        vol = 5;
                        gActivePlayerState->unk8E = 0x1A;
                        break;
                    default:
                        spawnId = 0x24;
                        scale = 0.3f;
                        sfx = 0x7A;
                        vol = 5;
                        gActivePlayerState->unk8E = 0x1A;
                        break;
                }
                if (isFirstPerson) {
                    sfxPlayOnFreeSlot(sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
                } else {
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, sfx, 0xFF, 0x7F, vol);
                }
                if (hasFlag != 0) {
                    if (isFirstPerson) {
                        sfxPlayOnFreeSlot(0x1EE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                    } else {
                        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1EE, 0xFF, 0x7F, 0xA);
                    }
                }
                gActivePlayerState->unk91 = gActivePlayerState->unk90;
                if (isFirstPerson) {
                    ang = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].focusX, gPlayerSlots[gCurrentPlayerIndex].focusZ, gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ);
                } else {
                    ang = gCurrentActor->yaw;
                }
                if (gCurrentActor->actorType == 4) {
                    if ((!isFirstPerson && actorTestNodeSegmentCollision(gCurrentActor)) || actorAngleInArcWithMargin(gCurrentActor, ang, 0) == 0) {
                        projectileSetSpawnFlag();
                    }
                } else if (actorAngleInArcWithMargin(gCurrentActor, ang, 0) == 0) {
                    projectileSetSpawnFlag();
                }
                if (isFirstPerson) {
                    ang2 = gPlayerSlots[gCurrentPlayerIndex].camZ;
                    projectileSetTargetCoords(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camY, ang2);
                    dz = gPlayerSlots[gCurrentPlayerIndex].focusZ - gPlayerSlots[gCurrentPlayerIndex].camZ;
                    dx = gPlayerSlots[gCurrentPlayerIndex].focusX - gPlayerSlots[gCurrentPlayerIndex].camX;
                    ang2 = mathAtan2(gPlayerSlots[gCurrentPlayerIndex].focusY - gPlayerSlots[gCurrentPlayerIndex].camY, sqrtf(dz * dz + dx * dx));
                    speedY = D_80753E2C[gCurrentCharacterIndex] * sinApprox(ang2);
                    speedXZ = D_80753E2C[gCurrentCharacterIndex] * cosApprox(ang2);
                    ang = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].focusX, gPlayerSlots[gCurrentPlayerIndex].focusZ, gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ);
                    projectileSpawnNodeEntry(spawnId, flags, scale, ang, speedXZ, speedY, gActivePlayerActor);
                } else {
                    if ((gCurrentActor->actorType == 2 || gCurrentActor->actorType == 3 || gCurrentActor->actorType == 6 || gCurrentActor->actorType == 7)) {
                        effectSetDepth(1);
                        effectSetSpeed(0x50);
                        effectSetCallback(effectLightPulseOscillate);
                        effectCreateAtActorBone(&D_807200D4, 0.5f, gActivePlayerActor, gActivePlayerState->unk90 + 9, 2);
                        if (gCurrentActor->actorType == 6 || gCurrentActor->actorType == 7) {
                            effectSetDepth(1);
                            effectSetSpeed(0x50);
                            effectSetCallback(effectLightPulseOscillate);
                            effectCreateAtActorBone(&D_8071FBC8, 0.5f, gActivePlayerActor, 9, 2);
                        }
                    }
                    projectileGetTargetCoords(gActivePlayerActor, gActivePlayerState->unk90 + 9);
                    projectileSpawnNodeEntry(spawnId, flags, scale, gActivePlayerActor->yaw, D_80753E2C[gCurrentCharacterIndex], 0.0f, gActivePlayerActor);
                }
                if ((func_80714608(0) != 0) && (slotQueueGetValue(sel, gCurrentPlayerIndex) == 0)) {
                    playerKongStopSoundByState(gCurrentActor);
                    playerResumeLocomotion(gCurrentActor);
                }
                playerInputToggleActiveState(gCurrentActor);
            }
        } else {
            switch (gCurrentActor->actorType) {
                case 6:
                case 7:
                    sfx = 0x190;
                    vol = 5;
                    break;
                case 4:
                    sfx = 0x77;
                    vol = 2;
                    break;
                case 5:
                    sfx = 0x7C;
                    vol = 0;
                    break;
                case 2:
                    sfx = 0xB0;
                    vol = 0xA;
                    gActivePlayerState->unk8E = 0x1A;
                    break;
                default:
                    sfx = 0x83;
                    vol = 5;
                    break;
            }
            if (isFirstPerson) {
                sfxPlayOnFreeSlot(sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
                return;
            }
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, sfx, 0xFF, 0x7F, vol);
        }
    }
}


u8 actorTestNodeSegmentCollision(void *actor) {
    f32 z;
    f32 pad2;
    f32 pad1;
    f32 t;
    f32 x2;
    f32 x1;
    f32 y2;
    f32 y1;
    f32 z2;
    f32 z1;
    s16 hitA;
    s16 hitB;
    u8 hit;

    hit = 0;
    t = 0.0f;
    actorGetNodePos(actor, 4, &x1, &y1, &z1);
    actorGetNodePos(actor, 0xA, &x2, &y2, &z2);
    for (; t <= 1.0 && hit == 0; t += 0.2) {
        do { // FAKE: do/while(0) block steers the z1 copy (scheduling of z)
            z = z1;
        } while (0);
        hit = collisionTestSphere(((x2 - x1) * t) + x1, ((y2 - y1) * t) + y1, z = ((z2 - z1) * t) + z, 10.0f, &hitA, &hitB, 0, 0);
    }
    return hit;
}

typedef struct G23State90 {
    /* 0x00 */ u8 pad0[0x90];
    /* 0x90 */ u8 unk90;
} G23State90;

void playerInputToggleActiveState(Actor *actor) {
    G23State90 *state = actor->customState;

    switch (actor->actorType) {
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        state->unk90 = 1;
        return;
    default:
        state->unk90 = 1 - state->unk90;
        return;
    }
}

extern s32 gGlobalOverlayFlags;

s32 playerInputCanFireWeapon(void) {
    s32 ok;

    ok = !func_80714608(0) && !(gGlobalOverlayFlags & 0x200) && slotQueueGetValue(4, gCurrentPlayerIndex) &&
           gPlayerCharacterId[gCurrentPlayerIndex] < 6 &&
           actorCountOwnedByClass(gCurrentActor, 4, 0) < D_80753E64[gCurrentCharacterIndex] &&
           (flagGet(0x184, 0) || (gGlobalOverlayFlags & 0x10000000) || gPlayerCount >= 2 || func_807142D8() ||
            menuIsTransitionTypeC());
    return ok & 0xFF;
}


void playerInputHandlerCheckZAndTriggerState2C(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && playerInputCanFireWeapon()) {
        actorScriptStartByIndex(gCurrentActor, 0x47);
        gCurrentActor->state = 0x2C;
        gCurrentActor->unk155 = 0;
    }
}


void playerFireWeaponIfOwned(void) {
    if (D_807FD568[2] & 1) {
        playerFireWeapon(0, 0);
    }
}

void playerFireWeaponFirstPerson(void) {
    playerFireWeapon(1, 0);
}

void playerInputHandlerCheckBAndFireWeapon(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x4000) {
        actorScriptStartByIndex(gCurrentActor, 0x54);
        return;
    }
    playerFireWeapon(0, 0);
}

extern s16 D_80753354[];

void playerInputHandleZButtonCrouch(void) {
    s32 canCrouch;

    canCrouch = 1;
    if (gPlayerCount >= 2) {
        canCrouch = playerInputCheckMultiplayerPlayerTarget() == 0;
    }
    if (canCrouch && (gCurrentActor->state != 0x62) && (gCurrentActor->contactFlags & 1)) {
        gActivePlayerState->turnRate = D_80753354[gCurrentCharacterIndex];
        gCurrentActor->state = 0x62;
        gCurrentActor->unk155 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x52);
    }
}


void playerInputCheckZButtonResume(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000)) {
        playerResumeLocomotion(gCurrentActor);
    }
}

extern f32 D_8075371C[];
extern f32 D_8075378C[];

void playerInputHandleAButtonKong(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (gPlayerCharacterId[gCurrentPlayerIndex] != 6) &&
        (!(gCurrentActor->contactFlags & 1) || (gCurrentActor->floorSlopeFactor == 0.0f))) {
        if (gActivePlayerState->unk20 > 70.0f) {
            gCurrentActor->state = 0x1D;
            gCurrentActor->unk155 = 0;
            gActivePlayerState->jumpVelocityY = D_8075378C[gCurrentCharacterIndex];
            gActivePlayerState->unk50 = 0;
            actorScriptStartByIndex(gCurrentActor, 0x1A);
            if (!gCurrentActor) {} // FAKE: dead test, steers uopt candidate priority
            gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
            return;
        }
        gCurrentActor->state = 0x3E;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_8075371C[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0xE);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}




void playerInputHandleAButtonSub17(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if (((gScheduler.unk280 - gActivePlayerState->jumpTimer) < 0xF) && (gCurrentActor->state == 0x17) && (!(gCurrentActor->contactFlags & 1) || (gCurrentActor->floorSlopeFactor == 0.0f))) {
        gCurrentActor->state = 0x17;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x10);
    }
}


void playerInputHandleAButtonSub61(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if (((gScheduler.unk280 - gActivePlayerState->jumpTimer) < 0xF) && (gCurrentActor->state == 0x61) && (!(gCurrentActor->contactFlags & 1) || (gCurrentActor->floorSlopeFactor == 0.0f))) {
        gCurrentActor->state = 0x61;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x50);
    }
}




void playerInputHandleAButtonSub58(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer) < 0xF) {
        gCurrentActor->state = 0x58;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->unk50 = 0;
        gActivePlayerState->approachTimer = 0;
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}


void playerFlipHeading180(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x10) {
        gCurrentActor->moveYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
    }
}


extern s16 gKongCannonLaunchSpeeds[];
extern f32 gKongCannonLaunchTimers[];

void playerInputInitCannonLaunch(void) {
    gCurrentActor->contactFlags &= 0xFFBF;
    gActivePlayerState->respawnTimer = gKongCannonLaunchSpeeds[gCurrentCharacterIndex];
    gCurrentActor->state = 0x17;
    gCurrentActor->unk155 = 0;
    gCurrentActor->speedXZ = 0.0f;
    gActivePlayerState->jumpVelocityY = gKongCannonLaunchTimers[gCurrentCharacterIndex];
    gActivePlayerState->unk50 = 0;
    actorScriptStartByIndex(gCurrentActor, 0x10);
}


void playerInputHandleAButtonSub5A(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer) < 0xF) {
        gCurrentActor->state = 0x5A;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->approachTimer = 0;
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x74);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}


void playerInputUpdateCannonAim(void) {
    u32 sel;
    Actor *p;

    do { // FAKE: do/while(0) block around the dead test steers uopt candidate order
        if (!gCurrentActor && !gCurrentActor) {} // FAKE: dead test, steers uopt candidate priority
    } while (0);
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer) < 0xF) {
        p = gCurrentActor; // FAKE: one-use pointer web (cand 119, adjsave 2.0) takes $v1, keeping &gActivePlayerState in $a2 and &gCurrentActor in $a3
        p->state = 0x4C;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        sel = gActivePlayerState->heldActor->actorType;
        sel ^= 0; // FAKE: no-op xor keeps sel a separate web (switch register)
        switch (sel) {
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x55:
            case 0x82:
                actorScriptStart(gCurrentActor, 0x1CB);
                break;
            default:
                actorScriptStartByIndex(gCurrentActor, 0x30);
                break;
        }
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}



void playerInputClearVelocity(void) {
    playerSetTerminalVelocity594();
}



void playerInputSetBaseGravity(void) {
    playerSetBaseGravity();
}


extern f32 D_807536E4[];

void playerInputStepCannonPitch(void) {
    f32 b;
    f32 c;
    f32 a;
    s32 t;

    a = gActivePlayerState->unk1A0 + 0x9E8;
    if (a >= 32768.0f) {
        a -= 65536.0f;
    }
    a /= 16;
    if (gCurrentActor->soundSlots[0] == -1) {
        sfxPlayActorSound(gCurrentActor, 0x114, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    t = (s16)(s32)a;
    c = mathCosF(t);
    b = D_807536E4[gCurrentCharacterIndex];
    gCurrentActor->accelY = D_807536E4[gCurrentCharacterIndex] + (-2.0f * b * c);
    if (gCurrentActor->speedY < 0.0f) {
        gCurrentActor->accelY = gCurrentActor->accelY - gCurrentActor->speedY / 100.0;
    }
    if (gCurrentActor->contactFlags & 1) {
        gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
    } else {
        c = mathSinF(t) * 8.0f;
        if (c >= 0.0f) {
            a = gCurrentActor->yaw;
        } else {
            a = gCurrentActor->yaw + 0x800;
            if (a > 4096.0f) {
                a -= 4096.0f;
            }
        }
        if (c > 0.0f) {
            gActivePlayerState->airAccel = c;
        } else {
            gActivePlayerState->airAccel = -c;
        }
        playerApproachVelocity((s32)a, 900.0f, gActivePlayerState->targetSpeed);
        a = gCurrentActor->speedXZ;
        gActivePlayerState->decelRate = (a * a) / 10000.0f + 1.0f;
    }
    gActivePlayerState->unk1A2 = 1;
}



void playerInputHandleCannonBButton(void) {
    f32 temp;

    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        if (slotQueueGetValue(5, gCurrentPlayerIndex) && gActivePlayerState->isHoldingObject) {
            playerInputStepCannonPitch();
        } else {
            sfxStopSlotSound(gCurrentActor, 0);
            gCurrentActor->accelY = D_807536E4[gCurrentCharacterIndex];
            temp = gCurrentActor->speedXZ;
            gActivePlayerState->decelRate = (temp * temp) / 10000.0f + 1.0f;
        }
    } else {
        gCurrentActor->accelY = D_807536E4[gCurrentCharacterIndex];
    }
    playerApplyDeceleration();
}



void playerInputHandlerResumeDecel(void) {
    playerResumeLocomotionDecel(gCurrentActor);
}


void playerInputStopSoundOnZRelease(void) {
    f32 temp;

    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    gCurrentActor->accelY = D_807536E4[gCurrentCharacterIndex];
    temp = gCurrentActor->speedXZ;
    gActivePlayerState->decelRate = (temp * temp) / 10000.0f + 1.0f;
    playerApplyDeceleration();
}


void playerInputResetCannonPitch(void) {
    gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
}


void playerStepPitchAngleToward(f32 target) {
    PlayerState *ps;
    f32 pitch;
    u16 raw;

    ps = gActivePlayerState;
    raw = ps->unk1A0;
    if ((s32)raw < 0x8000) {
        pitch = (s32)raw + 0x10000;
    } else {
        pitch = (u32)raw;
    }
    if (target < pitch) {
        pitch -= 3000.0f;
        if (pitch < target) {
            pitch = target;
        }
    }
    if (pitch < target) {
        pitch += 3000.0f;
        if (target < pitch) {
            pitch = target;
        }
    }
    ps->unk1A0 = (u32)pitch;
}

void playerInputHandleStickAction(void) {
    static u8 D_807FD6E0; // function-local static (only user): uopt treats it as non-aliased; needs the E4090 .bss carve
    static u8 D_807FD6E1;
    f32 ang;
    f32 ground;
    f32 a;
    f32 arg;
    s16 t;

    if (slotQueueGetValue(5, gCurrentPlayerIndex) && gActivePlayerState->isHoldingObject) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000) {
            D_807FD6E0 = 0;
            D_807FD6E1 = 0;
        }
        ang = gCurrentActor->moveYaw - gCurrentActor->yaw;
        if (ang < 0.0f) {
            ang += 4096.0f;
        }
        t = (s32)ang;
        ground = mathSinF(t) * gCurrentActor->speedXZ;
        if (ground > 0.0f) {
            a = ground;
        } else {
            a = -ground;
        }
        if (a > 10.0f) {
            if (ang > 2048.0f) {
                arg = 1024.0f;
            } else {
                arg = 3072.0f;
            }
            arg += gCurrentActor->yaw;
            if (arg >= 4096.0f) {
                arg -= 4096.0f;
            }
            gActivePlayerState->airAccel = 8.0f;
            playerApproachVelocity((s32)arg, 0.0f, gActivePlayerState->targetSpeed);
        }
        ang = mathCosF(t) * gCurrentActor->speedXZ;
        ground = gCurrentActor->speedY;
        if (ground > 0.0f) {
            ground = 0.0f;
        }
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (a > 10.0f) {
            if (ground > 0.0f) {
                a = ground;
            } else {
                a = -ground;
            }
            arg = (f64)(mathAtan2(a, ang) - 1.5707964f) * 16384.0 / 1.5707963705062866 + 63000.0;
        } else {
            arg = 63000.0f;
        }
        playerStepPitchAngleToward(arg);
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (((a > 10.0f) || (gCurrentActor->speedY < 0.0f)) && (D_807FD6E1 == 0)) {
            D_807FD6E0 = 4;
        }
        if (D_807FD6E0) {
            D_807FD6E0 -= 1;
            if (D_807FD6E0 == 0) {
                D_807FD6E1 = 8;
            }
            playerInputStepCannonPitch();
        } else {
            sfxStopSlotSound(gCurrentActor, 0);
        }
        if (D_807FD6E1) {
            D_807FD6E1 -= 1;
        }
    }
}


void playerInputHandlerStartScript15(void) {
    actorScriptStartByIndex(gCurrentActor, 0x15);
    gCurrentActor->unk155 = 7;
}



extern f32 D_807531E0[];
extern f32 D_8075318C[];
extern f32 D_807534B8[];
extern s16 D_807534D4[];
extern s16 D_8075380C[];
extern s16 D_8075381C[];
extern s16 D_8075382C[];
extern s16 D_8075385C[];
extern f32 D_80750FF4;
extern u8 D_807FC9AE[];
extern u8 D_807FCA0C[];
extern u8 D_807FCAC8[];

void playerInputHandleBButtonGun(void) {
    PadInputState *pad;

    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->jumpStartTime = gScheduler.unk280;
    }
    if (gActorGlobalState.unk1C && (flagGet(0x185, 0) || (gGlobalOverlayFlags & 0x10000000) || (gPlayerCount >= 2) ||
                       menuIsTransitionTypeC())) {
        playerStateQueueCallback(3, 0, gCurrentPlayerIndex);
        return;
    }
    if (playerInputCheckBButtonTarget()) {
        return;
    }
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if (!(pad->pressedButtons & 0x4000)) {
        return;
    }
    if (!(gCurrentActor->contactFlags & 1)) {
        return;
    }
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 6) {
        if (pad->heldButtons & 0x2000) {
            gCurrentActor->state = 0x2F;
            gCurrentActor->unk155 = 0;
            actorScriptStartByIndex(gCurrentActor, 0x48);
            gActivePlayerState->slideLaunchSpeed = D_8075380C[gCurrentCharacterIndex];
            gActivePlayerState->targetSpeed = D_8075381C[gCurrentCharacterIndex];
            gActivePlayerState->decelRate = D_8075382C[gCurrentCharacterIndex];
            gActivePlayerState->turnRate = D_8075385C[gCurrentCharacterIndex];
            gCurrentActor->moveYaw = gCurrentActor->yaw;
        } else {
            gCurrentActor->state = 0x29;
            gCurrentActor->unk155 = 0;
            actorScriptStart(gCurrentActor, 0x1DF);
            gActivePlayerState->unk64 = 0;
            gActivePlayerState->slideLaunchSpeed = D_8075380C[gCurrentCharacterIndex];
        }
    } else {
        if (!func_80714608(0) && (D_807531E0[gCurrentCharacterIndex] <= gActivePlayerState->unk20) && (gCurrentActor->floorSlopeFactor == 0.0f)) {
            actorScriptStartByIndex(gCurrentActor, 0x44);
            gCurrentActor->state = 0x29;
            gCurrentActor->unk155 = 0;
            gCurrentActor->unkEA = gCurrentActor->moveYaw;
            gCurrentActor->speedXZ = 150.0f;
            gActivePlayerState->targetSpeed = 150.0f;
        } else {
            actorScriptStartByIndex(gCurrentActor, 0x3F);
            gCurrentActor->state = 0x26;
            gCurrentActor->unk155 = 0;
        }
        gActivePlayerState->unkC8 = 0x32;
        gActivePlayerState->unk64 = 0;
    }
}

s32 playerInputCheckBButtonTarget(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) && gActorGlobalState.unk2 && (gActorGlobalState.unk14 == 8)) {
        gActivePlayerState->unk220 = gActorGlobalState.unk4;
        gActivePlayerState->unk224 = gActorGlobalState.unk8;
        gActivePlayerState->unk228 = gActorGlobalState.unkC;
        playerStateQueueCallback(0x1F, 0, gCurrentPlayerIndex);
        return 1;
    }
    return 0;
}

void playerInputHandleBButtonPunch(void) {
    f32 v;
    f32 w;

    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->jumpStartTime = gScheduler.unk280;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        v = gCurrentActor->distToFloor;
        if (gCurrentActor->contactFlags & 2) {
            w = gCurrentActor->y - gCurrentActor->waterY;
            if (!(v < w)) {
                v = w;
            }
        }
        if ((3.0f < v) && (gPlayerCharacterId[gCurrentPlayerIndex] != 6)) {
            playerStateQueueCallback(0xF, 0, gCurrentPlayerIndex);
        }
    }
}

void playerInputHandleBButtonSpecial(void) {
    u8 idx;

    idx = gCurrentPlayerIndex;
    if (gPlayerPadState[idx].pressedButtons & 0x4000) {
        if ((D_8075318C[gCurrentCharacterIndex] < gActivePlayerState->unk20) &&
            ((gPlayerCharacterId[gCurrentPlayerIndex] == 3) || (gPlayerCharacterId[gCurrentPlayerIndex] == 0) || (gPlayerCharacterId[gCurrentPlayerIndex] == 5))) {
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 3) {
                gCurrentActor->speedY = 200.0f;
            }
            playerSetBaseGravity();
            gCurrentActor->state = 0x2B;
            gCurrentActor->unk155 = 0;
            actorScriptStartByIndex(gCurrentActor, 0x45);
            gActivePlayerState->unkC8 = 0x32;
        } else {
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                case 2:
                    if (D_807FCA0C[gCurrentPlayerIndex * 0x306] > 0) {
                        playerStateQueueCallback(0x25, 0, gCurrentPlayerIndex);
                    }
                    break;
                case 4:
                    if (D_807FCAC8[gCurrentPlayerIndex * 0x306] >= 2) {
                        playerStateQueueCallback(0x26, 0, gCurrentPlayerIndex);
                    }
                    break;
                case 1:
                    if (D_807FC9AE[gCurrentPlayerIndex * 0x306] > 0) {
                        gActivePlayerState->turnRate = 0x64;
                        gCurrentActor->state = 0x2E;
                        gCurrentActor->unk155 = 0;
                        actorScriptStartByIndex(gCurrentActor, 0x48);
                        gActivePlayerState->slideLaunchSpeed = D_8075380C[gCurrentCharacterIndex] * 4;
                        gActivePlayerState->targetSpeed = D_8075381C[gCurrentCharacterIndex] * 2;
                        gActivePlayerState->decelRate = D_8075382C[gCurrentCharacterIndex];
                    }
                    break;
                case 6:
                    gCurrentActor->state = 0x2F;
                    gCurrentActor->unk155 = 0;
                    actorScriptStartByIndex(gCurrentActor, 0x48);
                    gActivePlayerState->slideLaunchSpeed = D_8075380C[gCurrentCharacterIndex];
                    gActivePlayerState->targetSpeed = D_8075381C[gCurrentCharacterIndex];
                    gActivePlayerState->decelRate = D_8075382C[gCurrentCharacterIndex];
                    gActivePlayerState->turnRate = D_8075385C[gCurrentCharacterIndex];
                    gCurrentActor->moveYaw = gCurrentActor->yaw;
                    break;
            }
        }
    }
}

void playerInputHandleZButtonInteract(void) {
    s16 arcCenter;
    s16 arcWidth;
    u8 pad;
    u8 ok;
    f32 radius;

    ok = 1;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000) {
        if (gActivePlayerState->heldActor->hasArcBounds == 0) {
            radius = (gActivePlayerState->heldActor->actorType == 0x3D) ? D_80750FF4 : 30.0f;
            if (collisionTestSphere(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, radius, &arcCenter, &arcWidth, 1, 0)) {
                if (!mathAngleInArcWithMargin(arcCenter, arcWidth, gCurrentActor->yaw, 0)) {
                    ok = 0;
                }
            }
            if (ok) {
                gCurrentActor->state = 0x4A;
                gCurrentActor->unk155 = 0;
                switch (gActivePlayerState->heldActor->actorType) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x55:
                    case 0x82:
                        actorScriptStart(gCurrentActor, 0x1CD);
                        break;
                    default:
                        actorScriptStartByIndex(gCurrentActor, 0x2C);
                        break;
                }
            }
        }
    }
}

void playerInputHandleZButtonState4B(void) {
    if ((gActivePlayerState->heldActor->actorType != 0x55) && (gActivePlayerState->heldActor->actorType != 0x82)) {
        gCurrentActor->state = 0x4B;
        gCurrentActor->unk155 = 0;
        switch (gActivePlayerState->heldActor->actorType) {
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
                actorScriptStart(gCurrentActor, 0x1CC);
                break;
            default:
                actorScriptStartByIndex(gCurrentActor, 0x2D);
                break;
        }
    }
}

void playerInputThrowHeldActor(void) {
    if ((gActivePlayerState->heldActor->actorType != 0x55) && (gActivePlayerState->heldActor->actorType != 0x82)) {
        gCurrentActor->speedY = 200.0f;
        gCurrentActor->state = 0x4D;
        gCurrentActor->unk155 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x2D);
    }
}

void playerInputHandleAButtonFire(void) {
    if ((playerInputCheckMultiplayerPlayerTarget() == 0) && (gActivePlayerState->unkC8 == -1)) {
        if ((gPlayerCharacterId[gCurrentPlayerIndex] != 6) || (gCurrentActor->speedXZ < D_807531E0[gCurrentCharacterIndex])) {
            gCurrentActor->state = 0x3C;
            gCurrentActor->unk155 = 0;
            actorScriptStartByIndex(gCurrentActor, 0xA);
            gActivePlayerState->turnRate = D_807534D4[gCurrentCharacterIndex];
        }
        gActivePlayerState->decelRate = D_807534B8[gCurrentCharacterIndex];
    }
}

void playerInputHandleZButtonFire(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && playerInputCanFireWeapon()) {
        projectileTrySpawnFromSlot(gCurrentActor);
        sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x21, 0x19);
    }
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) {
        if (gScheduler.unk280 - gActivePlayerState->unk60 < 0xF) {
            if (gActivePlayerState->gunDrawn) {
                playerPlayKongSpecificSfx(gCurrentActor);
            }
            gActivePlayerState->gunDrawn = 0;
            func_806EAB44(gCurrentActor, 0);
        } else if (!func_80714608(0) && !(gGlobalOverlayFlags & 0x80000200) && (D_807FD568[2] & 1) &&
                   !(gActivePlayerState->stateFlags & 0x30) &&
                   (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1)) {
            playerToggleGun(gCurrentActor, gActivePlayerState, 1);
        }
        gActivePlayerState->unk60 = gScheduler.unk280;
    }
}

void playerInputHandleZButtonShoot(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && playerInputCanFireWeapon()) {
        projectileTrySpawnFromSlot(gCurrentActor);
        sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x21, 0x19);
    }
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) {
        if (gScheduler.unk280 - gActivePlayerState->unk60 < 0xF) {
            if (gActivePlayerState->gunDrawn) {
                playerPlayKongSpecificSfx(gCurrentActor);
            }
            gActivePlayerState->gunDrawn = 0;
            func_806EAB44(gCurrentActor, 0);
        } else if (!func_80714608(0) && !(gGlobalOverlayFlags & 0x200) && (D_807FD568[2] & 1) &&
                   (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1)) {
            playerToggleGun(gCurrentActor, gActivePlayerState, 1);
            gPlayerSlots[gCurrentPlayerIndex].fov = 45.0f;
        }
        gActivePlayerState->unk60 = gScheduler.unk280;
    }
}

void playerInputUpdateStickSwimming(void) {
    if (func_80714608(0)) {
        if (((gCurrentActor->state == 0x31) || (gCurrentActor->state == 0x32)) && (gActivePlayerState->gunDrawn == 0)) {
            playerInputHandleAButtonFire();
        }
    }
}

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

s32 actorAnyActiveHasFlag2000000(void) {
    s32 ret;
    s32 i;
    Actor *actor;

    ret = 0;
    for (i = 0; i < gActiveActorCount && ret == 0; i++) {
        actor = gActiveActors[i].actor;
        ret = actor->flags & 0x2000000;
    }
    return ret;
}

extern u32 gFrameCounter;
extern s32 gGlobalCutsceneFlags;

void playerInputCheckInstrumentPlayback(void) {
    u8 isTarget;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) && (gFrameCounter >= 3) && (D_807FD568[4] & 1) &&
        !(gGlobalOverlayFlags & 0x4000) && !(gGlobalCutsceneFlags & 1) &&
        (gPlayerSlots[gCurrentPlayerIndex].unk2C0 != 2) &&
        (playerInputCheckTargetMoved(gCurrentActor) == 0) && (actorAnyActiveHasFlag2000000() == 0) &&
        (gActivePlayerState->damageCooldown == 0)) {
        isTarget = func_806E560C(gCurrentActor);
        if ((gCurrentMap != 0xCD) || (isTarget != 0)) {
            if ((slotQueueGetValue(7, gCurrentPlayerIndex) != 0) || (isTarget != 0)) {
                playerStateQueueCallback(0x53, 0, gActivePlayerState->playerIndex);
                if (!(gGlobalCutsceneFlags & 2)) {
                    gCurrentActor->unk144 = 1;
                }
                if (!isTarget) {
                    slotQueueAddValue(7, gCurrentPlayerIndex, -1);
                }
            }
            if (!isTarget) {
                slotQueueUpdate(7, 0, 0);
            }
        }
    }
}


u8 playerInputCheckTargetMoved(Actor *mob) {
    f32 dx;
    f32 dy;
    f32 dz;

    if (mob->attachMode == 1) {
        dx = mob->unk94 - mob->prevX;
        dz = mob->unk98 - mob->prevZ;
        if (sqrtf(dx * dx + dz * dz) > 1.0) {
            return 1;
        }
    }
    if (mob->contactFlags & 8) {
        dx = mob->x - mob->prevX;
        dz = mob->y - mob->prevY;
        dy = mob->z - mob->prevZ;
        if (sqrtf(dx * dx + dz * dz + dy * dy) > 1.0) {
            return 1;
        }
    }
    if ((mob->attachMode == 1) && (modelSlotGetType(mob->cutsceneId) == 0x88)) {
        return 1;
    }
    if ((mob->attachMode == 1) && (modelSlotGetType(mob->cutsceneId) == 0x219)) {
        return 1;
    }
    if ((mob->attachMode == 1) && (modelSlotGetType(mob->cutsceneId) == 0x132)) {
        return 1;
    }
    return 0;
}

int func_806E560C(Actor *mob) {
    u8 ret;

    ret = 0;
    if (mob->attachMode == 1) {
        switch (modelSlotGetType(mob->cutsceneId)) {
            case 0xA8:
                if (mob->actorType == 2) {
                    ret = 1;
                }
                break;
            case 0xA9:
                if (mob->actorType == 3) {
                    ret = 1;
                }
                break;
            case 0xAA:
                if (mob->actorType == 5) {
                    ret = 1;
                }
                break;
            case 0xAB:
                if (mob->actorType == 6) {
                    ret = 1;
                }
                break;
            case 0xAC:
                if (mob->actorType == 4) {
                    ret = 1;
                }
                break;
        }
    }
    return ret;
}


extern u8 D_807F6903;
extern s32 D_8076A094;
extern u8 D_8076A0B2;
extern f32 D_807536AC[];
extern u8 D_8072014C[];

s32 playerInputCheckMultiplayerPlayerTarget(void) {
    s32 i;

    if (gActorGlobalState.unk2 != 0) {
        switch (gActorGlobalState.unk14) {
            case 9:
                if (gActivePlayerState->transitionTimer == 0) {
                    gActivePlayerState->unk204 = gActorGlobalState.unk4;
                    gActivePlayerState->unk208 = gActorGlobalState.unk8;
                    gActivePlayerState->unk20C = gActorGlobalState.unkC;
                    gActivePlayerState->unk21C = gActorGlobalState.unk10;
                    playerStateQueueCallback(0x1E, 0, gCurrentPlayerIndex);
                    playerRestoreKongState(gCurrentActor, gActivePlayerState);
                    return 1;
                }
                break;
            case 5:
                if (D_807F6903 == 0) {
                    if (++D_8076A094 < 0x5DD) {
                        gActivePlayerState->unk204 = gActorGlobalState.unk4;
                        gActivePlayerState->unk208 = gActorGlobalState.unk8;
                        gActivePlayerState->unk20C = gActorGlobalState.unkC;
                        playerStateQueueCallback(0x1C, 0, gCurrentPlayerIndex);
                        playerRestoreKongState(gCurrentActor, gActivePlayerState);
                        return 1;
                    }
                }
                break;
            case 3:
                if (D_807F6903 == 0) {
                    if (++D_8076A094 < 0x5DD) {
                        gActivePlayerState->unk204 = gActorGlobalState.unk4;
                        gActivePlayerState->unk208 = gActorGlobalState.unk8;
                        gActivePlayerState->unk20C = gActorGlobalState.unkC;
                        playerStateQueueCallback(0x1D, 0, gCurrentPlayerIndex);
                        playerRestoreKongState(gCurrentActor, gActivePlayerState);
                        return 1;
                    }
                }
                break;
            case 10:
                if (D_8076A0B2 == 0) {
                    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xE6, 0xFF, 0x7F, 0, 0, 0.3f, 0);
                    screenSetTransitionFadeType(0);
                    mapSaveSlotAndTransition(gActorGlobalState.unk10, gActorGlobalState.unk12, 0, 0);
                }
                return 1;
            case 4:
                if (!(gActivePlayerState->stateFlags & 0x40)) {
                    playerTransformAnimalStartSfx(gPrimaryPlayerActor);
                    gActivePlayerState->unk1FE = gActorGlobalState.unk10;
                }
                return 1;
            case 0:
                if (gFrameCounter >= 4) {
                    camStartPath(gCurrentActor, 0x26, 5);
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x18, 0xFF, 0x7F, 0x19);
                    gCurrentActor->state = 0x18;
                    gCurrentActor->unk155 = 0;
                    gCurrentActor->unk144 = 1;
                    gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex] * 2.5;
                    gActivePlayerState->unk50 = 0x28;
                    actorScriptStartByIndex(gCurrentActor, 0x22);
                    timerQueueAdd(playerInputStartTransitionToMap, 0x14, gActorGlobalState.unk10, gActorGlobalState.unk12, 0);
                    for (i = 0; i != 0x14; i++) {
                        effectSetDepth(1);
                        effectSetCallback(func_8071F034);
                        effectSetAngle(i);
                        effectCreateAtPosition(D_8072014C, 0.8f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                    }
                    effectSpawnBurstParticleCluster(gPrimaryPlayerActor);
                    return 1;
                }
                break;
            case 2:
                gCurrentActor->state = 0x1B;
                gCurrentActor->unk155 = 0;
                gActivePlayerState->jumpVelocityY = D_807536AC[gCurrentCharacterIndex];
                gActivePlayerState->unk50 = 0;
                actorScriptStartByIndex(gCurrentActor, 0x14);
                return 1;
            case 6:
                gCurrentActor->state = 0x6E;
                gCurrentActor->unk155 = 0;
                gCurrentActor->speedY = 0.0f;
                gCurrentActor->accelY = gActorGlobalState.unk10 * 0.2 + 2.0;
                gActivePlayerState->unkC0 = gActorGlobalState.unk12;
                actorScriptStart(gCurrentActor, 0x169);
                return 1;
            case 7:
                gCurrentActor->unk144 = 1;
                gActivePlayerState->unk242 = gActorGlobalState.unk10;
                gCurrentActor->state = 0x76;
                gCurrentActor->unk155 = 0;
                actorScriptStartByIndex(gCurrentActor, 0x86);
                return 1;
        }
    }
    return 0;
}


void playerInputStartTransitionToMap(s32 mapId, s32 fade, s32 unused) {
    if (fade != 0) {
        transitionSetState(2);
        screenSetTransitionFadeType(0);
    }
    mapSaveSlotAndTransition(mapId, 0, 0, 0);
}


extern u8 gSplitScreenMode;

int func_806E5C74(void) {
    f32 fv;
    f32 t;

    fv = gCurrentActor->distToFloor;
    if (gCurrentActor->contactFlags & 2) {
        t = gCurrentActor->y - gCurrentActor->waterY;
        if (!(fv < t)) {
            fv = t;
        }
    }
    return ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000) != 0) && ((f64)gActivePlayerState->currentScale[0] * 66.0 < (f64)fv) &&
           (gPlayerCharacterId[gCurrentPlayerIndex] != 6) && (D_807FD568[1] != 0);
}


void playerInputCheckEnterLongJump(void) {
    if (func_806E5C74() != 0) {
        switch (D_807FD568[1]) {
            case 2:
                actorScriptStartByIndex(gCurrentActor, 0x17);
                controllerAnimSetStateRemap(gCurrentActor, 0x18, 0.0f, 3.0f);
                scriptSetActorRampTarget(gCurrentActor, 1.35f, 0.0f);
                break;
            case 3:
                actorScriptStartByIndex(gCurrentActor, 0x19);
                break;
            default:
                actorScriptStartByIndex(gCurrentActor, 0x16);
                controllerAnimSetStateRemap(gCurrentActor, 0x17, 0.0f, 3.0f);
                scriptSetActorRampTarget(gCurrentActor, 1.35f, 0.0f);
                break;
        }
        gCurrentActor->state = 0x1C;
        gCurrentActor->unk155 = 0;
    }
}

void playerInputHandlerNoop1(void) {
}

void playerInputHandlerNoop2(void) {
}

void playerInputQueueCrouchCallback(void) {
    if (!(gActivePlayerState->stateFlags & 0x20)) {
        playerStateQueueCallback(0x24, 0, gCurrentPlayerIndex);
    }
}

void playerInputQueueCrouchCallbackDirect(void) {
    playerStateQueueCallback(0x24, 0, gCurrentPlayerIndex);
}

void playerInputHandleBButtonMusicalInstrument(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (D_807FD568[2] & 1) &&
        (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) && !(gActivePlayerState->stateFlags & 0x30) &&
        (func_80714608(0) == 0)) {
        playerStateQueueCallback(0x14, 0, gCurrentPlayerIndex);
    }
}

void playerInputHandleBButtonFairyCamera(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (D_807FD568[2] & 1) && !(gGlobalOverlayFlags & 0x200) &&
        (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) && !(gActivePlayerState->stateFlags & 0x30) &&
        (func_80714608(0) == 0)) {
        playerStateQueueCallback(0x15, 0, gCurrentPlayerIndex);
    }
}


void playerInputHandleRButtonCameraLock(void) {
    CamState *obj;

    obj = gActivePlayerState->camActor->customState;
    obj->unkAC |= 4;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x10) {
        if ((gGlobalOverlayFlags & 1) || ((gPlayerCount >= 2) && (gSplitScreenMode == 0))) {
            if (obj->unkAC & 0x10000) {
                camClearSecondTarget(gActivePlayerState->camActor);
                return;
            }
            camSetSecondTarget(gActivePlayerState->camActor, 0, 0);
            return;
        }
        if (!(obj->unkAC & 0x4000)) {
            obj->unkAC ^= 2;
            if ((obj->unkF1 < 3) && (obj->unkF5 == 0) && (obj->unkF3 != 2)) {
                obj->unkF1 = 0x14;
                obj->unkB2 = gCurrentActor->yaw;
                gActivePlayerState->camActor->distToFloor = obj->unkB8;
                obj->unkF5 = 0xA;
            }
        }
    }
}

void playerInputHandleRButtonReleaseCameraLock(void) {
    CamState *obj;

    if (!(gGlobalOverlayFlags & 1) && ((gPlayerCount < 2) || (gSplitScreenMode != 0))) {
        obj = gActivePlayerState->camActor->customState;
        obj->unk4 = 0;
        obj->unkAC &= ~4;
    }
}

extern u8 gPausingPlayer;
extern f32 gScreenFadeProgress;

void playerInputRequestPause(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x1000) && (camIsCutsceneActive() == 0) && (gScreenFadeProgress == 0.0f) &&
        ((menuIsTransitionType6() != 0) || (menuIsTransitionTypeC() != 0) || (func_807142D8() != 0)) &&
        (screenWipeGetState() == 0) && (screenWipeGetCooldown() == 0)) {
        gPausingPlayer = gCurrentPlayerIndex;
        gGlobalPauseFlags |= 1;
    }
}



extern f32 D_80753988[];
extern s16 gKongStickTurnRates[];
extern f32 D_8075396C[];
extern f32 D_80753AC4[];
extern f32 D_80753AA8[];
extern s16 D_80753A98[];
extern s16 D_8075395C[];
extern s16 D_80753B44[];

void playerInputRecordAPress(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
}

void playerInputRecordBPress(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->jumpStartTime = gScheduler.unk280;
    }
}

void playerInputCalculateStickForwardSpeed(void) {
    f32 temp;

    if (gPlayerPadState[gCurrentPlayerIndex].stickMag != 0.0f) {
        temp = gActivePlayerState->unk34;
        gActivePlayerState->maxSpeed = (gPlayerPadState[gCurrentPlayerIndex].stickMagNorm * (gActivePlayerState->targetSpeed - temp)) + temp;
    } else {
        gActivePlayerState->maxSpeed = 0.0f;
    }
    gActivePlayerState->maxSpeed = gActivePlayerState->maxSpeed / 4;
    if (gPlayerPadState[gCurrentPlayerIndex].stickMag != 0.0f) {
        mathAngleStepToward(&gCurrentActor->yaw, gPlayerPadState[gCurrentPlayerIndex].stickAngle, gActivePlayerState->turnRate);
    }
    mathAngleStepToward(&gCurrentActor->roll, 0, 0x10);
    mathAngleStepToward(&gCurrentActor->pitch, 0, 0x10);
}

void playerInputCalculateStickTurnRate(void) {
    s16 pitch;

    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX != 0) {
        pitch = gKongStickTurnRates[gCurrentCharacterIndex] * ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0) ? 1 : -1);
        pitch &= 0xFFF;
    } else {
        pitch = 0;
    }
    mathAngleStepToward(&gCurrentActor->pitch, pitch, 0x10);
    mathAngleStepToward(&gCurrentActor->roll, gActivePlayerState->subTimer, 0x10);
    gActivePlayerState->targetSpeed = D_80753988[gCurrentCharacterIndex];
}

extern s16 D_80753B54[];
extern s16 D_80753B64[];

void playerInputStepTurnFacingAngle(void) {
    s32 ang;
    s16 target;
    s16 rollStep;

    ang = gCurrentActor->yaw;
    rollStep = 0x10;
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
        rollStep = 0x19;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX != 0) {
        ang ^= 0; // FAKE: no-op xor keeps ang a separate web
        gCurrentActor->yaw = (u16)(ang - (gPlayerPadState[gCurrentPlayerIndex].stickX / 2)) & 0xFFF;
        target = D_80753B54[gCurrentCharacterIndex] * ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0) ? 1 : -1);
        target &= 0xFFF;
    } else {
        target = 0;
    }
    mathAngleStepToward(&gCurrentActor->pitch, target, 0x10);
    if (gPlayerPadState[gCurrentPlayerIndex].stickY != 0) {
        target = (D_80753B44[gCurrentCharacterIndex] * gPlayerPadState[gCurrentPlayerIndex].stickY) / 70;
        target = target & 0xFFF;
        mathAngleStepToward(&gCurrentActor->roll, target, (s16)(s32)((((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.125) > 0.0 ? ((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.125) : -((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.125)) + (f64)rollStep));
        return;
    }
    mathAngleStepToward(&gCurrentActor->roll, D_80753B64[gCurrentCharacterIndex], 0x10);
}

void playerInputUpdateStickTurnYaw(void) {
    f32 dist;
    f32 scale;
    s16 targetYaw;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        scale = (f32)(((f64)gPlayerPadState[gCurrentPlayerIndex].stickMagNorm * 0.5) + 0.5);
        targetYaw = gActivePlayerState->targetYaw;
        delta = gCurrentActor->yaw - targetYaw;
        if (delta > 0) {
            dist = (f32)delta;
        } else {
            dist = (f32)-delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * ((f64)gActivePlayerState->turnRate / 400.0);
        mathAngleStepToward(&gCurrentActor->yaw, targetYaw, (s16)(s32)(dist * scale));
    }
    mathAngleStepToward(&gCurrentActor->roll, 0, 0x10);
    mathAngleStepToward(&gCurrentActor->pitch, 0, 0x10);
    gActivePlayerState->subTimer = 0;
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    gActivePlayerState->actionTimer = D_8075395C[gCurrentCharacterIndex];
    gActivePlayerState->targetSpeed = D_80753988[gCurrentCharacterIndex] * gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x4000) {
        gActivePlayerState->targetSpeed = gActivePlayerState->targetSpeed * 1.33;
    }
}

void playerInputUpdateStickTurnYawFast(void) {
    f32 dist;
    f32 scale;
    s16 targetYaw;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        scale = (f32)(((f64)gPlayerPadState[gCurrentPlayerIndex].stickMagNorm * 0.5) + 0.5);
        targetYaw = gActivePlayerState->targetYaw;
        delta = gCurrentActor->yaw - targetYaw;
        if (delta > 0) {
            dist = (f32)delta;
        } else {
            dist = (f32)-delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * 0.45;
        mathAngleStepToward(&gCurrentActor->yaw, targetYaw, (s16)(s32)(dist * scale));
    }
    mathAngleStepToward(&gCurrentActor->roll, 0, 0x10);
    mathAngleStepToward(&gCurrentActor->pitch, 0, 0x10);
}

void playerInputCalculateTurnStep(void) {
    s16 pad;
    s16 target;
    s16 ang;
    s16 rollStep;

    ang = gCurrentActor->yaw;
    rollStep = 0x10;
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX != 0) {
        if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
            ang = (s16)(s32)((f64)ang - ((f64)gPlayerPadState[gCurrentPlayerIndex].stickX * 0.8));
        } else {
            ang = (s16)(s32)((f64)ang - ((f64)gPlayerPadState[gCurrentPlayerIndex].stickX * 0.5));
        }
        gCurrentActor->yaw = ang & 0xFFF;
        target = gKongStickTurnRates[gCurrentCharacterIndex] * ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0) ? 1 : -1);
        target &= 0xFFF;
    } else {
        target = 0;
    }
    mathAngleStepToward(&gCurrentActor->pitch, target, 0x10);
    target = (D_80753B44[gCurrentCharacterIndex] * gPlayerPadState[gCurrentPlayerIndex].stickY) / 70;
    target = target & 0xFFF;
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
        rollStep = (s16)(s32)((((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5) > 0.0 ? ((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5) : -((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5)) + 16.0);
    }
    mathAngleStepToward(&gCurrentActor->roll, target, rollStep);
}

void playerInputHandleAButtonJumpQueue(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if (gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) {
        playerStateQueueCallback(1, 0, gCurrentPlayerIndex);
    }
}

void playerInputInitDashParams(void) {
    gActivePlayerState->subTimer = 0;
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    if (gActivePlayerState->actionTimer == 0) {
        gActivePlayerState->actionTimer = 1;
        gActivePlayerState->targetSpeed = D_8075396C[gCurrentCharacterIndex];
    }
}

void playerInputCheckAButtonScriptTrigger(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000)) {
        actorScriptStartByIndex(gCurrentActor, 0x37);
        gCurrentActor->unk155 = 4;
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
}

void playerInputHandleBButtonDiveAttack(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        actorScriptStartByIndex(gCurrentActor, 0x37);
        gCurrentActor->unk155 = 4;
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
}

void playerInputHandleBButtonRollingAttack(void) {
    gActivePlayerState->jumpTimer = gScheduler.unk280;
    scriptSetActorRampTarget(gCurrentActor, 2.0f, 0.0f);
    actorScriptStartByIndex(gCurrentActor, 0x38);
    gCurrentActor->unk155 = 7;
}

void playerInputHandleBButtonSlideAttack(void) {
    actorScriptStartByIndex(gCurrentActor, 0x39);
    gCurrentActor->unk155 = 7;
}

void playerInputSetSubstate6(void) {
    gCurrentActor->unk155 = 6;
}

void playerInputHandleBButtonComboPunch(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
            gActivePlayerState->subTimer = gCurrentActor->roll;
            gActivePlayerState->pitchAngle = gCurrentActor->yaw;
            if (gActivePlayerState->actionTimer == 0) {
                gActivePlayerState->targetSpeed = D_80753AC4[gCurrentCharacterIndex];
                actorScriptStartByIndex(gCurrentActor, 0x36);
            } else {
                gActivePlayerState->targetSpeed = D_80753AA8[gCurrentCharacterIndex];
            }
            gActivePlayerState->actionTimer = D_80753A98[gCurrentCharacterIndex];
            gActivePlayerState->jumpStartTime = gScheduler.unk280;
        } else if (!(gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000)) {
            gActivePlayerState->subTimer = gCurrentActor->roll;
            gActivePlayerState->pitchAngle = gCurrentActor->yaw;
            if (gActivePlayerState->actionTimer == 0) {
                gActivePlayerState->actionTimer = 1;
                gActivePlayerState->targetSpeed = D_80753AA8[gCurrentCharacterIndex];
            }
        }
    }
}

void playerInputHandleBButtonAttack(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->targetSpeed = D_80753AC4[gCurrentCharacterIndex];
            actorScriptStartByIndex(gCurrentActor, 0x36);
        } else {
            gActivePlayerState->targetSpeed = D_80753AA8[gCurrentCharacterIndex];
        }
        gActivePlayerState->actionTimer = D_80753A98[gCurrentCharacterIndex];
        gActivePlayerState->jumpStartTime = gScheduler.unk280;
    }
}

typedef struct G28State {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[0x28];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ u8 *unk34;
    /* 0x38 */ u8 pad38[6];
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
    /* 0x40 */ u8 unk40;
    /* 0x41 */ u8 pad41;
    /* 0x42 */ u8 unk42;
} G28State;


void playerInputHandleAButtonSuperJump(void) {
    s32 btn;

    btn = gPlayerPadState[gCurrentPlayerIndex].pressedButtons;
    if (btn & 0x8000) {
        gCurrentActor->unk155 = 3;
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->targetSpeed = 300.0f;
            actorScriptStart(gCurrentActor, 0x318);
        } else {
            gActivePlayerState->targetSpeed = 250.0f;
        }
        gActivePlayerState->actionTimer = 0xF;
        gActivePlayerState->jumpStartTime = gScheduler.unk280;
        return;
    }
    if (!(btn & 0x4000)) {
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->actionTimer = 1;
            gActivePlayerState->targetSpeed = 250.0f;
        }
    }
}

extern f32 D_80753B18[];

void playerInputHandleAButtonSuperJump2(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gCurrentActor->unk155 = 3;
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->targetSpeed = 300.0f;
            actorScriptStart(gCurrentActor, 0x318);
        } else {
            gActivePlayerState->targetSpeed = 250.0f;
        }
        gActivePlayerState->actionTimer = 0xF;
        gActivePlayerState->jumpStartTime = gScheduler.unk280;
    }
}


void playerInputHandleBButtonDashAttack(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->targetSpeed = D_80753AC4[gCurrentCharacterIndex];
        actorScriptStartByIndex(gCurrentActor, 0x36);
        gCurrentActor->unk155 = 3;
        gActivePlayerState->actionTimer = D_80753A98[gCurrentCharacterIndex];
        gActivePlayerState->jumpStartTime = gScheduler.unk280;
    }
}


void playerInputHandleCDownFairyCheck(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4) && !(gGlobalOverlayFlags & 2)) {
        func_806E9804(8);
        return;
    }
    gActivePlayerState->subTimer = gCurrentActor->roll;
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    gActivePlayerState->actionTimer = 0;
    gActivePlayerState->decelRate = 8.0f;
}

s32 playerInputCanPerformFairySnap(void) {
    s32 ok;

    ok = flagGet(0x182, 0) || (gGlobalOverlayFlags & 0x10000000) || gPlayerCount >= 2 || menuIsTransitionTypeC();
    return ok & 0xFF;
}


extern s16 D_8075386C[];
extern f32 D_8075389C[];

void playerInputHandleCDownCameraSnap(void) {
    f32 minHeight;
    s32 btn;

    btn = gPlayerPadState[gCurrentPlayerIndex].pressedButtons;
    if ((btn & 4) && !(gGlobalOverlayFlags & 2)) {
        func_806E9804(8);
        return;
    }
    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        minHeight = D_8075386C[gCurrentCharacterIndex];
    } else {
        minHeight = D_8075389C[gCurrentCharacterIndex];
    }
    if ((btn & 0x2000) && (minHeight < gCurrentActor->distToFloor) && playerInputCanPerformFairySnap()) {
        playerStateQueueCallback(0x3E, 0, gCurrentPlayerIndex);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
    }
}

void playerInputSetCharacterDecelRate(void) {
    gActivePlayerState->decelRate = D_80753B18[gCurrentCharacterIndex];
}

void playerInputResetDecelRate(void) {
    gActivePlayerState->decelRate = 1.0f;
}

void func_806E78F8(void) {
}

void playerInputHandleLadderClimb(void) {
    G28State *st;
    PadInputState *pad;
    s8 stick;
    u8 state;

    st = gActivePlayerState->actor->customState;
    if (gCurrentActor->state == 7) {
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        if (!(pad->heldButtons & 0x10)) {
            stick = pad->stickX;
            if (stick < -0x1E && gCurrentActor->sub4->model->animId != 0xFB) {
                actorScriptStartByIndex(gCurrentActor, 0x81);
                gCurrentActor->state = 0xA;
                gCurrentActor->unk155 = 0;
                st->unk42 = 1;
            } else if (stick >= 0x1F && gCurrentActor->sub4->model->animId != 0xFF) {
                actorScriptStartByIndex(gCurrentActor, 0x7D);
                gCurrentActor->state = 0xB;
                gCurrentActor->unk155 = 0;
                st->unk42 = 2;
            }
        }
    }
    stick = gPlayerPadState[gCurrentPlayerIndex].stickX;
    if ((stick < 0x1E && gCurrentActor->state != 0xA) || (stick >= -0x1D && gCurrentActor->state != 0xB)) {
        st->unk42 = 0;
        state = gCurrentActor->state;
        if (state != 0xA) {
            if (state == 0xB) {
                if (gCurrentActor->unk155 == 1) {
                    actorScriptStartByIndex(gCurrentActor, 0x7E);
                } else {
                    actorScriptStartByIndex(gCurrentActor, 0x80);
                }
                gCurrentActor->state = 7;
                gCurrentActor->unk155 = 0;
            }
        } else {
            if (gCurrentActor->unk155 == 1) {
                actorScriptStartByIndex(gCurrentActor, 0x82);
            } else {
                actorScriptStartByIndex(gCurrentActor, 0x80);
            }
            gCurrentActor->state = 7;
            gCurrentActor->unk155 = 0;
        }
    }
}

void playerInputUpdateLadderState(void) {
    G28State *st;

    st = gActivePlayerState->actor->customState;
    if (gActivePlayerState->stateFlags & 8) {
        st->unk3E = 4;
    } else {
        st->unk3E = (gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5) + 60.0;
    }
    playerInputHandleLadderClimb();
}

void playerInputStepLadderClimb(void) {
    G28State *st;

    st = gActivePlayerState->actor->customState;
    if (st->unk0 != 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
    }
    playerInputHandleLadderClimb();
    if (gActivePlayerState->stateFlags & 8) {
        st->unk3E = 3;
    } else {
        st->unk3E = (gPlayerPadState[gCurrentPlayerIndex].stickY / 1.5) + 80.0;
    }
    st->unk2 = gPlayerPadState[gCurrentPlayerIndex].stickX;
}

extern s16 D_80750338;

void playerInputCheckLadderTopOrBottom(void) {
    G28State *st;
    u8 flag;
    s32 rungLimit;
    u8 cnt;

    st = gActivePlayerState->actor->customState;
    if (st->unk0 != 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
    } else {
        flag = (gActivePlayerState->actor->state == 5) ? 1 : 0;
        rungLimit = (*st->unk34 & 0x80) ? 1 : 3;
        if (flag) {
            gPlayerPadState[gCurrentPlayerIndex].stickX = gPlayerPadState[gCurrentPlayerIndex].stickX * -1;
        }
        if (gActivePlayerState->stateFlags & 0x10000002) {
            gPlayerPadState[gCurrentPlayerIndex].stickX = gPlayerPadState[gCurrentPlayerIndex].stickX * -1;
        }
        if (gActivePlayerState->stateFlags & 0x10000002) {
            gPlayerPadState[gCurrentPlayerIndex].stickY = gPlayerPadState[gCurrentPlayerIndex].stickY * -1;
        }
        if ((*st->unk34 & 0xC0) &&
            ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0x1F && st->unk3F > 0) || (gPlayerPadState[gCurrentPlayerIndex].stickX < -0x1E && st->unk3F < rungLimit))) {
            gActivePlayerState->jumpTimer = gScheduler.unk280;
            gActivePlayerState->actor->speedY = D_80750338;
            gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
            cnt = st->unk3F;
            st->unk2C = 1.0f;
            st->unk40 = cnt;
            if (gPlayerPadState[gCurrentPlayerIndex].stickX >= 0x1F) {
                st->unk3F = cnt - 1;
                if (st->unk3F == 1) {
                    st->unk3F = 0;
                }
                actorScriptStartByIndex(gCurrentActor, flag ? 0x81 : 0x7D);
                actorScriptStart(gActivePlayerState->actor, flag ? 0x295 : 0x296);
            } else {
                st->unk3F = cnt + 1;
                if (st->unk3F == 1 && (*st->unk34 & 0x40)) {
                    st->unk3F = 2;
                }
                actorScriptStartByIndex(gCurrentActor, flag ? 0x7D : 0x81);
                actorScriptStart(gActivePlayerState->actor, flag ? 0x296 : 0x295);
            }
        }
    }
    if (gActivePlayerState->stateFlags & 8) {
        st->unk3E = 3;
        gActivePlayerState->actor->speedXZ = 3.0f;
        return;
    }
    st->unk3E = (gPlayerPadState[gCurrentPlayerIndex].stickY / 1.5) + 80.0;
}

typedef struct G29Obj178 {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    u8 padC[8];
    f32 unk14;
} G29Obj178;

typedef struct G29State {
    u8 pad0[2];
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0xC];
    s32 unk20;
    u8 pad24[1];
    u8 unk25;
    u8 pad26[3];
    u8 unk29;
    u8 pad2A[6];
    Actor *unk30;
    u8 unk34;
    u8 pad35[9];
    u8 unk3E;
    u8 pad3F[3];
    u8 unk42;
    u8 pad43[2];
    u8 unk45;
} G29State;

typedef struct G29Act {
    u8 pad0[0xB8];
    f32 unkB8;
    u8 padBC[0xB8];
    G29State *unk174;
    G29Obj178 *unk178;
} G29Act;




extern f32 D_80750FF8;
extern f32 D_80750FFC;
extern f32 D_80751000;

void playerInputRegisterAnimatedEffect(void) {
    G29State *st;
    PadInputState *pad;
    s16 yaw;

    st = gActivePlayerState->actor->customState;
    if (hudCanRender() != 0) {
        renderCallbacksRegister(actorDrawAnimatedEffect, gActivePlayerState->actor, 5);
    }
    yaw = gCurrentActor->yaw;
    if (yaw < 0x200 || yaw >= 0xE01) {
        st->unk2 = gPlayerPadState[gCurrentPlayerIndex].stickX;
        pad = &gPlayerPadState[gCurrentPlayerIndex ^ 0]; // FAKE: no-op xor splits this index from the CSE (keeps the other arms' multu)
    } else if (yaw >= 0x201 && yaw < 0x600) {
        s8 t;
        st->unk2 = gPlayerPadState[gCurrentPlayerIndex].stickY;
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        t = pad->stickX;
        pad->stickX = pad->stickY;
        pad->stickY = t;
    } else if (yaw >= 0x601 && yaw < 0xA00) {
        st->unk2 = -gPlayerPadState[gCurrentPlayerIndex].stickX;
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        pad->stickX = -pad->stickX;
        pad->stickY = -pad->stickY;
    } else {
        s8 t;
        st->unk2 = -gPlayerPadState[gCurrentPlayerIndex].stickY;
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        t = pad->stickX;
        pad->stickX = -pad->stickY;
        pad->stickY = -t;
    }
    if (pad->stickX < -0x1E) {
        gActivePlayerState->unk23C = 0x28;
        st->unk42 = 1;
    } else if (pad->stickX >= 0x1F) {
        gActivePlayerState->unk23C = 0x28;
        st->unk42 = 2;
    } else if (gActivePlayerState->unk23C != 0) {
        gActivePlayerState->unk23C--;
    } else {
        st->unk42 = 0;
    }
}

void playerInputSetClimbTimer20(void) {
    G29State *st;

    st = gActivePlayerState->actor->customState;
    st->unk3E = 0x14;
}

void playerInputSetClimbTimer100(void) {
    G29State *st;

    st = gActivePlayerState->actor->customState;
    st->unk3E = 0x64;
    if (gActivePlayerState->unk23C != 0) {
        gActivePlayerState->unk23C--;
    }
}

void playerInputSetClimbTimer50(void) {
    G29State *st;

    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0xE000)) {
        st = gActivePlayerState->actor->customState;
        st->unk3E = 0x32;
    }
}

void func_806E854C(G29State *st, s32 idleAnim, s32 moveAnim) {
    AnimSlot *sub;
    s32 n;
    f32 f;
    f32 h;
    f32 cur;

    sub = gActivePlayerActor->sub4->model;
    if (moveAnim != sub->animId) {
        if (idleAnim == sub->animId) {
            controllerAnimSetStateIfChanged(gActivePlayerActor, moveAnim, 0.0f, 5.0f);
            return;
        }
        if (gCurrentActor->sub4->model->speed >= 0.0f && sub->frame > 0.0f) {
            scriptSetRampValue(gActivePlayerActor, -1.0f, 0.0f);
        }
        if (gCurrentActor->sub4->model->frame == 0.0f) {
            controllerAnimSetStateIfChanged(gActivePlayerActor, moveAnim, 0.0f, 5.0f);
        }
    } else {
        cur = st->unkC;
        f = (cur > 0.0f) ? cur : -cur;
        h = f - 0.2f;
        n = st->unk10 > 1.0 ? 8 : 5;
        cur = sub->frame;
        f = n * h * 1.25f;
        if (f - 1.0f <= cur && cur <= f + 1.0f) {
            n = 0;
        } else {
            n = f <= cur ? -1 : 1;
        }
        scriptSetRampValue(gActivePlayerActor, n, 5.0f);
    }
}

void func_806E8724(G29Act *actor, G29State *st) {
    s32 sign;
    s32 t;
    f32 f;
    f32 g;
    f32 x;

    if (st->unk45 == 0 && st->unk34 == 2) {
        t = gPlayerPadState[gCurrentPlayerIndex].stickY < -0x14;
        sign = gPlayerPadState[gCurrentPlayerIndex].stickX >= 0 ? 1 : -1;
        f = gPlayerPadState[gCurrentPlayerIndex].stickAbsX;
        if (f > 80.0f) {
            g = 80.0f;
        } else {
            g = f;
        }
        x = g;
        x *= sign;
        x *= 0.0125f;
        st->unkC = x;
        st->unkC = x * D_80750FFC;
        if (st->unk20 == 0) {
            st->unk20 = (actor->unkB8 < D_80750FF8) & t;
        } else {
            st->unk20 = t;
        }
    } else {
        st->unk20 = 0;
        st->unkC = 0.0f;
    }
}

void playerInputUpdateHeldActorVineClimb(void) {
    G29Act *a;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        func_806E8724(a, a->unk174);
    }
}

void playerInputSetHeldActorVineSpeed(void) {
    G29Act *a;
    G29State *st;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        st->unk8 = D_80751000;
    }
}

void playerInputClearHeldActorVineSpeed(void) {
    G29Act *a;
    G29State *st;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        st->unk8 = 0.0f;
    }
}

void playerInputPlayHeldActorClimbSfx(void) {
    G29Act *a;
    G29State *st;
    s32 idleAnim;
    s32 leftAnim;
    s32 rightAnim;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        if (gCurrentActor->actorType == 4) {
            idleAnim = 0x1C7;
            leftAnim = 0x1C5;
            rightAnim = 0x1C6;
        } else {
            idleAnim = 0x53;
            leftAnim = 0x54;
            rightAnim = 0x55;
        }
        st = a->unk174;
        func_806E8724(a, st);
        if (camIsCutsceneActive() == 0 && gActivePlayerActor->sub4->animId != 0x3B5) {
            if (st->unkC < 0.2f && st->unkC > -0.2f && idleAnim != gActivePlayerActor->sub4->model->animId) {
                if (gActivePlayerActor->sub4->model->speed >= 0.0f && gActivePlayerActor->sub4->model->frame > 0.0f) {
                    scriptSetRampValue(gActivePlayerActor, -1.0f, 5.0f);
                    return;
                }
                if (gCurrentActor->sub4->model->frame == 0.0f) {
                    controllerAnimSetStateIfChanged(gActivePlayerActor, idleAnim, 0.0f, 5.0f);
                }
            } else {
                if (st->unkC < -0.2f) {
                    func_806E854C(st, idleAnim, leftAnim);
                    return;
                }
                if (st->unkC > 0.2f) {
                    func_806E854C(st, idleAnim, rightAnim);
                }
            }
        }
    }
}

void playerInputScaleHeldActorVineClimb(void) {
    G29Act *a;
    G29State *st;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            if (st->unk25 == 0) {
                st->unk4 = 1.1f;
            }
        } else {
            st->unk4 = 0.0f;
        }
    }
}

void func_806E8AF0(void) {
    G29Act *a;
    G29State *st;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        if (st->unk25 == 0) {
            st->unk4 = 0.0f;
        }
    }
}

void func_806E8B28(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            o = a->unk178;
            if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
                o->unk4 = 1;
            }
        }
    }
}

void func_806E8BA4(void) {
    G29Act *a;
    G29State *st;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            st->unk10 = 2.0f;
        } else {
            st->unk10 = 1.0f;
        }
    }
}

void func_806E8BFC(void) {
    G29Act *a;
    G29State *st;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        st->unk10 = 1.0f;
    }
}

void func_806E8C2C(void) {
    G29Act *a;
    G29Obj178 *o;
    s32 current;
    s32 target;
    s8 stickX;

    a = (G29Act *)gActivePlayerState->actor;
    if (a != NULL) {
        if (gActivePlayerActor->sub4->model->animId != 0x22A) {
            controllerAnimSetStateIfChanged(gActivePlayerActor, 0x22A, 0.0f, 0.0f);
        }
        if (a->unk174->unk45 == 0 && a->unk174->unk30->state == 2) {
            o = a->unk178;
            target = o->unk1;
            current = o->unk0;
            stickX = gPlayerPadState[gCurrentPlayerIndex].stickX;
            if (target == current && o->unk4 == 0) {
                if (stickX >= 0x1F && current < 2) {
                    o->unk1 = current + 1;
                } else if (stickX < -0x1E) {
                    if (current > 0) {
                        o->unk1 = current - 1;
                    }
                }
                target = o->unk1;
                if (target != current) {
                    o->unk4 = 2;
                    o->unk8 = 0.0f;
                }
            }
        }
    }
}

void func_806E8D54(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        if (st->unk34 != 0 && st->unk34 < 3 && st->unk45 == 0) {
            o = a->unk178;
            st->unk4 = o->unk14 + 1.1;
        }
    }
}

void func_806E8DB4(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        if (st->unk34 != 0 && st->unk34 < 3 && st->unk45 == 0) {
            o = a->unk178;
            st->unk4 = o->unk14;
        }
    }
}

void func_806E8E00(void) {
    G29Act *a;
    G29State *st;

    a = ((G29Act *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2 && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000)) {
            st->unk29 = 1;
        }
    }
}

void func_806E8E78(void) {
    if (gCurrentActor->state == 7 && !(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x10)) {
        actorScriptStartByIndex(gCurrentActor, 0x7F);
        gCurrentActor->state = 8;
        gCurrentActor->unk155 = 0;
    }
}

typedef struct G30State {
    /* 0x00 */ s16 unk0;
} G30State;



extern f32 D_807537E0[];
extern s16 D_80750338;
extern s16 D_807539DC[];
extern s16 D_807539EC[];

void func_806E8F04(void) {
    if (gCurrentActor->unk155 == 1) {
        actorScriptStartByIndex(gCurrentActor, 0x7B);
    } else {
        actorScriptStartByIndex(gCurrentActor, 0x80);
    }
    gCurrentActor->state = 7;
    gCurrentActor->unk155 = 0;
}

void func_806E8F68(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) && !(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x10)) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if (gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) {
        gCurrentActor->state = 9;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = D_807537E0[gCurrentCharacterIndex];
        gActivePlayerState->unk50 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x7C);
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
    }
}

void func_806E9070(void) {
    G30State *st;

    st = gActivePlayerState->actor->customState;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if ((gScheduler.unk280 - gActivePlayerState->jumpTimer < 0xF) && (st->unk0 == 0)) {
        gActivePlayerState->actor->speedY = D_80750338;
        gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
        actorScriptStartByIndex(gCurrentActor, 0x7C);
        if (gCurrentActor->actorType == 2) {
            actorScriptStart(gActivePlayerState->actor, 0x294);
        } else {
            actorScriptStart(gActivePlayerState->actor, 0x293);
        }
    }
}


void func_806E918C(void) {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;

    if (!(gActivePlayerState->stateFlags & 0x10000000)) {
        if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x10) && (gCurrentActor->state == 7)) {
            actorGetNodePos(gActivePlayerState->actor, 3, &x1, &y1, &z1);
            actorGetNodePos(gActivePlayerState->actor, 4, &x2, &y2, &z2);
            camSetFixedView(gActivePlayerState->camActor, x2, y2 + 8.0f, z2, (x2 - x1) + x2, (y2 - y1) + y2 + 5.0f, (z2 - z1) + z2, 1);
            gActivePlayerState->stateFlags |= 2;
            gCurrentActor->flags |= 0x400;
        } else {
            if (gActivePlayerState->stateFlags & 2) {
                gActivePlayerState->stateFlags &= ~2;
                camSetTargetScaled(gActivePlayerState->camActor, gActivePlayerState->actor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                if (gCurrentActor->state == 7) {
                    actorScriptStartByIndex(gCurrentActor, 0x84);
                }
            }
            gCurrentActor->flags &= ~0x400;
        }
    }
}

void func_806E9388(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gCurrentActor->state = 0x80;
        gCurrentActor->unk155 = 0;
        actorScriptStart(gCurrentActor, 0x316);
    }
}

void func_806E93F8(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gCurrentActor->state = 0x81;
        gCurrentActor->unk155 = 0;
        actorScriptStart(gCurrentActor, 0x316);
    }
}

void func_806E9468(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xA000) {
        gActivePlayerState->subTimer = D_807539EC[gCurrentCharacterIndex];
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->actionTimer = D_807539DC[gCurrentCharacterIndex];
        gCurrentActor->state = 0x7F;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unk155 = 1;
        if (gCurrentActor->speedY > 0.0f) {
            gCurrentActor->speedY = 0.0f;
        }
        actorScriptStart(gCurrentActor, 0x318);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
    }
}

extern s16 D_8075388C[];
extern s16 D_807538C8[];

s32 playerInputPostUpdate(void) {
    f32 diff;
    f32 lim;
    f32 t;
    u8 ret;
    s32 n;

    ret = 0;
    gActivePlayerState->unk24 = 0;
    n = 0x1E;
    if (gCurrentActor->contactFlags & 4) {
        t = gCurrentActor->speedY;
        if (t <= 0.0f) {
            if (-150.0f < t) {
                gCurrentActor->speedY = t;
            } else {
                gCurrentActor->speedY = -150.0f;
            }
            diff = gCurrentActor->waterY - gCurrentActor->y;
            if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 2) {
                n = 0x3C;
            }
            if (((f32)n < diff) && playerInputCanPerformFairySnap()) {
                playerStateQueueCallback(0x3E, 0, gCurrentPlayerIndex);
                playerClearCarriedItemState();
            } else if (gCurrentActor->contactFlags & 1) {
                if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
                    lim = D_8075386C[gCurrentCharacterIndex];
                } else {
                    lim = D_8075389C[gCurrentCharacterIndex];
                }
                if (lim < diff) {
                    playerStateQueueCallback(0x3D, 0, gCurrentPlayerIndex);
                    ret = 1;
                    playerClearCarriedItemState();
                }
            } else {
                if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
                    lim = D_8075388C[gCurrentCharacterIndex];
                } else {
                    lim = D_807538C8[gCurrentCharacterIndex];
                }
                if (lim < gCurrentActor->distToFloor + diff) {
                    playerStateQueueCallback(0x3D, 0, gCurrentPlayerIndex);
                    actorScriptStart(gCurrentActor, 0);
                    if (gActivePlayerState->sfxHandle) {
                        n_alSndpStop(gActivePlayerState->sfxHandle);
                    }
                    ret = 1;
                    playerClearCarriedItemState();
                }
            }
        }
    }
    return ret;
}

void func_806E9804(s16 callbackId) {
    if (flagGet(0x179, 0)) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4) {
            func_806E9D1C(callbackId, 0xB, 0);
        }
    }
}

void func_806E9874(void) {
    if (!(gGlobalOverlayFlags & 2) && (gPlayerCharacterId[gCurrentPlayerIndex] < 5)) {
        func_806E9804(6);
        gPlayerSlots[gCurrentPlayerIndex].fov = 45.0f;
    }
}

void func_806E98F8(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4)) {
        func_806E9874();
    }
}

void func_806E9964(PlayerState *ps) {
    Actor *a;
    s32 flag;

    a = gCurrentActor;
    flag = (a->state == 5) || (a->state == 0x65);
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4)) {
        if (flag) {
            func_806E9D1C(7, 3, 0);
        } else {
            func_806E9D1C(5, 3, 0);
        }
    } else {
        func_806EAB44(a, flag);
    }
    slotQueueCancel(6, 1);
    slotQueueCancel(0xC, 1);
    ps->stateFlags &= ~0x8000;
}

void func_806E9A5C(void) {
    if (!(gActivePlayerState->stateFlags & 0x8000) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 8)) {
        func_806E9964(gActivePlayerState);
    }
}

void func_806E9ACC(void) {
    if (!(gActivePlayerState->stateFlags & 0x8000) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4)) {
        func_806E9964(gActivePlayerState);
    }
}

void func_806E9B3C(void) {
    if (!(gActivePlayerState->stateFlags & 0x8000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4)) {
        func_806E9964(gActivePlayerState);
    }
}


void func_806E9BA8(s32 newState) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        if (!(gActivePlayerState->stateFlags & 0x8000)) {
            if (slotQueueGetValue(6, gCurrentPlayerIndex) > 0) {
                sfxPlayOnFreeSlot(0x263, 0x7FFF, 63.0f, 1.0f, 0xA, 0);
                gCurrentActor->state = newState;
                gCurrentActor->unk155 = 0;
                slotQueueAddValue(6, gCurrentPlayerIndex, -1);
                lightAdd(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camY, gPlayerSlots[gCurrentPlayerIndex].camZ, gPlayerSlots[gCurrentPlayerIndex].focusX, gPlayerSlots[gCurrentPlayerIndex].focusY, gPlayerSlots[gCurrentPlayerIndex].focusZ, 0.0f, 1, 0xFF, 0xFF, 0xFF);
            }
        }
    }
}

void func_806E9CDC(void) {
    func_806E9BA8(0x64);
}

void func_806E9CFC(void) {
    func_806E9BA8(0x65);
}


s32 func_806E9D1C(s16 callbackId, u8 param1, u8 param2) {
    if (((gPlayerCount < 2) || (gSplitScreenMode != 1)) && (gScreenFadeProgress == 0.0f) && (gCurrentActor->floorSlopeFactor == 0.0f)) {
        playerStateSetCallbackParameters(gCurrentPlayerIndex, param1, param2, 0);
        playerStateQueueCallback(callbackId, 0, gCurrentPlayerIndex);
        gCurrentActor->speedXZ = 0.0f;
        return 1;
    }
    return 0;
}


void playerInputHandleCUpCameraZoomIn(void) {
    CamState *state;
    s32 act;

    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) {
        state = gActivePlayerState->camActor->customState;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000)) {
            act = gCurrentActor->state;
            if (((act == 0x5D || act == 0x5E || act == 0x62) && !(gGlobalOverlayFlags & 0x80000000)) || act == 0x4E || act == 0x4F ||
                act == 0xD || act == 0xC) {
                func_806E9D1C(5, 3, 0);
            }
        }
    }
}




void func_806E9ECC(void) {
    CamState *state;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (gCurrentActor->contactFlags & 1)) {
        state = gActivePlayerState->camActor->customState;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000) && !(gGlobalOverlayFlags & 0x80000000)) {
            func_806E9D1C(5, 3, 1);
        }
    }
}

void playerInputHandleCUpMode7(void) {
    CamState *state;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) && (gCurrentActor->contactFlags & 1)) {
        state = gActivePlayerState->camActor->customState;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000) && !(gGlobalOverlayFlags & 0x80000000)) {
            func_806E9D1C(5, 3, 1);
        }
    }
}

void func_806EA04C(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) {
        func_806E9D1C(7, 3, 0);
    }
}


void playerInputCycleCameraZoom(void) {
    CamState *state;
    u8 max;
    s32 cur;

    state = gActivePlayerState->camActor->customState;
    if ((gGlobalOverlayFlags & 1) && !(gGlobalCutsceneFlags & 2)) {
        max = 2;
    } else {
        max = 3;
    }
    cur = state->unkEF;
    if ((cur != 0) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4) && ((state->unkEE == max) || (state->unkFC == 0))) {
        state->unkF0 = cur;
        if (cur < max) {
            state->unkEF = cur + 1;
        } else {
            state->unkEF = 1;
        }
        camSetZoomLevel(gActivePlayerState->camActor, state->unkEF);
        state->unkEE = state->unkEF;
        if ((state->unkEF != state->unkF0) && ((state->unk8 == 0) || (state->unk8 >= 0x96)) && (state->unkF3 != 2)) {
            sfxPlayOnFreeSlot(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        state->unkF1 = 0xB;
        state->unkF6 = 0xF;
    }
}

void playerInputCamRotateLeft(void) {
    CamState *state;

    state = gActivePlayerState->camActor->customState;
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (state->unkF1 < 3)) {
        state->unkB0 -= 0x2D;
        state->unkF1 = 0xB;
    }
}

void playerInputCamRotateRight(void) {
    CamState *state;

    state = gActivePlayerState->camActor->customState;
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && (state->unkF1 < 3)) {
        state->unkB0 += 0x2D;
        state->unkF1 = 0xB;
    }
}


f32 aimStickSpeedScale(void) {
    return (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) ? 0.2 : 1.0;
}

void cameraZoomIn(void) {
    f32 limit;
    f32 next;
    s32 buttons;

    buttons = gPlayerPadState[gCurrentPlayerIndex].heldButtons;
    if (!(buttons & 0x2000) && !(buttons & 2) && (gCurrentActor->state == 2)) {
        limit = (gCurrentMap == 0x22) ? 15.0 : 13.0;
        next = gPlayerSlots[gCurrentPlayerIndex].fov - 1.5f;
        if (limit < next) {
            gPlayerSlots[gCurrentPlayerIndex].fov = next;
            sfxPlayActorSound(gCurrentActor, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        gPlayerSlots[gCurrentPlayerIndex].fov = limit;
        sfxStopSlotSound(gCurrentActor, 0);
    }
}

void cameraZoomOut(void) {
    f32 next;
    s32 buttons;

    buttons = gPlayerPadState[gCurrentPlayerIndex].heldButtons;
    if (!(buttons & 0x2000) && !(buttons & 1) && (gCurrentActor->state == 2)) {
        next = gPlayerSlots[gCurrentPlayerIndex].fov + 1.5f;
        if (next < 45.0) {
            gPlayerSlots[gCurrentPlayerIndex].fov = next;
            sfxPlayActorSound(gCurrentActor, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        gPlayerSlots[gCurrentPlayerIndex].fov = 45.0f;
        sfxStopSlotSound(gCurrentActor, 0);
    }
}

void cameraZoomStopSound(void) {
    u16 buttons;

    buttons = gPlayerPadState[gCurrentPlayerIndex].heldButtons & 3;
    if ((buttons != 2) && (buttons != 1)) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
}


void playerInputPostUpdateFirstPerson(void) {
    if (playerInputPostUpdate()) {
        func_806EAB44(gCurrentActor, 1);
    }
}

void playerInputUpdateStickFirstPersonAim(void) {
    cameraZoomStopSound();
    playerInputPostUpdateFirstPerson();
}

void aimUpdateFromStick(void) {
    CamState *state;
    s16 *angle;
    f32 *dist;
    f32 scale;

    if (!(gActivePlayerState->stateFlags & 0x8000)) {
        state = gActivePlayerState->camActor->customState;
        angle = &state->unkB2;
        *angle = (f64)*angle - (((f64)aimStickSpeedScale() * ((f64)gPlayerPadState[gCurrentPlayerIndex].stickX * 0.08) * 4096.0) / 360.0);
        dist = &state->unkB8;
        scale = aimStickSpeedScale();
        *dist = ((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.04 * scale) + (f64)*dist;
        *angle &= 0xFFF;
        if ((f32)(state->unkBC + 0x32) < *dist) {
            *dist = state->unkBC + 0x32;
        } else if (*dist < (f32)(state->unkBC - 0x50)) {
            *dist = state->unkBC - 0x50;
        }
        gActivePlayerState->camActor->distToFloor = *dist;
        gCurrentActor->yaw = (state->unkB2 + 0x800) & 0xFFF;
    }
}

void playerInputHandleAButtonAimRight(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x8000) {
        func_806EAB44(gCurrentActor, 0);
    }
}

void playerInputHandleBButtonAimLeft(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x4000) {
        func_806EAB44(gCurrentActor, 0);
    }
}

void playerInputHandleAButtonAimUp(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x8000) {
        func_806EAB44(gCurrentActor, 1);
    }
}

void playerInputHandleBButtonAimDown(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x4000) {
        func_806EAB44(gCurrentActor, 1);
    }
}

void func_806EA958(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 8) {
        func_806EAB44(gCurrentActor, 0);
    }
}


void func_806EA9B4(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4)) {
        func_806E9874();
        return;
    }
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4) {
        func_806EAB44(gCurrentActor, 0);
    }
}

void func_806EAA44(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 8) {
        func_806EAB44(gCurrentActor, 1);
    }
}

void func_806EAAA0(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4) && !(gGlobalOverlayFlags & 2)) {
        func_806E9804(8);
        return;
    }
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4) {
        func_806EAB44(gCurrentActor, 1);
    }
}


void func_806EAB44(Actor *actor, u8 isFirstPerson) {
    PlayerState *state;

    state = actor->customState;
    if (!(state->stateFlags2 & 0x10)) {
        sfxPlayOnFreeSlot(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
    if (isFirstPerson) {
        if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
            if (actor->waterY - actor->y < 20.0f) {
                actor->state = 0x7E;
                actor->unk155 = 0;
            } else {
                actor->state = 0x7F;
                actor->unk155 = 0;
            }
        } else {
            actor->state = 0x4F;
            actor->unk155 = 3;
        }
    } else {
        actor->state = 1;
        actor->unk155 = 0;
        playerResumeLocomotion(actor);
        if (actor->state == 0xC) {
            actor->unk155 = 0xA;
        }
    }
    if (state->gunDrawn) {
        playerKongPlaySoundByState(actor);
    } else {
        playerKongStopSoundByState(actor);
    }
    actor->speedXZ = 0.0f;
    actor->yaw = func_8062773C(state->camActor);
}

typedef struct G32Inner {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ u8 unkE;
} G32Inner;

typedef struct G32Mid {
    /* 0x000 */ u8 pad0[0x154];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ G32Inner *unk178;
} G32Mid;


void func_806EAC8C(void) {
    G32Inner *inner;

    inner = ((G32Mid *)gActivePlayerState->actor)->unk178;
    if (inner->unkE == 5) {
        inner->unkE = 10;
    }
}

void func_806EACBC(void) {
    G32Inner *inner;

    inner = ((G32Mid *)gActivePlayerState->actor)->unk178;
    if (inner->unkE == 5) {
        inner->unkE = 0xF;
    }
}

void func_806EACEC(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.unk280;
    }
    if (gCurrentActor->contactFlags & 1) {
        if ((gScheduler.unk280 - gActivePlayerState->jumpTimer) < 0xF) {
            playerSetTerminalVelocity5B0();
            gCurrentActor->speedY = D_807535CC[gCurrentCharacterIndex];
            gActivePlayerState->unk50 = 0;
            gActivePlayerState->airTimer = 0;
            gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x309, 0xFF, 0x7F, 0);
        }
    }
}

void func_806EAE04(void) {
    Actor *mid;

    mid = gActivePlayerState->actor;
    if (mid->state == 0) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
            mid->state = 1;
        }
    }
}

void func_806EAE60(void) {
    PadInputState *pad;
    s32 v;

    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if ((pad->stickX >= 0x29) || (pad->stickY >= 0x29)) {
        if (gActivePlayerState->unk108 != 0.0f) {
            gActivePlayerState->unk108 = 0.0f;
            v = gActivePlayerState->unk200 - 5;
            if (v <= 0) {
                gActivePlayerState->unk200 = 1;
            } else {
                gActivePlayerState->unk200 = v;
            }
            return;
        }
    }
    if ((pad->stickX < -0x28) || (pad->stickY < -0x28)) {
        if (gActivePlayerState->unk108 == 0.0f) {
            gActivePlayerState->unk108 = 1.0f;
            v = gActivePlayerState->unk200 - 5;
            if (v <= 0) {
                gActivePlayerState->unk200 = 1;
            } else {
                gActivePlayerState->unk200 = v;
            }
        }
    }
}

void func_806EAF6C(void) {
    Actor *mid;

    mid = gActivePlayerState->actor;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        switch (mid->state) {
            case 2:
                mid->state = 4;
                mid->unk155 = 0;
                break;
            case 5:
                mid->unk155++;
                break;
        }
    }
}

void playerInputHandlerNoop3(void) {
}

void playerInputHandleCUpRotate120(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) {
        gCurrentActor->speedY = 0.0f;
    } else {
        gCurrentActor->speedY = 120.0f;
    }
}

void playerInputHandleCDownRotateMinus120(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0xC) {
        gCurrentActor->speedY = 0.0f;
    } else {
        gCurrentActor->speedY = -120.0f;
    }
}

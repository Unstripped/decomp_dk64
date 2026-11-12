#include "common.h"
#include "actor.h"
#include "sched.h"
#include "text.h"
#include "proto/boot/3630.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/103AB0.h"
#include "proto/global/119370.h"
#include "proto/global/166A0.h"
#include "proto/global/450.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/A7710.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern PlayerState *gActivePlayerState;

typedef struct CountdownTimerState {
    /* 0x00 */ u64 startTime;
    /* 0x08 */ u32 elapsedSecs;
    /* 0x0C */ u32 totalSecs;
    /* 0x10 */ u8 textId;
} CountdownTimerState;

u64 gHudCountdownSavedElapsed;
u8 gHudCountdownHundredths;

void hudSpawnCountdownTimer(s16 x, s16 y, u8 seconds) {
    actorSpawn(0xB0, 0);
    if (x & 0x8000) {
        seconds--;
        gSpawnedActor->unk15F = 0xB;
    } else {
        gSpawnedActor->unk15F = 6;
    }
    x &= 0x7FFF;
    gCurrentActor->parentActor = gSpawnedActor;
    gActivePlayerState->countdownTimer = gSpawnedActor;
    ((CountdownTimerState *)gSpawnedActor->customState)->totalSecs = seconds;
    gSpawnedActor->x = x;
    gSpawnedActor->y = y;
    gSpawnedActor->state = 1;
    gSpawnedActor->alpha = 0;
}

void hudCountdownTimerStart(Actor *actor) {
    actor->state = 2;
    actor->unk155 = 0;
    actor->alpha = 0xFF;
}

void hudCountdownTimerHold(Actor *actor) {
    if (actor != NULL) {
        actor->state = 1;
        actor->unk155 = 0;
    }
}

void hudCountdownTimerSaveElapsed(Actor *actor) {
    gHudCountdownSavedElapsed = osGetTime() - ((CountdownTimerState *)actor->customState)->startTime;
}

void hudCountdownTimerResume(Actor *actor) {
    actor->state = 3;
    actor->unk155 = 0;
}

extern Gfx D_1000118;
extern Mtx D_2000180;
extern Gfx D_8071FC58;
extern PlayerStruct *gPlayerSlots;

Gfx *renderActorSpriteCallback(Gfx *gfx, Actor *actor) {
    CountdownTimerState *timer;
    u8 pad[0x18];
    f32 angle;
    u8 pad2[8];
    f32 sinAngle;
    s32 animMode;
    s32 offset;

    timer = actor->customState;
    if (hudCanRender() != 0) {
        gSPDisplayList(gfx++, &D_1000118);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, actor->alpha);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        animMode = actor->unk15F;
        if (animMode == 0xB) {
            gfx = func_8070068C(gfx);
            gfx = textDrawStringVtx(gfx, 0x86, actor->x * 4.0f, gPlayerSlots->rect[3] * 4 - 0x3C,
                                    gfxResourceFindById(timer->textId)->text, 1);
        } else {
            angle = 6.28318548202514648 - 2.0 * actor->splineT;
            offset = 8;
            if (actor->yawSpeed == 3) {
                offset = -7;
            }
            gfx = textDrawAnimated(gfx, timer->textId, animMode, actor->x + offset, actor->y + 5.0f, 0.0f, 1.0f);
            if (actor->state == 2) {
                gfx = func_8070068C(gfx);
                effectEnableFade();
                sinAngle = sinApprox(angle);
                effectCreateAtPosition(&D_8071FC58, 0.5f, sinAngle * 40.0 + (40.0f + actor->x),
                                       cosApprox(angle) * 25.0 + actor->y, 0.0f);
            }
        }
    }
    return gfx;
}

extern u64 D_807445B0;
extern u64 gCamPathTimeDelta;
extern s32 gCurrentMap;

void hudCountdownTimerUpdate(void) {
    f32 nextBeepAngle;
    f32 angle;
    u8 text[0x20];
    CountdownTimerState *timer;
    s32 pad;
    u64 usec;
    s32 secsLeft;

    timer = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        if (gCurrentActor->unk15F == 6) {
            _sprintf(text, "%.2d", timer->totalSecs);
        } else {
            _sprintf(text, "%.2d:%.2d:00", timer->totalSecs / 60, timer->totalSecs % 60);
        }
        timer->textId = gfxResourceCreate(gCurrentActor->unk15F == 0xB ? 6 : 3, text, gCurrentActor->unk15F, 0.0f, 0.0f, 0.0f);
    }
    if (gCurrentActor->state == 3) {
        timer->startTime = osGetTime() - gHudCountdownSavedElapsed;
        gCurrentActor->state = 2;
        gCurrentActor->unk155 = 1;
    }
    timer->startTime += D_807445B0;
    if (gCurrentActor->unk15F == 0xB) {
        timer->startTime += gCamPathTimeDelta;
    }
    usec = OS_CYCLES_TO_USEC(osGetTime() - timer->startTime);
    timer->elapsedSecs = usec / 1000000;
    if (gCamPathTimeDelta == 0) {
        gHudCountdownHundredths = usec / 10000 % 100;
    }
    nextBeepAngle = (s32)((func_806FDA8C(timer->textId) - 1.5707964f) / 3.1415927f) * 3.1415927f + 3.1415927f + 1.5707964f;
    angle = usec / 10000.0 / 100.0 * 3.1415927410125732 + 1.5707963705062866;
    func_806FDAB8(timer->textId, 0.0f);
    secsLeft = timer->totalSecs - timer->elapsedSecs;
    switch (gCurrentActor->state) {
    case 1:
        if (gCurrentActor->alpha < 0xFF) {
            if (gCurrentActor->alpha + 3 >= 0x100) {
                gCurrentActor->alpha = 0xFF;
            } else {
                gCurrentActor->alpha += 3;
            }
        }
        func_806FDAB8(timer->textId, 1.5707964f);
        gCurrentActor->yawSpeed = 0;
        break;
    case 4:
        gCurrentActor->state = 2;
        gCurrentActor->unk155 = 0xFF;
        // fallthrough
    case 2:
        if (gCurrentActor->unk155 == 0) {
            gCurrentActor->unk155++;
            timer->startTime = osGetTime();
            timer->elapsedSecs = 0;
            angle = 1.5707964f;
        }
        secsLeft = timer->totalSecs - timer->elapsedSecs;
        if (secsLeft >= 0) {
            func_806FDAB8(timer->textId, angle < 0.0f ? 0.0f : angle);
            gCurrentActor->splineT = angle < 0.0f ? 0.0f : angle;
            if (nextBeepAngle <= angle) {
                if (timer->elapsedSecs >= timer->totalSecs
                    && (gCurrentActor->unk15F == 6 || timer->totalSecs < timer->elapsedSecs || gHudCountdownHundredths >= 91)) {
                    gCurrentActor->state = 5;
                    gCurrentActor->unk155 = 0;
                } else if (gCurrentActor->unk15F == 6) {
                    if ((s32)(nextBeepAngle / 3.1415927f) & 1) {
                        sfxPlayOnFreeSlot(0x8E, 0x58EF, 63.0f, 1.0f, 5, 0);
                    } else {
                        sfxPlayOnFreeSlot(0x8F, 0x58EF, 63.0f, 1.0f, 5, 0);
                    }
                }
                if (secsLeft == 10) {
                    gCurrentActor->state = 4;
                }
            }
            if (gCurrentActor->unk15F == 6) {
                _sprintf(text, "%.2d", secsLeft);
            } else if (gCurrentActor->state != 5) {
                _sprintf(text, "%.2d:%.2d:%.2d", secsLeft / 60, secsLeft % 60, 99 - gHudCountdownHundredths);
            } else {
                _sprintf(text, "00:00:00");
            }
            gCurrentActor->yawSpeed = strlen(text);
            gfxResourceSetString(timer->textId, text);
        } else {
            gCurrentActor->state = 5;
            gCurrentActor->unk155 = 0;
            gfxResourceSetString(timer->textId, "00:00:00");
        }
        break;
    case 5:
        switch (gCurrentMap) {
        case 0x35:
        case 0x49:
        case 0x9B:
        case 0x9C:
        case 0x9D:
        case 0x9E:
        case 0x9F:
        case 0xA0:
        case 0xA1:
        case 0xA2:
            switch (gCurrentActor->unk155) {
            case 0:
            case 7:
            case 14:
            case 21:
            case 28:
            case 35:
            case 42:
                sfxPlayOnFreeSlot(0x3BD, 0x7FFF, 63.0f, 1.15f, 1, 0x80);
                break;
            }
            gCurrentActor->unk155++;
            break;
        case 0x13:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0xCB:
        case 0xCC:
        case 0xCD:
        case 0xCE:
        case 0xCF:
            break;
        default:
            if (gCurrentActor->unk155 == 0) {
                sfxPlayOnFreeSlot(0x1BB, 0x7FFF, 63.0f, 1.0f, 0, 0);
                gCurrentActor->unk155++;
            }
            break;
        }
        gCurrentActor->yawSpeed = 0;
        if (secsLeft <= 0 && secsLeft >= -2) {
            func_806FDAB8(timer->textId, ((randomNonNegative() >> 15) % 180) / 180.0 * 3.1415927410125732 + 1.5707963705062866);
        }
        break;
    }
    renderCallbacksRegister(renderActorSpriteCallback, gCurrentActor, 7);
}

void func_806A36F4(void) {
}

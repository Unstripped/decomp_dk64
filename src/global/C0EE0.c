#include "common.h"
#include "actor.h"
#include "proto/global/100180.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/A7710.h"
#include "proto/global/C0EE0.h"
#include "proto/global/CEAE0.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

typedef struct BC1E0_State {
    /* 0x00 */ f32 progress;
    /* 0x04 */ f32 step;
    /* 0x08 */ f32 startX;
    /* 0x0C */ f32 startY;
    /* 0x10 */ f32 startZ;
    /* 0x14 */ f32 targetX;
    /* 0x18 */ f32 targetY;
    /* 0x1C */ f32 targetZ;
    /* 0x20 */ f32 gravity;
    /* 0x24 */ f32 homeX;
    /* 0x28 */ f32 homeY;
    /* 0x2C */ f32 homeZ;
    /* 0x30 */ f32 homeScaleY;
    /* 0x34 */ s16 delay;
    /* 0x36 */ s8 gridX;
    /* 0x37 */ s8 gridY;
    /* 0x38 */ u8 state;
    /* 0x39 */ u8 subState;
} BC1E0_State;

typedef struct BC1E0_Actor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BC1E0_State *gridState;
} BC1E0_Actor;

extern s8 D_80750650;
extern s8 D_807FC8C0[16];
extern u16 D_807ECD58;
extern u16 D_807ECD60;

void enemyGridStateStep(void) {
    f32 roll;
    f32 old;
    f32 a;
    f32 t;
    f32 b;
    f32 targetScaleY;
    s16 i;
    s16 dist;
    BC1E0_State *st;
    AnimSlot *obj;
    s32 j;
    s32 dx;
    s32 dy;
    s16 best;
    s16 n;
    s8 cand[16];
    s16 ones;
    s16 zeros;
    s8 cell;

    st = ((BC1E0_Actor *)gCurrentActor)->gridState;
    obj = gCurrentActor->sub4->model;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        st->step = 0.0f;
        func_806BD0CC();
        gCurrentActor->alpha = 0x80;
        gCurrentActor->flags &= ~0x8000;
        st->homeX = gCurrentActor->x;
        st->homeY = gCurrentActor->y;
        st->homeZ = gCurrentActor->z;
        st->homeScaleY = gCurrentActor->sub4->scaleY;
        currentActorClearFlag();
    }
    switch (st->state) {
    case 0:
        if (flagGet(0x10F, 0) == 0) {
            if ((gCurrentActor->x - gPrimaryPlayerActor->x) * (gCurrentActor->x - gPrimaryPlayerActor->x) + (gCurrentActor->z - gPrimaryPlayerActor->z) * (gCurrentActor->z - gPrimaryPlayerActor->z) < 14400.0) {
                camStartPath(gCurrentActor, 0, 1);
                st->subState = 0;
                st->state = 1;
            }
        }
        break;
    case 1:
        if (currentActorTestClearFlag() != 0) {
            st->state = 2;
        }
        break;
    case 2:
        switch (st->subState) {
        case 0:
            renderCallbacksRegister(func_806BCF98, gCurrentActor, 5);
            if ((D_807ECD58 & 0x8000) && !(D_807ECD60 & 0x8000)) {
                camResumePath();
                st->subState = 1;
                gPrimaryPlayerActor->state = 0xC;
                gPrimaryPlayerActor->unk155 = 0;
                playerResumeLocomotion(gPrimaryPlayerActor);
            }
            if ((D_807ECD58 & 0x4000) && !(D_807ECD60 & 0x4000)) {
                camResumePath();
                st->subState = 2;
                gPrimaryPlayerActor->state = 0xC;
                gPrimaryPlayerActor->unk155 = 0;
                playerResumeLocomotion(gPrimaryPlayerActor);
            }
            break;
        case 1:
            camStartPath(gCurrentActor, 1, 1);
            st->subState = 3;
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                D_80750650 = 1;
                st->state = 3;
                st->step = 0.025f;
                st->progress = 0.0f;
                st->startX = gCurrentActor->x;
                st->startY = gCurrentActor->y;
                st->startZ = gCurrentActor->z;
                st->targetX = 294.0f;
                st->targetY = 0.0f;
                st->targetZ = 359.0f;
                st->gridX = 3;
                st->gridY = 0;
                st->gravity = -500.0f;
                actorScriptStart(gCurrentActor, 0x31C);
                hudSpawnCountdownTimer(0xDC, 0x2A, 0x3C);
                flagSet(0x30, 1, 2);
                sfxAllocateChannel(0x78, 1.0f);
                hudCountdownTimerStart(gCurrentActor->parentActor);
            }
            break;
        case 2:
            if (camIsCutsceneActive() == 0) {
                if ((gCurrentActor->x - gPrimaryPlayerActor->x) * (gCurrentActor->x - gPrimaryPlayerActor->x) + (gCurrentActor->z - gPrimaryPlayerActor->z) * (gCurrentActor->z - gPrimaryPlayerActor->z) > 25600.0) {
                    st->subState = 0;
                    st->state = 0;
                }
            }
            break;
        }
        break;
    case 3:
    case 4:
        if (st->step == 0.0f) {
            if (st->state == 3) {
                st->state = 4;
            }
            if (gCurrentActor->parentActor != NULL && gCurrentActor->parentActor->state == 5) {
                ones = 0;
                zeros = 0;
                for (j = 0; &D_807FC8C0[j] < &D_807FC8C0[16]; j++) { // FAKE: pointer-compare bound keeps sltu+bnezl (j < 16 gives bnel v1,a0)
                    if (D_807FC8C0[j] == 1) {
                        ones++;
                    }
                    if (D_807FC8C0[j] == 0) {
                        zeros++;
                    }
                }
                flagSet(0x30, 0, 2);
                actorScriptStart(gCurrentActor, 0x31C);
                D_80750650 = 1;
                if (ones < zeros) {
                    st->state = 6;
                } else {
                    st->state = 7;
                }
                st->step = 0.0125f;
                st->progress = 0.0f;
                st->startX = gCurrentActor->x;
                st->startY = 0.0f;
                st->startZ = gCurrentActor->z;
                st->targetX = st->homeX;
                st->targetY = st->homeY;
                st->targetZ = st->homeZ;
                st->gravity = -500.0f;
                st->delay = 0x1E;
            } else {
                actorScriptStart(gCurrentActor, 0);
                D_80750650 = 0;
                best = 4;
                n = 0;
                for (i = 0; i < 16; i++) {
                    if (D_807FC8C0[i] == 0 || D_807FC8C0[i] == -1) {
                        dx = (s16)((s16)(i & 3) - st->gridX);  // FAKE: redundant operand narrowing burns 2 ring temps (as1 deletes it)
                        dy = (s16)((s16)(i >> 2) - st->gridY);  // FAKE: redundant operand narrowing burns 2 ring temps (as1 deletes it)
                        if (dx > 0) {
                            dist = dx;
                        } else {
                            dist = -dx;
                        }
                        if (dist < (dy > 0 ? dy : -dy)) {
                            if (dy > 0) {
                                dist = dy;
                            } else {
                                dist = -dy;
                            }
                        }
                        if (dist > 0) {
                            if (dist < best) {
                                cand[0] = i;
                                n = 1;
                                best = dist;
                            } else if (dist == best) {
                                cand[n++] = i;
                            }
                        }
                    }
                }
                if (n > 0) {
                    roll = randomFloat();
                    cell = cand[(s32)(roll * (n - 1))];
                    dx = (s16)(cell & 3) - st->gridX;  // FAKE: redundant operand narrowing
                    dy = (u16)(cell >> 2) - st->gridY;  // FAKE: redundant operand narrowing
                    dx = (s16)dx;  // FAKE: s32 dx/dy with deferred s16 narrowing orders ugen ring temps (cell >> 2 before the dx sll)
                    dy = (s16)dy;  // FAKE: see dx above
                    if (dx < -1) {
                        dx = -1;
                        if (ones == 0) {}  // FAKE: dead test (with the cell test below) keeps lb gridX/gridY in t0/t1, removal gives v1/a3
                    }
                    if (dx >= 2) {
                        dx = 1;
                    }
                    if (dy < -1) {
                        dy = -1;
                        if (cell & 3) {}  // FAKE: dead test, see the ones test above
                    }
                    if (dy >= 2) {
                        dy = 1;
                    }
                    st->gridX += dx;
                    st->gridY += dy;
                }
                st->step = 0.01369863f;
                st->progress = 0.0f;
                st->startX = st->targetX;
                st->startY = 0.0f;
                st->startZ = st->targetZ;
                st->targetX = st->gridX * -11.666666666666666 + 329.0 + st->gridY * -28.666666666666668;
                st->targetY = 0.0f;
                st->targetZ = st->gridX * 28.333333333333332 + 274.0 + st->gridY * -11.333333333333334;
                st->gravity = -250.0f;
            }
        }
        break;
    case 6:
        if (st->delay == 0 && st->step == 0.0f) {
            sfxStopChannel(0x78, 1);
            sfxAllocateChannel(0x56, 1.0f);
            actorScriptStart(gCurrentActor, 0x31C);
            actorDespawn(gCurrentActor->parentActor);
            camStartPath(gCurrentActor, 2, 1);
            st->state = 8;
        }
        break;
    case 8:
        if (currentActorTestClearFlag() != 0) {
            func_806BD0CC();
            if (flagGet(0x10F, 0) == 0) {
                csModelStateSetFirstByte(0x10, 0xA);
            }
            st->state = 0xA;
            sfxStopChannel(0x56, 1);
            sfxAllocateChannel(0x67, 1.0f);
        }
        break;
    case 10:
        break;
    case 7:
        if (st->delay == 0 && st->step == 0.0f) {
            actorDespawn(gCurrentActor->parentActor);
            actorScriptStart(gCurrentActor, 0x31C);
            camStartPath(gCurrentActor, 3, 1);
            st->state = 9;
            sfxStopChannel(0x78, 1);
            sfxAllocateChannel(0x57, 1.0f);
        }
        break;
    case 9:
        if (currentActorTestClearFlag() != 0) {
            sfxStopChannel(0x57, 1);
            sfxAllocateChannel(0x67, 1.0f);
            func_806BD0CC();
            st->subState = 0;
            st->state = 2;
        }
        break;
    default:
        break;
    }
    gCurrentActor->flags |= 0x400;
    gCurrentActor->eyeHeight = 0x14;
    st->delay--;
    if (st->delay < 0) {
        st->delay = 0;
    }
    targetScaleY = st->homeScaleY;
    if (st->step != 0.0f && st->delay == 0) {
        a = st->step;
        old = st->progress;
        st->progress = old + a;
        if (D_80750650 == 0) {
            if (old < 0.63f && st->progress >= 0.63f) {
                csModelStateSetByte(st->gridX + st->gridY * 4, 1, 1);
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x361, 0xFF, 0x7F, 0xA);
            }
        } else {
            targetScaleY += (st->progress - 0.5f) * 0.25f;
        }
        if (st->progress >= 1.0) {
            st->progress = 0;
            st->step = 0;
            gCurrentActor->x = st->targetX;
            gCurrentActor->y = st->targetY;
            gCurrentActor->z = st->targetZ;
        } else {
            t = st->progress;
            if (D_80750650 == 0) {
                t = 2.0 * t;
                if (t > 1.0) {
                    t = 1.0f;
                }
            }
            gCurrentActor->x = st->startX + t * (st->targetX - st->startX);
            gCurrentActor->z = st->startZ + t * (st->targetZ - st->startZ);
            if (D_80750650 == 0) {
                gCurrentActor->y = st->startY + t * (st->targetY - st->startY);
            } else {
                t = st->gravity;
                old = st->startY;
                a = st->progress;
                b = (st->targetY - st->startY) - t * 0.5;
                gCurrentActor->y = old + (b * a + a * a * t * 0.5);
            }
        }
        if (D_80750650 == 0 && obj != NULL && st->progress != 0.0f) {
            if (obj->animId != 0x5C3) {
                controllerAnimSetStateIfChanged(gCurrentActor, 0x5C3, 0.0f, 0.0f);
            }
            controllerApplyMotionWindow(gCurrentActor, obj, st->progress * 40.0f);
        }
    }
    gCurrentActor->sub4->scaleY += (targetScaleY - gCurrentActor->sub4->scaleY) * 0.25f;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern Gfx D_1000118[];
extern Mtx D_2000180;

Gfx *func_806BCF98(Gfx *dl, Actor *actor) {
    gSPDisplayList(dl++, D_1000118);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(dl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gSPMatrix(dl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    dl = textDrawStringVtx(dl, 1, 0x208, 0xC8, "q YES", 1);
    return textDrawStringVtx(dl, 1, 0x208, 0x12C, "b NO", 1);
}

void func_806BD094(s16 idx, s8 val) {
    if (idx >= 0 && idx < 0x10) {
        D_807FC8C0[idx] = val;
    }
}


void func_806BD0CC(void) {
    s32 i;

    flagSet(0x30, 0, 2);
    for (i = 0; i < 0x10; i++) {
        D_807FC8C0[i] = -1;
        csModelStateSetFirstByte(i, 0);
    }
    D_807FC8C0[5] = 0;
    D_807FC8C0[6] = 1;
    D_807FC8C0[9] = 1;
    D_807FC8C0[0xA] = 0;
}

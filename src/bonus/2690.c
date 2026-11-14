#include "common.h"
#include "actor.h"
#define PROTO_SKIP_func_806FDAB8 // FAKE: callee prototype steer
#include "proto/bonus/12A0.h"
#include "proto/bonus/2690.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/131B0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/A7710.h"
#include "proto/global/C4620.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"

typedef struct BonusShooterState {
    s16 phase;
    char pad2[2];
    struct EffectNode *ammoIcons[5];
    u8 ammoIconSlide[5];
    char pad1D;
    s16 crosshairX;
    s16 crosshairY;
    u8 aimSlot;
    u8 ammoCount;
    u8 unk24;
    u8 unk25;
    u8 showCrosshair;
} BonusShooterState;
// Actor storage beyond the 0x178-byte Actor view (bonus actors keep a second payload pointer here).
typedef struct BonusActorExt {
    Actor actor;
    void *gameState;
    s16 *unk17C;
} BonusActorExt;

extern Actor *gCurrentActor;


extern PadInputState gPlayerPadState[];
struct BonusTargetGameState;
typedef struct BonusTargetState {
    struct BonusTargetGameState *game;
    u32 lastFrame;
    u8 targetType;
    u8 slot;
    char padA[7];
    u8 unk11;
    char pad12[0xA];
    u8 unk1C;
} BonusTargetState;


typedef struct BonusTargetGameState {
    Actor *targets[6];
    char pad18[3];
    u8 unk1B;
    u8 unk1C;
    char pad1D[3];
    s16 shownCount;
    s16 targetsLeft;
    u8 rollTimer;
    u8 counterTextId;
    char pad26;
    u8 spawnThreshold;
    u8 typeThreshold;
    u8 timeLimit;
    char pad2A[2];
    f32 targetAnimSpeed;
} BonusTargetGameState;
typedef struct {
    Actor *game;
    u8 slot;
} LightFlashTargetState;

extern s16 D_8002D900;

void func_806FDAB8(u8, f32);  // FAKE: callee prototype steer

extern u8 D_1000118[];
extern u8 D_2000180[];
extern u8 D_20000C0[];
extern u8 gCurrentPlayerIndex;
extern s16 D_8002D8C8[]; // bonusLightFlashSpawnTargets spawn ids (6)
extern s16 D_8002D8D4[];
extern s16 D_8002D8E0[];
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern f32 D_8002D90C;
extern u8 D_8071FFD4[];

extern Actor *gSpawnedActor;

Gfx *bonusRenderCrosshair(Gfx *gdl, Actor *actor) {
    BonusShooterState *bonusExt = actor->customState;
    s16 crosshairX = bonusExt->crosshairX;
    s16 crosshairY = bonusExt->crosshairY;
    s32 pad;

    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, D_1000118);
    gSPMatrix(gdl++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX - 0x34, crosshairY - 0x34, 3.2f, 3.2f, 0xE1, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX + 0x34, crosshairY - 0x34, 3.2f, 3.2f, 0x13B, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX + 0x34, crosshairY + 0x34, 3.2f, 3.2f, 0x2D, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX - 0x34, crosshairY + 0x34, 3.2f, 3.2f, 0x87, 0.0f);
    return gdl;
}

Gfx *bonusRenderTargetGameHud(Gfx *gdl, Actor *actor) {
    BonusShooterState *bonusExt = actor->customState;
    BonusTargetGameState *targetExt = ((BonusActorExt *)actor)->gameState;
    s32 pad1[4];
    u8 *textStr;
    s32 pad2[6];
    s32 textX;
    s32 pad3[4];
    s32 textX2;

    if (actor->state == 0) {
        if (bonusExt->showCrosshair != 0) {
            gdl = bonusRenderCrosshair(gdl, actor);
        }
    }
    gSPDisplayList(gdl++, D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (actor->state != 1) {
        gdl = hudDrawRollingCounter(textDrawAnimated(gdl, targetExt->counterTextId, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &targetExt->shownCount, targetExt->targetsLeft, &targetExt->rollTimer);
    }
    if (bonusExt->unk25 != 0) {
        textX = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 6, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk25);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX << 2, (gScreenHeight - textGetFontHeight(1)) * 2, textStr, 1);
        bonusExt->unk25 -= (bonusExt->unk25 < 8) ? bonusExt->unk25 : 8;
    }
    if (bonusExt->unk24 != 0) {
        textX2 = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 8, 1);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk24);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX2 -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX2 << 2, (textGetFontHeight(1) + gScreenHeight) * 2, textStr, 1);
        bonusExt->unk24 -= (bonusExt->unk24 < 8) ? bonusExt->unk24 : 8;
    }
    return gdl;
}

// customState of a Turtle Trouble turtle (actor 0x12D), riding node 1 of its snake.
typedef struct TurtleTroubleTurtle {
    Actor *snake;
    u8 fallen;
    u8 warned;
    u8 slot;
    char pad7;
    s16 labelText;
    char padA[2];
    f32 fallSpeed;
} TurtleTroubleTurtle;
// customState of a Turtle Trouble snake (actor 0x12C).
typedef struct TurtleTroubleSnake {
    Actor *game;
    Actor *turtle;
    f32 spinTarget;
    f32 spinSpeed;
    s8 slowDelay;
    u8 slowDelayStart;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    u8 hitTimer;
} TurtleTroubleSnake;
// Turtle Trouble game state (the game actor's second component at 0x178).
typedef struct TurtleTroubleGameState {
    Actor *snakes[6];
    char pad18[2];
    u8 timeLimit;
    u8 slowDelayMin;
    u8 slowDelayMax;
    char pad1D[3];
    f32 spinDecay;
} TurtleTroubleGameState;

Gfx *bonusRenderPopupGameHud(Gfx *gdl, Actor *actor) {
    BonusShooterState *bonusExt = actor->customState;
    TurtleTroubleGameState *game = ((BonusActorExt *)actor)->gameState;
    s32 hasSetupGfx = 0;
    s32 textX;
    u8 *textStr;
    s32 i;
    Actor *turtleActor;
    TurtleTroubleTurtle *turtle;
    Actor *snakeActor;
    TurtleTroubleSnake *snake;

    if (actor->state == 0) {
        if (bonusExt->showCrosshair != 0) {
            gdl = bonusRenderCrosshair(gdl, actor);
        }
    }
    if (bonusExt->unk25 != 0) {
        textX = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 6, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk25);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX << 2, (gScreenHeight - textGetFontHeight(1)) * 2, textStr, 1);
        bonusExt->unk25 -= (bonusExt->unk25 < 8) ? bonusExt->unk25 : 8;
    }
    if (bonusExt->unk24 != 0) {
        textX = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 7, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk24);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX << 2, (textGetFontHeight(1) + gScreenHeight) * 2, textStr, 1);
        bonusExt->unk24 -= (bonusExt->unk24 < 8) ? bonusExt->unk24 : 8;
    }
    for (i = 0; i < 6; i++) {
        snakeActor = game->snakes[i];
        snake = snakeActor->customState;
        turtleActor = snake->turtle;
        turtle = turtleActor->customState;
        if (turtle->warned != 0 && actor->state == 0) {
            if (turtle->labelText < 0) {
                turtle->labelText = gfxResourceCreate(1, textTableGetString(0x1A, 9, 1), 9, turtleActor->x * 0.25, turtleActor->y * 0.25, turtleActor->z * 0.25);
            }
            if (hasSetupGfx == 0) {
                gSPDisplayList(gdl++, D_1000118);
                gDPPipeSync(gdl++);
                gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
                gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                gSPSetGeometryMode(gdl++, G_SHADE | G_SHADING_SMOOTH);
                gDPSetCycleType(gdl++, G_CYC_1CYCLE);
                gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                hasSetupGfx = 1;
            }
            gdl = textDrawAnimated(gdl, turtle->labelText, 9, turtleActor->x, turtleActor->y + 20.0f, turtleActor->z, 0.1f);
        } else if (turtle->labelText >= 0) {
            gfxResourceFree(turtle->labelText);
            turtle->labelText = -1;
        }
    }
    return gdl;
}

void bonusSpawnTarget(s16 x, s16 y, s16 z, u8 slotIndex, BonusTargetGameState *gameCtx) {
    u8 targetType;
    BonusTargetState *targetExt;

    if (gameCtx->typeThreshold < ((randomNonNegative() >> 0xF) % 100)) {
        targetType = 1;
    } else {
        targetType = 0;
    }
    if (actorSpawn(0xBA, targetType ? 0x32 : 0x33) != 0) {
        targetExt = gSpawnedActor->customState;
        actorScriptStart(gSpawnedActor, targetType ? 0x211 : 0x20F);
        scriptSetActorRampTarget(gSpawnedActor, gameCtx->targetAnimSpeed, 0.0f);
        gSpawnedActor->x = x;
        gSpawnedActor->y = y - 0x19;
        gSpawnedActor->z = z;
        gSpawnedActor->yaw = 0xC00;
        targetExt->slot = slotIndex;
        targetExt->targetType = targetType;
        targetExt->game = gameCtx;
        gameCtx->targets[slotIndex] = gSpawnedActor;
    }
}

void bonusDespawnTarget(BonusTargetState *targetExt, BonusTargetGameState *gameCtx) {
    gameCtx->targets[targetExt->slot] = NULL;
    actorDespawn(gCurrentActor);
}

void bonusResetAmmo(BonusShooterState *ammo) {
    s16 i;
    s16 y;
    y = 0x118;
    for (i = 0; i < 5; i++) {
        if (ammo->ammoIcons[i] != NULL) {
            effectFreeAndUnlink(ammo->ammoIcons[i]);
        }
        ammo->ammoIconSlide[i] = 0;
        effectEnableFade();
        effectSetDuration(-1);
        effectSetMode(2);
        effectSetParam(i * 3);
        effectSetCallback(effectSpriteMatrixUpdate);
        effectSetSpeed((s32)&ammo->ammoIconSlide[i]);
        ammo->ammoIcons[i] = effectCreateAtPosition(D_8071FFD4, 1.0f, y, 210.0f, -10.0f);
        y -= 0x1E;
    }
    sfxPlayOnFreeSlot(0x3E4, 0x7FFF, 63.0f, 1.0f, 5, 0);
}

void bonusFireProjectile(f32 targetX, f32 targetY, f32 targetZ) {
    sfxPlayOnFreeSlot(0x59, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
    projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y - 10.0f, gCurrentActor->z);
    projectileAimAndSpawn(0x23, 1, 0.6f, targetX, targetY, targetZ, 385.0f, gCurrentActor);
}

u8 bonusAimAndFire(f32 aimX, f32 aimY, f32 aimZ) {
    BonusShooterState *bonusExt = gCurrentActor->customState;
    f32 screenX;
    f32 screenY;
    s16 ammoIndex;
    f32 distance;
    u8 pad1;
    u8 pad2;
    u8 pad3;
    u8 fireStatus;

    fireStatus = 0;
    bonusExt->showCrosshair = 1;
    camProjectToScreen(aimX, aimY, aimZ, &screenX, &screenY, 0, 4.0f, 0);
    bonusExt->crosshairX = screenX;
    bonusExt->crosshairY = screenY;
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(aimX, aimZ, gCurrentActor->x, gCurrentActor->z), 10.0f);
    distance = sqrtf((gCurrentActor->x - aimX) * (gCurrentActor->x - aimX) + (gCurrentActor->z - aimZ) * (gCurrentActor->z - aimZ));
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, mathAtan2(gCurrentActor->y - aimY, distance) * 2048.0 / 3.1415927f + 150.0, 5.0f);
    if ((gPlayerPadState[0].pressedButtons & 0xE000) != 0) {
        if (gCurrentActor->state == 0) {
            fireStatus = 1;
            if (bonusExt->aimSlot != 0) {
                if (bonusExt->ammoCount != 0 && bonusExt->ammoIconSlide[0] == 0) {
                    bonusFireProjectile(aimX, aimY, aimZ);
                    bonusExt->ammoCount--;
                    effectFreeAndUnlink(bonusExt->ammoIcons[bonusExt->ammoCount]);
                    rumbleRequest(0, 0xFF, 3);
                    bonusExt->ammoIcons[bonusExt->ammoCount] = NULL;
                    for (ammoIndex = 0; ammoIndex < bonusExt->ammoCount; ammoIndex++) {
                        bonusExt->ammoIconSlide[ammoIndex] = 10;
                    }
                } else if (bonusExt->ammoCount == 0) {
                    if (gCurrentActor->unk155 == 0) {
                        fireStatus = 2;
                        gCurrentActor->unk155 = 1;
                    }
                }
            } else if (bonusExt->ammoCount < 5) {
                bonusExt->ammoCount = 5;
                bonusResetAmmo(bonusExt);
                gCurrentActor->unk155 = 0;
            }
        }
    }
    return fireStatus;
}

extern s32 gCurrentMap;
extern PlayerState *gActivePlayerState;

extern u8 gGameMode;


void bonusTargetGameUpdate(void) {
    BonusShooterState *bonusExt = gCurrentActor->customState;
    BonusTargetGameState *game = ((BonusActorExt *)gCurrentActor)->gameState;
    TargetVec3f *p;
    f32 ang;
    u8 c;
    s32 r;
    u8 idx;

    if (!(gCurrentActor->flags & 0x10)) {
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        game->counterTextId = c;
        func_806FDAB8(c, 0.0f);
        bonusExt->ammoCount = 5;
        bonusExt->phase = -2;
        bonusExt->aimSlot = 0;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, -7, 0, 0x16, 0x2C, 4, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x310;
        switch (gCurrentMap) {
        case 0xA:
            game->spawnThreshold = 0x55;
            game->typeThreshold = 0x46;
            game->targetAnimSpeed = 0.85f;
            game->shownCount = 0x12;
            game->targetsLeft = game->shownCount;
            game->timeLimit = 0x3C;
            break;
        case 0x73:
            game->spawnThreshold = 0x5A;
            game->typeThreshold = 0x46;
            game->targetAnimSpeed = 1.0f;
            game->shownCount = 0x16;
            game->targetsLeft = game->shownCount;
            game->timeLimit = 0x3C;
            break;
        case 0x74:
            game->spawnThreshold = 0x57;
            game->typeThreshold = 0x50;
            game->targetAnimSpeed = 1.2f;
            game->shownCount = 0x19;
            game->targetsLeft = game->shownCount;
            game->timeLimit = 0x3C;
            break;
        case 0x75:
            game->spawnThreshold = 0x5C;
            game->typeThreshold = 0x50;
            game->targetAnimSpeed = 1.3f;
            game->shownCount = 0x1C;
            game->targetsLeft = game->shownCount;
            game->timeLimit = 0x3C;
            break;
        }
    }
    if (bonusExt->phase > 0) {
        bonusExt->aimSlot = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState[0].stickAbsX >= 0x1F || gPlayerPadState[0].stickAbsY >= 0x1F)) {
            ang = mathAtan2(gPlayerPadState[0].stickY, gPlayerPadState[0].stickX) / 6.2831855f * 8.0 + 5.5;
            if (ang > 9.0f) {
                ang -= 8.0f;
            }
            bonusExt->aimSlot = ang;
        }
        p = *gMinecartTrackPoints + bonusExt->aimSlot;
        if (bonusAimAndFire(p->x, p->y, p->z) == 2) {
            bonusExt->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        switch (gCurrentActor->state) {
        case 0:
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 0xFF;
            }
            if (game->targetsLeft == 0) {
                bonusEndWin(0, 0);
                camStartPath(0, 1, 0x11);
                gCurrentActor->state = 1;
            } else if (game->spawnThreshold < (randomNonNegative() >> 0xF) % 100) {
                r = (randomNonNegative() >> 0xF) % 0xFF;
                idx = r % 8;
                if (game->targets[idx] == 0) {
                    p = *gMinecartTrackPoints + idx + 1;
                    bonusSpawnTarget(p->x, p->y, p->z, idx, game);
                }
            }
            if ((gCurrentActor->parentActor)->state == 4 && (gCurrentActor->parentActor)->unk155 != 0xFF) {
                gCurrentActor->state = 0xFE;
            }
            break;
        case 0xFE:
            bonusExt->unk24 = 0xFF;
            sfxPlayOnFreeSlot(0x142, 0x7FFF, 63.0f, 1.0f, 0, 0);
            gCurrentActor->state = 0;
            break;
        case 0xFF:
            bonusEndLose(0, 5);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 1;
            break;
        }
    } else {
        switch (bonusExt->phase) {
        case -2:
            if (gGameMode != 1) {
                bonusExt->phase++;
                hudSpawnCountdownTimer(0xDC, 0x2A, game->timeLimit);
                resQueueAttachActor(gCurrentActor, 0, 1);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                bonusExt->phase = 1;
                hudCountdownTimerStart(gCurrentActor->parentActor);
                bonusResetAmmo(bonusExt);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    if (bonusExt->phase >= -1) {
        renderCallbacksRegister(bonusRenderTargetGameHud, gCurrentActor, 3);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}



void bonusPopupGameUpdate(void) {
    BonusShooterState *bonusExt = gCurrentActor->customState;
    TurtleTroubleGameState *game = ((BonusActorExt *)gCurrentActor)->gameState;
    TargetVec3f *p;
    f32 y;
    f32 z;

    if (!(gCurrentActor->flags & 0x10)) {
        bonusExt->ammoCount = 5;
        bonusExt->phase = -2;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x9A;
        switch (gCurrentMap) {
        case 0x12:
            game->spinDecay = 0.5f;
            game->timeLimit = 0x2D;
            game->slowDelayMin = 0x1E;
            game->slowDelayMax = 0x46;
            break;
        case 0x76:
            game->spinDecay = 0.8f;
            game->timeLimit = 0x2D;
            game->slowDelayMin = 0x14;
            game->slowDelayMax = 0x46;
            break;
        case 0x77:
            game->spinDecay = 1.0f;
            game->timeLimit = 0x3C;
            game->slowDelayMin = 0x14;
            game->slowDelayMax = 0x46;
            break;
        case 0x78:
            game->spinDecay = 1.5f;
            game->timeLimit = 0x3C;
            game->slowDelayMin = 0x14;
            game->slowDelayMax = 0x46;
            break;
        }
        bonusPopupSpawnActors(game);
    }
    if (gCurrentActor->state == 0) {
        gCurrentActor->unk15F = 1;
    } else {
        gCurrentActor->unk15F = 0;
    }
    if (bonusExt->phase > 0) {
        bonusExt->aimSlot = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState[0].stickAbsX >= 0x1F || gPlayerPadState[0].stickAbsY >= 0x1F)) {
            if (gPlayerPadState[0].stickY > 0) {
                if (gPlayerPadState[0].stickX < -0x28) {
                    bonusExt->aimSlot = 1;
                } else if (gPlayerPadState[0].stickX >= 0x29) {
                    bonusExt->aimSlot = 3;
                } else {
                    bonusExt->aimSlot = 2;
                }
            } else if (gPlayerPadState[0].stickX < -0x28) {
                bonusExt->aimSlot = 4;
            } else if (gPlayerPadState[0].stickX >= 0x29) {
                bonusExt->aimSlot = 5;
            } else {
                bonusExt->aimSlot = 6;
            }
        }
        p = *gMinecartTrackPoints + bonusExt->aimSlot;
        y = p->y;
        z = p->z;
        if (bonusExt->aimSlot != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            if (bonusExt->aimSlot) {
                Actor *snakeActor = game->snakes[bonusExt->aimSlot - 1];
                TurtleTroubleSnake *snake = snakeActor->customState;
                if (snake->hitTimer == 0) {
                    snake->hitTimer = 6;
                }
            }
            break;
        case 2:
            bonusExt->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (gCurrentActor->state) {
        case 0:
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 0xFF;
            }
            if ((gCurrentActor->parentActor)->state == 4 && (gCurrentActor->parentActor)->unk155 != 0xFF) {
                gCurrentActor->state = 0xFE;
            }
            break;
        case 2:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 0;
            break;
        case 0xFE:
            bonusExt->unk24 = 0xFF;
            gCurrentActor->state = 0;
            break;
        case 0xFF:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 1;
            break;
        }
    } else {
        switch (bonusExt->phase) {
        case -2:
            if (gGameMode != 1) {
                bonusExt->phase++;
                hudSpawnCountdownTimer(0xDC, 0x2A, game->timeLimit);
                resQueueAttachActor(gCurrentActor, 0, 2);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                bonusExt->phase = 1;
                hudCountdownTimerStart(gCurrentActor->parentActor);
                bonusResetAmmo(bonusExt);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    if (bonusExt->phase >= -1) {
        renderCallbacksRegister(bonusRenderPopupGameHud, gCurrentActor, 3);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusTargetUpdate(void) {
    BonusTargetState *sub = gCurrentActor->customState;
    BonusTargetGameState *p = sub->game;
    s32 step;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 0x24;
    }
    func_8072881C(0, &sub->lastFrame);
    switch (gCurrentActor->state) {
    case 0:
        if (gActorGlobalState.unk15 != 0) {
            if (p->targetsLeft - ((sub->targetType != 0) ? 2 : 1) < 0) {
                p->targetsLeft = 0;
            } else {
                step = (sub->targetType != 0) ? 2 : 1;
                p->targetsLeft -= step;
            }
            func_806FDAB8(p->counterTextId, 3.1415927f);
            actorScriptStart(gCurrentActor, (sub->targetType != 0) ? 0x212 : 0x210);
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 0;
        } else if (gCurrentActor->unk155 != 0) {
            bonusDespawnTarget(sub, p);
        }
        break;
    case 1:
        if (gCurrentActor->unk155 != 0) {
            bonusDespawnTarget(sub, p);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusPopupSpawnActors(TurtleTroubleGameState *game) {
    s32 i;
    TurtleTroubleSnake *snake;
    Actor *snakeActor;
    TargetVec3f *pos;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x12C, 0x15) != 0) {
            snake = gSpawnedActor->customState;
            snake->game = gCurrentActor;
            snake->slowDelayStart = (((randomNonNegative() >> 0xF) % 0x7FFF) % (game->slowDelayMax - game->slowDelayMin + 1)) + game->slowDelayMin;
            pos = *gMinecartTrackPoints + i;
            actorScriptStart(gSpawnedActor, 0x1F5);
            gSpawnedActor->x = pos->x;
            gSpawnedActor->y = pos->y;
            gSpawnedActor->z = pos->z;
            gSpawnedActor->flags |= 0x1000;
            gSpawnedActor->yaw = 0x800;
            game->snakes[i - 1] = gSpawnedActor;
            snakeActor = gSpawnedActor;
            if (actorSpawn(0x12D, 0x16) != 0) {
                TurtleTroubleTurtle *turtle = gSpawnedActor->customState;
                turtle->snake = snakeActor;
                turtle->slot = i - 1;
                snake->turtle = gSpawnedActor;
                turtle->labelText = -1;
            }
        }
    }
}


void bonusActorUpdateVertexPositions(void) {
    TurtleTroubleSnake *snake = gCurrentActor->customState;
    BonusShooterState *shooter = snake->game->customState;
    TurtleTroubleGameState *game = ((BonusActorExt *)snake->game)->gameState;
    TurtleTroubleTurtle *turtle;
    BoneRotation *chk;
    s32 vb[2]; // FAKE: stack pair (index 0, base) read back as vb[1] * 8 + vb[0]; p = chk drops the reloads and shifts the loop
    f32 invScale;
    BoneRotation *p;
    f32 fx;
    f32 fy;
    f32 zOffset;
    s32 i;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 0x24;
        snake->spinSpeed = 275.0f;
        snake->spinTarget = 275.0f;
        snake->slowDelay = snake->slowDelayStart;
        gCurrentActor->sub4->boneRotations = heapAlloc(0x38);
        heapClearBlock(gCurrentActor->sub4->boneRotations);
    }
    turtle = snake->turtle->customState;
    if (gActorGlobalState.bossFightPhase == 4 && turtle->fallen == 0 && snake->slowDelay == -1) {
        snake->spinTarget = 275.0f;
        snake->slowDelay = snake->slowDelayStart;
        turtle->warned = 0;
    }
    if (shooter->phase > 0 && snake->game->state == 0) {
        if (turtle->fallen == 0) {
            if (snake->slowDelay >= 0) {
                snake->slowDelay--;
            }
            if (snake->slowDelay < 0) {
                snake->spinTarget -= game->spinDecay;
            }
        } else {
            snake->spinTarget += 40.0f;
            snake->game->state = 2;
        }
    }
    snake->spinSpeed = snake->spinSpeed + (snake->spinTarget - snake->spinSpeed) * 0.3;
    if (turtle->fallen != 0) {
        if (snake->unk14 < 1.0f) {
            snake->unk14 += 0.1f;
        } else if (snake->unk14 > 1.0f) {
            snake->unk14 = 1.0f;
        }
    } else if (snake->hitTimer != 0) {
        snake->hitTimer--;
        if (snake->hitTimer == 0) {
            actorScriptStart(gCurrentActor, 0x1F6);
        }
    }
    chk = gCurrentActor->sub4->boneRotations;
    if (chk != 0) {
        vb[1] = 0;
        vb[0] = (s32)chk;
        invScale = 1.0f - ((snake->spinSpeed - 40.0f) / 235.0f);
        fx = mathSinF(snake->turtle->yaw) * (5000.0f * invScale + 150.0f);
        fy = mathCosF(snake->turtle->yaw) * (5000.0f * invScale + 150.0f);
        zOffset = snake->unk14 * 128.0f + -128.0f;
        if (fx < 0.0f) {
            fx = 65535.0f + fx;
        }
        if (fy < 0.0f) {
            fy = 65535.0f + fy;
        }
        for (i = 4, p = (BoneRotation *)(vb[1] * 8 + vb[0]); i < 7; i++, p++) {
            p->bone = i;
            p->weight = zOffset;
            p->rotX = fx;
            p->rotY = 0;
            p->rotZ = fy;
            if (fx > 32767.0f) {
                fx = fx + (65535.0f - fx) * 0.5;
            } else {
                fx = fx * 0.5;
            }
            if (fy > 32767.0f) {
                fy = fy + (65535.0f - fy) * 0.5;
            } else {
                fy = fy * 0.5;
            }
        }
        switch (gCurrentActor->unk155) {
        case 0:
            snake->unk18 = snake->unk18 + (invScale - snake->unk18) * 0.1;
            break;
        case 1:
        case 2:
            snake->unk18 = snake->unk18 + (0.0 - snake->unk18) * 0.1;
            break;
        }
        p->weight = snake->unk18 * -128.0f;
        p->bone = 0xE;
        p->rotX = 0x61A8;
        p->rotY = 0;
        p->rotZ = 0;
        p++;
        for (i = 0xC; i < 0xD; i++, p += 2) {
            p->weight = snake->unk18 * -128.0f;
            p->bone = i;
            p->rotX = 0xD8F0;
            p->rotY = 0;
            p->rotZ = 0;
        }
        p->weight = 0;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 D_8002D8C0[];

void bonusTurtleTroubleTurtleUpdate(void) {
    TurtleTroubleTurtle *turtle = gCurrentActor->customState;
    TurtleTroubleSnake *snake = turtle->snake->customState;
    f32 temp;
    f64 v;
    s16 idx;
    s32 volume;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->yaw = (randomNonNegative() >> 0xF) % 4096;
        gCurrentActor->accelY = -10.0f;
        gCurrentActor->contactFlags &= 0xFFFE;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x688, 0.0f, 0.0f);
        scriptSetActorRampTarget(gCurrentActor, 1.0, 0.0f);
    }
    if (snake->slowDelay == -1 && turtle->fallen == 0) {
        if (snake->spinSpeed < 220.0f) {
            if (turtle->warned == 0) {
                volume = 0x7F;
                turtle->warned = 1;
                idx = turtle->slot % 3;
                if (turtle->slot / 3 != 0) {
                    idx = 2 - idx;
                    volume = 0x64;
                }
                idx = D_8002D8C0[idx];
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, idx, 0xFF, volume, 0, 0, 0.0f, 0);
            }
            if (snake->spinSpeed < 40.0f) {
                turtle->fallen = 1;
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1ED, 0xFF, 0x7F, 0, 0, 0.0f, 0);
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x76, 0xFF, 0x7F, 0x1E);
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 10.0f;
                actorScriptStart(turtle->snake, 0x1F7);
            }
        }
    }
    if (turtle->fallen == 0) {
        actorGetNodePos(turtle->snake, 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    } else {
        if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            gCurrentActor->speedY = turtle->fallSpeed * -0.8f;
            v = -turtle->fallSpeed * 1.5;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, (v > 255.0) ? 255.0 : v, 0x7F, 0xA);
        }
        gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
        turtle->fallSpeed = gCurrentActor->speedY;
        actorUpdatePrevContactFlags(gCurrentActor);
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    }
    gCurrentActor->yaw += snake->spinSpeed;
    if (gCurrentActor->yaw >= 0x1000) {
        gCurrentActor->yaw -= 0x1000;
    }
    temp = 30000.0f / snake->spinSpeed;
    gCurrentActor->pitch = mathSinF(gCurrentActor->yaw) * -temp;
    gCurrentActor->roll = mathCosF(gCurrentActor->yaw) * temp;
    temp = temp * 0.006666667f;
    temp = (temp < 1.0f) ? 1.0f : ((temp > 2.5f) ? 2.5f : temp);
    scriptSetActorRampTarget(gCurrentActor, temp, 0.0f);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    s16 flashTimer;
    char pad2[2];
    f32 lightLevel;
    s8 slotOrder[6];
    s16 timeLimit;
    char pad10;
    u8 counterTextId;
    u8 rollTimer;
    char pad13;
    s16 shownCount;
    s16 targetsLeft;
} BonusLightFlashState;

extern s8 D_8002D8F4;
extern s16 D_8002D8F8;
extern s16 D_8002D8FC;
extern s16 D_8002D8EC[];

void bonusLightFlashGameUpdate(void) {
    BonusShooterState *bonusExt = gCurrentActor->customState;
    BonusLightFlashState *game = ((BonusActorExt *)gCurrentActor)->gameState;
    TargetVec3f *p;
    f32 y;
    f32 z;
    s32 pad;
    s32 i;
    s32 j;
    s32 r;
    u8 c;
    s16 d;

    if (!(gCurrentActor->flags & 0x10)) {
        bonusExt->ammoCount = 5;
        bonusExt->phase = -2;
        switch (gCurrentMap) {
        case 0x65:
            game->targetsLeft = 0xA;
            D_8002D8F4 = 0x30;
            break;
        case 0x8D:
            game->targetsLeft = 0xF;
            D_8002D8F4 = 0x30;
            break;
        case 0x8E:
            game->targetsLeft = 5;
            D_8002D8F4 = 0x1E;
            break;
        case 0x8F:
            game->targetsLeft = 0xA;
            D_8002D8F4 = 0x1E;
            break;
        }
        game->shownCount = game->targetsLeft;
        game->timeLimit = 0x3C;
        game->rollTimer = 0;
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        game->counterTextId = c;
        func_806FDAB8(c, 0.0f);
        game->flashTimer = 0x3C;
        game->lightLevel = 1.0f;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x9A;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        i = 0;
        do {
            game->slotOrder[i] = i | 0x80;
        } while (++i < 6);
        bonusLightFlashSpawnTargets(gCurrentActor);
    }
    if (bonusExt->phase > 0) {
        if (gCurrentActor->state == 0) {
            game->flashTimer -= 1;
        } else {
            game->flashTimer = 0x3C;
        }
        if (game->flashTimer > 0) {
            game->lightLevel = game->lightLevel + 0.2f;
        } else {
            game->lightLevel = game->lightLevel - 0.2f;
        }
        if (game->lightLevel > 1.0) {
            game->lightLevel = 1.0f;
        }
        if (game->lightLevel < 0.0) {
            game->lightLevel = 0.0f;
        }
        lightSetColor(game->lightLevel, game->lightLevel, game->lightLevel, 0);
        if (game->lightLevel == 0.0f) {
            j = (s16)(D_8002D8F8 - 1);
            ((s16 *)&D_8002D8F4)[2] = j; // FAKE: storing through D_8002D8F4's base keeps the D_8002D8F8 lh/sh from sharing a hoisted lui/addiu base (Q0332)
            if (j <= 0) {
                sfxPlayOnFreeSlot(0x1A1, 0x7FFF, 63.0f, 1.0f, 0x50, 0);
                j = randomLcgNext() & 3; if (gCurrentActor->state && gCurrentActor->state) {} if (j == 9) {} D_8002D8F8 = j + 2; // FAKE/LAYOUT: dead tests make j a coloured candidate (andi v1) and burn one ring temp (addiu t4); one line keeps the lw t0 reload below the sh
            }
            d = D_8002D8FC + 1;
            ((s16 *)&D_8002D8F4)[4] = d; // FAKE: storing through D_8002D8F4's base keeps the D_8002D8FC lh/sh from sharing a hoisted lui/addiu base (Q0332)
            if (d == 0xE) {
                sfxPlayOnFreeSlot(D_8002D8EC[randomLcgNext() & 3], 0x7FFF, 63.0f, 1.0f, 0x14, 0);
            }
        } else {
            if (randomFloat() < 0.5f) { D_8002D8FC = 0; }
            else { d = -100; if (d) {} D_8002D8FC = d | 0; } // FAKE/LAYOUT: dead test and |0 keep d colored in v0; preserve this line.
            j = 1; if (j) {} D_8002D8F8 = j | 0; // FAKE/LAYOUT: dead test and |0 keep j colored in v1; preserve this line.
        }
        if (game->flashTimer < -0x1E) {
            game->flashTimer = D_8002D8F4;
            i = 0;
            do {
                game->slotOrder[i] = -1;
                i++;
            } while (i < 6);
            for (i = 0; i != 6; i++) {
                j = i;
                r = randomLcgNext() & 7;
                while (r >= 0) {
                    if (game->slotOrder[j] == -1) {
                        r -= 1;
                        if (r >= 0) {
                            j += 1;
                        }
                    } else {
                        j += 1;
                    }
                    if (j >= 6) {
                        j = 0;
                    }
                }
                game->slotOrder[j] = i | 0x80;
            }
        }
        bonusExt->aimSlot = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState[0].stickAbsX >= 0x1F || gPlayerPadState[0].stickAbsY >= 0x1F)) {
            if (gPlayerPadState[0].stickY > 0) {
                if (gPlayerPadState[0].stickX < -0x28) {
                    bonusExt->aimSlot = 1;
                } else if (gPlayerPadState[0].stickX >= 0x29) {
                    bonusExt->aimSlot = 3;
                } else {
                    bonusExt->aimSlot = 2;
                }
            } else if (gPlayerPadState[0].stickX < -0x28) {
                bonusExt->aimSlot = 4;
            } else if (gPlayerPadState[0].stickX >= 0x29) {
                bonusExt->aimSlot = 5;
            } else {
                bonusExt->aimSlot = 6;
            }
        }
        p = *gMinecartTrackPoints + bonusExt->aimSlot;
        y = p->y;
        z = p->z;
        if (bonusExt->aimSlot != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            break;
        case 2:
            bonusExt->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (gCurrentActor->state) {
        case 0:
            if (game->shownCount == 0) {
                gCurrentActor->state = 2;
            }
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 1;
            }
            break;
        case 1:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        case 2:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        }
    } else {
        switch (bonusExt->phase) {
        case -2:
            if (gGameMode != 1) {
                bonusExt->phase++;
                hudSpawnCountdownTimer(0xDC, 0x2A, game->timeLimit);
                resQueueAttachActor(gCurrentActor, 0, 9);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                bonusExt->phase = 1;
                hudCountdownTimerStart(gCurrentActor->parentActor);
                bonusResetAmmo(bonusExt);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    renderCallbacksRegister(func_80029B9C, gCurrentActor, 3);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    s16 spawnTimer;
    char pad2;
    u8 counterTextId;
    s16 timeLimit;
    u8 rollTimer;
    char pad7;
    s16 shownCount;
    s16 fairiesLeft;
} PathPanicGameState;

typedef struct BugBashGameState {
    f32 centerX;
    f32 centerZ;
    f32 offsetX;
    f32 offsetZ;
    f32 velX;
    f32 velZ;
    s16 bobAngle;
    char pad1A[2];
    f32 unk1C;
    char pad20[2];
    s16 timeLimit;
    u8 unk24;
    u8 counterTextId;
    u8 rollTimer;
    char pad27;
    s16 shownCount;
    s16 fliesLeft;
    s8 spawnDelay;
    s8 respawnTimers[1];
} BugBashGameState;

Gfx *func_80029B9C(Gfx *gdl, Actor *actor) {
    BonusShooterState *bonusExt = actor->customState;
    BonusLightFlashState *lightFlash = ((BonusActorExt *)actor)->gameState;
    PathPanicGameState *pathPanic = ((BonusActorExt *)actor)->gameState;
    BugBashGameState *bugBash = actor->customState;

    if (actor->actorType != 0x7E && actor->state == 0 && bonusExt->showCrosshair != 0) {
        gdl = bonusRenderCrosshair(gdl, actor);
    }
    gSPDisplayList(gdl++, D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (actor->actorType) {
    case 0x7D:
        if (actor->state != 3) {
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, lightFlash->counterTextId, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &lightFlash->shownCount, lightFlash->targetsLeft, &lightFlash->rollTimer);
        }
        break;
    case 0x7C:
        if (actor->state != 3) {
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, pathPanic->counterTextId, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &pathPanic->shownCount, pathPanic->fairiesLeft, &pathPanic->rollTimer);
        }
        break;
    case 0x7E:
        switch (actor->state) {
        case 7:
            break;
        case 0:
        case 1:
        case 2:
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, bugBash->counterTextId, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &bugBash->shownCount, bugBash->fliesLeft, &bugBash->rollTimer);
            break;
        }
        break;
    }
    return gdl;
}

void bonusLightFlashSpawnTargets(void *ownerActor) {
    Actor *a = ownerActor;
    s32 i;
    BonusLightFlashState *base = ((BonusActorExt *)a)->gameState;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x147, D_8002D8C8[i - 1]) != 0) {
            LightFlashTargetState *subExt = gSpawnedActor->customState;
            s16 *actorProp = ((BonusActorExt *)gSpawnedActor)->unk17C;
            TargetVec3f *pt;
            f32 scale;

            *actorProp = D_8002D8C8[i - 1];
            subExt->game = a;
            subExt->slot = i - 1;
            pt = *gMinecartTrackPoints + (base->slotOrder[subExt->slot] & 0x7F) + 1;
            gSpawnedActor->x = pt->x;
            gSpawnedActor->y = pt->y;
            gSpawnedActor->z = pt->z;
            gSpawnedActor->state = 0;
            gSpawnedActor->flags |= 0x1000;
            gSpawnedActor->yaw = 0x800;
            if (i != 6) {
                playerKongStopSoundByState(gSpawnedActor);
                actorScriptStart(gSpawnedActor, D_8002D8D4[i - 1]);
            }
            scale = (i != 6) ? 0.25f : 0.04f;
            gSpawnedActor->sub4->scaleX = scale;
            gSpawnedActor->sub4->scaleY = scale;
            gSpawnedActor->sub4->scaleZ = scale;
        }
    }
}

void bonusLightFlashTargetUpdate(void) {
    f32 scale;
    LightFlashTargetState *subExt;
    Actor *owner;
    BonusLightFlashState *base;
    f32 lightR;
    f32 lightG;
    f32 lightB;
    TargetVec3f *p;
    s8 isHit;
    s8 flags;

    subExt = gCurrentActor->customState;
    owner = subExt->game;
    base = ((BonusActorExt *)owner)->gameState;
    if (!(gCurrentActor->flags & 0x10)) {
        if (subExt->slot != 5) {
            actorClearAllNodeFlags(gCurrentActor);
            actorAppendModelNode(gCurrentActor, 0.0f, 50.0f, 0.0f, 80.0f, -1);
        }
        gCurrentActor->unk144 = 0x24;
    }
    p = *gMinecartTrackPoints + (base->slotOrder[subExt->slot] & 0x7F) + 1;
    gCurrentActor->x = p->x;
    gCurrentActor->y = p->y;
    gCurrentActor->z = p->z;
    lightGetColor(&lightR, &lightG, &lightB, 0);
    if (lightR < 0.1f) {
        gCurrentActor->unk144 = 0;
    } else {
        gCurrentActor->unk144 = 0x24;
    }
    isHit = 0;
    if (gActorGlobalState.unk15 == 1 && base->flashTimer >= -9) {
        isHit = 1;
    }
    if (subExt->slot != 5) {
        flags = base->slotOrder[subExt->slot];
        if (flags & 0x80) {
            base->slotOrder[subExt->slot] = flags & 0x7F;
            actorScriptStart(gCurrentActor, D_8002D8D4[subExt->slot]);
        } else if (lightR < 0.05f && gCurrentActor->sub4->scriptStart != NULL) {
            actorScriptStart(gCurrentActor, 0);
        }
        if (isHit != 0) {
            actorScriptStart(gCurrentActor, D_8002D8E0[subExt->slot]);
            sfxPlayOnFreeSlot(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
            if (base->targetsLeft != 0) {
                base->targetsLeft += 1;
            }
        }
        func_806BF920();
    } else {
        gCurrentActor->flags |= 0x1000;
        gCurrentActor->yaw += 0x12C;
        if (base->flashTimer < -0x1C) {
            gCurrentActor->state = 0;
        }
        scale = gCurrentActor->sub4->scaleX;
        if (gCurrentActor->state == 1) {
            scale = scale - 0.005;
            if (scale < 0.0) {
                scale = 0.0f;
            }
        } else {
            scale = 0.04f;
        }
        gCurrentActor->sub4->scaleX = scale;
        gCurrentActor->sub4->scaleY = scale;
        gCurrentActor->sub4->scaleZ = scale;
        if (isHit != 0) {
            sfxPlayOnFreeSlot(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
            base->flashTimer = 0;
            base->targetsLeft -= 1;
            gCurrentActor->state = 1;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

// customState of the Peril Path Panic klaptraps (0x148) and fairies (0x149).
typedef struct {
    Actor *game;
    s8 unk4;
    char pad5;
    s16 snapTimer;
} PathPanicActorState;

extern s8 D_8002D904;

void bonusPerilPathPanicGameUpdate(void) {
    BonusShooterState *bonusExt = gCurrentActor->customState;
    PathPanicGameState *game = ((BonusActorExt *)gCurrentActor)->gameState;
    TargetVec3f *p;
    f32 y;
    f32 z;
    s32 n;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        bonusExt->ammoCount = 5;
        bonusExt->phase = -2;
        D_8002D904 = 0;
        switch (gCurrentMap) {
        case 0x90:
            game->fairiesLeft = 6;
            D_8002D900 = 0x15;
            break;
        case 0x91:
            game->fairiesLeft = 8;
            D_8002D900 = 0x12;
            break;
        case 0x92:
            game->fairiesLeft = 0xA;
            D_8002D900 = 0xF;
            break;
        case 0x93:
            game->fairiesLeft = 0xC;
            D_8002D900 = 0xC;
            break;
        }
        game->timeLimit = 0x3C;
        game->rollTimer = 0;
        game->shownCount = game->fairiesLeft;
        game->counterTextId = gfxResourceCreate(1, textTableGetString(0x1A, 4, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(game->counterTextId, 0.0f);
        game->spawnTimer = 0x1E;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x9A;
        for (i = 1; i != 7; i++) {
            if (actorSpawn(0x148, 0x21) != 0) {
                PathPanicActorState *u = gSpawnedActor->customState;

                u->game = gCurrentActor;
                u->unk4 = i;
                p = *gMinecartTrackPoints + i;
                gSpawnedActor->x = p->x;
                gSpawnedActor->y = p->y;
                gSpawnedActor->z = p->z + 45.0;
                gSpawnedActor->state = 0;
                gSpawnedActor->yaw = 0x800;
                gSpawnedActor->sub4->scaleX = 0.45f;
                gSpawnedActor->sub4->scaleY = 0.45f;
                gSpawnedActor->sub4->scaleZ = 0.45f;
            }
        }
    }
    if (bonusExt->phase > 0) {
        if (game->spawnTimer > 0) {
            game->spawnTimer--;
        } else {
            if (actorSpawn(0x149, 0x3D) != 0) {
                PathPanicActorState *u = gSpawnedActor->customState;

                n = D_8002D904;
                u->game = gCurrentActor;
                p = *gMinecartTrackPoints + (n + n + n) + 1; // FAKE: n + n + n keeps two addu; n * 3 becomes sll/subu and shifts the block
                gSpawnedActor->x = p->x + 50.0;
                gSpawnedActor->y = p->y + 12.0;
                gSpawnedActor->z = p->z - 5.0;
                gSpawnedActor->yaw = -0x400;
                gSpawnedActor->sub4->scaleX = 0.08f;
                if (u) {} // FAKE: empty guard steers regalloc
                gSpawnedActor->sub4->scaleY = 0.08f;
                gSpawnedActor->sub4->scaleZ = 0.08f;
            }
            n = D_8002D904;
            game->spawnTimer = 0x5A;
            ((s8 *)&D_8002D900)[4] = (u16)(1 - n); // FAKE: storing through D_8002D900's base keeps the D_8002D904 lb/sb from sharing a hoisted lui/addiu base (Q0332); the (u16) puts the subu in t7
        }
        bonusExt->aimSlot = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState[0].stickAbsX >= 0x1F || gPlayerPadState[0].stickAbsY >= 0x1F)) {
            if (gPlayerPadState[0].stickY > 0) {
                if (gPlayerPadState[0].stickX < -0x28) {
                    bonusExt->aimSlot = 1;
                } else if (gPlayerPadState[0].stickX >= 0x29) {
                    bonusExt->aimSlot = 3;
                } else {
                    bonusExt->aimSlot = 2;
                }
            } else if (gPlayerPadState[0].stickX < -0x28) {
                bonusExt->aimSlot = 4;
            } else if (gPlayerPadState[0].stickX >= 0x29) {
                bonusExt->aimSlot = 5;
            } else {
                bonusExt->aimSlot = 6;
            }
        }
        p = *gMinecartTrackPoints + bonusExt->aimSlot;
        y = p->y;
        z = p->z;
        if (bonusExt->aimSlot != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            break;
        case 2:
            bonusExt->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (gCurrentActor->state) {
        case 0:
            if (game->shownCount == 0) {
                gCurrentActor->state = 2;
            }
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 1;
            }
            break;
        case 1:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        case 2:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        }
    } else {
        switch (bonusExt->phase) {
        case -2:
            if (gGameMode != 1) {
                bonusExt->phase++;
                hudSpawnCountdownTimer(0xDC, 0x2A, game->timeLimit);
                resQueueAttachActor(gCurrentActor, 0, 0xB);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                bonusExt->phase = 1;
                hudCountdownTimerStart(gCurrentActor->parentActor);
                bonusResetAmmo(bonusExt);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    renderCallbacksRegister(func_80029B9C, gCurrentActor, 3);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusPerilPathPanicKlaptrapUpdate(void) {
    PathPanicActorState *actorExt;
    Actor *targetActor;
    f32 dx;
    f32 dy;
    s32 animScript;
    AnimSlot *animSub;
    ActorSub4 *modelData;
    PathPanicActorState *targetExt;
    s32 i;

    actorExt = gCurrentActor->customState;
    modelData = gCurrentActor->sub4;
    animSub = modelData->model;
    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x239);
        gCurrentActor->unk144 = 0x24;
        modelData = gCurrentActor->sub4;
    }
    animScript = modelData->animId;
    if (animScript == 0x239) {
        for (i = 0; i < gActiveActorCount; i++) {
            targetActor = gActiveActors[i].actor;
            if (targetActor->actorType == 0x149) {
                dx = targetActor->x - gCurrentActor->x;
                dy = targetActor->y - gCurrentActor->y;
                if (dx < 5.0 && dx > -5.0 && dy < 20.0f && dy > -20.0) {
                    targetExt = targetActor->customState;
                    targetExt->unk4 = 8;
                    actorScriptStart(gCurrentActor, 0x23B);
                }
            }
        }
    }
    if ((animScript == 0x239 || animScript == 0x23B || (animScript == 0x238 && animSub != NULL && animSub->frame > 48.0f)) && gActorGlobalState.unk15 == 1) {
        actorScriptStart(gCurrentActor, 0x23C);
        actorExt->snapTimer = ((randomLcgNext() & 7) + 6) * D_8002D900;
    }
    if (animScript == 0x23A) {
        actorExt->snapTimer -= 1;
        if (actorExt->snapTimer == 0) {
            actorScriptStart(gCurrentActor, 0x238);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusPerilPathPanicFairyUpdate(void) {
    s32 pad;
    PathPanicActorState *subExt;
    Actor *owner;
    PathPanicGameState *ownerExt;
    TargetVec3f *p;

    subExt = gCurrentActor->customState;
    owner = subExt->game;
    ownerExt = ((BonusActorExt *)owner)->gameState;
    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x2B5);
    }
    if (subExt->unk4 == 0 || subExt->unk4 >= 5) {
        gCurrentActor->x = gCurrentActor->x - 1.5;
    }
    p = *gMinecartTrackPoints + 3;
    if (gCurrentActor->x < p->x - 50.0) {
        if (ownerExt->fairiesLeft > 0) {
            ownerExt->fairiesLeft -= 1;
        }
        actorDespawn(gCurrentActor);
    }
    if (subExt->unk4 != 0) {
        subExt->unk4 -= 1;
        if (subExt->unk4 < 4) {
            if (subExt->unk4 == 3) {
                sfxPlayOnFreeSlot(0x2D2, 0x7FFF, 63.0f, 7.12f, 0, 1);
            }
            gCurrentActor->sub4->scaleX *= 0.8f;
            gCurrentActor->sub4->scaleY *= 0.8f;
            gCurrentActor->sub4->scaleZ *= 0.8f;
        }
        if (subExt->unk4 == 0) {
            actorDespawn(gCurrentActor);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern Actor *gPrimaryPlayerActor;
extern PlayerStruct *gPlayerSlots;
extern OSContPad *D_807ECDEC;
typedef struct {
    Actor *game;
    f32 goalX;
    f32 goalZ;
    s16 fleeTimer;
    s16 retargetTimer;
} BugBashActorState;

void bonusBigBugBashGameUpdate(void) {
    s32 pad0[4];
    f32 fx;
    f32 fz;
    f32 diffDelta;
    AnimSlot *animData = gCurrentActor->sub4->model;
    BugBashGameState *game = gCurrentActor->customState;
    s32 i;
    u8 c;
    s32 padz;
    BugBashActorState *swatter;
    s16 spawnAngle;

    if (!(gCurrentActor->flags & 0x10)) {
        gPrimaryPlayerActor->state = 0x77;
        gPrimaryPlayerActor->unk155 = 0;
        game->centerX = gCurrentActor->x + 10.0;
        game->centerZ = gCurrentActor->z + 8.0;
        gCurrentActor->y = gCurrentActor->y + 50.0;
        switch (gCurrentMap) {
        case 0x66:
            game->fliesLeft = 4;
            break;
        case 0x94:
            game->fliesLeft = 6;
            break;
        case 0x95:
            game->fliesLeft = 8;
            break;
        case 0x96:
            game->fliesLeft = 0xA;
            break;
        }
        game->rollTimer = 0;
        game->timeLimit = 0x3C;
        game->shownCount = game->fliesLeft;
        fx = 0.0;
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, fx, fx, fx);
        game->counterTextId = c;
        func_806FDAB8(c, fx);
        lightSetColor(1.0f, 1.0f, 1.0f, -1);
        gCurrentActor->roll = 0;
        gCurrentActor->yaw = 0x800;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x5FB, 0.0f, 0.0f);
        gCurrentActor->sub4->scaleX = 0.2f;
        gCurrentActor->sub4->scaleY = 0.2f;
        gCurrentActor->sub4->scaleZ = 0.2f;
        camStartPath(0, 0, 1);
        gCurrentActor->state = 3;
        game->unk1C = 0.0f;
        game->velX = 0.0f;
        game->velZ = 0.0f;
        game->offsetX = 0.0f;
        game->offsetZ = 0.0f;
        actorSpawn(0x14C, 0x55);
        swatter = gSpawnedActor->customState;
        swatter->game = gCurrentActor;
        game->spawnDelay = 0x3C;
        i = 0;
        do {
            game->respawnTimers[i] = 1;
            i++;
        } while (i != 1);
    }
    for (i = 0; i < 1; i++) {
        if (game->respawnTimers[i] > 0) {
            game->respawnTimers[i] -= 1;
            if (game->respawnTimers[i] == 0 && actorSpawn(0x14A, 0x53) != 0) {
                BugBashActorState *fly = gSpawnedActor->customState;

                fly->game = gCurrentActor;
                fly->goalX = gSpawnedActor->x;
                fly->goalZ = gSpawnedActor->z;
                fly->retargetTimer = 2;
                spawnAngle = mathAngleBetweenPoints2D(game->centerX, game->centerZ, gCurrentActor->x, gCurrentActor->z) + 0x800;
                fly->goalX = mathSinF(spawnAngle) * 70.0 + game->centerX;
                fly->goalZ = mathCosF(spawnAngle) * 70.0 + game->centerZ;
                if (game->spawnDelay == 0) {
                    gSpawnedActor->x = fly->goalX;
                    gSpawnedActor->y = gCurrentActor->y - 30.0;
                    gSpawnedActor->z = fly->goalZ;
                } else {
                    gSpawnedActor->x = game->centerX - 30.0;
                    gSpawnedActor->z = game->centerX;
                    gSpawnedActor->y = gCurrentActor->y - 30.0;
                }
            }
        }
    }
    if (game->spawnDelay != 0) {
        game->spawnDelay -= 1;
    }
    game->bobAngle += 0x19;
    if (gCurrentActor->state < 2) {
        f32 cosYaw;
        f32 stickY;

        fz = mathSinF(gPlayerSlots[gCurrentPlayerIndex].camYawInt);
        cosYaw = mathCosF(gPlayerSlots[gCurrentPlayerIndex].camYawInt);
        fx = D_807ECDEC->stick_x * 0.04f;
        stickY = D_807ECDEC->stick_y * 0.04f;

        diffDelta = (fx * cosYaw - stickY * fz) - game->velX;
        game->velX += diffDelta * 0.125f;
        game->velZ += ((fx * fz + stickY * cosYaw) - game->velZ) * 0.25f;
        game->offsetX += game->velX;
        game->offsetZ -= game->velZ;
    }
    switch (gCurrentActor->state) {
    case 0: {
        f32 prev = game->unk1C;

        game->unk1C += (-diffDelta * 4.0f - game->unk1C) * 0.125f;
        if (game->unk1C < 0.0f) {
            if (game->unk1C < -8.0f) {
                game->unk1C = -8.0f;
            }
            if (prev >= 0.0f) {
                controllerAnimSetStateIfChanged(gCurrentActor, 0x5FC, 0.0f, 0.0f);
            }
            if (animData != NULL) {
                controllerApplyMotionWindow(gCurrentActor, animData, -game->unk1C);
            }
        } else {
            if (game->unk1C > 8.0f) {
                game->unk1C = 8.0f;
            }
            if (prev < 0.0f) {
                controllerAnimSetStateIfChanged(gCurrentActor, 0x5FB, 0.0f, 0.0f);
            }
            if (animData != NULL) {
                controllerApplyMotionWindow(gCurrentActor, animData, game->unk1C);
            }
        }
        if (game->shownCount == 0) {
            gCurrentActor->state = 5;
        }
        if (gCurrentActor->parentActor->state == 5) {
            gCurrentActor->state = 6;
        }
        if (gCurrentActor->state == 0 && (*gPlayerSlots[gCurrentPlayerIndex].heldButtonsPtr & 0xE000)) {
            sfxPlayOnFreeSlot(0x25, 0x7FFF, 63.0f, 0.51f, 0, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x5FD, 0.0f, 1.0f);
            gCurrentActor->state = 1;
        }
        break;
    }
    case 1:
    case 2:
        if (animData->frame > 10.0f && animData->frame < 14.0f) {
            gCurrentActor->state = 2;
        } else {
            gCurrentActor->state = 1;
        }
        if (animData->speed == 0.0f) {
            controllerAnimSetStateIfChanged(gCurrentActor, 0x5FC, 0.0f, 1.0f);
            gCurrentActor->state = 0;
            game->unk1C = 0.0f;
        }
        break;
    case 3:
        if (gGameMode != 1) {
            gCurrentActor->state = 4;
            hudSpawnCountdownTimer(0xDC, 0x2A, game->timeLimit);
            resQueueAttachActor(gCurrentActor, 0, 0xA);
        }
        break;
    case 4:
        if (!(gCurrentActor->flags & 0x2000000)) {
            gCurrentActor->state = 0;
            hudCountdownTimerStart(gCurrentActor->parentActor);
            sfxAllocateChannel(8, 1.0f);
        }
        break;
    case 5:
    case 6:
        if (gCurrentActor->state == 6) {
            bonusEndLose(0, 1);
        } else {
            bonusEndWin(0, 0);
        }
        camStartPath(0, 1, 0x11);
        gCurrentActor->state = 7;
        break;
    }
    fx = game->offsetX * 0.85;
    fz = game->offsetZ - 40.0;
    diffDelta = sqrtf(fx * fx + fz * fz);

    if (diffDelta > 80.0f) {
        diffDelta = 80.0f / diffDelta;
        game->offsetX = (fx * diffDelta) / 0.85;
        game->offsetZ = (fz * diffDelta) + 40.0;
    }
    gCurrentActor->x = mathSinF(game->bobAngle) * 5.0 + (game->centerX + game->offsetX * 0.8);
    gCurrentActor->z = 2.0 * mathCosF(game->bobAngle * 2) + (game->centerZ + game->offsetZ * 0.9);
    gPrimaryPlayerActor->x = game->centerX + game->offsetX * 0.5f;
    gPrimaryPlayerActor->y = gCurrentActor->y;
    gPrimaryPlayerActor->z = game->centerZ + game->offsetZ * 0.5f;
    renderCallbacksRegister(func_80029B9C, gCurrentActor, 3);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusBigBugBashFlyUpdate(void) {
    BugBashActorState *flyExt = gCurrentActor->customState;
    Actor *targetActor = flyExt->game;
    BugBashGameState *targetExt = targetActor->customState;
    f32 flySpeed;
    f32 wanderRadius;
    f32 dx;

    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x32F);
        gCurrentActor->sub4->scaleX = 0.06f;
        gCurrentActor->sub4->scaleY = 0.06f;
        gCurrentActor->sub4->scaleZ = 0.06f;
        sfxPlayActorSound(gCurrentActor, 0x10E, 0x3C, 1, 0, 0xFF, 1.0f, 0);
    }
    if (gCurrentActor->state == 0) {
        if (targetExt->spawnDelay == 0) {
            if (flyExt->fleeTimer > 0) {
                if (flyExt->fleeTimer == 0x28) {
                    sfxPlayFromActorDirect(gCurrentActor, 0x801, 0xFF, 3.0f, 2, 0);
                }
                flyExt->fleeTimer--;
                flySpeed = 5.0f;
            } else {
                flySpeed = 3.0f;
            }
            gCurrentActor->yaw -= mathAngleSignedDistance(mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, flyExt->goalX, flyExt->goalZ) + 0x800, gCurrentActor->yaw) >> 3;
            gCurrentActor->x += mathSinF(gCurrentActor->yaw) * flySpeed;
            gCurrentActor->z += mathCosF(gCurrentActor->yaw) * flySpeed;
            flyExt->retargetTimer--;
            if (flyExt->retargetTimer <= 0) {
                s16 angle;

                if (flyExt->fleeTimer > 0) {
                    flyExt->retargetTimer = (randomLcgNext() & 7) + 0xA;
                } else {
                    flyExt->retargetTimer = (randomLcgNext() & 0x3F) + 0xF;
                }
                angle = mathAngleBetweenPoints2D(targetExt->centerX, targetExt->centerZ, flyExt->goalX, flyExt->goalZ);
                angle += ((randomLcgNext() & 7) << 8) + 0x400;
                wanderRadius = randomFloat() * 70.0;
                flyExt->goalX = mathSinF(angle) * wanderRadius + targetExt->centerX;
                flyExt->goalZ = mathCosF(angle) * wanderRadius + targetExt->centerZ;
            }
        } else {
            if (targetExt->spawnDelay == 0x28) {
                sfxPlayFromActorDirect(gCurrentActor, 0x801, 0xFF, 3.0f, 2, 0);
            }
            gCurrentActor->y = mathSinF(targetExt->bobAngle) * 5.0 + (targetActor->y - 30.0);
        }
    } else {
        gCurrentActor->alpha -= 4;
        if (gCurrentActor->alpha < 5) {
            gCurrentActor->alpha = 0;
            actorDespawn(gCurrentActor);
        }
    }
    if (targetActor->state == 2) {
        f32 dz;
        dx = mathSinF(targetActor->yaw) * 65.0f + targetActor->x;
        dz = mathCosF(targetActor->yaw) * 65.0f + targetActor->z;
        dx -= gCurrentActor->x;
        dz -= gCurrentActor->z;
        if (gCurrentActor->state == 0) {
            if (dx < 12.0 && dx > -12.0 && dz < 12.0 && dz > -12.0) {
                s32 i;

                sfxStopSlotSound(gCurrentActor, 0);
                actorScriptStart(gCurrentActor, 0x331);
                if (targetExt->fliesLeft != 0) {
                    targetExt->fliesLeft--;
                }
                for (i = 0; i < 1; i++) {
                    if (targetExt->respawnTimers[i] == 0) {
                        targetExt->respawnTimers[i] = 0x1E;
                        i = 1;
                    }
                }
                gCurrentActor->state = 1;
                sfxPlayFromActorDirect(gCurrentActor, 0x16, 0xFF, 1.0f, 0x14, 0);
                gCurrentActor->alpha = 0xFF;
                gCurrentActor->flags &= ~0x8000;
            } else if (dx * dx + dz * dz < 900.0f) {
                flyExt->fleeTimer = 0x3C;
                flyExt->retargetTimer = 1;
            }
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusBigBugBashSwatterShadowUpdate(void) {
    BugBashActorState *link = gCurrentActor->customState;
    Actor *targetActor = link->game;
    AnimSlot *selfAnim = gCurrentActor->sub4->model;
    AnimSlot *targetAnim = targetActor->sub4->model;
    s16 animId;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->roll = 0;
        gCurrentActor->yaw = 0x800;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x5FB, 0, 0);
        gCurrentActor->sub4->scaleX = 0.2f;
        gCurrentActor->sub4->scaleY = 0.2f;
        gCurrentActor->sub4->scaleZ = 0.2f;
    }
    gCurrentActor->x = targetActor->x;
    gCurrentActor->y = targetActor->y - 35.0;
    gCurrentActor->z = targetActor->z;
    if (selfAnim != NULL) {
        if (targetAnim != NULL) {
            animId = targetAnim->animId;
            if (animId == 0x5FD) {
                animId = 0x5FE;
            }
            if (animId != selfAnim->animId) {
                controllerAnimSetStateIfChanged(gCurrentActor, animId, 0, 0);
            }
            controllerApplyMotionWindow(gCurrentActor, selfAnim, targetAnim->frame);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    f32 lightLevel;
    f32 centerX;
    f32 centerZ;
    f32 offsetX;
    f32 offsetZ;
    f32 velX;
    f32 velZ;
    s16 bobAngle;
    s16 fireCooldown;
    s16 timeLimit;
    u8 unk22;
    u8 counterTextId;
    u8 rollTimer;
    u8 pad25;
    s16 shownCount;
    s16 targetsLeft;
    s8 respawnTimers[1];
} SearchlightGameState;

typedef struct {
    Actor *game;
    s16 heading;
    char pad6[2];
    f32 radius;
    s16 retargetTimer;
} SearchlightTargetState;


void bonusSearchlightSeekGameUpdate(void) {
    f32 sinYaw;
    f32 cosYaw;
    f32 targetOffsetZ;
    f32 scale;
    f32 targetOffsetX;
    f32 velX;
    f32 stickY;
    SearchlightGameState *subExt = gCurrentActor->customState;
    SearchlightTargetState *spawnExt;
    s32 i;
    s32 pad;
    s16 spawnAngle;
    if (!(gCurrentActor->flags & 0x10)) {
        gPrimaryPlayerActor->state = 0x77;
        gPrimaryPlayerActor->unk155 = 0;
        gPrimaryPlayerActor->unk144 = 1;
        subExt->lightLevel = 1.0f;
        subExt->centerX = gCurrentActor->x;
        subExt->centerZ = gCurrentActor->z;
        switch (gCurrentMap) {
            case 0x67:
                subExt->targetsLeft = 4;
                D_8002D90C = 1.0f;
                break;
            case 0x8A:
                subExt->targetsLeft = 6;
                D_8002D90C = 1.3f;
                break;
            case 0x8B:
                subExt->targetsLeft = 8;
                D_8002D90C = 1.6f;
                break;
            case 0x8C:
                subExt->targetsLeft = 0xA;
                D_8002D90C = 1.9f;
                break;
        }
        subExt->rollTimer = 0;
        subExt->shownCount = subExt->targetsLeft;
        subExt->timeLimit = 0x3C;
        subExt->counterTextId = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(subExt->counterTextId, 0.0f);
        gCurrentActor->sub4->scaleX = 0.33f;
        gCurrentActor->sub4->scaleY = 0.33f;
        gCurrentActor->sub4->scaleZ = 0.33f;
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->state = 3;
        subExt->velX = 0.0;
        subExt->velZ = 0.0;
        subExt->offsetX = 0.0;
        subExt->offsetZ = 0.0;
        subExt->lightLevel = 1.0;
        i = 0;
        do {
            subExt->respawnTimers[i] = 1;
            i++;
        } while (i != 1);
    }
    for (i = 0; i < 1; i++) {
        if (subExt->respawnTimers[i] > 0) {
            subExt->respawnTimers[i] -= 1;
            if (subExt->respawnTimers[i] == 0 && actorSpawn(0x14B, 0x21) != 0) {
                spawnExt = gSpawnedActor->customState;
                spawnExt->game = gCurrentActor;
                spawnExt->retargetTimer = 2;
                spawnExt->retargetTimer = (randomLcgNext() & 0x3F) + 0xF;
                spawnExt->heading = randomLcgNext() & 0xF;
                spawnExt->radius = randomFloat() * 40.0 + 15.0;
                spawnAngle = spawnExt->heading * 0xC8 - 0x578;
                gSpawnedActor->x = mathSinF(spawnAngle) * spawnExt->radius + subExt->centerX;
                gSpawnedActor->y = gCurrentActor->y;
                gSpawnedActor->z = mathCosF(spawnAngle) * spawnExt->radius + subExt->centerZ;
            }
        }
    }
    subExt->bobAngle += 0x19;
    if (gCurrentActor->state == 0 || gCurrentActor->state == 1) {
        subExt->lightLevel = subExt->lightLevel - 0.03333333333333333;
        if (subExt->lightLevel < 0.0) {
            subExt->lightLevel = 0.0;
        }
    } else {
        subExt->lightLevel = subExt->lightLevel + 0.03333333333333333;
        if (subExt->lightLevel > 1.0) {
            subExt->lightLevel = 1.0;
        }
    }
    lightSetColor(subExt->lightLevel, subExt->lightLevel, subExt->lightLevel, -1);
    switch (gCurrentActor->state) {
        case 0: {
            sinYaw = mathSinF(gPlayerSlots[gCurrentPlayerIndex].camYawInt);
            cosYaw = mathCosF(gPlayerSlots[gCurrentPlayerIndex].camYawInt);
            velX = subExt->velX;
            targetOffsetZ = subExt->velZ;
            targetOffsetX = D_807ECDEC->stick_x * 0.06f;
            stickY = D_807ECDEC->stick_y * 0.06f;
            velX = ((targetOffsetX * cosYaw) - (stickY * sinYaw)) - velX;
            subExt->velX = subExt->velX + velX * 0.155f;
            subExt->velZ = subExt->velZ + ((targetOffsetX * sinYaw + stickY * cosYaw) - targetOffsetZ) * 0.25f;
            subExt->offsetX = subExt->offsetX + subExt->velX;
            subExt->offsetZ = subExt->offsetZ - subExt->velZ;
            if (subExt->shownCount == 0) {
                gCurrentActor->state = 5;
            }
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 6;
            }
            if (subExt->fireCooldown > 0) {
                subExt->fireCooldown = subExt->fireCooldown - 1;
            }
            if (subExt->fireCooldown <= 0 && (*gPlayerSlots[gCurrentPlayerIndex].heldButtonsPtr & 0xE000)) {
                sfxPlayOnFreeSlot(0x59, 0x7FFF, 63.0f, 1.0, 0x1E, 0);
                targetOffsetZ = mathSinF(gPlayerSlots->camYawInt) * 30.0f + gPlayerSlots->camX;
                scale = gPlayerSlots->camY - 25.0f;
                targetOffsetX = mathCosF(gPlayerSlots->camYawInt) * 30.0f + gPlayerSlots->camZ;
                projectileSetTargetCoords(targetOffsetZ, scale, targetOffsetX);
                projectileAimAndSpawn(0x23, 1, 0.8f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 625.0f, gCurrentActor);
                subExt->fireCooldown = 0x1E;
            }
            break;
        }
        case 3:
            if (gGameMode != 1) {
                gCurrentActor->state = 4;
                hudSpawnCountdownTimer(0xDC, 0x2A, subExt->timeLimit);
                resQueueAttachActor(gCurrentActor, 0, 0xC);
            }
            break;
        case 4:
            if (!(gCurrentActor->flags & 0x02000000)) {
                gCurrentActor->state = 0;
                hudCountdownTimerStart(gCurrentActor->parentActor);
                sfxAllocateChannel(8, 1.0);
            }
            break;
        case 5:
        case 6:
            if (gCurrentActor->state == 6) {
                bonusEndLose(0, 1);
            } else {
                bonusEndWin(0, 0);
            }
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 7;
            break;
    }
    targetOffsetZ = subExt->offsetX;
    targetOffsetX = subExt->offsetZ;
    cosYaw = sqrtf(targetOffsetZ * targetOffsetZ + targetOffsetX * targetOffsetX);
    if (cosYaw > 110.0f) {
        scale = 110.0f / cosYaw;
        subExt->offsetX = targetOffsetZ * scale;
        subExt->offsetZ = targetOffsetX * scale;
    }
    gCurrentActor->x = mathSinF(subExt->bobAngle) * 5.0 + (subExt->centerX + subExt->offsetX);
    gCurrentActor->z = mathCosF(subExt->bobAngle * 2) * 2.0 + (subExt->centerZ + subExt->offsetZ);
    gPrimaryPlayerActor->x = subExt->centerX + subExt->offsetX * 0.5f;
    gPrimaryPlayerActor->y = gCurrentActor->y;
    gPrimaryPlayerActor->z = subExt->centerZ + subExt->offsetZ * 0.5f;
    renderCallbacksRegister(func_8002CC08, gCurrentActor, 3);
    lightAdd(gCurrentActor->x, gCurrentActor->y + 25.0, gCurrentActor->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 25.0f, 1, 0xFF, 0xFF, 0xFF);
}


void bonusSearchlightSeekTargetUpdate(void) {
    s32 pad[3];
    f32 speed;
    s32 pad2[3];
    f32 targetX, targetZ;
    s16 angle;
    s32 i;
    Actor *targetOwner;
    SearchlightTargetState *spawnLink = gCurrentActor->customState;
    SearchlightGameState *targetExt;

    targetOwner = spawnLink->game;
    targetExt = targetOwner->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x232);
        gCurrentActor->unk144 = 0x24;
        gCurrentActor->sub4->scaleX = 0.25f;
        gCurrentActor->sub4->scaleY = 0.25f;
        gCurrentActor->sub4->scaleZ = 0.25f;
    }
    if (gCurrentActor->state == 0) {
        speed = D_8002D90C;
        angle = spawnLink->heading * 0xC8 - 0x578;
        targetX = mathSinF(angle) * spawnLink->radius + targetExt->centerX;
        targetZ = mathCosF(angle) * spawnLink->radius + targetExt->centerZ;
        gCurrentActor->yaw -= mathAngleSignedDistance(mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, targetX, targetZ) + 0x800, gCurrentActor->yaw) >> 5;
        gCurrentActor->x += mathSinF(gCurrentActor->yaw) * speed;
        gCurrentActor->z += mathCosF(gCurrentActor->yaw) * speed;
        spawnLink->retargetTimer--;
        if (spawnLink->retargetTimer <= 0) {
            spawnLink->retargetTimer = (randomLcgNext() & 0x3F) + 0xF;
            spawnLink->heading += (randomLcgNext() & 0xF) + 3;
            spawnLink->radius = 40.0 * randomFloat() + 10.0;
        }
        if (gActorGlobalState.unk15 == 1) {
            gCurrentActor->alpha = 0xFF;
            gCurrentActor->flags &= ~0x8000;
            actorScriptStart(gCurrentActor, 0x332);
            gCurrentActor->state = 1;
            sfxPlayOnFreeSlot(0x16, 0x7FFF, 63.0f, 1.0f, 0, 0);
            if (targetExt->targetsLeft != 0) {
                targetExt->targetsLeft--;
            }
            for (i = 0; i < 1; i++) {
                if (targetExt->respawnTimers[i] == 0) {
                    targetExt->respawnTimers[i] = 0x1E;
                    i = 1;
                }
            }
        }
    } else {
        gCurrentActor->alpha -= 4;
        if (gCurrentActor->alpha < 5) {
            gCurrentActor->alpha = 0;
            actorDespawn(gCurrentActor);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

Gfx *func_8002CC08(Gfx *gdl, Actor *actor) {
    SearchlightGameState *subExt;
    f32 projX;
    f32 projY;
    s32 state;
    s16 screenX;
    s16 screenY;

    subExt = actor->customState;
    camProjectToScreen(actor->x, actor->y, actor->z, &projX, &projY, 0, 1.0f, gCurrentPlayerIndex);
    screenX = (f32)(projX * 4.0);
    screenY = (f32)(projY * 4.0);
    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, D_1000118);
    gSPMatrix(gdl++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    state = actor->state;
    if (state == 0 || state == 1) {
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX - 0x34, screenY - 0x34, 3.2f, 3.2f, 0xE1, 0.0f);
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX + 0x34, screenY - 0x34, 3.2f, 3.2f, 0x13B, 0.0f);
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX + 0x34, screenY + 0x34, 3.2f, 3.2f, 0x2D, 0.0f);
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX - 0x34, screenY + 0x34, 3.2f, 3.2f, 0x87, 0.0f);
    }
    gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (actor->state) {
    case 7:
        do {
        } while (0); // FAKE: empty do/while(0) moves the spill temps up one word (sp+0x50/0x54/0x4C)
        break;
    case 0:
    case 1:
        gdl = hudDrawRollingCounter(textDrawAnimated(gdl, subExt->counterTextId, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &subExt->shownCount, subExt->targetsLeft, &subExt->rollTimer);
        break;
    }
    return gdl;
}

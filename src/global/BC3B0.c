#include "common.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/12E800.h"
#include "proto/global/201B0.h"
#include "proto/global/5E2F0.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/A7710.h"
#include "proto/global/BC3B0.h"

extern Actor *gCurrentActor;

typedef struct BC3B0Cursor {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 vx;
    /* 0xC */ f32 vy;
    /* 0x10 */ s16 lockX;
    /* 0x12 */ s16 lockY;
    /* 0x14 */ s16 lockZ;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 beepInterval;
} BC3B0Cursor;

typedef struct BC3B0CursorActor {
    Actor base;
    /* 0x178 */ BC3B0Cursor *cursor;
} BC3B0CursorActor;

extern Gfx D_1000118;
extern Mtx D_2000080;

Gfx *actorCursorDrawSprite(Gfx *dl, Actor *actor) {
    BehaviourWorkState *work = actor->customState;
    BC3B0Cursor *cursor = ((BC3B0CursorActor *)actor)->cursor;

    gDPPipeSync(dl++);
    if (actor->state == 0x11) {
        gDPSetPrimColor(dl++, 0, 0, 200, 0, 0, 255);
    } else if (work->timer != 0) {
        gDPSetPrimColor(dl++, 0, 0, 0, 200, 0, 255);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 220, 180, 0, 255);
    }
    gDPSetCombineMode(dl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(dl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(dl++, &D_1000118);
    gSPMatrix(dl++, &D_2000080, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, cursor->x, cursor->y, 0.5f, 0.5f, 0x2D, 0.0f);
}

Gfx *actorCursorDrawBurst(Gfx *dl, Actor *actor) {
    BehaviourWorkState *work = actor->customState;
    BC3B0Cursor *cursor = ((BC3B0CursorActor *)actor)->cursor;
    f32 t;
    f32 x;
    f32 y;
    s16 angle;
    s16 i;

    t = work->timer / 20.0f;
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0, 200, 0, 255);
    dl = renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, cursor->x, cursor->y, t * 7.5 + 0.5, t * 7.5 + 0.5, 90.0f * t + 45.0f, 0.0f);
    angle = 2048.0f * t;
    for (i = 0; i < 5; i++) {
        x = cursor->x + (0.0f - cursor->x) * t;
        y = cursor->y + (240.0f - cursor->y) * t;
        gDPSetPrimColor(dl++, 0, 0, 0, 200, 0, -255.0f * t + 255.0f);
        dl = renderRotatedSprite(dl, 0x42, 3, 1, 0x40, 0x40, x, 0x78, 0.5f, 4.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, 0x42, 3, 1, 0x40, 0x40, 0xA0, y, 0.5f, 5.0f, 0x5A, 0.0f);
        t += 0.1 * mathSinF(angle);
        t = (t > 1.0) ? 1.0 : t;
    }
    return dl;
}

extern s32 gCurrentMap;

void actorCursorFireProjectile(void *unused) {
    s32 id;

    if (gCurrentMap != 0x5A && gCurrentMap != 0x64) {
        id = 0x1E;
    } else {
        id = 0x63;
    }
    projectileSetTargetCoords(gBehaviourTargetActor->x, gBehaviourTargetActor->y + 100.0f, gBehaviourTargetActor->z);
    projectileAimAndSpawn(id, 1, 0.5f, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, 285.0f, gCurrentActor);
}

extern s16 gScreenWidth;
extern s16 gScreenHeight;

void actorCursorSteer(BC3B0Cursor *c, f32 tx, f32 ty) {
    if (tx < c->x) {
        c->vx -= 0.6;
        if (c->vx < -5.0f) {
            c->vx = -5.0f;
        }
    } else if (c->x < tx) {
        c->vx += 0.6;
        if (c->vx > 5.0f) {
            c->vx = 5.0f;
        }
    }
    if (ty < c->y) {
        c->vy -= 0.6;
        if (c->vy < -5.0f) {
            c->vy = -5.0f;
        }
    } else if (c->y < ty) {
        c->vy += 0.6;
        if (c->vy > 5.0f) {
            c->vy = 5.0f;
        }
    }
    c->x = MIN(MAX(c->x + c->vx, 0.0f), gScreenWidth);
    c->y = MIN(MAX(c->y + c->vy, 0.0f), gScreenHeight);
}

extern s32 gGlobalOverlayFlags;
extern s32 gGlobalCutsceneFlags;

void actorUpdateLockOnCursor(void) {
    BC3B0Cursor *c;
    f32 screenX;
    f32 screenY;

    c = ((BC3B0CursorActor *)gCurrentActor)->cursor;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x60;
        gGlobalOverlayFlags |= 2;
        hudSpawnCountdownTimer(0xDC, 0x2A, gBehaviourExtraState->unkAWide ? gBehaviourExtraState->unkAWide : 10);
        gBehaviourWorkState->unk2E = gBehaviourExtraState->unkAWide != 0 ? 0xF : 0x78;
        if (gBehaviourExtraState->unkAWide != 0) {
            c->beepInterval = gBehaviourExtraState->unkAWide;
        } else {
            c->beepInterval = 10.0f;
        }
    }
    if (gBehaviourWorkState->unk2E != 0) {
        if (camIsCutsceneActive() == 0) {
            gBehaviourWorkState->unk2E--;
        }
        if (gBehaviourWorkState->unk2E != 0) {
            return;
        }
        gCurrentActor->state = 0x23;
        gCurrentActor->unk155 = 0;
        sfxPlayOnFreeSlot(0x1A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
        hudCountdownTimerStart(gCurrentActor->parentActor);
        gGlobalCutsceneFlags |= 1;
        gGlobalOverlayFlags |= 2;
    }
    if (gCurrentActor->parentActor->state == 5 && gCurrentActor->state != 0x11) {
        if (gBehaviourTargetActor->hasArcBounds != 0) {
            gBehaviourTargetActor->yaw = mathAngleArcMidpoint(gBehaviourTargetActor->arcYawMin, gBehaviourTargetActor->arcYawMax);
        }
        camStartPath(0, 6, 5);
        gCurrentActor->state = 0x11;
        gCurrentActor->unk155 = 0;
        c->lockX = gBehaviourTargetActor->x;
        c->lockY = gBehaviourTargetActor->y + gBehaviourTargetActor->eyeHeight;
        c->lockZ = gBehaviourTargetActor->z;
        gBehaviourWorkState->timer = 0x14;
    }
    gCurrentActor->soundSlots[0]++;
    if (c->beepInterval < gCurrentActor->soundSlots[0]) {
        sfxPlayOnFreeSlot(0x15B, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
        gCurrentActor->soundSlots[0] = 0;
        if (c->beepInterval > 2.0f) {
            c->beepInterval -= 0.18;
        }
    }
    if (gCurrentActor->state != 0x11) {
        if (gCurrentActor->state == 0x23 && camIsFollowingActive() == 0) {
            camProjectToScreen(gBehaviourTargetActor->x, gBehaviourTargetActor->y + gBehaviourTargetActor->eyeHeight, gBehaviourTargetActor->z, &screenX, &screenY, 0, 1.0f, 0);
            actorCursorSteer(c, screenX, screenY);
        }
    } else {
        if (camIsFollowingActive() == 0) {
            renderCallbacksRegister(actorCursorDrawBurst, gCurrentActor, 3);
        }
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer--;
            if (gBehaviourWorkState->timer == 5) {
                sfxPlayOnFreeSlot(0x175, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        } else {
            actorCursorFireProjectile(c);
            gBehaviourWorkState->unk2E = 0x64;
            if (gBehaviourExtraState->unkAWide != 0) {
                c->beepInterval = gBehaviourExtraState->unkAWide;
            } else {
                c->beepInterval = 10.0f;
            }
        }
        camProjectToScreen(c->lockX, c->lockY, c->lockZ, &c->x, &c->y, 0, 1.0f, 0);
    }
    if (camIsFollowingActive() == 0) {
        renderCallbacksRegister(actorCursorDrawSprite, gCurrentActor, 3);
    }
}

typedef struct BC3B0EmitterActor {
    Actor base;
    /* 0x178 */ s16 *startDelay;
    /* 0x17C */ s16 *burstCooldown;
} BC3B0EmitterActor;

extern u8 D_807201D4[];

void actorUpdatePeriodicParticleEmitter(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourWorkState->scale = gBehaviourExtraState->unkB;
        actorSetCollisionRadius(gCurrentActor, 300.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 280.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
    }
    if (gBehaviourWorkState->scale <= 0.001) {
        gBehaviourWorkState->timer = gBehaviourExtraState->unkA;
        gBehaviourWorkState->scale = gBehaviourExtraState->unkB;
        actorSetNodeFlag(gCurrentActor, 1);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x182, 0xFF, 0x7F, 0x1E);
    }
    gBehaviourWorkState->scale -= 1.0;
    if (gBehaviourWorkState->timer != 0 && gFrameCounter % 5 == 0) {
        effectSetDuration(3);
        effectSetDepth(1);
        effectSetSpeed(-0x1C2);
        effectSetCallback(func_80717D4C);
        effectCreateAtPosition(D_807201D4, 1.2f, gCurrentActor->x, gCurrentActor->y + 7.0, gCurrentActor->z);
    }
    if (gBehaviourWorkState->timer != 0) {
        lightAdd(gCurrentActor->x, gCurrentActor->y + 7.0, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 200.0f, 0, 0xFF, 0xC8, 0);
        gBehaviourWorkState->timer--;
        if (gBehaviourWorkState->timer == 0) {
            actorClearNodeFlag(gCurrentActor, 1);
        }
    }
}

void actorUpdateAimedProjectileEmitter(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourWorkState->unk2E = gBehaviourAnimState->unkB;
    }
    if (gBehaviourWorkState->unk2E == 0) {
        gBehaviourWorkState->timer = gBehaviourAnimState->unkA;
        gBehaviourWorkState->unk2E = gBehaviourAnimState->unkB;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x182, 0xFF, 0x7F, 0x1E);
    }
    gBehaviourWorkState->unk2E--;
    if (gBehaviourWorkState->timer != 0 && gFrameCounter % 5 == 0) {
        projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        projectileAimAndSpawn(0x51, 1, 0.3f, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, 80.0f, gCurrentActor);
    }
    if (gBehaviourWorkState->timer != 0) {
        lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 200.0f, 0, 0xFF, 0xC8, 0);
        gBehaviourWorkState->timer--;
    }
}

void func_806B8878(void) {
    actorUpdateBurstProjectileEmitter();
}

void func_806B8898(void) {
    actorUpdateBurstProjectileEmitter();
}

void actorUpdateBurstProjectileEmitter(void) {
    s16 *delay = ((BC3B0EmitterActor *)gCurrentActor)->startDelay;
    s16 *cooldown = ((BC3B0EmitterActor *)gCurrentActor)->burstCooldown;
    s16 kind;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourWorkState->scale = gBehaviourExtraState->unkB;
        *delay = gBehaviourExtraState->unkD;
    }
    if (*delay != 0) {
        (*delay)--;
        return;
    }
    if (gBehaviourWorkState->scale <= 0.001) {
        gBehaviourWorkState->timer = gBehaviourExtraState->unkA;
        gBehaviourWorkState->scale = gBehaviourExtraState->unkB;
        *cooldown = 0;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17, 0xFF, 0x7F, 0x19);
    }
    gBehaviourWorkState->scale -= 1.0;
    if (gBehaviourWorkState->timer != 0 && *cooldown == 0) {
        projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        switch (gCurrentActor->actorType) {
            case 0xDC:
                kind = 0x37;
                break;
            case 0xDF:
                kind = 0x1E;
                break;
        }
        projectileSpawnNodeEntry(kind, 0, 0.6f, gCurrentActor->yaw, gBehaviourExtraState->targetSpeed * 10, 0.0f, 0);
        gBehaviourWorkState->timer--;
        *cooldown = gBehaviourExtraState->scale;
    }
    if (*cooldown != 0) {
        (*cooldown)--;
    }
}

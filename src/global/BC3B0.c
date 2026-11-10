#include "common.h"
#include "actor.h"
#define PROTO_SKIP_hudSpawnCountdownTimer // FAKE: callee prototype steer
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
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gBossFightPhase;

typedef struct BC3B0CursorSub174 {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ s16 unk2C;
} BC3B0CursorSub174;

typedef struct BC3B0CursorActor {
    /* 0x000 */ u8 pad0[0x6E];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x104];
    /* 0x174 */ BC3B0CursorSub174 *unk174;
    /* 0x178 */ f32 *unk178;
} BC3B0CursorActor;

#define BC3B0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern u8 D_1000118[];
extern u8 D_2000080[];


Gfx *actorCursorDrawSprite(Gfx *dl, Actor *actor) {
    BC3B0CursorSub174 *sub = ((BC3B0CursorActor *)actor)->unk174;
    f32 *pos = ((BC3B0CursorActor *)actor)->unk178;

    gDPPipeSync(dl++);
    if (actor->state == 0x11) {
        gDPSetPrimColor(dl++, 0, 0, 200, 0, 0, 255);
    } else if (sub->unk2C != 0) {
        gDPSetPrimColor(dl++, 0, 0, 0, 200, 0, 255);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 220, 180, 0, 255);
    }
    BC3B0_WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    BC3B0_WRITE_GFX(dl++, 0xE200001C, 0x504240);
    BC3B0_WRITE_GFX(dl++, 0xDE000000, D_1000118);
    BC3B0_WRITE_GFX(dl++, 0xDA380007, D_2000080);
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, (s32)pos[0], (s32)pos[1], 0.5f, 0.5f, 0x2D, 0.0f);
}

f32 mathSinF(s16);

Gfx *actorCursorDrawBurst(Gfx *dl, Actor *actor) {
    BC3B0CursorSub174 *sub = ((BC3B0CursorActor *)actor)->unk174;
    f32 *pos = ((BC3B0CursorActor *)actor)->unk178;
    f32 t;
    f32 x;
    f32 y;
    s16 angle;
    s16 i;

    t = sub->unk2C / 20.0f;
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0, 200, 0, 255);
    dl = renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, (s32)pos[0], (s32)pos[1], t * 7.5 + 0.5, t * 7.5 + 0.5, (s32)(90.0f * t + 45.0f), 0.0f);
    angle = (s16)(s32)(2048.0f * t);
    i = 0;
    do {
        x = (0.0f - pos[0]) * t + pos[0];
        y = (240.0f - pos[1]) * t + pos[1];
        gDPSetPrimColor(dl++, 0, 0, 0, 200, 0, (u32)(-255.0f * t + 255.0f));
        dl = renderRotatedSprite(renderRotatedSprite(dl, 0x42, 3, 1, 0x40, 0x40, (s32)x, 0x78, 0.5f, 4.0f, 0, 0.0f), 0x42, 3, 1, 0x40, 0x40, 0xA0, (s32)y, 0.5f, 5.0f, 0x5A, 0.0f);
        t += 0.1 * mathSinF(angle);
        i++;
        t = (t > 1.0) ? 1.0 : t;
    } while (i < 5);
    return dl;
}

extern s32 gCurrentMap;

void actorCursorFireProjectile(void *unused) {
    s32 id;

    if ((gCurrentMap != 0x5A) && (gCurrentMap != 0x64)) {
        id = 0x1E;
    } else {
        id = 0x63;
    }
    projectileSetTargetCoords(gBehaviourTargetActor->x, gBehaviourTargetActor->y + 100.0f, gBehaviourTargetActor->z);
    projectileAimAndSpawn(id, 1, 0.5f, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, 285.0f, gCurrentActor);
}

typedef struct BC3B0Cursor {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 vx;
    /* 0xC */ f32 vy;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 unk18;
} BC3B0Cursor;

#define BC3B0MAX(a, b) ((a) > (b) ? (a) : (b))
#define BC3B0MIN(a, b) ((a) < (b) ? (a) : (b))

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
    c->x = BC3B0MIN(BC3B0MAX(c->x + c->vx, 0.0f), gScreenWidth);
    c->y = BC3B0MIN(BC3B0MAX(c->y + c->vy, 0.0f), gScreenHeight);
}

#define BC3B0CA ((BC3B0CursorActor *)gCurrentActor)

extern s32 gGlobalOverlayFlags;
extern s32 gGlobalCutsceneFlags;

void hudSpawnCountdownTimer(s32, s32, u8, s32 *);

void func_806B7EA0(void) {
    BC3B0Cursor *c;
    f32 screenX;
    f32 screenY;
    c = (BC3B0Cursor *)BC3B0CA->unk178;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x60;
        gGlobalOverlayFlags |= 2;
        hudSpawnCountdownTimer(0xDC, 0x2A, gBehaviourExtraState->unkAWide ? gBehaviourExtraState->unkAWide : 10, &gGlobalOverlayFlags);
        gBehaviourWorkState->unk2E = gBehaviourExtraState->unkAWide != 0 ? 0xF : 0x78;
        if (gBehaviourExtraState->unkAWide != 0) {
            c->unk18 = gBehaviourExtraState->unkAWide;
        } else {
            c->unk18 = 10.0f;
        }
    }
    if (gBehaviourWorkState->unk2E != 0) {
        if (camIsCutsceneActive() == 0) {
            gBehaviourWorkState->unk2E = gBehaviourWorkState->unk2E - 1;
        }
        if (gBehaviourWorkState->unk2E != 0) {
            return;
        }
        gCurrentActor->state = 0x23;
        gCurrentActor->unk155 = 0;
        sfxPlayOnFreeSlot(0x1A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
        actorSetStateTwo(gCurrentActor->parentActor);
        gGlobalCutsceneFlags |= 1;
        gGlobalOverlayFlags |= 2;
    }
    if (((Actor *)gCurrentActor->parentActor)->state == 5 && gCurrentActor->state != 0x11) {
        if (gBehaviourTargetActor->hasArcBounds != 0) {
            gBehaviourTargetActor->yaw = mathAngleArcMidpoint(gBehaviourTargetActor->arcYawMin, gBehaviourTargetActor->arcYawMax);
        }
        camStartPath(0, 6, 5);
        gCurrentActor->state = 0x11;
        gCurrentActor->unk155 = 0;
        c->unk10 = (s32)gBehaviourTargetActor->x;
        c->unk12 = (s32)(gBehaviourTargetActor->y + (u32)gBehaviourTargetActor->eyeHeight);
        c->unk14 = (s32)gBehaviourTargetActor->z;
        gBehaviourWorkState->timer = 0x14;
    }
    BC3B0CA->unk6E = BC3B0CA->unk6E + 1;
    if (c->unk18 < (f32)BC3B0CA->unk6E) {
        sfxPlayOnFreeSlot(0x15B, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
        BC3B0CA->unk6E = 0;
        if (c->unk18 > 2.0f) {
            c->unk18 -= 0.18;
        }
    }
    if (gCurrentActor->state != 0x11) {
        if (gCurrentActor->state == 0x23 && camIsFollowingActive() == 0) {
            camProjectToScreen(gBehaviourTargetActor->x, gBehaviourTargetActor->y + (u32)gBehaviourTargetActor->eyeHeight, gBehaviourTargetActor->z, &screenX, &screenY, 0, 1.0f, 0);
            actorCursorSteer(c, screenX, screenY);
        }
    } else {
        if (camIsFollowingActive() == 0) {
            renderCallbacksRegister(actorCursorDrawBurst, gCurrentActor, 3);
        }
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer = gBehaviourWorkState->timer - 1;
            if (gBehaviourWorkState->timer == 5) {
                sfxPlayOnFreeSlot(0x175, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        } else {
            actorCursorFireProjectile(c);
            gBehaviourWorkState->unk2E = 0x64;
            if (gBehaviourExtraState->unkAWide != 0) {
                c->unk18 = gBehaviourExtraState->unkAWide;
            } else {
                c->unk18 = 10.0f;
            }
        }
        camProjectToScreen(c->unk10, c->unk12, c->unk14, &c->x, &c->y, 0, 1.0f, 0);
    }
    if (camIsFollowingActive() == 0) {
        renderCallbacksRegister(actorCursorDrawSprite, gCurrentActor, 3);
    }
}

typedef struct BC3B0EmitterActor {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ s16 *unk178;
    /* 0x17C */ s16 *unk17C;
} BC3B0EmitterActor;

#define BC3B0EA ((BC3B0EmitterActor *)gCurrentActor)

extern u32 gFrameCounter;
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
    gBehaviourWorkState->scale = gBehaviourWorkState->scale - 1.0;
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
    s16 *a = BC3B0EA->unk178;
    s16 *b = BC3B0EA->unk17C;
    s16 kind;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourWorkState->scale = gBehaviourExtraState->unkB;
        *a = gBehaviourExtraState->unkD;
    }
    if (*a != 0) {
        *a = *a - 1;
        return;
    }
    if (gBehaviourWorkState->scale <= 0.001) {
        gBehaviourWorkState->timer = gBehaviourExtraState->unkA;
        gBehaviourWorkState->scale = gBehaviourExtraState->unkB;
        *b = 0;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17, 0xFF, 0x7F, 0x19);
    }
    gBehaviourWorkState->scale = gBehaviourWorkState->scale - 1.0;
    if (gBehaviourWorkState->timer != 0 && *b == 0) {
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
        *b = gBehaviourExtraState->scale;
    }
    if (*b != 0) {
        *b = *b - 1;
    }
}

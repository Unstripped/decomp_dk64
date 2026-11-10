#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorListLookupEntry // FAKE: callee prototype steer
#define PROTO_SKIP_effectSetColor // FAKE: callee prototype steer
#define PROTO_SKIP_flagGet // FAKE: callee prototype steer
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/127B00.h"
#include "proto/global/1295B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8D3E0.h"
#include "proto/global/AA960.h"
#include "proto/global/CC800.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

typedef struct SfxTableEntry {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
} SfxTableEntry; /* size = 6 */

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalOverlayFlags;
extern u32 gGlobalCutsceneFlags;
extern u8 gPlayerCount;
extern SfxTableEntry D_80750400[];

extern u8 D_807204BC[];
extern u8 D_80720508[];
extern u8 D_807205C4[];
extern u8 D_807205E8[];
extern u8 D_80720710[];
extern u8 D_80720768[];
extern u8 D_807207BC[];
extern u8 D_807207E0[];
extern u8 D_807209EC[];
extern u8 D_80720A10[];
extern u8 D_80720A34[];
extern u8 D_80720A58[];
extern u8 D_807211D0[];
extern u8 D_80721378[];

void effectSetColor(s32, s32, s32, u8); // FAKE: callee prototype steer

void sfxSpawnTableNodes(Actor *actor) {
    s32 i;
    s32 found;
    s32 j;
    s16 step;
    s16 offset;

    i = 0;
    found = 0;
    offset = 0;
    if (gPlayerCount >= 2) {
        return;
    }
    if (gGlobalOverlayFlags & 0x4000) {
        return;
    }
    while (found == 0 && D_80750400[i].unk0 != 0) {
        if (D_80750400[i].unk0 == actor->actorType) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found == 0) {
        return;
    }
    if (D_80750400[i].unk4 != 0) {
        sfxAllocateChannel(D_80750400[i].unk4, 1.0f);
    }
    step = (s16)(0xFFF / D_80750400[i].unk5);
    for (j = 0; j < D_80750400[i].unk5; j++) {
        actorSpawnNodeEntryScaled(D_80750400[i].unk2, actor->x, actor->y, actor->z, offset, 1, -1, 0);
        offset = offset + step;
    }
}

void actorSpawnNodeEntryScaled(s16 actorType, f32 x, f32 y, f32 z, s32 yaw, s32 pitch, s32 roll, s32 extraParam) {
    s32 pad[6];
    f32 vec[3];
    f32 scale;

    scale = 0.15f;
    if (gGlobalCutsceneFlags & 0x10) {
        scale = scale + scale;
    }
    vec[0] = (f32)(u8)pitch;
    vec[1] = (f32)(s16)yaw;
    vec[2] = (f32)(s16)roll;
    actorListSpawnNodeEntry(actorType, x, y, z, 0, scale, extraParam, vec);
}

void effectSpawnAttachedSprite(void *targetState, void *spriteAsset, f32 scale) {
    if (gGlobalCutsceneFlags & 0x10) {
        scale = scale + scale;
    }
    effectSetDuration(-1);
    effectSetDepth(1);
    effectSetMode(2);
    *(s32 *)((u8 *)targetState + 4) = effectCreateAtActorBone(spriteAsset, scale * 0.35, gCurrentActor, 1, 2);
}

void func_806A5F44(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(temp, D_80720710, 1.0f);
    }
}

void func_806A5FA4(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(temp, D_80720508, 1.0f);
    }
}

void effectSpawnAttachedSpriteColored(void *spriteAsset, s32 characterId) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        if (characterId != gPrimaryPlayerActor->actorType) {
            effectSetColor(0xFF, 0xFF, 0xFF, 0x64);
        }
        effectSpawnAttachedSprite(temp, spriteAsset, 1.0f);
    }
}

void effectSpawnAttachedSpriteColoredType3(void) {
    effectSpawnAttachedSpriteColored(D_807209EC, 3);
}

void effectSpawnAttachedSpriteColoredType6(void) {
    effectSpawnAttachedSpriteColored(D_80720A10, 6);
}

void effectSpawnAttachedSpriteColoredType4(void) {
    effectSpawnAttachedSpriteColored(D_807207E0, 4);
}

void effectSpawnAttachedSpriteColoredType2(void) {
    effectSpawnAttachedSpriteColored(D_80720A34, 2);
}

void effectSpawnAttachedSpriteColoredType5(void) {
    effectSpawnAttachedSpriteColored(D_80720A58, 5);
}

void func_806A615C(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSetScale(-0.35f, 0.35f);
        effectSpawnAttachedSprite(temp, D_80720768, 1.0f);
    }
}

void func_806A61D0(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(temp, D_807204BC, 1.0f);
    }
}

void func_806A6230(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        if ((gGlobalOverlayFlags & 0x80000) || (gGlobalOverlayFlags & 0x2000)) {
            gCurrentActor->unk15F = 1;
        }
        effectSpawnAttachedSprite(temp, D_807207BC, 1.0f);
    }
}

void effectSpawnA6230Wrapper(void) {
    func_806A6230();
}

void func_806A62D4(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSetColor(0xFF, 0xFF, 0, 0xFF);
        effectSpawnAttachedSprite(temp, D_807211D0, 1.5f);
    }
}

void func_806A6348(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(temp, D_807205C4, 1.0f);
    }
}

void func_806A63A8(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(temp, D_807205E8, 1.0f);
    }
}

void func_806A6408(void) {
    void *temp = gCurrentActor->customState;

    actorDropBounceExpireUpdate(12.0f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(temp, D_80721378, 2.0f);
    }
}

extern u8 D_807203B0;
extern u8 D_807203D4;
extern u8 D_807203F8;
extern u8 D_8072041C;
extern u8 D_80720440;

void func_806A6468(void) {
    void *state;
    void *anim;

    state = gCurrentActor->customState;
    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        switch (gPrimaryPlayerActor->actorType) {
        case 3:
            anim = &D_807203B0;
            break;
        case 2:
            anim = &D_8072041C;
            break;
        case 4:
            anim = &D_807203F8;
            break;
        case 6:
            anim = &D_807203D4;
            break;
        case 5:
            anim = &D_80720440;
            break;
        }
        effectSpawnAttachedSprite(state, anim, 1.0f);
        if (gCurrentActor->state == 0x63) {
            gCurrentActor->state = 1;
            gCurrentActor->unk15F = 2;
        }
    }
}

extern u8 D_80720EBC;
extern u8 D_80720EE8;
extern u8 D_80720F14;
extern u8 D_80720F40;
extern u8 D_80720F6C;

void func_806A6574(void) {
    void *state;
    void *anim;

    state = gCurrentActor->customState;
    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        switch (gPrimaryPlayerActor->actorType) {
        case 3:
            anim = &D_80720EE8;
            break;
        case 2:
            anim = &D_80720F40;
            break;
        case 4:
            anim = &D_80720F14;
            break;
        case 6:
            anim = &D_80720EBC;
            break;
        case 5:
            anim = &D_80720F6C;
            break;
        }
        effectSpawnAttachedSprite(state, anim, 1.0f);
    }
}

typedef struct BehaviourState {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ u8 *unk4;
    /* 0x8 */ u16 unk8;
    /* 0xA */ s16 unkA;
} BehaviourState;

typedef struct BehaviourConfig {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
} BehaviourConfig;

extern ActorGlobalState gActorGlobalState;
extern s16 D_8075038C;

void actorDropBounceExpireUpdate(f32 floorOffset) {
    BehaviourState *state;
    s32 v;

    state = (BehaviourState *)gCurrentActor->customState;
    if (gGlobalCutsceneFlags & 0x10) {
        floorOffset *= 2.0f;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = (u8)(s32)((BehaviourConfig *)gCurrentActor->spawnData)->unk0;
        *(s16 *)((u8 *)gCurrentActor + 0xEE) = (s16)(s32)((BehaviourConfig *)gCurrentActor->spawnData)->unk4;
        gCurrentActor->yaw = *(s16 *)((u8 *)gCurrentActor + 0xEE);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        state->unk0 = 0;
        state->unk1 = 0;
        state->unkA = (s16)(s32)((BehaviourConfig *)gCurrentActor->spawnData)->unk8;
        *(s16 *)((u8 *)gCurrentActor + 0xFA) = 0x270F;
    }
    if (gActorGlobalState.unk0 != 0) {
        gCurrentActor->state = gActorGlobalState.unk1[0];
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0) {
        if (actorAngleInArc(gCurrentActor, *(s16 *)((u8 *)gCurrentActor + 0xEE)) == 0) {
            s16 temp;
            s16 b;
            s16 c;

            temp = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
            b = (*(s16 *)((u8 *)gCurrentActor + 0xEE) + 0x800) & 0xFFF;
            c = temp - b;
            *(s16 *)((u8 *)gCurrentActor + 0xEE) = temp + c;
        }
    }
    switch (gCurrentActor->state) {
    case 0:
        break;
    case 1:
        gCurrentActor->unk144 = 0x1C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        *(f32 *)((u8 *)gCurrentActor + 0xC0) = (f32)((f64)((randomLcgNext() / 10000) % 200) * 0.5 + 220.0 - 50.0);
        if (!(gGlobalOverlayFlags & 0x4000) && (((u32)gCurrentActor->actorType < 0x4B) || ((u32)gCurrentActor->actorType >= 0x50))) {
            gCurrentActor->speedXZ = 30.0f;
        }
        gCurrentActor->state++;
    case 2:
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, floorOffset);
        *(f32 *)((u8 *)gCurrentActor + 0xC0) -= 20.0f;
        if (*(f32 *)((u8 *)gCurrentActor + 0xC0) < (f32)D_8075038C) {
            *(f32 *)((u8 *)gCurrentActor + 0xC0) = (f32)D_8075038C;
        }
        if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            switch (state->unk0) {
            case 0:
                if (gCurrentActor->unk15F != 1) {
                    state->unk1 = 1;
                }
                *(f32 *)((u8 *)gCurrentActor + 0xC0) = 150.0f;
                break;
            case 1:
                *(f32 *)((u8 *)gCurrentActor + 0xC0) = 100.0f;
                break;
            case 2:
                *(f32 *)((u8 *)gCurrentActor + 0xC0) = 50.0f;
                break;
            case 3:
                gCurrentActor->speedXZ = 0.0f;
                *(f32 *)((u8 *)gCurrentActor + 0xC0) = 0.0f;
                if (gCurrentActor->actorType == 0x8C) {
                    state->unk1 = 1;
                }
                if (gCurrentActor->actorType != 0x6E && gCurrentActor->actorType != 0x8C && !(gGlobalOverlayFlags & 0x4000) && gCurrentActor->unk15F != 2) {
                    state->unk8 = 0x64;
                    gCurrentActor->state = 3;
                } else {
                    gCurrentActor->state = 0x64;
                }
                break;
            }
            switch (gCurrentActor->actorType) {
            case 0x34:
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, (*(f32 *)((u8 *)gCurrentActor + 0xC0) + 105.0f), 0x7F, 0x1E);
                break;
            case 0x36:
                if (state->unk0 == 0) {
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1D1, 0xFF, 0x7F, 0xA);
                }
                break;
            default:
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 1, (*(f32 *)((u8 *)gCurrentActor + 0xC0) + 105.0f), 0x7F, 0x14);
                break;
            }
            state->unk0++;
        }
        break;
    case 3:
        if (camIsCutsceneActive() == 0) {
            state->unk8--;
        }
        if (state->unk8 == 0) {
            gCurrentActor->state = 4;
        }
        break;
    case 4:
        state->unk4[0x36D] -= 5;
        if ((s32)state->unk4[0x36D] < 0xA) {
            if ((gGlobalOverlayFlags & 0x10000) && actorTypeIsRespawnPickup(gCurrentActor->actorType) != 0) {
                func_806F5F2C(gCurrentActor->actorType, 0x258, (s16)(s32)gCurrentActor->x, (s16)(s32)gCurrentActor->y, (s32)gCurrentActor->z);
            }
            actorDespawn(gCurrentActor);
        }
        break;
    case 25:
        state->unk8 = 0x64;
        gCurrentActor->state = 3;
        state->unk1 = 1;
        break;
    }
}

typedef struct ActorConfig {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} ActorConfig;

typedef struct EffectState {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad3[1];
    u16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
} EffectState;

extern ActorGlobalState gActorGlobalState;
extern s16 D_80750384;
extern s16 D_8075038C;
extern f32 D_80750388;

typedef struct PhysicsActor {
    u8 pad0[0xC0];
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
} PhysicsActor;

#define AA960_PHY ((PhysicsActor *)gCurrentActor)


void actorBounceFadeInSpinUpdate(u8 fadeAlpha) {
    EffectState *state;
    s16 temp;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x801000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->state = (s32)((ActorConfig *)gCurrentActor->spawnData)->unk0;
        AA960_PHY->unkEE = ((ActorConfig *)gCurrentActor->spawnData)->unk4;
        gCurrentActor->yaw = AA960_PHY->unkEE;
        state->unk0 = 0;
        state->unk1 = 1;
        state->unkA = ((ActorConfig *)gCurrentActor->spawnData)->unk8;
        AA960_PHY->unkFA = 0x270F;
        func_806C9974(0, 0x40);
    }
    if ((f32)state->unk8 < 30.0f) {
        state->unk8++;
    }
    gCurrentActor->alpha = state->unk8 * 0.033333335f * 255.0f;
    if (gActorGlobalState.unk0 != 0) {
        gCurrentActor->state = gActorGlobalState.unk1[0];
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, AA960_PHY->unkEE) == 0) {
        temp = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
        {
            s16 b = (AA960_PHY->unkEE + 0x800) & 0xFFF;
            s16 c = temp - b;

            AA960_PHY->unkEE = temp + c;
        }
    }
    if (gCurrentActor->state == 1 || gCurrentActor->state == 2 || gCurrentActor->state == 4
        || gCurrentActor->state == 5 || gCurrentActor->state == 6) {
        gCurrentActor->unk144 = 0x1C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        switch (gCurrentActor->state) {
        case 1:
            gCurrentActor->speedXZ = D_80750384;
            AA960_PHY->unkC0 = 0.0f;
            break;
        case 2:
            AA960_PHY->unkC0 = 2000.0f;
            break;
        case 4:
            gCurrentActor->speedXZ = 1500.0f;
            AA960_PHY->unkC0 = 4000.0f;
            break;
        case 5:
            gCurrentActor->speedXZ = 200.0f;
            AA960_PHY->unkC0 = 2000.0f;
            break;
        case 6:
            gCurrentActor->speedXZ = 1000.0f;
            AA960_PHY->unkC0 = 2000.0f;
            break;
        }
        gCurrentActor->state = 3;
    }
    switch (gCurrentActor->state) {
    case 0:
        break;
    case 3:
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        AA960_PHY->unkC0 += D_80750388;
        if (AA960_PHY->unkC0 < (f32)D_8075038C) {
            AA960_PHY->unkC0 = (f32)D_8075038C;
        }
        if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            temp = 0xC8;
            switch (state->unk0) {
            case 0:
                AA960_PHY->unkC0 = 1600.0f;
                gCurrentActor->speedXZ = gCurrentActor->speedXZ / 2;
                temp = 0xC8;
                break;
            case 1:
                AA960_PHY->unkC0 = 1200.0f;
                gCurrentActor->speedXZ = gCurrentActor->speedXZ / 2;
                temp = 0x64;
                break;
            case 2:
                AA960_PHY->unkC0 = 800.0f;
                gCurrentActor->speedXZ = gCurrentActor->speedXZ / 2;
                temp = 0x46;
                break;
            case 3:
                gCurrentActor->speedXZ = 0.0f;
                AA960_PHY->unkC0 = 0.0f;
                temp = 0x1E;
                if (fadeAlpha != 0) {
                    gCurrentActor->state = 0x64;
                }
                break;
            }
            if (gCurrentActor->actorType == 0x48) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2A1, temp, 0x7F, 0, 0, 0.0f, 0);
            }
            state->unk0++;
        }
        break;
    case 0x64:
        break;
    }
    gCurrentActor->yaw += 0x72;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorBounceFadeInSpinUpdateType1(void) {
    actorBounceFadeInSpinUpdate(1);
}

typedef struct ActorPhysics {
    u8 pad0[0xC0];
    f32 unkC0;
    f32 unkC4;
} ActorPhysics;

typedef struct EffectCounter {
    u8 pad0[0x8];
    u16 unk8;
} EffectCounter;


void actorUpdateSfxAndGround(void) {
    EffectCounter *counter;

    counter = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 4;
        gCurrentActor->flags |= 0x400;
        effectSpawnBurstParticleCluster(gCurrentActor);
    }
    if (counter->unk8 == 1) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x73, 0xFF, 0x7F, 1, 0, 0.0f, 0);
        sfxAllocateChannel(0x3B, 0.7f);
    } else if (counter->unk8 == 0xA) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x19C, 0xB4, 0x7F, 1, 0, 0.0f, 0);
    }
    actorBounceFadeInSpinUpdate(0);
    if (gCurrentActor->y < gCurrentActor->waterY) {
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->y = gCurrentActor->waterY;
        ((ActorPhysics *)gCurrentActor)->unkC0 = ((ActorPhysics *)gCurrentActor)->unkC4;
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x96, 0x78, 0, 1.0f);
}


void actorSpawnRingBurstAndUpdate(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x400;
        effectSpawnRingBursts(gCurrentActor, 20.0f, 40.0f, 0x1E);
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    }
    actorBounceFadeInSpinUpdate(0);
    if (gCurrentActor->floorY != 99999.0f) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x19, 0x19, 1, 0x96, 0x78, 0, 1.0f);
    }
}



typedef struct AA960ConfigInt {
    s32 unk0;
    s32 unk4;
} AA960ConfigInt;

extern u8 gBossFightPhase;
extern u32 gGameFrameCounter;
s32 actorListLookupEntry(s32); // FAKE: callee prototype steer
s32 flagGet(s32, s32); // FAKE: callee prototype steer
f32 mathSinF(s16);

void actorPathCollectibleUpdate(void *unused) {
    EffectState *state;
    s32 temp;
    s32 cond;
    s32 flag;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        if (gCurrentActor->actorType == 0x93) {
            state->unk6 = -1;
        } else {
            state->unk6 = actorListLookupEntry(actorListFindIdByActor(gCurrentActor) & 0xFFFF);
        }
        if (state->unk6 != -1 && flagGet(state->unk6, 0) != 0) {
            actorDespawn(gCurrentActor);
            return;
        }
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        actorSetCollisionRadius(gCurrentActor, 175.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 12.0f, 0.0f, 80.0f, -1);
        state->unk0 = ((AA960ConfigInt *)gCurrentActor->spawnData)->unk0;
        state->unk1 = ((AA960ConfigInt *)gCurrentActor->spawnData)->unk4;
        state->unk2 = pathPlaybackStart(gCurrentActor, state->unk0, 0, 0.0f, 0.0f, 0.0f, 0);
        if (state->unk2 != -1) {
            pathPlaybackSetLooping(state->unk2, 1);
            pathPlaybackSetSpeed(state->unk2, state->unk1);
            pathPlaybackSetLoopLimit(state->unk2, -1);
            pathPlaybackSetActive(state->unk2, 1);
        }
        state->unk4 = 0;
    } else {
        if (state->unk2 != -1) {
            pathPlaybackAdvance(state->unk2);
            pathPlaybackGetPosition(state->unk2, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
        }
        gCurrentActor->y += 5.0 * mathSinF(state->unk4);
        state->unk4 = (state->unk4 + 0x50) & 0xFFF;
        if (gGameFrameCounter % 0x18 == 0) {
            switch (gCurrentActor->actorType) {
            case 0x5B:
                temp = 6;
                break;
            case 0x6F:
                temp = 0x75;
                break;
            case 0x70:
                temp = 0x42;
                break;
            case 0x71:
                temp = 0x46;
                break;
            default:
                temp = -1;
                break;
            }
            flag = (temp == -1 || flagGet(temp, 0) != 0) ? 1 : 0;
            if (flag != 0) {
                effectSetDepth(1);
                cond = 1;
                if (gCurrentActor->actorType == 0x93) {
                    cond = 0;
                } else if (gPrimaryPlayerActor->actorType == 3 && gCurrentActor->actorType == 0x5B) {
                    cond = 0;
                } else if (gPrimaryPlayerActor->actorType == 6 && gCurrentActor->actorType == 0x6F) {
                    cond = 0;
                } else if (gPrimaryPlayerActor->actorType == 5 && gCurrentActor->actorType == 0x70) {
                    cond = 0;
                } else if (gPrimaryPlayerActor->actorType == 4 && gCurrentActor->actorType == 0x71) {
                    cond = 0;
                } else if (gPrimaryPlayerActor->actorType == 2 && gCurrentActor->actorType == 0x72) {
                    cond = 0;
                }
                if (cond != 0) {
                    effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
                } else {
                    effectSetCallback(&effectProximityFadeUpdate);
                    effectSetSpeed(0x226);
                }
                effectSetFlags(4);
                effectSetMode(3);
                effectCreateAtActorBone(unused, 0.8f, gCurrentActor, 1, 2);
                gCurrentActor->unk144 = 2;
            } else {
                gCurrentActor->unk144 = 1;
            }
        }
        if (gBossFightPhase == 4) {
            effectSpawnBurstParticleCluster(gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2BF, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
            actorDespawn(gCurrentActor);
            if (gCurrentActor->actorType == 0x93) {
                func_80724994(3, 1, 0x27, 0, 0);
            } else {
                if (state->unk6 != -1) {
                    flagSet(state->unk6, 1, 0);
                }
                slotQueueUpdate(0, 0, 0);
                slotQueueAddValue(0, 0, 0xA);
            }
        }
    }
}

extern u8 D_80720FBC;
void actorPathCollectibleUpdateFBC(void) {
    actorPathCollectibleUpdate(&D_80720FBC);
}

extern u8 D_80720F98;

void actorPathCollectibleUpdateF98(void) {
    actorPathCollectibleUpdate(&D_80720F98);
}

extern u8 D_80721028;

void actorPathCollectibleUpdate1028(void) {
    actorPathCollectibleUpdate(&D_80721028);
}

extern u8 D_80721004;

void actorPathCollectibleUpdate1004A(void) {
    actorPathCollectibleUpdate(&D_80721004);
}

extern u8 D_80720FE0;

void actorPathCollectibleUpdateFE0(void) {
    actorPathCollectibleUpdate(&D_80720FE0);
}

void actorPathCollectibleUpdate1004B(void) {
    actorPathCollectibleUpdate(&D_80721004);
}


typedef struct SfxTable {
    s32 unk0[7];
} SfxTable;

extern u8 gPlayerCharacterId;
extern u8 gBossFightPhase;
extern u8 D_807FC954[];
extern u32 gFrameCounter;
extern u8 D_80721170;
extern SfxTable D_807504A4;

void effectActorSparkleTick(void) {
    s32 flag;
    s32 idx;
    SfxTable table;

    flag = D_807FC954[gPlayerCharacterId * 94] & 1;
    if (!(gCurrentActor->flags & 0x10)) {
        actorAppendModelSubNode(gCurrentActor, 0.0f, 10.0f, 0.0f, -1);
        actorSetCollisionRadius(gCurrentActor, 175.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 10.0f, 0.0f, 80.0f, -1);
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    if (flag != 0) {
        if (gBossFightPhase == 4) {
            if (gFrameCounter % 5 == 0) {
                idx = (randomNonNegative() >> 15) % 0xFF % 7;
                table = D_807504A4;
                effectSetCallback(&effectOrbitSourceUpdate);
                effectSetDuration(-1);
                effectSetDepth(1);
                effectSetSpeed(100);
                effectCreateAtActorBone((void *)table.unk0[idx], 0.2f, gCurrentActor, 1, 0);
                sfxAllocateChannel(0x7F, 1.0f);
                slotQueueUpdate(7, 0, 0);
                slotQueueAddValue(7, 0, (s16)slotQueueGetMaxValue(7, 0));
            }
        }
    }
    if (!(gFrameCounter & 0xF)) {
        effectSetDepth(1);
        effectSetCallback(&effectProximityFadeUpdate);
        effectSetSpeed(0x226);
        effectSetMode(2);
        effectSetColor(0xFF, 0xFF, 0xFF, flag ? 0xFF : 0x7F);
        effectCreateAtActorBone(&D_80721170, 0.4f, gCurrentActor, 1, 2);
    }
    if (gCurrentActor->floorY != 99999.0f) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    }
}

typedef struct ActorDrawBuffer {
    u8 pad0[0x20];
    void *unk20;
} ActorDrawBuffer;

typedef struct SparkleState {
    f32 unk0;
    s16 unk4;
} SparkleState;

typedef struct SparkleBuffer {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
} SparkleBuffer;

extern u8 D_807504C8;
extern u8 D_807504CC;
extern u8 D_807504D0;
extern f32 D_807504C0;
extern f32 D_807504C4;

void effectActorShrinkTick(void) {
    SparkleState *state;
    SparkleBuffer *drawBuf;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        ((ActorDrawBuffer *)gCurrentActor->sub4)->unk20 = heapAlloc(0x20);
        heapClearBlock(((ActorDrawBuffer *)gCurrentActor->sub4)->unk20);
        state->unk4 = 0;
        state->unk0 = 1.0f;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->flags |= 0x40000000;
        gCurrentActor->alpha = D_807504CC;
    }
    if (D_807504D0 < gCurrentActor->alpha) {
        gCurrentActor->alpha -= D_807504D0;
    }
    state->unk4 += 1;
    if (D_807504C4 < (f32)state->unk4) {
        actorDespawn(gCurrentActor);
    } else {
        state->unk0 *= D_807504C0;
        drawBuf = ((ActorDrawBuffer *)gCurrentActor->sub4)->unk20;
        drawBuf->unk0 = D_807504C8;
        drawBuf->unk1 = 0xFF;
        drawBuf->unk4 = state->unk0;
        drawBuf->unk8 = state->unk0;
        drawBuf->unkC = state->unk0;
        drawBuf->unk10 = 0xFF;
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}


void func_806A8070(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x40000000;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

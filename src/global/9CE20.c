#include "common.h"
#include "actor.h"
#include "proto/global/117190.h"
#include "proto/global/133A90.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/7130.h"
#include "proto/global/9CE20.h"
#include "proto/global/CEAE0.h"


typedef struct BoneChainData {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 unk28;
} BoneChainData;

typedef struct BoneChainPlayerState {
    /* 0x130 */ u8 pad0[0x130];
    /* 0x130 */ void *unk130;
    /* 0x134 */ u8 pad134[4];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ u8 pad13C[0x10];
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ f32 unk150;
    /* 0x154 */ s16 unk154;
    /* 0x156 */ u8 pad156[0x9A];
    /* 0x1F0 */ u32 unk1F0;
} BoneChainPlayerState;

typedef struct BoneChainPlayerRoot {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ BoneChainPlayerState *unk174;
} BoneChainPlayerRoot;

typedef struct BoneChainMain {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ BoneChainPlayerRoot *unk4;
} BoneChainMain;

typedef struct BoneChainActor2 {
    /* 0x06A */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x7A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x6C];
    /* 0x154 */ u8 unk154;
} BoneChainActor2;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;
extern s32 gGlobalOverlayFlags;
extern u32 gFrameDelta;
extern s16 D_8075037C;
extern s16 D_80750380;

f32 sinApprox(f32);

void actorBoneChainSwingUpdate(nodeCount)
u8 nodeCount;
{
    BoneChainData *data;
    BoneRotation *node;
    s16 i;
    f32 padA;
    BoneChainPlayerState *player;
    f32 padC;
    s16 *p;
    u8 dir;
    f32 limit = 15.0f;

    data = gCurrentActor->customState;
    player = ((BoneChainMain *)gPlayerSlots)->unk4->unk174;
    if (!(gCurrentActor->flags & 0x10)) {
        data->unk0 = 0.0f;
        data->unk4 = 0.10471976f;
        data->unk8 = 0.75f;
        data->unk10 = 0.00f;
        data->unkC = 0.f;
        data->unk1C = gCurrentActor->y;
        data->unk20 = 0.000f;
        data->unk24 = (f32)((f64)(s32)((randomNonNegative() >> 15) % 100) / 1000.0 + 0.1);
        data->unk18 = 0.0f;
        gCurrentActor->sub4->boneRotations = heapAlloc(0x80);
        proxPathAdd(gCurrentActor, 0, 0, 0, nodeCount, 0.0f, (f32)((f64)nodeCount * 0.333333), 0.15f, 100.0f, 20.0f, 8.0f, 0, 0.0f, 0.0f, 0);
        if (gFrameDelta == 0x50) {}  // FAKE: deadsweep; keeps the 0x50 store constant out of a register (a0 stays unk254, p takes v0)
        for (i = 1; i <= nodeCount; i++) {
            proxPathSetSegment(gCurrentActor, 0, i - 1, i, i + 1, 0.333333f, 0.0f, 0.0f, 0, 0, 0, 0, 0);
        }
        ((u8 *)gCurrentActor)[0x130] = 0x3C;
        ((u8 *)gCurrentActor)[0x131] = 0xC8;
        data->unk14 = 0;
        data->unk15 = 0;
        data->unk28 = flagGet(0x183, 0) != 0 || (gGlobalOverlayFlags & 0x10000000) != 0 || func_807142D8() != 0;
    }
    if (gPrimaryPlayerActor->state == 0x63 || data->unk28 == 0 ||
        (*(s32 *)gCurrentActor->spawnData == 1 && !(player->unk1F0 & 0x40))) {
        gCurrentActor->flags &= 0xFBFFFFFB;
    } else {
        gCurrentActor->flags |= 0x04000004;
    }
    if (gActorGlobalState.volumeTriggerQueueCount == 0) {}
    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        p = gActorGlobalState.volumeTriggerQueueId[i];
        if (!*p) {
            data->unk16 = 0x50;
        }
    }
    if (data->unk16 != 0) {
        gCurrentActor->y -= 1.0;
        data->unk16--;
        data->unk1C -= 1.0;
    }
    node = gCurrentActor->sub4->boneRotations;
    if (data->unk0 > 2.0f) {
        if (data->unkC < 3.926991f && data->unkC + data->unk4 >= 3.926991f) {
            if (gCurrentActor->actorType == 0x74) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x257, (f64)data->unk0 * 100.0 / limit, 0x7F, 5);
            } else {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C, (f64)data->unk0 * 100.0 / limit, 0x7F, 5);
            }
        }
        if (data->unkC < 0.7853982f && data->unkC + data->unk4 >= 0.7853982f) {
            if (gCurrentActor->actorType == 0x74) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x258, (f64)data->unk0 * 25.0 / limit, 0x7F, 0x14);
            } else {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1D, (f64)data->unk0 * 25.0 / limit, 0x7F, 0x14);
            }
        }
    }
    if (gCurrentActor->actorType != 0x74 && data->unk0 > 10.0f) {
        if (data->unkC < 2.3561945f && data->unkC + data->unk4 >= 2.3561945f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1E, 0xFF, 0x7F, 0x14);
        }
        if (data->unkC < 5.497787f && data->unkC + data->unk4 >= 5.497787f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1E, 0xFF, 0x7F, 0x14);
        }
    }
    switch (gCurrentActor->actorType) {
    case 0x44:
    case 0x74:
        dir = 1;
        break;
    case 0x21:
    case 0x45:
        dir = 2;
        break;
    }
    data->unkC = data->unkC + data->unk4 * gFrameDelta * 0.5;
    data->unk10 = sinApprox(data->unkC) * data->unk0;
    for (i = 0; i < 0xE; i++) {
        node[i].weight = -0x80;
        node[i].bone = i + dir;
        node[i].rotY = 0;
        node[i].rotX = (s16)(s32)((f64)data->unk10 / 360.0 * 65535.0);
        node[i].rotZ = 0;
        data->unk10 = data->unk10 * data->unk8;
    }
    if (gCurrentActor->actorType == 0x45 || gCurrentActor->actorType == 0x21) {
        node[i].weight = -0x80;
        node[i].bone = 1;
        node[i].rotY = (s16)(s32)((f64)data->unk18 / 360.0 * 65535.0);
        node[i].rotX = 0;
        node[i].rotZ = 0;
        i++;
        data->unk18 += 20.0f;
        if (data->unk18 > 360.0f) {
            data->unk18 -= 360.0f;
        }
    }
    node[i].weight = 0;
    if (gPrimaryPlayerActor->state == 0x58) {
        data->unk15 = 5;
    } else if (data->unk15 != 0) {
        data->unk15--;
    }
    if ((gPrimaryPlayerActor->contactFlags & 0x40) && data->unk14 == 0 && gCurrentActor == player->unk130) {
        data->unk0 = 15.0f;
        if (mathAngleDistance(gPrimaryPlayerActor->yaw, gCurrentActor->yaw) < 0x400) {
            data->unkC = 3.1415927f;
        } else {
            data->unkC = 0.0f;
        }
    }
    if (data->unkC >= 6.2831855f) {
        data->unkC -= 6.2831855f;
    }
    if (data->unkC < 0.0f) {
        data->unkC += 6.2831855f;
    }
    if ((gPrimaryPlayerActor->contactFlags & 0x40) && gCurrentActor == player->unk130) {
        data->unk14 = 1;
        data->unk0 += 0.2;
        if (data->unk0 > 15.0f) {
            data->unk0 = 15.0f;
        }
    } else {
        data->unk14 = 0;
        data->unk0 = data->unk0 + (0.0 - data->unk0) * 0.03;
        if (data->unk0 < 2.0) {
            data->unk0 = 0.0f;
        }
    }
    if ((gPrimaryPlayerActor->contactFlags & 0x40) && gCurrentActor == player->unk130) {
        if (player->unk138 < 1.5 && (((f64)data->unkC > 4.0 && (f64)data->unkC < 4.712389f) ||
                                     ((f64)data->unkC < 1.5707964f && (f64)data->unkC > 0.9))) {
            player->unk14C = (f32)D_8075037C * (data->unk0 / 15.0f);
            player->unk150 = (f32)D_80750380 * (data->unk0 / 15.0f);
        } else {
            player->unk14C = 200.0f;
            player->unk150 = 200.0f;
        }
        player->unk154 = gCurrentActor->yaw & 0xFFF;
        if ((f64)data->unkC < 1.5707964f || data->unkC > 4.71238911151886) {
            player->unk154 = (player->unk154 + 0x800) & 0xFFF;
        }
    }
    switch (gCurrentActor->actorType) {
    case 0x21:
    case 0x45:
        gCurrentActor->y = sinApprox(data->unk20) * 5.0 + data->unk1C;
        data->unk20 += data->unk24;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void projectileBehaviourEntryA(void) {
    actorBoneChainSwingUpdate(0xE);
}

void projectileBehaviourEntryB(void) {
    actorBoneChainSwingUpdate(0xB);
}

void projectileBehaviourEntryC(void) {
    actorBoneChainSwingUpdate(0xB);
}

void projectileBehaviourEntryD(void) {
    actorBoneChainSwingUpdate(0xE);
}

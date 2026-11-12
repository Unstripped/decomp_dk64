#include "common.h"
#include "actor.h"
#include "proto/global/5E020.h"
#include "proto/global/5E2F0.h"
#include "proto/global/63810.h"

typedef struct QueuedLightEntry {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 pad19[3];
} QueuedLightEntry;

extern s16 gLightQueueCount;
extern QueuedLightEntry gLightQueue[];

typedef struct LightKeyframe {
    f32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 pad7;
    s16 unk8;
    s16 unkA;
} LightKeyframe;

typedef struct LightKeyframeSet {
    LightKeyframe sub[5];
} LightKeyframeSet;

extern LightKeyframeSet gLightKeyframeTable[];

void lightQueueKeyframed(u8 keyframeSetIndex, s16 lightId, f32 x, f32 y, f32 z, s16 radius, f32 fade, s16 targetId) {
    u8 count;
    s32 i;
    s32 total;
    s32 cyclePos;
    s32 accum;
    s32 next;
    f32 t;
    f32 factor;
    f32 base;
    f64 d6;

    keyframeSetIndex = keyframeSetIndex - 1;
    if (gLightQueueCount != 0x1E) {
        for (i = 0; i < gLightQueueCount; i++) {
            if (lightId == gLightQueue[i].unk0) {
                return;
            }
        }

        total = 0;
        count = 0;
        for (i = 0; gLightKeyframeTable[keyframeSetIndex].sub[i].unkA != 0; count++, i++) {
            total += gLightKeyframeTable[keyframeSetIndex].sub[i].unkA;
        }

        cyclePos = (s32)(lightId + gFrameCounter) % total;
        accum = gLightKeyframeTable[keyframeSetIndex].sub[0].unkA;
        i = 1;
        while (cyclePos >= accum) {
            accum += gLightKeyframeTable[keyframeSetIndex].sub[i].unkA;
            i++;
        }

        i--;
        accum -= gLightKeyframeTable[keyframeSetIndex].sub[i].unkA;
        cyclePos -= accum;
        t = (f32)cyclePos / (f32)gLightKeyframeTable[keyframeSetIndex].sub[i].unkA;
        next = i + 1;
        if (next == count) {
            next = 0;
        }


        d6 = fade;
        if (d6 < 0.8) {
            factor = 1.0f;
        } else {
            factor = 1.0 - ((d6 - 0.8) / 0.19999999999999996);
        }

        base = gLightKeyframeTable[keyframeSetIndex].sub[i].unk0 + (gLightKeyframeTable[keyframeSetIndex].sub[next].unk0 - gLightKeyframeTable[keyframeSetIndex].sub[i].unk0) * t;
        base = base * factor;

        gLightQueue[gLightQueueCount].unk16 = (u32)(((f32)(u32)gLightKeyframeTable[keyframeSetIndex].sub[i].r + (f32)(gLightKeyframeTable[keyframeSetIndex].sub[next].r - gLightKeyframeTable[keyframeSetIndex].sub[i].r) * t) * base);
        gLightQueue[gLightQueueCount].unk17 = (u32)(((f32)(u32)gLightKeyframeTable[keyframeSetIndex].sub[i].g + (f32)(gLightKeyframeTable[keyframeSetIndex].sub[next].g - gLightKeyframeTable[keyframeSetIndex].sub[i].g) * t) * base);
        gLightQueue[gLightQueueCount].unk18 = (u32)(((f32)(u32)gLightKeyframeTable[keyframeSetIndex].sub[i].b + (f32)(gLightKeyframeTable[keyframeSetIndex].sub[next].b - gLightKeyframeTable[keyframeSetIndex].sub[i].b) * t) * base);
        gLightQueue[gLightQueueCount].unk10 = (s32)((f32)gLightKeyframeTable[keyframeSetIndex].sub[i].unk8 + (f32)(gLightKeyframeTable[keyframeSetIndex].sub[next].unk8 - gLightKeyframeTable[keyframeSetIndex].sub[i].unk8) * t);
        gLightQueue[gLightQueueCount].unk4 = x;
        gLightQueue[gLightQueueCount].unk8 = y;
        gLightQueue[gLightQueueCount].unkC = z;
        gLightQueue[gLightQueueCount].unk12 = targetId;
        gLightQueue[gLightQueueCount].unk14 = radius;
        gLightQueue[gLightQueueCount++].unk0 = lightId;
    }
}





extern s32 gCurrentMap;
extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalCutsceneFlags;


void lightFlushQueued(void) {
    s32 i;

    if (gCurrentMap == 0x30 && !(((PlayerState *)gPrimaryPlayerActor->customState)->stateFlags & 0x100000)) {
        gLightQueueCount = 0;
        return;
    }

    if (!(gGlobalPauseFlags & 2)) {
        for (i = 0; i < gLightQueueCount; i++) {
            if (!(gGlobalCutsceneFlags & 4)) {
                lightSetFlags(2);
            }
            lightSetTargetId(gLightQueue[i].unk12);
            lightSetRadius(gLightQueue[i].unk14);
            lightAdd(gLightQueue[i].unk4, gLightQueue[i].unk8, gLightQueue[i].unkC, 0.0f, 0.0f, 0.0f, gLightQueue[i].unk10, 0, gLightQueue[i].unk16, gLightQueue[i].unk17, gLightQueue[i].unk18);
        }
    }
    gLightQueueCount = 0;
}

typedef struct ActorSlotEntry {
    u8 pad0[0x20];
    u8 *unk20;
    u8 pad24[0x62];
    s16 unk86;
    u8 pad88[0x8];
} ActorSlotEntry;

extern ActorSlotEntry *gModelSlots;

void actorSetTargetSlotByte(s32 key, u8 val) {
    u8 *volatile dst;
    s16 slotType;
    s32 slotIdx;
    u8 *slotBase;

    slotIdx = hashTableLookup(key);
    if (slotIdx != -1) {
        slotBase = (u8 *)gModelSlots + (slotIdx * 0x90);
        slotType = *(s16 *)(slotBase + 0x86);
        if (slotType != 1) {
            if (slotType == 2) {
                dst = *(u8 **)(slotBase + 0x20) + 0x5B;
            }
        } else {
            dst = *(u8 **)(slotBase + 0x20) + 0xC3;
        }
        *dst = val;
    }
}

#include "common.h"
#include "actor.h"
#include "model.h"
#include "proto/global/5E020.h"
#include "proto/global/5E2F0.h"
#include "proto/global/63810.h"

typedef struct QueuedLightEntry {
    s16 lightId;
    u8 pad2[2];
    f32 x;
    f32 y;
    f32 z;
    s16 radius;
    s16 targetId;
    s16 activeRadius;
    u8 r;
    u8 g;
    u8 b;
    u8 pad19[3];
} QueuedLightEntry;

extern s16 gLightQueueCount;
extern QueuedLightEntry gLightQueue[];

typedef struct LightKeyframe {
    f32 intensity;
    u8 r;
    u8 g;
    u8 b;
    u8 pad7;
    s16 radius;
    s16 duration;
} LightKeyframe;

typedef struct LightKeyframeSet {
    LightKeyframe keys[5];
} LightKeyframeSet;

extern LightKeyframeSet gLightKeyframeTable[];

void lightQueueKeyframed(u8 keyframeSetIndex, s16 lightId, f32 x, f32 y, f32 z, s16 activeRadius, f32 fade, s16 targetId) {
    u8 keyCount;
    s32 i;
    s32 cycleLength;
    s32 cyclePos;
    s32 accum;
    s32 next;
    f32 t;
    f32 fadeScale;
    f32 intensity;

    keyframeSetIndex--; // 1-based: model objects store 0 for no keyframed light
    if (gLightQueueCount == 0x1E) {
        return;
    }

    for (i = 0; i < gLightQueueCount; i++) {
        if (lightId == gLightQueue[i].lightId) {
            return;
        }
    }

    cycleLength = 0;
    keyCount = 0;
    for (i = 0; gLightKeyframeTable[keyframeSetIndex].keys[i].duration != 0; keyCount++, i++) {
        cycleLength += gLightKeyframeTable[keyframeSetIndex].keys[i].duration;
    }

    cyclePos = (s32)(lightId + gFrameCounter) % cycleLength;
    accum = gLightKeyframeTable[keyframeSetIndex].keys[0].duration;
    i = 1;
    while (cyclePos >= accum) {
        accum += gLightKeyframeTable[keyframeSetIndex].keys[i].duration;
        i++;
    }

    i--;
    accum -= gLightKeyframeTable[keyframeSetIndex].keys[i].duration;
    cyclePos -= accum;
    t = (f32)cyclePos / gLightKeyframeTable[keyframeSetIndex].keys[i].duration;
    next = i + 1;
    if (next == keyCount) {
        next = 0;
    }

    if (fade < 0.8) {
        fadeScale = 1.0f;
    } else {
        fadeScale = 1.0 - ((fade - 0.8) / (1.0 - 0.8));
    }

    intensity = gLightKeyframeTable[keyframeSetIndex].keys[i].intensity + (gLightKeyframeTable[keyframeSetIndex].keys[next].intensity - gLightKeyframeTable[keyframeSetIndex].keys[i].intensity) * t;
    intensity *= fadeScale;

    gLightQueue[gLightQueueCount].r = (gLightKeyframeTable[keyframeSetIndex].keys[i].r + (gLightKeyframeTable[keyframeSetIndex].keys[next].r - gLightKeyframeTable[keyframeSetIndex].keys[i].r) * t) * intensity;
    gLightQueue[gLightQueueCount].g = (gLightKeyframeTable[keyframeSetIndex].keys[i].g + (gLightKeyframeTable[keyframeSetIndex].keys[next].g - gLightKeyframeTable[keyframeSetIndex].keys[i].g) * t) * intensity;
    gLightQueue[gLightQueueCount].b = (gLightKeyframeTable[keyframeSetIndex].keys[i].b + (gLightKeyframeTable[keyframeSetIndex].keys[next].b - gLightKeyframeTable[keyframeSetIndex].keys[i].b) * t) * intensity;
    gLightQueue[gLightQueueCount].radius = gLightKeyframeTable[keyframeSetIndex].keys[i].radius + (gLightKeyframeTable[keyframeSetIndex].keys[next].radius - gLightKeyframeTable[keyframeSetIndex].keys[i].radius) * t;
    gLightQueue[gLightQueueCount].x = x;
    gLightQueue[gLightQueueCount].y = y;
    gLightQueue[gLightQueueCount].z = z;
    gLightQueue[gLightQueueCount].targetId = targetId;
    gLightQueue[gLightQueueCount].activeRadius = activeRadius;
    gLightQueue[gLightQueueCount++].lightId = lightId;
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
            lightSetTargetId(gLightQueue[i].targetId);
            lightSetRadius(gLightQueue[i].activeRadius);
            lightAdd(gLightQueue[i].x, gLightQueue[i].y, gLightQueue[i].z, 0.0f, 0.0f, 0.0f, gLightQueue[i].radius, 0, gLightQueue[i].r, gLightQueue[i].g, gLightQueue[i].b);
        }
    }
    gLightQueueCount = 0;
}

extern ModelSlot *gModelSlots;

void actorSetTargetSlotByte(s32 modelId, u8 keyframeSetIndex) {
    u8 *dst;
    s32 slotIdx;

    slotIdx = hashTableLookup(modelId);
    if (slotIdx != -1) {
        // the model object layout depends on the slot type; the byte is its keyframed light set (lightQueueKeyframed)
        switch (gModelSlots[slotIdx].unk86) {
            case 2:
                dst = (u8 *)gModelSlots[slotIdx].unk20 + 0x5B;
                break;
            case 1:
                dst = (u8 *)gModelSlots[slotIdx].unk20 + 0xC3;
                break;
        }
        *dst = keyframeSetIndex;
    }
}

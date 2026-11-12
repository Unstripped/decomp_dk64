#include "common.h"
#include "actor.h"
#include "model.h"
#include "sched.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/36880.h"
#include "proto/global/68EA0.h"

typedef struct ActorProximityEntry {
    u16 modelType;
    s16 x;
    s16 y;
    s16 z;
    s16 scale;
    s16 modelId;
} ActorProximityEntry;

extern ModelSlot *gModelSlots;
extern s32 gModelSlotCount;
extern ActorProximityEntry *gModelEmitters;
extern s16 gModelEmitterCount;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 D_807213D0;
extern u8 D_80720A7C;

void modelEmittersInit(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < gModelSlotCount; i++) {
        if (modelTypeIsEmitter(gModelSlots[i].modelType)) {
            count++;
        }
    }

    gModelEmitterCount = count;
    if (count != 0) {
        gModelEmitters = heapAlloc(count * sizeof(ActorProximityEntry));
        count = 0;
        for (i = 0; i < gModelSlotCount; i++) {
            if (modelTypeIsEmitter(gModelSlots[i].modelType)) {
                gModelEmitters[count].modelType = gModelSlots[i].modelType;
                gModelEmitters[count].x = gModelSlots[i].x;
                gModelEmitters[count].y = gModelSlots[i].y;
                gModelEmitters[count].z = gModelSlots[i].z;
                modelEmitterApplyOffset(count, gModelSlots[i].modelType, gModelSlots[i].unk14);
                gModelEmitters[count].scale = gModelSlots[i].scale * 100.0;
                gModelEmitters[count].modelId = gModelSlots[i].id;
                count++;
            }
        }
    }
}

void modelEmitterApplyOffset(s32 entryIdx, s32 modelType, f32 angle) {
    s32 pad[2];
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 rotMtx[4][4];

    if (modelType == 0x138) {
        guRotateF(rotMtx, angle, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(rotMtx, 0.0f, 0.0f, -10.0f, &outX, &outY, &outZ);
        gModelEmitters[entryIdx].x += outX;
        gModelEmitters[entryIdx].z += outZ;
    }
}

void modelEmitterSetPosition(s16 modelId, f32 x, f32 y, f32 z, f32 scale, f32 angle) {
    s32 i;

    for (i = 0; i < gModelEmitterCount; i++) {
        if (modelId == gModelEmitters[i].modelId) {
            gModelEmitters[i].x = x;
            gModelEmitters[i].y = y;
            gModelEmitters[i].z = z;
            modelEmitterApplyOffset(i, gModelEmitters[i].modelType, angle);
            gModelEmitters[i].scale = scale * 100.0;
            return;
        }
    }
}

void modelEmitterDisable(s16 modelId) {
    s32 i;

    for (i = 0; i < gModelEmitterCount; i++) {
        if (modelId == gModelEmitters[i].modelId) {
            gModelEmitters[i].modelId = -1;
        }
    }
}

s32 modelTypeIsEmitter(s16 modelType) {
    if (modelType == 1 || modelType == 0x10 || modelType == 0x74 || modelType == 0xF3 || modelType == 0x138 || modelType == 0x288) {
        return 1;
    }
    return 0;
}

void modelEmittersUpdate(void) {
    s32 i;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 sum;

    if (gPlayerCount < 2) {
        for (i = 0; i < gModelEmitterCount; i++) {
            dz = gPlayerSlots->eyeZ - gModelEmitters[i].z;
            dx = gPlayerSlots->eyeX - gModelEmitters[i].x;
            dy = gPlayerSlots->eyeY - gModelEmitters[i].y;
            sum = dz * dz + (dx * dx + dy * dy);
            dx = gModelEmitters[i].modelId;  // FAKE: dead float store steers uopt (sum gets $f14)
            if (sum < 90000.0 && gModelEmitters[i].modelId != -1 && func_8063C2A8(gModelEmitters[i].modelId)) {
                switch (gModelEmitters[i].modelType) {
                    case 1:
                    case 0x10:
                    case 0xF3:
                    case 0x138:
                        modelEmitterSpawnJitterParticle(i);
                        break;
                    case 0x74:
                    case 0x288:
                        modelEmitterSpawnScaledParticle(i);
                        break;
                }
            }
        }
    }
}

void modelEmitterSpawnJitterParticle(s16 entryIdx) {
    ActorProximityEntry *entry;
    s32 randX;
    s32 randZ;

    if (randomNonNegative() % 10000 % 12 == 0) {
        effectSetDepth(1);
        effectSetMode(7);
        effectSetSpeed(randomNonNegative() % 10000 % 50 - 120);
        effectSetCallback(effectDriftXZUpdate);
        effectSetColor(255, 200, 200, 200);
        effectSetScale(0.2f, 0.1f);
        effectSetFlags(4);
        randX = randomNonNegative();
        randZ = randomNonNegative();
        entry = (ActorProximityEntry *)((u8 *)gModelEmitters + entryIdx * sizeof(ActorProximityEntry));  // FAKE: byte-offset entry address (vs &gModelEmitters[entryIdx]) picks t1/t2 for the *12 index temps
        effectCreateAtPosition(&D_807213D0, 0.0f,
            randX % 10000 % 100 / 20.0 + entry->x - 2.5,
            entry->y + 4.0,
            randZ % 10000 % 100 / 20.0 + entry->z - 2.5);
    }
}

void modelEmitterSpawnScaledParticle(s16 entryIdx) {
    f32 scaleFactor;
    s32 randZ;
    s32 randY;
    s32 randX;

    if (randomNonNegative() % 10000 % 10 == 0) {
        scaleFactor = gModelEmitters[entryIdx].scale / 25.0;
        effectSetDepth(1);
        effectSetMode(2);
        effectSetFlags(4);
        randX = randomNonNegative();
        randY = randomNonNegative();
        randZ = randomNonNegative();
        effectCreateAtPosition(&D_80720A7C, 0.4f,
            (randX % 10000 % 300 / 20.0 - 7.5) * scaleFactor + (gModelEmitters + entryIdx)->x,  // FAKE: (gModelEmitters + entryIdx)-> spelling (vs [entryIdx].) keeps the lh/cvt.d.w order around the div.d
            randY % 10000 % 600 / 20.0 * scaleFactor + (gModelEmitters + entryIdx)->y,  // FAKE: (gModelEmitters + entryIdx)-> spelling (vs [entryIdx].) keeps the lh/cvt.d.w order around the div.d
            (randZ % 10000 % 300 / 20.0 - 7.5) * scaleFactor + (gModelEmitters + entryIdx)->z);  // FAKE: (gModelEmitters + entryIdx)-> spelling (vs [entryIdx].) keeps the lh/cvt.d.w order around the div.d
    }
}


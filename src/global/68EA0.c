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
extern s32 D_80747D70;
extern ActorProximityEntry *D_807F9430;
extern s16 D_807F9434;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 D_807213D0;
extern u8 D_80720A7C;

void actorInitEntryPoints(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_80747D70; i++) {
        if (actorEntryTypeIsEmitter(gModelSlots[i].unk84)) {
            count++;
        }
    }

    D_807F9434 = count;
    if (count != 0) {
        D_807F9430 = heapAlloc(count * sizeof(ActorProximityEntry));
        count = 0;
        for (i = 0; i < D_80747D70; i++) {
            if (actorEntryTypeIsEmitter(gModelSlots[i].unk84)) {
                D_807F9430[count].modelType = gModelSlots[i].unk84;
                D_807F9430[count].x = gModelSlots[i].unk0;
                D_807F9430[count].y = gModelSlots[i].unk4;
                D_807F9430[count].z = gModelSlots[i].unk8;
                actorApplyRotatedOffset(count, gModelSlots[i].unk84, gModelSlots[i].unk14);
                D_807F9430[count].scale = gModelSlots[i].unkC * 100.0;
                D_807F9430[count].modelId = gModelSlots[i].unk88;
                count++;
            }
        }
    }
}

void actorApplyRotatedOffset(s32 entryIdx, s32 modelType, f32 angle) {
    s32 pad[2];
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 rotMtx[4][4];

    if (modelType == 0x138) {
        guRotateF(rotMtx, angle, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(rotMtx, 0.0f, 0.0f, -10.0f, &outX, &outY, &outZ);
        D_807F9430[entryIdx].x += outX;
        D_807F9430[entryIdx].z += outZ;
    }
}

void actorUpdateEntryCoordinates(s16 modelId, f32 x, f32 y, f32 z, f32 scale, f32 angle) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (modelId == D_807F9430[i].modelId) {
            D_807F9430[i].x = x;
            D_807F9430[i].y = y;
            D_807F9430[i].z = z;
            actorApplyRotatedOffset(i, D_807F9430[i].modelType, angle);
            D_807F9430[i].scale = scale * 100.0;
            return;
        }
    }
}

void actorClearEntrySlot(s16 modelId) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (modelId == D_807F9430[i].modelId) {
            D_807F9430[i].modelId = -1;
        }
    }
}

s32 actorEntryTypeIsEmitter(s16 modelType) {
    if (modelType == 1 || modelType == 0x10 || modelType == 0x74 || modelType == 0xF3 || modelType == 0x138 || modelType == 0x288) {
        return 1;
    }
    return 0;
}

void actorUpdateEntryEmitters(void) {
    s32 i;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 sum;

    if (gPlayerCount < 2) {
        for (i = 0; i < D_807F9434; i++) {
            dz = gPlayerSlots->unk224 - D_807F9430[i].z;
            dx = gPlayerSlots->unk21C - D_807F9430[i].x;
            dy = gPlayerSlots->unk220 - D_807F9430[i].y;
            sum = dz * dz + (dx * dx + dy * dy);
            dx = D_807F9430[i].modelId;  // FAKE: dead float store steers uopt (sum gets $f14)
            if (sum < 90000.0 && D_807F9430[i].modelId != -1 && func_8063C2A8(D_807F9430[i].modelId)) {
                switch (D_807F9430[i].modelType) {
                    case 1:
                    case 0x10:
                    case 0xF3:
                    case 0x138:
                        actorEntryEmitJitterParticle(i);
                        break;
                    case 0x74:
                    case 0x288:
                        actorEntryEmitScaledParticle(i);
                        break;
                }
            }
        }
    }
}

void actorEntryEmitJitterParticle(s16 entryIdx) {
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
        entry = (ActorProximityEntry *)((u8 *)D_807F9430 + entryIdx * sizeof(ActorProximityEntry));  // FAKE: byte-offset entry address (vs &D_807F9430[entryIdx]) picks t1/t2 for the *12 index temps
        effectCreateAtPosition(&D_807213D0, 0.0f,
            randX % 10000 % 100 / 20.0 + entry->x - 2.5,
            entry->y + 4.0,
            randZ % 10000 % 100 / 20.0 + entry->z - 2.5);
    }
}

void actorEntryEmitScaledParticle(s16 entryIdx) {
    f32 scaleFactor;
    s32 randZ;
    s32 randY;
    s32 randX;

    if (randomNonNegative() % 10000 % 10 == 0) {
        scaleFactor = D_807F9430[entryIdx].scale / 25.0;
        effectSetDepth(1);
        effectSetMode(2);
        effectSetFlags(4);
        randX = randomNonNegative();
        randY = randomNonNegative();
        randZ = randomNonNegative();
        effectCreateAtPosition(&D_80720A7C, 0.4f,
            (randX % 10000 % 300 / 20.0 - 7.5) * scaleFactor + (D_807F9430 + entryIdx)->x,  // FAKE: (D_807F9430 + entryIdx)-> spelling (vs [entryIdx].) keeps the lh/cvt.d.w order around the div.d
            randY % 10000 % 600 / 20.0 * scaleFactor + (D_807F9430 + entryIdx)->y,  // FAKE: (D_807F9430 + entryIdx)-> spelling (vs [entryIdx].) keeps the lh/cvt.d.w order around the div.d
            (randZ % 10000 % 300 / 20.0 - 7.5) * scaleFactor + (D_807F9430 + entryIdx)->z);  // FAKE: (D_807F9430 + entryIdx)-> spelling (vs [entryIdx].) keeps the lh/cvt.d.w order around the div.d
    }
}


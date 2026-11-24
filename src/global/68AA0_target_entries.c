#include "common.h"
#include "actor.h"
#include "model.h"
#include "sched.h"
#include "proto/global/15050_heap.h"
#include "proto/global/55B20_map_chunk.h"
#include "proto/global/68AA0_target_entries.h"
#include "proto/global/7130_sfx.h"


typedef struct ActorTargetEntry {
    s16 x;
    s16 y;
    s16 z;
    u8 type;
    union {
        struct {
            s8 chunk;
            s8 linkedChunks[4];
        } s;
        s8 chunks[5];
    } u;
} ActorTargetEntry;

extern ModelSlot *gModelSlots;
extern ActorTargetEntry *gActorTargetEntries;
extern s16 gActorTargetEntryCount;
extern s32 gModelSlotCount;


void actorInitTargetEntries(void) {
    s32 k = 0;
    s32 i;

    gActorTargetEntryCount = 0;
    for (i = 0; i < gModelSlotCount; i++) {
        if (mapObjectIsTargetType(i)) {
            gActorTargetEntryCount++;
        }
    }

    gActorTargetEntries = NULL;
    if (gActorTargetEntryCount != 0) {
        gActorTargetEntries = heapAlloc(gActorTargetEntryCount * sizeof(ActorTargetEntry));
        for (i = 0; i < gModelSlotCount; i++) {
            s32 cond = mapObjectIsTargetType(i);
            u8 res = cond;
            if (cond) {
                s32 temp;
                gActorTargetEntries[k].x = gModelSlots[i].x;
                gActorTargetEntries[k].y = gModelSlots[i].y;
                gActorTargetEntries[k].z = gModelSlots[i].z;
                gActorTargetEntries[k].type = res;
                gActorTargetEntries[k].u.s.chunk = mapChunkFindByPosition(gModelSlots[i].x, gModelSlots[i].y, gModelSlots[i].z, 0);
                temp = mapPortalCollectTargets(gActorTargetEntries[k].u.s.chunk, &gActorTargetEntries[k].u.s.linkedChunks[0], 4);
                if (temp != 4) {
                    gActorTargetEntries[k].u.s.linkedChunks[temp] = -1;
                }
                k++;
            }
        }
    }
}

u8 mapObjectIsTargetType(s16 objIndex) {
    s16 val = gModelSlots[objIndex].modelType;

    if (val == 1 || val == 0xC || val == 0x10 || val == 0xF3 || val == 0x134 || val == 0x135 || val == 0x138) {
        return 1;
    }
    return 0;
}

extern PlayerStruct *gPlayerSlots;


void actorTargetEntriesUpdateSfx(u8 targetType, u8 volume, u8 sfxId, f32 factor) {
    s32 i;
    s32 j;
    s32 found;

    for (i = 0; i < gActorTargetEntryCount; i++) {
        j = 0;
        found = 0;
        if (gActorTargetEntries[i].type != targetType) {
            continue;
        }
        do {
            if (gActorTargetEntries[i].u.chunks[j] == gPlayerSlots[0].camChunk) {
                found = 1;
            }
            j++;
            if (j >= 5 || found) {
                break;
            }
        } while (gActorTargetEntries[i].u.chunks[j] != -1);

        if (found) {
            sfxUpdateDistanceVolumeAndPan(gActorTargetEntries[i].x, gActorTargetEntries[i].y, gActorTargetEntries[i].z, volume, sfxId, factor);
        }
    }
}


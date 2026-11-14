#include "common.h"
#include "actor.h"
#include "model.h"
#include "sched.h"
#include "proto/global/15050.h"
#include "proto/global/55B20.h"
#include "proto/global/68AA0.h"
#include "proto/global/7130.h"


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
extern ActorTargetEntry *D_807F9420;
extern s16 D_807F9424;
extern s32 gModelSlotCount;


void actorInitTargetEntries(void) {
    s32 k = 0;
    s32 i;

    D_807F9424 = 0;
    for (i = 0; i < gModelSlotCount; i++) {
        if (mapObjectIsTargetType(i)) {
            D_807F9424++;
        }
    }

    D_807F9420 = NULL;
    if (D_807F9424 != 0) {
        D_807F9420 = heapAlloc(D_807F9424 * sizeof(ActorTargetEntry));
        for (i = 0; i < gModelSlotCount; i++) {
            s32 cond = mapObjectIsTargetType(i);
            u8 res = cond;
            if (cond) {
                s32 temp;
                D_807F9420[k].x = gModelSlots[i].x;
                D_807F9420[k].y = gModelSlots[i].y;
                D_807F9420[k].z = gModelSlots[i].z;
                D_807F9420[k].type = res;
                D_807F9420[k].u.s.chunk = mapChunkFindByPosition(gModelSlots[i].x, gModelSlots[i].y, gModelSlots[i].z, 0);
                temp = mapObjectCollectIdsByType(D_807F9420[k].u.s.chunk, &D_807F9420[k].u.s.linkedChunks[0], 4);
                if (temp != 4) {
                    D_807F9420[k].u.s.linkedChunks[temp] = -1;
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

    for (i = 0; i < D_807F9424; i++) {
        j = 0;
        found = 0;
        if (D_807F9420[i].type != targetType) {
            continue;
        }
        do {
            if (D_807F9420[i].u.chunks[j] == gPlayerSlots[0].unk290) {
                found = 1;
            }
            j++;
            if (j >= 5 || found) {
                break;
            }
        } while (D_807F9420[i].u.chunks[j] != -1);

        if (found) {
            sfxUpdateDistanceVolumeAndPan(D_807F9420[i].x, D_807F9420[i].y, D_807F9420[i].z, volume, sfxId, factor);
        }
    }
}


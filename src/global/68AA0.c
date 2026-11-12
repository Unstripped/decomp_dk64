#include "common.h"
#include "actor.h"
#include "model.h"
#include "sched.h"
#include "proto/global/15050.h"
#include "proto/global/55B20.h"
#include "proto/global/68AA0.h"
#include "proto/global/7130.h"


typedef struct ActorTargetEntry {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    union {
        struct {
            s8 unk7;
            s8 ids[4];
        } s;
        s8 unk7_arr[5];
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
                D_807F9420[k].unk0 = gModelSlots[i].x;
                D_807F9420[k].unk2 = gModelSlots[i].y;
                D_807F9420[k].unk4 = gModelSlots[i].z;
                D_807F9420[k].unk6 = res;
                D_807F9420[k].u.s.unk7 = mapChunkFindByPosition(gModelSlots[i].x, gModelSlots[i].y, gModelSlots[i].z, 0);
                temp = mapObjectCollectIdsByType(D_807F9420[k].u.s.unk7, &D_807F9420[k].u.s.ids[0], 4);
                if (temp != 4) {
                    D_807F9420[k].u.s.ids[temp] = -1;
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
        if (D_807F9420 == 0) {}  // FAKE: dead statement, steers P into a3 / s4-s6 order
        j = 0;
        found = 0;
        if (D_807F9420[i].unk6 == targetType) {
            do {
                if (D_807F9420[i].u.unk7_arr[j] == gPlayerSlots[0].unk290) {
                    found = 1;
                }
                j++;
                if (j >= 5 || found) {
                    break;
                }
            } while (D_807F9420[i].u.unk7_arr[j] != -1);

            if (found) {
                sfxUpdateDistanceVolumeAndPan(D_807F9420[i].unk0, D_807F9420[i].unk2, D_807F9420[i].unk4, volume, sfxId, factor);
            }
        }
    }
}


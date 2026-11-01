#include "common.h"
#include "actor.h"


typedef struct ActorTargetSource {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x84 - 0xC];
    s16 unk84;
    u8 pad86[0xA];
} ActorTargetSource;

typedef struct ActorTargetEntry {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    union {
        struct {
            s8 unk7;
            s8 pad8[4];
        } s;
        s8 unk7_arr[5];
    } u;
} ActorTargetEntry;

extern ActorTargetSource *D_807F6000;
extern ActorTargetEntry *D_807F9420;
extern s16 D_807F9424;
extern s32 D_80747D70;

void *heapAlloc(s32);
u8 mapObjectIsTargetType(s16);
s8 mapChunkFindByPosition(f32, f32, f32, s32);
s16 mapObjectCollectIdsByType(s8, void *, s16);

void actorInitTargetEntries(void) {
    s32 k = 0;
    s32 i;
    s32 res;

    D_807F9424 = 0;
    for (i = 0; i < D_80747D70; i++) {
        if (mapObjectIsTargetType(i)) {
            D_807F9424++;
        }
    }

    D_807F9420 = NULL;
    if (D_807F9424 != 0) {
        D_807F9420 = heapAlloc(D_807F9424 * sizeof(ActorTargetEntry));
        for (i = 0; i < D_80747D70; i++) {
            s32 cond = mapObjectIsTargetType(i);
            u8 res = cond;
            if (cond) {
                s32 temp;
                D_807F9420[k].unk0 = D_807F6000[i].unk0;
                D_807F9420[k].unk2 = D_807F6000[i].unk4;
                D_807F9420[k].unk4 = D_807F6000[i].unk8;
                D_807F9420[k].unk6 = res;
                D_807F9420[k].u.s.unk7 = mapChunkFindByPosition(D_807F6000[i].unk0, D_807F6000[i].unk4, D_807F6000[i].unk8, 0);
                temp = mapObjectCollectIdsByType(D_807F9420[k].u.s.unk7, &D_807F9420[k].u.s.pad8, 4);
                if (temp != 4) {
                    D_807F9420[k].u.s.pad8[temp] = -1;
                }
                k++;
            }
        }
    }
}

typedef struct ActorTargetType {
    u8 pad[0x84];
    s16 unk84;
    u8 pad86[0xA];
} ActorTargetType;

u8 mapObjectIsTargetType(s16 arg0) {
    s16 val = ((ActorTargetType *)D_807F6000)[arg0].unk84;

    if (val == 1 || val == 0xC || val == 0x10 || val == 0xF3 || val == 0x134 || val == 0x135 || val == 0x138) {
        return 1;
    }
    return 0;
}

typedef struct PlayerAreaView {
    u8 pad0[0x290];
    s16 unk290;
} PlayerAreaView;

extern PlayerAreaView *D_807FC924;

f32 sfxUpdateDistanceVolumeAndPan(f32, f32, f32, u8, u8, f32);

void actorTargetEntriesUpdateSfx(u8 arg0, u8 arg1, u8 arg2, f32 arg3) {
    ActorTargetEntry *entry;
    s32 i;
    PlayerAreaView **new_var;
    s32 stride;
    s32 j;
    s32 found;

    for (i = 0; i < D_807F9424; i++) {
        stride = 12;  // FAKE: constant in a local, flips s2/s3 preheader order
        if (D_807F9420 == 0) {}  // FAKE: dead statement, steers P into a3 / s4-s6 order
        j = 0;
        found = 0;
        entry = (ActorTargetEntry *)((s32)D_807F9420 + i * stride);
        if (entry->unk6 == arg0) {
            do {
                new_var = &D_807FC924;  // FAKE: pointer-to-pointer read steers regalloc
                if (D_807F9420[i].u.unk7_arr[j] == (*new_var)->unk290) {
                    found = 1;
                }
                j++;
                if (j >= 5 || found) {
                    break;
                }
            } while (D_807F9420[i].u.unk7_arr[j] != -1);

            if (found) {
                sfxUpdateDistanceVolumeAndPan(entry->unk0, entry->unk2, entry->unk4, arg1, arg2, arg3);
            }
        }
    }
}


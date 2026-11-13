#include "common.h"
#include "proto/global/5230.h"

extern u16 D_80744734[];
extern s32 gCurrentMap;
#include "sched.h"
extern SchedStruct gScheduler;

// .bss 0x8076AF00-0x8076AF20
s16 D_8076AF00[7];
u16 D_8076AF0E;
s32 D_8076AF10;
u8 D_8076AF14;
u8 D_8076AF15;
u16 D_8076AF16;
u8 D_8076AF18[8];

s32 frameTimingGetMapIndex(void) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while (!found && i < 8) {
        if (gCurrentMap == D_80744734[i]) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        i = 0;
    }
    return i;
}

void frameTimingReset(s32 mapId) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_8076AF00[i] = 2;
    }

    D_8076AF10 = gScheduler.unk284;
    switch (mapId) {
    case 0x6:
    case 0x1B:
    case 0x27:
    case 0x28:
    case 0x37:
    case 0x4C:
    case 0x6A:
    case 0x98:
    case 0x99:
    case 0xAC:
    case 0xD0:
        D_8076AF14 = 0;
        break;
    default:
        D_8076AF14 = 1;
        break;
    }
}

extern u32 gFrameDelta;
extern u8 D_80745290;
#define SCHED284 (*(volatile s32 *)&gScheduler.unk284)

void frameTimingUpdate(void) {
    s32 max;
    s32 min;
    s32 sample;
    s32 flag;
    s32 n;
    s32 i;
    s32 idx;
    u32 limit;
    s32 *p;

    max = 1;
    min = 20;
    if (D_8076AF14 != 0) {
        sample = SCHED284 - D_8076AF10;
        if (sample <= 0) {
            sample = 1;
        }
        D_8076AF00[D_80745290] = sample;
        D_80745290++;
        if (D_80745290 == 8) {
            D_80745290 = 0;
        }
        if (gFrameDelta >= 4) {
            n = 1;
        } else if (gFrameDelta < sample) {
            n = 2;
        } else {
            n = 4;
        }
        idx = D_80745290;
        flag = 0;
        for (i = 0; i < n; i++) {
            if (gFrameDelta && gFrameDelta) {}  // FAKE: dead read splits the hoisted gFrameDelta address web (lui/%lo per access, less max/min interference)
            idx--;
            if (idx < 0) {
                idx = 7;
            }
            if (D_8076AF00[idx] >= max) {
                max = D_8076AF00[idx];
            }
            if (min >= D_8076AF00[idx]) {
                min = D_8076AF00[idx];
            }
        }
        if (gFrameDelta < sample && gFrameDelta < min) {
            flag = 1;
        } else if (sample < gFrameDelta && max < gFrameDelta) {
            flag = 1;
        }
        if (flag != 0) {
            gFrameDelta = sample;
        }
        if (gFrameCounter >= 0xB) {
            p = &gScheduler.unk284;
            limit = D_8076AF10 + gFrameDelta;
            if (SCHED284 < limit) {
                do {
                } while (*(volatile s32 *)p < limit);
            }
        }
        D_8076AF10 = SCHED284;
    } else {
        gFrameDelta = SCHED284 - D_8076AF10;
        D_8076AF10 = SCHED284;
    }
}

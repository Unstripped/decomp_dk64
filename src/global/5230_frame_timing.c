#include "common.h"
#include "proto/global/5230_frame_timing.h"

extern u16 gWorldLobbyMaps[];
extern s32 gCurrentMap;
#include "sched.h"
extern SchedStruct gScheduler;

// .bss 0x8076AF00-0x8076AF20
s16 sFrameTimingSamples[8];
s32 sFrameTimingLastRetrace;
u8 sFrameTimingPaced;
u8 D_8076AF15;
u16 D_8076AF16;
u8 D_8076AF18[8];

s32 frameTimingGetMapIndex(void) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while (!found && i < 8) {
        if (gCurrentMap == gWorldLobbyMaps[i]) {
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
        sFrameTimingSamples[i] = 2;
    }

    sFrameTimingLastRetrace = gScheduler.retraceCount;
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
        sFrameTimingPaced = 0;
        break;
    default:
        sFrameTimingPaced = 1;
        break;
    }
}

extern u32 gFrameDelta;
u8 sFrameTimingSampleIndex = 0;
// The scheduler thread increments retraceCount; frame timing polls it, so these reads must not be cached.
#define SCHED_RETRACE_COUNT (*(volatile s32 *)&gScheduler.retraceCount)

void frameTimingUpdate(void) {
    s32 max;
    s32 min;
    s32 sample;
    s32 flag;
    s32 n;
    s32 i;
    s32 idx;
    u32 limit;
    volatile s32 *p;

    max = 1;
    min = 20;
    if (sFrameTimingPaced != 0) {
        sample = SCHED_RETRACE_COUNT - sFrameTimingLastRetrace;
        if (sample <= 0) {
            sample = 1;
        }
        sFrameTimingSamples[sFrameTimingSampleIndex] = sample;
        sFrameTimingSampleIndex++;
        if (sFrameTimingSampleIndex == 8) {
            sFrameTimingSampleIndex = 0;
        }
        if (gFrameDelta >= 4) {
            n = 1;
        } else if (gFrameDelta < sample) {
            n = 2;
        } else {
            n = 4;
        }
        idx = sFrameTimingSampleIndex;
        flag = 0;
        for (i = 0; i < n; i++) {
            idx--;
            if (idx < 0) {
                idx = 7;
            }
            max = MAX(max, sFrameTimingSamples[idx]);
            min = MIN(min, sFrameTimingSamples[idx]);
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
            p = &gScheduler.retraceCount;
            limit = sFrameTimingLastRetrace + gFrameDelta;
            while (*p < limit) {
            }
        }
        sFrameTimingLastRetrace = SCHED_RETRACE_COUNT;
    } else {
        gFrameDelta = SCHED_RETRACE_COUNT - sFrameTimingLastRetrace;
        sFrameTimingLastRetrace = SCHED_RETRACE_COUNT;
    }
}

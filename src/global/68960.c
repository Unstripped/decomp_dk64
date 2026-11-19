#include "common.h"
#include "proto/global/201B0.h"
#include "proto/global/68960.h"

typedef struct MapFogEntry {
    s16 map;
    s8 character;
    s8 pad3;
    s16 fogDistance;
} MapFogEntry;

// This TU's .data (0x80748B70-0x80748B94 + 12-byte TU pad).
MapFogEntry gMapFogDistances[6] = {
    { 72, 4, 0, 2500 },
    { 72, 8, 0, 2500 },
    { 72, 5, 0, 1000 },
    { 72, 0, 0, 1500 },
    { 72, 13, 0, 4000 },
    { 72, -1, 0, 800 },
};
extern s32 gCurrentMap;

void mapUpdateFogDistance(f32 *pDist, s16 characterId) {
    s16 count = sizeof(gMapFogDistances) / sizeof(gMapFogDistances[0]);
    f32 target;
    f32 val;
    s16 i;

    if (gCurrentMap == 0x57) {
        if (camIsFollowingActive()) {
            target = 2200.0f;
        } else {
            target = 900.0f;
        }
        val = *pDist;
        *pDist = (target - val) * 0.03 + val;
    }

    for (i = 0; i < count; i++) {
        if (gCurrentMap == gMapFogDistances[i].map && (characterId == gMapFogDistances[i].character || gMapFogDistances[i].character == -1)) {
            val = *pDist;
            *pDist = (gMapFogDistances[i].fogDistance - val) * 0.03 + val;
            return;
        }
    }
}


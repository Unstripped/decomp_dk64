#include "common.h"
#include "proto/global/201B0.h"
#include "proto/global/68960.h"

typedef struct MapFogEntry {
    s16 map;
    s8 character;
    s8 pad3;
    s16 fogDistance;
} MapFogEntry;

extern MapFogEntry gMapFogDistances[6];
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


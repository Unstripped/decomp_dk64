#include "common.h"
#include "proto/global/201B0.h"
#include "proto/global/68960.h"

typedef struct MapFogEntry {
    s16 map;
    s8 character;
    s8 pad3;
    s16 fogDistance;
} MapFogEntry;

extern MapFogEntry D_80748B70[];
extern s32 gCurrentMap;

void mapUpdateFogDistance(f32 *pDist, s16 characterId) {
    s16 limit = 6; // FAKE: value-named constant local keeps 6 in a register (slt at,i,t1); a literal 6 folds to slti and reshapes the frame
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

    for (i = 0; i < limit; i++) {
        if (gCurrentMap == D_80748B70[i].map && (characterId == D_80748B70[i].character || D_80748B70[i].character == -1)) {
            val = *pDist;
            *pDist = (D_80748B70[i].fogDistance - val) * 0.03 + val;
            return;
        }
    }
}


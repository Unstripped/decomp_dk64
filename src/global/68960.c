#include "common.h"
#include "actor.h"


typedef struct MapFogEntry {
    s16 unk0;
    s8 unk2;
    s8 pad3;
    s16 unk4;
} MapFogEntry;

extern MapFogEntry D_80748B70[];
extern s32 gCurrentMap;
s32 camIsFollowingActive(void);

void mapUpdateFogDistance(f32 *pDist, s16 characterId) {
    s16 limit = 6;
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
        if (gCurrentMap == D_80748B70[i].unk0 && (characterId == D_80748B70[i].unk2 || D_80748B70[i].unk2 == -1)) {
            val = *pDist;
            *pDist = (D_80748B70[i].unk4 - val) * 0.03 + val;
            return;
        }
    }
}


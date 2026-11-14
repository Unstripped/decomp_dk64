#include "common.h"
#include "proto/global/F93B0.h"

extern s32 gCurrentMap;

typedef struct {
    s16 map;
    s8 character;
    u8 pad3;
    s16 value;
} MapVoidHeight;

extern MapVoidHeight gMapVoidHeights[13];

f32 mapGetVoidHeightForCharacter(s16 characterId) {
    s32 map;
    s32 count;
    s16 i;
    MapVoidHeight *e;

    count = sizeof(gMapVoidHeights) / sizeof(gMapVoidHeights[0]);
    i = 0; map = gCurrentMap; do { // LAYOUT: statements joined on one line steer as1 scheduling
        e = &gMapVoidHeights[i];
        if (e->map == map && (characterId == e->character || e->character == -1)) {
            return e->value;
        }
        i++;
    } while (i < count);
    return 20000.0f;
}

#include "common.h"
#include "proto/global/F93B0.h"

extern s32 gCurrentMap;

typedef struct {
    s16 map;
    s8 character;
    u8 pad3;
    s16 value;
} MapVoidHeight;

extern MapVoidHeight D_80753EA0[];

f32 mapGetVoidHeightForCharacter(s16 characterId) {
    s32 map;
    s32 lim;
    s16 i;
    MapVoidHeight *e;

    lim = 13; // FAKE: value-named constant local keeps 13 in a register (slt at,i,v0); a literal 13 folds to slti
    i = 0; map = gCurrentMap; do { e = &D_80753EA0[i]; if (e->map == map && (characterId == e->character || e->character == -1)) { return e->value; } // LAYOUT: statements joined on one line steer as1 scheduling
        i++;
    } while (i < lim);
    return 20000.0f;
}

#include "common.h"
#include "proto/global/F93B0.h"

extern s32 gCurrentMap;

typedef struct {
    s16 map;
    s8 character;
    u8 pad3;
    s16 value;
} MapVoidHeight;

// This TU's .data (0x80753EA0-0x80753EEE + 2-byte TU pad).
MapVoidHeight gMapVoidHeights[13] = {
    { 0x1E, 9, 0, 2260 },
    { 0x1E, -1, 0, 1976 },
    { 0x26, -1, 0, 550 },
    { 0xCC, -1, 0, 380 },
    { 0xC9, -1, 0, 550 },
    { 0x22, -1, 0, 2200 },
    { 0x30, 0, 0, 800 },
    { 0x30, 11, 0, 1640 },
    { 0x30, 8, 0, 450 },
    { 0x30, 14, 0, 700 },
    { 0x30, -1, 0, 450 },
    { 0x48, -1, 0, 800 },
    { 0x57, -1, 0, 2100 },
};

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

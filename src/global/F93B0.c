#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern Struct807FD580 *gActivePlayerState;
extern s16 D_807FD584;
extern s32 gCurrentMap;
extern u8 gPlayerCharacterId[];

typedef struct {
    s16 map;
    s8 character;
    u8 pad3;
    s16 value;
} F9N5_MapHeight;

extern F9N5_MapHeight D_80753EA0[];

f32 mapGetVoidHeightForCharacter(s16 characterId) {
    s32 map;
    s32 lim;
    s16 i;
    F9N5_MapHeight *e;

    lim = 13;
    i = 0; map = gCurrentMap; do { e = &D_80753EA0[i]; if (e->map == map && (characterId == e->character || e->character == -1)) { return e->value; } // LAYOUT: statements joined on one line steer as1 scheduling
        i++;
    } while (i < lim);
    return 20000.0f;
}

#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern s32 D_8076A0A8;
extern u8 D_8074E77C[];

typedef struct {
    s16 map;
    s8 character;
    u8 pad3;
    s16 value;
} F9N5_MapHeight;

extern F9N5_MapHeight D_80753EA0[];

f32 func_806F46B0(s16 arg0) {
    s32 map;
    s32 lim;
    s16 i;
    F9N5_MapHeight *e;

    lim = 13;
    i = 0; map = D_8076A0A8; do { e = &D_80753EA0[i]; if (e->map == map && (arg0 == e->character || e->character == -1)) { return e->value; } // FAKE: statements joined on one line steer as1 scheduling
        i++;
    } while (i < lim);
    return 20000.0f;
}

#ifndef MAP_H
#define MAP_H

#include "common.h"

// One ambient sound emitter of the map geometry file (mapGetSoundEmitters); 8 bytes.
typedef struct LevelSoundEmitter {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 volume;
    /* 0x7 */ u8 group;
} LevelSoundEmitter; // size = 0x8

#endif

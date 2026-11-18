#ifndef ARCADE_H
#define ARCADE_H

#include "common.h"

// Types shared by the arcade overlay (ovl08): 0.c (game code) and E220.c (sprite pixels and
// entity templates).

// One Donkey Kong arcade entity (D_8004BCD0[80]; templates D_8004A398..D_8004A718); 0x20 bytes.
typedef struct ArcadeEntity {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 vx;
    /* 0x0C */ f32 vy;
    /* 0x10 */ f32 animTimer;
    /* 0x14 */ void *sprite;
    /* 0x18 */ u8 type;
    /* 0x19 */ u8 state;
    /* 0x1A */ u8 facing; // bit0: texture S flip (barrels: set = rolling left, vx = 1 - 2 * facing); bit1: player last moved right
    /* 0x1B */ u8 flipY; // texture T flip (arcadeRenderEntity)
    /* 0x1C */ u8 param; // per-type: rank, spawn index, timer or flag bits
    /* 0x1D */ u8 param2; // per-type: jump start y, linked entity index, name-entry cursor
    /* 0x1E */ u8 width; // sprite texture width (arcadeRenderEntity)
    /* 0x1F */ u8 height; // sprite texture height
} ArcadeEntity;

#endif

#ifndef JETPAC_H
#define JETPAC_H

#include "common.h"

/* Jetpac overlay types shared by src/jetpac/. */

typedef struct JetpacSprite {
    /* 0x00 */ void *frame;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
} JetpacSprite; // size 0x18

typedef struct JetpacExplosion {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 timer;
    /* 0x0C */ u8 color[4];
} JetpacExplosion; // size 0x10

/* Enemies (jetpacActors) and lasers (jetpacLasers). */
typedef struct JetpacActor {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 vx;
    /* 0x0C */ f32 vy;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ s32 state;
    /* 0x18 */ s32 flip;
    /* 0x1C */ s32 boxX1;
    /* 0x20 */ s32 boxY1;
    /* 0x24 */ s32 boxX2;
    /* 0x28 */ s32 boxY2;
    /* 0x2C */ s32 timer;
    /* 0x30 */ JetpacExplosion explosion;
    /* 0x40 */ u32 lifetime;
    /* 0x44 */ s32 points;
    /* 0x48 */ void (*update)(struct JetpacActor *);
    /* 0x4C */ JetpacSprite *sprite;
} JetpacActor; // size 0x50

/* The jetman (jetpacPlayer): JetpacActor's first 0x30 bytes, then player state. */
typedef struct JetpacPlayerActor {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 vx;
    /* 0x0C */ f32 vy;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ s32 state;
    /* 0x18 */ s32 flip;
    /* 0x1C */ s32 boxX1;
    /* 0x20 */ s32 boxY1;
    /* 0x24 */ s32 boxX2;
    /* 0x28 */ s32 boxY2;
    /* 0x2C */ s32 timer;
    /* 0x30 */ s32 flying;
    /* 0x34 */ s32 ledge;
    /* 0x38 */ s32 fireCooldown;
    /* 0x3C */ JetpacExplosion explosion;
} JetpacPlayerActor; // size 0x4C

/* jetpacPlayer: the jetman followed by his lasers. */
typedef struct JetpacState {
    /* 0x00 */ JetpacPlayerActor player;
    /* 0x4C */ JetpacActor lasers[4];
} JetpacState;

/* Rocket parts and bonus items. */
typedef struct JetpacItem {
    /* 0x00 */ JetpacSprite *sprites[2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 color[4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ void (*unk44)(struct JetpacItem *);
    /* 0x48 */ void (*unk48)(struct JetpacItem *, s32);
} JetpacItem; // size 0x4C

typedef struct JetpacPlayer {
    /* 0x000 */ s32 stage;
    /* 0x004 */ s32 score;
    /* 0x008 */ s32 lives;
    /* 0x00C */ s32 unkC;
    /* 0x010 */ s32 currentItem;
    /* 0x014 */ JetpacItem items[4];
    /* 0x144 */ s32 unk144;
    /* 0x148 */ JetpacItem bonus;
} JetpacPlayer; // size 0x194

typedef struct JetpacLedge {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ u8 pad14[8];
    /* 0x1C */ s32 boxX1;
    /* 0x20 */ s32 boxY1;
    /* 0x24 */ s32 boxX2;
    /* 0x28 */ s32 boxY2;
    /* 0x2C */ u8 pad2C[4];
    /* 0x30 */ s32 unk30;
} JetpacLedge; // size 0x34

/* jetpacGame; jetpacLedges, jetpacPlayer, jetpacLasers and jetpacActors are symbols inside it. */
typedef struct JetpacGlobal {
    /* 0x000 */ u32 buttons;
    /* 0x004 */ u32 prevButtons;
    /* 0x008 */ u32 pressedButtons;
    /* 0x00C */ s8 menuSelection;
    /* 0x00D */ u8 padD[0x18 - 0xD];
    /* 0x018 */ s32 highScore;
    /* 0x01C */ JetpacPlayer players[2];
    /* 0x344 */ s32 activePlayer;
    /* 0x348 */ s32 numPlayers;
    /* 0x34C */ s32 controlType;
    /* 0x350 */ JetpacLedge ledges[4];
    /* 0x420 */ JetpacPlayerActor player;
    /* 0x46C */ JetpacActor lasers[4];
    /* 0x5AC */ JetpacActor actors[6];
    /* 0x78C */ s32 gameState;
    /* 0x790 */ u32 stateTimer;
    /* 0x794 */ u32 unk794;
    /* 0x798 */ u8 unk798;
    /* 0x799 */ u8 unk799;
} JetpacGlobal;

/* One cell of the 32x24 sprite grid. */
typedef struct JetpacCellItem {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 flip;
    /* 0x0C */ JetpacSprite *texture;
} JetpacCellItem;

typedef struct JetpacCell {
    /* 0x00 */ JetpacCellItem items[6];
    /* 0x60 */ s32 count;
    /* 0x64 */ u8 color[4];
} JetpacCell;

extern JetpacGlobal jetpacGame;
extern JetpacCell jetpacGrid[24][32];

#endif

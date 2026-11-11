#ifndef RACE_H
#define RACE_H

#include "common.h"
#include "actor.h"

// Race actor records shared by the race overlay (1770 vehicle race, 36B0 car race, 7BD0 race manager,
// A960 racers): the per-actor components that actorAllocate places from Actor.customState (0x174) on.

// Checkpoint path cursor (vehicle/car racer component; racePathFollowStep, raceAdvanceCheckpoint); 0x3C bytes.
typedef struct RacePathState {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8 pad2C[4];
    /* 0x30 */ struct Actor *unk30;
    /* 0x34 */ void *unk34;
    /* 0x38 */ u8 pad38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 pad3A[2];
} RacePathState; // size = 0x3C

// Race participant record (Actor.customState of racers and the player tracker; registered with the race
// manager by raceRegisterParticipant, which only touches 0x27..0x48). 0x14..0x1F differ by actor type.
typedef struct RaceParticipant {
    /* 0x00 */ s8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0xC];
    union {
        struct {
            /* 0x14 */ u8 pad14[8];
            /* 0x1C */ u16 unk1C; // racers
            /* 0x1E */ u8 pad1E[2];
        };
        struct {
            /* 0x14 */ f32 unk14; // player tracker (racePlayerTrackerBehaviorUpdate)
            /* 0x18 */ f32 unk18;
            /* 0x1C */ f32 unk1Cf;
        };
    };
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 route; // route index (raceGetRoute)
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 playerIdx;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ struct Actor *unk2C;
    /* 0x30 */ struct Actor *actor; // the race manager this participant is registered with
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ s8 lap;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 pad39;
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ u8 pad3E[2];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 pad47;
    /* 0x48 */ s32 unk48; // camera viewport entry (cameraFindViewportEntry)
    /* 0x4C */ u8 pad4C[0x104 - 0x4C];
    /* 0x104 */ void *unk104;
} RaceParticipant; // size = 0x108

#endif

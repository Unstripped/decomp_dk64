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

struct RacePair;

// Race participant record (Actor.customState of racers, the player tracker and the race manager; registered
// with the manager by raceRegisterParticipant, which only touches 0x27..0x48). 0x00..0x23 differ by actor
// type: the manager (7BD0 raceInit*RaceManager, raceManagerBehaviorUpdate) keeps its HUD/minimap setup and
// the registered participant array there.
typedef struct RaceParticipant {
    union {
        /* 0x00 */ s8 unk0;
        /* 0x00 */ u8 hudFlags; // manager: 2 place, 4 lap counter, 8 coin HUD, 0x10 speed-boost HUD
        /* 0x00 */ s16 heading; // 52B0 opponent racers: steering yaw (raceRacerSteerTowardWaypoint)
    };
    /* 0x02 */ s16 unk2; // 52B0 opponent racers: eased yaw offset
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8; // manager 0x04..0x10: minimap scale X, scale Z, centre X, centre Z (raceCalculatePathBoundingBox)
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    union {
        struct {
            /* 0x14 */ u8 pad14[8];
            /* 0x1C */ u16 unk1C; // racers; manager: frame timer
            /* 0x1E */ u8 unk1E; // manager: registered participant count
            /* 0x1F */ u8 pad1F;
        };
        struct {
            /* 0x14 */ f32 unk14; // player tracker (racePlayerTrackerBehaviorUpdate)
            /* 0x18 */ f32 unk18;
            /* 0x1C */ f32 unk1Cf;
        };
        struct {
            /* 0x14 */ s16 minimapSprites[4]; // manager: radar background sprite ids
        };
    };
    union {
        /* 0x20 */ struct RacePair *pairs; // manager: the registered participants (raceInitParticipantArray)
        /* 0x20 */ s32 unk20; // 6650 racers: nonzero turns the thrust around and caps speed (raceUpdateRacerMotion)
    };
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
    union {
        /* 0x37 */ s8 lap;
        /* 0x37 */ u8 unk37;
    };
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
    /* 0x48 */ struct G00Entry *unk48; // camera viewport entry (cameraFindViewportEntry)
    /* 0x4C */ u8 pad4C[4];
    /* 0x50 */ Mtx_t hudScale[2]; // per gfx buffer: the HUD text scale matrix (raceInitHudDisplayList guScale)
    /* 0xD0 */ u8 padD0[0x104 - 0xD0];
    /* 0x104 */ void *unk104;
} RaceParticipant; // size = 0x108

// One race route (raceGetRoute): the ordered waypoint indices a participant passes.
typedef struct RaceRoute {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u16 *items;
    /* 0x08 */ u16 active;
    /* 0x0A */ u8 padA[2];
} RaceRoute;

// One registered participant of the race manager (RaceParticipant.pairs[slot]).
typedef struct RacePair {
    /* 0x0 */ struct Actor *actor;
    /* 0x4 */ RaceParticipant *data;
} RacePair; // size = 0x8

// Actor types with three components (racers spawned by spawnNodeSpawnById(1, ...)): the 0x178 participant
// record and the 0x17C rubber-band target, whose actor/participant the race manager fills with the racer
// to chase (raceGetParticipantPair).
typedef struct RaceComponentActor {
    /* 0x000 */ struct Actor base;
    /* 0x178 */ RaceParticipant *participant;
    /* 0x17C */ struct RaceTarget *target;
} RaceComponentActor;

// One waypoint/gate of the race path (raceGetWaypoint).
typedef struct RaceWaypoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u16 angle;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 kind;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 mode;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ u16 width;
    /* 0x1C */ struct Actor *actors[2]; // the two gate posts (raceSetGateVisualState)
    /* 0x24 */ s32 state;
} RaceWaypoint;

// Racer rubber-band state (a racer component): the racer it chases, its speed-curve mode
// (raceSetPiecewiseCurveMode) and the bump cooldown and distance of raceHandleRacerCollision.
typedef struct RaceTarget {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ RaceParticipant *participant;
    /* 0x08 */ u8 finishCamStarted; // 52B0 opponents: finish camera path started
    /* 0x09 */ u8 pad9;
    /* 0x0A */ u16 startCountdown; // 52B0 opponents: start countdown frames
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ u8 bumpCooldown;
    /* 0x0F */ u8 curveMode;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 distSq;
} RaceTarget; // size = 0x18

// One knot of a piecewise-linear speed curve (raceEvaluatePiecewiseCurve reads 6).
typedef struct RaceCurvePoint {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
} RaceCurvePoint;

typedef struct RaceVec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} RaceVec3f;

// Race projectile component (1770 racer projectiles, the 0x17C component): the racer that fired it and
// its homing target (raceFindNearestParticipant); raceDespawnProjectile clears the owner's unk2C.
typedef struct RaceAuxState {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ struct Actor *target;
    /* 0x0C */ struct Actor *owner;
} RaceAuxState; // size = 0x10

#endif

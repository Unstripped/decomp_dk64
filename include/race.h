#ifndef RACE_H
#define RACE_H

#include "common.h"
#include "actor.h"

// Race actor records shared by the race overlay (1770 vehicle race, 36B0 car race, 7BD0 race manager,
// A960 racers): the per-actor components that actorAllocate places from Actor.customState (0x174) on.

// Checkpoint path cursor (vehicle/car racer component; racePathFollowStep, raceAdvanceCheckpoint); 0x3C bytes.
typedef struct RacePathState {
    /* 0x00 */ u8 lane;
    /* 0x01 */ u8 targetLane;
    /* 0x02 */ u16 waypoint;
    /* 0x04 */ u8 laneSettleTimer;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ f32 laneBlend;
    /* 0x0C */ f32 laneOffset;
    /* 0x10 */ u8 boostTimer;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 boostAmount;
    /* 0x18 */ f32 bankAngle;
    /* 0x1C */ f32 pitchAngle;
    /* 0x20 */ f32 shakeRoll;
    /* 0x24 */ f32 shakePitch;
    /* 0x28 */ f32 bankVelocity;
    /* 0x2C */ u8 pad2C[4];
    /* 0x30 */ struct Actor *targetActor;
    /* 0x34 */ void *cameraActor;
    /* 0x38 */ u8 pad38;
    /* 0x39 */ u8 stunTimer;
    /* 0x3A */ u8 pad3A[2];
} RacePathState; // size = 0x3C

struct RacePair;

// Race participant record (Actor.customState of racers, the player tracker and the race manager; registered
// with the manager by raceRegisterParticipant, which only touches 0x27..0x48). 0x00..0x23 differ by actor
// type: the manager (7BD0 raceInit*RaceManager, raceManagerBehaviorUpdate) keeps its HUD/minimap setup and
// the registered participant array there.
typedef struct RaceParticipant {
    union {
        /* 0x00 */ s8 gateKind;
        /* 0x00 */ u8 hudFlags; // manager: 2 place, 4 lap counter, 8 coin HUD, 0x10 speed-boost HUD
        /* 0x00 */ s16 heading; // 52B0 opponent racers: steering yaw (raceRacerSteerTowardWaypoint)
    };
    /* 0x02 */ s16 yawOffset; // 52B0 opponent racers: eased yaw offset
    union {
        struct {
            /* 0x04 */ f32 throttle;
            /* 0x08 */ f32 brake;
            /* 0x0C */ f32 steer;
            /* 0x10 */ f32 steerGain;
        };
        struct { // manager: minimap transform (raceCalculatePathBoundingBox, raceRenderMinimapIcon)
            /* 0x04 */ f32 minimapScaleX;
            /* 0x08 */ f32 minimapScaleZ;
            /* 0x0C */ f32 minimapCenterX;
            /* 0x10 */ f32 minimapCenterZ;
        };
    };
    union {
        struct {
            /* 0x14 */ u8 pad14[8];
            /* 0x1C */ u16 phaseTimer; // racers; manager: frame timer
            /* 0x1E */ u8 participantCount; // manager: registered participant count
            /* 0x1F */ u8 pad1F;
        };
        struct {
            /* 0x14 */ f32 progressScore; // player tracker (racePlayerTrackerBehaviorUpdate)
            /* 0x18 */ f32 maxProgressScore;
            /* 0x1C */ f32 maxNextPointDistSq;
        };
        struct {
            /* 0x14 */ s16 minimapSprites[4]; // manager: radar background sprite ids
        };
    };
    union {
        /* 0x20 */ struct RacePair *pairs; // manager: the registered participants (raceInitParticipantArray)
        /* 0x20 */ s32 reverseThrust; // 6650 racers: nonzero turns the thrust around and caps speed (raceUpdateRacerMotion)
    };
    /* 0x24 */ u8 lapCount;
    /* 0x25 */ u8 hasCpuRival;
    /* 0x26 */ u8 route; // route index (raceGetRoute)
    /* 0x27 */ u8 isCpu;
    /* 0x28 */ u8 playerIdx;
    /* 0x29 */ u8 fireRequested;
    /* 0x2A */ u8 projectileAmmo;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ struct Actor *projectile;
    /* 0x30 */ struct Actor *actor; // the race manager this participant is registered with
    /* 0x34 */ u8 raceStatus;
    /* 0x35 */ u8 statusStep;
    /* 0x36 */ u8 place;
    /* 0x37 */ s8 lap;
    /* 0x38 */ u8 facingWaypoint;
    /* 0x39 */ u8 pad39;
    /* 0x3A */ u16 routePos;
    /* 0x3C */ u16 activeGatePos;
    /* 0x3E */ u8 pad3E[2];
    /* 0x40 */ f32 nextPointDist;
    /* 0x44 */ u8 gateMissesLeft;
    /* 0x45 */ u8 eliminated;
    /* 0x46 */ u8 resultTextId;
    /* 0x47 */ u8 pad47;
    /* 0x48 */ struct ViewportLayout *viewport; // camera viewport entry (cameraFindViewportEntry)
    /* 0x4C */ u8 pad4C[4];
    /* 0x50 */ Mtx_t hudScale[2]; // per gfx buffer: the HUD text scale matrix (raceInitHudDisplayList guScale)
    /* 0xD0 */ s16 unkD0;
    /* 0xD2 */ u8 padD2[0x108 - 0xD2];
} RaceParticipant; // size = 0x108

// A racer actor (936B0 VEHICLE_ACTOR helpers, raceCompetitorMotionUpdate): the participant record at 0x174 and
// the motion state (936B0 VehicleMotion) the shared racer helpers step at 0x178.
typedef struct VehicleActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ struct VehicleMotion *motion;
} VehicleActor;

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
    /* 0x08 */ f32 normalX;
    /* 0x0C */ f32 normalZ;
    /* 0x10 */ u8 kind;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 gateScale;
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
    /* 0x10 */ u8 chaseEnabled;
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
    /* 0x00 */ u16 lifetime;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ struct Actor *target;
    /* 0x0C */ struct Actor *owner;
} RaceAuxState; // size = 0x10

// Racer actor: its participant is the customState (0x174); path cursor and aux state follow.
typedef struct RaceRacerActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RacePathState *path;
    /* 0x17C */ RaceAuxState *aux;
} RaceRacerActor;

#endif

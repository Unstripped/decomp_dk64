#ifndef SCHED_H
#define SCHED_H

#include "common.h"

// Scheduler task / client node (0x5C bytes)
typedef struct TaskNode {
    /* 0x00 */ struct TaskNode *next;
    /* 0x04 */ s32 state;
    /* 0x08 */ u32 flags;
    /* 0x0C */ void *framebuffer;
    /* 0x10 */ OSTask task;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ OSMesgQueue *msgQ;
    /* 0x58 */ OSMesg msg;
} TaskNode;

// Scheduler client registration (0x10 bytes), linked from SchedStruct.clientList
typedef struct SchedClient {
    /* 0x00 */ struct SchedClient *next;
    /* 0x04 */ OSMesgQueue *msgQ;
    /* 0x08 */ s32 id;
    /* 0x0C */ s32 kind;
} SchedClient;

// Scheduler context (0x298 bytes)
typedef struct SchedStruct {
    /* 0x000 */ OSMesgQueue interruptQ;
    /* 0x018 */ OSMesg intMsgs[16];
    /* 0x058 */ OSMesgQueue cmdQ;
    /* 0x070 */ OSMesg cmdMsgs[16];
    /* 0x0B0 */ OSThread thread;
    /* 0x260 */ SchedClient *clientList;
    /* 0x264 */ TaskNode *audioListHead;
    /* 0x268 */ TaskNode *gfxListHead;
    /* 0x26C */ TaskNode *audioListTail;
    /* 0x270 */ TaskNode *gfxListTail;
    /* 0x274 */ TaskNode *curRSPTask;
    /* 0x278 */ TaskNode *curRDPTask;
    /* 0x27C */ u32 frameCount;
    /* 0x280 */ u32 unk280;
    /* 0x284 */ s32 unk284;
    /* 0x288 */ u64 unk288;
    /* 0x290 */ u64 unk290;
} SchedStruct;

// Scheduler config copied in schedCreate (0xC bytes)
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} SchedConfig;

// Rumble-pak state struct (0x14 bytes each), array at gRumbleInfo
typedef struct {
    /* 0x00 */ s32 pakState;
    /* 0x04 */ u8 motorOn;
    /* 0x05 */ u8 intensity;
    /* 0x06 */ u8 pad06[2];
    /* 0x08 */ u32 pwmAccum;
    /* 0x0C */ s32 duration;
    /* 0x10 */ u16 heat;
    /* 0x12 */ u8 overheated;
    /* 0x13 */ u8 pad13;
} RumbleInfo;

struct Actor;

// Player struct array (stride 0x2F0) pointed to by gPlayerSlots
// Health HUD state block (PlayerStruct.healthHud, hudDrawItemWithAlpha in 10D2D0.c).
typedef struct HealthHudInit {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ u8 unkA;
} HealthHudInit; // size = 0xC

typedef struct {
    /* 0x000 */ u8 active;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ struct Actor *actor;
    /* 0x008 */ Mtx viewMtx[2];
    /* 0x088 */ Mtx projMtx[2];
    /* 0x108 */ Mtx bgMtx[2]; // per-buffer sky quad matrix (gfxDrawBackgroundQuad)
    /* 0x188 */ u16 perspNorm;
    /* 0x18A */ u8 pad18A[0x190 - 0x18A];
    /* 0x190 */ LookAt lookAt[2]; // per-buffer guLookAtHilite output (gSPLookAtX/Y)
    /* 0x1D0 */ Hilite hilite[2]; // per-buffer specular highlight tile offsets
    /* 0x1F0 */ Gfx hiliteDl[2][2]; // per-buffer segment-5 display list (gDPSetHilite1Tile)
    /* 0x210 */ f32 camX;
    /* 0x214 */ f32 camY;
    /* 0x218 */ f32 camZ;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 focusX;
    /* 0x22C */ f32 focusY;
    /* 0x230 */ f32 focusZ;
    /* 0x234 */ f32 unk234;
    /* 0x238 */ f32 unk238;
    /* 0x23C */ f32 unk23C;
    /* 0x240 */ f32 upX;
    /* 0x244 */ f32 upY;
    /* 0x248 */ f32 upZ;
    /* 0x24C */ f32 unk24C;
    /* 0x250 */ Vp viewport[2];
    s16 rect[4];
    s16 unk278;
    s16 unk27A;
    /* 0x27C */ f32 fov;
    /* 0x280 */ f32 unk280;
    /* 0x284 */ f32 unk284;
    /* 0x288 */ f32 farClip;
    /* 0x28C */ f32 prevFov;
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[2];
    /* 0x294 */ OSContPad *contPad;
    /* 0x298 */ u16 *heldButtonsPtr;
    s16 queuedState;
    u8 pad29E[2];
    struct Actor *queuedActor;
    s32 queuedActorId;
    s32 queuedParam0;
    s32 queuedParam1;
    s32 queuedParam2;
    /* 0x2B4 */ f32 headX;
    /* 0x2B8 */ f32 headY;
    /* 0x2BC */ f32 headZ;
    u8 unk2C0;
    /* 0x2C1 */ u8 sizeModeDirty;
    /* 0x2C2 */ u8 pad2C2[2];
    /* 0x2C4 */ f32 unk2C4;
    /* 0x2C8 */ s16 unk2C8;
    /* 0x2CA */ s16 camYInt;
    /* 0x2CC */ s16 skyRoll;
    /* 0x2CE */ u8 pad2CE[2];
    /* 0x2D0 */ f32 unk2D0;
    /* 0x2D4 */ f32 bgRotX;
    /* 0x2D8 */ f32 bgRotY;
    union {
        /* 0x2DC */ HealthHudInit healthHud; // health HUD state (hudDrawItemWithAlpha, 10D2D0.c)
        struct {
            /* 0x2DC */ f32 unk2DC;
            /* 0x2E0 */ u16 unk2E0; // health HUD flash phase (sinApprox * 65535)
            union {
                /* 0x2E2 */ u16 unk2E2; // HUD flags
                struct {
                    /* 0x2E2 */ u8 pad2E2;
                    /* 0x2E3 */ u8 unk2E3; // low byte of unk2E2, read on its own by the health HUD
                };
            };
            /* 0x2E4 */ u8 unk2E4;
            /* 0x2E5 */ u8 unk2E5;
            /* 0x2E6 */ u8 unk2E6;
            /* 0x2E7 */ u8 pad2E7;
        };
    };
    /* 0x2E8 */ u8 unk2E8;
    /* 0x2E9 */ u8 unk2E9;
    u8 unk2EA;
    u8 unk2EB;
    u8 pad2EC[4];
} PlayerStruct;

typedef PlayerStruct RumblePlayer;

#endif

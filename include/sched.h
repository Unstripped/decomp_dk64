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

// Scheduler context (0x298 bytes)
typedef struct SchedStruct {
    /* 0x000 */ OSMesgQueue interruptQ;
    /* 0x018 */ OSMesg intMsgs[16];
    /* 0x058 */ OSMesgQueue cmdQ;
    /* 0x070 */ OSMesg cmdMsgs[16];
    /* 0x0B0 */ OSThread thread;
    /* 0x260 */ TaskNode *clientList;
    /* 0x264 */ TaskNode *audioListHead;
    /* 0x268 */ TaskNode *gfxListHead;
    /* 0x26C */ TaskNode *audioListTail;
    /* 0x270 */ TaskNode *gfxListTail;
    /* 0x274 */ TaskNode *curRSPTask;
    /* 0x278 */ TaskNode *curRDPTask;
    /* 0x27C */ u32 frameCount;
    /* 0x280 */ s32 unk280;
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

// Rumble-pak state struct (0x14 bytes each), array at D_807F0470
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 pad06[2];
    /* 0x08 */ u32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13;
} RumbleInfo;

// Player struct array (stride 0x2F0) pointed to by D_807FC924
typedef struct {
    u8 pad0[0x210];
    s32 unk210;
    s32 unk214;
    s32 unk218;
    u8 pad21C[0x270 - 0x21C];
    s16 rect[4];
    s16 unk278;
    s16 unk27A;
    u8 pad27C[4];
    f32 unk280;
    u8 pad284[0x2EB - 0x284];
    u8 unk2EB;
    u8 pad2EC[4];
} PlayerStruct;

typedef PlayerStruct RumblePlayer;

#endif

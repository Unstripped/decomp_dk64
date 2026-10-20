// The boot segment's osGetIntMask implementation takes the interrupt mask to set
// (asm/libultra/os/getintmask.s reads $a0), but ultralib's header prototypes it as
// osGetIntMask(void). Preempt that header and declare the 1-argument form the
// game's code calls.
#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;

#include "common.h"

// Scheduler task list node (an OSScTask-like entry)
typedef struct TaskNode {
    /* 0x00 */ struct TaskNode *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ OSTask unk10;
} TaskNode;

// Scheduler context
typedef struct SchedStruct {
    /* 0x000 */ u8 pad00[0x260];
    /* 0x260 */ TaskNode *unk260;
    /* 0x264 */ TaskNode *unk264;
    /* 0x268 */ TaskNode *unk268;
    /* 0x26C */ TaskNode *unk26C;
    /* 0x270 */ TaskNode *unk270;
    /* 0x274 */ TaskNode *unk274;
    /* 0x278 */ TaskNode *unk278;
    /* 0x27C */ u8 pad27C[0x14];
    /* 0x290 */ u64 unk290;
} SchedStruct; // 0x298

extern s32 osGetIntMask(s32 arg0);
extern void func_8060F928();
extern void func_8060F960(SchedStruct *, s32);
extern void func_8060FA5C(SchedStruct *);
extern u8 D_80746818;
extern u8 D_80746828;
extern u32 D_807F04F0;
extern u64 D_807F04F8;
extern u64 D_807F0508;
extern u64 D_807F04C0;
extern u64 D_807F04D0;

// Rumble-pak state struct (0x14 bytes each), array at D_807F0470
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 pad06[0x06];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13;
} RumbleInfo; // size 0x14

// Player struct array (stride 0x2F0) pointed to by D_807FC924
typedef struct {
    u8 pad00[0x2EB];
    u8 unk2EB;
    u8 padEC[0x04];
} RumblePlayer; // size 0x2F0

// Data symbols (defined in asm data/other files)
extern OSPfs D_807F02D0[4];
extern RumbleInfo D_807F0470[4];
extern u8 D_807F0474[];
extern u8 D_807ECD09;
extern s32 D_80746810;
extern u8 D_8076A0B1;
extern OSMesgQueue D_807ECCF0;
extern u32 D_807FBB60;
extern RumblePlayer *D_807FC924;
extern s32 func_8060AB38(s32);
extern void func_8060EC54(s32);

void func_8060E4B0(RumbleInfo *arg0) {
    bzero(arg0, 0x14);
}

void func_8060E4D0(u8 arg0) {
    RumbleInfo *sp18;

    if (__osMotorAccess(&D_807F02D0[arg0], 1) == 4) {
        sp18 = &D_807F0470[arg0];
        func_8060E4B0(sp18);
        sp18->unk00 = 3;
    } else {
        D_807F0474[arg0 * 0x14] = 1;
    }
}

void func_8060E574(u8 arg0) {
    s32 ret = osMotorInit(&D_807ECCF0, &D_807F02D0[arg0], arg0);

    switch (ret) {
    case 0:
        D_807F0470[arg0].unk00 = 1;
        break;
    case 1:
        D_807F0470[arg0].unk00 = 0;
        break;
    case 11:
        D_807F0470[arg0].unk00 = 2;
        break;
    case 4:
        D_807F0470[arg0].unk00 = 3;
        break;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060E664.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060E6E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060E79C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060E7EC.s")

void func_8060E8CC(RumbleInfo *arg0) {
    if (arg0->unk00 == 1) {
        arg0->unk05 = 0;
        arg0->unk0C = 0;
    }
}

void func_8060E8EC(u8 arg0) {
    func_8060E8CC(&D_807F0470[func_8060AB38(arg0)]);
}

void func_8060E930(void) {
    func_8060E6E8(1);
    func_8060EC54(1);
}

void func_8060E958(void) {
    func_8060E6E8(0);
    func_8060EC54(1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060E980.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060EA28.s")

void func_8060EC54(s32 arg0) {
    if (arg0 != D_80746810) {
        D_80746810 = arg0;
        D_80746818 = 1;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060EC80.s")

void func_8060ED6C(SchedStruct *arg0, TaskNode *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp14 = osGetIntMask(1);

    arg1->unk4 = arg2;
    arg1->unk0 = arg0->unk260;
    arg0->unk260 = arg1;
    arg1->unk8 = arg3;
    arg1->unkC = arg4;
    osGetIntMask(sp14);
}

void func_8060EDD0(SchedStruct *arg0, TaskNode *arg1) {
    TaskNode *sp1C = arg0->unk260;
    TaskNode *sp18 = NULL;
    s32 sp14 = osGetIntMask(1);

    while (sp1C != 0) {
        if (sp1C == arg1) {
            if (sp18 != 0) {
                sp18->unk0 = arg1->unk0;
            } else {
                arg0->unk260 = arg1->unk0;
            }
            break;
        }
        sp18 = sp1C;
        sp1C = sp1C->unk0;
    }
    osGetIntMask(sp14);
}

s32 func_8060EE58(SchedStruct *arg0) {
    return (s32)arg0 + 0x58;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060EE60.s")

void func_8060F1D0(SchedStruct *arg0) {
    func_8060F928(arg0);
    if (arg0->unk274 == 0) {
        func_8060F960(arg0, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F208.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F254.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F54C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F730.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F854.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F928.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F960.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060FA5C.s")

void func_8060FAA4(OSMesgQueue *arg0, OSMesg arg1, s32 arg2) {
    osGetTime();
    osGetTime();
    osSendMesg(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/D_80757184.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/D_80757188.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060FAE4.s")

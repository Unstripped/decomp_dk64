// The boot segment's osGetIntMask implementation takes the interrupt mask to set
// (asm/libultra/os/getintmask.s reads $a0), but ultralib's header prototypes it as
// osGetIntMask(void). Preempt that header and declare the 1-argument form the
// game's code calls.
#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;

#include "sched.h"

extern s32 osGetIntMask(s32 arg0);
extern s32 __osMotorAccess(OSPfs *, s32);
extern u64 __ull_div(u64, u64);

extern SchedConfig D_80746838;
extern s32 D_80746810;
extern u8 D_80746818;
extern s32 D_80746820;
extern s32 D_80746824;
extern u8 D_80746828;
extern u8 D_807444EC;
extern u8 D_8076A0B1;
extern u32 D_8076A064;
extern u8 D_807ECD09;
extern OSMesgQueue D_807ECCF0;
extern OSPfs D_807F02D0[4];
extern RumbleInfo D_807F0470[4];
extern u8 D_807F0474[];
extern u32 D_807F04E4;
extern TaskNode *D_807F04E0;
extern u64 D_807F04F8;
extern u64 D_807F0508;
extern u64 D_807F04C0;
extern u64 D_807F04D0;
extern s32 D_807F0564;
extern u32 D_807FBB60;
extern PlayerStruct *D_807FC924;

void rumbleInfoClear(RumbleInfo *);
void rumbleMotorStart(u8);
void rumbleMotorStop(u8);
void func_8060E6E8(s32);
s32 func_8060E79C(u8);
void func_8060E7EC(u8, u8, s32);
void func_8060E8CC(RumbleInfo *);
void func_8060E8EC(u8);
void func_8060E930(void);
void func_8060E958(void);
int func_8060E980(void);
void func_8060EA28(void);
void func_8060EC54(s32);
void schedCreate(SchedStruct *, void *, s32, u8, u8);
void schedAddClient(SchedStruct *, TaskNode *, s32, s32, s32);
void schedRemoveClient(SchedStruct *, TaskNode *);
void schedMain(void *);
void func_8060F1D0(SchedStruct *, TaskNode *);
void func_8060F208(SchedStruct *);
void schedHandleRetrace(SchedStruct *);
void schedHandleRSP(SchedStruct *);
void schedHandleRDP(SchedStruct *);
s32 schedTaskDone(SchedStruct *, TaskNode *);
void schedAppendTask(SchedStruct *, TaskNode *);
void schedStartTask(SchedStruct *, s32);
void schedYield(SchedStruct *);
void func_8060FAA4(OSMesgQueue *, OSMesg, s32);
s32 func_8060FAE4(s32, s32);

extern s32 func_8060AB38(s32);
extern u8 func_8060AC28(void);
extern u32 func_8062919C(void);
extern u32 func_8061CB50(void);
extern s32 func_8071432C(void);
extern s32 func_8071441C(void);
extern s32 func_807143E8(void);

void rumbleInfoClear(RumbleInfo *arg0) {
    bzero(arg0, 0x14);
}

void rumbleMotorStart(u8 arg0) {
    RumbleInfo *sp18;

    if (__osMotorAccess(&D_807F02D0[arg0], 1) == 4) {
        sp18 = &D_807F0470[arg0];
        rumbleInfoClear(sp18);
        sp18->unk00 = 3;
    } else {
        D_807F0474[arg0 * 0x14] = 1;
    }
}

void rumbleMotorInit(u8 arg0) {
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

void rumbleMotorStop(u8 arg0) {
    rumbleMotorInit(arg0);
    __osMotorAccess(&D_807F02D0[arg0], 0);
    __osMotorAccess(&D_807F02D0[arg0], 0);
    __osMotorAccess(&D_807F02D0[arg0], 0);
    D_807F0474[arg0 * 0x14] = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060E6E8.s")

s32 func_8060E79C(u8 arg0) {
    if (arg0 >= 4) {
        return 0;
    }
    return D_807F0470[func_8060AB38(arg0)].unk00;
}

void func_8060E7EC(u8 arg0, u8 arg1, s32 arg2) {
    RumbleInfo *info;

    info = &D_807F0470[func_8060AB38(arg0)];
    if (D_80746810 != 1 && info->unk00 == 1 && D_807FC924[arg0].unk2EB == 0) {
        if (func_8071432C() != 0 || func_8071441C() != 0) {
            if (info->unk12 != 0) {
                if (info->unk10 >= 0x1F) {
                    return;
                }
                info->unk12 = 0;
                info->unk10 = 0;
            }
            info->unk0C = arg2;
            info->unk05 = arg1;
        }
    }
}

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

int func_8060E980(void) {
    return ((D_807FBB60 & 0x4002) != 0) ||
           ((D_8076A0B1 & 1) != 0) ||
           (func_8062919C() != 0) ||
           (func_8061CB50() != 0) ||
           (func_8071432C() == 0 && func_8071441C() == 0 && func_807143E8() == 0);
}

void func_8060EA28(void) {
    RumbleInfo *info;
    s32 i;
    s32 pad_w;
    u8 pad;

    info = D_807F0470;
    if (D_80746810 == 1) {
        if (func_8060E980() == 0) {
            func_8060EC54(0);
        }
    } else {
        if (func_8060E980() != 0) {
            func_8060EC54(1);
        }
    }

    if (D_80746818 != 0) {
        func_8060E6E8(0);
    }
    D_80746818 = 0;

    if (D_80746810 != 1) {
        pad = func_8060AC28();
        for (i = 0; i < 4; i++, info++) {
            if (info->unk00 != 1) {
                if ((D_807ECD09 & (1 << i)) && (pad & (1 << i)) && (D_8076A064 % 15 == 0)) {
                    rumbleMotorStop(i);
                }
            } else {
                if (info->unk12 == 0) {
                    info->unk12 = info->unk10 >= 0x33;
                }
                if (info->unk0C == 0 && info->unk05 == 0) {
                    if (info->unk10 != 0) {
                        info->unk10--;
                    }
                }
                if (info->unk05 == 0) {
                    if (info->unk04 != 0) {
                        rumbleMotorStop(i);
                    }
                } else {
                    if (info->unk0C != 0) {
                        info->unk0C--;
                        info->unk10++;
                    }
                    if (info->unk0C == 0 || info->unk12 != 0) {
                        func_8060E8CC(info);
                    } else {
                        if (info->unk08 >= 0x100) {
                            if (info->unk04 == 0) {
                                rumbleMotorStart(i);
                            }
                            info->unk08 -= 0x100;
                        } else {
                            u8 val = info->unk05;
                            info->unk08 += val * 4;
                            if (info->unk04 != 0) {
                                rumbleMotorStop(i);
                            }
                        }
                    }
                }
            }
        }
    }
}

void func_8060EC54(s32 arg0) {
    if (arg0 != D_80746810) {
        D_80746810 = arg0;
        D_80746818 = 1;
    }
}

void schedCreate(SchedStruct *sc, void *stack, s32 priority, u8 arg3, u8 retraceCount) {
    SchedConfig sp2C;

    sp2C = D_80746838;
    sc->audioListTail = (TaskNode *)&sc->audioListHead;
    sc->gfxListTail = (TaskNode *)&sc->gfxListHead;
    D_807F04E0 = 0;
    osCreateMesgQueue(&sc->interruptQ, sc->intMsgs, 16);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgs, 16);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)0x29B);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)0x29C);
    osViSetEvent(&sc->interruptQ, (OSMesg)0x29A, retraceCount);
    osCreateThread(&sc->thread, 5, schedMain, sc, stack, priority);
    osStartThread(&sc->thread);
}

void schedAddClient(SchedStruct *arg0, TaskNode *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp14 = osGetIntMask(1);

    arg1->state = arg2;
    arg1->next = arg0->clientList;
    arg0->clientList = arg1;
    arg1->flags = arg3;
    arg1->framebuffer = (void *)arg4;
    osGetIntMask(sp14);
}

void schedRemoveClient(SchedStruct *arg0, TaskNode *arg1) {
    TaskNode *sp1C = arg0->clientList;
    TaskNode *sp18 = NULL;
    s32 sp14 = osGetIntMask(1);

    while (sp1C != 0) {
        if (sp1C == arg1) {
            if (sp18 != 0) {
                sp18->next = arg1->next;
            } else {
                arg0->clientList = arg1->next;
            }
            break;
        }
        sp18 = sp1C;
        sp1C = sp1C->next;
    }
    osGetIntMask(sp14);
}

s32 func_8060EE58(SchedStruct *arg0) {
    return (s32)arg0 + 0x58;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/schedMain.s")

void func_8060F1D0(SchedStruct *arg0, TaskNode *arg1) {
    schedAppendTask(arg0, arg1);
    if (arg0->curRSPTask == 0) {
        schedStartTask(arg0, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060F208.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/schedHandleRetrace.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/schedHandleRSP.s")

void schedHandleRDP(SchedStruct *sc) {
    TaskNode *task = sc->curRDPTask;
    s32 cond = 0;

    sc->curRDPTask = NULL;
    task->flags |= 8;

    if (D_807444EC == 3 || D_807444EC == 4) {
        cond = 1;
    }

    if (cond || D_80746820 != sc->unk284) {
        D_807F04E0 = NULL;
        if (D_8076A0B1 & 2) {
            D_8076A0B1 ^= 2;
            osViBlack(0);
        }
        osViSwapBuffer(task->framebuffer);
        D_80746824 = D_80746820;
        D_80746820 = sc->unk284 + 1;
        osDpSetStatus(8);
    } else {
        D_807F04E0 = task;
    }

    D_807F04E4 = __ull_div(osGetTime() - sc->unk288, 0x1E91);
    schedTaskDone(sc, task);
}

s32 schedTaskDone(SchedStruct *sc, TaskNode *task) {
    s32 state = task->flags & 3;
    s32 done = (task->flags >> 2) & 3;
    s32 type = task->task.t.type;
    s32 ret;

    if (!(task->flags & 0x40)) {
        state &= 1;
        done &= 1;
    }

    if (state == done) {
        if (type == 1) {
            sc->gfxListHead = sc->gfxListHead->next;
            if (sc->gfxListHead == NULL) {
                sc->gfxListTail = (TaskNode *)&sc->gfxListHead;
            }
        }
        if (task->msgQ != NULL) {
            if (D_807F04E0 == 0 || type != 1) {
                if (task->flags & 0x40) {
                    func_8060FAA4(task->msgQ, task->msg, 0);
                    ret = 1;
                    goto end;
                }
                osSendMesg(task->msgQ, task->msg, 0);
            }
        }
        ret = 1;
    } else {
        ret = 0;
    }

end:
    D_807F0564 = ret;
    return ret;
}

void schedAppendTask(SchedStruct *sc, TaskNode *task) {
    s32 state = 2;
    s32 type = task->task.t.type;

    if (type == state) {
        sc->audioListTail->next = task;
        sc->audioListTail = task;
    } else {
        sc->gfxListTail->next = task;
        sc->gfxListTail = task;
    }
    task->next = NULL;
    task->state = state;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/schedStartTask.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/schedYield.s")

void func_8060FAA4(OSMesgQueue *arg0, OSMesg arg1, s32 arg2) {
    osGetTime();
    osGetTime();
    osSendMesg(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/D_80757184.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/D_80757188.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/131B0/func_8060FAE4.s")

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
extern u64 __ull_div(u64, u64);

extern SchedConfig D_80746838;
extern s32 D_80746820;
extern s32 D_80746824;
extern u8 D_80746828;
extern u8 D_807444EC;
extern u8 D_8076A0B1;

void schedCreate(SchedStruct *, void *, s32, u8, u8);
void schedAddClient(SchedStruct *, TaskNode *, s32, s32, s32);
void schedRemoveClient(SchedStruct *, TaskNode *);
void schedMain(void *);
void schedHandleNewTask(SchedStruct *, TaskNode *);
void schedStartAudioOrYield(SchedStruct *);
void schedHandleRetrace(SchedStruct *);
void schedHandleRSP(SchedStruct *);
void schedHandleRDP(SchedStruct *);
s32 schedTaskDone(SchedStruct *, TaskNode *);
void schedAppendTask(SchedStruct *, TaskNode *);
void schedStartTask(SchedStruct *, s32);
void schedYield(SchedStruct *);
void func_8060FAA4(OSMesgQueue *, OSMesg, s32);
s32 schedDlDebugDump(s32, s32);

typedef struct {
    u16 button;
    u8 pad2[6];
} ContPadButtons;

// .bss 0x807F04C0-0x807F0570
u64 D_807F04C0;
u64 D_807F04C8;
u64 D_807F04D0;
u32 D_807F04D8;
u32 D_807F04DC;
TaskNode *D_807F04E0;
u32 D_807F04E4;
u32 D_807F04E8;
u32 D_807F04EC;
u32 D_807F04F0;
u32 D_807F04F4;
u64 D_807F04F8;
u64 D_807F0500;
u64 D_807F0508;
u64 D_807F0510;
u16 D_807F0518[20];
OSTimer D_807F0540;
u32 D_807F0560;
s32 D_807F0564;
ContPadButtons D_807F0568;

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

s32 schedGetCmdQueue(SchedStruct *arg0) {
    return (s32)arg0 + 0x58;
}

extern u8 D_807563B4;
extern s8 D_80746830;
extern s16 D_8074682C;
extern s8 D_80746844;
extern s8 D_80746848;
extern u32 D_8076154C;
extern u32 D_80744470[];
extern void faultFontInit(s32, s32, s32);
extern void faultPrintf(const char *, ...);


#pragma GLOBAL_ASM("asm/global/nonmatchings/13980/schedMain.s")

void schedHandleNewTask(SchedStruct *arg0, TaskNode *arg1) {
    schedAppendTask(arg0, arg1);
    if (arg0->curRSPTask == 0) {
        schedStartTask(arg0, 1);
    }
}

void schedStartAudioOrYield(SchedStruct *arg0) {
    if (arg0->curRSPTask != NULL) {
        schedYield(arg0);
    } else {
        D_807F04D0 = 0;
        schedStartTask(arg0, 0);
    }
}

extern s8 D_80744510;
extern s16 D_80746858;
extern u32 D_8074684C[];


void schedHandleRetrace(SchedStruct *sc) {
    TaskNode *sp54;
    s32 i;
    s32 s2;
    s32 n;
    TaskNode *client;
    TaskNode *fb;

    sc->unk284++;
    sc->unk280++;
    D_807F04F8 = osGetTime();
    if (D_80744510 != 0) {
        if (D_80744510 == 1) {
            if (D_80746858 == 0) {
                osViBlack(1);
                if (D_80744510 && D_80744510) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            if (D_80746858 == 0x3C) {
                osViSetMode(&osViModeTable[D_8074684C[osTvType]]);
                osViSetSpecialFeatures(0x42);
                osViBlack(0);
                D_80744510 = 2;
                if (D_80744470 && D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            D_80746858++;
        }
        osViSwapBuffer((void *)D_80744470[0]);
    }
    if (D_807F04E0 != NULL) {
        if (D_8076A0B1 & 2) {
            D_8076A0B1 ^= 2;
            osViBlack(0);
        }
        osViSwapBuffer(D_807F04E0->framebuffer);
        D_80746824 = D_80746820;
        D_80746820 = sc->unk284 + 1;
        osDpSetStatus(8);
        if (D_807F04E0->msgQ != NULL) {
            func_8060FAA4(D_807F04E0->msgQ, D_807F04E0->msg, 0);
        }
        D_807F04E0 = NULL;
    } else {
        fb = osViGetCurrentFramebuffer();
        if (osViGetNextFramebuffer() == (void *)fb) {
            if (osDpGetStatus() & 2) {
                sc->unk288 = osGetTime();
                osDpSetStatus(4);
            }
        }
    }
    n = sc->cmdQ.validCount;
    for (i = 0; i < n; i++) {
        osRecvMesg(&sc->cmdQ, (OSMesg *)&sp54, 0);
        if (sp54 == (TaskNode *)-1) {}  // FAKE: steers uopt (hoists -1 into s2)
        if ((u32)sc->unk284 % ((u32 *)sp54->unk50)[2] == 0) {
            schedAppendTask(sc, sp54);
        } else {
            osSendMesg(&sc->cmdQ, (OSMesg)sp54, 0);
            if (D_80746858 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if (sp54 == (TaskNode *)-1) {}  // FAKE: steers uopt (hoists -1 into s2)
    }
    if (sc->audioListHead != NULL) {
        if ((sc->unk284 & 1) == 0) {
            osSetTimer(&D_807F0540, 0x445C0, 0, ((OSMesgQueue **)sc->audioListHead->unk50)[1], (OSMesg)5);
        }
    }
    for (client = sc->clientList; client != NULL; client = client->next) {
        if ((s32)client->framebuffer == 3) {
            osSendMesg((OSMesgQueue *)client->state, (OSMesg)0x29A, 0);
        }
    }
}

void schedHandleRSP(SchedStruct *sc) {
    TaskNode *task = sc->curRSPTask;

    sc->curRSPTask = NULL;
    if (task->state == 3) {
        D_807F04D0 = osGetTime() - D_807F04C0;
        if (D_807F04C8 < D_807F04D0) {
            D_807F04C8 = D_807F04D0;
        }
        if (osSpTaskYielded(&task->task) == 0) {
            task->state = 2;
            task->flags |= 4;
            schedTaskDone(sc, task);
        }
        schedStartTask(sc, 0);
    } else {
        if (task->flags & 0x40) {
            D_807F04E8 = __ull_div(osGetTime() - sc->unk290, 0x1E91);
            D_80746828 = 1;
        } else if (task->task.t.type == 2) {
            D_807F0510 = osGetTime();
            D_807F0500 = D_807F0508;
        }
        task->state = 2;
        task->flags |= 4;
        if (schedTaskDone(sc, task) != 0) {
            if (sc->gfxListHead != NULL && sc->gfxListHead->flags != 0x47) {
                schedStartTask(sc, 1);
            }
        }
    }
}

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

void schedStartTask(SchedStruct *arg0, s32 arg1) {
    TaskNode *task;
    TaskNode *head;

    if (arg1 == 0) {
        head = arg0->audioListHead;
        task = head;
        if (head == NULL) {
            return;
        }
        arg0->audioListHead = task->next;
        if (arg0->audioListHead == NULL) {
            arg0->audioListTail = (TaskNode *)&arg0->audioListHead;
        }
        D_807F0508 = osGetTime();
    } else {
        task = arg0->gfxListHead;
        if (D_80746828 != 0) {
            arg0->unk290 = osGetTime();
            D_807F04F0 = __ull_div(osGetTime() - D_807F04F8, 0x1E91);
            D_80746828 = 0;
        }
    }
    task->state = 1;
    osSpTaskLoad(&task->task);
    osSpTaskStartGo(&task->task);
    arg0->curRSPTask = task;
    if (task->flags & 0x40) {
        arg0->curRDPTask = task;
    }
}

void schedYield(SchedStruct *arg0) {
    TaskNode *task = arg0->curRSPTask;

    if (task->task.t.type == 1) {
        task->state = 3;
        D_807F04C0 = osGetTime();
        osSpTaskYield();
    }
}

void func_8060FAA4(OSMesgQueue *arg0, OSMesg arg1, s32 arg2) {
    osGetTime();
    osGetTime();
    osSendMesg(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/13980/D_80757184.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13980/D_80757188.s")

typedef struct {
    u8 op;
    char name[13];
    u8 size;
    u8 warn;
} DlOpInfo;

extern DlOpInfo D_8074685C[];
extern s8 D_80746A2C;
extern s16 D_80746A1C;
extern u32 D_80746A18;
extern u32 D_80746A20;
extern s32 D_80746A24;
extern s32 D_80746A28;
extern s32 D_80746A14;
extern char *D_80746A0C[];
extern u32 D_807F05A4;
extern u32 D_807F0984;
extern u32 D_80744478;
extern void faultFontSetColorMode(s32);
extern void controllerStartRead(void);


#pragma GLOBAL_ASM("asm/global/nonmatchings/13980/schedDlDebugDump.s")

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

// 13980's .data (0x80746820-0x80746A30), declaration order = address order
s32 D_80746820 = 2;
s32 D_80746824 = 1;
u8 D_80746828 = 1;
s16 D_8074682C = 0x3E8;
s8 D_80746830 = 1;
s8 D_80746834 = 0;
SchedConfig D_80746838 = { 0xF, 0, 0x1C };
s8 D_80746844 = 1;
s8 D_80746848 = 0;
u32 D_8074684C[3] = { 0xF, 2, 0x1E };
s16 D_80746858 = 0;

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
void schedSendMesgTimed(OSMesgQueue *, OSMesg, s32);
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


void schedMain(void *arg0) {
    u32 msg;
    s32 i;
    s32 flag;
    s32 pad1;
    s32 fbIdx;
    u32 cnt;
    s32 pad3;

    for (;;) {
        osRecvMesg(arg0, (OSMesg *)&msg, OS_MESG_BLOCK);
        if (D_807563B4 != 0) {
            if (D_80746830 == 0) {
                D_8074682C--;
            }
            if (D_8074682C <= 0) {
                D_807F0518[0]++;
                fbIdx = D_807F0518[0];
                osViSwapBuffer((void *)D_80744470[(fbIdx >> 5) & 1]);
                osViBlack(0);
                D_807F0518[0]++;
                if (D_8074682C < -0x9F && D_8074682C >= -0x100) {
                    for (i = 0; i < 2; i++) {
                        faultFontInit(D_80744470[i & 1], 2, 2);
                        faultPrintf("CURRENT=%x\n", IO_READ(DPC_CURRENT_REG));
                        faultPrintf("START=%x\n", IO_READ(DPC_START_REG));
                        faultPrintf("END=%x\n", IO_READ(DPC_END_REG));
                        faultPrintf("DPSTAT=%x\n", IO_READ(DPC_STATUS_REG));
                        faultPrintf("SPSTAT=%x\n", IO_READ(SP_STATUS_REG));
                        faultPrintf("MAIN-PC=%x\n", D_8076154C);
                    }
                }
                if (D_8074682C < -0x12B) {
                    flag = 0;
                    if ((D_807F0518[0] & 0x1F) == 0) {
                        flag = 1;
                    }
                    if (flag) {
                        if (D_80746848 == 0) {
                            flag = 0;
                            D_80746848 = 1;
                        }
                    }
                    schedDlDebugDump(D_80746844, flag);
                    D_80746844 = 0;
                    D_8074682C = -0x12C;
                }
                osWritebackDCacheAll();
            }
            if (D_807F0560 == 0) {}  // FAKE: keeps D_807F0560 un-pointerized (separate lui per access)
        }
        switch (msg) {
        case 0x29A:
            cnt = D_807F0560 + 1;
            D_807F0560 = cnt;
            if (cnt % 0x1E0 == 0) {
                D_807F04C8 = D_807F04D0;
                D_807F04D8 = D_807F04DC;
            }
            schedHandleRetrace(arg0);
            break;
        case 0x29E:
            schedStartAudioOrYield(arg0);
            break;
        case 0x29B:
            schedHandleRSP(arg0);
            break;
        case 0x29C:
            schedHandleRDP(arg0);
            break;
        case 0x29F:
            if (osSendMesg(D_807F0540.mq, D_807F0540.msg, OS_MESG_BLOCK) == -1) {
            }
            break;
        case 0x2A0:
        case 0x3F2:
            break;
        default:
            schedHandleNewTask(arg0, (TaskNode *)msg);
            break;
        }
    }
}

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
            schedSendMesgTimed(D_807F04E0->msgQ, D_807F04E0->msg, 0);
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
                    schedSendMesgTimed(task->msgQ, task->msg, 0);
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

void schedSendMesgTimed(OSMesgQueue *arg0, OSMesg arg1, s32 arg2) {
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

DlOpInfo D_8074685C[27] = {
    { 0xFF, "SETCIMG", 8, 0 },
    { 0xFE, "SETZIMG", 8, 0 },
    { 0xFD, "SETTIMG", 8, 0 },
    { 0xFC, "SETCMBMODE", 8, 0 },
    { 0xFB, "SETENVCOL", 8, 0 },
    { 0xFA, "SETPRIMCOL", 8, 0 },
    { 0xF9, "SETBLENDCOL", 8, 0 },
    { 0xF8, "SETFOGCOL", 8, 0 },
    { 0xF7, "SETFILLCOL", 8, 0 },
    { 0xF6, "FILLRECT", 8, 1 },
    { 0xF5, "SETTILE ", 8, 0 },
    { 0xF4, "LOADTILE", 8, 1 },
    { 0xF3, "LOADBLK ", 8, 1 },
    { 0xF2, "SETTILESZ", 8, 0 },
    { 0xF0, "LOADTLUT", 8, 0 },
    { 0xEF, "SETOTHRMODE", 8, 0 },
    { 0xEE, "SETPRMDP", 8, 0 },
    { 0xED, "SETSCSR", 8, 0 },
    { 0xEC, "SETCONV", 8, 0 },
    { 0xEB, "SETKEYR", 8, 0 },
    { 0xEA, "SETKEYGB", 8, 0 },
    { 0xE9, "FULLSYNC", 8, 0 },
    { 0xE8, "TILESYNC", 8, 0 },
    { 0xE7, "PIPESYNC", 8, 0 },
    { 0xE6, "LOADSYNC", 8, 0 },
    { 0xE5, "RECTFLIP", 16, 1 },
    { 0xE4, "TEXRECT", 16, 1 },
};
extern char D_80757184[];
extern char D_80757188[];
char *D_80746A0C[2] = { D_80757184, D_80757188 };
extern u32 D_807F05A4;
extern u32 D_807F0984;
extern u32 D_80744478;
extern void faultFontSetColorMode(s32);
extern void controllerStartRead(void);


s32 schedDlDebugDump(s32 arg0, s32 arg1) {
    static s32 D_80746A14 = 0;
    static u32 D_80746A18 = 0;
    static s16 D_80746A1C = 0;
    static u32 D_80746A20 = 0;
    static s32 D_80746A24 = 0;
    static s32 D_80746A28 = 0;
    static s8 D_80746A2C = 4;
    u32 p;
    s32 size;
    char *q;
    u16 colorIdx;
    u8 op;
    s16 buttons;
    s32 off;
    u32 n;
    s16 found;
    s32 line;
    s32 cur;
    s32 mode;
    u32 done;
    char buf[36];
    s32 i;
    s32 raw;
    u32 ret;

    done = 0;
    ret = 0;
    if (arg0 == 0) {
        osContGetReadData((OSContPad *)((u8 *)&D_807F0564 + 4));  // FAKE: arg spelled off D_807F0564 so uopt does not CSE lda D_807F0568 with the .button read
        raw = D_807F0568.button;
        buttons = raw;
        if (arg1 != 0 && D_80746A2C != 0) {
            buttons |= 0x400;
        }
        if (buttons & 0x1000) {
            if (!(D_80746A1C & 0x1000)) {
                if (D_80746A2C > 0) {
                    D_80746A2C -= 1;
                }
            }
        }
        if (buttons & 0x400) {
            if (!(D_80746A1C & 0x400)) {
                if (D_80746A18 != 0) {
                    D_80746A24 = D_80746A28;
                    D_80746A20 = D_80746A18;
                }
            }
        }
        if (buttons & 0x800) {
            if (!(D_80746A1C & 0x800)) {
                if (D_807F05A4 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_80746A24 = 0;
                D_80746A20 = D_807F05A4;
            }
        }
        if (buttons & 0x10) {
            if (!(D_80746A1C & 0x10)) {
                ret = 1;
            }
        }
        D_80746A1C = buttons;
    } else {
        D_80746A24 = 0;
        D_80746A14 = D_807F05A4;
        D_80746A20 = D_807F05A4;
        D_80746A1C = 0;
        D_80746A18 = 0;
    }
    p = 0;
    do {
        faultFontInit(D_80744470[p], 0, 1);
        line = 0;
        mode = D_80746A24;
        cur = *(u32 *)&D_80746A20;
        if (*(u32 *)&D_80746A20) {}  // FAKE: second ilod of D_80746A20 makes uopt keep the load in a CSE temp ($v0), so as1 expands it via lui $v0 and moves it to s5
        while (done == 0 && line < 0xF) {
            off = cur - D_807F05A4;
            if (line < 0xE) {
                D_80746A28 = mode;
                D_80746A18 = cur;
            }
            op = (*(u32 *)cur >> 24) & 0xFFFF;  // FAKE: burns one ugen ring slot before opcode/extent temporaries
            if (D_807F05A4 + D_807F0984 < cur) {
                done = 1;
            }
            if ((op & 0xF0) == 0xC0) {
                n = 0;
                size = 0x20;
                mode = 2;
                if (op & 4) {
                    buf[0] = 'S';
                    size = 0x60;
                    n = 1;
                }
                if (op & 2) {
                    buf[n] = 'T';
                    n++;
                    size += 0x40;
                }
                if (op & 1) {
                    buf[n] = 'Z';
                    size += 0x10;
                    n++;
                }
                buf[n] = 0;
                size >>= 2;
                faultPrintf("  %05x.:Triangle:.(%s)....\n", off, buf);
                line++;
                if (line == 1) {
                    for (i = 0; i < size; i += 4) {
                        faultPrintf("  %08x.%08x.%08x.%08x\n", ((u32 *)cur)[i], ((u32 *)cur)[i + 1], ((u32 *)cur)[i + 2], ((u32 *)cur)[i + 3]);
                        line++;
                    }
                    D_80746A18 = cur + size * 4;
                } else {
                    D_80746A18 = cur;
                }
                while (line < 0xF) {
                    faultPrintf("  ----------------------------------\n");
                    line++;
                }
                line = 0x1E;
            } else {
                if (D_80746A20 && D_80746A20) {}  // FAKE: dead read at the opcode branch start steers uopt candidate order (i = 0 is scheduled first)
                colorIdx = 0;
                found = 0;
                if (op == 0xE7) {
                    mode = 0;
                }
                if (op == 0xF6) {
                    mode = 0;
                }
                if (mode != 0) {
                    faultFontSetColorMode(1);
                    colorIdx = 1;
                    mode = 0;
                }
                for (i = 0; i < 0x1B; i++) {
                    if (op == D_8074685C[i].op) {
                        op = i;
                        found = 1;
                        i = 0x1B;
                    }
                }
                if (D_8074685C[op].warn != 0) {
                    mode = 1;
                }
                if (found) {
                    size = D_8074685C[op].size >> 2;
                    faultPrintf("  %05x.:.%s...%s.\n", off, D_8074685C[op].name, D_80746A0C[colorIdx]);
                    line++;
                    if (size <= 2) {
                        faultPrintf("  %08x..%08x............\n", ((u32 *)cur)[0], ((u32 *)cur)[1]);
                        line++;
                    } else {
                        faultPrintf("  %08x.%08x.%08x.%08x...\n", ((u32 *)cur)[0], ((u32 *)cur)[1], ((u32 *)cur)[2], ((u32 *)cur)[3]);
                        line += 2;
                    }
                } else {
                    size = 2;
                    if (op == 0) {
                        faultPrintf(" %05x  NOOP..........\n", off);
                    } else {
                        faultPrintf("  %05x Undef.............\n", off);
                    }
                    line++;
                }
            }
            faultFontSetColorMode(0);
            cur += size * 4U;
        }
        p += 1;
    } while (&D_80744478 != &D_80744470[p]);
    controllerStartRead();
    return ret;
}

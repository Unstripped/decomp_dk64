// The boot segment's osGetIntMask implementation takes the interrupt mask to set
// (asm/libultra/os/getintmask.s reads $a0), but ultralib's header prototypes it as
// osGetIntMask(void). Preempt that header and declare the 1-argument form the
// game's code calls.
#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;

#include "sched.h"
#include "proto/global/13980.h"
#include "proto/global/136820.h"
#include "proto/global/F600.h"

extern s32 osGetIntMask(s32 arg0);

// 13980's .data (0x80746820-0x80746A30), definition order = address order: function-local
// statics take their function's place (schedMain's sFirstAdvanceSkipped is 0x80746848)
s32 gSchedSwapRetrace = 2;
s32 gSchedPrevSwapRetrace = 1;
u8 D_80746828 = 1;
s16 D_8074682C = 1000;
s8 D_80746830 = 1;
s8 D_80746834 = 0;
SchedConfig D_80746838 = { 0xF, 0, 0x1C };
s8 D_80746844 = 1;

extern u8 gGameMode;
extern u8 gScreenRenderFlags;

// .bss 0x807F04C0-0x807F0570; 0x807F0560-0x807F0570 holds the function-local statics of
// schedMain, schedTaskDone and schedDlDebugDump, in that order
u64 D_807F04C0;
u64 D_807F04C8;
u64 D_807F04D0;
u32 D_807F04D8;
u32 D_807F04DC;
TaskNode *gSchedPendingSwapTask;
u32 D_807F04E4;
u32 D_807F04E8;
u32 D_807F04EC;
u32 D_807F04F0;
u32 D_807F04F4;
u64 gSchedRetraceTime;
u64 D_807F0500;
u64 D_807F0508;
u64 D_807F0510;
u16 D_807F0518[20];
OSTimer gSchedAudioTimer;

void schedCreate(SchedStruct *sc, void *stack, s32 priority, u8 viMode, u8 retraceCount) {
    SchedConfig config;

    config = D_80746838;
    sc->audioListTail = (TaskNode *)&sc->audioListHead;
    sc->gfxListTail = (TaskNode *)&sc->gfxListHead;
    gSchedPendingSwapTask = NULL;
    osCreateMesgQueue(&sc->interruptQ, sc->intMsgs, 16);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgs, 16);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)0x29B);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)0x29C);
    osViSetEvent(&sc->interruptQ, (OSMesg)0x29A, retraceCount);
    osCreateThread(&sc->thread, 5, schedMain, sc, stack, priority);
    osStartThread(&sc->thread);
}

void schedAddClient(SchedStruct *sc, SchedClient *client, OSMesgQueue *msgQ, s32 id, s32 kind) {
    s32 mask = osGetIntMask(1);

    client->msgQ = msgQ;
    client->next = sc->clientList;
    sc->clientList = client;
    client->id = id;
    client->kind = kind;
    osGetIntMask(mask);
}

void schedRemoveClient(SchedStruct *sc, SchedClient *client) {
    SchedClient *cur = sc->clientList;
    SchedClient *prev = NULL;
    s32 mask = osGetIntMask(1);

    while (cur != NULL) {
        if (cur == client) {
            if (prev != NULL) {
                prev->next = client->next;
            } else {
                sc->clientList = client->next;
            }
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    osGetIntMask(mask);
}

OSMesgQueue *schedGetCmdQueue(SchedStruct *sc) {
    return &sc->cmdQ;
}

extern u8 gFaultScreenEnabled;
extern u32 D_8076154C;
extern u32 gFramebuffers[];


void schedMain(void *arg) {
    static s8 sFirstAdvanceSkipped = 0;
    static u32 sRetraceCount;
    OSMesg msg;
    s32 i;
    s32 flag;
    SchedStruct *sc = arg;
    s32 fbIdx;
    s32 pad[2];

    for (;;) {
        osRecvMesg(&sc->interruptQ, &msg, OS_MESG_BLOCK);
        if (gFaultScreenEnabled != 0) {
            if (D_80746830 == 0) {
                D_8074682C--;
            }
            if (D_8074682C <= 0) {
                fbIdx = ++D_807F0518[0];
                osViSwapBuffer((void *)gFramebuffers[(fbIdx >> 5) & 1]);
                osViBlack(0);
                D_807F0518[0]++;
                if (D_8074682C < -159 && D_8074682C >= -256) {
                    for (i = 0; i < 2; i++) {
                        faultFontInit(gFramebuffers[i & 1], 2, 2);
                        faultPrintf("CURRENT=%x\n", IO_READ(DPC_CURRENT_REG));
                        faultPrintf("START=%x\n", IO_READ(DPC_START_REG));
                        faultPrintf("END=%x\n", IO_READ(DPC_END_REG));
                        faultPrintf("DPSTAT=%x\n", IO_READ(DPC_STATUS_REG));
                        faultPrintf("SPSTAT=%x\n", IO_READ(SP_STATUS_REG));
                        faultPrintf("MAIN-PC=%x\n", D_8076154C);
                    }
                }
                if (D_8074682C < -299) {
                    flag = 0;
                    if ((D_807F0518[0] & 0x1F) == 0) {
                        flag = 1;
                    }
                    if (flag && sFirstAdvanceSkipped == 0) {
                        flag = 0;
                        sFirstAdvanceSkipped = 1;
                    }
                    schedDlDebugDump(D_80746844, flag);
                    D_80746844 = 0;
                    D_8074682C = -300;
                }
                osWritebackDCacheAll();
            }
        }
        switch ((u32)msg) {
        case 0x29A:
            if (++sRetraceCount % 480 == 0) {
                D_807F04C8 = D_807F04D0;
                D_807F04D8 = D_807F04DC;
            }
            schedHandleRetrace(sc);
            break;
        case 0x29E:
            schedStartAudioOrYield(sc);
            break;
        case 0x29B:
            schedHandleRSP(sc);
            break;
        case 0x29C:
            schedHandleRDP(sc);
            break;
        case 0x29F:
            if (osSendMesg(gSchedAudioTimer.mq, gSchedAudioTimer.msg, OS_MESG_BLOCK) == -1) {  // ORIG: target compares the result at 0x4f0/0x4f4 (li at,-1; bnel v0,at), both arms rejoin the loop head
            }
            break;
        case 0x2A0:
        case 0x3F2:
            break;
        default:
            schedHandleNewTask(sc, msg);
            break;
        }
    }
}

u32 sViModeIndexByTvType[3] = { OS_VI_PAL_LPF1, OS_VI_NTSC_LAN1, OS_VI_MPAL_LAN1 };

void schedHandleNewTask(SchedStruct *sc, TaskNode *task) {
    schedAppendTask(sc, task);
    if (sc->curRSPTask == NULL) {
        schedStartTask(sc, 1);
    }
}

void schedStartAudioOrYield(SchedStruct *sc) {
    if (sc->curRSPTask != NULL) {
        schedYield(sc);
    } else {
        D_807F04D0 = 0;
        schedStartTask(sc, 0);
    }
}

extern s8 D_80744510; // ORIG: this TU reads it signed (lb a0,0(s0) at 0x620 for the != 0 / == 1 tests); 450.c defines it u8


void schedHandleRetrace(SchedStruct *sc) {
    static s16 sViModeDelay = 0;
    OSMesg msg;
    s32 i;
    s32 pad;
    s32 n;
    SchedClient *client;
    void *fb;

    sc->retraceCount++;
    sc->unk280++;
    gSchedRetraceTime = osGetTime();
    if (D_80744510 != 0) {
        if (D_80744510 == 1) {
            if (sViModeDelay == 0) {
                osViBlack(1);
            }
            if (sViModeDelay == 60) {
                osViSetMode(&osViModeTable[sViModeIndexByTvType[osTvType]]);
                osViSetSpecialFeatures(OS_VI_GAMMA_OFF | OS_VI_DITHER_FILTER_ON);
                osViBlack(0);
                D_80744510 = 2;
            }
            sViModeDelay++;
        }
        osViSwapBuffer((void *)gFramebuffers[0]);
    }
    if (gSchedPendingSwapTask != NULL) {
        if (gScreenRenderFlags & 2) {
            gScreenRenderFlags ^= 2;
            osViBlack(0);
        }
        osViSwapBuffer(gSchedPendingSwapTask->framebuffer);
        gSchedPrevSwapRetrace = gSchedSwapRetrace;
        gSchedSwapRetrace = sc->retraceCount + 1;
        osDpSetStatus(DPC_SET_FREEZE);
        if (gSchedPendingSwapTask->msgQ != NULL) {
            schedSendMesgTimed(gSchedPendingSwapTask->msgQ, gSchedPendingSwapTask->msg, OS_MESG_NOBLOCK);
        }
        gSchedPendingSwapTask = NULL;
    } else {
        fb = osViGetCurrentFramebuffer();
        if (osViGetNextFramebuffer() == fb) {
            if (osDpGetStatus() & DPC_STATUS_FREEZE) {
                sc->unk288 = osGetTime();
                osDpSetStatus(DPC_CLR_FREEZE);
            }
        }
    }
    n = sc->cmdQ.validCount;
    for (i = 0; i < n; i++) {
        osRecvMesg(&sc->cmdQ, &msg, OS_MESG_NOBLOCK);
        if (msg == (OSMesg)-1) {}  // FAKE: steers uopt (hoists -1 into s2)
        if ((u32)sc->retraceCount % ((TaskNode *)msg)->client->id == 0) {
            schedAppendTask(sc, msg);
        } else {
            osSendMesg(&sc->cmdQ, msg, OS_MESG_NOBLOCK);
        }
        if (msg == (OSMesg)-1) {}  // FAKE: steers uopt (hoists -1 into s2)
    }
    if (sc->audioListHead != NULL) {
        if ((sc->retraceCount & 1) == 0) {
            osSetTimer(&gSchedAudioTimer, 0x445C0, 0, sc->audioListHead->client->msgQ, (OSMesg)5);
        }
    }
    for (client = sc->clientList; client != NULL; client = client->next) {
        if (client->kind == 3) {
            osSendMesg(client->msgQ, (OSMesg)0x29A, OS_MESG_NOBLOCK);
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
            D_807F04E8 = (osGetTime() - sc->unk290) / 0x1E91;
            D_80746828 = 1;
        } else if (task->task.t.type == M_AUDTASK) {
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

    if (gGameMode == 3 || gGameMode == 4) {
        cond = 1;
    }

    if (cond || gSchedSwapRetrace != sc->retraceCount) {
        gSchedPendingSwapTask = NULL;
        if (gScreenRenderFlags & 2) {
            gScreenRenderFlags ^= 2;
            osViBlack(0);
        }
        osViSwapBuffer(task->framebuffer);
        gSchedPrevSwapRetrace = gSchedSwapRetrace;
        gSchedSwapRetrace = sc->retraceCount + 1;
        osDpSetStatus(DPC_SET_FREEZE);
    } else {
        gSchedPendingSwapTask = task;
    }

    D_807F04E4 = (osGetTime() - sc->unk288) / 0x1E91;
    schedTaskDone(sc, task);
}

s32 schedTaskDone(SchedStruct *sc, TaskNode *task) {
    static s32 sTaskDone;
    s32 state = task->flags & 3;
    s32 done = (task->flags >> 2) & 3;
    s32 type = task->task.t.type;
    s32 ret;

    if (!(task->flags & 0x40)) {
        state &= 1;
        done &= 1;
    }

    if (state == done) {
        if (type == M_GFXTASK) {
            sc->gfxListHead = sc->gfxListHead->next;
            if (sc->gfxListHead == NULL) {
                sc->gfxListTail = (TaskNode *)&sc->gfxListHead;
            }
        }
        if (task->msgQ != NULL) {
            if (gSchedPendingSwapTask == NULL || type != M_GFXTASK) {
                if (task->flags & 0x40) {
                    schedSendMesgTimed(task->msgQ, task->msg, OS_MESG_NOBLOCK);
                } else {
                    osSendMesg(task->msgQ, task->msg, OS_MESG_NOBLOCK);
                }
            }
        }
        ret = 1;
    } else {
        ret = 0;
    }

    sTaskDone = ret;
    return ret;
}

void schedAppendTask(SchedStruct *sc, TaskNode *task) {
    s32 type = task->task.t.type;

    if (type == M_AUDTASK) {
        sc->audioListTail->next = task;
        sc->audioListTail = task;
    } else {
        sc->gfxListTail->next = task;
        sc->gfxListTail = task;
    }
    task->next = NULL;
    task->state = 2;
}

void schedStartTask(SchedStruct *sc, s32 isGfx) {
    TaskNode *task;

    if (isGfx == 0) {
        task = sc->audioListHead;
        if (task == NULL) {
            return;
        }
        sc->audioListHead = sc->audioListHead->next; // FAKE: re-read of audioListHead (one load at 0xcf8) instead of task->next keeps the popped head in v0 (task->next moves task to s0)
        if (sc->audioListHead == NULL) {
            sc->audioListTail = (TaskNode *)&sc->audioListHead;
        }
        D_807F0508 = osGetTime();
    } else {
        task = sc->gfxListHead;
        if (D_80746828 != 0) {
            sc->unk290 = osGetTime();
            D_807F04F0 = (osGetTime() - gSchedRetraceTime) / 0x1E91;
            D_80746828 = 0;
        }
    }
    task->state = 1;
    osSpTaskLoad(&task->task);
    osSpTaskStartGo(&task->task);
    sc->curRSPTask = task;
    if (task->flags & 0x40) {
        sc->curRDPTask = task;
    }
}

void schedYield(SchedStruct *sc) {
    TaskNode *task = sc->curRSPTask;

    if (task->task.t.type == M_GFXTASK) {
        task->state = 3;
        D_807F04C0 = osGetTime();
        osSpTaskYield();
    }
}

void schedSendMesgTimed(OSMesgQueue *mq, OSMesg msg, s32 flags) {
    osGetTime();
    osGetTime();
    osSendMesg(mq, msg, flags);
}

const char D_80757184[4] = "";
const char D_80757188[12] = "WARNING!!";

typedef struct {
    u8 op;
    char name[13];
    u8 size;
    u8 warn;
} DlOpInfo;

DlOpInfo sDlOpInfo[27] = {
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
const char *sDlDumpWarnLabels[2] = { D_80757184, D_80757188 };


s32 schedDlDebugDump(s32 reset, s32 autoAdvance) {
    static OSContPad sContPad;
    static u32 *sDumpBase = NULL;
    static u32 *sNextPageAddr = NULL;
    static s16 sPrevButtons = 0;
    static u32 *sPageAddr = NULL;
    static s32 sPageMode = 0;
    static s32 sNextPageMode = 0;
    static s8 sAutoPageCount = 4;
    u32 p;
    s32 size;
    s32 pad;
    u16 colorIdx;
    u8 op;
    s16 buttons;
    s32 off;
    u32 n;
    s16 found;
    s32 line;
    u32 *cur;
    s32 mode;
    u32 done;
    char buf[36];
    s32 i;
    s32 pad2;
    s32 ret;

    done = 0;
    ret = 0;
    if (reset == 0) {
        osContGetReadData(&sContPad);
        buttons = sContPad.button;
        if (autoAdvance != 0 && sAutoPageCount != 0) {
            buttons |= D_JPAD;
        }
        if ((buttons & START_BUTTON) && !(sPrevButtons & START_BUTTON) && sAutoPageCount > 0) {
            sAutoPageCount--;
        }
        if ((buttons & D_JPAD) && !(sPrevButtons & D_JPAD) && sNextPageAddr != NULL) {
            sPageMode = sNextPageMode;
            sPageAddr = sNextPageAddr;
        }
        if ((buttons & U_JPAD) && !(sPrevButtons & U_JPAD)) {
            sPageAddr = (u32 *)gRdpOutputBuffer;
            sPageMode = 0;
        }
        if ((buttons & R_TRIG) && !(sPrevButtons & R_TRIG)) {
            ret = 1;
        }
        sPrevButtons = buttons;
    } else {
        sPageMode = 0;
        sPageAddr = (u32 *)gRdpOutputBuffer;
        sDumpBase = sPageAddr;
        sPrevButtons = 0;
        sNextPageAddr = NULL;
    }
    for (p = 0; p < 2; p++) {
        faultFontInit(gFramebuffers[p], 0, 1);
        line = 0;
        mode = sPageMode;
        cur = sPageAddr;
        while (done == 0 && line < 15) {
            off = (u8 *)cur - gRdpOutputBuffer;
            if (line < 14) {
                sNextPageMode = mode;
                sNextPageAddr = cur;
            }
            op = (*cur >> 24) & 0xFF;
            if (gRdpOutputBuffer + gRdpOutputBufferSize < (u8 *)cur) {
                done = 1;
            }
            if ((op & 0xF0) == 0xC0) {
                n = 0;
                size = 32;
                mode = 2;
                if (op & 4) {
                    buf[0] = 'S';
                    size = 96;
                    n = 1;
                }
                if (op & 2) {
                    buf[n] = 'T';
                    n++;
                    size += 64;
                }
                if (op & 1) {
                    buf[n] = 'Z';
                    size += 16;
                    n++;
                }
                buf[n] = '\0';
                size >>= 2;
                faultPrintf("  %05x.:Triangle:.(%s)....\n", off, buf);
                line++;
                if (line == 1) {
                    for (i = 0; i < size; i += 4) {
                        faultPrintf("  %08x.%08x.%08x.%08x\n", cur[i], cur[i + 1], cur[i + 2], cur[i + 3]);
                        line++;
                    }
                    sNextPageAddr = cur + size;
                } else {
                    sNextPageAddr = cur;
                }
                while (line < 15) {
                    faultPrintf("  ----------------------------------\n");
                    line++;
                }
                line = 30;
            } else {
                if (op == G_RDPPIPESYNC) {
                    mode = 0;
                }
                if (op == G_FILLRECT) {
                    mode = 0;
                }
                colorIdx = 0;
                if (mode != 0) {
                    faultFontSetColorMode(1);
                    colorIdx = 1;
                    mode = 0;
                }
                found = 0;
                for (i = 0; i < 27; i++) {
                    if (op == sDlOpInfo[i].op) {
                        op = i;
                        found = 1;
                        i = 27;
                    }
                }
                if (sDlOpInfo[op].warn != 0) {
                    mode = 1;
                }
                if (found) {
                    size = sDlOpInfo[op].size >> 2;
                    faultPrintf("  %05x.:.%s...%s.\n", off, sDlOpInfo[op].name, sDlDumpWarnLabels[colorIdx]);
                    line++;
                    if (size <= 2) {
                        faultPrintf("  %08x..%08x............\n", cur[0], cur[1]);
                        line++;
                    } else {
                        faultPrintf("  %08x.%08x.%08x.%08x...\n", cur[0], cur[1], cur[2], cur[3]);
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
            cur += size;
        }
    }
    controllerStartRead();
    return ret;
}

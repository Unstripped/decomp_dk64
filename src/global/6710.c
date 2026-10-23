#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/6710/func_80601A10.s")

extern s8 D_807452CC;
extern OSThread D_8076D4E8;

void func_80601CC0(void) {
    D_807452CC = 1;
    osStartThread(&D_8076D4E8);
}

void func_80601CF0(s32 arg0) {
    if (D_807452CC != 0) {
        osStopThread(&D_8076D4E8);
    }
}

typedef struct Aud6710_Sched {
    OSMesgQueue interruptQ;
    u8 pad[0x264 - sizeof(OSMesgQueue)];
    void *audioListHead;
} Aud6710_Sched;

typedef struct Aud6710_AudioCtx {
    u32 unk0[2];
    void *tasks[3];
} Aud6710_AudioCtx;

extern Aud6710_AudioCtx D_8076D4D0;
extern u8 D_8076D4C0;
extern OSMesgQueue D_8076D698;
extern OSMesgQueue D_8076D6D0;
extern s32 D_8076D708;
extern Aud6710_Sched gScheduler;
extern u32 D_807452C0;
s32 func_80602144();

void schedAddClient(void *, void *, OSMesgQueue *, s32, s32);
void func_80601EE4(void *, void *);
void func_80602104();
void func_8060A500(void);
void n_alClose(void *);
#ifdef NON_MATCHING
void func_80601D24(s32 arg0) {
    OSMesg sp58;
    void *var_s0;
    s32 done;
    s32 first;
    s32 numBuffers;
    s32 retraceMsg;

    done = 0;
    var_s0 = NULL;
    first = 1;
    schedAddClient(&gScheduler, &D_8076D4C0, &D_8076D698, 2, 2);
    retraceMsg = 5;
    osSendMesg(&D_8076D698, (OSMesg)retraceMsg, 0);
    numBuffers = 3;
    do {
        osRecvMesg(&D_8076D698, &sp58, 1);
        switch ((s32)sp58) {
        case 5:
            if (gScheduler.audioListHead != NULL) {
                osSendMesg(&gScheduler.interruptQ, (OSMesg)0x29E, 1);
            }
            func_80601EE4(D_8076D4D0.tasks[D_807452C0 % numBuffers], var_s0);
            var_s0 = D_8076D4D0.tasks[(D_807452C0 + 1) % numBuffers];
            if (first != 0) {
                first = 0;
            } else {
                osRecvMesg(&D_8076D6D0, &sp58, 1);
                func_80602104(var_s0);
            }
            func_8060A500();
            break;
        case 10:
            done = 1;
            break;
        }
    } while (!done);
    n_alClose(&D_8076D708);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6710/func_80601D24.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/6710/func_80601EE4.s")

#ifdef NON_MATCHING
extern s32 D_807454E8;

void func_80602104(s32 arg0) {
    if (((osAiGetLength() >> 2) == 0) && (D_807454E8 == 0)) {
        D_807454E8 = 0;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6710/func_80602104.s")
#endif

typedef struct Aud6710_DmaNode {
    struct Aud6710_DmaNode *next;
    struct Aud6710_DmaNode *prev;
    u32 unk8;
    u32 unkC;
    void *unk10;
} Aud6710_DmaNode;

typedef struct Aud6710_Struct80770188 {
    u8 unk0;
    u8 pad1[3];
    Aud6710_DmaNode *unk4;
    Aud6710_DmaNode *unk8;
} Aud6710_Struct80770188;

extern Aud6710_Struct80770188 D_80770188;
extern Aud6710_DmaNode D_8076FE68;
extern OSIoMesg D_807701A8[];
extern u32 D_807452C4;
extern OSMesgQueue D_807704A8;

#ifdef NON_MATCHING
s32 func_80602144(u32 addr, s32 len, void *state) {
    void *sp44;
    Aud6710_DmaNode *node;
    Aud6710_DmaNode *last;
    s32 head;
    u32 dmaIndex;
    s32 end;

    last = NULL;
    head = (s32)D_80770188.unk4;
    node = (Aud6710_DmaNode *)head;
    if (head != 0) {
        do {
            end = node->unk8 + 0x800;
            if (addr < node->unk8) {
                break;
            }
            if (end >= (s32)(addr + len)) {
                last = node;
                node->unkC = D_807452C0;
                return osVirtualToPhysical((u8 *)node->unk10 + (addr - node->unk8));
            }
            last = node;
            node = node->next;
        } while (node != NULL);
    }

    node = D_80770188.unk8;
    if (node == NULL) {
        return osVirtualToPhysical((void *)head);
    }

    D_80770188.unk8 = node->next;
    alUnlink((ALLink *)node);
    if (last != NULL) {
        alLink((ALLink *)node, (ALLink *)last);
    } else {
        head = (s32)D_80770188.unk4;
        if (head != 0) {
            D_80770188.unk4 = node;
            node->next = (Aud6710_DmaNode *)head;
            node->prev = NULL;
            ((Aud6710_DmaNode *)head)->prev = node;
        } else {
            D_80770188.unk4 = node;
            node->next = NULL;
            node->prev = NULL;
        }
    }

    head = addr & 1;
    addr -= head;
    node->unk8 = addr;
    node->unkC = D_807452C0;
    dmaIndex = D_807452C4;
    sp44 = node->unk10;
    D_807452C4 = dmaIndex + 1;
    osPiStartDma(&D_807701A8[dmaIndex], 1, 0, addr, sp44, 0x800, &D_807704A8);
    return osVirtualToPhysical(sp44) + head;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6710/func_80602144.s")
#endif


void *func_806022DC(Aud6710_Struct80770188 **arg0) {
    if (D_80770188.unk0 == 0) {
        D_80770188.unk4 = 0;
        D_80770188.unk8 = &D_8076FE68;
        D_80770188.unk0 = 1;
    }
    *arg0 = &D_80770188;
    return func_80602144;
}


void func_80602314(void) {
    s32 pad;
    OSMesg msg;
    Aud6710_DmaNode *node;
    Aud6710_DmaNode *next;
    u32 i;

    msg = NULL;
    i = 0;
    if (D_807452C4 != 0) {
        do {
            osRecvMesg(&D_807704A8, &msg, 0);
            i++;
        } while (i < D_807452C4);
    }
    for (node = D_80770188.unk4; node != NULL; node = next) {
        next = node->next;
        if ((node->unkC + 1) < D_807452C0) {
            if (node == D_80770188.unk4) {
                D_80770188.unk4 = node->next;
            }
            alUnlink((ALLink *)node);
            if (D_80770188.unk8 != NULL) {
                alLink((ALLink *)node, (ALLink *)D_80770188.unk8);
            } else {
                D_80770188.unk8 = node;
                node->next = NULL;
                node->prev = NULL;
            }
        }
    }
    D_807452C4 = 0;
    D_807452C0++;
}

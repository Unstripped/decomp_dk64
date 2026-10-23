// func_80601D24 (src/global/6710.c): stage 5, score 380, remaining diff frame size 0x68 vs 0x60 and if(!temp) branch order
#include "common.h"
#include "actor.h"

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

void schedAddClient(void *, void *, OSMesgQueue *, s32, s32);
void func_80601EE4(void *, void *);
void func_80602104(void *);
void func_8060A500(void);
void n_alClose(void *);

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
                osSendMesg(&gScheduler, (OSMesg)0x29E, 1);
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

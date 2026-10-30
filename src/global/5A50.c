#define alCSPSendMidi alCSPSendMidi_unused
#include "common.h"
#undef alCSPSendMidi

void alCSPSendMidi();

void postCSPChannelCommand(ALCSPlayer *, u8, u8, u8, s32);
void alCSPSetChlPanVolume(ALCSPlayer *, f32, f32);
void alCSPSetChlFX2Mix(ALCSPlayer *, u8, u8);

typedef struct {
    u8 pad[0xF8];
} Struct8076BF48;

typedef struct {
    u8 pad[0xEC];
} Struct8076C328_Marker;

typedef struct {
    Struct8076C328_Marker marker[4];
} Struct8076C328;

extern Struct8076BF48 D_8076BF48[];
extern Struct8076C328 D_8076C328[];

s32 __n_alCSeqNextDelta(Struct8076BF48 *, Struct8076C328 *, u8, s32);

extern ALCSPlayer *gSeqPlayers[];
void func_80737E90(ALCSPlayer *, s32);
void setCSPChannelStateValue(ALCSPlayer *, s32, u8);
void func_80737FD8(ALCSPlayer *, s32);
void enableCSPChannel(ALCSPlayer *, s32);
void func_80738080(ALCSPlayer *, s32, u8);
void setCSPChannelPortamento(ALCSPlayer *, s32, u8);
void setCSPChannelStopControl(ALCSPlayer *, s32, u8);
void func_8060B140(s32, s32 *, s32 *, s32, s32, s32, s32);
extern s32 D_8000DDCC;
extern s32 D_8076D200;

typedef struct CtrlAAudioArgs {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    ALHeap *heap;
    s32 w6;
    s8 b1C;
    s8 b1D;
    s16 pad1E;
    s32 w8;
    s32 w9;
} CtrlAAudioArgs;

typedef struct CtrlATaskCfg {
    s32 rate;
    s32 unk4;
    s32 cmdCount;
} CtrlATaskCfg;

typedef struct CtrlASndpCfg {
    s32 a;
    s32 b;
    s32 c;
    ALHeap *heap;
    s16 d;
} CtrlASndpCfg;

extern ALHeap D_8076D1E8;
extern u8 D_80770F50[];
extern ALBank *D_8076D1F8;
extern ALBank *D_8076D1FC;
extern u16 D_8076BF30[];
extern void *D_8076BF38[];
extern s32 D_807452B0[];
extern u32 gSegmentTable[];
void alHeapInit(ALHeap *, u8 *, s32);
void func_80601A10(void *, s32, void *);
void *func_80610FE8(s32);
void heapFree(u8 *);
void oscSetupConfig(ALSeqpConfig *, s32);
void n_alCSPlayerNew(ALCSPlayer *, ALSeqpConfig *);
void n_alSndpNew(void *);
void configureCSPOutputMode(s32);
void updateCSPOutputChannelMode(s32, s32);
void audioThreadStart(void);
void func_806010A0(void);

void audioInit(void) {
    CtrlASndpCfg sndp;
    ALBankFile *bankB;
    ALBankFile *tmp;
    s32 len;
    CtrlAAudioArgs args;
    s32 i;
    ALSeqpConfig seqp;
    CtrlATaskCfg task;
    ALBankFile *bankA;
    ALCSPlayer *player;
    ALCSPlayer *arg;

    alHeapInit(&D_8076D1E8, D_80770F50, 0x7BD80);
    args.w0 = 0x2C;
    args.w1 = 0x1E;
    args.w2 = 0x40;
    args.w3 = 1;
    args.w4 = 0;
    args.b1C = 6;
    args.b1D = 6;
    args.w6 = 0;
    args.heap = &D_8076D1E8;
    task.rate = 22050;
    task.unk4 = 2;
    task.cmdCount = 0xC00;
    func_80601A10(&args, 0x14, &task);
    len = gSegmentTable[0x5B] - gSegmentTable[0x5A];
    tmp = func_80610FE8(0x38000);
    func_8060B140(gSegmentTable[0x5A], (s32 *)tmp, &len, 0xD, 0, 2, 0);
    bankA = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, len);
    func_8060B140(gSegmentTable[0x5A], (s32 *)bankA, &len, 0xD, 0, 2, 0);
    alBnkfNew(bankA, (u8 *)gSegmentTable[0x54]);
    D_8076D1FC = bankA->bankArray[0];
    len = gSegmentTable[0x61] - gSegmentTable[0x60];
    func_8060B140(gSegmentTable[0x60], (s32 *)tmp, &len, 0xD, 0, 2, 0);
    heapFree((u8 *)tmp);
    bankB = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, len);
    func_8060B140(gSegmentTable[0x60], (s32 *)bankB, &len, 0xD, 0, 2, 0);
    alBnkfNew(bankB, (u8 *)gSegmentTable[0x66]);
    D_8076D1F8 = bankB->bankArray[0];
    seqp.maxVoices = 0x2C;
    seqp.maxEvents = 0x40;
    seqp.debugFlags = 0;
    seqp.maxChannels = 0x10;
    seqp.heap = &D_8076D1E8;
    oscSetupConfig(&seqp, 0x58);
    for (i = 0; i < 4; i++) {
        D_8076BF30[i] = 0xFFFF;
        D_8076BF38[i] = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, D_807452B0[i]);
        player = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, 0x8C);
        gSeqPlayers[i] = player;
        if (D_8076BF38[i] == NULL || (arg = player, player == NULL)) {
            arg = gSeqPlayers[i];
        }
        n_alCSPlayerNew(arg, &seqp);
        alCSPSetBank(gSeqPlayers[i], bankA->bankArray[0]);
    }
    func_806010A0();
    sndp.b = 0x40;
    sndp.a = 0x40;
    sndp.c = 0x14;
    sndp.d = 8;
    sndp.heap = &D_8076D1E8;
    n_alSndpNew(&sndp);
    configureCSPOutputMode(4);
    updateCSPOutputChannelMode(0, 4);
    audioThreadStart();
}

void func_806010A0(void) {
    s32 sp34;
    s32 sp30;
    s32 pad1;
    s32 temp;

    sp34 = 0x80;
    func_8060B140(D_8000DDCC, &D_8076D200, &sp34, 0, 0, 0, 0);
    temp = D_8076D200;
    sp30 = 0x2C0;
    func_8060B140(D_8000DDCC + temp, &D_8076D200, &sp30, 0, 0, 0, 0);
}

void seqPlayerPlay(u8 arg0) {
    if (alCSPGetState(gSeqPlayers[arg0]) == 0) {
        alCSPPlay(gSeqPlayers[arg0]);
    }
}

s32 seqPlayerGetState(u8 arg0) {
    return alCSPGetState(gSeqPlayers[arg0]);
}

void func_806011A0(u8 arg0, s32 arg1) {
    func_80737E90(gSeqPlayers[arg0], arg1);
}

typedef struct {
    s32 a, b, c;
} Struct806011D4;

void func_806011D4(Struct806011D4 arg0) {
}

void func_806011E4(u8 arg0, s32 arg1, u8 arg2) {
    setCSPChannelStateValue(gSeqPlayers[arg0], arg1, arg2);
}

void func_80601224(u8 arg0, s32 arg1) {
    func_80737FD8(gSeqPlayers[arg0], arg1);
}

void func_80601258(u8 arg0, s32 arg1) {
    enableCSPChannel(gSeqPlayers[arg0], arg1);
}

void func_8060128C(u8 arg0, u8 arg1, u8 arg2) {
    func_80738080(gSeqPlayers[arg0], arg1, arg2);
}

void func_806012D4(u8 arg0, u8 arg1, u8 arg2) {
    setCSPChannelPortamento(gSeqPlayers[arg0], arg1, arg2);
}
void func_8060131C(u8 arg0, s32 arg1, u8 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            func_8060128C(arg0, i, arg2);
        }
    }
}

void func_806013A0(u8 arg0, u8 arg1, u8 arg2) {
    setCSPChannelStopControl(gSeqPlayers[arg0], arg1, arg2);
}

void func_806013E8(u8 arg0, s32 arg1, u8 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            setCSPChannelStopControl(gSeqPlayers[arg0], i, arg2);
        }
    }
}

void func_80601484(u8 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            if (arg2 != 0) {
                func_80601258(arg0, i);
            } else {
                func_80601224(arg0, i);
            }
        }
    }
}

void func_8060151C(u8 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            if (arg2 != 0) {
                gSeqPlayers[arg0]->chanMask |= arg1;
            } else {
                gSeqPlayers[arg0]->chanMask &= arg1 ^ 0xFFFF;
            }
        }
    }
}

void func_806015E0(u8 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            alCSPSetChlFX2Mix(gSeqPlayers[arg0], i, arg2);
        }
    }
}

void func_80601678(u8 arg0, u8 arg1, u8 arg2) {
    alCSPSendMidi(gSeqPlayers[arg0], 0, (u8)(arg1 | 0xB0), 0x21, arg2);
}

void func_806016D0(u8 arg0, u8 arg1, u8 arg2) {
    alCSPSendMidi(gSeqPlayers[arg0], 0, (u8)(arg1 | 0xB0), 0x22, arg2);
}

void func_80601728(u8 arg0, u8 arg1, u8 arg2) {
    alCSPSendMidi(gSeqPlayers[arg0], 0, (u8)(arg1 | 0xB0), 0x23, arg2);
}
void seqPlayerSetTempo(u8 arg0, s32 tempo) {
    alCSPSetTempo(gSeqPlayers[arg0], tempo);
}
s32 seqPlayerGetTempo(u8 arg0) {
    return alCSPGetTempo(gSeqPlayers[arg0]);
}
void func_806017E8(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    postCSPChannelCommand(gSeqPlayers[arg0], arg1, arg2, arg3, arg4);
}

void func_80601848(u8 arg0, f32 arg1, f32 arg2) {
    alCSPSetChlPanVolume(gSeqPlayers[arg0], arg1, arg2);
}

void func_8060188C(u8 arg0, s32 arg1) {
    gSeqPlayers[arg0]->nextDelta += arg1;
}

s32 seqPlayerGetCurTime(u8 arg0) {
    return gSeqPlayers[arg0]->curTime;
}
s32 func_806018D4(u8 arg0, u8 arg1, s32 arg2) {
    return __n_alCSeqNextDelta(&D_8076BF48[arg0], &D_8076C328[arg0], arg1, arg2);
}

void func_8060193C(u8 arg0, u8 arg1) {
    alCSeqSetLoc((ALCSeq *)&D_8076BF48[arg0], (ALCSeqMarker *)&D_8076C328[arg0].marker[arg1]);
}

void seqPlayerSendMidi(u8 arg0, s32 ticks, u8 status, u8 byte1, s32 byte2) {
    alCSPSendMidi(gSeqPlayers[arg0], ticks, status, byte1, byte2);
}

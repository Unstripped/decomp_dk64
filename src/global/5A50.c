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
void alCSPSetUnk84(ALCSPlayer *, s32);
void setCSPChannelStateValue(ALCSPlayer *, s32, u8);
void alCSPChannelResetControl(ALCSPlayer *, s32);
void enableCSPChannel(ALCSPlayer *, s32);
void alCSPChannelSetControl(ALCSPlayer *, s32, u8);
void setCSPChannelPortamento(ALCSPlayer *, s32, u8);
void setCSPChannelStopControl(ALCSPlayer *, s32, u8);
void dmaReadAssetDecompress(s32, s32 *, s32 *, s32, s32, s32, s32);
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
void audioThreadInit(void *, s32, void *);
void *heapAlloc(s32);
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
    audioThreadInit(&args, 0x14, &task);
    len = gSegmentTable[0x5B] - gSegmentTable[0x5A];
    tmp = heapAlloc(0x38000);
    dmaReadAssetDecompress(gSegmentTable[0x5A], (s32 *)tmp, &len, 0xD, 0, 2, 0);
    bankA = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, len);
    dmaReadAssetDecompress(gSegmentTable[0x5A], (s32 *)bankA, &len, 0xD, 0, 2, 0);
    alBnkfNew(bankA, (u8 *)gSegmentTable[0x54]);
    D_8076D1FC = bankA->bankArray[0];
    len = gSegmentTable[0x61] - gSegmentTable[0x60];
    dmaReadAssetDecompress(gSegmentTable[0x60], (s32 *)tmp, &len, 0xD, 0, 2, 0);
    heapFree((u8 *)tmp);
    bankB = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, len);
    dmaReadAssetDecompress(gSegmentTable[0x60], (s32 *)bankB, &len, 0xD, 0, 2, 0);
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
    s32 size1;
    s32 size2;
    s32 pad;
    s32 offset;

    size1 = 0x80;
    dmaReadAssetDecompress(D_8000DDCC, &D_8076D200, &size1, 0, 0, 0, 0);
    offset = D_8076D200;
    size2 = 0x2C0;
    dmaReadAssetDecompress(D_8000DDCC + offset, &D_8076D200, &size2, 0, 0, 0, 0);
}

void seqPlayerPlay(u8 playerIndex) {
    if (alCSPGetState(gSeqPlayers[playerIndex]) == 0) {
        alCSPPlay(gSeqPlayers[playerIndex]);
    }
}

s32 seqPlayerGetState(u8 playerIndex) {
    return alCSPGetState(gSeqPlayers[playerIndex]);
}

void func_806011A0(u8 playerIndex, s32 val) {
    alCSPSetUnk84(gSeqPlayers[playerIndex], val);
}

typedef struct {
    s32 a, b, c;
} Struct806011D4;

void func_806011D4(Struct806011D4 unused) {
}

void seqPlayerSetChannelState(u8 playerIndex, s32 channel, u8 value) {
    setCSPChannelStateValue(gSeqPlayers[playerIndex], channel, value);
}

void seqPlayerDisableChannel(u8 playerIndex, s32 channel) {
    alCSPChannelResetControl(gSeqPlayers[playerIndex], channel);
}

void seqPlayerEnableChannel(u8 playerIndex, s32 channel) {
    enableCSPChannel(gSeqPlayers[playerIndex], channel);
}

void seqPlayerSetChannelControl(u8 playerIndex, u8 channel, u8 value) {
    alCSPChannelSetControl(gSeqPlayers[playerIndex], channel, value);
}

void seqPlayerSetChannelPortamento(u8 playerIndex, u8 channel, u8 portamento) {
    setCSPChannelPortamento(gSeqPlayers[playerIndex], channel, portamento);
}
void seqPlayerSetChannelControlMask(u8 playerIndex, s32 chanMask, u8 value) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (chanMask & (1 << i)) {
            seqPlayerSetChannelControl(playerIndex, i, value);
        }
    }
}

void seqPlayerSetChannelStopControl(u8 playerIndex, u8 channel, u8 control) {
    setCSPChannelStopControl(gSeqPlayers[playerIndex], channel, control);
}

void seqPlayerSetChannelStopControlMask(u8 playerIndex, s32 chanMask, u8 control) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (chanMask & (1 << i)) {
            setCSPChannelStopControl(gSeqPlayers[playerIndex], i, control);
        }
    }
}

void seqPlayerEnableChannelMask(u8 playerIndex, s32 chanMask, s32 enable) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (chanMask & (1 << i)) {
            if (enable != 0) {
                seqPlayerEnableChannel(playerIndex, i);
            } else {
                seqPlayerDisableChannel(playerIndex, i);
            }
        }
    }
}

void seqPlayerSetChannelMask(u8 playerIndex, s32 chanMask, s32 enable) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (chanMask & (1 << i)) {
            if (enable != 0) {
                gSeqPlayers[playerIndex]->chanMask |= chanMask;
            } else {
                gSeqPlayers[playerIndex]->chanMask &= chanMask ^ 0xFFFF;
            }
        }
    }
}

void seqPlayerSetChannelFX2MixMask(u8 playerIndex, s32 chanMask, s32 fxMix) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (chanMask & (1 << i)) {
            alCSPSetChlFX2Mix(gSeqPlayers[playerIndex], i, fxMix);
        }
    }
}

void func_80601678(u8 playerIndex, u8 channel, u8 val) {
    alCSPSendMidi(gSeqPlayers[playerIndex], 0, (u8)(channel | 0xB0), 0x21, val);
}

void func_806016D0(u8 playerIndex, u8 channel, u8 val) {
    alCSPSendMidi(gSeqPlayers[playerIndex], 0, (u8)(channel | 0xB0), 0x22, val);
}

void func_80601728(u8 playerIndex, u8 channel, u8 val) {
    alCSPSendMidi(gSeqPlayers[playerIndex], 0, (u8)(channel | 0xB0), 0x23, val);
}
void seqPlayerSetTempo(u8 playerIndex, s32 tempo) {
    alCSPSetTempo(gSeqPlayers[playerIndex], tempo);
}
s32 seqPlayerGetTempo(u8 playerIndex) {
    return alCSPGetTempo(gSeqPlayers[playerIndex]);
}
void func_806017E8(u8 playerIndex, u8 b0, u8 b1, u8 b2, s32 w3) {
    postCSPChannelCommand(gSeqPlayers[playerIndex], b0, b1, b2, w3);
}

void seqPlayerSetChannelPanVolume(u8 playerIndex, f32 pan, f32 volume) {
    alCSPSetChlPanVolume(gSeqPlayers[playerIndex], pan, volume);
}

void seqPlayerAddDeltaTime(u8 playerIndex, s32 delta) {
    gSeqPlayers[playerIndex]->nextDelta += delta;
}

s32 seqPlayerGetCurTime(u8 playerIndex) {
    return gSeqPlayers[playerIndex]->curTime;
}
s32 func_806018D4(u8 playerIndex, u8 byte, s32 delta) {
    return __n_alCSeqNextDelta(&D_8076BF48[playerIndex], &D_8076C328[playerIndex], byte, delta);
}

void seqPlayerSetMarkerLocation(u8 playerIndex, u8 markerIndex) {
    alCSeqSetLoc((ALCSeq *)&D_8076BF48[playerIndex], (ALCSeqMarker *)&D_8076C328[playerIndex].marker[markerIndex]);
}

void seqPlayerSendMidi(u8 playerIndex, s32 ticks, u8 status, u8 byte1, s32 byte2) {
    alCSPSendMidi(gSeqPlayers[playerIndex], ticks, status, byte1, byte2);
}

#define alCSPSendMidi alCSPSendMidi_unused
#include "common.h"
#undef alCSPSendMidi
#include "audio_config.h"
#include "segment.h"
#include "proto/global/13A7A0.h"
#include "proto/global/6710.h"
#include "proto/global/13D170.h"

void alCSPSendMidi(); // FAKE: callee prototype steer (header u8 byte2 masks seqPlayerSendMidi arg)

void postCSPChannelCommand(ALCSPlayer *, u8, u8, u8, s32);
void alCSPSetChlPanVolume(ALCSPlayer *, f32, f32);
void alCSPSetChlFX2Mix(ALCSPlayer *, u8, u8);

extern ALCSeq D_8076BF48[];
extern ALCSeqMarker D_8076C328[][4];


extern ALCSPlayer *gSeqPlayers[];
void alCSPSetUnk84(ALCSPlayer *, s32);
void setCSPChannelStateValue(ALCSPlayer *, s32, u8); // FAKE: callee prototype steer
void alCSPChannelResetControl(ALCSPlayer *, s32);
void enableCSPChannel(ALCSPlayer *, s32);
void alCSPChannelSetControl(ALCSPlayer *, s32, u8);
void setCSPChannelPortamento(ALCSPlayer *, s32, u8);
void setCSPChannelStopControl(ALCSPlayer *, s32, u8);
void dmaReadAssetDecompress(u32, void *, s32 *, u8, u8, u8, void *);
extern s32 D_8000DDCC;
extern s32 D_8076D200;

extern ALHeap D_8076D1E8;
extern u8 D_80770F50[];
extern ALBank *D_8076D1F8;
extern ALBank *D_8076D1FC;
extern u16 D_8076BF30[];
extern void *D_8076BF38[];
extern s32 D_807452B0[];
void alHeapInit(ALHeap *, u8 *, s32);
void *heapAlloc(s32);
void heapFree(void *);
void oscSetupConfig(ALSeqpConfig *, s32);
void n_alCSPlayerNew(ALCSPlayer *, ALSeqpConfig *);
void configureCSPOutputMode(u8);
void updateCSPOutputChannelMode(s32, s32);
void func_806010A0(void);

void audioInit(void) {
    GeSndpConfig sndp;
    ALBankFile *bankB;
    u8 *tmp;
    s32 len;
    AudioInitArgs args;
    s32 i;
    ALSeqpConfig seqp;
    AudioTaskConfig task;
    ALBankFile *bankA;
    ALCSPlayer *player;
    ALCSPlayer *arg;

    alHeapInit(&D_8076D1E8, D_80770F50, 0x7BD80);
    args.maxVVoices = 0x2C;
    args.maxPVoices = 0x1E;
    args.maxUpdates = 0x40;
    args.maxFXbusses = 1;
    args.dmaNew = NULL;
    args.fxType[0] = AL_FX_CUSTOM;
    args.fxType[1] = AL_FX_CUSTOM;
    args.outputRate = 0;
    args.heap = &D_8076D1E8;
    task.outputRate = 22050;
    task.framesPerField = 2;
    task.cmdCount = 0xC00;
    audioThreadInit(&args, 0x14, &task);
    len = gSegmentTable[15].romEnd - gSegmentTable[15].romStart;
    tmp = heapAlloc(0x38000);
    dmaReadAssetDecompress(gSegmentTable[15].romStart, tmp, &len, 0xD, 0, 2, 0);
    bankA = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, len);
    dmaReadAssetDecompress(gSegmentTable[15].romStart, bankA, &len, 0xD, 0, 2, 0);
    alBnkfNew(bankA, (u8 *)gSegmentTable[14].romStart);
    D_8076D1FC = bankA->bankArray[0];
    len = gSegmentTable[16].romEnd - gSegmentTable[16].romStart;
    dmaReadAssetDecompress(gSegmentTable[16].romStart, tmp, &len, 0xD, 0, 2, 0);
    heapFree(tmp);
    bankB = alHeapDBAlloc(NULL, 0, &D_8076D1E8, 1, len);
    dmaReadAssetDecompress(gSegmentTable[16].romStart, bankB, &len, 0xD, 0, 2, 0);
    alBnkfNew(bankB, (u8 *)gSegmentTable[17].romStart);
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
        if (D_8076BF38[i] == NULL || (arg = player, player == NULL)) { // FAKE: comma re-assign steers player/gSeqPlayers[i] reload
            arg = gSeqPlayers[i];
        }
        n_alCSPlayerNew(arg, &seqp);
        alCSPSetBank(gSeqPlayers[i], bankA->bankArray[0]);
    }
    func_806010A0();
    sndp.maxEvents = 0x40;
    sndp.maxSounds = 0x40;
    sndp.unk8 = 0x14;
    sndp.maxStates = 8;
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

typedef struct Struct806011D4 {
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
    alCSPSendMidi(gSeqPlayers[playerIndex], 0, (u8)(channel | AL_MIDI_ControlChange), 0x21, val);
}

void func_806016D0(u8 playerIndex, u8 channel, u8 val) {
    alCSPSendMidi(gSeqPlayers[playerIndex], 0, (u8)(channel | AL_MIDI_ControlChange), 0x22, val);
}

void func_80601728(u8 playerIndex, u8 channel, u8 val) {
    alCSPSendMidi(gSeqPlayers[playerIndex], 0, (u8)(channel | AL_MIDI_ControlChange), 0x23, val);
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
void func_806018D4(u8 playerIndex, u8 byte, s32 delta) {
    __n_alCSeqNextDelta(&D_8076BF48[playerIndex], D_8076C328[playerIndex], byte, delta);
}

void seqPlayerSetMarkerLocation(u8 playerIndex, u8 markerIndex) {
    alCSeqSetLoc(&D_8076BF48[playerIndex], &D_8076C328[playerIndex][markerIndex]);
}

void seqPlayerSendMidi(u8 playerIndex, s32 ticks, u8 status, u8 byte1, s32 byte2) {
    alCSPSendMidi(gSeqPlayers[playerIndex], ticks, status, byte1, byte2);
}

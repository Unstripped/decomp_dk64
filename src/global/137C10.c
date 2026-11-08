// ultralib prototypes osGetIntMask(void); the boot-segment implementation takes the mask (see 131B0.c).
#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;
#include "common.h"

extern s32 osGetIntMask(s32 unused);

typedef struct GcChanState {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ u8 priority;
    /* 0x09 */ u8 unk9[4];
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF[2];
    /* 0x11 */ u8 fxmix;
    /* 0x12 */ s8 pan;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 pitchBend;
    /* 0x18 */ u8 unk18[0x1C];
} GcChanState; // size 0x34

typedef struct GcVoiceState {
    /* 0x00 */ struct GcVoiceState *next;
    /* 0x04 */ ALVoice voice;
    /* 0x20 */ ALSound *sound;
    /* 0x24 */ s32 envEndTime;
    /* 0x28 */ f32 pitch;
    /* 0x2C */ f32 vibrato;
    /* 0x30 */ u8 envGain;
    /* 0x31 */ u8 channel;
    /* 0x32 */ u8 key;
    /* 0x33 */ u8 velocity;
    /* 0x34 */ u8 envPhase;
    /* 0x35 */ u8 phase;
    /* 0x36 */ u8 tremelo;
    /* 0x37 */ u8 flags;
    /* 0x38 */ void *tremOsc;
    /* 0x3C */ void *vibOsc;
} GcVoiceState; // size 0x40

typedef struct GcEvent {
    /* 0x00 */ u16 type;
    union {
        ALNoteEvent note;
        ALVolumeEvent vol;
        ALSeqpVolEvent spvol;
        ALSeqpPriorityEvent sppriority;
        ALSeqpSeqEvent spseq;
        ALSeqpBankEvent spbank;
        ALOscEvent osc;
        struct {
            f32 f0;
            f32 f1;
        } fpair;
        struct {
            u8 b0;
            u8 b1;
            u8 b2;
            u32 w4;
        } cmd;
    } msg;
} GcEvent;

typedef struct GcCSPlayer {
    /* 0x00 */ ALPlayer node;
    /* 0x14 */ ALSynth *drvr;
    /* 0x18 */ ALCSeq *target;
    /* 0x1C */ ALMicroTime curTime;
    /* 0x20 */ ALBank *bank;
    /* 0x24 */ s32 uspt;
    /* 0x28 */ s32 nextDelta;
    /* 0x2C */ s32 state;
    /* 0x30 */ u16 chanMask;
    /* 0x32 */ s16 vol;
    /* 0x34 */ u8 maxChannels;
    /* 0x35 */ u8 debugFlags;
    /* 0x38 */ GcEvent nextEvent;
    /* 0x48 */ ALEventQueue evtq;
    /* 0x5C */ ALMicroTime frameTime;
    /* 0x60 */ GcChanState *chanState;
    /* 0x64 */ GcVoiceState *vAllocHead;
    /* 0x68 */ GcVoiceState *vAllocTail;
    /* 0x6C */ GcVoiceState *vFreeList;
    /* 0x70 */ ALOscInit initOsc;
    /* 0x74 */ ALOscUpdate updateOsc;
    /* 0x78 */ ALOscStop stopOsc;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 unk88;
    /* 0x89 */ u8 unk89;
} GcCSPlayer;

extern ALSynth *n_syn;
void resetCSPChannelStates(GcCSPlayer *);
void __n_initChanState(GcCSPlayer *);
void n_alSynAddCSPPlayer(GcCSPlayer *);
ALMicroTime __n_CSPVoiceHandler(void *node);

void n_alCSPlayerNew(GcCSPlayer *seqp, ALSeqpConfig *c) {
    s32 i;
    GcVoiceState *unused0;
    GcVoiceState *unused1;
    ALEventListItem *items;
    GcVoiceState *vs;
    GcVoiceState *vsArray;
    ALHeap *hp = c->heap;

    seqp->bank = NULL;
    seqp->target = NULL;
    seqp->drvr = n_syn;
    seqp->chanMask = 0xFFFF;
    resetCSPChannelStates(seqp);
    seqp->uspt = 488;
    seqp->nextDelta = 0;
    seqp->state = 0;
    seqp->vol = 0x7FFF;
    seqp->debugFlags = c->debugFlags;
    seqp->frameTime = 16000;
    seqp->curTime = 0;
    seqp->initOsc = c->initOsc;
    seqp->updateOsc = c->updateOsc;
    seqp->stopOsc = c->stopOsc;
    seqp->unk7C = 0.0f;
    seqp->unk80 = 1.0f;
    seqp->unk84 = 0;
    seqp->unk89 = 0;
    seqp->unk88 = c->maxVoices;
    seqp->nextEvent.type = 9;
    seqp->maxChannels = c->maxChannels;
    seqp->chanState = alHeapDBAlloc(NULL, 0, hp, c->maxChannels, 0x34);
    __n_initChanState(seqp);
    vsArray = alHeapDBAlloc(NULL, 0, hp, c->maxVoices, 0x40);
    seqp->vFreeList = NULL;
    for (i = 0; i < c->maxVoices; i++) {
        vs = &vsArray[i];
        vs->next = seqp->vFreeList;
        seqp->vFreeList = vs;
    }
    seqp->vAllocHead = NULL;
    seqp->vAllocTail = NULL;
    items = alHeapDBAlloc(NULL, 0, hp, c->maxEvents, 0x1C);
    alEvtqNew(&seqp->evtq, items, c->maxEvents);
    seqp->node.next = NULL;
    seqp->node.handler = __n_CSPVoiceHandler;
    seqp->node.clientData = seqp;
    n_alSynAddCSPPlayer(seqp);
}

void n_alCSeqNextEvent(ALCSeq *, ALEvent *, s32);
void __n_CSPHandleMIDIMsg();
void __n_CSPPostNextSeqEvent();
void __n_CSPHandleMetaMsg();
s16 __n_vsVol(GcVoiceState *, GcCSPlayer *);
s32 __n_vsDelta(GcVoiceState *, s32);
void n_alSynSetVol(ALVoice *, s16, s32);
void n_alSynSetFXMix(ALVoice *, u8);
void n_alSynSetPan(ALVoice *, f32);
f32 n_alSemitonesToPitchRatio(s32);

void __n_CSPHandleNextSeqEvent(GcCSPlayer *);
void __n_seqpStopOsc(GcCSPlayer *, GcVoiceState *);
void __n_unmapVoice(GcCSPlayer *, ALVoice *);
s32 __n_voiceNeedsNoteKill(GcCSPlayer *, ALVoice *, s32);
void __n_seqpReleaseVoice(GcCSPlayer *, ALVoice *, s32);
void __n_initFromBank(GcCSPlayer *, ALBank *);
void n_alSynStopVoice(ALVoice *);
void n_alSynFreeVoice(ALVoice *);
void n_alSynSetPitch(ALVoice *, f32);
u8 n_alCSPClampVoiceFXMix(GcVoiceState *, GcCSPlayer *);
void n_alSynSetVoiceUnkC(ALVoice *, u8);
void *n_alSynGetFXDelay(u8);
void n_alSynSetFXParam(void *, s32, void *);
void *n_alSynGetFXFeedback(u8);
void n_alSynSetFXFilterParam(void *, u8, void *);

ALMicroTime __n_CSPVoiceHandler(void *node) {
    GcCSPlayer *seqp = node;
    ALEvent evt;
    ALVoice *voice;
    ALMicroTime delta;
    GcVoiceState *vs;
    void *oscState;
    f32 oscValue;
    u8 chan;
    s32 unused;
    void *cmdA;
    void *cmdB;

    do {
        switch (seqp->nextEvent.type) {
            case 0:
                __n_CSPHandleNextSeqEvent(seqp);
                break;
            case 9:
                evt.type = 9;
                alEvtqPostEvent(&seqp->evtq, &evt, seqp->frameTime);
                break;
            case 5:
                voice = seqp->nextEvent.msg.note.voice;
                n_alSynStopVoice(voice);
                n_alSynFreeVoice(voice);
                vs = voice->clientPrivate;
                if (vs->flags != 0) {
                    __n_seqpStopOsc(seqp, vs);
                }
                __n_unmapVoice(seqp, voice);
                break;
            case 6:
                voice = seqp->nextEvent.msg.note.voice;
                vs = voice->clientPrivate;
                if (vs->envPhase == 0) {
                    vs->envPhase = 1;
                }
                delta = seqp->nextEvent.msg.vol.delta;
                vs->envEndTime = seqp->curTime + delta;
                vs->envGain = seqp->nextEvent.msg.vol.vol;
                n_alSynSetVol(voice, __n_vsVol(vs, seqp), delta);
                break;
            case 22:
                vs = (GcVoiceState *)seqp->nextEvent.msg.osc.vs;
                oscState = seqp->nextEvent.msg.osc.oscState;
                delta = seqp->updateOsc(oscState, &oscValue);
                vs->tremelo = oscValue;
                n_alSynSetVol(&vs->voice, __n_vsVol(vs, seqp), __n_vsDelta(vs, seqp->curTime));
                evt.type = 0x16;
                evt.msg.osc.vs = (ALVoiceState *)vs;
                evt.msg.osc.oscState = oscState;
                alEvtqPostEvent(&seqp->evtq, &evt, delta);
                break;
            case 23:
                vs = (GcVoiceState *)seqp->nextEvent.msg.osc.vs;
                oscState = seqp->nextEvent.msg.osc.oscState;
                chan = seqp->nextEvent.msg.osc.chan;
                delta = seqp->updateOsc(oscState, &oscValue);
                vs->vibrato = oscValue;
                n_alSynSetPitch(&vs->voice, seqp->chanState[chan].pitchBend * (vs->pitch * vs->vibrato));
                if (seqp->chanState[chan].fxmix != 0) {
                    n_alSynSetPan(&vs->voice, 440.0f * n_alSemitonesToPitchRatio(vs->key - vs->sound->keyMap->keyBase) * seqp->chanState[chan].pitchBend * vs->vibrato);
                }
                evt.type = 0x17;
                evt.msg.osc.vs = (ALVoiceState *)vs;
                evt.msg.osc.oscState = oscState;
                evt.msg.osc.chan = chan;
                alEvtqPostEvent(&seqp->evtq, &evt, delta);
                break;
            case 2:
            case 21:
                __n_CSPHandleMIDIMsg(seqp, &seqp->nextEvent);
                break;
            case 7:
                __n_CSPHandleMetaMsg(seqp, &seqp->nextEvent);
                break;
            case 10:
                seqp->vol = seqp->nextEvent.msg.spvol.vol;
                for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                    n_alSynSetVol(&vs->voice, __n_vsVol(vs, seqp), __n_vsDelta(vs, seqp->curTime));
                }
                break;
            case 24:
                seqp->unk7C = seqp->nextEvent.msg.fpair.f0;
                seqp->unk80 = seqp->nextEvent.msg.fpair.f1;
                for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                    n_alSynSetVoiceUnkC(&vs->voice, n_alCSPClampVoiceFXMix(vs, seqp));
                }
                break;
            case 25:
                if (seqp->nextEvent.msg.cmd.b1 < 8) {
                    cmdA = n_alSynGetFXDelay(seqp->nextEvent.msg.cmd.b0);
                    if (cmdA != NULL) {
                        n_alSynSetFXParam(cmdA, (seqp->nextEvent.msg.cmd.b2 << 3) | (seqp->nextEvent.msg.cmd.b1 & 7), &seqp->nextEvent.msg.cmd.w4);
                    }
                } else {
                    cmdB = n_alSynGetFXFeedback(seqp->nextEvent.msg.cmd.b0);
                    if (cmdB != NULL) {
                        n_alSynSetFXFilterParam(cmdB, seqp->nextEvent.msg.cmd.b1, &seqp->nextEvent.msg.cmd.w4);
                    }
                }
                break;
            case 15:
                if (seqp->state != 1) {
                    seqp->state = 1;
                    __n_CSPPostNextSeqEvent(seqp);
                }
                break;
            case 16:
                if (seqp->state == 2) {
                    for (vs = seqp->vAllocHead; vs != NULL; vs = seqp->vAllocHead) {
                        n_alSynStopVoice(&vs->voice);
                        n_alSynFreeVoice(&vs->voice);
                        if (vs->flags != 0) {
                            __n_seqpStopOsc(seqp, vs);
                        }
                        __n_unmapVoice(seqp, &vs->voice);
                    }
                    seqp->state = 0;
                }
                break;
            case 17:
                if (seqp->state == 1) {
                    alEvtqFlushType(&seqp->evtq, 0);
                    alEvtqFlushType(&seqp->evtq, 0x15);
                    alEvtqFlushType(&seqp->evtq, 2);
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (__n_voiceNeedsNoteKill(seqp, &vs->voice, 50000)) {
                            __n_seqpReleaseVoice(seqp, &vs->voice, 50000);
                        }
                    }
                    for (chan = 0; chan < 16; chan++) {
                        seqp->chanState[chan].unkD = seqp->chanState[chan].unkE;
                        if (seqp->chanState[chan].unkD == 0) {
                            seqp->chanMask &= (1 << chan) ^ 0xFFFF;
                        } else {
                            seqp->chanMask |= 1 << chan;
                        }
                    }
                    seqp->state = 2;
                    evt.type = 0x10;
                    alEvtqPostEvent(&seqp->evtq, &evt, 0x7FFFFFFF);
                }
                break;
            case 12:
                chan = seqp->nextEvent.msg.sppriority.chan;
                seqp->chanState[chan].priority = seqp->nextEvent.msg.sppriority.priority;
                break;
            case 13:
                seqp->target = seqp->nextEvent.msg.spseq.seq;
                seqp->chanMask = 0xFFFF;
                if (seqp->bank != NULL) {
                    __n_initFromBank(seqp, seqp->bank);
                }
                break;
            case 14:
                seqp->bank = seqp->nextEvent.msg.spbank.bank;
                __n_initFromBank(seqp, seqp->bank);
                break;
            case 1:
            case 3:
            case 4:
                break;
        }
        seqp->nextDelta = alEvtqNextEvent(&seqp->evtq, (ALEvent *)&seqp->nextEvent);
    } while (seqp->nextDelta == 0);
    seqp->curTime += seqp->nextDelta;
    return seqp->nextDelta;
}


void __n_CSPHandleNextSeqEvent(GcCSPlayer *seqp) {
    ALEvent evt;

    if (seqp->target == NULL) {
        return;
    }
    n_alCSeqNextEvent(seqp->target, &evt, 1);
    switch (evt.type) {
        case 1:
            __n_CSPHandleMIDIMsg(seqp, &evt);
            __n_CSPPostNextSeqEvent(seqp);
            break;
        case 3:
            __n_CSPHandleMetaMsg(seqp, &evt);
            __n_CSPPostNextSeqEvent(seqp);
            break;
        case 4:
            seqp->state = 2;
            evt.type = 0x10;
            alEvtqPostEvent(&seqp->evtq, &evt, 0x7FFFFFFF);
            break;
        case 18:
        case 19:
        case 20:
            __n_CSPPostNextSeqEvent(seqp);
            break;
        default:
            break;
    }
}

void __n_CSPUpdateChanVol(GcCSPlayer *seqp, u8 chan) {
    GcVoiceState *vs;
    s16 vol;

    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
        if (vs->channel == chan && vs->envPhase != 3) {
            vol = __n_vsVol(vs, seqp);
            n_alSynSetVol(&vs->voice, vol, __n_vsDelta(vs, seqp->curTime));
        }
    }
}

void __n_CSPUpdateChanFxPan(GcCSPlayer *seqp, u8 chan) {
    GcVoiceState *vs;
    s16 fxmix;
    s8 pan;
    f32 pitchBend;

    pan = seqp->chanState[chan].pan - 0x40;
    pitchBend = seqp->chanState[chan].pitchBend;
    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
        if (vs->channel == chan) {
            fxmix = seqp->chanState[chan].fxmix;
            n_alSynSetFXMix(&vs->voice, fxmix);
            if (fxmix != 0) {
                n_alSynSetPan(&vs->voice, n_alSemitonesToPitchRatio(vs->key - vs->sound->keyMap->keyBase + pan) * 440.0f * pitchBend);
            }
        }
    }
}

typedef struct {
    /* 0x00 */ ALInstrument *instrument;
    /* 0x04 */ s16 bendRange;
    /* 0x06 */ u8 pad06;
    /* 0x07 */ u8 pan;
    /* 0x08 */ u8 priority;
    /* 0x09 */ u8 vol;
    /* 0x0A */ u8 fxmix;
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ u8 sustain;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ u8 unk0F;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 pitchBend;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ s8 unk27;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 pad30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 pad33;
} GdChanState;

typedef s32 (*GdOscInit)(void **, f32 *, u8, u8, u8, u8, u8);

typedef struct {
    u8 pad00[0x3C];
    s32 unk3C;
} GdBankInfo;

extern s32 D_807FF040[];

ALSound *__n_lookupSoundQuick(GcCSPlayer *seqp, u8 key, u8 vel, u8 chan);
GcVoiceState *__n_mapVoice(GcCSPlayer *seqp, u8 key, u8 vel, u8 chan);
GcVoiceState *__n_lookupVoice(GcCSPlayer *seqp, u8 key, u8 chan);
void __n_setInstChanState(GcCSPlayer *seqp, ALInstrument *inst, u8 chan);
u8 __n_vsPan(GcVoiceState *vs, GcCSPlayer *seqp);
void n_alSynAllocVoicePriorityA(ALVoice *voice, u8 arg);
void n_alSynAllocVoicePriorityB(ALVoice *voice, u8 arg);
void n_alSynAllocVoice(ALVoice *voice, ALVoiceConfig *config);
void n_alSynStartVoiceParams(ALVoice *voice, ALWaveTable *w, f32 pitch, s16 vol, u8 pan, u8 fxmix, u8 unityPitch, f32 fxVolume, u8 fxDelay, s32 samples);

#define GdCH(seqp, c) (((GdChanState *)(seqp)->chanState)[c])

void __n_CSPHandleMIDIMsg(GcCSPlayer *seqp, ALEvent *event) {
    ALVoice *voice;
    GcVoiceState *vs;
    s32 status;
    u8 chan;
    u8 key;
    u8 vel;
    u8 byte1;
    u8 byte2;
    ALMIDIEvent *midi;
    s16 vol;
    ALEvent evt;
    s32 delta;
    GcVoiceState *voiceState;
    u8 pan;
    GdChanState *chanSt;
    s32 oscTypeOrIndex;
    ALVoiceConfig vc;
    ALSound *sound;
    s16 cents;
    f32 pitch;
    f32 oscVal;
    u8 fxmix;
    u8 unityPitch;
    f32 voiceTune;
    void *oscState;
    ALInstrument *inst;
    u8 currentVal;
    u8 targetVal;
    s32 stepDelta;
    s32 targetInst;
    s32 bendVal;
    f32 bendRatio;
    s32 bendCents;

    midi = (ALMIDIEvent *)&event->msg;
    status = midi->status & 0xF0;
    chan = midi->status & 0xF;
    byte1 = key = midi->byte1;
    byte2 = vel = midi->byte2;
    switch (status) {
        case 0x90:
            if (vel != 0) {
                if (seqp->state != 1 || !(seqp->chanMask & (1 << chan))) {
                    if (midi->duration != 0) {
                        evt.type = 0x15;
                        evt.msg.midi.status = chan | 0x80;
                        evt.msg.midi.byte1 = key;
                        evt.msg.midi.byte2 = 0;
                        delta = seqp->uspt * midi->duration;
                        D_807FF040[chan] = delta;
                        alEvtqPostEvent(&seqp->evtq, &evt, delta);
                    }
                    break;
                }
                {
                    chanSt = &GdCH(seqp, chan);
                    sound = __n_lookupSoundQuick(seqp, key, vel, chan);
                    if (sound == NULL) {
                        return;
                    }
                    vc.priority = chanSt->priority;
                    vc.fxBus = chanSt->unk0B;
                    vc.unityPitch = 0;
                    voiceState = __n_mapVoice(seqp, key, vel, chan);
                    if (voiceState == NULL) {
                        return;
                    }
                    voice = &voiceState->voice;
                    n_alSynAllocVoice(voice, &vc);
                    voiceState->sound = sound;
                    voiceState->envPhase = 0;
                    if (chanSt->sustain >= 0x40) {
                        voiceState->phase = 2;
                    } else {
                        voiceState->phase = 0;
                    }
                    cents = (key - sound->keyMap->keyBase) * 100 + sound->keyMap->detune;
                    if (chanSt->unk24 != 0) {
                        cents += chanSt->unk27;
                    }
                    voiceState->pitch = alCents2Ratio(cents);
                    if (chanSt->unk24 != 0) {
                        voiceState->envGain = chanSt->unk25;
                        voiceState->envEndTime = seqp->curTime + chanSt->unk18;
                    } else {
                        voiceState->envGain = sound->envelope->attackVolume;
                        voiceState->envEndTime = seqp->curTime + sound->envelope->attackTime;
                    }
                    voiceState->flags = 0;
                    if (chanSt->unk24 != 0) {
                        oscTypeOrIndex = chanSt->unk28;
                    } else {
                        inst = GdCH(seqp, chan).instrument;
                        oscTypeOrIndex = inst->tremType;
                    }
                    oscVal = 127.0f;
                    if (oscTypeOrIndex != 0 && seqp->initOsc != NULL) {
                        if (chanSt->unk24 != 0) {
                            delta = ((GdOscInit)seqp->initOsc)(&oscState, &oscVal, chanSt->unk28, chanSt->unk29, chanSt->unk2A, chanSt->unk2B, chanSt->unk31);
                        } else {
                            delta = ((GdOscInit)seqp->initOsc)(&oscState, &oscVal, inst->tremType, inst->tremRate, inst->tremDepth, inst->tremDelay, chanSt->unk31);
                        }
                        if (delta != 0) {
                            evt.type = 0x16;
                            evt.msg.osc.vs = (void *)voiceState;
                            evt.msg.osc.oscState = oscState;
                            alEvtqPostEvent(&seqp->evtq, &evt, delta);
                            voiceState->flags |= 1;
                            voiceState->tremOsc = oscState;
                        }
                    }
                    voiceState->tremelo = (u32)oscVal;
                    oscVal = 1.0f;
                    if (chanSt->unk24 != 0) {
                        oscTypeOrIndex = chanSt->unk2C;
                    } else {
                        oscTypeOrIndex = inst->vibType;
                    }
                    if (oscTypeOrIndex != 0 && seqp->initOsc != NULL) {
                        if (chanSt->unk24 != 0) {
                            delta = ((GdOscInit)seqp->initOsc)(&oscState, &oscVal, chanSt->unk2C, chanSt->unk2D, chanSt->unk2E, chanSt->unk2F, chanSt->unk31);
                        } else {
                            delta = ((GdOscInit)seqp->initOsc)(&oscState, &oscVal, inst->vibType, inst->vibRate, inst->vibDepth, inst->vibDelay, chanSt->unk31);
                        }
                        if (delta != 0) {
                            evt.type = 0x17;
                            evt.msg.osc.vs = (void *)voiceState;
                            evt.msg.osc.oscState = oscState;
                            evt.msg.osc.chan = chan;
                            alEvtqPostEvent(&seqp->evtq, &evt, delta);
                            voiceState->flags |= 2;
                            voiceState->vibOsc = oscState;
                        }
                    }
                    voiceState->vibrato = oscVal;
                    pitch = voiceState->pitch * chanSt->pitchBend * voiceState->vibrato;
                    fxmix = n_alCSPClampVoiceFXMix(voiceState, seqp);
                    unityPitch = chanSt->unk11;
                    if (unityPitch != 0) {
                        voiceTune = n_alSemitonesToPitchRatio(((cents / 100) + chanSt->unk12) - 0x40) * 440.0f * chanSt->pitchBend;
                    } else {
                        voiceTune = 127.0f;
                    }
                    pan = __n_vsPan(voiceState, seqp);
                    vol = __n_vsVol(voiceState, seqp);
                    if (chanSt->unk24 != 0) {
                        delta = chanSt->unk18;
                    } else {
                        delta = sound->envelope->attackTime;
                    }
                    n_alSynStartVoiceParams(voice, sound->wavetable, pitch, vol, pan, fxmix, unityPitch, voiceTune, chanSt->unk13, delta);
                    evt.type = 6;
                    evt.msg.vol.voice = voice;
                    if (chanSt->unk24 != 0) {
                        evt.msg.vol.vol = chanSt->unk26;
                        evt.msg.vol.delta = chanSt->unk1C;
                    } else {
                        evt.msg.vol.vol = sound->envelope->decayVolume;
                        evt.msg.vol.delta = sound->envelope->decayTime;
                    }
                    alEvtqPostEvent(&seqp->evtq, &evt, delta);
                    if (midi->duration != 0) {
                        evt.type = 0x15;
                        evt.msg.midi.status = chan | 0x80;
                        evt.msg.midi.byte1 = key;
                        evt.msg.midi.byte2 = 0;
                        delta = seqp->uspt * midi->duration;
                        D_807FF040[chan] = delta;
                        alEvtqPostEvent(&seqp->evtq, &evt, delta);
                    }
                    if ((chanSt->unk10 & 1) && ((OSMesgQueue *)seqp->unk84) != NULL) {
                        osSendMesg(((OSMesgQueue *)seqp->unk84), (OSMesg)((D_807FF040[chan] & ~0xFF) | (chanSt->unk10 >> 2)), 0);
                    }
                }
                break;
            }
        case 0x80:
            voiceState = __n_lookupVoice(seqp, key, chan);
            if (voiceState == NULL) {
                return;
            }
            chanSt = &GdCH(seqp, chan);
            if (voiceState->phase == 2) {
                voiceState->phase = 4;
            } else {
                voiceState->phase = 3;
                if (chanSt->unk24 != 0) {
                    __n_seqpReleaseVoice(seqp, &voiceState->voice, chanSt->unk20);
                } else {
                    __n_seqpReleaseVoice(seqp, &voiceState->voice, voiceState->sound->envelope->releaseTime);
                }
            }
            if ((chanSt->unk10 & 2) && ((OSMesgQueue *)seqp->unk84) != NULL) {
                osSendMesg(((OSMesgQueue *)seqp->unk84), (OSMesg)((key << 16) | 8 | (chanSt->unk10 >> 2)), 0);
            }
            break;
        case 0xA0:
            voiceState = __n_lookupVoice(seqp, key, chan);
            if (voiceState == NULL) {
                return;
            }
            voiceState->velocity = byte2;
            n_alSynSetVol(&voiceState->voice, __n_vsVol(voiceState, seqp), __n_vsDelta(voiceState, seqp->curTime));
            break;
        case 0xD0:
            for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                if (vs->channel == chan) {
                    vs->velocity = byte1;
                    n_alSynSetVol(&vs->voice, __n_vsVol(vs, seqp), __n_vsDelta(vs, seqp->curTime));
                }
            }
            break;
        case 0xB0:
            switch (byte1) {
                case 0xA:
                    GdCH(seqp, chan).pan = byte2;
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan) {
                            pan = __n_vsPan(vs, seqp);
                            n_alSynAllocVoicePriorityA(&vs->voice, pan);
                        }
                    }
                    break;
                case 0xFD:
                    GdCH(seqp, chan).unk0F = byte2;
                    break;
                case 0xFF:
                    if (GdCH(seqp, chan).unk0F == 0) {
                        GdCH(seqp, chan).unk0F = 0x90;
                    }
                    if (GdCH(seqp, chan).unk0E != byte2) {
                        if (GdCH(seqp, chan).unk0E == GdCH(seqp, chan).unk0D) {
                            GdCH(seqp, chan).unk0E = byte2;
                        } else {
                            GdCH(seqp, chan).unk0E = byte2;
                            break;
                        }
                    } else {
                        break;
                    }
                    midi->byte1 = 0xFE;
                case 0xFE:
                    currentVal = GdCH(seqp, chan).unk0D;
                    targetVal = GdCH(seqp, chan).unk0E;
                    vel = GdCH(seqp, chan).unk0F;
                    stepDelta = targetVal - currentVal;
                    if (stepDelta > 0) {
                        if (vel & 0x80) {
                            vel = (vel & 0x7F) << 1;
                        }
                        if (stepDelta > vel) {
                            stepDelta = vel;
                        }
                    } else {
                        vel &= 0x7F;
                        if (stepDelta < -vel) {
                            stepDelta = -vel;
                        }
                    }
                    currentVal += stepDelta;
                    GdCH(seqp, chan).unk0D = currentVal;
                    if (currentVal != targetVal) {
                        alEvtqPostEvent(&seqp->evtq, event, seqp->uspt * 100);
                    }
                    if (currentVal != 0) {
                        seqp->chanMask |= 1 << chan;
                    } else {
                        seqp->chanMask &= ~(1 << chan);
                    }
                    __n_CSPUpdateChanVol(seqp, chan);
                    break;
                case 0xFC:
                    GdCH(seqp, chan).unk0D = byte2;
                    GdCH(seqp, chan).unk0E = byte2;
                    if (byte2 == 0) {
                        seqp->chanMask = seqp->chanMask & ((1 << chan) ^ 0xFFFF);
                    } else {
                        seqp->chanMask |= 1 << chan;
                    }
                    __n_CSPUpdateChanVol(seqp, chan);
                    break;
                case 0x21:
                    GdCH(seqp, chan).unk11 = byte2;
                    __n_CSPUpdateChanFxPan(seqp, chan);
                    break;
                case 0x22:
                    GdCH(seqp, chan).unk12 = byte2;
                    __n_CSPUpdateChanFxPan(seqp, chan);
                    break;
                case 0x23:
                    GdCH(seqp, chan).unk13 = byte2;
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan) {
                            n_alSynAllocVoicePriorityB(&vs->voice, byte2);
                        }
                    }
                    break;
                case 0x1E:
                    if (((OSMesgQueue *)seqp->unk84) != NULL) {
                        osSendMesg(((OSMesgQueue *)seqp->unk84), (OSMesg)(((byte2 & 7) | 0x10) | ((seqp->node.samplesLeft << 5) & ~0xFF)), 0);
                    }
                    break;
                case 0x7:
                    GdCH(seqp, chan).vol = byte2;
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan && vs->envPhase != 3) {
                            vol = __n_vsVol(vs, seqp);
                            n_alSynSetVol(&vs->voice, vol, __n_vsDelta(vs, seqp->curTime));
                        }
                    }
                    break;
                case 0x10:
                    GdCH(seqp, chan).priority = byte2;
                    break;
                case 0x40:
                    GdCH(seqp, chan).sustain = byte2;
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan && vs->phase != 3) {
                            if (byte2 >= 0x40) {
                                if (vs->phase == 0) {
                                    vs->phase = 2;
                                }
                            } else if (vs->phase == 2) {
                                vs->phase = 0;
                            } else if (vs->phase == 4) {
                                vs->phase = 3;
                                if (chanSt->unk24 != 0) {
                                    __n_seqpReleaseVoice(seqp, &vs->voice, (GdCH(seqp, chan).unk20 < 0x3E80) ? 0x3E80 : GdCH(seqp, chan).unk20);
                                } else {
                                    __n_seqpReleaseVoice(seqp, &vs->voice, (voiceState->sound->envelope->releaseTime < 0x3E80) ? 0x3E80 : voiceState->sound->envelope->releaseTime);
                                }
                            }
                        }
                    }
                    break;
                case 0x5B:
                    GdCH(seqp, chan).fxmix = (GdCH(seqp, chan).fxmix & 0x80) | byte2;
                    byte2 = GdCH(seqp, chan).fxmix >> 7;
                case 0x41:
                    GdCH(seqp, chan).fxmix = (GdCH(seqp, chan).fxmix & 0x7F) | (byte2 << 7);
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan) {
                            n_alSynSetVoiceUnkC(&vs->voice, GdCH(seqp, chan).fxmix);
                        }
                    }
                    break;
                case 0x5C:
                    if (byte2 < ((GdBankInfo *)n_syn)->unk3C && byte2 >= 0) {
                        GdCH(seqp, chan).unk0B = byte2;
                    }
                    break;
                case 0x1A:
                    break;
                case 0x20:
                    GdCH(seqp, chan).unk32 = byte2;
                    break;
                default:
                    break;
            }
            break;
        case 0xC0:
            oscTypeOrIndex = (GdCH(seqp, chan).unk32 << 7) + key;
            if (oscTypeOrIndex < seqp->bank->instCount) {
                targetInst = (s32)seqp->bank->instArray[oscTypeOrIndex];
                __n_setInstChanState(seqp, (ALInstrument *)targetInst, chan);
            } else {
            }
            break;
        case 0xE0:
            bendVal = ((byte2 << 7) + byte1) - 0x2000;
            bendCents = (GdCH(seqp, chan).bendRange * bendVal) / 8192;
            bendRatio = alCents2Ratio(bendCents);
            GdCH(seqp, chan).pitchBend = bendRatio;
            for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                if (vs->channel == chan) {
                    n_alSynSetPitch(&vs->voice, vs->pitch * bendRatio * vs->vibrato);
                    if (GdCH(seqp, chan).unk11 != 0) {
                        n_alSynSetPan(&vs->voice, n_alSemitonesToPitchRatio(vs->key - vs->sound->keyMap->keyBase) * 440.0f * bendRatio * vs->vibrato);
                    }
                }
            }
            break;
        default:
            break;
    }
}

void __n_setUsptFromTempo(GcCSPlayer *seqp, f32 tempo);
void __n_CSPRepostEvent(ALEventQueue *evtq, ALEventListItem *item);

void __n_CSPHandleMetaMsg(GcCSPlayer *seqp, ALEvent *event) {
    ALTempoEvent *tevt = &event->msg.tempo;
    s32 tempo;
    s32 oldUspt;
    s32 quot;
    s32 tmp;
    s32 deltaTime = 0;
    ALEventListItem *item;
    ALEventListItem *nextItem;
    ALEventListItem *lastItem = NULL;

    if (event->msg.tempo.status == 0xFF) {
        if (event->msg.tempo.type == 0x51) {
            oldUspt = seqp->uspt;
            tempo = (tevt->byte1 << 16) | (tevt->byte2 << 8) | tevt->byte3;
            __n_setUsptFromTempo(seqp, (f32)tempo);
            item = (ALEventListItem *)seqp->evtq.allocList.next;
            while (item != NULL) {
                deltaTime += item->delta;
                nextItem = (ALEventListItem *)item->node.next;
                if (item->evt.type == 0x15) {
                    alUnlink((ALLink *)item);
                    if (lastItem != NULL) {
                        alLink((ALLink *)item, (ALLink *)lastItem);
                    } else {
                        item->node.next = NULL;
                        item->node.prev = NULL;
                        lastItem = item;
                    }
                    tmp = deltaTime;
                    if (nextItem != NULL) {
                        deltaTime -= item->delta;
                        nextItem->delta += item->delta;
                    }
                    item->delta = tmp;
                }
                item = nextItem;
            }
            item = lastItem;
            while (item != NULL) {
                nextItem = (ALEventListItem *)item->node.next;
                quot = item->delta / oldUspt;
                item->delta = seqp->uspt * quot;
                __n_CSPRepostEvent(&seqp->evtq, item);
                item = nextItem;
            }
        }
    }
}

void __n_CSPRepostEvent(ALEventQueue *evtq, ALEventListItem *item) {
    s32 mask;
    ALLink *node;
    ALLink *next;

    mask = osGetIntMask(1);
    for (node = &evtq->allocList; node != 0; node = node->next) {
        if (node->next == 0) {
            alLink((ALLink *)item, node);
            break;
        } else {
            next = node->next;
            if (item->delta < ((ALEventListItem *)next)->delta) {
                ((ALEventListItem *)next)->delta -= item->delta;
                alLink((ALLink *)item, node);
                break;
            }
            item->delta -= ((ALEventListItem *)next)->delta;
        }
    }
    osGetIntMask(mask);
}

void __n_setUsptFromTempo(GcCSPlayer *seqp, f32 tempo) {
    if (seqp->target != NULL) {
        seqp->uspt = (f32)tempo * (f32)seqp->target->qnpt;
    } else {
        seqp->uspt = 0x1E8;
    }
}

extern s32 __n_alCSeqGetNextDelta(ALCSeq *seq, s32 *ticks);

void __n_CSPPostNextSeqEvent(GcCSPlayer *seqp) {
    ALEvent evt;
    s32 deltaTicks;

    if (seqp->state != 1 || seqp->target == NULL) {
        return;
    }
    if (!__n_alCSeqGetNextDelta(seqp->target, &deltaTicks)) {
        return;
    }
    evt.type = 0;
    alEvtqPostEvent(&seqp->evtq, &evt, seqp->uspt * deltaTicks);
}

void n_alCSPSetMaxVoices(GcCSPlayer *seqp, u8 arg) {
    seqp->unk88 = arg;
}

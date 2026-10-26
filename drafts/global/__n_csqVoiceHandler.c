// __n_csqVoiceHandler (src/global/137C10.c): stage 6 of 6, near match: frame 0x78 and s0-s2/fs0 saved set match; whole body identical except the 3 sites n_alSynSetVol(.., __n_vsVol(vs,seqp), ..) (cases 6, 22, 10): target 'sll s0,v0,16; sra s0,s0,16; move a1,s0', IDO 5.3 -g always emits 'sll s0,v0,16; sra t,s0,16; move s0,t' (+4 bytes each, tried s16/s32 return, casts, K&R, register var). Needs msg union GcEvent (u16 type); locals declared in order seqp,evt,voice,delta,vs,oscState,oscValue,chan,unused,cmdA,cmdB
#include "common.h"

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
    /* 0x38 */ u8 pad38[8];
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

void n_alCSeqNextEvent(ALCSeq *, ALEvent *, s32);
void __n_csqRepostEvent();
void n_alCSPStop();
void n_alCSPSetBank();
s16 __n_vsVol(GcVoiceState *, GcCSPlayer *);
s32 __n_vsDelta(GcVoiceState *, s32);
void n_alSynSetVol(ALVoice *, s16, s32);
void n_alSynSetFXMix(ALVoice *, u8);
void n_alSynSetPan(ALVoice *, f32);
f32 func_8073BDC4(s32);

void __n_csqHandleMIDIMsg(GcCSPlayer *);
void __n_seqpStopOsc(GcCSPlayer *, GcVoiceState *);
void __n_unmapVoice(GcCSPlayer *, ALVoice *);
s32 __n_voiceNeedsNoteKill(GcCSPlayer *, ALVoice *, s32);
void __n_seqpReleaseVoice(GcCSPlayer *, ALVoice *, s32);
void __n_initFromBank(GcCSPlayer *, ALBank *);
void n_alSynStopVoice(ALVoice *);
void n_alSynFreeVoice(ALVoice *);
void n_alSynSetPitch(ALVoice *, f32);
u8 func_8073A7B8(GcVoiceState *, GcCSPlayer *);
void func_8073C820(ALVoice *, u8);
void *func_8073C8D0(u8);
void func_8073C9C0(void *, s32, void *);
void *func_8073C948(u8);
void func_8073CA04(void *, u8, void *);

ALMicroTime __n_csqVoiceHandler(void *node) {
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
                __n_csqHandleMIDIMsg(seqp);
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
                    n_alSynSetPan(&vs->voice, 440.0f * func_8073BDC4(vs->key - vs->sound->keyMap->keyBase) * seqp->chanState[chan].pitchBend * vs->vibrato);
                }
                evt.type = 0x17;
                evt.msg.osc.vs = (ALVoiceState *)vs;
                evt.msg.osc.oscState = oscState;
                evt.msg.osc.chan = chan;
                alEvtqPostEvent(&seqp->evtq, &evt, delta);
                break;
            case 2:
            case 21:
                __n_csqRepostEvent(seqp, &seqp->nextEvent);
                break;
            case 7:
                n_alCSPSetBank(seqp, &seqp->nextEvent);
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
                    func_8073C820(&vs->voice, func_8073A7B8(vs, seqp));
                }
                break;
            case 25:
                if (seqp->nextEvent.msg.cmd.b1 < 8) {
                    cmdA = func_8073C8D0(seqp->nextEvent.msg.cmd.b0);
                    if (cmdA != NULL) {
                        func_8073C9C0(cmdA, (seqp->nextEvent.msg.cmd.b2 << 3) | (seqp->nextEvent.msg.cmd.b1 & 7), &seqp->nextEvent.msg.cmd.w4);
                    }
                } else {
                    cmdB = func_8073C948(seqp->nextEvent.msg.cmd.b0);
                    if (cmdB != NULL) {
                        func_8073CA04(cmdB, seqp->nextEvent.msg.cmd.b1, &seqp->nextEvent.msg.cmd.w4);
                    }
                }
                break;
            case 15:
                if (seqp->state != 1) {
                    seqp->state = 1;
                    n_alCSPStop(seqp);
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

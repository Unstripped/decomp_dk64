// __n_csqRepostEvent (src/global/137C10.c): stage 6 (real __CSPHandleMIDIMsg, whole function ok incl. 0x90/0x80/0xA0/0xD0/0xB0 ctl switch/0xC0/0xE0): same frame 0xD0, s0/s1/f20; only diffs vs target: 2x in-place 'sll s1,v0,16; sra s1,s1,16' (IDO5.3 gives sll s1; sra t; move s1,t) for n_alSynSetVol(...,__n_vsVol(),__n_vsDelta()) in cases 0xA0/0xD0, and in-place mul a2,a2,100 (move at,a2;sll a2,at,2..) for uspt*100 in case 0xFE; jump-table reloc symbols only
#include "common.h"

typedef struct GdVoiceState_s {
    /* 0x00 */ struct GdVoiceState_s *next;
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
} GdVoiceState;

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
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ void *drvr;
    /* 0x18 */ ALCSeq *target;
    /* 0x1C */ s32 curTime;
    /* 0x20 */ ALBank *bank;
    /* 0x24 */ s32 uspt;
    /* 0x28 */ s32 nextDelta;
    /* 0x2C */ s32 state;
    /* 0x30 */ u16 chanMask;
    /* 0x32 */ s16 vol;
    /* 0x34 */ u8 maxChannels;
    /* 0x35 */ u8 debugFlags;
    /* 0x38 */ ALEvent nextEvent;
    /* 0x48 */ ALEventQueue evtq;
    /* 0x5C */ s32 frameTime;
    /* 0x60 */ GdChanState *chanState;
    /* 0x64 */ GdVoiceState *vAllocHead;
    /* 0x68 */ GdVoiceState *vAllocTail;
    /* 0x6C */ GdVoiceState *vFreeList;
    /* 0x70 */ GdOscInit initOsc;
    /* 0x74 */ void *updateOsc;
    /* 0x78 */ void *stopOsc;
    /* 0x7C */ u8 pad7C[8];
    /* 0x84 */ OSMesgQueue *msgq;
    /* 0x88 */ u8 unk88;
} GdCSPlayer;

typedef struct {
    u8 pad00[0x3C];
    s32 unk3C;
} GdBankInfo;

extern GdBankInfo *D_807563E4;
extern s32 D_807FF040[];

void __n_csqHandleMetaMsg();
void __n_csqPostNextSeqEvent();
ALSound *__n_lookupSoundQuick(GdCSPlayer *seqp, u8 key, u8 vel, u8 chan);
GdVoiceState *__n_mapVoice(GdCSPlayer *seqp, u8 key, u8 vel, u8 chan);
GdVoiceState *__n_lookupVoice(GdCSPlayer *seqp, u8 key, u8 chan);
void __n_seqpReleaseVoice(GdCSPlayer *seqp, ALVoice *voice, s32 deltaTime);
void __n_setInstChanState(GdCSPlayer *seqp, ALInstrument *inst, u8 chan);
s32 __n_vsDelta(GdVoiceState *vs, s32 curTime);
u8 __n_vsPan(GdVoiceState *vs, GdCSPlayer *seqp);
s16 __n_vsVol(GdVoiceState *vs, GdCSPlayer *seqp);
u8 func_8073A7B8(GdVoiceState *vs, GdCSPlayer *seqp);
f32 func_8073BDC4(s32 cents);
void func_8073C820(ALVoice *voice, u8 arg);
void func_8073CF00(ALVoice *voice, u8 arg);
void func_8073CFB0(ALVoice *voice, u8 arg);
void n_alSynAllocVoice(ALVoice *voice, ALVoiceConfig *config);
void n_alSynSetPan(ALVoice *voice, f32 pan);
void n_alSynSetPitch(ALVoice *voice, f32 pitch);
void n_alSynSetVol(ALVoice *voice, s16 vol, s32 delta);
void n_alSynStartVoiceParams(ALVoice *voice, ALWaveTable *w, f32 pitch, s16 vol, u8 pan, u8 fxmix, u8 unityPitch, f32 arg7, u8 arg8, s32 arg9);

void __n_csqRepostEvent(GdCSPlayer *seqp, ALEvent *event) {
    ALVoice *voice;
    GdVoiceState *vs;
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
    GdVoiceState *voiceState;
    u8 pan;
    GdChanState *chanSt;
    s32 sp90;
    ALVoiceConfig vc;
    ALSound *sound;
    s16 cents;
    f32 pitch;
    f32 oscVal;
    u8 fxmix;
    u8 unityPitch;
    f32 sp70;
    void *oscState;
    ALInstrument *inst;
    u8 sp67;
    u8 sp66;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    f32 sp54;
    s32 sp50;

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
                } else {
                    chanSt = &seqp->chanState[chan];
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
                        sp90 = chanSt->unk28;
                    } else {
                        inst = seqp->chanState[chan].instrument;
                        sp90 = inst->tremType;
                    }
                    oscVal = 127.0f;
                    if (sp90 != 0 && seqp->initOsc != NULL) {
                        if (chanSt->unk24 != 0) {
                            delta = seqp->initOsc(&oscState, &oscVal, chanSt->unk28, chanSt->unk29, chanSt->unk2A, chanSt->unk2B, chanSt->unk31);
                        } else {
                            delta = seqp->initOsc(&oscState, &oscVal, inst->tremType, inst->tremRate, inst->tremDepth, inst->tremDelay, chanSt->unk31);
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
                        sp90 = chanSt->unk2C;
                    } else {
                        sp90 = inst->vibType;
                    }
                    if (sp90 != 0 && seqp->initOsc != NULL) {
                        if (chanSt->unk24 != 0) {
                            delta = seqp->initOsc(&oscState, &oscVal, chanSt->unk2C, chanSt->unk2D, chanSt->unk2E, chanSt->unk2F, chanSt->unk31);
                        } else {
                            delta = seqp->initOsc(&oscState, &oscVal, inst->vibType, inst->vibRate, inst->vibDepth, inst->vibDelay, chanSt->unk31);
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
                    fxmix = func_8073A7B8(voiceState, seqp);
                    unityPitch = chanSt->unk11;
                    if (unityPitch != 0) {
                        sp70 = func_8073BDC4(((cents / 100) + chanSt->unk12) - 0x40) * 440.0f * chanSt->pitchBend;
                    } else {
                        sp70 = 127.0f;
                    }
                    pan = __n_vsPan(voiceState, seqp);
                    vol = __n_vsVol(voiceState, seqp);
                    if (chanSt->unk24 != 0) {
                        delta = chanSt->unk18;
                    } else {
                        delta = sound->envelope->attackTime;
                    }
                    n_alSynStartVoiceParams(voice, sound->wavetable, pitch, vol, pan, fxmix, unityPitch, sp70, chanSt->unk13, delta);
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
                    if ((chanSt->unk10 & 1) && seqp->msgq != NULL) {
                        osSendMesg(seqp->msgq, (OSMesg)((D_807FF040[chan] & ~0xFF) | (chanSt->unk10 >> 2)), 0);
                    }
                }
                break;
            }
        case 0x80:
            voiceState = __n_lookupVoice(seqp, key, chan);
            if (voiceState == NULL) {
                return;
            }
            chanSt = &seqp->chanState[chan];
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
            if ((chanSt->unk10 & 2) && seqp->msgq != NULL) {
                osSendMesg(seqp->msgq, (OSMesg)((key << 16) | 8 | (chanSt->unk10 >> 2)), 0);
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
                    seqp->chanState[chan].pan = byte2;
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan) {
                            pan = __n_vsPan(vs, seqp);
                            func_8073CF00(&vs->voice, pan);
                        }
                    }
                    break;
                case 0xFD:
                    seqp->chanState[chan].unk0F = byte2;
                    break;
                case 0xFF:
                    if (seqp->chanState[chan].unk0F == 0) {
                        seqp->chanState[chan].unk0F = 0x90;
                    }
                    if (seqp->chanState[chan].unk0E != byte2) {
                        if (seqp->chanState[chan].unk0E == seqp->chanState[chan].unk0D) {
                            seqp->chanState[chan].unk0E = byte2;
                        } else {
                            seqp->chanState[chan].unk0E = byte2;
                            break;
                        }
                    } else {
                        break;
                    }
                    midi->byte1 = 0xFE;
                case 0xFE:
                    sp67 = seqp->chanState[chan].unk0D;
                    sp66 = seqp->chanState[chan].unk0E;
                    vel = seqp->chanState[chan].unk0F;
                    sp60 = sp66 - sp67;
                    if (sp60 > 0) {
                        if (vel & 0x80) {
                            vel = (vel & 0x7F) << 1;
                        }
                        if (sp60 > vel) {
                            sp60 = vel;
                        }
                    } else {
                        vel &= 0x7F;
                        if (sp60 < -vel) {
                            sp60 = -vel;
                        }
                    }
                    sp67 += sp60;
                    seqp->chanState[chan].unk0D = sp67;
                    if (sp67 != sp66) {
                        alEvtqPostEvent(&seqp->evtq, event, seqp->uspt * 100);
                    }
                    if (sp67 != 0) {
                        seqp->chanMask |= 1 << chan;
                    } else {
                        seqp->chanMask &= ~(1 << chan);
                    }
                    __n_csqHandleMetaMsg(seqp, chan);
                    break;
                case 0xFC:
                    seqp->chanState[chan].unk0D = byte2;
                    seqp->chanState[chan].unk0E = byte2;
                    if (byte2 == 0) {
                        seqp->chanMask = seqp->chanMask & ((1 << chan) ^ 0xFFFF);
                    } else {
                        seqp->chanMask |= 1 << chan;
                    }
                    __n_csqHandleMetaMsg(seqp, chan);
                    break;
                case 0x21:
                    seqp->chanState[chan].unk11 = byte2;
                    __n_csqPostNextSeqEvent(seqp, chan);
                    break;
                case 0x22:
                    seqp->chanState[chan].unk12 = byte2;
                    __n_csqPostNextSeqEvent(seqp, chan);
                    break;
                case 0x23:
                    seqp->chanState[chan].unk13 = byte2;
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan) {
                            func_8073CFB0(&vs->voice, byte2);
                        }
                    }
                    break;
                case 0x1E:
                    if (seqp->msgq != NULL) {
                        osSendMesg(seqp->msgq, (OSMesg)(((byte2 & 7) | 0x10) | ((seqp->unk10 << 5) & ~0xFF)), 0);
                    }
                    break;
                case 0x7:
                    seqp->chanState[chan].vol = byte2;
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan && vs->envPhase != 3) {
                            vol = __n_vsVol(vs, seqp);
                            n_alSynSetVol(&vs->voice, vol, __n_vsDelta(vs, seqp->curTime));
                        }
                    }
                    break;
                case 0x10:
                    seqp->chanState[chan].priority = byte2;
                    break;
                case 0x40:
                    seqp->chanState[chan].sustain = byte2;
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
                                    __n_seqpReleaseVoice(seqp, &vs->voice, (seqp->chanState[chan].unk20 < 0x3E80) ? 0x3E80 : seqp->chanState[chan].unk20);
                                } else {
                                    __n_seqpReleaseVoice(seqp, &vs->voice, (voiceState->sound->envelope->releaseTime < 0x3E80) ? 0x3E80 : voiceState->sound->envelope->releaseTime);
                                }
                            }
                        }
                    }
                    break;
                case 0x5B:
                    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x80) | byte2;
                    byte2 = seqp->chanState[chan].fxmix >> 7;
                case 0x41:
                    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x7F) | (byte2 << 7);
                    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                        if (vs->channel == chan) {
                            func_8073C820(&vs->voice, seqp->chanState[chan].fxmix);
                        }
                    }
                    break;
                case 0x5C:
                    if (byte2 < D_807563E4->unk3C && byte2 >= 0) {
                        seqp->chanState[chan].unk0B = byte2;
                    }
                    break;
                case 0x1A:
                    break;
                case 0x20:
                    seqp->chanState[chan].unk32 = byte2;
                    break;
                default:
                    break;
            }
            break;
        case 0xC0:
            sp90 = (seqp->chanState[chan].unk32 << 7) + key;
            if (sp90 < seqp->bank->instCount) {
                sp5C = (s32)seqp->bank->instArray[sp90];
                __n_setInstChanState(seqp, (ALInstrument *)sp5C, chan);
            } else {
            }
            break;
        case 0xE0:
            sp58 = ((byte2 << 7) + byte1) - 0x2000;
            sp50 = (seqp->chanState[chan].bendRange * sp58) / 8192;
            sp54 = alCents2Ratio(sp50);
            seqp->chanState[chan].pitchBend = sp54;
            for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
                if (vs->channel == chan) {
                    n_alSynSetPitch(&vs->voice, vs->pitch * sp54 * vs->vibrato);
                    if (seqp->chanState[chan].unk11 != 0) {
                        n_alSynSetPan(&vs->voice, func_8073BDC4(vs->key - vs->sound->keyMap->keyBase) * 440.0f * sp54 * vs->vibrato);
                    }
                }
            }
            break;
        default:
            break;
    }
}

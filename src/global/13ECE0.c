#include "common.h"

typedef struct VoiceMapVoiceState {
    struct VoiceMapVoiceState *next;
    ALVoice voice;
    ALSound *sound;
    s32 envEndTime;
    f32 pitch;
    f32 vibrato;
    u8 envGain;
    u8 channel;
    u8 key;
    u8 velocity;
    u8 envPhase;
    u8 phase;
    u8 tremelo;
    u8 flags;
    void *tremOsc;
    void *vibOsc;
} VoiceMapVoiceState;

typedef struct {
    ALInstrument *instrument;
    s16 bendRange;
    u8 fxId;
    u8 pan;
    u8 priority;
    u8 vol;
    u8 fxmix;
    u8 unk0B;
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 unk0F;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 pitchBend;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    s8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 pad30;
    u8 unk31;
    u8 unk32;
    u8 pad33;
} VoiceMapChanState;

typedef struct {
    u8 unk[0x10];
    ALSound **soundArray;
} VoiceMapInstrument;

typedef struct {
    ALPlayer node;
    ALSynth *drvr;
    ALCSeq *target;
    ALMicroTime curTime;
    ALBank *bank;
    s32 uspt;
    s32 nextDelta;
    s32 state;
    u16 chanMask;
    s16 vol;
    u8 maxChannels;
    u8 debugFlags;
    ALEvent nextEvent;
    ALEventQueue evtq;
    ALMicroTime frameTime;
    VoiceMapChanState *chanState;
    VoiceMapVoiceState *vAllocHead;
    VoiceMapVoiceState *vAllocTail;
    VoiceMapVoiceState *vFreeList;
    ALOscInit initOsc;
    ALOscUpdate updateOsc;
    ALOscStop stopOsc;
    f32 unk7C;
    f32 unk80;
    s32 unk84;
    u8 unk88;
    u8 unk89;
} VoiceMapCSPlayer;


f32 alCents2Ratio(s32 cents) {
    f32 pow;
    f32 ratio;

    ratio = 1.0f;
    if (cents >= 0) {
        pow = 1.0005778f;
    } else {
        pow = 0.99942255f;
        cents = -cents;
    }
    if (cents != 0) {
        do {
            if (cents & 1) {
                ratio *= pow;
            }
            pow *= pow;
            cents = cents >> 1;
        } while (cents != 0);
    }
    return ratio;
}

void __n_unmapVoice(VoiceMapCSPlayer *seqp, ALVoice *voice) {
    VoiceMapVoiceState *prev;
    VoiceMapVoiceState *vs;

    prev = NULL;
    vs = seqp->vAllocHead;
    if (vs != NULL) {
        do {
            if (&vs->voice == voice) {
                if (prev != NULL) {
                    prev->next = vs->next;
                } else {
                    seqp->vAllocHead = vs->next;
                }
                if (seqp->vAllocTail == vs) {
                    seqp->vAllocTail = prev;
                }
                vs->next = seqp->vFreeList;
                seqp->vFreeList = vs;
                seqp->unk89 = seqp->unk89 - 1;
                return;
            }
            prev = vs;
        } while ((vs = vs->next) != NULL);
    }
}

void __n_seqpReleaseVoice(VoiceMapCSPlayer *seqp, ALVoice *voice, s32 delta) {
    ALEvent evt;
    ALVoiceState *vs;
    ALEventListItem *item;
    ALEventListItem *next;
    ALEventListItem *volatile current;
    ALEventListItem *nextItem;

    vs = voice->clientPrivate;
    if (vs->envPhase == 0) {
        item = (ALEventListItem *)seqp->evtq.allocList.next;
        if (item != NULL) {
            do {
                next = (ALEventListItem *)item->node.next;
                current = item;
                nextItem = next;
                if ((current->evt.type == 6) && (current->evt.msg.osc.vs == (ALVoiceState *)voice)) {
                    if (nextItem != NULL) {
                        nextItem->delta = nextItem->delta + current->delta;
                    }
                    alUnlink(&item->node);
                    alLink(&item->node, &seqp->evtq.freeList);
                }
                item = next;
            } while (item != NULL);
        }
    }
        vs->velocity = 0;
        vs->envPhase = 3;
        vs->envGain = 0;
        vs->envEndTime = seqp->curTime + delta;
        n_alSynSetPriority(voice, 0);
        n_alSynSetVol(voice, 0, delta);
        evt.type = 5;
        evt.msg.osc.vs = (ALVoiceState *)voice;
        delta = delta + 0x7D00;
        alEvtqPostEvent(&seqp->evtq, &evt, delta);
}

u8 __n_voiceNeedsNoteKill(VoiceMapCSPlayer *seqp, ALVoice *voice, s32 delta) {
    ALEventListItem *item;
    ALEventListItem *next;
    ALEventListItem *volatile current;
    s32 elapsed;
    u8 result;

    elapsed = 0;
    result = 1;
    item = (ALEventListItem *)seqp->evtq.allocList.next;
    if (item != NULL) {
        do {
            next = (ALEventListItem *)item->node.next;
            current = item;
            elapsed += current->delta;
            if ((current->evt.type == 5) && (current->evt.msg.osc.vs == (ALVoiceState *)voice)) {
                if (elapsed > delta) {
                    if (next != NULL) {
                        next->delta = next->delta + current->delta;
                    }
                    alUnlink(&item->node);
                    alLink(&item->node, &seqp->evtq.freeList);
                } else {
                    result = 0;
                }
                break;
            }
            item = next;
        } while (item != NULL);
    }
    return result;
}

VoiceMapVoiceState *__n_mapVoice(VoiceMapCSPlayer *seqp, u8 key, u8 velocity, u8 chan) {
    VoiceMapVoiceState *vs;

    vs = seqp->vFreeList;
    if (seqp->unk89 > seqp->unk88) {
        return NULL;
    }
    if (vs != NULL) {
        seqp->vFreeList = vs->next;
        vs->next = NULL;
        if (seqp->vAllocHead == NULL) {
            seqp->vAllocHead = vs;
        } else {
            seqp->vAllocTail->next = vs;
        }
        seqp->vAllocTail = vs;
        vs->channel = chan;
        vs->key = key;
        vs->velocity = velocity;
        vs->voice.clientPrivate = vs;
        seqp->unk89 = seqp->unk89 + 1;
    }
    return vs;
}

VoiceMapVoiceState *__n_lookupVoice(VoiceMapCSPlayer *seqp, u8 key, u8 chan) {
    VoiceMapVoiceState *vs;

    vs = seqp->vAllocHead;
    if (vs != NULL) {
        do {
            if ((vs->key == key) && (vs->channel == chan) && (vs->phase != 3) && (vs->phase != 4)) {
                return vs;
            }
            vs = vs->next;
        } while (vs != NULL);
    }
    return NULL;
}

typedef struct {
    u8 pad[0xC];
    ALSound *soundArray[];
} VoiceNMLookupInstrument;

ALSound *__n_lookupSoundQuick(VoiceMapCSPlayer *seqp, u8 key, u8 velocity, u8 chan) {
    ALInstrument *inst;
    s32 min;
    s32 max;
    s32 mid;
    ALKeyMap *keyMap;

    inst = seqp->chanState[chan].instrument;
    min = 1;
    max = inst->soundCount;
    while (max >= min) {
        mid = (min + max) / 2;
        keyMap = ((VoiceNMLookupInstrument *)inst)->soundArray[mid]->keyMap;
        if ((key >= keyMap->keyMin) && (keyMap->keyMax >= key)
            && (velocity >= keyMap->velocityMin) && (keyMap->velocityMax >= velocity)) {
            return ((VoiceNMLookupInstrument *)inst)->soundArray[mid];
        } else {
            if ((key < keyMap->keyMin)
                || ((velocity < keyMap->velocityMin) && (key <= keyMap->keyMax))) {
                max = mid - 1;
            } else {
                min = mid + 1;
            }
        }
    }
    return NULL;
}

s16 __n_vsVol(VoiceMapVoiceState *vs, VoiceMapCSPlayer *seqp) {
    s32 vol;
    s32 chanVol;

    vol = (vs->tremelo * vs->velocity * vs->envGain) >> 6;
    chanVol = (seqp->chanState[vs->channel].vol * (vs->sound->sampleVolume * seqp->vol)) >> 14;
    if (seqp->chanState[vs->channel].unk0D != 0xFF) {
        chanVol = (u32)((seqp->chanState[vs->channel].unk0D * chanVol) + 1) >> 8;
    }
    vol *= chanVol;
    vol = (u32)vol >> 15;
    return (s16)vol;
}


u8 func_8073A7B8(VoiceMapVoiceState *vs, VoiceMapCSPlayer *seqp) {
    s32 flags;
    s32 mix;
    f32 unused;

    flags = seqp->chanState[vs->channel].fxmix & 0x80;
    mix = (s32)(((s32)(seqp->unk7C * 127.0f) + (seqp->chanState[vs->channel].fxmix & 0x7F)) * seqp->unk80);
    return ((mix > 0x7F ? 0x7F : mix) < 0 ? 0 : (mix > 0x7F ? 0x7F : mix)) | flags;
}

s32 __n_vsDelta(VoiceMapVoiceState *vs, s32 time) {
    s32 delta;

    delta = vs->envEndTime - time;
    if (delta >= 0) {
        return delta;
    } else {
        return 1000;
    }
}

u8 __n_vsPan(VoiceMapVoiceState *vs, VoiceMapCSPlayer *seqp) {
    s32 pan;

    pan = (seqp->chanState[vs->channel].pan + vs->sound->samplePan) - 0x40;
    if (pan > 0) {
    } else {
        pan = 0;
    }
    if (pan < 0x7F) {
    } else {
        pan = 0x7F;
    }
    return pan;
}

void __n_resetPerfChanState(VoiceMapCSPlayer *seqp, s32 chan);
void __n_setInstChanState(VoiceMapCSPlayer *seqp, ALInstrument *inst, s32 chan);

#pragma GLOBAL_ASM("asm/global/nonmatchings/13ECE0/__n_initFromBank.s")

void __n_initChanState(VoiceMapCSPlayer *seqp) {
    s32 chan;

    if ((chan = 0, seqp->maxChannels > 0)) {
        do {
            seqp->chanState[chan].instrument = NULL;
            __n_resetPerfChanState(seqp, chan);
        } while (++chan < seqp->maxChannels);
    }
}

void __n_resetPerfChanState(VoiceMapCSPlayer *seqp, s32 chan) {
    seqp->chanState[chan].fxId = 0;
    seqp->chanState[chan].fxmix = 0;
    seqp->chanState[chan].pan = 0x40;
    seqp->chanState[chan].vol = 0x7F;
    seqp->chanState[chan].priority = 5;
    seqp->chanState[chan].unk0C = 0;
    seqp->chanState[chan].bendRange = 0xC8;
    seqp->chanState[chan].pitchBend = 1.0f;
    seqp->chanState[chan].unk10 = 0;
    seqp->chanState[chan].unk0D = 0xFF;
    seqp->chanState[chan].unk0E = 0xFF;
    seqp->chanState[chan].unk0F = 0;
    seqp->chanState[chan].unk0B = 0;
    seqp->chanState[chan].unk13 = 0;
    seqp->chanState[chan].unk12 = 0;
    seqp->chanState[chan].unk11 = 0;
    seqp->chanState[chan].unk32 = 0;
}

void __n_setInstChanState(VoiceMapCSPlayer *seqp, ALInstrument *inst, s32 chan) {
    ALSound **sounds;

    seqp->chanState[chan].instrument = inst;
    seqp->chanState[chan].pan = inst->pan;
    seqp->chanState[chan].vol = inst->volume;
    seqp->chanState[chan].priority = inst->priority;
    seqp->chanState[chan].bendRange = inst->bendRange;
    if (inst->soundCount == 0) {
        return;
    }
    sounds = ((VoiceMapInstrument *)inst)->soundArray;
    seqp->chanState[chan].unk18 = (s32)(*sounds)->envelope;
    seqp->chanState[chan].unk1C = (s32)(*sounds)->keyMap;
    seqp->chanState[chan].unk20 = (s32)(*sounds)->wavetable;
    seqp->chanState[chan].unk25 = (*sounds)->samplePan;
    seqp->chanState[chan].unk26 = (*sounds)->sampleVolume;
    seqp->chanState[chan].unk27 = 0;
    seqp->chanState[chan].unk28 = inst->tremType;
    seqp->chanState[chan].unk29 = inst->tremRate;
    seqp->chanState[chan].unk2A = inst->tremDepth;
    seqp->chanState[chan].unk2B = inst->tremDelay;
    seqp->chanState[chan].unk2C = inst->vibType;
    seqp->chanState[chan].unk2D = inst->vibRate;
    seqp->chanState[chan].unk2E = inst->vibDepth;
    seqp->chanState[chan].unk2F = inst->vibDelay;
    seqp->chanState[chan].unk24 = 0;
    seqp->chanState[chan].unk31 = 0;
}

void __n_seqpStopOsc(VoiceMapCSPlayer *seqp, VoiceMapVoiceState *vs) {
    ALEventListItem *item;
    ALEventListItem *next;
    s16 type;

    item = (ALEventListItem *)seqp->evtq.allocList.next;
    if (item != NULL) {
        do {
            next = (ALEventListItem *)item->node.next;
            type = item->evt.type;
            if (((type == 0x16) || (type == 0x17)) && (item->evt.msg.osc.vs == (ALVoiceState *)vs)) {
                seqp->stopOsc(item->evt.msg.osc.oscState);
                alUnlink(&item->node);
                if (next != NULL) {
                    next->delta = next->delta + item->delta;
                }
                alLink(&item->node, &seqp->evtq.freeList);
                if (type == 0x16) {
                    vs->flags = vs->flags & 0xFE;
                } else {
                    vs->flags = vs->flags & 0xFD;
                }
                if (vs->flags == 0) {
                    return;
                }
            }
            item = next;
        } while (item != NULL);
    }
}

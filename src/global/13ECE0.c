#include "common.h"
#include "seqplayer.h"
#include "proto/global/13E0E0.h"
#include "proto/global/13ECE0.h"
#include "proto/global/13FED0.h"
#include "proto/global/140530.h"
#include "proto/global/1435A0.h"

typedef struct {
    u8 unk[0x10];
    ALSound **soundArray;
} VoiceMapInstrument;

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
    while (cents != 0) {
        if (cents & 1) {
            ratio *= pow;
        }
        pow *= pow;
        cents >>= 1;
    }
    return ratio;
}

void __n_unmapVoice(N_CSPlayer *seqp, ALVoice *voice) {
    N_VoiceState *prev;
    N_VoiceState *vs;

    prev = NULL;
    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
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
            seqp->unk89--;
            return;
        }
        prev = vs;
    }
}

void __n_seqpReleaseVoice(N_CSPlayer *seqp, ALVoice *voice, s32 delta) {
    ALEvent evt;
    ALVoiceState *vs;
    ALEventListItem *item;
    ALEventListItem *next;
    ALEventListItem *current;
    ALEventListItem *nextItem;

    vs = voice->clientPrivate;
    if (vs->envPhase == 0) {
        item = (ALEventListItem *)seqp->evtq.allocList.next;
        while (item != NULL) {
            next = (ALEventListItem *)item->node.next;
            current = item;
            nextItem = next;
            if (current->evt.type == 6) {
                if (current->evt.msg.osc.vs == (ALVoiceState *)voice) {
                    if (nextItem != NULL) {
                        nextItem->delta += current->delta;
                    }
                    alUnlink(&item->node);
                    alLink(&item->node, &seqp->evtq.freeList);
                }
            }
            item = next;
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
    delta += 0x7D00;
    alEvtqPostEvent(&seqp->evtq, &evt, delta);
}

u8 __n_voiceNeedsNoteKill(N_CSPlayer *seqp, ALVoice *voice, s32 delta) {
    ALEventListItem *item;
    ALEventListItem *next;
    ALEventListItem *current;
    s32 elapsed;
    u8 result;

    elapsed = 0;
    result = 1;
    item = (ALEventListItem *)seqp->evtq.allocList.next;
    while (item != NULL) {
        next = (ALEventListItem *)item->node.next;
        current = item;
        elapsed += current->delta;
        if (current->evt.type == 5) {
            if (current->evt.msg.osc.vs == (ALVoiceState *)voice) {
                if (elapsed > delta) {
                    if (next != NULL) {
                        next->delta += current->delta;
                    }
                    alUnlink(&item->node);
                    alLink(&item->node, &seqp->evtq.freeList);
                } else {
                    result = 0;
                }
                break;
            }
        }
        item = next;
    }
    return result;
}

N_VoiceState *__n_mapVoice(N_CSPlayer *seqp, u8 key, u8 velocity, u8 chan) {
    N_VoiceState *vs;

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
        seqp->unk89++;
    }
    return vs;
}

N_VoiceState *__n_lookupVoice(N_CSPlayer *seqp, u8 key, u8 chan) {
    N_VoiceState *vs;

    vs = seqp->vAllocHead;
    while (vs != NULL) {
        if ((vs->key == key) && (vs->channel == chan) && (vs->phase != 3) && (vs->phase != 4)) {
            return vs;
        }
        vs = vs->next;
    }
    return NULL;
}

ALSound *__n_lookupSoundQuick(N_CSPlayer *seqp, u8 key, u8 velocity, u8 chan) {
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
        keyMap = inst->soundArray[mid - 1]->keyMap;
        if ((key >= keyMap->keyMin) && (keyMap->keyMax >= key)
            && (velocity >= keyMap->velocityMin) && (keyMap->velocityMax >= velocity)) {
            return inst->soundArray[mid - 1];
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

s16 __n_vsVol(N_VoiceState *vs, N_CSPlayer *seqp) {
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


u8 n_alCSPClampVoiceFXMix(N_VoiceState *vs, N_CSPlayer *seqp) {
    s32 flags;
    s32 mix;

    flags = seqp->chanState[vs->channel].fxmix & 0x80;
    mix = (s32)(((s32)(seqp->unk7C * 127.0f) + (seqp->chanState[vs->channel].fxmix & 0x7F)) * seqp->unk80);
    return ((mix > 0x7F ? 0x7F : mix) < 0 ? 0 : (mix > 0x7F ? 0x7F : mix)) | flags;
}

s32 __n_vsDelta(N_VoiceState *vs, s32 time) {
    s32 delta;

    delta = vs->envEndTime - time;
    if (delta >= 0) {
        return delta;
    } else {
        return 1000;
    }
}

u8 __n_vsPan(N_VoiceState *vs, N_CSPlayer *seqp) {
    s32 pan;

    pan = (seqp->chanState[vs->channel].pan + vs->sound->samplePan) - 0x40;
    pan = (pan > 0) ? pan : 0;
    pan = (pan < 0x7F) ? pan : 0x7F;
    return pan;
}


void __n_initFromBank(N_CSPlayer *seqp, ALBank *bank) {
    s32 chan;
    ALInstrument *inst;

    inst = NULL;
    for (chan = 0; inst == NULL; chan++) {
        inst = bank->instArray[chan];
    }
    for (chan = 0; chan < seqp->maxChannels; chan++) {
        __n_resetPerfChanState(seqp, chan);
        __n_setInstChanState(seqp, inst, chan);
    }
    if (bank->percussion != NULL) {
        __n_resetPerfChanState(seqp, chan);
        __n_setInstChanState(seqp, bank->percussion, 9);
    }
}

void __n_initChanState(N_CSPlayer *seqp) {
    s32 chan;

    for (chan = 0; chan < seqp->maxChannels; chan++) {
        seqp->chanState[chan].instrument = NULL;
        __n_resetPerfChanState(seqp, chan);
    }
}

void __n_resetPerfChanState(N_CSPlayer *seqp, s32 chan) {
    seqp->chanState[chan].fxId = 0;
    seqp->chanState[chan].fxmix = 0;
    seqp->chanState[chan].pan = 0x40;
    seqp->chanState[chan].vol = 0x7F;
    seqp->chanState[chan].priority = 5;
    seqp->chanState[chan].sustain = 0;
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

void __n_setInstChanState(N_CSPlayer *seqp, ALInstrument *inst, s32 chan) {
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

void __n_seqpStopOsc(N_CSPlayer *seqp, N_VoiceState *vs) {
    ALEventListItem *item;
    ALEventListItem *next;
    s16 type;

    item = (ALEventListItem *)seqp->evtq.allocList.next;
    while (item != NULL) {
        next = (ALEventListItem *)item->node.next;
        type = item->evt.type;
        if (((type == 0x16) || (type == 0x17)) && (item->evt.msg.osc.vs == (ALVoiceState *)vs)) {
            seqp->stopOsc(item->evt.msg.osc.oscState);
            alUnlink(&item->node);
            if (next != NULL) {
                next->delta += item->delta;
            }
            alLink(&item->node, &seqp->evtq.freeList);
            if (type == 0x16) {
                vs->flags &= 0xFE;
            } else {
                vs->flags &= 0xFD;
            }
            if (vs->flags == 0) {
                return;
            }
        }
        item = next;
    }
}

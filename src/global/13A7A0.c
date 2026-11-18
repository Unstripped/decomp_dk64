#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;

#include "common.h"
#include "audio_config.h"
#include "proto/global/13A7A0.h"
#include "proto/global/13FED0.h"
#include "proto/global/140530.h"
#include "proto/global/140600.h"
#include "proto/global/141520.h"
#include "proto/global/1417C0.h"
#include "proto/global/141AD0.h"
#include "proto/global/141C00.h"

extern s32 osGetIntMask(s32 unused);

// Sounds are libaudio ALSound/ALEnvelope/ALKeyMap. The game reuses the key map's MIDI range fields:
//   velocityMin  low byte of the next chained sound id
//   velocityMax  delay before the sound starts, in 33333 us steps
//   keyMin       bits 0-4: group volume index (gSndpGroupVol); bits 6-7 and 5: next id bits 8-9 and 10
//   keyMax       bits 0-3: fx mix boost (<< 3); bits 4-7: initial state flags
//   keyBase/detune: pitch, as in libaudio

typedef struct GfSndState {
    struct GfSndState *next;
    struct GfSndState *prev;
    ALSound *sound;
    ALVoice voice;
    f32 pitchRatio;
    f32 pitch;
    struct GfSndState **handle;
    s32 retries;
    s16 vol;
    s16 envVol;
    s32 endTime;
    u8 priority;
    u8 pan;
    u8 fxMix;
    u8 flags;
    u8 state;
} GfSndState;

typedef struct GeSndEvt {
    u16 type;
    struct GfSndState *state;
    union {
        s32 i;
        f32 f;
    } arg8;
    void *arg12;
} GeSndEvt;

typedef struct {
    ALPlayer node;
    ALEventQueue evtq;
    ALEvent nextEvent;
    s32 nextEventPad;
    struct GfSndState *target; // the state n_alSndpPlay last started
    GfSndState *sndState;
    s32 maxVoices; // voices the player may hold at once (gSndpVoiceCount counts them)
    ALMicroTime frameTime;
    ALMicroTime nextDelta;
    ALMicroTime curTime;
} GeSndp;

extern GeSndp D_807FF080;

GfSndState *gSndpUsedHead = NULL;
GfSndState *gSndpUsedTail = NULL;
GfSndState *gSndpFreeList = NULL;
GeSndp *gSndp = &D_807FF080;
s16 gSndpVoiceCount = 0;

extern s16 *gSndpGroupVol;

void n_alSndpNew(GeSndpConfig *c) {
    u32 i;
    void *ptr;
    ALEvent evt;

    gSndp->maxVoices = c->maxVoices;
    gSndp->target = 0;
    gSndp->frameTime = 16000;
    ptr = alHeapDBAlloc(0, 0, c->heap, 1, c->maxSounds * 72);
    gSndp->sndState = ptr;
    ptr = alHeapDBAlloc(0, 0, c->heap, 1, c->maxEvents * 28);
    alEvtqNew(&gSndp->evtq, ptr, c->maxEvents);
    gSndpFreeList = gSndp->sndState;
    for (i = 1; i < c->maxSounds; i++) {
        GfSndState *sndState = gSndp->sndState;
        alLink((ALLink *)&sndState[i], (ALLink *)&sndState[i - 1]);
    }
    gSndpGroupVol = alHeapDBAlloc(0, 0, c->heap, 2, c->maxStates);
    for (i = 0; i < c->maxStates; i++) {
        gSndpGroupVol[i] = 0x7FFF;
    }
    gSndp->node.next = NULL;
    gSndp->node.handler = __n_sndpVoiceHandler;
    gSndp->node.clientData = gSndp;
    n_alSynAddSndPlayer(&gSndp->node);
    evt.type = 0x20;
    alEvtqPostEvent(&gSndp->evtq, &evt, gSndp->frameTime);
    gSndp->nextDelta = alEvtqNextEvent(&gSndp->evtq, &gSndp->nextEvent);
}

ALMicroTime __n_sndpVoiceHandler(void *node) {
    GeSndp *sndp = node;
    ALEvent evt;

    do {
        switch (sndp->nextEvent.type) {
            case 0x20:
                evt.type = 0x20;
                alEvtqPostEvent(&sndp->evtq, &evt, sndp->frameTime);
                break;
            default:
                __n_handleEvent((GeSndEvt *)&sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);
    } while (sndp->nextDelta == 0);
    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}

#define GE_STATE_VOL(st, km, snd) \
    (gSndpGroupVol[(km)->keyMin & 0x1F] * (((st)->envVol * (st)->vol * (snd)->sampleVolume) / 0x3F01) / 0x7FFF)
#define GE_CALC_VOL(dst, st, km, snd) \
    if (GE_STATE_VOL(st, km, snd) <= 0) { \
        dst = 0; \
    } else { \
        dst = GE_STATE_VOL(st, km, snd) - 1; \
    }
#define GE_CLAMP_PAN(dst, tmp) \
    dst = (((tmp) > 0 ? (tmp) : 0) < 0x7F) ? ((tmp) > 0 ? (tmp) : 0) : 0x7F
#define GE_CLAMP_FX(dst) \
    dst = ((((dst) < 0) ? 0 : (dst)) > 0x7F) ? 0x7F : (((dst) < 0) ? 0 : (dst))

void __n_handleEvent(GeSndEvt *event) {
    ALVoiceConfig config;
    ALSound *sound;
    ALKeyMap *keyMap;
    u8 pan;
    GeSndEvt evt2;
    GeSndEvt evt;
    s32 delta;
    s32 fx;
    s32 vol;
    s32 panTmp;
    s32 full;
    s32 mask;
    s32 done;
    s32 voice;
    GfSndState *state;
    GfSndState *nextState;
    u16 freeCount;
    u16 usedCount;

    done = 1;
    voice = 0;
    state = NULL;
    nextState = NULL;
    do {
        if (nextState) {
            evt.state = state;
            evt.type = event->type;
            evt.arg8.i = event->arg8.i;
            event = &evt;
        }
        state = event->state;
        sound = state->sound;
        if (sound == NULL) {
            n_alSndpCountStates(&freeCount, &usedCount);
            return;
        }
        keyMap = sound->keyMap;
        nextState = state->next;
        switch (event->type) {
            case 1:
                if (state->state != 5 && state->state != 4) {
                    return;
                }
                config.fxBus = 0;
                config.priority = state->priority;
                config.unityPitch = 0;
                full = gSndpVoiceCount >= gSndp->maxVoices;
                if (!full || (state->flags & 0x10)) {
                    voice = n_alSynAllocVoice(&state->voice, &config);
                }
                if (voice == 0) {
                    if ((state->flags & 0x12) || state->retries > 0) {
                        state->state = 4;
                        state->retries--;
                        alEvtqPostEvent(&gSndp->evtq, (ALEvent *)event, 0x8235);
                    } else if (full) {
                        GfSndState *iter;
                        GeSndEvt evt3;

                        iter = gSndpUsedTail;
                        do {
                            if (!(iter->flags & 0x12) && (iter->flags & 4) && iter->state != 3) {
                                full = 0;
                                evt3.type = 0x80;
                                evt3.state = iter;
                                iter->state = 3;
                                alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&evt3, 0x3E8);
                                n_alSynSetVol(&iter->voice, 0, 0x3E8);
                            }
                            iter = iter->prev;
                        } while (full && iter);
                        if (!full) {
                            state->retries = 2;
                            alEvtqPostEvent(&gSndp->evtq, (ALEvent *)event, 0x3E9);
                        } else {
                            __n_sndpDestroyState(state);
                        }
                    } else {
                        __n_sndpDestroyState(state);
                    }
                    return;
                }
                state->flags |= 4;
                state->envVol = sound->envelope->attackVolume;
                delta = sound->envelope->attackTime / state->pitch / state->pitchRatio;
                state->endTime = gSndp->curTime + delta;
                GE_CALC_VOL(vol, state, keyMap, sound)
                panTmp = state->pan + sound->samplePan - 0x40;
                GE_CLAMP_PAN(pan, panTmp);
                fx = (state->fxMix & 0x7F) + ((keyMap->keyMax & 0xF) << 3);
                GE_CLAMP_FX(fx);
                fx |= state->fxMix & 0x80;
                n_alSynStartVoiceParams(&state->voice, sound->wavetable, state->pitch * state->pitchRatio, vol, pan, fx, 0, 0.0f, 0, delta);
                state->state = 1;
                gSndpVoiceCount++;
                if (!(state->flags & 2)) {
                    if (delta == 0) {
                        state->envVol = sound->envelope->decayVolume;
                        GE_CALC_VOL(vol, state, keyMap, sound)
                        delta = sound->envelope->decayTime / state->pitchRatio / state->pitch;
                        state->endTime = gSndp->curTime + delta;
                        n_alSynSetVol(&state->voice, vol, delta);
                        evt2.type = 2;
                        evt2.state = state;
                        alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&evt2, delta);
                        if (state->flags & 0x20) {
                            __n_sndpPostPitch(state);
                        }
                    } else {
                        evt2.type = 0x40;
                        evt2.state = state;
                        delta = sound->envelope->attackTime / state->pitch / state->pitchRatio;
                        alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&evt2, delta);
                    }
                }
                break;
            case 2:
            case 0x400:
            case 0x1000:
                if (event->type != 0x1000 || (state->flags & 2)) {
                    switch (state->state) {
                        case 1:
                            __n_removeEvents(&gSndp->evtq, state, 0x40);
                            delta = sound->envelope->releaseTime / state->pitchRatio / state->pitch;
                            n_alSynSetVol(&state->voice, 0, delta);
                            if (delta != 0) {
                                evt2.type = 0x80;
                                evt2.state = state;
                                alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&evt2, delta);
                                state->state = 2;
                            } else {
                                __n_sndpDestroyState(state);
                            }
                            break;
                        case 4:
                        case 5:
                            __n_sndpDestroyState(state);
                            break;
                        default:
                            break;
                    }
                    if (event->type == 2) {
                        event->type = 0x1000;
                    }
                }
                break;
            case 4:
                state->pan = event->arg8.i;
                if (state->state == 1) {
                    panTmp = state->pan + sound->samplePan - 0x40;
                    GE_CLAMP_PAN(pan, panTmp);
                    n_alSynAllocVoicePriorityA(&state->voice, pan);
                }
                break;
            case 0x10:
                state->pitch = event->arg8.f;
                if (state->state == 1) {
                    n_alSynSetPitch(&state->voice, state->pitch * state->pitchRatio);
                    if (state->flags & 0x20) {
                        __n_sndpPostPitch(state);
                    }
                }
                break;
            case 0x100:
                state->fxMix = event->arg8.i;
                if (state->state == 1) {
                    fx = (state->fxMix & 0x7F) + ((keyMap->keyMax & 0xF) << 3);
                    GE_CLAMP_FX(fx);
                    fx |= state->fxMix & 0x80;
                    n_alSynSetVoiceUnkC(&state->voice, fx);
                }
                break;
            case 8:
                state->vol = event->arg8.i;
                if (state->state == 1) {
                    GE_CALC_VOL(vol, state, keyMap, sound)
                    n_alSynSetVol(&state->voice, vol,
                                  (state->endTime - gSndp->curTime < 0x3E8) ? 0x3E8 : state->endTime - gSndp->curTime);
                }
                break;
            case 0x800:
                if (state->state == 1) {
                    delta = sound->envelope->releaseTime / state->pitchRatio / state->pitch;
                    GE_CALC_VOL(vol, state, keyMap, sound)
                    n_alSynSetVol(&state->voice, vol, delta);
                }
                break;
            case 0x40:
                if (!(state->flags & 2)) {
                    state->envVol = sound->envelope->decayVolume;
                    GE_CALC_VOL(vol, state, keyMap, sound)
                    delta = sound->envelope->decayTime / state->pitchRatio / state->pitch;
                    state->endTime = gSndp->curTime + delta;
                    n_alSynSetVol(&state->voice, vol, delta);
                    evt2.type = 2;
                    evt2.state = state;
                    alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&evt2, delta);
                    if (state->flags & 0x20) {
                        __n_sndpPostPitch(state);
                    }
                }
                break;
            case 0x80:
                __n_sndpDestroyState(state);
                break;
            case 0x200:
                if (state->flags & 0x10) {
                    GfSndState *chained;

                    chained = n_alSndpPlay(event->arg12, event->arg8.i, state->vol, state->pan, state->pitch, state->fxMix, state->handle);
                }
                break;
            default:
                break;
        }
        mask = event->type & 0x2D1;
        if ((state = nextState) && !mask) {
            done = state->flags & 1;
        }
    } while (!done && state && !mask);
}

void __n_sndpDestroyState(GfSndState *state) {
    if (state->flags & 4) {
        n_alSynStopVoice(&state->voice);
        n_alSynFreeVoice(&state->voice);
    }
    __n_freeState(state);
    __n_removeEvents(&gSndp->evtq, state, 0xFFFF);
}

void __n_sndpPostPitch(GfSndState *state) {
    GeSndEvt ev;
    f32 pitch;

    pitch = alCents2Ratio(state->sound->keyMap->detune) * state->pitch;
    ev.type = 0x10;
    ev.state = state;
    ev.arg8.i = *(s32 *)&pitch; // ORIG: addiu t2,sp,0x1c (&pitch) at 0x15c8, lw t3,0(t2) at 0x15cc, sw t3,0x28(sp) at 0x15d0
    alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev, 33333);
}

void __n_removeEvents(ALEventQueue *evtq, GfSndState *state, u16 mask) {
    ALLink *thisNode;
    ALLink *nextNode;
    ALEventListItem *thisItem;
    ALEventListItem *nextItem;
    GeSndEvt *thisEvent;
    s32 intMask;

    intMask = osGetIntMask(1);
    thisNode = evtq->allocList.next;
    while (thisNode != NULL) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        thisEvent = (GeSndEvt *)&thisItem->evt;
        if (thisEvent->state == state && (thisEvent->type & mask)) {
            if (nextItem) {
                nextItem->delta += thisItem->delta;
            }
            alUnlink(thisNode);
            alLink(thisNode, (ALLink *)evtq);
        }
        thisNode = nextNode;
    }
    osGetIntMask(intMask);
}

u16 n_alSndpCountStates(u16 *outFree, u16 *outUsed) {
    u16 usedCount;
    u16 freeCount;
    u16 tailCount;
    GfSndState *usedNode = gSndpUsedHead;
    GfSndState *freeNode = gSndpFreeList;
    GfSndState *tailNode = gSndpUsedTail;

    for (usedCount = 0; usedNode; usedCount++, usedNode = usedNode->next) {
    }
    for (freeCount = 0; freeNode; freeCount++, freeNode = freeNode->next) {
    }
    for (tailCount = 0; tailNode; tailCount++, tailNode = tailNode->prev) {
    }
    *outFree = freeCount;
    *outUsed = usedCount;
    return tailCount;
}

GfSndState *__n_allocState(void *sndp, ALSound *sound) {
    GfSndState *state;
    ALKeyMap *km = sound->keyMap;
    s32 sustained;
    s32 intMask;

    intMask = osGetIntMask(1);
    state = gSndpFreeList;
    if (state) {
        gSndpFreeList = state->next;
        alUnlink((ALLink *)state);
        if (gSndpUsedHead) {
            state->next = gSndpUsedHead;
            state->prev = 0;
            gSndpUsedHead->prev = state;
            gSndpUsedHead = state;
        } else {
            state->prev = 0;
            state->next = state->prev;
            gSndpUsedHead = state;
            gSndpUsedTail = state;
        }
        osGetIntMask(intMask);
        sustained = sound->envelope->decayTime == -1;
        state->sound = sound;
        state->priority = sustained + 0x40;
        state->state = 5;
        state->pitch = 1.0f;
        state->retries = 2;
        state->flags = km->keyMax & 0xF0;
        state->handle = 0;
        if (state->flags & 0x20) {
            state->pitchRatio = alCents2Ratio(km->keyBase * 100 - 6000);
        } else {
            state->pitchRatio = alCents2Ratio(km->keyBase * 100 + km->detune - 6000);
        }
        if (sustained) {
            state->flags |= 2;
        }
        state->fxMix = 0;
        state->pan = 0x40;
        state->vol = 0x7FFF;
    } else {
        osGetIntMask(intMask);
    }
    return state;
}

void __n_freeState(GfSndState *state) {
    if (gSndpUsedHead == state) {
        gSndpUsedHead = state->next;
    }
    if (gSndpUsedTail == state) {
        gSndpUsedTail = state->prev;
    }
    alUnlink((ALLink *)state);
    if (gSndpFreeList) {
        state->next = gSndpFreeList;
        state->prev = NULL;
        gSndpFreeList->prev = state;
        gSndpFreeList = state;
    } else {
        state->next = state->prev = NULL;
        gSndpFreeList = state;
    }
    if (state->flags & 4) {
        gSndpVoiceCount--;
    }
    state->state = 0;
    if (state->handle) {
        if (*state->handle == state) {
            *state->handle = NULL;
        }
        state->handle = NULL;
    }
}

void n_alSndpSetPriority(GfSndState *state, u8 priority) {
    if (state) {
        state->priority = (s16)priority; // ORIG: the target narrows priority through s16 (sll/sra at 0x1B4C-0x1B50) before the sb
    }
}

u8 n_alSndpGetState(GfSndState *state) {
    if (state) {
        return state->state;
    } else {
        return 0;
    }
}

GfSndState *n_alSndpPlay(void *bank, s16 sndId, u16 vol, u8 pan, f32 pitch, u8 fxMix, GfSndState **handle) {
    GfSndState *state;
    GfSndState *ret;
    ALKeyMap *km;
    ALSound *sound;
    s16 lastId;
    s32 delay48;
    s32 delta;
    s32 total;
    s32 val;
    GeSndEvt ev1;
    GeSndEvt ev2;

    ret = 0;
    lastId = 0;
    total = 0;
    if (sndId) {
        do {
            sound = ((ALBank *)bank)->instArray[0]->soundArray[sndId - 1];
            state = __n_allocState(bank, sound);
            if (state) {
                gSndp->target = state;
                ev1.type = 1;
                ev1.state = state;
                val = pan + state->pan - 0x40;
                if (val >= 0x80) {
                    val = 0x7F;
                } else if (val < 0) {
                    val = 0;
                }
                state->pan = val;
                state->vol = ((u32)vol * state->vol) >> 15;
                state->pitch = state->pitch * pitch;
                state->fxMix = fxMix;
                delta = sound->keyMap->velocityMax * 33333;
                if (state->flags & 0x10) {
                    state->flags &= ~0x10;
                    alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev1, total + 1);
                    delay48 = delta + 1;
                    lastId = sndId;
                } else {
                    alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev1, delta + 1);
                }
                ret = state;
            }
            total += delta;
            km = sound->keyMap;
            sndId = km->velocityMin + ((km->keyMin & 0xC0) << 2);
            sndId = sndId + ((km->keyMin & 0x20) << 5);
        } while (sndId && state);
        if (ret) {
            ret->flags |= 1;
            ret->handle = handle;
            if (lastId) {
                ret->flags |= 0x10;
                ev2.type = 0x200;
                ev2.state = ret;
                ev2.arg8.i = lastId;
                ev2.arg12 = bank;
                alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev2, delay48);
            }
        }
    }
    if (handle) {
        *handle = ret;
    }
    return ret;
}

void n_alSndpStop(GfSndState *state) {
    GeSndEvt ev;

    ev.type = 0x400;
    ev.state = state;
    if (state) {
        ev.state->flags &= ~0x10; // ORIG: the target reloads ev.state from 28(sp) for the flag update (lw at 0x1EAC)
        alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev, 0);
    }
}

void __n_sndpStopByFlags(u8 mask) {
    s32 intMask;
    GeSndEvt ev;
    GfSndState *state;

    intMask = osGetIntMask(1);
    state = gSndpUsedHead;
    while (state) {
        ev.type = 0x400;
        ev.state = state;
        if ((state->flags & mask) == mask) {
            ev.state->flags &= ~0x10; // ORIG: the target reloads ev.state from 32(sp) for the flag update (lw at 0x1F48)
            alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev, 0);
        }
        state = state->next;
    }
    osGetIntMask(intMask);
}

void n_alSndpStopAll(void) {
    __n_sndpStopByFlags(1);
}

void n_alSndpStopChained(void) {
    __n_sndpStopByFlags(0x11);
}

void n_alSndpStopSustained(void) {
    __n_sndpStopByFlags(3);
}

void n_alSndpPostEvent(GfSndState *state, s16 type, s32 arg) {
    GeSndEvt ev;

    ev.type = type;
    ev.state = state;
    ev.arg8.i = arg;
    if (state) {
        alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev, 0);
    }
}

u16 n_alSndpGetGroupVol(u8 idx) {
    return ((u16 *)gSndpGroupVol)[idx];
}

void n_alSndpSetGroupVol(u8 idx, u16 val) {
    GfSndState *state = gSndpUsedHead;
    s32 i;
    GeSndEvt ev;

    ((u16 *)gSndpGroupVol)[idx] = val;
    for (i = 0; state; i++, state = state->next) {
        if ((state->sound->keyMap->keyMin & 0x1F) == idx) {
            ev.type = 0x800;
            ev.state = state;
            alEvtqPostEvent(&gSndp->evtq, (ALEvent *)&ev, 0);
        }
    }
}

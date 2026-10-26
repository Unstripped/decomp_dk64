#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;

#include "common.h"

extern s32 osGetIntMask(s32 arg0);

struct GeSndState;

typedef struct {
    u16 type;
    struct GeSndState *state;
    union {
        s32 i;
        f32 f;
    } arg8;
    s32 arg12;
} GeSndEvt;

typedef struct {
    s32 maxSounds;
    s32 maxEvents;
    s32 unk8;
    ALHeap *heap;
    u16 maxStates;
} GeSndpConfig;

typedef struct {
    ALPlayer node;
    ALEventQueue evtq;
    ALEvent nextEvent;
    s32 nextEventPad;
    s32 unk3C;
    u8 *sndState;
    s32 unk44;
    ALMicroTime frameTime;
    ALMicroTime nextDelta;
    ALMicroTime curTime;
} GeSndp;

extern GeSndp *D_807563CC;
extern u8 *D_807563C8;
extern s16 *D_807FF0E4;
ALMicroTime __n_sndpVoiceHandler(void *);
void func_8073B5D0(void *);

void n_alSndpNew(GeSndpConfig *c) {
    u32 i;
    void *ptr;
    ALEvent evt;

    D_807563CC->unk44 = c->unk8;
    D_807563CC->unk3C = 0;
    D_807563CC->frameTime = 16000;
    ptr = alHeapDBAlloc(0, 0, c->heap, 1, c->maxSounds * 72);
    D_807563CC->sndState = ptr;
    ptr = alHeapDBAlloc(0, 0, c->heap, 1, c->maxEvents * 28);
    alEvtqNew(&D_807563CC->evtq, ptr, c->maxEvents);
    D_807563C8 = D_807563CC->sndState;
    for (i = 1; i < c->maxSounds; i++) {
        u8 *sndState = D_807563CC->sndState;
        alLink((ALLink *)(sndState + i * 72), (ALLink *)(sndState + i * 72 - 72));
    }
    D_807FF0E4 = alHeapDBAlloc(0, 0, c->heap, 2, c->maxStates);
    for (i = 0; i < c->maxStates; i++) {
        D_807FF0E4[i] = 0x7FFF;
    }
    D_807563CC->node.next = NULL;
    D_807563CC->node.handler = __n_sndpVoiceHandler;
    D_807563CC->node.clientData = D_807563CC;
    func_8073B5D0(D_807563CC);
    evt.type = 0x20;
    alEvtqPostEvent(&D_807563CC->evtq, &evt, D_807563CC->frameTime);
    D_807563CC->nextDelta = alEvtqNextEvent(&D_807563CC->evtq, &D_807563CC->nextEvent);
}

void __n_handleEvent(GeSndEvt *);

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

typedef struct {
    s32 attackTime;
    s32 decayTime;
    s32 releaseTime;
    u8 attackVolume;
    u8 decayVolume;
} GeSndEnvelope;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 volIndex;
    u8 panFx;
} GeSndKeyMap;

typedef struct {
    GeSndEnvelope *envelope;
    GeSndKeyMap *keyMap;
    void *wave;
    u8 samplePan;
    u8 sampleVolume;
} GeSndSound;

typedef struct GeSndState {
    struct GeSndState *next;
    struct GeSndState *prev;
    GeSndSound *sound;
    u8 voice[0x1C];
    f32 unk28;
    f32 pitch;
    s32 unk30;
    s32 retries;
    s16 vol;
    s16 envVol;
    s32 endTime;
    u8 priority;
    u8 pan;
    u8 fxMix;
    u8 flags;
    u8 state;
} GeSndState;

extern s16 D_807563D0;
extern GeSndState *D_807563C4;

void __n_sndpDestroyState();
void __n_sndpPostPitch();
void __n_removeEvents();
u16 n_alSndpCountStates();
struct GfSndState *n_alSndpPlay(void *, s16, u16, u8, f32, u8, struct GfSndState **);
s32 n_alSynAllocVoice(void *, void *);
void n_alSynSetVol(void *, s32, s32);
void n_alSynStartVoiceParams(void *, void *, f32, s32, u8, s32, s32, f32, s32, s32);
void n_alSynSetPitch(void *, f32);
void func_8073CF00(void *, u8);
void func_8073C820(void *, s32);

#define GE_STATE_VOL(st, km, snd) \
    (D_807FF0E4[(km)->volIndex & 0x1F] * (((st)->envVol * (st)->vol * (snd)->sampleVolume) / 0x3F01) / 0x7FFF)
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
    GeSndSound *sound;
    GeSndKeyMap *keyMap;
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
    GeSndState *state;
    GeSndState *nextState;
    s16 junk1;
    s16 junk2;

    done = 1;
    voice = 0;
    state = 0;
    nextState = 0;
    do {
        if (nextState) {
            evt.state = state;
            evt.type = event->type;
            evt.arg8.i = event->arg8.i;
            event = &evt;
        }
        state = event->state;
        sound = state->sound;
        if (sound == 0) {
            n_alSndpCountStates(&junk1, &junk2);
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
                full = D_807563D0 >= D_807563CC->unk44;
                if (!full || (state->flags & 0x10)) {
                    voice = n_alSynAllocVoice(&state->voice, &config);
                }
                if (voice == 0) {
                    if ((state->flags & 0x12) || state->retries > 0) {
                        state->state = 4;
                        state->retries--;
                        alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)event, 0x8235);
                    } else if (full) {
                        GeSndState *iter;
                        GeSndEvt evt3;

                        iter = D_807563C4;
                        do {
                            if (!(iter->flags & 0x12) && (iter->flags & 4) && iter->state != 3) {
                                full = 0;
                                evt3.type = 0x80;
                                evt3.state = iter;
                                iter->state = 3;
                                alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)&evt3, 0x3E8);
                                n_alSynSetVol(&iter->voice, 0, 0x3E8);
                            }
                            iter = iter->prev;
                        } while (full && iter);
                        if (!full) {
                            state->retries = 2;
                            alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)event, 0x3E9);
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
                delta = sound->envelope->attackTime / state->pitch / state->unk28;
                state->endTime = D_807563CC->curTime + delta;
                GE_CALC_VOL(vol, state, keyMap, sound)
                panTmp = state->pan + sound->samplePan - 0x40;
                GE_CLAMP_PAN(pan, panTmp);
                fx = (state->fxMix & 0x7F) + ((keyMap->panFx & 0xF) << 3);
                GE_CLAMP_FX(fx);
                fx |= state->fxMix & 0x80;
                n_alSynStartVoiceParams(&state->voice, sound->wave, state->pitch * state->unk28, vol, pan, fx, 0, 0.0f, 0, delta);
                state->state = 1;
                D_807563D0++;
                if (!(state->flags & 2)) {
                    if (delta == 0) {
                        state->envVol = sound->envelope->decayVolume;
                        GE_CALC_VOL(vol, state, keyMap, sound)
                        delta = sound->envelope->decayTime / state->unk28 / state->pitch;
                        state->endTime = D_807563CC->curTime + delta;
                        n_alSynSetVol(&state->voice, vol, delta);
                        evt2.type = 2;
                        evt2.state = state;
                        alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)&evt2, delta);
                        if (state->flags & 0x20) {
                            __n_sndpPostPitch(state);
                        }
                    } else {
                        evt2.type = 0x40;
                        evt2.state = state;
                        delta = sound->envelope->attackTime / state->pitch / state->unk28;
                        alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)&evt2, delta);
                    }
                }
                break;
            case 2:
            case 0x400:
            case 0x1000:
                if (event->type != 0x1000 || (state->flags & 2)) {
                    switch (state->state) {
                        case 1:
                            __n_removeEvents(&D_807563CC->evtq, state, 0x40);
                            delta = sound->envelope->releaseTime / state->unk28 / state->pitch;
                            n_alSynSetVol(&state->voice, 0, delta);
                            if (delta != 0) {
                                evt2.type = 0x80;
                                evt2.state = state;
                                alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)&evt2, delta);
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
                    func_8073CF00(&state->voice, pan);
                }
                break;
            case 0x10:
                state->pitch = event->arg8.f;
                if (state->state == 1) {
                    n_alSynSetPitch(&state->voice, state->pitch * state->unk28);
                    if (state->flags & 0x20) {
                        __n_sndpPostPitch(state);
                    }
                }
                break;
            case 0x100:
                state->fxMix = event->arg8.i;
                if (state->state == 1) {
                    fx = (state->fxMix & 0x7F) + ((keyMap->panFx & 0xF) << 3);
                    GE_CLAMP_FX(fx);
                    fx |= state->fxMix & 0x80;
                    func_8073C820(&state->voice, fx);
                }
                break;
            case 8:
                state->vol = event->arg8.i;
                if (state->state == 1) {
                    GE_CALC_VOL(vol, state, keyMap, sound)
                    n_alSynSetVol(&state->voice, vol,
                                  (state->endTime - D_807563CC->curTime < 0x3E8) ? 0x3E8 : state->endTime - D_807563CC->curTime);
                }
                break;
            case 0x800:
                if (state->state == 1) {
                    delta = sound->envelope->releaseTime / state->unk28 / state->pitch;
                    GE_CALC_VOL(vol, state, keyMap, sound)
                    n_alSynSetVol(&state->voice, vol, delta);
                }
                break;
            case 0x40:
                if (!(state->flags & 2)) {
                    state->envVol = sound->envelope->decayVolume;
                    GE_CALC_VOL(vol, state, keyMap, sound)
                    delta = sound->envelope->decayTime / state->unk28 / state->pitch;
                    state->endTime = D_807563CC->curTime + delta;
                    n_alSynSetVol(&state->voice, vol, delta);
                    evt2.type = 2;
                    evt2.state = state;
                    alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)&evt2, delta);
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
                    s32 id;

                    id = (s32)n_alSndpPlay((void *)event->arg12, event->arg8.i, state->vol, state->pan, state->pitch, state->fxMix, (struct GfSndState **)state->unk30);
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

typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    s8 b5;
} GfKeyMap;

typedef struct {
    s32 attackTime;
    s32 decayTime;
} GfEnv;

typedef struct {
    GfEnv *env;
    GfKeyMap *keymap;
} GfSound;

typedef struct GfSndState {
    struct GfSndState *next;
    struct GfSndState *prev;
    GfSound *sound;
    u8 voice[0x1C];
    f32 pitchRatio;
    f32 pitch;
    struct GfSndState **handle;
    s32 unk34;
    s16 vol;
    s16 pad3A;
    s32 unk3C;
    u8 priority;
    u8 pan;
    u8 fxMix;
    u8 flags;
    u8 state;
} GfSndState;

typedef struct {
    u16 type;
    GfSndState *state;
    s32 arg;
    s32 arg2;
} GfSndEvt;

typedef struct {
    u8 pad0[0x14];
    ALEventQueue evtq;
    u8 pad28[0x14];
    GfSndState *unk3C;
} GfSndp;

extern GfSndState *D_807563C0;

extern void n_alSynStopVoice(void *);
extern void n_alSynFreeVoice(void *);
void __n_freeState(GfSndState *state);

void __n_sndpDestroyState(GfSndState *state) {
    if (state->flags & 4) {
        n_alSynStopVoice(&state->voice);
        n_alSynFreeVoice(&state->voice);
    }
    __n_freeState(state);
    __n_removeEvents(&((GfSndp *)D_807563CC)->evtq, state, 0xFFFF);
}

void __n_sndpPostPitch(GfSndState *state) {
    GfSndEvt ev;
    f32 pitch;

    pitch = alCents2Ratio(state->sound->keymap->b5) * state->pitch;
    ev.type = 0x10;
    ev.state = state;
    ev.arg = *(s32 *)&pitch;
    alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev, 33333);
}

void __n_removeEvents(evtq, state, mask)
ALEventQueue *evtq;
GfSndState *state;
u16 mask;
{
    ALLink *thisNode;
    ALLink *nextNode;
    ALEventListItem *thisItem;
    ALEventListItem *nextItem;
    GfSndEvt *thisEvent;
    s32 intMask;

    intMask = osGetIntMask(1);
    thisNode = evtq->allocList.next;
    while (thisNode != 0) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        thisEvent = (GfSndEvt *)&thisItem->evt;
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

u16 n_alSndpCountStates(u16 *a0, u16 *a1) {
    u16 n0;
    u16 n8;
    u16 n4;
    GfSndState *p0 = D_807563C0;
    GfSndState *p8 = (GfSndState *)D_807563C8;
    GfSndState *p4 = (GfSndState *)D_807563C4;

    for (n0 = 0; p0; n0++, p0 = p0->next) {
    }
    for (n8 = 0; p8; n8++, p8 = p8->next) {
    }
    for (n4 = 0; p4; n4++, p4 = p4->prev) {
    }
    *a0 = n8;
    *a1 = n0;
    return n4;
}

GfSndState *__n_allocState(void *sndp, GfSound *sound);

GfSndState *__n_allocState(void *sndp, GfSound *sound) {
    GfSndState *state;
    GfKeyMap *km = sound->keymap;
    s32 stolen;
    s32 intMask;

    intMask = osGetIntMask(1);
    state = (GfSndState *)D_807563C8;
    if (state) {
        D_807563C8 = (u8 *)state->next;
        alUnlink((ALLink *)state);
        if (D_807563C0) {
            state->next = D_807563C0;
            state->prev = 0;
            D_807563C0->prev = state;
            D_807563C0 = state;
        } else {
            state->prev = 0;
            state->next = state->prev;
            D_807563C0 = state;
            D_807563C4 = (GeSndState *)state;
        }
        osGetIntMask(intMask);
        stolen = sound->env->decayTime == -1;
        state->sound = sound;
        state->priority = stolen + 0x40;
        state->state = 5;
        state->pitch = 1.0f;
        state->unk34 = 2;
        state->flags = km->b3 & 0xF0;
        state->handle = 0;
        if (state->flags & 0x20) {
            state->pitchRatio = alCents2Ratio(km->b4 * 100 - 6000);
        } else {
            state->pitchRatio = alCents2Ratio(km->b4 * 100 + km->b5 - 6000);
        }
        if (stolen) {
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
    if (D_807563C0 == state) {
        D_807563C0 = state->next;
    }
    if ((GfSndState *)D_807563C4 == state) {
        D_807563C4 = (GeSndState *)state->prev;
    }
    alUnlink((ALLink *)state);
    if (D_807563C8) {
        state->next = (GfSndState *)D_807563C8;
        state->prev = 0;
        ((GfSndState *)D_807563C8)->prev = state;
        D_807563C8 = (u8 *)state;
    } else {
        state->prev = 0;
        state->next = state->prev;
        D_807563C8 = (u8 *)state;
    }
    if (state->flags & 4) {
        D_807563D0--;
    }
    state->state = 0;
    if (state->handle) {
        if (*state->handle == state) {
            *state->handle = 0;
        }
        state->handle = 0;
    }
}

void n_alSndpSetPriority(GfSndState *state, u8 priority) {
    if (state) {
        state->priority = (s16)priority;
    }
}

u8 n_alSndpGetState(GfSndState *state) {
    if (state) {
        return state->state;
    } else {
        return 0;
    }
}

GfSndState *n_alSndpPlay(void *a0, s16 sndId, u16 vol, u8 pan, f32 pitch, u8 fxMix, GfSndState **handle) {
    GfSndState *state;
    GfSndState *ret;
    GfKeyMap *km;
    GfSound *sound;
    s16 lastId;
    s32 delay48;
    s32 delta;
    s32 total;
    s32 val;
    GfSndEvt ev1;
    GfSndEvt ev2;

    ret = 0;
    lastId = 0;
    total = 0;
    if (sndId) {
        do {
            sound = ((GfSound **)((u8 *)((void **)a0)[3] + sndId * 4))[3];
            state = __n_allocState(a0, sound);
            if (state) {
                ((GfSndp *)D_807563CC)->unk3C = state;
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
                delta = sound->keymap->b1 * 33333;
                if (state->flags & 0x10) {
                    state->flags &= ~0x10;
                    alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev1, total + 1);
                    delay48 = delta + 1;
                    lastId = sndId;
                } else {
                    alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev1, delta + 1);
                }
                ret = state;
            }
            total += delta;
            km = sound->keymap;
            sndId = km->b0 + ((km->b2 & 0xC0) << 2);
            sndId = sndId + ((km->b2 & 0x20) << 5);
        } while (sndId && state);
        if (ret) {
            ret->flags |= 1;
            ret->handle = handle;
            if (lastId) {
                ret->flags |= 0x10;
                ev2.type = 0x200;
                ev2.state = ret;
                ev2.arg = lastId;
                ev2.arg2 = (s32)a0;
                alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev2, delay48);
            }
        }
    }
    if (handle) {
        *handle = ret;
    }
    return ret;
}

void n_alSndpStop(GfSndState *state) {
    GfSndEvt ev;

    ev.type = 0x400;
    ev.state = state;
    if (state) {
        ev.state->flags &= ~0x10;
        alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev, 0);
    }
}

void __n_sndpStopByFlags(u8 mask) {
    s32 intMask;
    GfSndEvt ev;
    GfSndState *state;

    intMask = osGetIntMask(1);
    state = D_807563C0;
    while (state) {
        ev.type = 0x400;
        ev.state = state;
        if ((state->flags & mask) == mask) {
            ev.state->flags &= ~0x10;
            alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev, 0);
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
    GfSndEvt ev;

    ev.type = type;
    ev.state = state;
    ev.arg = arg;
    if (state) {
        alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev, 0);
    }
}

u16 n_alSndpGetGroupVol(u8 idx) {
    return ((u16 *)D_807FF0E4)[idx];
}

void n_alSndpSetGroupVol(u8 idx, u16 val) {
    GfSndState *state = D_807563C0;
    s32 i;
    GfSndEvt ev;

    ((u16 *)D_807FF0E4)[idx] = val;
    for (i = 0; state; i++, state = state->next) {
        if ((state->sound->keymap->b2 & 0x1F) == idx) {
            ev.type = 0x800;
            ev.state = state;
            alEvtqPostEvent(&((GfSndp *)D_807563CC)->evtq, (ALEvent *)&ev, 0);
        }
    }
}

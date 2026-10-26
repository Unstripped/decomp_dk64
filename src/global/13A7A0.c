#include "common.h"

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
ALMicroTime __n_sndpHandleEvent(void *);
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
    D_807563CC->node.handler = __n_sndpHandleEvent;
    D_807563CC->node.clientData = D_807563CC;
    func_8073B5D0(D_807563CC);
    evt.type = 0x20;
    alEvtqPostEvent(&D_807563CC->evtq, &evt, D_807563CC->frameTime);
    D_807563CC->nextDelta = alEvtqNextEvent(&D_807563CC->evtq, &D_807563CC->nextEvent);
}

void __n_sndpVoiceHandler(GeSndEvt *);

ALMicroTime __n_sndpHandleEvent(void *node) {
    GeSndp *sndp = node;
    ALEvent evt;

    do {
        switch (sndp->nextEvent.type) {
            case 0x20:
                evt.type = 0x20;
                alEvtqPostEvent(&sndp->evtq, &evt, sndp->frameTime);
                break;
            default:
                __n_sndpVoiceHandler((GeSndEvt *)&sndp->nextEvent);
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

void n_alSndpSetVol();
void n_alSndpSetPitch();
void n_alSndpSetPan();
void n_alSndpSetPriority();
s32 n_alSndpAllocate(s32, s32, s32, s32, f32, s32, s32);
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

void __n_sndpVoiceHandler(GeSndEvt *event) {
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
            n_alSndpSetPriority(&junk1, &junk2);
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
                            n_alSndpSetVol(state);
                        }
                    } else {
                        n_alSndpSetVol(state);
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
                            n_alSndpSetPitch(state);
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
                            n_alSndpSetPan(&D_807563CC->evtq, state, 0x40);
                            delta = sound->envelope->releaseTime / state->unk28 / state->pitch;
                            n_alSynSetVol(&state->voice, 0, delta);
                            if (delta != 0) {
                                evt2.type = 0x80;
                                evt2.state = state;
                                alEvtqPostEvent(&D_807563CC->evtq, (ALEvent *)&evt2, delta);
                                state->state = 2;
                            } else {
                                n_alSndpSetVol(state);
                            }
                            break;
                        case 4:
                        case 5:
                            n_alSndpSetVol(state);
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
                        n_alSndpSetPitch(state);
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
                        n_alSndpSetPitch(state);
                    }
                }
                break;
            case 0x80:
                n_alSndpSetVol(state);
                break;
            case 0x200:
                if (state->flags & 0x10) {
                    s32 id;

                    id = n_alSndpAllocate(event->arg12, event->arg8.i, state->vol, state->pan, state->pitch, state->fxMix, state->unk30);
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpSetVol.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpSetPitch.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpSetPan.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpSetPriority.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpSetFXMix.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpPlay.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpPlayAt.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpStop.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpAllocate.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpDeallocate.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpGetState.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpSetSound.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpGetSound.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/n_alSndpDelete.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/func_80737AC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/func_80737B2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/func_80737B48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13A7A0/func_80737B58.s")

// n_alSndpSetFXMix (src/global/13A7A0.c): stage 6, text same size/frame; only diff: first branch (flags&0x20) alCents2Ratio(km->b4*100-6000): target multiplies in place in a0 (move at,a0; sll a0,at,2; subu a0,a0,at; ...), IDO emits sll t7,a0,2 ... move a0,t7; second branch then differs only by temp regs (t7 vs t8 shift). Tried operand order, casts, unsigned, field types, temps, K&R callee; permuter best 375 (no hit). Needs osGetIntMask(s32) preempt (#define _OS_EXCEPTION_H_ before common.h) and D_807563C0/C4/C8/CC externs.
#include "common.h"

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
extern GfSndState *D_807563C4;
extern u8 *D_807563C8;
extern void *D_807563CC;
extern s16 D_807563D0;
extern u16 *D_807FF0E4;

extern void n_alSynStopVoice(void *);
extern void n_alSynFreeVoice(void *);
void n_alSndpPlay(GfSndState *state);
void n_alSndpSetPan();

GfSndState *n_alSndpSetFXMix(void *sndp, GfSound *sound) {
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
            D_807563C4 = state;
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

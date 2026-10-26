// ultralib prototypes osGetIntMask(void); the boot-segment implementation takes the mask.
#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;
#include "common.h"
typedef struct SynCoreParam {
    ALLink *next;
    s32 timestamp;
    s16 type;
    s16 pad;
    s32 value;
    s32 delta;
} SynCoreParam;

typedef struct SynCoreSynth {
    ALPlayer *head;
    ALLink pFreeList;
    ALLink pAllocList;
    ALLink pLameList;
    s32 paramSamples;
    s32 curSamples;
    void *dma;
    void *paramPool;
    SynCoreParam *paramFreeList;
    void *mainBus;
    void *auxBuses;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
    s32 maxOutSamples;
    void *outBuffer;
    s32 unk4C;
} SynCoreSynth;

typedef struct SynCorePVoice {
    u8 pad0[0x88];
    s32 envOffset;
} SynCorePVoice;

extern SynCoreSynth *D_807563E4;
extern s32 osGetIntMask(s32);
void n_alEnvmixerParam(void *, s32, SynCoreParam *);
SynCoreParam *__n_allocParam(void);
void _n_freePVoice(ALLink *);

void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount) {
    s32 i;

    evtq->eventCount = 0;
    evtq->allocList.next = NULL;
    evtq->allocList.prev = NULL;
    evtq->freeList.next = NULL;
    evtq->freeList.prev = NULL;
    if (itemCount + (i = 0) > 0) {
        do {
            alLink(&items[i].node, &evtq->freeList);
        } while (++i < itemCount);
    }
}

ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt) {
    ALEventListItem *item;
    ALMicroTime delta;
    s32 intMask;

    intMask = osGetIntMask(1);
    item = (ALEventListItem *)evtq->allocList.next;
    if (item != NULL) {
        alUnlink(&item->node);
        bcopy(&item->evt, evt, 0x10);
        alLink(&item->node, &evtq->freeList);
        delta = item->delta;
    } else {
        evt->type = -1;
        delta = 0;
    }
    osGetIntMask(intMask);
    return delta;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/13FED0/alEvtqPostEvent.s")

void alEvtqFlushType(ALEventQueue *evtq, s16 type) {
    ALEventListItem *item;
    ALEventListItem *next;
    ALEventListItem *current;
    ALEventListItem *nextCurrent;
    s32 intMask;

    intMask = osGetIntMask(1);
    item = (ALEventListItem *)evtq->allocList.next;
    if (item != NULL) {
        do {
            next = (ALEventListItem *)item->node.next;
            current = item;
            nextCurrent = next;
            if (current->evt.type == type) {
                if (nextCurrent != NULL) {
                    nextCurrent->delta += current->delta;
                }
                alUnlink(&item->node);
                alLink(&item->node, &evtq->freeList);
            }
            item = next;
        } while (item != NULL);
    }
    osGetIntMask(intMask);
}

void n_alSynAddPlayer(ALPlayer *player) {
    s32 intMask;

    intMask = osGetIntMask(1);
    player->samplesLeft = D_807563E4->curSamples;
    player->next = D_807563E4->head;
    D_807563E4->head = player;
    osGetIntMask(intMask);
}

void func_8073B5D0(ALPlayer *player) {
    s32 intMask;

    intMask = osGetIntMask(1);
    player->samplesLeft = D_807563E4->curSamples;
    player->next = D_807563E4->head;
    D_807563E4->head = player;
    osGetIntMask(intMask);
}

void func_8073B640(ALPlayer *player) {
    s32 intMask;

    intMask = osGetIntMask(1);
    player->samplesLeft = D_807563E4->curSamples;
    player->next = D_807563E4->head;
    D_807563E4->head = player;
    osGetIntMask(intMask);
}

void n_alSynStopVoice(ALVoice *voice) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->timestamp = D_807563E4->paramSamples + ((SynCorePVoice *)voice->pvoice)->envOffset;
        param->type = 0xF;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynFreeVoice(ALVoice *voice) {
    void *unused;
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        if (((SynCorePVoice *)voice->pvoice)->envOffset != 0) {
            param = __n_allocParam();
            if (param == NULL) {
                return;
            }
            param->timestamp = D_807563E4->paramSamples + ((SynCorePVoice *)voice->pvoice)->envOffset;
            param->type = 0;
            param->value = (s32)voice->pvoice;
            n_alEnvmixerParam(voice->pvoice, 3, param);
        } else {
            _n_freePVoice((ALLink *)voice->pvoice);
        }
        voice->pvoice = NULL;
    }
}

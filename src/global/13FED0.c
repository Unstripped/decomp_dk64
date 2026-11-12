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

extern SynCoreSynth *n_syn;
extern s32 osGetIntMask(s32);
SynCoreParam *__n_allocParam(void);

void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount) {
    s32 i;

    evtq->eventCount = 0;
    evtq->allocList.next = NULL;
    evtq->allocList.prev = NULL;
    evtq->freeList.next = NULL;
    evtq->freeList.prev = NULL;
    for (i = 0; i < itemCount; i++) {
        alLink(&items[i].node, &evtq->freeList);
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

void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta) {
    ALEventListItem *item;
    ALEventListItem *next;
    ALLink *node;
    s32 infinite;
    s32 intMask;

    infinite = 0;
    intMask = osGetIntMask(1);
    item = (ALEventListItem *)evtq->freeList.next;
    if (item == NULL) {
        osGetIntMask(intMask);
        return;
    }
    alUnlink(&item->node);
    bcopy(evt, &item->evt, 0x10);
    if (delta == 0x7FFFFFFF) infinite = -1;
    for (node = &evtq->allocList; node != NULL; node = node->next) {
        if (node->next == NULL) {
            item->delta = infinite != 0 ? 0 : delta;
            alLink(&item->node, node);
            break;
        } else {
            next = (ALEventListItem *)node->next;
            if (delta < next->delta) {
                item->delta = delta;
                next->delta -= delta;
                alLink(&item->node, node);
                break;
            }
            delta -= next->delta;
        }
    }
    osGetIntMask(intMask);
}

void alEvtqFlushType(ALEventQueue *evtq, s16 type) {
    ALLink *thisNode;
    ALLink *nextNode;
    ALEventListItem *thisItem;
    ALEventListItem *nextItem;
    s32 intMask;

    intMask = osGetIntMask(1);
    thisNode = evtq->allocList.next;
    while (thisNode != NULL) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        if (thisItem->evt.type == type) {
            if (nextItem != NULL) {
                nextItem->delta += thisItem->delta;
            }
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }
    osGetIntMask(intMask);
}

void n_alSynAddPlayer(ALPlayer *player) {
    s32 intMask;

    intMask = osGetIntMask(1);
    player->samplesLeft = n_syn->curSamples;
    player->next = n_syn->head;
    n_syn->head = player;
    osGetIntMask(intMask);
}

void n_alSynAddSndPlayer(ALPlayer *player) {
    s32 intMask;

    intMask = osGetIntMask(1);
    player->samplesLeft = n_syn->curSamples;
    player->next = n_syn->head;
    n_syn->head = player;
    osGetIntMask(intMask);
}

void n_alSynAddCSPPlayer(ALPlayer *player) {
    s32 intMask;

    intMask = osGetIntMask(1);
    player->samplesLeft = n_syn->curSamples;
    player->next = n_syn->head;
    n_syn->head = player;
    osGetIntMask(intMask);
}

void n_alSynStopVoice(ALVoice *voice) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->timestamp = n_syn->paramSamples + ((SynCorePVoice *)voice->pvoice)->envOffset;
        param->type = 0xF;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynFreeVoice(ALVoice *voice) {
    void *pad;
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        if (((SynCorePVoice *)voice->pvoice)->envOffset != 0) {
            param = __n_allocParam();
            if (param == NULL) {
                return;
            }
            param->timestamp = n_syn->paramSamples + ((SynCorePVoice *)voice->pvoice)->envOffset;
            param->type = 0;
            param->value = (s32)voice->pvoice;
            n_alEnvmixerParam(voice->pvoice, 3, param);
        } else {
            _n_freePVoice((ALLink *)voice->pvoice);
        }
        voice->pvoice = NULL;
    }
}

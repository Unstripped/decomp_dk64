// ultralib prototypes osGetIntMask(void); the boot-segment implementation takes the mask.
#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;
#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E160.h"

extern N_ALSynth *n_syn;
extern s32 osGetIntMask(s32);

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
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 0xF;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynFreeVoice(ALVoice *voice) {
    void *pad;
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        if (voice->pvoice->delta != 0) {
            param = __n_allocParam();
            if (param == NULL) {
                return;
            }
            param->delta = n_syn->paramSamples + voice->pvoice->delta;
            param->type = 0;
            param->data.ptr = voice->pvoice;
            n_alEnvmixerParam(voice->pvoice, 3, param);
        } else {
            _n_freePVoice(voice->pvoice);
        }
        voice->pvoice = NULL;
    }
}

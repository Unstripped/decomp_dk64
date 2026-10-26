// __n_seqpReleaseVoice (src/global/13ECE0.c): stage 4: TEXT OK
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

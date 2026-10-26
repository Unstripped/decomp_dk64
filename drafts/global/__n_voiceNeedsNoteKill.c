// __n_voiceNeedsNoteKill (src/global/13ECE0.c): stage 3: TEXT OK
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

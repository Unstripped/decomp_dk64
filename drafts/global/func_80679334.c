// func_80679334 (src/global/7CA80.c): stage 4: frame 0x28, s0-s3 match, s0/s1 regalloc swap between i and entry pointer
void func_80679334(void) {
    ActorQueueEntry *entry;
    s32 i;
    Actor *actor;
    ActorCallbackNode *curr;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    s32 changed;

    for (i = 0, entry = D_807FBF18; i < D_807FBFD8; i++, entry++) {
        entry->arg6--;
        if (entry->arg6 == 0) {
            actor = (Actor *)entry->arg0;
            if (actorTableContains(actor)) {
                curr = actor->unk13C;
                link = &actor->unk13C;
                prev = NULL;
                if (curr != NULL) {
                    do {
                        link = &curr->next;
                        prev = curr;
                        curr = curr->next;
                    } while (curr != NULL);
                }
                *link = entry->node;
                entry->node->prev = prev;
            } else {
                if (entry->node->unk10 != NULL) {
                    heapFree(entry->node->unk10);
                }
                heapFree(entry->node);
            }
        }
    }
    do {
        changed = 0;
        for (i = 0, entry = D_807FBF18; i < D_807FBFD8; i++, entry++) {
            if (entry->arg6 == 0) {
                *entry = D_807FBF18[--D_807FBFD8];
                changed = 1;
            }
        }
    } while (changed);
}

// actorDelayedCallbacksTick (src/global/7CA80.c): stage 3: 87 insns, frame 0x30 vs 0x28 (extra s4 reg for %hi(D_807FBF18)); deadsweep round 2 full=63 text=53
s32 actorTableContains(Actor *);

void actorDelayedCallbacksTick(void) {
    ActorQueueEntry *entry;
    s32 i;
    Actor *actor;
    ActorCallbackNode *curr;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    s32 changed;

    for (i = 0, entry = D_807FBF18; i < D_807FBFD8; i++, entry++) {
        entry->arg6--;
        if (D_807FBFD8 && D_807FBFD8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                    if (D_807FBF18) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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

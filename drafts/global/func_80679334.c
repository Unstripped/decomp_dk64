// func_80679334 (src/global/7CA80.c): from .scratch/R3A/func_80679334_best.c
void func_80679334(void) {
    ActorQueueEntry *entry;
    s32 i;
    Actor *actor;
    ActorCallbackNode *curr;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    s32 changed;

    for (i = 0; i < D_807FBFD8; i++) {
        D_807FBF18[i].arg6--;
        if (D_807FBF18[i].arg6 == 0) {
            actor = (Actor *)D_807FBF18[i].arg0;
            if (func_8067AF44(actor)) {
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
                *link = D_807FBF18[i].node;
                D_807FBF18[i].node->prev = prev;
            } else {
                if (D_807FBF18[i].node->unk10 != NULL) {
                    heapFree(D_807FBF18[i].node->unk10);
                }
                heapFree(D_807FBF18[i].node);
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

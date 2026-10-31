// actorCallbackListSort (src/global/7CA80.c): stage 5: 53 insns, frame 0, 5 diff lines, regalloc only: second block (if (!inserted) unlink) uses t1,t2,t3 where target uses t2,t3,t4 (target burns one extra ugen temp () earlier). Tried: store/temp orders, next/temp locals in either block, while forms, casts, u32/ordering of compare, permuter 2x~1000s best 25 (hint: curr->next = temp = scan->next reorder, worse)
ActorCallbackNode *actorCallbackListSort(ActorCallbackNode *head) {
    ActorCallbackNode *new_head = head;
    ActorCallbackNode *curr;
    ActorCallbackNode *scan;
    s32 inserted;
    ActorCallbackNode *temp;

    if (head != NULL) {
        curr = head->next;
        if (curr != NULL) {
            do {
                scan = curr->prev;
                inserted = 0;
                if (scan != NULL) {
                    do {
                        if ((s32)curr->callback >= (s32)scan->callback) {
                            inserted = 1;
                            curr->prev->next = curr->next;
                            if (curr->next != NULL) {
                                curr->next->prev = curr->prev;
                            }
                            temp = scan->next;
                            scan->next = curr;
                            curr->next = temp;
                            if (temp != NULL) {
                                temp->prev = curr;
                            }
                            curr->prev = scan;
                        }
                        scan = scan->prev;
                    } while ((scan != NULL) && (!inserted));
                }
                if (!inserted) {
                    curr->prev->next = curr->next;
                    if (curr->next != NULL) {
                        curr->next->prev = curr->prev;
                    }
                    curr->prev = NULL;
                    curr->next = new_head;
                    new_head->prev = curr;
                    new_head = curr;
                }
                curr = curr->next;
            } while (curr != NULL);
        }
    }
    return new_head;
}

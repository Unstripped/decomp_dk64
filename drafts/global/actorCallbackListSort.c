// actorCallbackListSort (src/global/7CA80.c): stage 5: 5 diff lines, only second-block unlink temps t1,t2,t3 vs target t2,t3,t4 (one ring slot consumed between block 1 (t8,t9,t0) and block 2). LgDisp2 tried: ==0/!=1 forms, while(!inserted&&scan), temp var for curr->next in either block, expression-statement nodes (dropped), 108 spelling combos: no change.
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

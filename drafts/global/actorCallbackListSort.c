// actorCallbackListSort (src/global/7CA80.c): W2Ring stage 5: 5 diff lines (block-1 third unlink temp / block-2 unlink temps t1,t2,t3 vs target t2,t3,t4). Best hack: dead 'if ((s16)curr) {}' anywhere in block 1 (lines after first unlink) burns the slot -> block 2 matches but block 1 third temp becomes t1 vs target t0 (2 hunks); burn must land after t0 and before t2: dead stmts in block 2/loop tail don't burn or shift t6. Tried: deadsweep (curr/scan/inserted/new_head + s16/u8 forms + expression forms), inserted type, for/while/do-while spellings, cast wrappers, permuter (no gain).
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

// alEvtqPostEvent (src/global/13FED0.c): SynCore near-match: target size 0x180, current 0x178.
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
    if ((node = &evtq->allocList) != NULL) do {
        if (node->next == NULL) {
            item->delta = infinite != 0 ? 0 : delta;
            alLink(&item->node, node);
            goto done;
        }
        next = (ALEventListItem *)node->next;
        if (delta < next->delta) {
            item->delta = delta;
            next->delta -= delta;
            alLink(&item->node, node);
            goto done;
        }
        delta -= next->delta;
    } while ((node = node->next) != NULL);
done:
    osGetIntMask(intMask);
}

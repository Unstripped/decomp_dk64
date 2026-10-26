#include "common.h"

void alLink(ALLink *element, ALLink *after) {
    element->next = after->next;
    element->prev = after;
    if (after->next != NULL) {
        after->next->prev = element;
    }
    after->next = element;
}

void alUnlink(ALLink *element) {
    if (element->next != NULL) {
        element->next->prev = element->prev;
    }
    if (element->prev != NULL) {
        element->prev->next = element->next;
    }
}

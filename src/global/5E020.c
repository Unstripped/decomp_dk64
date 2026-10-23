#include "common.h"
#include "actor.h"

typedef struct HashNode {
    s32 key;
    s32 value;
    struct HashNode *next;
} HashNode;

extern HashNode *D_807F7370[];

void hashTableInit(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        D_807F7370[i] = NULL;
    }
}

void hashTableClear(void) {
    s32 i;
    HashNode *node;
    HashNode *next;
    for (i = 0; i < 100; i++) {
        node = D_807F7370[i];
        if (node != NULL) {
            do {
                next = node->next;
                heapFree(node);
                node = next;
            } while (node != NULL);
        }
    }
    hashTableInit();
}

s32 hashTableHashKey(s32);
void *func_80610FE8(s32);

void hashTableInsert(s32 key, s32 value) {
    HashNode *node;
    HashNode **prev;

    prev = &D_807F7370[hashTableHashKey(key)];
    node = *prev;
    while ((node != NULL) && (key != node->key)) {
        prev = &node->next;
        node = node->next;
    }
    if (node == NULL) {
        node = func_80610FE8(sizeof(HashNode));
        *prev = node;
        node->key = key;
        node->value = value;
        node->next = NULL;
    } else {
        node->value = value;
    }
}
s32 hashTableLookup(s32 arg0) {
    HashNode *node;

    node = D_807F7370[hashTableHashKey(arg0)];
    while (node != NULL) {
        if (arg0 == node->key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void hashTableRemove(s32 arg0) {
    HashNode **prev = &D_807F7370[hashTableHashKey(arg0)];
    HashNode *node = *prev;

    while ((node != NULL) && (arg0 != node->key)) {
        prev = &node->next;
        node = node->next;
    }
    if (node != NULL) {
        *prev = node->next;
        heapFree(node);
    }
}

s32 hashTableHashKey(s32 arg0) {
    s32 k = (arg0 > 0) ? arg0 : -arg0;

    return k % 100;
}

void hashTableTraverse(void) {
    s32 i;
    HashNode *node;

    for (i = 0; i < 100; i++) {
        node = D_807F7370[i];
        if (node != NULL) {
            do {
                node = node->next;
            } while (node != NULL);
        }
    }
}

void hashTableTraverseDuplicate(void) {
    s32 i;
    HashNode *node;

    for (i = 0; i < 100; i++) {
        node = D_807F7370[i];
        if (node != NULL) {
            do {
                node = node->next;
            } while (node != NULL);
        }
    }
}

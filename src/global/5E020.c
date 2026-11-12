#include "common.h"
#include "proto/global/15050.h"
#include "proto/global/5E020.h"

#define HASH_BUCKET_COUNT 100

typedef struct HashNode {
    s32 key;
    s32 value;
    struct HashNode *next;
} HashNode;

extern HashNode *gHashTableBuckets[HASH_BUCKET_COUNT];

void hashTableInit(void) {
    s32 i;

    for (i = 0; i < HASH_BUCKET_COUNT; i++) {
        gHashTableBuckets[i] = NULL;
    }
}

void hashTableClear(void) {
    s32 i;
    HashNode *node;
    HashNode *next;

    for (i = 0; i < HASH_BUCKET_COUNT; i++) {
        node = gHashTableBuckets[i];
        while (node != NULL) {
            next = node->next;
            heapFree(node);
            node = next;
        }
    }
    hashTableInit();
}

void hashTableInsert(s32 key, s32 value) {
    HashNode *node;
    HashNode **prev;

    prev = &gHashTableBuckets[hashTableHashKey(key)];
    node = *prev;

    while ((node != NULL) && (key != node->key)) {
        prev = &node->next;
        node = node->next;
    }
    if (node == NULL) {
        node = heapAlloc(sizeof(HashNode));
        *prev = node;
        node->key = key;
        node->value = value;
        node->next = NULL;
    } else {
        node->value = value;
    }
}

s32 hashTableLookup(s32 key) {
    HashNode *node = gHashTableBuckets[hashTableHashKey(key)];

    while (node != NULL) {
        if (key == node->key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void hashTableRemove(s32 key) {
    HashNode **prev = &gHashTableBuckets[hashTableHashKey(key)];
    HashNode *node = *prev;

    while ((node != NULL) && (key != node->key)) {
        prev = &node->next;
        node = node->next;
    }
    if (node != NULL) {
        *prev = node->next;
        heapFree(node);
    }
}

s32 hashTableHashKey(s32 key) {
    s32 absKey = (key > 0) ? key : -key;

    return absKey % HASH_BUCKET_COUNT;
}

void hashTableTraverse(void) {
    s32 i;
    HashNode *node;

    for (i = 0; i < HASH_BUCKET_COUNT; i++) {
        node = gHashTableBuckets[i];
        while (node != NULL) {
            node = node->next;
        }
    }
}

void hashTableTraverseDuplicate(void) {
    s32 i;
    HashNode *node;

    for (i = 0; i < HASH_BUCKET_COUNT; i++) {
        node = gHashTableBuckets[i];
        while (node != NULL) {
            node = node->next;
        }
    }
}

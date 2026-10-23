#include "common.h"
#include "actor.h"

typedef struct Cam1_Node {
    s32 key;
    s32 value;
    struct Cam1_Node *next;
} Cam1_Node;

extern Cam1_Node *D_807F7370[];

void func_80659320(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        D_807F7370[i] = NULL;
    }
}

void func_80659350(void) {
    s32 i;
    Cam1_Node *node;
    Cam1_Node *next;

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
    func_80659320();
}

s32 func_80659544(s32);
void *func_80610FE8(s32);

void func_806593C8(s32 key, s32 value) {
    Cam1_Node *node;
    Cam1_Node **prev;

    prev = &D_807F7370[func_80659544(key)];
    node = *prev;
    while ((node != NULL) && (key != node->key)) {
        prev = &node->next;
        node = node->next;
    }
    if (node == NULL) {
        node = func_80610FE8(sizeof(Cam1_Node));
        *prev = node;
        node->key = key;
        node->value = value;
        node->next = NULL;
    } else {
        node->value = value;
    }
}
s32 func_80659470(s32 arg0) {
    Cam1_Node *node;

    node = D_807F7370[func_80659544(arg0)];
    while (node != NULL) {
        if (arg0 == node->key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void func_806594C8(s32 arg0) {
    Cam1_Node **prev = &D_807F7370[func_80659544(arg0)];
    Cam1_Node *node = *prev;

    while ((node != NULL) && (arg0 != node->key)) {
        prev = &node->next;
        node = node->next;
    }
    if (node != NULL) {
        *prev = node->next;
        heapFree(node);
    }
}

#ifdef NON_MATCHING
s32 func_80659544(s32 arg0) {
    int new_var = arg0;

    if (new_var > 0) {
        return new_var % 100;
    }
    new_var = -new_var;
    return new_var % 100;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E020/func_80659544.s")
#endif

void func_80659574(void) {
    s32 i;
    Cam1_Node *node;

    for (i = 0; i < 100; i++) {
        node = D_807F7370[i];
        if (node != NULL) {
            do {
                node = node->next;
            } while (node != NULL);
        }
    }
}

void func_806595B0(void) {
    s32 i;
    Cam1_Node *node;

    for (i = 0; i < 100; i++) {
        node = D_807F7370[i];
        if (node != NULL) {
            do {
                node = node->next;
            } while (node != NULL);
        }
    }
}

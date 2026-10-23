// func_806595B0 (src/global/5E020.c): matched: for (i = 0; i < 100; i++) gives exact addiu a0/v1 order
#include "common.h"

typedef struct Cam1_Node {
    s32 key;
    s32 value;
    struct Cam1_Node *next;
} Cam1_Node;

extern Cam1_Node *D_807F7370[];

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

// func_80659350 (src/global/5E020.c): matched: for (i = 0; i < 100; i++) gives exact commutative order s3/s2 in loop setup
#include "common.h"

typedef struct Cam1_Node {
    s32 key;
    s32 value;
    struct Cam1_Node *next;
} Cam1_Node;

extern Cam1_Node *D_807F7370[];
void heapFree(void *);
void func_80659320(void);

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

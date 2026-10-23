// func_80659350 (src/global/5E020.c): stage 6, score 20: 2 insns, addiu s3/s2 commutative order in loop setup
#include "common.h"

typedef struct Cam1_Node {
    s32 key;
    s32 value;
    struct Cam1_Node *next;
} Cam1_Node;

extern Cam1_Node *D_807F7370[];
extern void *D_807F7500;
void heapFree(void *);
void func_80659320(void);

void func_80659350(void) {
    Cam1_Node **it = D_807F7370;
    Cam1_Node **end = (Cam1_Node **)&D_807F7500;
    Cam1_Node *node;
    Cam1_Node *next;

    do {
        node = *it;
        if (node != NULL) {
            do {
                next = node->next;
                heapFree(node);
                node = next;
            } while (node != NULL);
        }
        it++;
    } while (it != end);
    func_80659320();
}

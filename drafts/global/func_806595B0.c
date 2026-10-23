// func_806595B0 (src/global/5E020.c): stage 6, score 30: 2 insns, addiu a0/v1 order between D_807F7500 and D_807F7370
#include "common.h"

typedef struct Cam1_Node {
    s32 key;
    s32 value;
    struct Cam1_Node *next;
} Cam1_Node;

extern Cam1_Node *D_807F7370[];
extern void *D_807F7500;

void func_806595B0(void) {
    Cam1_Node **it;
    Cam1_Node *node;

    node = D_807F7370[0];
    it = D_807F7370;
    do {
        node = *(it++);
        if (node != NULL) {
            do {
                node = node->next;
            } while (node != NULL);
        }
    } while (it != (Cam1_Node **)&D_807F7500);
}

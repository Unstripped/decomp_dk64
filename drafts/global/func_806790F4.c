// func_806790F4 (src/global/7CA80.c): from .scratch/R3A/func_806790F4_best.c
void func_806790F4(u8 arg0) {
    ActorCallbackNode **ptr = D_807FBFE0;

    do {
        if ((*ptr != NULL) && ((*ptr)->unk4 == arg0)) {
            ((void (*)(void *))(*ptr)->callback)(&(*ptr)->unk8);
            heapFree(*ptr);
            *ptr = NULL;
        }
        ptr++;
    } while (ptr != (ActorCallbackNode **)&D_807FBFF0);
}

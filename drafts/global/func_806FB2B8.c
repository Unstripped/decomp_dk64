// func_806FB2B8 (src/global/FCCD0.c): stage 2: behavior reconstructed; list traversal and prologue differ
void func_806FB2B8(void) {
    void **allocation;
    void *node;
    s32 i;

    allocation = &D_80754284;
    if (*allocation != NULL) {
        node = *allocation;
        if (*(void **)((u8 *)node + 4) != NULL) {
            do {
                node = *(void **)((u8 *)node + 4);
            } while (*(void **)((u8 *)node + 4) != NULL);
        }
        for (i = 0; i != 0xF; i++) {
            if ((*(s32 *)node & (1 << i)) != 0) {
                func_806F8BC4(i, 1, 0);
            }
        }
        heapFree(node);
        *allocation = NULL;
    }
}

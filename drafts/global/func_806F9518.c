// func_806F9518 (src/global/FCCD0.c): stage 5: same frame/saved regs; remaining: IDO emits addu a1,v1,v0; addiu s1,a1,0x28 instead of addu s1,v0,v1 + lw 0x28(s1) + addiu s1,s1,0x28 (16 diff lines); idx-first locals fixed v0/v1
typedef struct FcAAllocNode {
    s32 type;
    u8 pad4[0x10];
    void *unk14;
    struct FcAAllocNode *next;
} FcAAllocNode;

void effectFreeAndUnlink(s32);
void heapFree(void *);

void func_806F9518(s32 arg0) {
    FcAAllocNode **var_s1;
    FcAAllocNode *temp_s0;
    FcAAllocNode **temp_s2;
    s32 idx;
    void *base;

    idx = arg0 * 0x30;
    base = D_80754280;
    ((R2FCCD0cSlot *)base)[arg0].unk20 = 0;
    var_s1 = (FcAAllocNode **)&((R2FCCD0cSlot *)(idx + (s32)base))->unk28;
    if (*var_s1 != NULL) {
        do {
            temp_s0 = *var_s1;
            temp_s2 = &temp_s0->next;
            if (temp_s0->type == 1) {
                effectFreeAndUnlink(*(s32 *)((u8 *)temp_s0->unk14 + 8));
                temp_s0 = *var_s1;
            }
            heapFree(temp_s0->unk14);
            heapFree(*var_s1);
            *var_s1 = NULL;
            var_s1 = temp_s2;
        } while (*temp_s2 != NULL);
    }
}

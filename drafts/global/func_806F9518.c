// func_806F9518 (src/global/FCCD0.c): stage 4: compiled allocation-list cleanup; saved-register schedule differs
typedef struct {
    void *unk0;
    u8 pad4[0x1C];
    s32 unk20;
    s32 unk24;
    void *unk28;
    u8 unk2C;
} Slot;

typedef struct AllocNode {
    s32 type;
    u8 pad4[0x10];
    void *unk14;
    struct AllocNode *next;
} AllocNode;

extern void *D_80754280;
void func_80715908(s32);
void heapFree(void *);

void func_806F9518(s32 arg0) {
    Slot *slot;
    AllocNode **var_s1;
    AllocNode *temp_s0;
    AllocNode **temp_s2;

    slot = &((Slot *)D_80754280)[arg0];
    slot->unk20 = 0;
    var_s1 = (AllocNode **)&slot->unk28;
    if (*var_s1 != NULL) {
        do {
            temp_s0 = *var_s1;
            temp_s2 = &temp_s0->next;
            if (temp_s0->type == 1) {
                func_80715908(*(s32 *)((u8 *)temp_s0->unk14 + 8));
                temp_s0 = *var_s1;
            }
            heapFree(temp_s0->unk14);
            heapFree(*var_s1);
            *var_s1 = NULL;
            var_s1 = temp_s2;
        } while (*temp_s2 != NULL);
    }
}

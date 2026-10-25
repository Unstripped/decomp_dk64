// func_806F4DC0 (src/global/F9450.c): Stage 4: recovered frame, traversal, allocation, and stores; head-pointer register allocation remains.
typedef struct F9A_PositionNode {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    struct F9A_PositionNode *next;
} F9A_PositionNode;

extern F9A_PositionNode *D_807FD780[];
void *func_80610FE8(s32);
void heapClearBlock(void *);
void heapFreeDeferred(void *);

void func_806F4DC0(u8 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    F9A_PositionNode **var_v1;
    F9A_PositionNode *var_v0;
    F9A_PositionNode *temp_v0;

    var_v1 = &D_807FD780[arg0];
    if (*var_v1 != NULL) {
        var_v0 = *var_v1;
        do {
            var_v1 = &var_v0->next;
            var_v0 = var_v0->next;
        } while (var_v0 != NULL);
    }
    temp_v0 = func_80610FE8(0x14);
    *var_v1 = temp_v0;
    heapClearBlock(temp_v0);
    (*var_v1)->unk0 = arg1;
    (*var_v1)->unk4 = arg2;
    (*var_v1)->unk8 = arg3;
    (*var_v1)->unkC = arg4;
    heapFreeDeferred(*var_v1);
}

// func_806F4DC0 (src/global/F9450.c): stage 1: m2c reconstruction retained for later type recovery
void *func_80610FE8(?);                             /* extern */
? heapClearBlock(void *);                           /* extern */
? heapFreeDeferred(void *);                         /* extern */
extern ? D_807FD780;

void func_806F4DC0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    void **sp1C;
    void **temp_v0;
    void **var_v1;
    void *temp_v0_2;
    void *var_v0;

    temp_v0 = ((arg0 & 0xFF) * 4) + &D_807FD780;
    var_v1 = temp_v0;
    if (*temp_v0 != NULL) {
        var_v0 = *temp_v0;
        do {
            var_v1 = var_v0 + 0x10;
            var_v0 = var_v0->unk10;
        } while (var_v0 != NULL);
    }
    sp1C = var_v1;
    temp_v0_2 = func_80610FE8(0x14);
    *var_v1 = temp_v0_2;
    heapClearBlock(temp_v0_2);
    (*var_v1)->unk0 = arg1;
    (*var_v1)->unk4 = arg2;
    (*var_v1)->unk8 = arg3;
    (*var_v1)->unkC = arg4;
    heapFreeDeferred(*var_v1);
}

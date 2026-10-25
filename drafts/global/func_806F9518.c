// func_806F9518 (src/global/FCCD0.c): m2c behavioural starter; 44-insn linked allocation cleanup.
? func_80715908(s32);                               /* extern */
? heapFree(void *);                                 /* extern */
extern s32 D_80754280;

void func_806F9518(s32 arg0) {
    s32 temp_v0;
    void **var_s1;
    void *temp_s0;
    void *temp_s1;

    temp_v0 = arg0 * 0x30;
    (D_80754280 + temp_v0)->unk20 = 0;
    temp_s1 = temp_v0 + D_80754280;
    var_s1 = temp_s1 + 0x28;
    if (temp_s1->unk28 != 0) {
        do {
            temp_s0 = *var_s1;
            if (temp_s0->unk0 == 1) {
                func_80715908(temp_s0->unk14->unk8);
            }
            heapFree((*var_s1)->unk14);
            heapFree(*var_s1);
            *var_s1 = NULL;
            var_s1 = temp_s0 + 0x18;
        } while (temp_s0->unk18 != 0);
    }
}

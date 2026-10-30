// func_8061324C (src/global/17B90.c): stage 1; m2c starter retained. Remaining: table-entry/node types, nested scan loop, and allocation-list writeback.
drafts/global/func_8061324C.c
// func_8061324C (src/global/17B90.c): stage 1: m2c starter; needs concrete command/list-node structs and loop/control-flow matching
void *heapAlloc(?);                             /* extern */

void func_8061324C(void *arg0, s32 arg1, void **arg2) {
    s32 var_v1;
    u32 temp_s1;
    u32 temp_v1;
    void **var_s5;
    void *temp_v0;
    void *var_s0;
    void *var_s3;

    var_s5 = arg2;
    var_s3 = arg0;
    if (arg0 != arg1) {
        do {
            temp_v1 = var_s3->unk0;
            if (((temp_v1 >> 0x18) == 0xDE) && (((temp_v1 >> 0x10) & 0xFF) == 1)) {
                var_s0 = arg0;
                var_v1 = 0;
                temp_s1 = (u32) (var_s3->unk4 * 0x10) >> 0x1C;
                if (arg0 != arg1) {
loop_5:
                    if ((((u32) var_s0->unk0 >> 0x18) == 0) && (temp_s1 == var_s0->unk4)) {
                        var_v1 = 1;
                    } else {
                        var_s0 += 8;
                    }
                    if ((var_v1 == 0) && (var_s0 != arg1)) {
                        goto loop_5;
                    }
                }
                temp_v0 = heapAlloc(0x10);
                *var_s5 = temp_v0;
                var_s5 = temp_v0 + 0xC;
                temp_v0->unk8 = (s8) temp_s1;
                temp_v0->unk0 = (void *) (var_s3 + 8);
                temp_v0->unk4 = var_s0;
            }
            var_s3 += 8;
        } while (var_s3 != arg1);
    }
    *var_s5 = NULL;
}

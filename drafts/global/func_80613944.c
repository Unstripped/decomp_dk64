// func_80613944 (src/global/17B90.c): stage 1: m2c starter recovered from local asm; requires typed cache entry/controller views and C compile
? assetFreeBuffer(s32, ?, ?, u16 *);                /* extern */
extern ? D_807FB7B0;
extern u16 D_807FBB32;

void func_80613944(void *arg0, s32 *arg1) {
    ? *sp18;
    ? *var_v1;
    s32 temp_a2;
    s32 temp_t9;
    s32 var_v0;
    u16 temp_t2;
    void *temp_v0;
    void *temp_v0_2;

    temp_a2 = *arg1;
    if (temp_a2 != 0) {
        var_v1 = &D_807FB7B0;
        var_v0 = 0;
        if ((s32) D_807FBB32 > 0) {
loop_2:
            var_v0 += 1;
            if (temp_a2 == var_v1->unk8) {
                temp_t9 = var_v1->unk4 - 1;
                var_v1->unk4 = temp_t9;
                if (temp_t9 == 0) {
                    sp18 = var_v1;
                    assetFreeBuffer(var_v1->unk8, 0x298, 0x15, &D_807FBB32);
                    temp_t2 = D_807FBB32 - 1;
                    temp_v0 = ((temp_t2 & 0xFFFF) * 0xC) + &D_807FB7B0;
                    D_807FBB32 = temp_t2;
                    var_v1->unk0 = (s32) temp_v0->unk0;
                    var_v1->unk8 = (s32) temp_v0->unk8;
                    var_v1->unk4 = (s32) temp_v0->unk4;
                    temp_v0->unk0 = 0xFFFF;
                    temp_v0->unk8 = 0;
                    temp_v0->unk4 = 0;
                }
            } else {
                var_v1 += 0xC;
                if (var_v0 < (s32) D_807FBB32) {
                    goto loop_2;
                }
            }
        }
        *arg1 = 0;
    }
    temp_v0_2 = arg0->unk4;
    if (arg1 == temp_v0_2->unk4) {
        temp_v0_2->unk84 = 0;
    }
}

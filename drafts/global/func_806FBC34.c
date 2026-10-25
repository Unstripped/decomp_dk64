// func_806FBC34 (src/global/100180.c): Stage 1 m2c draft saved; resource cleanup loop remains.
? assetFreeBuffer(s32, ?, ?);                       /* extern */
extern ? D_80754A34;
extern s32 D_807FD7F0;
extern s32 D_807FD7F4;

void func_806FBC34(void) {
    s16 temp_t0;
    s16 var_s0;
    s16 var_s1;
    s16 var_s5;
    void *temp_s3;
    void *temp_v0;

    var_s0 = 0;
    var_s5 = 0;
    do {
        var_s1 = 0;
        temp_s3 = &D_80754A34 + (var_s5 * 6);
        if ((s32) temp_s3->unk1 > 0) {
            do {
                temp_t0 = var_s0 + 1;
                var_s0 = temp_t0;
                if (*(var_s0 + D_807FD7F4) != 0) {
                    temp_v0 = D_807FD7F4 + temp_t0;
                    temp_v0->unk-1 = (u8) (temp_v0->unk-1 - 1);
                    if ((D_807FD7F4 + temp_t0)->unk-1 == 0) {
                        assetFreeBuffer((D_807FD7F0 + (temp_t0 * 4))->unk-4, 0x156, 0x23);
                    }
                }
                var_s1 += 1;
            } while (var_s1 < (s32) temp_s3->unk1);
        }
        var_s5 += 1;
    } while (var_s5 < 8);
}

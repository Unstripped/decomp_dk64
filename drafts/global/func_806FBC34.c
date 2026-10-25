// func_806FBC34 (src/global/100180.c): Stage 3: full body and stack/register set match; remaining allocation differs for the outer and inner s16 counters.
extern void *D_807FD7F0;
extern u8 *D_807FD7F4;
extern u8 D_80754A34[];
void assetFreeBuffer(void *, s32, s32);

void func_806FBC34(void) {
    s16 temp_t0;
    s16 var_s0;
    s16 var_s1;
    s16 var_s5;
    u8 *temp_s3;
    u8 *temp_v0;

    var_s0 = 0;
    var_s5 = 0;
    do {
        var_s1 = 0;
        temp_s3 = D_80754A34 + (var_s5 * 6);
        if (temp_s3[1] > 0) {
            do {
                temp_t0 = var_s0 + 1;
                var_s0 = temp_t0;
                if (*(var_s0 + D_807FD7F4) != 0) {
                    temp_v0 = D_807FD7F4 + temp_t0;
                    temp_v0[-1] = temp_v0[-1] - 1;
                    if ((D_807FD7F4 + temp_t0)[-1] == 0) {
                        assetFreeBuffer(*(void **)((u8 *) D_807FD7F0 + (temp_t0 * 4) - 4), 0x156, 0x23);
                    }
                }
                var_s1 += 1;
            } while (var_s1 < temp_s3[1]);
        }
        var_s5 += 1;
    } while (var_s5 < 8);
}

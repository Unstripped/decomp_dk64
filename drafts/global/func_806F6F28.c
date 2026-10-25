// func_806F6F28 (src/global/F9450.c): Stage 1 m2c starter; reviewed 96-instruction caller/update flow.
? func_806F603C();                                  /* extern */
? func_806F69A8(s32);                               /* extern */
s32 func_806F6E58(u8);                              /* extern */
s32 func_8073110C(?, ?);                            /* extern */
extern u8 D_8074E77C;
extern s32 D_807FBB64;
extern s32 D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FD738;

void func_806F6F28(void) {
    u8 sp45;
    s32 temp_lo;
    s32 temp_t7;
    s32 var_fp;
    s32 var_s0;
    void *temp_v0;

    var_fp = 0;
    sp45 = 0;
    if (D_807FBB64 & 0x10000) {
        func_806F603C();
    }
    if (func_8073110C(0x179, 0) != 0) {
        var_fp = 1;
    }
    if (func_806F6E58(D_8074E77C) != 0) {
        sp45 = 1;
    }
    var_s0 = 0;
    if ((s32) D_807FC928 > 0) {
        do {
            temp_lo = var_s0 * 0x2F0;
            temp_v0 = (D_807FC924 + temp_lo)->unk4->unk174;
            if (var_fp != 0) {
                temp_v0->unk1F4 = (s32) (temp_v0->unk1F4 | 1);
            } else {
                temp_v0->unk1F4 = (s32) (temp_v0->unk1F4 & ~1);
            }
            if (sp45 != 0) {
                temp_v0->unk1F4 = (s32) (temp_v0->unk1F4 | 2);
            } else {
                temp_v0->unk1F4 = (s32) (temp_v0->unk1F4 & ~2);
            }
            if (((D_807FC924 + temp_lo)->unk4->unk154 != 0x36) && (D_807FD738 == 0)) {
                func_806F69A8(var_s0 & 0xFF);
            }
            temp_t7 = (var_s0 + 1) & 0xFF;
            var_s0 = temp_t7;
        } while (temp_t7 < (s32) D_807FC928);
    }
}

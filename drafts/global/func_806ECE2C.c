// func_806ECE2C (src/global/EFDC0.c): stage 1: m2c reconstruction of conditional transition; needs camera-block and player-state views
? func_80614D00(void *, ?, ?);                      /* extern */
? func_80614E78(void *, ?);                         /* extern */
? func_806CF42C(void *);                            /* extern */
? func_806CFE7C();                                  /* extern */
extern void *D_807FBB48;
extern s32 D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806ECE2C(void) {
    if (((s32) D_807FC928 >= 2) || (D_807FBB48->unk58 != 6) || ((D_807FC924 + (D_807FC929 * 0x2F0))->unk2C0 == 1)) {
        D_807FBB48->unkC0 = 260.0f;
        func_806CFE7C();
        D_807FD580->unk50 = 0;
        D_807FD580->unk48 = 0x64;
        func_80614E78(D_807FBB48, 0x1F);
        func_80614D00(D_807FBB48, 0x3F800000, 0);
        D_807FBB48->unk154 = 0x30;
        D_807FBB48->unk155 = 0;
        func_806CF42C(D_807FBB48);
    }
}

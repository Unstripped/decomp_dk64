// func_80700AE4 (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
extern s16 D_80744490;
extern ? D_80754BC4;
extern s32 D_8076A060;
extern void *D_807FC924;

s32 func_80700AE4(s16 arg0, s16 arg1) {
    ? sp18;
    u16 temp_a2;
    void *temp_t1;

    M2C_MEMCPY_ALIGNED(&sp18, &D_80754BC4, 0x3C);
    sp18.unk3C = (s32) D_80754BC4.unk3C;
    if ((arg0 < D_807FC924->unk270) || (D_807FC924->unk274 < arg0) || (arg1 < D_807FC924->unk272) || (D_807FC924->unk276 < arg1)) {
        return 0xFFFF;
    }
    temp_a2 = *(D_8076A060 + (((D_80744490 * arg1) + arg0) * 2));
    temp_t1 = &sp18 + ((((s32) temp_a2 >> 0xD) & 7) * 8);
    return ((u32) (temp_t1->unk4 + ((((s32) temp_a2 >> 2) & 0x7FF) << temp_t1->unk0)) >> 3) & 0xFFFF;
}

// func_8070068C (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
extern ? D_2000100;
extern u8 D_807444FC;
extern void *D_807FC924;

void *func_8070068C(void *arg0) {
    void *sp18;
    void *temp_a2;

    arg0->unk0 = 0xDA380007;
    arg0->unk4 = &D_2000100;
    temp_a2 = arg0 + 8;
    arg0->unk8 = 0xDC080008;
    arg0 = temp_a2 + 8;
    sp18 = temp_a2;
    temp_a2->unk4 = osVirtualToPhysical(D_807FC924 + (D_807444FC * 0x10) + 0x250);
    arg0->unk0 = (s32) (((s32) ((f32) D_807FC924->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) ((f32) D_807FC924->unk270 * 4.0f) & 0xFFF) << 0xC));
    arg0->unk4 = (? *) (((s32) ((f32) D_807FC924->unk276 * 4.0f) & 0xFFF) | (((s32) ((f32) D_807FC924->unk274 * 4.0f) & 0xFFF) << 0xC));
    return arg0 + 8;
}

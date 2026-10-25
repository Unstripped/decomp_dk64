// func_8070770C (src/global/109660.c): Stage 1 compiled display-list reconstruction; m2c starter records all command words and view dimensions.
extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;
extern void *D_807FC924;

void *func_8070770C(void *arg0) {
    void *sp1C;
    void *spC;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_t3;
    void *temp_t3_2;
    void *temp_t4;
    void *temp_t4_2;
    void *temp_t5;
    void *temp_t5_2;

    temp_t3 = arg0 + 8;
    arg0->unk0 = 0xE7000000;
    arg0->unk4 = 0;
    temp_t4 = temp_t3 + 8;
    arg0->unk8 = 0xE200001C;
    temp_t3->unk4 = 0;
    temp_t3->unk8 = 0xF7000000;
    temp_t4->unk4 = 0x10001;
    temp_t5 = temp_t4 + 8;
    temp_t5->unk4 = 0x300000;
    temp_t4->unk8 = 0xE3000A01;
    temp_a0_2 = temp_t5 + 8;
    sp1C = temp_a0_2;
    temp_t3_2 = temp_a0_2 + 8;
    temp_t4_2 = temp_t3_2 + 8;
    temp_t5_2 = temp_t4_2 + 8;
    temp_a0 = temp_t5_2 + 8;
    sp1C->unk0 = (s32) ((((s32) ((f32) D_80744498 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32) ((f32) D_8074449C * 4.0f) & 0xFFF));
    sp1C->unk4 = (s32) ((((s32) ((f32) D_807444A0 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) D_807444A4 * 4.0f) & 0xFFF));
    temp_a0_2->unk8 = (s32) ((((D_807444A0 - 1) & 0x3FF) << 0xE) | 0xF6000000 | (((D_807444A4 - 1) & 0x3FF) * 4));
    temp_t3_2->unk4 = (s32) (((D_80744498 & 0x3FF) << 0xE) | ((D_8074449C & 0x3FF) * 4));
    temp_t4_2->unk4 = 0;
    temp_t3_2->unk8 = 0xE7000000;
    temp_t4_2->unk8 = (s32) (((s32) ((f32) D_807FC924->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) ((f32) D_807FC924->unk270 * 4.0f) & 0xFFF) << 0xC));
    temp_t5_2->unk4 = (s32) (((s32) ((f32) D_807FC924->unk276 * 4.0f) & 0xFFF) | (((s32) ((f32) D_807FC924->unk274 * 4.0f) & 0xFFF) << 0xC));
    spC = temp_a0;
    spC->unk0 = 0xE3000A01;
    spC->unk4 = 0;
    return temp_a0 + 8;
}

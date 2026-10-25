// func_80703374 (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;

void *func_80703374(void *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_a0_7;
    void *temp_a0_8;
    void *temp_a0_9;
    void *var_a0;

    var_a0 = arg0;
    if (arg4 != 0) {
        temp_a0 = var_a0 + 8;
        var_a0->unk0 = 0xD9000000;
        var_a0->unk4 = 0;
        temp_a0_2 = temp_a0 + 8;
        var_a0->unk8 = 0xD9FFFFFF;
        temp_a0->unk4 = 0x200004;
        temp_a0_3 = temp_a0_2 + 8;
        temp_a0->unk8 = 0xD7000000;
        temp_a0_2->unk4 = -1;
        temp_a0_4 = temp_a0_3 + 8;
        temp_a0_2->unk8 = 0xE7000000;
        temp_a0_3->unk4 = 0;
        temp_a0_4->unk4 = 0x504340;
        temp_a0_5 = temp_a0_4 + 8;
        temp_a0_3->unk8 = 0xE200001C;
        temp_a0_4->unk8 = 0xFA000000;
        temp_a0_6 = temp_a0_5 + 8;
        temp_a0_5->unk4 = (s32) (((arg1 & 0xFF) << 0x18) | ((arg2 & 0xFF & 0xFF) << 0x10) | ((arg3 & 0xFF & 0xFF) << 8) | arg4);
        temp_a0_7 = temp_a0_6 + 8;
        temp_a0_5->unk8 = 0xE3000A01;
        temp_a0_6->unk4 = 0;
        temp_a0_7->unk4 = 0xFFFDF6FB;
        temp_a0_6->unk8 = 0xFCFFFFFF;
        temp_a0_8 = temp_a0_7 + 8;
        temp_a0_9 = temp_a0_8 + 8;
        var_a0 = temp_a0_9 + 8;
        temp_a0_7->unk8 = (s32) ((((s32) ((f32) D_80744498 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32) ((f32) D_8074449C * 4.0f) & 0xFFF));
        temp_a0_8->unk4 = (s32) ((((s32) ((f32) D_807444A0 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) D_807444A4 * 4.0f) & 0xFFF));
        temp_a0_8->unk8 = (s32) (((D_807444A0 & 0x3FF) << 0xE) | 0xF6000000 | ((D_807444A4 & 0x3FF) * 4));
        temp_a0_9->unk4 = (s32) (((D_80744498 & 0x3FF) << 0xE) | ((D_8074449C & 0x3FF) * 4));
    }
    var_a0->unk0 = 0xE7000000;
    var_a0->unk4 = 0;
    return var_a0 + 8;
}

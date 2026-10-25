// func_807035C4 (src/global/103AB0.c): Compiled display-list draft; exact code size, frame/register allocation remains unmatched.
s32 func_80611A44(s16);                             /* extern */
extern void *D_807FC924;

void *func_807035C4(void *arg0, ? arg1) {
    s16 temp_a0;
    s16 temp_s2;
    s16 temp_t8;
    s16 var_s1;
    s32 *temp_v1;
    s32 *var_s0;
    s32 temp_t2;
    void *temp_s0;
    void *temp_s0_10;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;

    temp_s0 = arg0 + 8;
    arg0->unk0 = 0xE7000000;
    arg0->unk4 = 0;
    arg0->unk8 = 0xE200001C;
    temp_s0->unk4 = 0x504340;
    temp_s0_2 = temp_s0 + 8;
    temp_s0_3 = temp_s0_2 + 8;
    temp_s0_2->unk4 = -1;
    temp_s0->unk8 = 0xD7000000;
    temp_s0_4 = temp_s0_3 + 8;
    temp_s0_3->unk4 = 0xC8C8C880;
    temp_s0_2->unk8 = 0xFA000000;
    temp_s0_5 = temp_s0_4 + 8;
    temp_s0_3->unk8 = 0xE3000A01;
    temp_s0_4->unk4 = 0;
    temp_s0_6 = temp_s0_5 + 8;
    temp_s0_5->unk4 = -0x805;
    temp_s0_4->unk8 = 0xFC71FEE3;
    temp_s0_6->unk4 = 0x4D4394;
    temp_s0_5->unk8 = 0xED028028;
    temp_s0_7 = temp_s0_6 + 8;
    temp_s0_6->unk8 = (s32) (((D_807FC924->unk276 & 0x3FF) * 4) | 0xF64D4000);
    temp_s0_8 = temp_s0_7 + 8;
    temp_s0_7->unk4 = (s32) (((D_807FC924->unk272 & 0x3FF) * 4) | 0x28000);
    temp_s0_9 = temp_s0_8 + 8;
    temp_s0_8->unk4 = 0;
    temp_s0_7->unk8 = 0xE7000000;
    temp_s0_10 = temp_s0_9 + 8;
    temp_s0_9->unk4 = 0xFF;
    temp_s0_8->unk8 = 0xFA000000;
    temp_s0_10->unk4 = 0xFFFDF6FB;
    temp_s0_9->unk8 = 0xFCFFFFFF;
    var_s0 = temp_s0_10 + 8;
    var_s1 = 0;
    do {
        temp_a0 = D_807FC924->unk272;
        temp_s2 = temp_a0 + ((s32) (func_80611A44() >> 0xF) % (s32) (D_807FC924->unk276 - temp_a0));
        temp_t8 = var_s1 + 1;
        temp_t2 = ((temp_s2 + (((s32) (func_80611A44(temp_a0) >> 0xF) % 10) + 2)) & 0x3FF) * 4;
        temp_v1 = var_s0;
        var_s1 = temp_t8;
        temp_v1->unk4 = (s32) (((temp_s2 & 0x3FF) * 4) | 0x28000);
        var_s0 += 8;
        temp_v1->unk0 = temp_t2 | 0xF64D4000;
    } while (temp_t8 < 0xA);
    var_s0->unk0 = 0xE7000000;
    var_s0->unk4 = 0;
    return var_s0 + 8;
}

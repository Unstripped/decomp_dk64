// func_806134B4 (src/global/17B90.c): stage 1: m2c starter; needs full local allocation-state structs and rodata literal ownership
? *func_80610FE8(s32);                              /* extern */
void *func_80612E90(s32, ?, s32);                   /* extern */

s32 func_806134B4(void *arg0, s32 arg1) {
    ? *temp_v0_2;
    ? *temp_v1;
    ? *temp_v1_2;
    s32 temp_a3;
    s32 temp_s1;
    s32 var_s0;
    void *temp_v0;

    temp_a3 = arg1 & 0xFFFF;
    temp_v0 = func_80612E90(temp_a3, 0, temp_a3);
    if (temp_v0 != NULL) {
        arg0->unk0 = temp_v0;
        arg0->unk4C = 0;
        arg0->unk50 = 0;
        temp_v0_2 = func_80610FE8((temp_v0->unk20 << 7) + 0x170);
        arg0->unk4 = temp_v0_2;
        *temp_v0_2 = temp_v0_2 + 0x90;
        arg0->unk4->unk4 = (? *) (temp_v0_2 + 0xC8);
        arg0->unk4->unk8 = (? *) (temp_v0_2 + 0x100);
        var_s0 = 0;
        arg0->unk4->unkC = (? *) (temp_v0_2 + 0x138);
        arg0->unk4->unk14 = (? *) (temp_v0_2 + 0x170);
        temp_v1 = arg0->unk4;
        temp_v1->unk18 = (void *) (temp_v1->unk14 + (temp_v0->unk20 << 6));
        if ((s32) temp_v0->unk20 > 0) {
            do {
                temp_s1 = var_s0 << 6;
                guMtxIdent(arg0->unk4->unk14 + temp_s1);
                guMtxIdent(arg0->unk4->unk18 + temp_s1);
                var_s0 += 1;
            } while (var_s0 < (s32) temp_v0->unk20);
        }
        guMtxIdentF(arg0 + 0xC);
        temp_v1_2 = arg0->unk4;
        temp_v1_2->unk1C = 0;
        temp_v1_2->unk20 = 0;
        temp_v1_2->unk24 = 0;
        temp_v1_2->unk34 = 0.15f;
        temp_v1_2->unk38 = 0.15f;
        temp_v1_2->unk3C = 0.15f;
        temp_v1_2->unk0->unk4 = 0.0f;
        temp_v1_2->unk0->unk8 = 0.0f;
        temp_v1_2->unk0->unk0 = NULL;
        temp_v1_2->unk0->unk10 = -1;
        temp_v1_2->unk0->unk1C = 0;
        temp_v1_2->unk0->unk14 = 0.0f;
        temp_v1_2->unk0->unk18 = 0.0f;
        temp_v1_2->unk0->unk24 = 1.0f;
        temp_v1_2->unk0->unk34 = 0.0f;
        temp_v1_2->unk4->unk0 = NULL;
        temp_v1_2->unk4->unk34 = 0.0f;
        temp_v1_2->unk8->unk0 = NULL;
        temp_v1_2->unk8->unk34 = 0.0f;
        temp_v1_2->unkC->unk0 = NULL;
        temp_v1_2->unkC->unk34 = 0.0f;
        temp_v1_2->unk68 = 0;
        temp_v1_2->unk64 = 0;
        temp_v1_2->unk70 = 0;
        temp_v1_2->unk78 = 0;
        temp_v1_2->unk7C = 0;
        temp_v1_2->unk84 = 0;
        temp_v1_2->unk88 = 0;
        temp_v1_2->unk10 = 0.0f;
        temp_v1_2->unk44 = 0.0f;
        temp_v1_2->unk58 = 0.0f;
        temp_v1_2->unk48 = 1.0f;
        temp_v1_2->unk80 = 0.0f;
        return 1;
    }
    return 0;
}

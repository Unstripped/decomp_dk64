// func_80714778 (src/global/119370.c): Stage 1 m2c-derived draft; not compiled to a match.
void *func_80610FE8(s32, void *);                   /* extern */
? func_807146E0(void *, void *, void *);            /* extern */
? func_807146F4(void *, void *, void *);            /* extern */
extern void *D_807FDB00;

void func_80714778(void *arg0) {
    void *sp2C;
    void *sp28;
    s32 sp20;
    s32 temp_lo;
    s32 temp_t0;
    s32 var_a0;
    s32 var_v0;
    s32 var_v0_2;
    void *temp_t4;
    void *temp_v0;
    void *var_a3;
    void *var_v1;

    var_v1 = D_807FDB00;
    var_a3 = NULL;
    if (var_v1 != NULL) {
loop_1:
        var_a3 = var_v1;
        if (arg0 != var_v1->unk0) {
            var_v1 = var_v1->unk24;
            if (var_v1 == NULL) {
                goto block_3;
            }
            goto loop_1;
        }
    } else {
block_3:
        sp2C = var_a3;
        temp_v0 = func_80610FE8(0x28, var_a3);
        temp_v0->unk24 = 0;
        temp_v0->unk0 = arg0;
        temp_v0->unk4 = (s32) arg0->unk0;
        sp28 = temp_v0;
        func_807146E0(arg0, temp_v0 + 8, temp_v0 + 9);
        sp28->unkA = (u8) arg0->unk6;
        sp28->unkB = (u8) arg0->unk7;
        sp28->unk10 = (u8) arg0->unk8;
        sp28->unk11 = (u8) arg0->unk9;
        sp28->unk12 = (u8) arg0->unkA;
        sp28->unk13 = (u8) arg0->unkB;
        sp28->unk14 = (u8) arg0->unkC;
        sp28->unk15 = (u8) arg0->unkD;
        func_807146F4(arg0, sp28 + 0xC, sp28 + 0xE);
        sp28->unk18 = -1;
        sp28->unk16 = (s16) arg0->unk12;
        if (D_807FDB00 != NULL) {
            var_a3->unk24 = sp28;
        } else {
            D_807FDB00 = sp28;
        }
        temp_lo = sp28->unk8 * sp28->unk9 * sp28->unk16;
        sp20 = temp_lo;
        var_a0 = 0;
        sp28->unk1C = func_80610FE8(temp_lo * 8, (void *)-1);
        if (temp_lo > 0) {
            temp_t0 = temp_lo & 3;
            if (temp_t0 != 0) {
                var_v0 = 0 * 8;
                do {
                    var_a0 += 1;
                    (sp28->unk1C + var_v0)->unk4 = -1;
                    var_v0 += 8;
                } while (temp_t0 != var_a0);
                if (var_a0 != temp_lo) {
                    goto block_11;
                }
            } else {
block_11:
                var_v0_2 = var_a0 * 8;
                do {
                    (sp28->unk1C + var_v0_2)->unk4 = -1;
                    (sp28->unk1C + var_v0_2)->unkC = -1;
                    (sp28->unk1C + var_v0_2)->unk14 = -1;
                    temp_t4 = sp28->unk1C + var_v0_2;
                    var_v0_2 += 0x20;
                    temp_t4->unk1C = -1;
                } while (var_v0_2 != (temp_lo * 8));
            }
        }
        sp28->unk20 = (void *) (arg0 + 0x14);
    }
}

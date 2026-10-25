// func_806FD094 (src/global/100180.c): Compiled stage-1 layout reconstruction; frame and matrix/display-list register allocation remain far from target.
void *func_80610FE8(s32);                           /* extern */
? func_806FB914(u8, u8 *);                          /* extern */
void *func_806FBEF0(void *, u8, s16);               /* extern */
? heapFreeDeferred(void *);                         /* extern */
extern ? D_2000000;
extern ? D_2000180;
extern ? D_2000200;
extern ? D_807549FC;
extern ? D_80754A18;
extern ? D_80754A35;
extern ? D_80754A36;

void *func_806FD094(void *arg0, void *arg1) {
    s32 spC4;
    u8 spC3;
    u8 spC2;
    s32 spBC;
    void *spB4;
    void *spB0;
    Mtx *temp_s3;
    s16 temp_a0_2;
    s16 temp_a1_2;
    s16 temp_a2_2;
    s16 temp_a3;
    s16 temp_s5;
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_t2;
    s16 temp_t7;
    s16 temp_v0_5;
    s32 temp_a0;
    s32 temp_t4;
    s32 var_s7;
    u8 temp_a1;
    u8 temp_s2;
    u8 temp_s4;
    u8 temp_t3;
    u8 temp_t8;
    void *temp_a2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s1_6;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *var_s0;
    void *var_s1;

    spBC = 0;
    temp_v0 = func_80610FE8(arg1->unkD << 6);
    var_s0 = temp_v0;
    heapFreeDeferred(temp_v0);
    temp_v0_2 = func_80610FE8(arg1->unkD << 6);
    spB0 = temp_v0_2;
    heapFreeDeferred(temp_v0_2);
    spB4 = var_s0;
    temp_s1 = arg0 + 8;
    arg0->unk4 = 0x2000;
    arg0->unk0 = 0xE3001201;
    temp_s1_2 = temp_s1 + 8;
    arg0->unk8 = 0xDA380007;
    temp_s1->unk4 = &D_2000000;
    temp_s1_3 = temp_s1_2 + 8;
    temp_s1->unk8 = 0xDA380005;
    temp_s1_2->unk4 = &D_2000200;
    temp_s1_3->unk4 = &D_2000180;
    temp_s1_2->unk8 = 0xDA380003;
    spC4 = 1;
    var_s1 = temp_s1_3 + 8;
    if ((*(&D_80754A35 + (arg1->unkC * 6)) + 1) >= 2) {
        do {
            spC2 = 0;
            var_s7 = 1;
            temp_t8 = *arg1->unk4;
            spC3 = temp_t8;
            if (temp_t8 & 0xFF) {
                do {
                    if (spC3 != 0x20) {
                        func_806FB914(arg1->unkC, &spC3);
                        temp_a1 = arg1->unkC;
                        temp_a0 = temp_a1 * 4;
                        temp_a2 = *(&D_807549FC + temp_a0) + spC4;
                        if (((s32) spC3 >= (s32) temp_a2->unk-1) && ((s32) spC3 < (s32) temp_a2->unk0)) {
                            temp_v0_3 = *(&D_80754A18 + temp_a0) + (spC3 * 4);
                            temp_s4 = temp_v0_3->unk2;
                            temp_s5 = temp_v0_3->unk0;
                            temp_s2 = *(&D_80754A36 + (temp_a1 * 6));
                            if (spC2 == 0) {
                                spC2 = 1;
                                var_s1 = func_806FBEF0(var_s1, temp_a1, unkspC6);
                            }
                            temp_v0_4 = arg1->unk8 + (spBC * 0x38);
                            temp_s3 = (spBC << 6) + spB0;
                            guPosition(temp_s3, temp_v0_4->unk18 * 57.295776f, temp_v0_4->unk1C * 57.295776f, temp_v0_4->unk20 * 57.295776f, temp_v0_4->unk30, temp_v0_4->unk0, temp_v0_4->unk4, temp_v0_4->unk8);
                            temp_s1_4 = var_s1 + 8;
                            var_s1->unk0 = 0xDA380003;
                            var_s1->unk4 = temp_s3;
                            var_s1->unk8 = 0xE7000000;
                            temp_s1_4->unk4 = 0;
                            temp_a0_2 = temp_s4 * 2;
                            temp_a2_2 = temp_s2 * 2;
                            temp_t1 = temp_s2 << 6;
                            temp_a3 = temp_a2_2 - 1;
                            temp_a1_2 = -temp_a0_2;
                            temp_t0 = temp_s5 << 6;
                            temp_v0_5 = temp_a0_2 - 1;
                            temp_t7 = (temp_s5 + temp_s4) << 6;
                            temp_t2 = -temp_a2_2;
                            temp_s1_5 = temp_s1_4 + 8;
                            var_s0->unk0 = temp_a1_2;
                            var_s0->unk2 = temp_a3;
                            var_s0->unk4 = 0;
                            var_s0->unk8 = temp_t0;
                            var_s0->unkA = temp_t1;
                            var_s0->unk10 = temp_v0_5;
                            var_s0->unk12 = temp_a3;
                            var_s0->unk14 = 0;
                            var_s0->unk18 = temp_t7;
                            var_s0->unk1A = temp_t1;
                            var_s0->unk22 = temp_t2;
                            var_s0->unk20 = temp_v0_5;
                            var_s0->unk24 = 0;
                            var_s0->unk28 = temp_t7;
                            var_s0->unk2A = 0;
                            var_s0->unk32 = temp_t2;
                            var_s0->unk30 = temp_a1_2;
                            var_s0->unk34 = 0;
                            var_s0->unk38 = temp_t0;
                            var_s0->unk3A = 0;
                            temp_s1_4->unk8 = 0x01004008;
                            var_s0 += 0x40;
                            temp_s1_6 = temp_s1_5 + 8;
                            temp_s1_5->unk4 = osVirtualToPhysical(spB4);
                            temp_s1_6->unk4 = 0x406;
                            temp_s1_5->unk8 = 0x07000204;
                            var_s1 = temp_s1_6 + 8;
                            spB4 = var_s0;
                        }
                        spBC += 1;
                    }
                    temp_t3 = *(var_s7 + arg1->unk4);
                    var_s7 += 1;
                    spC3 = temp_t3;
                } while (temp_t3 & 0xFF);
                spBC = 0;
            }
            temp_t4 = spC4 + 1;
            spC4 = temp_t4;
        } while (temp_t4 < (*(&D_80754A35 + (arg1->unkC * 6)) + 1));
    }
    var_s1->unk0 = 0xE7000000;
    var_s1->unk4 = 0;
    return var_s1 + 8;
}

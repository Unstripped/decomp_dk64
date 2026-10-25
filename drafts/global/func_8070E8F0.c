// func_8070E8F0 (src/global/1135F0.c): Stage 1: full m2c switch/display-list draft compiled through fdiff using a local view wrapper; 0x158 frame vs target 0xC8 and pointer-view aliases still alter every block. Stage 2 not reached.
extern void *D_807550D0;
extern s16 D_807FD9D0;
extern s16 D_807FD9D2;
extern u8 D_807FD9D4;
extern u8 D_807FD9D5;

void func_8070E8F0(s32 **arg0, void *arg1) {
    void *sp94;
    s32 *sp90;
    void *sp74;
    void *sp60;
    void *sp5C;
    void *sp58;
    void *sp40;
    void *sp3C;
    void *sp24;
    s32 *sp20;
    void *sp8;
    s32 *sp4;
    s16 temp_a3;
    R1135E8View *temp_v0;
    s32 *temp_v0_31;
    s32 *temp_v0_37;
    s32 *temp_v0_7;
    s32 *var_t9;
    s32 *var_v0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_t1;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 var_t8;
    u32 temp_a2;
    u32 temp_t2;
    u32 temp_t2_2;
    u32 temp_t2_3;
    u32 temp_t9;
    u32 temp_v1_3;
    u32 temp_v1_5;
    u32 var_a0;
    u32 var_a0_2;
    u32 var_a0_3;
    u32 var_a1;
    u32 var_a1_2;
    u32 var_a1_3;
    u32 var_v1;
    u32 var_v1_2;
    u32 var_v1_3;
    u8 temp_v1;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_14;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v0_17;
    void *temp_v0_18;
    void *temp_v0_19;
    void *temp_v0_20;
    void *temp_v0_21;
    void *temp_v0_22;
    void *temp_v0_23;
    void *temp_v0_24;
    void *temp_v0_25;
    void *temp_v0_26;
    void *temp_v0_27;
    void *temp_v0_28;
    void *temp_v0_29;
    void *temp_v0_2;
    void *temp_v0_30;
    void *temp_v0_32;
    void *temp_v0_33;
    void *temp_v0_34;
    void *temp_v0_35;
    void *temp_v0_36;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_8;
    void *temp_v0_9;

    temp_v0 = *arg0;
    D_807550D0 = arg1;
    D_807FD9D0 = 0x400;
    D_807FD9D2 = 0x400;
    D_807FD9D4 = 0;
    D_807FD9D5 = 0;
    temp_v1 = D_807550D0->unkF;
    temp_a3 = D_807550D0->unk8;
    temp_t4 = D_807550D0->unkC + D_807550D0->unk12;
    switch (temp_v1) {                              /* irregular */
    case 1:
        if (!(temp_a3 & 7)) {
            temp_v0->unk0 = ((D_807550D0->unkE & 7) << 0x15) | 0xFD000000 | 0x100000;
            temp_v0_2 = temp_v0 + 8;
            temp_v0->unk4 = (s32) D_807550D0->unk0;
            temp_v0_3 = temp_v0_2 + 8;
            temp_v0->unk8 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x100000);
            temp_v0_2->unk4 = 0x07080200;
            temp_t2 = ((u32) ((temp_a3 * temp_t4) + 1) >> 1) - 1;
            temp_v0_4 = temp_v0_3 + 8;
            temp_v0_2->unk8 = 0xE6000000;
            temp_v0_3->unk4 = 0;
            temp_v0_3->unk8 = 0xF3000000;
            temp_v0_5 = temp_v0_4 + 8;
            if (temp_t2 < 0x7FFU) {
                var_a1 = temp_t2;
            } else {
                var_a1 = 0x7FF;
            }
            temp_t2_2 = (u32) temp_a3 >> 3;
            if (temp_t2_2 == 0) {
                var_a0 = 1;
            } else {
                var_a0 = temp_t2_2;
            }
            if (temp_t2_2 == 0) {
                var_v1 = 1;
            } else {
                var_v1 = temp_t2_2;
            }
            temp_v0_4->unk4 = (s32) ((((u32) (var_a0 + 0x7FF) / var_v1) & 0xFFF) | 0x07000000 | ((var_a1 & 0xFFF) << 0xC));
            temp_v0_4->unk8 = 0xE7000000;
            temp_v0_5->unk4 = 0;
            temp_v0_6 = temp_v0_5 + 8;
            sp94 = temp_v0_6;
            temp_v0_7 = temp_v0_6 + 8;
            sp94->unk0 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x80000 | ((((u32) (temp_a3 + 7) >> 3) & 0x1FF) << 9));
            sp94->unk4 = (s32) (((D_807550D0->unk4 & 0xF) << 0x14) | 0x80000 | 0x200);
            sp90 = temp_v0_7;
            var_t9 = sp90;
            *var_t9 = 0xF2000000;
            var_t8 = ((((temp_a3 - 1) * 4) & 0xFFF) << 0xC) | (((temp_t4 - 1) * 4) & 0xFFF);
            var_v0 = temp_v0_7 + 8;
block_40:
            ((R1135E8View *)var_t9)->unk4 = var_t8;
        } else {
            temp_v0->unk0 = ((D_807550D0->unkE & 7) << 0x15) | 0xFD000000 | 0x80000 | ((temp_a3 - 1) & 0xFFF);
            temp_t1 = (((u32) (temp_a3 + 8) >> 3) & 0x1FF) << 9;
            temp_v0->unk4 = (s32) D_807550D0->unk0;
            temp_v0_8 = temp_v0 + 8;
            temp_v0_9 = temp_v0_8 + 8;
            temp_v0->unk8 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x80000 | temp_t1);
            temp_v0_8->unk4 = 0x07080200;
            temp_v0_10 = temp_v0_9 + 8;
            temp_v0_8->unk8 = 0xE6000000;
            temp_v0_9->unk4 = 0;
            temp_v0_9->unk8 = 0xF4000000;
            temp_v1_2 = ((temp_a3 * 4) & 0xFFF) << 0xC;
            temp_t7 = (temp_t4 * 4) & 0xFFF;
            temp_v0_11 = temp_v0_10 + 8;
            temp_v0_10->unk4 = (s32) (temp_v1_2 | 0x07000000 | temp_t7);
            temp_v0_10->unk8 = 0xE7000000;
            temp_v0_11->unk4 = 0;
            temp_v0_12 = temp_v0_11 + 8;
            temp_v0_13 = temp_v0_12 + 8;
            temp_v0_11->unk8 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x80000 | temp_t1);
            temp_v0_12->unk4 = (s32) (((D_807550D0->unk4 & 0xF) << 0x14) | 0x80000 | 0x200);
            sp74 = temp_v0_13;
            var_v0 = temp_v0_13 + 8;
            sp74->unk0 = 0xF2000000;
            sp74->unk4 = (s32) (temp_v1_2 | temp_t7);
        }
block_41:
        *arg0 = var_v0;
        return;
    case 2:
        if (!(temp_a3 & 3)) {
            temp_v0->unk0 = ((D_807550D0->unkE & 7) << 0x15) | 0xFD000000 | 0x100000;
            temp_v0_14 = temp_v0 + 8;
            temp_v0->unk4 = (s32) D_807550D0->unk0;
            temp_v0_15 = temp_v0_14 + 8;
            temp_v1_3 = (temp_a3 * temp_t4) - 1;
            temp_v0->unk8 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x100000);
            temp_v0_14->unk4 = 0x07080200;
            temp_v0_16 = temp_v0_15 + 8;
            temp_v0_14->unk8 = 0xE6000000;
            temp_v0_15->unk4 = 0;
            temp_v0_15->unk8 = 0xF3000000;
            temp_v0_17 = temp_v0_16 + 8;
            if (temp_v1_3 < 0x7FFU) {
                var_a1_2 = temp_v1_3;
            } else {
                var_a1_2 = 0x7FF;
            }
            temp_a2 = temp_a3 * 2;
            temp_t2_3 = temp_a2 >> 3;
            if (temp_t2_3 == 0) {
                var_a0_2 = 1;
            } else {
                var_a0_2 = temp_t2_3;
            }
            if (temp_t2_3 == 0) {
                var_v1_2 = 1;
            } else {
                var_v1_2 = temp_t2_3;
            }
            temp_v0_16->unk4 = (s32) ((((u32) (var_a0_2 + 0x7FF) / var_v1_2) & 0xFFF) | 0x07000000 | ((var_a1_2 & 0xFFF) << 0xC));
            sp60 = temp_v0_17;
            temp_v0_18 = temp_v0_17 + 8;
            sp60->unk0 = 0xE7000000;
            sp60->unk4 = 0;
            sp5C = temp_v0_18;
            temp_v0_19 = temp_v0_18 + 8;
            sp5C->unk0 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x100000 | ((((u32) (temp_a2 + 7) >> 3) & 0x1FF) << 9));
            sp5C->unk4 = (s32) (((D_807550D0->unk4 & 0xF) << 0x14) | 0x80000 | 0x200);
            sp58 = temp_v0_19;
            sp58->unk0 = 0xF2000000;
            var_v0 = temp_v0_19 + 8;
            sp58->unk4 = (s32) (((((temp_a3 - 1) * 4) & 0xFFF) << 0xC) | (((temp_t4 - 1) * 4) & 0xFFF));
        } else {
            temp_v0->unk0 = ((D_807550D0->unkE & 7) << 0x15) | 0xFD000000 | 0x100000 | ((temp_a3 - 1) & 0xFFF);
            temp_v0->unk4 = (s32) D_807550D0->unk0;
            temp_a1 = (((u32) ((temp_a3 * 2) + 9) >> 3) & 0x1FF) << 9;
            temp_v0_20 = temp_v0 + 8;
            temp_v0->unk8 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x100000 | temp_a1);
            temp_v0_21 = temp_v0_20 + 8;
            temp_v0_20->unk4 = 0x07080200;
            temp_v0_22 = temp_v0_21 + 8;
            temp_v0_20->unk8 = 0xE6000000;
            temp_v0_21->unk4 = 0;
            temp_v0_21->unk8 = 0xF4000000;
            temp_v1_4 = ((temp_a3 * 4) & 0xFFF) << 0xC;
            temp_t7_2 = (temp_t4 * 4) & 0xFFF;
            temp_v0_23 = temp_v0_22 + 8;
            temp_v0_22->unk4 = (s32) (temp_v1_4 | 0x07000000 | temp_t7_2);
            temp_v0_22->unk8 = 0xE7000000;
            temp_v0_23->unk4 = 0;
            temp_v0_24 = temp_v0_23 + 8;
            sp40 = temp_v0_24;
            temp_v0_25 = temp_v0_24 + 8;
            sp40->unk0 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x100000 | temp_a1);
            sp40->unk4 = (s32) (((D_807550D0->unk4 & 0xF) << 0x14) | 0x80000 | 0x200);
            sp3C = temp_v0_25;
            sp3C->unk0 = 0xF2000000;
            var_v0 = temp_v0_25 + 8;
            sp3C->unk4 = (s32) (temp_v1_4 | temp_t7_2);
        }
        goto block_41;
    case 3:
        if (!(temp_a3 & 1)) {
            temp_v0->unk0 = ((D_807550D0->unkE & 7) << 0x15) | 0xFD000000 | 0x180000;
            temp_v0_26 = temp_v0 + 8;
            temp_v0->unk4 = (s32) D_807550D0->unk0;
            temp_v0_27 = temp_v0_26 + 8;
            temp_v1_5 = (temp_a3 * temp_t4) - 1;
            temp_v0->unk8 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x180000);
            temp_v0_26->unk4 = 0x07080200;
            temp_v0_28 = temp_v0_27 + 8;
            temp_v0_26->unk8 = 0xE6000000;
            temp_v0_27->unk4 = 0;
            temp_v0_27->unk8 = 0xF3000000;
            temp_v0_29 = temp_v0_28 + 8;
            if (temp_v1_5 < 0x7FFU) {
                var_a1_3 = temp_v1_5;
            } else {
                var_a1_3 = 0x7FF;
            }
            temp_t9 = (u32) (temp_a3 * 4) >> 3;
            if (temp_t9 == 0) {
                var_a0_3 = 1;
            } else {
                var_a0_3 = temp_t9;
            }
            if (temp_t9 == 0) {
                var_v1_3 = 1;
            } else {
                var_v1_3 = temp_t9;
            }
            temp_v0_28->unk4 = (s32) ((((u32) (var_a0_3 + 0x7FF) / var_v1_3) & 0xFFF) | 0x07000000 | ((var_a1_3 & 0xFFF) << 0xC));
            temp_v0_28->unk8 = 0xE7000000;
            temp_v0_29->unk4 = 0;
            temp_v0_30 = temp_v0_29 + 8;
            sp24 = temp_v0_30;
            temp_v0_31 = temp_v0_30 + 8;
            sp24->unk0 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x180000 | ((((u32) ((temp_a3 * 2) + 7) >> 3) & 0x1FF) << 9));
            sp24->unk4 = (s32) (((D_807550D0->unk4 & 0xF) << 0x14) | 0x80000 | 0x200);
            sp20 = temp_v0_31;
            *sp20 = 0xF2000000;
            var_t9 = sp20;
            var_t8 = ((((temp_a3 - 1) * 4) & 0xFFF) << 0xC) | (((temp_t4 - 1) * 4) & 0xFFF);
            var_v0 = temp_v0_31 + 8;
        } else {
            temp_v0->unk0 = ((D_807550D0->unkE & 7) << 0x15) | 0xFD000000 | 0x180000 | ((temp_a3 - 1) & 0xFFF);
            temp_v0->unk4 = (s32) D_807550D0->unk0;
            temp_a1_2 = (((u32) ((temp_a3 * 2) + 9) >> 3) & 0x1FF) << 9;
            temp_v0_32 = temp_v0 + 8;
            temp_v0->unk8 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x180000 | temp_a1_2);
            temp_v0_33 = temp_v0_32 + 8;
            temp_v0_32->unk4 = 0x07080200;
            temp_v0_34 = temp_v0_33 + 8;
            temp_v0_32->unk8 = 0xE6000000;
            temp_v0_33->unk4 = 0;
            temp_v0_33->unk8 = 0xF4000000;
            temp_v1_6 = ((temp_a3 * 4) & 0xFFF) << 0xC;
            temp_t6 = (temp_t4 * 4) & 0xFFF;
            temp_v0_35 = temp_v0_34 + 8;
            temp_v0_34->unk4 = (s32) (temp_v1_6 | 0x07000000 | temp_t6);
            temp_v0_34->unk8 = 0xE7000000;
            temp_v0_35->unk4 = 0;
            temp_v0_36 = temp_v0_35 + 8;
            sp8 = temp_v0_36;
            temp_v0_37 = temp_v0_36 + 8;
            sp8->unk0 = (s32) (((D_807550D0->unkE & 7) << 0x15) | 0xF5000000 | 0x180000 | temp_a1_2);
            sp8->unk4 = (s32) (((D_807550D0->unk4 & 0xF) << 0x14) | 0x80000 | 0x200);
            sp4 = temp_v0_37;
            var_t8 = temp_v1_6 | temp_t6;
            *sp4 = 0xF2000000;
            var_t9 = sp4;
            var_v0 = temp_v0_37 + 8;
        }
        goto block_40;
    }
}

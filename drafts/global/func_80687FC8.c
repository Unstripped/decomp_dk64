// func_80687FC8 (src/global/8CA50.c): stage 5: exact 197 insns, 4 insns diff at switch case 1 beql/addiu duplication, fixed temp_v0_5 reassociation
typedef struct AnimNode {
    /* 0x00 */ void **unk0;
    /* 0x04 */ void **unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x2];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ struct AnimNode *next;
} AnimNode;

void func_80687FC8(AnimNode *arg0) {
    s16 temp_a1;
    s32 temp_ft3;

    switch (arg0->unk20) {
    case 0: {
        f32 temp_fv0;
        s32 temp_lo;
        s16 temp_v0_2;

        arg0->unk14 += arg0->unk10;
        temp_fv0 = arg0->unk14;
        temp_ft3 = (s32)temp_fv0;
        arg0->unkC += temp_ft3;
        arg0->unk14 = temp_fv0 - (f32)temp_ft3;
        temp_a1 = arg0->unk1E;
        if (arg0->unkC >= temp_a1) {
            temp_lo = arg0->unkC / temp_a1;
            temp_v0_2 = arg0->unk18;
            arg0->unk1A += temp_lo;
            if (arg0->unk1A >= temp_v0_2 && temp_v0_2 != -1) {
                arg0->unkC = temp_a1 - 1;
                arg0->unk22 = 1;
                arg0->unk14 = 1.0f;
                if (arg0->unk21 == 1) {
                    arg0->unk20 = 1;
                    return;
                }
            } else {
                switch (arg0->unk21) {
                case 0:
                    arg0->unkC = arg0->unkC % temp_a1;
                    if (arg0->unkC < arg0->unk1C) {
                        arg0->unkC = arg0->unk1C;
                        return;
                    }
                    break;
                case 1:
                    if (temp_lo != 0) {
                        arg0->unk20 = 1;
                        arg0->unkC = temp_a1 - 1;
                        arg0->unk14 = 1.0f;
                        return;
                    }
                    break;
                default:
                    return;
                }
            }
        } else {
            return;
        }
        break;
    }
    case 1: {
        f32 temp_fv0_2;
        s32 temp_a2;
        s16 temp_v0_6;
        s32 temp_lo_2;

        arg0->unk14 -= arg0->unk10;
        temp_fv0_2 = arg0->unk14;
        if ((f64)temp_fv0_2 < 0.0) {
            s32 temp_v0_5 = (s32)temp_fv0_2 - 1;
            arg0->unkC = (s16)(arg0->unkC + temp_v0_5);
            arg0->unk14 = temp_fv0_2 - (f32)temp_v0_5;
        }
        if (arg0->unkC < 0) {
            temp_a2 = -arg0->unkC;
            temp_a1 = arg0->unk1E;
            temp_v0_6 = arg0->unk18;
            temp_lo_2 = temp_a2 / temp_a1;
            arg0->unk1A = (s16)(arg0->unk1A + temp_lo_2 + 1);
            if (arg0->unk1A >= temp_v0_6 && temp_v0_6 != -1) {
                arg0->unkC = 0;
                arg0->unk22 = 1;
                arg0->unk14 = 0.0f;
                if (arg0->unk21 == 1) {
                    arg0->unk20 = 0;
                    return;
                }
            } else {
                switch (arg0->unk21) {
                case 0:
                    arg0->unkC = temp_a2 % (temp_a1 - 1);
                    if (arg0->unkC != 0) {
                        arg0->unkC = (temp_a1 - arg0->unkC) - 1;
                        return;
                    }
                    break;
                case 1:
                    if ((temp_lo_2 + 1) != 0) {
                        arg0->unkC = 0;
                        arg0->unk20 = 0;
                        if (arg0->unkC < arg0->unk1C) {
                            arg0->unkC = arg0->unk1C;
                        }
                        arg0->unk14 = 0.0f;
                    }
                    break;
                default:
                    return;
                }
            }
        }
        break;
    }
    }
}

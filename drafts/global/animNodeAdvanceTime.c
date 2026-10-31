// animNodeAdvanceTime (src/global/8CA50.c): stage 5: 197 vs 198 insns, only diff: case 1 'if (temp_lo_2 + 1)' addiu lands in ring t2 instead of v0 (target beql v0,t0 + delay-slot copy addiu v0,a3,1; one ring slot shift t2/t3 after); u32 cast on temp_v0_5 add matches reassociation. Tried inc var/shared locals/switch(lo+1)/forms: fold to lo!=-1 or ring temp. Likely needs lo+1 as uopt candidate in v0
void animNodeAdvanceTime(AnimNode *arg0) {
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
            arg0->unkC = (s16)(arg0->unkC + (u32)temp_v0_5); // FAKE: u32 cast keeps the add unreassociated (-1 folded into v0)
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
                    if (temp_lo_2 + 1) {
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

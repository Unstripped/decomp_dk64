// func_8066F06C (src/global/70FD0.c): stack layout differences: 0xC0 frame with sp6C at 0x6C and curr/i at 0xB0/0xB8; logic is complete
void func_8066F06C(M70C_Sub140 *arg0) {
    s32 i;
    M70C_Struct58 *curr;
    float sp6C[4][4];
    s32 j;
    Mtx *mtx;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;
    f32 *var_s0;
    u8 var_v1;

    curr = arg0->unk98;
    if (curr != NULL) {
        if (D_8076A064 == arg0->unk88) {
            var_v1 = D_807444FC;
        } else {
            var_v1 = (D_807444FC ^ 1);
        }
        mtx = arg0->unk74[var_v1];
        i = 0;
        if (arg0->unk94 > 0) {
            do {
                var_s0 = (f32 *)curr;
                var_s1 = (f32 *)((u8 *)curr + 0x24);
                var_s2 = (f32 *)((u8 *)curr + 0x30);
                var_s3 = (f32 *)((u8 *)curr + 0x3C);
                j = 0;
                do {
                    s32 unk48 = *(s32 *)((u8 *)var_s0 + 0x48);
                    if (unk48 == -1) {
                        memcpy(sp6C, arg0->unk70, 0x40);
                        guMtxXFMF(sp6C, var_s0[0], var_s0[3], var_s0[6], var_s1, var_s2, var_s3);
                    } else {
                        guMtxXFML((Mtx *)(((unk48 >> 6) << 6) + (u8 *)mtx), var_s0[0], var_s0[3], var_s0[6], var_s1, var_s2, var_s3);
                    }
                    j += 4;
                    var_s0++;
                    var_s1++;
                    var_s2++;
                    var_s3++;
                } while (j != 0xC);
                i++;
                curr = (M70C_Struct58 *)((u8 *)curr + 0x58);
            } while (i < arg0->unk94);
        }
    }
}

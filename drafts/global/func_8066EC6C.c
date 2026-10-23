// func_8066EC6C (src/global/70FD0.c): regalloc and stack variable alignment for vector transformation loops; calls func_8066EE50
void func_8066EC6C(M70C_Sub140 *arg0) {
    float spCC[4][4];
    f32 sp80;
    f32 sp74;
    f32 sp68;
    M70C_Struct58 *sp8C;
    s32 sp118;
    Mtx *mtx;
    u8 var_v1;
    void *var_s5;
    f32 *var_s0;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;

    var_s5 = arg0->unkA0;
    if (var_s5 != NULL) {
        if (D_8076A064 == arg0->unk88) {
            var_v1 = D_807444FC;
        } else {
            var_v1 = (D_807444FC ^ 1);
        }
        mtx = arg0->unk74[var_v1];
        sp118 = 0;
        sp8C = arg0->unkA4;
        if (arg0->unk9C > 0) {
            do {
                var_s0 = (f32 *)var_s5;
                var_s2 = &sp68;
                var_s3 = &sp74;
                var_s1 = &sp80;
                do {
                    s32 unk24 = *(s32 *)((u8 *)var_s5 + 0x24);
                    if (unk24 == -1) {
                        memcpy(spCC, arg0->unk70, sizeof(spCC));
                        guMtxXFMF(spCC, var_s0[0], var_s0[3], var_s0[6], var_s2, var_s3, var_s1);
                    } else {
                        guMtxXFML((Mtx *)(((unk24 >> 6) << 6) + (u8 *)mtx), var_s0[0], var_s0[3], var_s0[6], var_s2, var_s3, var_s1);
                    }
                    var_s1++;
                    var_s0++;
                    var_s2++;
                    var_s3++;
                } while (var_s1 != &sp80 + 3);
                if (func_8066EE50(&sp68, sp8C) != 0) {
                    if (*(u8 *)((u8 *)var_s5 + 0x2A) == 0) {
                        sp8C->unk4B = 0;
                    }
                    if (*(s32 *)((u8 *)var_s5 + 0x24) == -1) {
                        sp8C->unk4E = -1;
                    } else {
                        sp8C->unk4E = (s8)(*(u32 *)((u8 *)var_s5 + 0x24) >> 6);
                    }
                    sp8C = (M70C_Struct58 *)((u8 *)sp8C + 0x58);
                }
                var_s5 = (u8 *)var_s5 + 0x2C;
                sp118++;
            } while (sp118 < arg0->unk9C);
        }
        arg0->unkA8 = sp8C;
    }
}

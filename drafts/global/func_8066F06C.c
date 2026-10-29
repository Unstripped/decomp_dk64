// func_8066F06C (src/global/70FD0.c): stage 6 (frame 0xC0 + callee-saved set equal; parked NON_MATCHING in 70FD0.c, 29 diff lines): only t5/t6/t7 temp numbering after the lw arg0 reload and the loop-tail reload order (lw t0,184 / t8,176 / t3,192) differ; stack layout matched with decl order first,i,var_v1,curr,mtx,sp6C,j,s1,s2,s3,s0,unk48,pad1; deadsweep not usable (K&R file)
typedef struct Col7C_Ent58 {
    /* 0x00 */ f32 x[9];
    /* 0x24 */ f32 out[9];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 pad57;
} Col7C_Ent58; // size = 0x58

typedef struct Col7C_Ent2C {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
} Col7C_Ent2C; // size = 0x2C

void func_8066F06C(ActorSub140 *arg0) {
    Col7C_Ent58 *first;
    s32 i;
    u8 var_v1;
    Col7C_Ent58 *curr;
    Mtx *mtx;
    float sp6C[4][4];
    s32 j;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;
    f32 *var_s0;
    u32 unk48;
    s32 pad1;

    first = arg0->unk98;
    if (first != NULL) {
        if (D_8076A064 == arg0->unk88) {
            var_v1 = D_807444FC;
        } else {
            var_v1 = (D_807444FC ^ 1);
        }
        mtx = ((Mtx **)&arg0->unk74)[var_v1];
        curr = first;
        i = 0;
        if (arg0->unk94 > 0) {
            do {
                var_s0 = (f32 *)curr;
                var_s1 = (f32 *)((u8 *)curr + 0x24);
                var_s2 = (f32 *)((u8 *)curr + 0x30);
                var_s3 = (f32 *)((u8 *)curr + 0x3C);
                for (j = 0; j != 0xC; j += 4) {
                    unk48 = *(s32 *)((u8 *)var_s0 + 0x48);
                    if ((unk48 ^ 0) == -1) { // FAKE: ^ 0 steers bne operand order
                        memcpy(sp6C, (void *)arg0->unk70, 0x40);
                        guMtxXFMF(sp6C, var_s0[0], var_s0[3], var_s0[6], var_s1, var_s2, var_s3);
                    } else {
                        guMtxXFML((Mtx *)((((unk48 >> 6) << 6)) + (u8 *)mtx), var_s0[0], var_s0[3], var_s0[6], var_s1, var_s2, var_s3);
                    }
                    var_s0++;
                    var_s1++;
                    var_s2++;
                    var_s3++;
                }
                i++;
                curr = (Col7C_Ent58 *)((u8 *)curr + 0x58);
            } while (i < arg0->unk94);
        }
    }
}

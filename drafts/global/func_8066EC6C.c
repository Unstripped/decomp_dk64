// func_8066EC6C (src/global/70FD0.c): stage 4 (frame 0x120, callee-saved set equal; parked NON_MATCHING in 70FD0.c, 90 diff lines): stack layout matched with pad arrays (padTop[1], padB[10], padE[5]); remaining: ent in s6 not s5, &sp80+3 sentinel computed per outer iteration (addiu t9,s6,12) instead of hoisted constant s8=sp+140, mtx/neg1/spCC regs shifted by one; tried scalar sp68/74/80, end ptr var, &sp80[3], cast forms
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

void func_8066EC6C(ActorSub140 *arg0) {
    s32 padTop[1];
    s32 i;
    Col7C_Ent2C *ent;
    Mtx *mtx;
    u8 var_v1;
    float spCC[4][4];
    f32 *var_s0;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;
    u32 unk24;
    s32 padB[10];
    CollisionBox *box;
    f32 sp80[3];
    f32 sp74[3];
    f32 sp68[3];
    s32 padE[5];

    ent = arg0->unkA0;
    if (ent != NULL) {
        if (D_8076A064 == arg0->unk88) {
            var_v1 = D_807444FC;
        } else {
            var_v1 = (D_807444FC ^ 1);
        }
        mtx = ((Mtx **)&arg0->unk74)[var_v1];
        i = 0;
        box = (CollisionBox *)arg0->unkA4;
        if (arg0->unk9C > 0) {
            do {
                var_s0 = (f32 *)ent;
                var_s2 = sp68;
                var_s3 = sp74;
                var_s1 = sp80;
                do {
                    unk24 = *(s32 *)((u8 *)ent + 0x24);
                    if ((unk24 ^ 0) == -1) { // FAKE: ^ 0 steers bne operand order
                        memcpy(spCC, (void *)arg0->unk70, 0x40);
                        guMtxXFMF(spCC, var_s0[0], var_s0[3], var_s0[6], var_s2, var_s3, var_s1);
                    } else {
                        guMtxXFML((Mtx *)(((unk24 >> 6) << 6) + (u8 *)mtx), var_s0[0], var_s0[3], var_s0[6], var_s2, var_s3, var_s1);
                    }
                    var_s1++;
                    var_s0++;
                    var_s2++;
                    var_s3++;
                } while (var_s1 != sp80 + 3);
                if (collisionBuildBoxFromMatrix(sp68, box) != 0) {
                    if (*(u8 *)((u8 *)ent + 0x2A) == 0) {
                        box->unk4B = 0;
                    }
                    if (*(s32 *)((u8 *)ent + 0x24) == -1) {
                        box->unk4E = -1;
                    } else {
                        box->unk4E = (s8)(*(u32 *)((u8 *)ent + 0x24) >> 6);
                    }
                    box = (CollisionBox *)((u8 *)box + 0x58);
                }
                ent = (Col7C_Ent2C *)((u8 *)ent + 0x2C);
                i++;
            } while (i < arg0->unk9C);
        }
        arg0->unkA8 = (s32)box;
    }
}

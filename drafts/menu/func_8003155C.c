// func_8003155C (src/menu/3E10.c): stage 4 (frame 0x38 + s0-s3), harness diff 13 -> 9: dead 'if ((arg1 * 4) << 2) {}' first statement (extra reference of the shared expression) fixed the 40/44(sp) spill-slot swap and the lui t3/t9 reg. Remaining: E1=arg1*4 in v1 / E2 in t7 (target E1 t7, E2 v1) and 'sll t2,s0,4' for the 373C pointer (arg1*2*2 folds). Spellings per occurrence (4 kinds x 4 forms) hill-climbed 4 times; pointer p/q locals worse (frame 64).
typedef struct MenuNM2_Sel {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    char padE[9];
    s8 unk17;
} MenuNM2_Sel;

extern f32 D_8003373C[];
extern f32 D_8003378C[];
f32 menuEvaluateSpline(f32 *, f32, f32 *);

s32 func_8003155C(void *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5, s16 *arg6) {
    f32 v;
    volatile s32 ret;
    if ((arg1 * 4) << 2) {} // FAKE: extra reference of the shared (arg1 * 4) << 2 expression; steers its CSE temp
    arg1 += ((MenuNM2_Sel *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    ret = arg1;
    (&D_8003378C[arg1 * 4])[2] = D_8003373C[arg1 * 2 * 2];
    D_8003373C[(arg1 * 2 * 2) + 2] = -D_8003378C[arg1 * 4];
    D_8003378C[(4 * arg1) + 3] = D_8003373C[(arg1 * 2 * 2) + 1];
    (&D_8003373C[arg1 * 2 * 2])[3] = -D_8003378C[(arg1 * 4) + 1];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + ((arg1 * 4) << 2)), ((MenuNM2_Sel *)arg0)->unk4, NULL);
    *arg3 = menuEvaluateSpline((f32 *)((u8 *)D_8003378C + ((4 * arg1) << 2)), ((MenuNM2_Sel *)arg0)->unk4, NULL);
    if (*arg3 < -40.0f) {
        v = -*arg3 - 40.0f;
        if (v > 20.0f) {
            v = 20.0f;
        }
        *arg4 = (v / 60.0f) + 1.0f;
        *arg5 = (s32)(v * 6.2f) + 0x80;
    } else {
        *arg4 = 1.0f;
        *arg5 = 0x80;
    }
    *arg6 = 0xFF;
    if (D_8003373C == &D_8003373C[4 * arg1]) {
        *arg3 *= 1.0f - D_80033F3C;
        *arg4 += D_80033F3C * 3.5f;
        if (D_80033F3C != 0.0f) {
            *arg6 = 0xFF - (s32)(((MenuNM2_Sel *)arg0)->unk0 * 255.0f);
            if (*arg6 < 0) {
                *arg6 = 0;
            }
        }
    }
    *arg2 *= 4.0f + (((MenuNM2_Sel *)arg0)->unk0 * 4.0f);
    *arg3 *= 4.0f + (((MenuNM2_Sel *)arg0)->unk0 * 4.0f);
    *arg2 += 640.0f;
    *arg3 += 480.0f;
    return ret;
}

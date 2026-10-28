// func_8003155C (src/menu/3E10.c): stage 4 (parked NON_MATCHING in MenuNM2 copy): frame 0x38 + s0-s3 + all ops/slots match; only regalloc differs (target E1=idx*4 in t7, E2=v1, p=a3, q=v0, base t1/t8; ours E1=v1, E2=a3, p=t0). Keys: arg1 as accumulator (idx in s0, addu s0,a1,t6 ok); NO separate idx local (extra locals cost slots); 'volatile s32 ret' (copy ret=arg1 kept in memory sw s0,0x30/lw v0,0x30; non-volatile merges into idx); element-index stores D[arg1*4+2] (arg1*4 is shared uopt temp, not folded) and spline args as (f32 *)((u8 *)D + ((arg1 * 4) << 2)) (non-folding sll 2;sll 2; pointer-index form folds to sll 4); compare &D_8003373C[arg1*4] == D_8003373C. store order q2,p2,q3,p3 gave best regs. Permuter 300s no gain.
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
    arg1 += ((MenuNM2_Sel *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    ret = arg1;
    D_8003378C[arg1 * 4 + 2] = D_8003373C[arg1 * 4];
    D_8003373C[arg1 * 4 + 2] = -D_8003378C[arg1 * 4];
    D_8003378C[arg1 * 4 + 3] = D_8003373C[arg1 * 4 + 1];
    D_8003373C[arg1 * 4 + 3] = -D_8003378C[arg1 * 4 + 1];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + ((arg1 * 4) << 2)), ((MenuNM2_Sel *)arg0)->unk4, NULL);
    *arg3 = menuEvaluateSpline((f32 *)((u8 *)D_8003378C + ((arg1 * 4) << 2)), ((MenuNM2_Sel *)arg0)->unk4, NULL);
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
    if (&D_8003373C[arg1 * 4] == D_8003373C) {
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

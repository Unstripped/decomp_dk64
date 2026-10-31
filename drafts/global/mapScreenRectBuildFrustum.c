// mapScreenRectBuildFrustum (src/global/55B20.c): stage 4 (MapA, parked NON_MATCHING in 55B20.c): frame 0xA8, callee set equal, 56 text lines (scheduling/regalloc). uopt -l5: FP candidate pool is 6 regs (f0,f2,f12,f14,f16,f18 = idx 24..29) and mine colors 6 candidates (D.0,D.4,cvt(unk278),D.C-D.0,t,cvt(unk27A)); target colors only D.0=f2,D.4=f12,cvt278=f14,DCD0=f16,cvt27A=f18 and SPILLS t (swc1 80(sp)/lwc1) and leaves f0 as div temp, i.e. target has one more higher-priority FP candidate than mine or t loses coloring. Tried: return type f32/f64/s32/u8 (no effect), t inline (frame/regs worse, >100), t as array/twice, all 120 statement orders of a/uv3/uv2/t/uv1/uv0, deadsweep (-3 with 'if (arg1 && arg1) {}' only), 900 hill-climb variants.
typedef struct FrustumCorners {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
} FrustumCorners;

extern FrustumCorners D_807F5DF0;
void mapScreenRectBuildFrustum(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, void *arg8, void *arg9, void *arg10) {
    f32 uv3;
    f32 t;
    f32 a;
    f32 uv2;
    f32 uv1;
    f32 uv0;
    f32 m[4][3];
    s32 i;
    MapPlayer *p;

    p = &D_807FC924[arg7];
    a = ((((f32)(arg0 - p->unk270)) / (f32)p->unk278) * (D_807F5DF0.unkC - D_807F5DF0.unk0)) + D_807F5DF0.unk0;
    uv3 = a;
    uv2 = ((((f32)(arg2 - p->unk270)) / (f32)p->unk278) * (D_807F5DF0.unkC - D_807F5DF0.unk0)) + D_807F5DF0.unk0;
    t = D_807F5DF0.unk1C - D_807F5DF0.unk4;
    uv1 = (t * (((f32)(arg1 - p->unk272)) / (f32)p->unk27A)) + D_807F5DF0.unk4;
    uv0 = (t * (((f32)(arg3 - p->unk272)) / (f32)p->unk27A)) + D_807F5DF0.unk4;
    m[0][0] = uv2; m[0][1] = uv0; m[0][2] = D_807F5DF0.unk8;
    m[1][0] = a; m[1][1] = uv0; m[1][2] = D_807F5DF0.unk14;
    m[2][0] = uv2; m[2][1] = uv1; m[2][2] = D_807F5DF0.unk20;
    m[3][0] = a; m[3][1] = uv1; m[3][2] = D_807F5DF0.unk2C;
    for (i = 0; i < 4; i++) {
        guMtxXFMF((float (*)[4])arg8, m[i][0], m[i][1], m[i][2], &((f32 (*)[3])arg10)[i][0], &((f32 (*)[3])arg10)[i][1], &((f32 (*)[3])arg10)[i][2]);
    }
    frustumOrientPolyNormals(arg4, arg5, arg6, arg9, arg10);
}

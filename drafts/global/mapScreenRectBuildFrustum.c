// mapScreenRectBuildFrustum (src/global/55B20.c): W3Static (leftovers6 w3): stage 5 score 2 unchanged (only temp slot 72 vs 80). Model: -l 5 shows ONE Ucg1 bit (121 ucg1{i}) = IV temp 4B allocated before spilltemps; pointer-only loops (named o/mp, no i: p3 form `o0=arg10; o1=arg10+1; o2=arg10+2; mp=m[0]; do{...mp+=3;o0..2+=3}while(mp!=m[4])`) DO drop it (diffY lands first at top-8) but cost count +1 (`move s0,s5`/`addiu t9,s5,48` bound) and frame +8 (4 named pointer words vs uv3+i; total vreg words must equal base 20); i+pointer forms (p3c) keep the IV temp. Tried: o ptr + i/mp (118/117 insns, no s2/s3 preheader IVs), (f32 (*)[3]) row pointers (118/124), full unroll (145 lines), idx*3 float indexing (130, 7 saved regs). No single-user globals.
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
    f32 uv3; // FAKE: unused pad slot, keeps the frame / home slots of q..uv0
    f32 q; // FAKE: named quotient (steers FP colouring: quotients take f0)
    f32 a;
    f32 uv2;
    f32 uv1;
    f32 uv0;
    f32 m[4][3];
    s32 i;
    MapPlayer *p;

    p = (MapPlayer *)((u8 *)gPlayerSlots + arg7 * 0x2F0);
    q = ((f32)(arg0 - p->unk270)) / (f32)p->unk278;
    a = (q * (D_807F5DF0.unkC - D_807F5DF0.unk0)) + D_807F5DF0.unk0;
    q = ((f32)(arg2 - p->unk270)) / (f32)p->unk278;
    uv2 = (q * (D_807F5DF0.unkC - D_807F5DF0.unk0)) + D_807F5DF0.unk0;
    q = ((f32)(arg1 - p->unk272)) / (f32)p->unk27A;
    uv1 = ((D_807F5DF0.unk1C - D_807F5DF0.unk4) * q) + D_807F5DF0.unk4;
    q = ((f32)(arg3 - p->unk272)) / (f32)p->unk27A;
    uv0 = ((D_807F5DF0.unk1C - D_807F5DF0.unk4) * q) + D_807F5DF0.unk4;
    m[0][0] = uv2; m[0][1] = uv0; m[0][2] = D_807F5DF0.unk8;
    m[1][0] = a; m[1][1] = uv0; m[1][2] = D_807F5DF0.unk14;
    m[2][0] = uv2; m[2][1] = uv1; m[2][2] = D_807F5DF0.unk20;
    m[3][0] = a; m[3][1] = uv1; m[3][2] = D_807F5DF0.unk2C;
    for (i = 0; i < 4; i++) {
        guMtxXFMF((float (*)[4])arg8, m[i][0], m[i][1], m[i][2], &((f32 (*)[3])arg10)[i][0], &((f32 (*)[3])arg10)[i][1], &((f32 (*)[3])arg10)[i][2]);
    }
    frustumOrientPolyNormals(arg4, arg5, arg6, arg9, arg10);
}

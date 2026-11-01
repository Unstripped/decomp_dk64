// mapScreenRectBuildFrustum (src/global/55B20.c): mapScreenRectBuildFrustum (src/global/55B20.c): stage 5 (parked NON_MATCHING), full=2: t's (D.1C-D.4 CSE) spill slot is 72(sp) (swc1/lwc1) vs target 80(sp); frame 0xA8, regs/order identical. W3Near 2026-11-01: temp slots are first-come 8-byte slots (a-value spill 64, then t 72); frame size does NOT depend on how many are used (removing the a spill by reading uv2 instead of a for m[1][0]/m[3][0] drops the spills but keeps 0xA8), so the target has an allocated-but-never-stored temp at 72 before t. Locals layout (decl order, highest first): pad/q 0xA4/0xA0, a/uv2/uv1/uv0 0x9C..0x90, m 0x8C..0x60, i 0x5C, p 0x58, temps 0x40..0x57. Tried (no gain, all stay (64,72)): w/h named denominators ((f32)p->unk278/27A) gives t slot 72 and code diff 111; named dx/dy removes the t spill (176 frame, 66); per-quotient q0..q3 (84), qx/qy (47); 216 spellings (3 p forms x 3 x-sum x 3 y-sum x 2 decl orders x 4 statement orders) all (64,72); 960 single dead tests (2 forms x 32 symbols x 15 points): slot 80 appears only with code-changing variants (min full 99); implicit vs explicit int->float casts; register on locals; scoping q.
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

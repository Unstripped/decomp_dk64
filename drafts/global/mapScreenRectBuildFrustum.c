// mapScreenRectBuildFrustum (src/global/55B20.c): leftovers6 W2FrameA: stage 5 park unchanged (full=2: temp slot 72(sp) vs 80(sp), count 123, frame 168 exact). NEW model from uopt source (.scratch/Mtx110/uopt{reg1,temp,emit}.c): temp slots = tempdisp top-down; strength-reduction (IV) Ucg1 temps (4B) are allocated in formlivbb BEFORE spilltemps, so ours = [4B IV/phantom 0x54, diffY 8B 0x48, a 8B 0x40] and target = [diffY 8B 0x50, 4B phantom 0x4C, a 8B 0x40] (i.e. target has NO pre-allocated 4B temp). Only the loop IV spelling moves it: out spelled &((f32*)arg10)[i*3+k] (one arg) puts diffY at 80 but adds 3 insns (n=126). No effect (identical code): loop forms ne/do/while/preinc/le3, i as s32/u32 (s16/u8/s8/u16 add insns), arg7 spelling (u32/s32/idx/mask/local copy), mixed out/in index spellings (4x3 forms, 1728 combos: best stays 2), local pointer for out/mt (uses an s-reg, frame 176), unrolled loop (frame 152), D accessed as f32 array (no lda: frame 160).
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

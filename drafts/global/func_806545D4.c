// func_806545D4 (src/global/55B20.c): stage 4 (parked NON_MATCHING in 55B20.c): frame 0xA8 and callee set s0-s5/ra equal; text diff 56 lines scheduling/regalloc only. Found: uv0..uv3 as f32 SCALARS (not uv[4]) gives frame 0xA8 and a spilled a@0x40; loop via f32 (*)[3] out cast gives the 3 stride-12 IV pointers + s0..s5 exactly. Remaining: target spills t(dy)@0x50 and reloads it (store->load barrier delays the D.1C load), f0/f2 swap, idx/base/offset temp order t9/t8/t2 for D_807FC924[idx]. Tried decl-order permutations, expression forms/statement orders (480), deadsweep, same-line joins, S[8] array homes
typedef struct S55dPlayer {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ u8 pad27C[0x2F0 - 0x27C];
} S55dPlayer;

extern S55dPlayer *D_807FC924;

typedef struct S55dRoad {
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
} S55dRoad;

extern S55dRoad D_807F5DF0;
void func_806545D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, void *arg8, void *arg9, void *arg10) {
    f32 uv3;
    f32 t;
    f32 a;
    f32 uv2;
    f32 uv1;
    f32 uv0;
    f32 m[4][3];
    s32 i;
    S55dPlayer *p;

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
    func_8062AD28(arg4, arg5, arg6, arg9, arg10);
}

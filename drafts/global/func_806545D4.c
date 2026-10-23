// func_806545D4 (src/global/55B20.c): stage 3: params are (s32 a0..a3, f32 a4@0xB8, f32 a5@0xBC, f32 a6@0xC0, u8 idx@0xC4 read as lbu 0xC7, MtxF*@0xC8, void*@0xCC, f32* dst@0xD0); bilinear A/B/C/D from D_807F5DF0 lerp over player unk270/272/278/27A, rows (B,D,unk8),(A,D,unk14),(B,C,unk20),(A,C,unk2C) + dead uv[4] block at 0x90; frame 0xB0 vs 0xA8 (2 extra scalar slots; target keeps only a@0x40 and t@0x50)
typedef struct M55P3Road {
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
} M55P3Road;

extern M55P3Road D_807F5DF0;

void func_806545D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, float (*arg8)[4], void *arg9, f32 *arg10) {
    f32 uv[4];
    f32 m[4][3];
    f32 t;
    f32 a;
    s32 i;
    M55P3Player *p;

    p = &D_807FC924[arg7];
    a = ((D_807F5DF0.unkC - D_807F5DF0.unk0) * (((f32)(arg0 - p->unk270)) / (f32)p->unk278)) + D_807F5DF0.unk0;
    uv[3] = a;
    uv[2] = ((D_807F5DF0.unkC - D_807F5DF0.unk0) * (((f32)(arg2 - p->unk270)) / (f32)p->unk278)) + D_807F5DF0.unk0;
    t = D_807F5DF0.unk1C - D_807F5DF0.unk4;
    uv[1] = (t * (((f32)(arg1 - p->unk272)) / (f32)p->unk27A)) + D_807F5DF0.unk4;
    uv[0] = (t * (((f32)(arg3 - p->unk272)) / (f32)p->unk27A)) + D_807F5DF0.unk4;
    m[0][0] = uv[2]; m[0][1] = uv[0]; m[0][2] = D_807F5DF0.unk8;
    m[1][0] = a; m[1][1] = uv[0]; m[1][2] = D_807F5DF0.unk14;
    m[2][0] = uv[2]; m[2][1] = uv[1]; m[2][2] = D_807F5DF0.unk20;
    m[3][0] = a; m[3][1] = uv[1]; m[3][2] = D_807F5DF0.unk2C;
    for (i = 0; i < 4; i++) {
        guMtxXFMF(arg8, m[i][0], m[i][1], m[i][2], &arg10[i * 3], &arg10[i * 3 + 1], &arg10[i * 3 + 2]);
    }
    func_8062AD28(arg4, arg5, arg6, arg9, arg10);
}

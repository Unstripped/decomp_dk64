// func_806699C4 (src/global/6AD90.c): STAGE 5: 5 rows left: expected loads D_807F6000 into t7/index t8 (temp numbering 1 lower than ours for the first statement). Nine nested &0xFF on arg3 fix every later temp (temp counter is mod 10: nine consumed temps = -1); first statement still +1. Dead-local/other no-op masks fold away.
void matrix4Invert(float [4][4], float [4][4]);

void func_806699C4(CollisionActorWork *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 pad2[10];
    float spB0[4][4];
    float pad[4][4];
    float sp30[4][4];

    arg0->unk10C = (arg1 + D_807F6000)->unk88;
    arg0->unk10E = (((((((((arg3 & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF); // FAKE: nine nested &0xFF shift uopt temp numbering
    arg0->unk10F = arg2;
    func_8066C610(arg1, arg2, spB0);
    matrix4Invert(sp30, spB0);
    guMtxXFMF(sp30, arg4, arg5, arg6, &arg0->unk100, &arg0->unk104, &arg0->unk108);
}

// func_807186C8 (src/global/11BC10.c): stage 6: 100% text-identical instructions, reloc only; *(f32 *)arg0->unk384 fixed mul.s operand order to (fa1, fa0) and aligned subsequent FP ring
extern f32 D_807FDB50;
extern f32 D_807FDB54;
extern f32 D_807FDB58;

typedef struct {
    f32 progress;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 increment;
    f32 angle;
    f32 angleIncrement;
} M2Interpolation;

void func_807186C8(TimedEffectActorView *arg0, s8 *arg1) {
    EffectMatrix spA0;
    EffectMatrix sp60;
    f32 start[3];
    f32 end[3];
    f32 result[3];
    s32 i;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0x28);
        ((M2Interpolation *)arg0->unk384)->progress = 0.0f;
        ((M2Interpolation *)arg0->unk384)->startX = D_807FDB50;
        ((M2Interpolation *)arg0->unk384)->startY = D_807FDB54;
        ((M2Interpolation *)arg0->unk384)->startZ = D_807FDB58;
        ((M2Interpolation *)arg0->unk384)->endX = arg0->unk340;
        ((M2Interpolation *)arg0->unk384)->endY = arg0->unk344;
        ((M2Interpolation *)arg0->unk384)->endZ = arg0->unk348;
        ((M2Interpolation *)arg0->unk384)->increment = 0.01f;
        ((M2Interpolation *)arg0->unk384)->angle = (f32)((u32)(func_806119A0() % 36000U) / 100U);
        ((M2Interpolation *)arg0->unk384)->angleIncrement = (f32)((u32)(func_806119A0() % 400U) / 100U);
    }
    start[0] = ((M2Interpolation *)arg0->unk384)->startX;
    start[1] = ((M2Interpolation *)arg0->unk384)->startY;
    start[2] = ((M2Interpolation *)arg0->unk384)->startZ;
    end[0] = ((M2Interpolation *)arg0->unk384)->endX;
    end[1] = ((M2Interpolation *)arg0->unk384)->endY;
    end[2] = ((M2Interpolation *)arg0->unk384)->endZ;
    for (i = 0; i < 3; i++) {
        result[i] = end[i] + (start[i] - end[i]) * *(f32 *)arg0->unk384;
    }
    arg0->unk340 = result[0];
    arg0->unk344 = result[1];
    arg0->unk348 = result[2];
    ((M2Interpolation *)arg0->unk384)->progress += ((M2Interpolation *)arg0->unk384)->increment;
    ((M2Interpolation *)arg0->unk384)->increment = (f32)((f64)((M2Interpolation *)arg0->unk384)->increment + 0.001);
    arg0->unk360 = (f32)((f64)arg0->unk360 * 0.975);
    arg0->unk364 = (f32)((f64)arg0->unk364 * 0.975);
    ((M2Interpolation *)arg0->unk384)->angle = ((M2Interpolation *)arg0->unk384)->angle + ((M2Interpolation *)arg0->unk384)->angleIncrement;
    guScaleF(spA0, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp60, ((M2Interpolation *)arg0->unk384)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(spA0, sp60, spA0);
    guMtxF2L(spA0, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *)arg0)[0x32C] = 2;
}

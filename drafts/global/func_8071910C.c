// func_8071910C (src/global/11BC10.c): stage 5: 0xD8 frame matched, s0-only saved. Callee func_806086CC 4th arg is s16 in TU causing sll/sra on a3.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
} Fx11BC2RotationState;

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
void func_806086CC(f32, f32, f32, s32, u32, s32, s32, s32, f32, s32);
extern s32 D_8072073C;
extern s32 D_807212B0;
extern s32 D_807212C8;

void func_8071910C(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp98[4][4];
    f32 sp58[4][4];
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp44;
    f32 var_fv0;
    f32 temp_fv0;
    Fx11BC2RotationState *state;
    s32 a3;

    state = (Fx11BC2RotationState *) arg0->unk384;
    if (state == NULL) {
        arg0->unk384 = func_80610FE8(0x1C);
        var_fv0 = (f32) (u32) ((func_806119A0() / 10000U) % 100U);
        ((Fx11BC2RotationState *) arg0->unk384)->unk0 = (f32) (((f64) var_fv0 / 25.0) + 5.0 + (((s32) arg0->unk35C >> 8) * 3.0));
        sp54 = ((f32) (u32) ((func_806119A0() / 10000U) % 1000U) / 500.0f) + (f32) (arg0->unk35C & 0xFF);
        sp50 = (f32) (u32) ((func_806119A0() / 10000U) % 360U);
        sp4C = sinApprox(sp50 * 0.017453292f) * sp54;
        temp_fv0 = cosApprox(sp50 * 0.017453292f);
        ((Fx11BC2RotationState *) arg0->unk384)->unk4 = sp4C;
        ((Fx11BC2RotationState *) arg0->unk384)->unk8 = temp_fv0 * sp54;
        ((Fx11BC2RotationState *) arg0->unk384)->unkC = (f32) (u32) ((func_806119A0() % 36000U) / 100U);
        sp44 = arg0->unk344;
        if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp44) != 0) {
            ((Fx11BC2RotationState *) arg0->unk384)->unk10 = sp44;
        } else {
            ((Fx11BC2RotationState *) arg0->unk384)->unk10 = 0.0f;
        }
        ((Fx11BC2RotationState *) arg0->unk384)->unk14 = 0;
    }
    state = (Fx11BC2RotationState *) arg0->unk384;
    state->unk0 = (f32) ((f64) state->unk0 + -0.63);
    state = (Fx11BC2RotationState *) arg0->unk384;
    arg0->unk340 += state->unk4;
    arg0->unk348 += state->unk8;
    arg0->unk344 += state->unk0;
    if (arg0->unk344 < state->unk10) {
        if (*(s32 **) arg0->unk330 == &D_8072073C) {
            a3 = 0x1B1;
        } else if ((*(s32 **) arg0->unk330 == &D_807212C8) || (*(s32 **) arg0->unk330 == &D_807212B0)) {
            a3 = 7;
        } else {
            a3 = 0x56;
        }
        func_806086CC(arg0->unk340, arg0->unk344, arg0->unk348, a3, (u32) ((f64) (u32) arg0->unk36D * 0.7), 0x96, 1, 0x4B, 0.3f, 0);
        ((Fx11BC2RotationState *) arg0->unk384)->unk0 = 5.0f;
        if (((Fx11BC2RotationState *) arg0->unk384)->unk14 != 2) {
            ((Fx11BC2RotationState *) arg0->unk384)->unk14++;
        }
    }
    if (((Fx11BC2RotationState *) arg0->unk384)->unk14 == 2) {
        if (arg0->unk36D >= 0xB) {
            arg0->unk36D -= 0xA;
        } else {
            arg0->unk36D = 0;
        }
    }
    state = (Fx11BC2RotationState *) arg0->unk384;
    state->unkC = (f32) ((f64) state->unkC + 5.9);
    guScaleF(sp98, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp58, state->unkC, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp98, sp58, sp98);
    guMtxF2L(sp98, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 2;
}

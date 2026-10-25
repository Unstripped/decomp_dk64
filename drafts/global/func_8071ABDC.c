// func_8071ABDC (src/global/11BC10.c): stage 1: m2c behavioral starter compiles; closest diff is frame/register allocation and branch structure
void func_8071ABDC(Ub5Actor *arg0, s8 *arg1) {
    f32 sp38, sp30, sp24, temp_fa0; f64 temp_ft5; s16 sp2C, temp_t9; u8 temp_v0_8; Ub5Motion *temp_v0;
    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0x10);
        temp_t9 = ((s32)arg0->unk35C >> 16) & 0xFF; sp2C = temp_t9; temp_v0 = (Ub5Motion *)arg0->unk384;
        if (temp_t9 == 0) temp_v0->unk0 = (f32)(((f64)(f32)((func_806119A0() / 10000U) % 100U) / 20.0) - 2.5); else temp_v0->unk0 = (f32)(((f64)(f32)((func_806119A0() / 10000U) % 100U) / 10.0) - 2.5);
        temp_fa0 = (f32)((arg0->unk35C & 0xFFFF) * 0x1E) * 0.017453292f; sp24 = temp_fa0;
        sp38 = (f32)((f64)func_80612D1C(temp_fa0) * 2.5); temp_ft5 = (f64)func_80612D10(temp_fa0) * 2.5; temp_v0->unk4 = sp38; temp_v0->unk8 = (f32)temp_ft5;
        if (sp2C == 1) { temp_v0->unk4 *= 2.0f; temp_v0->unk8 *= 2.0f; } else if (sp2C == 2) { temp_v0->unk4 *= 4.0f; temp_v0->unk8 *= 4.0f; }
        sp30 = arg0->unk344; if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp30) != 0) temp_v0->unkC = sp30; else temp_v0->unkC = 0.0f;
    }
    temp_v0 = (Ub5Motion *)arg0->unk384;
    if (arg0->unk34E >= 9) { temp_v0->unk0 = (f32)((f64)temp_v0->unk0 - 0.63); temp_v0->unk4 = (f32)((f64)temp_v0->unk4 * 0.9); temp_v0->unk8 = (f32)((f64)temp_v0->unk8 * 0.9); }
    if (arg0->unk34E >= (((s32)arg0->unk35C >> 24) & 0xFF)) { temp_v0_8 = arg0->unk36D; if (temp_v0_8 >= 0x3C) arg0->unk36D = temp_v0_8 - 0x3C; else arg0->unk36D = 0; }
    arg0->unk340 += temp_v0->unk4; arg0->unk348 += temp_v0->unk8; arg0->unk344 += temp_v0->unk0; if (arg0->unk344 < temp_v0->unkC) *arg1 = 1;
}

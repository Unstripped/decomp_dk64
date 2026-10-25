// func_806F1A18 (src/global/F56F0.c): Stage 4: target blocks/frame/callees match. Remaining first result slot sp+0x20 versus +0x24 and FP register/commutative operand allocation.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} F5N1Spring;

f32 func_80612D10(f32);
f32 func_80612D1C(f32);

void func_806F1A18(f32 arg0, f32 arg1, F5N1Spring *arg2, f32 *arg3) {
    f32 sp20;

    sp20 = func_80612D10(arg2->unk4);
    arg2->unk8 = (f32)(arg2->unk8 + ((arg0 * func_80612D10(*arg3)) * sp20));
    arg2->unk8 = (f32)(arg2->unk8 - (arg1 * func_80612D1C(arg2->unk4)));
    arg2->unk8 = (f32)((f64)arg2->unk8 * 0.93);
    arg2->unk4 = (f32)(arg2->unk4 + arg2->unk8);
    *arg3 += arg2->unk4 + arg2->unk0;
}

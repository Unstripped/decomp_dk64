// func_8071E864 (src/global/11BC10.c): text-identical, reloc only: all 117 insns match; fdiff FAILED only on %hi/%lo spelling (.rodata+0x3a0 in C build vs dlabel D_8075EA70/78/80/88 in expected .s); shape: state ptr via field reads CSEd + sp1C copy, no named u8 temp (inline unk36D -= 0x32 then reload-andi); EA84 .float 0 is 8-align padding before the 1.08 double
typedef struct {
    f32 unk0;
    f32 unk4;
} Fx11BHE8State;

void func_8071E864(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp24;
    Fx11BHE8State *temp_v0;
    Fx11BHE8State *sp1C;
    f32 temp_fa0;

    if (arg0->unk384 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 10.0f;
        temp_v0->unk4 = (f32)(arg0->unk35C * 0x154);
    }
    sp1C = (Fx11BHE8State *)arg0->unk384;
    sp1C->unk0 = (f32)((f64)sp1C->unk0 - 0.2);
    if ((f64)sp1C->unk0 < 0.8) {
        sp1C->unk0 = 0.8f;
    }
    sp24 = sp1C->unk0 * func_80612794((s16)(s32)sp1C->unk4);
    temp_fa0 = sp1C->unk0 * func_80612790((s16)(s32)sp1C->unk4);
    arg0->unk360 = (f32)((f64)arg0->unk360 * 1.08);
    arg0->unk364 = (f32)((f64)arg0->unk364 * 1.08);
    if ((f64)arg0->unk360 > 8.0) {
        arg0->unk36D = arg0->unk36D - 0x32;
        if (arg0->unk36D < 0x33) {
            *arg1 = 1;
        }
    }
    arg0->unk340 = (f32)(arg0->unk340 + sp24);
    arg0->unk348 = (f32)(arg0->unk348 + temp_fa0);
}

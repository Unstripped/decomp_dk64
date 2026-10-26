// func_80615134 (src/global/19A00.c): stage 4: typed command-state candidate compiled; control flow and instruction count recovered, remaining global/state register scheduling
// Stage 2: m2c behavioral starter; remaining diff: nested state view and delay-slot expression shape.
extern u8 *D_807F5AF0;

s32 func_80615134(void *arg0) {
    void *temp_v0;
    void *temp_v0_2;
    void *var_v1;

    temp_v0 = arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    D_807F5AF0 += 1;
    if ((var_v1->unk24 != 0.0f) || ((var_v1->unk2C != 0.0f) && (var_v1->unk34 != 0.0f))) {
        temp_v0_2 = arg0->unk4;
        temp_v0_2->unk78 = (s32)(temp_v0_2->unk78 | 1);
    }
    return 0;
}

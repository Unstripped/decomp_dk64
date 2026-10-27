// func_806F58A0 (src/global/F9450.c): Stage 4: reconstructed switch and calls; stack-local placement and loop counter allocation remain unresolved.
typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} F9N2At58;

extern s16 modelSlotAppend(s32, f32, f32, f32, f32, s32);
extern void modelSlotGetTransformVectors();
extern void func_806F50C8(s16, s16, s16, s32, s32, s32);
extern void func_806F54E0(s32, s16, u8);

void func_806F58A0(u8 arg0, s16 arg1, F9N2At58 *arg2) {
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s16 var_s0;
    s16 var_s2;
    s32 temp_t4;
    s32 var_s1;

    if (D_807FC928 == 1) {
        modelSlotGetTransformVectors(arg1, &sp7C, &sp78, &sp74, &sp70, &sp6C, &sp68, &sp64, &sp60, 1);
    }
    temp_t4 = arg2->unk58;
    var_s2 = 0xD;
    switch (temp_t4) {
    case 3: var_s2 = 0xA; break;
    case 5: var_s2 = 0x16; break;
    case 4:
    case 9: var_s2 = 0x1E; break;
    case 6:
    case 7: var_s2 = 0x1F; break;
    case 2:
    case 8: var_s2 = 0xD; break;
    }
    var_s0 = 0;
    var_s1 = 0;
    do {
        if (D_807FC928 == 1) {
            func_806F50C8(modelSlotAppend(var_s2, sp7C, sp78, sp74, 0.0f, 0), var_s2, var_s0, 1, 0, 1);
        } else {
            func_806F54E0(arg0, var_s2, 0);
        }
        var_s1++;
        var_s0 += 3;
    } while (var_s1 != 5);
}

// func_80615CE4 (src/global/19A00.c): stage 3: compiled typed candidate; target frame is 0x28 versus candidate 0x30. Tried current shared state view; state-local allocation remains.
? func_80614644(void *, s32, f32);                  /* extern */
? func_80614F28(u8 *, s32, void *);                 /* extern */
extern u8 D_80746D5C;
extern s32 D_807F5AF0;

s32 func_80615CE4(void *arg0) {
    u8 sp27;
    s32 sp20;
    f32 var_ft0;
    s32 var_a1;
    void *temp_v0;

    temp_v0 = arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_a1 = temp_v0->unk4;
    } else {
        var_a1 = temp_v0->unk0;
    }
    sp20 = var_a1;
    D_807F5AF0 += 1;
    func_80614F28(&sp27, var_a1, arg0);
    var_ft0 = (f32) D_80746D5C;
    if ((s32) D_80746D5C < 0) {
        var_ft0 += 4294967296.0f;
    }
    func_80614644(arg0, sp20, var_ft0);
    if (D_80746D5C != 0) {
        D_80746D5C += sp27;
    } else {
        D_80746D5C = 0;
    }
    return 1;
}

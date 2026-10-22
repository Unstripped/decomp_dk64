// func_8068A074 (src/global/8D3E0.c): 34/38 insns match; 4 insns diff only (v0 vs v1 regalloc in !(dist < unk54))
u8 func_8068A074(ActD3B_Struct1 *arg0) {
    s32 var_v1;

    if (func_80652E58(arg0->unk44->unk12C, arg0) == 0 || (var_v1 = !(func_80689DD4(arg0->unk10, arg0->unk14, arg0->unk18) < arg0->unk54))) {
        var_v1 = arg0->unk44->unk114 == NULL;
        if (var_v1 != 0) {
            var_v1 = arg0->unk44->unk154 == 0;
        }
    }
    return var_v1;
}

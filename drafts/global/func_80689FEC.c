// func_80689FEC (src/global/8D3E0.c): Closest diff: all instructions match except v0 vs v1 temporary register in boolean negation.
u8 func_80689FEC(ActD3B_Struct1 *arg0) {
    s32 var_v1;

    if (func_80652E58(arg0->unk44->unk12C, arg0) == 0 || (var_v1 = !(func_80689DD4(arg0->unk10, arg0->unk14, arg0->unk18) < arg0->unk54))) {
        var_v1 = arg0->unk44->unk114 == NULL;
    }
    return var_v1;
}

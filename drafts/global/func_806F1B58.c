// func_806F1B58 (src/global/F56F0.c): stage 5: m2c reconstruction; target keeps predicate in v0 while current uses v1 plus return move
s32 func_806F1B58(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t8;
    s32 var_v0;

    var_v0 = (arg0->unk60 & 0x100) != 0;
    if (var_v0 != 0) {
        temp_t8 = arg1->unk14 == 0;
        var_v0 = temp_t8;
        if (temp_t8 != 0) {
            var_v0 = arg2 == arg1->unk18;
        }
    }
    return var_v0;
}

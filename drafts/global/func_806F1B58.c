// func_806F1B58 (src/global/F56F0.c): Stage 5: correct blocks and result flow; target keeps predicate/result in v0/t8 while draft uses v1 plus final move. uopt trace and 600s permutation search reached zero only by omitting the non-void fallthrough return, so it was rejected as undefined behavior.
typedef struct {
    u8 pad0[0x14];
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
} F5N1Predicate;

s32 func_806F1B58(F5BActor *arg0, F5N1Predicate *arg1, s32 arg2) {
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

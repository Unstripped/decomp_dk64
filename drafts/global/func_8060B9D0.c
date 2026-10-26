// func_8060B9D0 (src/global/104F0.c): stage 6: sole remaining diff is scheduling of the table-base addiu before versus after the zero index initialization; 600s permuter reported a context-sensitive zero that did not reproduce in the private copy.
extern u8 D_807EDEA8[];

s32 func_8060B9D0(s32 arg0) {
    s32 temp_t8;
    s32 var_v1;

    var_v1 = 0;
loop_1:
    if (arg0 == D_807EDEA8[var_v1]) {
        return var_v1;
    }
    temp_t8 = (var_v1 = (var_v1 + 1) & 0xFF);
    if (temp_t8 >= 4) {
        return 0;
    }
    goto loop_1;
}

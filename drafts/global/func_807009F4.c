// func_807009F4 (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
extern s32 D_8076A0A0;

s16 func_807009F4(s16 arg0) {
    s16 temp_v0;
    s16 var_a1;
    s16 var_v0;
    s16 var_v1;
    s32 temp_t8;
    void *temp_a2;

    var_v0 = 0;
    var_a1 = 0x1FE;
    if (arg0 == -1) {
        return 0;
    }
loop_3:
    temp_t8 = (s32) (var_v0 + var_a1) / 2;
    if (arg0 < *(D_8076A0A0 + ((s16) temp_t8 * 2))) {
        var_a1 = (s16) temp_t8 - 1;
    } else {
        var_v0 = (s16) temp_t8 + 1;
    }
    temp_a2 = D_8076A0A0 + ((s16) temp_t8 * 2);
    if ((arg0 >= temp_a2->unk0) && (arg0 < temp_a2->unk2)) {
        return (s16) ((s16) temp_t8 + 8);
    }
    if (var_a1 < var_v0) {
        temp_v0 = arg0 - 0x7C1B;
        var_v1 = temp_v0;
        if (temp_v0 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    goto loop_3;
}

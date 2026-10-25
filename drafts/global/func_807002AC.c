// func_807002AC (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
s16 *func_80610FE8(?);                              /* extern */
s16 func_80700088(?, u16);                          /* extern */
? heapFreeDeferred(s16 *);                          /* extern */

void func_807002AC(u16 *arg0, s16 **arg1, ? arg2) {
    s16 *temp_v0;
    s16 *var_s0;
    s16 var_s1;
    u16 *var_s2;
    u16 temp_a1;

    var_s2 = arg0;
    temp_v0 = func_80610FE8(0xA000);
    *arg1 = temp_v0;
    heapFreeDeferred(temp_v0);
    var_s1 = 0;
    var_s0 = *arg1;
    do {
        temp_a1 = *var_s2;
        var_s2 += 2;
        var_s1 += 1;
        *var_s0 = func_80700088(arg2, temp_a1);
        var_s0 += 2;
    } while (var_s1 < 0x5000);
}

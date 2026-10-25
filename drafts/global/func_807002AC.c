// func_807002AC (src/global/103AB0.c): Stage 5 conversion loop; frame and behavior reconstructed, remaining s0/s2 allocation and loop schedule mismatch.
s16 *func_80610FE8(s32);
void heapFreeDeferred(void *);
s16 func_80700088(f32, u16);

void func_807002AC(u16 *arg0, s16 **arg1, f32 arg2) {
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
        var_s2++;
        var_s1++;
        *var_s0 = func_80700088(arg2, temp_a1);
        var_s0++;
    } while (var_s1 < 0x5000);
}

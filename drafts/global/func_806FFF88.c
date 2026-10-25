// func_806FFF88 (src/global/103AB0.c): Stage 6: exact opcode sequence and frame/s-register set; all remaining 60 differences are ugen scratch register allocation, including the width*0x70 intermediate.
s32 func_80610FE8(s32);
s32 func_806FFEAC();
extern void *D_80744470[];

s32 func_806FFF88(void) {
    s32 sp34;
    s16 var_s0;
    s16 var_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s2;

    if (D_807FBB40->unk58 == 0xD9) {
        return func_806FFF5C();
    }
    temp_v0 = func_80610FE8(0xA000);
    sp34 = temp_v0;
    var_s1 = temp_v0;
    var_s2 = (s32)D_80744470[D_807444FC] + (D_80744490 * 0x70) + 0xA0;
    var_s3 = 0;
    do {
        var_s0 = 0;
        do {
            temp_v0_2 = func_806FFEAC(var_s1, (var_s0 << 6) + var_s2);
            var_s0++;
            var_s1 = temp_v0_2;
        } while (var_s0 < 5);
        var_s3++;
        var_s2 += D_80744490 << 7;
    } while (var_s3 < 2);
    return sp34;
}

// func_80713EB0 (src/global/117190.c): stage 3: branch behavior reconstructed; target frame 0x20/a3 persistence, current frame 0x30/s0. Need recover a3 spill and independent global-load order
// func_80713EB0: stage 3; all semantic branches reconstructed, but target uses a3 plus 0x20-byte frame while C colors the persistent selection into s0 and frame is 0x30.
extern s16 D_807FC828;
extern s16 D_807FC82A;
extern s16 D_807FC82C;
void func_806ABE3C(s32);
s32 func_8073110C(s32, s32);

void func_80713EB0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    s16 *temp_v0;
    s32 temp_v1;
    s32 var_a3;

    var_a3 = arg0;
    if (arg0 >= 0) {
        if (D_80755314 == 0xE) {
            if (arg2 == 1) {
                var_a3 = arg0;
                if (func_8073110C(0x2A, 1) == 0) var_a3 = -1;
            }
            if (arg2 == 2) {
                arg0 = var_a3;
                var_a3 = arg0;
                if (func_8073110C(0x2B, 1) == 0) var_a3 = -1;
            }
        } else {
            func_806ABE3C(var_a3);
            temp_v0 = &(&D_807FC828)[3];
            var_a3 = arg0;
            temp_v1 = D_807FC828 + D_807FC82A + D_807FC82C + temp_v0[0] + temp_v0[1] + temp_v0[2] + temp_v0[3];
            if (arg2 == 1) {
                if (temp_v1 < 0x118) var_a3 = -1;
                else { sp18 = temp_v1; func_8073129C(0x2A, 1, 1); var_a3 = arg0; }
            }
            if (arg2 == 2) {
                if (temp_v1 < 0x119) var_a3 = -1;
                else { arg0 = var_a3; func_8073129C(0x2B, 1, 1); var_a3 = arg0; }
            }
        }
        if (var_a3 >= 0) { func_80712524(var_a3, arg1); return; }
    }
    if (D_80755314 == 0xE) { func_8070B308(0); func_80712490(0x50, 0, 5); return; }
    func_807124B8(0x28, 0, 1);
}

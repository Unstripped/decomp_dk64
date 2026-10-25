// func_80713EB0 (src/global/117190.c): stage 4: readable split accumulation lowers permuter/fdiff score 1317→900; target frame/spills match, remaining a0,a3 move and indexed sum
// func_80713EB0: stage 4. First-parameter reuse gives target 0x20 frame and selection spill. A readable split accumulation lowered the permuter score from 1317 to 900, but the premature move a0,a3 and base-plus-index global sum still differ.
extern s16 D_807FC828;
extern s16 D_807FC82A;
extern s16 D_807FC82C;
void func_806ABE3C(s32);
s32 func_8073110C(s32, s32);

void func_80713EB0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    s32 temp_v1;

    if (arg0 >= 0) {
        if (D_80755314 == 0xE) {
            if (arg2 == 1) {
                if (func_8073110C(0x2A, 1) == 0) {
                    arg0 = -1;
                }
            }
            if (arg2 == 2) {
                if (func_8073110C(0x2B, 1) == 0) {
                    arg0 = -1;
                }
            }
        } else {
            func_806ABE3C(arg0);
            temp_v1 = D_807FC828 + D_807FC82A + D_807FC82C;
            temp_v1 += (&D_807FC828)[3] + (&D_807FC828)[4] + (&D_807FC828)[5] + (&D_807FC828)[6];
            if (arg2 == 1) {
                if (temp_v1 < 0x118) {
                    arg0 = -1;
                } else {
                    sp18 = temp_v1;
                    func_8073129C(0x2A, 1, 1);
                }
            }
            if (arg2 == 2) {
                if (temp_v1 < 0x119) {
                    arg0 = -1;
                } else {
                    func_8073129C(0x2B, 1, 1);
                }
            }
        }
        if (arg0 >= 0) {
            func_80712524(arg0, arg1);
            return;
        }
    }
    if (D_80755314 == 0xE) {
        func_8070B308(0);
        func_80712490(0x50, 0, 5);
        return;
    }
    func_807124B8(0x28, 0, 1);
}

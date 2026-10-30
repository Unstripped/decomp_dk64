// func_80713EB0 (src/global/117190.c): Stage 5: matches except one lui: target 'lui t0,%hi(D_807FC82C)' sits after 'sll t1,a0,1', mine places 'lui t0' earlier (before addiu t2). Unrolled 'for (i=0;i<7;i++) sum += D_807FC828[i]' reproduces the whole unrolled sum (v1 spill 0x18, a3 spill 0x20); reloc symbols D_807FC82A/82C vs D_807FC828+2/+4 are reloc-only. func_806ABE3C must be called WITHOUT an argument (K&R decl, a0 still holds arg0): with func_806ABE3C(arg0) uopt adds 'move a0,a3'.
extern s16 D_807FC828[];
void func_806ABE3C();
void func_8070B308(s32);

void func_80713EB0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    s32 sum;
    s32 i;

    if (arg0 >= 0) {
        if (D_80755314 == 0xE) {
            if (arg2 == 1) {
                if (flagGet(0x2A, 1) == 0) {
                    arg0 = -1;
                }
            }
            if (arg2 == 2) {
                if (flagGet(0x2B, 1) == 0) {
                    arg0 = -1;
                }
            }
        } else {
            func_806ABE3C();
            sum = 0;
            for (i = 0; i < 7; i++) {
                sum += D_807FC828[i];
            }
            if (arg2 == 1) {
                if (sum < 0x118) {
                    arg0 = -1;
                } else {
                    flagSet(0x2A, 1, 1);
                }
            }
            if (arg2 == 2) {
                if (sum < 0x119) {
                    arg0 = -1;
                } else {
                    flagSet(0x2B, 1, 1);
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

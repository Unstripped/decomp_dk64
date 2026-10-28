// func_80026B28 (src/menu/1AF0.c): NON_MATCHING parked, stage 5-6. Temp reg numbering one step off from func entry (t7/t8 vs t8/t9, case-1 lui t1 vs t0); target keeps a dup 'b; li a3,9' else-branch of the (unk10+1==D_807FCC4C) test which IDO folds away in my source; a3/v1 locals priority swap if both branches set sp28=9.
typedef struct {
    char pad0[4];
    Struct_BB40_58 *unk4;
} MenuM1b_C924;
#define M1B_C924 ((MenuM1b_C924 *)D_807FC924)
extern s32 D_807FBB60;
s32 func_806F8EDC(s32, s32);

extern u16 D_80033A50[][4];
extern u16 D_80033A78[];
extern u16 D_800334E4[];

#define M1B_ARG1 ((u8 *)arg1)

void func_80026B28(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;

    switch (arg0->unkE) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            D_807FBB60 |= 0x10030;
            sp24 = -1;
            M1B_C924->unk4->unk60 &= 0xBFFFFFFF;
            sp28 = 0;
            sp2C = -1;
            currentActorClearFlag();
            switch (arg0->unkB) {
            case 0:
                sp2C = D_80033A50[D_8074E77C][M1B_ARG1[arg0->unkB]];
            case 1:
                if (sp2C == -1) {
                    sp2C = D_80033A78[M1B_ARG1[arg0->unkB]];
                }
                sp28 = 8;
                break;
            case 4:
                if (arg0->unk11 == 1) {
                    if (func_80025AF0(arg0, 1) == 0) {
                        sp24 = 0x15;
                    }
                    sp2C = 0x12;
                    sp28 = 9;
                } else {
                    sp2C = 0x13;
                    sp28 = 9;
                    if (*((u8 *)arg0 + 0x10) + 1 == D_807FCC4C) {
                        sp2C = 0x14;
                    } else {
                        sp28 = 9;
                    }
                }
                break;
            case 2:
                sp2C = D_800334E4[arg0->unk11];
            case 3:
                if (sp2C == -1) {
                    D_80750AC8 = func_806F8EDC(2, 0);
                    sp2C = 0x15;
                }
                sp28 = 7;
                break;
            }
            func_8070D8C0(D_807FBB40, sp28, sp2C);
            if (sp24 >= 0) {
                func_8070D8C0(D_807FBB40, sp28, sp24);
            }
            arg0->unkE++;
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            flagSet(arg2, 1, 0);
            camResumePath();
            arg0->unkE++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            menuTransitionToSubmenu(arg0, arg1);
        }
        break;
    }
}

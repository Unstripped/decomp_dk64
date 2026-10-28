// func_80026DAC (src/menu/1AF0.c): NON_MATCHING parked, stage 6. Switch-selector temp gets v0 and local v gets v1 (target: selector v1, v v0, sp1C candidate v1 reloaded after call, sw v0,0x1C in delay slot). func_806F91B4 prototype first param s16 gives lh (target lw): change to s32 (func_80025E04 stays SAME).
typedef struct {
    char pad0[4];
    Struct_BB40_58 *unk4;
} MenuM1b_C924;
#define M1B_C924 ((MenuM1b_C924 *)D_807FC924)
extern s32 D_807FBB60;
s32 func_806F8EDC(s32, s32);

void func_805FF898(void);
void func_806CFF9C(void *);

void func_80026DAC(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    s32 x;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 v;
    s32 sp1C;

    switch (arg0->unkE) {
    case 0:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath();
            arg0->unkE++;
            flagSet(arg2, 1, 0);
        }
        break;
    case 2:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            x = -1;
            camResumePath();
            arg0->unkE = 4;
            switch (D_807FBB40->unk58) {
            case 0xBE:
                x = 2;
            case 0xBF:
                if (x < 0) {
                    x = 7;
                }
                slotQueueUpdate(x, 0, 0);
                break;
            }
        }
        break;
    case 1:
        if (currentActorTestClearFlag() != 0) {
            sp30 = 1;
            sp24 = -1;
            v = -1;
            currentActorClearFlag();
            func_806CFF9C(D_807FBB4C);
            switch (D_807FBB40->unk58) {
            case 0xBE:
                sp2C = 7;
                sp28 = 0x11;
                sp24 = 2;
                v = 2;
            case 0xBF:
                if (sp24 < 0) {
                    sp2C = 9;
                    sp28 = 0x10;
                    sp24 = 7;
                    v = 4;
                }
                if (v >= 0 && (((u8 *)arg1)[v] & 1)) {
                    sp1C = func_806F8AD4((u8)sp24, 0);
                    if (sp1C < func_806F8EDC(sp24, 0)) {
                        func_8070D8C0(D_807FBB40, sp2C, sp28);
                        func_806F91B4(sp24, 0, 0x3E7);
                        arg0->unkE = 0;
                        sp30 = 5;
                    }
                }
                break;
            }
            arg0->unkE += 2;
            camStartPath(0, (s16)sp30, 1);
        }
        break;
    case 4:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
    case 3:
            func_805FF898();
            arg0->unkE = 0xA;
        }
        break;
    }
}

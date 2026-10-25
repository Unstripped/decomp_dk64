// func_80712830 (src/global/117190.c): Stage 5: control flow and calls recovered; wrong func_80709464 second argument and local stack offsets remain, with register allocation differences.
typedef struct R117dMenuObject {
    u8 unk0[0x155];
    u8 unk155;
} R117dMenuObject;

extern s32 D_807FBB64;
extern s32 D_807FBB68;
extern u8 D_807FC928;
void func_80709464(s32, R117dMenuObject *);
void func_805FF800(s32 *, s32 *, R117dMenuObject *);
void func_80026D40(R117dMenuObject *);
void func_805FF1B0(s32);

void func_80712830(R117dMenuObject *arg0, s32 arg1) {
    s32 sp20;
    s32 sp1C;
    s32 var_a0;
    s32 var_a1;

    func_80709464(arg1 & 0xFF, arg0);
    if (D_807FBB64 & 1) {
        arg0->unk155++;
        if (D_807FBB68 & 2) {
            func_8073129C(0x5C, 1, 2);
            var_a0 = 0x22;
            var_a1 = 0xC;
        } else {
            var_a0 = 0x2A;
            var_a1 = 2;
            if (D_8076A0A8 == 0x3C) {
                var_a0 = 0x3E;
                var_a1 = 1;
            }
        }
        func_805FF378(var_a0, var_a1);
        return;
    }
    if (D_807FBB64 & 0x400) {
        arg0->unk155++;
        func_805FF800(&sp20, &sp1C, arg0);
        func_805FF378(sp20, sp1C);
        return;
    }
    if (D_807FC928 >= 2) {
        func_80026D40(arg0);
        return;
    }
    func_805FF1B0(arg1);
}

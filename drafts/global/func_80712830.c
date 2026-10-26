// func_80712830 (src/global/117190.c): Stage 5: target control flow and 0x30 frame recovered; remaining helper-call scheduling, result local stack offsets, and register allocation.
typedef struct R117d2MenuObject {
    u8 unk0[0x155];
    u8 unk155;
} R117d2MenuObject;

extern s32 D_807FBB64;
extern s32 D_807FBB68;
extern u8 D_807FC928;
void func_80709464(u8);
s32 func_805FF800(s32 *, s32 *);
void func_80026D40(void *);
void func_805FF1B0(s32);

void func_80712830(R117d2MenuObject *arg0, s32 arg1) {
    s32 sp20;
    s32 sp1C;
    s32 var_a0;
    s32 var_a1;

    func_80709464(arg1 & 0xFF);
    if (D_807FBB64 & 1) {
        arg0->unk155++;
        if (D_807FBB68 & 2) {
            flagSet(0x5C, 1, 2);
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
        func_805FF800(&sp20, &sp1C);
        func_805FF378(sp20, sp1C);
        return;
    }
    if (D_807FC928 >= 2) {
        func_80026D40(arg0);
        return;
    }
    func_805FF1B0(arg1);
}

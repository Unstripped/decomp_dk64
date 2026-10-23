// func_8066C958 (src/global/70FD0.c): Frame 0x68 vs 0x60 caused by s2 holding &D_807FB549; loop structure and logic matched
extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern s32 D_807FB530;
extern M70A_Struct_CB88 *D_807FB534;
extern s32 D_807FB538;
extern u8 D_807FB549;

void *func_8066B0F8(s32, s32, s32, s32);
s32 func_8066B020(s32, s32);
void func_8066B424(void);
void func_8066B434(void *, s32, s32);
void *func_80610FE8(s32);
void gunzip(void *, void *, void *);

void func_8066C958(M70A_Struct_C958 *arg0) {
    void *sp60;
    void *sp5C;
    void *sp58;
    s32 sp38;
    void *sp30;
    void *var_s0;
    s32 *var_a2;
    u8 *var_v1;
    u8 *temp_a0;
    s32 temp_lo;
    s32 var_a3;
    s32 var_s1;
    s32 elem_size;

    var_s1 = 4;
    var_s0 = func_8066B0F8(2, D_8076A0A8, 1, 0);
    D_807FB549 = 0;
    if (arg0->unk9 & 1) {
        sp60 = var_s0;
        var_s0 = func_80610FE8(arg0->unk0);
        sp30 = func_80610FE8(0x2400);
        sp5C = var_s0;
        sp58 = sp60;
        gunzip(&sp58, &sp5C, sp30);
        heapFree(sp30);
        func_8066B424();
        func_8066B434(sp60, 0x14C, 0xA);
        D_807FB549 = 1;
    }
    sp38 = func_8066B020(2, D_8076A0A8);
    D_807FB530 = *(s32 *)var_s0;
    D_807FB534 = func_80610FE8(0x1518);
    temp_lo = arg0->unk10 * arg0->unk12;
    var_a2 = (s32 *)((u8 *)var_s0 + 4);
    var_a3 = 0;
    var_v1 = (u8 *)var_s0 + var_s1;
    elem_size = 24;
    D_807FB538 = temp_lo;
    if (temp_lo > 0) {
        do {
            temp_a0 = var_v1 + 4;
            var_s1 = *var_a2;
            if (D_807FB549 != 0) {
                D_807FB534[var_a3].unk4 = temp_a0;
            } else {
                D_807FB534[var_a3].unk4 = NULL;
            }
            D_807FB534[var_a3].unk0 = NULL;
            var_v1 = (u8 *)var_s0 + var_s1;
            D_807FB534[var_a3].unkC = sp38 + (temp_a0 - (u8 *)var_s0);
            D_807FB534[var_a3].unk10 = var_v1 - temp_a0;
            var_a2 = (s32 *)var_v1;
            D_807FB534[var_a3].unk8 = 0;
            D_807FB534[var_a3].unk14 = (var_v1 - temp_a0) / elem_size;
            var_a3++;
        } while (var_a3 < D_807FB538);
    }
    if (D_807FB549 == 0) {
        func_8066B424();
        func_8066B434(var_s0, 0x17C, 0xA);
    }
}

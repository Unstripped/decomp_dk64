// func_8066CB88 (src/global/70FD0.c): Closest diff: frame 0x58 matched, loop matched, only unk14 load into s0 vs v0 remaining
extern M70A_Struct_CB88 *D_807FB534;
extern s32 D_807FB538;
extern u8 D_807FB549;
extern s32 D_8076A064;

void *func_80610FE8(s32);
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);
s32 func_8066DB40(void *, void *);

void func_8066CB88(s32 arg0) {
    s32 sp54;
    s32 pad;
    void *s2;
    void *s1;
    s32 s0;

    if (D_807FB534[arg0].unk0 == NULL && arg0 < D_807FB538) {
        sp54 = D_807FB534[arg0].unk10;
        if (sp54 != 0) {
            if (D_807FB549 == 0) {
                D_807FB534[arg0].unk4 = func_80610FE8(sp54);
                func_8060B140(D_807FB534[arg0].unkC, D_807FB534[arg0].unk4, &sp54, 0, 0, 0, 0);
            }
            s0 = D_807FB534[arg0].unk14 * 0x28;
            D_807FB534[arg0].unk0 = func_80610FE8(s0);
            s1 = D_807FB534[arg0].unk4;
            s2 = D_807FB534[arg0].unk0;
            if (s0 != 0) {
                do {
                    if (func_8066DB40(s1, s2) != 0) {
                        s2 = (void *)((u8 *)s2 + 0x28);
                    }
                    s0 -= 0x28;
                    s1 = (void *)((u8 *)s1 + 0x18);
                } while (s0 != 0);
            }
        }
    }
    D_807FB534[arg0].unk8 = D_8076A064;
}

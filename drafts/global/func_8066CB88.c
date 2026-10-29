// func_8066CB88 (src/global/70FD0.c): Stage 5: frame 0x58, loop matched; only the unk14 load goes to s0 (target v0, product built in s0 then move a0,s0); deadsweep dead stmt if(D_807FB534==0){} fixed the rest
typedef struct Col7A_CacheView {
    void *unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Col7A_CacheView;

#define COL7A_CACHE ((Col7A_CacheView *)D_807FB534)

void func_8060B140(s32, void *, void *, s32, s32, s32, s32);
s32 func_8066DB40(void *, void *);

void func_8066CB88(s32 arg0) {
    s32 sp54;
    s32 pad;
    void *s2;
    void *s1;
    s32 s0;

    if (COL7A_CACHE[arg0].unk0 == NULL && arg0 < D_807FB538) {
        sp54 = COL7A_CACHE[arg0].unk10;
        if (sp54 != 0) {
            if (D_807FB549 == 0) {
                COL7A_CACHE[arg0].unk4 = func_80610FE8(sp54);
                func_8060B140(COL7A_CACHE[arg0].unkC, COL7A_CACHE[arg0].unk4, &sp54, 0, 0, 0, 0);
            }
            s0 = COL7A_CACHE[arg0].unk14 * 0x28;
            COL7A_CACHE[arg0].unk0 = func_80610FE8(s0);
            s1 = COL7A_CACHE[arg0].unk4;
            s2 = COL7A_CACHE[arg0].unk0;
            if (D_807FB534 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
    COL7A_CACHE[arg0].unk8 = D_8076A064;
}

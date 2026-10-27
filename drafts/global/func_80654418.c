// func_80654418 (src/global/55B20.c): stage 6: frame 0x138 and callee-saved set match; with 'off = 0; i = 0;' (off first) i/off land in s1/s0 as in the target and D_807F7148 as u8[] (target passes its address to memcpy). Remaining: &D_807FC929 gets a register (s8) so uopt rematerialises spB8 instead of hoisting it into s3; target rematerialises the D_807FC929 address (lui/lbu twice) and keeps &spB8 in s3, which rotates every other hoisted constant up one register (D_807F6C28 s4, 1 s5, sp+0x84 s6, D_807482F4 s7, D_807F7148 s8). Tried: (u8) cast on the call arg, u8 cast on spB8, a pb=(u8*)spB8 pointer, a local idx = D_807FC929 for the matrix index (frame grew), i/off swap; all keep s8.
extern f32 D_807F5FAC;
extern s32 D_807482F4;
extern u8 D_807F7148[];
void matrix4Invert(f32 (*)[4], f32 (*)[4]);
void func_806545D4(s32, s32, s32, s32, f32, f32, f32, u8, void *, void *, void *);

void func_80654418(f32 arg0, f32 arg1, f32 arg2) {
    f32 spF8[4][4];
    f32 spB8[4][4];
    u8 sp84[0x34];
    s32 i;
    s32 off;
    u8 *p;

    func_8062A944(D_807F5FB4, D_807F5FB0, D_807F5FAC);
    guMtxL2F(spF8, (Mtx *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + (D_807444FC << 6) + 8));
    matrix4Invert(spB8, spF8);
    off = 0;
    i = 0;
    while (i < D_807F6C28) {
        p = (u8 *)D_807F6C18 + off;
        if (p[0] == 1) {
            func_806545D4(*(s32 *)(p + 0x68), *(s32 *)(p + 0x6C), *(s32 *)(p + 0x70), *(s32 *)(p + 0x74),
                          arg0, arg1, arg2, D_807FC929, spB8, p + 0x88, sp84);
        }
        if (i == D_807482F4) {
            memcpy(D_807F7148, (u8 *)D_807F6C18 + off + 0x88, 0x140);
        }
        i++;
        off += 0x1C8;
    }
}

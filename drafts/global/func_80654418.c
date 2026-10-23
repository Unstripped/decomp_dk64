// func_80654418 (src/global/55B20.c): stage6: frame 0x138+callee-saved set match, 90% instructions identical; left: callee-saved rotation (sp+0x184: s8 vs s3, &D_807F6C28: s3 vs s4, sp+0x84: s5 vs s6), i/off in s0/s1 swapped, +0x88 via v0+0x88 vs target's recomputed off+base+0x88. Adding a scaffolding 'if (!spB8) {}' after 'off = 0;' drops the diff to regalloc-only (score 520). Needs the file prototype (f32,f32,f32).
// frame 0x138 and callee-saved set (s0-s8) match; remaining diffs are regalloc: this version
// hoists the address of D_807FC929 into s8 (target rematerialises lui/lbu per use) and
// rematerialises the sp+0x184 buffer address in the loop (target keeps it in s3); the i/off
// induction pair lands in s0/s1 the other way round and the +0x88 pointer is v0+0x88 here
// vs a recomputed off+base+0x88 in the target.
// NOTE: needs the file's prototype changed to (f32, f32, f32) - the target reads a2 in
// mtc1 a2,$f24, and its only C caller func_80654380 then passes arg2 as the third arg
// (codegen of 80654380 is unchanged by that).
#include "common.h"

extern f32 D_807F5FAC;
extern s32 D_807482F4;
extern u8 *D_807F7148;

void func_8062FF10(f32 (*)[4], f32 (*)[4]);
void func_806545D4(s32, s32, s32, s32, f32, f32, f32, u8, void *, void *, void *);

void func_80654418(f32 arg0, f32 arg1, f32 arg2) {
    f32 spF8[4][4];
    f32 spB8[4][4];
    u8 sp84[0x34];
    s32 off;
    s32 i;
    u8 *p;

    func_8062A944(D_807F5FB4, D_807F5FB0, D_807F5FAC);
    guMtxL2F(spF8, (Mtx *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + (D_807444FC << 6) + 8));
    func_8062FF10(spB8, spF8);
    i = 0;
    off = 0;
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

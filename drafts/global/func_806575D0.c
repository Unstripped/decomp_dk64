// func_806575D0 (src/global/55B20.c): code identical except stack frame 0x88 vs built 0x88-with-+8-shift; needs 8 bytes of unused top-of-frame pad
#include "common.h"

typedef struct {
    /* 0x00 */ s64 unk0;
    /* 0x08 */ s64 unk8;
    /* 0x10 */ s64 unk10;
    /* 0x18 */ s64 unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0xC];
} M55P5GridPoint;

extern M55P5GridPoint *D_807F6C24;
extern void func_80657CB0(s32, f32, f32, f32, f32 *, f32 *, f32 *);
extern void func_80657974(s32, f32, f32, f32, u8 *);
extern s32 func_8065776C(u8 *);

s32 func_806575D0(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    u8 sp4C[0x28];
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 h;
    f32 x;

    sp40 = (f32)D_807F6C24[arg0].unk10;
    sp44 = (f32)D_807F6C24[arg0].unk8;
    sp48 = (f32)D_807F6C24[arg0].unk0;
    h = (f32)D_807F6C24[arg0].unk18;
    x = (h + (sp48 * arg1 + sp44 * arg2 + sp40 * arg3)) / D_807F6C24[arg0].unk20;
    if (x < 0.0) {
        x = 0.0 - x;
    }
    if (x > 80.0) {
        return 0;
    }
    func_80657CB0(arg0, arg1, arg2, arg3, &sp7C, &sp78, &sp74);
    func_80657974(arg0, sp7C, sp78, sp74, sp4C);
    if (func_8065776C(sp4C)) {
        return 1;
    }
    return 0;
}

// func_806A3C6C (src/global/A8400.c): stage 5: display-list builder; instruction multiset matches, middle-block scheduling of 0.0f/0x40/0x20 constant hoists differs
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

s32 texCacheFindOrLoad(u16);
void func_80702464(Gfx **, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32);

Gfx *func_806A3C6C(Gfx *arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 tex;

    tex = texCacheFindOrLoad((arg3 + 0x52) & 0xFFFF);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, arg2 | 0xFFFFFF00);
    WRITE_GFX(arg0++, 0xDA380002, arg1);
    func_80702464(&arg0, tex, 3, 0x60, 0x40, 0x20, 0x20, 0.0f, 0.0f, 96.0f, 64.0f, 0.0f, 0.0f, 1, 8);
    WRITE_GFX(arg0++, 0xD8380002, 0x40);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    return arg0;
}

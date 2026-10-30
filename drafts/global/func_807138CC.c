// func_807138CC (src/global/117190.c): Stage 5 parked: frame 0x40, FP clamp (nested ternary), cvt/andi spill at 0x28 and sp3C at 0x3C all match; only diff is the Gfx macro pointer: target 'move v0,s0; sw w0,0(v0); sw w1,4(v0)' (R117D macro _g costs a frame word -> 0x48 frame, all instructions identical otherwise), draft stores through s0 directly. Prototypes needed: Gfx *func_8071338C(Gfx *) (return textDrawStringVtx), Gfx *func_807135B4(Gfx *), Gfx *func_80713438(Gfx *, s32), Gfx *func_80713764(Gfx *, s32, f32), func_807132DC K&R taking arg0.
void *heapAlloc(s32);
void heapFreeDeferred(void *);
void viewportSetFromRect(void *, s32, s32, s32, s32);
Gfx *func_806FF144(void *);
Gfx *func_80713438(Gfx *, s32);
Gfx *func_80713764(Gfx *, s32, f32);

Gfx *func_807138CC(Gfx *arg0) {
    void *sp3C;
    f32 temp_fv0;

    sp3C = heapAlloc(0x10);
    heapFreeDeferred(sp3C);
    viewportSetFromRect(sp3C, 0xA, 0xA, 0x135, 0xE5);
    arg0 = func_8071338C(func_807135B4(func_807132DC(arg0)));
    if ((u32)++D_80755320 < 0xD3U) {
        temp_fv0 = (f32) (0xD2U - D_80755320) * 0.03333333507f;
        temp_fv0 = (temp_fv0 < 0.0f) ? 0.0f : ((temp_fv0 > 1.0f) ? 1.0f : temp_fv0);
        arg0 = func_80713764(func_80713438(arg0, (u32) (255.0f * temp_fv0) & 0xFF), (u32) (255.0f * temp_fv0) & 0xFF, 0);
    }
    arg0->words.w0 = 0xDC080008;
    arg0->words.w1 = (u32)sp3C;
    arg0++;
    return func_806FF144(arg0);
}

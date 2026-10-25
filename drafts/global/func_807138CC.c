// func_807138CC (src/global/117190.c): stage 3: command sequence and D_8075E624 literal recovered; frame 0x50 vs target 0x40 and pointer should occupy s0 before the call chain
// func_807138CC: stage 3; behavior and literal recovered, but target frame is 0x40/s0 while C reaches 0x50 and does not retain the display pointer in s0.
extern u32 D_80755320;
void *func_80610FE8(s32);
void heapFreeDeferred(void *);
void func_8062C99C(void *, s32, s32, s32, s32);
Gfx *func_806FF144(void *);
Gfx *func_807132DC();
Gfx *func_8071338C(Gfx *);
Gfx *func_80713438(Gfx *, s32);
Gfx *func_807135B4(Gfx *);
Gfx *func_80713764(Gfx *, s32, s32);

Gfx *func_807138CC(Gfx *arg0) {
    void *sp3C;
    s32 sp28;
    f32 temp_fv0;
    f32 var_fv1;
    s32 temp_t2;
    u32 temp_t8;
    Gfx *var_s0;

    sp3C = func_80610FE8(0x10);
    heapFreeDeferred(sp3C);
    func_8062C99C(sp3C, 0xA, 0xA, 0x135, 0xE5);
    var_s0 = func_8071338C(func_807135B4(func_807132DC(arg0)));
    temp_t8 = D_80755320 + 1;
    D_80755320 = temp_t8;
    if (temp_t8 < 0xD3U) {
        var_fv1 = 0.0f;
        temp_fv0 = (f32) (0xD2 - temp_t8) * 0.03333333507f;
        if (temp_fv0 < 0.0f) {
        } else if (temp_fv0 > 1.0f) {
            var_fv1 = 1.0f;
        } else {
            var_fv1 = temp_fv0;
        }
        temp_t2 = (u32) (255.0f * var_fv1) & 0xFF;
        sp28 = temp_t2;
        var_s0 = func_80713764(func_80713438(var_s0, temp_t2), sp28, 0);
    }
    R117D_WRITE_GFX(var_s0++, 0xDC080008, sp3C);
    return func_806FF144(var_s0);
}

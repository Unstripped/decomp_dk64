// func_807138CC (src/global/117190.c): stage 4: preincrement/merged-alpha candidate remains best manual form (frame 0x48 vs target 0x40); 900-second permuter improved score 765→725 only through extra pointer aliases that regressed frame to 0x50, rejected
// func_807138CC: stage 4. Direct display parameter and preincrement counter now match target register flow; merging alpha and byte temporaries reduced frame to 0x48. Remaining target frame is 0x40 (sp3C target 0x3C, current 0x44).
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

    sp3C = func_80610FE8(0x10);
    heapFreeDeferred(sp3C);
    func_8062C99C(sp3C, 0xA, 0xA, 0x135, 0xE5);
    arg0 = func_8071338C(func_807135B4(func_807132DC(arg0)));
    if (++D_80755320 < 0xD3U) {
        temp_fv0 = (f32) (0xD2 - D_80755320) * 0.03333333507f;
        if (temp_fv0 < 0.0f) {
            temp_fv0 = 0.0f;
        } else if (temp_fv0 > 1.0f) {
            temp_fv0 = 1.0f;
        }
        sp28 = (u32) (255.0f * temp_fv0) & 0xFF;
        arg0 = func_80713764(func_80713438(arg0, sp28), sp28, 0);
    }
    R117D_WRITE_GFX(arg0++, 0xDC080008, sp3C);
    return func_806FF144(arg0);
}

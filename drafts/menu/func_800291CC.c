// func_800291CC (src/menu/3E10.c): stage 3 (frame 280 vs 240, FP hoist/regalloc differ): loop constants order now matches (sc=3.0f var, n85=85 int var for unfolded 85*4, four var); remaining: target loads lwc1 f12/f14 spCC/spD0 before beqz in menuSetElementCoordinates call (mine lw a2/a3), target locals above spD0 = 7 words and below spA4 = 7 words+8, x(f32)*4 'four' lands in f28 vs target f26
extern s8 D_80033804;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern f32 D_80033F4C;
extern s8 D_80033F51;
extern u32 D_8076A064;
extern s32 *D_80033F28;
extern s8 D_80033F48;
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_806FC530(s32, s16, s16, s16, void *, s32);
s32 menuSetElementCoordinates(s32, s32, f32, f32, f32);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
f32 func_80612794(s16);

s32 func_800291CC(void *arg0, Gfx *arg1) {
    f32 fa0;
    f32 fa1;
    f32 fs0;
    f32 fs0b;
    f32 fs1;
    f32 fs2;
    f32 fv1;
    f32 spD0;
    f32 spCC;
    char spA4[0x20];
    f32 x = 66.0f;
    s16 y;
    s16 px;
    s16 py;
    void *temp_s4 = *(void **)((u8 *)arg0 + 0x174);
    s32 i = 0;
    s8 *p = &D_80033804;
    f32 sc = 3.0f;
    f32 four;
    s32 n85 = 85;

    do {
        func_800317E8(temp_s4, x, 85.0f, &spD0, &spCC, 4, 0, 1.5f);
        if (*p != 0) {
            arg1 = (Gfx *)menuSetElementCoordinates((s32)arg1, i, spD0, spCC, sc * 0.85);
        } else {
            arg1 = (Gfx *)menuSetElementCoordinates((s32)arg1, i | 0x80, spD0, spCC, sc);
        }
        i++;
        p++;
        x += 55.0f;
    } while (i != 5);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s4, 160.0f, 180.0f, &spD0, &spCC, 5, 1, 2.0f);
    four = 4.0f;
    D_80033F4C = spCC * four;
    y = (s32)D_80033F4C - 0x140;
    _sprintf(spA4, "%d%%", D_80033F51);
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d", D_8003380C);
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d:%02d", D_80033810, D_80033814);
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, 0x280, y, spA4, 0x81);
    fv1 = func_80612794((D_8076A064 * 0x78) & 0xFFF) * 0.1f + 0.5f;
    y = (s32)((f32)y + 40.0f);
    fs1 = y;
    fs0 = 0.5f * four;
    fa0 = (fs1 * 0.25f + 32.0f * fv1) * four;
    fa1 = n85 * four;
    spD0 = fa1;
    spCC = fa0;
    arg1 = func_8068C5A8(arg1, 0xA1, 3, 0, 0x40, 0x40, (s32)fa1, (s32)fa0, fs0, -(fv1 * four), 0, 0.0f);
    gDPPipeSync(arg1++);
    spCC = fs1;
    fs0b = fs0 * 0.75f;
    fs2 = -fs0b;
    spD0 = 340.0f;
    arg1 = func_8068C5A8(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, fs0b, fs2 * 0.5f, D_8076A064 % 360U, 0.0f);
    gDPPipeSync(arg1++);
    arg1 = func_8068C5A8(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, fs0b, fs2, (D_8076A064 * 0xC) % 360U, 0.0f);
    gDPPipeSync(arg1++);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s4, 160.0f, 15.0f, &spD0, &spCC, 5, 1, 0.3f);
    px = spD0 * four;
    py = spCC * four;
    _sprintf(spA4, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    return (s32)hudDrawScaledText(arg1, px, py, 0.6f, spA4);
}

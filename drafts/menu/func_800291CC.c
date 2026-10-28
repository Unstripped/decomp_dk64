// func_800291CC (src/menu/3E10.c): stage 3: structural diff 362 -> 226, frame now 264 vs 240. Fixes found: (1) spD0/spCC must be READ later ((s32)spD0,(s32)spCC in the 0xA1 call) instead of via fa0/fa1 copies: more uses make uopt promote them, giving the target lwc1 f12/f14 + mfc1 a2/a3 in the loop; (2) y = D_80033F4C; y -= 0x140; (not y = (s32)D_80033F4C - 0x140) gives mfc1 t4/addiu s0,t4,-320; (3) 85 * four (int const) instead of n85 var/85.0f literal stops the 85.0 const being CSE'd with the loop's; (4) one variable fs0 (fs0 = fs0 * 0.75f) instead of fs0/fs0b. Remaining: FP webs colour (fs0 f24 then fs0b f20 vs target in-place f20, four f28 vs f26, 0.5f f30 vs f28, 0.0f not hoisted (target f30)); a2/a3 arg load order (target loads spCC first -> f12); move s0,zero placement; each removed named local only trims the frame ~8 bytes (px/py inline: 256 but score worse).
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
Gfx *func_8068C5A8(Gfx *, u16, s32, s32, s32, s32, s16, s32, f32, f32, s32, f32);
f32 func_80612794(s16);

s32 func_800291CC(void *arg0, Gfx *arg1) {
    f32 fa0;
    f32 fa1;
    f32 fs0;
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
    y = D_80033F4C;
    y -= 0x140;
    _sprintf(spA4, "%d%%", D_80033F51);
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d", D_8003380C);
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d:%02d", D_80033810, D_80033814);
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, 0x280, y, spA4, 0x81);
    fv1 = func_80612794((s16)((D_8076A064 * 0x78) & 0xFFF)) * 0.1f + 0.5f;
    y = (s32)((f32)y + 40.0f);
    fs1 = y;
    fs0 = 0.5f * four;
    spCC = (fs1 * 0.25f + 32.0f * fv1) * four;
    spD0 = 85 * four;
    arg1 = func_8068C5A8(arg1, 0xA1, 3, 0, 0x40, 0x40, (s32)spD0, (s32)spCC, fs0, -(fv1 * four), 0, 0.0f);
    gDPPipeSync(arg1++);
    spCC = fs1;
    fs0 = fs0 * 0.75f;
    fs2 = -fs0;
    spD0 = 340.0f;
    arg1 = func_8068C5A8(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, fs0, fs2 * 0.5f, D_8076A064 % 360U, 0.0f);
    gDPPipeSync(arg1++);
    arg1 = func_8068C5A8(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, fs0, fs2, (D_8076A064 * 0xC) % 360U, 0.0f);
    gDPPipeSync(arg1++);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s4, 160.0f, 15.0f, &spD0, &spCC, 5, 1, 0.3f);
    px = spD0 * four;
    py = spCC * four;
    _sprintf(spA4, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    return (s32)hudDrawScaledText(arg1, px, py, 0.6f, spA4);
}

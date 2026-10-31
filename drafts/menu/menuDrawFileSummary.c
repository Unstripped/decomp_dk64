// menuDrawFileSummary (src/menu/3E10.c): menuDrawFileSummary (src/menu/3E10.c): stage 4 (QMenu round 2, parked NON_MATCHING): frame 240 = target, saved set s0-s6,f20-f30, loop prologue and stack addrs now match (decl order 'p' before 'i', spD0 declared before spCC => spD0@208,spCC@204; spA4 still at 172 vs target 164). Remaining: (1) loop: target loads spCC->f12 first then spD0->f14 and passes a2=f14,a3=f12 (ucode arg temps reversed; all 8 combos of decl order x out-param order x arg order give f12->a2), (2) post-loop FP candidate colouring: target four f26, 0.5f f28 (loaded BEFORE the func_80612794 call), 0.0f f30 hoisted after that call, sc(cvt y) f22, -x f24 (separate expression cand), x f20 in place; ours four f28, 0.5f f30, 0.0f unhoisted. Permuter hint (score 5304->3304 and FP callee-saved regs all match): 'spD0 = 0.5f * four;' before 'fv1 = ...' and 'x = spD0;' replacing 'x = 0.5f * four;' -- but it adds a real store/load of spD0 so it is not the answer; it says 0.5f/four need an earlier use before the func_80612794 call. deadsweep (+ --extra locals) only 140->129 (if (spCC && spCC) {} after the loop, if (sc && sc) {}, if (four && four) {}): fakes, not applied. Named nx/x2/sy/half temps, inline fv1, x forms, 600 random decl orders: no gain.
extern s8 D_80033804;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern f32 D_80033F4C;
extern s8 D_80033F51;
extern u32 D_8076A064;
Gfx *menuSetElementCoordinates(Gfx *, s32, f32, f32, f32);
Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, s32, s32, s16, s32, f32, f32, s32, f32);
f32 func_80612794(s16);

s32 menuDrawFileSummary(void *arg0, Gfx *arg1) {
    f32 x = 66.0f;
    s16 y;
    s16 py;
    void *temp_s4 = *(void **)((u8 *)arg0 + 0x174);
    s8 *p = &D_80033804;
    s32 i = 0;
    f32 sc = 3.0f;
    f32 four;
    f32 spD0;
    f32 spCC;
    char spA4[0x20];
    f32 fv1;

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
    arg1 = (Gfx *)textDrawStringVtx((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d", D_8003380C);
    arg1 = (Gfx *)textDrawStringVtx((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d:%02d", D_80033810, D_80033814);
    arg1 = (Gfx *)textDrawStringVtx((s32)arg1, 1, 0x280, y, spA4, 0x81);
    fv1 = func_80612794((s16)((D_8076A064 * 0x78) & 0xFFF)) * 0.1f + 0.5f;
    y = (s32)((f32)y + 40.0f);
    sc = y;
    x = 0.5f * four;
    spCC = (sc * 0.25f + 32.0f * fv1) * four;
    spD0 = 85 * four;
    arg1 = renderRotatedSprite(arg1, 0xA1, 3, 0, 0x40, 0x40, (s32)spD0, (s32)spCC, x, -(fv1 * four), 0, 0.0f);
    gDPPipeSync(arg1++);
    spCC = sc;
    x = x * 0.75f;
    sc = -x;
    spD0 = 340.0f;
    arg1 = renderRotatedSprite(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, x, sc * 0.5f, D_8076A064 % 360U, 0.0f);
    gDPPipeSync(arg1++);
    arg1 = renderRotatedSprite(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, x, sc, (D_8076A064 * 0xC) % 360U, 0.0f);
    gDPPipeSync(arg1++);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s4, 160.0f, 15.0f, &spD0, &spCC, 5, 1, 0.3f);
    y = spD0 * four;
    py = spCC * four;
    _sprintf(spA4, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    return (s32)hudDrawScaledText(arg1, y, py, 0.6f, spA4);
}

// menuDrawFileSlotLabel (src/menu/3E10.c): menuDrawFileSlotLabel (src/menu/3E10.c): stage 4 (frame 0x128, s0=y, stack+regalloc match; 7 diff lines in arg3 of 2nd hudDrawScaledText: target addiu t2,s0,-60; sll a2,t2,16; sra t6,a2,16; move a2,t6 vs built addiu a2,s0,-60; sll t4,a2,16; sra a2,t4,16). Diagnosed: ugen ring allocation order between float mul argument 1 (sp110*4.0f) and integer argument 2 (y-60) is swapped (target evaluated y-60 first into t2, then converted a1 into t4; built evaluated a1 first into t2, then y-60 into t4).
extern s32 *D_80033F28;
s32 menuCheckSaveFile();
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);

Gfx *menuDrawFileSlotLabel(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    s32 sp120;
    Gfx *g;
    int ty;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    s16 spFE;
    s16 y;
    char sp34[200];

    g = arg1++; g->words.w0 = 0xFA000000; g->words.w1 = -1;
    sp120 = func_800317E8(temp_a0, 160.0f, 25.0f, &sp110, &sp10C, 3, 1, 0.45f);
    spFE = (s16)(sp110 * 4.0f);
    y = (s16)(sp10C * 4.0f);
    if (menuCheckSaveFile(sp120) != 0) {
        _sprintf(sp34, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp34, "%s %d", (char *)D_80033F28[7], sp120 + 1);
    }
    ty = (s16)(y - 0x3C);
    if (y == 0x7FFF) {
    }
    if (y == 0x7FFF) {
    }
    if (y == 0x7FFF) {
    }
    if (arg0) {
    }
    return hudDrawScaledText(
        hudDrawScaledText(arg1, spFE, y, 0.6f, sp34),
        (s16)(sp110 * 4.0f),
        (u16)ty,
        0.6f,
        (char *)D_80033F28[8]
    );
}

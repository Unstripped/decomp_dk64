// func_80029BB4 (src/menu/3E10.c): stage 4 (frame 0x128 via unused f32 pad locals, s0): y (s32 raw + (s16) casts) not colored s0 and arg1 takes s0 instead; target keeps arg1 in home slot 0x12c
extern s32 *D_80033F28;
s32 menuCheckSaveFile();
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);

Gfx *func_80029BB4(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    s32 sp120;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    s16 spFE;
    char sp34[200];
    s32 y;

    arg1->words.w1 = -1;
    arg1->words.w0 = 0xFA000000;
    sp120 = func_800317E8(temp_a0, 160.0f, 25.0f, &sp110, &sp10C, 3, 1, 0.45f);
    arg1 += 1;
    spFE = (s16)(sp110 * 4.0f);
    y = (s32)(sp10C * 4.0f);
    if (menuCheckSaveFile(sp120) != 0) {
        _sprintf(sp34, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp34, "%s %d", (char *)D_80033F28[7], sp120 + 1);
    }
    return hudDrawScaledText(
        hudDrawScaledText(arg1, spFE, (s16)y, 0.6f, sp34),
        (s16)(sp110 * 4.0f),
        (s16)((s16)y - 0x3C),
        0.6f,
        (char *)D_80033F28[8]
    );
}

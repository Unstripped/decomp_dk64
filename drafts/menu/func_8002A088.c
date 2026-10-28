// func_8002A088 (src/menu/3E10.c): stage 4 (frame 0x130 via pad locals): same y->s1 allocation miss as func_80029BB4 (y spilled, arg1 chain in s0)
extern s32 *D_80033F28;
s32 menuCheckSaveFile();
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);

extern s8 D_80033F48;

Gfx *func_8002A088(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    s32 sp124;
    s32 sp120;
    s32 sp11C;
    f32 sp118;
    f32 sp114;
    s32 sp110;
    s32 sp10C;
    s16 sp106;
    char sp3C[200];
    s16 y;

    arg1->words.w1 = -1;
    arg1->words.w0 = 0xFA000000;
    func_800317E8(temp_a0, 160.0f, 25.0f, &sp118, &sp114, 5, 0, 0.45f);
    arg1 += 1;
    sp106 = (s16)(sp118 * 4.0f);
    y = (s16)(sp114 * 4.0f);
    if (menuCheckSaveFile(D_80033F48) != 0) {
        _sprintf(sp3C, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp3C, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    }
    arg1 = hudDrawScaledText(hudDrawScaledText(arg1, sp106, y, 0.6f, sp3C), (s16)(sp118 * 4.0f), (s16)(y - 0x3C), 0.6f, (char *)D_80033F28[8]);
    func_800317E8(temp_a0, 160.0f, 80.0f, &sp118, &sp114, 5, 0, 2.0f);
    arg1 = hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[9]);
    func_800317E8(temp_a0, 80.0f, 120.0f, &sp118, &sp114, 5, 0, 2.0f);
    return hudDrawScaledText(hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[10]), (s16)(0x500 - (s32)(sp118 * 4.0f)), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[11]);
}

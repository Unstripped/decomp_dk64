// func_8002A088 (src/menu/3E10.c): stage 4 (frame 0x130, 18 diff lines): same single quirk as menuDrawFileSlotLabel (arg3 of the 1st hudDrawScaledText: target 'addiu t0,s1,-60; sll a2,t0,16; sra t4,a2,16; move a2,t4', mine 'addiu t2; sll t3,t2; sra a2,t3'; later t-ring shifted). OlP revisit: see menuDrawFileSlotLabel note (register-allocated ty candidate gets v1 not t0/t2 with the comma-seq forms); no transferable fix found.
extern s32 *D_80033F28;
extern s8 D_80033F48;
s32 menuCheckSaveFile();
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);

Gfx *func_8002A088(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    int ty;
    f32 sp11C;
    Gfx *g;
    f32 sp120;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    s16 sp106;
    s16 y;
    char sp3C[200];

    g = arg1++; g->words.w0 = 0xFA000000; g->words.w1 = -1;
    func_800317E8(temp_a0, 160.0f, 25.0f, &sp118, &sp114, 5, 0, 0.45f);
    sp106 = (s16)(sp118 * 4.0f);
    y = (s16)(sp114 * 4.0f);
    if (menuCheckSaveFile(D_80033F48) != 0) {
        _sprintf(sp3C, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp3C, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    }
    ty = (s16)(y - 0x3C);
    if (y == 0x7FFF) {
    }
    if (y == 0x7FFF) {
    }
    if (y == 0x7FFF) {
    }
    arg1 = hudDrawScaledText(hudDrawScaledText(arg1, sp106, y, 0.6f, sp3C), (s16)(sp118 * 4.0f), (u16)ty, 0.6f, (char *)D_80033F28[8]);
    func_800317E8(temp_a0, 160.0f, 80.0f, &sp118, &sp114, 5, 0, 2.0f);
    arg1 = hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[9]);
    func_800317E8(temp_a0, 80.0f, 120.0f, &sp118, &sp114, 5, 0, 2.0f);
    return hudDrawScaledText(hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[10]), (s16)(0x500 - (s32)(sp118 * 4.0f)), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[11]);
}

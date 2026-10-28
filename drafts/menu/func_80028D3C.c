// func_80028D3C (src/menu/3E10.c): text-identical, reloc only (.rodata+off for 0.3f and strings vs D_80033C90/B30/B34/B38); needs void *temp_a0 declared FIRST, idx, spFC, spF8, char sp2C[204], gDPSetPrimColor(arg1++,..) (macro _g gives the lowest 4-byte slot)
extern s32 D_807FBB60;
extern s32 *D_80033F28;
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 menuCheckSaveFile();

s32 func_80028D3C(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    s32 idx;
    f32 spFC;
    f32 spF8;
    char sp2C[204];

    D_807FBB60 &= ~0x10;
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    idx = func_800317E8(temp_a0, 160.0f, 15.0f, &spFC, &spF8, 4, 1, 0.3f);
    if (idx == 2) {
        _sprintf(sp2C, "%s", (char *)D_80033F28[5]);
    } else {
        if (idx == 3) {
            idx = 2;
        }
        if (menuCheckSaveFile(idx) != 0) {
            _sprintf(sp2C, "%s", (char *)D_80033F28[6]);
        } else {
            _sprintf(sp2C, "%s %d", (char *)D_80033F28[7], idx + 1);
        }
    }
    return (s32)hudDrawScaledText(arg1, (s16)(spFC * 4.0f), (s16)(spF8 * 4.0f), 0.6f, sp2C);
}

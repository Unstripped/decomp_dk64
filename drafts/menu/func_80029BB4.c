// func_80029BB4 (src/menu/3E10.c): stage 4 (frame 0x128, s0=y, arg1 homed at 0x12C, stack layout and all regalloc now match; 7 diff lines left, all in the arg3 block of the 2nd hudDrawScaledText: target 'addiu t2,s0,-60; sll a2,t2,16; sra t6,a2,16; move a2,t6' (cvt result via temp then move; later t-ring then t4 vs t2), mine 'addiu t4; sll t5,t4; sra a2,t5'). Recipe found by scripted variant harness (reduced TU, ~0.4s/compile, ~60k variants): (1) y gets s0 (arg1 spilled) only with ~3 dead 'if (y == 0x7FFF) {}' + 'if (arg0) {}' after the sprintf if (they also keep 'sw a0,296(sp)'); (2) expand gDPSetPrimColor by hand with a FUNCTION-LEVEL 'Gfx *g' (g = arg1++; g->words.w0 = 0xFA000000; g->words.w1 = -1; ONE line) -> exact 'lui t7; li t8; sw t8,4; sw t7,0' ordering and no phantom macro slot; w1/w0 separate stmts give li/lui order; (3) frame layout needs pads: decl order TA, sp120, [3 pad words: g, ty, f32], sp110, sp10C, [3 f32 pads], s16 spFE, s16 y (consecutive s16 share a slot: spFE at +2 -> sh 254), char sp34[200], nothing after; dummies add uopt temp slots below the buffer so pad counts must be re-fit after any dummy change; (4) 'int ty = (s16)(y-0x3C)' passed as (u16)ty gave the best tail (7 lines). Swept without effect: ty types s16/s32/u16/u8/int x casts x position x dummy uses, y s16/s32 x cast forms (y1/y2), '+ -0x3C' idioms, dead '(void)(y-0x3C)', permuter (700s, no gain over baseline).
extern s32 *D_80033F28;
s32 menuCheckSaveFile();
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);

Gfx *func_80029BB4(void *arg0, Gfx *arg1) {
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

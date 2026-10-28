// func_8002C634 (src/menu/3E10.c): stage 3: frame 0x150 matches only with arg1 as accumulator (no p2 temp) and K&R def; remaining: local layout (sp13C/sp138/sp134 at 0x148.. not 0x13c.., buf at 0x74 not 0x64) and reg allocation (step in a0 vs s5, y s5 vs s6, q s1 vs s2, i s2 vs s1); gfx w1/w0 li/lui order. Declaration-order permutation search (700 samples) never gave target layout.
extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;

s32 func_8002C634(arg0, arg1)
void *arg0;
Gfx *arg1;
{
    void *temp_s0 = *(void **)((u8 *)arg0 + 0x174);
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    s16 sp12C;
    char sp64[200];
    s16 x;
    s16 y;
    s32 step;
    s32 i;
    u8 *q;

    arg1->words.w1 = -1;
    arg1->words.w0 = 0xFA000000;
    arg1 += 1;
    func_800317E8(temp_s0, 160.0f, 45.0f, &sp13C, &sp138, 2, 0, 1.8f);
    func_800317E8(temp_s0, 160.0f, 185.0f, &sp13C, &sp134, 2, 0, 1.8f);
    step = 0x11D / D_80033878;
    x = step * 2 + 0x46;
    y = (s32)(sp138 * 4.0);
    q = D_80033F20;
    i = 0;
    sp12C = (s32)(sp134 * 4.0);
    if (D_80033878 > 0) {
        do {
            _sprintf(sp64, "P %d", *q + 1);
            arg1 = hudDrawScaledText(hudDrawScaledText(arg1, x, y, 0.6f, sp64), x, (s16)(y + 0x30), 0.6f, (char *)D_80033F28[0x1D + (i == D_8076A105)]);
            _sprintf(sp64, "%d", D_80744524[*q]);
            i += 1;
            q += 1;
            arg1 = hudDrawScaledText(arg1, x, sp12C, 0.6f, sp64);
            x += step * 4;
        } while (i < D_80033878);
    }
    return (s32)hudDrawScaledText(arg1, 0x280, (s16)(sp12C - 0x50), 0.6f, (char *)D_80033F28[0x1F]);
}

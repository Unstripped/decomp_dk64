// func_8002C634 (src/menu/3E10.c): stage 4 (frame 0x150, s0-s8+f20 saved set, 218 insns, stack layout 0x13C/138/134/sh 0x12C/buf 0x64 all match). Remaining: xor v1 (flag temp in v1) vs t9 + t-ring shift (~45 normalised diff lines), and q++/move s4,v0 order at loop end. Recipe: decl order temp_s0,step,i,x,sp13C,sp138,sp134,q,y,sp12C,sp64 (x lone s16, y+sp12C pair gives sh at +0), step*=4 after x, gDPSetPrimColor(arg1++,0,0,255,255,255,255) for the lui/li/sw order, y/sp12C computed before step, i+=1;q+=1;x+=step after last hud call, dead if (i) {} after the do-while to swap i/q colours. Swept: dead-stmt sweep (4 forms x all globals/locals), 5000 random + exhaustive layout-valid decl permutations, tail permutations, preheader order permutations.
extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;

s32 func_8002C634(arg0, arg1)
void *arg0;
Gfx *arg1;
{
    void *temp_s0;
    s32 step;
    s32 i;
    s16 x;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    u8 *q;
    s16 y;
    s16 sp12C;
    char sp64[200];

    temp_s0 = *(void **)((u8 *)arg0 + 0x174);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s0, 160.0f, 45.0f, &sp13C, &sp138, 2, 0, 1.8f);
    func_800317E8(temp_s0, 160.0f, 185.0f, &sp13C, &sp134, 2, 0, 1.8f);
    y = (s32)(sp138 * 4.0);
    sp12C = (s32)(sp134 * 4.0);
    step = 0x11D / D_80033878;
    x = step * 2 + 0x46;
    step *= 4;
    q = D_80033F20;
    i = 0;
    if (D_80033878 > 0) {
        do {
            _sprintf(sp64, "P %d", *q + 1);
            arg1 = hudDrawScaledText(hudDrawScaledText(arg1, x, y, 0.6f, sp64), x, (s16)(y + 0x30), 0.6f, (char *)D_80033F28[0x1D + (i == D_8076A105)]);
            _sprintf(sp64, "%d", D_80744524[*q]);
            arg1 = hudDrawScaledText(arg1, x, sp12C, 0.6f, sp64);
            i += 1;
            q += 1;
            x += step;
        } while (i < D_80033878);
        if (i) {}
    }
    return (s32)hudDrawScaledText(arg1, 0x280, (s16)(sp12C - 0x50), 0.6f, (char *)D_80033F28[0x1F]);
}

// func_8002C634 (src/menu/3E10.c): stage 4+, 2-line diff left: at loop end target has 'slt at,s1,t7; addiu s2,s2,1; move s4,v0; bnez' (q++ before the arg1 move), mine has move s4,v0 before addiu s2 (only remaining text diff; rodata reloc names aside). Recipe: K&R def; decl order temp_s0,step,i,x,sp13C,sp138,sp134,q,y,sp12C,sp64[200],sel (x lone s16 / y+sp12C consecutive s16 pair puts sh at 0x12C; floats at 0x13C..0x134; buf 0x64; sel declared LAST); gDPSetPrimColor(arg1++,0,0,255,255,255,255) gives lui/li/sw order; y,sp12C computed before step=0x11D/n; x=step*2+0x46; step*=4; q; i=0; hud(arg1,..y..) then SEPARATE stmt sel = i == D_8076A105 (makes the xor result a uopt candidate = xor v1) then hud with D_80033F28[0x1D+sel]; loop end hud, i+=1,q+=1,x+=step; dead 'if (i) {}' after the do-while swaps i/q s1/s2 colours. Swept: 5000 random decl permutations, exhaustive layout-valid orders, preheader perms, tail perms x hud placement, loop forms (for/while/do), tmp-var arg1 forms, dead-stmt sweep of 4 forms x all locals/globals/arrays at every statement boundary.
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
    s32 sel;

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
            arg1 = hudDrawScaledText(arg1, x, y, 0.6f, sp64);
            sel = i == D_8076A105;
            arg1 = hudDrawScaledText(arg1, x, (s16)(y + 0x30), 0.6f, (char *)D_80033F28[0x1D + sel]);
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

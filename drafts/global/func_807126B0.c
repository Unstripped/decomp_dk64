// func_807126B0 (src/global/117190.c): stage 2: store set and 12-store chain ok, but ours folds i=1 into constants (all D_807FC950 stores off one base) while target keeps v0=t0+i*0x5E unfolded (li a2,1; sll/subu chain), uses lui at per [0][x] store, t0 base for +0x2FB/0x2FC, and spills a0/a1 home (arg4/arg5 get a0/a1). Tried: i as s32/u8, loops (<,<=,!=, countdown; fully unrolled+folded), pointer p, do-while i+=4. Not solved.
extern u8 D_807FC950[][0x5E];
extern s8 D_8074E77C;

void func_807126B0(s32 arg0, s32 arg1, s8 arg2, s8 arg3, s8 arg4, s8 arg5, s8 arg6) {
    s32 i = 1;

    D_8074E77C = arg2;
    D_807FC950[8][0xB] = arg6 * 4;
    D_807FC950[8][0xC] = arg6;
    D_807FC950[0][0] = arg3;
    D_807FC950[0][1] = arg4;
    D_807FC950[0][4] = arg5;
    D_807FC950[i][0] = D_807FC950[i + 1][0] = D_807FC950[i + 2][0] = D_807FC950[i + 3][0] = arg3;
    D_807FC950[i][1] = D_807FC950[i + 1][1] = D_807FC950[i + 2][1] = D_807FC950[i + 3][1] = arg4;
    D_807FC950[i][4] = D_807FC950[i + 1][4] = D_807FC950[i + 2][4] = D_807FC950[i + 3][4] = arg5;
    func_80712490(arg0, arg1, 12);
}

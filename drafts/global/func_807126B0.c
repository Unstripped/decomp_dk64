// func_807126B0 (src/global/117190.c): Player-stride writes recovered; aggregate expression/register allocation remains off
void func_807126B0(s32 arg0, s32 arg1, s8 arg2, s8 arg3, s8 arg4, s8 arg5, s8 arg6) {
    s32 i = 1;
    u8 *player = (u8 *)D_807FC924 + (i * 0x2F0);

    D_8074E77C = arg2;
    ((u8 *)D_807FC924)[0x2FB] = arg6 * 4;
    ((u8 *)D_807FC924)[0x2FC] = arg6;
    ((u8 *)D_807FC924)[0] = arg3;
    ((u8 *)D_807FC924)[1] = arg4;
    ((u8 *)D_807FC924)[4] = arg5;
    player[0x11A] = player[0xBC] = player[0x5E] = player[0] = arg3;
    player[0x11B] = player[0xBD] = player[0x5F] = player[1] = arg4;
    player[0x11E] = player[0xC0] = player[0x62] = player[4] = arg5;
    func_80712490(arg0, arg1, 12);
}

// func_806FAC64 (src/global/FCCD0.c): stage 3: behavior and frame match; stride and temporary scheduling differ
void func_806FAC64(s32 arg0) {
    s32 player;
    s32 resource;
    u8 *value;

    player = (u8)arg0;
    resource = func_805FF030(D_8076A0AB, 0);
    value = (u8 *)D_807FC950 + (player * 0x306) + (resource * 2) + 0x26;
    *(u8 **)((u8 *)D_80754280 + 0x270) = value;
    *(u16 *)((u8 *)D_80754280 + 0x274) = *(u16 *)value;
    D_80754288 = player;
}

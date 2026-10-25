// func_80712944 (src/global/117190.c): Stage 6: all instructions and access order match; only register allocation uses a0/v0/v1 instead of target a2/v1/a0.
extern u16 D_80755308;
extern u8 D_8075530C;
extern u8 D_80755310;

void func_80712944(OSContPad *arg0) {
    OSContPad *temp_a2;

    controllerGetReadData();
    temp_a2 = arg0;
    temp_a2[0].stick_x &= D_8075530C;
    temp_a2[0].stick_y &= D_80755310;
    temp_a2[0].button &= D_80755308;
    temp_a2[1].stick_x &= D_8075530C;
    temp_a2[1].stick_y &= D_80755310;
    temp_a2[1].button &= D_80755308;
    temp_a2[2].stick_x &= D_8075530C;
    temp_a2[2].stick_y &= D_80755310;
    temp_a2[2].button &= D_80755308;
    temp_a2[3].stick_x &= D_8075530C;
    temp_a2[3].stick_y &= D_80755310;
    temp_a2[3].button &= D_80755308;
}

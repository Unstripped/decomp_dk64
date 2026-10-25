// func_8072177C (src/global/126260.c): Stage 4: correct pointer-base calculation still spills arg0 and hoists arg1 extension.
extern s32 D_807FDB70;
extern u8 D_807FDB74;

void func_8072177C(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    u8 temp_t3;
    u8 var_v0;
    void *temp_v1;

    var_v0 = D_807FDB74;
    if ((s32) var_v0 >= 0x20) {
        temp_t3 = var_v0 - 1;
        D_807FDB74 = temp_t3;
        var_v0 = temp_t3 & 0xFF;
    }
    D_807FDB74 = var_v0 + 1;
    temp_v1 = (var_v0 * 0x10) + D_807FDB70;
    temp_v1->unk0 = arg0;
    temp_v1->unk4 = arg1;
    temp_v1->unk6 = arg2;
    temp_v1->unk8 = arg3;
    temp_v1->unkA = arg4;
    temp_v1->unkB = arg5;
    temp_v1->unkC = arg6;
    temp_v1->unkD = arg7;
    temp_v1->unkE = arg8;
}

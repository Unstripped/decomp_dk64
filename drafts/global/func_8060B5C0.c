// func_8060B5C0 (src/global/10130.c): stage 3: behaviour recovered; frame/register allocation mismatch (0x40 frame vs target 0x20)
extern s16 D_807463A0;
extern s16 *D_807463A8;
extern s16 D_807463B0;
extern u16 *D_807ECE94;
extern s16 *D_807ECE90;
extern s16 *D_807ECE98;
extern u8 D_807ECE20[];
s16 *func_80610FE8(s32);

void func_8060B5C0(s32 arg0) {
    s16 *temp_a3;
    s16 *temp_v1;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;

    temp_v1 = D_807463A8;
    if (temp_v1 == NULL) {
        D_807463A8 = func_80610FE8(0x1C20);
    }
    temp_a3 = D_807ECE90;
    D_807ECE98 = temp_v1;
    if (temp_a3 == NULL) {
        D_807ECE90 = func_80610FE8(0xE10);
    }
    D_807ECE94 = D_807ECE90;
    memcpy(&D_807463B0, arg0, 2);
    temp_s1 = arg0 + 2;
    temp_a2 = D_807463B0 * 4;
    memcpy(D_807463A8, temp_s1, temp_a2);
    temp_s1_2 = temp_s1 + temp_a2;
    memcpy(&D_807463A0, temp_s1_2, 2);
    temp_s1_3 = temp_s1_2 + 2;
    temp_a2_2 = D_807463A0 * 2;
    memcpy(D_807ECE90, temp_s1_3, temp_a2_2);
    memcpy(D_807ECE20, temp_s1_3 + temp_a2_2, 0x70);
}

// func_80704298 (src/global/103AB0.c): stage 2 color quad builder draft; compiled and fdiffed, frame and pointer allocation differ
typedef struct {
    s16 unk0; s16 unk2; s16 unk4; u8 unk6[2]; s16 unk8; s16 unkA; s8 unkC; s8 unkD; s8 unkE; u8 unkF;
} R1F103AB0cView;
extern s16 D_807FD892;
extern s8 D_807FD894, D_807FD895, D_807FD896, D_807FD897, D_807FD898, D_807FD899;
void func_80704130(R1F103AB0cView *, s8, s8, s8, u8, u8);
void func_80704298(R1F103AB0cView *arg0, s32 arg1, u8 arg2) {
    s16 sp3C, temp_v0, temp_v0_2, var_t0, var_t1;
    s32 sp34, sp30, sp2C, temp_t6, temp_v0_3, temp_v0_4, temp_v1;
    R1F103AB0cView *temp_s0, *temp_s0_2;
    temp_t6 = arg1 & 0xFF;
    if (D_807FD892 >= 0x4000) { temp_v0 = D_807FD892 - 0x4200 + (temp_t6 * 0x14); var_t0 = temp_v0; var_t1 = temp_v0 + 0xA; }
    else { temp_v0_2 = D_807FD892 - (temp_t6 * 0x14); var_t0 = temp_v0_2; var_t1 = temp_v0_2 - 0xA; }
    if (var_t0 < 0) var_t0 = 0; if (var_t0 >= 0x100) var_t0 = 0xFF;
    if (var_t1 < 0) var_t1 = 0; if (var_t1 >= 0x100) var_t1 = 0xFF;
    temp_v0_3 = var_t0 & 0xFF; sp34 = temp_v0_3; temp_s0 = (R1F103AB0cView *)((u8 *)arg0 + 0x10); sp3C = var_t1;
    func_80704130(arg0, D_807FD894, D_807FD895, D_807FD896, temp_v0_3, arg2);
    temp_v0_4 = var_t1 & 0xFF; sp30 = temp_v0_4; temp_s0_2 = (R1F103AB0cView *)((u8 *)temp_s0 + 0x10);
    func_80704130(temp_s0, D_807FD894, D_807FD895, D_807FD896, temp_v0_4, arg2);
    temp_v1 = (arg2 | 0x40) & 0xFF; sp2C = temp_v1;
    func_80704130(temp_s0_2, D_807FD897, D_807FD898, D_807FD899, temp_v0_4, temp_v1);
    func_80704130((R1F103AB0cView *)((u8 *)temp_s0_2 + 0x10), D_807FD897, D_807FD898, D_807FD899, sp34, temp_v1);
}

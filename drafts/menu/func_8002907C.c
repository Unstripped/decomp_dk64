// func_8002907C (src/menu/3E10.c): stage 6: only v0/v1 swap (D_80033818 value in v1, D_807ECD48 in v0 in mine); temp_t8 must be assigned inside the if (outside it hoists addiu); u32 cast gives sltiu
extern u8 D_80033818;
extern u16 D_8003381C[];
extern s8 D_807563B4;
extern u16 D_807ECD48;
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_8002907C(void) {
    u8 temp_t8;

    if (D_8003381C[D_80033818] == D_807ECD48) {
        temp_t8 = D_80033818 + 1;
        D_80033818 = temp_t8;
        if ((u32)(temp_t8 & 0xFF) >= 7U) {
            D_807563B4 = 1;
            func_80609140(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
            D_80033818 = 0;
        }
    } else if (D_807ECD48 != 0) {
        D_80033818 = 0;
    }
}

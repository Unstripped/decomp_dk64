// func_806F9CD0 (src/global/FCCD0.c): Stage 3: behaviour reconstructed; global representation prevents target s0 allocation and changes frame.
extern u8 D_80754280;
void func_806F8DC4(void *, s32, s32);
void func_806F9744(void *, s32, f32, f32, s32);
void func_806F9CD0(s32 arg0) { s32 sp30; s32 sp2C; s32 temp_t6; R1FCCD0bEffect *temp_a0; u8 *temp_s0; u8 *temp_v0; temp_t6 = arg0 * 0x30; temp_s0 = &D_80754280 + temp_t6; sp2C = temp_t6; func_806F9608((R1FCCD0bAllocRecord **)(temp_s0 + 0x28)); temp_a0 = *(R1FCCD0bEffect **)(temp_s0 + 0x28); sp30 = (s32)(*(void **)((u8 *)temp_a0 + 0x14)); func_806F96CC(temp_a0, arg0); temp_v0 = &D_80754280 + sp2C; func_806F9744(*(void **)(temp_s0 + 0x28), arg0, (f32)*(s32 *)(temp_v0 + 8), (f32)*(s32 *)(temp_v0 + 0xC), 0); func_806F8DC4((void *)sp30, 0, arg0); *(s16 *)((u8 *)temp_a0 + 0x10) = 0; }

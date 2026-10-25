// func_80700088 (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
s32 func_80700088(f32 arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = arg1 & 0xFFFF;
    return ((((u32) (((f32) (((s32) (temp_v1 & 0xF800) >> 0xB) - 0x1F) * arg0) + 31.0f) & 0xFF) << 0xB) + (((u32) (((f32) (((s32) (temp_v1 & 0x7C0) >> 6) - 0x1F) * arg0) + 31.0f) & 0xFF) << 6) + (((u32) (((f32) (((s32) (temp_v1 & 0x3E) >> 1) - 0x1F) * arg0) + 31.0f) & 0xFF) * 2) + (temp_v1 & 1)) & 0xFFFF;
}

// func_806F8278 (src/global/FCCD0.c): stage 2: compiled behavioral terrain-column sum; compiler unrolls loop
typedef struct {
    u8 pad0[0x1B4];
    s16 unk1B4;
    u8 pad1B6[0x11A];
} PlayerSlots;

extern void *D_80754280;
extern u8 D_807FC950[][0x306];

void func_806F8278(s32 arg0) {
    s16 var_v0;
    s32 temp_v0;
    s32 var_a3;
    u8 *var_t2;
    u8 *temp_t1;
    u8 *temp_v1;
    s32 temp_t6;

    temp_t6 = arg0 & 0xFF;
    temp_v1 = &D_807FC950[0][temp_t6 * 0x306];
    var_v0 = 0;
    var_t2 = temp_v1;
    var_a3 = 0;
    do {
        temp_t1 = temp_v1 + 0x5E + var_a3;
        temp_v0 = var_v0 + *(u16 *)(var_t2 + 0x42) + *(u16 *)(temp_t1 + 0x42);
        var_a3 += 2;
        var_t2 += 2;
        var_v0 = temp_v0 + *(u16 *)(temp_t1 + 0xA0) + *(u16 *)(temp_t1 + 0xFE) +
            *(u16 *)(temp_t1 + 0x15C);
    } while (var_a3 < 0x1C);
    ((PlayerSlots *)D_80754280)[temp_t6].unk1B4 = var_v0;
}

// func_807065F8 (src/global/109660.c): stage 1 nested plain switch with exact jump-table case values; table layout matches but local/address allocation remains different
typedef struct {
    s16 end;
    u8 end_red;
    u8 end_green;
    u8 end_blue;
    u8 unk5;
    s16 start;
    u8 start_red;
    u8 start_green;
    u8 start_blue;
    u8 unkB;
} R2F109660cGradient;

extern R2F109660cGradient D_80754F58[];

void func_807065F8(s16 arg0, s8 *arg1, s8 *arg2, s8 *arg3) {
    R2F109660cGradient *gradient;
    s16 *gradient_data;
    s32 index;
    f32 factor;

    if (D_8076A0A8 >= 0x4C) {
        switch (D_8076A0A8) {
            case 0x7C:
            case 0x7D:
            case 0x7E:
            case 0x7F:
            case 0x80:
                *arg1 = 0x3F;
                *arg2 = 0x3F;
                *arg3 = 0x3F;
                return;
        }
    } else if (D_8076A0A8 >= 0xF) {
        switch (D_8076A0A8) {
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x44:
            case 0x45:
            case 0x4A:
            case 0x4B:
                break;
            case 0x46:
            case 0x47:
            case 0x48:
            case 0x49:
                *arg1 = 0x3F;
                *arg2 = 0x3F;
                *arg3 = 0x3F;
                return;
        }
    } else if (D_8076A0A8 == 0xE) {
        index = 0;
        gradient_data = (s16 *)D_80754F58;
        if (arg0 < gradient_data[3]) {
            do {
                index = (index + 1) & 0xFF;
            } while (arg0 < gradient_data[index * 6 + 3]);
        }
        gradient = (R2F109660cGradient *)&gradient_data[index * 6];
        factor = (f32)(arg0 - gradient->start) / (f32)(gradient->end - gradient->start);
        *arg1 = (u8)(((f32)(gradient->end_red - gradient->start_red) * factor) + gradient->start_red);
        *arg2 = (u8)(((f32)(gradient->end_green - gradient->start_green) * factor) + gradient->start_green);
        *arg3 = (u8)(((f32)(gradient->end_blue - gradient->start_blue) * factor) + gradient->start_blue);
        return;
    }
    *arg1 = -1;
    *arg2 = -1;
    *arg3 = -1;
}

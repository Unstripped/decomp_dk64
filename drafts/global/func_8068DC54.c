// func_8068DC54 (src/global/90D80.c): matched 120-byte frame size, 516/520 insns; exact local layout with s32 pad after sp5E, func_805FD030 unprototyped pass-through, func_80612D1C(f32) sine calculation, arg0 reused as glist in s1
void *func_805FD030();
f32 func_80612D1C(f32);
extern void *D_807FC924;

typedef struct R290C_DC_Sub {
    u8 pad[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} R290C_DC_Sub;

Gfx *func_8068DC54(Gfx *arg0, s16 arg1, s16 arg2, s16 *arg3, s16 arg4, u8 *arg5) {
    f32 sp74;
    char sp70[2];
    char sp6C[2];
    char sp68[2];
    char sp64[2];
    char sp60[4];
    s16 sp5E;
    s32 pad;
    s16 var_s0;
    s16 var_v1;
    u16 temp_v1;
    u8 temp_v0;
    u8 temp_t8;
    s32 temp_t9;
    s32 temp_a3;
    s32 temp;

    temp_v1 = *arg3;
    if (arg4 < temp_v1) {
        sp5E = -1;
    } else {
        sp5E = 1;
    }
    if (arg4 != temp_v1) {
        temp_v0 = *arg5;
        temp_t8 = temp_v0 - 1;
        if (temp_v0 != 0) {
            *arg5 = temp_t8;
            if (!(temp_t8 & 0xFF)) {
                *arg3 += sp5E;
                if (arg4 == *arg3) {
                    goto block_dce8;
                }
                *arg5 = 0xC;
            }
        } else {
            *arg5 = 0xC;
        }
    }
block_dce8:
    arg0 = (Gfx *)func_805FD030((s32)arg0);
    temp_t9 = (s32)((f32)arg2 * 4.0f) & 0xFFF;
    arg0->words.w0 = (s32)((((s32)((f32)arg1 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | temp_t9);
    temp_a3 = (((s32)((f32)(arg1 + 0x34) * 4.0f) & 0xFFF) << 0xC) | ((s32)((f32)(arg2 + 0x1B) * 4.0f) & 0xFFF);
    arg0->words.w1 = temp_a3;
    arg0++;
    var_s0 = 0;

    var_v1 = *arg3;
    if (var_v1 >= 100) {
        do {
            temp = var_v1 - 100;
            var_s0 += 1;
            var_v1 = temp;
        } while (temp >= 100);
    }
    if (var_v1 == 99) {
        var_s0 += 1;
    }

    sp70[0] = (var_v1 / 10) + '0';
    sp70[1] = 0;
    sp6C[0] = (var_v1 % 10) + '0';
    sp6C[1] = 0;
    sp68[0] = ((var_v1 + sp5E) / 10) + '0';
    sp68[1] = 0;
    sp64[0] = ((var_v1 + sp5E) % 10) + '0';
    sp64[1] = 0;

    sp74 = (f32)((f64)func_80612D1C((f32)((((f64)(u32)*arg5 / 12.0) * 1.57079637050628662) + 1.57079637050628662)) * 96.0);
    if (arg4 == *arg3) {
        arg0 = textDrawStringVtx(arg0, 3, arg1 * 4, arg2 * 4, sp70, 1);
        arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) + 0x50, arg2 * 4, sp6C, 1);
    } else if (sp70[0] != sp68[0]) {
        arg0 = textDrawStringVtx(arg0, 3, arg1 * 4, (s16)((f32)(arg2 * 4 - 0x60) + sp74), sp68, 1);
        arg0 = textDrawStringVtx(arg0, 3, arg1 * 4, (s16)((f32)(arg2 * 4 + 4) + sp74), sp70, 1);
        arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) + 0x50, (s16)((f32)(arg2 * 4 - 0x60) + sp74), sp64, 1);
        arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) + 0x50, (s16)((f32)(arg2 * 4 + 4) + sp74), sp6C, 1);
    } else {
        arg0 = textDrawStringVtx(arg0, 3, arg1 * 4, arg2 * 4, sp70, 1);
        arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) + 0x50, (s16)((f32)(arg2 * 4 - 0x60) + sp74), sp64, 1);
        arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) + 0x50, (s16)((f32)(arg2 * 4 + 4) + sp74), sp6C, 1);
    }

    if ((*arg3 + sp5E) >= 100) {
        temp = arg1 - 0x14;
        if (temp < 0) {
            temp = 0;
        }
        arg0->words.w0 = (s32)((((s32)((f32)temp * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | temp_t9);
        arg0->words.w1 = temp_a3;
        arg0++;
        _sprintf(sp60, "%d", var_s0);
        if (*arg3 >= 100 && *arg3 != 0xC7) {
            arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) - 0x50, arg2 * 4, sp60, 1);
        } else if (*arg3 == 0x63 || *arg3 == 0xC7) {
            arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) - 0x50, (s16)((f32)(arg2 * 4 - 0x60) + sp74), sp60, 1);
            if (*arg3 == 0xC7) {
                arg0 = textDrawStringVtx(arg0, 3, (arg1 * 4) - 0x50, (s16)((f32)(arg2 * 4 + 4) + sp74), "1", 1);
            }
        }
    }

    arg0->words.w0 = 0xE7000000;
    arg0->words.w1 = 0;
    arg0++;
    arg0->words.w0 = (s32)((((s32)((f32)((R290C_DC_Sub *)D_807FC924)->unk272 * 4.0f) & 0xFFF)) | 0xED000000 | (((s32)((f32)((R290C_DC_Sub *)D_807FC924)->unk270 * 4.0f) & 0xFFF) << 0xC));
    arg0->words.w1 = (s32)((((s32)((f32)((R290C_DC_Sub *)D_807FC924)->unk276 * 4.0f) & 0xFFF)) | (((s32)((f32)((R290C_DC_Sub *)D_807FC924)->unk274 * 4.0f) & 0xFFF) << 0xC));
    return arg0 + 1;
}

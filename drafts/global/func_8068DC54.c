// func_8068DC54 (src/global/90D80.c): never attempted before this session; 527 insns with rodata order constraint with func_8068E7B4
int _sprintf(char *, const char *, ...);
void *func_805FD030(s32, u8 *);
f32 func_80612D1C(f32, s32, u8 *, s32, s32);
Gfx *func_806FC530(Gfx *, s32, s16, s16, void *, s32);
extern void *D_807FC924;

typedef struct Act90B_DC_Sub {
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} Act90B_DC_Sub;

Gfx *func_8068DC54(Gfx *arg0, s16 arg1, s16 arg2, s16 *arg3, s16 arg4, u8 *arg5) {
    f32 sp74;
    u8 sp70;
    s8 sp71;
    u8 sp6C;
    s8 sp6D;
    u8 sp68;
    s8 sp69;
    u8 sp64;
    s8 sp65;
    char sp60[4];
    s16 sp5E;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    f64 var_ft5;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_s0;
    s16 temp_t4;
    s16 temp_t6;
    s16 temp_t8_2;
    s16 temp_v0_6;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_4;
    s16 var_s0;
    s16 var_v1;
    s32 temp_a3;
    s32 temp_ft1;
    s32 temp_ft5;
    s32 temp_t9;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_v1_2;
    u8 temp_t8;
    u8 temp_t9_2;
    u8 temp_v0;
    Gfx *temp_s1;
    Gfx *temp_s1_2;
    Gfx *temp_v0_2;
    Gfx *temp_v0_5;
    Gfx *temp_v0_7;
    Gfx *temp_v0_8;
    Gfx *temp_v0_9;
    Gfx *var_s1;
    Gfx *var_v0;
    Gfx *var_v0_2;

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
                if (arg4 != *arg3) {
                    *arg5 = 0xC;
                }
            }
        } else {
            *arg5 = 0xC;
        }
    }
    temp_v0_2 = (Gfx *)func_805FD030((s32)arg0, arg5);
    temp_s1_2 = temp_v0_2 + 1;
    var_s0 = 0;
    temp_t9 = (s32)((f32)arg2 * 4.0f) & 0xFFF;
    temp_v0_2->words.w0 = (s32)((((s32)((f32)arg1 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | temp_t9);
    temp_a3 = (((s32)((f32)(arg1 + 0x34) * 4.0f) & 0xFFF) << 0xC) | ((s32)((f32)(arg2 + 0x1B) * 4.0f) & 0xFFF);
    temp_v0_2->words.w1 = temp_a3;
    var_v1 = *arg3;
    if (var_v1 >= 0x64) {
        do {
            temp_v1_2 = var_v1 - 0x64;
            var_s0 += 1;
            var_v1 = temp_v1_2;
        } while (temp_v1_2 >= 0x64);
    }
    if (var_v1 == 0x63) {
        var_s0 += 1;
    }
    temp_v0_3 = var_v1 + sp5E;
    sp70 = (var_v1 / 10) + 0x30;
    sp71 = 0;
    sp6C = (var_v1 % 10) + 0x30;
    sp6D = 0;
    sp68 = (temp_v0_3 / 10) + 0x30;
    sp69 = 0;
    sp64 = (temp_v0_3 % 10) + 0x30;
    sp65 = 0;
    temp_t9_2 = *arg5;
    var_ft5 = (f64)temp_t9_2;
    if ((s32)temp_t9_2 < 0) {
        var_ft5 += 4294967296.0;
    }
    sp40 = temp_t9;
    sp3C = temp_a3;
    temp_v1_3:
    sp74 = (f32)((f64)func_80612D1C((f32)(((var_ft5 / 12.0) * 1.57079637050628662) + 1.57079637050628662), 0xA, arg5, temp_t9, temp_a3) * 96.0);
    if (arg4 == *arg3) {
        sp34 = (s32)(arg2 * 4);
        sp38 = (s32)(arg1 * 4);
        sp30 = (s32)(arg2 * 4);
        var_v0 = func_806FC530(func_806FC530(temp_s1_2, 3, arg1 * 4, arg2 * 4, &sp70, 1), 3, (s16)(sp38 + 0x50), (s16)sp34, &sp6C, 1);
    } else if (sp70 != sp68) {
        temp_v0_4 = arg2 * 4;
        temp_t8_2 = arg1 * 4;
        sp34 = (s32)temp_t8_2;
        temp_ft1 = (s32)((f32)(temp_v0_4 - 0x60) + sp74);
        sp38 = (s32)temp_t8_2;
        sp30 = temp_v0_4;
        sp2C = (s32)(s16)temp_ft1;
        temp_ft5 = (s32)((f32)(sp30 + 4) + sp74);
        temp_v0_5 = func_806FC530(func_806FC530(temp_s1_2, 3, temp_t8_2, (s16)temp_ft1, &sp68, 1), 3, (s16)sp34, (s16)temp_ft5, &sp70, 1);
        temp_a2 = sp38 + 0x50;
        sp34 = (s32)temp_a2;
        var_v0 = func_806FC530(func_806FC530(temp_v0_5, 3, temp_a2, (s16)sp2C, &sp64, 1), 3, (s16)sp34, (s16)temp_ft5, &sp6C, 1);
    } else {
        temp_v0_6 = arg2 * 4;
        temp_t4 = arg1 * 4;
        sp38 = (s32)temp_t4;
        sp30 = (s32)temp_v0_6;
        temp_v0_7 = func_806FC530(temp_s1_2, 3, temp_t4, temp_v0_6, &sp70, 1);
        temp_a2_2 = sp38 + 0x50;
        sp34 = (s32)temp_a2_2;
        var_v0 = func_806FC530(func_806FC530(temp_v0_7, 3, temp_a2_2, (s16)(s32)((f32)(sp30 - 0x60) + sp74), &sp64, 1), 3, (s16)sp34, (s16)(s32)((f32)(sp30 + 4) + sp74), &sp6C, 1);
    }
    var_s1 = var_v0;
    var_v1_2 = arg1 - 0x14;
    if ((*arg3 + sp5E) >= 0x64) {
        if (var_v1_2 < 0) {
            var_v1_2 = 0;
        }
        temp_v0_8 = var_s1;
        var_s1 += 1;
        temp_v0_8->words.w0 = (s32)((((s32)((f32)var_v1_2 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | sp40);
        temp_v0_8->words.w1 = sp3C;
        _sprintf(sp60, "%d", var_s0);
        temp_v1_4 = *arg3;
        if ((temp_v1_4 >= 0x64) && (temp_v1_4 != 0xC7)) {
            var_v0_2 = func_806FC530(var_s1, 3, (s16)(sp38 - 0x50), (s16)sp34, sp60, 1);
            goto block_30;
        }
        if ((temp_v1_4 == 0x63) || (temp_v1_4 == 0xC7)) {
            temp_s0 = sp38 - 0x50;
            temp_v0_9 = func_806FC530(var_s1, 3, temp_s0, (s16)(s32)((f32)(sp30 - 0x60) + sp74), sp60, 1);
            var_s1 = temp_v0_9;
            if (*arg3 == 0xC7) {
                var_v0_2 = func_806FC530(temp_v0_9, 3, temp_s0, (s16)(s32)((f32)(sp30 + 4) + sp74), "1", 1);
block_30:
                var_s1 = var_v0_2;
            }
        }
    }
    var_s1->words.w0 = 0xE7000000;
    var_s1->words.w1 = 0;
    temp_s1 = var_s1 + 1;
    temp_s1->words.w0 = (s32)((((s32)((f32)((Act90B_DC_Sub *)D_807FC924)->unk272 * 4.0f) & 0xFFF)) | 0xED000000 | (((s32)((f32)((Act90B_DC_Sub *)D_807FC924)->unk270 * 4.0f) & 0xFFF) << 0xC));
    temp_s1->words.w1 = (s32)((((s32)((f32)((Act90B_DC_Sub *)D_807FC924)->unk276 * 4.0f) & 0xFFF)) | (((s32)((f32)((Act90B_DC_Sub *)D_807FC924)->unk274 * 4.0f) & 0xFFF) << 0xC));
    return temp_s1 + 1;
}

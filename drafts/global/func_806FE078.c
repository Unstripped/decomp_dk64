// func_806FE078 (src/global/1025E0.c): m2c-guided stage 2: corrected Node offsets/u8 fields and func_80612D1C unary prototype; functional switch and render sequence recovered, target still requires original block order, conversions, register pressure, and final dispatch.
typedef struct R1F1025E0Entry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} R1F1025E0Entry;

typedef struct R1F1025E0Node {
    struct R1F1025E0Node *next;
    u8 *unk4;
    R1F1025E0Entry *unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE[2];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} R1F1025E0Node;

extern u8 D_80754A37[];
extern s32 func_805FCA64(Gfx *, u8);
extern f32 func_80612D10(f32);
extern f32 func_80612D1C(f32);
extern s32 func_806FD7A8(s16, u8);
extern Gfx *func_806FCC88(Gfx *, R1F1025E0Node *);
extern Gfx *func_806FD094(Gfx *, R1F1025E0Node *);

Gfx *func_806FE078(Gfx *arg0, s16 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    R1F1025E0Node *node;
    R1F1025E0Entry *entry;
    f32 sp7C;
    f32 sp70;
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fs4;
    f32 temp_ft2;
    s16 var_s3;
    s16 var_s5;
    s32 var_s6;
    s32 var_s7;
    u8 var_a1;

    var_fs3 = arg3;
    node = func_806FD9B4(arg1);
    var_s3 = 0;
    temp_ft2 = ((f32)D_80744490 - ((f32)func_806FBD5C(node->unkC, (s32)node->unk4) * arg6)) / 2.0f;
    sp7C = (f32)(D_80744490 >> 3);
    var_fs2 = node->unk10;
    var_fs4 = temp_ft2 - 3.0f;
    sp70 = 6.2831855f / (f32)node->unkD;
    var_s6 = 1;
    var_s7 = 1;
    var_s5 = 1;
    var_a1 = *(u8 *)node->unk4;
    while (var_a1 != 0) {
        if (var_a1 != 0x20) {
            s32 glyph;
            s32 temp_a0;
            s32 temp_a1;
            s32 temp_a2;
            s32 temp_s1;

            glyph = func_806FD7A8(node->unkC, var_a1) * arg6;
            temp_a1 = glyph & 0xFF;
            temp_s1 = glyph & 0xFF;
            temp_a2 = temp_a1 / 2;
            temp_a0 = temp_a2 & 0xFF;
            entry = &node->unk8[var_s3];
            switch (arg2) {
                case 8:
                    entry->unkC = ((f32)temp_a0 + var_fs3) * 4.0f;
                    entry->unk10 = arg4 * 4.0f;
                    var_fs3 += (f32)temp_s1;
                    entry->unk34 = (f32)((f64)func_80612D1C(node->unk18) * 0.5 + arg6);
                    if (node->unk18 > 0.0f) {
                        node->unk18 = (f32)((f64)node->unk18 - 0.1);
                    } else {
                        node->unk18 = 0.0f;
                    }
                    break;
                case 6:
                    var_s6 = 0;
                    var_s7 = 0;
                    entry->unk0 = (var_fs3 + 20.0f) * 4.0f;
                    entry->unk4 = arg4 * 4.0f;
                    entry->unk20 = (f32)((f64)func_80612D1C(node->unk18) * 0.35);
                    entry->unk30 = 1.5f;
                    var_fs3 += 28.0f;
                    break;
                case 5:
                    var_s6 = 0;
                    var_s7 = 0;
                    entry->unk0 = ((f32)temp_a0 + var_fs4) * 4.0f;
                    entry->unk4 = arg4 * 4.0f;
                    var_fs4 += (f32)temp_s1;
                    entry->unk20 = 0.0f;
                    entry->unk30 = (f32)((f64)func_80612D1C(var_fs2) * 0.05 + 1.0);
                    var_fs2 += sp70;
                    node->unk10 = (f32)((f64)node->unk10 + 0.1);
                    break;
                case 4:
                    entry->unkC = ((f32)(temp_a2 & 0xFF) + var_fs4) * 4.0f;
                    entry->unk10 = arg4 * 4.0f;
                    var_fs4 += (f32)temp_a1;
                    entry->unk34 = 1.0f;
                    break;
                case 3:
                    entry->unkC = ((f32)temp_a0 + var_fs4) * 4.0f;
                    entry->unk10 = arg4 * 4.0f;
                    var_fs4 += (f32)temp_s1;
                    entry->unk2C = 0.0f;
                    entry->unk34 = (f32)((f64)func_80612D1C(var_fs2) * 0.3 + 1.2);
                    var_fs2 += sp70;
                    node->unk10 = (f32)((f64)node->unk10 + 0.04);
                    break;
                case 1:
                    var_fs2 -= (f32)temp_a0 * 0.013f;
                    entry->unkC = (func_80612D1C(var_fs2) * sp7C + var_fs3) * 4.0f;
                    entry->unk10 = (func_80612D10(var_fs2) * sp7C + arg4) * 4.0f;
                    entry->unk2C = 3.1415927f - var_fs2;
                    var_fs2 -= (f32)temp_s1 * 0.013f;
                    break;
                case 2:
                    entry->unkC = ((f32)temp_a0 + var_fs4) * 4.0f;
                    entry->unk10 = (f32)(((f64)func_80612D1C(var_fs2 * 2.0f) * 5.0 + arg4) * 4.0);
                    var_fs2 += sp70;
                    var_fs4 += (f32)temp_s1;
                    entry->unk20 = (f32)((f64)func_80612D1C(var_fs2 * 2.0f) * 0.5);
                    node->unk10 = (f32)((f64)node->unk10 - 0.01);
                    entry->unk34 = arg6;
                    break;
                case 9:
                    entry->unkC = var_fs3 - (f32)(temp_a0 * 4);
                    var_fs3 -= (f32)(temp_s1 * 4);
                    entry->unk10 = arg4;
                    entry->unk14 = arg5;
                    var_fs2 += sp70;
                    entry->unk34 = (f32)((f64)func_80612D1C(var_fs2) * (0.2 * arg6) + arg6);
                    entry->unk2C = 3.1415927f;
                    node->unk10 = (f32)((f64)node->unk10 - 0.08);
                    break;
                case 10:
                    entry->unkC = var_fs3;
                    entry->unk10 = arg4;
                    entry->unk14 = (f32)temp_s1 + arg5;
                    var_fs2 += sp70;
                    arg5 += (f32)(temp_s1 * 4);
                    entry->unk34 = (f32)((f64)func_80612D1C(var_fs2) * (0.2 * arg6) + arg6);
                    entry->unk24 = 1.5707964f;
                    entry->unk28 = -1.5707964f;
                    entry->unk2C = 0.0f;
                    node->unk10 = (f32)((f64)node->unk10 - 0.08);
                    break;
            }
            if (var_s6 != 0) {
                entry->unk0 += (entry->unkC - entry->unk0) * node->unk14;
                entry->unk4 += (entry->unk10 - entry->unk4) * node->unk14;
                entry->unk8 += (entry->unk14 - entry->unk8) * node->unk14;
                func_806FDF54(&entry->unk18, &entry->unk24);
                func_806FDF54(&entry->unk1C, &entry->unk28);
                func_806FDF54(&entry->unk20, &entry->unk2C);
            }
            if (var_s7 != 0) {
                entry->unk30 += (entry->unk34 - entry->unk30) * node->unk14;
            }
            var_s3 += 1;
        } else {
            u8 width;

            width = D_80754A37[node->unkC * 6];
            switch (arg2) {
                case 1:
                    var_fs2 -= (f32)width * 0.013f;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                case 8:
                    var_fs4 += width;
                    break;
                case 6:
                    var_fs3 += 32.0f;
                    break;
                case 10:
                    arg5 += width;
                    break;
                default:
                    var_fs3 += width;
                    break;
            }
            var_fs2 -= (f64)width * 0.019;
        }
        if (var_fs2 < 0.0f) {
            var_fs2 += 6.2831855f;
        }
        var_a1 = ((u8 *)node->unk4)[var_s5];
        var_s5 += 1;
    }
    arg0->words.w0 = 0xE7000000;
    arg0->words.w1 = 0;
    arg0++;
    arg0->words.w0 = 0xE200001C;
    arg0->words.w1 = 0x00504240;
    arg0++;
    switch (arg2) {
        case 9:
        case 10:
            return func_806FD094(arg0, node);
        case 0xFF:
            node->unk10 = (f32)((f64)node->unk10 + 0.04);
            return func_806FD094(arg0, node);
        case 8:
            if (func_805FCA64(arg0, var_a1) == 0) {
                return arg0;
            }
        default:
            node->unk10 = (f32)((f64)node->unk10 + 0.04);
            return func_806FCC88(arg0, node);
        case 1:
            node->unk10 = (f32)((f64)node->unk10 + 0.02);
            node->unk10 = (f32)((f64)node->unk10 + 0.04);
            return func_806FCC88(arg0, node);
    }
}

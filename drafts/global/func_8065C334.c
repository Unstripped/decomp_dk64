// func_8065C334 (src/global/5E2F0.c): Stage 5/6: frame 0x88, 16 saved regs matched, text size matched (13216 bytes), switch dispatch matched; regalloc/hoisting order of 1.0f remaining
#include <ultra64.h>

typedef struct Cam2_Struct_40 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
} Cam2_Struct_40;

extern Cam2_Struct_40 D_807F7BC8[];
extern s16 D_807F7EC8;
extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;

s32 func_80651B64(s16);

void func_8065C334(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, u8 *arg5, u8 *arg6, s16 arg7) {
    f32 diff[14];
    Cam2_Struct_40 *entry;
    f32 r;
    f32 g;
    f32 b;
    s32 three;

    if (func_80651B64(arg7) == 0) {
        *arg6 = 0xFF;
        *arg5 = 0xFF;
        *arg4 = 0xFF;
        return;
    }
    if (D_807F7EC8 == 0) {
        *arg4 = (s32)(D_8076A0B4[arg7] * 255.0f);
        *arg5 = (s32)(D_8076A0B8[arg7] * 255.0f);
        *arg6 = (s32)(D_8076A0BC[arg7] * 255.0f);
        return;
    }
    r = D_8076A0B4[arg7];
    g = D_8076A0B8[arg7];
    b = D_8076A0BC[arg7];
    if (D_807F7EC8 > 0) {
        three = 3;
        entry = D_807F7BC8;
        do {
            switch (entry->unk3E) {
            default:
                break;
            case 1: {
                f32 dist;
                f32 dot;
                f32 factor;

                diff[0] = arg0 - (f32)(entry->unk38 / three);
                diff[1] = arg1 - (f32)(entry->unk3A / three);
                diff[2] = arg2 - (f32)(entry->unk3C / three);
                dist = sqrtf((diff[2] * diff[2]) + ((diff[0] * diff[0]) + (diff[1] * diff[1])));
                if (dist == 0.0f) {
                    dist = 0.1f;
                }
                diff[3] = diff[0] / dist;
                diff[4] = diff[1] / dist;
                diff[5] = diff[2] / dist;
                dot = (entry->unk14 * diff[5]) + ((diff[3] * entry->unkC) + (diff[4] * entry->unk10));
                if (dot < 0.0f) {
                    dot = 0.0f;
                }
                if (entry->unk0 <= dot) {
                    if (entry->unk4 <= dot) {
                        factor = (dot - entry->unk0) * entry->unk8;
                    } else {
                        factor = 1.0f;
                    }
                    if ((f64)dist > 300.0) {
                        if ((f64)dist > 1100.0) {
                            factor = 0.0f;
                        } else {
                            factor = (f64)factor * (1.0 - (((f64)dist - 300.0) / 800.0));
                        }
                    }
                    r += entry->unk2C * factor;
                    g += entry->unk30 * factor;
                    b += entry->unk34 * factor;
                }
                break;
            }
            case 0: {
                f32 dist;
                f32 diff_val;
                f32 range;
                f32 max_range;
                f32 factor;

                diff[2] = (f32)(entry->unk3C / three) - arg2;
                diff[0] = (f32)(entry->unk38 / three) - arg0;
                diff[1] = (f32)(entry->unk3A / three) - arg1;
                dist = sqrtf((diff[2] * diff[2]) + ((diff[0] * diff[0]) + (diff[1] * diff[1])));
                diff_val = dist - (f32)arg3;
                if (dist <= (f32)arg3) {
                    diff_val = 0.1f;
                }
                range = entry->unk28 / 3.0f;
                if (diff_val < range) {
                    r += entry->unk2C;
                    g += entry->unk30;
                    b += entry->unk34;
                } else {
                    max_range = ((1.0f / entry->unk24) / 3.0f) - range;
                    if ((diff_val - range) < max_range) {
                        factor = 1.0f - ((diff_val - range) / max_range);
                        r += entry->unk2C * factor;
                        g += entry->unk30 * factor;
                        b += entry->unk34 * factor;
                    }
                }
                break;
            }
            }
            entry++;
        } while (entry < &D_807F7BC8[D_807F7EC8]);
    }
    if (r > 1.0f) {
        r = 1.0f;
    }
    if (g > 1.0f) {
        g = 1.0f;
    }
    if (b > 1.0f) {
        b = 1.0f;
    }
    *arg4 = (s32)(r * 255.0f);
    *arg5 = (s32)(g * 255.0f);
    *arg6 = (s32)(b * 255.0f);
}

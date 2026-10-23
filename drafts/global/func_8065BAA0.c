// func_8065BAA0 (src/global/5E2F0.c): Stage 5/6: frame size 168 matched, register saves matched, regalloc remaining
#include <ultra64.h>

typedef struct Cam2_Struct_3C {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk14;
    /* 0x14 */ f32 unk14_pad;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B;
} Cam2_Struct_3C;

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

extern Cam2_Struct_3C D_807F7500[];
extern Cam2_Struct_40 D_807F78C0[];
extern s16 D_80748300;
extern s16 D_807F7BC0;

void func_8065BE74(s16);
s32 func_8065BF18(Cam2_Struct_3C *, f32, f32, f32, s16, s16, s16, s16, s16, s16, s32);

s16 func_8065BAA0(volatile f32 arg0, volatile f32 arg1, volatile f32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, s8 *arg10) {
    f32 diff[6];
    s32 i;
    Cam2_Struct_3C *var_s0;
    f32 dist;
    f32 temp_fa0, temp_fa1;
    f32 temp_f1;
    f32 temp_ft4, temp_ft5, temp_ft2;
    f32 three;
    s16 a4 = arg4;
    s16 a5 = arg5;
    s16 a6 = arg6;

    *arg10 = 0;
    D_807F7BC0 = 0;
    three = 3.0f;
    var_s0 = D_807F7500;
    for (i = 0; i < D_80748300; i++, var_s0++) {
        if (func_8065BF18(var_s0, arg0, arg1, arg2, arg3, a4, a5, a6, arg7, arg8, arg9)) {
            if (D_807F7BC0 < 12) {
                if (var_s0->unk3A & 1) {
                    *arg10 = 1;
                }
                D_807F78C0[D_807F7BC0].unk3F = i;
                D_807F78C0[D_807F7BC0].unk38 = var_s0->x * 3.0f;
                D_807F78C0[D_807F7BC0].unk3A = var_s0->y * 3.0f;
                D_807F78C0[D_807F7BC0].unk3C = var_s0->z * 3.0f;
                D_807F78C0[D_807F7BC0].unk2C = (f64)(u32)var_s0->unk36 / 255.0;
                D_807F78C0[D_807F7BC0].unk30 = (f64)(u32)var_s0->unk37 / 255.0;
                D_807F78C0[D_807F7BC0].unk34 = (f64)(u32)var_s0->unk38 / 255.0;
                D_807F78C0[D_807F7BC0].unk3E = var_s0->unk39;
                switch (var_s0->unk39) {
                case 1:
                    diff[0] = var_s0->unk24 - var_s0->x;
                    diff[1] = var_s0->unk28 - var_s0->y;
                    diff[2] = var_s0->unk2C - var_s0->z;
                    dist = sqrtf((diff[2] * diff[2]) + ((diff[0] * diff[0]) + (diff[1] * diff[1])));
                    if (dist == 0.0f) {
                        dist = 0.1f;
                    }
                    D_807F78C0[D_807F7BC0].unk18 = 0x127690;
                    D_807F78C0[D_807F7BC0].unk4 = var_s0->unk4;
                    D_807F78C0[D_807F7BC0].unkC = diff[0] / dist;
                    D_807F78C0[D_807F7BC0].unk0 = var_s0->unkC;
                    D_807F78C0[D_807F7BC0].unk10 = diff[1] / dist;
                    D_807F78C0[D_807F7BC0].unk8 = var_s0->unk10;
                    D_807F78C0[D_807F7BC0].unk14 = diff[2] / dist;
                    break;
                case 0:
                    if (var_s0->unk14 == 0.0f) {
                        var_s0->unk14 = 0.1f;
                    }
                    temp_fa0 = var_s0->unk14 * 3.0f;
                    temp_f1 = var_s0->unk14 / three;
                    temp_fa1 = temp_f1 * 3.0f;
                    D_807F78C0[D_807F7BC0].unk20 = temp_fa1;
                    D_807F78C0[D_807F7BC0].unk18 = (s32)(temp_fa0 * temp_fa0);
                    D_807F78C0[D_807F7BC0].unk1C = 1.0f / (temp_fa0 - temp_fa1);
                    temp_ft4 = var_s0->unk14 * 1.3f;
                    temp_f1 = temp_ft4 / three;
                    temp_ft5 = temp_f1 * 3.0f;
                    temp_ft2 = temp_ft4 * 3.0f;
                    D_807F78C0[D_807F7BC0].unk28 = temp_ft5;
                    D_807F78C0[D_807F7BC0].unk24 = 1.0f / (temp_ft2 - temp_ft5);
                    break;
                }
                func_8065BE74(D_807F7BC0);
                D_807F7BC0++;
            }
        }
    }
    return D_807F7BC0;
}

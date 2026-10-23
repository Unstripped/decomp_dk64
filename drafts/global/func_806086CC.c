// func_806086CC (src/global/7130.c): Stage 4/5: 10 insns diff (0x6dc expected vs 0x704 built), frame 0x88, fs0 allocated, fs1 spilled to stack, fully equivalent behaviour
typedef struct Aud7130L1_PlayerStruct {
    u8 unk0;
    char pad1[0x20F];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    char pad234[0x90];
    f32 unk2C4;
    char pad2C8[0x28];
} Aud7130L1_PlayerStruct;

extern Aud7130L1_PlayerStruct *D_807FC924;
extern u8 D_807FC928;
extern f32 D_80770DE4;

void func_8061CF24(s16 *, s16 *, s16 *, s16 *);
f32 func_80612D1C(f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
s16 func_80609140(s16, s32, f32, f32, u8, u8);

s32 func_806086CC(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, s16 arg5, u8 arg6, u8 arg7, f32 arg8, u8 arg9);

s32 func_806086CC(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, s16 arg5, u8 arg6, u8 arg7, f32 arg8, u8 arg9) {
    s16 sp62;
    s16 sp60;
    s16 sp5E;
    s16 sp5C;
    f32 sp74;
    s32 var_a1;
    u8 i;
    u8 closest_idx = 0;

    D_80770DE4 = -1.0f;
    for (i = 0; i < D_807FC928; i++) {
        if (D_807FC924[i].unk0 != 0) {
            s32 dx = D_807FC924[i].unk210 - arg0;
            s32 dy = D_807FC924[i].unk214 - arg1;
            s32 dz = D_807FC924[i].unk218 - arg2;
            if (D_80770DE4 == -1.0f || (f32)(dx * dx + dy * dy + dz * dz) < D_80770DE4) {
                closest_idx = i;
                D_80770DE4 = dx * dx + dy * dy + dz * dz;
            }
        }
    }

    if (D_80770DE4 == -1.0f) {
        return -1;
    }

    sp5C = D_807FC924[closest_idx].unk210;
    sp5E = D_807FC924[closest_idx].unk214;
    sp60 = D_807FC924[closest_idx].unk218;
    sp62 = (D_807FC924[closest_idx].unk2C4 * 4096.0) / 6.2831854820251465;
    func_8061CF24(&sp5C, &sp5E, &sp60, &sp62);

    if (D_80770DE4 < 500.0f) {
        sp74 = 0.0f;
    } else {
        sp74 = (f64)mathAngleBetweenPointsRad(sp5C, sp60, arg0, arg2) - ((f64)(sp62 * 6.2831855f) * 0.000244140625);
        if (sp74 < 0.0f) {
            sp74 += 6.2831855f;
        }
        if (sp74 > 1.5707964f && (f64)sp74 < 4.71238911151886) {
            arg9 |= 0x80;
        }
    }

    if (arg7 == 0) {
        var_a1 = ((f64)(u32)arg4 * 32767.0) / 255.0;
    } else {
        f64 temp_ft5 = sp74;
        f32 temp_fa0_2;
        f32 diff;

        D_80770DE4 = sqrtf(D_80770DE4);
        if (D_807FC928 == 1 && (f64)arg8 >= 0.8) {
            f32 dy1 = arg2 - sp60;
            f32 dx1 = arg0 - sp5C;
            f32 dy2 = D_807FC924->unk230 - sp60;
            f32 dx2 = D_807FC924->unk228 - sp5C;
            f32 angle2;

            arg0 = mathAngleBetweenPointsRad(sp5E, 0.0f, arg1, sqrtf(dy1 * dy1 + dx1 * dx1));
            angle2 = mathAngleBetweenPointsRad(sp5E, 0.0f, D_807FC924->unk22C, sqrtf(dy2 * dy2 + dx2 * dx2));
            diff = arg0 - angle2;
            if (arg0 < angle2) {
                diff += 6.2831855f;
            }
            if (diff > 3.1415927f) {
                diff = 6.2831855f - diff;
            }
            if ((f64)diff > 0.39269909262657166) {
                D_80770DE4 *= 1.0 + ((f64)(diff - 0.3926991f) * 20.0);
            }
        }

        if (temp_ft5 > 0.7853981852531433 && temp_ft5 < 5.497787296772003) {
            arg0 = 1.0f;
            D_80770DE4 *= arg0 - (func_80612D1C(((2.0 * temp_ft5) / 3.0) + 2.617993950843811) * arg8);
        } else {
            arg0 = 1.0f;
        }
        if (D_80770DE4 < arg0) {
            D_80770DE4 = arg0;
        }

        temp_fa0_2 = (f32)(arg7 * 4000);
        var_a1 = (temp_fa0_2 / sqrtf(D_80770DE4)) - ((temp_fa0_2 / 7.74596600000000013) - 32767.0);
        if (var_a1 >= 0x8000) {
            var_a1 = 0x7FFF;
        }
        var_a1 = (arg4 * var_a1) / 255.0;
    }

    if (var_a1 >= 1001) {
        return func_80609140(arg3, var_a1, (arg0 - func_80612D1C(sp74)) * 63.5, (f64)arg5 / 127.0, arg6, arg9);
    }
    return -1;
}

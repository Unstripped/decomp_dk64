// func_8062DBDC (src/global/2F550.c): Stage 3 (NM2F3). 285 vs 281 insns, frame 0xD0 vs 0xB0. Verified behavior: 8-corner bounding box frustum culling against D_807F5E50 plane, point-in-box test, and 5-plane clipping tests. Callee prototypes checked against current src definitions. Target saves fs0-fs3 and s0-s6, ra.
typedef struct ClipPlane {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 unk20;
    /* 0x28 */ f64 unk28;
    /* 0x30 */ f64 unk30;
    /* 0x38 */ f64 unk38;
} ClipPlane;

extern f32 D_807F5E50[];

f32 boxMinCornerDistance(s16, s16, s16, s16, s16, s16, f32, f32, f32);
s32 clipPolyToBox(s32, s16, s16, s16, s16, s16, s16, void *);

s32 func_8062DBDC(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, void *arg10) {
    f32 sp8C;
    f32 sp80;
    f32 sp70;
    s32 in1;
    s32 in2;
    s32 behind;
    s32 i;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs2_2;
    f32 temp_fs3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_ft5_2;

    temp_fa1 = arg0;
    sp80 = arg1;
    temp_ft5 = temp_fa1 * D_807F5E50[0];
    temp_fs1 = sp80 * D_807F5E50[1];
    sp70 = arg2;
    temp_fa0 = sp70 * D_807F5E50[2];
    temp_fs2 = temp_ft5 + temp_fs1;
    sp8C = temp_fa1;
    if (D_807F5E50[3] + (temp_fs2 + temp_fa0) < 0.0) {
        temp_fa1_2 = arg5 * D_807F5E50[2];
        if (D_807F5E50[3] + (temp_fs2 + temp_fa1_2) < 0.0) {
            temp_fs2_2 = arg4 * D_807F5E50[1];
            temp_fs3 = temp_ft5 + temp_fs2_2;
            if (D_807F5E50[3] + (temp_fs3 + temp_fa0) < 0.0 && D_807F5E50[3] + (temp_fs3 + temp_fa1_2) < 0.0) {
                temp_ft5_2 = arg3 * D_807F5E50[0];
                temp_fs0 = temp_ft5_2 + temp_fs1;
                if (D_807F5E50[3] + (temp_fs0 + temp_fa0) < 0.0 && D_807F5E50[3] + (temp_fs0 + temp_fa1_2) < 0.0) {
                    temp_ft4 = temp_ft5_2 + temp_fs2_2;
                    if (D_807F5E50[3] + (temp_ft4 + temp_fa0) < 0.0 && D_807F5E50[3] + (temp_ft4 + temp_fa1_2) < 0.0) {
                        return 0;
                    }
                }
            }
        }
    }
    in1 = 0;
    in2 = 0;
    behind = 0;
    if (sp8C <= arg6 && arg6 <= (f32)arg3 && sp80 <= arg7 && arg7 <= (f32)arg4 && sp70 <= arg8 && arg8 <= (f32)arg5) {
        return 1;
    }
    for (i = 0; i < 5 && behind == 0; i++) {
        if (((ClipPlane *)arg10)[i].unk38 + ((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg1) + ((ClipPlane *)arg10)[i].unk30 * arg2) < 0.0) {
            in1 = 1;
        }
        if (((ClipPlane *)arg10)[i].unk38 + ((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg4) + ((ClipPlane *)arg10)[i].unk30 * arg2) < 0.0) {
            in2 = 1;
        }
        if (in1 != 0 && in2 != 0) {
            behind = 1;
        }
    }
    if (behind == 0 && boxMinCornerDistance(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) < arg9) {
        return 1;
    }
    for (i = 0; i < 5; i++) {
        if (clipPolyToBox(i, arg0, arg1, arg2, arg3, arg4, arg5, arg10) != 0) {
            return 1;
        }
    }
    return 0;
}

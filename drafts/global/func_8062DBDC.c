// func_8062DBDC (src/global/2F550.c): Stage 3 (NM2F3). Draft now compiles against the file (typedef/extern already present; needs prototypes for boxMinCornerDistance/E1F8 above). Frame 0xD0 vs 0xB0 (target saves f20-f26 = 4 fp regs, s0-s6; mine 3 fp regs) and 283 vs 281 insns. Inlining subsets of the 11 m2c temps (2048 combos) and a DOT macro form never got below 363 diff lines / frame 0xB8; loads of D_807F5E50[0..3] are CSE'd into regs in target (D1->fs0, D2->fs3), x0/y0/z0 homes at 0x8C/0x80/0x70.
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

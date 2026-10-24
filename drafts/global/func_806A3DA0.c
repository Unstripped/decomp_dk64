// func_806A3DA0 (src/global/A8400.c): TEXT OK: instruction stream identical; only a %lo addend differs (3000.0f lands at .rodata+0x20 in the copy because other constants still come from the GLOBAL_ASM blocks). Key trick from the permuter: extra (s16) cast INSIDE the &0xFFF, i.e. (s16)((s16)(s32)x & 0xFFF), on both angle chains -- that is what makes IDO keep the mfc1 result in t0/t8 instead of folding into a0.
f32 func_80612790(s16);
f32 func_80612794(s16);

typedef struct M7Angle {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
} M7Angle;

void func_806A3DA0(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, M7Angle *arg4) {
    *arg0 += (arg2 * arg3) * 24.0f * func_80612794((s16) ((s16) ((s32) ((f32) arg4->unk38 + (arg2 * 3000.0f))) & 0xFFF));
    *arg1 += (arg2 * arg3) * 16.0f * func_80612790((s16) ((s16) ((s32) ((f32) arg4->unk3A + (arg2 * 3000.0f))) & 0xFFF));
}

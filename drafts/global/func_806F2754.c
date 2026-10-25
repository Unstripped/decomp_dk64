// func_806F2754 (src/global/F56F0.c): Stage 3: reconstructed player-path camera angular clamp, including both wrapped angle clamp branches and 8-byte output entry; retained for frame/type tuning.
typedef struct F5CPathSample {
    u8 pad0[0x210];
    f32 x0;
    f32 z0;
    f32 y0;
    u8 pad21C[0x228 - 0x21C];
    f32 x1;
    f32 z1;
    f32 y1;
} F5CPathSample;
typedef struct F5CChain3 { u8 pad0[0xB2]; s16 unkB2; } F5CChain3;
typedef struct F5CChain2 { u8 pad0[0x174]; F5CChain3 *unk174; } F5CChain2;
typedef struct F5CChain1 { u8 pad0[0x104]; F5CChain2 *unk104; } F5CChain1;
typedef struct F5CCameraActor { u8 pad0[0xE6]; s16 unkE6; u8 padE8[0x174 - 0xE8]; F5CChain1 *unk174; } F5CCameraActor;
typedef struct F5CCameraEntry { s8 unk0; u8 unk1; s16 unk2; s16 unk4; s16 unk6; } F5CCameraEntry;
extern f32 func_80611BB4(f32, f32);
void func_806F2754(F5CCameraActor *arg0, F5CCameraEntry *arg1, s32 *arg2) {
    F5CPathSample *sample;
    f32 x;
    f32 y;
    f32 planar_angle;
    s16 delta;
    s16 clamped;
    sample = (F5CPathSample *)D_807FC924 + D_807FC929;
    x = sample->y0 - sample->y1;
    y = sample->x0 - sample->x1;
    delta = (arg0->unk174->unk104->unk174->unkB2 - arg0->unkE6) - 0x800;
    planar_angle = func_80611BB4(sample->z0 - sample->z1, sqrtf((x * x) + (y * y)));
    clamped = delta & 0xFFF;
    if ((clamped < 0xC00) && (clamped >= 0x801)) {
        clamped = 0xC00;
        arg0->unkE6 = (arg0->unkE6 + (delta & 0xFFF)) - 0xC00;
    } else if ((clamped >= 0x401) && (clamped < 0x800)) {
        arg0->unkE6 = (arg0->unkE6 + (delta & 0xFFF)) - 0x400;
        clamped = 0x400;
    }
    arg1[*arg2].unk0 = -128;
    arg1[*arg2].unk1 = 2;
    arg1[*arg2].unk2 = (s16)(u32)(((f64)clamped / 4095.0) * 65535.0);
    arg1[*arg2].unk4 = (s16)(u32)((f64)(planar_angle / 6.2831855f) * 65535.0);
    arg1[*arg2].unk6 = 0;
    *arg2 += 1;
}

// func_806F2754 (src/global/F56F0.c): Stage 3 semantic reconstruction corrected sample stride to 0x2F0 and output halfword ordering; closest is 16 bytes long with 0x28 frame versus target 0x20.
typedef struct F5N5PathSample {
    u8 pad0[0x210];
    f32 x0;
    f32 z0;
    f32 y0;
    u8 pad21C[0x228 - 0x21C];
    f32 x1;
    f32 z1;
    f32 y1;
    u8 pad234[0x2F0 - 0x234];
} F5N5PathSample;

typedef struct F5N5Chain3 {
    u8 pad0[0xB2];
    s16 unkB2;
} F5N5Chain3;

typedef struct F5N5Chain2 {
    u8 pad0[0x174];
    F5N5Chain3 *unk174;
} F5N5Chain2;

typedef struct F5N5Chain1 {
    u8 pad0[0x104];
    F5N5Chain2 *unk104;
} F5N5Chain1;

typedef struct F5N5CameraActor {
    u8 pad0[0xE6];
    s16 unkE6;
    u8 padE8[0x174 - 0xE8];
    F5N5Chain1 *unk174;
} F5N5CameraActor;

typedef struct F5N5CameraEntry {
    s8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} F5N5CameraEntry;

extern f32 func_80611BB4(f32, f32);
#define F5N5_PATH_SAMPLE ((F5N5PathSample *)D_807FC924 + D_807FC929)

void func_806F2754(F5N5CameraActor *arg0, F5N5CameraEntry *arg1, s32 *arg2) {
    f32 x;
    f32 y;
    f32 planarAngle;
    s16 delta;
    s16 clamped;

    x = F5N5_PATH_SAMPLE->y0 - F5N5_PATH_SAMPLE->y1;
    y = F5N5_PATH_SAMPLE->x0 - F5N5_PATH_SAMPLE->x1;
    delta = (arg0->unk174->unk104->unk174->unkB2 - arg0->unkE6) - 0x800;
    planarAngle = func_80611BB4(F5N5_PATH_SAMPLE->z0 - F5N5_PATH_SAMPLE->z1, sqrtf((x * x) + (y * y)));
    clamped = delta & 0xFFF;
    if ((clamped < 0xC00) && (clamped >= 0x801)) {
        arg0->unkE6 = (arg0->unkE6 + clamped) - 0xC00;
        clamped = 0xC00;
    } else if ((clamped >= 0x401) && (clamped < 0x800)) {
        arg0->unkE6 = (arg0->unkE6 + clamped) - 0x400;
        clamped = 0x400;
    }
    arg1[*arg2].unk0 = -128;
    arg1[*arg2].unk1 = 2;
    arg1[*arg2].unk4 = (s16)(u32)(((f64)clamped / 4095.0) * 65535.0);
    arg1[*arg2].unk2 = (s16)(u32)((f64)(planarAngle / 6.2831855f) * 65535.0);
    arg1[*arg2].unk6 = 0;
    *arg2 += 1;
}

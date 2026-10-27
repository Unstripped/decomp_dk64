// func_80028AD0 (src/race/36B0.c): stage 5 (parked NON_MATCHING): frame 0x60, slots, all integer regs match (int sp38/int temp_v0 instead of s32/s16 fixed the li t4,1 ring shift). Remaining: FP regalloc in the camSetFixedView clamp: expected dist copy temp_fv1 in $f2 (mov.s f2,f0 after func_80027920) and var_fv0/var_fv1 in f0/f2, mine uses f12/f2; ~7 FP-reg lines. Decl-order sweeps of the f32 locals, sp34 reuse, permuter 10+7 min no gain.
extern s32 *D_807F5FD4;
extern void *D_807FBB40;
typedef struct {
    char pad0[4];
    void *unk4;
    char pad8[0x2F0 - 8];
} RaceBStructPlayer;
extern RaceBStructPlayer *D_807FC924;
s32 raceGetPrevWaypointIndex(s32, s32);
void camSetFixedView(void *, f32, f32, f32, f32, f32, f32, s32);
void func_80026354(void *, void *, s32);

void func_80028AD0(void) {
    s32 pad54[3];
    u8 *sp50;
    u8 *sp4C;
    u8 *sp48;
    s32 pad44;
    u8 *sp40;
    s32 pad3C;
    int sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_fv0;
    f32 var_fv0;
    f32 var_fv1;
    f32 temp_fv0_3;
    int temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_a1;

    temp_s0 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    temp_s1 = *(u8 **)((u8 *)D_807FBB40 + 0x174);
    sp50 = *(u8 **)(temp_s0 + 0x30);
    sp4C = *(u8 **)(sp50 + 0x174);
    sp48 = *(u8 **)(sp50 + 0x178);
    temp_a1 = (u8 *)D_807FC924[sp4C[0x28]].unk4;
    sp40 = *(u8 **)(temp_a1 + 0x174);
    sp38 = (D_807F5FD4[temp_s0[0] + 1] - D_807F5FD4[temp_s0[0]]) / 12;
    sp30 = 1.0f;
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        temp_v0 = raceGetPrevWaypointIndex(sp38, *(u16 *)(sp48 + 2));
        *(u16 *)(temp_s0 + 2) = temp_v0;
        *(u16 *)(temp_s0 + 2) = raceGetPrevWaypointIndex(sp38, (u16)temp_v0);
        temp_s0[0] = temp_s0[1] = 1;
        func_80026354(temp_s0, temp_s1, 0);
    }
    temp_v0_2 = sp4C[0x34];
    if (temp_v0_2 != temp_s1[0x34]) {
        temp_s1[0x34] = temp_v0_2;
        temp_s1[0x35] = 0;
    }
    temp_fv0 = func_80027920((s32)D_807FBB40, (s32)temp_s0, (s32)sp50, (Waypoint *)sp48);
    sp34 = temp_fv0;
    temp_v0_3 = sp48[1];
    if (temp_v0_3 != temp_s0[1]) {
        temp_s0[1] = temp_v0_3;
        *(f32 *)(temp_s0 + 8) = 0.0f;
    }
    if ((temp_s1[0x34] >= 2) && (temp_s1[0x34] < 4)) {
        if ((u32)sp48[0x10] > 24.0) {
            sp30 = -2.5f;
        } else if (*(f32 *)(sp48 + 0x14) > 0.5f) {
            sp30 = 2.5f;
        }
        temp_s0[0x39] = sp48[0x39];
        temp_s0[0x10] = sp48[0x10];
        *(f32 *)(temp_s1 + 4) = *(f32 *)(sp4C + 4) + ((temp_fv0 - (90.0f * sp30)) * 0.006f);
        if (temp_fv0 < 30.0f) {
            if (*(f32 *)(sp50 + 0xB8) < *(f32 *)((u8 *)D_807FBB40 + 0xB8)) {
                *(f32 *)((u8 *)D_807FBB40 + 0xB8) = *(f32 *)(sp50 + 0xB8);
            }
        }
        func_80026354(temp_s0, temp_s1, 0);
    }
    if ((temp_s1[0x34] < 4) && (temp_s1[0x34] > 0)) {
        temp_fv0_3 = sp34 / 90.0f;
        if (temp_fv0_3 < 0.0f) {
            var_fv0 = 0.0f;
        } else {
            if (temp_fv0_3 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = temp_fv0_3;
            }
            var_fv0 = var_fv1;
        }
        camSetFixedView(*(void **)(sp40 + 0x104), *(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80) + ((20.0f * var_fv0) + 20.0f), *(f32 *)((u8 *)D_807FBB40 + 0x84), *(f32 *)(sp50 + 0x7C), *(f32 *)(sp50 + 0x80) + 20.0f, *(f32 *)(sp50 + 0x84), 1);
    }
}

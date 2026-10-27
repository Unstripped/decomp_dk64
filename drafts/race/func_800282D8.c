// func_800282D8 (src/race/36B0.c): stage 3: with 6th arg of func_806086CC as u8 (mfc1/sw now matches), named chain locals + 'new_var = D_807FBB40' in the sfx call arg: frame 0x40, v0/v1 chain, lhu a1, mfc1 all match. Remaining: D_807FBB40 candidate colored t0 (expected a0) and temp_t0 t1 (expected t0), plus extra move a0,t0 before sfx call. Without new_var global is colored s0 (frame 0x48). Inline chain gets global=a0 but chain temps t6/t7/v1 (frame 0x38). Coloring order: chain candidates (short ranges) colored before the global. permuter cannot setup (late_rodata_alignment).
extern void *D_807FBB40;
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void func_806086CC(f32, f32, s32, s32, s32, u8, s32, s32, f32, s32);

void func_800282D8(void) {
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_t0;
    u16 var_a1;
    void *new_var;

    temp_v0 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    temp_v1 = *(u8 **)(temp_v0 + 0x30);
    temp_t0 = *(u8 **)(temp_v1 + 0x174);
    var_a1 = *(u16 *)(temp_t0 + 0x1C);
    switch (var_a1) {
    case 0x5A:
        sfxPlayActorSound((new_var = D_807FBB40), 0x107, 0, 1, 0, 0xFF, 1.0f, 0);
        var_a1 = *(u16 *)(temp_t0 + 0x1C);
    case 0x1D:
    case 0x25:
    case 0x2C:
    case 0x30:
    case 0x38:
    case 0x3F:
    case 0x43:
    case 0x47:
    case 0x4E:
    case 0x54:
        func_806086CC(*(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80), *(s32 *)((u8 *)D_807FBB40 + 0x84), 0x187, 0xFF, (s32)(((f64)(var_a1 - 0x1D) * 0.5) + 157.0), 0, 0, 0.3f, 0);
        break;
    }
}

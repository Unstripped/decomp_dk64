// func_806B4194 (src/global/B7490.c): R3B7490a stage 6, 14 rows unchanged: only reg naming. Target: cases 1/0 c[2] consts in a0 (not ugen t8/t9), so ugen temps shift (lui D_8076A064 = t8, not t0). Tried: u8 col temp, struct/union/u8[3] for c, (u8)c[2], arg3 proto u8 w/o mask, arg order, s32 var_v0, decl orders, && forms, 600s permuter (no improvement from 80).
void func_807149C8(s32, s32, s32, u8);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);

void func_806B4194(void) {
    u8 c[4];
    f32 f;
    u32 var_v0;

    switch (B7490A->unk134) {
        case 2:
            c[2] = 0xC8;
            var_v0 = 0x20;
            f = 0.5f;
            break;
        case 1:
            var_v0 = 0x18;
            c[2] = 0x64;
            f = 1.0f;
            break;
        case 0:
            var_v0 = 8;
            c[2] = 0x32;
            f = 1.5f;
            break;
        default:
            var_v0 = 0;
    }
    if ((var_v0 != 0) && ((D_8076A064 % var_v0) == 0)) {
        func_80714998(3);
        func_807149C8(c[2], c[2], c[2] & 0xFF, *(u8 *) ((u8 *) D_807FBB40 + 0x129));
        effectSpawnBoneDefault(D_807FBB40, 1, f, 0.0f, 0.0f, 0.0f, -0x50);
    }
}

// func_806E0D40 (src/global/E4090.c): Behaviourally equivalent C (text mismatch only): IDO removes the dead FP chain (abs-diff 2048/400 clamp: the 4096-x sub.s and the empty 'x>400' bc1fl branch) that the target keeps; regs shifted (a0/a2) afterwards. Tried: empty/assigning 400 clamp, reuse of var for result, ternary, dead extra use, f32 return type, pad pointer var, permuter 240s (best 1670 vs 1755 base).
typedef struct G22Main {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 pad0C[0x2C];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x152];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ s16 unk1A0;
} G22Main;

#define G22_M ((G22Main *)D_807FD580)


void func_806E0D40(void) {
    f32 var_fv0;
    s16 temp_v1;
    s16 var_v1;
    s32 temp_a0;
    G21Table *pad;

    func_806E007C();
    if (G22_M->unk4 != 0.0f) {
        temp_v1 = D_807FBB40->unkE6;
        temp_a0 = temp_v1 - G22_M->unkA;
        pad = &D_807FD610[D_807FC929];
        if (temp_a0 > 0) {
            var_fv0 = (f32)temp_a0;
        } else {
            var_fv0 = (f32)-temp_a0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        var_fv0 = var_fv0 > 400.0f ? 400.0f : var_fv0;
        D_807FBB40->unkE6 = (s16)(s32)((f32)temp_v1 - (f32)((pad->unk2E * G22_M->unk48) / 400));
        var_v1 = D_807FBB40->unkE6;
        if (var_v1 >= 0x1000) {
            D_807FBB40->unkE6 = var_v1 - 0x1000;
            var_v1 = D_807FBB40->unkE6;
        }
        if (var_v1 < 0) {
            D_807FBB40->unkE6 = var_v1 + 0x1000;
        }
    }
    pad = &D_807FD610[D_807FC929];
    if (!(pad->unk2A & 0x2000)) {
        G22_M->unk1A0 = (u32)((f64)(pad->unk2F * 0xCC) * 0.6 + 63000.0);
    }
}

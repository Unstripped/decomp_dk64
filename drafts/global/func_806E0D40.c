// func_806E0D40 (src/global/E4090.c): Stage 6: only temp_v1/temp_a0 swapped (v1<->a0). Prefix kept via trailing dead 'if (var_fv0 > 1.0f) {}' (last empty compare is dropped, earlier 2048/4096/400 chain survives). Dead tests (4x if(1){}, !D_807FBB40 x3, temp_a0&&temp_a0, pad before temp_v1) fix everything else; needs adjsave temp_v1 > temp_a0.
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

typedef struct G22Sub4b {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G22Sub4b;

typedef struct G22Sub4 {
    /* 0x00 */ G22Sub4b *unk0;
    /* 0x04 */ u8 pad4[0x60];
    /* 0x64 */ u16 unk64;
} G22Sub4;

typedef struct G22Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G22Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0x5C];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x2A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G22Act;

#define G22_M ((G22Main *)D_807FD580)

void func_806E0D40(void) {
    f32 var_fv0;
    s16 temp_v1;
    s16 var_v1;
    s32 temp_a0;
    G21Table *pad;

    func_806E007C();
    if (G22_M->unk4 != 0.0f) {
        pad = &D_807FD610[D_807FC929];
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        temp_v1 = D_807FBB40->unkE6;
        temp_a0 = temp_v1 - G22_M->unkA;
        if (temp_a0 > 0) {
            var_fv0 = (f32)temp_a0;
        } else {
            var_fv0 = (f32)-temp_a0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
            if (temp_a0 && temp_a0) {
            }
        }
        if (var_fv0 > 1.0f) {
        }
        var_fv0 = (f32)((pad->unk2E * G22_M->unk48) / 400);
        D_807FBB40->unkE6 = (s16)(s32)((f32)temp_v1 - var_fv0);
        if (D_807FBB40->unkE6 >= 0x1000) {
            if (!D_807FBB40 && !D_807FBB40 && !D_807FBB40) {
            }
            D_807FBB40->unkE6 -= 0x1000;
        }
        if (D_807FBB40->unkE6 < 0) {
            D_807FBB40->unkE6 += 0x1000;
        }
    }
    pad = &D_807FD610[D_807FC929];
    if (!(pad->unk2A & 0x2000)) {
        G22_M->unk1A0 = (u32)((f64)(pad->unk2F * 0xCC) * 0.6 + 63000.0);
    }
}

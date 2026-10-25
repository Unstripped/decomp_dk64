// func_806E07F8 (src/global/E4090.c): Behaviourally equivalent C, state machine/switch layout plausible, but IDO drops the dead FP prefix the target keeps (clamped abs angle diff * (0.25+0.75*unkB8/unk38) result unused: div.s, mul.d, add.d, mul.d, cvt.s.d all present in target). Everything after shifted by regs. Same retention puzzle as func_806E0D40.
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
#define G22_A ((G22Act *)D_807FBB40)

extern u8 D_8074E77C[];

void func_806E07F8(void) {
    f32 var_fv0;
    s16 temp_a1;
    s32 temp_v0;
    s8 temp_a1_2;
    s8 temp_a0;
    u8 var_v0;
    G21Table *temp_v1;

    func_806E007C();
    temp_a1 = G22_A->unkEE;
    temp_v0 = G22_A->unkE6 - temp_a1;
    if (temp_v0 > 0) {
        var_fv0 = (f32)temp_v0;
    } else {
        var_fv0 = (f32)-temp_v0;
    }
    if (var_fv0 > 2048.0f) {
        var_fv0 = 4096.0f - var_fv0;
    }
    if (var_fv0 > 400.0f) {
        var_fv0 = 400.0f;
    }
    var_fv0 = (f32)((f64)var_fv0 * (0.25 + 0.75 * (G22_A->unkB8 / G22_M->unk38)));
    func_806DF494(&G22_A->unkE6, temp_a1, G22_M->unk48 / 4);
    if (G22_A->unk154 != 0x14) {
        if (G22_A->unk154 == 0xF && (G22_A->unk4->unk0->unk10 == 0x1F2 || G22_A->unk4->unk0->unk10 == 0x1B3)) {
            temp_v1 = &D_807FD610[D_807FC929];
            temp_a1_2 = temp_v1->unk2E;
            if (temp_a1_2 < -0x1E) {
                func_80614E78(D_807FBB40, 0x61);
                G22_A->unk154 = 0x10;
                G22_A->unk155 = 0;
            } else if (temp_a1_2 >= 0x1F) {
                func_80614E78(D_807FBB40, 0x5F);
                G22_A->unk154 = 0x11;
                G22_A->unk155 = 0;
            } else {
                temp_a0 = temp_v1->unk2F;
                if (temp_a0 >= 0x1F) {
                    func_80614E78(D_807FBB40, 0x63);
                    G22_A->unk154 = 0x12;
                    G22_A->unk155 = 0;
                } else if (temp_a0 < -0x1E) {
                    func_80614E78(D_807FBB40, 0x65);
                    G22_A->unk154 = 0x13;
                    G22_A->unk155 = 0;
                }
            }
        }
        temp_v1 = &D_807FD610[D_807FC929];
        temp_a1_2 = temp_v1->unk2E;
        temp_a0 = temp_v1->unk2F;
        if ((temp_a1_2 < 0x1E && G22_A->unk154 == 0x11) || (temp_a0 >= -0x1D && G22_A->unk154 == 0x13) || (temp_a0 < 0x1E && G22_A->unk154 == 0x12) || (temp_a1_2 >= -0x1D && G22_A->unk154 == 0x10)) {
            var_v0 = G22_A->unk154;
            if (D_8074E77C[D_807FC929] == 2 && var_v0 != 0x12) {
                func_80614EBC(D_807FBB40, 0x191);
            } else if (G22_A->unk155 == 1) {
                switch (var_v0) {
                    case 0x11:
                        func_80614E78(D_807FBB40, 0x60);
                        break;
                    case 0x10:
                        func_80614E78(D_807FBB40, 0x62);
                        break;
                    case 0x12:
                        func_80614E78(D_807FBB40, 0x64);
                        break;
                    case 0x13:
                        func_80614E78(D_807FBB40, 0x66);
                        break;
                }
            } else {
                func_80614E78(D_807FBB40, 0x68);
            }
            G22_A->unk154 = 0xF;
            G22_A->unk155 = 0;
        }
    }
}

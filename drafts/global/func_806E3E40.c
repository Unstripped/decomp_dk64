// func_806E3E40 (src/global/E4090.c): Stage 6: frame/spills/slots match (t declared last, ang first, 5 f32 locals); remaining: D_807FD580 lda in a3 (target) vs v1, and tail: target keeps D_807FD6E0 stores as plain lui at (no lda CSE), li v0,4 before the bnez; mine builds lda v1 for D_807FD6E0 and puts li in delay slot.
typedef struct G24Sub {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ u32 unk58;
} G24Sub;

typedef struct G24Main {
    /* 0x000 */ u8 pad0[0x2C];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[2];
    /* 0x03E */ s16 unk3E;
    /* 0x040 */ u8 pad40[0x10];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u32 unk58;
    /* 0x05C */ u8 pad5C[0xA4];
    /* 0x100 */ s32 unk100;
    /* 0x104 */ u8 pad104[0x9C];
    /* 0x1A0 */ u16 unk1A0;
    /* 0x1A2 */ u8 unk1A2;
    /* 0x1A3 */ u8 unk1A3;
    /* 0x1A4 */ u8 pad1A4[8];
    /* 0x1AC */ G24Sub *unk1AC;
} G24Main;

typedef struct G24Act {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[2];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x48];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x18];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G24Act;

#define G24_M ((G24Main *)D_807FD580)
#define G24_A ((G24Act *)D_807FBB40)
#define G24_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))

extern u32 D_80767CC0;
extern f32 D_807535CC[];

extern u8 D_807FD6E0;
extern u8 D_807FD6E1;
f32 func_80611BB4(f32, f32);

void sfxStopSlotSound();
void func_806E3D14(f32);
void func_806E384C(void);
void func_806CD424(s16, f32, f32);
f32 func_80612794(s16);
f32 func_80612790(s16);
void func_806E3E40(void) {
    f32 ang;
    f32 ground;
    f32 a;
    f32 arg;
    s16 t;

    if (func_806F8AD4(5, D_807FC929) && G24_M->unk1A3) {
        if (G24_PAD(D_807FD63C, u16) & 0x2000) {
            D_807FD6E0 = 0;
            D_807FD6E1 = 0;
        }
        ang = G24_A->unkEE - G24_A->unkE6;
        if (ang < 0.0f) {
            ang += 4096.0f;
        }
        t = (s32)ang;
        ground = func_80612794(t) * G24_A->unkB8;
        if (ground > 0.0f) {
            a = ground;
        } else {
            a = -ground;
        }
        if (a > 10.0f) {
            if (ang > 2048.0f) {
                arg = 1024.0f;
            } else {
                arg = 3072.0f;
            }
            arg += G24_A->unkE6;
            if (arg >= 4096.0f) {
                arg -= 4096.0f;
            }
            G24_M->unk2C = 8.0f;
            func_806CD424((s32)arg, 0.0f, G24_M->unk38);
        }
        ang = func_80612790(t) * G24_A->unkB8;
        ground = G24_A->unkC0;
        if (ground > 0.0f) {
            ground = 0.0f;
        }
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (a > 10.0f) {
            if (ground > 0.0f) {
                a = ground;
            } else {
                a = -ground;
            }
            arg = (f64)(func_80611BB4(a, ang) - 1.5707964f) * 16384.0 / 1.5707963705062866 + 63000.0;
        } else {
            arg = 63000.0f;
        }
        func_806E3D14(arg);
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (((a > 10.0f) || (G24_A->unkC0 < 0.0f)) && (D_807FD6E1 == 0)) {
            D_807FD6E0 = 4;
        }
        if (D_807FD6E0 != 0) {
            D_807FD6E0 -= 1;
            if (D_807FD6E0 == 0) {
                D_807FD6E1 = 8;
            }
            func_806E384C();
        } else {
            sfxStopSlotSound(D_807FBB40, 0);
        }
        if (D_807FD6E1 != 0) {
            D_807FD6E1 -= 1;
        }
    }
}

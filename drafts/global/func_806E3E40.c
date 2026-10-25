// func_806E3E40 (src/global/E4090.c): stage 6, unchanged code (47 diff lines by my count, all from one cause): target colors constants 4 and 8 (li v0,4 / li v1,8) and never makes lda candidates for D_807FD6E0/E1, so D_807FD580 lda lands in a3 (ours v1) and the D_807FD6E0 tail uses lui at/lbu v0. Tried this unit without effect: --D_807FD6E0 / assign / (u8) cast / & 0xFF forms, dead x*4 x+4 x&4 tests, duplicate stores of 4 and 8, dead if (D_807FD6E0/E1/580/BB40) {} hill-climb at every statement (no improvement). A u8 local c = D_807FD6E0; c -= 1; D_807FD6E0 = c; if (c == 0) makes the store masked (andi t7; sb t7) like the target but moves other things.
extern u8 D_807FD6E0;
extern u8 D_807FD6E1;

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

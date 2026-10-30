// func_806E3E40 (src/global/E4090.c): stage 6, diff 20 (was 33): a3/v1 lda for D_807FD580 now matches (found by random dead-test search, 17 dead tests incl. 'if (D_807FD6E0 && D_807FD6E0) {}' early, 'if (!ground) {}', float-compare forms). Remaining diff = tail only: target colors hi/value of D_807FD6E1 in v1 and const 4/8 in v0/v1 and has no lda for D_807FD6E0 (lui at/lbu v0 + 'andi t5; sb t5' masked store); ours makes lda D_807FD6E0 in v1 (D6E0 has 3 accesses in a call-free region, D6E1 spans calls so only D6E0 qualifies as caller-saved lda), li t5,4 ugen temp, unmasked store. Tried: --D6E0/assign/local-u8/s32 c forms (all worse 32-39), SA 160k iters stalls at 20.
extern u8 D_807FD6E0;
extern u8 D_807FD6E1;

void func_806E3E40(void) {
    f32 ang;
    f32 ground;
    f32 a;
    f32 arg;
    s16 t;

    if (slotQueueGetValue(5, D_807FC929) && G24_M->unk1A3) {
        if (!ground) {} // FAKE: dead test steers uopt coloring
        if (G24_PAD(D_807FD63C, u16) & 0x2000) {
            D_807FD6E0 = 0;
            if (D_807FBB40 == 0) {} // FAKE: dead test steers uopt coloring
            D_807FD6E1 = 0;
        }
        ang = G24_A->unkEE - G24_A->unkE6;
        if (D_807FD6E0 && D_807FD6E0) {} // FAKE: dead test steers uopt coloring
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
        if (D_807FBB40 != 0) {} // FAKE: dead test steers uopt coloring
        if (a > 10.0f) {
            if (ang > 2048.0f) {
                arg = 1024.0f;
            } else {
                arg = 3072.0f;
            }
            arg += G24_A->unkE6;
            if (arg >= 4096.0f) {
                if (1) {} // FAKE: dead test steers uopt coloring
                arg -= 4096.0f;
            }
            if (arg != 0) {} // FAKE: dead test steers uopt coloring
            G24_M->unk2C = 8.0f;
            func_806CD424((s32)arg, 0.0f, G24_M->unk38);
        }
        ang = func_80612790(t) * G24_A->unkB8;
        ground = G24_A->unkC0;
        if (D_807FD6E1 + 1.0f) {} // FAKE: dead test steers uopt coloring
        if (ground > 0.0f) {
            if (D_807FD6E1) {} // FAKE: dead test steers uopt coloring
            ground = 0.0f;
            if (ang) {} // FAKE: dead test steers uopt coloring
        }
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
            if (1) {} // FAKE: dead test steers uopt coloring
        }
        if (1) {} // FAKE: dead test steers uopt coloring
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
            if (!D_807FD6E1) {} // FAKE: dead test steers uopt coloring
            D_807FD6E0 = 4;
        }
        if (D_807FD6E0 != 0) {
            D_807FD6E0 -= 1;
            if (D_807FD6E0 == 0) {
                if (a) {} // FAKE: dead test steers uopt coloring
                D_807FD6E1 = 8;
            }
            func_806E384C();
        } else {
            sfxStopSlotSound(D_807FBB40, 0);
            if (!D_807FBB40) {} // FAKE: dead test steers uopt coloring
        }
        if (D_807FD6E1 != 0) {
            if (D_807FBB40 && D_807FBB40) {} // FAKE: dead test steers uopt coloring
            D_807FD6E1 -= 1;
        }
        if (D_807FD6E1 == 0) {} // FAKE: dead test steers uopt coloring
    }
}

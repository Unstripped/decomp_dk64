// func_806E3E40 (src/global/E4090.c): MiscC leftovers7: stage 4 park full 6 (was 12; 274 vs 275 lines: li v1,4 fills the nop delay), shape 2. Lever: dead tests with the stored CONSTANTS on another global (if (D_807FD63C == 4U) {} before the D_807FD6E0 = 4 block, == 8U before D_807FD6E1 = 8, if (D_807FBB40 != 0) {}) colour const 4/8 webs; remaining: const 4 coloured v1/E1 load v0 vs target v0/v1 (+ nop). D_807FD6E0/D_807FD6E1 are used ONLY here: function-local statics (static u8 D_807FD6E0, D_807FD6E1; natural C, no FAKEs) are count-exact 275/275 with shape 0 / text 16 (regs only: E1 var uncoloured adjsave 0, E0 coloured v1 instead of v0), needs .bss carve.
extern u8 D_807FD6E0;
extern u8 D_807FD6E1;

void func_806E3E40(void) {
    f32 ang;
    f32 ground;
    f32 a;
    f32 arg;
    s16 t;
    u8 c;

    if (slotQueueGetValue(5, gCurrentPlayerIndex) && G24_M->unk1A3) {
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
        if (D_807FD6E0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (a > 10.0f) {
            if (D_807FD6E1 && D_807FD6E1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
            playerApproachVelocity((s32)arg, 0.0f, G24_M->unk38);
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
        playerStepPitchAngleToward(arg);
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (D_807FD63C == 4U) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (((a > 10.0f) || (G24_A->unkC0 < 0.0f)) && (D_807FD6E1 == 0)) {
            D_807FD6E0 = 4;
            if (D_807FD6E1 + gCurrentPlayerIndex) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        c = D_807FD6E0;
        if (c != 0) {
            c -= 1;
            D_807FD6E0 = c;
            if (c == 0) {
                if (D_807FD63C == 8U) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_807FD6E1 = 8;
                if (D_807FBB40 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            func_806E384C();
        } else {
            sfxStopSlotSound(D_807FBB40, 0);
        }
        if (D_807FD6E1 != 0) {
            D_807FD6E1 -= 1;
        }
        if (D_807FD6E1 && D_807FD6E1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    if (!D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
}

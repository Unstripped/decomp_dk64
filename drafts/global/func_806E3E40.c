// func_806E3E40 (src/global/E4090.c): W2IntD: stage 6, 12 diff lines (unchanged). Target has uopt-coloured webs in v0/v1 for D_807FD6E1 value (lbu v1), const 4 (li v0), D_807FD6E0 value (lbu v0), const 8 (li v1); ours has cvt(ilod D_807FD6E1) cand 49/91 in v1/v0 and consts as ring t5/t7. Re-swept deadsweep with field-expression symbols (G24_A->unkC0/B8/E6/EE, G24_M->unk1A3/2C/38, D_807FBB40->unk60, 14 syms x4 forms, 3.7k): nothing.
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
        if (((a > 10.0f) || (G24_A->unkC0 < 0.0f)) && (D_807FD6E1 == 0)) {
            D_807FD6E0 = 4;
            if (D_807FD6E1 + gCurrentPlayerIndex) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        c = D_807FD6E0;
        if (c != 0) {
            c -= 1;
            D_807FD6E0 = c;
            if (c == 0) {
                D_807FD6E1 = 8;
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

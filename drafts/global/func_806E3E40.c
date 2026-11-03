// func_806E3E40 (src/global/E4090.c): Carve7 leftovers7: STAGE 4 (count exact 275/275, frame exact, only 3 register-naming lines differ): function-local statics D_807FD6E0/D_807FD6E1 (needs the E4090 .bss carve, worktree commit 684ee11) + direct E0 spelling (no c local: if (E0 != 0) { E0 -= 1; if (E0 == 0) E1 = 8; ...}) + 2 dead tests (gCurrentPlayerIndex && gCurrentPlayerIndex at the top of the E0 block, E1 && E1 inside the E1 block). Closer park: deadsweep text 6 -> 3 (276->275 lines). Remaining: E0 reload cvt coloured v1, target v0 (lbu v1/beqz v1/addiu v0,v1,-1 vs lbu v0/beqz v0/addiu v0,v0,-1). Tried: c-local forms (c = E0 with a dead c test at function end gives text 1 but costs an extra sb spill of c), compare spellings, declaration order, 40k dead-test slot samples, hill-climb, permuter: all plateau at 3. Target colouring is E0/E1 vars uncoloured (memory), const 4 = v0, const 8 = v1, cvt E0 = v0, cvt E1 = v1; ours has E0 and E1 vars coloured.
void func_806E3E40(void) {
    static u8 D_807FD6E0; // function-local static (only user): uopt treats it as non-aliased; needs the E4090 .bss carve
    static u8 D_807FD6E1;
    f32 ang;
    f32 ground;
    f32 a;
    f32 arg;
    s16 t;

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
        }
        if (D_807FD6E0 != 0) {
            if (gCurrentPlayerIndex && gCurrentPlayerIndex) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            D_807FD6E0 -= 1;
            if (D_807FD6E0 == 0) {
                D_807FD6E1 = 8;
            }
            func_806E384C();
        } else {
            sfxStopSlotSound(D_807FBB40, 0);
        }
        if (D_807FD6E1 != 0) {
            if (D_807FD6E1 && D_807FD6E1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            D_807FD6E1 -= 1;
        }
    }
}

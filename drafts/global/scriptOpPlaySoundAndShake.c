// scriptOpPlaySoundAndShake (src/global/19A00.c): stage 4: full=7 text=7 reloc=0 shape=6; R11_scriptOpPlaySoundAndShake (base 9d6acd9d): verified stage 4 park remains closest at full=7 text=7 reloc=0 shape=6 (n=223 insns). Proved via as1probe scan/try that any .livereg mask from records 180 to 193 (preceding switch jump) or moving the .rdata jump table after .end yields exact match full=0 text=0 reloc=0 shape=0 (n=223). Stock as1 computes switch jr live-ins as the union of its case targets, treating a1, a2, t2, t6 as dead across the switch and hoisting lh t2, 78(sp), li a1, 10, li a2, 1 into the unk2C0 load-use stall. Confirmed no C-level producer of live switch jr exists under IDO 5.3 (Q0544, guide ido-backend-record-pipeline); exact park restored in .scratch/R11_scriptOpPlaySoundAndShake/19A00.c; whole-file fdiff OK.
// As1Group (base d495328bf722a26c83c592a497693f5a487e9132): zero-indexed &gPlayerSlots access in the mode condition folds without a new alias boundary; full=7/text=7/shape=6 n=223 unchanged. The corpus emits livereg at calls/returns, not arbitrary joins. Stage-4 park retained; catalogue: .scratch/as1group/catalogue.md.
// Orchestrator 2026-11-06 (base 0475d51c): the FAKE-free form of this body (drop the four `if (...) {}` FAKEs and `volatile` on sp4D; stock as1 full=16 n=221) is EXACT (full=0, n=223) once as1 treats the `switch (arg0->unk58)` jump as reading a1,a2,t2,t6: `as1probe try --insert <j>:live=0x06220000` before the `j $8`, an all-live mask, an as1 patched so a non-$ra jr without .livereg is all-live, or the jump table moved after `.end`. The stock jr gets precise case live-ins, so the then-arm's `lh t2,78(sp)`/`li a1,10`/`li a2,8` hoist into the unk2C0 test stall. Same cause as func_806F03C4; the patch changes 129 matched functions game-wide, and no C/ugen producer of a live switch jump is known. Q0544; guide ido-backend-record-pipeline 'Switch jr liveness'.
s32 scriptOpPlaySoundAndShake(Actor *arg0) {
    s16 sp4E;
    volatile u8 sp4D; // FAKE: memory-resident local steers as1 scheduling
    s16 sp4A;
    u8 sp49;
    u8 var_v1;
    u8 pad;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp4E);
    scriptReadU8((u8 *)&sp4D);
    scriptReadU16((u8 *)&sp4A);
    scriptReadU8(&sp49);
    if (sp49 == 1) {} // FAKE
    if (sp4A && sp4A) {} // FAKE
    if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 2) {
        var_v1 = 0xA;
        if (sp4E == 1) {
            sp4D = (u32)((f64)(u32)sp4D * 0.5);
            if (sp49 == 2) {} // FAKE: dead test steers as1 hoisting
        }
        camStartShakeFromPoint(((GlobalSoundState *)gActivePlayerState)->unk104, 0xA, 8, ((ActorSoundPosView *)arg0)->unk7C, ((ActorSoundPosView *)arg0)->unk80, ((ActorSoundPosView *)arg0)->unk84, 100.0f, 800.0f);
    } else if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 0) {
        var_v1 = 0xFF;
        sp4D = (u32)((f64)(u32)sp4D * 0.5);
    } else {
        switch (arg0->unk58) {
        case 6:
        case 7:
            var_v1 = 0x46;
            break;
        case 8:
            var_v1 = 0x5A;
            break;
        case 2:
        case 4:
            var_v1 = 0x32;
            break;
        default:
            var_v1 = 0x50;
            break;
        }
    }
    sp4E = mapActionLookupEntry(sp4E, arg0, ((ActorSoundPosView *)arg0)->unk78);
    if (sp4A) {} // FAKE
    if ((sp4E == 2) || (sp4E == 8)) {
        sp49 = 0xA;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp4E, (s32)sp4D, (s32)sp4A, (s32)sp49, (s32)var_v1, 0.3f, 0);
    return 1;
}

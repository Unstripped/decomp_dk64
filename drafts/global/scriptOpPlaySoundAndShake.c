// scriptOpPlaySoundAndShake (src/global/19A00.c): stage 4 park. full=7 text=7 reloc=0 shape=6 (n=223). Exact registers/frame/rodata. Diff is as1 hoisting lh t2,78(sp) and li a1,10 out of then-block into bne v1,at stall. as1probe live=0x06220000 ($a1,$a2,$t2,$t6) at label $33 (.L80616FA4) yields exact full=0 across all 223 insns by marking registers live across branch. Tried natural C (0 FAKEs, full=9), dead tests, switch on unk2C0.
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

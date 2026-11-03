// scriptOpPlaySoundAndShake (src/global/19A00.c): W3CountB 2026-11-02: PARKED stage 4, count-exact 223/223, full 7 (was 16 at 221). Levers: volatile u8 sp4D (every read reloads; removes as1's bnezl copy / hoist at the else-if label), plus 3 dead tests on sp49/sp4A. Remaining diff: target keeps 'bne v1,at; nop; lh t2,78(sp)' un-hoisted (no entry-stall hoist at all); ours hoists li a1/li a2 (+ li a2,1 const web from the sp49==1 FAKE) above the first bne. MiscC leftovers7: volatile sp4D ALONE (no FAKEs) is full 9 text 9 (205/206 insns): diff = lh t2 hoisted above sll, li a1,10/li a2,8 hoisted into the lbu-v1 stall, li at,1 later; tried and no better: switch(unk2C0) (97, tests 0 first), local sel (u8/s32/u32: 90), empty if (P[i].unk2C0 == K) {} before the compare (JetBoss, K = every stored const, 15 forms), volatile s16 sp4E / volatile-cast compare reads, volatile on every local combo (480 combos), exact prototypes from unit_check (sfxPlayAtPositionPooled s16 + u8/s16 widths, raw args, no effect; camStartShakeFromPoint 4th param f32 in its definition: +72 lines if declared f32 with an s32 field), all 1-3 statement LINE-JOINS (13k combos), as1 record insertion at the bne/B head (57..59, 100 records: nothing below 7).
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

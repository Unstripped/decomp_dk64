// scriptOpPlaySoundAndShake (src/global/19A00.c): stage 4 park unchanged: whole-object full=7 text=7 reloc=0 shape=6 n=223 (206 insns), frame0x50 s0/ra. Matcher12 Base e0a4052eadcc3cc847239207d52d4e5a70353e70. K&R narrow-parameter hypothesis disproved: original target lh t2,78(sp) uses decimal 78 = 0x4E, inside the 0x50-byte local frame, not 0x78; scriptReadU16 is explicitly called with sp+0x4E. D_80746BEC slot 0x3D dispatches through actorScriptExecute, whose original expected object sets only a0=s4 before jalr (0xFC,0x110 in object); signature is s32 (Actor *). Same one-Actor-pointer K&R definition is identical. Ran unit_check.py protos --seg global src/global/19A00.c: existing mismatches include sfxPlayAtPositionPooled narrow params/return and camStartShakeFromPoint fourth param w/f32, already exhausted in previous pass; no target signature discrepancy. 37 new local-type representations/K&R checks: one-element arrays, struct/union wrappers, byte/unsigned storage views, exact-layout sound/volume and priority/mode/pitch groups, and grouped volatile/plain variants; none beat7. Struct/array wrappers shift stack homes; compensating exact-layout sound/volume grouping restores identical7 but not desired as1 liveness. No new FAKEs, retained original park; no merge. Prior history: stage 4 park unchanged: whole-object full=7 text=7 reloc=0 shape=6 n=223 (206 insns), frame 0x50, s0/ra. Base 2acc852d8bdc3314546a691e95943c529047f7db. This pass exhausted new common-use/liveness routes without improving the C: moving the shake call to a guarded post-join block (var_v1/state/flag predicates, typed flags, parameter variables) changes block layout and scores at least full127; duplicating two/three common lookup/sound tails scores at least full88. Cached shared sound-id locals, no-code common-tail assignments, constant 1/10 carriers used on both paths, shared temporary roles across the two half-volume branches, typed zero-dependent array indices, equivalent branch predecessors and inner switch/loop forms, selective volatile reads, canonical callee parameter/return types, byte signedness, and reviewed legal permuter subsets all fail to beat 7. as1 keep plus scan --rounds2 yields only instruction-deleting/non-equivalent improvements; proper subsets of the reported live mask at label33 are insufficient (best full5 but n224). Permuter -j2 --seconds600 completed 70878 iterations and emitted 8 candidates, best score300 vs340; its best candidates change the inner sound-id test to 10 or overwrite the final volume, so rejected. The legal float-dead-test/copy/shadow ideas also do not improve exact scoring. No private source changes or header changes. Plain fdiff: FAILED: Section .text content mismatch (built: 18640 bytes, expected: 18640 bytes); FAILED: Relocations mismatch. Parked fdiff OK; --non-matching compiles. Evidence .scratch/Matcher-scriptOpPlaySoundAndShake/full-object-score.json. Prior note: stage 4 park. full=7 text=7 reloc=0 shape=6 (n=223). Exact registers/frame/rodata. Diff is as1 hoisting lh t2,78(sp) and li a1,10 out of then-block into bne v1,at stall. as1probe live=0x06220000 ($a1,$a2,$t2,$t6) at label $33 (.L80616FA4) yields exact full=0 across all 223 insns by marking registers live across branch. Tried natural C (0 FAKEs, full=9), dead tests, switch on unk2C0.
// As1Group (base d495328bf722a26c83c592a497693f5a487e9132): zero-indexed &gPlayerSlots access in the mode condition folds without a new alias boundary; full=7/text=7/shape=6 n=223 unchanged. The corpus emits livereg at calls/returns, not arbitrary joins. Stage-4 park retained; catalogue: .scratch/as1group/catalogue.md.
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

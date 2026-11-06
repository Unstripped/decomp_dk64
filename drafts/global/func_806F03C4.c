// func_806F03C4 (src/global/EFDC0.c): stage 6: natural zero-FAKE five-entry switch remains full=4 text=2 reloc=2 shape=4; 152 instructions, frame 0x20. Matcher12: 37 named-address/current-slot variants and 24 dynamic-address arithmetic/shared-base variants did not improve. Computing u8*/const u8*/s8*/s32*/void*/struct/union/array address of gCurrentPlayerIndex before dispatch or at the join all folds to original direct lbu; optimized ucode contains no index pointer rlda/unal and ugen emits no pre-jal alias. Capturing the actual slot pointer before dispatch hoists its loads/calculation and reduces body, unlike target; per-arm index-pointer assignments inhibit target PRE and move loads to join. Signed/unsigned selector-offset cancellation, zero-index address variants, and shared gPlayerSlots/index base all worsen. Target directly loads gCurrentPlayerIndex with lbu (u8), not lw; shared declaration was not changed. Plain fdiff CURRENT (65), default lui t9 hoist remains. No new FAKE retained. Prior: stage 6 park; natural five-entry switch full=4 text=2 reloc=2 shape=4; fdiff CURRENT (65): only default lui t9 hoisted into entry stall, with consequent jump-table address changes. Removed historical case-7 FAKE and duplicate per-arm camera assignments from park (old artificial six-entry-table variant scored full=1 text=1 reloc=0 shape=1; not a match). Matcher2: 76 second-switch/shared-goto/function-pointer variants, 149 computed-index-lifetime/duplicate-dispatch variants, 51 volatile/address-view variants, 410 integer-typed/address-equality dead-test placements, and 63,667 bounded permuter iterations found no improvement; as1probe scan --rounds 2 still yields exact backend-only alias/live edits. No new C t9-liveness route found. Prior attempts: stage 6 park. full=1 text=1 reloc=0 shape=1 (case 7 widens the table; not a match); natural switch full=4 text=2 reloc=2 shape=4. Natural C has the target frame, registers, spill and five-entry table; as1 hoists default's lui t9 into the stall after lw t6,0x58(a0). Backend probes only: alias before default or a dead move reading t9 on the dispatch/case/join path before the first jal give full=0; as1 deletes the move but its liveness suppresses the hoist. No C realization found. Address-taken ev/local-pointer/union forms did not emit the needed alias and changed allocation or the lw+sll+sra reload to lh. A case-4 ghost index dead-test gives shape=0 but changes default to t7 (already live in dispatch), not a solution with target t9. Selector/case-order/loop/layout/escape/wide-identity grids, 700 dead-test placements and 53,363 permuter iterations found no improvement to natural C. No flags or assembly changes accepted.
// As1Group (base d495328bf722a26c83c592a497693f5a487e9132): removing the six-entry-table FAKE and giving case 6 a zero-indexed &gPlayerSlots access still yields natural full=4/text=2/reloc=2/shape=4, n=200; no pre-jal alias boundary. Original source park retained, natural best draft unchanged. Catalogue: .scratch/as1group/catalogue.md.
// Orchestrator (base 9974ec4e): wrapping the switch in do {} while (0) (ok-fine levers-revisit-7 MiscB) gives shape=0 but full=100/text=79: dispatch leaves bb0, so case 2's ev piece becomes the uncoloured one, the ring shifts by one and default's index lands in t7 (live in dispatch). That blocks the hoist only through registers; its ugen stream has no record before the default label, so with target registers the hoist is expected to return (inferred, not tested). Moving the .rdata jump table to the end of t.G still hoists (full=4): as1's jr liveness did not depend on table placement in this test. A dead `if (gPlayerCharacterId[gCurrentPlayerIndex]) {}` in case 6 or default emits no alias region (single symbol+index access); it only CSEs the index (full=39/29). uoptemit.c base_sp_noalias: a noalias-with-$sp region needs a coloured register holding an lda of an Smt variable (pointtoheap is Pascal-only); func_00422AF0 also resets register-pair and $gp aliases, which this attempt did not explore. No tested C route provides the boundary; that is not a proof that none exists.
void func_806F03C4(void) {
    s32 ev;

    switch (D_807FBB48->unk58) {
    case 2:
        ev = 7;
        break;
    case 3:
        ev = 0;
        break;
    case 4:
        EfEPS->unk1F0 |= 0x100;
        ev = 4;
        break;
    case 5:
        if (EfECam[gCurrentPlayerIndex].unk2C0 == 1) {
            ev = 8;
        } else {
            ev = 0x1F;
        }
        break;
    case 6:
        ev = 9;
        break;
    default:
        break;
    }
    D_807FBB48->unkE6 = mathAngleBetweenPoints2D(EfECam[gCurrentPlayerIndex].unk210, EfECam[gCurrentPlayerIndex].unk218,
                                                  D_807FBB48->unk7C, D_807FBB48->unk84);
    if (D_807FBB68 & 2) {
        EfEPS->unk1F0 &= ~0x100;
        actorScriptStart(D_807FBB48, 0x165);
    } else {
        if (D_807FBB48->unk154 != 0x56) {
            camStartPath(D_807FBB48, (s16)ev, 5);
        }
        func_80614E78(D_807FBB48, 0x5A);
    }
    D_807FBB48->unk154 = 0x67;
    D_807FBB48->unk155[0] = 0;
}

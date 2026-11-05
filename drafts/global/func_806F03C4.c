// func_806F03C4 (src/global/EFDC0.c): stage 6 park; natural five-entry switch full=4 text=2 reloc=2 shape=4; fdiff CURRENT (65): only default lui t9 hoisted into entry stall, with consequent jump-table address changes. Removed historical case-7 FAKE and duplicate per-arm camera assignments from park (old artificial six-entry-table variant scored full=1 text=1 reloc=0 shape=1; not a match). Matcher2: 76 second-switch/shared-goto/function-pointer variants, 149 computed-index-lifetime/duplicate-dispatch variants, 51 volatile/address-view variants, 410 integer-typed/address-equality dead-test placements, and 63,667 bounded permuter iterations found no improvement; as1probe scan --rounds 2 still yields exact backend-only alias/live edits. No new C t9-liveness route found. Prior attempts: stage 6 park. full=1 text=1 reloc=0 shape=1 (case 7 widens the table; not a match); natural switch full=4 text=2 reloc=2 shape=4. Natural C has the target frame, registers, spill and five-entry table; as1 hoists default's lui t9 into the stall after lw t6,0x58(a0). Backend probes only: alias before default or a dead move reading t9 on the dispatch/case/join path before the first jal give full=0; as1 deletes the move but its liveness suppresses the hoist. No C realization found. Address-taken ev/local-pointer/union forms did not emit the needed alias and changed allocation or the lw+sll+sra reload to lh. A case-4 ghost index dead-test gives shape=0 but changes default to t7 (already live in dispatch), not a solution with target t9. Selector/case-order/loop/layout/escape/wide-identity grids, 700 dead-test placements and 53,363 permuter iterations found no improvement to natural C. No flags or assembly changes accepted.
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

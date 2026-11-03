// func_806F03C4 (src/global/EFDC0.c): MiscB 2026-11-03: unchanged stage-6 park (full=1: sltiu 6 vs 5 from the case-7 hole; without it full=4 = default-arm 'lui t9' hoisted into the entry stall). NEW: wrapping the switch in do{}while(0) / if(1){} / for(;;){break;} / while(1){break;} removes the hoist AND the hole (200 insns, table 5, shape 0, full 100) but ev then loses its coloured web (ugen 'li $24,7; sw $24,28(sp)' instead of the hole version's 'li $7,7 ... sw $7,28(sp)' at arm end) so every arm's t-ring is shifted one step; a dead statement placed between 'switch (..) {' and 'case 2:' (e.g. if (D_807FBB48->unk58) {}) restores ev's web (registers exact) but also restores the hoist (full 4). 2900 singles + 3160 pairs of dead statements over wrapper bases, and a 40k-eval anneal: nothing below 4 without the hole. Unreachable statements after break in case 6 (11 forms) are deleted by uopt.
void func_806F03C4(void) {
    s32 ev;
    EfECamBlock *camera;

    switch (D_807FBB48->unk58) {
    case 2:
        ev = 7;
        camera = &EfECam[gCurrentPlayerIndex];
        break;
    case 3:
        ev = 0;
        camera = &EfECam[gCurrentPlayerIndex];
        break;
    case 4:
        EfEPS->unk1F0 |= 0x100;
        ev = 4;
        camera = &EfECam[gCurrentPlayerIndex];
        break;
    case 5:
        camera = &EfECam[gCurrentPlayerIndex];
        if (camera->unk2C0 == 1) {
            ev = 8;
        } else {
            ev = 0x1F;
        }
        break;
    case 6:
        ev = 9;
        camera = &EfECam[gCurrentPlayerIndex];
        break;
    case 7:  // FAKE: second as1-visible ref to the default label (jump-table hole) keeps its lui out of the entry stall; widens the table to 6 entries (sltiu 6 vs 5)
    default:
        camera = &EfECam[gCurrentPlayerIndex];
        break;
    }
    D_807FBB48->unkE6 = mathAngleBetweenPoints2D(camera->unk210, camera->unk218,
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

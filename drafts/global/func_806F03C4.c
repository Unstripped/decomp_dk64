// func_806F03C4 (src/global/EFDC0.c): Player rev8: re-derived: natural switch (no `case 7:` hole, table 5) is text-diff 2 = ONLY a hoisted `lui t9,hi(gCurrentPlayerIndex)` (default arm's first insn) in the entry load stall; `case 7:` hole (6-entry table, sltiu 6) is the only spelling found that stops it. Tried new: `switch (x - 2)` cases 0..4 (same), post-switch camera with/without `default: break;` (same as natural / much worse), unreachable gotos + labels adjacent to default, null/dead statements after every case label and break, 991 single/pair LINE-JOINs over the switch, as1probe record edits (extra label/.loc/dup branch: no effect; removing the break into default flips it but wrecks code). PREVIOUS: W2Tiny 2026-11-03: stage-6 park unchanged (full=1 hole version; table 6 entries = rodata mismatch, so not a true match path). NEW analysis: wrapper/dead-block variants with table 5 + no hoist (full 90-100, count 200 exact) lose ev's a3 web in the FIRST arm: -l5 shows ev splits into piece A (uncoloured, blocks around the mathAngle call + ONE arm) and piece B (a3). Plain/hole/dead-between-switch-and-case2 (dispatch in bb0) exclude the case-6 arm (target-like: target case 6 is 'li t3,9; sw t3,28(sp)', case 3 'sw zero'); any variant with a block before the dispatch (do-while(0), if(1), dead if before switch) excludes the case-2 arm instead. So hoist suppression and arm exclusion are coupled to dispatch-in-entry-block; 4 wrappers x 32 camera/ev arm orders x 17.7k single dead tests: best wrapper score 6 (dead stmt between 'switch {' and 'case 2:' restores web, restores hoist). Tried extras on ev (ev=ev, |=0, if(ev)) per arm: no change.
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

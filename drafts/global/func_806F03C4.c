// func_806F03C4 (src/global/EFDC0.c): W3Sched 2026-11-02: unchanged stage-6 park (full=1: case-7 hole widens the table, sltiu 6 vs 5; without it full=4 = default-arm 'lui t9' hoisted into the entry stall). NEW: (1) PRE form (no 'camera' var in arms, case 5 reads EfECam[..].unk2C0, one 'camera = &EfECam[..]' after the switch + 'default: break;') compiles to the SAME 200 insns as the explicit-arm form (uopt PRE inserts the camera computation into every arm and the default edge), so it is not the structure. (2) ugen text of the real code (scan of all 208 src files at -S): the only non-.loc records between an unconditional 'b' and a label are '.alias/.noalias reg,$sp|reg' resets (170 sites) and the inline jump-table; they are emitted when a la-derived/addu-derived base register had a '.noalias' state in the arm (e.g. '.noalias $3,$sp; sb ..($3); b L; .alias $3,$sp'). Loaded pointers (lw reg,SYM) never get one. as1probe: ANY extra instruction record after case 6's 'b' (dup addu, dup lw) gives full=0, moving the addu after the b does not (4). So the original case-6 arm (or the dispatch block) used a la-derived base register that left a noalias state; no C found: dead tests of gCurrentPlayerIndex/gPlayerSlots (1-4 in case 6 -> pointerized, +2 insns), volatile reads (+5 insns), raw '*(&G)'/'((u8*)&G)[0]' spellings (full 4/18), 40 PRE-shape x default-form variants: none emit a directive before the default label with 200 insns. Untried: none cheap left.
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

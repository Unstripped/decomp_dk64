// func_806F03C4 (src/global/EFDC0.c): stage 6 park; C reachability OPEN (2026-11-03 deep-dive). Natural switch (this body minus the `case 7:` hole) = text 2: as1 hoists the default arm's `lui t9` into the entry load stall. `as1probe scan` on the natural body finds two single-record routes to full=0, both as1-level: (1) a fall-through predecessor for $41: any record between case 6's `b $42` and `$41:` (`insert 108:alias|noop|bnext`; also exact one stage up: a `unal $v1 $sp 0` injected after case 6's `ujp 11` in uopt's t.O -> real ugen 5.3 -> as1); (2) t9 live on the dispatch path (`.livereg` with $25 live anywhere in the entry block, e.g. `try --insert 28:live=0x0000004E`). Route 1 from C needs uopt's `.alias` reset (ugen labelopt deletes every other record after a jump; an injected `ujp 12` is removed), and uopt emits unal only for a register holding a variable address whose region ends in case 6 (n64decomp/ido uoptemit.c base_in_reg + func_00422AF0; C alias mode 2): this switch holds none. Route 2 is untried from C: ugen emits `.livereg` only at calls/returns, so t9 would have to be read before written on some path from the dispatch. Not excluded: several coordinated stream changes (the do-while(0) wrapper loses the hoist through ring temps but breaks the ev web). Flags (-g1/-g2/-g3, -Wo,-noPalias, -Olimit) and a preceding function's open noalias region change nothing. The `case 7:` park below is behaviourally equivalent but its table has 6 entries (sltiu 6; rodata +4).
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

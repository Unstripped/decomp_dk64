// func_806F03C4 (src/global/EFDC0.c): BLOCKED, no C path (2026-11-03 deep-dive). Natural switch (this body minus the `case 7:` hole) = text 2: as1 hoists the default arm's `lui t9` into the entry load stall because label $41 has ONE predecessor. Exact match proven at both back-end boundaries: one as1-visible record between case 6's `b $42` and `$41:` (`as1probe scan` on the natural body: only `insert 108:alias|noop|bnext` -> full=0, 917 edits tried) and, one stage up, a `unal $v1 $sp 0` injected after case 6's `ujp 11` in uopt's t.O -> real ugen 5.3 -> as1 = full 0. From C that record can only be uopt's `.alias` reset: ugen labelopt deletes every other record after a jump (verified: an injected `ujp 12` is removed), and uopt emits unal only for a register holding a variable address (`la`/`addu sp`) whose noalias region ends in case 6 (n64decomp/ido uoptemit.c base_in_reg + func_00422AF0; C alias mode 2 makes pointer bases never noalias). The target's switch holds no such register, so no spelling reaches it; flags (-g1/-g2/-g3, -Wo,-noPalias, -Olimit) and a preceding function's open noalias region do not either. The `case 7:` park below is behaviourally equivalent but its table has 6 entries (sltiu 6; rodata +4).
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

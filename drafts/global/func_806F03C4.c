// func_806F03C4 (src/global/EFDC0.c): stage 6 park. full=1 text=1 reloc=0 shape=1 (via case 7:; natural switch full=4 text=2 reloc=2 shape=4). Frame, registers, stack spill, and 5-entry jump table exact in natural C. Remaining diff in natural C is as1 entry load-delay hoist of default arm lui t9 into stall after lw t6,0x58(a0). as1probe insert 108:alias/bnext before default label yields exact full=0. Tried default at start/middle/end, goto def, if before switch, do-while.
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

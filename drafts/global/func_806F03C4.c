// func_806F03C4 (src/global/EFDC0.c): Stage 5 (frame 0x20, jump table, all arms/regs match; 2 text lines + 2 reloc lines: as1 hoists the default arm's 'lui t9,%hi(D_807FC929)' into the dispatch block (between 'lw t6,0x58(a0)' and 'addiu t7,t6,-2'; as1 speculates independent head instructions of the beqz target into the lw-use stall) while the target keeps it as the first instruction of the default arm. Not needed: the old deadsweep 'if (D_807FD580 && D_807FD580) {}' in case 2 (removed, same score). Tried: 48 arm-statement-order x case-5 spellings, default spellings (idx*0x2F0 first, pointer arithmetic, ev=ev, no break, goto), switch cast s32/u8, cached Actor local, decl order, deadsweep with ev/camera/D_807FBB44/D_8074E77C extras (1517 variants), 10 min permuter -j 2: none move the lui. idx-first default arm (D_807FC929*0x2F0 + base) hoists lui t6 into the beqz delay slot instead.
void func_806F03C4(void) {
    s32 ev;
    EfECamBlock *camera;

    switch (D_807FBB48->unk58) {
    case 2:
        ev = 7;
        camera = &EfECam[D_807FC929];
        break;
    case 3:
        ev = 0;
        camera = &EfECam[D_807FC929];
        break;
    case 4:
        EfEPS->unk1F0 |= 0x100;
        ev = 4;
        camera = &EfECam[D_807FC929];
        break;
    case 5:
        camera = &EfECam[D_807FC929];
        if (camera->unk2C0 == 1) {
            ev = 8;
        } else {
            ev = 0x1F;
        }
        break;
    case 6:
        ev = 9;
        camera = &EfECam[D_807FC929];
        break;
    default:
        camera = &EfECam[D_807FC929];
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

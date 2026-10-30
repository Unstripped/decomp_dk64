// func_806F03C4 (src/global/EFDC0.c): Stage 5 (frame 0x20, jump table, 2 diff lines): per-arm camera=&EfECam[idx] + s32 ev (colours to a3, spilled around the call) + redundant else in case 5 + one dead 'if (D_807FD580 && D_807FD580) {}' in case 2 reproduce everything except one hoist: ours emits 'lui t9,%hi(D_807FC929)' for the default arm right after 'lw t6,0x58(a0)' in the dispatch block, target keeps it as the first instruction of the default arm. Pair deadsweep, arm statement order, line joins, default-arm spellings and a 4 min permuter run did not move it.
void func_806F03C4(void) {
    s32 ev;
    EfECamBlock *camera;

    switch (D_807FBB48->unk58) {
    case 2:
        if (D_807FD580 && D_807FD580) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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

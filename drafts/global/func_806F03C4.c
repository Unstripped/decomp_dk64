// func_806F03C4 (src/global/EFDC0.c): Stage 5 (frame 0x20, jump table, all arms/regs match; diff = 2 text lines + 2 reloc lines: as1 hoists the default arm's 'lui t9,%hi(D_807FC929)' into the lw->addiu stall of the dispatch block (entry block). NmEfd2 findings: (1) the hoist happens only when the dispatch is in the ENTRY block and the default block has a single predecessor: 'case 7: default:' (default gets a 2nd pred via a 6th jump-table entry) removes it (text diff 1, only sltiu 6 vs 5 left); any dead 'if (1) {}' / 'do {} while (0)' / 'if (G) {}' before the switch also removes it but shifts uopt's ev live-range split (a3 piece covers arm 6 instead of arms 2-5, ring temps +1: 79 text lines); a 2nd dead statement right after 'switch (...) {' restores the target arms AND the hoist. (2) volatile selector, local sel, line joins/format, arm spelling combos (729), default placement/no-break, 64 arm-order x decl x case5 forms with entry boundary, deadsweep (+ev/camera extras) from the boundary body, permuter 12 min -j 2 (never below base 60): none gives hoist-less arms-identical code. Still needed: a construct giving default arm a 2nd as1 predecessor without changing the 5-entry table, or a dead entry boundary that keeps the ev split.)
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

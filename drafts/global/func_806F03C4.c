// func_806F03C4 (src/global/EFDC0.c): (src/global/EFDC0.c): Stage 5 (frame 0x20, jump table, all arms/regs match; diff = 2 text lines + 2 reloc lines: as1 hoists the default arm's 'lui t9,%hi(D_807FC929)' into the lw->addiu stall of the ENTRY (dispatch) block because the default label has a single reference). CtrlEfd findings: (1) 'case N: default:' for any N in 7..16 gives a 2nd label ref and removes the hoist AND the reloc diff (text diff 1 = 'sltiu at,t7,N-1' vs 5; table gets N-1 entries); N>=40 or N<=0 turns the switch into a compare chain/other. (2) any pre-switch dead boundary ('if (1) {}', 'do {} while (0)', 'goto L; L:;', 'if (G) {}') removes the hoist but shifts uopt's ev live-range split (79 text lines); a 2nd dead stmt after 'switch {' restores arms+hoist (NmEfd2). (3) Searched with a random hill-climb (26k evals): boundary forms x case5 spellings x per-arm statement order x ev type/decl order x new dead locals x dead stmts on all globals: nothing below text 2. (4) No effect on the hoist: whole function on one line / 1350 random line joins / switch on '(x-2)' with cases 0..4 (s32/u32) / volatile index or base in the default arm / goto after break / default first or no-break / camera spelled as EfECam+idx etc. (.loc granularity only moves 'sll' scheduling). Still needed: a construct giving the default arm a 2nd as1 label reference without changing the 5-entry table, or an entry boundary that keeps the ev split.
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

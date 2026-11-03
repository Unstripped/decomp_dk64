// func_806F03C4 (src/global/EFDC0.c): W2SchedA: stage 6, full=1 (park keeps 'case 7:' hole; sltiu 6 vs 5). New facts: (a) the whole-file compile reproduces the entry-stall hoist of the DEFAULT arm's 'lui t9' without case 7 (reduced TU is faithful). (b) as1probe: inserting ANY non-.loc directive record (type 0x4 '.text', 0x1b, 0x2b, 0x30 '.noalias', 0x31 '.alias') in t.G between the last arm's 'b $42' and the '$41:' default label gives full 0 (so the original has a stray ugen directive there, e.g. an alias/noalias or inline .rdata/.text record); inserting '.loc' records, extra labels after the label, label before the label, '.livereg' do nothing. (c) do{}while(0)/if(1)/any empty block BEFORE the switch also kills the hoist but only because the first arm's 'ev' piece then loses its a3 colour (ring shifts, default arm lui becomes t7 = live in the jr path): shape 0, full 100; 1204-variant dead-test sweep on ev/camera/globals cannot recover ev's colour without bringing the hoist back. (d) .loc/line-join pairs (1035), no-op statements (;, 0;, ev=ev, labels, goto L;L:) at every position, annealing 15k evals: none beat 4 without case 7. Open: a C construct that makes ugen emit .alias/.noalias (or .text/.rdata) between the case-6 arm and the default label with a 5-entry table. || PREVIOUS: W3SchedB: stage 5->6, 1 text line: only 'sltiu at,t7,6' vs expected 5 (jump table 6 entries). KEY: adding 'case 7:' before 'default:' gives the default label a second as1-visible ref (table hole), so as1 no longer hoists 'lui t9,%hi(gCurrentPlayerIndex)' into the entry stall (was 2 text + 2 reloc). Any extra branch/retarget to the default label in ugen records (a1probe insertion) gives full 0; table-hole spelling widens the table (case 8..16 same 1 line; case 1 gives 2). goto/dead-statement forms to the default label do not survive uopt. Need a way to add a ref without widening the bounds check.
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

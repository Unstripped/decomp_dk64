// actorPatrolFollowerUpdate (src/global/B1F60.c): stage 5, 25 insns diff (was 31): needs file prototype 'void patrolPathStep(u8, u8);' (was s32,s32: u8 first param removes the cvt candidate that stole a3/a1). Remaining: hidden switch temp (cvt cand 23) coloured a1 not v0 (interferes with D_807FBB40 value cand 14 = v0, created by the F1 dead tests), and 0x37 arm tails: mine lui v1/lw v0 pointerised vs target ring t1; t-ring +1 at nested-switch case 0 (ori t0 vs t9)
void actorPatrolFollowerUpdate(arg0, arg1, arg2)
s16 arg0;
u8 arg1;
u16 arg2;
{
    Actor *actor;

    if (arg0 != 0 && (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0)) {
        actor = D_807FBB40;
        if (actor->unk154 != 0x37) {
            ((B1F60Actor *)actor)->unkC0 = 200.0f;
            func_8072D714(D_807FBB70.unk1FC, arg0, actor);
        }
    }
    actor = D_807FBB40;
    switch (D_807FBB40->unk154) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, (actor->unk6A & 1) ? arg2 : (arg2 | 2), 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, arg2, 0.0f);
            break;
        case 0x37:
            switch (((B1F60Actor *)actor)->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    if (D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    break;
                case 1:
                    sfxSpawnTableNodes(actor);
                    if (arg1 != 0) {
                        B1F60A->unk155 = 2;
                        break;
                    }
                    B1F60A->unkC0 = 100.0f;
                    actor = D_807FBB40;
                    ((B1F60Actor *)actor)->unk155++;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    if (D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    actor->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(((B1F60View98 *)D_807FDC98)->unk28);
            break;
    }
    if (D_807FBB40->unk154) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    switch (D_807FBB40->unk154) {
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x4C90, ((B1F60View98 *)D_807FDC98)->unk28, ((B1F60View98 *)D_807FDC98)->unk2A);
        case 0x37:
        case 0x40:
            break;
    }
}

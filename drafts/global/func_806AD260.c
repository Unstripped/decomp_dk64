// func_806AD260 (src/global/B1F60.c): func_806AD260 (src/global/B1F60.c): stage 5, 31 insns diff, frame 0x20 matches. Per-arm structure matches target except arm tails load unk154 into a3 instead of a0 + move v0, a0 because P-load candidate 689|0 is colored v0.
void func_806AD260(arg0, arg1, arg2)
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

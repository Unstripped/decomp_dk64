// func_806B49B0 (src/global/B7490.c): func_806B49B0 (src/global/B7490.c): stage 5, exact length match (13056 bytes, frame 0x40); full=56 text=56 shape=18 (improved from full=114 text=123 / 8 insns short). Steered arg0 into t0 caller-saved reg spilled/reloaded across calls with dead temp_v0/D_807FDC9C tests.
extern f32 D_807502EC;
void func_80724CA4(s32, s32);

void func_806B49B0(u8 arg0, s16 arg1, s16 arg2) {
    s16 *temp_v0;
    s32 *dead1;
    s32 *dead2;
    s16 sp32;

    temp_v0 = B7490A->unk178;
    if (temp_v0 && temp_v0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    dead1 = (s32 *) temp_v0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(1, 1);
        D_807FDC90->unk30 = D_807FBB40->unk4->unk38;
        D_807FBB40->unkB8 = (f32) (u32) D_807FDC9C->unkC;
        *temp_v0 = D_807FDC9C->unkA;
        B7490A->unkC4 = D_807502EC;
    }
    if (D_807FDC9C && D_807FDC9C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    sp32 = D_807FDC9C->unk6 + *temp_v0;
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (arg0 != 0x37)) {
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155[0] = 0;
    }
    switch (arg0) {
        case 2:
        case 3:
            if (D_807FBB40->unk155[0] == 0) {
                actorScriptStart(D_807FBB40, arg1);
                D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            }
            actorMoveWithinZone(arg0, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0xE1, 0.0f);
            if (temp_v0 && temp_v0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (D_807FBB40->unk80 < (f32) sp32) {
                if (D_807FBB40->unk155[0] == 2) {
                    D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.03125));
                } else {
                    D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.015625));
                }
            }
            B7490A->unkE8 = mathAngleEaseToward(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                case 1:
                case 2:
                    actorScriptStart(D_807FBB40, arg2);
                    if (temp_v0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_807FBB40->unk155[0] = 3;
                case 3:
                    actorFlyTowardPosition((void *) D_807FDC90, 0x26);
                    break;
            }
            break;
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            if (temp_v0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (D_807FBB40->unk6A & 1) {
                D_807FBB40->unk154 = 0x40;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(arg1);
            break;
    }
    if (temp_v0 && temp_v0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    switch (arg0) {
        case 2:
        case 3:
            patrolPathStep(arg0, 1);
            break;
        case 0x26:
            if (patrolPathStep(arg0, 1) != 0) {
                if (D_807FDC9C && D_807FDC9C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_807FBB40->unk154 = D_807FDC9C->unk10;
                D_807FBB40->unk155[0] = 0;
            }
            break;
    }
}

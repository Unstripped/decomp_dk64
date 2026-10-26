// func_806B42A8 (src/global/B7490.c): stage 6: only 3 diffs. needs file-level proto s32 func_8072D13C(u8, s32) (K&R decl gives move a0,a2 not andi a0,a2,0xff) + t6/t8 swap at lh *var_t2 vs lh unk6 (scratch temp order); trailing 'if (!D_807FBB40->unk154) {}' dummy read stops &D_807FBB40 being hoisted into t0 (any read of D_807FBB40 field after func_806319C4 works); st=E before first test + st=E at end of if-body + switch(st), E reused as call arg gives lbu a2/move v1,a2 pairs; actorFlyTowardPosition now s32 (no return) so no function-pointer cast
s32 func_8061CB50(void *);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void sfxSpawnTableNodes(Actor *);
/* actorFlyTowardPosition must be defined as s32 actorFlyTowardPosition(B7490Pos *, u8) (no return statement): v0&1 is read here; needs B7490Pos struct from B7490.c */
/* needs file-level "s32 func_8072D13C(u8, s32);" (currently K&R "s32 func_8072D13C();") for the final andi a0,a2,0xff */

void func_806B42A8(void (*arg0)(), u16 arg1, u16 arg2, s16 arg3) {
    s16 *var_t2;
    s16 var_t0;
    s16 var_t1;
    s32 st;

    var_t2 = B7490A->unk178;
    if ((arg3 != 0) && (D_807FBB40->unk154 != 0x37) && (B7490A->unk6E == -1)) {
        sfxPlayActorSound(D_807FBB40, arg3, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        *var_t2 = D_807FDC9C->unkA;
        if (D_807FDC9C->unkB == 0) {
            D_807FDC9C->unkB = 0x28;
        }
    }
    st = D_807FBB40->unk154;
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (st != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, arg1);
        B7490A->unkC0 = 300.0f;
        *var_t2 = 0;
        D_807FDC90->unk2C = 0x2BC;
        st = D_807FBB40->unk154;
    }
    var_t0 = D_807FDC90->unkA;
    var_t1 = D_807FDC90->unkE;
    switch (st) {
        case 1:
        case 0x10:
        case 0x23:
            var_t0 = (s16) (s32) D_807FDC94->unk7C;
            var_t1 = (s16) (s32) D_807FDC94->unk84;
        case 2:
        case 3:
        case 7:
        case 0x35:
            if (D_807FBB40->unk80 < (f32) (D_807FDC9C->unk6 + *var_t2)) {
                D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (u32) D_807FDC9C->unkB * 0.03125));
            } else {
                if ((func_8061CB50(D_807FDC90) == 0) && (arg0 != NULL)) {
                    arg0();
                }
            }
            actorMoveWithinZone(D_807FBB40->unk154, (f32) var_t0, (f32) var_t1, 0x2C1, 0.0f);
            B7490A->unkE8 = func_806CC190(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    D_807FDC90->unkA = (s16) (s32) D_807FDC94->unk7C;
                    D_807FDC90->unkC = (s16) (s32) D_807FDC94->unk80;
                    D_807FDC90->unkE = (s16) (s32) D_807FDC94->unk84;
                    D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
                    D_807FDC90->unk2C = 0x64;
                case 1:
                    if ((actorFlyTowardPosition((B7490Pos *) D_807FDC90, 0x23) & 1) || (D_807FBB40->unk80 < (f32) (D_807FDC90->unkC + 0xF))) {
                        D_807FBB40->unk154 = D_807FDC9C->unk10;
                        D_807FBB40->unk155[0] = 0;
                    }
                    break;
            }
            break;
        case 0x37:
            D_807FBB40->unkE6 = D_807FBB40->unkE6 + D_807FDC90->unk2C;
            D_807FDC90->unk2C = ((D_807FDC90->unk2C - 0x11) < 0) ? 0 : (D_807FDC90->unk2C - 0x11);
            if (D_807FDC90->unk2C == 0) {
                sfxStopSlotSound(D_807FBB40, 0);
            }
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    if (D_807FBB40->unk58 == 0x11D) {
                        D_807FBB40->unk155[0] = 3;
                        break;
                    }
                    B7490A->unkC0 = 50.0f;
                    D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x222, 0.0f);
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(arg2);
            break;
    }
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            func_8072D13C(D_807FBB40->unk154, 1);
            break;
    }
    func_806319C4(D_807FBB40, 0);
    if (!D_807FBB40->unk154) {
    }
}

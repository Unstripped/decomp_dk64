// func_806B42A8 (src/global/B7490.c): R2B7490 stage 4: structure + jump tables right. Needs func_806B3F90 to return s32 (target uses v0 & 1; parked C casts the void def to s32(*)()), B7490Actor.unk6E (split pad0 at 0x6E). Variant with s32 st only before the final switch: 13024 vs 13056 bytes (missing the 8 'or v1,a2,zero' copies of target's T=a2/st=v1 pattern; end call is andi a0,a2,0xff). Adding st before the first D_807FBB70 test gives target size but IDO hoists &D_807FBB40 into t0 (209 rows). 2790-style T/st fix (use st in first call arg) not found here.
s32 func_8061CB50(void *);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void sfxSpawnTableNodes(Actor *);

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
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, arg1);
        B7490A->unkC0 = 300.0f;
        *var_t2 = 0;
        D_807FDC90->unk2C = 0x2BC;
    }
    var_t0 = D_807FDC90->unkA;
    var_t1 = D_807FDC90->unkE;
    switch (D_807FBB40->unk154) {
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
            func_8072AB74(D_807FBB40->unk154, (f32) var_t0, (f32) var_t1, 0x2C1, 0.0f);
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
                    /* func_806B3F90 is defined above as void; the target uses its v0 result. */
                    if ((((s32 (*)()) func_806B3F90)(D_807FDC90, 0x23) & 1) || (D_807FBB40->unk80 < (f32) (D_807FDC90->unkC + 0xF))) {
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
                    func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    if (D_807FBB40->unk58 == 0x11D) {
                        D_807FBB40->unk155[0] = 3;
                    } else {
                        B7490A->unkC0 = 50.0f;
                        D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
                case 2:
                        func_8072AB74(0x37, 0.0f, 0.0f, 0x222, 0.0f);
                    }
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
            func_8072D13C(st, 1);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

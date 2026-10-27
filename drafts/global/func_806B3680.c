// func_806B3680 (src/global/B7490.c): R4B7490 stage 6, 7 rows (was 9): remaining = first switch (target lbu v1; move v0,v1 -- mine lbu v0; move v1,v0) and func_8071ABDC spill slot sp44 vs sp40 (3 rows). Fixed final if with ONE var reused: st = (s32)D_807FBB40->unk154; if (D_807FBB40->unk154 == 2 || st == 3) call(unk154,1) (the (s32)/+0/|0 cast gives copy in v0; plain or (u8)/(u32) gives v1/t5). Spill slot: removing dz (ternary assigned to var: var=(dx<dy)?dx:dy) moves spill to 0x44 but result reg f14 not f12; inline ternary / dz var both keep 0x40 (ternary temp costs a slot). register kw, decl order, extra dead locals, st as s16/s32 (frame grows to 0x68) no help. 2x600s permuter no help.
void func_806B3680(void) {
    f32 dx;
    f32 var;
    f32 sp54;
    f32 dy;
    f32 dz;
    u8 st;
    s16 i;

    var = D_807FBB40->unk4->unk38 * 800.0f;
    sp54 = 1.1f;
    if (D_8076A0A8 == 0xC7) {
        if (!(D_807FBB4C->unk6A & 4)) {
            var = 0.0f;
            sp54 = 0.4f;
        } else {
            var = var * 0.75;
            sp54 = 0.7f;
        }
    }
    var = var * var;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 4;
        func_8067ACB4(D_807FBB40);
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x27)) {
        D_807FBB40->unk154 = 0x27;
        D_807FBB40->unk155[0] = 0;
    } else if (D_807FBB40->unk154 != 0x27) {
        dx = D_807FDC94->unk7C - D_807FBB40->unk7C;
        dy = D_807FDC94->unk80 - D_807FBB40->unk80;
        dz = D_807FDC94->unk84 - D_807FBB40->unk84;
        if (dx * dx + dy * dy + dz * dz < var) {
            D_807FBB40->unk154 = 0x27;
            D_807FBB40->unk155[0] = 0;
        }
    }
    effectSpawnSparks(0x1F, 0);
    st = D_807FBB40->unk154;
    switch (st) {
        case 4:
            actorMoveWithinZone(0, 0.0f, 0.0f, 2, 0.0f);
            if (D_807FBB40->unk80 < D_807FBB40->unkAC) {
                D_807FBB40->unk80 = D_807FBB40->unkAC;
                B7490A->unkC0 = B7490A->unkC4;
            }
        case 0:
            func_8072E1A4(0xA, D_807FDC94);
            break;
        case 0x27:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C2, 0xFF, 0x7F, 0);
                    D_807FDC90->unk30 = 2.0 * D_807FBB40->unk4->unk38;
                    D_807FBB40->unk155[0]++;
                case 1:
                    if (D_807FDC90->unk30 > (dx = D_807FBB40->unk4->unk38)) {
                        actorSetUniformScale(D_807FBB40, dx * 1.01);
                    } else {
                        for (i = 0; i < 0xC; i++) {
                            func_807149B8(1);
                            func_807149FC(2);
                            func_80714950(i + 0x0B020000);
                            func_8071498C(func_8071ABDC);
                            func_80714998(1);
                            func_80714CC0(D_8072073C, 2.0 * D_807FBB40->unk4->unk38, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                        }
                        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3D, 0xFF, 0x7F, 0);
                        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x35C, 0xFF, 0x7F, 0, 0x32, 0.3f, 0);
                        func_8067E278(0, 1);
                        actorGetOrSetNodeScale(D_807FBB40, 1, D_807FBB40->unk140->unkC * sp54);
                        func_8066EB40(D_807FBB40, D_807FBB40->unk140->unkC * sp54);
                        D_807FBB40->unk60 &= ~4;
                        D_807FBB40->unk155[0]++;
                    }
                    break;
                case 5:
                    D_807FBB40->unk154 = 0x40;
                    break;
                default:
                    D_807FBB40->unk155[0]++;
            }
            break;
        case 2:
        case 3:
            dx = D_807FDC90->unkC;
            dy = D_807FBB40->unkAC - D_807FBB40->unk15E;
            dz = (dx < dy) ? dx : dy;
            func_8072A920((s16)st, 0, D_807FDC90->unkA, dz, D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        default:
            func_8072B7CC(0x32E);
            break;
    }
    st = (s32)D_807FBB40->unk154;
    if (D_807FBB40->unk154 == 2 || st == 3) {
        func_8072D13C(D_807FBB40->unk154, 1);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

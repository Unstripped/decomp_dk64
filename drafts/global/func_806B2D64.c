// func_806B2D64 (src/global/B7490.c): L1 stage 6: NON_MATCHING parked; only diff = case 0x37 shared a1/a2 const hoist (+16 bytes); see header comment
// Only diff: case 0x37 inner switch: target hoists `move a1,zero`/`lui a2,0x40e0` (shared consts of func_806CC190/func_8072DC7C calls) into the dispatch and
// func_8072DC7C's block has no a1/a2 setup; mine re-emits them in that block (+16 bytes). Needs: `void func_8072DE44();` (unprototyped, called with 1 arg).
// Key recipes: `s32 st` (not u8) gives target's `lbu a0; move v1,a0`; per-case reload is made by uopt PRE from ONE `st = D_807FBB40->unk154;` before the final switch;
// final func_8072D13C(D_807FBB40->unk154, 1) uses the expression not st; `M5A->unkE4 += 800.0f * f()` (compound) fixes fp reg order; ternaries inline in the call args.
// Uses D_807FBB40 (Actor*), D_807FBB70, D_807FBD70, D_807FDC90/94/98 (header), B7490A = ((B7490Actor *)D_807FBB40).
typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} L1Sub24;

typedef struct {
    /* 0x00 */ L1Sub24 *unk0;
} L1Sub4;

void projectileGetTargetCoords(void *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);
void func_8072DEA8(s32, s32, s32, void *);
void func_8072881C(s32, void *);

void func_806B2D64(void) {
    s32 st;
    f32 min;
    f32 fa;
    f32 fb;

    func_80729B00();
    effectSpawnSparks(0x1F, 2);
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        D_807FDC98->unk46 |= 8;
        func_8072D714(D_807FBB70.unk1FC, 0x2E7);
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x2E5, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
        D_807FBB40->unkB8 = 0.0f;
    }
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x31:
            effectSpawnSparks(0x1F, 2);
            if ((D_807FBB40->unk155[0] != 0) || (((L1Sub4 *)D_807FBB40->unk4)->unk0->unk24 == 0.0f)) {
                func_8072DE44(0x2E2);
            }
            break;
        case 0x27:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_80614EBC(D_807FBB40, 0x2E6);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    break;
                case 4:
                    func_8072DE44(0x2E2);
                    break;
            }
            break;
        case 0x25:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_80614EBC(D_807FBB40, 0x2E4);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(D_807FBB40, 1);
                    projectileSpawnNodeEntry(0x112, 0, 0.3f, D_807FBB40->unkE6, 300.0f, func_80612794(B7490A->unkE8) * 300.0f, D_807FBB40);
                    effectSpawnSparks(1, 1);
                    break;
                case 3:
                    func_8072DE44(0x2E2);
                    break;
            }
            break;
        case 1:
            func_806B2D5C();
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((func_80611A44() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, D_807FDC90->unkC, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            func_806B2D5C();
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, ((D_807FBB40->unkAC - D_807FBB40->unk15E) < D_807FDC94->unk80) ? (D_807FBB40->unkAC - D_807FBB40->unk15E) : D_807FDC94->unk80, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
            D_807FBB40->unk132 = 2;
        case 7:
        case 0x35:
            func_806B2D5C();
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC90->unkA, (D_807FDC90->unkC < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? D_807FDC90->unkC : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    B7490A->unkE4 = func_806CC190(B7490A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14, 0, 7.0f);
                    break;
                case 2:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x2E2);
            break;
    }
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            func_8072D13C(D_807FBB40->unk154, 1);
            break;
        default:
            func_8072C918(0x6400, 0x2E2, 0x2E2);
            break;
    }
    func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
    func_806319C4(D_807FBB40, 0);
}

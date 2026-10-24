// func_806AE588 (src/global/B2CE0.c): MATCHED (TEXT OK) in private copy: sel pinned via func_8072B7CC(0x1FB, sel); sw = sel copy for the switch, 0x35 test on sw, switch(sel)
typedef struct L5View {
    /* 0x000 */ u8 pad0[0x134];
    /* 0x134 */ s16 unk134;
} L5View;

extern s32 D_8076A0A8;
void actorClearNodeFlag(M3Actor *, s32);
void func_8072881C(s32, void *);
void func_8063DA40(s32, s32);

void func_806AE588(void) {
    s32 sel;
    s32 sw;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_8072B79C(0x1FD, 0x1FB, 0x1FC);
        func_80724CA4(3, 1);
        actorClearNodeFlag(D_807FBB40, 3);
        if (D_8076A0A8 == 0xA5) {
            D_807FBB40->unk132 = 1;
        }
    }
    func_8072881C(0, D_807FDC90->unk28);
    sel = D_807FBB40->unk154;
    if ((sel != 0x32) || (D_807FBB70.unk15 != 0)) {
        if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (sel != 0x37)) {
            if (((L5View *)D_807FBB40)->unk134 < -1) {
                func_8072D714(D_807FBB70.unk1FC, 0x202);
                D_807FBB40->unkC0 = 250.0f;
            } else {
                func_8072D714(D_807FBB70.unk1FC, 0x201);
                D_807FBB40->unkC0 = 200.0f;
            }
            ((M3View90 *)D_807FDC90)->unk35 = 2;
            D_807FBB40->unk138 &= 0xFFFF7FFF;
        } else if (D_807FBB70.unk200 == 4) {
            func_8072DEA8(0x1FF, 0x31, D_807FBB70.unk1FC);
        } else if (D_807FBB70.unk200 == 5) {
            func_8072DEA8(0x200, 0x32, D_807FBB70.unk1FC);
            D_807FBB40->unkC0 = 220.0f;
        }
    }
    sel = D_807FBB40->unk154;
    sw = sel;
    switch (sel) {
    case 0x31:
        if ((D_807FBB40->unk155 != 0) || ((*(M3Node **)D_807FBB40->unk4)->unk24 == 0.0f)) {
            func_8072DE44(0x1FB);
        }
        func_8072AB74(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, D_807FBB40->unkEE, 7.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            func_8072AB74(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            D_807FBB40->unkC0 = 200.0f;
            D_807FBB40->unkB8 = 120.0f;
            D_807FBB40->unk155++;
        case 2:
            func_8072AB74(0, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 3:
            func_8072DE44(0x1FB);
            break;
        }
        break;
    case 0x11:
        func_80724E48(5);
        switch (D_807FBB40->unk155) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x1FD);
            D_807FBB40->unk155++;
        case 1:
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            if (D_807FBB40->unkB8 < 1.0f) {
                D_807FBB40->unk155++;
            }
            break;
        case 2:
            func_8072A450();
            if ((func_80611A44() >> 0xF) % 1000 >= 0x3E4) {
                func_8072DE44(0x1FB);
            }
            break;
        }
        break;
    case 0x27:
        func_8072AB74(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x1FE);
            D_807FBB40->unk155 = 1;
            break;
        case 2:
            D_807FBB40->unk132 = 2;
            break;
        case 3:
            D_807FBB40->unk132 = 1;
            break;
        case 4:
            func_8072DE44(0x1FB);
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            D_807FBB40->unk154 = 0x11;
            D_807FBB40->unk155 = 0;
        }
    case 0x23:
        if ((D_807FBB70.unk200 == 2) && (func_8072DE10(0x2710) != 0)) {
            D_807FBB40->unk154 = 0x27;
            D_807FBB40->unk155 = 0;
        }
        sel = D_807FBB40->unk154;
    case 0x10:
        func_80724E48((sel == 1) ? 2 : 0);
        func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((sw == 0x35) ? 2 : 3);
        func_8072AB74(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0, 0.0f);
        break;
    case 0x37:
        D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, D_807FBB40->unkEE, 7.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if ((D_8076A0A8 == 0xA5) && (D_807FBB40->unk15F != 0)) {
                func_8063DA40(0, 0xA);
            }
            sfxSpawnTableNodes(D_807FBB40);
            D_807FBB40->unk155++;
        case 2:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            func_8072DC7C(8);
            break;
        case 3:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x1FB, sel);
        break;
    }
    sel = D_807FBB40->unk154;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        func_8072D13C(D_807FBB40->unk154, 1);
    default:
        func_8072C918(0x6400, 0x1FB, 0x1FC);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

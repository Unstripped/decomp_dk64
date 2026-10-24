// func_806AFB58 (src/global/B2CE0.c): stage 4: size+frame match (0x28), first switch regs ok; remaining v1/t0 swap of &D_807FBB70/&D_807FDC90 hoists, second-switch temp a2/a0 vs a0/a1, actor local copy moves; 84 diff lines
typedef struct L2Node {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} L2Node;

typedef struct L2Actor {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ L2Node **unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[0x54];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x2A];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[4];
    /* 0xEC */ s16 unkEC;
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[4];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ u8 pad13C[0xA];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} L2Actor;

typedef struct L2State90 {
    /* 0x00 */ u8 pad0[0x1E];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20[6];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xD];
    /* 0x35 */ u8 unk35;
} L2State90;

extern L2Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern ActorGlobalState D_807FBB70;

s32 func_80611A44(void);
void func_80614EBC(void *, s32);
void func_806319C4(void *, s32);
void func_806AE2B0(s32, s32, s32, s32);
void func_806AFA60(s32);
s16 func_806CC190(s16, s16, f32);
void func_80724CA4(s32, s32);
void func_80724E48(s32);
void func_80729B00(void);
void func_8072A450();
void func_8072AB74(s32, f32, f32, s32, f32);
void func_8072B324(void *, s32);
void func_8072B79C(s32, s32, s32);
void func_8072B7CC(s32);
void func_8072C918(s32, s32, s32);
void func_8072D13C(s32, s32);
void func_8072D714(s32, s32);
void func_8072DC7C(s32);
s32 func_8072DE10(u16);
void func_8072DE44(s32);
void func_8072DEA8(s32, s32, s32);
void func_8072E1A4(s32, void *);
s32 func_8072E54C();
void sfxSpawnTableNodes(void *);

void func_806AFB58(void) {
    u8 sel;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk146 = -1;
        func_8072B79C(0x2D9, 0x2D7, 0x2D8);
        func_80724CA4(2, 1);
        D_807FBB40->unkEC = 0x1770;
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, 0x2DD);
        ((L2State90 *)D_807FDC90)->unk35 = 2;
        D_807FBB40->unk138 &= 0xFFFF7FFF;
    } else if ((D_807FBB70.unk200 == 4) || (D_807FBB70.unk200 == 5)) {
        if (D_807FBB40->unk146 & 1) {
            ((L2State90 *)D_807FDC90)->unk1E = 0xF;
            ((L2State90 *)D_807FDC90)->unk1F = 0xF;
            D_807FBB40->unkEC = -1;
            func_806AE2B0(0xC2, 0x800, 1, 0x190);
            D_807FBB44->unk15F = 1;
            func_806AFA60(1);
        } else if (D_807FBB40->unk146 & 2) {
            func_806AFA60(2);
        }
        D_807FBB40->unk146 = D_807FBB40->unk146 * 2;
        func_8072DEA8(0x2DC, 0x31, D_807FBB70.unk1FC);
        ((L2State90 *)D_807FDC90)->unk26 = 0;
        D_807FBB40->unkB8 = 0.0f;
    }
    sel = D_807FBB40->unk154;
    switch (sel) {
    case 0x31:
        if ((D_807FBB40->unk155 != 0) || ((*D_807FBB40->unk4)->unk24 == 0.0f)) {
            func_8072DE44(0x2D7);
        }
        func_8072AB74(0, 0.0f, 0.0f, 0x4200, 0.0f);
        break;
    case 0x11:
        func_80724E48(5);
        switch (D_807FBB40->unk155) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x2D9);
            D_807FBB40->unk155++;
        case 1:
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            if (D_807FBB40->unkB8 < 1.0f) {
                D_807FBB40->unk155++;
            }
            break;
        case 2:
            func_8072A450(D_807FBB40);
            if ((func_80611A44() >> 0xF) % 1000 >= 0x3E4) {
                func_8072DE44(0x2D7);
            }
            break;
        }
        break;
    case 0x27:
        if ((u16)D_807FBB40->unkEC < 0xFFFF) {
            func_8072E1A4(0xA, D_807FDC94);
        }
        func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            if (((f64)((Actor *)D_807FBB40)->unk4->unk38 > 0.18) && ((func_80611A44() >> 0xF) % 1000 >= 0x1F5)) {
                func_80614EBC(D_807FBB40, 0x2DB);
            } else {
                func_80614EBC(D_807FBB40, 0x2DA);
            }
            D_807FBB40->unk155 = 1;
            break;
        case 2:
            D_807FBB40->unk132 = 2;
            break;
        case 3:
            D_807FBB40->unk132 = 1;
            break;
        case 4:
            func_8072DE44(0x2D7);
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            D_807FBB40->unk154 = 0x11;
            D_807FBB40->unk155 = 0;
        }
    case 0x23:
        if ((D_807FBB70.unk200 == 2) && (func_8072DE10(D_807FBB40->unkEC) != 0)) {
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
        func_80724E48((sel == 0x35) ? 2 : 3);
        func_8072AB74(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0, 0.0f);
        break;
    case 0x37:
        D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, D_807FBB40->unkEE, 7.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x202, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(D_807FBB40);
            D_807FBB40->unk155++;
        case 2:
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
        func_8072B7CC(0x2D7);
        break;
    }
    switch (D_807FBB40->unk154) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        func_8072D13C(D_807FBB40->unk154, 1);
    default:
        func_8072C918(0x6400, 0x2D7, 0x2D8);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

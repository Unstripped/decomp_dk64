// func_806B0848 (src/global/B2CE0.c): stage 5: text identical except order of 4 hoisted 'li 1' (fcsr consts) at top (want t2,t0,t7,t5); u32 func_8072AB74 decl needed (shared decl is void); reloc: D_8075B1B0/B8/jtbl show as .rodata
typedef struct L4Actor {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[6];
    /* 0x138 */ s32 unk138;
} L4Actor;

typedef struct L4Sub24 {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} L4Sub24;

typedef struct L4Sub4Ptr {
    /* 0x0 */ L4Sub24 *unk0;
} L4Sub4Ptr;

typedef struct L4Sub64 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} L4Sub64;

typedef struct L4DC90 {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s32 unk4;
} L4DC90;

s32 func_806B0770();
s16 func_806CC190(s16, s16, s32);
void func_8072D714(s32, s32);
void func_8072DEA8(s32, s32, s32);
void sfxSpawnTableNodes(M3Actor *);
void func_8072DC7C(s32);
void func_8072E1A4(s32, Actor *);
s32 func_8072E22C(s32);
s32 func_8072DE10(s32);
void func_8072C918(s32, s32, s32);
extern s32 D_8076A064;
extern s32 D_807FBB4C;

void func_806B0848(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        f64 d;
        f64 m = 255.0;

        d = (f64)D_807FBB40->unk4->unk38 / 0.15 * 100.0;
        if (d > m) {
            ((L4Actor *)D_807FBB40)->unk130 = m;
        } else {
            ((L4Actor *)D_807FBB40)->unk130 = d;
        }
        d = (f64)D_807FBB40->unk4->unk38 / 0.15 * 100.0;
        if (d > m) {
            ((L4Actor *)D_807FBB40)->unk131 = m;
        } else {
            ((L4Actor *)D_807FBB40)->unk131 = d;
        }
        func_8072B79C(0x35E, 0x35F, 0x360);
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        func_8072D714(D_807FBB70.unk1FC, 0x367);
        ((L4Actor *)D_807FBB40)->unk138 &= 0xFFFF7FFF;
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x365, 0x31, D_807FBB70.unk1FC);
    } else if (D_807FBB70.unk200 == 5) {
        func_8072DEA8(0x366, 0x31, D_807FBB70.unk1FC);
    }
    if (D_807FBB40->unk154 == 4) {
        D_807FBB40->unk154 = 1;
    }
    switch (D_807FBB40->unk154) {
        case 0x37:
            D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, D_807FBB40->unkEE, 0x40E00000);
            switch (D_807FBB40->unk155) {
                case 0:
                    func_8072AB74(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    D_807FBB40->unk155 = D_807FBB40->unk155 + 1;
                case 2:
                    func_8072DC7C(8);
                    break;
                case 3:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        case 0x31:
            if (D_807FBB40->unk155 != 0 || ((L4Sub4Ptr *)D_807FBB40->unk4)->unk0->unk24 == 0.0f) {
                func_8072DE44(0x35F);
            }
            func_8072AB74(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x27:
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            switch (D_807FBB40->unk155) {
                case 0:
                    func_8072B324(D_807FBB40, 0);
                    func_80614EBC(D_807FBB40, (D_8076A064 & 1) ? 0x362 : 0x361);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    D_807FBB40->unk132 = ((L4Sub64 *)D_807FBB40->unk4)->unk64 == 0x362 ? 4 : 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = ((L4Sub64 *)D_807FBB40->unk4)->unk64 == 0x362 ? 8 : 1;
                    break;
                case 4:
                    D_807FBB40->unk132 = 1;
                    func_8072DE44(0x35F);
                    break;
            }
            break;
        case 0x28:
            func_8072E1A4(0xA, D_807FDC94);
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            switch (D_807FBB40->unk155) {
                case 0:
                    func_8072B324(D_807FBB40, 0);
                    func_80614EBC(D_807FBB40, 0x363);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    D_807FBB40->unk155++;
                    break;
                case 4:
                    ((L4DC90 *)D_807FDC90)->unk4 = D_807FBB4C;
                    func_8072DE44(0x35F);
                    break;
            }
            break;
        case 0x11:
            if (func_806B0770() == 0) {
                switch (D_807FBB40->unk155) {
                    case 0:
                        func_8072B324(D_807FBB40, 0);
                        func_80614EBC(D_807FBB40, 0x35E);
                        D_807FBB40->unk155 = D_807FBB40->unk155 + 1;
                    case 1:
                        func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
                        if (D_807FBB40->unkB8 < 1.0f) {
                            D_807FBB40->unk155 = D_807FBB40->unk155 + 1;
                        }
                        break;
                    case 2:
                        func_8072A450();
                        if ((func_80611A44() >> 15) % 1000 >= 0x3E4) {
                            func_8072DE44(0x35F);
                        }
                        break;
                }
            }
            break;
        case 1:
            if (func_8072E54C() != 0) {
                D_807FBB40->unk154 = 0x11;
                D_807FBB40->unk155 = 0;
            }
        case 0x23:
            if (func_8072E22C(0x50) != 0 && func_8072DE10(0x1770) != 0) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155 = 0;
            }
        case 0x10:
            func_806B0770();
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_8072AB74(D_807FBB40->unk154, D_807FDC90->unkA, D_807FDC90->unkE, 0, 0.0f);
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
            func_8072C918(0x6400, 0x35F, 0x360);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

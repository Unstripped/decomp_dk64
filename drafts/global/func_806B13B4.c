// func_806B13B4 (src/global/B5EC0.c): L6 stage 5: size matches (3472), 14 diff hunks, near-match. Remaining: lda D_807FBB40 piece gets v0 in the 0x20B/0x20C branch (expected lui/lw per access, li a1,0x20B hoisted instead of 0x20C), case 0x35 compare uses a0 instead of a1, jtbl/lo reloc only. Keys: local s32 sel assigned after every store/call path and before 2nd switch; K&R func_8072DE44(0x203, sel) pins sel to a1; if/else for v=0/2 ternary-in-arg for 0x35.
typedef struct L6Sub4 {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} L6Sub4;

typedef struct L6Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ L6Sub4 **unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x54];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[2];
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u8 pad13C[0x18];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} L6Actor;

typedef struct L6Sub90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0x19];
    /* 0x35 */ u8 unk35;
} L6Sub90;

typedef struct L6Sub9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} L6Sub9C;

typedef struct L6Sub94 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
} L6Sub94;

extern ActorGlobalState D_807FBB70;
extern s32 D_8076A0A8;

void func_80729B00(void);
void func_8072B79C(s32, s32, s32);
void func_80724CA4(s32, s32);
void func_8072D714(s32, s32);
void func_8072DEA8(s32, s32, s32);
void func_8072DE44();
void func_80614EBC(void *, s32);
s32 func_8061CB50(void);
void func_806B11C0(u8);
s16 func_806CC190(s16, s16, f32);
void func_80724E48(u8);
void func_8072AB74(s32, f32, f32, s32, f32);
void func_8072B324(Actor *, s32);
void func_8072A450(void);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void sfxSpawnTableNodes(Actor *);
void actorClearNodeFlag(Actor *, s32);
void func_8072DC7C(s32);
s32 func_8072E54C();
void func_8072D13C(s32, s32);
void func_8072C918(s32, s32, s32);
void func_806319C4(Actor *, s32);
void func_8072B7CC();

void func_806B13B4(u8 arg0) {
    s32 v;
    s32 sel;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (D_8076A0A8 == 0x43) {
            ((L6Sub9C *)D_807FDC9C)->unkD = 0x82;
            D_807FDC98->unk46 |= 0x40;
        }
        func_8072B79C(0x205, 0x203, 0x204);
        func_80724CA4(2, 1);
    }
    sel = D_807FBB40->unk154;
    if (sel == 0x27) {
        ((L6Actor *)D_807FBB40)->unk132 = 2;
        sel = D_807FBB40->unk154;
    } else if (sel != 0x32) {
        ((L6Actor *)D_807FBB40)->unk132 = 1;
        sel = D_807FBB40->unk154;
    }
    if (sel != 0x32 || D_807FBB70.unk15 != 0) {
        if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && sel != 0x37) {
            if (((L6Actor *)D_807FBB40)->unk134 < -1) {
                func_8072D714(D_807FBB70.unk1FC, 0x20C);
                ((L6Actor *)D_807FBB40)->unkC0 = 250.0f;
            } else {
                func_8072D714(D_807FBB70.unk1FC, 0x20B);
                ((L6Actor *)D_807FBB40)->unkC0 = 200.0f;
            }
            ((L6Sub90 *)D_807FDC90)->unk35 = 2;
            D_807FBB40->unk138 &= 0xFFFF7FFF;
            sel = D_807FBB40->unk154;
        } else if (D_807FBB70.unk200 == 4) {
            func_8072DEA8(0x209, 0x31, D_807FBB70.unk1FC);
            sel = D_807FBB40->unk154;
        } else if (D_807FBB70.unk200 == 5) {
            func_8072DEA8(0x20A, 0x32, D_807FBB70.unk1FC);
            ((L6Actor *)D_807FBB40)->unkC0 = 220.0f;
            D_807FBB40->unk132 = 8;
            sel = D_807FBB40->unk154;
        }
    }
    switch (sel) {
    case 0x31:
        if (((L6Actor *)D_807FBB40)->unk155 != 0 || (*((L6Actor *)D_807FBB40)->unk4)->unk24 == 0.0f) {
            func_8072DE44(0x203, sel);
        }
        func_8072AB74(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        ((L6Actor *)D_807FBB40)->unkE6 = func_806CC190(((L6Actor *)D_807FBB40)->unkE6, ((L6Actor *)D_807FBB40)->unkEE, 7.0f);
        switch (((L6Actor *)D_807FBB40)->unk155) {
        case 0:
            func_8072AB74(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            ((L6Actor *)D_807FBB40)->unk132 = 1;
            func_8072DE44(0x203);
            break;
        }
        break;
    case 0x28:
        switch (((L6Actor *)D_807FBB40)->unk155) {
        case 0:
            func_80614EBC(D_807FBB40, 0x20D);
            ((L6Actor *)D_807FBB40)->unk155 = 1;
            break;
        case 2:
            func_806B11C0(1);
            func_806B11C0(2);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1D5, 0xFF, 0x7F, 1);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x25A, 0xFF, 0x7F, 1);
            ((L6Actor *)D_807FBB40)->unk155 = 3;
            break;
        case 4:
            func_8072DE44(0x203, sel);
            break;
        }
        break;
    case 0x11:
        func_80724E48(5);
        switch (((L6Actor *)D_807FBB40)->unk155) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x205);
            ((L6Actor *)D_807FBB40)->unk155 += 1;
        case 1:
            func_8072AB74(D_807FBB40->unk154, ((L6Sub94 *)D_807FDC94)->unk7C, ((L6Sub94 *)D_807FDC94)->unk84, 0x200, 0.0f);
            if (((L6Actor *)D_807FBB40)->unkB8 < 1.0f) {
                ((L6Actor *)D_807FBB40)->unk155 += 1;
            }
            break;
        case 2:
            func_8072A450();
            if ((func_80611A44() >> 15) % 1000 >= 0x3E4) {
                func_8072DE44(0x203);
            }
            break;
        }
        break;
    case 0x27:
        func_8072AB74(D_807FBB40->unk154, ((L6Sub94 *)D_807FDC94)->unk7C, ((L6Sub94 *)D_807FDC94)->unk84, 0x200, 0.0f);
        switch (((L6Actor *)D_807FBB40)->unk155) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            if ((func_80611A44() >> 15) % 1000 >= 0x259) {
                func_80614EBC(D_807FBB40, 0x208);
                ((L6Actor *)D_807FBB40)->unk155 = 5;
            } else {
                func_80614EBC(D_807FBB40, 0x206);
                ((L6Actor *)D_807FBB40)->unk155 = 1;
            }
            break;
        case 1:
            if (((L6Sub90 *)D_807FDC90)->unk1A & 0x100) {
                actorClearNodeFlag(D_807FBB40, 2);
                actorClearNodeFlag(D_807FBB40, 3);
            }
            break;
        case 2:
            if (((L6Sub90 *)D_807FDC90)->unk1A & 0x100) {
                ((L6Sub90 *)D_807FDC90)->unk1A &= 0xFEFF;
                func_80614EBC(D_807FBB40, 0x207);
                ((L6Actor *)D_807FBB40)->unk155 = 3;
            } else {
                func_8072DE44(0x203);
            }
            break;
        case 3:
            if (((L6Sub90 *)D_807FDC90)->unk1A & 0x100) {
                ((L6Sub90 *)D_807FDC90)->unk1A &= 0xFEFF;
                func_80614EBC(D_807FBB40, 0x208);
                ((L6Actor *)D_807FBB40)->unk155 = 5;
            }
            break;
        case 4:
            func_8072DE44(0x203);
            break;
        case 5:
            ((L6Actor *)D_807FBB40)->unk132 = 4;
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            D_807FBB40->unk154 = 0x11;
            ((L6Actor *)D_807FBB40)->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        if (func_8061CB50() == 0) {
            func_806B1290();
            func_806B1348();
        }
        func_80724E48(D_807FBB40->unk154 == 1 ? 2 : 0);
        func_8072AB74(D_807FBB40->unk154, ((L6Sub94 *)D_807FDC94)->unk7C, ((L6Sub94 *)D_807FDC94)->unk84, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48(D_807FBB40->unk154 == 0x35 ? 2 : 3);
        func_8072AB74(D_807FBB40->unk154, ((L6Sub90 *)D_807FDC90)->unkA, ((L6Sub90 *)D_807FDC90)->unkE, 0, 0.0f);
        break;
    case 0x37:
        ((L6Actor *)D_807FBB40)->unkE6 = func_806CC190(((L6Actor *)D_807FBB40)->unkE6, ((L6Actor *)D_807FBB40)->unkEE, 7.0f);
        switch (((L6Actor *)D_807FBB40)->unk155) {
        case 0:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if (arg0 != 0) {
                sfxSpawnTableNodes(D_807FBB40);
            }
            ((L6Actor *)D_807FBB40)->unk155 += 1;
        case 2:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            func_8072DC7C(8);
            break;
        case 3:
            ((L6Actor *)D_807FBB40)->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x203);
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
        func_8072C918(0x6400, 0x203, 0x204);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

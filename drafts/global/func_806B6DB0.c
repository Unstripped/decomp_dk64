// func_806B6DB0 (src/global/BB300.c): Parked NON_MATCHING, stage 6: only diff is 3 insns at u8 'near' flag (sp31): target 'move t1,zero; bc1fl: sb t1 in delay; li t1,1; sb t1' vs ours 'li t1,1 hoisted; sb zero; sb t1'. Needs func_8072AB74 declared s32 (fixed 4 v0/v1 temps), sel pinned to a1 via func_8072B7CC(0x232, sel), func_806B6C88(u8,s16) and func_806B6600(u8) prototyped, case 1 empty in 0x11 switch, reuse diff for abs check. Tried near: if/else, ternary, relational assign, init, flag temp, inverted cond.
typedef struct L2Sub178 {
    /* 0x0 */ s16 pad0;
    /* 0x2 */ s16 unk2;
} L2Sub178;

// File-local view of the current actor (D_807FBB40) for fields Actor lacks or types differently.
typedef struct L2Actor {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ L2Sub178 *unk178;
} L2Actor;

typedef struct L2View90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0x10];
    /* 0x2C */ s16 unk2C;
} L2View90;

typedef struct L2View98 {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
} L2View98;

typedef struct L2View9C {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[5];
    /* 0x13 */ u8 unk13;
} L2View9C;

extern s32 D_8076A064;
extern s32 D_8076A0A8;

s32 func_80611A44(void);
void func_80614EBC(void *, s32);
void func_806319C4(Actor *, s32);
void func_806B6600(u8);
void func_806B6C88(u8, s16);
void func_80724CA4(s32, s32);
void func_80724E48();
void func_8072881C(s32, void *);
s32 func_8072AB74(s32, f32, f32, s32, f32);
void func_8072B324(Actor *, s32);
void func_8072B59C();
void func_8072B7CC();
void func_8072C918(s32, s32, s32);
void func_8072D13C(s32, s32);
void func_8072D714(s32, s32);
void func_8072DAA4();
void func_8072DC7C(s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void sfxSpawnTableNodes(Actor *);
void sfxStopSlotSound(Actor *, s32);

void func_806B6DB0(s32 arg0) {
    L2Sub178 *p;
    s16 diff;
    u8 near;
    s32 tgt;
    s32 sel;
    f32 dx;
    f32 dz;

    p = ((L2Actor *)D_807FBB40)->unk178;
    if (((L2Actor *)D_807FBB40)->unkEE < D_807FBB40->unkE6) {
        diff = D_807FBB40->unkE6 - ((L2Actor *)D_807FBB40)->unkEE;
    } else {
        diff = ((L2Actor *)D_807FBB40)->unkEE - D_807FBB40->unkE6;
    }
    dx = D_807FBB40->unk7C - D_807FDC94->unk7C;
    dz = D_807FBB40->unk84 - D_807FDC94->unk84;
    near = 0;
    if (dx * dx + dz * dz < 2500.0f) {
        near = 1;
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((L2View98 *)D_807FDC98)->unk34 = 1.0f;
        func_80724CA4(2, 2);
        D_807FBB40->unkB8 = ((L2View9C *)D_807FDC9C)->unkC;
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        tgt = D_807FBB70.unk1FC;
        ((L2Actor *)D_807FBB40)->unkC0 = 200.0f;
        func_8072D714(tgt, 0x236);
        if ((tgt != 0 && ((Actor *)tgt)->unk58 == 0x29) || (D_8076A0A8 == 0x10 && ((L2View9C *)D_807FDC9C)->unk13 < 0x11)) {
            ((L2View90 *)D_807FDC90)->unk1A |= 1;
        }
    }
    sel = D_807FBB40->unk154;
    if (sel == 0x23 && D_807FBB40->unkB8 > 90.0f && diff >= 0x1F5 && diff < 0xE0C) {
        diff = ((L2Actor *)D_807FBB40)->unkEE - D_807FBB40->unkE6;
        if (diff < 0 || diff >= 0x801) {
            p->unk2 = 0x8C;
        } else {
            p->unk2 = -0x8C;
        }
        func_8072B59C(0x14, 0xA, 0x235);
        sel = D_807FBB40->unk154;
    }
    switch (sel) {
    case 0x14:
        switch (((L2Actor *)D_807FBB40)->unk155) {
        case 0:
            ((L2View90 *)D_807FDC90)->unk2C = 0x1E;
            ((L2Actor *)D_807FBB40)->unk155 += 1;
            break;
        case 1:
            if (((L2View90 *)D_807FDC90)->unk2C != 0) {
                D_807FBB40->unkE6 += p->unk2;
                p->unk2 += -p->unk2 * 0.01;
                ((L2View90 *)D_807FDC90)->unk2C -= 1;
                if (!(D_8076A064 & 3)) {
                    func_8072DAA4();
                }
            } else {
                ((L2Actor *)D_807FBB40)->unk155 = 2;
            }
            break;
        case 2:
            sfxStopSlotSound(D_807FBB40, 0);
            func_8072B59C(1, ((L2View9C *)D_807FDC9C)->unkC, 0x232);
            ((L2Actor *)D_807FBB40)->unkEE = D_807FBB40->unkE6;
            break;
        }
        func_80724E48(5);
        func_806B6600(0);
        func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x300, 0.0f);
        break;
    case 1:
        if ((func_80611A44() >> 15) % 1000 >= 0x3E3) {
            D_807FBB40->unk154 = 0x11;
            ((L2Actor *)D_807FBB40)->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
        func_80724E48((u8)(D_807FBB40->unk154 == 1 ? 2 : 0));
        func_806B6600(near);
        func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x400, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
        func_80724E48((u8)(D_807FBB40->unk154 == 0x35 ? 2 : 3));
        func_806B6600(0);
        func_8072AB74(D_807FBB40->unk154, ((L2View90 *)D_807FDC90)->unkA, ((L2View90 *)D_807FDC90)->unkE, 0x400, 0.0f);
        break;
    case 0x11:
        func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
        func_806B6600(0);
        func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 2, 0.0f);
        switch (((L2Actor *)D_807FBB40)->unk155) {
        case 1:
            break;
        case 0:
            func_8072B324(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x234);
            ((L2Actor *)D_807FBB40)->unk155 += 1;
            break;
        case 2:
            func_8072B59C(1, ((L2View9C *)D_807FDC9C)->unkC, 0x232);
            break;
        }
        break;
    case 0x37:
        switch (((L2Actor *)D_807FBB40)->unk155) {
        case 0:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(D_807FBB40);
            ((L2Actor *)D_807FBB40)->unkC0 = 100.0f;
            ((L2Actor *)D_807FBB40)->unk155 += 1;
        case 2:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 3:
            if (((L2View90 *)D_807FDC90)->unk1A & 1) {
                ((L2Actor *)D_807FBB40)->unk155 += 1;
            } else {
                func_806B6C88(((L2View9C *)D_807FDC9C)->unkD, mathAngleBetweenPoints2D(D_807FDC94->unk7C, D_807FDC94->unk84, D_807FBB40->unk7C, D_807FBB40->unk84));
                ((L2Actor *)D_807FBB40)->unk155 = 5;
            }
            break;
        case 4:
            func_8072DC7C(5);
            break;
        case 5:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x16:
        ((L2View90 *)D_807FDC90)->unk1A |= 1;
    default:
        func_8072B7CC(0x232, sel);
        break;
    }
    sel = D_807FBB40->unk154;
    switch (sel) {
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        func_8072D13C(D_807FBB40->unk154, 1);
    default:
        func_8072C918(arg0, 0x232, 0x233);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

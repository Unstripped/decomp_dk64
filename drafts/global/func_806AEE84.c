// func_806AEE84 (src/global/B2CE0.c): stage 5: all but 0x11 case-1 tail matches; target reloads s0 in shared tail (lui/lw s0 at join, bc1f/default nop), mine PRE-reloads per path (+4 insns)
typedef struct L3Sub178 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
} L3Sub178;

typedef struct L3Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x54];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x2A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x4A];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x20];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ L3Sub178 *unk178;
} L3Actor;

typedef struct L3ModelHdr {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x12];
    /* 0x24 */ f32 unk24;
} L3ModelHdr;

extern L3Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
s32 func_80611A44(void);
void func_80614EBC(L3Actor *, s32);
void func_806319C4(L3Actor *, s32);
void func_806AEE08(void);
void func_80724CA4(s32, s32);
void func_80724E48(u8);
void func_80729B00(void);
void func_8072A450(void);
void func_8072AB74(u8, f32, f32, s32, f32);
void func_8072B324(L3Actor *, s32);
void func_8072B79C(s32, s32, s32);
void func_8072B7CC(s32);
void func_8072C918(s32, s32, s32);
void func_8072D13C(u8, s32);
void func_8072D714(s32, s32);
void func_8072DC7C(s32);
s32 func_8072DE10(s32);
void func_8072DE44(s32);
void func_8072DEA8(s32, s32, s32, ActorGlobalState *);
s32 func_8072E54C(void);
void projectileGetTargetCoords(L3Actor *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s16, f32, f32, L3Actor *);
void sfxSpawnTableNodes(L3Actor *);

void func_806AEE84(void) {
    L3Sub178 *sp34;
    f32 sp30;

    sp34 = D_807FBB40->unk178;
    sp30 = D_807FBB40->unk4->unk38 / 0.15;
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp34->unk0 = 0x2710;
        sp34->unk2 = 0x20;
        func_8072B79C(0x2AD, 0x2AB, 0x2AC);
        func_80724CA4(2, 1);
    }
    if (D_807FBB40->unk154 != 0x32 || D_807FBB70.unk15 != 0) {
        if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
            func_8072D714(D_807FBB70.unk1FC, 0x2AE);
            D_807FDC90->unk2C = 0x1C2;
        } else if (D_807FBB70.unk200 == 4) {
            func_8072DEA8(0x2B2, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
            D_807FBB40->unkB8 = 0.0f;
        } else if (D_807FBB70.unk200 == 5) {
            func_8072DEA8(0x2B1, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
            D_807FBB40->unkB8 = 0.0f;
        }
    }
    switch (D_807FBB40->unk154) {
        case 0x31:
            if (D_807FBB40->unk155 != 0 || (*(L3ModelHdr **)D_807FBB40->unk4)->unk24 == 0.0f) {
                func_8072DE44(0x2AB);
            }
            func_8072AB74(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x11:
            func_80724E48(5);
            switch (D_807FBB40->unk155) {
                case 0:
                    func_8072B324(D_807FBB40, 0);
                    func_80614EBC(D_807FBB40, 0x2B0);
                    D_807FBB40->unk155 = 1;
                case 1:
                    func_8072AB74(0x11, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
                    if (D_807FBB40->unkB8 < 1.0f) {
                        D_807FBB40->unk155++;
                    }
                    break;
                case 2:
                    func_806AEE08();
                    func_8072A450();
                    if ((func_80611A44() >> 15) % 1000 >= 0x3DF && (*(L3ModelHdr **)D_807FBB40->unk4)->unk10 != 0x4C4) {
                        func_8072DE44(0x2AB);
                    }
                    break;
            }
            break;
        case 0x27:
            switch (D_807FBB40->unk155) {
                case 0:
                    func_8072B324(D_807FBB40, 0);
                    D_807FBB40->unkB8 = 0.0f;
                    func_80614EBC(D_807FBB40, 0x2B4);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    break;
                case 4:
                    func_8072DE44(0x2AB);
                    break;
            }
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            break;
        case 0x25:
            func_80724E48(0);
            switch (D_807FBB40->unk155) {
                case 0:
                    func_80614EBC(D_807FBB40, 0x2B3);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(D_807FBB40, 2);
                    projectileSpawnNodeEntry(0x32, 0x63, sp30 * 0.4, D_807FBB40->unkE6, 300.0f, 280.0f, D_807FBB40);
                    D_807FBB40->unk155 = 3;
                    break;
                case 4:
                    func_8072DE44(0x2AB);
                    break;
            }
            break;
        case 1:
            if (func_8072E54C() != 0) {
                D_807FBB40->unk154 = 0x11;
                D_807FBB40->unk155 = 0;
            }
        case 0x23:
            if (D_807FBB70.unk200 == 2 && func_8072DE10(0x1388) != 0) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155 = 0;
            }
        case 0x10:
            func_806AEE08();
            func_80724E48(D_807FBB40->unk154 == 1 ? 2 : 0);
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(D_807FBB40->unk154 == 0x35 ? 2 : 3);
            func_8072AB74(D_807FBB40->unk154, D_807FDC90->unkA, D_807FDC90->unkE, 0, 0.0f);
            break;
        case 0x37:
            switch (D_807FBB40->unk155) {
                case 0:
                    D_807FBB40->unkE6 += D_807FDC90->unk2C;
                    D_807FDC90->unk2C = D_807FDC90->unk2C * 0.95;
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    D_807FBB40->unk155++;
                case 2:
                    func_8072DC7C(5);
                    break;
                case 3:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(0x2AB);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 0x24:
        case 0x25:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            func_8072D13C(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x6400, 0x2AB, 0x2AC);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

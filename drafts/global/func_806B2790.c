// func_806B2790 (src/global/B7490.c): M5: stage 5 (frame 0x40 matches, structure/branches match). Only regalloc left: target loads unk154 into a0 then 'move v1,a0' (two webs: a0 for switch1 + func_8072D13C arg, v1 for func_8072A86C (s16) arg + final switch); mine loads straight into v1/t regs. Explicit copy local does not survive uopt copy-prop. Parked NON_MATCHING in private copy.
extern Actor *D_807FBB40;
extern Actor *D_807FDC94;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[0x12];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ f32 unk30;
} M5State90;

typedef struct {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 unk46;
} M5State98;

typedef struct {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ u8 padC8[0x1C];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ u8 padE6[2];
    /* 0xE8 */ s16 unkE8;
} M5Actor;

#define M5A ((M5Actor *)D_807FBB40)

extern M5State90 *D_807FDC90;
extern M5State98 *D_807FDC98;

void func_80614EBC(void *, s32);
s32 func_8072E0A8(s32, s32);
void func_80729B00(void);
void func_8067ACB4(Actor *);
void func_806319C4(void *, s32);
void effectSpawnSparks(s32, s32);
void func_8072AB74(s32, f32, f32, s32, f32);
void func_8072A920(s16, s32, f32, f32, f32, s32, f32, f32, s32);
void func_8072A86C(s16, f32, f32, f32, s32);
void func_8072B7CC(s32);
s32 func_8072D13C();
void func_8072D714(s32, s32);
void func_8072DE44(s32, s32);
void func_8072DC7C(s32, s32, f32);
void func_8072AA80(void);
void func_8072C918(s32, s32, s32);
s32 func_80611A44(void);
f32 func_80612794(s16);
s16 func_806CC190(s16, s16, f32);

void func_806B2790(void) {
    u8 flag;
    u8 st;

    func_80729B00();
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, 0x2E1);
        D_807FDC98->unk46 |= 8;
    }
    effectSpawnSparks(0x1F, 0);
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x27:
            flag = 0;
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_80614EBC(D_807FBB40, 0x2E0);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    flag = 1;
                    D_807FBB40->unkB8 = 150.0f;
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    flag = 1;
                    break;
                case 4:
                    func_8072DE44(0x2DE, 0x2E0);
                    break;
            }
            st = D_807FBB40->unk154;
            if (flag) {
                func_8072A86C(st, D_807FDC94->unk7C, D_807FDC94->unk84, 100.0f, 0x2240);
            }
            break;
        case 1:
            M5A->unkE4 = M5A->unkE4 + 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((func_80611A44() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, D_807FDC90->unkC, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            M5A->unkE4 = M5A->unkE4 + 800.0f * func_80612794(D_807FDC90->unk18 * 15);
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, ((D_807FBB40->unkAC - D_807FBB40->unk15E) < D_807FDC94->unk80) ? (D_807FBB40->unkAC - D_807FBB40->unk15E) : D_807FDC94->unk80, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC90->unkA, (D_807FDC90->unkC < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? D_807FDC90->unkC : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    M5A->unkE4 = func_806CC190(M5A->unkE4, 0, 7.0f);
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
            func_8072B7CC(0x2DE);
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
            func_8072D13C(st, 1);
        default:
            func_8072C918(0x6400, 0x2DE, 0x2DE);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

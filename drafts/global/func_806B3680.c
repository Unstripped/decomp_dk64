// func_806B3680 (src/global/B7490.c): M5: stage 5-6. Frame 0x60 matches, sp54/sp58 slots match with local decl order dx,var,sp54,dy,dz,i,st. Left: spill of func_8071ABDC ptr at 0x40 vs 0x44 (target has one extra named slot below), target keeps 0x27 const in s0 (beql v0,s0) and v1=unk154 while mine uses li at,0x27 and s0=unk154; inner switch default 'addiu t7,v1,1' delay slot + shared sb. Parked NON_MATCHING in private copy.
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

extern Actor *D_807FBB4C;
extern s32 D_8076A0A8;
extern u8 D_8072073C[];

void func_8072E1A4(s32, void *);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_807248B0(void *, f32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714950(s32);
void func_8071498C(void *);
void func_8071ABDC();
void func_80714998(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_8067E278(s32, s32);
void actorGetOrSetNodeScale(void *, s32, f32);
void func_8066EB40(void *, f32);

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
    func_80729B00();
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
            func_8072AB74(0, 0.0f, 0.0f, 2, 0.0f);
            if (D_807FBB40->unk80 < D_807FBB40->unkAC) {
                D_807FBB40->unk80 = D_807FBB40->unkAC;
                M5A->unkC0 = M5A->unkC4;
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
                    dx = D_807FBB40->unk4->unk38;
                    i = 0;
                    if (dx < D_807FDC90->unk30) {
                        func_807248B0(D_807FBB40, dx * 1.01);
                    } else {
                        do {
                            func_807149B8(1);
                            func_807149FC(2);
                            func_80714950(i + 0x0B020000);
                            func_8071498C(func_8071ABDC);
                            func_80714998(1);
                            func_80714CC0(D_8072073C, 2.0 * D_807FBB40->unk4->unk38, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                            i++;
                        } while (i < 0xC);
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
                    break;
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
    if (D_807FBB40->unk154 == 2 || D_807FBB40->unk154 == 3) {
        func_8072D13C(st, 1);
    }
    func_806319C4(D_807FBB40, 0);
}

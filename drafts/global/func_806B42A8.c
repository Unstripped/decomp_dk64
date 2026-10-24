// func_806B42A8 (src/global/B7490.c): Stage 4: switch layout/jump tables right (cases 1,0x10,0x23 fall into 2,3,7,0x35; 0x26 inner switch; 0x37 inner jtbl; 0x40 no-op; default func_8072B7CC(arg2)). No var_a2/var_v1 locals: first 50 insns match, frame 0x38 ok. Target loads actor->unk154 into a2 before the D_807FBB70 test and keeps a copy in v1 (move v1,a2), re-read at each case end; adding m2c's var_a2/var_v1 makes IDO hoist &D_807FBB40 into t0 (not in target) and size 13008 vs 13056. Callees func_806B3F90/8072D714/sfxStopSlotSound/8072D13C probably take 2 args only (extra a2/a3 are just live regs).
typedef struct M6ActorX {
    /* 0x000 */ u8 pad0[0x6E];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x50];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[2];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[0x46];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x1E];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ s16 *unk178;
} M6ActorX;

typedef struct M6State90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x18];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ f32 unk30;
} M6State90;

typedef struct M6State9C {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD[3];
    /* 0x10 */ u8 unk10;
} M6State9C;

extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
extern M6State90 *D_807FDC90;
extern Actor *D_807FDC94;
extern M6State9C *D_807FDC9C;
void func_80729B00(void);
void func_806319C4(void *, s32);
void func_8072881C();
s16 func_806CC190(s16, s16, f32);
s32 func_806B3F90();
s32 func_8072D13C();
void func_8072B7CC(s32);
void func_8072AB74(u8, f32, f32, s32, f32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void func_8072D714(s32, u16);
s32 func_8061CB50(void *);
void sfxStopSlotSound(Actor *, s32);
void sfxSpawnTableNodes(Actor *);
void func_8072DC7C(s32);

void func_806B42A8(void (*arg0)(), u16 arg1, u16 arg2, s16 arg3) {
    s16 *var_t2;
    s16 var_t0;
    s16 var_t1;

    var_t2 = ((M6ActorX *) D_807FBB40)->unk178;
    if ((arg3 != 0) && (D_807FBB40->unk154 != 0x37) && (((M6ActorX *) D_807FBB40)->unk6E == -1)) {
        sfxPlayActorSound(D_807FBB40, arg3, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        *var_t2 = D_807FDC9C->unkA;
        if (D_807FDC9C->unkB == 0) {
            D_807FDC9C->unkB = 0x28;
        }
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, arg1);
        ((M6ActorX *) D_807FBB40)->unkC0 = 300.0f;
        *var_t2 = 0;
        D_807FDC90->unk2C = 0x2BC;
    }
    var_t0 = D_807FDC90->unkA;
    var_t1 = D_807FDC90->unkE;
    switch (D_807FBB40->unk154) {
    case 1:
    case 0x10:
    case 0x23:
        var_t0 = (s16) (s32) D_807FDC94->unk7C;
        var_t1 = (s16) (s32) D_807FDC94->unk84;
    case 2:
    case 3:
    case 7:
    case 0x35:
        if (D_807FBB40->unk80 < (f32) (D_807FDC9C->unk6 + *var_t2)) {
            D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (u32) D_807FDC9C->unkB * 0.03125));
        } else {
            if ((func_8061CB50(D_807FDC90) == 0) && (arg0 != NULL)) {
                arg0();
            }
        }
        func_8072AB74(D_807FBB40->unk154, (f32) var_t0, (f32) var_t1, 0x2C1, 0.0f);
        ((M6ActorX *) D_807FBB40)->unkE8 = func_806CC190(((M6ActorX *) D_807FBB40)->unkE8, 0, 5.0f);
        break;
    case 0x26:
        switch (D_807FBB40->unk155[0]) {
        case 0:
            D_807FDC90->unkA = (s16) (s32) D_807FDC94->unk7C;
            D_807FDC90->unkC = (s16) (s32) D_807FDC94->unk80;
            D_807FDC90->unkE = (s16) (s32) D_807FDC94->unk84;
            D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            D_807FDC90->unk2C = 0x64;
        case 1:
            if ((func_806B3F90(D_807FDC90, 0x23) & 1) || (D_807FBB40->unk80 < (f32) (D_807FDC90->unkC + 0xF))) {
                D_807FBB40->unk154 = D_807FDC9C->unk10;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        }
        break;
    case 0x37:
        D_807FBB40->unkE6 = D_807FBB40->unkE6 + D_807FDC90->unk2C;
        D_807FDC90->unk2C = ((D_807FDC90->unk2C - 0x11) < 0) ? 0 : (D_807FDC90->unk2C - 0x11);
        if (D_807FDC90->unk2C == 0) {
            sfxStopSlotSound(D_807FBB40, 0);
        }
        switch (D_807FBB40->unk155[0]) {
        case 0:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(D_807FBB40);
            if (D_807FBB40->unk58 == 0x11D) {
                D_807FBB40->unk155[0] = 3;
            } else {
                ((M6ActorX *) D_807FBB40)->unkC0 = 50.0f;
                D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
        case 2:
                func_8072AB74(0x37, 0.0f, 0.0f, 0x222, 0.0f);
            }
            break;
        case 3:
            func_8072DC7C(0xA);
            break;
        case 4:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(arg2);
        break;
    }
    switch (D_807FBB40->unk154) {
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        func_8072D13C(D_807FBB40->unk154, 1);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

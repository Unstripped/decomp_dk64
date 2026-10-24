// func_806B49B0 (src/global/B7490.c): Stage 4: structure and switch order right (cases 2,3 / 0x26 inner switch / 0x37 / 0x40 empty / default; second switch 2,3 and 0x26). Dead s32* locals assigned from temp_v0 fix frame size 0x40 (two extra slots). Remaining: target reserves t0 for the switch var arg0 (lbu t0,0x43(sp)) for the whole function so other temps start at t1, and spills it (sw t0,0x24) only around calls; mine allocates it late (t8) with a hoisted spill; sp32 add order lh unk6 first (addu t2,t9,t1). u8->float conversions need (f32)(u32)x. Total size 8 insns short.
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
extern f32 D_807502EC;
void func_80614EBC(void *, s32);
void func_80724CA4(s32, s32);
void func_8072AB74(u8, f32, f32, s32, f32);
s16 func_806CC190(s16, s16, f32);
s32 func_806B3F90();
s32 func_8072D13C();
void func_8072B7CC(s32);

void func_806B49B0(u8 arg0, s16 arg1, s16 arg2) {
    s16 *temp_v0;
    s16 sp32;
    u8 var_t0;
    s32 *dead1;
    s32 *dead2;

    temp_v0 = ((M6ActorX *) D_807FBB40)->unk178;
    dead1 = (s32 *) temp_v0;
    dead2 = (s32 *) temp_v0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(1, 1);
        D_807FDC90->unk30 = D_807FBB40->unk4->unk38;
        D_807FBB40->unkB8 = (f32) (u32) D_807FDC9C->unkC;
        *temp_v0 = D_807FDC9C->unkA;
        ((M6ActorX *) D_807FBB40)->unkC4 = D_807502EC;
    }
    sp32 = D_807FDC9C->unk6 + *temp_v0;
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (arg0 != 0x37)) {
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155[0] = 0;
    }
    var_t0 = arg0;
    switch (var_t0) {
    case 2:
    case 3:
        if (D_807FBB40->unk155[0] == 0) {
            func_80614EBC(D_807FBB40, arg1);
            D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
        }
        func_8072AB74(arg0, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0xE1, 0.0f);
        if (D_807FBB40->unk80 < (f32) sp32) {
            if (D_807FBB40->unk155[0] == 2) {
                D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.03125));
            } else {
                D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.015625));
            }
        }
        ((M6ActorX *) D_807FBB40)->unkE8 = func_806CC190(((M6ActorX *) D_807FBB40)->unkE8, 0, 5.0f);
        break;
    case 0x26:
        switch (D_807FBB40->unk155[0]) {
        case 0:
        case 1:
        case 2:
            func_80614EBC(D_807FBB40, arg2);
            D_807FBB40->unk155[0] = 3;
        case 3:
            func_806B3F90(D_807FDC90, 0x26);
            break;
        }
        break;
    case 0x37:
        func_8072AB74(0x37, 0.0f, 0.0f, 0x22, 0.0f);
        if (D_807FBB40->unk6A & 1) {
            D_807FBB40->unk154 = 0x40;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(arg1);
        break;
    }
    switch (var_t0) {
    case 2:
    case 3:
        func_8072D13C(arg0, 1);
        break;
    case 0x26:
        if (func_8072D13C(arg0, 1) != 0) {
            D_807FBB40->unk154 = D_807FDC9C->unk10;
            D_807FBB40->unk155[0] = 0;
        }
        break;
    }
}

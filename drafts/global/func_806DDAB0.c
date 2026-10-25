// func_806DDAB0 (src/global/D5E10.c): Stage 6, 2 rows differ: in the join before 'if (P->unkF8 == 0)' target orders addiu a0,sp,0x4c / addiu a1,sp,0x4a / lbu F8 / move v1,zero while ours emits move v1,zero / addiu a0 / lbu / addiu a1. Layout needs dead 'u8 k; s16 h;' locals + 'u8 flag' (u8 flag makes 'or a2,flag,cmp' order). Tried v=0 placement, 4-arg/unproto collisionGetCoords, F8 local, permuter 900s (best 567 vs base 570, no gain).
// Needs from file context: G15PlayerEntry/D_807FC924, func_806CC190, func_80614D00, func_80614E78, func_806DF6D4, func_806CFF9C, func_806319C4, D_807FBB48, D_807FD584, D_807FC929
s32 func_806CFC90(Actor *, f32 *, s32, f32);

typedef struct LD5CActor {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[4];
    /* 0x0F4 */ s16 unkF4;
    /* 0x0F6 */ s16 unkF6;
    /* 0x0F8 */ u8 padF8[4];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x57];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} LD5CActor;

typedef struct LD5CPlayer {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ u8 padA[0xD6];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ f32 unkE4;
    /* 0x0E8 */ u8 padE8[2];
    /* 0x0EA */ s16 unkEA;
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[2];
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ f32 unkF4;
    /* 0x0F8 */ u8 unkF8;
    /* 0x0F9 */ u8 padF9[3];
    /* 0x0FC */ s32 unkFC;
} LD5CPlayer;

typedef struct LD5Pad {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u8 pad2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 pad30[4];
} LD5Pad;

#define LD5C_A ((LD5CActor *)D_807FBB40)
#define LD5C_P ((LD5CPlayer *)D_807FD580)

extern LD5Pad D_807FD610[];
extern s8 D_807FD63F;
extern f32 D_80753D70[];
extern f32 D_80753D8C[];
extern s16 D_80753DA8[];
extern s16 D_80753DB8[];
u8 actorSetTargetAngleAndCheck(Actor *, s16);
s32 func_80672A70(s16, s16);
s32 func_80666AEC(void);
void collisionGetCoords(void *, s16 *);
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocity(Actor *);
void func_80665548(void);
void func_80665564(Actor *, s32);

void func_806DDAB0(void) {
    f32 sp64;
    u8 k;
    u8 sp62;
    s16 sp60;
    f32 t;
    s16 h;
    u8 a;
    f32 f;
    f32 sp50;
    u8 v;
    u8 flag;
    s16 sp4C;
    s16 sp4A;
    u8 sp49;
    s32 x;

    sp49 = 0;
    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        sp50 = D_80753D70[D_807FD584];
    } else {
        sp50 = D_80753D8C[D_807FD584];
    }
    switch (LD5C_A->unk155) {
    case 0:
        func_806DF6D4(0x5A);
        LD5C_P->unkEC = LD5C_A->unkE6;
        LD5C_P->unkF8 = 5;
        LD5C_A->unk155 = 2;
        break;
    case 1:
    case 2:
    case 3:
        if (LD5C_P->unkF8 != 0) {
            LD5C_P->unkF8 -= 1;
        }
        if (func_806DF6D4(0x5A) == 0) {
            switch (LD5C_P->unk8) {
            case -1:
                if (LD5C_A->unk155 == 1) {
                    t = LD5C_A->unkB8 * 0.025;
                    f = t > 0.1 ? t : 0.1;
                    func_80614D00(D_807FBB40, f, 1.0f);
                } else {
                    func_80614E78(D_807FBB48, 0x77);
                    LD5C_A->unk155 = 1;
                }
                break;
            case 0:
                if (LD5C_A->unk155 != 2) {
                    func_80614E78(D_807FBB48, 0x76);
                    LD5C_A->unk155 = 2;
                }
                break;
            case 1:
                if (LD5C_A->unk155 == 3) {
                    t = LD5C_A->unkB8 * 0.025;
                    f = t > 0.1 ? t : 0.1;
                    func_80614D00(D_807FBB40, f, 0.0f);
                } else {
                    func_80614E78(D_807FBB48, 0x78);
                    LD5C_A->unk155 = 3;
                }
                break;
            }
        }
        LD5C_A->unkC0 = 0.0f;
        LD5C_A->unkB8 = LD5C_P->unk4;
        if (func_806CFC90(D_807FBB40, &sp64, 1, 15.0f) != 0) {
            if (LD5C_A->unk80 <= sp64 && sp64 - sp50 - LD5C_A->unk80 < 10.0f && func_80666AEC() != 0) {
                LD5C_A->unk80 = sp64 - sp50;
                sp49 = 1;
            }
        }
        if (LD5C_A->unkB8 < 0.0f) {
            if (LD5C_A->unkB8 > 0.0f) {
                LD5C_A->unkB8 = LD5C_A->unkB8;
            } else {
                LD5C_A->unkB8 = -LD5C_A->unkB8;
            }
            sp60 = LD5C_P->unkEA + 0x400;
            sp60 &= 0xFFF;
            LD5C_A->unkEE = LD5C_A->unkF4 + 0xA;
        } else if (LD5C_A->unkB8 > 0.0f) {
            sp60 = LD5C_P->unkEA - 0x400;
            sp60 &= 0xFFF;
            LD5C_A->unkEE = LD5C_A->unkF6 - 0xA;
        }
        sp62 = actorSetTargetAngleAndCheck(D_807FBB40, sp60);
        if (sp62 == 0) {
            LD5C_A->unkB8 = 0.0f;
        }
        LD5C_P->unkEC = func_80672A70(LD5C_A->unkF4, LD5C_A->unkF6) + 0x800;
        LD5C_P->unkEC &= 0xFFF;
        LD5C_A->unkE6 = func_806CC190(LD5C_A->unkE6, LD5C_P->unkEC, 3.0f);
        LD5C_A->unk7C = LD5C_P->unkE0;
        LD5C_A->unk84 = LD5C_P->unkE4;
        if (sp62 == 0 || LD5C_A->unkB8 == 0.0) {
            LD5C_A->unk60 |= 0x800;
        } else {
            LD5C_A->unk60 &= ~0x800;
        }
        break;
    }
    flag = D_807FD610[D_807FC929].unk2F < -0x32 && (D_807FD610[D_807FC929].unk2C & 0x2000);
    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        a = flag;
        a |= LD5C_A->unk80 - LD5C_A->unkA4 < D_80753DA8[D_807FD584];
    } else {
        a = flag;
        a |= LD5C_A->unk80 - LD5C_A->unkA4 < D_80753DB8[D_807FD584];
    }
    v = 0;
    if (LD5C_P->unkF8 == 0) {
        x = LD5C_A->unkFC == 0 || sp49 == 0;
        v = x;
        collisionGetCoords(&sp4C, &sp4A);
        if (sp4A < 0x385) {
            v = x;
            v |= 1;
        }
    }
    if (a != 0 || v != 0) {
        LD5C_P->unkFC = 0x14;
        func_806CFF9C(D_807FBB40);
        LD5C_A->unk60 &= ~0x800;
    }
    if (*(s8 *)((u8 *)&D_807FD63F + D_807FC929 * 0x34) >= 0x33 && LD5C_P->unkF8 == 0 && v == 0) {
        func_80614E78(D_807FBB48, 0x79);
        LD5C_A->unk154 = 0x5C;
        LD5C_A->unk155 = 0;
        LD5C_P->unkF0 = LD5C_A->unk80 + sp50;
        LD5C_P->unkF4 = LD5C_P->unkF0;
    }
    actorStepPhysics(D_807FBB40, LD5C_A->unkEE, LD5C_A->unkEE);
    actorApplyVelocity(D_807FBB40);
    func_80665548();
    func_80665564(D_807FBB40, 0);
    func_806319C4(D_807FBB40, 0);
}

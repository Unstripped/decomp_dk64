// func_8069F020 (src/global/A2F10.c): stage 6: frame 0x68, s0/s1, all args/calls match; remaining: 4 extra insns (case-1 branch likely/branch layout: mine bnezl+b vs beql; zero-constant 0.0f kept in f2 across switch vs per-case mtc1; li vs move for the 0,0 args to func_80613C48)
typedef struct L5bNode {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x16];
    /* 0x24 */ f32 unk24;
} L5bNode;

typedef struct L5bSub4 {
    /* 0x00 */ L5bNode *unk0;
    /* 0x04 */ u8 pad4[0x30];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u8 pad40[0x8];
    /* 0x48 */ s32 unk48;
} L5bSub4;

typedef struct L5bActor {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ L5bSub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x66];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x38];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0xA];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
} L5bActor;

void animSetLoopLimit(void *, s32, s32);
void animSetSpeed(void *, s32, f32);
void animSetFinished(void *, s32, s32);
s32 animIsPlaying(void *, s32);
L5bNode *animGetNodeByIndex(void *, s32);
void lightSetFlags(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, u32, u32, u32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
void func_80613C48(Actor *, s16, s32, s32);
void func_80614D00(Actor *, s32, s32);
void func_8067B238(void *, void *, f32);
void playerStateQueueCallback(s32, void *, s32);
void actorUpdateModelMatrix(void *, s32);
extern u8 D_807444EC;
extern s32 D_807FBB68;

#define L5B_A0 ((L5bActor *)D_807FBB40)
#define L5B_A1 ((L5bActor *)D_807FBB44)

void func_8069F020(void) {
    u8 sp67;
    u16 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    L5bNode *node;

    sp67 = (L5B_A0->unkF0 == 0xBB) ? 0x28 : 0x23;
    sp64 = (L5B_A0->unkF0 == 0x6A) ? 0x78 : 0x190;
    if (D_807444EC == 1) {
        actorDespawn((Actor *)D_807FBB40);
    }
    if (!(L5B_A0->unk60 & 0x10)) {
        L5B_A0->unk12A = 0x3E8;
        L5B_A0->unk60 |= 0x400;
        animSetLoopLimit(D_807FBB40, 0, 1);
        animSetSpeed(D_807FBB40, 0, 0.5f);
        animSetFinished(D_807FBB40, 0, 1);
        L5B_A0->unkEE = 0x3C;
    }
    if (L5B_A0->unk168 != 0) {
        sp60 = 1.0f;
        if (L5B_A0->unkEE < 0x1E) {
            sp60 = L5B_A0->unkEE / 30.0;
        }
        lightSetFlags(1);
        lightAdd(L5B_A0->unk7C, L5B_A0->unk80, L5B_A0->unk84, 0.0f, 0.0f, 0.0f,
                 L5B_A0->unk4->unk34 * 300.0f, 0,
                 (u32)((f32)L5B_A0->unk16A * sp60),
                 (u32)((f32)L5B_A0->unk16B * sp60),
                 (u32)((f32)L5B_A0->unk16C * sp60));
        L5B_A0->unk4->unk34 = (f32)((f64)L5B_A0->unk4->unk34 * L5B_A0->unk160);
        L5B_A0->unk4->unk3C = (f32)((f64)L5B_A0->unk4->unk3C * L5B_A0->unk160);
    }
    switch (L5B_A0->unk154) {
    case 0:
        if (L5B_A0->unk168 == 0) {
            L5B_A0->unk4->unk34 =
                (f32)((f64)L5B_A0->unk4->unk34 * L5B_A0->unk160);
            L5B_A0->unk4->unk3C =
                (f32)((f64)L5B_A0->unk4->unk3C * L5B_A0->unk160);
        }
        if (L5B_A0->unk4->unk0->unk24 == 0.0f ||
            L5B_A0->unk4->unk0->unk4 > 5.0f) {
            L5B_A0->unk154 = 1;
            animSetFinished(D_807FBB40, 0, 0);
        }
        break;
    case 1:
        node = L5B_A0->unk4->unk0;
        if (node->unk24 == 0.0f) {
            if (animGetNodeByIndex(L5B_A0, 0)->unkC < 0xE) {
                node = L5B_A0->unk4->unk0;
            } else {
                goto promote;
            }
        }
        if (node->unk4 > 9.0f) {
promote:
            L5B_A0->unk154 = 2;
            if (L5B_A0->unk15F != 0 && actorSpawn(0x102, L5B_A0->unkF0) != 0) {
                if (L5B_A0->unk4->unk0->unk4 > 9.0f) {
                    func_80613C48(D_807FBB44, 0x4F9, 0, 0);
                    func_80614D00(D_807FBB44, L5B_A0->unk4->unk48, 0);
                }
                func_8067B238(D_807FBB44, L5B_A0, L5B_A0->unk4->unk38);
                L5B_A1->unkF0 = L5B_A0->unkF0;
                L5B_A1->unk4->unk34 = (f32)((f64)L5B_A0->unk4->unk34 + 0.02);
                L5B_A1->unk4->unk3C = (f32)((f64)L5B_A0->unk4->unk3C + 0.02);
                L5B_A1->unk15F = L5B_A0->unk15F - 1;
                L5B_A1->unk160 = L5B_A0->unk160;
            }
        }
        break;
    case 2:
        if (animIsPlaying(L5B_A0, 0) == 0) {
            L5B_A0->unk154 = 3;
            if (L5B_A0->unk168 != 0) {
                L5B_A0->unk60 &= ~4;
            } else {
                actorDespawn((Actor *)L5B_A0);
            }
        }
        break;
    case 3:
        L5B_A0->unkEE--;
        if (L5B_A0->unkEE == 0) {
            actorDespawn((Actor *)L5B_A0);
        }
        break;
    }
    if (L5B_A0->unkF0 != 0x6A && !(D_807FBB68 & 2)) {
        if ((L5B_A0->unk60 & 4) && (L5B_A0->unk60 & 0x10)) {
            sp50 = L5B_A0->unk80;
            actorGetNodePos((Actor *)L5B_A0, 1, &sp5C, &sp58, &sp54);
            sp58 += 50.0f;
            if (collisionCheckGroundAtPoint(sp5C, sp54, &sp58) != 0) {
                f32 dist;

                if (sp58 < sp50) {
                    dist = sp50 - sp58;
                } else {
                    dist = sp58 - sp50;
                }
                if (dist < 40.0f || !(L5B_A0->unk60 & 0x10)) {
                    L5B_A0->unk80 = sp58;
                }
            }
        }
    }
    if (L5B_A0->unk168 == 0 || L5B_A0->unk154 != 3) {
        if (func_8069EF50((s16)L5B_A0->unk7C, (s16)(L5B_A0->unk80 - 20.0f),
                          (s16)L5B_A0->unk84, sp67,
                          L5B_A0->unk4->unk34 * (f32)sp64) != 0 &&
            func_8069EF50((s16)L5B_A0->unk7C, (s16)(L5B_A0->unk80 - 20.0f),
                          (s16)L5B_A0->unk84, sp67,
                          L5B_A0->unk4->unk34 * (f32)(sp64 - 0x14)) == 0) {
            playerStateQueueCallback(0x2E, L5B_A0, 0);
        }
    }
    actorUpdateModelMatrix(L5B_A0, 0);
}

#undef L5B_A1

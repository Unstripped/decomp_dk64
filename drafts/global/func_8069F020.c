// func_8069F020 (src/global/A2F10.c): stage 6: frame 0x68 matches (fixed by removing unused node/dist locals and adjusting declaration order); beql branch likely in case 1 matched via ((a&&b)||c); remaining: only 2 extra insns in case 0 branch layout (608 vs 606 lines)
typedef struct ModelNodeView {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x16];
    /* 0x24 */ f32 unk24;
} ModelNodeView;

typedef struct ModelSubView {
    /* 0x00 */ ModelNodeView *unk0;
    /* 0x04 */ u8 pad4[0x30];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u8 pad40[0x8];
    /* 0x48 */ f32 unk48;
} ModelSubView;

typedef struct ActorView {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ ModelSubView *unk4;
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
} ActorView;

void animSetLoopLimit(void *, s32, s16);
void animSetSpeed(void *, s32, f32);
void animSetFinished(void *, s32, u8);
s32 animIsPlaying(void *, s32);
ModelNodeView *animGetNodeByIndex(void *, u32);
void lightSetFlags(u8);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8);
s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
s32 collisionCheckGroundAtPoint(f32, f32, void *);
void func_80613C48(Actor *, s16, f32, f32);
void scriptSetActorRampTarget(Actor *, f32, f32);
void func_8067B238(Actor *, Actor *, f32);
s32 playerStateQueueCallback(s16, void *, u8);
void actorUpdateModelMatrix(void *, s32);
extern u8 D_807444EC;
extern s32 D_807FBB68;

#define CUR_ACTOR ((ActorView *)D_807FBB40)
#define SPAWNED_ACTOR ((ActorView *)D_807FBB44)

void func_8069F020(void) {
    u8 sp67;
    u16 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    sp67 = (CUR_ACTOR->unkF0 == 0xBB) ? 0x28 : 0x23;
    sp64 = (CUR_ACTOR->unkF0 == 0x6A) ? 0x78 : 0x190;
    if (D_807444EC == 1) {
        actorDespawn((Actor *)D_807FBB40);
    }
    if (!(CUR_ACTOR->unk60 & 0x10)) {
        CUR_ACTOR->unk12A = 0x3E8;
        CUR_ACTOR->unk60 |= 0x400;
        animSetLoopLimit(D_807FBB40, 0, 1);
        animSetSpeed(D_807FBB40, 0, 0.5f);
        animSetFinished(D_807FBB40, 0, 1);
        CUR_ACTOR->unkEE = 0x3C;
    }
    if (CUR_ACTOR->unk168 != 0) {
        sp60 = 1.0f;
        if (CUR_ACTOR->unkEE < 0x1E) {
            sp60 = CUR_ACTOR->unkEE / 30.0;
        }
        lightSetFlags(1);
        lightAdd(CUR_ACTOR->unk7C, CUR_ACTOR->unk80, CUR_ACTOR->unk84, 0.0f, 0.0f, 0.0f,
                 CUR_ACTOR->unk4->unk34 * 300.0f, 0,
                 (u32)((f32)CUR_ACTOR->unk16A * sp60),
                 (u32)((f32)CUR_ACTOR->unk16B * sp60),
                 (u32)((f32)CUR_ACTOR->unk16C * sp60));
        CUR_ACTOR->unk4->unk34 = (f32)((f64)CUR_ACTOR->unk4->unk34 * CUR_ACTOR->unk160);
        CUR_ACTOR->unk4->unk3C = (f32)((f64)CUR_ACTOR->unk4->unk3C * CUR_ACTOR->unk160);
    }
    switch (CUR_ACTOR->unk154) {
    case 0:
        if (CUR_ACTOR->unk168 == 0) {
            CUR_ACTOR->unk4->unk34 =
                (f32)((f64)CUR_ACTOR->unk4->unk34 * CUR_ACTOR->unk160);
            CUR_ACTOR->unk4->unk3C =
                (f32)((f64)CUR_ACTOR->unk4->unk3C * CUR_ACTOR->unk160);
        }
        if (CUR_ACTOR->unk4->unk0->unk24 == 0.0f ||
            CUR_ACTOR->unk4->unk0->unk4 > 5.0f) {
            CUR_ACTOR->unk154 = 1;
            animSetFinished(D_807FBB40, 0, 0);
        }
        break;
    case 1:
        if ((CUR_ACTOR->unk4->unk0->unk24 == 0.0f && animGetNodeByIndex(CUR_ACTOR, 0)->unkC >= 0xE) ||
            CUR_ACTOR->unk4->unk0->unk4 > 9.0f) {
            CUR_ACTOR->unk154 = 2;
            if (CUR_ACTOR->unk15F != 0 && actorSpawn(0x102, CUR_ACTOR->unkF0) != 0) {
                if (CUR_ACTOR->unk4->unk0->unk4 > 9.0f) {
                    func_80613C48(D_807FBB44, 0x4F9, 0.0f, 0.0f);
                    scriptSetActorRampTarget(D_807FBB44, CUR_ACTOR->unk4->unk48, 0.0f);
                }
                func_8067B238(D_807FBB44, CUR_ACTOR, CUR_ACTOR->unk4->unk38);
                SPAWNED_ACTOR->unkF0 = CUR_ACTOR->unkF0;
                SPAWNED_ACTOR->unk4->unk34 = (f32)((f64)CUR_ACTOR->unk4->unk34 + 0.02);
                SPAWNED_ACTOR->unk4->unk3C = (f32)((f64)CUR_ACTOR->unk4->unk3C + 0.02);
                SPAWNED_ACTOR->unk15F = CUR_ACTOR->unk15F - 1;
                SPAWNED_ACTOR->unk160 = CUR_ACTOR->unk160;
            }
        }
        break;
    case 2:
        if (animIsPlaying(CUR_ACTOR, 0) == 0) {
            CUR_ACTOR->unk154 = 3;
            if (CUR_ACTOR->unk168 != 0) {
                CUR_ACTOR->unk60 &= ~4;
            } else {
                actorDespawn((Actor *)CUR_ACTOR);
            }
        }
        break;
    case 3:
        CUR_ACTOR->unkEE--;
        if (CUR_ACTOR->unkEE == 0) {
            actorDespawn((Actor *)CUR_ACTOR);
        }
        break;
    }
    if (CUR_ACTOR->unkF0 != 0x6A && !(D_807FBB68 & 2)) {
        if ((CUR_ACTOR->unk60 & 4) && (CUR_ACTOR->unk60 & 0x10)) {
            sp50 = CUR_ACTOR->unk80;
            actorGetNodePos((Actor *)CUR_ACTOR, 1, &sp5C, &sp58, &sp54);
            sp58 += 50.0f;
            if (collisionCheckGroundAtPoint(sp5C, sp54, &sp58) != 0) {
                if (((sp58 < sp50) ? (sp50 - sp58) : (sp58 - sp50)) < 40.0f || !(CUR_ACTOR->unk60 & 0x10)) {
                    CUR_ACTOR->unk80 = sp58;
                }
            }
        }
    }
    if (CUR_ACTOR->unk168 == 0 || CUR_ACTOR->unk154 != 3) {
        if (actorIsTargetInCylinder((s16)CUR_ACTOR->unk7C, (s16)(CUR_ACTOR->unk80 - 20.0f),
                          (s16)CUR_ACTOR->unk84, sp67,
                          CUR_ACTOR->unk4->unk34 * (f32)sp64) != 0 &&
            actorIsTargetInCylinder((s16)CUR_ACTOR->unk7C, (s16)(CUR_ACTOR->unk80 - 20.0f),
                          (s16)CUR_ACTOR->unk84, sp67,
                          CUR_ACTOR->unk4->unk34 * (f32)(sp64 - 0x14)) == 0) {
            playerStateQueueCallback(0x2E, CUR_ACTOR, 0);
        }
    }
    actorUpdateModelMatrix(CUR_ACTOR, 0);
}

#undef SPAWNED_ACTOR

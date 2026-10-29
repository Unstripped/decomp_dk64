// func_8069346C (src/global/936B0.c): stage 5: text same size/frame -104 matched (stale callee names fixed: sfxPlayFromActorWithAltitudeCheck, camStartShakeFromPoint, actorAppendModelNode/SubNode, actorApplyVelocity, actorSpawnSparkleBurst). Locals i (temp_v0+loops)/var_a0(also chain byte) split from flag; remaining diff only v0/v1 vs t-reg temps (angle-wrap temp should be v1)
typedef struct M93J_ActorExtra {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[0x13 - 0x05];
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 pad14[0x1C - 0x14];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 unk20;
} M93J_ActorExtra;

typedef struct M93J_Actor124 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} M93J_Actor124;

typedef struct M93J_Actor {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ u16 unk68;
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ u8 pad6E[0x7C - 0x6E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xB8 - 0x88];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0xEE - 0xC4];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[4];
    /* 0xF4 */ s16 unkF4;
    /* 0xF6 */ s16 unkF6;
    /* 0xF8 */ u8 padF8[2];
    /* 0xFA */ s16 unkFA;
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 unkFD;
    /* 0xFE */ u8 padFE[0x124 - 0xFE];
    /* 0x124 */ M93J_Actor124 *unk124;
    /* 0x128 */ u8 pad128[0x144 - 0x128];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x154 - 0x145];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x16E - 0x155];
    /* 0x16E */ u8 unk16E;
    /* 0x16F */ u8 unk16F;
    /* 0x170 */ u8 pad170[4];
    /* 0x174 */ M93J_ActorExtra *unk174;
} M93J_Actor;

#define M93J_ACTOR ((M93J_Actor *)D_807FBB40)

extern u8 D_80720268;
extern s16 D_80750348;
extern s16 D_8075034C;
extern s8 D_80029FA0;
s32 func_806725A0(Actor *, s16);
s16 func_80672A70(s16, s16);

void func_8069346C(void) {
    M93J_ActorExtra *sp64;
    s32 var_s0;
    f32 sp5C;
    f32 sp3C;
    s32 i;
    s32 var_a0;

    sp64 = M93J_ACTOR->unk174;
    var_s0 = 0;
    sp5C = M93J_ACTOR->unk124->unkC * 2.5f;
    if (!(M93J_ACTOR->unk60 & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF4, 0xFF, 0x7F, 5);
        M93J_ACTOR->unk6A &= 0xFFFE;
        M93J_ACTOR->unkEE = (s16)((M93J_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93J_ACTOR->unkB8 = (f32)(((f64)(M93J_ACTOR->unk124->unk4 / (f32)4)) * 2.6);
        M93J_ACTOR->unkB8 *= sp5C;
        M93J_ACTOR->unkC0 = M93J_ACTOR->unk124->unk8;
        M93J_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, sp5C * 60.0);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, sp5C * 50.0, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        sp64->unk13 = (u8)(u32)M93J_ACTOR->unk124->unk10;
        func_807149FC(-1);
        func_807149B8(1);
        sp64->unk0 = D_8076A068;
        if (sp64->unk13 >= 0xCA) {
            func_80714950(0xA);
            func_8071498C(func_8071A8B0);
        }
        if (sp64->unk13 >= 0xCB) {
            M93J_ACTOR->unkC0 = 250.0f * sp5C;
            sp64->unk0 -= D_80750348 - D_8075034C;
        } else {
            M93J_ACTOR->unkC0 = 200.0f * sp5C;
        }
        func_80714C08(&D_80720268, M93J_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp64->unk4 = 0;
        M93J_ACTOR->unk60 |= 0x01080000;
        M93J_ACTOR->unkFA = 0x2328;
        var_a0 = (u32)(60.0f * sp5C);
        M93J_ACTOR->unk16E = var_a0;
        M93J_ACTOR->unk16F = var_a0;
        sp64->unk1C = 0;
        sp64->unk20 = 0;
    }
    if ((u32)(sp64->unk0 + 5) < D_8076A068) {
        M93J_ACTOR->unk60 &= ~0x00080000;
    }
    var_a0 = 2;
    if (D_807FC928 >= 2) {
        var_a0 = 3;
    }
    func_80690C60(var_a0, D_807FBB40, NULL, 1);
    func_8067ACB4(D_807FBB40);
    if (M93J_ACTOR->unkFC != 0 && func_806725A0(D_807FBB40, M93J_ACTOR->unkEE) == 0) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF5, 0xFF, 0x7F, 0x1E);
        i = func_80672A70(M93J_ACTOR->unkF4, M93J_ACTOR->unkF6);
        M93J_ACTOR->unkEE = i + (i - ((M93J_ACTOR->unkEE + 0x800) & 0xFFF));
        if (M93J_ACTOR->unkEE < 0) {
            M93J_ACTOR->unkEE += 0xFFF;
        }
        if (M93J_ACTOR->unkEE >= 0x1000) {
            M93J_ACTOR->unkEE -= 0xFFF;
        }
        if (func_806725A0(D_807FBB40, M93J_ACTOR->unkEE) == 0) {
            var_s0 = 1;
        }
    }
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    M93J_ACTOR->unkC0 += D_807502E4 * sp5C;
    if (M93J_ACTOR->unkC0 < (f32)D_807502D0) {
        M93J_ACTOR->unkC0 = (f32)D_807502D0;
    }
    if ((M93J_ACTOR->unk6A & 1) && !(M93J_ACTOR->unk6C & 1)) {
        switch (sp64->unk4) {
        case 0:
            M93J_ACTOR->unkC0 = 200.0f * sp5C;
            break;
        case 1:
            sp3C = 100.0f * sp5C;
            M93J_ACTOR->unkC0 = 150.0f * sp5C;
            func_8066EB40(D_807FBB40, sp3C);
            actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, sp3C, -1);
            break;
        case 2:
            sp3C = 150.0f * sp5C;
            M93J_ACTOR->unkC0 = 100.0f * sp5C;
            func_8066EB40(D_807FBB40, sp3C);
            actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, sp3C, -1);
            break;
        case 3:
            M93J_ACTOR->unkC0 = 80.0f * sp5C;
            break;
        }
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF5, 0xFF, 0x7F, 0x1E);
        sp64->unk4++;
        M93J_ACTOR->unkB8 = ((f64)M93J_ACTOR->unkB8 / 3.0) * 2.5;
    }
    if ((M93J_ACTOR->unk6A & 1) && (M93J_ACTOR->unk6C & 1)) {
        sp64->unk20++;
    } else {
        sp64->unk20 = 0;
    }
    if (sp64->unk20 == 4) {
        D_807FBB70.unk15 = 1;
    }
    if (M93J_ACTOR->unk124->unk14 != 0.0f && (u32)(sp64->unk0 + 1) < D_8076A068) {
        D_807FBB70.unk15 = 1;
    }
    if ((M93J_ACTOR->unk64 & 0x100) || var_s0 != 0) {
        D_807FBB70.unk15 = 1;
    }
    if ((((M93J_ACTOR->unk6A & 1) && sp64->unk4 == 4) || D_807FBB70.unk15 != 0) && M93J_ACTOR->unk154 == 0) {
        sp3C = 250.0f * sp5C;
        if (sp64->unk13 != 0xCA) {
            func_807149B8(1);
            func_80714950(0x100D2);
            func_8071498C(func_8071A8B0);
            func_80714CC0(&D_80720120, 2.0f, D_807FBB40->unk7C, D_807FBB40->unk80 + 22.0f, D_807FBB40->unk84);
            actorSpawnSparkleBurst();
            if (D_80750AD0 == 0) {
                i = 0;
                do {
                    func_807149B8(1);
                    func_80714950(0x0B010000 + i);
                    func_8071498C(func_8071ABDC);
                    func_80714CC0(&D_807200EC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                    i++;
                } while (i != 12);
            }
        }
        i = 0;
        if (D_807FC928 > 0) {
            do {
                camStartShakeFromPoint(D_807FC924[i].actor->unk174->unk104, 7, 0x16, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 200.0f, 400.0f);
                i++;
            } while (i < D_807FC928);
        }
        func_8066EB40(D_807FBB40, sp3C);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, sp3C, -1);
        M93J_ACTOR->unk154 = 1;
    } else if (M93J_ACTOR->unk154 != 0) {
        if (M93J_ACTOR->unk154++ == 2) {
            if (sp64->unk13 != 0xCA) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF6, 0xFF, 0x7F, 0x1E);
            }
            actorDespawn(D_807FBB40);
            D_80029FA0--;
        }
    }
    if ((u32)(sp64->unk0 + D_80750348) < D_8076A068) {
        actorDespawn(D_807FBB40);
        D_80029FA0--;
    }
}

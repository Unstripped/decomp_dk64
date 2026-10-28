#include "common.h"

typedef struct BossC_A7A0_178 {
    s32 unk0;
    u8 pad4[0x10];
    u8 unk14;
} BossC_A7A0_178;

typedef struct BossC_A7A0_Actor {
    char pad[0x58];
    s32 unk58;
    s32 pad5C;
    s32 unk60;
    char pad64[0xB8];
    struct BossC_A7A0_Actor *unk11C;
    char pad120[8];
    s16 unk128;
    char pad12A[0x1A];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x12];
    s16 unk168;
    char pad16A[0xE];
    BossC_A7A0_178 *unk178;
} BossC_A7A0_Actor;

typedef struct BossC_A7A0_BB70 {
    char pad[0x15];
    u8 unk15;
    char pad16[0x1E6];
    BossC_A7A0_Actor *unk1FC;
    u8 unk200;
} BossC_A7A0_BB70;

extern BossC_A7A0_BB70 D_807FBB70;
extern BossC_A7A0_Actor *D_807FBB40;
extern BossC_A7A0_Actor *D_807FBB4C;
void actorDespawn(BossC_A7A0_Actor *);
void actorUpdateModelMatrix(BossC_A7A0_Actor *, s32);

typedef struct {
    BossC_A7A0_Actor *actor;
    s32 pad;
} BossC_A7A0_Entry;

extern BossC_A7A0_Entry gActiveActors[];
extern u16 gActiveActorCount;

void bossResetMinions(BossC_A7A0_Actor *arg0) {
    s16 i;
    BossC_A7A0_Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if ((arg0 == NULL || actor != arg0) && actor->unk58 == 0xDE) {
            actor->unk60 &= ~0x8000;
            actor->unk154 = 1;
            actor->unk155 = 0;
        }
    }
}

void bossPhaseTick(void) {
    BossC_A7A0_Actor *other;
    s16 timer;

    if (!(D_807FBB40->unk60 & 0x10)) {
        bossResetMinions(D_807FBB40);
        D_807FBB40->unk168 = 0x258;
        D_807FBB40->unk144 = 2;
    }
    if (D_807FBB4C->unk154 != 0x67) {
        timer = D_807FBB40->unk168;
        if (timer != 0) {
            D_807FBB40->unk168 = timer - 1;
        } else {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155 = 0;
        }
    }
    if (((D_807FBB70.unk15 != 0) || (D_807FBB70.unk200 == 9)) &&
        ((other = D_807FBB70.unk1FC)->unk154 == 0x2B) &&
        (other->unk155 == 3)) {
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unk11C->unk154 = 0x64;
        D_807FBB40->unk11C->unk155 = 0;
        other->unk155 = 0;
        other->unk154 = 0x31;
    }
    if (D_807FBB40->unk154 == 1) {
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk128 -= 10;
        if (D_807FBB40->unk128 < 0) {
            actorDespawn(D_807FBB40);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


void actorScriptStart(BossC_A7A0_Actor *, s32);
void func_80614D90(BossC_A7A0_Actor *);
void func_80613CA8(s32, s16, f32, f32);

void func_8002E9B8(arg0, arg1)
s32 arg0;
s16 arg1;
{
    BossC_A7A0_178 *sp1C = D_807FBB40->unk178;

    actorScriptStart(D_807FBB40, arg0);
    func_80614D90(D_807FBB40);
    func_80613CA8(sp1C->unk0, arg1, 0.0f, 6.0f);
}

typedef struct BossC_A7A0_DC9C {
    char pad[0xC];
    u8 unkC;
} BossC_A7A0_DC9C;

extern BossC_A7A0_DC9C *D_807FDC9C;
void actorSetTargetSpeed(BossC_A7A0_Actor *, s32);

void func_8002EA14(void) {
    BossC_A7A0_178 *sp1C = D_807FBB40->unk178;

    func_8002E9B8(0x406, 0x674);
    actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC + (sp1C->unk14 * 10) + 15);
}

typedef struct BsA7_178 {
    void *unk0;
    char pad4[0x10];
    u8 unk14;
    u8 unk15;
} BsA7_178;

typedef struct BsA7_Sub4 {
    char pad0[0x64];
    u16 unk64;
} BsA7_Sub4;

typedef struct BsA7_Sub140 {
    char pad0[0xC];
    s32 unkC;
} BsA7_Sub140;

typedef struct BsA7_Actor {
    char pad0[4];
    BsA7_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x60];
    f32 unkC4;
    char padC8[4];
    u8 unkCC;
    char padCD[0x73];
    BsA7_Sub140 *unk140;
    char pad144[2];
    s16 unk146;
    char pad148[0xC];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    BsA7_178 *unk178;
} BsA7_Actor;

typedef struct BsA7_BB70 {
    char pad[0x1B];
    u8 unk1B;
    char pad1C[0x200 - 0x1C];
    u8 unk200;
} BsA7_BB70;

typedef struct BsA7_DC90 {
    char pad[0x1A];
    u16 unk1A;
} BsA7_DC90;

typedef struct BsA7_DC94 {
    char pad[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
} BsA7_DC94;

typedef struct BsA7_DC9C {
    char pad[0xD];
    u8 unkD;
} BsA7_DC9C;

extern u8 *D_80035A80[];
extern BsA7_DC90 *D_807FDC90;
extern BsA7_DC94 *D_807FDC94;
void behaviourFrameBegin(void);
void func_80028878(u8 *);
void func_80724CA4(s32, s32);
void bossAttachActor(void);
s32 camStartPath(void *, s32, s32);
s32 camIsPlayingPath(s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void playerStateQueueCallback(s32, void *, s32);
void func_8066EB40(void *, f32);
void actorOrNodeFlags(void *, s32, s32);
s32 currentActorTestClearFlag(void);
void func_805FF158(s32);
void func_805FF378(s32, s32);
void func_80027BA8(u8 *, s32, f32);
void func_80614D00(void *, f32, f32);
void func_8072A450(void);
s32 func_8072881C(s32, void *);

#define ACTOR40 ((BsA7_Actor *)D_807FBB40)
#define ACTOR4C ((BsA7_Actor *)D_807FBB4C)
#define BB70 (*(BsA7_BB70 *)&D_807FBB70)
#define DC9C ((BsA7_DC9C *)D_807FDC9C)

void func_8002EA7C(void) {
    BsA7_178 *sp178;
    u8 *sp28;

    sp178 = (BsA7_178 *)D_807FBB40->unk178;
    sp28 = D_80035A80[sp178->unk14];
    behaviourFrameBegin();
    func_80028878(sp28);
    if (!(ACTOR40->unk60 & 0x10)) {
        ACTOR40->unk146 = 1;
        ACTOR40->unk154 = 0x1E;
        ACTOR40->unk155 = 0;
        ACTOR40->unkCC = 1;
        func_80724CA4(2, 1);
        bossAttachActor();
        ACTOR40->unkC4 = 0.0f;
    }
    if ((ACTOR4C->unk154 == 0x48) && !(D_807FDC90->unk1A & 0x8000)) {
        camStartPath(ACTOR40, 0, 1);
        D_807FDC90->unk1A |= 0x8000;
    }
    if ((camIsPlayingPath(0) == 0) && (camIsPlayingPath(1) == 0) && ((ACTOR4C->unk154 != 0x67) || (ACTOR40->unk154 != 0x42))) {
        switch (ACTOR40->unk154) {
        case 0x2B:
            switch (ACTOR40->unk155) {
            case 0:
                actorSetTargetSpeed(D_807FBB40, 0);
                camStartPath(ACTOR4C, 9, 1);
                func_8002E9B8(0x3F5, 0x679);
                ACTOR40->unk155++;
                break;
            case 2:
                actorSetTargetSpeed(D_807FBB40, DC9C->unkD);
                func_8002E9B8(0x3F4, 0x678);
                ACTOR40->unk155++;
                break;
            case 3:
                if (BB70.unk1B != 0) {
                    ACTOR40->unk154 = 0x31;
                    ACTOR40->unk155 = 0;
                } else if (BB70.unk200 == 2) {
                    bossResetMinions(NULL);
                    ACTOR40->unk154 = 0x2C;
                    ACTOR40->unk155 = 0;
                }
                actorMoveWithinZone(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
                break;
            }
            break;
        case 0x2C:
            if (ACTOR40->unk155 == 0) {
                playerStateQueueCallback(0x36, ACTOR40, 0);
                func_8002EA14();
                ACTOR40->unk154 = 0x42;
                ACTOR40->unk155 = 0;
            }
            break;
        case 0x1E:
            sp178->unk14 = 0;
            sp178->unk15 = 0;
            ACTOR40->unk154 = sp28[sp178->unk15++];
            ACTOR40->unk155 = 0;
            break;
        case 0:
            switch (ACTOR40->unk155) {
            case 0:
                func_8002E9B8(0x3F5, 0x679);
                ACTOR40->unk155++;
                break;
            case 2:
                func_8002EA14();
                ACTOR40->unk154 = sp28[sp178->unk15++];
                ACTOR40->unk155 = 0;
                func_8066EB40(ACTOR4C, (f32)(ACTOR4C->unk140->unkC * 2));
                actorOrNodeFlags(ACTOR4C, 6, 1);
                actorOrNodeFlags(ACTOR4C, 7, 1);
                actorOrNodeFlags(ACTOR4C, 8, 1);
                actorOrNodeFlags(ACTOR4C, 9, 1);
                actorOrNodeFlags(ACTOR4C, 0xA, 1);
                actorOrNodeFlags(ACTOR4C, 0xB, 1);
                break;
            }
            break;
        case 0x31:
            switch (ACTOR40->unk155) {
            case 0:
                if (sp178->unk14 == 3) {
                    ACTOR40->unk154 = 0x37;
                    ACTOR40->unk155 = 0;
                } else {
                    actorScriptStart(D_807FBB40, 0x3F2);
                    actorScriptStart(sp178->unk0, 0x3F1);
                    actorSetTargetSpeed(D_807FBB40, 0);
                    ACTOR40->unk155++;
                }
                break;
            case 1:
                actorMoveWithinZone(0, 0.0f, 0.0f, 0x310, 0.0f);
                break;
            case 2:
                bossResetMinions(NULL);
                func_8002EA14();
                sp178->unk15 = 0;
                sp178->unk14++;
                {
                    u8 *tbl = D_80035A80[sp178->unk14];
                    ACTOR40->unk154 = tbl[sp178->unk15++];
                }
                ACTOR40->unk155 = 0;
                break;
            }
            break;
        case 0x37:
            switch (ACTOR40->unk155) {
            case 0:
                actorDespawn(sp178->unk0);
                actorScriptStart(D_807FBB40, 0);
                camStartPath(ACTOR40, 5, 1);
                ACTOR40->unk155++;
                break;
            case 1:
                if (currentActorTestClearFlag() != 0) {
                    func_805FF158(0);
                    func_805FF378(0xCE, 0);
                    ACTOR40->unk155++;
                }
                break;
            }
            break;
        default:
            func_80027BA8(sp28, 0x10, 0.0f);
            break;
        }
    } else if (ACTOR40->unk4->unk64 == 0x406) {
        func_80614D00(ACTOR40, 0.0f, 0.0f);
    }
    func_8072A450();
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036840.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036850.s")

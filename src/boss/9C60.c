#include "common.h"

typedef struct BossC_9C60_Sub0 {
    char pad[0x10];
    s16 unk10;
    char pad12[0x12];
    f32 unk24;
} BossC_9C60_Sub0;

typedef struct BossC_9C60_Sub4 {
    BossC_9C60_Sub0 *unk0;
    char pad4[0x18];
    void *unk1C;
    char pad20[0x18];
    f32 unk38;
    char pad3C[0xC];
    f32 unk48;
} BossC_9C60_Sub4;

typedef struct BossC_9C60_Actor {
    char pad[4];
    BossC_9C60_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[0x10];
    u8 unkCC;
    char padCD[0x19];
    s16 unkE6;
    char padE8[0x34];
    struct BossC_9C60_Actor *unk11C;
    char pad120[0x26];
    s16 unk146;
    char pad148[0xC];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    void *unk178;
} BossC_9C60_Actor;

extern BossC_9C60_Actor *D_807FBB40;
extern BossC_9C60_Actor *D_807FBB44;

void actorSpawn(s32, s32);
void func_8067B238(BossC_9C60_Actor *, BossC_9C60_Actor *, f32);
void actorDespawn(void *);
void func_806319C4(BossC_9C60_Actor *, s32);
void bossAttachActor(void) {
    BossC_9C60_Actor **sp1C = D_807FBB40->unk178;

    actorSpawn(0xDD, 0xE3);
    D_807FBB44->unk60 |= 0x400;
    D_807FBB44->unk11C = D_807FBB40;
    *sp1C = D_807FBB44;
    func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
}

void bossUpdateAttachment(void) {
    func_8067B238(D_807FBB40, D_807FBB40->unk11C, D_807FBB40->unk4->unk38);
    D_807FBB40->unk4->unk48 = D_807FBB40->unk11C->unk4->unk48;
    if (D_807FBB40->unk4->unk0->unk10 == 0x675 && D_807FBB40->unk4->unk0->unk24 == 0.0f) {
        actorDespawn(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct BossC_9C60_Target {
    char pad[0x58];
    s32 unk58;
} BossC_9C60_Target;

typedef struct {
    BossC_9C60_Target *actor;
    s32 pad;
} BossC_9C60_Entry;

extern BossC_9C60_Entry D_807FB930[];
extern u16 D_807FBB34;

void actorDespawn(void *);

void bossDespawnEntities(void) {
    s16 i;
    BossC_9C60_Target *actor;

    for (i = 0; i < D_807FBB34; i++) {
        actor = D_807FB930[i].actor;
        if (actor->unk58 == 0xAA) {
            actorDespawn(actor);
        }
    }
}

typedef struct Boss2F_9C60_178 {
    void *unk0;
    char pad4[0x10];
    u8 unk14;
    u8 unk15;
    char pad16[2];
    u8 unk18;
    u8 unk19;
} Boss2F_9C60_178;

typedef struct Boss2F_9C60_BB4C {
    char pad[0x6A];
    u16 unk6A;
} Boss2F_9C60_BB4C;

typedef struct Boss2F_9C60_DC90 {
    char pad[0x28];
    u8 unk28;
    char pad29[3];
    s16 unk2C;
} Boss2F_9C60_DC90;

typedef struct Boss2F_9C60_DC9C {
    char pad[0xC];
    u8 unkC;
} Boss2F_9C60_DC9C;

typedef struct Boss2F_9C60_DCA0_Sub {
    char pad[0x28];
    s16 unk28;
    char pad2A[2];
    s16 unk2C;
} Boss2F_9C60_DCA0_Sub;
typedef struct Boss2F_9C60_DCA0 {
    char pad[0x14];
    Boss2F_9C60_DCA0_Sub *unk14;
} Boss2F_9C60_DCA0;

typedef struct Boss2F_9C60_Sub1C {
    char pad[2];
    u16 unk2;
} Boss2F_9C60_Sub1C;

extern u8 *D_80035A60[];
extern s32 D_807F5D10;
extern Boss2F_9C60_BB4C *D_807FBB4C;
extern Boss2F_9C60_DC90 *D_807FDC90;
extern Boss2F_9C60_DC9C *D_807FDC9C;
extern Boss2F_9C60_DCA0 *D_807FDCA0;

void func_80027BA8(u8 *, s32, f32);
void func_80028878(u8 *);
void func_805FF158(s32);
void func_805FF378(s32, s32);
void func_80613C48(void *, s32, f32, f32);
void func_80614D90(BossC_9C60_Actor *);
void func_80614EBC(BossC_9C60_Actor *, s32);
s32 func_8061CB50(void);
void func_8061CC40(BossC_9C60_Actor *, s32, s32);
void func_8061F0B0(s32, s32, s32);
void func_80626110(s32, s32, s32);
s32 func_80629148(void);
void func_8063DA40(s16, s32);
s16 func_80665DE0(f32, f32, f32, f32);
void projectileGetTargetCoords(BossC_9C60_Actor *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, BossC_9C60_Actor *);
void func_80724CA4(s32, s32);
void func_80724E48(s32);
s32 func_8072881C(s32, void *);
void func_80729B00(void);
void func_8072A450(void);
void func_8072B324(BossC_9C60_Actor *, s32);
void func_8072E1A4(s32, void *);

void func_8002DE04(void) {
    Boss2F_9C60_178 *sp3C;
    u8 *sp38;
    s32 pad34;
    f32 sp30;
    u8 action;

    sp3C = D_807FBB40->unk178;
    sp38 = D_80035A60[sp3C->unk14];
    sp30 = (D_807FBB4C->unk6A & 1) ? 0.7 : 1.0;
    func_80729B00();
    func_80028878(sp38);
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80626110(D_807F5D10, 0, 0);
        D_807FBB40->unk146 = 5;
        D_807FBB40->unk154 = 0x1E;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unkCC = 1;
        func_80614EBC(D_807FBB40, 0x3E3);
        func_80724CA4(2, 1);
    }
    if (D_807FBB40->unk154 != 0x28) {
        func_80724E48(5);
    }
    switch (D_807FBB40->unk154) {
    case 0x1E:
        sp3C->unk14 = 0;
        sp3C->unk15 = 0;
        D_807FBB40->unk154 = sp38[sp3C->unk15++];
        D_807FBB40->unk155 = 0;
        D_807FBB40->unkB8 = D_807FDC9C->unkC;
        break;
    case 0x27:
        func_80614EBC(D_807FBB40, 0x3E1);
        D_807FBB40->unk154 = sp38[sp3C->unk15++];
        D_807FBB40->unk155 = 0;
        break;
    case 0x2C:
        switch (D_807FBB40->unk155) {
        case 0:
            D_807FDC90->unk2C = 0x14;
            D_807FBB40->unk155++;
            break;
        case 1:
            func_8072E1A4(0xA, D_807FBB4C);
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                func_8063DA40((sp3C->unk14 * 2) + 8, 0xA);
                func_8063DA40((sp3C->unk14 * 2) + 9, 0xA);
                D_807FBB40->unk154 = sp38[sp3C->unk15++];
                D_807FBB40->unk155 = 0;
            }
            break;
        }
        break;
    case 0:
        switch (D_807FBB40->unk155) {
        case 0:
            func_80614EBC(D_807FBB40, 0x3EA);
            D_807FBB40->unk155++;
            break;
        case 1:
            func_8072E1A4(0xA, D_807FBB4C);
            break;
        case 2:
            D_807FBB40->unk154 = sp38[sp3C->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x28:
        switch (D_807FBB40->unk155) {
        case 0:
            sp3C->unk18 = sp38[sp3C->unk15++];
            sp3C->unk19 = sp38[sp3C->unk15++];
            D_807FBB40->unk155++;
            /* fallthrough */
        case 1:
            if (func_8061CB50() == 0) {
                D_807FDC90->unk2C = sp3C->unk18;
                func_80614EBC(D_807FBB40, 0x3EF);
                D_807FBB40->unk155++;
            }
            break;
        case 3:
            D_807FBB40->unk146 = 6;
            projectileGetTargetCoords(D_807FBB40, 4);
            projectileSpawnNodeEntry(0xAA, 1, D_807FBB40->unk4->unk38, 0, (f32)sp3C->unk19 * sp30, 0.0f, D_807FBB40);
            D_807FBB40->unk155++;
            break;
        case 5:
            func_80614EBC(D_807FBB40, 0x3F0);
            D_807FBB40->unk155++;
            break;
        case 7:
            D_807FBB40->unk146 = 5;
            D_807FBB40->unk155++;
            /* fallthrough */
        case 8:
            func_80724E48(0);
            if (((Boss2F_9C60_Sub1C *)D_807FBB40->unk4->unk1C)->unk2 < 0x7FFF) {
                ((Boss2F_9C60_Sub1C *)D_807FBB40->unk4->unk1C)->unk2 = 0xFFFF;
            }
            func_8072E1A4(0xA, D_807FBB4C);
            if (D_807FDC90->unk2C != 0) {
                if ((D_807FBB4C->unk6A & 1) && (D_807FDC90->unk2C >= 0xB)) {
                    D_807FDC90->unk2C = 0xA;
                }
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk154 = sp38[sp3C->unk15++];
                D_807FBB40->unk155 = 0;
            }
            break;
        }
        break;
    case 0x29:
        switch (D_807FBB40->unk155) {
        case 0:
            D_807FBB40->unk146 = 5;
            func_80614EBC(D_807FBB40, sp3C->unk14 ? 0x409 : 0x408);
            func_80614D90(D_807FBB40);
            func_80613C48(sp3C->unk0, 0x675, 0.0f, 0.0f);
            D_807FBB40->unk155++;
            break;
        case 2:
            D_807FBB40->unk154 = sp38[sp3C->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x31:
        switch (D_807FBB40->unk155) {
        case 0:
            D_807FBB40->unk146 = 5;
            func_80614EBC(D_807FBB40, 0);
            bossDespawnEntities();
            func_8061CC40(D_807FBB40, 1, 1);
            D_807FBB40->unk155++;
            break;
        case 1:
            if (func_80629148() != 0) {
                func_80614EBC(D_807FBB40, 0x403);
                D_807FBB40->unk155++;
            }
            break;
        case 2:
            if (func_80629148() != 0) {
                func_8061F0B0(D_807F5D10, 5, 0x14);
                if (sp3C->unk14 == 3) {
                    D_807FBB40->unk154 = 0x37;
                    D_807FBB40->unk155 = 0;
                } else {
                    bossAttachActor();
                    D_807FBB40->unk146 = 1;
                    func_80614EBC(D_807FBB40, 0x404);
                    func_80614D90(D_807FBB40);
                    func_80613C48(sp3C->unk0, 0x673, 0.0f, 0.0f);
                    D_807FBB40->unk155++;
                }
            }
            break;
        case 3:
            if (func_80629148() != 0) {
                D_807FBB40->unk155++;
            }
            break;
        case 4:
            func_8072B324(D_807FBB40, D_807FDC9C->unkC);
            sp3C->unk15 = 0;
            sp3C->unk14++;
            sp38 = D_80035A60[sp3C->unk14];
            func_80614EBC(D_807FBB40, 0x406);
            func_80614D90(D_807FBB40);
            func_80613C48(sp3C->unk0, 0x674, 0.0f, 0.0f);
            D_807FBB40->unk154 = sp38[sp3C->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (D_807FBB40->unk155) {
        case 0:
            D_807FBB40->unkE6 = func_80665DE0(D_807FDCA0->unk14->unk28, D_807FDCA0->unk14->unk2C, D_807FBB40->unk7C, D_807FBB40->unk84);
            func_80614EBC(D_807FBB40, 0);
            func_8061CC40(D_807FBB40, 2, 1);
            D_807FBB40->unk155++;
            break;
        case 1:
            if (func_80629148() != 0) {
                func_805FF158(0);
                func_805FF378(0xCD, 0);
                D_807FBB40->unk155++;
            }
            break;
        }
        break;
    default:
        func_80027BA8(sp38, 0x10, 0.0f);
        break;
    }
    func_8072A450();
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036750.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036768.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036774.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036780.s")

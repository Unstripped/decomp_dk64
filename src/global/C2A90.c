#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern Struct807FD580 *D_807FD580;

#pragma GLOBAL_ASM("asm/global/nonmatchings/C2A90/func_806BDD90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C2A90/func_806BDEC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C2A90/func_806BE09C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C2A90/func_806BE674.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C2A90/func_806BE6F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C2A90/func_806BE8BC.s")

typedef struct LgBF218Sub124 {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 unk8;
} LgBF218Sub124;

typedef struct LgBF218Node {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} LgBF218Node;

typedef struct LgBF218Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x52];
    /* 0x05A */ s16 unk5A;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x34];
    /* 0x11C */ struct LgBF218Actor *unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ LgBF218Sub124 *unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[8];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x20];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[8];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0x15];
    /* 0x174 */ LgBF218Node *unk174;
} LgBF218Actor;

typedef struct LgBF218Sub14 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
} LgBF218Sub14;

typedef struct LgBF218Sub4 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ LgBF218Sub14 *unk14;
} LgBF218Sub4;

typedef struct LgBF218Global {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ LgBF218Sub4 *unk4;
} LgBF218Global;

extern LgBF218Global *D_80755690;
#define LA ((LgBF218Actor *)D_807FBB40)
#define LB ((LgBF218Actor *)D_807FBB4C)

void actorDespawn(void *);
void actorClearMovementFlags(void *);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);
void func_80614EBC(void *, s32);
void func_8061CB08(void);
s32 func_8061CC40(void *, s32, s32);
void func_8063DA40(s32, s32);
void func_8067B238(void *, void *, f32);
void func_8068A2FC(void *);
void func_8070D8C0(void *, s32, s32);
void func_8070E8DC(s32);
void func_80724B5C(s32, s32, void *, void *, void *);
s32 func_80726DC0(s32);
s32 func_8073110C(s32, s32);
void func_8073129C(s32, s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void *memcpy(void *, const void *, u32);

void func_806BF218(void) {
    LgBF218Node *node;
    LgBF218Actor *other;
    s32 kind;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 spawn[3];
    f32 ex;
    f32 ey;
    f32 ez;

    if (!(LA->unk60 & 0x10)) {
        LA->unk15E = 0x2D;
    }
    other = LA->unk11C;
    if (other == NULL) {
        actorDespawn(LA);
    } else {
        kind = other->unk154;
        if (kind != 0x63) {
            switch (LA->unk154) {
                case 0:
                    if (func_8073110C(0xFD, 0)) {
                        other = LA->unk11C;
                        if (other->unk124->unk8 == 0) {
                            func_8068A2FC(other);
                        } else {
                            func_80614EBC(LA, 0x3A8);
                            func_80614EBC(LA->unk11C, 0x3AA);
                            LA->unk154 = 4;
                            LA->unk155 = 0;
                        }
                    } else {
                        other = LA->unk11C;
                        if (other->unk124->unk8 == 1) {
                            func_8068A2FC(other);
                        } else if (other->unk154 == 1) {
                            func_80614EBC(LA, 0x3A9);
                            func_80614EBC(LA->unk11C, 0x3AB);
                            LA->unk154 = 1;
                            LA->unk155 = 0;
                        } else if (!(LA->unk60 & 0x02000000)) {
                            dx = LA->unk7C - LB->unk7C;
                            dy = LA->unk80 - LB->unk80;
                            dz = LA->unk84 - LB->unk84;
                            if ((dx * dx + dy * dy + dz * dz) < 90000.0f) {
                                switch (LA->unk155) {
                                    case 0:
                                        func_80614EBC(LA, 0x3A8);
                                        func_80614EBC(LA->unk11C, 0x3AA);
                                        if (func_8073110C(0x29, 2) == 0) {
                                            func_8070E8DC(1);
                                            func_8070D8C0(LA, 0x16, 0);
                                            func_8061CC40(LA, 0x19, 1);
                                            func_8073129C(0x29, 1, 2);
                                        }
                                        LA->unk155++;
                                        break;
                                    case 1:
                                        if (other->unk132 == 2) {
                                            if (func_8073110C(0x2A, 2) == 0) {
                                                func_8070E8DC(1);
                                                func_8070D8C0(LA, 0x16, 1);
                                                func_8061CC40(LA, 0x19, 1);
                                                func_8073129C(0x2A, 1, 2);
                                            }
                                            LA->unk155++;
                                        }
                                        break;
                                }
                            }
                        }
                        if (func_80726DC0(9) && func_80726DC0(0xA) && func_80726DC0(0xB) && func_80726DC0(0xC)) {
                            LA->unk11C->unk132 = 2;
                        } else {
                            LA->unk11C->unk132 = 4;
                        }
                    }
                    break;
                case 1:
                    if (!(LA->unk60 & 0x02000000)) {
                        if (LA->unk155 == 0) {
                            LA->unk155++;
                            func_8070D8C0(LA, 0x16, 2);
                            other = LA->unk11C;
                            kind = other->unk154;
                        }
                    }
                    if (kind == 2) {
                        LB->unkE6 += 0x800;
                        LA->unk154 = 2;
                        LA->unk155 = 0;
                        func_80614EBC(LA, 0x3A7);
                        func_80614EBC(LA->unk11C, 0x3AA);
                    }
                    break;
                case 2:
                    switch (LA->unk155) {
                        case 0:
                            ez = LA->unk84 - D_80755690->unk4->unk14->unk2C;
                            ex = LA->unk7C - D_80755690->unk4->unk14->unk28;
                            ey = LA->unk80 - D_80755690->unk4->unk14->unk2A;
                            if ((ez * ez + (ex * ex + ey * ey)) < 22500.0f) {
                                func_8061CC40(LA, 0x17, 1);
                                func_8070D8C0(LA, 0x16, 4);
                                func_8073129C(0xFC, 1, 0);
                                LA->unk155++;
                                actorClearMovementFlags(LB);
                                func_80724B5C(1, 5, &LB->unk7C, &LB->unk80, &LB->unk84);
                                LB->unkE6 = mathAngleBetweenPoints2D(LA->unk7C, LA->unk84, LB->unk7C, LB->unk84);
                            } else {
                                func_8061CC40(other, 0x12, 5);
                                func_8070D8C0(LA, 0x16, 3);
                                LA->unk154 = 3;
                                LA->unk155 = 0;
                                LA->unk60 &= ~0x8000;
                                other = LA->unk11C;
                                other->unk60 &= ~0x8000;
                            }
                            LA->unk11C->unk132 = 4;
                            break;
                        case 1:
                            if (!(LA->unk60 & 0x02000000)) {
                                func_8063DA40(0x3E, 0xA);
                                LA->unk154 = 4;
                                LA->unk155 = 0;
                            }
                            break;
                    }
                    break;
                case 3:
                    if (!(LA->unk60 & 0x02000000)) {
                        node = other->unk174;
                        switch (LA->unk155) {
                            case 0:
                                LA->unk128 -= 5;
                                if (LA->unk128 < 0) {
                                    LA->unk155++;
                                    LA->unk128 = 0;
                                }
                                LA->unk11C->unk128 = LA->unk128;
                                break;
                            case 1:
                                func_8061CB08();
                                func_8068A2FC(LA->unk11C);
                                spawn[0] = 1;
                                spawn[1] = 1;
                                spawn[2] = 0;
                                actorListSpawnNodeEntry(LA->unk11C->unk5A, node->unk4, node->unk8, node->unkC, 0, node->unk10, 0, spawn);
                                break;
                        }
                    }
                    break;
                case 4:
                    break;
            }
        } else {
            actorDespawn(LA);
        }
    }
    other = LA->unk11C;
    if (other != NULL) {
        func_8067B238(LA, other, other->unk4->unk38);
        memcpy((u8 *)LA + 0xC, (u8 *)LA->unk11C + 0xC, 0x40);
    }
}

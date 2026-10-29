#include "common.h"

#include "actor.h"

typedef struct CollisionNode {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[6];
    u8 unk26;
    u8 unk27;
    struct CollisionNode *next;
} CollisionNode;

typedef struct ActorCollisionBounds {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x7C];
    CollisionNode *unk8C;
    u8 pad90[0x14];
    s32 unkA4;
    s32 unkA8;
} ActorCollisionBounds;

typedef struct CollisionActor {
    u8 pad0[0x60];
    u32 unk60;
    u32 unk64;
    u8 pad68[0x94];
    u8 unkFC;
    u8 padFD[0x43];
    ActorCollisionBounds *unk140;
    u8 unk144;
} CollisionActor;

extern u8 D_807FB600;
extern u8 D_807FB5FF;
extern u8 D_807FB5FD;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
u8 func_80673708(s32, s32, s32, s32, s32, s32, s32, s32);
u8 actorCollisionReflectAndPush(Actor *, Actor *);

u8 actorCheckCollisionsAgainstActiveActors(CollisionActor *arg0, s32 arg1, s32 arg2) {
    ActorCollisionBounds *sub140;
    s32 pad78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 i;
    s32 pad60;
    s16 pad5E;
    s16 pad5C;
    u8 pad5B;
    u8 ret;
    ActorEntry *entry;
    u8 var_s3;
    CollisionNode *node;
    CollisionActor *other;
    ActorCollisionBounds *other_sub140;

    ret = 0;
    var_s3 = 0;
    if (!(arg0->unk60 & 0x10)) {
        return 0;
    }
    sub140 = arg0->unk140;
    sp74 = sub140->unk0;
    sp70 = sub140->unk4;
    sp6C = sub140->unk8;
    sp68 = sub140->unkC;
    D_807FB600 = 0;
    do { i = 0; if (gActiveActorCount > 0) { entry = gActiveActors; do { other = (CollisionActor *) entry->actor; other_sub140 = other->unk140; if ((((!(other->unk60 & 0x2000)) && (sub140 != other_sub140)) && (other->unk144 != 1)) && (other->unk60 & 0x10)) { if (func_80674ADC(sp74, sp70, sp6C, sp68, other_sub140->unk0, other_sub140->unk4, other_sub140->unk8, other_sub140->unkC)) { node = sub140->unk8C; D_807FB5FF = 0; if (other->unk64 & 0x20) { D_807FB5FD = 0; } else { D_807FB5FD = 1; } while ((node != 0) && (D_807FB5FF == 0)) { if ((node->unk26 != 0) && (!(node->unk27 & 2))) { var_s3 |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, other_sub140->unkA4, other_sub140->unkA8, arg1, arg2); } node = node->next; } if (other->unk64 & 0x20) { arg0->unkFC |= var_s3; } if (D_807FB5FF != 0) { ret |= actorCollisionReflectAndPush((Actor *) arg0, (Actor *) other); } } } i++; entry++; } while (i < gActiveActorCount); } } while (0); // FAKE: same-line preheader steers ugen tie-break order
    return ret;
}

#ifdef NON_MATCHING
typedef f32 CollisionMtxF[4][4];

typedef struct CollisionTarget {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s16 unk48;
    u8 pad4A[2];
    u8 unk4C;
    u8 pad4D;
    s8 unk4E;
} CollisionTarget;

typedef struct CollisionPadD610 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x20];
    s16 unk28;
} CollisionPadD610;
extern CollisionPadD610 D_807FD610;

typedef struct ActorCollisionBoundsFull {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x48];
    s16 unk58;
    u8 pad5A[0xC];
    s16 unk66;
    u8 pad68[0x3C];
    s32 unkA4;
    s32 unkA8;
    u8 unkAC;
    u8 padAD[0xB];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
} ActorCollisionBoundsFull;

typedef struct CollisionActorFull {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u32 unk64;
    u16 unk68;
    u8 pad6A[0x12];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x30];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
    u8 padE8[0x14];
    u8 unkFC;
    u8 padFD[0x43];
    ActorCollisionBoundsFull *unk140;
    u8 unk144;
} CollisionActorFull;

struct Beh7BB_Struct_760C;
extern s32 D_807FB5C4;
extern s32 D_807FB5C8;
extern s32 D_807FB5CC;
extern s32 D_807FB5D0;
extern struct Beh7BB_Target *D_807FB5D8;

s32 func_806744A8(void *, s32, s32, s32, s32);
s32 actorCheckFacingTarget(Actor *);
void actorGetMatrix(struct Beh7BB_Struct_760C *, CollisionMtxF, s8);
void matrix4Invert(CollisionMtxF, CollisionMtxF);
void func_8067A864(Actor *, Actor *, s16, s16, f32 *, f32 *, s8, s32, s32);
void actorReflectCollisionAngle(Actor *, void *, void *);
s32 actorGetCollisionThreshold(Actor *);
void func_8067A908(Actor *, Actor *, f32 *, f32 *, s8, s32, s32);
s32 actorIsTargetWithinAngle(s16, s16);

u8 actorCollisionReflectAndPush(Actor *arg0, Actor *arg1) {
    u8 sp15F;
    CollisionMtxF sp11C;
    CollisionMtxF spDC;
    f32 padD0[1];
    f32 spC4[3];
    f32 spB8[3];
    f32 spAC[3];
    f32 spA0[3];
    f32 sp7C[3][3];
    s32 i;
    f32 var_fv1;
    f32 var_fa0;
    f32 var_fa1;
    ActorCollisionBoundsFull *temp_s6;
    ActorCollisionBoundsFull *temp_s0;

    sp15F = 0;
    temp_s6 = (ActorCollisionBoundsFull *)arg0->unk140;
    temp_s0 = (ActorCollisionBoundsFull *)arg1->unk140;
    if (func_806744A8((CollisionTarget *)D_807FB5D8, temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, temp_s6->unkC) == 0) {
        return 0;
    }
    if ((((CollisionActorFull *)arg0)->unk68 & 2) && (((CollisionActorFull *)arg1)->unk68 & 4)) {
        sp15F = 1;
    }
    if (actorCheckFacingTarget(arg0) == 0) {
        sp15F = 0;
    }
    if (((CollisionActorFull *)arg1)->unk68 & 8) {
        sp15F = 2;
    }
    temp_s6->unk58 = (s32)((u8 *)D_807FB5D8 - (u8 *)temp_s0->unkA4) / 88;
    actorGetMatrix((struct Beh7BB_Struct_760C *)temp_s0, sp11C, ((CollisionTarget *)D_807FB5D8)->unk4E);
    matrix4Invert(spDC, sp11C);
    if (((CollisionActorFull *)arg1)->unk64 & 0x10) {
        var_fv1 = arg0->unk7C;
        var_fa0 = arg0->unk80;
        var_fa1 = arg0->unk84;
    } else {
        var_fv1 = (f32)D_807FB5C4 / 8;
        var_fa0 = (f32)D_807FB5C8 / 8;
        var_fa1 = (f32)D_807FB5CC / 8;
    }
    if (!(arg0->unk60 & 0x800)) {
        guMtxXFMF(spDC, var_fv1, var_fa0, var_fa1, &spC4[0], &spC4[1], &spC4[2]);
    } else {
        spC4[0] = temp_s6->unkB8;
        spC4[1] = temp_s6->unkBC;
        spC4[2] = temp_s6->unkC0;
    }
    temp_s6->unkB8 = spC4[0];
    temp_s6->unkBC = spC4[1];
    temp_s6->unkC0 = spC4[2];

    spB8[0] = (f32)((CollisionTarget *)D_807FB5D8)->unk24 / 8;
    spAC[0] = (f32)((CollisionTarget *)D_807FB5D8)->unk28 / 8;
    spA0[0] = (f32)((CollisionTarget *)D_807FB5D8)->unk2C / 8;
    spB8[1] = (f32)((CollisionTarget *)D_807FB5D8)->unk30 / 8;
    spAC[1] = (f32)((CollisionTarget *)D_807FB5D8)->unk34 / 8;
    spA0[1] = (f32)((CollisionTarget *)D_807FB5D8)->unk38 / 8;
    spB8[2] = (f32)((CollisionTarget *)D_807FB5D8)->unk3C / 8;
    spAC[2] = (f32)((CollisionTarget *)D_807FB5D8)->unk40 / 8;
    spA0[2] = (f32)((CollisionTarget *)D_807FB5D8)->unk44 / 8;

    for (i = 0; i < 3; i++) {
        guMtxXFMF(spDC, spB8[i], spAC[i], spA0[i], &sp7C[i][0], &sp7C[i][1], &sp7C[i][2]);
    }

    temp_s6->unk66 = ((CollisionTarget *)D_807FB5D8)->unk48;
    if (((CollisionTarget *)D_807FB5D8)->unk4C != 0) {
        temp_s6->unk66 -= 0x800;
    }
    if (temp_s6->unk66 < 0) {
        temp_s6->unk66 += 0x1000;
    }

    if (sp15F != 1) {
        if (sp15F == 2) {
            if (((CollisionActorFull *)arg0)->unk5C & 1) {
                actorReflectCollisionAngle(arg0, (CollisionTarget *)D_807FB5D8, temp_s6);
            }
        }
        func_8067A908(arg0, arg1, &spC4[0], &sp7C[0][0], ((CollisionTarget *)D_807FB5D8)->unk4E, D_807FB5D0, actorGetCollisionThreshold(arg0));
    } else {
        func_8067A864(arg0, arg1, ((CollisionActorFull *)arg0)->unkE6, (s16)(s32)((CollisionActorFull *)arg0)->unkB8, &spC4[0], &sp7C[0][0], ((CollisionTarget *)D_807FB5D8)->unk4E, D_807FB5D0, actorGetCollisionThreshold(arg0));
        if (actorIsTargetWithinAngle(D_807FD610.unk28, 400) && (f64)D_807FD610.unk4 > 30.0) {
            ((CollisionActorFull *)arg0)->unkE6 = temp_s6->unk66;
        }
    }
    return sp15F == 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7BBD0/actorCollisionReflectAndPush.s")
#endif

#include "actor.h"

typedef f32 Beh7BB_MtxF[4][4];

typedef struct Beh7BB_Struct_760C {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
    u8 pad7C[0xC];
    s32 unk88;
} Beh7BB_Struct_760C;

extern u8 D_807444FC;
extern s32 D_8076A064;
void actorGetMatrix(Beh7BB_Struct_760C *arg0, Beh7BB_MtxF arg1, s8 arg2) {
    u8 var_v0;
    Mtx *mtx;

    if (D_8076A064 == arg0->unk88) {
        var_v0 = D_807444FC;
    } else {
        var_v0 = D_807444FC ^ 1;
    }
    mtx = arg0->unk74[var_v0];
    if (arg2 == -1) {
        memcpy(arg1, arg0->unk70, 0x40);
    } else {
        guMtxL2F(arg1, &mtx[arg2]);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7BBD0/func_806776A0.s")
typedef struct Beh7BB_Target {
    u8 pad0[0x48];
    s16 unk48;
    u8 pad4A[2];
    u8 unk4C;
} Beh7BB_Target;
extern Beh7BB_Target *D_807FB5D8;

s32 actorIsTargetWithinAngle(s16 arg0, s16 arg1) {
    s16 var_v0;
    s16 diff;

    var_v0 = D_807FB5D8->unk48;
    if (D_807FB5D8->unk4C != 0) {
        var_v0 -= 0x800;
    }
    if (var_v0 < 0) {
        var_v0 += 0x1000;
    }
    diff = var_v0 - arg0;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x801) {
        diff = 0xFFF - diff;
    }
    if (diff < arg1) {
        return 1;
    }
    return 0;
}

s32 actorCheckFacingTarget(Actor *arg0) {
    return actorIsTargetWithinAngle(arg0->unkE6, 400);
}

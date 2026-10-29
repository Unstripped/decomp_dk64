// actorCollisionReflectAndPush (src/global/7BBD0.c): stage 5, score 59 (frame 0x168, 9 saved regs match, div.s matched; minor regalloc in reflection calculation)
#include "common.h"
#include "actor.h"

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

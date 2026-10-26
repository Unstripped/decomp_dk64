#include "common.h"

#include "actor.h"
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_806319C4(Actor *, s32);

typedef struct ProjectileActorSub174 {
    s16 unk0;
    u8 pad2[0x25];
    u8 unk27;
    u8 unk28;
    u8 pad29[0xB];
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 pad37[0x88 - 0x37];
    Actor *unk88;
    u8 pad8C[0x1A4 - 0x8C];
    u8 unk1A4;
} ProjectileActorSub174;

typedef struct ProjectileActorSync {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x7C - 0x5C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xAC - 0x88];
    f32 unkAC;
    u8 padB0[0xB8 - 0xB0];
    f32 unkB8;
    u8 padBC[0xE4 - 0xBC];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0x174 - 0xEA];
    void *unk174;
} ProjectileActorSync;

void actorSnapToBone(Actor **arg0) {
    f32 sp2C;
    ProjectileActorSub174 *temp_v1;

    temp_v1 = (*arg0)->unk174;
    actorGetNodePos(temp_v1->unk88, 9, &(*arg0)->unk7C, &sp2C, &(*arg0)->unk84);
    if ((*arg0)->unk80 < sp2C) {
        (*arg0)->unk80 = sp2C;
    }
    (*arg0)->unkE6 = temp_v1->unk88->unkE6;
    func_806319C4(*arg0, 0);
}

void actorSyncTransformFromParent(ProjectileActorSync **arg0) {
    ProjectileActorSync *temp_a2;
    ProjectileActorSub174 *temp_v0;
    ProjectileActorSync *temp_v1;
    ProjectileActorSub174 *temp_a1;

    temp_a2 = *arg0;
    temp_v0 = temp_a2->unk174;
    temp_v1 = (ProjectileActorSync *)temp_v0->unk88;
    if (temp_v1 != NULL) {
        temp_a1 = temp_v1->unk174;
        if (temp_a1->unk34 < 5) {
            temp_a2->unk7C = temp_v1->unk7C;
            (*arg0)->unk80 = ((ProjectileActorSync *)temp_v0->unk88)->unk80;
            (*arg0)->unk84 = ((ProjectileActorSync *)temp_v0->unk88)->unk84;
            (*arg0)->unkE6 = ((ProjectileActorSync *)temp_v0->unk88)->unkE6;
            (*arg0)->unkE8 = ((ProjectileActorSync *)temp_v0->unk88)->unkE8;
            (*arg0)->unkE4 = ((ProjectileActorSync *)temp_v0->unk88)->unkE4;
            (*arg0)->unkAC = ((ProjectileActorSync *)temp_v0->unk88)->unkAC;
            temp_v1 = (ProjectileActorSync *)temp_v0->unk88;
            if (temp_v1->unk58 == 0x12E) {
                (*arg0)->unkB8 = temp_v1->unkB8 * 10.0f;
            } else {
                (*arg0)->unkB8 = temp_v1->unkB8;
            }
            temp_a2 = *arg0;
        } else {
            temp_a2 = *arg0;
            temp_a2->unkB8 = 0.0f;
            temp_a2 = *arg0;
        }
    }
    func_806319C4((Actor *)temp_a2, 0);
}

typedef struct TargetVec3f {
    f32 x, y, z;
} TargetVec3f;
void func_8061F2B8(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
s32 mathPickCloserTargetPoint3D(f32 arg0, f32 arg1, f32 arg2, TargetVec3f *arg3, TargetVec3f *arg4, TargetVec3f *arg5, TargetVec3f *arg6, f32 *arg7, f32 *arg8, f32 *arg9) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    func_8061F2B8(arg0, arg1, arg2, arg3->x, arg3->y, arg3->z, arg4->x, arg4->y, arg4->z, &sp48, &sp4C, &sp50);
    func_8061F2B8(arg0, arg1, arg2, arg5->x, arg5->y, arg5->z, arg6->x, arg6->y, arg6->z, &sp54, &sp58, &sp5C);
    if (((arg0 - sp48) * (arg0 - sp48) + (arg1 - sp4C) * (arg1 - sp4C) + (arg2 - sp50) * (arg2 - sp50)) <
        ((arg2 - sp5C) * (arg2 - sp5C) + ((arg0 - sp54) * (arg0 - sp54) + (arg1 - sp58) * (arg1 - sp58)))) {
        *arg7 = sp48;
        *arg8 = sp4C;
        *arg9 = sp50;
        return 0;
    }
    *arg7 = sp54;
    *arg8 = sp58;
    *arg9 = sp5C;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8068ECF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8068EF54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8068F72C.s")

typedef struct ProjectileActorSub4 {
    u8 pad0[0x1C];
    void *unk1C;
} ProjectileActorSub4;

typedef struct ProjectileActorBase {
    u8 pad0[4];
    ProjectileActorSub4 *unk4;
} ProjectileActorBase;

typedef struct ProjectileAngleTarget {
    u8 pad0[0xC];
    f32 unkC;
} ProjectileAngleTarget;

typedef struct ProjectileAngleStep {
    s16 unk0;
    s16 unk2;
} ProjectileAngleStep;

typedef struct ProjectileAngleSub1C {
    s8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
} ProjectileAngleSub1C;

s16 func_806CC190(s16, s16, f32);

extern Actor *D_807FBB40;

void actorInterpolateAngles(u8 arg0, ProjectileAngleTarget *arg1, ProjectileAngleStep *arg2) {
    f32 var_fv0;
    f32 var_fv1;
    ProjectileAngleSub1C *temp_v1;

    temp_v1 = ((ProjectileActorSub4 *)D_807FBB40->unk4)->unk1C;
    if (arg0) {
        var_fv0 = 500.0f;
        var_fv1 = 0.0f;
    } else {
        var_fv0 = 0.0f;
        var_fv1 = (f32)((f64)arg1->unkC * (400.0 - (0.7 * (f64)D_807FBB40->unkB8)));
    }
    arg2->unk2 = func_806CC190(arg2->unk2, (s16)(s32)var_fv0, 5.0f);
    arg2->unk0 = func_806CC190(arg2->unk0, (s16)((s32)var_fv1 & 0xFFF), 3.0f);
    temp_v1->unk0 = -0x80;
    temp_v1->unk1 = 1;
    temp_v1->unk2 = (u16)arg2->unk2 * 16;
    temp_v1->unk4 = (u16)arg2->unk0 * 16;
    temp_v1->unk6 = 0;
    temp_v1->unk8 = 0;
}

void *func_80610FE8(s32);
void heapClearBlock(void *);

void actorAllocSubBuffer(Actor *arg0, s32 arg1) {
    ((ProjectileActorBase *)arg0)->unk4->unk1C = func_80610FE8(arg1 * 8);
    heapClearBlock(((ProjectileActorBase *)arg0)->unk4->unk1C);
}

void playerStateQueueCallback(s32, Actor *, u8);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
void func_8067B238(Actor *, Actor *, f32);
extern s32 D_8076A0A8;

void actorInitAnimations(Actor *arg0, Actor *arg1) {
    u8 sp37[4];
    ProjectileActorSub174 *temp_v0;

    sp37[3] = 0;
    temp_v0 = arg1->unk174;
    playerStateQueueCallback(0x4C, arg0, temp_v0->unk1A4);
    if (D_8076A0A8 == 0x6F) {
        sp37[3] = 0x3C;
    }
    sfxPlayActorSound(arg0, 0x115, sp37[3], 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(arg0, 0x116, sp37[3], 1, 1, 0xFF, 1.0f, 0);
    animSetSpeed(arg0, 0, 1.0f);
    animSetLoopLimit(arg0, 0, -1);
    actorAllocSubBuffer(arg0, 2);
    func_8067B238(arg0, arg1, 0.15f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690190.s")

typedef struct SpawnCoord {
    s16 x;
    s16 y;
    s16 z;
    u8 yaw;
} SpawnCoord;

typedef struct SpawnPointActor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
} SpawnPointActor;

SpawnCoord *func_806C96C4(s32);

void actorInitFromSpawnPoint(SpawnPointActor *arg0, ProjectileActorSub174 *arg1) {
    SpawnCoord *temp_v0;
    s16 temp;

    temp_v0 = func_806C96C4(arg1->unk36);
    arg0->unk7C = temp_v0->x;
    arg0->unk80 = temp_v0->y;
    arg0->unk84 = temp_v0->z;
    temp = (u32)temp_v0->yaw * 16.062746f;
    arg0->unkE6 = temp;
    arg0->unkEE = temp;
    arg1->unk0 = temp;
}

void actorSpawn(s32, s32);
void actorInitAnimations(Actor *, Actor *);
extern Actor *D_807FBB44;

void actorSpawnChildActor(Actor *arg0) {
    ProjectileActorSub174 *sp24 = arg0->unk174;
    ProjectileActorSub174 *temp_v0;
    s32 pad;
    Actor *temp_a0;

    actorSpawn(0x13F, 0xDA);
    temp_a0 = D_807FBB44;
    temp_v0 = temp_a0->unk174;
    temp_v0->unk28 = sp24->unk1A4;
    actorInitAnimations(temp_a0, arg0);
    temp_v0->unk35 = 0;
    temp_v0->unk27 = 0;
    temp_v0->unk0 = arg0->unkE6;
    sp24->unk88 = temp_a0;
    temp_a0->unk60 &= ~0x20000;
}

typedef struct PlayerInteractionState {
    u8 pad0[0xF3];
    u8 unkF3;
} PlayerInteractionState;

typedef struct PlayerActor104 {
    u8 pad0[0x174];
    PlayerInteractionState *unk174;
} PlayerActor104;

typedef struct PlayerActorSub174 {
    u8 pad0[0x104];
    PlayerActor104 *unk104;
    u8 pad108[0x1A4 - 0x108];
    u8 unk1A4;
} PlayerActorSub174;

typedef struct PlayerInteractionActor {
    u8 pad0[0x174];
    PlayerActorSub174 *unk174;
} PlayerInteractionActor;

typedef struct PlayerInteractionEntry {
    u8 pad0[4];
    PlayerInteractionActor *actor;
    u8 pad8[0x2F0 - 8];
} PlayerInteractionEntry;

typedef struct ActorPlayerInteraction {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0xC4 - 0x6C];
    f32 unkC4;
    u8 padC8[0x144 - 0xC8];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    ProjectileActorSub174 *unk174;
    void *unk178;
} ActorPlayerInteraction;
#define G_PLAYER_INTERACT_ACTOR ((ActorPlayerInteraction *)D_807FBB40)

struct PlayerTrackEntry;
extern struct PlayerTrackEntry *D_807FC924;
extern u8 D_807444EC;
extern f32 D_80750300;
extern Actor *D_807FBB4C;
void func_8061C6A8(void *, Actor *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8068F72C(void *, s32, s32, s32);
void func_80690190(void *, s32, void *);
s32 func_8061CB50(void);
void lightAdd(f32, f32, s32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_8070033C(f32, f32, s32, f32, f32, f32, f32, s32, s32, s32);
s32 flagGet(s32, s32);

void actorUpdatePlayerInteraction(void) {
    ProjectileActorSub174 *sp5C;
    PlayerInteractionActor *playerActor;
    PlayerActorSub174 *sp54;
    s32 sp50;
    PlayerInteractionState *sp4C;
    u8 sp4B;
    f32 sp44;
    f32 sp40;
    s32 sp3C;

    sp5C = G_PLAYER_INTERACT_ACTOR->unk174;
    sp50 = (s32)G_PLAYER_INTERACT_ACTOR->unk178;
    playerActor = ((PlayerInteractionEntry *)D_807FC924)[sp5C->unk28].actor;
    sp54 = playerActor->unk174;
    sp4C = sp54->unk104->unk174;
    sp4B = G_PLAYER_INTERACT_ACTOR->unk6A & 1;
    sp5C->unk34 = 2;
    func_80690190(sp5C, sp50, sp54);
    if (D_807444EC == 0 && sp4C->unkF3 != 4) {
        func_8061C6A8(sp54->unk104, D_807FBB40, 4, 0x800, 0xA0, 0, 6, 0x12C, 0x8F, 0, 0.2f);
    }
    func_8068F72C(sp5C, sp50, 1, 1);
    actorInterpolateAngles(sp4B, (ProjectileAngleTarget *)sp5C, (ProjectileAngleStep *)sp50);
    if (!(G_PLAYER_INTERACT_ACTOR->unk60 & 0x10)) {
        G_PLAYER_INTERACT_ACTOR->unkC4 = D_80750300;
        G_PLAYER_INTERACT_ACTOR->unk144 = 0x3C;
        playerStateQueueCallback(0x4C, D_807FBB40, sp54->unk1A4);
    }
    if (func_8061CB50() == 0 || (func_8061CB50() != 0 && (D_807FBB4C->unk6A & 0x100))) {
        actorGetNodePos(D_807FBB40, 1, &sp44, &sp40, (f32 *)&sp3C);
        lightAdd(sp44, sp40, sp3C, 0.0f, 0.0f, 0.0f, 300.0f, 0, 0xFF, 0xFF, 0xFF);
        if (flagGet(0x6B, 2) == 0) {
            if (func_8061CB50() != 0 && (D_807FBB4C->unk6A & 0x100)) {
                actorGetNodePos(D_807FBB40, 2, &sp44, &sp40, (f32 *)&sp3C);
                func_8070033C(sp44, sp40, sp3C, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
            }
            if (func_8061CB50() == 0) {
                D_807FBB4C->unk6A &= ~0x100;
            }
        }
    }
    func_806319C4(D_807FBB40, 0);
}

void actorClearSubState(void) {
    func_806319C4(D_807FBB40, 0);
}

extern u8 D_80750270;
void projectileSetSpawnFlag(void) {
    D_80750270 = 1;
}

extern f32 D_807FC7B0;
extern f32 D_807FC7B4;
extern f32 D_807FC7B8;
void projectileSetTargetCoords(f32 arg0, f32 arg1, f32 arg2) {
    D_807FC7B0 = arg0;
    D_807FC7B4 = arg1;
    D_807FC7B8 = arg2;
}

#include "actor.h"

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void projectileCalculateTrajectoryAndSpawn(s16, s16, s16, f32, f32, f32, f32, f32, s32);
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} ProjectileSpawnParams;
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);
typedef struct {
    s16 unk0;
    char pad2[6];
    f32 unk8;
    f32 unkC;
    u8 pad10;
    u8 unk11;
} ProjectileTrackerSub174;
extern s32 D_807F5D10;
void screenShakeStart(f32, f32, f32, f32, f32, f32);
void func_8061F0B0(s32, s32, s32);
void func_807149B8(s32);
void func_80714950(s32);
void func_80714998(s32);
void func_8071498C(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
extern u8 D_80750AD0;

void projectileGetTargetCoords(Actor *arg0, s32 arg1) {
    actorGetNodePos(arg0, arg1, &D_807FC7B0, &D_807FC7B4, &D_807FC7B8);
}

void projectileSpawnNodeEntry(s16 arg0, s16 arg1, f32 arg2, s16 arg3, f32 arg4, f32 arg5, s32 arg6) {
    ProjectileSpawnParams sp28;

    sp28.unk0 = (f32)(((f64)arg3 / 4095.0) * 6.28318548202514648);
    sp28.unk4 = arg4;
    sp28.unkC = arg2;
    sp28.unk8 = arg5;
    sp28.unk10 = (f32)arg1;
    sp28.unk14 = (f32)(u32)D_80750270;
    actorListSpawnNodeEntry(arg0, D_807FC7B0, D_807FC7B4, D_807FC7B8, 0, arg2, arg6, &sp28);
    D_80750270 = 0;
}

void projectileCalculateTrajectoryAndSpawn(s16 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8) {
    f32 sp2C;
    f32 sp28;

    sp2C = sqrtf(((arg4 - D_807FC7B0) * (arg4 - D_807FC7B0)) + ((arg5 - D_807FC7B4) * (arg5 - D_807FC7B4)) + ((arg6 - D_807FC7B8) * (arg6 - D_807FC7B8)));
    sp28 = arg5 - D_807FC7B4;
    projectileSpawnNodeEntry(arg1, arg2, arg3, arg0, sqrtf(((arg4 - D_807FC7B0) * (arg4 - D_807FC7B0)) + ((arg6 - D_807FC7B8) * (arg6 - D_807FC7B8))) / (sp2C / arg7), sp28 / (sp2C / arg7), arg8);
}

void projectileAimAndSpawn(s16 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    projectileCalculateTrajectoryAndSpawn(mathAngleBetweenPoints2D(arg3, arg5, D_807FC7B0, D_807FC7B8), arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

s16 mathAngleDistance(s16, s16);
void projectileClampAngleAndSpawn(s16 arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, s32 arg9) {
    s16 sp3C;
    s16 sp38;
    s16 var_s0;

    var_s0 = mathAngleBetweenPoints2D(arg5, arg7, D_807FC7B0, D_807FC7B8);
    if (arg1 < mathAngleDistance(arg0, var_s0)) {
        sp3C = (arg0 - arg1) & 0xFFF;
        sp38 = (arg0 + arg1) & 0xFFF;
        if (mathAngleDistance(var_s0, sp3C) < mathAngleDistance(var_s0, sp38)) {
            var_s0 = sp3C;
        } else {
            var_s0 = sp38;
        }
    }
    projectileCalculateTrajectoryAndSpawn(var_s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

void projectileAimFromActorAndSpawn(s16 arg0, s16 arg1, f32 arg2, Actor *arg3, s32 arg4, f32 arg5, s32 arg6) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    actorGetNodePos(arg3, arg4, &sp34, &sp30, &sp2C);
    projectileAimAndSpawn(arg0, arg1, arg2, sp34, sp30, sp2C, arg5, arg6);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690C60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690F30.s")

u32 func_806119A0(void);
void func_807149C8(s32, s32, s32, s32);
extern s32 D_8071FFA0;
void func_80717D4C(void);
void actorSpawnSparkleBurst(void) {
    s32 count;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    if (D_80750AD0 != 0) {
        count = 3;
    } else {
        count = 6;
    }
    for (i = 0; i < count; i++) {
        dx = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        dy = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        dz = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        func_807149B8(1);
        func_807149C8(0x8C, 0x8C, 0x8C, 0x64);
        func_80714950(i * -0x14);
        func_80714998(3);
        func_8071498C(func_80717D4C);
        func_80714CC0(&D_8071FFA0, 2.0f, D_807FBB40->unk7C + dx, D_807FBB40->unk80 + 42.0f + dy, D_807FBB40->unk84 + dz);
    }
}

void projectileSpawnWithShockwave(s16 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    actorSpawn(0x102, arg0);
    func_8067B238(D_807FBB44, D_807FBB40, arg1);
    *(s16 *)((u8 *)D_807FBB44 + 0xF0) = arg0;
    D_807FBB44->unk16A = arg2;
    D_807FBB44->unk16B = arg3;
    D_807FBB44->unk16C = arg4;
    D_807FBB44->unk15F = arg5;
    D_807FBB44->unk168 = 1;
    *(f64 *)&D_807FBB44->unk160 = (f64)arg6;
    if (arg7 != 0.0f) {
        screenShakeStart(D_807FBB40->unk7C, D_807FBB40->unk84, arg7, 2.0f, arg8, arg9);
    }
    func_8061F0B0(D_807F5D10, 0x50, 0x14);
}

void projectileSpawnActor107(u8 arg0, u8 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    ProjectileTrackerSub174 *sub;

    actorSpawn(0x107, 0);
    func_8067B238(D_807FBB44, D_807FBB40, 0.15f);
    sub = D_807FBB44->unk174;
    sub->unk11 = arg0;
    sub->unk8 = arg2;
    sub->unkC = arg3;
    sub->unk0 = arg1;
    D_807FBB44->unk80 = *(f32 *)D_807FBB40->unkA8;
    D_807FBB44->unk15F = arg4;
    D_807FBB44->unk168 = arg5;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806919E0.s")

typedef struct SparkleParticleState {
    u32 unk0;
    char pad4[0xE];
    u8 unk12;
    u8 unk13;
} SparkleParticleState;

typedef struct SparkleConfig124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} SparkleConfig124;

typedef struct SparkleProjectileActor {
    u8 pad0[0x60];
    u32 unk60;
    u32 unk64;
    u16 unk68;
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0xB8 - 0x70];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFC - 0xF0];
    u8 unkFC;
    u8 padFD[0x124 - 0xFD];
    SparkleConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    void *unk174;
} SparkleProjectileActor;

#define G_SPARKLE_ACTOR ((SparkleProjectileActor *)D_807FBB40)

extern u8 D_80720120;
extern u8 D_80720BE8;
extern u32 D_8076A068;
extern u8 D_807FBB85;
void func_8071C914(void);
void func_807149A8(s32);
void func_807149FC(s32);
s32 func_80611A44(void);
void func_8066EB40(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void func_8067ACB4(Actor *);
void actorApplyVelocity(Actor *);
void func_80665564(Actor *, f32);
void actorDespawn(Actor *);
s32 func_80714C08(void *, f32, Actor *, s32, s32);

void projectileSparkleUpdate(s32 arg0) {
    SparkleParticleState *sp2C;

    sp2C = (SparkleParticleState *)G_SPARKLE_ACTOR->unk174;
    if (!(G_SPARKLE_ACTOR->unk60 & 0x10)) {
        G_SPARKLE_ACTOR->unk6A &= (G_SPARKLE_ACTOR->unk6E = -2);
        G_SPARKLE_ACTOR->unkEE = (s16)((G_SPARKLE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_SPARKLE_ACTOR->unkB8 = G_SPARKLE_ACTOR->unk124->unk4;
        G_SPARKLE_ACTOR->unkC0 = G_SPARKLE_ACTOR->unk124->unk8;
        G_SPARKLE_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 40.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(1);
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(func_8071C914);
        func_80714950((s32)(func_80611A44() >> 15) % 360);
        func_807149A8(2000);
        switch ((u8)arg0) {
        case 0:
            func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
            func_80714C08(&D_80720120, G_SPARKLE_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
            break;
        case 1:
            func_807149C8(0xC8, 0xC8, 0xFA, 0x9B);
            func_80714C08(&D_80720BE8, G_SPARKLE_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
            break;
        }
        sp2C->unk13 = (u8)(u32)G_SPARKLE_ACTOR->unk124->unk10;
        sp2C->unk0 = D_8076A068;
        sp2C->unk12 = 0;
        G_SPARKLE_ACTOR->unk60 |= 0x80000;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 4.0f);
    if ((G_SPARKLE_ACTOR->unk6A & 1) || (G_SPARKLE_ACTOR->unkFC != 0) || (D_807FBB85 != 0) || ((u32)(sp2C->unk0 + 24) < D_8076A068)) {
        actorDespawn(D_807FBB40);
    }
}

void func_806919E0(void *);
extern u8 D_807201D4;

void projectileSparkleUpdateGold(void) {
    projectileSparkleUpdate(0);
}

void projectileSparkleUpdateSilver(void) {
    projectileSparkleUpdate(1);
}

void projectileSpawnParticleEffect(void) {
    func_806919E0(&D_807201D4);
}

#include "actor.h"

typedef struct ProjectileConfig124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} ProjectileConfig124;

typedef struct PlayerTrackActorSub {
    u8 pad0[0x104];
    s32 unk104;
} PlayerTrackActorSub;

typedef struct PlayerTrackActor {
    u8 pad0[0x174];
    PlayerTrackActorSub *unk174;
} PlayerTrackActor;

typedef struct PlayerTrackEntry {
    u8 pad0[0x4];
    PlayerTrackActor *actor;
    u8 pad8[0x2F0 - 0x8];
} PlayerTrackEntry;

typedef struct ProjectileActorExtra {
    u32 unk0;
    u8 pad4[0x13 - 4];
    u8 unk13;
    f32 unk14;
    u8 pad18[4];
    s32 unk1C;
} ProjectileActorExtra;

typedef struct ProjectilePhysicsActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x7C - 0x6C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
    u8 unkFC;
    u8 unkFD;
    u8 padFE[0x11C - 0xFE];
    Actor *unk11C;
    u8 pad120[4];
    ProjectileConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x16E - 0x145];
    u8 unk16E;
    u8 unk16F;
    u8 pad170[0x174 - 0x170];
    void *unk174;
} ProjectilePhysicsActor;

extern u8 D_80720020;
extern u8 D_807202D0;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern s16 D_80750344;
extern ActorGlobalState D_807FBB70;
extern u8 D_807200EC;
extern PlayerTrackEntry *D_807FC924;
extern u8 D_807FC928;
extern u8 D_8072029C;
extern u8 D_80720BA0;
extern s16 D_8075035C;
extern s16 D_80750370;

void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_8071D260(void);
void func_8071A8B0(void);
void func_8071ABDC(void);
void func_8061EF4C(s32, s32, s32, f32, f32, f32, f32, f32);
void actorSpawnSparkleBurst(void);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_80714A28(s32);
void func_80690C60(s32, Actor *, void *, s32);
s32 func_80665558(void);
s32 collisionGetStateByte(void);

void projectileSpawnParticleEffect2(void) {
    func_806919E0(&D_807201D4);
}

void projectileSpawnParticleEffect3(void) {
    func_806919E0(&D_807201D4);
}

void projectileSpawnParticleEffectWithScale(void) {
    ProjectileActorExtra *extra;
    f32 temp;

    extra = (ProjectileActorExtra *)D_807FBB40->unk174;
    func_806919E0(&D_807201D4);
    if (extra->unk13 == 1) {
        ((ProjectilePhysicsActor *)D_807FBB40)->unkC0 += D_807502E4;
        temp = (f32)D_807502D0;
        if (((ProjectilePhysicsActor *)D_807FBB40)->unkC0 < temp) {
            ((ProjectilePhysicsActor *)D_807FBB40)->unkC0 = temp;
        }
    }
}

#define G_PROJECTILE_ACTOR ((ProjectilePhysicsActor *)D_807FBB40)

void projectileDespawnOrExplode(void) {
    u32 *sp44;
    u8 unkFC;
    Actor *other;

    sp44 = (u32 *)G_PROJECTILE_ACTOR->unk174;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 50.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714C08(&D_80720020, G_PROJECTILE_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        *sp44 = D_8076A068;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x96, 0x78, 0, 1.0f);
    unkFC = G_PROJECTILE_ACTOR->unkFC;
    if (unkFC != 0 || (G_PROJECTILE_ACTOR->unk6A & 1) || D_807FBB70.unk15 != 0 || D_807FBB70.unk200 == 9) {
        other = G_PROJECTILE_ACTOR->unk11C;
        if (other == NULL || other->unk58 != 0x2E || (other->unk58 == 0x2E && (unkFC != 0 || (G_PROJECTILE_ACTOR->unk6A & 1)))) {
            func_807149B8(0);
            func_807149FC(1);
            func_8071498C(func_8071D260);
            func_80714950(0xC);
            func_80714CC0(&D_807202D0, 0.75f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x61, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
        actorDespawn(D_807FBB40);
    }
    if ((u32)(*sp44 + D_80750344) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80692940.s")

void projectileMultiplayerUpdate(void) {
    ProjectileActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;
    s32 var_s1;
    sp44 = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714A28(4);
        func_80714C08(&D_8072029C, G_PROJECTILE_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp44->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        sp44->unk0 = D_8076A068;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_8075035C;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (D_807FC928 >= 2) {
            var_a0 = 3;
        }
        func_80690C60(var_a0, D_807FBB40, &D_8072029C, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_80750370;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    if (G_PROJECTILE_ACTOR->unkFD != 0 ||
        func_80665558() != 0 ||
        ((G_PROJECTILE_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < D_8076A068)) {
        if (D_80750AD0 == 0) {
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                func_807149B8(1);
                func_80714950(0x05000000 + var_s1);
                func_80714998(1);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_80720BA0, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            }
        }
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x91, 0xFF, 0x7F, 0x1E);
        actorDespawn(D_807FBB40);
    }
    if (D_807FC928 >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

void projectileSpawnExplosion(void) {
    s32 i;

    func_807149B8(1);
    func_80714950(0x1006E);
    func_8071498C(func_8071A8B0);
    func_80714CC0(&D_80720120, 2.0f, D_807FBB40->unk7C, D_807FBB40->unk80 + 22.0f, D_807FBB40->unk84);

    for (i = 0; i < D_807FC928; i++) {
        func_8061EF4C(D_807FC924[i].actor->unk174->unk104, 7, 0x16, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 200.0f, 400.0f);
    }

    actorSpawnSparkleBurst();

    if (D_80750AD0 == 0) {
        for (i = 0; i < 12; i++) {
            func_807149B8(1);
            func_80714950(0x0B010000 + i);
            func_8071498C(func_8071ABDC);
            func_80714CC0(&D_807200EC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
    }

    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF6, 0xFF, 0x7F, 0x1E);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8069346C.s")

#include "actor.h"

typedef struct ProjectileBeamConfig124 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} ProjectileBeamConfig124;

typedef struct ProjectileBeamActorExtra {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[0x13 - 0x05];
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s32 unk1C;
} ProjectileBeamActorExtra;

typedef struct ProjectileBeamActor {
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
    /* 0x124 */ ProjectileBeamConfig124 *unk124;
    /* 0x128 */ u8 pad128[0x144 - 0x128];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x154 - 0x145];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x16E - 0x155];
    /* 0x16E */ u8 unk16E;
    /* 0x16F */ u8 unk16F;
    /* 0x170 */ u8 pad170[4];
    /* 0x174 */ void *unk174;
} ProjectileBeamActor;

#define G_PROJECTILE_BEAM_ACTOR ((ProjectileBeamActor *)D_807FBB40)

extern s16 D_80750358;
extern s16 D_8075036C;

void projectileSpawnExplosion(void);
extern u8 D_8071FB34;
extern u8 D_807201A0;

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80693EC0.s")

void projectileBeamUpdate(void) {
    ProjectileBeamActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;
    s32 var_s1;
    sp44 = (ProjectileBeamActorExtra *)G_PROJECTILE_BEAM_ACTOR->unk174;
    if (!(G_PROJECTILE_BEAM_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_BEAM_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_BEAM_ACTOR->unkEE = (s16)((G_PROJECTILE_BEAM_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_BEAM_ACTOR->unkB8 = G_PROJECTILE_BEAM_ACTOR->unk124->unk4;
        G_PROJECTILE_BEAM_ACTOR->unkC0 = G_PROJECTILE_BEAM_ACTOR->unk124->unk8;
        G_PROJECTILE_BEAM_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714A28(4);
        func_80714C08(&D_807201A0, G_PROJECTILE_BEAM_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp44->unk14 = G_PROJECTILE_BEAM_ACTOR->unk124->unkC;
        sp44->unk0 = D_8076A068;
        G_PROJECTILE_BEAM_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_BEAM_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_BEAM_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)G_PROJECTILE_BEAM_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_80750358;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (D_807FC928 >= 2) {
            var_a0 = 3;
        }
        func_80690C60(var_a0, D_807FBB40, &D_807201A0, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_8075036C;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    if (func_80665558() != 0 ||
        G_PROJECTILE_BEAM_ACTOR->unkFD != 0 ||
        ((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_BEAM_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < D_8076A068)) {
        func_807149B8(1);
        func_80714950(0x1006E);
        func_8071498C(func_8071A8B0);
        func_80714CC0(&D_8071FB34, 0.45f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1E5, 0xFF, 0x7F, 0x1E);
        actorDespawn(D_807FBB40);
        if (D_80750AD0 == 0) {
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                func_807149B8(1);
                func_80714950(0x0B000000 + var_s1);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_807200EC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            }
        }
    }
    if (D_807FC928 >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80694948.s")

extern u8 D_807206A8;
extern u8 D_807206DC;
extern s16 D_80750360;
extern s16 D_80750374;
extern s16 D_80750354;
extern s16 D_80750368;
void func_80613C48(Actor *, s32, f32, f32);
void func_80614D00(Actor *, f32, f32);


f32 func_80611BB4(f32, f32);
void func_80695724(f32, u8);
void func_80612BC0(void *, s32);

typedef struct ProjectileRotSub174 {
    u8 pad0[8];
    s32 unk8;
} ProjectileRotSub174;

typedef struct ProjectileRotActorExtra {
    u32 unk0;
    u8 pad4[4];
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    u8 pad18[4];
    s32 unk1C;
} ProjectileRotActorExtra;

typedef struct ProjectileRotActor {
    u8 pad0[4];
    ActorSub4 *unk4;
    u8 pad8[0x60 - 8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x7C - 0x6C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xC0 - 0xBC];
    f32 unkC0;
    u8 padC4[0xE6 - 0xC4];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0xFD - 0xF0];
    u8 unkFD;
    u8 padFE[0x124 - 0xFE];
    ProjectileConfig124 *unk124;
    u8 pad128[0x132 - 0x128];
    s16 unk132;
    u8 pad134[4];
    s32 unk138;
    u8 pad13C[0x144 - 0x13C];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 pad155[0x16E - 0x155];
    u8 unk16E;
    u8 unk16F;
    u8 pad170[4];
    void *unk174;
} ProjectileRotActor;

#define G_PROJECTILE_ROT_ACTOR ((ProjectileRotActor *)D_807FBB40)


void projectileRotatingUpdate(void) {
    ProjectileActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;

    sp44 = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 50.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714A28(4);
        func_80714C08(&D_807206A8, G_PROJECTILE_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp44->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        sp44->unk0 = D_8076A068;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_80750360;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (D_807FC928 >= 2) {
            var_a0 = 3;
        }
        func_80690C60(var_a0, D_807FBB40, &D_807206A8, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_80750374;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    if (G_PROJECTILE_ACTOR->unkFD != 0 ||
        func_80665558() != 0 ||
        ((G_PROJECTILE_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < D_8076A068)) {
        func_807149B8(1);
        func_80714950(0x1006E);
        func_8071498C(func_8071A8B0);
        func_80714CC0(&D_8071FB34, 0.45f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xFF, 0xFF, 0x7F, 5);
        actorDespawn(D_807FBB40);
        if (D_80750AD0 == 0) {
            s32 var_s0;
            for (var_s0 = 0; var_s0 != 0xC; var_s0 += 2) {
                func_807149B8(1);
                func_80714950(0x0B000000 + var_s0);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_807206DC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            }
        }
    }
    if (D_807FC928 >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

s32 actorIsActiveType2B(Actor *arg0) {
    if (arg0->unk58 != 0x2B) {
        return 1;
    }
    if (arg0->unk154 == 0) {
        return 1;
    }
    return 0;
}

void projectileMatrixRotationUpdate(void) {
    ProjectileRotActorExtra *temp_s2;
    s32 var_a0;
    s32 sp84;
    f32 sp44[4][4];
    temp_s2 = G_PROJECTILE_ROT_ACTOR->unk174;
    if (!(G_PROJECTILE_ROT_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ROT_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ROT_ACTOR->unkEE = (s16)((G_PROJECTILE_ROT_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ROT_ACTOR->unkE6 = (s16)G_PROJECTILE_ROT_ACTOR->unkEE;
        G_PROJECTILE_ROT_ACTOR->unkB8 = G_PROJECTILE_ROT_ACTOR->unk124->unk4;
        G_PROJECTILE_ROT_ACTOR->unkC0 = G_PROJECTILE_ROT_ACTOR->unk124->unk8;
        G_PROJECTILE_ROT_ACTOR->unk144 = 0x3C;
        temp_s2->unk0 = D_8076A068;
        G_PROJECTILE_ROT_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ROT_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ROT_ACTOR->unk16F = 0x3C;
        func_80613C48(D_807FBB40, 0x404, 0.0f, 1.0f);
        temp_s2->unk8 = -(func_80611BB4(G_PROJECTILE_ROT_ACTOR->unkC0, G_PROJECTILE_ROT_ACTOR->unkB8) * 57.295776f);
        temp_s2->unk10 = 0;
        temp_s2->unkC = (f32)((u32)(func_806119A0() % 3600U) / 10U);
        temp_s2->unk13 = (u8)(u32)G_PROJECTILE_ROT_ACTOR->unk124->unk10;
        temp_s2->unk1C = 0;
    }
    sp84 = D_80750354;
    if (temp_s2->unk13 & 2) {
        var_a0 = 2;
        if (D_807FC928 >= 2) {
            var_a0 = 3;
        }
        func_80690C60(var_a0, D_807FBB40, 0, 0);
    }
    if (temp_s2->unk13 & 4) {
        sp84 = D_80750368;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    switch (G_PROJECTILE_ROT_ACTOR->unk154) {
    case 0:
        if (G_PROJECTILE_ROT_ACTOR->unkFD != 0 || (G_PROJECTILE_ROT_ACTOR->unk124->unk14 != 0.0f && (u32)(temp_s2->unk0 + 1) < D_8076A068)) {
            func_80614D00(D_807FBB40, 0.5f, 0);
            func_80613C48(D_807FBB40, 0x406, 0, 0.0f);
            G_PROJECTILE_ROT_ACTOR->unkB8 = 0.0f;
            G_PROJECTILE_ROT_ACTOR->unkC0 = 0.0f;
            G_PROJECTILE_ROT_ACTOR->unk154 = 1;
            temp_s2->unk10 = 0x3C;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x308, 0xFF, 0x7F, 5);
            if (D_80750AD0 != 0) {
                actorDespawn(D_807FBB40);
                return;
            }
        }
        break;
    case 1:
        G_PROJECTILE_ROT_ACTOR->unk138 = 0;
        G_PROJECTILE_ROT_ACTOR->unk144 = 1;
        temp_s2->unk0 = D_8076A068;
        if (!--temp_s2->unk10) {
            func_80614D00(D_807FBB40, 0.5f, 0);
            func_80613C48(D_807FBB40, 0x405, 0, 10.0f);
            G_PROJECTILE_ROT_ACTOR->unk154++;
        }
        break;
    case 2:
        G_PROJECTILE_ROT_ACTOR->unkC0 -= 20.0f;
        if (G_PROJECTILE_ROT_ACTOR->unkC0 < -150.0f) {
            G_PROJECTILE_ROT_ACTOR->unkC0 = -150.0f;
        }
        break;
    }
    if (((G_PROJECTILE_ROT_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) || D_807FBB85 != 0) {
        actorDespawn(D_807FBB40);
    }
    if (D_807FC928 >= 2) {
        sp84 = (s32)((f32)sp84 * 1.4f);
    }
    if ((u32)(temp_s2->unk0 + sp84) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
    guRotateF((void *)((u8 *)D_807FBB40 + 0xC), temp_s2->unkC, 0.0f, 0.0f, 1.0f);
    guRotateF(sp44, temp_s2->unk8, 1.0f, 0.0f, 0.0f);
    guMtxCatF((void *)((u8 *)D_807FBB40 + 0xC), sp44, (void *)((u8 *)D_807FBB40 + 0xC));
    func_806319C4(D_807FBB40, 1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80695724.s")

void actorApplyTransformAndRender(void) {
    ProjectileRotSub174 *sp1C;

    sp1C = D_807FBB40->unk174;
    func_80695724(0.0f, 1);
    func_80612BC0((u8 *)D_807FBB40 + 0xC, sp1C->unk8);
    func_806319C4(D_807FBB40, 1);
}

extern u8 D_8071FBC8;
extern u8 D_8071FC40;
extern u8 D_80720804;
void func_807189BC(void);

typedef struct ProjectileParticleActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
    u8 unkFC;
    u8 padFD[0x124 - 0xFD];
    ProjectileBeamConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    void *unk174;
} ProjectileParticleActor;

#define G_PROJECTILE_PARTICLE_ACTOR ((ProjectileParticleActor *)D_807FBB40)

void projectileParticleSpawnerTick(void) {
    ProjectileBeamActorExtra *sp54;
    s32 var_s0;
    sp54 = (ProjectileBeamActorExtra *)G_PROJECTILE_PARTICLE_ACTOR->unk174;
    if (!(G_PROJECTILE_PARTICLE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_PARTICLE_ACTOR->unkFA = 0x270F;
        G_PROJECTILE_PARTICLE_ACTOR->unk6E = -2;
        G_PROJECTILE_PARTICLE_ACTOR->unk6A &= -2;
        G_PROJECTILE_PARTICLE_ACTOR->unkEE = (s16)((G_PROJECTILE_PARTICLE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_PARTICLE_ACTOR->unkB8 = G_PROJECTILE_PARTICLE_ACTOR->unk124->unk4;
        G_PROJECTILE_PARTICLE_ACTOR->unkC0 = G_PROJECTILE_PARTICLE_ACTOR->unk124->unk8;
        sp54->unk13 = (u8)(u32)G_PROJECTILE_PARTICLE_ACTOR->unk124->unk10;
        G_PROJECTILE_PARTICLE_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 110.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714C08(&D_80720804, G_PROJECTILE_PARTICLE_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp54->unk0 = D_8076A068;
        G_PROJECTILE_PARTICLE_ACTOR->unk60 |= 0x80000;
        if (sp54->unk13 != 0xA) {
            func_80714998(2);
            func_807149B8(1);
            func_80714CC0(&D_8071FBC8, 1.5f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 4.0f);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    if (G_PROJECTILE_PARTICLE_ACTOR->unk6A & 4) {
        func_807149B8(1);
        func_807149FC(-1);
        func_8071498C(func_807189BC);
        func_80714950((s32)D_807FBB40);
        func_80714CC0(&D_8071FC40, 0.3f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    }
    if (((G_PROJECTILE_PARTICLE_ACTOR->unkFC != 0) && ((u32)(D_8076A068 - sp54->unk0) >= 6)) || D_807FBB85 != 0) {
        if ((D_807FBB85 != 0) && (sp54->unk13 != 0xA)) {
            func_807149B8(1);
            func_80714950(0x100D2);
            func_8071498C(func_8071A8B0);
            func_80714CC0(&D_80720120, 2.0f, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84);
            func_8061EF4C(((PlayerTrackActor *)D_807FBB4C)->unk174->unk104, 7, 0x16, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 200.0f, 400.0f);
            actorSpawnSparkleBurst();
            for (var_s0 = 0; var_s0 != 12; var_s0 += 2) {
                func_807149B8(1);
                func_80714950(0x0B000000 + var_s0);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_807206DC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            }
        }
        if (sp54->unk13 != 0xA) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3C, 0xFF, 0x7F, 0x1E);
        }
        actorDespawn(D_807FBB40);
    }
    if ((u32)(sp54->unk0 + D_80750344) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

extern u8 D_80720340;
extern f32 D_80750274;
void func_8071496C(s16);

typedef struct ProjectileHomingActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
    u8 unkFC;
    u8 padFD[0x124 - 0xFD];
    ProjectileBeamConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    void *unk174;
} ProjectileHomingActor;

#define G_PROJECTILE_HOMING_ACTOR ((ProjectileHomingActor *)D_807FBB40)

void projectileHomingParticleUpdate(void) {
    u32 *sp74;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fv0;
    s32 var_s1;

    sp74 = (u32 *)G_PROJECTILE_HOMING_ACTOR->unk174;
    if (!(G_PROJECTILE_HOMING_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_HOMING_ACTOR->unkFA = 0x270F;
        G_PROJECTILE_HOMING_ACTOR->unk6E = -2;
        G_PROJECTILE_HOMING_ACTOR->unk6A &= -2;
        G_PROJECTILE_HOMING_ACTOR->unkEE = (s16)((G_PROJECTILE_HOMING_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_HOMING_ACTOR->unkB8 = G_PROJECTILE_HOMING_ACTOR->unk124->unk4;
        G_PROJECTILE_HOMING_ACTOR->unkC0 = G_PROJECTILE_HOMING_ACTOR->unk124->unk8;
        G_PROJECTILE_HOMING_ACTOR->unk144 = 0x1C;
        func_8066EB40(D_807FBB40, 110.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714C08(&D_80720804, G_PROJECTILE_HOMING_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        *sp74 = D_8076A068;
        G_PROJECTILE_HOMING_ACTOR->unk60 |= 0x80000;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 4.0f);
    G_PROJECTILE_HOMING_ACTOR->unkC0 += D_80750274;
    temp_fv0 = (f32)D_807502D0;
    if (G_PROJECTILE_HOMING_ACTOR->unkC0 < temp_fv0) {
        G_PROJECTILE_HOMING_ACTOR->unkC0 = temp_fv0;
    }
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    var_s1 = 0;
    if ((G_PROJECTILE_HOMING_ACTOR->unk6A & 1) || ((G_PROJECTILE_HOMING_ACTOR->unkFC != 0) && ((u32)(D_8076A068 - *sp74) >= 6)) || D_807FBB85 != 0) {
        do {
            temp_fs2 = ((f64)((func_80611A44() >> 15) % 8191) / 200.0) - 20.0;
            temp_fs3 = ((f64)((func_80611A44() >> 15) % 8191) / 200.0) - 20.0;
            temp_fs4 = ((f64)((func_80611A44() >> 15) % 8191) / 200.0) - 20.0;
            func_8071496C(var_s1);
            func_807149B8(1);
            if (var_s1 == 0) {
                func_80714950(0x1006E);
                func_8071498C(func_8071A8B0);
            } else {
                func_8071498C(func_80717D4C);
                func_80714950(-150 - ((func_80611A44() >> 15) % 50));
            }
            func_80714CC0(&D_80720340, 1.6f, D_807FBB40->unk7C + temp_fs2, D_807FBB40->unk80 + temp_fs3, D_807FBB40->unk84 + temp_fs4);
            var_s1 += 2;
        } while (var_s1 != 16);
        func_8061F0B0(D_807F5D10, 20, 15);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3C, 0xFF, 0x7F, 0x1E);
        actorDespawn(D_807FBB40);
    }
    if ((u32)(*sp74 + D_80750344) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80696574.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80696A6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806970CC.s")

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);

void actorAppendActiveCallback8(void) {
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;

        if (actor->unk5C & 4) {
            actorAppendCallback(actor, (s32)D_807FBB40, 8, 0, 0, NULL);
        }
    }
}

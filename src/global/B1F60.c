#include "common.h"
#include "actor.h"

typedef struct B1F60Sub0 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
} B1F60Sub0;

typedef struct B1F60Sub4 {
    /* 0x00 */ B1F60Sub0 *unk0;
    /* 0x04 */ u8 pad4[0x60];
    /* 0x64 */ u16 unk64;
} B1F60Sub4;

// File-local view of Actor for the fields the shared Actor lacks or types differently.
typedef struct B1F60Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ B1F60Sub4 *unk4;
    /* 0x008 */ u8 pad8[0xB8];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x24];
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x65];
    /* 0x155 */ u8 unk155;
} B1F60Actor;

typedef struct B1F60View90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
} B1F60View90;

typedef struct B1F60View98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
} B1F60View98;

typedef struct B1F60View9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} B1F60View9C;

typedef struct B1F60Global924 {
    /* 0x000 */ u8 pad0[0x2C8];
    /* 0x2C8 */ s16 unk2C8;
} B1F60Global924;

#define B1F60A ((B1F60Actor *)gCurrentActor)

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern ActorGlobalState D_807FBB70;
extern s32 gCurrentMap;
extern B1F60Global924 *gPlayerSlots;

void actorSpawn(s32, s32);
Actor *actorFindByType(s32);
void actorDespawn(Actor *);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void sfxSpawnTableNodes(Actor *);
s32 randomNonNegative(void);
void actorScriptStart(Actor *, s32);
void actorUpdateModelMatrix(Actor *, s32);
void func_80724CA4(s32, s32);
void func_80724E48(u8);
void behaviourFrameBegin(void);
void func_8072881C(s32, void *);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void actorSetTargetSpeed(Actor *, s32);
void behaviourSetAnimIds(s32, s32, s32);
void func_8072B7CC(s32);
void func_8072D714();
void func_8072DC7C(s32);
void actorSetDefaultState(s32);
void func_8072DEA8(s32, s32, s32);
s32 actorIsTargetWithinDistance(s32);
void actorPatrolFollowerUpdate();


void enemyAggroStateUpdate(s32, s32, s32);
u8 patrolPathStep(u8, u8);
void actorPatrolFollowerUpdate(targetId, skipStep, movementFlags)
s16 targetId;
u8 skipStep;
u16 movementFlags;
{
    Actor *actor;

    if (targetId != 0 && (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0)) {
        actor = gCurrentActor;
        if (actor->state != 0x37) {
            ((B1F60Actor *)actor)->unkC0 = 200.0f;
            func_8072D714(D_807FBB70.unk1FC, targetId, actor);
        }
    }
    if (gCurrentActor->state) {}  // FAKE: raises the actor-type expression's priority so the switch-selector copy colours v0
    actor = gCurrentActor;
    switch (gCurrentActor->state) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            actorMoveWithinZone(gCurrentActor->state, D_807FDC94->x, D_807FDC94->z, (actor->contactFlags & 1) ? movementFlags : (movementFlags | 2), 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(gCurrentActor->state, (f32)D_807FDC90->targetX, (f32)D_807FDC90->targetZ, movementFlags, 0.0f);
            break;
        case 0x37:
            switch (((B1F60Actor *)actor)->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, movementFlags | 0x4200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(actor);
                    if (skipStep != 0) {
                        B1F60A->unk155 = 2;
                        break;
                    }
                    B1F60A->unkC0 = 100.0f;
                    actor = gCurrentActor;
                    ((B1F60Actor *)actor)->unk155++;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, movementFlags | 0x4200, 0.0f);
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    actor->state = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(((B1F60View98 *)D_807FDC98)->unk28);
            break;
    }
    switch (gCurrentActor->state) {
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
        default:
            enemyAggroStateUpdate(0x4C90, ((B1F60View98 *)D_807FDC98)->unk28, ((B1F60View98 *)D_807FDC98)->unk2A);
        case 0x37:
        case 0x40:
            break;
    }
}

void func_806AD54C(void) {
    Actor *found;
    f32 dx;
    f32 dz;
    s32 dir;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(2, 1);
        behaviourSetAnimIds(0x1F8, 0x1F8, 0x1F9);
        if (gCurrentMap == 0x68 || gCurrentMap == 0x88 || gCurrentMap == 0x89) {
            gCurrentActor->unk132 = 2;
        }
    }
    if (gCurrentActor->unk132 == 2 && gCurrentActor->state != 0x36) {
        found = actorFindByType(0x11A);
        if (found != NULL) {
            if (found->state != 0) {
                if (!(((B1F60View90 *)D_807FDC90)->unk1A & 0x8000)) {
                    dx = found->x - gCurrentActor->x;
                    dz = found->z - gCurrentActor->z;
                    if ((dx * dx) + (dz * dz) < 1600.0f) {
                        dir = (((found->yaw - gCurrentActor->yaw) & 0xFFF) > 0x800) ? 1 : -1;
                        gCurrentActor->speedXZ = (f64)(u32)((B1F60View9C *)D_807FDC9C)->unkD * 1.8;
                        gCurrentActor->yaw += dir * 0x190;
                        B1F60A->unkEE = gCurrentActor->yaw;
                        ((B1F60View90 *)D_807FDC90)->unk1A |= 0x8000;
                        gCurrentActor->state = 0x10;
                        B1F60A->unk155 = 0;
                    }
                }
            } else {
                ((B1F60View90 *)D_807FDC90)->unk1A &= 0x7FFF;
            }
        }
    }
    actorPatrolFollowerUpdate(0x1FA, 0, 0);
    func_80724E48((gCurrentActor->state == 0x23) ? 0 : 2);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806AD7AC(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(2, 1);
        behaviourSetAnimIds(0x1F8, 0x1F8, 0x1F9);
    }
    actorPatrolFollowerUpdate(0x1FA, 0, 0);
    func_80724E48((gCurrentActor->state == 0x23) ? 0 : 2);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorFollowLinkedNodeFadeUpdate(void) {
    Actor *linked;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk4->unk34 = 0.05f;
        gCurrentActor->unk4->unk3C = 0.05f;
        gCurrentActor->unk4->unk38 = 2.0f;
        gCurrentActor->flags |= 0x400;
    }
    switch (gCurrentActor->state) {
        case 0:
            linked = (Actor *)gCurrentActor->unk11C;
            if (linked == NULL || (linked->contactFlags & 1)) {
                gCurrentActor->state = 1;
                gCurrentActor->flags &= ~0x8000;
            } else {
                actorGetNodePos(linked, 2, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
                B1F60A->unkE8 = ((B1F60Actor *)gCurrentActor->unk11C)->unkE8;
            }
            break;
        case 1:
            if (gCurrentActor->unk128 >= 0xB) {
                gCurrentActor->unk128 -= 0xA;
            } else {
                actorDespawn(gCurrentActor);
            }
            break;
    }
    gCurrentActor->yaw = gPlayerSlots->unk2C8 & 0xFFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorSpawnLinkedFollower(void) {
    actorSpawn(0x118, 0xC0);
    gSpawnedActor->unk11C = (s32)gCurrentActor;
    gSpawnedActor->unk12A = 0x7D0;
}

void func_806AD9F4(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        D_807FDC98->unk46 |= 0x200;
        behaviourSetAnimIds(0x2F4, 0x2F4, 0x2F4);
        if (gCurrentActor->y != gCurrentActor->floorY) {
            gCurrentActor->state = 0x1E;
            actorScriptStart(gCurrentActor, 0x2F8);
            actorSpawnLinkedFollower();
        }
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && gCurrentActor->state != 0x37) {
        func_8072D714(D_807FBB70.unk1FC, 0x2F7);
        actorSetTargetSpeed(gCurrentActor, 0);
        gCurrentActor->speedXZ = -200.0f;
    } else if (D_807FBB70.unk200 == 4) {
        gCurrentActor->unk132 = 2;
        func_8072DEA8(0x2F6, 0x27, D_807FBB70.unk1FC);
        gCurrentActor->speedXZ = gCurrentActor->speedXZ * 2;
        D_807FDC90->timer = 0x1F4;
    }
    switch (gCurrentActor->state) {
        case 0x1E:
            actorMoveWithinZone(0, D_807FDC94->x, D_807FDC94->z, 0x4202, 0.0f);
            if (B1F60A->unk155 != 0) {
                actorSetDefaultState(0x2F4);
            }
            break;
        case 0x27:
            actorMoveWithinZone(0, D_807FDC94->x, D_807FDC94->z, 0x4300, 0.0f);
            gCurrentActor->yaw += D_807FDC90->timer;
            if (D_807FDC90->timer >= 0x15) {
                D_807FDC90->timer -= 0x14;
            } else {
                D_807FDC90->timer = 0;
                B1F60A->unkEE = gCurrentActor->yaw;
            }
            if (B1F60A->unk155 != 0 && D_807FDC90->timer == 0) {
                gCurrentActor->unk132 = 1;
                actorSetDefaultState(0x2F4);
            }
            break;
        case 0x28:
            switch (B1F60A->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2F5);
                    B1F60A->unk155++;
                case 1:
                    actorMoveWithinZone(0, D_807FDC94->x, D_807FDC94->z, 0x4200, 0.0f);
                    if (gCurrentActor->speedXZ < 1.0f) {
                        B1F60A->unk155++;
                    }
                    break;
                case 3:
                    actorSetDefaultState(0x2F4);
                    break;
            }
            break;
        case 1:
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                if (gCurrentActor->contactFlags & 1) {
                    gCurrentActor->state = 0x28;
                    B1F60A->unk155 = 0;
                }
            }
        default:
            actorPatrolFollowerUpdate(0, 1, 0);
            break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806ADDD8(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        D_807FDC98->unk46 |= 0x40;
        ((B1F60View98 *)D_807FDC98)->unk28 = 0x31A;
    }
    switch (gCurrentActor->state) {
        case 0:
        case 1:
            if (actorIsTargetWithinDistance(0x12C) != 0) {
                actorScriptStart(gCurrentActor, 0x31A);
                gCurrentActor->state = 0x23;
                B1F60A->unk155 = 0;
            }
            break;
        case 4:
            if (B1F60A->unk4->unk64 != 0x319) {
                gCurrentActor->state = 0x23;
                B1F60A->unk155 = 0;
            } else if (actorIsTargetWithinDistance(0x64) != 0) {
                actorScriptStart(gCurrentActor, 0x31B);
                gCurrentActor->state = 0x1E;
                B1F60A->unk155 = 0;
            }
            break;
        case 0x1E:
            if (B1F60A->unk4->unk64 == 0x31A) {
                gCurrentActor->state = 0x23;
                B1F60A->unk155 = 0;
            }
            break;
        case 0x23:
            if (B1F60A->unk4->unk64 == 0x31A && B1F60A->unk4->unk0->unk4 > 4.0f) {
                actorMoveWithinZone(gCurrentActor->state, D_807FDC94->x, D_807FDC94->z, 0, 0.0f);
            }
            if (actorIsTargetWithinDistance(0x12C) == 0) {
                actorScriptStart(gCurrentActor, 0x31C);
                gCurrentActor->state = 0;
                B1F60A->unk155 = 0;
            }
            break;
        default:
            func_8072B7CC(0x31A);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

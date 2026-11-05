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

s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);
u8 func_80673708(s32, s32, s32, s32, s32, s32, s32, s32);
u8 actorCollisionReflectAndPush(Actor *, Actor *);

u8 actorCheckCollisionsAgainstActiveActors(CollisionActor *self, s32 anglePtr1, s32 anglePtr2) {
    ActorCollisionBounds *sub140;
    s32 pad78;
    s32 posX;
    s32 posY;
    s32 posZ;
    s32 radius;
    s32 i;
    s32 pad60;
    s16 pad5E;
    s16 pad5C;
    u8 pad5B;
    u8 ret;
    ActorEntry *entry;
    u8 hitMask;
    CollisionNode *node;
    CollisionActor *other;
    ActorCollisionBounds *other_sub140;

    ret = 0;
    hitMask = 0;
    if (!(self->unk60 & 0x10)) {
        return 0;
    }
    sub140 = self->unk140;
    posX = sub140->unk0;
    posY = sub140->unk4;
    posZ = sub140->unk8;
    radius = sub140->unkC;
    D_807FB600 = 0;
    do { i = 0; if (gActiveActorCount > 0) { entry = gActiveActors; do { other = (CollisionActor *) entry->actor; other_sub140 = other->unk140; if ((((!(other->unk60 & 0x2000)) && (sub140 != other_sub140)) && (other->unk144 != 1)) && (other->unk60 & 0x10)) { if (collisionSpheresOverlap(posX, posY, posZ, radius, other_sub140->unk0, other_sub140->unk4, other_sub140->unk8, other_sub140->unkC)) { node = sub140->unk8C; D_807FB5FF = 0; if (other->unk64 & 0x20) { D_807FB5FD = 0; } else { D_807FB5FD = 1; } while ((node != 0) && (D_807FB5FF == 0)) { if ((node->unk26 != 0) && (!(node->unk27 & 2))) { hitMask |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, other_sub140->unkA4, other_sub140->unkA8, anglePtr1, anglePtr2); } node = node->next; } if (other->unk64 & 0x20) { self->unkFC |= hitMask; } if (D_807FB5FF != 0) { ret |= actorCollisionReflectAndPush((Actor *) self, (Actor *) other); } } } i++; entry++; } while (i < gActiveActorCount); } } while (0); // FAKE: same-line preheader steers ugen tie-break order
    return ret;
}

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
extern CollisionPadD610 gPlayerPadState;

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

struct ActorMtxOwner;
extern s32 D_807FB5C4;
extern s32 D_807FB5C8;
extern s32 D_807FB5CC;
extern s32 D_807FB5D0;
extern struct CollisionTargetAngle *D_807FB5D8;

s32 func_806744A8(void *, s32, s32, s32, s32);
s32 actorCheckFacingTarget(Actor *);
void actorGetMatrix(struct ActorMtxOwner *owner, CollisionMtxF dst, s8 mtxIndex);
void matrix4Invert(CollisionMtxF, CollisionMtxF);
void func_8067A864(Actor *, Actor *, s16, s16, f32 *, f32 *, s8, s32, s32);
void actorReflectCollisionAngle(Actor *, void *, void *);
s32 actorGetCollisionThreshold(Actor *);
void func_8067A908(Actor *, Actor *, f32 *, f32 *, s8, s32, s32);
s32 actorIsTargetWithinAngle(s16, s16);

u8 actorCollisionReflectAndPush(Actor *self, Actor *other) {
    f32 posX;
    f32 posY;
    u8 hitMode;
    CollisionMtxF otherMtx;
    CollisionMtxF invMtx;
    f32 posZ;
    s32 i;
    f32 padD0[1];
    f32 localPos[3];
    f32 ptX[3];
    f32 ptY[3];
    f32 ptZ[3];
    f32 localPts[3][3];
    ActorCollisionBoundsFull *selfBounds;
    ActorCollisionBoundsFull *otherBounds;

    hitMode = 0;
    selfBounds = (ActorCollisionBoundsFull *)self->unk140;
    otherBounds = (ActorCollisionBoundsFull *)other->unk140;
    if (func_806744A8((CollisionTarget *)D_807FB5D8, selfBounds->unk0, selfBounds->unk4, selfBounds->unk8, selfBounds->unkC) == 0) {
        return 0;
    }
    if ((((CollisionActorFull *)self)->unk68 & 2) && (((CollisionActorFull *)other)->unk68 & 4)) {
        hitMode = 1;
    }
    if (actorCheckFacingTarget(self) == 0) {
        hitMode = 0;
    }
    if (((CollisionActorFull *)other)->unk68 & 8) {
        hitMode = 2;
    }
    selfBounds->unk58 = (s32)((u8 *)D_807FB5D8 - (u8 *)otherBounds->unkA4) / 88;
    actorGetMatrix((struct ActorMtxOwner *)otherBounds, otherMtx, ((CollisionTarget *)D_807FB5D8)->unk4E);
    matrix4Invert(invMtx, otherMtx);
    if (((CollisionActorFull *)other)->unk64 & 0x10) {
        posX = self->unk7C;
        posY = self->unk80;
        posZ = self->unk84;
    } else {
        posX = (f32)D_807FB5C4 / 8;
        posY = (f32)D_807FB5C8 / 8;
        posZ = (f32)D_807FB5CC / 8;
    }
    if (!(self->unk60 & 0x800)) {
        guMtxXFMF(invMtx, posX, posY, posZ, &localPos[0], &localPos[1], &localPos[2]);
    } else {
        localPos[0] = selfBounds->unkB8;
        localPos[1] = selfBounds->unkBC;
        localPos[2] = selfBounds->unkC0;
    }
    selfBounds->unkB8 = localPos[0];
    selfBounds->unkBC = localPos[1];
    selfBounds->unkC0 = localPos[2];

    ptX[0] = (f32)((CollisionTarget *)D_807FB5D8)->unk24 / 8;
    ptY[0] = (f32)((CollisionTarget *)D_807FB5D8)->unk28 / 8;
    ptZ[0] = (f32)((CollisionTarget *)D_807FB5D8)->unk2C / 8;
    ptX[1] = (f32)((CollisionTarget *)D_807FB5D8)->unk30 / 8;
    ptY[1] = (f32)((CollisionTarget *)D_807FB5D8)->unk34 / 8;
    ptZ[1] = (f32)((CollisionTarget *)D_807FB5D8)->unk38 / 8;
    ptX[2] = (f32)((CollisionTarget *)D_807FB5D8)->unk3C / 8;
    ptY[2] = (f32)((CollisionTarget *)D_807FB5D8)->unk40 / 8;
    ptZ[2] = (f32)((CollisionTarget *)D_807FB5D8)->unk44 / 8;

    for (i = 0; i < 3; i++) {
        guMtxXFMF(invMtx, ptX[i], ptY[i], ptZ[i], &localPts[i][0], &localPts[i][1], &localPts[i][2]);
    }

    selfBounds->unk66 = ((CollisionTarget *)D_807FB5D8)->unk48;
    if (((CollisionTarget *)D_807FB5D8)->unk4C != 0) {
        selfBounds->unk66 -= 0x800;
    }
    if (selfBounds->unk66 < 0) {
        selfBounds->unk66 += 0x1000;
    }

    switch (hitMode) {
    case 2:
        if (((CollisionActorFull *)self)->unk5C & 1) {
            actorReflectCollisionAngle(self, (CollisionTarget *)D_807FB5D8, selfBounds);
        }
    case 0:
        func_8067A908(self, other, &localPos[0], &localPts[0][0], ((CollisionTarget *)D_807FB5D8)->unk4E, D_807FB5D0, actorGetCollisionThreshold(self));
        break;
    case 1:
        func_8067A864(self, other, ((CollisionActorFull *)self)->unkE6, (s16)(s32)((CollisionActorFull *)self)->unkB8, &localPos[0], &localPts[0][0], ((CollisionTarget *)D_807FB5D8)->unk4E, D_807FB5D0, actorGetCollisionThreshold(self));
        if (actorIsTargetWithinAngle(gPlayerPadState.unk28, 400) && (f64)gPlayerPadState.unk4 > 30.0) {
            ((CollisionActorFull *)self)->unkE6 = selfBounds->unk66;
        }
        break;
    }
    return hitMode == 1;
}

#include "actor.h"

typedef f32 ActorMtxF[4][4];

typedef struct ActorMtxOwner {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
    u8 pad7C[0xC];
    s32 unk88;
} ActorMtxOwner;

extern u8 D_807444FC;
extern s32 gFrameCounter;
void actorGetMatrix(ActorMtxOwner *owner, ActorMtxF dst, s8 mtxIndex) {
    u8 bufIdx;
    Mtx *mtx;

    if (gFrameCounter == owner->unk88) {
        bufIdx = D_807444FC;
    } else {
        bufIdx = D_807444FC ^ 1;
    }
    mtx = owner->unk74[bufIdx];
    if (mtxIndex == -1) {
        memcpy(dst, owner->unk70, 0x40);
    } else {
        guMtxL2F(dst, &mtx[mtxIndex]);
    }
}

typedef struct ActorCollisionSub140 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x48];
    s16 unk58;
    u8 pad5A[0xE];
    s32 unk68;
    u8 pad6C[0x20];
    CollisionNode *unk8C;
    u8 pad90[0x14];
    s32 unkA4;
    s32 unkA8;
    u8 unkAC;
} ActorCollisionSub140;

extern u8 D_807FD614[];
extern u8 D_807FB603;
extern u8 D_807FB547;
extern void *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern s16 D_807FD584;

void func_80672E90(s32, s32, s32);
void actorSetCameraBoundaryMode(s32);
void actorSetTargetAngleBounds();
u8 func_806738D0(s32, s32, s32, s32, s32, s32);
u8 playerFindIndexByActor(Actor *);
void func_8067A99C(s32, Actor *, s32);
void func_8067A69C(s32, Actor *, f32, f32, u8, u8);

void actorCollisionResolveSurfaceHit(Actor *self, Actor *other, f32 *pos, f32 *verts, s8 mtxIndex, s32 hitRadius, s32 maxClamp, u8 flag) {
    ActorCollisionSub140 *selfBounds;
    ActorCollisionSub140 *otherBounds;
    CollisionNode *node;
    ActorMtxF selfMtx;
    f32 worldX;
    f32 worldY;
    f32 worldZ;
    f32 triX[3];
    f32 triY[3];
    f32 triZ[3];
    f32 edge1[3];
    f32 edge2[3];
    f32 cross[3];
    f32 normal[3];
    f32 scale;
    f32 norm;
    s32 clamp;
    u8 *p174;
    f32 scaledNormal[3];
    f32 *ptr3;
    f32 pushX;
    f32 pushZ;
    f32 *pTriX;
    f32 *pTriY;
    f32 *pVerts;
    u8 hit;

    selfBounds = (ActorCollisionSub140 *)self->unk140;
    otherBounds = (ActorCollisionSub140 *)other->unk140;
    D_807FB603 = selfBounds->unkAC;
    D_807FB5FD = 1;
    D_807FB600 = 1;
    D_807FB547 = 0;
    func_80672E90(otherBounds->unk0, otherBounds->unk4, otherBounds->unk8);
    actorSetCameraBoundaryMode(other->unk58);
    if (*(u8 *)&flag != 0) { // FAKE: address-taken flag stops cvt CSE (flag reloaded)
        hit = func_80673708(otherBounds->unk0, otherBounds->unk4, otherBounds->unk8, hitRadius, selfBounds->unkA4, selfBounds->unkA8, (s32)&other->unkF4, (s32)&other->unkF6);
    } else {
        actorSetTargetAngleBounds(selfBounds->unkA4 + otherBounds->unk58 * 0x58);
        if (!(self->unk64 & 0x10)) {
            hit = func_806738D0(otherBounds->unk0, otherBounds->unk4, otherBounds->unk8, hitRadius, selfBounds->unkA4, selfBounds->unkA8);
        } else {
            hit = func_80673708(otherBounds->unk0, otherBounds->unk4, otherBounds->unk8, hitRadius, selfBounds->unkA4, selfBounds->unkA8, (s32)&other->unkF4, (s32)&other->unkF6);
        }
    }
    if ((*(u8 *)&flag != 0) && ((f64)*(f32 *)(D_807FD614 + playerFindIndexByActor(other) * 0x34) > 30.0)) {
        hit = 1;
    }
    if (hit != 0) {
        actorGetMatrix((ActorMtxOwner *)selfBounds, selfMtx, mtxIndex);
        guMtxXFMF(selfMtx, pos[0], pos[1], pos[2], &worldX, &worldY, &worldZ);
        pushX = worldX;
        pVerts = verts;
        pTriX = triX;
        pTriY = triY;
        ptr3 = triZ;
        if (self->unk64 & 0x10) {
            pushZ = worldZ;
        } else {
            do {
                guMtxXFMF(selfMtx, pVerts[0], pVerts[1], pVerts[2], pTriX, pTriY, ptr3);
                ptr3 += 1;
                pVerts += 3;
                pTriX += 1;
                pTriY += 1;
            } while (ptr3 != &triY[0]);
            edge1[0] = triX[2] - triX[0];
            edge1[1] = triY[2] - triY[0];
            edge1[2] = triZ[2] - triZ[0];
            edge2[0] = triX[1] - triX[0];
            edge2[1] = triY[1] - triY[0];
            edge2[2] = triZ[1] - triZ[0];
            cross[0] = (edge1[1] * edge2[2]) - (edge1[2] * edge2[1]);
            cross[1] = (edge1[2] * edge2[0]) - (edge1[0] * edge2[2]);
            cross[2] = (edge1[0] * edge2[1]) - (edge1[1] * edge2[0]);
            norm = sqrtf((cross[0] * cross[0]) + (cross[1] * cross[1]) + (cross[2] * cross[2]));
            normal[0] = cross[0] / norm;
            normal[1] = cross[1] / norm;
            normal[2] = cross[2] / norm;
            if (other->unk5C & 1) {
                scale = (*(u8 *)(*(s32 *)&gPlayerSlots + (gCurrentPlayerIndex * 0x2F0) + 0x2C0) == 1 ? (f32)D_80753D50[D_807FD584] : (f32)D_80753D60[D_807FD584]) / 8;
                p174 = other->unk174;
                scaledNormal[0] = normal[0] * scale;
                scaledNormal[1] = normal[1] * scale;
                scaledNormal[2] = normal[2] * scale;
                *(f32 *)(p174 + 0xE0) = worldX - scaledNormal[0];
                *(f32 *)(p174 + 0xE4) = worldZ - scaledNormal[2];
            }
            if (otherBounds->unk68 != 0) {
                clamp = D_807FB5D0 = otherBounds->unk68 + 5;
                if (maxClamp < clamp) {
                    clamp = D_807FB5D0 = maxClamp;
                }
            } else {
                clamp = D_807FB5D0 = hitRadius;
                if (clamp < 0xF) {
                    clamp = D_807FB5D0 = 0xF;
                }
                if (maxClamp < clamp) {
                    clamp = D_807FB5D0 = maxClamp;
                }
            }
            normal[0] *= (f32)clamp / 8;
            normal[1] *= (f32)clamp / 8;
            normal[2] *= (f32)clamp / 8;
            do {} while (0); // FAKE: splits BB so pushX/pushZ can reuse $f0 after the CSE'd division
            pushX = worldX - normal[0];
            pushZ = worldZ - normal[2];
            func_8067A99C((s32)self, other, clamp);
        }
        func_8067A69C((s32)self, other, pushX, pushZ, 1, 1);
        for (node = otherBounds->unk8C; node != 0; node = node->next) {
            if (node->unk26 != 0) {
                other->unkFC |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, selfBounds->unkA4, selfBounds->unkA8, (s32)&other->unkF4, (s32)&other->unkF6);
            }
        }
    } else {
        for (node = otherBounds->unk8C; node != 0; node = node->next) {
            if (node->unk26 != 0) {
                other->unkFC |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, selfBounds->unkA4, selfBounds->unkA8, (s32)&other->unkF4, (s32)&other->unkF6);
            }
        }
    }
    other->unkFD = D_807FB547;
}
typedef struct CollisionTargetAngle {
    u8 pad0[0x48];
    s16 unk48;
    u8 pad4A[2];
    u8 unk4C;
} CollisionTargetAngle;
extern CollisionTargetAngle *D_807FB5D8;

s32 actorIsTargetWithinAngle(s16 angle, s16 threshold) {
    s16 targetAngle;
    s16 diff;

    targetAngle = D_807FB5D8->unk48;
    if (D_807FB5D8->unk4C != 0) {
        targetAngle -= 0x800;
    }
    if (targetAngle < 0) {
        targetAngle += 0x1000;
    }
    diff = targetAngle - angle;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x801) {
        diff = 0xFFF - diff;
    }
    if (diff < threshold) {
        return 1;
    }
    return 0;
}

s32 actorCheckFacingTarget(Actor *actor) {
    return actorIsTargetWithinAngle(actor->unkE6, 400);
}

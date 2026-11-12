#include "common.h"
#include "compiler/ido/memory.h"

#include "actor.h"
#include "sched.h"
#include "proto/global/2F550.h"
#include "proto/global/70FD0.h"
#include "proto/global/7BBD0.h"
#include "proto/global/7CA80.h"

extern u8 D_807FB600;
extern u8 D_807FB5FF;
extern u8 D_807FB5FD;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);
u8 func_80673708(s32, s32, s32, s32, CollisionBox *, CollisionBox *, s16 *, s16 *);

u8 actorCheckCollisionsAgainstActiveActors(Actor *self, s16 *arcMin, s16 *arcMax) {
    ActorSub140 *sub140;
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
    ModelNode *node;
    Actor *other;
    ActorSub140 *otherSub140;

    ret = 0;
    hitMask = 0;
    if (!(self->flags & 0x10)) {
        return 0;
    }
    sub140 = self->collision;
    posX = sub140->scaledX;
    posY = sub140->scaledY;
    posZ = sub140->scaledZ;
    radius = sub140->scaledRadius;
    D_807FB600 = 0;
    i = 0; if (gActiveActorCount > 0) { entry = gActiveActors; do { // LAYOUT: same-line preheader steers ugen tie-break order
        other = entry->actor;
        otherSub140 = other->collision;
        if (!(other->flags & 0x2000) && sub140 != otherSub140 && other->unk144 != 1 && (other->flags & 0x10)) {
            if (collisionSpheresOverlap(posX, posY, posZ, radius, otherSub140->scaledX, otherSub140->scaledY, otherSub140->scaledZ, otherSub140->scaledRadius)) {
                node = sub140->nodes;
                D_807FB5FF = 0;
                if (other->renderFlags & 0x20) {
                    D_807FB5FD = 0;
                } else {
                    D_807FB5FD = 1;
                }
                while (node != NULL && D_807FB5FF == 0) {
                    if (node->active != 0 && !(node->unk27 & 2)) {
                        hitMask |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, otherSub140->unkA4, otherSub140->unkA8, arcMin, arcMax);
                    }
                    node = node->next;
                }
                if (other->renderFlags & 0x20) {
                    self->hasArcBounds |= hitMask;
                }
                if (D_807FB5FF != 0) {
                    ret |= actorCollisionReflectAndPush(self, other);
                }
            }
        }
        i++; entry++; } while (i < gActiveActorCount); } // LAYOUT: increments on the loop-test line keep the sw t5 in the bnez delay slot
    return ret;
}

typedef f32 CollisionMtxF[4][4];

typedef struct CollisionPadD610 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x20];
    s16 unk28;
} CollisionPadD610;
extern CollisionPadD610 gPlayerPadState;

extern s32 D_807FB5C4;
extern s32 D_807FB5C8;
extern s32 D_807FB5CC;
extern s32 D_807FB5D0;
extern CollisionBox *D_807FB5D8;

s32 func_806744A8(CollisionBox *, s32, s32, s32, s32);

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
    ActorSub140 *selfBounds;
    ActorSub140 *otherBounds;

    hitMode = 0;
    selfBounds = self->collision;
    otherBounds = other->collision;
    if (func_806744A8(D_807FB5D8, selfBounds->scaledX, selfBounds->scaledY, selfBounds->scaledZ, selfBounds->scaledRadius) == 0) {
        return 0;
    }
    if ((self->flags2 & 2) && (other->flags2 & 4)) {
        hitMode = 1;
    }
    if (actorCheckFacingTarget(self) == 0) {
        hitMode = 0;
    }
    if (other->flags2 & 8) {
        hitMode = 2;
    }
    selfBounds->unk58 = D_807FB5D8 - otherBounds->unkA4;
    actorGetMatrix(otherBounds, otherMtx, D_807FB5D8->unk4E);
    matrix4Invert(invMtx, otherMtx);
    if (other->renderFlags & 0x10) {
        posX = self->x;
        posY = self->y;
        posZ = self->z;
    } else {
        posX = (f32)D_807FB5C4 / 8;
        posY = (f32)D_807FB5C8 / 8;
        posZ = (f32)D_807FB5CC / 8;
    }
    if (!(self->flags & 0x800)) {
        guMtxXFMF(invMtx, posX, posY, posZ, &localPos[0], &localPos[1], &localPos[2]);
    } else {
        localPos[0] = selfBounds->unkB8;
        localPos[1] = selfBounds->unkBC;
        localPos[2] = selfBounds->unkC0;
    }
    selfBounds->unkB8 = localPos[0];
    selfBounds->unkBC = localPos[1];
    selfBounds->unkC0 = localPos[2];

    ptX[0] = (f32)D_807FB5D8->x0 / 8;
    ptY[0] = (f32)D_807FB5D8->y0 / 8;
    ptZ[0] = (f32)D_807FB5D8->z0 / 8;
    ptX[1] = (f32)D_807FB5D8->x1 / 8;
    ptY[1] = (f32)D_807FB5D8->y1 / 8;
    ptZ[1] = (f32)D_807FB5D8->z1 / 8;
    ptX[2] = (f32)D_807FB5D8->x2 / 8;
    ptY[2] = (f32)D_807FB5D8->y2 / 8;
    ptZ[2] = (f32)D_807FB5D8->z2 / 8;

    for (i = 0; i < 3; i++) {
        guMtxXFMF(invMtx, ptX[i], ptY[i], ptZ[i], &localPts[i][0], &localPts[i][1], &localPts[i][2]);
    }

    selfBounds->unk66 = D_807FB5D8->unk48;
    if (D_807FB5D8->unk4C != 0) {
        selfBounds->unk66 -= 0x800;
    }
    if (selfBounds->unk66 < 0) {
        selfBounds->unk66 += 0x1000;
    }

    switch (hitMode) {
    case 2:
        if (self->collisionFlags & 1) {
            actorReflectCollisionAngle(self, D_807FB5D8, selfBounds);
        }
    case 0:
        actorAppendCallbackPayloadA908(self, other, &localPos[0], &localPts[0][0], D_807FB5D8->unk4E, D_807FB5D0, actorGetCollisionThreshold(self));
        break;
    case 1:
        actorAppendCallbackPayloadA864(self, other, self->yaw, (s16)(s32)self->speedXZ, &localPos[0], &localPts[0][0], D_807FB5D8->unk4E, D_807FB5D0, actorGetCollisionThreshold(self));
        if (actorIsTargetWithinAngle(gPlayerPadState.unk28, 400) && (f64)gPlayerPadState.unk4 > 30.0) {
            self->yaw = selfBounds->unk66;
        }
        break;
    }
    return hitMode == 1;
}


extern u8 gGfxBufferIndex;
void actorGetMatrix(ActorSub140 *owner, CollisionMtxF dst, s8 mtxIndex) {
    u8 bufIdx;
    Mtx *mtx;

    if (gFrameCounter == owner->unk88) {
        bufIdx = gGfxBufferIndex;
    } else {
        bufIdx = gGfxBufferIndex ^ 1;
    }
    mtx = owner->nodeMtx[bufIdx];
    if (mtxIndex == -1) {
        memcpy(dst, owner->modelMtxF, 0x40);
    } else {
        guMtxL2F(dst, &mtx[mtxIndex]);
    }
}

extern u8 D_807FD614[];
extern u8 D_807FB603;
extern u8 D_807FB547;
extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern s16 gCurrentCharacterIndex;

void func_80672E90(s32, s32, s32);
u8 func_806738D0(s32, s32, s32, s32, CollisionBox *, CollisionBox *);

void actorCollisionResolveSurfaceHit(Actor *self, Actor *other, f32 *pos, f32 *verts, s8 mtxIndex, s32 hitRadius, s32 maxClamp, u8 flag) {
    ActorSub140 *selfBounds;
    ActorSub140 *otherBounds;
    ModelNode *node;
    CollisionMtxF selfMtx;
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
    PlayerState *playerState;
    f32 scaledNormal[3];
    f32 *ptr3;
    f32 pushX;
    f32 pushZ;
    f32 *pTriX;
    f32 *pTriY;
    f32 *pVerts;
    u8 hit;

    selfBounds = self->collision;
    otherBounds = other->collision;
    D_807FB603 = selfBounds->unkAC;
    D_807FB5FD = 1;
    D_807FB600 = 1;
    D_807FB547 = 0;
    func_80672E90(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ);
    actorSetCameraBoundaryMode(other->actorType);
    if (flag != 0) {
        hit = func_80673708(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ, hitRadius, selfBounds->unkA4, selfBounds->unkA8, &other->arcYawMin, &other->arcYawMax);
    } else {
        actorSetTargetAngleBounds(selfBounds->unkA4 + otherBounds->unk58);
        if (!(self->renderFlags & 0x10)) {
            hit = func_806738D0(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ, hitRadius, selfBounds->unkA4, selfBounds->unkA8);
        } else {
            hit = func_80673708(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ, hitRadius, selfBounds->unkA4, selfBounds->unkA8, &other->arcYawMin, &other->arcYawMax);
        }
    }
    if ((*(u8 *)&flag != 0) && ((f64)*(f32 *)(D_807FD614 + playerFindIndexByActor(other) * 0x34) > 30.0)) { // FAKE: punned *(u8 *)&flag re-reads the u8 param from its stack home (lbu 343(sp) into t8, not a callee-saved copy)
        hit = 1;
    }
    if (hit != 0) {
        actorGetMatrix(selfBounds, selfMtx, mtxIndex);
        guMtxXFMF(selfMtx, pos[0], pos[1], pos[2], &worldX, &worldY, &worldZ);
        pushX = worldX;
        pVerts = verts;
        pTriX = triX;
        pTriY = triY;
        ptr3 = triZ;
        if (self->renderFlags & 0x10) {
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
            if (other->collisionFlags & 1) {
                scale = (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1 ? (f32)D_80753D50[gCurrentCharacterIndex] : (f32)D_80753D60[gCurrentCharacterIndex]) / 8;
                playerState = other->customState;
                scaledNormal[0] = normal[0] * scale;
                scaledNormal[1] = normal[1] * scale;
                scaledNormal[2] = normal[2] * scale;
                playerState->unkE0 = worldX - scaledNormal[0];
                playerState->unkE4 = worldZ - scaledNormal[2];
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
            actorAppendCallbackS32(self, other, clamp);
        }
        actorAppendMoveTarget2D(self, other, pushX, pushZ, 1, 1);
        for (node = otherBounds->nodes; node != 0; node = node->next) {
            if (node->active != 0) {
                other->hasArcBounds |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, selfBounds->unkA4, selfBounds->unkA8, &other->arcYawMin, &other->arcYawMax);
            }
        }
    } else {
        for (node = otherBounds->nodes; node != 0; node = node->next) {
            if (node->active != 0) {
                other->hasArcBounds |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, selfBounds->unkA4, selfBounds->unkA8, &other->arcYawMin, &other->arcYawMax);
            }
        }
    }
    other->collisionHit = D_807FB547;
}

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
    return actorIsTargetWithinAngle(actor->yaw, 400);
}

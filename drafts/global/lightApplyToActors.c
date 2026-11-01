// lightApplyToActors (src/global/5E2F0.c): lightApplyToActors (src/global/5E2F0.c): stage 4 (frame 0x158, prologue, stack layout dx/dy/dz 0x134, aX.. 0x124, scale 0x10C, angle 0x10A, spC8 0xC8 all identical; f20-f30 colouring dist/dot/scale/dirXYZ identical; 1241 insns vs 1240). Levers found: (1) angleRatio and scale are ONE variable (scale = y/dist2d; fix sign; scale = unk15E*0.4/scale); (2) decl order i,actorIdx,lightCount,light,actor,dot,dz,dy,dx,dist,aZ,aY,aX,dirZ,dirY,dirX,dist2d,maxDist,scale,angle,spC8,spC,innerDist,range,distFromInner,factor,alpha (arrays BEFORE the trailing unreferenced scalars so those get no slot); (3) dx/dy/dz must have LOW uopt priority (tail dead reads 'if (dx) {}' at function end = huge live range gives target colouring f0/f2/f14 split + memory home; natural cause unknown, original probably has a use-before-def path). Remaining diff: dy/dz colour order (mine dx f0, dz f2, dy f14; target dx f0 dy f2 dz f14 -> add refs to dy/dz priority ties), zero-const web (target keeps 0.0 in f22 across both dist==0.0f compares; mine rematerialises mtc1), as1 scheduling of the first sub/lwc1 group; later hunks (inner dist2d block, else branch) untouched. Fakes: tail dx/dy/dz reads + if (dist) {} in dot<0 block.
#include "common.h"
#include "actor.h"

extern s16 D_80748300;
typedef struct LightVolume {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B;
} LightVolume;

extern LightVolume D_807F7500[];

extern s32 D_80748304;
extern s32 D_80748308;
extern u8 gPlayerCount;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
s32 lightCheckPlayerDistance(LightVolume *);
void billboardSubmit(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void commandQueuePush(Actor *, s16, s16, s16, s32, s32, s32, s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void lightApplyToActors(void) {
    s32 i;
    s32 actorIdx;
    s32 lightCount;
    LightVolume *light;
    Actor *actor;
    f32 dot;
    f32 dz;
    f32 dy;
    f32 dx;
    f32 dist;
    f32 aZ;
    f32 aY;
    f32 aX;
    f32 dirZ;
    f32 dirY;
    f32 dirX;
    f32 dist2d;
    f32 maxDist;
    f32 scale;
    s16 angle;
    u8 spC8[64];
    f32 spC[2];
    f32 innerDist;
    f32 range;
    f32 distFromInner;
    f32 factor;
    f32 alpha;

    lightCount = 0;
    for (i = 0; i < gActiveActorCount; i++) {
        spC8[i] = 0;
    }
    {
        for (i = 0; i < D_80748300 && gPlayerCount < 3; i++) {
            light = &D_807F7500[i];
            if ((lightCheckPlayerDistance(light) != 0) && (lightCount < 12)) {
                lightCount++;
                for (actorIdx = 0; actorIdx < gActiveActorCount; actorIdx++) {
                    actor = gActiveActors[actorIdx].actor;
                    if (actor->unk60 & 0x2000) {
                        continue;
                    }
                    {
                        if (light->unk39 != 0) {
                            if (light->unk39 != 1) {
                                continue;
                            }
                            {
                                dx = light->unk24 - light->x;
                                dy = light->unk28 - light->y;
                                dz = light->unk2C - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (dist == 0.0f) {
                                    dist = 0.1f;
                                }
                                dirX = dx / dist;
                                dirY = dy / dist;
                                dirZ = dz / dist;

                                dx = actor->unk7C - light->x;
                                dy = actor->unk80 - light->y;
                                dz = actor->unk84 - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (dist == 0.0f) {
                                    dist = 0.1f;
                                }
                                aX = dx / dist;
                                aY = dy / dist;
                                aZ = dz / dist;

                                dot = (aZ * dirZ) + ((aX * dirX) + (aY * dirY));
                                if (dot < 0.0f) {
                                    dot = 0.0f;
                                    if (dist) {}  // FAKE: dist priority/colour order
                                }
                                if (dot >= light->unkC) {
                                    if (dot >= light->unk4) {
                                        dot = 1.0f;
                                    } else {
                                        dot = (dot - light->unkC) * light->unk10;
                                    }
                                    commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                        0xFF,
                                        (u32)((f32)light->unk36 * dot),
                                        (u32)((f32)light->unk37 * dot),
                                        (u32)((f32)light->unk38 * dot),
                                        0);
                                    if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                        dz = light->z - actor->unk84;
                                        dx = light->x - actor->unk7C;
                                        dist = sqrtf((dz * dz) + (dx * dx));
                                        dist2d = (dist != 0.0f) ? dist : 0.001f;
                                        scale = (light->y - actor->unk80) / dist2d;
                                        if (!(scale > 0.0f)) {
                                            scale = -scale;
                                        }
                                        if (scale == 0.0f) {
                                            scale = 0.1f;
                                        }
                                        scale = ((f32)actor->unk15E * 0.4f) / scale;
                                        angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                        if (actor->unk4 != NULL) {
                                            spC[0] = actor->unk4->unk34;
                                            spC[1] = actor->unk4->unk3C;
                                        } else {
                                            spC[0] = 0.15f;
                                            spC[1] = 0.15f;
                                        }
                                        alpha = actor->unk128 / 255.0;
                                        billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                                            (s32)(spC[0] * (f32)actor->unk16E[0]),
                                            (s32)(spC[1] * (f32)actor->unk16E[1]),
                                            1, 0x64,
                                            (u32)((f32)D_80748304 * dot * alpha),
                                            angle + 0xC00,
                                            scale * dot);
                                        spC8[actorIdx] = 1;
                                    }
                                }
                            }
                        } else {
                            dz = light->z - actor->unk84;
                            dx = light->x - actor->unk7C;
                            dy = light->y - actor->unk80;
                            dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy))) - (f32)*(s16 *)((u8 *)actor + 0xCE);
                            if (dist < 0.0) {
                                dist = 0.1f;
                            }
                            maxDist = light->unk14 * 1.3f;
                            if ((actor->unk60 & 0x01000000) && (dist < maxDist) && (actor->unk60 & 4)) {
                                dz = light->z - actor->unk84;
                                dx = light->x - actor->unk7C;
                                dist2d = sqrtf((dz * dz) + (dx * dx));
                                if (dist2d == 0.0f) {
                                    dist2d = 1.0f;
                                }
                                scale = (light->y - actor->unk80) / dist2d;
                                if (!(scale > 0.0f)) {
                                    scale = -scale;
                                }
                                if (scale == 0.0f) {
                                    scale = 0.1f;
                                }
                                scale = ((f32)actor->unk15E * 0.4f) / scale;
                                angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                if (scale > 10.0f) {
                                    scale = 10.0f;
                                }
                                if (actor->unk4 != NULL) {
                                    spC[0] = actor->unk4->unk34;
                                    spC[1] = actor->unk4->unk3C;
                                } else {
                                    spC[0] = 0.15f;
                                    spC[1] = 0.15f;
                                }
                                spC8[actorIdx] = 1;
                            }
                            innerDist = maxDist / 3.0f;
                            if (dist < innerDist) {
                                commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                    0xFF, light->unk36, light->unk37, light->unk38, 0);
                                if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                    alpha = actor->unk128 / 255.0;
                                    billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                                        (s32)(spC[0] * (f32)actor->unk16E[0]),
                                        (s32)(spC[1] * (f32)actor->unk16E[1]),
                                        1, 0x64,
                                        (u32)((f32)D_80748304 * alpha),
                                        angle + 0xC00,
                                        scale);
                                }
                            } else {
                                range = maxDist - innerDist;
                                distFromInner = dist - innerDist;
                                if (distFromInner < range) {
                                    factor = 1.0f - (distFromInner / range);
                                    commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                        0xFF,
                                        (u32)((f32)light->unk36 * factor),
                                        (u32)((f32)light->unk37 * factor),
                                        (u32)((f32)light->unk38 * factor),
                                        0);
                                    if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                        alpha = actor->unk128 / 255.0;
                                        billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                                            (s32)(spC[0] * (f32)actor->unk16E[0]),
                                            (s32)(spC[1] * (f32)actor->unk16E[1]),
                                            1, 0x64,
                                            (u32)((f32)D_80748304 * factor * alpha),
                                            angle + 0xC00,
                                            scale * factor);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < gActiveActorCount; i++) {
        {
            if (spC8[i] == 0) {
                actor = gActiveActors[i].actor;
                if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                    if (actor->unk4 != NULL) {
                        spC[0] = actor->unk4->unk34;
                        spC[1] = actor->unk4->unk3C;
                    } else {
                        spC[0] = 0.15f;
                        spC[1] = 0.15f;
                    }
                    alpha = actor->unk128 / 255.0;
                    billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                        (s32)(spC[0] * (f32)actor->unk16E[0]),
                        (s32)(spC[1] * (f32)actor->unk16E[1]),
                        1, 0x64,
                        (u32)((f32)D_80748308 * alpha),
                        0,
                        1.0f);
                }
            }
        }
    }
    if (dx) {}  // FAKE: extends live range (priority of dx/dy/dz below dirXYZ)
    if (dy) {}  // FAKE: extends live range (priority of dx/dy/dz below dirXYZ)
    if (dz) {}  // FAKE: extends live range (priority of dx/dy/dz below dirXYZ)
}

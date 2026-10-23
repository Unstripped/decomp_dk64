// func_8065A884 (src/global/5E2F0.c): func_8065A884 (src/global/5E2F0.c): stage 4, clean behaviourally equivalent C, matching callee-saved registers and frame size 0x160 vs 0x158
#include "common.h"
#include "actor.h"

typedef struct Cam2_Struct_3C {
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
} Cam2_Struct_3C;

extern s16 D_80748300;
extern s32 D_80748304;
extern s32 D_80748308;
extern u8 D_807FC928;
extern Cam2_Struct_3C D_807F7500[];
extern ActorEntry D_807FB930[];
extern u16 D_807FBB34;
s32 func_8065C240(Cam2_Struct_3C *);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8072177C(Actor *, s16, s16, s16, s32, s32, s32, s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_8065A884(void) {
    s32 lightCount;
    s32 lightIdx;
    s32 actorIdx;
    u8 spC8[64];
    Cam2_Struct_3C *light;
    Actor *actor;
    f32 intensity;
    f32 scale;
    s16 angle;
    f32 spC0;
    f32 spC4;
    f32 dist2d;
    f32 angleRatio;
    f32 dx, dy, dz;
    f32 dirX, dirY, dirZ;
    f32 aX, aY, aZ;
    f32 dist;
    f32 dist2;
    f32 dot;
    f32 maxDist;
    f32 innerDist;
    f32 range;
    f32 distFromInner;
    f32 factor;

    lightCount = 0;
    lightIdx = 0;
    if (D_807FBB34 > 0) {
        for (actorIdx = 0; actorIdx < D_807FBB34; actorIdx++) {
            spC8[actorIdx] = 0;
        }
    }
    if ((D_80748300 > 0) && (D_807FC928 < 3)) {
        for (lightIdx = 0; lightIdx < D_80748300; lightIdx++) {
            light = &D_807F7500[lightIdx];
            if ((func_8065C240(light) != 0) && (lightCount < 12)) {
                lightCount++;
                for (actorIdx = 0; actorIdx < D_807FBB34; actorIdx++) {
                    actor = D_807FB930[actorIdx].actor;
                    if (!(actor->unk60 & 0x2000)) {
                        if (light->unk39 != 0) {
                            if (light->unk39 == 1) {
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
                                dist2 = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (dist2 == 0.0f) {
                                    dist2 = 0.1f;
                                }
                                aX = dx / dist2;
                                aY = dy / dist2;
                                aZ = dz / dist2;

                                dot = (aZ * dirZ) + ((aX * dirX) + (aY * dirY));
                                if (dot < 0.0f) {
                                    dot = 0.0f;
                                }
                                if (dot >= light->unkC) {
                                    if (dot >= light->unk4) {
                                        intensity = 1.0f;
                                    } else {
                                        intensity = (dot - light->unkC) * light->unk10;
                                    }
                                    func_8072177C(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                        0xFF,
                                        (u32)((f32)light->unk36 * intensity),
                                        (u32)((f32)light->unk37 * intensity),
                                        (u32)((f32)light->unk38 * intensity),
                                        0);
                                    if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                        dz = light->z - actor->unk84;
                                        dx = light->x - actor->unk7C;
                                        dist2d = sqrtf((dz * dz) + (dx * dx));
                                        if (dist2d != 0.0f) {
                                        } else {
                                            dist2d = 0.001f;
                                        }
                                        angleRatio = (light->y - actor->unk80) / dist2d;
                                        if (!(angleRatio > 0.0f)) {
                                            angleRatio = -angleRatio;
                                        }
                                        if (angleRatio == 0.0f) {
                                            angleRatio = 0.1f;
                                        }
                                        scale = ((f32)actor->unk15E * 0.4f) / angleRatio;
                                        angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                        if (actor->unk4 != NULL) {
                                            spC0 = actor->unk4->unk34;
                                            spC4 = actor->unk4->unk3C;
                                        } else {
                                            spC0 = 0.15f;
                                            spC4 = 0.15f;
                                        }
                                        func_8065D254(actor, 0x3C9, 0x40, 0x40,
                                            (s32)(spC0 * (f32)actor->unk16E[0]),
                                            (s32)(spC4 * (f32)actor->unk16E[1]),
                                            1, 0x64,
                                            (u32)((f32)D_80748304 * intensity * ((f64)actor->unk128 / 255.0)),
                                            angle + 0xC00,
                                            scale * intensity);
                                        spC8[actorIdx] = 1;
                                    }
                                }
                            }
                        } else {
                            dz = light->z - actor->unk84;
                            dx = light->x - actor->unk7C;
                            dy = light->y - actor->unk80;
                            dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy))) - (f32)*(s16 *)((u8 *)actor + 0xCE);
                            if (dist < 0.0f) {
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
                                angleRatio = (light->y - actor->unk80) / dist2d;
                                if (!(angleRatio > 0.0f)) {
                                    angleRatio = -angleRatio;
                                }
                                if (angleRatio == 0.0f) {
                                    angleRatio = 0.1f;
                                }
                                scale = ((f32)actor->unk15E * 0.4f) / angleRatio;
                                angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                if (scale > 10.0f) {
                                    scale = 10.0f;
                                }
                                if (actor->unk4 != NULL) {
                                    spC0 = actor->unk4->unk34;
                                    spC4 = actor->unk4->unk3C;
                                } else {
                                    spC0 = 0.15f;
                                    spC4 = 0.15f;
                                }
                                spC8[actorIdx] = 1;
                            }
                            innerDist = maxDist / 3.0f;
                            if (dist < innerDist) {
                                func_8072177C(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                    0xFF, light->unk36, light->unk37, light->unk38, 0);
                                if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                    func_8065D254(actor, 0x3C9, 0x40, 0x40,
                                        (s32)(spC0 * (f32)actor->unk16E[0]),
                                        (s32)(spC4 * (f32)actor->unk16E[1]),
                                        1, 0x64,
                                        (u32)((f32)D_80748304 * ((f64)actor->unk128 / 255.0)),
                                        angle + 0xC00,
                                        scale);
                                }
                            } else {
                                range = maxDist - innerDist;
                                distFromInner = dist - innerDist;
                                if (distFromInner < range) {
                                    factor = 1.0f - (distFromInner / range);
                                    func_8072177C(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                        0xFF,
                                        (u32)((f32)light->unk36 * factor),
                                        (u32)((f32)light->unk37 * factor),
                                        (u32)((f32)light->unk38 * factor),
                                        0);
                                    if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                        func_8065D254(actor, 0x3C9, 0x40, 0x40,
                                            (s32)(spC0 * (f32)actor->unk16E[0]),
                                            (s32)(spC4 * (f32)actor->unk16E[1]),
                                            1, 0x64,
                                            (u32)((f32)D_80748304 * factor * ((f64)actor->unk128 / 255.0)),
                                            angle + 0xC00,
                                            scale * factor);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (D_807FC928 >= 3) {
                break;
            }
        }
    }
    if (D_807FBB34 > 0) {
        for (actorIdx = 0; actorIdx < D_807FBB34; actorIdx++) {
            if (spC8[actorIdx] == 0) {
                actor = D_807FB930[actorIdx].actor;
                if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                    if (actor->unk4 != NULL) {
                        spC0 = actor->unk4->unk34;
                        spC4 = actor->unk4->unk3C;
                    } else {
                        spC0 = 0.15f;
                        spC4 = 0.15f;
                    }
                    func_8065D254(actor, 0x3C9, 0x40, 0x40,
                        (s32)(spC0 * (f32)actor->unk16E[0]),
                        (s32)(spC4 * (f32)actor->unk16E[1]),
                        1, 0x64,
                        (u32)((f32)D_80748308 * ((f64)actor->unk128 / 255.0)),
                        0,
                        1.0f);
                }
            }
        }
    }
}

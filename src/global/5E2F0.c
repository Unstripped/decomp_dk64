#include "common.h"
#include "actor.h"

extern u8 D_807F7EF8;
extern s16 D_807F7EFA;
extern s16 D_807F7EFC;

void lightSetFlags(u8 arg0) {
    D_807F7EF8 = arg0;
}

void lightSetTargetId(s16 arg0) {
    D_807F7EFA = arg0;
}

void lightSetRadius(s16 arg0) {
    D_807F7EFC = arg0;
}

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;

void lightGetColor(f32 *arg0, f32 *arg1, f32 *arg2, s16 arg3) {
    *arg0 = D_8076A0B4[arg3];
    *arg1 = D_8076A0B8[arg3];
    *arg2 = D_8076A0BC[arg3];
}

extern s32 D_807F6C28;

void lightSetColor(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    u8 count;
    s32 i;

    if (D_807F6C28 <= 0) {
        count = 1;
    } else {
        count = D_807F6C28;
    }
    if (arg3 != -1) {
        if (arg3 < count) {
            D_8076A0B4[arg3] = (arg0 <= 1.0f) ? arg0 : 1.0f;
            D_8076A0B8[arg3] = (arg1 <= 1.0f) ? arg1 : 1.0f;
            D_8076A0BC[arg3] = (arg2 <= 1.0f) ? arg2 : 1.0f;
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = (arg0 <= 1.0f) ? arg0 : 1.0f;
            D_8076A0B8[i] = (arg1 <= 1.0f) ? arg1 : 1.0f;
            D_8076A0BC[i] = (arg2 <= 1.0f) ? arg2 : 1.0f;
        }
    }
}

extern f32 *D_8076A0C0;
extern f32 *D_8076A0C4;
extern f32 *D_8076A0C8;

void lightCopyTargetColors(s16 arg0) {
    u8 count;
    s32 i;

    if (D_807F6C28 <= 0) {
        count = 1;
    } else {
        count = D_807F6C28;
    }

    if (arg0 != -1) {
        if (arg0 < count) {
            D_8076A0B4[arg0] = D_8076A0C0[arg0];
            D_8076A0B8[arg0] = D_8076A0C4[arg0];
            D_8076A0BC[arg0] = D_8076A0C8[arg0];
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = D_8076A0C0[i];
            D_8076A0B8[i] = D_8076A0C4[i];
            D_8076A0BC[i] = D_8076A0C8[i];
        }
    }
}

void lightSetTargetColor(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    u8 count;
    u8 i;

    if (D_807F6C28 <= 0) {
        count = 1;
    } else {
        count = D_807F6C28;
    }

    if (arg3 != -1) {
        if (arg0 <= 1.0f) {
            D_8076A0C0[arg3] = arg0;
        } else {
            D_8076A0C0[arg3] = 1.0f;
        }
        if (arg1 <= 1.0f) {
            D_8076A0C4[arg3] = arg1;
        } else {
            D_8076A0C4[arg3] = 1.0f;
        }
        if (arg2 <= 1.0f) {
            D_8076A0C8[arg3] = arg2;
        } else {
            D_8076A0C8[arg3] = 1.0f;
        }
    } else {
        for (i = 0; i < count; i++) {
            if (arg0 <= 1.0f) {
                D_8076A0C0[i] = arg0;
            } else {
                D_8076A0C0[i] = 1.0f;
            }
            if (arg1 <= 1.0f) {
                D_8076A0C4[i] = arg1;
            } else {
                D_8076A0C4[i] = 1.0f;
            }
            if (arg2 <= 1.0f) {
                D_8076A0C8[i] = arg2;
            } else {
                D_8076A0C8[i] = 1.0f;
            }
        }
    }
}

void lightLerpColors(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    u8 count;
    s32 i;

    if (D_807F6C28 <= 0) {
        count = 1;
    } else {
        count = D_807F6C28;
    }

    if (arg4 != -1) {
        if (arg4 < count) {
            D_8076A0B4[arg4] = ((D_8076A0C0[arg4] - arg0) * arg3) + arg0;
            D_8076A0B8[arg4] = ((D_8076A0C4[arg4] - arg1) * arg3) + arg1;
            D_8076A0BC[arg4] = ((D_8076A0C8[arg4] - arg2) * arg3) + arg2;
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = ((D_8076A0C0[i] - arg0) * arg3) + arg0;
            D_8076A0B8[i] = ((D_8076A0C4[i] - arg1) * arg3) + arg1;
            D_8076A0BC[i] = ((D_8076A0C8[i] - arg2) * arg3) + arg2;
        }
    }
}

f32 func_80612D10(f32);
extern s16 D_80748300;
extern f32 D_807F7ECC;
extern f32 D_807F7ED0;
extern f32 D_807F7ED4;
extern f32 D_807F7ED8;
extern f32 D_807F7EDC;
extern f32 D_807F7EE0;
extern f32 D_807F7EE4;
extern f32 D_807F7EE8;
extern s16 D_807F7EFE;

void lightInitGlobals(void) {
    D_807F7ECC = func_80612D10(0.4363323152f);
    D_807F7ED0 = func_80612D10(1.134464025f);
    D_807F7ED4 = 1.0f / (D_807F7ECC - D_807F7ED0);
    D_807F7ED8 = D_807F7ECC;
    D_807F7EDC = D_807F7ED0;
    D_807F7EE0 = D_807F7ED4;
    D_807F7EE4 = 25.0f;
    D_807F7EE8 = 65.0f;
    D_80748300 = 0;
    D_807F7EF8 = 0;
    D_807F7EFA = -1;
    D_807F7EFC = 700;
    D_807F7EFE = 600;
}

void lightClearCount(void) {
    D_80748300 = 0;
}

extern s16 D_807F7EC8;
void lightClearActiveCount(void) {
    D_807F7EC8 = 0;
}

void lightSetFovAngles(f32 arg0, f32 arg1) {
    D_807F7EE4 = arg0;
    D_807F7EE8 = arg1;
    D_807F7ED8 = func_80612D10(arg0 * 0.017453292f);
    D_807F7EDC = func_80612D10(arg1 * 0.017453292f);
    D_807F7EE0 = 1.0f / (D_807F7ED8 - D_807F7EDC);
}

void lightSetDistanceThreshold(s16 arg0) {
    D_807F7EFE = arg0;
}

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

void lightAdd(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10) {
    if (D_80748300 != 0x10) {
        D_807F7500[D_80748300].unk34 = D_807F7EFE;
        D_807F7500[D_80748300].unk3A = D_807F7EF8;
        D_807F7500[D_80748300].unk30 = D_807F7EFA;
        D_807F7500[D_80748300].unk32 = D_807F7EFC;
        D_807F7500[D_80748300].unk8 = D_807F7EE8;
        D_807F7500[D_80748300].unk0 = D_807F7EE4;
        D_807F7500[D_80748300].unkC = D_807F7EDC;
        D_807F7500[D_80748300].unk4 = D_807F7ED8;
        D_807F7500[D_80748300].unk39 = arg7;
        D_807F7500[D_80748300].x = arg0;
        D_807F7500[D_80748300].y = arg1;
        D_807F7500[D_80748300].unk10 = D_807F7EE0;
        D_807F7500[D_80748300].z = arg2;
        D_807F7500[D_80748300].unk24 = arg3;
        D_807F7500[D_80748300].unk28 = arg4;
        D_807F7500[D_80748300].unk2C = arg5;
        D_807F7500[D_80748300].unk14 = arg6;
        D_807F7500[D_80748300].unk36 = arg8;
        D_807F7500[D_80748300].unk37 = arg9;
        D_807F7500[D_80748300].unk38 = arg10;
        D_80748300++;
        D_807F7ED8 = D_807F7ECC;
        D_807F7EDC = D_807F7ED0;
        D_807F7EE0 = D_807F7ED4;
        D_807F7EE4 = 25.0f;
        D_807F7EE8 = 65.0f;
        D_807F7EF8 = 0;
        D_807F7EFA = -1;
        D_807F7EFC = 700;
        D_807F7EFE = 600;
    }
}

extern s32 D_80748304;
extern s32 D_80748308;
extern u8 D_807FC928;
extern ActorEntry D_807FB930[];
extern u16 D_807FBB34;
s32 lightCheckPlayerDistance(LightVolume *);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8072177C(Actor *, s16, s16, s16, s32, s32, s32, s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

#ifdef NON_MATCHING
void func_8065A884(void) {
    s32 lightCount;
    s32 lightIdx;
    s32 actorIdx;
    u8 spC8[64];
    LightVolume *light;
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
            if ((lightCheckPlayerDistance(light) != 0) && (lightCount < 12)) {
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A884.s")
#endif

typedef struct LightTrigger {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
} LightTrigger;

extern LightTrigger D_807F78C0[];
extern LightTrigger D_807F7BC8[];
extern s16 D_807F7BC0;
void lightAddDedupEntry(s16);
s32 lightCheckVolumeBounds(LightVolume *, f32, f32, f32, s16, s16, s16, s16, s16, s16, s32);
#ifdef NON_MATCHING
s16 func_8065BAA0(volatile f32 arg0, volatile f32 arg1, volatile f32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, s8 *arg10) {
    f32 diff[6];
    s32 i;
    LightVolume *var_s0;
    f32 dist;
    f32 temp_fa0, temp_fa1;
    f32 temp_f1;
    f32 temp_ft4, temp_ft5, temp_ft2;
    f32 three;
    s16 a3 = arg3;
    s16 a4 = arg4;
    s16 a5 = arg5;
    s16 a6 = arg6;

    *arg10 = 0;
    D_807F7BC0 = 0;
    three = 3.0f;
    var_s0 = D_807F7500;
    for (i = 0; i < D_80748300; i++, var_s0++) {
        if (lightCheckVolumeBounds(var_s0, arg0, arg1, arg2, a3, a4, a5, a6, arg7, arg8, arg9)) {
            if (D_807F7BC0 < 12) {
                if (var_s0->unk3A & 1) {
                    *arg10 = 1;
                }
                D_807F78C0[D_807F7BC0].unk3F = i;
                D_807F78C0[D_807F7BC0].unk38 = var_s0->x * 3.0f;
                D_807F78C0[D_807F7BC0].unk3A = var_s0->y * 3.0f;
                D_807F78C0[D_807F7BC0].unk3C = var_s0->z * 3.0f;
                D_807F78C0[D_807F7BC0].unk2C = (f64)(u32)var_s0->unk36 / 255.0;
                D_807F78C0[D_807F7BC0].unk30 = (f64)(u32)var_s0->unk37 / 255.0;
                D_807F78C0[D_807F7BC0].unk34 = (f64)(u32)var_s0->unk38 / 255.0;
                D_807F78C0[D_807F7BC0].unk3E = var_s0->unk39;
                switch (var_s0->unk39) {
                case 1:
                    diff[0] = var_s0->unk24 - var_s0->x;
                    diff[1] = var_s0->unk28 - var_s0->y;
                    diff[2] = var_s0->unk2C - var_s0->z;
                    dist = sqrtf((diff[2] * diff[2]) + ((diff[0] * diff[0]) + (diff[1] * diff[1])));
                    if (dist == 0.0f) {
                        dist = 0.1f;
                    }
                    D_807F78C0[D_807F7BC0].unk18 = 0x127690;
                    D_807F78C0[D_807F7BC0].unk4 = var_s0->unk4;
                    D_807F78C0[D_807F7BC0].unkC = diff[0] / dist;
                    D_807F78C0[D_807F7BC0].unk0 = var_s0->unkC;
                    D_807F78C0[D_807F7BC0].unk10 = diff[1] / dist;
                    D_807F78C0[D_807F7BC0].unk8 = var_s0->unk10;
                    D_807F78C0[D_807F7BC0].unk14 = diff[2] / dist;
                    break;
                case 0:
                    if (var_s0->unk14 == 0.0f) {
                        var_s0->unk14 = 0.1f;
                    }
                    temp_fa0 = var_s0->unk14 * 3.0f;
                    temp_f1 = var_s0->unk14 / three;
                    temp_fa1 = temp_f1 * 3.0f;
                    D_807F78C0[D_807F7BC0].unk20 = temp_fa1;
                    D_807F78C0[D_807F7BC0].unk18 = (s32)(temp_fa0 * temp_fa0);
                    D_807F78C0[D_807F7BC0].unk1C = 1.0f / (temp_fa0 - temp_fa1);
                    temp_ft4 = var_s0->unk14 * 1.3f;
                    temp_f1 = temp_ft4 / three;
                    temp_ft5 = temp_f1 * 3.0f;
                    temp_ft2 = temp_ft4 * 3.0f;
                    D_807F78C0[D_807F7BC0].unk28 = temp_ft5;
                    D_807F78C0[D_807F7BC0].unk24 = 1.0f / (temp_ft2 - temp_ft5);
                    break;
                }
                lightAddDedupEntry(D_807F7BC0);
                D_807F7BC0++;
            }
        }
    }
    return D_807F7BC0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065BAA0.s")
#endif
void *memcpy(void *, const void *, unsigned int);

void lightAddDedupEntry(s16 arg0) {
    s32 i;
    u8 val;

    if (D_807F7EC8 != 12) {
        val = D_807F78C0[arg0].unk3F;
        for (i = 0; i < D_807F7EC8; i++) {
            if (val == D_807F7BC8[i].unk3F) {
                return;
            }
        }
        memcpy(&D_807F7BC8[D_807F7EC8++], &D_807F78C0[arg0], sizeof(LightTrigger));
    }
}

void func_8062A944(f32, f32, f32);
void func_8062AC68(Mtx *);
void func_8062AD28(f32, f32, f32, void *, void *);
void func_8062DB70(f32, f32, f32, f32, f32, f32);
s32 func_8062DBDC(s16, s16, s16, s16, s32, s32, f32, f32, f32, f32, void *);
extern u8 D_807F5E20[];
extern u8 D_807F5E68[];

s32 lightCheckVolumeBounds(LightVolume *arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 arg10) {
    Mtx sp60;
    f32 dx, dy;

    if ((arg0->unk3A & 2) && (arg10 != arg0->unk30) && (arg4 != -0x8000)) {
        return 0;
    }

    dx = arg0->x - arg1;
    dy = arg0->y - arg2;
    if (sqrtf((dx * dx) + (dy * dy) + ((arg0->z - arg3) * (arg0->z - arg3))) < (f32)arg0->unk32) {
        if (arg4 == -0x8000) {
            return 1;
        }
        switch (arg0->unk39) {
        case 0:
            if ((arg0->x < (f32)arg4 - arg0->unk14) ||
                (arg0->y < (f32)arg5 - arg0->unk14) ||
                (arg0->z < (f32)arg6 - arg0->unk14) ||
                ((f32)arg7 + arg0->unk14 < arg0->x) ||
                ((f32)arg8 + arg0->unk14 < arg0->y) ||
                ((f32)arg9 + arg0->unk14 < arg0->z)) {
                return 0;
            }
            return 1;
        case 1:
            guLookAt(&sp60, arg0->x, arg0->y, arg0->z, (arg0->x == arg0->unk24) ? (arg0->unk24 + 0.2f) : arg0->unk24, arg0->unk28, arg0->unk2C, 0.0f, 1.0f, 0.0f);
            func_8062A944(arg0->unk8 * 2, 1.0f, (f32)arg0->unk34);
            func_8062AC68(&sp60);
            func_8062AD28(arg0->x, arg0->y, arg0->z, &D_807F5E68, &D_807F5E20);
            func_8062DB70(arg0->x, arg0->y, arg0->z, arg0->unk24, arg0->unk28, arg0->unk2C);
            return func_8062DBDC(arg4, arg5, arg6, arg7, arg8, arg9, arg0->x, arg0->y, arg0->z, (f32)arg0->unk34, &D_807F5E68);
        }
        return 0;
    }
    return 0;
}

typedef struct LightPlayer {
    u8 unk0;
    u8 pad1[0x20F];
    f32 x;
    f32 y;
    f32 z;
    u8 pad21C[0xD4];
} LightPlayer;


extern LightPlayer *D_807FC924;
extern u8 D_80750AB4;
#define SQ(x) ((x) * (x))

s32 lightCheckPlayerDistance(LightVolume *arg0) {
    s32 i;
    LightPlayer *player;

    for (i = 0; i < D_80750AB4; i++) {
        player = (LightPlayer *)((u8 *)D_807FC924 + (i * sizeof(LightPlayer)));
        if (player->unk0 != 0) {
            if (sqrtf(SQ(arg0->z - player->z) + (SQ(arg0->x - player->x) + SQ(arg0->y - player->y))) < (f32)arg0->unk32) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_80651B64(s16);

#ifdef NON_MATCHING
void func_8065C334(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, u8 *arg5, u8 *arg6, s16 arg7) {
    f32 diff[14];
    LightTrigger *entry;
    f32 r;
    f32 g;
    f32 b;
    s32 three;

    if (func_80651B64(arg7) == 0) {
        *arg6 = 0xFF;
        *arg5 = 0xFF;
        *arg4 = 0xFF;
        return;
    }
    if (D_807F7EC8 == 0) {
        *arg4 = (s32)(D_8076A0B4[arg7] * 255.0f);
        *arg5 = (s32)(D_8076A0B8[arg7] * 255.0f);
        *arg6 = (s32)(D_8076A0BC[arg7] * 255.0f);
        return;
    }
    r = D_8076A0B4[arg7];
    g = D_8076A0B8[arg7];
    b = D_8076A0BC[arg7];
    if (D_807F7EC8 > 0) {
        three = 3;
        entry = D_807F7BC8;
        do {
            switch (entry->unk3E) {
            default:
                break;
            case 1: {
                f32 dist;
                f32 dot;
                f32 factor;

                diff[0] = arg0 - (f32)(entry->unk38 / three);
                diff[1] = arg1 - (f32)(entry->unk3A / three);
                diff[2] = arg2 - (f32)(entry->unk3C / three);
                dist = sqrtf((diff[2] * diff[2]) + ((diff[0] * diff[0]) + (diff[1] * diff[1])));
                if (dist == 0.0f) {
                    dist = 0.1f;
                }
                diff[3] = diff[0] / dist;
                diff[4] = diff[1] / dist;
                diff[5] = diff[2] / dist;
                dot = (entry->unk14 * diff[5]) + ((diff[3] * entry->unkC) + (diff[4] * entry->unk10));
                if (dot < 0.0f) {
                    dot = 0.0f;
                }
                if (entry->unk0 <= dot) {
                    if (entry->unk4 <= dot) {
                        factor = (dot - entry->unk0) * entry->unk8;
                    } else {
                        factor = 1.0f;
                    }
                    if ((f64)dist > 300.0) {
                        if ((f64)dist > 1100.0) {
                            factor = 0.0f;
                        } else {
                            factor = (f64)factor * (1.0 - (((f64)dist - 300.0) / 800.0));
                        }
                    }
                    r += entry->unk2C * factor;
                    g += entry->unk30 * factor;
                    b += entry->unk34 * factor;
                }
                break;
            }
            case 0: {
                f32 dist;
                f32 diff_val;
                f32 range;
                f32 max_range;
                f32 factor;
                diff[2] = (f32)(entry->unk3C / three) - arg2;
                diff[0] = (f32)(entry->unk38 / three) - arg0;
                diff[1] = (f32)(entry->unk3A / three) - arg1;
                dist = sqrtf((diff[2] * diff[2]) + ((diff[0] * diff[0]) + (diff[1] * diff[1])));
                diff_val = dist - (f32)arg3;
                if (dist <= (f32)arg3) {
                    diff_val = 0.1f;
                }
                range = entry->unk28 / 3.0f;
                if (diff_val < range) {
                    r += entry->unk2C;
                    g += entry->unk30;
                    b += entry->unk34;
                } else {
                    max_range = ((1.0f / entry->unk24) / 3.0f) - range;
                    if ((diff_val - range) < max_range) {
                        factor = 1.0f - ((diff_val - range) / max_range);
                        r += entry->unk2C * factor;
                        g += entry->unk30 * factor;
                        b += entry->unk34 * factor;
                    }
                }
                break;
            }
            }
            entry++;
        } while (entry < &D_807F7BC8[D_807F7EC8]);
    }
    if (r > 1.0f) {
        r = 1.0f;
    }
    if (g > 1.0f) {
        g = 1.0f;
    }
    if (b > 1.0f) {
        b = 1.0f;
    }
    *arg4 = (s32)(r * 255.0f);
    *arg5 = (s32)(g * 255.0f);
    *arg6 = (s32)(b * 255.0f);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065C334.s")
#endif

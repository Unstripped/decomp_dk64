// lightApplyToActors (src/global/5E2F0.c): Light(u6): count-exact (1159=1159), frame 344, saved set identical; blocks 136 vs 135 (one extra real compare block from a dx dead test); deadsweep full 366 text 348 shape 146 (was 698/717). KEY: callee prototypes fixed to definition widths FIRST (billboardSubmit(Actor*,s16,s16,s16,s16,s16,u8,s16,u8,s16,f32), commandQueuePush(Actor*,s16,s16,s16,u8,u8,u8,u8,u8), s32 mathAngleBetweenPoints2D): 698->469 with no other change (unit_check protos). Then annealed guarded dead tests (count weight 8, block weight 30). Needs the three prototypes in the file head (they sit just above the function). Remaining: dx/dy/dz and a-vec colouring, final-loop consts (255.0/0.15f/1.0f) not hoisted into f20-f24, zero web f22.
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
    dx = 0.0f;  // FAKE: define dx for tail dead reads
    dy = 0.0f;  // FAKE: define dy for tail dead reads
    dz = 0.0f;  // FAKE: define dz for tail dead reads
    for (i = 0; i < gActiveActorCount; i++) {
        spC8[i] = 0;
    }
    {
        for (i = 0; i < D_80748300 && gPlayerCount < 3; i++) {
            light = &D_807F7500[i];
            if (light->x > 0.0f) {}  // FAKE: dead test
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
                if (dx > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                dy = light->unk28 - light->y;
                                dz = light->unk2C - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (gActiveActorCount && gActiveActorCount) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (dist == 0.0f) {
                                    dist = 0.1f;
                                    if (actor && actor) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (dx) {}  // FAKE: dead test
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
                                if (actor == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                aZ = dz / dist;
                                if (gPlayerCount) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (aZ > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)

                                dot = (aZ * dirZ) + ((aX * dirX) + (aY * dirY));
                                if (dot < 0.0f) {
                                    dot = 0.0f;
                                    if (aY > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                }
                                if (dot >= light->unkC) {
                                    if (dot >= light->unk4) {
                                        dot = 1.0f;
                                    } else {
                                        dot = (dot - light->unkC) * light->unk10;
                                        if (dot < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        if (actor == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        if (D_80748300 == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                    }
                                    commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                        0xFF,
                                        (u32)((f32)light->unk36 * dot),
                                        (u32)((f32)light->unk37 * dot),
                                        (u32)((f32)light->unk38 * dot),
                                        0);
                                        if (dirX > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                    if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                        dist = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + ((light->x - actor->unk7C) * (light->x - actor->unk7C)));
                                if (gActiveActorCount && gActiveActorCount) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        dist2d = (dist != 0.0f) ? dist : 0.001f;
                            if (dy > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                            if (dz) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        scale = (light->y - actor->unk80) / dist2d;
                                        if (!(scale > 0.0f)) {
                                            scale = -scale;
                                if (dist == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        }
                                        if (scale == 0.0f) {
                                            scale = 0.1f;
                                        if (dy < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        }
                                        scale = ((f32)actor->unk15E * 0.4f) / scale;
                                    if (aY) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (dz < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (dirY < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                        if (actor->unk4 != NULL) {
                                            spC[0] = actor->unk4->unk34;
                                            if (actorIdx) {}  // FAKE: regalloc/count steer (annealed dead test)
                if (dx > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                            spC[1] = actor->unk4->unk3C;
                                if (scale) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        if (dx) {}  // FAKE: x
                                        } else {
                                            spC[0] = 0.15f;
                                            spC[1] = 0.15f;
                                        }
                                        alpha = actor->unk128 / 255.0;
                                if (maxDist < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                                            (s32)(spC[0] * (f32)actor->unk16E[0]),
                                            (s32)(spC[1] * (f32)actor->unk16E[1]),
                                            1, 0x64,
                                            (u32)((f32)D_80748304 * dot * alpha),
                                            angle + 0xC00,
                                            scale * dot);
                                            if (actor) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        spC8[actorIdx] = 1;
                                    }
                                }
                            }
                        } else {
                            dist = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + (((light->x - actor->unk7C) * (light->x - actor->unk7C)) + ((light->y - actor->unk80) * (light->y - actor->unk80)))) - (f32)*(s16 *)((u8 *)actor + 0xCE);
                            if (dist < 0.0) {
                                dist = 0.1f;
                            }
                            maxDist = light->unk14 * 1.3f;
                            if ((actor->unk60 & 0x01000000) && (dist < maxDist) && (actor->unk60 & 4)) {
                                dist2d = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + ((light->x - actor->unk7C) * (light->x - actor->unk7C)));
                                if (dist2d == 0.0f) {
                                    dist2d = 1.0f;
                                }
                                scale = (light->y - actor->unk80) / dist2d;
                                if (dy > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (maxDist) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (!(scale > 0.0f)) {
                                    scale = -scale;
                                    if (dy == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (D_80748300 && D_80748300) {}  // FAKE: regalloc/count steer (annealed dead test)
                                }
                                if (scale == 0.0f) {
                                    scale = 0.1f;
                                }
                                scale = ((f32)actor->unk15E * 0.4f) / scale;
                                if (dist) {}  // FAKE: regalloc/count steer (annealed dead test)
                                angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                if (scale > 10.0f) {
                                    scale = 10.0f;
                        if (dx) {}  // FAKE: regalloc/count steer (annealed dead test)
                                }
                                if (actor->unk4 != NULL) {
                                    spC[0] = actor->unk4->unk34;
                                    spC[1] = actor->unk4->unk3C;
                                } else {
                                    spC[0] = 0.15f;
                                    if (dz > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (dz < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                    spC[1] = 0.15f;
                                if (light) {}  // FAKE: regalloc/count steer (annealed dead test)
                                }
                                spC8[actorIdx] = 1;
                                if (lightCount != 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        if (dz > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                            }
                            innerDist = maxDist / 3.0f;
                            if (lightCount != 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                    if (dist < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
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
                                if (dx < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (light && light) {}  // FAKE: regalloc/count steer (annealed dead test)
                                distFromInner = dist - innerDist;
                            if (dy < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
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
                    if (dx && dy && dz) {}  // FAKE: dead test
                    if (actor->unk4 != NULL) {
                        spC[0] = actor->unk4->unk34;
                        spC[1] = actor->unk4->unk3C;
                    } else {
                        spC[0] = 0.15f;
                        if (lightCount == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (dx < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                        spC[1] = 0.15f;
                                if (D_80748304) {}  // FAKE: regalloc/count steer (annealed dead test)
                    }
                    alpha = actor->unk128 / 255.0;
                    billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                        (s32)(spC[0] * (f32)actor->unk16E[0]),
                        (s32)(spC[1] * (f32)actor->unk16E[1]),
                        1, 0x64,
                        (u32)((f32)D_80748308 * alpha),
                        0,
                        1.0f);
                        if (gActiveActorCount == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (gPlayerCount && gPlayerCount) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (D_80748304 != 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (D_80748300 && D_80748300) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (gActiveActorCount != 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                }
            }
        }
    }
}

// lightApplyToActors (src/global/5E2F0.c): stage 4: R12_fable_5 (base f826d6ee) as1-XBB survey: park full=361 text=367 reloc=8 shape=119; candidate-limit variants give L0/L1=364 (one target-matching rank-2 hoist lost), L2/L3/L5/L10/L20=361: no as1-steerable hunk; stage-4 stack-store/colouring diff as noted. No C changed, park kept. | Prior: stage 4: full=361 text=367 reloc=8 shape=119 n=1240 (1159 instructions, frame 344); R11_lightApplyToActors: analyzed uopt_trace -l 5 and as1probe keep output. Confirmed 4 spurious stack stores in prologue (maxDist, dx, dy, dz = 0.0f) from FAKE initializations. In CFG, 134 branch/call/return sites and callee-saved register set match target. Verified exact park form in 5E2F0.c with whole-file fdiff OK. | Prior: stage 4: 1159 instructions, frame 344, identical saved registers, 134 branch/call/return sites (target 134); deadsweep full 361 text 367 reloc 8 shape 119. Extra basic block was the final empty dx/scale tests in the spotlight model arm; remove both. Switch cases 1 then 0 with per-case break restores the duplicated active-count reload and two relocations. Initialized maxDist before its formerly undefined spotlight dead read. Pruned 16 further FAKEs; single and pair deletions stalled. Tried clean no-FAKE switch (1149 insns, full465, reloc0), floating-to-integer dead reads, moving/removing maxDist dead read, dx/dy/dz reuse in point math and dist/maxDist/factor + dot/pd lifetime reuse; no further count-exact improvement. Lower raw score stage3 alternative287 has1157 insns and an extra branch, retained in private valid-keep-drop.c. Plain-C fdiff FAILED text (built13216 expected13216), rodata176, reloc; CURRENT10219. Parked stage4 candidate.
void billboardSubmit(Actor *, s16, s16, s16, s16, s16, u8, s16, u8, s16, f32);
void commandQueuePush(Actor *, s16, s16, s16, u8, u8, u8, u8, u8);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
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
    f32 pd;
    f32 factor;
    f32 alpha;

    maxDist = 0; // FAKE: define maxDist for dead read
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
                        switch (light->unk39) {
                        case 1:
                            {
                                dx = light->unk24 - light->x;
                if (dx > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                dy = light->unk28 - light->y;
                                dz = light->unk2C - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (dist == 0.0f) {
                                    dist = .1f;
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
                                    dist = .10f;
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
                                }
                                if (dot >= light->unkC) {
                                    if (dot >= light->unk4) {
                                        dot = 1.f;
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
                                        dist2d = (dist != 0.0f) ? dist : 0.00100f;
                            if (dy > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                            if (dz) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        scale = (light->y - actor->unk80) / dist2d;
                                        if (!(scale > 0)) {
                                            scale = -scale;
                                if (dist == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        }
                                        if (scale == 0.0f) {
                                            scale = .1f;
                                        if (dy < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        }
                                        scale = ((f32)actor->unk15E * .40f) / scale;
                                    if (aY) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (dz < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                        if (actor->unk4 != NULL) {
                                            spC[0] = actor->unk4->unk34;
                                            spC[1] = actor->unk4->unk3C;
                                        } else {
                                            spC[0] = 0.15f;
                                            spC[1] = 0.15f;
                                        }
                                        alpha = actor->unk128 / 255.;
                                if (maxDist < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
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
                            break;
                        case 0: {
                            pd = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + (((light->x - actor->unk7C) * (light->x - actor->unk7C)) + ((light->y - actor->unk80) * (light->y - actor->unk80)))) - (f32)*(s16 *)((u8 *)actor + 0xCE);
                            if (pd < 0.0) {
                                pd = .1f;
                            }
                            maxDist = light->unk14 * 1.300f;
                            if ((actor->unk60 & 0x01000000) && (pd < maxDist) && (actor->unk60 & 4)) {
                                dist2d = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + ((light->x - actor->unk7C) * (light->x - actor->unk7C)));
                                if (dist2d == 0) {
                                    dist2d = 1.f;
                                }
                                scale = (light->y - actor->unk80) / dist2d;
                                if (dy > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (maxDist) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (!(scale > 0.0f)) {
                                    scale = -scale;
                                    if (dy == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                }
                                if (scale == 0.0f) {
                                    scale = .1f;
            if (D_80748308 == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                }
                                scale = ((f32)actor->unk15E * .40f) / scale;
                                if (pd) {}  // FAKE: regalloc/count steer (annealed dead test)
                                angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                if (scale > 10) {
                                    scale = 10;
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
                                }
                                spC8[actorIdx] = 1;
                                        if (dz > 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                            }
                            innerDist = maxDist / 3;
                            if (pd < innerDist) {
                                commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                    0xFF, light->unk36, light->unk37, light->unk38, 0);
                                if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                    alpha = actor->unk128 / 255.;
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
                                pd = pd - innerDist;
                            if (dy < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (pd < range) {
                                    factor = 1.f - (pd / range);
                                    commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                        0xFF,
                                        (u32)((f32)light->unk36 * factor),
                                        (u32)((f32)light->unk37 * factor),
                                        (u32)((f32)light->unk38 * factor),
                                        0);
                                    if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                        alpha = actor->unk128 / 255.;
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
                            break;
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
                        spC[0] = .150f;
                        if (lightCount == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                        spC[1] = .150f;
                                if (D_80748304) {}  // FAKE: regalloc/count steer (annealed dead test)
                    }
                    alpha = actor->unk128 / 255.0;
                    billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                        (s32)(spC[0] * (f32)actor->unk16E[0]),
                        (s32)(spC[1] * (f32)actor->unk16E[1]),
                        1, 0x64,
                        (u32)((f32)D_80748308 * alpha),
                        0,
                        1);
                        if (gActiveActorCount == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                        if (D_80748304 != 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                }
            }
        }
    }
}

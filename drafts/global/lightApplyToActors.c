// lightApplyToActors (src/global/5E2F0.c): stage 6 (orchestrator, revisit 13): this annealed full=299 body is NOT parked in src (src keeps the full=361 park): its ~60 annealed dead tests include uninitialised reads (if (pd == 0) {} and if (dirX) {} before their first assignments), which the park rules reject. Next: re-anneal with dead tests of initialised values only, or derive the natural source from the colour spec below (Q0442, Q0558) | stage 6 (colour world now mapped): R13_sonnet_xhigh_4 (base 555ed2b6) full 361->299 text 297 reloc 2 shape 97 n=1240 (1159 insns, frame 344) via 4 annealing chains over dead tests (deadsweep.Scorer in-container, ~50 evals/s; .scratch/R13_sonnet_xhigh_4/anneal*.py). TARGET COLOUR SPEC (from asm): dist/maxDist/factor fs0; dot/pd/zero-web-A fs1; scale fs2 (loop-carried uninit web, lwc1 fs2,0x10C preheader, swc1 at exit, angle s3 likewise); dirX/dirY/dirZ fs3/fs4/fs5 (zero-web-D also fs3 in case 0); dx/dy/dz whole-var UNcoloured, pieces f0/f2/f14 in case-1 block1 and block3 reloads but block2 pieces uncoloured (sub into ring temp, swc1, real lwc1 reload); aX/aY/aZ stores kept, values in f12/f16/f18 (only 6 lines use f16/f18 => uopt colours them, ugen FP ring is f4-f10 only). NATURAL C (no FAKE) colours dx,dy,dz fs1-3 and leaves dirX/Y/Z in stack (adj 0), 1230 insns. Clean lever: a read of dx/dy/dz after the loops flips priorities and gives dirs fs3-5 + dx f0/dy f2/dz f14 exactly: use NO-CODE form 'if ((s32)dx) {}' x3 in the tail loop (the 'if (dx && dy && dz) {}' form leaves lwc1+c.eq.s residue; plain dx+dy+dz; and (void) forms are dropped by cfe). That base (.scratch/R13_sonnet_xhigh_4/t_c3.c, full 505, 1235 lines) is structurally closer but dead-test search could not yet get f12/f16/f18 for the aX/aY/aZ div pieces nor the A/D zero pieces; remaining target-only features: 3 aX/aY/aZ swc1 stores, block-2 reloads, A(fs1)/D(fs3) coloured zero pieces (target 10 mtc1 zero vs 12), one bc1f/bc1fl flavour. Prior: stage 4 ... (older notes below). | stage 4: R12_fable_5 (base f826d6ee) as1-XBB survey: park full=361 text=367 reloc=8 shape=119; candidate-limit variants give L0/L1=364 (one target-matching rank-2 hoist lost), L2/L3/L5/L10/L20=361: no as1-steerable hunk; stage-4 stack-store/colouring diff as noted. No C changed, park kept. | Prior: stage 4: full=361 text=367 reloc=8 shape=119 n=1240 (1159 instructions, frame 344); R11_lightApplyToActors: analyzed uopt_trace -l 5 and as1probe keep output. Confirmed 4 spurious stack stores in prologue (maxDist, dx, dy, dz = 0.0f) from FAKE initializations. In CFG, 134 branch/call/return sites and callee-saved register set match target. Verified exact park form in 5E2F0.c with whole-file fdiff OK. | Prior: stage 4: 1159 instructions, frame 344, identical saved registers, 134 branch/call/return sites (target 134); deadsweep full 361 text 367 reloc 8 shape 119. Extra basic block was the final empty dx/scale tests in the spotlight model arm; remove both. Switch cases 1 then 0 with per-case break restores the duplicated active-count reload and two relocations. Initialized maxDist before its formerly undefined spotlight dead read. Pruned 16 further FAKEs; single and pair deletions stalled. Tried clean no-FAKE switch (1149 insns, full465, reloc0), floating-to-integer dead reads, moving/removing maxDist dead read, dx/dy/dz reuse in point math and dist/maxDist/factor + dot/pd lifetime reuse; no further count-exact improvement. Lower raw score stage3 alternative287 has1157 insns and an e
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

if (pd == 0) {}  // FAKE: annealed dead test
    maxDist = 0; // FAKE: define maxDist for dead read
    lightCount = 0;
    dx = 0.0f;  // FAKE: define dx for tail dead reads
    dy = 0.0f;  // FAKE: define dy for tail dead reads
    dz = 0.0f;  // FAKE: define dz for tail dead reads
    for (i = 0; i < gActiveActorCount; i++) {
    if (dirX) {}  // FAKE: annealed dead test
        spC8[i] = 0;
    }
    {
        for (i = 0; i < D_80748300 && gPlayerCount < 3; i++) {
            light = &D_807F7500[i];
            if (light->x > 0.0f) {}  // FAKE: dead test
            if ((lightCheckPlayerDistance(light) != 0) && (lightCount < 12)) {
                lightCount++;
                if ((s32)scale) {}  // FAKE: annealed dead test
                for (actorIdx = 0; actorIdx < gActiveActorCount; actorIdx++) {
                                if (actorIdx == 0) {}  // FAKE: annealed dead test
                    actor = gActiveActors[actorIdx].actor;
                    if (actor->unk60 & 0x2000) {
                        continue;
                    }
                    if (dx == 0) {}  // FAKE: annealed dead test
                    if (light) {}  // FAKE: annealed dead test
                    {
                        switch (light->unk39) {
                        if (dist2d) {}  // FAKE: annealed dead test
                        case 1:
                        if (alpha == 0) {}  // FAKE: annealed dead test
                            {
                                dx = light->unk24 - light->x;
                                if (dx < 0.0f) {}  // FAKE: annealed dead test
                                dy = light->unk28 - light->y;
                                dz = light->unk2C - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (dist == 0.0f) {
                                    dist = .1f;
                                    if (dist == 0) {}  // FAKE: annealed dead test
                                }
                                dirX = dx / dist;
                                dirY = dy / dist;
                                dirZ = dz / dist;

                                dx = actor->unk7C - light->x;
                                dy = actor->unk80 - light->y;
                                dz = actor->unk84 - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (dist == 0.0f) {
                                if ((s32)dist) {}  // FAKE: annealed dead test
                                    dist = .10f;
                                }
                                aX = dx / dist;
                                if ((s32)dirZ) {}  // FAKE: annealed dead test
                                aY = dy / dist;
                                if (dirX < 0.0f) {}  // FAKE: annealed dead test
                                aZ = dz / dist;

                                dot = (aZ * dirZ) + ((aX * dirX) + (aY * dirY));
                                if (dot < 0.0f) {
                                if (dirZ) {}  // FAKE: annealed dead test
                                    dot = 0.0f;
                                }
                                if (dot >= light->unkC) {
                                    if (dot >= light->unk4) {
                                        dot = 1.f;
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
                                        dist = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + ((light->x - actor->unk7C) * (light->x - actor->unk7C)));
                                if (actor) {}  // FAKE: annealed dead test
                                        dist2d = (dist != 0.0f) ? dist : 0.00100f;
                                if (dz < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        scale = (light->y - actor->unk80) / dist2d;
                                            if (dz) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        if (!(scale > 0)) {
                                if (dx < 0.0f) {}  // FAKE: annealed dead test
                                            scale = -scale;
                                        }
    if (dirZ > 0.0f) {}  // FAKE: annealed dead test
                                        if (scale == 0.0f) {
                                            scale = .1f;
                                if (dirX == 0) {}  // FAKE: annealed dead test
                                        if (dist < 0.0f) {}  // FAKE: annealed dead test
                                        }
                                        if (dy < 0.0f) {}  // FAKE: annealed dead test
                                        if (scale > 0.0f) {}  // FAKE: annealed dead test
                                        scale = ((f32)actor->unk15E * .40f) / scale;
                                if (scale == 0) {}  // FAKE: annealed dead test
                                        angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                        if (actor->unk4 != NULL) {
                                            spC[0] = actor->unk4->unk34;
                                            spC[1] = actor->unk4->unk3C;
                                        } else {
                                            spC[0] = 0.15f;
                                            spC[1] = 0.15f;
                                        }
                                        if (dx < 0.0f) {}  // FAKE: annealed dead test
                                        alpha = actor->unk128 / 255.;
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
                                if (dx < 0.0f) {}  // FAKE: annealed dead test
                                        if (dz < 0.0f) {}  // FAKE: annealed dead test
                            pd = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + (((light->x - actor->unk7C) * (light->x - actor->unk7C)) + ((light->y - actor->unk80) * (light->y - actor->unk80)))) - (f32)*(s16 *)((u8 *)actor + 0xCE);
                        if (dz < 0.0f) {}  // FAKE: regalloc/count steer (annealed dead test)
                            if (pd < 0.0) {
                                pd = .1f;
                            }
                            maxDist = light->unk14 * 1.300f;
                            if ((actor->unk60 & 0x01000000) && (pd < maxDist) && (actor->unk60 & 4)) {
                            if ((s32)aY) {}  // FAKE: annealed dead test
                                dist2d = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + ((light->x - actor->unk7C) * (light->x - actor->unk7C)));
                                if (dist2d == 0) {
                                    dist2d = 1.f;
                                }
                                scale = (light->y - actor->unk80) / dist2d;
                                if (dy > 0.0f) {}  // FAKE: annealed dead test
                                if (!(scale > 0.0f)) {
                                    scale = -scale;
                                }
                                if ((s32)scale) {}  // FAKE: annealed dead test
                                if (scale == 0.0f) {
                                    scale = .1f;
    if (dz > 0.0f) {}  // FAKE: annealed dead test
                                }
                                scale = ((f32)actor->unk15E * .40f) / scale;
                                angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                if (scale > 10) {
                                    scale = 10;
                                    if ((s32)dirX) {}  // FAKE: annealed dead test
                                }
                                if (actor) {}  // FAKE: annealed dead test
                                if (actor->unk4 != NULL) {
                                    spC[0] = actor->unk4->unk34;
                                    if (light != 0) {}  // FAKE: annealed dead test
                                    spC[1] = actor->unk4->unk3C;
                                } else {
            if (scale > 0.0f) {}  // FAKE: annealed dead test
                                    spC[0] = 0.15f;
                                    spC[1] = 0.15f;
                                    if (light == 0) {}  // FAKE: annealed dead test
                                }
                                spC8[actorIdx] = 1;
                                if (dy < 0.0f) {}  // FAKE: annealed dead test
                            }
                            if (actor != 0) {}  // FAKE: annealed dead test
                            innerDist = maxDist / 3;
                            if (pd < innerDist) {
                            if (dy < 0.0f) {}  // FAKE: annealed dead test
                        if (dx < 0.0f) {}  // FAKE: annealed dead test
                            if (D_80748300 == 0) {}  // FAKE: annealed dead test
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
                                    if (light != 0) {}  // FAKE: annealed dead test
                                }
                            } else {
                                range = maxDist - innerDist;
                                pd = pd - innerDist;
                                if (pd < range) {
                                if (gActiveActorCount != 0) {}  // FAKE: annealed dead test
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
                                if (alpha == 0) {}  // FAKE: annealed dead test
                                }
                            }
                        }
                        if (dy > 0.0f) {}  // FAKE: annealed dead test
                            if (aZ > 0.0f) {}  // FAKE: annealed dead test
                            break;
if ((s32)dy) {}  // FAKE: annealed dead test
                        }
                        if (aZ < 0.0f) {}  // FAKE: annealed dead test
                if (scale == 0) {}  // FAKE: annealed dead test
                    }
                }
                if ((s32)aY) {}  // FAKE: annealed dead test
            }
        }
        if (D_80748304 != 0) {}  // FAKE: annealed dead test
    }
    for (i = 0; i < gActiveActorCount; i++) {
    if (lightCount == 0) {}  // FAKE: annealed dead test
        {
        if (dirX < 0.0f) {}  // FAKE: annealed dead test
            if (spC8[i] == 0) {
                actor = gActiveActors[i].actor;
                if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                    if (actor->unk4 != NULL) {
                    if (actorIdx != 0) {}  // FAKE: annealed dead test
                        spC[0] = actor->unk4->unk34;
                        spC[1] = actor->unk4->unk3C;
                    } else {
                        spC[0] = .150f;
                        spC[1] = .150f;
                    }
                    alpha = actor->unk128 / 255.0;
                    billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                        (s32)(spC[0] * (f32)actor->unk16E[0]),
                        (s32)(spC[1] * (f32)actor->unk16E[1]),
                        1, 0x64,
                        (u32)((f32)D_80748308 * alpha),
                        0,
                        1);
                        if (gActiveActorCount == 0) {}  // FAKE: annealed dead test
                }
                    if (dx && dy && dz) {}  // FAKE: dead test
            }
            if (lightCount == 0) {}  // FAKE: annealed dead test
        }
    }
}

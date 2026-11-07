// lightApplyToActors (src/global/5E2F0.c): stage 6 (R13_sonnet_xhigh_11 final, base c3c47579): park body full 361->294 text 298 reloc 2 shape 89 n=1240 (frame 344), annealed (anneal_b/c.py + initcheck.py dominance filter) from the park with dead tests of INITIALISED variables only; no uninitialised read; no-effect FAKE tests pruned (prune.py). Remaining diff: 5-8 lines of FAKE init stores in the prologue (dx/dy/dz/maxDist=0), case-1 head (expected lines 85-215): dirX uncoloured (stack 280) / zero chain hoisted to fs5 instead of web A fs1 + D fs3, aX/aY/aZ stores missing and their f12/f16/f18 colours absent; rest are FP ring permutations (windows f4<->f8, f6<->f10) that follow the head. Findings: (1) uopt colours by descending adjsave (frequency 10^(loopdepth-1)); target needs the aX/aY/aZ webs coloured AFTER the dx/dy/dz pieces (f12/f16/f18 are the first free after f0/f2/f14) and dz pieces never take f12 (inherited forbidden from the sqrtf arg block); in c3 the coloured dx pieces are blocks 17+20, in the target 17+23. (2) f32 array local aV[3] keeps aX/aY/aZ stores (coloured isvar elements) but colours them before dx pieces (f0/f2/f12). (3) cfe constant chain = literal source text: zero webs A/D need their own spellings; their needsplit trigger needs f16/f18 used elsewhere in the loop. | stage 6 (R13_sonnet_xhigh_11, base c3c47579): park body full 361->307 text 307 reloc 2 shape 95 n=1240, annealed from the park with dead tests of INITIALISED variables only (initcheck.py dominance filter; no uninitialised read); mutated spellings of 0/0.f/.00f zero chains (the cfe constant chain key is the literal's source text: 0.0f='0.0', 0.f='0.', .0f='.0'; 0 int='0.0'). | stage 6 (orchestrator, revisit 13): this annealed full=299 body is NOT parked in src (src keeps the full=361 park): its ~60 annealed dead tests include uninitialised reads (if (pd == 0) {} and if (dirX) {} before their first assignments), which the park rules reject. Next: re-anneal with dead tests of initialised values only, or derive the natural source from the colour spec below (Q0442, Q0558) | stage 6 (colour world now mapped): R13_sonnet_xhigh_4 (base 555ed2b6) full 361->299 text 297 reloc 2 shape 97 n=1240 (1159 insns, frame 344) via 4 annealing chains over dead tests (deadsweep.Scorer in-container, ~50 evals/s; .scratch/R13_sonnet_xhigh_4/anneal*.py). TARGET COLOUR SPEC (from asm): dist/maxDist/factor fs0; dot/pd/zero-web-A fs1; scale fs2 (loop-carried uninit web, lwc1 fs2,0x10C preheader, swc1 at exit, angle s3 likewise); dirX/dirY/dirZ fs3/fs4/fs5 (zero-web-D also fs3 in case 0); dx/dy/dz whole-var UNcoloured, pieces f0/f2/f14 in case-1 block1 and block3 reloads but block2 pieces uncoloured (sub into ring temp, swc1, real lwc1 reload); aX/aY/aZ stores kept, values in f12/f16/f18 (only 6 lines use f16/f18 => uopt colours them, ugen FP ring is f4-f10 only). NATURAL C (no FAKE) colours dx,dy,dz fs1-3 and leaves dirX/Y/Z in stack (adj 0), 1230 insns. Clean lever: a read of dx/dy/dz after the loops flips priorities and gives dirs fs3-5 + dx f0/dy f2/dz f14 exactly: use NO-CODE form 'if ((s32)dx) {}' x3 in the tail loop (the 'if (dx && dy && dz) {}' form leaves lwc1+c.eq.s residue; plain dx+dy+dz; and (void) forms are dropped by cfe). That base (.scratch/R13_sonnet_xhigh_4/t_c3.c, full 505, 1235 lines) is structurally closer but dead-test search could not yet get f12/f16/f18 for the aX/aY/aZ div pieces nor the A/D zero pieces; remaining target-only features: 3 aX/aY/aZ swc1 stores, block-2 reloads, A(fs1)/D(fs3) coloured zero pieces (target 10 mtc1 zero vs 12), one bc1f/bc1fl flavour. Prior: stage 4 ... (older notes below). | stage 4: R12_fable_5 (base f826d6ee) as1-XBB survey: park full=361 text=367 reloc=8 shape=119; candidate-limit variants give L0/L1=364 (one target-matching rank-2 hoist lost), L2/L3/L5/L10/L20=361: no as1-steerable hunk; stage-4 stack-store/colouring diff as noted. No C changed, park kept. | Prior: stage 4: full=361 text=367 reloc=8 shape=119 n=1240 (1159 instructions, frame 344); R11_lightApplyToActors: analyzed uopt_trace -l 5 and as1probe keep output. Confirmed 4 spurious stack stores in prologue (maxDist, dx, dy, dz = 0.0f) from FAKE initializations. In CFG, 134 branch/call/return sites and callee-saved register set match target. Verified exact park form in 5E2F0.c with whole-file fdiff OK. | Prior: stage 4: 1159 instructions, frame 344, identical saved registers, 134 branch/call/return sites (target 134); deadsweep full 361 text 367 reloc 8 shape 119. Extra basic block was the final empty dx/scale tests in the spotlight model arm; remove both. Switch cases 1 then 0 with per-case break restores the duplicated active-count reload and two relocations. Initialized maxDist before its formerly undefined spotlight dead read. Pruned 16 further FAKEs; single and pair deletions stalled. Tried clean no-FAKE switch (1149 insns, full465, reloc0), floating-to-integer dead reads, moving/removing maxDist dead read, dx/dy/dz reuse in point math and dist/maxDist/factor + dot/pd lifetime reuse; no further count-exact improvement. Lower raw score stage3 alternative287 has1157 insns and an e
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
    dx = .000f;  // FAKE: define dx for tail dead reads
    dy = 0.00f;  // FAKE: define dy for tail dead reads
    dz = 0.00f;  // FAKE: define dz for tail dead reads
    for (i = 0; i < gActiveActorCount; i++) {
        spC8[i] = 0;
        if (dx) {}  // FAKE: annealed dead test
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
                                dy = light->unk28 - light->y;
                                dz = light->unk2C - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (dist == 0.0f) {
                                if (light == 0) {}  // FAKE: annealed dead test
                                    dist = 0.1000f;
                                }
                                dirX = dx / dist;
                                if (dirX > 0.00f) {}  // FAKE: annealed dead test
                                dirY = dy / dist;
                                dirZ = dz / dist;

                                dx = actor->unk7C - light->x;
                                dy = actor->unk80 - light->y;
                                dz = actor->unk84 - light->z;
                                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                                if (maxDist == 0) {}  // FAKE: annealed dead test
                                if (dist == 0.0f) {
                                        if (maxDist > 0.0f) {}  // FAKE: annealed dead test
                                    dist = 0.1f;
                                    if (dx < 0.0f) {}  // FAKE: annealed dead test
                                }
                                aX = dx / dist;
                                if (gPlayerCount) {}  // FAKE: annealed dead test
                                aY = dy / dist;
                                aZ = dz / dist;
                                    if (aY) {}  // FAKE: regalloc/count steer (annealed dead test)
                                if (dirZ > 0.f) {}  // FAKE: annealed dead test

                                dot = (aZ * dirZ) + ((aX * dirX) + (aY * dirY));
                                if (dot < 0.0f) {
                                    dot = 0.f;
                                }
                                if (dot >= light->unkC) {
                                    if (dot >= light->unk4) {
                                        dot = 1.0000f;
                                    } else {
                                        dot = (dot - light->unkC) * light->unk10;
                                        if (dirZ < 0.0f) {}  // FAKE: annealed dead test
                                    }
                                if (aZ > .000f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                    commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                        0xFF,
                                        (u32)((f32)light->unk36 * dot),
                                        (u32)((f32)light->unk37 * dot),
                                        (u32)((f32)light->unk38 * dot),
                                        0);
                                    if ((actor->unk60 & 0x01000000) && (actor->unk60 & 4)) {
                                        dist = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + ((light->x - actor->unk7C) * (light->x - actor->unk7C)));
                                        if (D_80748300 != 0) {}  // FAKE: annealed dead test
                                        dist2d = (dist != 0.0f) ? dist : .0010f;
                                if (dx > .00f) {}  // FAKE: annealed dead test
                            if (dy > .000f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        scale = (light->y - actor->unk80) / dist2d;
                                        if (!(scale > 0)) {
                                        if (scale < 0.000f) {}  // FAKE: annealed dead test
                                            scale = -scale;
                                        }
                                        if (scale == 0.0f) {
                                    if (dy == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                            scale = .1f;
                                if (dist == 0) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        }
                                if (dx < .0000f) {}  // FAKE: annealed dead test
                                        scale = ((f32)actor->unk15E * 0.4f) / scale;
                                        angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                        if (actor->unk4 != NULL) {
                                            spC[0] = actor->unk4->unk34;
                                            if ((s32)dist) {}  // FAKE: annealed dead test
                                            if ((s32)dx) {}  // FAKE: annealed dead test
                                            spC[1] = actor->unk4->unk3C;
                                        } else {
                                        if (dz < 0.0f) {}  // FAKE: annealed dead test
                                            spC[0] = 0.15f;
                                            spC[1] = 0.15f;
                                        }
                                        alpha = actor->unk128 / 255.;
                                        billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                                            (s32)(spC[0] * (f32)actor->unk16E[0]),
                                            (s32)(spC[1] * (f32)actor->unk16E[1]),
                                            1, 0x64,
                                            (u32)((f32)D_80748304 * dot * alpha),
                                            angle + 0xC00,
                                            scale * dot);
                                        spC8[actorIdx] = 1;
                                        if (scale > 0.0f) {}  // FAKE: annealed dead test
                                        if (dy < 0.0000f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                        if ((s32)dirX) {}  // FAKE: annealed dead test
                                    }
                                if (dy > 0.00f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                }
                            }
                            break;
                        case 0: {
                            pd = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + (((light->x - actor->unk7C) * (light->x - actor->unk7C)) + ((light->y - actor->unk80) * (light->y - actor->unk80)))) - (f32)*(s16 *)((u8 *)actor + 0xCE);
                            if (pd < 0.0) {
                                pd = .100f;
                            }
                            maxDist = light->unk14 * 1.30f;
                            if ((actor->unk60 & 0x01000000) && (pd < maxDist) && (actor->unk60 & 4)) {
                                dist2d = sqrtf(((light->z - actor->unk84) * (light->z - actor->unk84)) + ((light->x - actor->unk7C) * (light->x - actor->unk7C)));
                                if (gActiveActorCount) {}  // FAKE: annealed dead test
                                    if (pd) {}  // FAKE: annealed dead test
                                if (dist2d == 0) {
                                    dist2d = 1.00f;
                                }
                                scale = (light->y - actor->unk80) / dist2d;
                                if (!(scale > 0.0f)) {
                                    scale = -scale;
                                    if (pd < 0.0f) {}  // FAKE: annealed dead test
                                }
                                if (scale == 0.0f) {
                                if (dist2d > 0.0f) {}  // FAKE: annealed dead test
                                    scale = .1000f;
                                }
                                scale = ((f32)actor->unk15E * .4f) / scale;
                                    if (maxDist > .0f) {}  // FAKE: annealed dead test
                                angle = mathAngleBetweenPoints2D(light->x, light->z, actor->unk7C, actor->unk84);
                                if (scale > 10) {
                                    scale = 10;
                                }
                                if (pd) {}  // FAKE: annealed dead test
                                if (actor->unk4 != NULL) {
                                    spC[0] = actor->unk4->unk34;
                                    spC[1] = actor->unk4->unk3C;
                                } else {
                                    spC[0] = .1500f;
                                    spC[1] = 0.150f;
                                }
                                spC8[actorIdx] = 1;
                            }
                            innerDist = maxDist / 3;
                            if (pd < innerDist) {
                            if (dy < 0.f) {}  // FAKE: regalloc/count steer (annealed dead test)
                                commandQueuePush(actor, (s16)(s32)light->x, (s16)(s32)light->y, (s16)(s32)light->z,
                                    0xFF, light->unk36, light->unk37, light->unk38, 0);
                                    if (light) {}  // FAKE: annealed dead test
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
                                if (pd < range) {
                                    factor = 1.00f - (pd / range);
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
                            if (dz == 0) {}  // FAKE: annealed dead test
                        }
                            break;
                        }
                                if (maxDist) {}  // FAKE: annealed dead test
                    }
                }
                    if (dx && dy && dz) {}  // FAKE: dead test
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
                }
            }
            if (dy > 0.0f) {}  // FAKE: annealed dead test
        }
    }
}

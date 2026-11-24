# actorNpcTinyUpdate (global, src/global/C4620_npc_kongs.c)
## Sites
global:806C1B50:goto:u72d9b goto: `default: goto done;` in the `switch (gCurrentActor->sub4->model->animId)` (0x23E/0x23F/0x240 pick bone/minFrame) jumps to the `done:` tail `actorUpdateModelMatrix(gCurrentActor, 0)`. KEPT (goto-hand, Q0591 shared tail).
## Attempts
- 2026-11-17 Cleanfunc_806C1B50 (opus-5-5:xhigh): kind-only sentinel (`default: kind = 0;` + `if (kind && ...)`) 23; sentinel with thr defined on every path 6 (frame kept 0x20); uopt -zdbug:5/6 on the kind-only sentinel: thr (cand 26, -8 vreg) in node-0 liveout, home 32(sp); permuter (hack-free weights, -j 2, 900 s) from the thr-defined sentinel body: base 330, only ties.
- 2026-11-18 Cleanfunc_806C1B50b (opus-5-5:xhigh): s32 hit-flag sentinel; if/else-if chain over an animId local (duplicated tail+return and sentinel variants); f32 frame snapshot local on the thr-defined sentinel; as1probe keep+scan of the thr-defined sentinel body (full 6, 122 lines vs 120): no C-emittable hit. Locals renamed kind -> bone, thr -> minFrame (Q1466).
- 2026-11-24 2026-11-24b: continue ReMeasureB18H (opus-5-5, base 127a3fd5, after cb17735e retyped gEffectSpriteImpactFlash to EffectGridAsset; it is the effectCreateAtActorBone argument at 0x2338/0x233c, not on the goto path), variants.py try: duplicated tail + return in the default 13, `bone = 0` sentinel with `bone != 0 &&` 32, `bone = 0; minFrame = 0;` sentinel 6.
## Untried ideas
none: the tail is one block with six entries; any goto-free C either duplicates it or adds a sentinel test the target lacks.
## Evidence
- 0x22b4 beqzl t3,0x2394 (flags & 4) and 0x22c0 beqzl t4,0x2394 (subState), each with move a0,a2 in the slot.
- 0x22e0-0x22f8 animId chain li at,574/beq 0x2304; li at,575/beq 0x230c; li at,576/beq 0x2314 (li v1,7 / li v1,3 minFrame in slots); default b 0x2394 at 0x22fc with move a0,a2 0x2300.
- 0x2318-0x2330 u32 minFrame to float (mtc1/cvt.s.w, bgez + add.s 2^32 fixup), c.lt.s 0x2340, bc1fl 0x2348 -> 0x2394 (move a0,a2 0x234c).
- 0x2350 jal effectCreateAtActorBone (&gEffectSpriteImpactFlash lui/addiu a0 0x2338/0x233c), sb zero subState 0x2364, b 0x2390 at 0x2368.
- else arm (0x2370-0x238c) falls into 0x2390 move a0,a2; 0x2394 jal actorUpdateModelMatrix (the one tail).

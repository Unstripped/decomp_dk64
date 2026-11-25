# modelPendingQueueInsert (global, src/global/36880_model_slot.c)

## Sites
- other:0eb0e4 (new 2026-11-21, replaces dead-if:6a7bf8) `f32 *px = NULL, *py = NULL, *pz = NULL;` dead initialisers: number px/py/pz cand 0/3/6, ahead of i*752 (umpy cand 54) and &gPlayerSlots[i] (uixa cand 55). All five tie at adjsave 15.00 and the earlier candidate wins (Q1551), so px/py/pz take v1/a0/a1 and umpy/uixa a2/a3. Removal 14. OPEN.
- other:cd1810 (was other:e6504d, keymap) `slots = gModelSlots; obj = slots[idx].csState;` on one line: as1 schedules `addu t9,t8,t7` (0x99a0) ahead of the slots home store `sw t8,52(sp)` (0x99a4); on two lines the store goes first (2). The if (0) taking &idx/&slots that shared the old line is gone: without the dead tests idx (cand 19) and slots (cand 24) have -ve save and keep their homes 70(sp)/52(sp). OPEN.
- dead-if:aa1df8 `if (1) {}` in case 4: REMOVED 2026-11-21 (kind byte ucvt cand 38 at 2.40 takes t5 once the loop steers are gone).
- dead-if:6a7bf8 `if (entry && entry) {}`: REMOVED 2026-11-21, replaced by 0eb0e4.
- dead-if:3e03d7 `if (slots && slots) {}`: FIXED 2026-11-21 by the inner `switch (obj->updateMode) { case 6: ...; break; default: ...; break; }` (R3 one-case selector switch on the outer switch's selector; same `bne t4,t5` 0x9a48): the 752 constant web drops 3.33 -> 2.50 so the gViewportCount ucvt (3.00) takes t2.
- dead-if:40ccd1 `if (px) {}`: FIXED 2026-11-17 by the early `continue` on inactive players.

## Attempts
2026-11-17 HackrenderModelAnimatedSlot3 anthropic/claude-opus-5-5 (re-measure on the 11134d9a CsState-field body)
- single removals at the base: if (0) 83, zPtr guard 18, entry 21, px 13, slots 10; all five 14 (only the loop colouring differs once slots/obj share a line).
- zPtr alias `zPtr = &actor->z; pz = zPtr;` redundant: fdiff 0 with `pz = &actor->z;`. The zPtr guard then read an unassigned local; guard on 1 matches before or after `allow = allowDefault` -> respelled `if (1) {}`, zPtr dropped (uninit 1 -> 0). `;`, braces, blank line there: 9.
- early `if (gPlayerSlots[i].active == 0) { continue; }` with the body unnested: px guard removable (fdiff 0); with all four guards 7; dropping entry/slots/case-4 instead 24/10/9.
- by-hand classify: entry site single-term guards 20, two-term on entry/slots 0 (i 10, px 56, obj 40); slots site single-term 9, two-term on entry/slots/px 0 (i 10).
- natural body (no hacks, multi-line) 16; slots/obj one line 14. Variants on it: inner switch default-first 14 / case-6-first 27, continue 20, Actor * local 14, PlayerStruct * local 96 (eye arm only 14), dx/dy/dz temps 25, d temp 14, ternary min 27, ternary pointer selection 113, u8 kind local 18 (s32 26), arms swapped 15. On the final body: kind local u8 4 (10 without the case-4 split), s32/s16 12; `if (!(d < best)) continue; best = d;` 0 with the slots guard, 10 without; `>=` 2 / 12.
- permuter 900 s on the hack-free natural body: base 135, best 75 = line join of slots/obj/switch only.
2026-11-21 continue unit 1 Hack36880 anthropic/claude-opus-5-5 (re-measure on the e14a06d4 CsState carve body, b1c3fd15): FAKE 4 -> 2, fdiff 0
- single removals at the base: if (0) 80, if (1) 9, entry 24, slots 10, all four (one-line head) 20; single reads if (entry) {} 23, if (slots) {} 9.
- natural multi-line body 22: only the loop colouring (umpy v1/uixa a0/px-pz a1-a3; gViewportCount t3, 752 t2) and the sw t8,52(sp) order differ. uopt -l5: umpy 45/uixa 46/px 53/py 58/pz 62 all 15.00 (tie, lower cand wins); 752 const 3.33 > gViewportCount ucvt 3.00 > 6 const 2.50 > kind 2.40.
- natural + entry guard 15 (fixes the tie, breaks t2-t5); natural + slots guard 84 (idx/slots coloured); count local for gViewportCount (u8/s16/s32/u16/u32, before/after best) 22, with the entry guard 15 (u8/u16 45).
- inner switch on obj->updateMode: case 6 first 16 (752 drops to 2.50: t2-t5 exact), default first 22, explicit case 3/4 + case 6 150; + entry guard 15; + if (entry) {} 27; nested active test 29; `!active` 16.
- px/py/pz dead inits on the switch body: at declaration 2 (0 with the slots/obj join), three statements before/after best = 1e8f or at the function start 0, chain px = py = pz = NULL 6-8, subsets px+py 8, px 11, px+pz 11, py/pz/py+pz 14.
- head layouts on the final body: two lines 2, slots/obj one line 0, idx/slots/obj one line 0, slots before idx one line 64, obj from gModelSlots[idx] then slots 54 (same on one line), assignment in the obj test 2, slots after the obj test 55.
- (f32) cast on updateRangeSq removed: 0 (the implicit conversion is the same cvt.s.w).
2026-11-25 continue CleanrenderModelAnimatedSlot anthropic/claude-opus-5-5 (base 9d5aabb3, 0eb0e4 only)
- dead inits removed (`f32 *px, *py, *pz;`): 14, mflo v1 / addu a0,t1,v1 for mflo a2 / addu a3,t1,a2 (0x9a2c/0x9a30) and px/py/pz in a1/a2/a3 for v1/a0/a1 (0x9a54-0x9a70).
- variants scan on that body (--max 1000, 101 variants incl. elem `(gPlayerSlots + i)->eyeX` / `(&gPlayerSlots[i])->active|actor`): best 14.
- default-then-override pointers (eye pointers assigned at the loop-body top, case 6 overriding in a one-case switch 25, in an if 32).
- permuter 900 s on that body (hack-free weights, -j 2, base 75): best 60 = a redundant alias `new_var = px` read in the distance sum (steer); 68 also aliases `&entry->modelId`; 70 aliases eyeZ; no zero.
- reasoning: every statement that assigns px/py/pz contains i*752 (via gPlayerSlots[i].actor or .eyeX), so umpy is always numbered ahead of a live px def; only a pre-loop statement can number px first, and any such statement is a dead store (fully dead declaration default ruling).

## Untried ideas
- A natural construct that lowers umpy/uixa below 15.00 or raises px/py/pz above it (Q1569 accesses vs blocks), replacing the numbering lever (not found: d temp, dx/dy/dz temps, PlayerSlot pointer, Actor pointer all tried).

## Evidence
- target 0x9940..0x9bd4, frame 88: allow in ra, spilled `sb ra,83(sp)` around hashTableLookup and reloaded `lbu ra,83(sp)` 0x99b0; idx home 70(sp) (`sh v0,70(sp)` 0x999c), slots 52(sp) (`sw t8,52(sp)` 0x99a4 after `addu t9,t8,t7` 0x99a0), obj 84(sp); reloads 0x9b78/0x9b7c.
- switch on lbu t5,84(t6) through the .rodata+712 table; case order in the text: 2 (0x99e0), 0 (0x99e8), 4 (0x99f0 `andi ra,a1,0xff` then falls into 3/6 at 0x99f4), 5 (0x9af8).
- loop 0x9a1c: gViewportCount t2 (0x99f8), 6 in t4 (0x9a14), 752 in t3 (0x9a18), `multu t0,t3` (i*752), `mflo a2` 0x9a2c, `addu a3,t1,a2` 0x9a30 (&gPlayerSlots[i]), `lbu t9,0(a3)` active test; entry loads f16/f18/f20 = z/x/y; `bne t4,t5` 0x9a48; actor arm `lw v0,4(a3)`, px/py/pz = v0+124/128/132 in v1/a0/a1; eye arm `addu v0,a2,t1` (offset first), +540/544/548; one squared-sum evaluation, `c.lt.s f14,f22`, `mov.s f22,f14`.
- uopt -l5 final body: px/py/pz cand 0/3/6 -> v1/a0/a1 (15.00), umpy 54 -> a2, uixa 55 -> a3 (15.00), gViewportCount ucvt 50 -> t2 (3.00), 752 -> t3 (2.50), 6 -> t4 (2.50), kind ucvt 38 -> t5 (2.40); idx 19 / slots 24 not coloured (-ve save).

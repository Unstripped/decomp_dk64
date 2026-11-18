# modelPendingQueueInsert (global, src/global/36880.c)

## Sites
- other:9ec202 (line 3525 at the final copy) `if (0) { csStateTickTimers((CsState *)&idx); csStateTickTimers((CsState *)&slots); }` on the one-line head: takes &idx/&slots so both keep homes 70(sp)/52(sp) (target `sh v0,70(sp)` 0x999c, `sw t8,52(sp)` 0x99a4, reloads 0x9b78/0x9b7c). Needed only while the dead tests below are present: they make idx (cand 19) and slots (cand 15) colourable (a3/t2). OPEN.
- dead-if:aa1df8 (was 8dcc1c `if (zPtr != 0) {}`) `if (1) {}` in case 4: pure block split (class 1 by hand); keeps the kind byte ucvt (cand 29) at adjsave 1.7 so it takes t5 (lbu t5,84(t6) 0x99bc) and 752/6 stay t3/t4. Terminal once the sweep classifies it (class 1).
- dead-if:6a7bf8 `if (entry && entry) {}` at the top of the active loop body: lowers i*752 (umpy) and &gPlayerSlots[i] (uixa) from adjsave 15 to 10 so px/py/pz colour v1/a0/a1 first and umpy/uixa take a2/a3; two-term guard on a live local (entry or slots) is required (single-term 20). OPEN.
- dead-if:40ccd1 `if (px) {}` after the kind-test join: FIXED 2026-11-17 by the early `continue` on inactive players.
- dead-if:3e03d7 `if (slots && slots) {}` at the end of the loop body: keeps gViewportCount ucvt in t2 and 752/6 in t3/t4; two-term guard on a live local (entry, slots or px) required (single-term 9). OPEN.

## Attempts
2026-11-17 HackrenderModelAnimatedSlot3 anthropic/claude-opus-5-5 (re-measure on the 11134d9a CsState-field body)
- single removals at the base: if (0) 83, zPtr guard 18, entry 21, px 13, slots 10; all five 14 (only the loop colouring differs once slots/obj share a line).
- zPtr alias `zPtr = &actor->z; pz = zPtr;` redundant: fdiff 0 with `pz = &actor->z;`. The zPtr guard then read an unassigned local; guard on 1 matches before or after `allow = allowDefault` -> respelled `if (1) {}`, zPtr dropped (uninit 1 -> 0). `;`, braces, blank line there: 9.
- early `if (gPlayerSlots[i].active == 0) { continue; }` with the body unnested: px guard removable (fdiff 0); with all four guards 7; dropping entry/slots/case-4 instead 24/10/9.
- by-hand classify: entry site single-term guards 20, two-term on entry/slots 0 (i 10, px 56, obj 40); slots site single-term 9, two-term on entry/slots/px 0 (i 10).
- natural body (no hacks, multi-line) 16; slots/obj one line 14. Variants on it: inner switch default-first 14 / case-6-first 27, continue 20, Actor * local 14, PlayerStruct * local 96 (eye arm only 14), dx/dy/dz temps 25, d temp 14, ternary min 27, ternary pointer selection 113, u8 kind local 18 (s32 26), arms swapped 15. On the final body: kind local u8 4 (10 without the case-4 split), s32/s16 12; `if (!(d < best)) continue; best = d;` 0 with the slots guard, 10 without; `>=` 2 / 12.
- permuter 900 s on the hack-free natural body: base 135, best 75 = line join of slots/obj/switch only.

## Untried ideas
- A natural construct that gives px/py/pz a higher uopt priority than i*752 / &gPlayerSlots[i] (or lowers those two below px/py/pz while keeping i below them) without empty blocks; none known.
- A real construct for the two-term splits at the top and bottom of the loop body (an inner loop or a second continue condition the target folds); none found.

## Evidence
- target 0x9940..0x9bd4, frame 88: allow in ra, spilled `sb ra,83(sp)` around hashTableLookup and reloaded `lbu ra,83(sp)` 0x99b0; idx home 70(sp), slots 52(sp), obj 84(sp).
- switch on lbu t5,84(t6) through the .rodata+712 table; case order in the text: 2 (0x99e0), 0 (0x99e8), 4 (0x99f0 `andi ra,a1,0xff` then falls into 3/6 at 0x99f4), 5 (0x9af8).
- loop 0x9a1c: `multu t0,t3` (i*752, t3 = 752), `mflo a2`, `addu a3,t1,a2` (&gPlayerSlots[i]), `lbu t9,0(a3)` active test; entry loads f16/f18/f20 = unkC/unk4/unk8; `bne t4,t5` (t4 = 6); actor arm `lw v0,4(a3)`, px/py/pz = v0+124/128/132 in v1/a0/a1; eye arm `addu v0,a2,t1`, +540/544/548; one squared-sum evaluation, `c.lt.s f14,f22`, `mov.s f22,f14`.

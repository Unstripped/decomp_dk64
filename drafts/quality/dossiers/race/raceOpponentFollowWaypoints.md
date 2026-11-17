# raceOpponentFollowWaypoints (race, src/race/0.c)

## Sites
race:80024000:other:b1d6ee: byte-offset `row` local ((u8 *)routeRows + routeRowIdx * 12) kept the row-address `addu a0,t0,t8` operand order at 0x1cc (base t0 = routeRows reloaded from sp+48, offset t8 = idx*12). FIXED.
race:80024000:dead-if:d2b271: `if (row) {}` added blocks to the fs0/fs1 live ranges so both compressed to length 9 (adjsave 14/9 tie, fs0 bit 36 wins $f20). FIXED.
race:80024000:other:58c1a4: `fv0 = q; fv0 = q;` kept q in $f2 and the 0.0f compare zero in $f12 (0x5e8-0x618). FIXED.
race:80024000:other:a1f722: `if (sqrtf(...) < (zone = &entries[idx])->radius)` re-took zone after the sqrtf call. Respelled `dist = sqrtf(...); zone = &entries[idx]; if (dist < zone->radius)`: the target really recomputes the address after the call (0x104-0x12c) and uses it for radius/y. FIXED (ordinary C, untagged).
race:80024000:other:e79659: tmp (clamped height offset) reused for the mathAtan2 heading. Own `heading` local declared after `dist` matches. FIXED.
race:80024000:other:149188: vx/vz (waypoint offset) reused for the velocity; separate dx/dz grows the function 0x634 -> 0x684 (Q1172). KEPT.

## Attempts
2026-11-14 HackraceOpponentBehaviourUpdate claude-code/claude-opus-5-5: row local deleted, `routeRows[routeRowIdx].unk0/.unk4/.unk8` indexed inline -> uopt CSEs the address with the target operand order (only the fs0/fs1 swap left, 36 lines).
2026-11-14 HackraceOpponentBehaviourUpdate claude-code/claude-opus-5-5: duplicate `a0 = &entries[unk25]` inside the inner if deleted, the one after the inner if moved after the outer distance if -> fs0 live bbs 30 -> 29, both fs0/fs1 compress to length 8 (adjsave 1.75 tie), fs0 keeps $f20 -> fdiff 0.
2026-11-14 HackraceOpponentBehaviourUpdate claude-code/claude-opus-5-5: friction tail `q = (speedXZ * speedXZ) / 15000.0; speedXZ -= q;` (no fv0 copy of speedXZ) -> fdiff 0. Also matching: `(f32)` cast kept, `speedXZ = speedXZ - q`. Not matching: any form loading speedXZ into fv0 first (14 lines).
2026-11-14 HackraceOpponentBehaviourUpdate claude-code/claude-opus-5-5: names: a0->zone, fs0/fs1->vx/vz, fv0->tmp, v1->yawDiff, q->friction.
Not matching: fs0/fs1 split into separate dx/dz for the first region (382 lines, any declaration slot); `a0` reused for the radius test without recomputing after sqrtf (299); radius test written as `entries[unk25].radius` with a0 set inside the if (248); fs1 assigned first (48); sqrt operands swapped (42); routeRowIdx s32/u16 (40); `routeRowIdx + routeRows`, `&routeRowIdx[routeRows]` (ixa, addu a0,t8,t0).
2026-11-17 HackraceOpponentFollowWaypoints anthropic/claude-opus-5-5: a1f722: `dist` local for the sqrtf result, zone refresh as its own statement after the call -> fdiff 0 (v_B). Not matching: no first zone + direct entries[].x/.z with dist + refresh (3), direct .x/.z + in-test assignment (3), direct `entries[idx].radius` test with zone set inside the if (120), first zone kept + direct radius test (128).
2026-11-17 HackraceOpponentFollowWaypoints anthropic/claude-opus-5-5: e79659: `heading` local declared after `dist` -> fdiff 0; declared after tmp full=20. tmp renamed heightAdjust; redundant `(s16)` mathSinF-arg and `(s32)` yaw casts dropped (fdiff 0).
2026-11-17 HackraceOpponentFollowWaypoints anthropic/claude-opus-5-5: 149188 re-measured on the new body: dx/dz in all 120 declaration slot pairs, best full=214 text=260 (size 0x684). curSpeed reuse (old speed -> new speed) left as one quantity refined in place; a separate newSpeed local is full=20.

## Untried ideas
149188 only: a structural change to the velocity block (e.g. accumulating into the actor or a velocity struct) that frees the offset roles without growing .text; untried.

## Evidence
0x0e8/0x0ec: sub.s $f22 (z diff = fs1) then sub.s $f20 (x diff = fs0); fs0 must colour first (Q0163 length compression `n>2 ? ((n-2)>>2)+2 : n`, ties to the lower candidate bit).
0x1cc: addu a0,t0,t8 (routeRows base first).
0x248-0x26c: zone pointer recomputed only on the unk25++ path; other paths reuse $a0 (CSE).
0x5d8-0x618: lwc1 $f0 speedXZ, mtc1 zero $f12 early, q in $f2, sub.s $f6.
0x104-0x12c: after jal sqrtf, gBehaviourWorkState (v1), D_807FDCA0 (a3), waypointIndex (a1) reloaded and the entry address recomputed into a0; a0 feeds radius (0x130) and y (0x160), a1 the entryCount-1 compare (0x1b8).

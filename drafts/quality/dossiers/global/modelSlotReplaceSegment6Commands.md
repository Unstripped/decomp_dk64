# modelSlotReplaceSegment6Commands (global, src/global/36880.c)
## Sites
global:80636AE8:proto-steer:81fdd2 proto-steer (REMOVED 2026-11-15): the file-local K&R `void renderReplaceSegment6Commands();` + PROTO_SKIP let both calls pass `seg, len`; the a2/a3 argument pins coloured seg into a2 and len/count into a3. Consolidated: the shared 61AA0.h (Gfx *, void *) prototype with 2-argument calls matches once `count` is reused for the byte length (count = C - mid; count >>= 3), with no `len`/`size` locals.
start = head (pre-existing, untagged at base; tagged 2026-11-15) other: alias of head. uopt -zdbug:6 on the final copy: head (bit 10) v0, mid (bit 6) v1, start (bit 14) a0, seg (bit 0) a2, count (bit 17) a3. Without the alias (call reads seg->displayListA, p2) seg takes a3, count is not coloured (ugen t0, reload lw t0,24(sp)): full=14.
## Attempts
2026-11-15 HackmodelSlotReplaceSegment6Commands anthropic/claude-opus-5-5:high: K&R kept, alias removed by reading seg->displayListA in the first call (k13) -> fdiff 0 (superseded by the consolidation).
2026-11-15 same: consolidate on base-like / sibling-shaped / Gfx* arithmetic bodies -> 15..25 (a1-a7, r1-r4); variants scan best 13.
2026-11-15 same: permuter perm_rs6 (from the 2-arg a6 body, 900 s, -j 2): base 607, best 0 at output-0-1 = count reused for the byte length (count = segmentData - mid; count = count >> 3) and len/size dropped; rewritten as `count >>= 3`; fdiff 0 with the shared prototype (applied).
2026-11-15 same: alias-free 2-arg forms: call reads seg->displayListA (p2) 14, start = seg->displayListA separate local (p5/p6) 16, Gfx *start = (Gfx *)head typed pointer (p7) 1 (addu a1,t0,a0 operand order; &start[head] and head + start same 1; reorders 8), expressions inlined into calls (p8) 18, p9 17; scans of p2 and p7 no zero.
2026-11-15 same: permuter perm_p2 (from alias-free p2, 900 s, -j 2): base 75, best 0 only respells the alias as new_var = (head = seg->displayListA) (hack for hack, not applied); next best 30.
2026-11-15 same: retype void *slot -> ModelSlot *slot (stand-in copy with PROTO_SKIP + declaration) -> fdiff 0; shadow proto header + patch for clint.
## Untried ideas
A typed Gfx * view of displayListA/B (ModelType1ObjAddrs fields as Gfx *) once the model.h H1/H2 regeneration lands; p7 shows a typed start pointer is one addu operand order away.
## Evidence
0x4f74 lw a2,32(a0) seg; 0x4f84 sw a2,32(sp) spill; 0x4f88 subu v0,v1,a0 (mid - head in head reg v0); 0x4f90 subu a3,t7,v1 (count = C - B in a3); 0x4f9c sw t9,24(sp) count >> 3 spill; 0x4fa4 addu a1,a0,t0 (start + head * 8); 0x4fa8 lw a2,32(sp); 0x4fac lw a3,24(sp); 0x4fb4 sll t1,a3,3. Callee 61AA0 renderReplaceSegment6Commands is a 2-parameter leaf (a2/a3 temps); 17B90 passes 2 args.

# actorTargetTableLoad (global, src/global/67890.c)
## Sites
- global:80662B90:other:87ac3c (FIXED 2026-11-17) `vtxOffset = start[0] * sizeof(Vtx);` with `s32 start[3]`: the zero
  stored at entry to sp+0x18 and reloaded once in the loop preheader to seed the vertex byte offset in v0.
  Replaced by a per-vertex index `vtxIndex` (`gActorTargetVerts[vtxIndex]`, `vtxIndex++`), set to 0 at entry and
  declared last (after base/i/j). No hack sites remain.
## Attempts
- round 25 (opus:medium): plain, diagnose, permute (vtxOffset = 0: uopt range 5 disappears, ranges 233-239 recolour).
- 2026-11-14 HackactorTargetTableLoad (opus:high), scored with variants.py try (full=):
  - array [1]/[2]: 2
  - array [4]: 4
  - struct field: 205
  - volatile: 14
  - plain 0: 205
  - per-vertex index: 206 (2026-11-17: init right before the loop scores exactly 206)
  - for loop: 230
- 2026-11-17 "2026-11-17: cleanup CleanactorTargetTableLoad" CleanactorTargetTableLoad anthropic/claude-opus-5-5: per-vertex index
  initialised at function entry, above both heapAlloc calls -> fdiff 0 (fixed). Measured with variants.py try:
  - init at entry, index declared 4th of 4 scalars (home -16; 4 orders of base/i/j before it tested): 0
  - init as `s32 vtxIndex = 0;` initialiser, or before `base = (u8 *)header;`: 0
  - init inside `if (gActorTargetCount != 0)` before the calls: 2 (sw zero,0x18(sp) leaves the prologue, now after the beqz at 0x1c)
  - init right before the loop (after the calls): 206 (no live range for the index: the 0 folds, no sw zero, frame 0x18)
  - index declared before i or j (home at -12/-20 instead of -16): 2-4
  - `s32 pad[2]` before the index (home -16) also matches: the pad is not needed
  - without the `base` local (`(u8 *)header + header->unk50`, `header->unk50 + (u8 *)header`, (s32)/(u32) casts):
    86-88 (&gActorTargetQuads CSEd into a1 at 0x30); `s32 base = (s32)header` matches. base is load-bearing.
  - variants.py scan of the final body: no better variant; sweep of the final copy: no sites.
## Untried ideas
- none for hack sites (function is hack-free). Possible later types work: a shared section type
  `{ s32 count; ActorTargetQuad quads[]; }` for the map blob at header->unk50 (needs the target to keep
  recomputing base + header->unk50 twice: lw 0x50(a0) at 0xc and 0x28).
## Evidence
- Frame 0x28: ra at 0x14; only sp+0x18 of the local area is touched (sw zero,0x18(sp) at 0x8 in the prologue,
  lw v0,0x18(sp) at 0x98, sll t7,v0,4 at 0xac, move v0,t7 at 0xb8; v0 += 16 per vertex at 0x16c/0x224/0x2dc/0x390).
- uopt (`uopt_trace.sh`, final copy): cfe homes base -4, i -8, j -12, vtxIndex -16 (= sp+0x18); vtxIndex is
  live range 5, split into 5/237, both `not colored (-ve save)`: its range runs from the entry store across the
  heapAlloc calls (jal at 0x44 and 0x68) to the preheader of the unrolled (4x) j loop, so it keeps its memory home.
- The j loop is fully unrolled (UNROLLING at BB 6, 4 times); header->unk50 is reloaded after the
  gActorTargetCount store (lw 0x50(a0) at 0xc and 0x28).

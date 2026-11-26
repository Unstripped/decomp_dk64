# mapPolyClipToFrustumPlane (global, src/global/55B20_map_chunk.c)
## Sites
global:806582F8:other:05b0e1 other (REMOVED 2026-11-25c): `cur = in;` redundant alias of in feeding `prev = cur + (count - 1)`;
  kept planeIdx in s8 and cur in s7 (Q1551 tie on candidate number); without it, with `plane = &gFrustumPlanes[planeIdx]` kept,
  s7/s8 swap (fdiff 1, score 30).
## Attempts
2026-11-24 Polishglobal55B20c opus: alias dropped, plane local kept (`in + (count - 1)` / `&in[count - 1]`) -> s7/s8 swap at 0x7534, score 30
2026-11-25c LeverScout27 (scout): alias + plane local dropped, PLANE_DIST on the table -> full=0; controls: plane local kept +
  PLANE_DIST(*plane) 6, table inline with `d + (...)` order 24
2026-11-25c CleanmapPolyClipToFrustumPlane opus: applied the scout candidate (`prev = cur` kept in the for header) -> fdiff 0
  whole file, clint uninit 0, cwarn 0; variants scan: only equivalent spellings at 0. `memcpy(&out[n++], cur, ...)` in the
  first arm instead of `memcpy(&out[n], cur, ...); n++;` -> full=4 (the split form is the target's order: increment after the
  call, `addiu s3,s3,1` in the delay slot of `b` at 0x7604).
## Untried ideas
none open (function is hack-free)
## Evidence
target 55B20_map_chunk.o (expected): prev = in + (count-1)*12 into s1 at 0x74dc-0x74f4/0x7528; planeIdx `lw s8,152(sp)` 0x7534;
plane address hoisted `addu s4,t8,t9` 0x754c (index loop over the global table, Q1618 init-only local folds);
`&in[i]` strength-reduced in s2 (`move s2,a0` 0x7550, `addiu s2,s2,12` 0x76a4) with copy `move s7,s2` 0x7584 (Q1620);
d added last in both distances: `add.d $f16,$f0,$f4` 0x75a4, `add.d $f18,$f0,$f8` 0x75d4 ($f0 = `ldc1 56(s4)`), i.e. the
render.h PLANE_DIST order (shared with 2F550_map_render.c x3 and mapFrustumPlaneIntersectEdge).

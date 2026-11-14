# actorCollisionResolveSurfaceHit (global, src/global/7BBD0.c)

## Sites
- ccff05: `*(u8 *)&flag != 0`, the second test of the u8 stack-passed parameter `flag` (8th argument, home byte 343(sp)). The target reads it with `lbu` from the home at both tests (0x84c, 0x92c).
  - With a plain `flag != 0`, uopt builds a ucvt{flag} candidate (adjsave 0.75, bb 2-11) and colours it into s1, which costs a callee-saved register.
  - The pun reads through the address, so no such candidate exists.
- e9a088: `do {} while (0);` after the normal[] *= clamp/8 block.
  - Without it, the clamp variable (cand 233) colours earlier, and pushX/pushZ (cands 62/81) take $f2/$f12 instead of $f0/$f2.

## Attempts
- 2026-11-14 U HackactorCollisionResolveSurfaceHit (:high): all nohit; see the ledger for line counts.
  - ccff05:
    - K&R definition.
    - Second-test spellings, including `(s8)` at 68 lines.
    - One-case switch.
    - Swapped branches.
  - e9a088:
    - for-loop over normal[].
    - scale local reuse.
    - scaledNormal push.
    - Clamp tail restructure.
    - pushX moved into the arm.
    - Float literal forms.
    - Branch order flipped.

## Untried ideas
- ccff05: a caller-side change, if 7CA80's call sites can be shown to pass flag through a different path (e.g. a wrapper). Not supported by any evidence found so far.
- e9a088: none promising. The steer only shifts FP candidate order by one register.

## Evidence
- Target 0x84c `lbu t8,343(sp)` and 0x92c `lbu t5,343(sp)`.
- Target FP: `lwc1 $f0,232(sp)` (worldX) and `lwc1 $f2,224(sp)` (worldZ); pushX/pushZ are computed in $f0/$f2 before `jal actorAppendCallbackS32`.

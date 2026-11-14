# actorCollisionResolveSurfaceHit (global, src/global/7BBD0.c)

## Sites
- ccff05 -> 94c1f4 (2026-11-14 HackactorCollisionResolveSurfaceHit2): `*(u8 *)&flag != 0`, the second test of the u8 stack-passed parameter `flag` (8th argument, home byte 343(sp)). The target reads it with `lbu` from the home at both tests (0x84c, 0x92c). The split-label pad read `*(f32 *)(D_807FD614 + idx * 0x34)` beside it is now `gPlayerPadState[idx].stickMag` (RELOC-EQUIV: 0x95c HI16 and 0x964 `lwc1 $f6,0`/`4(at)` LO16 D_807FD614/gPlayerPadState, both 0x807FD614).
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
- 2026-11-14 U HackactorCollisionResolveSurfaceHit2 (:high, after the PadInputState retype):
  - ccff05/94c1f4: stickMag spelling kept the pun matching (text 0). On that spelling: plain `flag != 0` 118, bare `flag` 114, 30.0f literal 199 (pun with 30.0f 84), nested if 118, u8 snapshot local 118, one-case switch on flag 118, `hit |= ...` 81, ternary 132. Moving the pun to the first test (plain second) also matches: the steer needs one address-taken read, either test.
  - e9a088: on the new spelling, removal 16; block-scoped `f32 clampScale` (Q0601) 92, function-scope snapshot 92, pushZ before pushX 18, scale folded into the push 21, callback before the push 28, recipe scan best 16.

## Untried ideas
- ccff05: none in this file. Since one `&flag` read in either test suffices, the original likely took the address of `flag` (or passed it by reference) in code that was later inlined or removed; no evidence in this TU.
- e9a088: none promising. The steer only shifts FP candidate order by one register.

## Evidence
- Target 0x84c `lbu t8,343(sp)` and 0x92c `lbu t5,343(sp)`.
- Target FP: `lwc1 $f0,232(sp)` (worldX) and `lwc1 $f2,224(sp)` (worldZ); pushX/pushZ are computed in $f0/$f2 before `jal actorAppendCallbackS32`.

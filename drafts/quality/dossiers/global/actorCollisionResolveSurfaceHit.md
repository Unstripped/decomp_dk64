# actorCollisionResolveSurfaceHit (global, src/global/7BBD0.c)

## Sites
- ccff05 -> 94c1f4 (2026-11-14 HackactorCollisionResolveSurfaceHit2): `*(u8 *)&flag != 0`, the second test of the u8 stack-passed parameter `flag` (8th argument, home byte 343(sp)). The target reads it with `lbu` from the home at both tests (0x84c, 0x92c). The split-label pad read `*(f32 *)(D_807FD614 + idx * 0x34)` beside it is now `gPlayerPadState[idx].stickMag` (RELOC-EQUIV: 0x95c HI16 and 0x964 `lwc1 $f6,0`/`4(at)` LO16 D_807FD614/gPlayerPadState, both 0x807FD614).
  - With a plain `flag != 0`, uopt builds a ucvt{flag} candidate (adjsave 0.75, bb 2-11) and colours it into s1, which costs a callee-saved register.
  - The pun reads through the address, so no such candidate exists. On the index-loop copy (-l5): plain gives ucvt cand 24 (adjsave 0.75, live bb 2..11); with the pun only the parameter variable cand 22 (P 31vreg, adjsave 0) remains, and it is not coloured.
- 932d5d (fixed 2026-11-15, HackactorCollisionResolveSurfaceHit3): the triZ pointer walk ending at `&triY[0]` is now the counted loop `for (i = 0; i < 3; i++) guMtxXFMF(selfMtx, verts[i * 3], verts[i * 3 + 1], verts[i * 3 + 2], &triX[i], &triY[i], &triZ[i]);`, written the same way as in the 70FD0 sibling. uopt LFTR rebuilds the walk and the `bne s1,t4` against `addiu t4,sp,200` on its own (Q0630, Q0748).
  - Remove the walker locals: if they stay declared, the frame grows from 0x138 to 0x148 (97 lines).
  - Declare `s32 i` in the old pTriZ slot: declared last, it scores 4.
- e9a088: `do {} while (0);` after the normal[] *= clamp/8 block.
  - Without it, pushX/pushZ (cands 64/69 on the index-loop copy) share a basic block with the clamp/8 udiv (cand 244) and with 303/167. That makes them forbidden from $f0, so they take $f2/$f12 (Q0523: interference is per block). With the split they take $f0/$f2.

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
- 2026-11-15 U HackactorCollisionResolveSurfaceHit3 (:high):
  - 932d5d: fixed as above. Other end tests:
    - `!= &triZ[3]`, `triZ + 3`, or swapped operands: 75 (uopt rewrites the neq as `pTriZ - 12 != triZ`).
    - `< &triZ[3]`: 2 (sltu/bnez).
    - `pTriY < &triY[3]`: 10.
    - `pTriX < &triX[3]`: 12.
    - Index loop with the walker locals still declared: 97.
  - 94c1f4:
    - Param retyped through a PROTO_SKIP stand-in: `s32 flag` 118 (the variable colours, `lw s2,0x154(sp)`), `u32` 118, and `(u8)flag` under either type 128.
    - `(u32)flag` in either test: 118.
    - `(u16)flag`: 122.
    - `flag != 0U`: 122.
    - `== 1` and `== TRUE`: 122.
  - e9a088:
    - D_807FB5D0 used directly, as the 70FD0 sibling does: 104-110.
    - `norm` or `scale` reused for `(f32)clamp / 8`: 16.
    - `for (i)` over normal[]: 35.
    - `8.0f` or `* 0.125f`: 18.
    - `clamp / 8.0f` with no cast: 2.

## Untried ideas
- 94c1f4: none in this file. One `&flag` read in either test is enough, so the original probably took the address of `flag` (or passed it by reference) in code that was later inlined or removed. This TU has no evidence of that. Retyping the parameter and changing the conversion width do not work.
- e9a088: the target needs pushX/pushZ to be defined in a basic block after the last use of the clamp/8 value. No ordinary C construct that splits the block without emitting code was found. The 70FD0 sibling has no matching construct.

## Evidence
- Target 0x84c `lbu t8,343(sp)` and 0x92c `lbu t5,343(sp)`.
- Target FP: `lwc1 $f0,232(sp)` (worldX) and `lwc1 $f2,224(sp)` (worldZ); pushX/pushZ are computed in $f0/$f2 before `jal actorAppendCallbackS32`.
- Target loop at 0x9f0-0xa24: s0/s2/s3/s1 walkers, and the bound `addiu t4,sp,200` is rebuilt inside the loop (LFTR of the counted loop).

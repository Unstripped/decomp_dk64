# arcadeUpdateDonkeyKongStage4 (arcade, src/arcade/0_game.c)
## Sites
arcade:8002F82C:noop-arith:08110d noop-arith: FIXED 2026-11-14 (cnt copy local removed; param re-read).
arcade:8002F82C:comma:ee9630 comma: FIXED 2026-11-14 (frame index in the single tmp local).
arcade:8002F82C:other:fad443 other (removed 2026-11-26, R-oildrum census pass: the reuse is ordinary C, tag dropped,
  base key): `s32 tmp` is the function's only declared word (cfe home -4 = sp+0x34, never touched). Case 2: the
  incremented param byte (`tmp = ++param`: v1 = andi t8,0xff at 0xb93c, `(u8)tmp` = andi t9,v1,0xff at 0xb940). Case 8:
  the dazed-eyes frame selector (`tmp = (s32)(animTimer / 6.0f) % 3`: mfhi v0 0xbc48, `bne v0,v1` at 0xbc7c with v1 = the
  constant 2). Declaration now carries a role comment (`// case 2: the incremented param byte; case 8: the dazed-eyes
  frame selector`); `tmp` is already role-neutral, no rename.
## Attempts
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: cnt + flash -> full=22/20 (only t0 spill 0x2c -> 0x28); no cnt with (u8)++param / ++param / param++ -> 87; (u8)(s32)++param or (++param & 0xFF) -> 0 (steers, not kept)
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: comma: inline == 2 or 2 == x -> 1 (bne v1,v0); switch -> 17; separate frame local -> 20 (spill shift); same tmp as the facing flag -> 0
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: final: s32 tmp = ++param; (u8)tmp < 0xA0; tmp = flag; tmp = (s32)(animTimer / 6.0f) % 3 -> fdiff 0
2026-11-24 2026-11-24: cleanup CleanarcadeUpdateDonkeyKongStage4 CleanarcadeUpdateDonkeyKongStage4 anthropic/claude-opus-5-5 (base 2e593510, re-measure after 05c5a664):
  - three per-role s32 locals (timer, dir, frame) at function scope -> 2: only the frame 0x38 -> 0x40 (addiu sp at
    0xb840/0xbe1c); the t0 spill stays 0x2c. Block-scoped (timer/dir in the gArcadeFrozen block, frame in the girder
    else block) -> 2. Two locals (any pair) -> 20 (t0 spill 0x2c -> 0x28). Zero locals -> frame 0x30, spill 0x28.
    So the original declares exactly one word of locals (odd local-word count keeps the spill at 0x2c, Q0869/Q0361).
  - width grid of the three locals (6^3 types, cast/no cast on the counter, 396 bodies): best 2 (s32/s32|u32/s32);
    u8 timer drops the second andi at 0xb940 (93); narrow frame adds sll/sra or andi after the mfhi (>= 37).
  - `ArcadeEntity *e = &gArcadeEntities[entIndex]` for every access: with tmp -> 20 (spill shift), roles inline -> 15.
  - facing-flag spellings with tmp kept for the other roles: `!((p & 0x20) / 32)` -> 0 (APPLIED), `(...) == 0` /
    `0 == ...` -> 76, `?:` forms -> 79, `!(p / 32 & 1)` -> 6.
  - after the facing fix: timer + frame as two s32 locals -> 20 (spill), function or block scope, either order; s32
    timer + frame inline -> 1 (`bne v1,v0` at 0xbc7c, uequ{2}{rem} canonicalisation); variants scan of that body: no
    zero; s32 frame + counter inline (`++p < 0xA0`, `(u8)++p`, `p++; if (p < 0xA0)`, `(p += 1)`, `(s32)++p`,
    `!(++p >= 0xA0)`) -> 85 (the second andi 0xff at 0xb940 is missing), `(p = p + 1) < 0xA0` -> 125; two-local width
    grid (36 types x order x cast): packed s16/s8 pairs restore the frame and spill but add sll/sra at 0xb940 and after
    the mfhi at 0xbc48 (37).
2026-11-26 fakehunt pass 1 (lead read): 11 permuter zeros, each one local for both roles again (tmp_2 = ++param, plus
  noise): the tagged steer respelled, not a fix and not census evidence; not re-run.
2026-11-26 2026-11-26: cleanup CleanarcadeUpdateDonkeyKongStage4 CleanarcadeUpdateDonkeyKongStage4 anthropic/claude-opus-5-5 (base d366ec4e):
  - R-oildrum three-part census (Q1666, rulings.md 100-118), table below: all three parts hold. `// FAKE:` comment on
    `s32 tmp;` replaced by a role comment (no code change), fdiff 0, clint uninit exit 0 (only the pre-existing
    arcadeUpdatePlayerEntity `i`), cwarn 0.
## Census (Q1666)
Bodies in .scratch/CleanarcadeUpdateDonkeyKongStage4/census/ (P1_*/P2_*), scores `variants.py try`, what moved from
`deadsweep.py score --diff` (census/diffs/), cfe offsets from `as1probe keep` + `ucode --cfe` (census/keep_*/cfe.txt).
Target R0: frame 0x38 (addiu sp,-56 0xb840), ra 0x24, tmp cfe home -4 (sp+0x34, never stored), cfe shared switch vreg -8
(sp+0x30, `vreg s32 Mmt off -8`, never reaches the asm), t0 (&gArcadeEntities[entIndex]) uopt spill sw/lw 44(sp) at
0xb924/0xb928, 0xb984/0xb990, 0xba4c/0xba54, 0xba5c/0xba64, 0xba6c/0xba70, 0xbad8/0xbadc, 0xbb50/0xbb70, 0xbbe8/0xbbf4,
0xbcbc/0xbcf8, 0xbdc4/0xbdd0; word 0x28 = local-area round-up.
Part 1, frame proof (a separate `frame` local for the case-8 frame selector; `tmp` keeps the case-2 param role):
| body | position | score | frame | t0 spill | cfe (tmp / frame / shared vreg) |
|---|---|---|---|---|---|
| F1_after | function scope, after tmp | 20 | 0x38 | 0x2c -> 0x28 | -4 / -8 / -8 -> -12 |
| F2_before | function scope, before tmp | 20 | 0x38 | 0x2c -> 0x28 | moves (same 20 lines) |
| F1r / F2r | `register` after / before tmp | 20 / 20 | 0x38 | 0x2c -> 0x28 | same object as plain |
| B1 / B1r | head of the state switch body (plain / register) | 20 / 20 | 0x38 | 0x2c -> 0x28 | |
| B2 / B2r | braced `case 8:` arm | 20 / 20 | 0x38 | 0x2c -> 0x28 | |
| B3 / B3r | `else` block of `animTimer++ == 720.0f` | 20 / 20 | 0x38 | 0x2c -> 0x28 | |
| B4 / B4r | `else if (animTimer > 200.0f)` block | 20 / 20 | 0x38 | 0x2c -> 0x28 | |
| B5 / B5r | girder `else` block (where the role lives) | 20 / 20 | 0x38 | 0x2c -> 0x28 | -4 / -8 / -8 -> -12 |
| B6 | bare `{ s32 frame = ...; if ... }` around the role | 20 | 0x38 | 0x2c -> 0x28 | |
| N1 | tmp in the gArcadeFrozen block, frame function scope | 20 | 0x38 | 0x2c -> 0x28 | |
| N2-N5 | tmp in the gArcadeFrozen block, frame in braced case 8 / 720 else / >200 / girder block | 20 each | 0x38 | 0x2c -> 0x28 | |
| N6 | tmp in braced case 2, frame in braced case 8 (siblings) | 20 | 0x38 | 0x2c -> 0x28 | |
| N7 / N8 | both at the switch-body head, tmp/frame and frame/tmp | 20 / 20 | 0x38 | 0x2c -> 0x28 | |
| N9 | tmp in braced case 2, frame function scope | 20 | 0x38 | 0x2c -> 0x28 | |
| N10 | tmp in braced case 2, frame in the girder block | 20 | 0x38 | 0x2c -> 0x28 | |
| W s8 / s16 (after, before, girder) | narrow frame (not the value's width: s32 % 3, no narrowing after mfhi 0xbc48) | 55 each | 0x38 | 0x2c -> 0x28 | plus sll/sra after the mfhi |
| W u8 / u16 (after, before, girder) | same | 136 each | 0x38 | 0x2c -> 0x28 | plus andi/temp renumbering |
Every s32 split diff is exactly the 10 t0 spill pairs 44(sp) -> 40(sp) (20 lines), nothing else. cfe gives the new local
its own home -8 and moves its shared switch vreg -8 -> -12 (base: tmp -4 x6, vreg -8 x10; split: tmp -4 x2, frame -8 x4,
vreg -12 x10), so uopt's spill temp lands at -16 = 0x28 instead of -12 = 0x2c: the move comes from the new local's own
slot (displaced spill temp, as in arcadeUpdateOilDrumEntity). Holds at every position. PASS.
Part 2, no-local proof (no separate local for the frame selector; tmp kept for the param role):
| body | spelling | score | what differs |
|---|---|---|---|
| X1 | `(s32)(animTimer / 6.0f) % 3` inline in each of the three tests | 1 | `bne v1,v0` for `bne v0,v1` at 0xbc7c (constant-first compare of the CSE'd value, Q0770); animTimer is read once (lwc1 0xbc04) in both, so the re-read form is the same code |
| X1m | mirrored `0 == E` / `1 == E` / `2 == E` | 1 | same flip |
| X1n | `!(E)` / `E == 1` / `E == 2` | 1 | same flip |
| X1e | third test dropped (`else`) | 14 | behaviour change, branch shape |
| X2 | `switch (E) { case 0/1/2 }` | 17 | switch lowering |
| X3 / X3b | function-local `static s32 frame;` (function / girder block) | 19 / 19 | `sw` to .bss after the mfhi (Q1680) |
| X4 | frame stored to `param2`, the tests re-read the field | 47 | extra sb + lbu (behaviour: clobbers param2) |
| X5 | `ArcadeEntity *kong` in the girder block, `kong->animTimer` inline | 30 | pointer home/registers |
| X10 | `ArcadeEntity *kong` at function scope for every access, frame inline | 21 | pointer home + spill shift + flip |
| X6 | function-local static sprite table indexed by E | 39 | .data table + lw, no compares |
| X9 | one ternary chain into `sprite` | 67 | extra store/branch shape |
| scan | `variants.py scan --max 0` of the X1 body (143 variants: truth, swap, arith, elem, branch, float, width, declswap) | best 1 | no zero |
Role 1 without a local (tmp kept for the frame role), for the record: `(u8)++param < 0xA0` 85 (second andi 0xff at 0xb940
missing); zero locals 108 (frame 0x30). Earlier units: counter-inline spellings 85-125. FAIL for every no-local spelling: PASS.
Part 3, plausibility: both roles are s32. Role 1 `tmp = ++gArcadeEntities[entIndex].param` (u8 field promoted; the
target holds the value in v1, andi t8,0xff 0xb93c, and executes the `(u8)tmp` conversion andi t9,v1,0xff 0xb940, so the
holder is wider than u8); role 2 `(s32)(animTimer / 6.0f) % 3` (trunc.w.s 0xbc38, mfc1 v0 0xbc3c, signed div/mfhi
0xbc44/0xbc48). Role 1: def/use copy lines 3258-3259, inside `case 2:` (3248-3269; the `< 0xA0` arm returns at 3261);
role 2: def 3305, uses 3306/3308/3310, inside case 8's girder else block (3298-3321). The state switch (3247) runs one
case per call, no loop, each role is read only after its own def on the same path; tmp is dead at exit. Target regions:
case 2 0xb864-0xb9c4 (role 1 v1 0xb93c-0xb958), case 8 from 0xb9c8 (dispatch `beql v0,at,b9c8` 0xb854; role 2 v0
0xbc3c-0xbc7c). A generic s32 scratch `tmp` reused for two short-lived per-case intermediates is ordinary original code;
the name is already role-neutral, so no rename, only a role comment. PASS.
Hidden-reuse check: entIndex is never reassigned; tmp is the only declared local (its third role, the facing flag, left
on 2026-11-24). None.
## Untried ideas
- none: census complete (frame 0x38 = args 0x00-0x1f (n_alSndpPlay stack args 0x10/0x14/0x18), save area with ra 0x24,
  local area 0x28-0x37: tmp -4 (0x34), cfe shared vreg -8 (0x30), t0 spill -12 (0x2c), round-up 0x28).
## Evidence
0xb93c andi v1,t8,0xff = value of ++param; 0xb940 andi t9,v1,0xff = (u8)tmp; 0xb958 andi t2,v1,0x1f; 0xb994 lbu v1,0x1c(t0) re-read after n_alSndpPlay; 0xb998 andi v0,v1,0x20; 0xb9b8 sltiu t5,t4,1; 0xb9c0 sb t5,0x1a(t0).
Frame 0x38, ra 0x24, t0 spill 0x2c: zero locals 0x30/0x28, one 0x38/0x2c, two 0x38/0x28, three 0x40/0x2c (Q0869, Q0361).
0xbc7c bne v0,v1: v0 = frame index, v1 = constant 2 shared with gArcadeGirderState (0xbbc4, 0xbc00).
cfe ucode (base d366ec4e): tmp = M -4; one `vreg s32 Mmt off -8 lexlev 1` (the state switch selector, str/lod -8); a
split local takes -8 and the vreg moves to -12 (Q1680, Q0940).

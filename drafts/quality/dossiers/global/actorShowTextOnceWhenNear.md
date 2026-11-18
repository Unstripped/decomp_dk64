# actorShowTextOnceWhenNear (global, src/global/C4620.c)

## Sites
global:806C151C:other:9dfb9e other (base line 604, `if ((u8)near)` FAKE): the target's per-test
`andi t6,a3,0xff` (0x1c74 in the bc1fl delay slot, 0x1c7c on the fall-through) before `beqzl t6` at 0x1c80, with
the 0/1 flag in a3. FIXED 2026-11-17 by a hand rewrite: no dx/dy/dz locals, the squared distance written with
`SQ()`, and the flag at its natural type, `u8 near = ... < 4900.0f; if (near)`. fdiff 0, no tag.

## Attempts
2026-11-10 cleanup round 9 CleanGlobalC4620 opus:low: sweep plain (u8 near local) -> fails; as1probe keep confirms
  andi t6,a3,0xff on both paths before beqzl; permuter hint `near & 0xFFFF` -> nohit
2026-11-11 cleanup round 16 Rev16B opus:xhigh: `u8 near = (dist < 4900.0f)` (delta locals kept) -> bc1fl+andi shape,
  near in t6 (andi t7,t6), fdiff 35
2026-11-11 cleanup round 16 Rev16D opus:xhigh: permuter from s32 two-step `if (near)`, best=0 = `near & 0xFFu` (swap)
2026-11-11 cleanup round 17 Rev17N opus:low: permuter best=0 = the `(u8)near` cast again
2026-11-12 cleanup round 31 CleanGlobalC4620 opus:medium: permuter best=0 = `near & 0xFFu`; others add & 0xFFFF chains,
  (u8) temps, commas
2026-11-17 cleanup CleanactorShowTextOnceWhenNear opus-5-5: with the dx/dy/dz locals kept (variants.py try):
  two-step s32/u32/s8/u8/s16/u16 -> full=4 each (no andi, beqzl a3); `near != 0` -> 4; bool-style s32/u32/s8/s16 -> 6,
  u8/u16 -> 5 (shape 0, regs only); near declared first -> 5-6; f32 dist local -> 5-6; folded compare -> 6;
  s32 two-step + `near & 0xFF` -> 0 (an interim ORIG candidate, superseded).
  Permuter with hack-free weights from bool-style u8 (base 35), 900 s: best=0. All 12 zeros re-insert a steer
  (dead `if (near) {}` / `if (!near) {}` / `(near && near && near)`, `dz = (near = ...)`, `dy = flagId` plus a dead if,
  dz recomputed inline at output-0-3). The output-0-3 hint led to dropping the delta locals:
  SQ() / written-out bool-style u8 -> full=0 (FIX), u16 -> 2, s32 -> 4; SQ two-step any width -> 4;
  SQ + f32 dist local -> 8-9; SQ folded into the if -> 6.

## Untried ideas
none (fixed).

## Evidence
- expected/build/src/global/C4620.o: the function is at 0x1bfc. `move a3,zero` 0x1c54; `c.lt.s` 0x1c68; `bc1fl` 0x1c70,
  whose delay slot is `andi t6,a3,0xff` 0x1c74; `li a3,1` 0x1c78; `andi t6,a3,0xff` 0x1c7c; `beqzl t6` 0x1c80.
- uopt_trace of the fix: the u8 near (M -1) is live range 0, assigned colour 6 (a3). The ugen compare-to-int
  materialises into a3, and the u8 store narrowing (ucvt) becomes the andi into t6 at the single test.
  With the three f32 delta locals (M -4/-8/-12) near (M -13) gets no coloured live range, so the value stays in ugen
  temps t6/t7 (andi t7,t6).
- Callers (0x20ac, 0x2208, 0x2380, 0x24fc, 0x2824) pass exactly three arguments and never set a3, so there is no 4th
  parameter. The home reloads fix the parameter types: lhu 26(sp) u16, lbu 31(sp) u8, lh 34(sp) s16.
- SQ is the same `#define SQ(x) ((x) * (x))` as 12E800 (placed inside the function body there too), 5E2F0, 68EA0 and CEAE0.

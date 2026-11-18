# faultDrawRegs (global, src/global/136820.c)

## Sites
- 5fb2de: `((s32 *)&ctx->ra)[1]`, a low-word read of the u64 saved ra. KEPT.
  - The target passes only `lw a1,228(s6)` (0x400, delay slot of `jal faultPrintf` at 0x3fc).
  - Any u64 -> 32-bit conversion makes ugen load the whole value into an aligned ring pair
    (`lw $8,224($22); lw $9,228($22); move $5,$9`): as1 deletes the dead high-word `lw` and folds the
    `move`, so the line's own code is identical, but t0/t1 are burned and D_807563B8 moves t0 -> t2
    (and every later ring temp by two).

## Attempts
- 2026-11-14 U HackfaultDrawRegs, fdiff lines:
  - Whole u64 passed: 2 (a2/a3 pair).
  - `(u32)` / `(s32)`: 14.
  - Masks: 17.
  - `>> 0`: 7.
  - Locals: 20-22.
- 2026-11-17 cleanup CleanfaultDrawRegs anthropic/claude-opus-5-5 (score = variants.py full):
  - ugen ring of `(u32)ctx->ra` (as1probe keep): queue after `li t6/t7/t8` (0x34c/0x35c/0x384) and the
    chained-store reload `lw $25,0($23)` (as1 deletes it) is `t0 t1 t2 ...`; the pair takes t0/t1.
  - Chained store split `D_807FEF7C = x; D_807FEF70 = x;` + `(u32)`: no t9 burn; the pair skips the odd
    front t9 and leaves it at the front, so D_807563B8 lands in t9 ($25): 14. Reverse split order: 22.
    The pun with the split store: 14 (D_807563B8 in t9): the chained store is load-bearing.
  - `(u32)(s64)ctx->ra`: 14 (same pair). `(u32)a0->context.ra` (no ctx): 23.
  - `variants.py scan` of the `(u32)` body (swap/width/declswap, 24 variants): best 14.
  - Hack-free weights permuter from the `(u32)` body, -j 2, 900 s (69292 iterations): base 80, best 30
    (fdiff 5). The best reuses one s32 local for the chained-store value and D_807563B8; uopt colours it
    v0, the chain reload leaves the ring, the t0/t1 pair skips t9: D_807563B8 in v0 (target t0, 0x404),
    D_807FF018 in t9 (target t1, 0x418). An unrelated reused local: a steer, and still not 0.
  - Parameter `a0` renamed `thread` (fdiff 0).

## Untried ideas
- None that stays natural C: a 32-bit view of the saved ra needs a types change in the shared SDK
  header `include/PR/os_thread.h` (`u64 gp, sp, s8, ra;`), and a union there would rename every
  `context.ra` user (createthread.c, faultUnwindStack). A file-local view struct is still a pun.

## Evidence
- Target 0x3fc: `jal faultPrintf` with `lw a1,228(s6)` in the delay slot; s6 = &a0->context (0x3c4).
- Target ring: `li t6` 0x34c, `li t7` 0x35c, `li t8` 0x384, then D_807563B8 in t0 (0x404), D_807FF018
  in t1 (0x418) and t2 (0x438), t3/t4 (0x474/0x478), t5 (0x4b4): exactly one ring allocation (t9, the
  chained-store reload) between 0x384 and 0x404, so the original had no u64 load at line 166.
- A pair keeping D_807563B8 in t0 needs the queue `t8 t9 t0 ...` at the conversion: nine single ring
  allocations between 0x384 and 0x400 where the target has one.
- cfe ucode of `(u32)ctx->ra`: `ldc 224; add Adt; ilod u64; cvt u32 u64`; uopt output keeps
  `ilod u64 i 224; cvt u32 u64` (no narrowing to a 32-bit ilod). The pun is `ilod s32 i 228` after uopt.
- Same TU, faultUnwindStack's natural `sp = a0->context.sp; ra = a0->context.ra;` (s32 locals) shows the
  pairs in the target: `lw t9,0xf4(a0)` (0x668, pair t8/t9) and `lw t1,0x104(a0)` (0x674, pair t0/t1).
- Other IDO games spell the ra print `(u32) tc->ra` (SM64 crash_screen.c) / `(u32)ctx->ra` (OoT fault):
  the tried `(u32)` spelling, 14 here.

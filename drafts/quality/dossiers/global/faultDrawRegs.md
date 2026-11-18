# faultDrawRegs (global, src/global/136820.c)

## Sites
- 5fb2de: `((s32 *)&ctx->ra)[1]`, a low-word read of the u64 saved ra. KEPT.
  - The target passes only `lw a1,228(s6)` (0x400, delay slot of `jal faultPrintf` at 0x3fc).
  - Any u64 -> 32-bit conversion makes ugen load the whole value into an aligned ring pair
    (`lw $8,224($22); lw $9,228($22); move $5,$9`): as1 deletes the dead high-word `lw` and folds the
    `move`, so the line's own code is identical, but t0/t1 are burned and D_807563B8 moves t0 -> t2
    (and every later ring temp by two).
  - Lead ruling 2026-11-18: stays FAKE, not ORIG. Both spellings end in the same `lw a1,228(s6)` at
    0x400; they differ only in register numbering (the ring), which is regalloc evidence.

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
- 2026-11-18 cleanup CleanfaultDrawRegsb anthropic/claude-opus-5-5 (score = variants.py full / fdiff):
  - Of the registers this function prints, only ra is a u64 slot: pc is the u32 field
    (`lw a1,252(s6)` at 0x3f0), so no consistent low-word view exists in the base.
  - u32 register-array view for both prints, `u32 *regs = (u32 *)&thread->context;` with `regs[63]`
    (pc) and `regs[57]` (ra low): fdiff 0, but a `punned-cast` site (ucde1d) with magic indices.
  - Game-local view `FaultContext` (`FaultGpr` = `u32 hi, lo` for each of the 31 u64 slots, then
    `u32 sr, pc, ...`), `ctx = (FaultContext *)&thread->context;`, `ctx->pc`, `ctx->ra.lo`: fdiff 0 and no
    AST site, but still a view chosen for codegen. Kept as header-request candidates only.
  - Pun through `((u32 *)&thread->context.ra)[1]` without the ctx local: 11.
  - as1probe keep confirms the ugen records: pun `lw $5,228($22)`; `(u32)` adds the 224/228 pair and
    `move $5,$9`, with D_807563B8 in `$10` (t2).

## Untried ideas
- None that stays natural C. A 32-bit view would need a header type: a game-local context view with
  u32 halves (its only user would be faultDrawRegs, since faultUnwindStack needs the u64 reads, as the
  pairs at 0x668/0x674 show), or an `__OSfp`-style union in the SDK header `include/PR/os_thread.h`
  (renames every `context.a0/sp/ra` user: createthread.c 30-32, faultUnwindStack 228-229; not measured).

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

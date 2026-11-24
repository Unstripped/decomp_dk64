# faultDrawRegs (global, src/global/136820_fault.c)

## Sites
- 5fb2de: `((s32 *)&ctx->ra)[1]`, a low-word read of the u64 saved ra. KEPT.
  - The target passes only `lw a1,228(s6)` (0x400, delay slot of `jal faultPrintf` at 0x3fc).
  - Any u64 -> 32-bit conversion makes ugen load the whole value into an aligned ring pair
    (`lw $8,224($22); lw $9,228($22); move $5,$9`): as1 deletes the dead high-word `lw` and folds the
    `move`, so the line's own code is identical, but t0/t1 are burned and gFaultDrawCount (was D_807563B8)
    moves t0 -> t2 (and every later ring temp by two).
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
  - Chained store split `gFaultLineStartX = x; gFaultCursorX = x;` + `(u32)`: no t9 burn; the pair skips the
    odd front t9 and leaves it at the front, so gFaultDrawCount lands in t9 ($25): 14. Reverse split
    order: 22. The pun with the split store: 14 (gFaultDrawCount in t9): the chained store is load-bearing.
  - `(u32)(s64)ctx->ra`: 14 (same pair). `(u32)a0->context.ra` (no ctx): 23.
  - `variants.py scan` of the `(u32)` body (swap/width/declswap, 24 variants): best 14.
  - Hack-free weights permuter from the `(u32)` body, -j 2, 900 s (69292 iterations): base 80, best 30
    (fdiff 5). The best reuses one s32 local for the chained-store value and gFaultDrawCount; uopt colours
    it v0, the chain reload leaves the ring, the t0/t1 pair skips t9: gFaultDrawCount in v0 (target t0,
    0x404), gFaultStackTraceCount in t9 (target t1, 0x418). An unrelated reused local: a steer, and still not 0.
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
    `move $5,$9`, with gFaultDrawCount in `$10` (t2).
- 2026-11-19 2026-11-18c: cleanup CleanfaultDrawRegsc CleanfaultDrawRegsc anthropic/claude-opus-5-5:xhigh
  (current body after f960a16f..4e14b5c5 and 7a1f8709; score = variants.py try full):
  - `(u32)ctx->ra` 14, `(s32)ctx->ra` 14, `(void *)ctx->ra` 14 (new: pointer spelling of a return
    address; cfe emits the same `cvt u32 u64`), whole u64 `ctx->ra` 2 (shape 1: a2/a3 pair, and `%X`
    would print the wrong word), chained store split + `(u32)` 14, `FaultStackEntry *entry` walk of
    gFaultStackTrace + `(u32)` 20 (new).
  - `variants.py scan` of the `(u32)` body on the current text (24 variants): best 14.
  - uopt_trace -l 6 base vs `(u32)`: identical colouring (the same 14..22/1 assignments in the same
    order; the extra `ucvt{202|1}` candidate #21 stays uncoloured), so the whole diff is ugen's.
  - as1probe keep + ringfifo sim: ugen hands out `$8 $9 $10` after the `$25` chained-store reload and
    before `$11`, i.e. the ring here is `t6 t7 t8 t9 t0 t1 t2 t3 t4 t5` (Q0418); the pair takes t0/t1 and
    every later temp moves two: gFaultDrawCount `$10` (target t0 0x404), gFaultStackTraceCount `$11` (t1
    0x418), its reload `$12` (t2 0x438), `mul`/gFaultMessageArg2 `$13`/`$14` (t3/t4 0x474/0x478),
    gFaultDrawCount+1 `$15` (t5 0x4b4). No ring allocation sits between the pair (0x400) and 0x404 to
    absorb the shift, and a pair that keeps t0 needs the front at t8: a full 10-register ring cycle after
    `li t8` (0x384) where the target has one allocation (t9).
- 2026-11-24 2026-11-24: cleanup CleanfaultDrawRegsd CleanfaultDrawRegsd anthropic/claude-opus-5-5
  (re-measure after 642afafe file-scope edits in other functions: faultPrintf case char literals and
  compound assigns, unwindDecodeJrRa comments, faultThreadMain `for (;;)`, osCreateThread `NULL`; the
  faultDrawRegs body is unchanged; score = variants.py try full):
  - `(u32)ctx->ra` 14, `(s32)` 14, `(void *)` 14, `(u32)(s64)` 14, whole u64 2 (shape 1), mask 17
    (shape 3), `(u32)(ctx->ra >> 0)` 7 (shape 7), chained store split + `(u32)` 14, reverse split +
    `(u32)` 22, split + pun 14, pun without ctx (`((u32 *)&thread->context.ra)[1]`) 11, `(u32)` without
    ctx (pc as `thread->context.pc` too) 25, u32 register-array view 0 (pun), u32 local 20,
    `FaultStackEntry *entry` walk (`j++, entry++`) + `(u32)` 14 (was 20 in another spelling).
  - `variants.py scan --max 1000` of the `(u32)` body: 31 variants (truth/swap/width/declswap), best 14.
  - uopt_trace -l 6 pun vs `(u32)`: same assignment sequence `14..21, 1, 22, 1`, 27 uncoloured each;
    `(u32)` candidate numbers are +1 (the extra cvt candidate). as1probe keep: the same ugen ring as
    2026-11-18c (`$25` reload, pair `$8/$9`, then `$10..$15` where the target has t0..t5).
  - New: a `count` local for the gFaultDrawCount test (Q1553/Q0601) makes it a uopt candidate coloured
    `$2` (v0) instead of ring t0 (target `lw t0` 0x408): pun + count 14 (gFaultStackTraceCount `$8`, target
    t1), `(u32)` + count 14 (`$10`). A uopt-coloured load cannot absorb the pair.
  - Hack-free weights permuter from the `(u32)` body on the current text, -j 2, 900 s (85425
    iterations): base 80, best 30 (variants.py try 5 once translated), the same family as 2026-11-17: a
    temp for the chained-store value (`start = gFaultLineStartX = x;`, uopt `$2`, so no `$25` reload)
    plus `(count = gFaultDrawCount) >= 4` (uopt `$2`, target t0 0x404-0x408): the pair skips the odd
    front t9 and gFaultStackTraceCount lands in `$25` (target t1 0x418). Its other edits (a
    `&gFaultDrawCount` pointer re-read, a `thread` alias) change nothing. Four steers, not 0.

## Untried ideas
- None that stays natural C. A 32-bit view would need a header type: a game-local context view with
  u32 halves (its only user would be faultDrawRegs, since faultUnwindStack needs the u64 reads, as the
  pairs at 0x668/0x674 show), or an `__OSfp`-style union in the SDK header `include/PR/os_thread.h`
  (renames every `context.a0/sp/ra` user: createthread.c 30-32, faultUnwindStack 225-226; not measured).

## Evidence
- Target 0x3fc: `jal faultPrintf` with `lw a1,228(s6)` in the delay slot; s6 = &thread->context (0x3c4).
- Target ring: `li t6` 0x34c, `li t7` 0x35c, `li t8` 0x384, then gFaultDrawCount in t0 (0x404),
  gFaultStackTraceCount in t1 (0x418) and t2 (0x438), t3/t4 (0x474/0x478), t5 (0x4b4): exactly one ring
  allocation (t9, the chained-store reload as1 deletes; the stores are `sw s5,0(s7)` / `sw s5,0(s8)` at
  0x3c8/0x3cc) between 0x384 and 0x404, so the original had no u64 load at line 166.
- Ring arithmetic left for natural C (2026-11-24): every u64 read burns an aligned pair, so the six ring
  temps after 0x400 move by two unless 8 extra invisible ring allocations (as1-deleted reloads) or 2
  fewer sit between `li t8` 0x384 and 0x404; only one invisible allocation exists there (the `$25`
  chained-store reload), the other three are the visible constants, and a uopt-coloured gFaultDrawCount
  (count local) leaves t0 itself. No single-site or natural lever remains.
- A pair keeping gFaultDrawCount in t0 needs the queue `t8 t9 t0 ...` at the conversion: nine single ring
  allocations between 0x384 and 0x400 where the target has one.
- cfe ucode of `(u32)ctx->ra`: `ldc 224; add Adt; ilod u64; cvt u32 u64`; uopt output keeps
  `ilod u64 i 224; cvt u32 u64` (no narrowing to a 32-bit ilod). The pun is `ilod s32 i 228` after uopt.
- Same TU, faultUnwindStack's natural `sp = thread->context.sp; ra = thread->context.ra;` (s32 locals)
  shows the pairs in the target: `lw t9,0xf4(a0)` (0x668, pair t8/t9) and `lw t1,0x104(a0)` (0x674, pair
  t0/t1).
- Other IDO games spell the ra print `(u32) tc->ra` (SM64 crash_screen.c) / `(u32)ctx->ra` (OoT fault):
  the tried `(u32)` spelling, 14 here.
- Tooling: `tools/ringfifo.py` RING `[14,15,24,25,11,12,13]` omits `$8-$10`; on this function's listing
  `sim` ignores the `$8/$9/$10` allocations and prints `mismatches: 0`, while a 10-register ring
  `[14,15,24,25,8,9,10,11,12,13]` reproduces every temp of both the base and the `(u32)` listing.

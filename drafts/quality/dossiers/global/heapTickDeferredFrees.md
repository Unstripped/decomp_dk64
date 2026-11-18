# heapTickDeferredFrees (global, src/global/15050.c)
## Sites
- c6d150 dead-if (FIXED 2026-11-17 CleanheapRegisterSurvivor): `if (gHeapDeferredFreeCount && gHeapDeferredFreeCount) {}` after `count = gHeapDeferredFreeCount`.
  - It was a two-block split: any two-term guard on a live local matched, any one-term guard did not.
  - It spread the count local (cand 19) over two more blocks: adjsave 17.33 -> 13.0. That put count below the ucg1-of-count end-pointer candidate (cand 51, 15.0).
  - So cand 51 took v1 and count a0 (target `lw a0,0(s1)` at 0x143c, `blez a0` at 0x1448). Without the guard, count got v1.
  - Fix: no count local and no entry pointer. The loop bound reads the global inline (`while (i < gHeapDeferredFreeCount)`) and every entry access indexes the array (`gHeapDeferredFrees[i].delay`, `.ptr`, `gHeapDeferredFrees[gHeapDeferredFreeCount]`). uopt -l5: the global's uilod candidate (bit 19) has adjsave 14.0 and the end-pointer ucg1 (bit 45) 15.0. The end pointer colours first and takes v1, the count load takes a0, as in the target. fdiff 0.
## Attempts
- 2026-11-10..14 rounds 6/19/24/36 (low, unlevelled, xhigh): uopt traces and permuter runs. best=0 only through new empty tests or do-while steers.
- 2026-11-16 cleanup HackloadOverlay2 anthropic/claude-opus-5-5:high, scored with variants.py try (full=):
  - plain removal, `if (1) {}`, `if (1 && 1) {}`, `if (count) {}`, `if (gHeapDeferredFreeCount) {}`: 10
  - two-term guards on count, flag, i, notExpected, addrBias, and mixed count/global terms: 0
  - two-term position sweep: 0 only directly after the count load. Before it: 10-14. In the loop: 37-42.
  - natural forms:
    - `if (count)` / `if (count > 0)` wrapper: 15
    - early return on count == 0 / <= 0: 15
    - early return on the global before the load: 17
    - `for (i = 0; i < count;)`: 47
    - if + do-while: 10
    - `for (;;)` with break: 64
    - `count > i`: 10
    - `count = --gHeapDeferredFreeCount`: 10
    - indexing without the entry pointer: 10
    - `!flag`: 10
    - flag as ternary: 17
    - flag as comparison: 49
    - count load before the flag test: 68
    - count load before the hook: 72
- 2026-11-17 cleanup CleanheapRegisterSurvivor anthropic/claude-opus-5-5, scored with variants.py try (full=):
  - entry pointer kept, loop bound read inline (`while (i < gHeapDeferredFreeCount)`, no count local): 25
  - same with `for (; i < gHeapDeferredFreeCount;)`: 25
  - same with a per-role `last = --gHeapDeferredFreeCount` (or `gHeapDeferredFreeCount--; last = gHeapDeferredFreeCount;`) for the moved entry: 10
  - count local for the bound plus `last` for the moved entry, `count = last`: 13
  - struct copy `*entry = gHeapDeferredFrees[gHeapDeferredFreeCount]`: 37 (the copy moves 8 bytes; the target moves the word and the byte)
  - indexing with the count local kept: 10
  - indexing plus inline global reads, no count or entry local: 0 (fdiff 0, kept)
  - indexing plus inline reads with a struct copy of the moved entry: 19
  - variants.py scan on the fixed body: zeros only for comparison mirrors, `flag` widths and declaration swaps; `notExpected` as u32: 43.
## Untried ideas
- none for the removed site.
## Evidence
- target 0x13e0-0x14f0:
  - count in a0: `lw a0,0(s1)` at 0x143c, `blez a0` at 0x1448
  - after a free, the decremented count comes back in a0 (`addiu a0,t3,-1` at 0x148c, `sw a0,0(s1)` at 0x14a0)
  - the loop is strength-reduced to an entry pointer s0 against the end pointer v1 (`addu v1` at 0x14ac/0x14c4, `sltu at,s0,v1` at 0x14cc)
  - `i * 8` is computed from s2 = 0 at 0x144c (`sll t8,s2,0x3`): i is not constant-propagated into the first entry address
- traces: .scratch/HackloadOverlay2/tr5_td_keep.txt and tr5_td_rm.txt; .scratch/CleanheapRegisterSurvivor/t/tr_td_plain5.txt, tr_td_keep5.txt, tr_td_fixed5.txt

# heapTickDeferredFrees (global, src/global/15050.c)
## Sites
- c6d150 dead-if: `if (gHeapDeferredFreeCount && gHeapDeferredFreeCount) {}` after `count = gHeapDeferredFreeCount`.
  - It is a two-block split: any two-term guard on a live local matches, any one-term guard does not.
  - It spreads count (cand 19) over two more blocks: adjsave 17.33 -> 13.0. That puts count below the ucg1-of-count candidate (cand 51, 15.0).
  - So cand 51 takes v1 and count takes a0 (target `lw a0,0(s1)` at 0x143c, `blez a0` at 0x1448). Without the guard, count gets v1.
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
## Untried ideas
- A natural construct that adds two empty blocks between the count load and the loop pre-test. The target has none: `blez a0,14d8` follows the load directly.
## Evidence
- target 0x13e0-0x14f0:
  - count in a0: `lw a0,0(s1)` at 0x143c, `blez a0` at 0x1448
  - after a free, the decremented count comes back in a0 (`addiu a0,t3,-1` at 0x148c)
  - the loop is strength-reduced to an entry pointer (`sltu at,s0,v1` at 0x14cc)
- traces: .scratch/HackloadOverlay2/tr5_td_keep.txt and tr5_td_rm.txt

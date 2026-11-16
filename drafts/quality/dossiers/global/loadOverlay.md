# loadOverlay (global, src/global/15050.c)
## Sites
- 06800c/107109/d792f5/5b9db4: u64 header save/restore. Retagged ORIG: target lw/sw pairs at 0x384-0x3a8 and 0x4a8-0x4cc.
- eb8b38 (fixed 2026-11-16): the dead if (gHeapPools[0].start == 0) {} in the rebuild loop.
  - It was a block split (Q0908): if (1) {} at the same spot also matched.
  - The extra block keeps the vram home store (t3, sp+0xE8, at 0x1ec) ahead of the sz spill (0x25c).
  - Replaced by an empty `default: break;` in the pool-size `switch (i)`.
## Attempts
- earlier rounds: low, unlevelled, xhigh round 36 (see the history file)
- 2026-11-14 U, scored with variants.py try (full=):
  - ORIG classification
  - eb8b38 while loop: 3
  - eb8b38 for-init: 5
  - eb8b38 previous-pointer walk: 123
- 2026-11-16 cleanup HackloadOverlay2 anthropic/claude-opus-5-5:high, on the u32 size/bssSize body:
  - eb8b38 removal: 3
  - guards `1`, `q`, `i`, `blk`, `gHeapPools[0].start`, `gHeapPools[0].size == 0`: 0. Two-term `q && q`: 29.
  - `if (1) {}` position sweep: 0 from `id = -1` through the dma call. Exceptions: loop-1 body, `dst = addr[0]`, the four heapInitBlockPool calls and loop 2 (6).
  - natural block sources in that window:
    - ternary as if/else: 3 or 8
    - default-then-assign forms: 36 or 10
    - `case 1:` before `default:`: 0
    - `default:` last: 7
    - `gHeapSurvivorCount > 0`: 4
    - `id >= 0`: 10
    - trailing return: 3
    - loop-2 `default: break;`: 0 (applied, fdiff 0)
## Untried ideas
- none for eb8b38 (fixed)
## Evidence
- target_15050.s (objdump of expected/build/src/global/15050.o)
- pool-size switch: `sltiu at,s1,5; beqz at,23c` at 0x1f4/0x1f8. The jump table at .rodata+0x2c has 5 entries.
- `switch (overlayId)` jump table at .rodata+0: case 1 points at the default arm (0xd4).
- variant scores: .scratch/HackloadOverlay2/lo, pos, nat

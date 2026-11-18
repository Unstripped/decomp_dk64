# loadOverlay (global, src/global/15050.c)
## Sites
- 06800c/107109/d792f5/5b9db4: u64 header save/restore. Retagged ORIG: target lw/sw pairs at 0x384-0x3a8 and 0x4a8-0x4cc.
- eb8b38 (fixed 2026-11-16): the dead if (gHeapPools[0].start == 0) {} in the rebuild loop.
  - It was a block split (Q0908): if (1) {} at the same spot also matched.
  - The extra block keeps the vram home store (t3, sp+0xE8, at 0x1ec) ahead of the sz spill (0x25c).
  - Replaced by an empty `default: break;` in the pool-size `switch (i)`.
- 71b822 other (kept): the empty `default: break;` in the pool-size `switch (i)`, a block split (lead retag 2026-11-16b). Without it the vram home store `sw t3,232(sp)` leaves the loop preheader (0x1ec) for the `beqz s2` delay slot after the pool loop (3 lines). The range check `sltiu at,s1,5; beqz at,0x23c` goes straight to the join: no default code to cite.
- 1c4e4e / d2dcae other (pre-existing, tagged 2026-11-18 under the director's field re-read ruling): `bssSize = ... - gSegmentTable[id].bssStart` and `size = (s32)gSegmentTable[id].bssStart - vram` re-read the field the bssStart local holds. The target loads it once (`lw v1,16(v0)` at 0x170: subu t8 0x180, home store sw v1,228(sp) 0x188, subu s0 0x18c). Spelled with the local, bssStart (homed at 228(sp)) gains a use in the if block and gets a register from its init (`move t4,zero` for `sw zero,228(sp)` at 0xac): 120 either line, 147 both.
- 5aa79e other (pre-existing, tagged 2026-11-18 under the unrelated-reuse ruling): `p` holds loop 2's survivor payload and the framebuffer end. Merged, the inner-loop refs give p adjsave 75 (alone 30), so p takes v1 (0x32c, 0x658) before hp (30), and hp gets a3 (0x298, 0x320-0x354). Any split (end pointer, payload local, q as loop 2's payload) ties p and hp at 30; hp takes v1 (9 lines).
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
- 2026-11-18 cleanup CleanheapReleasePoolb anthropic/claude-opus-5-5 (review, per-role locals):
  - `id` reused as the framebuffer index -> `fb` in pad2's slot: 0 (applied). `i` there: 48.
  - q's framebuffer-cursor role -> `pix` in pad[0]: 0 (applied); q's rebuild role -> `HeapBlock *prev`: 0 alone, 17 together with pix (q's survivor roles are one quantity: kept).
  - p's framebuffer-end role split (pixEnd), loop 2's payload split, or q as loop 2's payload: 9 each (tagged 5aa79e).
  - sz's free-block role split: 21 (same role, region size: kept untagged).
  - bssStart local instead of the field re-reads: 120/120/147/147 (tagged 1c4e4e, d2dcae).
  - 71b822 plain removal on the fb/pix body: 3; with the p split too: 12; variants scan of the removal body (108 variants): no zero.
## Untried ideas
- none for eb8b38 (fixed)
- 71b822: a real block that the target already has code for, anywhere from `id = -1` through the dma call outside the loops (HackloadOverlay2's `if (1) {}` window); `case 1:` before `default:` (0, HackloadOverlay2) is a label-shape block (Q0855) without evidence for a separate case value (overlay id 1 shares the default slot of an 11-entry table either way).
- 1c4e4e/d2dcae: a bssStart that is not homed in the if block (the target stores it to 228(sp) at 0x188 and reloads it at 0x59c for the bzero test).
## Evidence
- target_15050.s (objdump of expected/build/src/global/15050.o)
- pool-size switch: `sltiu at,s1,5; beqz at,23c` at 0x1f4/0x1f8. The jump table at .rodata+0x2c has 5 entries.
- `switch (overlayId)` jump table at .rodata+0: case 1 points at the default arm (0xd4).
- variant scores: .scratch/HackloadOverlay2/lo, pos, nat

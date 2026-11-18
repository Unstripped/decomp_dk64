# renderEntryListSortByDistance (global, src/global/35000.c)

## Sites
global:80630890:other:4e1a0c other: `base = list;` third copy of list (removed 2026-11-17). With it, copy
propagation folds base into param list {925|0}, which is coloured a0 for the whole function (adjsave 2.20); with list read
directly the param pays the save/reload around `jal sqrtf` (adjsave -4.0), splits 5/160 and both pieces stay uncoloured.

## Attempts
2026-11-11 round 13 CleanGlobal35000 opus-5-5:low: uopt -l5 diagnosis (with base list {925|0} a0 adjsave 2.20; without, split 5/160); list/head/u8-inserted spellings fdiff=1 (+12 bytes) -> nohit
2026-11-11 round 13 CleanGlobal35000 opus-5-5:low: permute 92 s base 1629 -> 0 only via `new_var = list` copy -> nohit
2026-11-11 round 16 Rev16F opus-5-5:xhigh: permute 134 s on the list-direct body, best 0 = `RenderEntry *new_var = list` again -> nohit
2026-11-11 round 16 Rev16K opus-5-5:low: permute 660 s on a head-based removal (base 8), best 0 = dead `if (!camZ) {}` + `(new_var = cur)->unk14` (Q0634) -> nohit
2026-11-17 cleanup CleanrenderEntryListSortByDistance opus-5-5: base-role reads through `head` (copy-propagated to list) + `dist` declared after `insKey` -> fdiff 0, FAKE 1 -> 0 (diagnose fixed); also dropped both `(f32)` ternary casts, split node's reuse into `next`, while loops -> fdiff 0

## Untried ideas
none left: the function has no hack site.

## Evidence
- Call-crossing saves at the `jal sqrtf` (0x624) show which variables are live across loop 1: v0 -> 60(sp) (0x608, node M-4),
  a0 -> 64(sp) (0x60c, list's own home), t0 -> 44(sp) (0x614, head M-20), $f18 -> 24(sp) (0x618, dist M-40). So a0 is the
  unchanged param list; the advancing cursor and the sorted head are locals (lever "list reassigned as a role" refuted).
- 0x5b4 `beqz a0` and 0x658 `beqzl a0` test the param itself; 0x660-0x6b4 read the base entry through a0; 0x84c `move t0,a1` is `head = cur`.
- uopt -l5, final body: list LR 5 `{925|0}` adjsave 2.20, live bb 0 (3 refs), 7, 8, 9, 11, 13, 14, default [1..6, 10, 12] with no
  needregsave; assigned reg 3 (a0). List read directly: adjsave -4.0, needregsave in bb 2 and bb 3, needreglod in bb 5,
  "live range 5 split out 160", both "not colored (-ve save)", list reloaded from 64(sp) (`lw t8,64(sp)` before the 0x658 test), full=44.
- Removing base's declaration moves dist from M-40 to M-36 (`swc1/lwc1 $f18` 24(sp) -> 28(sp), full=2); the 12-local frame (64 bytes) needs dist 10th.
- `if (next != NULL) next->unk18 = cur;` in place of the re-read `cur->unk14` shifts the later t-ring (t7/t8/t9 -> t6/t7/t8 at 0x820-0x83c, full=5).

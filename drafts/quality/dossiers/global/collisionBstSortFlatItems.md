# collisionBstSortFlatItems (global, src/global/6AD90.c)
## Sites
None left. Both were removed on 2026-11-15 by deleting the `pivot_ptr` local and spelling every pivot access as `arr[high].f`:
global:8066C0DC:dead-if:f76049 `if (!arr) {}` between the pivot write-back stores. Removed. The Q0908 test showed it was a block split: `if (!temp0/!high/!i/!pivot_ptr) {}`, `if (0) {}` and `while (0) {}` at the same spot all give 0. Without the split, the walker uixa{arr}{i*20} (adjsave 716.7) is live in the call block (TRE BB 21). There the call-argument precolouring forbids a0-a2, so the walker takes a3 and j, key and pivot rotate into a0-a2 (0x60a4 on). With `arr[high].f` the post-loop code gets one more uopt block (TRE BB 22). The walker range then ends in BB 19/20, its forbidden set is [v0 v1], and it takes a0.
global:8066C0DC:other:38df36 byte-offset pivot address `(u8 *)arr + high * sizeof(CollisionBstFlatItem)`. Removed. The repeated `arr[high].f` CSEs to uixa{arr}{high*20} and emits base-first `addu t5,s3,t6` at 0x60b0, the same as the target (Q0781). A named element pointer emits it offset-first.
## Attempts
2026-11-09 CleanD5E10: review. 2026-11-11/12 Rev16G, Rev17L: sweep remove/cond/classify (class 1).
2026-11-14 HackcollisionBstSortFlatItems opus:high: first diagnosis. Tried an early return instead of the wrapping if (0 with the test, 48 without). Tried do-while and swapped-compare scan loops, plus an `arr[high]` write-back that kept pivot_ptr for the load (48-69 without the test). Removed the `s32 size = 20` local via sizeof (fdiff 0).
2026-11-15 HackcollisionBstSortFlatItems2 opus:high: removed both sites by dropping pivot_ptr (fdiff 0) and retyped temp0 u32 -> s32. Before that, measured without the test:
- `while (low < high)` with `low = i + 1` instead of the tail call: 80.
- Final swap inside the break-if: 53. Registers are right but the block order is wrong.
- Temp reads hoisted before the break: 21.
- All 42 read/write interleavings of the post-loop swap: 48.
- Inner scope or compound block around the write-back: 48.
Pivot spellings with pivot_ptr kept: `arr + high`, `high + arr`, `&high[arr]` and a `(u32)` index all scored 1. `pivot_ptr = arr; pivot_ptr += high;` scored 0 but is a steer spelling, so it was not used.
## Untried ideas
None open.
## Evidence
Target 0x60a4-0x61dc: `move a1,s1; lw a3,0(t5); addu a0,s3,t7; lw a2,20(a0)` (walker in a0, j in a1, values in a2/a3). 0x60ac-0x60b0: `mflo t6; addu t5,s3,t6` (pivot address, base first).

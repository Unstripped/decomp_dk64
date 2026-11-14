# collisionBstSortFlatItems (global, src/global/6AD90.c)
## Sites
global:8066C0DC:dead-if:f76049 `if (!arr) {}` between the pivot write-back stores: class 1 kept. uopt_trace -l 5: with it the &arr[i] walker (uixa{arr}{975}, bit 32, adjsave 716.7) has forbidden [1 2] and takes a0; without it the walker is live in the entry block, the precoloured a0-a2 are forbidden ([1-5]), it takes a3 and i/temps rotate through a0-a3 (43 lines from 0x60a4) (Q0546).
global:8066C0DC:other:38df36 (copy-only, pre-existing, now tagged) byte-offset pivot address `(u8 *)arr + high * sizeof(CollisionBstFlatItem)`: keeps arr first in addu t5,s3,t6 at 0x60b0; &arr[high] / arr + high / high + arr swap it (1 line).
## Attempts
2026-11-09 CleanD5E10: review. 2026-11-11/12 Rev16G, Rev17L: sweep remove/cond/classify (class 1).
2026-11-14 HackcollisionBstSortFlatItems opus:high: first diagnosis (above); early return instead of the wrapping if (keeps 0 with the test, 48 without); do-while / swapped-compare scan loops and arr[high] write-back without the test (48-69); `s32 size = 20` local removed via sizeof (fdiff 0).
## Untried ideas
A real block between the pivot write-back stores that ends the walker range before the entry block.
## Evidence
Target 0x60a4-0x61dc: move a1,s1; lw a3,0(t5); addu a0,s3,t7; lw a2,20(a0) (walker in a0, j in a1, values a2/a3).

# actorUpdateNodePositions (global, src/global/70FD0.c)
## Sites
global:80671A6C:dead-if:d7c9c6 dead-if (REMOVED): `if (mtxBase) {}` before the node do-while added an empty uopt block that dropped mtxBase (cand 29, M -88vreg) adjsave 3.67 -> 3.0 below the -1 constant (3.33), so -1 took $s5 and mtxBase $s6. Replaced by the sibling's `switch (node->mtxOffset) { case -1: ... default: ... }` inside a plain `while (node != NULL)` loop (Q1589): mtxBase adjsave 2.75 < 3.33 with no dead test.
## Attempts
2026-11-09..13 (rounds 2-37, Clean70FD0/ReReview/Rev10F/Rev16G/Rev17N/Rev22A/Rev30B/CleanGlobal70FD0): remove/cond/classify/recipe nohit (class 2); permute best=0 only by if (1) {}, if (!node) {}, goto dummy_label, do {} while (0), three if (1) {} blocks: hack swaps, not taken.
2026-11-21 2026-11-21: continue unit 2 Lever70FD0 anthropic/claude-opus-5-5: variants.py try with the mtxOffset branch as a switch, dead test removed: if+do-while switch 0, while+switch 0 (applied: sibling form), switch with dead test kept 0, default-first switch 25 (both loop forms), plain if/else without dead test 4. Applied while+switch -> whole-object fdiff 0, clint uninit exit 0, cfe warnings 0.
## Untried ideas
none left for this function (0 FAKE, 0 goto; the one (u32) cast is the logical shift of the s32 mtxOffset, srl at 0x5854).
## Evidence
```
5800: li    s5,-1          ; -1 constant, uopt reg 19 (coloured before mtxBase)
582c: lw    s6,116(t3)     ; mtxBase = sub->nodeMtx[bufIdx], uopt reg 20
5850: bne   s5,v0,5888     ; node->mtxOffset (lw v0,24(s0)) vs -1
5854: srl   t4,v0,0x6      ; (u32)node->mtxOffset >> 6
5898: addu  a0,t5,s6       ; &mtxBase[...]
uopt -l 5 (switch form): cand 29 {58|0} M -88vreg adjsave 2.75; cand 70 const -1 adjsave 3.333
```

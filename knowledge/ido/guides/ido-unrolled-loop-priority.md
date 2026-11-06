---
title: "IDO unrolled-loop priority and compiler-owned float literals"
description: "How restoring a four-iteration loop and a real 0.15f literal matched func_806C850C without fake constructs."
origin: "ok-fine dk64/notes/ido-unrolled-loop-priority"
---
# Reconstruct unrolled loops before fighting register allocation

`func_806C850C` in `src/global/CC800.c` matched on 2026-11-04: 286 instructions / 1,144 bytes. Both the isolated gate and the main checkout built the original ROM byte-for-byte. The final C removes the park and four FAKE constructs (two volatile field qualifiers and two empty global tests).[^cc800][^log]

## 1. Recheck the diagnosis

The stored draft described an `s2`/`s3` swap between the selector and `&D_807FBB48`. A fresh whole-file diff also showed a rotated temporary-register sequence in the pad-history stores. Scalar spelling changes were treating symptoms; the missing source structure was a four-iteration loop.[^before][^cc800]

The pad record has stride `0x34`, an `f32[4]` at `+0x10`, an `s16[4]` at `+0x20`, and current values at `+0x04` and `+0x28`. Use real arrays and nonvolatile fields:

```c
s32 i;
/* ... */
for (i = 0; i < 4; i++) {
    gPlayerPadState[sel].unk20[i] = gPlayerPadState[sel].unk28;
    gPlayerPadState[sel].unk10[i] = gPlayerPadState[sel].unk4;
}
```

IDO 5.3 `-O2` reports `UNROLLING ... 4 times`. Its level-6 trace shows these priority numerators and live-range lengths; the address candidate stays unchanged:[^trace][^log]

| Candidate | Scalar version | Loop version |
|---|---:|---:|
| Selector priority | 8 / 7 = 1.142857 | 17 / 7 = 2.428571 |
| `&D_807FBB48` priority | 10 / 5 = 2.0 | 10 / 5 = 2.0 |

The unrolled body retains a higher frequency weight (10 rather than 1), moving the selector ahead of the address in coloring order. The selector gets target `$s2` and the address gets `$s3`; the store temporaries also match. This is evidence that apparently straight-line target assembly can still require a source loop because optimizer history influences allocation. It is not a universal prescription to wrap scalar stores in loops: confirm the repeated data shape, exact unrolling, accesses and trace.[^trace][^cc800]

## 2. Distinguish a literal pool entry from a real global

The natural loop reduced the difference to six scheduling lines. The park read `extern f32 D_8075C4B0` into a local and copied it to six player fields. The original bytes at that address are `0x3E19999A`, the single-precision representation of `0.15f`. Six direct `0.15f` assignments give the exact target scheduling; there is no `flt` local and no fake statement.[^before][^cc800]

A compiler literal and an extern load can ultimately load the same bytes yet reach ugen/as1 differently. Treat a generated `D_...` float as a candidate literal, not proof of an authored global. This is safe only after checking its bytes and uses; do not replace a writable global with a constant.[^cc800]

## 3. Gate constant ownership, not only instructions

Leaving the standalone `D_8075C4B0.s` pragma alongside the new literal duplicated `0.15f`, shifting following rodata by four bytes. Remove that pragma. The neighboring `func_806C8D2C` also uses the address as the end marker of the preceding table; changing it to `&D_8075C430[8]` changes its instructions. Keep that existing boundary reference and define `D_8075C4B0 = 0x8075C4B0` in `undefined_syms.us.txt`, following the existing interior-label convention. No extra float storage remains.[^cc800][^syms]

Object-level relocation differences remain permissible only when the full ROM gate passes. Here it did; the source commit is `2c70c29c` and the bookkeeping commit is `d2389aa9`.[^cc800][^log]

Related: uopt live ranges (guide ido-uopt-statics-and-live-ranges: python3 tools/quirks.py get ido-uopt-statics-and-live-ranges), matching quirks, player subsystem (ok-fine dk64 architecture/player-state-angle-camera).

[^before]: `src/global/CC800.c` before this match, commit `a83f952c9e1f5e6c068ca28159e720806f1c977b`.
[^cc800]: Matching `src/global/CC800.c`, commit `2c70c29ce80c63d463275a7298a2ce2f5eb5cdd0`.
[^syms]: `undefined_syms.us.txt` at the matching commit.
[^trace]: Level-6 IDO uopt trace obtained with `tools/uopt_trace.sh`, comparing the old parked function with the reconstructed loop; procedure retained in that tool at the matching commit.
[^log]: `.omp/skills/decomp-unit/run-log.md` and `ROADMAP.md`, commit `d2389aa997893c0e71ecf923a0d5af823aba9be2`; focused-match ROM gate and main-checkout build both passed.

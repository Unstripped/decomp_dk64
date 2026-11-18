# modelAnimEntryBuildKeyMatrix (global, src/global/54150.c)
## Sites
global:8064FB64:noop-arith:6ef768 noop-arith (sweep kind from the `* 0.125` factor; really a recomputation): FIXED 2026-11-17
(CleanmodelAnimEntryBuildKeyMatrix). Case 9 wrote `sz = ((next2 - prev2) * t + prev2) * k` instead of `sz *= k` so that the lerp
stayed a CSE temp in $f2 (uopt bit 127, reg 25) from the dispatch node through case 9 and sz stayed uncoloured: `add.s $f2,$f4,$f0`
at 0x958 and `swc1 $f2,0xd8(sp)` in the delay slot at 0x960 (Q0560 point 3, Q0559 `no_nested_ops`). Natural fix: the factor
`(scaleMode >> 4 & 0xF) * 0.125` computed once before the switch into `f32 factor` and every case `v *= factor`. uopt copy-propagates
`factor` back into each case (per-case conversion code unchanged), and with a leaf right operand `sz *= factor` lets sz's dominating
lerp propagate into case 9 (no `no_nested_ops` refusal), which gives the target's temp.
## Attempts
2026-11-18 2026-11-17: cleanup Polishglobal54150 Polishglobal54150 anthropic/claude-opus-5-5: tagged as pre-existing untagged steer;
`sz *= k`, `sz = sz * k`, `sz = k * sz` -> fdiff 1 (the `sz *=` build computes sz into $f18 at 0x95c, adds `swc1 $f2,0xdc(sp)` at
0xb78 and reloads `lwc1 $f18,0xd8(sp)` at 0xb90 for the guScaleF argument).
2026-11-18 2026-11-17: cleanup CleanmodelAnimEntryBuildKeyMatrix CleanmodelAnimEntryBuildKeyMatrix anthropic/claude-opus-5-5:
`variants.py try` full scores against the FAKE body (0): shared `f32 factor` computed once before the switch, every case
`v *= factor` -> 0, whole-object fdiff 0 (MERGED SPELLING; `(f32)` cast on the assignment and declaration right after sz or right
before pad both 0); per-case `k = (f32)(...); v *= k` -> 13 (k substituted at input, same as `sz *= expr`); sz lerp as three
statements on next2/prev2 -> 13; sz lerp from direct field reads (tx style) -> 52; all three scale lerps from field reads (next2/prev2
dropped) -> 259; lerp alias local `scale` with `sz = scale` and case 9 `sz = scale * k` -> 4; the same alias for all three chains -> 124;
`sz = (next2 - prev2) * t; sz += prev2;` with `sz = sz * k` -> 13; home probe (one unused f32 declared before sz) -> 3, all three sz
accesses move 0xd8(sp) -> 0xd4(sp) (0x960, 0xb60, 0xba0); dropping pad[2] after adding factor -> 63.
## Untried ideas
None for the removed site. The remaining 7 words between sz and work (next, prev, next2, prev2, factor, pad[2]) are register-only;
per-chain locals (Q0560 point 2) could replace pad[2] if a review wants the pad gone (unmeasured).
## Evidence
Target 0x958 `add.s $f2,$f4,$f0`, 0x960 `swc1 $f2,0xd8(sp)` (delay slot), case 9 at 0xb5c `mul.s $f6,$f2,$f4`, 0xb60
`swc1 $f6,0xd8(sp)`; sz is passed to guScaleF from its 0xd8(sp) home (`lw a3,0xd8(sp)` at 0xba0; uopt M -40). Every case recomputes
the factor (`sra`/`andi`/`mtc1`/`cvt.d.w`/`mul.d`/`cvt.s.d`, e.g. 0xb34-0xb58), with a different FP ring register per case, so the
factor is no coloured variable in the target. Case 7 reloads sx from 0xe0(sp) (next2/prev2 are redefined before the switch, so its
lerp is no longer available); case 8 multiplies sy in $f18.

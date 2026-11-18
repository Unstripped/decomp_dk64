# modelAnimEntryBuildKeyMatrix (global, src/global/54150.c)
## Sites
global:8064FB64:noop-arith:6ef768 noop-arith (sweep kind from the `* 0.125` factor; really a recomputation): case 9 writes
`sz = ((next2 - prev2) * t + prev2) * k` instead of `sz *= k`. The recomputed lerp lets uopt keep the value in a temp from the
dispatch node through the case and leave `sz` uncoloured, so the target computes sz into $f2 (`add.s $f2,$f4,$f0` at 0x958)
and stores it to 0xd8(sp) in the delay slot at 0x960 (Q0560 point 3, Q0559 `no_nested_ops`).
## Attempts
2026-11-18 2026-11-17: cleanup Polishglobal54150 Polishglobal54150 anthropic/claude-opus-5-5: tagged as pre-existing untagged steer;
`sz *= k`, `sz = sz * k`, `sz = k * sz` -> fdiff 1 (the `sz *=` build computes sz into $f18 at 0x95c, adds `swc1 $f2,0xdc(sp)` at
0xb78 and reloads `lwc1 $f18,0xd8(sp)` at 0xb90 for the guScaleF argument).
## Untried ideas
Give the scale chain the per-chain pair treatment of Q0560 point 2 in another shape (e.g. sz computed only after the switch from a
scale factor local that defaults to 1.0f for cases 0-8) and check whether `sz` stays uncoloured (Q0560, Q0556 varreflimit cuts).
## Evidence
Target 0x958 `add.s $f2,$f4,$f0`, 0x960 `swc1 $f2,0xd8(sp)` (delay slot), case 9 at 0xb60 `swc1 $f6,0xd8(sp)`; sz is passed to
guScaleF from its 0xd8(sp) home (`lw a3`).

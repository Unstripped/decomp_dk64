# actorConfigLookup (global, src/global/8F050.c)
## Sites
- global:8068A3A0:do-while0:5c6932: REMOVED earlier as an as1 line join (`i = 0; do {`, tagged `// LAYOUT:`); the 2026-11-16 rewrite drops the join entirely.
- global:8068A3A0:dead-if:fdc560 `if (actorType && actorType && actorType) {}`: FIXED 2026-11-16 (HackactorConfigLookup3).
  - It numbered actorType (candidate bit 0) before next's ustr so actorType kept a0. The real source has no `next`/`i` locals: the loop index is `*outIndex` itself.
## Attempts
- rounds 15/16 (opus:low): diagnose/permute both (the permuter only re-adds dead uses / re-joins the line).
- 2026-11-14 U HackactorConfigLookup: as1probe scan, init orders 10, for/break 14, uopt -l 6 bit comparison, 10 body shapes 8-20, variants scan 8.
- 2026-11-15 U HackactorConfigLookup2: compare-first bodies 5-19, boolean temps, K&R, register/const, param widths 8-14 (see Q0956).
- 2026-11-16 U HackactorConfigLookup3 anthropic/claude-opus-5-5:high:
  - compare-first with `next` set in both arms and a separate `if (!found) { *outIndex = next; i = next; }`: every register right, full=5 (only the extra `bnez v1`). `if (next != i)` 5, `if (found) break` 7, unused label in the else arm 11 (no block split), `if (next)` 14, natural `i++` 17.
  - `*outIndex` as the loop index, `(*outIndex)++` in the else arm, unsigned bound: full=0 with `(u32)*outIndex < 7`, `*outIndex < 7U`, and `*outIndex < sizeof(t) / sizeof(t[0])` (kept, Q0810), with or without a `cfg` local. `u32 *outIndex` retype does not match (no cvt: sltiu on v0, no `move a2,v0`) and warns 709 at both callers.
## Untried ideas
- none (no hack sites left).
## Evidence
- leaf; table base a3 (lui at 0x50, addiu at 0x5c); table is 7 x 20 bytes at 0x80750100 (8 zero bytes follow to 0x80750194).
- move v0,zero at 0x60 (the s32 `*outIndex` value), stride 20 via multu at 0x68.
- `addiu a2,v0,1` at 0x6c = `(*outIndex)++`, stored in the bnel delay slot (0x80) / 0x90.
- found arm `move a2,v0` at 0x8c and else `move v0,a2` at 0x94: the unsigned-converted `*outIndex` compare value (sltiu a2,7 at 0x98) vs the s32 index value.

# commandApplyToLight (global, src/global/126260.c)
## Sites
- global:80721814:other:bd52bc: REMOVED (2026-11-14). Byte-offset views replaced by `fb->lightSets[gLightSetIndex].l / .a / .l[lightIndex]`.
- global:80721814:dead-if:4cea0a: REMOVED (2026-11-15). `FrameMatrices *fb = gGfxCurrentFrameBuffer;` (declared last) makes the frame-buffer base a coloured variable in v1 (lw v1 at 0x2c0, addu v0,v1,t8 at 0x2dc). This only works once 062c74 is gone: with that guard kept, the fb local swaps ambient/slot t0/t1 (0x2e8/0x304).
- global:80721814:dead-if:062c74: REMOVED (2026-11-15). The ambient halving is spelled `(f64)col / 2.0`. uopt strength-reduces it to a separate `5.0E-1` constant web, so the ambient piece colours $f14 (loaded at 0x7ec) instead of joining the `0.5` web of `0.5 * factor * factor` in $f16 (loaded at 0x578).
- global:80721814:dead-if:0c2321 / 0c2321#2: REMOVED (2026-11-15), replaced by copy-only global:80721814:other:f7de45 (kept, `// FAKE`; director ruling: reusing a local for an unrelated value is a hidden steer unless the target stores it to that local's home slot; this function has no swc1/sdc1). One f32 local `factor` holds the falloff base (type 5) and then `127.0f / dist` for the direction bytes (slot path). The extra def and uses give it savings 6 over 5 blocks (adjsave 3.0), tying clamped (3.0). The lower candidate index colours it first ($f2), then clamped ($f12) and the 1.0 web ($f16).
- global:80721814:other:d00a99 (was d9b15d before the cast cleanup): kept, `// FAKE` (lead Q0816 ruling). Ambient halving `c = col + (col / 2.0 - col) * intensity`; `* 0.5` / `0.5 *` = 10 lines (the 0.5 joins the falloff web hoisted to 0x578).
- global:80721814:other:f7de45: kept, `// FAKE`. `factor = 127.0f / dist` reuse (see 0c2321 above); no natural replacement found (2026-11-16 audit below).
## Attempts
- rounds 13-20 (opus:low): diagnose, permute, reconstruct h1-h10; see history.
- 2026-11-14 U HackcommandApplyToLight opus:high: typed head 0; &lights[lightIndex] 156; Lights7 *set 177; 4cea0a alone 100, fb local 29; 062c74 alone 39; 0c2321 pair 17; clamp if-forms best 5 (guards kept).
- 2026-11-15 U HackcommandApplyToLight2 anthropic/claude-opus-5-5:high (variants.py try full=):
  - fb local + all guards removed: 27; fb + 062c74 removed: 10; fb with all other guards kept: 29
  - ambient `/ 2.0`: 0 with fb and the base pair kept (applied)
  - base pair, before the factor reuse: product spellings 17-735; f64 base / arm casts 628-634 (colours right, but the f32 rounding moves to the join); named falloff temp 638/17; reusing dist/intensity/clamped/dist_d 17-644; merged f64 locals 17-22; early numerator def 270; clamp flips 16-18; integer `1` literals best 13; single compound guard `if (base == base || base == base) {}` 0 (superseded)
  - permuter 1 (typed head, no fb, all guards removed, 900 s): base 1836, best 540, no natural fix
  - permuter 2 (fb + `/ 2.0`, base pair removed, 900 s): base 95, hints reusing base in the slot path (best 10) -> `factor = 127.0f / dist` rewrite: 0 (applied)
  - dropped the redundant `(s32)` on `cmd->radius / 2` and `(f64)` on `intensity *`: 0
  - plain forms re-checked on the final head: no fb local 100, `* 0.5` 10
- 2026-11-16 U HackcommandApplyToLight3 anthropic/claude-opus-5-5:high (variants.py try full=):
  - cast-free body (68 redundant casts dropped; only `(f32)cmd->radius` stays, the target rounds through f32 at 0x418): 0 (applied); `intensity *= 1.0 - dy_d / 20.0`: 0 (applied)
  - f7de45 without the reuse (separate `scale`, or inline `127.0f / dist`): 17; block-scoped `factor`/`scale` (distinct homes -60/-64vreg): 17; dist refined in place (falloff lands in $f18): 17; MIN-style inline clamp (udiv isop, still 3.0): 17; inline dy clamp 291; f64 falloff with `(f32)(ternary)` 628 / `(f32)` arms 634; falloff if-clamp forms 630-633
  - d9b15d on the cast-free form: `* 0.5` 10, `0.5 *` 10, `/ 2` 465; on the cast form `* 0.5f` 0 (float-suffix steer, not applied)
  - permuter 3 (perm_plain: no reuse, separate `scale`, 900 s): base 95, best 0, but both zeros are the same one-local reuse (falloff and `127.0f / dist` in `scale` or `factor`); 35 = dead `if (!lights ...)` guard, 85 = factor reused for `(f32)cmd->z`
## Untried ideas
- f7de45: none left on the uopt side: factor needs 3 more f32 accesses (or clamped a 10+ block range) with no new code; a different control-flow reconstruction of the whole type-5 path is the only open direction.
## Evidence
- Prologue: `lw v1,gGfxCurrentFrameBuffer` (0x2c0); v0 = v1 + set*0x78 (0x2dc); a3 = v0+0x278 (lights), t0 = v0+0x270 (ambient), t1 = v0 + idx*16 + 0x278 (slot).
- 1.0 in $f16/$f17 (0x3a8/0x3ac). Falloff base: `cvt.s.d $f2` in both arms (0x3e4-0x3f0), `cvt.d.s $f0,$f2` at the join (0x3f4). Clamped: `div.d $f12` (0x428).
- Ambient 0.5 loaded at 0x7ec into $f14/$f15 (`mul.d ...,$f14` at 0x818/0x8dc/0x9a0). Direction scale `div.s $f0,$f8,$f18` (0xc80), used by three `mul.s` (0xca4/0xcd0/0xcfc).
- uopt priorities (`-l 5`, compute_save = savings / (n > 2 ? ((n-2)>>2)+2 : n)): without the reuse factor (bit 69, f32) has 2 arm defs + 1 use = savings 3 over 3 blocks -> 1.5; clamped (bit 75, f64, accesses weigh 2) savings 6 over 2 blocks -> 3.0. With the reuse factor has 3 defs + 3 uses over 5 blocks -> 3.0 and wins the tie on the lower bit.

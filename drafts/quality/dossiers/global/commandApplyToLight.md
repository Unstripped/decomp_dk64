# commandApplyToLight (global, src/global/126260.c)
## Sites
- global:80721814:other:bd52bc: REMOVED. The byte-offset lights/ambient/slot views are replaced by `gGfxCurrentFrameBuffer->lightSets[gLightSetIndex].l / .a / .l[lightIndex]`.
- global:80721814:dead-if:4cea0a (kept): the dead read of gGfxCurrentFrameBuffer keeps the frame-buffer base a uopt candidate in v1.
- global:80721814:dead-if:062c74 (kept): the dead 0.5 use orders the ambient/slot address temps (t0/t1).
- global:80721814:dead-if:0c2321 / #2 (kept): the two dead base uses colour 1.0 into $f16/$f17 and base's cvt into $f2.
## Attempts
- rounds 13-20 (opus:low): diagnose, permute, reconstruct h1-h10; see history.
- 2026-11-14 U HackcommandApplyToLight opus:high (variants.py try full=):
  - typed head with all guards: 0 (applied)
  - &lights[lightIndex]: 156
  - Lights7 *set snapshot: 177
  - 4cea0a: guard alone removed 100; fb local 29; setup moved after the return 128
  - 062c74: alone removed 39; 0.5 operand orders 40-736
  - 0c2321: both removed 17; base declaration position 17-29; clamp if-forms best 5 (guards kept), 23 with no guards
## Untried ideas
- A permuter run on the typed head with the guards removed.
## Evidence
- Prologue: `lw v1,gGfxCurrentFrameBuffer` (0x2c0)
  - v0 = v1 + set*0x78 (0x2dc)
  - a3 = v0+0x278 (lights), t0 = v0+0x270 (ambient), t1 = v0 + idx*16 + 0x278 (slot)
- Constants: 1.0 in $f16/$f17 (0x3a8/0x3ac); base's `cvt.s.d` into $f2 (0x3e4).

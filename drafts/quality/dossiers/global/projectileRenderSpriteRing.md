# projectileRenderSpriteRing (global, src/global/9BF30.c)
## Sites
- global:80697230:other:e23d19 (final key 153bd8): gSPMatrixShared through the function-scope _g. FIXED 2026-11-15: gbi gSPMatrix, macro deleted; the register-only function-scope `Gfx *_g` is declared after q1 and `f64 pad[2]` became `f64 pad`.
- global:80697230:other:2c23a5: hand-written SETTIMG/render-tile SETTILE words through the function-scope `_g` (plus a LAYOUT same-line join). FIXED 2026-11-17: one `gDPLoadTextureBlock(glist++, gSpriteRingTextures[texIndex], G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)`. collisionRadius moved into the `if (actor->unk15F)` block; offsetX/Y/Z, spriteScale, progress, growth and clampedProgress moved into the loop body. The function-scope `_g`, `f64 pad` and the LAYOUT tag are gone.
## Attempts
- round 28 (opus:low): gbi gSPMatrix (spill shift), permute.
- 2026-11-14 U:
  - gDPLoadTextureBlock + gbi: frame 0x1a0
  - dropping q3/q2/pads: frame fixed, but the f32 homes are 8 higher
  - 321-layout brute force: no match
  - Mtx * local for both uses: 3808 bytes
  - Mtx-array indexing: adopted (view fix, fdiff 0)
- 2026-11-15 U HackprojectileRenderSpriteRing2 (opus:high):
  - cfe home census from the t.B ucode (`as1probe.py keep` + `ucode --cfe`): fixed the site
  - moving f/idx/i/stepAngle/_g to other declaration positions without a pad change: full 2-19
  - switch -> if-chain for the collision switch (A), the loop switch (B), or both: full 12/29/33. The if-chain changes the branch shape, and the switch temp is shared, so one if-chain does not free it.
  - 648 layouts of {q0,q1,f,idx,_g,pad} that keep collisionRadius at -180: every tested one is full 0, and the adopted layout is the smallest edit
  - SETTIMG/SETTILE raw words written straight through glist (no `_g`): full 34, because the target copies the packet pointer (move v0,s0)
- 2026-11-17 U HackprojectileRenderSpriteRing3 (opus):
  - all function-scope decls, gbi SETTIMG/SETTILE macros: full 19 (cfe len 280, frame 0x1a0); with the now-unused function `_g` dropped: full 12 (frame 0x198 but the in-memory scalars 8 higher: collisionRadius -172)
  - Q0944 lever, a selector local for both switches (`ringType = sub->ringType;` before each switch, or `switch (ringType = sub->ringType)`), u32 and s32: identical scores (2 alone, 14/21 with macros). cfe still emits `vreg u32 ... off -276` and copies the local into it, so the local only adds a home; one assignment at the top: 197-212
  - block-scoped declarations (adopted): function scope keeps sub, the two matrices, i, stepAngle, texIndex; collisionRadius in the `if (actor->unk15F)` block; offsets, spriteScale, progress/growth/clampedProgress at the loop body top. cfe gives homes in source order, so the 9 pre-loop gbi block homes land at -144..-176 above collisionRadius (-180). Loop-body order p,c,g: full 21 (len 268, frame 0x190); p,g,c or c,g,p: full 0 (two f64 alignment holes give len 272); g,p,c / g,c,p: full 19
  - splitting the LOADTILE..SetTileSize statements onto separate lines: full 13; one `gDPLoadTextureBlock` statement: full 0 (adopted, no LAYOUT join needed)
  - review: `(f32)` cast on the matrixMakeRotationY argument removed (prototype takes f32): full 0
## Untried ideas
- none for this function.
## Evidence
- frame 0x198. cfe `def Mmt len` is 272 in the target.
- Homes in the final form (offset from the frame top):
  - sub -4
  - mtx2 -68 (0x154), mtx1 -132 (0x114)
  - i -136 (0x110), stepAngle -134 (shares i's word)
  - texIndex -140 (register-only)
  - the 9 pre-loop gbi block `_g` homes -144..-176
  - collisionRadius -180 (0xe4), offsetX -184, offsetY -188, offsetZ -192, spriteScale -196 (the in-memory scalars)
  - progress -208, growth -212, clampedProgress -224 (register-only; -200 and -216 are f64 alignment holes)
  - the 11 loop gbi block `_g` homes -228..-268
  - one cfe switch temp -272, shared by both switches; cfe allocates it after every block home
- uopt spill temps go below cfe len. The idx*4 spill is at 0x7c (sw at 0x274, lw at 0x45c).

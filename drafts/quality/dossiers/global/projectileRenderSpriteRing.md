# projectileRenderSpriteRing (global, src/global/9BF30.c)
## Sites
- global:80697230:other:e23d19 (final key 153bd8): gSPMatrixShared through the function-scope _g. FIXED 2026-11-15: gbi gSPMatrix, macro deleted; the register-only function-scope `Gfx *_g` is declared after q1 and `f64 pad[2]` became `f64 pad`.
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
## Untried ideas
- none for this function. The raw SETTIMG/SETTILE words cannot become gbi macros at this frame: they would need 19-20 block homes below vscale, where the frame has room for only 18 plus the switch temp.
## Evidence
- frame 0x198. cfe `def Mmt len` is 272 in the target and 276 with a plain gbi gSPMatrix.
- Homes (offset from the frame top):
  - sub -4
  - mtx2 -68 (0x154), mtx1 -132 (0x114)
  - i -136 (0x110), stepAngle -134 (shares i's word)
  - q0 -144, q1 -152 (register-only)
  - pad, then f -172 and idx -176 (register-only)
  - collisionRadius -180 (0xe4), vx -184, vz -188, vy -192, vscale -196 (the in-memory scalars)
  - the gbi block `_g` homes from -200 down
  - one cfe switch temp, shared by all three switches
- uopt spill temps go below cfe len. The idx*4 spill is at 0x7c (sw at 0x274, lw at 0x45c).
- Register-only homes can move freely within -137..-176 as long as collisionRadius stays at -180.

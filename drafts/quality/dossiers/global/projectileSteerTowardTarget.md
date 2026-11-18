# projectileSteerTowardTarget (global, src/global/936B0.c)
## Sites
- global:80690C60:other:8fcc57 (was punned-cast 8a4e49): FIXED 2026-11-17 (HackvehicleUpdateMotion9). The `(u32)straight`
  arg-5 cast is gone: the file-local callee projectileFindHomingTarget got its real ANSI prototype
  `s32 projectileFindHomingTarget(u16, Actor **outTarget, Actor *, u8 useAim, u8 levelOnly, u8 includeModels, f32 *, f32 *, f32 *)`
  (definition retyped from K&R; stand-in PROTO_SKIP + declaration until the header is regenerated). With the u8 prototype in
  scope the caller passes `straight` unwidened, so plain `straight, straight == 0` matches. Caller bundle: 103AB0.c
  (playerViewDrawCrosshair, playerViewDrawScopeCrosshair: target/targetX..Z locals retyped Actor * / f32, fdiff 0).

## Attempts
- rounds 2/10/16 (opus:low): diagnose, permute, reconstruct; see history.
- 2026-11-14 U HackprojectileSteerTowardTarget opus:high (variants.py try full=):
  - plain straight: 55; `!straight`: 43; `straight != 0`: 8; `?:`: 52; casts: 55
  - u8 snapshot local: 43-78; precomputed second arg: 78
  - ANSI s32 prototype for the callee: 300+ diff lines plus cfe W642
- 2026-11-15 U HackprojectileSteerTowardTarget2 opus:high (uopt -l6 + variants.py try full=):
  - plain: ucvt cand 39 is PRE'd across the jal: v0 at 0x2358, `sw v0,0x38(sp)` in the jal delay slot, then `lw t7,0x38(sp)` at 0x2434
  - declared s8/s16/s32/u32: 4 (only the load opcode differs: lb/lh/lw vs lbu); u16: 55
  - s32 parameter with `(u8)` casts at both uses: 55
  - `void *target` local: 55
  - ANSI definition: cfe redeclaration error against the K&R header
  - `!straight` post-call test: 54
  - `straight != 0` as arg 5: adds `sltu t2,zero,v0` and is not equivalent
  - 2026-11-16 U HackprojectileSteerTowardTarget3 opus:high (variants.py try/scan, fdiff, uopt trace):
  - (u32) value cast on one use before the call, plus `!straight` after the call: full=0. Whole-file fdiff OK in `zeroL/` (arg 5 `(u32)straight`) and `zeroD/` (`(u32)straight == 0` at both tests). In the copy the pun is kept: the cast exists only for codegen (CEAE0.c:401 tags the same kind of cast FAKE), so the net tag count would not drop. The lead decides.
  - arg 5 cast with post `straight == 0`: 7; arg 6 cast with post `straight == 0`: 7; post-call cast only: 54; `!(u32)straight` at both: 40
  - `== 0U` / `<= 0U`: 54-79; `(s32)`/`(u16)` arg casts: 54; u32 copy local: 40
  - early `if (straight != 0) return;`: 55
  - ANSI definition through a PROTO_SKIP stand-in: same v0 PRE, and .text grows by 32 bytes
  - block-scope u8 prototype for projectileFindHomingTarget: cfe redeclaration error
  - variants.py scan of the plain body: s8/s16/s32/u32 widths 4; `NULL != target` swaps 41/47; no zero
- 2026-11-17 U HackvehicleUpdateMotion9 anthropic/claude-opus-5-5 (variants.py try, uopt -l5, fdiff):
  - K&R callee, caller spellings: plain `straight, straight == 0` 54; `straight, !straight` 40 = instruction-identical but cfe stores
    `!straight` into a temp (M -72vreg) below steps, frame 0x88, every sp offset +8; plus `f64 pad58` dropped 14 (the temp sits below
    steps so camState..steps stay +8); pad58 as s32 14; `register u8 straight` 40; `straight ? TRUE : FALSE` args 55.
  - block-scope prototypes: `s32 levelOnly` 40; `u32 levelOnly` + `straight == 0` 0 (codegen-chosen, not taken); `u8` = cfe
    redeclaration error against the K&R definition.
  - ANSI callee (u8 narrow params): `straight, straight == 0` 0 (applied); `straight, !straight` 45; `(u32)straight` 0.
  - dropped redundant casts (fdiff 0): `(f64)` on `speedXZ < 0.1` and on `eyeHeight * 0.5`, `(void **)` on `&target`.

## Untried ideas
- none: the site is fixed. 103AB0 playerViewDrawScopeCrosshair: `(u16)targetKind` becomes redundant under the u16 prototype (fdiff 0 without it); the 103AB0 owner may drop it.

## Evidence
- uopt trace: plain splits ucvt cand 39 out to 148 (not coloured, the 0x38(sp) spill) and gives cand 39 colour 1. With the (u32) arg cast and `!straight`, cand 39 is never offered for colouring (trace_zeroL.txt vs trace_plain.txt).
- 0x2358 `lbu t2,0x8f(sp)` (0x22f8/0x231c are delay-slot copies); `sltiu t3,t2,1` at 0x2368; arg 4 is stored from t2 in the jal delay slot (0x2390).
- 0x2434 `lbu t8,0x8f(sp)`: reloaded for `if (straight == 0)`.
- a3 home `sw a3,0x8c(sp)` at 0x22c4; every read is at the a3 home 0x8f(sp), so no frame-census local can be the read source.
- 0x2598-0x25a0 (callee prologue): `sw a3,244(sp); andi t6,a3,0xff; move a3,t6` = ANSI u8 formal pattern (Q0411); 0x27a8 `lbu t5,251(sp)` reads levelOnly.
- 0x2358 `lbu t2,143(sp)`, 0x2368 `sltiu t3,t2,1`, 0x2390 `sw t2,16(sp)` (jal delay slot): arg 5 is the raw byte, arg 6 its == 0.

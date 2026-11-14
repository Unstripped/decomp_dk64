# effectSpawnJointBeam (global, src/global/89250.c)
## Sites
- global:8068780C:proto-steer:cdd49c and eccdf5: REMOVED (this unit).
  - With the shared s16 prototype, only the inline 0x8A/0xA1 ternary gets narrowed: sll/sra/move a3, +16 bytes.
  - A named `s16 sfxId` local, declared directly before `u8 bones[2]` (they share one stack word), matches.
## Attempts
- rounds 3/16/34 (opus:low): consolidate x3 (+16 bytes); diagnose (s32 params pass the ternary straight to a3).
- 2026-11-14 U HackeffectSpawnJointBeam:
  - header prototype diff: only the sfxId narrowing (8 r + 3 extra)
  - sfxId local as s16/s32/u16/u8, in if/else, ternary and default-then-if forms: s16 removes the narrowing but the frame grows 0x78 -> 0x80
  - the other widths keep the narrowing
  - s16 at each of 14 declaration positions plus block scope: only "before bones[2]" matches (both forms)
## Evidence
- frame 0x78; bones at 0x44/0x45
- callee sfxPlayAtPositionPooled homes a3 at 148(sp) (0x62d0)

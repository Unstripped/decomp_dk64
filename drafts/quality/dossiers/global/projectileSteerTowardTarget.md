# projectileSteerTowardTarget (global, src/global/936B0.c)
## Sites
- global:80690C60:punned-cast:8a4e49 (kept): `*(u8 *)&straight` makes the K&R u8 parameter address-taken, so it stays memory-resident and is loaded from its home at each use.
## Attempts
- rounds 2/10/16 (opus:low): diagnose, permute, reconstruct; see history.
- 2026-11-14 U HackprojectileSteerTowardTarget opus:high (variants.py try full=):
  - plain straight: 55; `!straight`: 43; `straight != 0`: 8; `?:`: 52; casts: 55
  - u8 snapshot local: 43-78; precomputed second arg: 78
  - ANSI s32 prototype for the callee: 300+ diff lines plus cfe W642
## Untried ideas
- none natural; only address-taken or volatile forms keep the parameter in memory.
## Evidence
- 0x2358 `lbu t2,0x8f(sp)` (0x22f8/0x231c are delay-slot copies); `sltiu t3,t2,1` at 0x2368; arg 4 stored from t2 in the jal delay slot (0x2390).
- 0x2434 `lbu t8,0x8f(sp)`: reloaded for `if (straight == 0)`.

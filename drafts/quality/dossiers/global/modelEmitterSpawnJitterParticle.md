# modelEmitterSpawnJitterParticle (global, src/global/68EA0.c)
## Sites
- global:80664834:other:c0fba7: the byte-offset entry address. Target: entryIdx in t1, base in t9 (0x788-0x7a8). Both &a[i] and a + i give t9/t2 (11 r).
## Attempts
- round 20 (opus): diagnose/permute (best 60-70).
- 2026-11-14 U, scored with variants.py try (full=):
  - a + i: 11
  - entry placed earlier: 31-54
  - no entry with [i]: 42
  - no entry with (a + i)->: 2 (the FAKE spelling used by modelEmitterSpawnScaledParticle)

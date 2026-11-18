# modelEmitterSpawnJitterParticle (global, src/global/68EA0.c)
## Sites
- global:80664834:other:c0fba7 (removed in the copy): the byte-offset entry address `(ActorProximityEntry *)((u8 *)gModelEmitters + entryIdx * sizeof(...))`. It kept the base load first (t9) and the index in t1 and t2 for the *12 at 0x788-0x7a8. Both &a[i] and a + i put the index first (t9/t2, 11 rows).
## Attempts
- round 20 (opus): diagnose/permute (best 60-70).
- 2026-11-14 U, scored with variants.py try (full=):
  - a + i: 11
  - entry placed earlier: 31-54
  - no entry with [i]: 42
  - no entry with (a + i)->: 2 (the FAKE spelling used by modelEmitterSpawnScaledParticle)
- 2026-11-17 "2026-11-17: cleanup CleanmodelEmitterSpawnJitterParticle" CleanmodelEmitterSpawnJitterParticle anthropic/claude-opus-5-5, scored with variants.py try (full=):
  - FIXED: no entry pointer and no randX/randZ locals. `gModelEmitters[entryIdx].x + randomNonNegative() % 10000 % 100 / 20.0 - 2.5`, `.y + 4.0`, `.z + ...` (the sibling form): 0. objdump -drz identical. fdiff exit 3; `--reloc-ok` gives RELOC-EQUIV OK. Only the .rel.text record order differs (proof: reloc_proof.txt).
  - direct reads with the inline calls, other orders: jitter-first 41, `x + (jitter - 2.5)` 22, `jitter - 2.5 + x` 41. `4.0 + y` and `y + 4.0` score the same.
  - direct reads with randX/randZ locals, all 4 x/z orders x 2 y orders: 42 (lh x is emitted before lw randX, so t3-t5 shift by one). Adding `s32 pad` first: 41.
  - entry spellings at the FAKE position, with locals: &a[i], &*(a + i), i + a, &i[a], &a[(s32)i], &a[(u32)i], a + (u32)i: 11 each. `entry = g; entry += i` and `entry = g; entry = &entry[i]`: 23. `&a[0] + i`: 0 (a steer, Q0813).
  - entry spellings with the inline calls (init, top, if-start or before the call): 36-61 (entry is live across the calls).
  - an `emitters = gModelEmitters` local: 66. `s16 *pos = &g[i].x`: 59. Field locals x/y/z (s16/s32/f32/f64): 31-86.
  - variants.py scan of the fixed body: only the f32 literal suffix zeros (`0.2f` -> `0.2` etc.). No change.
## Untried ideas
- none for c0fba7 (removed). If the lead rejects reloc-order-only RELOC-EQUIV: every separate-statement entry spelling that keeps the expected reloc order is offset-first (Q0813) or a pun. The FAKE stays as at the base.
## Evidence
- Target 0x788-0x7a8: `lh t1,42(sp); lui/lw t9 gModelEmitters; sll t2,t1,2; subu t2,t2,t1; sll t2,t2,2; addu v1,t9,t2`. Then lh 2/4/6(v1) into t6/t7/t9 (0x7ac-0x7bc).
- x arg: `add.d f18,f8,f16` at 0x7fc (jitter f8, field f16), then `sub.d f4,f18,f2` (2.5). z arg: `add.d f4,f8,f18` at 0x874. y arg: `add.d f18,f8,f16` (field + 4.0) at 0x838.
- Both random calls (jal at 0x744 and 0x74c) come before the address computation. The first result spills to 32(sp) (0x750); frame 40.
- cfe ucode (as1probe ucode --cfe):
  - FAKE: `lod gModelEmitters; lod entryIdx; cvt u32 s32; ldc u32 12; mpy u32; add` (base first).
  - &gModelEmitters[entryIdx]: `lod entryIdx; ldc s32 12; mpy s32; lod gModelEmitters; add` (offset first).
  - p[i].f: `lod gModelEmitters; lod entryIdx; ixa s32 12`. uopt makes this `lod base; lod idx; ldc 12; mpy; ixa 1` (base first).
- Inline calls: cfe hoists both calls into hidden temps (-8, -4). It emits the call-bearing right operand of `+` first (Q1222), so `field + jitter` source gives (jitter, field) add.d operands.
- uopt places the common address computation before the first argument tree that uses it (after the a0/a1 rpar). In ugen, `lw gModelEmitters` therefore follows `la a0,D_807213D0`. That is the only object difference (reloc record order). The final schedule is identical.

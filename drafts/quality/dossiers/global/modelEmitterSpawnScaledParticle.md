# modelEmitterSpawnScaledParticle (global, src/global/68EA0.c)
## Sites
All three fixed 2026-11-17 (HackmodelEmitterSpawnScaledParticle4); the function has no hack site left.
- Base keys global:80664A38:other:5ef858 / 9eff7a / 0341ea (base lines 173-175), other: `(gModelEmitters + entryIdx)->x/y/z`.
- They steered the float-add operand order: add.d at 0xa10 / 0xa84 / 0xaec must be product + field.
- Fix: each coordinate written position + jitter, `gModelEmitters[entryIdx].x + (randomNonNegative() % 10000 % 300 / 20.0 - 7.5) * scaleFactor`.
  The three random calls are nested arguments (cfe hidden temps at 40/44/48(sp)), and only scaleFactor is declared.
## Attempts
- round 20 (opus / opus:low):
  - [entryIdx]. spellings, fdiff 1 / 57 lines off.
  - f32 x/y/z locals.
  - entry pointer before/after the randoms.
  - permute: best 1303 / 1404.
- 2026-11-14 HackmodelEmitterSpawnScaledParticle (opus), variants.py try (lines off):

  | variant | lines off |
  |---|---|
  | entry local after the randoms (also as &-form, register, with a one-case switch, with an early return) | 4 (idx*12 spill 36 -> 32, t4/t5 swap) |
  | entry local with XYZ declaration order | 6 |
  | entry local declared first | 10 |
  | randZ called inline with an entry local | 24-27 |
  | `[ ]` with s32 idx snapshot | 59 |
  | `[ ]` with field first | 57 |
  | `[ ]` with scaleFactor first | 57 |
  | `[ ]` with `-7.5 +` term order | 58 |
  | `[ ]` with a one-case switch or a `!x` test | 57 |
  | nested pos struct | no change |
  | f32/f64 locals, function or block scope | 158-166 |

  variants.py scan of the entry body: best 4.
- 2026-11-15 HackmodelEmitterSpawnScaledParticle2 (anthropic/claude-opus-5-5:high), variants.py try (lines off):

  | variant | lines off |
  |---|---|
  | `ActorProximityEntry *entry` declared LAST, set after the randoms (`gModelEmitters + entryIdx` and `&gModelEmitters[entryIdx]`) | 4 (same spill 36 -> 32, t4/t5 swap) |
  | entry declared at the top of the if-block | 4 |
  | entry declared in a `{ }` block after the randoms | 4 |
  | entry declared last, randZ declared after it | 8 |
  | entry declared last, XYZ declaration order | 6 |
  | entry declared last, randZ called inline | 27 |
  | entry declared last, set before the randZ call | 24 |
  | entry in randZ's declared position, randZ inline | 24 (entry stored to 48(sp) across the call) |
  | all three randoms inline, entry local (after scaleFactor / first / set before the calls) | 57 / 59 / 57 |
  | all three randoms inline, only scaleFactor declared, (p + i)-> | **0** (frame 40/44/48 are cfe hidden temps) |
  | same with `[entryIdx].` | 57 |
  | `(&gModelEmitters[entryIdx])->` | 57 |
  | `(entryIdx + gModelEmitters)->` | 3 |

  variants.py scan of the declared-last entry body: best 4 (`0.4f` -> `0.4`).
- 2026-11-16 HackmodelEmitterSpawnScaledParticle (anthropic/claude-opus-5-5:high), variants.py try, applied to all three lines (lines off):

  | variant | lines off |
  |---|---|
  | `(*(gModelEmitters + entryIdx)).` | 57 (same as `[entryIdx].`) |
  | `entryIdx[gModelEmitters].` | 57 |
  | `(f64)gModelEmitters[entryIdx].` | 57 |
  | `[entryIdx].` fields, `(gModelEmitters + entryIdx)->scale` | 58 |
  | `(gModelEmitters + entryIdx)->` with the field written first | 60 |

  So the steer is the `->` operator, not the pointer add. A `.` access always puts the field first in the add. A `->` access keeps the written order, and the target's order is product + field (add.d at 0xa10/0xa84/0xaec). `(&p[i])->` folds back to `.` (57). The only natural `->` base is an entry local, and the frame has no word for one.
- 2026-11-16 HackmodelEmitterSpawnScaledParticle3 (anthropic/claude-opus-5-5:high), reconstruct around the 5-word frame without an entry pointer, variants.py try (lines off):

  | variant | lines off |
  |---|---|
  | `s32 offset = entryIdx * sizeof(ActorProximityEntry)` declared last, `((ActorProximityEntry *)((u8 *)gModelEmitters + offset))->` everywhere | 2 (offset owns 36, spill sw t8,32(sp)) |
  | same offset local plus an entry pointer built from it | 10 (frame 0x38 -> 0x40: offset M -20, entry M -24, spill 0x24) |
  | `s32 idx = entryIdx` snapshot plus `entry = &gModelEmitters[idx]` | 13 |
  | inline byte-offset cast `((T *)((u8 *)gModelEmitters + entryIdx * sizeof(T)))->` on all four accesses | **0** (punned cast, not adopted) |
  | `(&gModelEmitters[0] + entryIdx)->` | **0** (same `(p + i)->` steer) |
  | all four accesses `(gModelEmitters + entryIdx)->`, scale included | 1 |
  | `(gModelEmitters + entryIdx)[0].` / `(&gModelEmitters[entryIdx])[0].` | 57 |

  A declared offset/index local is copy-propagated (uopt trace: `ustr` into its M home, the idx*12 CSE keeps its own temp), so it never takes over the spill word. quality.py sweep: 0 hits.
- 2026-11-17 HackmodelEmitterSpawnScaledParticle4 (anthropic/claude-opus-5-5), variants.py try / deadsweep score (lines off):

  | variant | lines off |
  |---|---|
  | `s16 pos[3]` struct member, `[entryIdx].pos[k]` (jitter + position) | 57 (field first, like `.`) |
  | all four accesses through `#define EMITTER(i) (gModelEmitters + (i))` | 1 (`->scale` gives `addu t2,t8,t9` at 0x8dc, offset first) |
  | `(entryIdx + gModelEmitters)->scale`, coordinates `(p + i)->` | 1 (same addu) |
  | all four `(entryIdx + gModelEmitters)->` | 4 (addu 0x8dc plus t4/t5 swap at 0x970) |
  | entry local declared last + `s16` / `u16` randZ (narrow pack, Q0361) | 18 / 16 (sll/sra 0x10 on v0, spill still 36 -> 32) |
  | entry local in randZ's slot + `s16 randZ` declared last | 18 |
  | local `struct { s32 x, y, z; } rand`, position + jitter / jitter + position | 57 / 57 |
  | `s32 rand[3]`, position + jitter | 15 (only `rand[2]` sw/lw 48(sp)) |
  | `s32 rand[3]`, jitter + position | 149 |
  | `s32 randZ; s32 rand[2]`, position + jitter on all three | 20 |
  | `s32 rand[3]`, x/y from `rand[0..1]`, z random inline, position + jitter | 2 |
  | **three randoms inline, only scaleFactor declared, position + jitter with `[entryIdx].`** | **0 (adopted, no FAKE)** |
  | three randoms inline, jitter + position with `[entryIdx].` | 57 |

  Permuter from the declared-last entry-local body, 900 s, -j 2, hack-free weights, about 6600 iterations: base 28, best 28 (no zero). Not recorded because the sites were already fixed.
  variants.py scan of the fixed body: only `0.4f` -> `0.4` also matches.
## Untried ideas
none: the function has no hack site.
## Evidence
- Target frame 56:
  - scaleFactor swc1 52(sp) at 0x90c.
  - randX/randY sw v0,40/44(sp) at 0x92c/0x934.
  - randZ stays in v0 (48 unused).
  - idx*12 sw t8,36(sp) at 0x8f4, reloaded at 0x978.
- 0x970-0x984: lui/lw t4 = gModelEmitters (reloaded after the calls), lw t5,36(sp), addu v1,t4,t5; lh 2/4/6(v1) at 0x994/0x998/0x9a0.
- Field cvt.d.w at 0xa08 / 0xa60 / 0xae4, each after the mul.d of its random term.
- Declared-last entry: entry's home takes 36, so sw t8,32(sp) at 0x8f4 and lw t4,32(sp) at 0x978 (t4/t5 swap); nothing else differs.
- cfe operand order for a commutative `+` (measured here): cfe emits the right operand first when it holds a call or an
  indirection spelled `[]`/`.` (`p[i].f`, `a[k]` of a local array, `.pos[k]`); else it emits left first. uopt keeps the first
  emitted operand on the left of add.d. A local struct member (`rand.x`) or `->` on `(p + i)` does not trigger the right-first rule.
  So `field + jitter` needs a call or a subscript in the jitter. A nested call does that without a frame word, because its cfe
  hidden temp takes the word a named random had.

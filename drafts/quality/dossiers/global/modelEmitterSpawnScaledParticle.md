# modelEmitterSpawnScaledParticle (global, src/global/68EA0.c)
## Sites
global:80664A38:other:5ef858 / 9eff7a / 0341ea (lines 177-179), other: `(gModelEmitters + entryIdx)->x/y/z`.
- The (p + i) form makes the field address its own uadd candidate (34, v1 = gModelEmitters + idx*12 with idx*12 spilled at 36(sp)).
- Each float sum then becomes uadd{product}{ucvt field}, so the lh/cvt.d.w of the field comes after the div.d/sub.d/mul.d of the random term.
- `[entryIdx].` always gives uadd{field}{product} (Q0678), whichever side the field is written on.
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
## Untried ideas
none in natural C (byte-offset index arithmetic tried 2026-11-16). Frame count: the target frame has 5 words at 36..52 (4 homes/hidden temps + the idx*12 spill at 36; 32 is padding below them). Every entry-local body needs 6: scaleFactor, randX, randY, randZ (declared home or cfe hidden temp, Q0456/Q0858), entry, and the idx*12 spill, so the spill always lands at 32. Inline randoms avoid the homes but then the calls run after the entry assignment and entry itself must cross them.
## Evidence
- Target frame 56:
  - scaleFactor swc1 52(sp) at 0x90c.
  - randX/randY sw v0,40/44(sp) at 0x92c/0x934.
  - randZ stays in v0 (48 unused).
  - idx*12 sw t8,36(sp) at 0x8f4, reloaded at 0x978.
- 0x970-0x984: lui/lw t4 = gModelEmitters (reloaded after the calls), lw t5,36(sp), addu v1,t4,t5; lh 2/4/6(v1) at 0x994/0x998/0x9a0.
- Field cvt.d.w at 0xa08 / 0xa60 / 0xae4, each after the mul.d of its random term.
- Declared-last entry: entry's home takes 36, so sw t8,32(sp) at 0x8f4 and lw t4,32(sp) at 0x978 (t4/t5 swap); nothing else differs.

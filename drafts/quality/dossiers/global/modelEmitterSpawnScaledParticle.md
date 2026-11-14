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
## Untried ideas
none left in natural C. An entry local needs a fifth named home, and the target frame has only four.
## Evidence
- Target frame 56:
  - scaleFactor swc1 52(sp) at 0x90c.
  - randX/randY sw v0,40/44(sp) at 0x92c/0x934.
  - randZ stays in v0 (home 48 unused).
  - idx*12 sw t8,36(sp) at 0x8f4, reloaded at 0x978.
- 0x970-0x984: lui/lw t4 = gModelEmitters (reloaded after the calls), lw t5,36(sp), addu v1,t4,t5; lh 2/4/6(v1) at 0x994/0x998/0x9a0.
- Field cvt.d.w at 0xa08 / 0xa60 / 0xae4, each after the mul.d of its random term.

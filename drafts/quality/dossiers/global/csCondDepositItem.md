# csCondDepositItem (global, src/global/478F0.c)
## Sites
- global:8064BE80:noop-arith:9b58ad (fixed 2026-11-16 by `q = LERP(0.5f, 1.0f, q)`; was kept): `q = (f32)0.5 * q + 0.5f`. The cast-folded `(f32)0.5` is a constant web separate from `0.5f`, so 0.5 is materialised twice from one `lui at,0x3f00`: `mtc1 at,$f16` for the mul.s and `mtc1 at,$f4` for the add.s.
## Attempts
- 2026-11-09..12, Clean478F0 / Rev16K / Rev17L / CleanGlobal478F0 (opus low/xhigh).
  - Plain `0.5f * q + 0.5f` and the operand-order/one-line/`*=` forms merge both uses into one register.
  - `q / 2.0f + 0.5f` leaves only the mul.s operand order.
  - Permuter best=0 only respells a constant (`.5f`, `0.50f`, `0.5f * 1.0f`; Q0634).
- 2026-11-15, HackcsCondDepositItem (opus high): nohit.
  - `q / 2.0f + 0.5f` and `0.5f + q / 2.0f`: 1 line. uopt's divide-by-two multiply keeps q first: `mul.s $f18,$f0,$f16`.
  - `(q + 1.0f) / 2.0f`, `(q + 1.0f) * 0.5f`, `0.5f * (q + 1.0f)`, `(q + 1) / 2`: 6 each.
  - `q / 2 + 0.5f`: 5. `q / 2.0 + 0.5f`: 12. `0.5f * q + 0.5` / `0.5 * q + 0.5f`: 10-12. The two-statement splits score 6.
  - `0.5f * q + 1.0f / 2` and `1.0f / 2 * q + 0.5f`: 0, but these are folded-constant spellings of the same split.
  - sweep: 0 hits.
- 2026-11-16 HackcsCmdStepSequenceProgress3 anthropic/claude-opus-5-5:high: fixed.
  - `q = LERP(0.5f, 1.0f, q)` with a file-local `#define LERP(a, b, t) ((a) + ((b) - (a)) * (t))` (pitch lerps 0.5 -> 1.0 by deposit progress): fdiff 0. cfe folds `(1.0f - 0.5f)` into a second 0.5 constant web.
  - Inline `0.5f + (1.0f - 0.5f) * q`: 0. `q * (1.0f - 0.5f) + 0.5f`, `0.5f + q * (1.0f - 0.5f)`: 1 (mul.s operand order).

## Untried ideas
- None (site fixed). If the lead rules the lerp a constant-split steer (Q0816), the tag goes back on the LERP line.
## Evidence
- 0x9304 lui at,0x3f00; 0x9310 mtc1 at,$f16; 0x9314 mtc1 at,$f4; 0x9338 mul.s $f18,$f16,$f0; 0x933c add.s $f0,$f18,$f4.

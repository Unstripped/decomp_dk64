# faultDrawRegs (global, src/global/136820.c)

## Sites
- 5fb2de: `((s32 *)&ctx->ra)[1]`, a low-word read of the u64 saved ra. KEPT.
  - The target passes only `lw a1,228(s6)`.
  - Every C conversion of the u64 to 32 bits adds ucvt ring temps.

## Attempts
- 2026-11-14 U HackfaultDrawRegs, fdiff lines:
  - Whole u64 passed: 2 (a2/a3 pair).
  - `(u32)` / `(s32)`: 14.
  - Masks: 17.
  - `>> 0`: 7.
  - Locals: 20-22.

## Untried ideas
- A union or struct view of the context with 32-bit halves of ra. That is a view, not natural C, unless the SDK version the game used declared it so (not verifiable from the repo).

## Evidence
- Target 0x3fc: `jal faultPrintf` with `lw a1,228(s6)` in the delay slot; s6 = &a0->context.

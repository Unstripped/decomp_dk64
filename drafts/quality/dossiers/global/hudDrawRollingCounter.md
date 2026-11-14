# hudDrawRollingCounter (global, src/global/90D80.c)
## Sites
- `global:8068DC54:other:9bad79`: the comma statement `val -= 100, hundreds++;`.
  - The target orders the s16 truncation of val (`sll t2,v1,0x10` at 0x1d40) before `addiu s0,s0,1` for hundreds.
  - **Fixed** with the one-line form `for (hundreds = 0; val >= 100; hundreds++) val -= 100;`, tagged `// LAYOUT:`.
- `global:8068DC54:warning:8c076a`: the W709. Not mine: `retype kept` by ruling.
## Attempts
**Earlier, Rev26A (low model).** All fdiff 1:
- two statements and swapped statements;
- `for (hundreds = 0; ...)`;
- `for (val = *curVal; ...; val -= 100)`.

**2026-11-14, Hack90D80HitCounter** (scores from `variants.py try`):

| form | score |
|---|---|
| step-form `for` over two lines | full=2: only the sll moves |
| `while` with two statements | full=6 |
| do-while | full=6 |
| `val -= 100` as the step | full=8 |
| `hundreds = val / 100; val %= 100;` | full=412 |
| variants scan of the step form | best full=2 |
| one-line `for`, or one-line `while { ...; ...; }` | full=0 |

## Evidence
- Only the source-line layout matters here: as1 schedules the two updates differently when they share a line (Q0396, Q0321, Q0149).

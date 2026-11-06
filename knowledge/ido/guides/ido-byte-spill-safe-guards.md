---
title: "Safe byte-spill guards in arcadeInsertHighScore"
description: "A defined-C alternative to the rejected uninitialized-halfword match, preserving IDO byte spills and register allocation."
origin: "ok-fine dk64/notes/ido-byte-spill-safe-guards"
---
# Safe byte-spill guards

`arcadeInsertHighScore` needs a byte saved at `sp+0xC` and reloaded into `a0` after shifting the score/name tables. Its old text-exact draft read a halfword after initializing only its first byte; that was rejected. The matching replacement uses `u16 initial[2]` only as backing storage: every evaluated read uses a `u8 *` and selects byte zero (`i % 1` is zero). The sole halfword expression is the right operand of `(u32)i < 0 && initial[0]`; unsigned comparison with zero is always false, so C short-circuit semantics prohibit that read.[^source]

The two byte-only dead guards surround a dead row-address guard, with the non-evaluated halfword guard between the first byte guard and the row guard. This combination reproduces all 45 instructions, including stack layout and register allocation. These are tagged FAKE constructs, not recovered original source; initialization of the second byte added an unwanted store, and tested volatile-storage alternatives did not match. The same-line loop initializer remains tagged LAYOUT.[^source]

Verification: whole-object code/extern relocation comparison passed; both the isolated gate and checkout build passed the full ROM SHA-1. A temporary ASan/UBSan harness checked all five valid insertion ranks, all 256 initial bytes, and scores `INT32_MIN`, `-1`, `0`, `1`, `INT32_MAX` (6,400 cases), comparing the full score/name tables to snapshot-based insertion. The harness was removed after passing.[^verification]

Review rule: prove evaluated accesses are initialized in the C abstract machine, including short-circuit paths; matching generated instructions alone does not establish that.

## Sources

[^source]: src/arcade/0.c @ a1b1cf901c90
[^verification]: ROADMAP.md @ a1b1cf901c90

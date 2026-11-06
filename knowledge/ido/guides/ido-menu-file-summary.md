---
title: "menuInitFileSummary: coordinated lifetime and source-line scheduling"
description: "How shared pointer/counter lifetimes and two combined .loc removals matched the menu file-summary initializer."
origin: "ok-fine dk64/notes/ido-menu-file-summary"
---
# menuInitFileSummary: coordinated lifetimes, then scheduling

Matched as ordinary C in `src/menu/3E10.c` at source commit `9db1e2fa`: 189 instructions / 756 bytes. The full translation-unit comparison was TEXT OK, the isolated gate reported GATE_OK, and the main checkout rebuilt the byte-identical ROM. Menu now has 110/113 matched functions and 57,848/61,236 matched function bytes.[^c][^status]

## Diagnose both loops together

The parked version was full=7 / text=7 / shape=2: the first flag-loading loop put its flag pointer `q` in s1 and its end address in s2, opposite the target. Its byte pointer `p` correctly occupied s0. The original score's 241 lines include relocations, not 241 instructions.[^before]

Level-5 uopt traces showed the old priorities: p=20.5, q=15.5, end=6.0. Two coordinated changes resolve the allocation:[^trace][^c]

- Reuse p in both the flag-loading loop and the character-icon loop instead of a separate p2. This also permits deleting the trailing dead `if (i) {}` FAKE that formerly extended the second loop's counter lifetime.
- Reuse signed 32-bit i first for the flag-array end address, then as the second loop's 0..4 counter. On this 32-bit target the pointer/integer casts preserve the address; do not generalize this spelling to a wider host ABI.

The resulting candidates are p (bit 18, priority 24, register 14=s0), i (bit 21, priority 24, register 15=s1), q (bit 15, priority 15.5, register 16=s2). q's forbidden set gains register 15. p alone leaves the original seven differences; bound reuse without the coordinated p reuse also fails. The unused pointer local's stack space is retained as an s32 pad so the frame stays 0x80 and the PI result stays at sp+0x64.[^c][^trace]

## Combine independent line-boundary fixes

With the right registers, full=8 / text=4 remained: only the order of three address-initialization addiu instructions differed. as1probe's single-edit scan found that deleting either intervening .loc record independently improved full 8 to 4. Combining both removes the difference entirely: keep q, p, and i's three initializers on one source line, in that order. The source carries a trailing LAYOUT comment. Individual scheduling edits can each fix only part of one group; a nonzero single-edit minimum is not a blocker.[^as1][^c]

The existing checksum `^ 0` FAKE remains: direct comparisons in either operand order, signed/unsigned casts, and explicit result locals all produced one branch-operand difference. This run removed the dead counter test, not that checksum tag. No game behavior, compiler flag, expected hash, or symbol address changed.[^c]

Related: cross-loop allocation (guide ido-load-overlay-diagnostics: python3 tools/quirks.py get ido-load-overlay-diagnostics), overlay units (ok-fine dk64 architecture/overlay-c-units).

[^before]: Parked function at commit 839d716e9e8d12c25cf85551e4793339e7dce902.
[^c]: Matching source in src/menu/3E10.c.
[^trace]: Level-5 traces from tools/uopt_trace.sh before and after the lifetime changes.
[^as1]: tools/as1probe.py keep/scan followed by initializer grouping experiments; final whole-file and ROM gates passed.
[^status]: README.md and ROADMAP.md matching status.

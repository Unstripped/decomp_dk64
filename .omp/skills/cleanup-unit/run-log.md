# Run log

One row per cleanup round, newest last; keep the last ~10. Read when sizing a round; SKILL.md
§8 adds the row.

|date|unit|files|FAKE −|goto −|steer|names|notes|
|---|---|---|---|---|---|---|---|
|2026-11-09|cleanup pilot|global/7130.c, menu/E550.c (2 agents, opus-5-5, default task model; 43 + 59 min)|net −19: 27 removed (7130 12, E550 5, 10 steers in 4 files sharing the sound handles), 8 added (7 untagged hacks tagged, 1 `int` limit local)|0|23 proto-steer lines removed|4 menu globals; ~175 locals/params, 38 file-local fields|45/45 functions EXHAUSTED. 3 header requests (Actor sound fields, PlayerState.sfxHandle, faultSetMessage u32) landed mid-round; the first missed a user (`rename.py field --dry-run` probe now in §4). Retyping the argument (handles as `struct GfSndState *`) beat keeping callee steers (Q0508). Tool fixes found by the pilot: permuter runs stopped at 0, `clint` punned casts scalar-only, layout accepts arrays over the same bytes, `quality.py carry` after renames; file knowledge before `record`.|

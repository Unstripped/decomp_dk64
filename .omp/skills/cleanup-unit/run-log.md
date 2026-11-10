# Run log

One row per cleanup round, newest last; keep the last ~10. Read when sizing a round; SKILL.md
§8 adds the row.

|date|unit|files|FAKE −|goto −|steer|names|notes|
|---|---|---|---|---|---|---|---|
|2026-11-09|cleanup pilot|global/7130.c, menu/E550.c (2 agents, opus-5-5, default task model; 43 + 59 min)|net −19: 27 removed (7130 12, E550 5, 10 steers in 4 files sharing the sound handles), 8 added (7 untagged hacks tagged, 1 `int` limit local)|0|23 proto-steer lines removed|4 menu globals; ~175 locals/params, 38 file-local fields|45/45 functions EXHAUSTED. 3 header requests (Actor sound fields, PlayerState.sfxHandle, faultSetMessage u32) landed mid-round; the first missed a user (`rename.py field --dry-run` probe now in §4). Retyping the argument (handles as `struct GfSndState *`) beat keeping callee steers (Q0508). Tool fixes found by the pilot: permuter runs stopped at 0, `clint` punned casts scalar-only, layout accepts arrays over the same bytes, `quality.py carry` after renames; file knowledge before `record`.|
|2026-11-09|cleanup round 1|global/E4090, D5E10, 478F0, 19A00, 201B0, EFDC0, 36880, CEAE0, 6AD90, 80150, 2F550, arcade/0, menu/3E10 (11BC10 deferred; done in round 2); 6 concurrent agents (opus-5-5), several 2–4 turns per file|repo FAKE 970 → 934 (−36 net: ≈100 steers retired by 14 callee-prototype batches, offset by pre-existing untagged hacks now tagged in E4090/36880/478F0/201B0)|0 (39 → 39)|`// PROTO:` 134 → 120; proto-steer 520 → 394|~1,700 m2c names (4,885 → 3,191); shared fields carved into Actor, ActorSub4, ActorSub140, ActorGlobalState, PlayerState, PlayerStruct, CsState, SchedStruct; DynamicBuffer → heap.h|reviewed 45 → 1,331, exhausted 45 → 1,258 of 4,270. Proto workstream: owner merged alone → `protos gen` → callers → `--stage` gate. Tool fixes: `record --dry-run`, review freshness ignores checklist tokens, `carry` across unrelated file-scope changes, newest event by time, per-function `fp_hdr2`, `objdiff.sh` always rebuilds (`make -B`), `rename.py field --dry-run` lists macro references. Round-end renames NOT applied (below).|

## Proposed names (not yet applied)

Not covered by `rename.py` (needs a symbol-fold procedure): D_807FD63A/C/E/F → gPlayerPadState+0x2A/0x2C/0x2E/0x2F
(3 E4090 functions keep the labels for codegen, Q0264). Unconfirmed (moderate evidence, round 2 55B20):
func_8065C990 → lightApplyToVertexRange.

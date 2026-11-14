# effectWaterInitNodes (global, src/global/63EC0.c)

## Sites
global:8065F1C0:dead-if:c329e5 dead-if: the empty `gCurrentMap == 0` block preserves the opening table loop's `$v0` base / `$v1` end coloring; removed by expressing the later real 0x53/0xC5 map selector as a switch.
global:8065F1C0:noop-arith:5ef177 noop-arith: the extra `count * 0` use raises count's uopt priority so it receives `$v0` while the water-definition base receives `$v1`.

## Attempts
2026-11-14 U HackeffectWaterInitNodes openai-codex/gpt-5.6-sol: replaced the dead map block and later OR condition with a two-case selector switch -> whole-function fdiff exit 0.
2026-11-14 U HackeffectWaterInitNodes openai-codex/gpt-5.6-sol: natural zero guards, count switches, positive guarded for/do-while loops, index sentinels, MAX/MIN, u8/s32 and structured loads, declaration/assignment timing, sizeof-derived table counts, constant node size, and targeted variant/as1 scans -> best natural fdiff score 55; noop retained.

## Untried ideas
None remaining within ordinary C after targeted uopt/as1 diagnosis and the session's current natural-C recipes.

## Evidence
The target loads count into `$v0` at 0x68, tests `$v0` at 0x70 and 0x88, computes the water-definition base in `$v1` at 0x84/0x8c, and spills count at sp+0x4c at 0x9c. Natural `count == 0` forms reverse `$v0`/`$v1` for ten register-only instruction differences (fdiff score 55); trace candidates change from the matching LR17/color-1 count with the extra use to natural LR14/color-2. The replacement map switch emits the target 0x53/0xC5 branches and `i == 0` check at 0xe0-0x124 while removing c329e5.

# bossMainStep (boss, src/boss/F0D0.c)

## Sites
boss:80033AF0:dead-if:21ced0 dead-if: `if (v) {}` after `left = v; left--;` in unk155 case 5 kept v (bit 285, -34vreg) live past the decrement, so v kept $v0 and v-1 took $v1 (target 0x157c-0x158c: lbu v0,24(s1); beqz v0; addiu v1,v0,-1; andi t4,v1,0xff; sb t4,24(s1)). FIXED (2026-11-14, HackbossMainStep).

## Attempts
2026-11-11 Rev16B opus-5-5:xhigh: uopt_trace (dead read extends v), permute best=10 (v--; through st->unk18) -> no match
2026-11-11 Rev16F opus-5-5:xhigh: objdump of the variant without the dead if (v in v1, raw v-1 in v0 stored before the mask), permute best 10 -> no match
2026-11-12 Rev17L opus-5-5:low: permute best 125 -> no match
2026-11-14 PolishBossF0D0Names / OwnerBossScriptStateCarve / RereviewSmallFiles4 opus-5-5:high: views/names only, site unchanged
2026-11-14 HackbossMainStep opus-5-5:high: case-5 respellings alone, all with the shared v unchanged (variants.py try): `--v` 4, `left = v - 1` 5, `left = v - 1` before `if (v != 0)` 4, field-only forms (`st->unk18[0]--; path[st->unk18[0]]`) 546 (v-1 becomes a ring temp, rest of the function shifts), `path[--st->unk18[0]]` 103, separate u8 local for case 5 or for case 0x23 101-113 (v must stay shared), width/declswap scans of the `--v` and `left = v - 1` forms: no zero
2026-11-14 HackbossMainStep opus-5-5:high: case 6 of state 0x25/0x28 rewritten as `if (st->unk18[0] != 0) { st->unk18[0]--; ...}` (no v), case 5 as `v = st->unk18[0]; left = v - 1; if (v) { st->unk18[0] = left; next = path[left]; ...}` -> fdiff 0 (same with `if (v != 0)`: 4)
2026-11-14 HackbossMainStep opus-5-5:high: casts: dropped 16 no-op casts (fdiff 0); `(f32)v` / plain `v` for `(f32)(s32)v` -> 47; plain store for `(s8)tbl[...]` -> 3

## Untried ideas
none open for this function (no sites left)

## Evidence
uopt -zdbug:5 (copy at base): v bit 285 adjsave 3.00 (assigned uopt 1 = $v0), ucvtl(v-1) bit 483 adjsave 3.00 (uopt 2 = $v1). Without the dead if: v adjsave 2.67, the v-1 uadd candidate (bit 293) adjsave 3.00 colours first and takes $v0. Final copy: v adjsave 3.00, $v0.
Target case 6 (0x1dcc): lbu v0,24(s1); beqz v0; addiu t6,v0,-1; sb t6,24(s1): v-1 is a ring temp there, so that case never needed the variable.

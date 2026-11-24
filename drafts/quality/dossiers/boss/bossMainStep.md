# bossMainStep (boss, src/boss/F0D0.c)

## Sites
boss:80033AF0:dead-if:21ced0 dead-if: `if (v) {}` after `left = v; left--;` in unk155 case 5 kept v (bit 285, -34vreg) live past the decrement, so v kept $v0 and v-1 took $v1 (target 0x157c-0x158c: lbu v0,24(s1); beqz v0; addiu v1,v0,-1; andi t4,v1,0xff; sb t4,24(s1)). FIXED (2026-11-14, HackbossMainStep).
boss:80033AF0:other:693ce5 other (pre-existing, tagged 2026-11-18b Polishboss3840): `u8 v` holds case 5's `scriptState->byteVars[0]` copy AND the case-2 hit frame (`v = 0x35` / `0x17`, `(f32)(s32)v <= model->frame`). The shared range is what gives v adjsave 3.00 -> $v0 in case 5 (0x157c-0x1588). KEPT (diagnose nohit, re-measured 2026-11-24b ReMeasureB18H).

## Attempts
2026-11-11 Rev16B opus-5-5:xhigh: uopt_trace (dead read extends v), permute best=10 (v--; through st->unk18) -> no match
2026-11-11 Rev16F opus-5-5:xhigh: objdump of the variant without the dead if (v in v1, raw v-1 in v0 stored before the mask), permute best 10 -> no match
2026-11-12 Rev17L opus-5-5:low: permute best 125 -> no match
2026-11-14 PolishBossF0D0Names / OwnerBossScriptStateCarve / RereviewSmallFiles4 opus-5-5:high: views/names only, site unchanged
2026-11-14 HackbossMainStep opus-5-5:high: case-5 respellings alone, all with the shared v unchanged (variants.py try): `--v` 4, `left = v - 1` 5, `left = v - 1` before `if (v != 0)` 4, field-only forms (`st->unk18[0]--; path[st->unk18[0]]`) 546 (v-1 becomes a ring temp, rest of the function shifts), `path[--st->unk18[0]]` 103, separate u8 local for case 5 or for case 0x23 101-113 (v must stay shared), width/declswap scans of the `--v` and `left = v - 1` forms: no zero
2026-11-14 HackbossMainStep opus-5-5:high: case 6 of state 0x25/0x28 rewritten as `if (st->unk18[0] != 0) { st->unk18[0]--; ...}` (no v), case 5 as `v = st->unk18[0]; left = v - 1; if (v) { st->unk18[0] = left; next = path[left]; ...}` -> fdiff 0 (same with `if (v != 0)`: 4)
2026-11-14 HackbossMainStep opus-5-5:high: casts: dropped 16 no-op casts (fdiff 0); `(f32)v` / plain `v` for `(f32)(s32)v` -> 47; plain store for `(s8)tbl[...]` -> 3
2026-11-18b Polishboss3840 opus-5-5:xhigh (693ce5): a dedicated hitFrame (u8 with (f32)(s32), s32 with implicit cvt) at each of the 21 declaration positions, a block-scoped s32, pad1/pad2-slot reuse, natural case-5 countdowns (x != 0 then x-- / --x / left-only): all fdiff 1; `(f32)v` without the (s32) adds the unsigned cvt fixup (Q0227)
2026-11-24b ReMeasureB18H opus-5-5:xhigh (693ce5, after the cb17735e EffectGridAsset extern retype; the site reads no sprite), variants.py try (base body scores full 3 in the reduced TU): hitFrame u8 at 21 slots best 13 (declared before sx, before/after left, or last), s32 at 21 slots 64-110, block-scoped u8 13 / s32 110; case-5 field-only 551, left-only 11, left inside the if 13, predecrement 668; ternary hit frame `(animId == 0x223 ? 0x35 : 0x17) <= frame` 7 (case 2 exact, only case 5's v0/v1 swap left), with 53.0f/23.0f 74; ternary + `if (v != 0)` 5 (addiu v0,v0,-1: v-1 coalesces with v), ternary + left-only 5 (beqz/addiu order), ternary + left inside the if 7, ternary + field-only 547, ternary with v at all 21 slots best 5; variants.py scan of the ternary body (truth/switch/swap/width/declswap/branch, 315 variants): best 5, no zero

## Untried ideas
none in natural C for 693ce5: v's case-5 colour needs a second role in the same uopt range; every split (21 slots x 2 widths, block scope, ternary) lowers v's priority

## Evidence
uopt -zdbug:5 (copy at base): v bit 285 adjsave 3.00 (assigned uopt 1 = $v0), ucvtl(v-1) bit 483 adjsave 3.00 (uopt 2 = $v1). Without the dead if: v adjsave 2.67, the v-1 uadd candidate (bit 293) adjsave 3.00 colours first and takes $v0. Final copy: v adjsave 3.00, $v0.
Target case 6 (0x1dcc): lbu v0,24(s1); beqz v0; addiu t6,v0,-1; sb t6,24(s1): v-1 is a ring temp there, so that case never needed the variable.
693ce5 uopt -zdbug:5 (2026-11-24b): base v {1440|0} bit 285 -34vreg adjsave 3.00, assigned uopt 1 ($v0); ternary hit frame: v adjsave 1.50, assigned uopt 2 ($v1), the v-1 candidates colour first. Target case 2 (0x1950-0x1968): b / li v0,53 (li v0,23 path), mtc1 v0,$f6; cvt.s.w; c.le.s against model->frame.

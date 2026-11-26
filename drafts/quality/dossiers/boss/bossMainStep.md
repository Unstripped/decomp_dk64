# bossMainStep (boss, src/boss/F0D0_common.c)

## Sites
boss:80033AF0:dead-if:21ced0 dead-if: `if (v) {}` after `left = v; left--;` in unk155 case 5 kept v (bit 285, -34vreg) live past the decrement, so v kept $v0 and v-1 took $v1 (target 0x157c-0x158c: lbu v0,24(s1); beqz v0; addiu v1,v0,-1; andi t4,v1,0xff; sb t4,24(s1)). FIXED (2026-11-14, HackbossMainStep).
boss:80033AF0:other:693ce5 other (pre-existing, tagged 2026-11-18b Polishboss3840): `u8 v` held case 5's `scriptState->byteVars[0]` copy AND the case-2 hit frame (`v = 0x35` / `0x17`, `(f32)(s32)v <= model->frame`). The shared range gave v adjsave 3.00 -> $v0 in case 5 (0x157c-0x1588). FIXED 2026-11-25c CleanbossMainStep: the hit frame is the ternary `(animId == 0x223 ? 0x35 : 0x17) <= model->frame`, and the counter copy (renamed `count`) is read in case 6 of state 0x25/0x28 too, its own role, which keeps adjsave 3.00 (fdiff 0).

## Attempts
2026-11-11 Rev16B opus-5-5:xhigh: uopt_trace (dead read extends v), permute best=10 (v--; through st->unk18) -> no match
2026-11-11 Rev16F opus-5-5:xhigh: objdump of the variant without the dead if (v in v1, raw v-1 in v0 stored before the mask), permute best 10 -> no match
2026-11-12 Rev17L opus-5-5:low: permute best 125 -> no match
2026-11-14 PolishBossF0D0Names / OwnerBossScriptStateCarve / RereviewSmallFiles4 opus-5-5:high: views/names only, site unchanged
2026-11-14 HackbossMainStep opus-5-5:high: case-5 respellings alone, all with the shared v unchanged (variants.py try): `--v` 4, `left = v - 1` 5, `left = v - 1` before `if (v != 0)` 4, field-only forms 546, `path[--st->unk18[0]]` 103, separate u8 local for case 5 or for case 0x23 101-113, width/declswap scans: no zero
2026-11-14 HackbossMainStep opus-5-5:high: case 6 of state 0x25/0x28 rewritten as `if (st->unk18[0] != 0) { st->unk18[0]--; ...}` (no v), case 5 as `v = st->unk18[0]; left = v - 1; if (v) {...}` -> fdiff 0 (dead if 21ced0 removed)
2026-11-14 HackbossMainStep opus-5-5:high: casts: dropped 16 no-op casts (fdiff 0); `(f32)v` / plain `v` for `(f32)(s32)v` -> 47; plain store for `(s8)tbl[...]` -> 3
2026-11-18b Polishboss3840 opus-5-5:xhigh (693ce5): a dedicated hitFrame (u8 with (f32)(s32), s32 with implicit cvt) at each of the 21 declaration positions, a block-scoped s32, pad1/pad2-slot reuse, natural case-5 countdowns: all fdiff 1
2026-11-24b ReMeasureB18H opus-5-5:xhigh (693ce5): hitFrame u8 at 21 slots best 13, s32 64-110, block-scoped u8 13 / s32 110; case-5 countdown forms 11-668; ternary hit frame 7 (case 2 exact, only case 5's v0/v1 swap), ternary + case-5 forms best 5, ternary with v at 21 slots best 5; variants.py scan of the ternary body: best 5
2026-11-25c CleanbossMainStep opus-5-5 (693ce5): frame map (below); case 6 of 0x25/0x28 through v (`v = byteVars[0]; if (v) { byteVars[0] = v - 1;`) with: the v hit frame 3 (= base score), the ternary hit frame 3 -> fdiff 0 (KEPT), `if (v != 0)` + ternary 10, u8 hitFrame (`(f32)(s32)`) in the 0x78-0x7A hole 9, u8 hitFrame declared after v 106, s32 hitFrame in the hole 106 -> site fixed; v renamed `count` (one role now)

## Untried ideas
none open: site fixed

## Evidence
Frame 0x90 (target 0xa20 addiu sp,-144): ra 0x44, s2 0x40, s1 0x3c, s0 0x38; outgoing args 0x10-0x2B; uopt spill 0x50 (a1, 0xfa8/0xfd0/0x1170); unnamed M candidates at -56/-60vreg (0x58/0x54) below the last declared local. Named homes, declaration order: scriptState 0x8C (in s1, home never touched), waypoints 0x88, tbl 0x84, playerAbove 0x83, pad2[3] 0x80-0x82, debrisSfx 0x7F, pad1 0x7E, nextIdx 0x7D, red 0x7C, green 0x7B, alignment hole 0x78-0x7A, sx 0x74, sy 0x70, idx 0x6F / v 0x6E / i 0x6C (register-only, never touched), boneX/Y/Z 0x68/0x64/0x60 (actorGetNodePos), left 0x5F / bright 0x5E (register-only). v's home 0x6E is never stored: the old reuse was register-only (rulings R5, not ORIG).
uopt -zdbug:5 (copy at base): v bit 285 adjsave 3.00 (assigned uopt 1 = $v0), ucvtl(v-1) bit 479 adjsave 3.00 (uopt 2 = $v1). Without the dead if: v adjsave 2.67, the v-1 uadd candidate (bit 293) adjsave 3.00 colours first and takes $v0.
Base 2026-11-25c: v live bbs 161/162 (defs 0x35/0x17), 163 (use), 101 (def+use), 102 (use): 6 points / bucket(5) = 2 -> 3.00 (Q1417). Fixed copy: v live bbs 101/102 (case 5) + 219/220 (case 6, def+use, use): 6 / bucket(4) = 2 -> 3.00, ties ucvtl(v-1) 3.00, lower bit 285 wins $v0.
Target case 6 (0x1dcc): lbu v0,24(s1); beqz v0; addiu t6,v0,-1; sb t6,24(s1): the counter copy in $v0 and v-1 a ring temp, which `count = byteVars[0]; if (count) { byteVars[0] = count - 1;` emits unchanged.
Target case 2 (0x193c-0x1968): li v0,23 / b; li v0,53, mtc1 v0,$f6; cvt.s.w; c.le.s against model->frame: the int ternary compared with an f32 emits it unchanged.

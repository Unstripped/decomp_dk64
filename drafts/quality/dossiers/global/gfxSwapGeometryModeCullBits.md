# gfxSwapGeometryModeCullBits (global, src/global/17B90.c)
## Sites
global:806130A4:other:17676c `op = 0;` at entry: makes op (-8vreg) candidate bit 0, coloured first into $v0 (uopt 1); without it w0 takes $v0 and the command shift lands in $a2 (lw v0,0(a0) / srl a2,v0,0x18).
global:806130A4:dead-if:3d5cd4 `if ((w0 & 0x600) && (w0 & 0x600)) {}` at loop top: starts the `w0 & 0x600` candidate (uand{1120}{1536}) before the D9 test so it overlaps the shift web in $v0 and is coloured $a3 (andi a3,v1,0x600 at 0x278). Without it the mask takes $v0, conflicts with op and as1 cannot fill the 0x280 delay slot (nop + one-insn shift; score 5, 4 with `0xD9 == command`).
global:806130A4:other:c82f14 / c82f14#2 `w0 = 0;` between `op = w0 | 0x400/0x200` and `op &= ~...`: kills w0 so uopt cannot forward the or-expression; op stays the $v0 variable (ori v0,v1,0x400 / and v0,v0,t4 at 0x280-0x284; ori v0,v1,0x200 / and v0,v0,s1 at 0x29c-0x2a0). Removed, op folds into ugen temps t7/t8/t9 and every web shifts (score 25 / 17; both 26).
global:806130A4:noop-arith:9530a0 `(op | 0) == 0x400`: REMOVED this round (see Attempts).
global:806130A4:dead-if:0d68f0 `if (command && command) {}` at loop end: keeps the command variable (-4vreg) a candidate coloured $a2 (no code), which pushes the mask/w1 webs to $a3 and the field load to $t0; removed, frame 0x18->0x10 and every constant shifts (score 52).
## Attempts
2026-11-11 round 12 CleanGlobal17B90 opus:low: diagnose all six, permute, reconstruct r_gfx (11085), review.
2026-11-11 round 16 Rev16E opus:low: permute x2 (all six removed), diagnose or0/dif600, reconstruct v_grec (for loop unrolled, Q0647).
2026-11-12 round 23 Rev23A opus:low: per-site diagnose + permute (op0, w0a, w0b, or0, cmd, dif600), reconstruct do-while (10750).
2026-11-14 HackgfxSwapGeometryModeCullBits opus:high:
- 9530a0: set-word arm written without op: `else if ((w1 & 0x600) == 0x200) {...} else if ((w1 & 0x600) == 0x400) {...}` (CSE'd mask, constant-first bne per Q0185) -> fdiff 0, site removed.
- casts: op declared `s32` (it only holds clear-word values now) -> both `(s32)op & ~0x200/0x400` casts drop (`op &= ~0x200`), fdiff 0; the clear arm keeps its signed ~0x200/~0x400 constant webs (t4/s1) apart from the unsigned set-arm ones (s2/s3), Q0523/Q0043.
- `if (cmdStart->unk4 == 0)` -> `if (w1 == 0)`, set arm folded into `else if`: fdiff 0.
- Full 31-subset ablation of the five remaining steers on the new base: op0 15, dif600 5, w0a 25, w0b 17, cmd 52; no pair or triple cheaper than its parts.
- Natural families scored with variants.py try (all steers removed): s32/u32 clear and mode locals, shared vs split op, rmw vs one-expression arms, while vs guarded do-while (72 bodies, best 53/62); single reused op for shift+clear+mask (72 bodies, best 53); outer/inner `switch` on the opcode and both masks (126 bodies, best 53); `_SHIFTR` shapes (andi 0xff stays, rejected); mask local in the clear arm (5); w1 load order (15/20); `0xD9 == command` (4); op copy/rmw/store-through-w0 forms for the w0 kills (26).
- Permuter perm_all5 from the five-steer-free body: 900 s, baseline 971, best 165 (output-165-1: a new_var copy temp holding both the loaded word and w1, a copy-temp steer); no zero.
## Untried ideas
A clear-arm mask candidate that starts before the D9 test without a dead test (the target needs `w0 & 0x600` live across the shift web).
A third variable that holds $a2 the way the dead command test does (target leaves $a2 unused while $a3/$t0 are taken).
## Evidence
Target (expected/build/src/global/17B90.o, 0x214-0x300): constants t2=0xFFFFFF, s3=-1025, s2=-513, s1=-1025, s0=1024, t5=0xD9000000, t4=-513, t3=512, t1=217; loop vars v1=w0/clear, t0=field w1, a3=w1 copy + clear mask, v0=shift/op/set mask, $a2 unused.
`bne v0,t1` at 0x260 (shift first), every mask compare constant-first: bne t3,a3 (0x27c), bne s0,a3 (0x298), bne t3,v0 (0x2b4), bne s0,v0 (0x2cc).
Set arm stores twice (sw t7,4(a0) then sw t9,4(a0) at 0x2bc/0x2c8): the `|=` then `&=` pair is behaviour.
Clear arm writes `~op | 0xD9000000` without re-masking (top byte becomes 0xFF): behaviour, not a typo to fix.

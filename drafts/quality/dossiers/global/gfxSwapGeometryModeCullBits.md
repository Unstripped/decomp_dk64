# gfxSwapGeometryModeCullBits (global, src/global/17B90.c)
## Sites
global:806130A4:other:17676c `op = 0;` at entry: makes op (-8vreg) candidate bit 0, coloured first into $v0 (uopt 1); without it w0 takes $v0 and the command shift lands in $a2 (lw v0,0(a0) / srl a2,v0,0x18). Still 15 on the 2026-11-16 op-copy body.
global:806130A4:dead-if:3d5cd4 REMOVED 2026-11-16: with the op = w0 copy the clear mask is coloured $a3 on its own (andi a3,v1,0x600 at 0x278); the only leftover was the D9 compare order at 0x260, fixed by writing `0xD9 == command`.
global:806130A4:other:c82f14 / c82f14#2 REMOVED 2026-11-16: the clear arm copies the complemented word once (`op = w0;`) and modifies the copy (`op |= 0x400; op &= ~0x200;` / `op |= 0x200; op &= ~0x400;`); op stays the $v0 variable (ori v0,v1,0x400 / and v0,v0,t4 at 0x280-0x284; ori v0,v1,0x200 / and v0,v0,s1 at 0x29c-0x2a0) with no w0 = 0 kill.
global:806130A4:noop-arith:9530a0 `(op | 0) == 0x400`: REMOVED 2026-11-14 (see Attempts).
global:806130A4:dead-if:0d68f0 `if (command && command) {}` at loop end: keeps the command variable (-4vreg) a candidate coloured $a2 (no code), which pushes w1 to $a3 and the field load to $t0. On the op-copy body removing it also lets uopt unroll the do-while 2x (subu v0,a1,a0; andi t6,v0,0xf remainder preheader; score 145); a for(;;) break loop stops the unroll and leaves the old 52 (frame 0x18->0x10).
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
2026-11-15 HackgfxSwapGeometryModeCullBits2 opus:high:
- Level-5/6 traces: every candidate is coloured unconstrained, in candidate-bit order (lowest free register). Target order: op(bit 0)->$v0, a0, a1, w0(10)->$v1, command(14)->$a2, ushr(16)->$v0, mask w0&0x600(18)->$a3, w1(19)->$a3, w1 load(21)->$t0, w1 mask(49)->$v0. Natural body (59): w0(7)->$v0, w1->$v1, load->$a2, w0 mask->$v1, w1 mask->$v0; command, ushr and op are no candidates.
- Re-ablation on the current base: op0 15, dif 5, kill pair 26, cmd 52, all 59 (matches dossier).
- cmd-test substitutes: combined `command == 0xD9 && w1 == 0` / `else if (command == 0xD9)` (42; while form 42), early `continue` (52). Command forwarded at input, ushr computed at the compare, mask loses its $v0 conflict.
- op0 substitutes: Gfx *gfx copy of cmdStart (25 without op0, 19 with), K&R definition (no change: 0/15/5/26/52/59).
- kill-free clear arms: w0 = op & ~0x200 (33), op = ~op | 0xD9000000; store op (26), w0 = ~op | 0xD9000000 write-back (47), w0 rmw (41), op as clear-mask local (41), u32 op (36). Set arm through w1 rmw + two stores (59 without kill, 140 with).
- Reconstruct: per-arm direct word reads (61), early-continue for/do (59, not unrolled), gfx pointer-walk for (55), per-arm mask local (143).
- variants.py scan on the copy: zeros only for neutral respellings (operand swaps, command s32, decl swaps).
2026-11-15 HackgfxSwapGeometryModeCullBits3 opus:high (brief untried ideas; 45 bodies scored with variants.py try):
- op0: `register s32 op` (first or second declaration) without op = 0: 15 (IDO ignores register; w0 takes $v0).
- dif600: declared-last mask local (`u32 mode`/reused `w1 = w0 & 0x600`, var-first or constant-first compares, other four steers kept): 5; `s32 mode` 19. One-op RHS forwarded (Q0550), the uand web starts in the clear arm after the ushr web dies, takes $v0 (andi v0,v1,0x600; nop at 0x280; bne t1,v0 at 0x260). Complemented-bits role local `clear = ~w0 & 0xFFFFFF`: 44-55, 19-39 only with its own dead test.
- kills: multi-op one-expression `op = (w0 | 0x400) & ~0x200` with the other steers kept 36 (37 no mask test, 64 no command test); op-free store arms 36; u32 op 36.
- cmd: `s32 pad`/`pad[2]` declared last 52 (frame 0x18 is four s-register saves, not a home); u8 command 24 (52 without the test); embedded `(command = w0 >> 24) == 0xD9` 15; command declared last neutral (0).
- reconstruct: role locals clear/mode with op-free one-expression stores 150 (s32 153, while 150); embedded w0/command assignment in the D9 test 59; combined mode local + one-expression arms 142.
2026-11-16 HackgfxSwapGeometryModeCullBits opus:high (base a7a3de0d; ~200 bodies with variants.py try):
- kills c82f14/c82f14#2 FIXED: copy-then-rmw `op = w0; if (...) { op |= 0x400; op &= ~0x200; store }` (fdiff 0 with the other three steers). Condition-embedded copy `if (((op = w0) & 0x600) == 0x200)` 14 (signed op mask gives the set arm its own 0x200/0x400 webs s2/s4); u32 op 10; per-arm `op = w0;` with the kill 22; complement straight into op (`op = ~w0 & 0xFFFFFF`, op masks) 27-29.
- dif600 3d5cd4 FIXED: on the op-copy body its removal scores 1 (bne t1,v0 at 0x260); `0xD9 == command` gives 0. Every compare constant-first also 0. as1probe scan of the old dif-free body: only deleting a branch helps (uopt-level).
- op0 17676c kept: op-copy body without it 15; chained `op = w0 = ~w0 & 0xFFFFFF` 15 (0 with op = 0); pre-guard `Gfx *end = cmdEnd` local 15 (19 with op = 0); three-parameter K&R definition homes the unused a2 (sw a2,0x18(sp)); `op = command = w0 >> 24` 61; one variable for op and command 9 (17 without op = 0).
- cmd 0d68f0 kept: op-copy body without it 145 (2x unroll). Loop shapes do-while/for/while × plain/constant-first/switch/switch-default/early-continue/combined/no-command-var 145-164; for(;;)/while (TRUE) guarded loops with `if (++cmdStart == cmdEnd) break;` or return 52 (0 with the test); clear-arm store `~op | (command << 24)` 42; command reused for the stored word 52; merged mask+command dead tests 40/52 (top) or 5 (end).
- statement order w0/command/dif/w1 (36 bodies on the old body): the mask must follow the shift and precede the w1 read; `w1` read only in the set arm 60; `mode` local holding w1 with a clear-arm mask local 5 (forwarded, Q0550).
- permute perm_noop0 (op-copy body without op = 0; 605 s, baseline 152): zeros only by reusing op before the loop: `op = cmdStart != cmdEnd; if (op)`, `op = 24; command = w0 >> op`, `op = 0xD9; if (op == command)`. A dedicated `s32 notEmpty` guard local scores 15, so only op's own first appearance matters.
## Untried ideas
A natural statement before the `cmdStart != cmdEnd` guard that makes op (not a0/a1) the first candidate without a dead store (none found; `register`, declaration order, pre-guard pointer locals and chained assignments do not change candidate order).
A natural late use of command that emits no code yet keeps it a live candidate to the loop end ($a2) and blocks the unroll (only dead tests found; every live use emits code).
## Evidence
Frame: the 0x18 vs 0x10 difference is the saved s-register count (s0-s3 at 8-0x14 vs s0-s1); sp+0..7 is unused in both. A pad local does not restore it: the command variable in $a2 is what pushes the constants into s registers.
Colouring is bit-order (all "assigned (unconstrained)"): the register a candidate gets depends only on which earlier-bit candidates it interferes with. op = 0 is the only construct that can precede the cmdStart != cmdEnd test; command must stay a stored variable to the loop end for the ushr web to overlap the mask web (mask forbidden $v0 -> $a3).
Target (expected/build/src/global/17B90.o, 0x214-0x300): constants t2=0xFFFFFF, s3=-1025, s2=-513, s1=-1025, s0=1024, t5=0xD9000000, t4=-513, t3=512, t1=217; loop vars v1=w0/clear, t0=field w1, a3=w1 copy + clear mask, v0=shift/op/set mask, $a2 unused.
`bne v0,t1` at 0x260 (shift first), every mask compare constant-first: bne t3,a3 (0x27c), bne s0,a3 (0x298), bne t3,v0 (0x2b4), bne s0,v0 (0x2cc).
Set arm stores twice (sw t7,4(a0) then sw t9,4(a0) at 0x2bc/0x2c8): the `|=` then `&=` pair is behaviour.
Clear arm writes `~op | 0xD9000000` without re-masking (top byte becomes 0xFF): behaviour, not a typo to fix.

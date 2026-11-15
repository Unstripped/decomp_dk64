# vsprintf (boot, src/boot/3D20.c)
## Sites
boot:8000320C:noop-arith:9bc6c1 (98) `(c ^ 0) == '%'`: an isop compare operand puts the 37 constant on the left (bne a0,v1 at 0x1b4) without referencing the ucvt(*f) candidate. Bare `c` gives bne v1,a0 (1); `*f == '%'` gets the order right but raises ucvt(*f) adjsave 73.5->78.5 over len (78.0), so ucvt(*f) takes a0 and the constant moves to a1 (29).
boot:8000320C:dead-if:2829ec (291) zero-pad loop `if (width == 0) {}`: keeps the pad-loop 48 out of the prec-loop v0 constant web, so the target rematerialises li t7,48 per iteration (0x88c); removed: 48 joins the v0 web and the ring shifts (59). The one-line LAYOUT is needed (multi-line 4).
boot:8000320C:dead-if:u8169d (401) `if (space && space) {}` in the exp-sign else: ugen record at the else head puts the PRE-inserted exp/10%10 before the + store (li t9,43 / mfhi t7 at 0xccc/0xcd8); removed, t7/t9 swap (4). One-line LAYOUT needed (multi-line 6).
boot:8000320C:other:69d5aa / dead-if:e415e5 / dead-if:7dcd26 (368-374) e-arm trio: adds one uopt block to exp (-240vreg, savings 540, blocks 98->99) and to the CSE prec > 0 (ugeq prec,1, savings 150, blocks 27->28), so exp (5.45) outranks prec > 0 (5.36) and takes s3, prec > 0 s4; without it they swap (190). Subsets: d = width only removed 11, padChar test only 42, if (d) only 154.
boot:8000320C:dead-if:7dcd26#2 (407) `if (d) {}`: keeps d a uopt variable in v0 (mflo v0 / addiu v0,v0,48 / sb v0 at 0xd00); removed, exp/100+48 is a ugen t8/t6 temp and the ring shifts (55).
boot:8000320C:goto:u01010/u01010#2 numout, goto:u860d7/u860d7#2 ufetch: Q0591 shared tails (one jal _itoa at 0x700, one unsigned fetch chain); kept.
## Attempts
2026-11-12 round 27 CleanBoot3D20 opus:medium: all sweep rungs, diagnoses, permutes, reconstruct, goto-hand kept.
2026-11-14 Hackvsprintf opus:high: 2829ec loop shapes (59-66; trailing continue 0 = steer); u8169d count/arm/ternary/switch/bound forms (4-108), as1probe ugen stream diff; e-arm coupled rewrites (154-392).
2026-11-15 RereviewSmallFiles3 opus:high: six guarded do-whiles -> while loops in the e/f digit loops (fdiff 0).
2026-11-15 Hackvsprintf2 opus:high: removed the dead `c` stores (loop-top `c = *f`, copy-loop `c = *f`, `%%` arm `c = *++f` -> `f++` dropping its LAYOUT tag, `c = *f` before every break), `*buf++ = *f++`, `conv = *f++` -> fdiff 0. 9bc6c1: `*f == '%'` 29, `(c = *++f) == '%'` 1, `'%' == c` 1, `f[0]` 29, `c = f[1]; f++` 115, outer `while ((c = *f) != 0)` 377, else-arm `c = *f` 540. e-arm: subsets 11/42/154, pad counter in d 84 (+ `width = d` 46), loop-form flips of all 8 e-arm loops 190-220, rounding counter i2 107 / ascending d 201. 7dcd26#2: d = exp / 100 then + 48, chained store, c/i2 digit var: all 55. 2829ec multi-line 4; u8169d multi-line 6. gotos: u/o/x if-chain on conv 242; merged numeric case with if (conv == d || conv == i) 173. variants scan of every plain form: no improvement.
## Untried ideas
9bc6c1: `*f == '%'` plus a natural change that lowers ucvt(*f) adjsave by >= 0.5 (one fewer weighted *f reference in the outer loop) or raises len above 78.5 (uopt adjsave race; Q0766).
e-arm trio: any natural construct adding exactly one uopt block where exp and prec > 0 are both live, or starting exp later / prec > 0 earlier (Q0766, Q0767).
2829ec: a different-typed 48 constant in the pad loop so it forms its own web (Q0463).
## Evidence
0x1b4 bne a0,v1 / move v0,v1 (c), 0x160 li a0,37. 0x794 li v0,48 (prec loop web); 0x88c li t7,48 / sb t7 in the zero-pad loop. 0x9c4 move s3,zero (exp), 0xa1c slt s4,zero,t2 (prec > 0). 0xcc4-0xcf0 else-arm: div exp/10, li t9,43, sb, div, mfhi t7. 0xd00 mflo v0 / addiu v0,v0,48 / sb v0. One jal _itoa at 0x700.

# mainThreadHalt (global, src/global/0.c)
## Sites
global:805FB5C4:other:febcf9 other: `p = &D_807655E8; ... while (osGetTime() < *(q = p) + 0x22ADD7)`. The `q = p` copy turns the loop-body read of the u64 global into a native S-var load (lui/lw %lo at 0x3bc-0x3cc). Without it, `&D_807655E8` becomes one lda web (store at 0x360-0x36c plus both loop tests) coloured into $s0 (+sw s0 0x18(sp), frame 0x50). REMOVED in this unit.

## Attempts
2026-11-14 U HackmainThreadHalt claude-opus-5-5: sweep plain/recipe -> nohit (no rewrite/no removal)
2026-11-14 U HackmainThreadHalt claude-opus-5-5: plain `D_807655E8` in loop (a0) -> full=27 (lda web in $s0); +pad2[2] -> 25
2026-11-14 U HackmainThreadHalt claude-opus-5-5: `*p` loop read (b), `*p` store+read (c), p set after store (h), p before store (i) -> 20/20/21/20 ($s0 holds p in loop body only)
2026-11-14 U HackmainThreadHalt claude-opus-5-5: q = p before loop (d) -> 21; store via *p, read via global (g) -> 24
2026-11-14 U HackmainThreadHalt claude-opus-5-5: swapped compare (e), for-loop init (f) -> 27; while(1)+break (j) -> 50
2026-11-14 U HackmainThreadHalt claude-opus-5-5: `*(q = &D_807655E8)` / `*(p = &D_807655E8)` without p (r, s) -> 29; for-loop re-assigning p (t) -> 24
2026-11-14 U HackmainThreadHalt claude-opus-5-5: extern decl + definition after the function -> same as a0 ($s0)
2026-11-14 U HackmainThreadHalt claude-opus-5-5: file-scope `static u64 D_807655E8` -> same as a0 ($s0, .bss relocs)
2026-11-14 U HackmainThreadHalt claude-opus-5-5: permuter 900 s, -j 2, hack-free base = plain global form: base 1099, best 100 (it found the base steer again, `*(new_var = new_var2)`), no zero
2026-11-14 U HackmainThreadHalt claude-opus-5-5: function-local `static u64 D_807655E8` + pad[2]/pad2[4]/pad3[2] -> fdiff TEXT OK (exit 3), text words equal except LO16 immediates (.bss+0x4598 vs D_807655E8); KEPT

## Untried ideas
none for this site (removed). A name for the static (`sHaltStartTime`) once the naming phase runs.

## Evidence
- Frame 0x48: ra 0x14(sp), receivedMsg 0x20(sp) (osRecvMesg a1 at 0x328), timeConfig 0x34(sp) (struct copy 0x2c8-0x2f0, never read afterwards: real behaviour).
- 0x358-0x36c: jal osGetTime; lui at,%hi(D_807655E8); sw v0/v1 sharing `at` (TU defines the symbol, Q0415).
- 0x370-0x380 (pre-test) and 0x3bc-0x3cc (loop body): separate lui/lw %lo per word, no address register; 0x394/0x3e0 `addiu tN,tN,0` = high half of 0x22ADD7.
- No callee-saved register saved anywhere in the function.
- uopt (-zdbug:6): global form = uistr/uilod of lda {1066} (cand 25 assigned $s0); base hack = loop read as `isvar S 13 0`, lda cand `-ve save`; function-local static = `isvar S 70 0` with ustr/uadd(lod) only (no lda candidate).
- Copy object vs expected: objdump -drz equal except LO16 immediates at 0x364/0x36c/0x374/0x380/0x3c0/0x3cc (0x4598/0x459c addend in the word vs 0/4); .bss of both 0x45a0, D_807655E8 at .bss+0x4598 in expected.o; .data/.rodata identical.

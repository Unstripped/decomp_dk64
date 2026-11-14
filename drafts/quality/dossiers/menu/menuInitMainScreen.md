# menuInitMainScreen (menu, src/menu/3E10.c)
## Sites
8083be/35013b/3e828b/37e38b/26a14c (397-401) (void *)(s32)&D_80721444 arguments: KEPT.
- Only the cvt pair makes the address one CSE value that is spilled and reloaded (Q0704/Q0341).
- Any pointer spelling is an lda that uopt rematerialises per call.
## Attempts
- rounds 1-35 (opus:low, opus:xhigh): plain, array decay, s32 extern, void * local, as1probe, uopt traces, permutes (no natural form).
- 2026-11-14 HackmenuInitMainScreen (opus), full-file objdump diff lines: plain 198 diff lines; struct-typed extern 198; initialised void * local 198.
## Untried ideas
none in natural C. There is no integer source for the address (no .data table or field), and a loop is ruled out by the target.
## Evidence
Background: five unrolled calls (separate .rodata 1.2f literals 312-328(at) at 0xac8-0xb90); &D_80721444 lui/addiu once at 0xacc, sw a1,48(sp) 0xae4, lw a1,48(sp) 0xb18/0xb48/0xb78/0xba8; frame 0x38

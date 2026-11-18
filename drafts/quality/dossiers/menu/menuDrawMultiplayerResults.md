# menuDrawMultiplayerResults (menu, src/menu/3E10.c)
## Sites
menu:8002C634:other:872b9e other (removed 2026-11-17): `dl = dl;` after `q += 1;` in the guarded do-while tail; kept `move s4,v0` after `addiu s2,s2,1` (as1 order). Replaced by the natural `for` header increments.
menu:8002C634:dead-if:9a58bb dead-if (removed 2026-11-17): `if (i) {}` after the loop; raised the counter (s1) over the D_80033F20 cursor (s2) in colouring while the cursor was initialised first. Replaced by init order `i = 0, player = D_80033F20` in the `for` header.
## Attempts
2026-11-09..14 earlier units (CleanE4090, CleanMenu3E10, Rev16H/I, Rev17L, CleanMenu3E10b, PolishMenu3E10Names): plain/remove/cond/classify (class 2)/recipe nohit; uopt_trace (cursor/counter swap s1/s2 without the dead if), as1probe keep+scan (move s4,v0 one slot early without dl = dl, full=2), permuter runs (best=0 only re-inserting steers or reusing i in the gDPSetPrimColor word), a for-loop form (fdiff 1, spelling not recorded) -> all nohit.
2026-11-17 2026-11-17: cleanup CleanmenuDrawMultiplayerResults CleanmenuDrawMultiplayerResults anthropic/claude-opus-5-5: variants try of loop shapes. Do-while with both steers removed full=10; only dl = dl removed full=2; `q = D_80033F20; for (i = 0; ...; i++, q++)` full=9 shape=0 (only s1/s2 swap); `for (q = D_80033F20, i = 0; ...)` full=9; `i = 0; q = ...; for (; ...)` full=6 (move s1,zero scheduled above trunc.w.d f10/mfc1 s6); do-while with `i = 0; q = ...;` full=8 / with dl = dl full=6; increment orders in the do-while tail full=10..20; `for (i = 0, q = D_80033F20; i < D_80033878; i++, q++)` full=0 -> fdiff 0 (both sites removed). Review: 4 casts dropped (fdiff 0), locals renamed; isWinner inlined full=29, `x += step * 4` full=61, strBuf[16] full=10.
## Untried ideas
none needed for the hack sites (function has no hack site left).
Global names (cross-file, lead/types work): D_80033878 gMpResultsPlayerCount, D_80033F20 gMpResultsSlotPlayer, D_80033F24 gMpResultsPlayerSlot, D_8003387C gMpResultsSlotKong, D_80744524 gMpPlayerWins (evidence: menuInitMultiplayerResults 3E10.c).
## Evidence
Target 0x4824 (expected/build/src/menu/3E10.o): frame 0x150; s8 = &D_80033878 (0x48E4), s5 = step then step*4 (0x4914/0x4940), s0 = x, s6 = scaledY1, s7 = scaledY1 + 0x30 hoisted (0x4998), scaledY2 home sp+0x12C (0x4968), strBuf sp+0x64 (s3, 0x4954), s4 = dl, f20 = 0.6f.
Counter i = s1 (`move s1,zero` 0x4950), cursor = s2 (`lui/addiu s2` 0x4934/0x4944), guard `blez v1` on the divisor load (0x4994).
Loop tail 0x4A7C-0x4A9C: lbu t7,0(s8); addiu s1,s1,1; addu s0,s0,s5; sll t5,s0,16; slt at,s1,t7; addiu s2,s2,1; move s4,v0; bnez; sra s0,t5,16.
uopt_trace: i and the cursor have equal priority and colour by candidate bit (44 -> s1, 47 -> s2); bit order follows first appearance, so the init order in the for header decides it.

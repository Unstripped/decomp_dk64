# textBoxRowUpdateGlyphs (global, src/global/A8400_text_box.c; was textBoxRowUpdateNodes)
## Sites
global:806A4B84:other:66d3ed other: the guard and the add re-read glyph->fade (line 294-295) while the fade local holds it; uopt CSEs the reads into one lbu v1,2(s0) (0x157c) that carries usub/uadd, which colours step a0; with the local at every read (N2) or no local (N3) step takes v1 and fade a0.
## Attempts
2026-11-18b Polishglobal126260 claude-opus-5-5:xhigh: fade in the test with += (fdiff 1, +16 bytes); no fade local (fdiff 1, register swaps 0x1528-0x158c).
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: N2 fade local for test, headroom and store -> full=21 (fade a0/step v1, alpha v0/v1 swap 0x162c-0x164c); N3 control -> the identical full=21 diff.
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: N2 respellings: 0xFF - fade > step 21, step + fade 21, fade += step; glyph->fade = fade 21, block-scoped fade/step 21, local only in the add 3 (shape 1); variants scan of N2 (53) best 18.
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: N5 assignment in condition on base -> full=0 (same IR, keeps the re-reads), on N2 -> 21; N4 alpha reused -> 19 (all reads), 10 (test only).
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: permuter from the N2 base, 900 s -j 2 (base 105) -> 12 zeros, all with the guard and add re-reads restored (the tagged spelling); best output keeping fade there 50, via fade reused as an alias in the alpha MIN arm.
## Untried ideas
None left for a hack-free form: N1-N5 measured, permuter from N2 converges on the tagged spelling. Open: the N1 ruling (is the one-load re-read FAKE at all).
## Evidence
0x1514 li s6,255 hoisted; 0x1560/0x156c delay-slot lbu v1,2(s0) on the no-call paths, 0x157c lbu v1,2(s0) after textBoxRowStartHook; 0x1564 lbu t1,2(s0) separate hook test load.
0x1580 beql s6,v1; 0x158c li a0,150 (step), 0x1590 li t3,150; 0x15a0-0x15b4 step *= 0.5 as double with 0.5 in $f22/$f23; 0x15c0 subu t5,s6,v1; 0x15c4 slt at,a0,t5; 0x15cc addu t6,v1,a0; 0x15d4 sb t6,2(s0); 0x15dc li t7,255.
0x1630 lbu v1,2(s0) reload for the alpha MIN after the stores; .rodata+0x50 = 0x40611999A0000000 = (f64) 136.8f.
uopt -zdbug:6 base: cand 48 (uilod glyph->fade) v1, cand 54 (fade M -14vreg) v0, cand 60 (step M -8vreg) a0; N2: 54 v0, 60 v1, 48 v0, 57 (ucvt fade) a0.
9DD70 textMarkerUpdate 0x4adc-0x4b00: two source reads of gCurrentActor->fadeValue (no local), one lbu v0,351(a1) used by slt 0x4aec and addu 0x4af8.

# hudDrawCountPair (global, src/global/ACDC0.c)
## Sites
global:806AA09C:other:1e1cf9 other: raw PipeSync words avoided the gDPPipeSync macro's _g block local. The frame census (uopt_trace -l 5, `isvar M`) of the base body has three block/temp words below buf2: gSPMatrix _g (-156 = sp+0x54), the cfe hidden temp of the nested textDrawStringVtx call and gSPPopMatrix _g (-160/-164 = sp+0x50/0x4C, both stored from v0); the (f32)x/(f32)y spills sit just below at 0x48/0x44. FIXED 2026-11-17f (CleanhudDrawCountPair): the two calls written as sequential `dl = textDrawStringVtx(dl, ...)` statements drop the hidden temp (Q0522) and gDPPipeSync(dl++) takes that word (-164 = sp+0x4C, stored from dl+8); fdiff 0.
## Attempts
2026-11-10..12 (low, medium): macro forms, permutes (behaviour-changing buffers)
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: gDPPipeSync(dl++) / (dl); dl++ (4), block-scoped sprite locals (33), named f32 x/y at 7 positions (40-43), buf order (8)
2026-11-17e 2026-11-17: cleanup HackhudPauseMenuRender13 HackhudPauseMenuRender13 anthropic/claude-opus-5-5 (base ff2f08b4, u32 siz prototype from 62d6133d): gDPPipeSync(dl++) 4 (re-measure), gDPPipeSync(dl); dl++ 4, s16 w with the macro 4, raw form moved to gSPPopMatrix with the PipeSync as macro 2 (w0 first) / 5 (w1 first), moved to gSPMatrix 3; variants scan of the macro copy (19) none below 4. Review: heapAlloc(0x40) -> heapAlloc(sizeof(Mtx)), fdiff 0.
2026-11-17f 2026-11-17: cleanup CleanhudDrawCountPair CleanhudDrawCountPair (base f34af09e): frame census of the base body via uopt_trace -l 5 (5 M words: mtx -4, w -8, -156, -160, -164; -160/-164 both stored from v0 = the nested-call cfe temp and the PopMatrix _g). Nested textDrawStringVtx split into two `dl = textDrawStringVtx(dl, ...)` statements + gDPPipeSync(dl++) -> full=0, fdiff 0 (FIXED); same split with the raw PipeSync words -> full=37 (control: the freed word moves the spills up). variants scan of the fixed copy: 8 natural zero variants (swaps, float suffixes, w as s8/s16), none needed. Review nohit.
## Untried ideas
none (site fixed; no hack left in the function)
## Evidence
swc1 $f0,72(sp) at 0x20b8 and $f2,68(sp) at 0x20c4 (float x/y spilled across the matrix calls, reloaded at 0x21ac/0x21b8).
Frame 0xF0: mtx 0xEC (lw a1,236(sp) at 0x20e0/0x20f4), w in s0 (home word 0xE8, -8vreg), m1 0xA8 (addiu a0,sp,168), m2 0x68 (addiu a1,sp,104), buf1 0x60 (addiu a0,sp,96 at 0x2114), buf2 0x58 (addiu a0,sp,88 at 0x2120); three block/temp words 0x54/0x50/0x4C, spills directly below at 0x48/0x44.
Second textDrawStringVtx takes the first one's result directly (move a0,v0 at 0x2164): no stack round trip, so the hidden temp word is pure frame cost.
PopMatrix stored w1 then w0 (sw t9,4(v0) / sw t8,0(v0) at 0x2198/0x219c); PipeSync w0 then w1 (sw t0,8(v0) / sw zero,12(v0) at 0x21a4/0x21a8) = the gDPNoParam macro order.

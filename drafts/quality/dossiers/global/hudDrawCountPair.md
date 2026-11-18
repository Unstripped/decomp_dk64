# hudDrawCountPair (global, src/global/ACDC0.c)
## Sites
global:806AA09C:other:1e1cf9 other: raw PipeSync words avoid the gDPPipeSync macro's _g block local; the 0xF0 frame holds exactly two block words (gSPMatrix, gSPPopMatrix) between buf2 (0x58) and the guTranslateF x/y float spills (0x48/0x44); a third _g moves the spills to 0x44/0x40 (KEPT, FAKE note made concrete 2026-11-17e)
## Attempts
2026-11-10..12 (low, medium): macro forms, permutes (behaviour-changing buffers)
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: gDPPipeSync(dl++) / (dl); dl++ (4), block-scoped sprite locals (33), named f32 x/y at 7 positions (40-43), buf order (8)
2026-11-17e 2026-11-17: cleanup HackhudPauseMenuRender13 HackhudPauseMenuRender13 anthropic/claude-opus-5-5 (base ff2f08b4, u32 siz prototype from 62d6133d): gDPPipeSync(dl++) 4 (re-measure), gDPPipeSync(dl); dl++ 4, s16 w with the macro 4, raw form moved to gSPPopMatrix with the PipeSync as macro 2 (w0 first) / 5 (w1 first), moved to gSPMatrix 3; variants scan of the macro copy (19) none below 4. Review: heapAlloc(0x40) -> heapAlloc(sizeof(Mtx)), fdiff 0.
## Untried ideas
none natural (every local addition or macro adds the word; the buffers are pinned at 0x60/0x58). Open question for the lead: whether the frame evidence (two _g words, spills at 0x48/0x44) is enough for `// ORIG` on the raw PipeSync words.
## Evidence
swc1 $f0,72(sp) at 0x20b8 and $f2,68(sp) at 0x20c4 (float x/y spilled across the matrix calls, reloaded at 0x21ac/0x21b8).
Frame 0xF0: mtx 0xEC (lw a1,236(sp) at 0x20e0/0x20f4), w in s0, m1 0xA8 (addiu a0,sp,168), m2 0x68 (addiu a1,sp,104), buf1 0x60 (addiu a0,sp,96 at 0x2114), buf2 0x58 (addiu a0,sp,88 at 0x2120); spills sit 8/12 bytes below the lowest local.
PopMatrix stored w1 then w0 (sw t9,4(v0) / sw t8,0(v0) at 0x2198/0x219c); PipeSync w0 then w1 (sw t0,8(v0) / sw zero,12(v0) at 0x21a4/0x21a8).

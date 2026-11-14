# hudDrawCountPair (global, src/global/ACDC0.c)
## Sites
global:806AA09C:other:1e1cf9 other: raw PipeSync words avoid the gDPPipeSync macro's _g block local, which costs a frame word (spills 0x48/0x44 -> 0x44/0x40) (KEPT)
## Attempts
2026-11-10..12 (low, medium): macro forms, permutes (behaviour-changing buffers)
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: gDPPipeSync(dl++) / (dl); dl++ (4), block-scoped sprite locals (33), named f32 x/y at 7 positions (40-43), buf order (8)
## Untried ideas
none natural (every local addition or macro adds the word)
## Evidence
swc1 $f0,72(sp) at 0x20b8 and $f2,68(sp) at 0x20c4 (float x/y spilled across the matrix calls, reloaded at 0x21ac/0x21b8).

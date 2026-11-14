# textDrawStringVtx (global, src/global/100180.c)
## Sites
- global:806FC530:other:1e50d1 other: TEXT_GFX_CMD writes each command through function-scope Gfx temps (9 names, g8 shared by 4 commands). The registers match gbi block `_g`; what the temps really provide is stack layout: the unused words at 0xb0-0xb8 and 0x84-0xa8 in the 0xc8 frame.
- global:806FC530:dead-if:ae146d dead-if: `if (w4) {}` is a block boundary so v0 holds yoff+y+h4-1 (0x148c) and then gx+w (0x149c). Classified class 1.
- global:806FC530:other:d481a0 other: the 4x `vp++` keep vp in s1 and gx in s2; `vp += 4` swaps them.
- global:806FC530:dead-store:cdb041 / cdb041#2 dead-store: `i = count /= 4` keeps count in s8 with the quad counter in scratch a3 (0x1564 `addiu a3,t7,-1`, 0x172c).
## Attempts
- rounds 9-32 (opus:low): see quality history (53 events). Summary: gbi block _g with gN/pads kept (frame 0x100 / 0xd8); vp += 4; i = count / 4; permute x4; reconstruct x2.
- 2026-11-14 U HacktextDrawStringVtx (opus:high), each scored with variants.py try (full=):
  - gbi block _g, gN + pads dropped: 74. In a whole-file fdiff it is registers identical; only 68 sp offsets differ, plus frame 0xd0 vs 0xc8.
  - one shared Gfx temp + s32 pads: 160
  - direct dl->words writes: 178
  - gbi vtx/quad only: 130
  - vp = &vp[4], vp = vp + 4, vp += 4: 35 each. Per-vertex vp-> walk: 77-89.
  - variants scan on the vp += 4 copy: no improvement on 35
  - quad loop with count as the counter after the divide: `while (count-- > 0)` 8 (best), `--count >= 0` 21, `for (count /= 4; count-- > 0;)` 28, `for (count = count / 4 - 1; ...)` 33, `count--` in the body 39
  - i-counter for-loops from count / 4: 329 / 332. Plain `i = count / 4`: 324.
  - `count /= 4; i = count;`: 0, but it is the tagged data flow
  - reconstruct gbi + count counter + vp += 4 + no w4 guard: 336. gbi + count counter alone: 95.
## Untried ideas
- Find out where IDO 5.3 places block-scoped locals relative to function-scope ones (one probe in a scratch TU). If a block declared earlier in source took a slot above later function-scope locals, a mix of gbi macros and declaration order could fill 0xb0-0xb8 / 0x84-0xa8 with `_g` slots (frame evidence above).
- count-counter form (full=8): find what moves the decremented counter from s8 to a scratch register while keeping `blez` on the quad count (uopt trace of the c2 copy; Q0557's loop-weighted reference to count).
- dead-if ae146d: a real statement boundary between the vp[1].ob[2] and vp[1].tc[0] stores.
## Evidence
- frame `addiu sp,sp,-0xc8`
- slots used: args 0xcc-0xdf; line 0xc7, idx 0xc6, ch 0xc5, startX 0xc2, strStart 0xbc, batch 0xac, leftPad 0xab, center 0xaa, started 0xa9, yoff 0x83, h4 0x7e, w 0x7a, h 0x78
- spills at 0x50 / 0x58 (t3 around every call) / 0x5c
- unused: 0xb0-0xb8, 0x84-0xa8, 0x60-0x77
- quad loops at 0x1550-0x15d0 and 0x1718-0x1798:
  - `sra t7,s8,2` (signed /4, no store back to s8), `blez t7`, `addiu a3,t7,-1`
  - LFTR test `slti t1,v1,14` with v1 -= 8
  - after the loop `move s8,zero`
- vertex block at 0x1478-0x1500: `addiu s1,s1,64` in the delay slot of `beqz s7` (flags & 0x32 hoisted into s7 at 0x1420)

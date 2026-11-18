# gfxDrawTexturedTileGrid (global, src/global/103AB0.c)

## Sites
- global:807024E0:other:89672b other (fixed 2026-11-17): `rowT = v;` row-top copy; without it the (s16)v chain is an early candidate and is built at the head of the x-loop preheader (sll t7,a0,16; sra t9 at 0x3ba8) instead of from the copy register a0 at 0x3c08 (norowT+pad: 638 diff lines)
- global:807024E0:other:732a72 other (fixed 2026-11-17): `colS = u;` cell-left copy; without it the (s16)u temp is an early candidate (ucvtl{u} bit 452 vs 542 through the copy) and takes slot 180(sp) instead of 136(sp) (sw a1 at 0x4278, lh a1 at 0x44d8), pushing x+tw from 180 to 164 (nocolS+pad: 10 diff lines)

## Attempts
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (bitSize) in source order 8/0x10/0x20/4 or sorted 4/8/0x10/0x20, with both copies, without rowT, without colS, without both: 408-716 diff lines (the copies alone stay at 754/3200 as recorded)
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (bitSize) with colS removed: 601 (source order) / 593 (sorted)
- 2026-11-17 cleanup CleangfxDrawTexturedTileGrid anthropic/claude-opus-5-5: copies as per-role locals: the vtxCallback calls read the cell-edge copies too (callbacks 1/4 colS for u, 1/2 rowT for v), so each copy is used at every use of its role -> variants try full=0 (colS only, rowT only, both), fdiff 0; renamed u/v/ustep/vstep/colS/rowT/ua/vb -> posX/posY/stepX/stepY/left/top/right/bottom, fdiff 0, both tags dropped
- 2026-11-17 cleanup CleangfxDrawTexturedTileGrid anthropic/claude-opus-5-5: right/bottom from the copies instead of the cursors: bottom = (s16)(top + stepY) full=110, right = (s16)(left + stepX) full=735, both 514
- 2026-11-17 cleanup CleangfxDrawTexturedTileGrid anthropic/claude-opus-5-5: widths: s16 right/bottom without casts full=829, s16 left/top full=187, all four s16 full=825, s16 right/bottom with casts full=829
- 2026-11-17 cleanup CleangfxDrawTexturedTileGrid anthropic/claude-opus-5-5: copy dropped with an s32 pad in its slot: colS 10 diff lines (slots only), rowT 638, both 644

## Untried ideas
- none open: no hack sites left

## Evidence
- vtxSetPosTex(vtx, s16 x, s16 y, s16 s, s16 t, u8 shift) writes ob[0]/ob[1] from x/y and tc[] from s/t << shift: posX/posY (texScale * s0/t0 + steps) are screen positions, xf/yf/xa are the texture S/T; the old names colS/rowT/u/v read as texture coordinates
- the bitSize ladder is a real else-if chain: the target reloads the byte for every compare (bne t9,8 at 0x3cb8, bne t8,0x10 at 0x3dfc, bne t7,0x20 at 0x3f44, bne t8,4 at 0x408c, in source order), which a switch (one load, one selector register) cannot give
- row top: posY lives in a1 and its home 452(sp) (sw a1 at 0x3b38, callbacks lw a1,452(sp) at 0x424c/0x4334); the top copy is a0 (move a0,a1 at 0x3b3c), from which (s16)top (sll t6,a0,16 at 0x3c08 -> 104(sp)) and bottom (addu v1,a0,t9 at 0x3bc0) are built late in the preheader
- cell left: (s16)left is lh a1,458(sp) from posX home 456 at 0x425c, spilled to 136(sp) at 0x4278 and reloaded lh a1,138(sp) at 0x44d8; x+tw is the 180(sp) temp (sw t8 at 0x4324, lw s5 at 0x4540)
- uopt_trace -l 5: with the copy ucvtl{1101} (s16 u) is bit 542 (created by copy propagation of colS, after x+tw at 464); without it bit 452, before x+tw: spilltemps gives the lower bit the higher slot (Q0521, Q0888)
- callbacks take the cell-edge values through an unprototyped pointer (void (*)()), so plain s32 reads: reading the copy or the cursor there is codegen-identical (copy-substituted back, no new candidate), while an expression operand moved onto the copy (right/bottom) changes its chain bit

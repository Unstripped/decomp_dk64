# modelSlotBuildTriangleBuffer (global, src/global/36880.c)
## Sites
global:80633A1C:dead-store:1b07df dead-store: `off = slot * 0x90;` gave the umpy slot*0x90 the first candidate number so it coloured $v0 before the gModelSlots load ($v1); removed 2026-11-17 (statement order lastBone, buf, anim).
## Attempts
2026-11-09..11-13 (rounds 1-35, see `quality.py history`): comma/noop-arith sites fixed (Rev15A permuter, Batch12 typed ModelAssetTri); dead-store site: Rev17M removal (v0/v1 swap), 606 s and 660 s permuter nohit; Rev11D natural anim-first + `ModelSlot *ms` (830).
2026-11-17 2026-11-17: cleanup CleanmodelSlotBuildTriangleBuffer CleanmodelSlotBuildTriangleBuffer anthropic/claude-opus-5-5: dead store removed, statements reordered `lastBone = -1; buf = &gModelSlots[slot].unk48; anim = gModelSlots[slot].unk78;`, `off`/pad2/pad3 -> `s32 pad[2];` -> fdiff exit 0. Orders alb/lab 7, abl 11, bal/bla 4; `s32 pad` 26, `pad[2]`/`pad[3]` 0.
## Untried ideas
none open (no hack sites left). Optional polish: `heapAlloc(count * sizeof(CollisionTriF))` also scores full=0 (not applied; the file uses hex sizes).
## Evidence
- 0x1ea0-0x1eb0: `lui/lw v1,gModelSlots`, `v0 = (slot*9)<<4`; 0x1ee4 `addu t6,v1,v0` + `lw a2,0x78(t6)` (anim, base first); 0x1eec `addu s6,v0,v1` + 0x1efc `addiu s6,s6,0x48` (buf, offset first): two separate address computations, the product in $v0.
- uopt_trace -l 6 (.scratch/CleanmodelSlotBuildTriangleBuffer/try/*.l6): `&gModelSlots[slot].unk48` lowers to `uadd{umpy}{uilod gModelSlots}`, `gModelSlots[slot].unk78` to `uixa{uilod gModelSlots}{umpy}`. Equal-priority colouring follows candidate number (first appearance): buf-first numbers umpy 7 / load 8 -> umpy reg 1 ($v0); anim-first numbers load 2 / umpy 5 -> swapped. Base copy (dead store) numbered umpy 4 / load 8.
- Offset-table reads: `data->unk60 + (u8 *)data` etc. are offset-first in the target (`addu t2,t1,s3` at 0x1f24, `addu t0,t9,s3` at 0x1f5c, `addu s1,t9,s3` at 0x1fdc); each base-first spelling scores full=1.
- Frame 0x180 needs two unused words beside the declared locals (one `s32 pad` gives full=26).

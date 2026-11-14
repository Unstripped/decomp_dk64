# menuEvaluateSelectorSpline (menu, src/menu/3E10.c)
## Sites
- menu:8003155C:dead-if:67f711 dead-if: steered spill slot order (pointer-scale temp t0 at sp+0x2c, row address a3 at sp+0x28). FIXED.
- menu:8003155C:other:2943a1 other: (u8 *) byte-offset first spline arg, kept t1+t0 apart from the uixa row address a3. FIXED.
- menu:8003155C:other:38cdcd other: same for the D_8003378C arg (t0 + rematerialized base). FIXED.
## Attempts
- 2026-11-14 U HackmenuEvaluateSelectorSpline anthropic/claude-opus-5-5:high: D_8003373C + index / D_8003378C + index args with index *= 4 -> full=4 (only spill slots 0x28/0x2c swapped); &D[index] args full=93; (u8 *)D + index * 4 / * sizeof(f32) full=27; f32 *x, *y pointer locals assigned before the stores -> slot order right but frame +8 (full 7-9); one reused pointer local / block-scoped locals full 9-13; f32 [5][4] row arrays full 85-89; index = index * 4 full=4; index += index * 3 full=10; index <<= 2 -> fdiff 0. Row-0 check: if (index == 0) fdiff 0, if (ret == 0) full=30.
## Untried ideas
- none: all sites fixed.
## Evidence
- Target 0x9784-0x97e0: t7 = s0 << 2; v1 = t7 << 2 (uixa offset, shared by v0 = &D_8003378C row and a3 = &D_8003373C row); t0 = t7 << 2 recomputed for the call args; sw t0,0x2c(sp) / sw a3,0x28(sp); ret in its home sp+0x30.
- uopt trace (-zdbug:6): with index *= 4, ushl{index}{2} is candidate bit 28 after uixa bits 16/17; with index <<= 2 it is bit 14, before uixa bits 17/18, so spilltemps gives it the higher slot (Q0342, Q0521).
- cfe lowers ptr + int to ushl/uadd and &a[i] to uixa: the two never CSE, which is the target split between stores and call args.

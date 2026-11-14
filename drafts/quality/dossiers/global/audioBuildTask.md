# audioBuildTask (global, src/global/6710.c)
## Sites
global:80601EE4:noop-arith:8e31ef / 8e31ef#2 `count = (count & 0) + 2;` in the two aiLen arms. Mechanism (uopt_trace): with the hack the arm is ustr{count}{2} + uistr{holdFrames}{count}: the store reads count (var {1536}, -24vreg, adjsave 4.0, coloured v0), so ugen emits li v0,2 / sw v0. A plain `count = 2` is constant-propagated into the store (uistr{holdFrames}{2}); count = 2 becomes dead and ugen materialises the 2 in the t-ring (li t0,2 / li t2,2), shifting every later ring temp by two (58 lines). uopt copy-prop refuses to forward increments (is_incr) and ilod expressions (Q0510's find_replacements list); the hack is read as an increment of count and only folds to 2 after copy-prop.
## Attempts
2026-11-10 round 10 Rev10B: diagnose (uistr{holdFrames}{2}), reconstruct (direct D_80770558[0] = 2: address CSE into a0), permute (& 0xFFFFu masks).
2026-11-12 round 19 Rev19B diagnose; Perm19 permute best 35/30 (pad + & 0xFF).
2026-11-14 HackaudioBuildTask opus:high:
- count widths s16/u16/s8/u8/u32 (58-77); `*holdFrames = count = 2` (58); `*holdFrames = 2` (58); store then reload count (53).
- `count += 2` (count is 0 on both paths): 2 lines (addiu v0,v0,2 instead of li v0,2) - right registers, wrong instruction.
- count = 2 before the sampleCount store, and a block between def and store: 58 (propagation is global).
- single store after the if/else chain (store reached by several defs of count): li v0,2 and every ring temp right, but the unconditional store adds a path (102 lines).
- direct global forms on D_80770558[0] (if / else if / else, `--`, `- 1`, pointer `(*holdFrames)--`): 103-113.
- variants.py scan on the hack-free body: 27 recipes, best 58.
- permuter perm_plain (hack-free body): 900 s, baseline 390, best 200 (output-200-1 moves count = 2 above the if and stores the loaded 0 in the first arm: a behaviour change, unusable); no zero.
## Untried ideas
none that keep the per-arm stores: the target needs a store whose operand is count with count = 2 as its only reaching def, which uopt always propagates unless the def is an increment.
## Evidence
Target 0x538-0x5a8: lui v0; lw v0,0(v0) (count = *holdFrames); bnez v0; lw t9 (D_8077019C); li v0,2; lui at; sh t9,4(s0); b 0x5ac; sw v0,0(at). Second arm 0x564-0x590 same with t0. Third arm li t1,736; beqz v0; addiu v0,v0,-1; sw v0.

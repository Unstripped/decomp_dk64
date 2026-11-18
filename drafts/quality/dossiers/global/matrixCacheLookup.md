# matrixCacheLookup (global, src/global/61AA0.c)

## Sites
global:8065E138:other:332352 other: `node = NULL;` before `return &lights[lightCount];` (FIXED 2026-11-17 CleanmatrixCacheLookup). Without it uopt copy-propagated `lights = node->lights` (node + 48) into the return and reassociated it to `((lightCount << 6) + node) + 48` (`beqzl v1; addu v0,t7,t1` then `addiu v0,v0,48`), losing the target's separate `addiu a0,t1,48` (0x17f8) and `addu v0,t7,a0` (0x186c). The redefinition made node + 48 unavailable in the return block, so the var `{189|0}` (-28vreg, cand 239) lived 71 -> 77 in uopt reg 3 (a0).

## Attempts
2026-11-10 round 9 CleanGlobal61AA0 anthropic/claude-opus-5-5:low: diagnose/permute on the removal -> nohit.
2026-11-11 round 17 Rev17N anthropic/claude-opus-5-5:low: removal -> trace length same, node->sub forwarded into the return; permute best 110.
2026-11-12 round 30 Rev30A: uopt_trace keep vs removed, same 81 blocks, colouring differs; permute best re-adds node = node->hashNext in the hit path.
2026-11-13 round 38 CleanGlobal61AA0 anthropic/claude-opus-5-5:xhigh: keep colours {189|0} lr 239 in reg 3; perm_node2 output-0-1 re-adds node = node->hashNext before the return.
2026-11-17 CleanmatrixCacheLookup anthropic/claude-opus-5-5: plain removal fdiff 5 lines; `return lights + lightCount`, `&node->lights[lightCount]` inline, lights = &node->lights[lightCount] early: 5 each; separate `void *`/`Vtx *` return local: 5; lever e (`lights = &lights[lightCount]; return lights;`, `lights += lightCount`, `lights = lightCount + lights`, u8 * and void * data locals, function-top declaration): 2 (a0 -> a1; `+=` also flips the addu to a1,t7). Trace: node + 48 becomes expression cand 241 (adjsave 1.0) but the dead var {189|0} cand 239 (adjsave 1.5, dead stores in bb 71 and 77) colours a0 first. lights = node->lights above the compare loop with `cached = &lights[i]`: 1 (addu v1,t9,t1 at 0x14c0, offset-first; `lights + i`, `i + lights`, `&node->lights[0]` same); `cached = lights; cached += i;` 0 (operand-order steer, rejected). FIX: lights above the compare loop and every compare read `lights[i].f` inline, no cached local -> fdiff 0, clint uninit 0, warnings 0.

## Untried ideas
none open: the site is fixed.

## Evidence
0x14c0 `addu v1,t1,t9` (node + (i << 6), base-first) then `addiu v1,v1,48`: the compare loop indexes node->lights base-first, which only inline `p[i].f` reads give once the address is a local (Q1223).
0x17f8 `addiu a0,t1,48` in the hit block, 0x186c `addu v0,t7,a0` in the return block (`b` delay slot to the shared epilogue at 0x1880): node + 48 is one value held in a0 across the move-to-front blocks; with lights used in the loop it is the cross-block expression candidate {1549|0} (cand 63, adjsave 0.67, Q0510) coloured uopt reg 3.

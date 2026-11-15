# mapSaveSlotAndTransition (global, src/global/3C10.c)
## Sites
global:805FF9AC:other:39a5c7 other: `k = 1; D_80750ACC = k; ... D_8076A160[i].inUse = k;` makes one `li a2,1` (0xed8) feed both `sb a2,D_80750ACC` (0xee0) and `sb a2,0(s1)` (0xf18, after the heldActor if/else join).
## Attempts
2026-11-14 U HackmapSaveSlotAndTransition anthropic/claude-opus-5-5:high: variants try, scores vs base: literal 1 in both stores 11; literal with D_80750ACC store after the playerState load 10; `inUse = D_80750ACC` read-back (store-to-load forwarding) mismatch +2 insns: IDO builds &D_80750ACC in a2 and emits `lb t6,0(a2)`, it does not forward the stored 1; slot pointer local for the tail 40; chained `inUse = D_80750ACC = 1` at the join 19. variants scan: no ZERO beyond operand swaps/widths. sweep: 0 hits.
2026-11-13 Rev27 (history): literal rematerialises li per store; permuter only zero is pad = 1 carrier (steer swap).
2026-11-11 Rev16I (history): permuter best=0 moves the carrier to pad (Q0634).
2026-11-10 Clean3C10 (history): permuter found=1 carrier reuse.
## Untried ideas
- A local with several defs that is naturally 1 at the end (Q0789: only a join store reached by several defs keeps the variable's register); no such meaning-bearing local is visible in the asm (found/i are dead or in s1).
- Callers/neighbour code in 3C10.c that set D_80750ACC elsewhere (spelling there might reveal an original idiom).
## Evidence
- 0xed8 `li a2,1` sits in the loop-exit block before `lw t2,gPrimaryPlayerActor`; a2 is a caller-saved reg live only to 0xf18, no call in between.
- 0xee0 `sb a2,%lo(D_80750ACC)(at)` precedes `lw v0,0x174(t2)` (customState), so source order is D_80750ACC store before playerState load.
- 0xf18 `sb a2,0(s1)` is the join block after `beqz v1` (heldActor) – a chained store cannot produce the split placement.

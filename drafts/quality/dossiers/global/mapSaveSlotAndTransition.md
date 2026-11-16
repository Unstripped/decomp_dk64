# mapSaveSlotAndTransition (global, src/global/3C10.c)
## Sites
global:805FF9AC:other:39a5c7 other: `k = 1; D_80750ACC = k; ... D_8076A160[i].inUse = k;` makes one `li a2,1` (0xed8) feed both `sb a2,D_80750ACC` (0xee0) and `sb a2,0(s1)` (0xf18, after the heldActor if/else join).
## Attempts
2026-11-16 U HackmapSaveSlotAndTransition2 anthropic/claude-opus-5-5:high: uopt trace (-l 6): k web {1117} gets ustr k,1 + uistr slot,k, live range colored a2. variants try: dedicated s32 local appended after playerState 29 (frame 96 vs 88 only: IDO reserves a slot per declared local); same local in place of `s32 pad` 0 (fdiff 0); u8/s8/s16 in that slot 11; `s32 saved = TRUE` initializer 11; literal 11. Kept: `s32 saved` in pad's slot, `saved = TRUE; D_80750ACC = saved; ... inUse = saved;`; also dropped the void* cast on customState. sweep on final copy: no sites.
2026-11-14 U HackmapSaveSlotAndTransition anthropic/claude-opus-5-5:high: variants try, scores vs base: literal 1 in both stores 11; literal with D_80750ACC store after the playerState load 10; `inUse = D_80750ACC` read-back (store-to-load forwarding) mismatch +2 insns: IDO builds &D_80750ACC in a2 and emits `lb t6,0(a2)`, it does not forward the stored 1; slot pointer local for the tail 40; chained `inUse = D_80750ACC = 1` at the join 19. variants scan: no ZERO beyond operand swaps/widths. sweep: 0 hits.
2026-11-13 Rev27 (history): literal rematerialises li per store; permuter only zero is pad = 1 carrier (steer swap).
2026-11-11 Rev16I (history): permuter best=0 moves the carrier to pad (Q0634).
2026-11-10 Clean3C10 (history): permuter found=1 carrier reuse.
## Untried ideas
- (2026-11-16) none left for the removed site; if a reviewer rejects the role-named constant local as a steer, the only other route is a multi-def flag whose last def is the 1 after the chunk loop (none found: found/i/flags/returnExitIndex are dead or reused there).
- A local with several defs that is naturally 1 at the end (Q0789: only a join store reached by several defs keeps the variable's register); no such meaning-bearing local is visible in the asm (found/i are dead or in s1).
- Callers/neighbour code in 3C10.c that set D_80750ACC elsewhere (spelling there might reveal an original idiom).
## Evidence
- Frame 88: with k reused the base needed `s32 pad` between b and playerState; a dedicated local in that slot keeps the frame, an extra one grows it to 96 (an s32 slot per local, 8-aligned).
- Only an s32 carrier keeps the a2 web; a u8/s8/s16 local or a def at the declaration is copy-propagated (Q0789, Q0402).
- 0xed8 `li a2,1` sits in the loop-exit block before `lw t2,gPrimaryPlayerActor`; a2 is a caller-saved reg live only to 0xf18, no call in between.
- 0xee0 `sb a2,%lo(D_80750ACC)(at)` precedes `lw v0,0x174(t2)` (customState), so source order is D_80750ACC store before playerState load.
- 0xf18 `sb a2,0(s1)` is the join block after `beqz v1` (heldActor) – a chained store cannot produce the split placement.

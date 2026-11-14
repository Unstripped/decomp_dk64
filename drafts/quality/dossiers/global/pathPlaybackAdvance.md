# pathPlaybackAdvance (global, src/global/127B00.c)
## Sites
global:80723484:dead-if:6354a6 dead-if: the folded `path == 0` comparison contributes constant -4 web 203 so pb web 13 and constant -1 web 201 remain constrained and take v0/v1.
global:80723484:dead-if:0106d1 dead-if: the block split keeps the remainder in t8 and copies it to the pointIndex web in a3 at target +0x418.
global:80723484:dead-if:f5ff39 dead-if: the repeated tq use keeps `quot + 1` in v1 at target +0x3DC and +0x430.
## Attempts
2026-11-14 cleanup retry HackpathPlaybackAdvance openai-codex/gpt-5.6-sol: quality sweep reran 48 checks -> 0 hits.
2026-11-14 cleanup retry HackpathPlaybackAdvance openai-codex/gpt-5.6-sol: removed singles/pairs/all; scores r1=299, r2=5, r3=93, r12=203, r13=299, r23=7, r123=301 -> no fdiff hit.
2026-11-14 cleanup retry HackpathPlaybackAdvance openai-codex/gpt-5.6-sol: level-5/6 uopt traces showed the path test adds folded -4 web 203; without it pb and -1 each lose the 22-neighbour constrained colouring threshold -> nohit.
2026-11-14 cleanup retry HackpathPlaybackAdvance openai-codex/gpt-5.6-sol: 511 selective `path->count` rewrites, 32 path count/points rereads, local elimination combinations, quotient/tq widths and spellings -> nohit.
2026-11-14 cleanup retry HackpathPlaybackAdvance openai-codex/gpt-5.6-sol: permuter on the r23 body found a named `s32 *pointIndex`; natural rewrite reduced the pb-guard removal from five differences to one (`move v1,t8` vs target `move a3,t8`). All 21 single pointer uses, 210 pairs, 127 direction-1 subsets, declaration/assignment positions and count-pointer combinations -> nohit.
2026-11-14 cleanup retry HackpathPlaybackAdvance openai-codex/gpt-5.6-sol: permuter connection ended after 239 seconds; best score 15, so no permute event is recordable.
## Untried ideas
A real shared type or source construct that introduces the target's folded -4 web without a dead pointer test (current evidence does not identify one).
A natural use that makes the pointIndex field web and tq web interfere across the loopMode switch without adding dead work.
## Evidence
Target +0x38 computes `path` as `addiu a0,v0,4`; the path-null test emits no instruction but uopt trace shows its folded -4 constant as web 203.
With all steers present, pb web 13 and -1 web 201 are constrained first and receive colours 1/2; deleting the path test makes both unconstrained.
Target +0x3EC is `mfhi t8`, +0x3F0 stores t8 to pointIndex, +0x418 copies `t8` to `a3`, and +0x41C tests `t8`.
Target +0x3DC computes `addiu v1,a2,1`; target +0x430 tests v1. Without the tq test those instructions use t5.
Related knowledge: Q0397, Q0589, Q0601, Q0602, Q0608.

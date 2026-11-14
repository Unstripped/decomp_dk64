# actorNodeRingUpdate (global, src/global/C1E70.c)
## Sites
global:806BD3E4:dead-if:35ea4a dead-if: made -1 a cross-block constant web (bb45 compare, bb47 store) coloured v0 for the reset store at 0x604 (FIXED)
global:806BD3E4:other:344bc1 (base 43319b) other: pointer local seqPos for every ring-check access of D_807506B4; without it &D_807506B4 is a coloured address in t1 and the t-reg ring shifts from 0x2b4 (KEPT, tagged)
## Attempts
2026-11-12 r27 CleanGlobalC1E70 opus-5-5:low: diagnose both, perm_deadif and perm_cnt (no hack-free hit)
2026-11-14 HackactorNodeRingUpdate opus-5-5:high: -1 respellings with the cnt load kept (n = -1; D = n / D = n = -1 / one-case switch / D = D_807506A8[n] / < 0 test) -> 2-39; join store after the if (w4) gives li v0,-1 but drops the early n+1 store -> 6; direct-global increment forms -> 91-95 (address CSE in t1); pointer local for every access with (*seqPos)++ -> 0 text, relocation table order of D_807506A8/D_807506B4 at 0x580-0x58c swapped (fdiff 3, --reloc-ok OK, objdump -drz identical)
## Untried ideas
order of the region-entry reglod vs the coloured &D_807506A8 init (target emits the D_807506A8 lui/addiu reloc first): lowering the promoted global's priority without a dead test
## Evidence
0x580 lui v0 / 0x584 lb v0 (D_807506B4), 0x588/0x58c &D_807506A8 in v1, 0x598 addiu v0,v0,1, 0x5a8 sra t5 / 0x5b0 sb t5, 0x604 li v0,-1 / 0x610 sb v0 (b delay slot), 0x614 sb zero. Target relocation table lists D_807506A8 (0x588) before D_807506B4 (0x580).
uopt -zdbug:5 on the fixed copy: {1194|1} isvar S 21 (D_807506B4) coloured reg 1 (v0), adjsave 1.0, live bb 40/41/45.
D_807506B4 is .data in asm/global/data/14C9E0.data.s (word-padded s8); no other src user.

# mapUpdateFogDistance (global, src/global/68960.c)
## Sites
global:80663C60:other:93673b `s16 limit = 6;` loop bound: REMOVED as a value-named constant; the bound is now `s16 count = sizeof(D_80748B70) / sizeof(D_80748B70[0]);` with `extern MapFogEntry D_80748B70[6];`. A variable bound is what keeps 6 in t1 for `slt`; a literal or inline sizeof folds to `slti`.
## Attempts
2026-11-14 PolishGlobal68960 (opus:high): names, review, tagged the bound local (plain nohit: literal 6 folds to slti).
2026-11-14 HackmapUpdateFogDistance (opus:high): uopt_trace / as1probe diagnosis; literal 6 (slti, frame 0x20); inline (s16) and unsigned sizeof bounds (fold to slti, fdiff 1); sizeof-derived count local (fdiff 0, raw words equal).
## Untried ideas
none for this site.
## Evidence
0x30 li t1,6 (delay slot of the gCurrentMap == 0x57 branch), 0x38 sh t1,38(sp) before jal camIsFollowingActive, 0x44 lh t1,38(sp); loop 0xa4-0x11c: multu a0,a3 (a3 = 6, the entry size), lh map / lb character / lh fogDistance, sll/sra s16 i, slt at,a0,t1.
Table data (asm/global/data/14C9E0.data.s): six entries {0x48,4,0x9C4} {0x48,8,0x9C4} {0x48,5,0x3E8} {0x48,0,0x5DC} {0x48,0xD,0xFA0} {0x48,-1,0x320}, then 12 zero bytes up to D_80748BA0.
uopt_trace: base bound isvar {1040} -2vreg -> uopt reg 8 (t1); literal version has no bound candidate and i in v0.

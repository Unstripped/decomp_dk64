# mapBspPlaneSideTest (global, src/global/2F550.c)
## Sites
global:8062E898:other:2f055e other: `n[0] = n[0] * 20;` int literal beside two `20.0f`. Only mattered while the dead ifs below were present (dead ifs removed: int 20 and 20.0f both score 12, xyz loads both 8). FIXED 2026-11-18 (plain 20.0f).
global:8062E898:dead-if:4414c6 dead-if: `if (ny > 0.0f) {}` raised ny's adjsave (1.667) over nz (1.333) so ny took $f16 before nz. FIXED 2026-11-18.
global:8062E898:dead-if:4a540a dead-if: `if (nx && nx) {}` raised nx's adjsave to 2.0 so nx took $f14 first. FIXED 2026-11-18.
Now: `nx = node->unk4C; ny = node->unk50; nz = node->unk54; // LAYOUT:` (one source line, field order), no FAKE left.
## Attempts
2026-11-09 CleanD5E10 opus:low: four hacks removed -> blocks 18/10, nx/nz f14/f18 swap; reconstruct n = c/len*20 inline 112 lines.
2026-11-10 Rev10E opus:xhigh: uopt_trace per site; permute (four removed) best 0 only with an uninitialised early s1 sum; reconstruct 1917.
2026-11-11 Rev17N opus:low: single 20.0f web, no guards: nx/nz swap at the node loads and nz spill; permute no gain.
2026-11-12 Rev20C/Rev21B opus:low: per-guard register effects; 20.000f literal -> int literal (Q0354); combined && tests 12 lines; s2 local 14.
2026-11-13 CleanGlobal55B20 opus:low: rc_side_a/b/c (c: nx, ny, nz loaded in order on separate lines) fdiff 1; permute best=0 moved the int literal (steer swap).
2026-11-18 2026-11-17f CleanmapBspPlaneSideTest opus: all three removed + loads in field order nx, ny, nz (separate lines) -> full=8, registers all match, only as1 order of the three lwc1 (0x4080-0x4088) and their spills (0x4148-0x4150) differs; as1probe on that ugen stream: deleting the two `.loc` records between the loads -> full=0; C with the three loads on ONE line -> fdiff 0 (whole file RELOC-EQUIV OK with the DistanceCheck retype). Permuter (hack-free, -j 2, 900 s) from the separate-line xyz body: base 46, best 0, its zero output-0-4 is the same one-line join.
## Untried ideas
none left for this function (all sites fixed).
## Evidence
uopt -l5 (no guards): nx/ny/nz tie at adjsave 2.0 over the same blocks (1,2,3,6 + default 5); the tie breaks on candidate number = first appearance (Q0900/Q0468): source order nz, ny, nx (cand 13/17/21) gave nz $f14, nx $f18; field order nx, ny, nz (cand 13/17/21) gives nx $f14, ny $f16, nz $f18 like the target.
ugen emits the three l.s in source order with one `.loc` each, and the spills before `jal sqrtf` in register order f14/f16/f18; as1 schedules spills after their loads. Target: lwc1 $f18,84(a0) / $f16,80(a0) / $f14,76(a0) at 0x4080-0x4088 and swc1 $f18,44 / $f16,48 / $f14,52 at 0x4148-0x4150 = the order as1 picks when the three statements share one `.loc` (Q0183, Q0409).
One line in the other order (nz, ny, nx) scores 12: candidate numbering (uopt), not as1, so only the field order works on the line.
Homes: d 40(sp), nz 44, ny 48, nx 52, s1 56, p 64, n 80, c 92, eb 104, ea 116 (declaration order).

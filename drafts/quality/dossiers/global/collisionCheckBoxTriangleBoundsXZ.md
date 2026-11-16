# collisionCheckBoxTriangleBoundsXZ (global, src/global/6AD90.c)
## Sites
global:8066A834:other:c17864 `minX = ((x0 = tri->x0) < (x1 = tri->x1)) ? x0 : x1;`: the assignments inside the test load x1 before x0 (lwc1 0x28 then 0x24 at 0x47b0) while x0 keeps the first colour (f0). Untagged 2026-11-16 as ordinary C: an assignment inside a test whose values the target then uses (ladder.md, Q1032).
## Attempts
2026-11-16 Polishglobal6AD90 opus:high: x0 = ..; x1 = ..; / x1 = ..; x0 = ..; / if-else min: fdiff 1.
2026-11-16 HackcollisionCheckBoxTriangleContainsPointXZ opus:high: plain loads with mirrored compares or swapped arms 2-8, loaded x1 first 13 (f0/f2 colours swap), one assignment in the test 2-13, if-form min 18, loads after the ternary 22. A variants scan of the plain body (27 variants) is 2-25. Without the redundant outer parentheses the form is fdiff 0 (the same construct). Tag dropped, construct kept.
## Untried ideas
none
## Evidence
47b0: lwc1 f2,0x28(a0); 47b4: lwc1 f0,0x24(a0); 47b8: c.lt.s f0,f2. Later maxX test c.lt.s f2,f0 at 0x4830 reuses both.

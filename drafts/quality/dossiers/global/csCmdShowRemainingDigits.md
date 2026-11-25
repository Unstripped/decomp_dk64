# csCmdShowRemainingDigits (global, src/global/478F0_cutscene_cmds.c)
## Sites
global:8064954C:other:ee668d other: `t = v;` redundant alias; v keeps its own web in v1 that ends at the clamp join (subu v1 0x69d8, move v1,zero 0x69e4) and the digit loop gets a separate s2 web across the modelSlotSetNodeFrame calls (move s2,v1 0x69e8). Kept FAKE (rulings.md: redundant alias; register numbering is no ORIG evidence).
## Attempts
2026-11-24 Polishglobal478F0 Polishglobal478F0 anthropic/claude-opus-5-5:xhigh: tagged the pre-existing alias; drop alias -> v in s2 from the subtraction (fdiff 1)
2026-11-25 LeverScout26 (Q1644): v = MAX(0, goals - counts) and t = MAX(0, v) -> 105 (ternary arms store into the destination)
2026-11-25 continue CleancsCmdShowRemainingDigits anthropic/claude-opus-5-5: Q1644 re-check, in-place clamp of the named value without the alias, loop on the clamped variable (variants.py try): plain if -> full=5; clamp+loop on t, v dropped -> 5; `if ((v = goals - counts) < 0) v = 0;` -> 5; `v = (v < 0) ? 0 : v;` -> 5; named digit local -> 5; `v = goals; v -= counts;` -> 21; do-while -> 7; while -> 7; operand order `(v % 10 + 10 - i)` -> 25
2026-11-25 continue CleancsCmdShowRemainingDigits: variants scan of the alias-free copy (26 variants: swap, width, declswap) -> best 5; scan of the base copy: unalias 5, widths >= 1, only zero-cost respellings (swap/int/declswap) match
2026-11-25 continue CleancsCmdShowRemainingDigits: sweep at base: plain nohit (no rewrite), recipe nohit (no removal)
## Untried ideas
none natural left in this scope: every single-variable in-place clamp is one s2 web; a second web needs a second variable live only from the join (the alias). v as u32 with the alias scores 3 but changes the clamp semantics (never taken), rejected.
## Evidence
0x69a4 slti at,v0,8; 0x69ac move a0,v0 (delay slot); 0x69b0 li a0,7: n clamped in place in a0
0x69d8 subu v1,t7,t8; 0x69dc bgez v1,0x69e8; 0x69e4 move v1,zero; 0x69e8 move s2,v1: one-arm in-place clamp in v1, join copy to s2 (Q1644)
0x69ec-0x6a98 digit loop: s0 i (li 1, bne s3=4), s1 = 10, s2 digit value (div/mfhi, mflo s2 0x6a94), s4 csId
uopt_trace base: cand 9 (v) -> v1, cand 23 (t) -> s2, cand 1 (n) -> a0; alias-free: cand 9 (v) -> s2, extra move v1,v0 at 0x69a8

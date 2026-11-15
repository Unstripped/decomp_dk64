# menuInitFileSummary (menu, src/menu/3E10.c)
## Sites
menu:800297B8:other:5ee4ba other: signed `i` holds the one-past byte address, then is reused as the icon-loop counter so p/i outrank q in allocation.
## Attempts
- Previous rounds: direct bound, typed `s8 *end`, declaration permutations, uopt traces, and long permutes failed (see supplied history and Q0515).
- 2026-11-15 HackmenuHandleHighScoreNameEntryInput openai-codex/gpt-5.6-sol:high: typed end pointer, end-derived second-loop cursor, typed four-byte flag array, and typed one-byte flag rows -> fdiff exit 1; q/end remain swapped.
## Untried ideas
None in natural typed-pointer C. Q0515 documents why coordinated reuse of p and integer i is the matching allocation constraint.
## Evidence
- Target text 0x1a94-0x1aac assigns q to s2, p to s0, and the end address to s1.
- A typed end form assigns q to s1 and end to s2; typed flag rows and cursor declaration order leave the same allocation.
- Reusing end in the second-loop initialization still gives end=s2/q=s1 and relocates the cursor expression without improving text.
- Relevant guidance: Q0515, Q0542, Q0726 and guide ido-menu-file-summary#1.

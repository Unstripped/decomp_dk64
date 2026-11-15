# textBoxUpdateRows (global, src/global/A8400.c)

## Sites
- a22210: dead `if (acc && acc) {}`. REMOVED earlier.
  - The `mode == 3` test is a one-case `switch (mode)` with `s16 mode`.
  - The switch dispatch block restores the state s2 / node s1 colouring.
  - s16 avoids the selector copy that u8 mode gets (Q0804).
- 158f8f other: `mode = actor->state;` after `state->holdTimer--`. Now an `// ORIG` line (not a site).
  - The target loads actor->state again in this arm only: `lbu v0,340(s3)` at +0x350.
  - A mode-free tail reads actor->state once at the join instead. That puts the `lbu` after both arms (full=6).

## Attempts
- 2026-11-14 U HacktextBoxUpdateRows: a22210 fixed. See the ledger for line counts.
- 2026-11-14 RereviewSmallFiles3: 158f8f tagged FAKE. Removing the line scored 11; a switch with no mode local scored 6.
- 2026-11-14 U HacktextBoxUpdateRows (2nd session, opus high): 158f8f diagnose fixed as ORIG.
  - Mode-free tails: switch(actor->state) with the test on actor->state 6, nested if 6.
  - holdTimer==0 arm first 9, mode selector plus a test on the field 12, mode read after the switch 22.
  - `actor->state = mode = 1` scored 12, a break inside the holdTimer arm 51, if-forms 51/58.
  - variants.py scan of the 6-word copy found no gain.

## Untried ideas
- None that stay ordinary C. The arm read matches the target's per-arm load.

## Evidence
- Function start is .text 0x16dc in A8400.o. Offsets below are function-relative.
- +0x324 `lbu v0,340(s3)` is the switch selector. It is compared directly at +0x32c and +0x35c.
- holdTimer arm: `sb t5,18(s2)` at +0x348, `b`, then `lbu v0,340(s3)` at +0x350 in the delay slot.
- else arm: `li t6,1` at +0x338 and `andi v0,t6,0xff` at +0x33c, then `sb t6,340(s3)` at +0x354. There is no reload.
- With u8 mode the selector is v1, plus `move v1,v0`.

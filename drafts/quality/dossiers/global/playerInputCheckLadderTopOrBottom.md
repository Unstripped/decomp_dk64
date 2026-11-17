# playerInputCheckLadderTopOrBottom (global, src/global/E4090.c)

## Sites
None (fake=0, goto=0, casts=0, uninit=0, cfe warnings 0 at base 4d0df275).

## Attempts
- **2026-11-17, HackplayerTurnByStickX5, anthropic/claude-opus-5-5:high:** review only. `-pad.stickX` / `-pad.stickY` instead of the three `* -1` negations: 151 full lines (variants.py try), so `* -1` stays; it is ordinary C, not a hidden steer.

## Untried ideas
- None open.

## Evidence
- The repeated `stateFlags & 0x10000002` test and the double jumpTimer store are target behaviour (reviewed 2026-11-15, RereviewW2Player).
- `rungLimit = (... & 0x80) ? 1 : 3;` is the Q0201 ternary `ujp` shape.
- `cnt = st->rung;` is an ordinary named temp (Q0601).

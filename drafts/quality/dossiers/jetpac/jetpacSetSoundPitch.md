# jetpacSetSoundPitch (jetpac, src/jetpac/0.c)
## Sites
- jetpac:80024F24:punned-cast:u2372d `*(s32 *)&pitch`: now `// ORIG:` (0xf40 sw a1,0x1c(sp); 0xf50 lw a2,0x1c(sp)).
## Attempts
- round 7 (opus:low): plain; the base form `s32 *p = &pitch` became the inline pun.
- round 17 (opus:low): diagnose/permute (18, uninitialised local).
- 2026-11-14 U:
  - union local: frame 0x20 + swc1 (3-4 diffs)
  - `s32 *bits` local: matches, but it is the same pun
  - owner 13A7A0 stores arg as `ev.arg8.i` (s32) for every event type, so it needs no change
  - classified ORIG (Q0660)
## Evidence
- target f24-f60: 0x18 frame, homes a1 in the beqz delay slot, reloads it into a2 in the jal delay slot

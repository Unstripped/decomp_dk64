# audioBuildTask

## Sites
- **8e31ef (line 239) and 8e31ef#2 (line 245):** `count = (count & 0) + 2;` in the two hold-frame arms.
  - The target builds the 2 in count's register: `li v0,2` at 0x550 and 0x580.
  - It stores it with `sw v0,%lo(sAudioFrameHoldCount)(at)` in the `b` delay slots at 0x560 and 0x590.
  - Every hack-free spelling builds the 2 in a ring temp instead (t0 / t2; Q0789).

## Attempts
**2026-11-14 HackSmallLeftovers (claude-opus-5-5):**

| form | result |
|---|---|
| `*holdFrames = count = 2` | text 66 |
| `count = *holdFrames = 2` | 66 |
| plain `*holdFrames = 2` | 66 |
| direct `sAudioFrameHoldCount[0] = count = 2` without holdFrames | li t0 / lui a0 differences |
| one-case switch (count) around the arm (Q0523) | 71 |
| switch default decrement in the else arm | 66 |
| `*holdFrames = --count` | 66 |
| `count++` twice | text 2 (`addiu v0,v0,2` at 0x550/0x580) |

Earlier rungs are in the history file (`count += 2`, join store, widths, direct forms, 900 s permute).

## Untried ideas
- A permuter run seeded from the chained-assignment body.
- A file-scope helper shape (would change the call graph; unlikely).

## Evidence
- 0x53c `lw v0`; 0x550 `li v0,2`; 0x560 `sw v0` (delay of `b` 0x5ac).
- 0x570 `lw v0` (reload in arm 2); 0x580 `li v0,2`; 0x590 `sw v0`.
- The else arm stores nothing when count == 0 (0x598 `beqz v0,0x5ac`).

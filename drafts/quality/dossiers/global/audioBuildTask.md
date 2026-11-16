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

## Resolution (2026-11-15 HackaudioBuildTask2, anthropic/claude-opus-5-5:high)
Both noop-arith sites removed: the file-scope `s32 sAudioFrameHoldCount[2];` became a function-local
`static s32 sAudioFrameHoldCount;` and the arms are a plain if / else-if / else storing `= 2` and `--`
directly (no `count`/`holdFrames` locals). Frame kept at 0x40 with `s32 pad2[2];` after `cmdEnd`.
`fdiff --reloc-ok` exit 0 (RELOC-EQUIV OK); raw words differ only at LO16 0x53c/0x560/0x570/0x590/0x5a8
(`.bss`+0x3098 vs `sAudioFrameHoldCount`+0, which the base object defines at .bss+0x3098).

### Attempts (this session)
2026-11-15 HackaudioBuildTask2 HackaudioBuildTask2 anthropic/claude-opus-5-5:high:
| form | result |
|---|---|
| `static s32 sAudioFrameHoldCount[2];` + `[0]` accesses, pad[1] | text 94 (array static -> lda web: `lui v1,%hi(.bss); addiu v1,v1,%lo(.bss+0x3098)`, +16 bytes) |
| `static s32 sAudioFrameHoldCount;` scalar, pad[1] | code identical, frame 0x38 vs 0x40 (text 12) |
| scalar + `static s32` 2nd unused scalar | same as scalar (text 12) |
| scalar + pad[3] in pad[1]'s slot | frame ok, cmdCount sp+0x2c vs 0x34 |
| scalar + pad[3] after cmdEnd (no pad[1]) | text 6 |
| scalar + count/holdFrames locals, `*holdFrames = 2` / `count = 2` | text 68 |
| scalar + pad[1] + `s32 pad2[2]` after cmdEnd | fdiff --reloc-ok exit 0 (KEPT) |

## Evidence (added)
- Base .o: `sAudioFrameHoldCount` g O .bss +0x3098 size 8, .bss size 0x30a0 (2**4). Copy .o: scalar static
  at .bss+0x3098 via section-relative relocs, .bss size 0x30a0 (section rounds to 16), .data 0x230 both.
  Only `.gptab.bss` differs (0x68 vs 0x70, not linked).
- Every target access has its own lui/%lo pair (0x538/0x53c, 0x554/0x560, 0x564/0x570, 0x584/0x590,
  0x5a4/0x5a8): the Q0761/Q0922 static-local signature.

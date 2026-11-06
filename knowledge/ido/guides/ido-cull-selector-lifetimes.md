---
title: "Culling-bit matcher: separate selector and mask lifetimes"
description: "Why identical target registers need not imply a shared C local, and how forwarding barriers preserve IDO mask temporaries."
origin: "ok-fine dk64/notes/ido-cull-selector-lifetimes"
---
# Separate selector and mask lifetimes

In `gfxSwapGeometryModeCullBits`, the target uses `$v0` for both the command-byte extraction and modified cull masks. That does **not** mean one C variable should serve both roles. Sharing them left the opcode shift/comparison in `$a2`; separate `command` and `op` locals allow the disjoint values to occupy `$v0`. A trailing dead test of `command` retains the selector variable, and an early `op = 0` preserves mask-candidate ordering. Both are explicitly tagged code-generation devices, not recovered source intent.[^culling]

The clear-mask arms assign the new mask to `op`, then kill the old `w0` value before the next use. This prevents expression forwarding from replacing the register variable with a ugen temporary chain. The killed value is not used for any later observable operation. A dead repeated cull-mask test keeps the required expression live range; the final set-mask comparison retains an `op | 0` expression to preserve operand order.[^culling]

All nine optional steering constructs in the first exact candidate were tested in subsets; six suffice. This establishes minimality only within that candidate's optional-construct set, not among all C spellings. The retained constructs are tagged `FAKE`.[^culling]

## Behavior boundary

Only opcode `0xD9` commands are processed. Exactly one of the `0x200`/`0x400` bits is exchanged; neither or both leaves the selected word unchanged. For a zero second word, the original assembly's full-width complement leaves the modified first word's high byte at `0xFF`, not `0xD9`. Preserve that behavior rather than normalizing the command byte. The matched implementation passed whole-object comparison, the isolated/main ROM hashes, and 81,920 ASan/UBSan cases covering every opcode, cull-bit combinations, empty/mixed ranges and sentinels.[^culling]

Related: coordinated menu lifetimes (guide ido-menu-file-summary: python3 tools/quirks.py get ido-menu-file-summary), register costs and forbidden sets (guide ido-load-overlay-diagnostics: python3 tools/quirks.py get ido-load-overlay-diagnostics).

[^culling]: `src/global/17B90.c`, matched function at `0x806130A4` (60 instructions / 240 bytes), commit `850257342b2b8bf696a67f032fdb5e895ef2d77a`.

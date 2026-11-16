# textSpawnSubtitle (global, src/global/2C910.c)
## Sites
global:80627C5C:proto-steer:30698d (line 5, PROTO_SKIP_textSpawnMarkerChecked): hides the 9DD70 (u8,s16,s16,u8 *,u16,u16,u8,u8) prototype. It keeps the promoted holdTime as one item: lhu t2,222(sp) at 0x118, sw t2,56(sp) at 0x128, lw at 0x1d8/0x210/0x250. Now `// ORIG`.
global:80627C5C:proto-steer:41f288 (line 61, local `(s32, s32, s32, u8 *, s32, s32, s32, s32)` declaration): replaced by an unprototyped `void textSpawnMarkerChecked();` (same codegen). Now `// ORIG`.
global:80627C5C:proto-steer:145e04 (line 63, K&R definition): the caller at 0x3e0-0x3ec passes the (s16) ternary into the u16 parameter without conversion (sll a1,v0,0x10 / sra t2,a1,0x10 / move a1,t2). Now `// ORIG`.
## Attempts
2026-11-09..13: see `uv run tools/quality.py history textSpawnSubtitle` (consolidate/diagnose rounds 14, 16, 30; Rev30B reconstruct). Each one hit fdiff 1.
2026-11-16 cleanup HacktextSpawnSubtitle anthropic/claude-opus-5-5:high:
- unprototyped `void textSpawnMarkerChecked();` in place of the s32 declaration, PROTO_SKIP kept -> fdiff 0
- PROTO_SKIP + declaration both removed (owner prototype applies) -> fdiff 1: frame 0xd8 -> 0xd0, each call reloads lhu 214(sp), no spill at 56(sp)
- (u8,u16,u8) definition + stand-in, body unchanged -> the callee matches exactly; the caller gets `andi a1,v0,0xffff` instead of sll/sra, plus an extra `andi` for `a & 0xFF` (redundant under the prototype)
- (u8,u16,u8) definition + cast-free caller `textSpawnSubtitle(a, b != 0 ? b : 0x5A, c)` -> the u8 args now match; the only diff left is the andi 0xffff for duration
- (u8,s16,u8) definition + cast-free caller, first call `duration`, later calls `(u16)duration` -> the caller matches; the callee loses the hoisted lhu/sw 56(sp) (frame 0xd0)
- (u8,s16,u8) definition + local `u16 holdTime = duration;` -> copy-propagated, same as the line above
- (u8,s32,u8) definition -> frame 0xd0
- all three removed at once (owner prototype, (u8,u16,u8) definition, cast-free caller) -> fdiff 1 (caller andi, callee frame 0xd0)
- body: splitting `_strncpy(speaker, s, idx = _strcspn(s, ":") + 1)` into a statement, or giving it a separate `len` local -> fdiff 1. The target converts the value twice (sll v1/sll a2 at 0xa0/0xa4): once for the argument and once for the store to idx's home at 66(sp), so the embedded assignment is ordinary C.
## Untried ideas
none left for these sites (every prototype fails one side)
## Evidence
- Owner 9DD70 textSpawnMarkerChecked 0x42a4-0x42c0 reloads its params narrow (lbu 43 / lh 46,50 / lhu 58,62 / lbu 67,71), consistent with the shared prototype widths.
- The callee's narrow reloads (andi a3,a0,0xff at 0x60, lbu 227(sp), lh/lhu 222(sp)) are identical for the K&R and the (u8,u16,u8) forms (Q0826, Q0862). The only proof of a K&R definition is at the call site, 0x3e0.

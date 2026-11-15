# playerStateWaypointAimUpdate (global, src/global/F56F0.c)

## Sites
global:806F3E0C:proto-type:14204c  proto-type: `#define PROTO_SKIP_playerStateQueueCallback` + K&R local
`s32 playerStateQueueCallback();` so the call can pass a 4th `&gWaypointCursor` (523ab5), which pins the
cursor address web (lui/addiu at 0x3428/0x3434, `lw t0,0(a3)` 0x3438, 0x3548, 0x35f0, `sw t0,0(a3)` 0x3600) to $a3.
global:806F3E0C:other:523ab5 and the 9 dead-if/other sites: EXHAUSTED (history), unchanged.

## Attempts
2026-11-15 HackplayerStateWaypointAimUpdate2 anthropic/claude-opus-5-5:high (types phase):
- shared 3-arg prototype (skip define + K&R decl deleted, 3-arg call, all other sites kept,
  `p/F56F0_3arg.c`): fdiff exit 1, variants try full=11 (cursor address in t2, zero/one temp in a3).
- 4-arg form with a full local prototype `s32 playerStateQueueCallback(s16, void *, u8, WaypointNode **)`
  (`p/F56F0_4proto.c`): fdiff exit 0; variadic `(s16, void *, u8, ...)` (`p/F56F0_varproto.c`): fdiff exit 0.
- callee side: EFDC0 definition made variadic (`efdc0/EFDC0_var.c`): fdiff exit 1 (adds `addiu sp,-8;
  sw a3,0x14(sp)` and shifts the arg homes); 4th `void *arg3` param (`efdc0/EFDC0_4p.c`): fdiff exit 1 (adds `sw a3,0xc(sp)`)
  -> neither a variadic nor a 4-parameter shared prototype can match the callee.
- F56F0 has no other caller of playerStateQueueCallback (only line 1339); ~100 callers in ~30 other files
  all pass 3 args, so a 4-parameter shared prototype would break every one of them.
=> views blocked (owner EFDC0).

## Untried ideas
none new for the 10 exhausted sites.

## Evidence
target 0x35a0 `jal playerStateQueueCallback` sets only a0 (0x3580), a1 (0x3594), a2 (0x3588); a3 is not
written for the call: it still holds &gWaypointCursor from 0x3434, so the 4th argument has no
instruction of its own (no ORIG evidence).

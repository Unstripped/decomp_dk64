# bonusTargetGameUpdate (bonus, src/bonus/2690.c)
## Sites
bonus:800277F8:proto-steer:689f58 proto-steer: `#define PROTO_SKIP_func_806FDAB8` (file line 3) hid 1025E0.h's `func_806FDAB8(s16, f32)`; FIXED
bonus:800277F8:proto-steer:e3027b proto-steer: local `void func_806FDAB8(u8, f32);` (file line 87) so the u8 local `c` reached a0 as `andi a0,v0,0xff` with no `sll/sra 0x10`; FIXED
## Attempts
2026-11-09..14 (history, 86 events): dropping both lines with the u8 local `c` kept -> fdiff 1 (sll a0/sra a0 0x10 before each of the 3 `jal func_806FDAB8`); owner retypes u8/u16/s32 -> fdiff 1.
2026-11-16 HackbonusTargetGameUpdate HackbonusTargetGameUpdate anthropic/claude-opus-5-5:high: both lines removed, `c` dropped, `game->counterTextId = gfxResourceCreate(...); func_806FDAB8(game->counterTextId, 0.0f);` -> variants try full=0; `s16 c` -> full=197; same rewrite in bonusLightFlashGameUpdate (full=0) and bonusBigBugBashGameUpdate (full=2: 0x52 vs 0x56 slot shift from the dropped `u8 c`; `s32 padz` -> `s32 padz[2]` full=0) -> whole-file fdiff 0.
2026-11-16 same: review removed value temp `r` (`idx = ((randomNonNegative() >> 0xF) % 0xFF) % 8;`) -> fdiff 0.
## Untried ideas
none open (all sites fixed).
## Evidence
0x11c0 jal gfxResourceCreate; 0x11d0 `andi a0,v0,0xff`; 0x11d8 jal func_806FDAB8; delay slot 0x11dc `sb v0,0x25(t0)` (counterTextId stored from the raw v0, the argument masked separately) = a u8 field store forwarded into the u8 field reload (Q0750/Q1012); a u8 field read passed to an s16 parameter gets no cvtl (unlike a u8 local, Q0666).

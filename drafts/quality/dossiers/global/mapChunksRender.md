# mapChunksRender (global, src/global/55B20.c)
## Sites
- a1232a / 19cc66: the PROTO_SKIP define plus a local s32 last-parameter declaration. Both deleted (HackmapChunksRender): the shared 35000.h `u8` prototype applies once the two list-selection tests are spelled `if (flag)`.
## Attempts
- 2026-11-16 HackmapChunksRender HackmapChunksRender anthropic/claude-opus-5-5:high: owner retypes in a 35000 copy (last parameter s32/u32/s16/u16, s32 with `(u8)` casts at the three uses, s32 plus a `u8` copy local in four placements): every one changes the owner's `lbu s5,0xaf(sp)` at 0x904 (lw/lh/lhu, extra andi), so the owner stays `u8` -> fdiff 1 each.
- 2026-11-16 HackmapChunksRender: shared u8 prototype with `(u8)flag != 0` tests or `(u8)flag` arguments -> fdiff 1 (13 diff lines).
- 2026-11-16 HackmapChunksRender: shared u8 prototype with `if (flag)` at both selections -> fdiff 0 whole object; only the first or only the second -> fdiff 1; `if (flag)` with the s32 steer kept -> fdiff 1.
## Untried ideas
- none left for these sites.
## Evidence
- **Call sites:** both mapChunksRender call sites store flag with `sw s5,0x1c(sp)` (0x5620, 0x5ac4) under either declaration, with no andi.
- **Owner:** renderEntryListBuildDisplayList reads the argument as a byte: `lbu s5,0xaf(sp)` at 0x904; any non-u8 last parameter changes that load.
- **Tests:** the target tests flag with `beqz s5` at 0x55e4 and 0x5a7c, the same register it passes; the -1 sentinel lives in s8 (`li s8,-1` at 0x5280). Under the u8 prototype, `flag != 0` gives a compare candidate separate from the u8 argument web, so flag splits into s8/s5 and the sentinel is rematerialised (`li at,-1`) per test. The bare truth test (Q0590) keeps one web.

# actorSinkAndDespawn (global, src/global/A6280.c)
## Sites
global:806A1FD8:other:39fa37 other: `s32 i` carried the actorListLookupEntry entry (narrowed for flagGet at 0xae0, whole as the 7th actorSpawnNodeEntryScaled argument `sw v0,24(sp)` 0xce0) beside the rider index (strength-reduced into s1). Fixed 2026-11-25c: own `s32 entry` in the word freed by deleting `node`.
global:806A1FD8:other:1039a0 other: `s32 node` carried the actorListFindIdByActor id (u16 argument `andi a0,v0,0xffff` 0xadc/0xcb0) before counting bone nodes (s0). Fixed 2026-11-25c: own `s16 id` packed into found's word; bone loop runs on `i`.
## Attempts
2026-11-14 PolishGlobalA6280Names anthropic/claude-opus-5-5:high: removed the untagged `do { i = 0; } while (0);` before the rider search -> fdiff 0.
2026-11-18b Polishglobal119370b anthropic/claude-opus-5-5:xhigh: separate entry / bone locals (any position) -> frame 0x68 -> 0x70 (every home +8); nested calls -> frame grows; tagged both FAKE.
2026-11-25c CleanactorSinkAndDespawn anthropic/claude-opus-5-5: frame census; `s16 id` after `u8 found` + nested lookups (both sites, either site alone) -> 12 (frame 0x70: each nested call adds a temp); `s16 id` + `s32 entry` (first, last, after id) -> 12; `s32 i` moved after found -> 6 (frame only); `u8 i` + `s16 id` in the hole -> 25 (strength reduction lost: move s1,zero, per-iteration sll/andi); `s16 i` -> 36; `u8 node` -> 34; bone loop on `i` + `s32 entry` in node's slot + `s16 id` after found -> 0 (both declaration orders of i/entry); bone loop as `for (i = 1; i < 9; i++)` inside the sinkTimer test, `i = 1` inside the test, or the old hoisted do-while -> 0. Kept: the for form. variants scan of the final body: only truth/swap/arith/float/width (count, i, entry to u32/int; id to u16)/declswap (i/entry, sub/act) zeros; `u8`/`u16` i 49, `u8` entry 43.
## Untried ideas
none open: both sites fixed.
## Evidence
Frame 0x68: outgoing args sp+0..0x1f, `sdc1 $f20,32(sp)`, s0..s3/ra sp+44..60, named homes from sp+0x67 down; one word of locals more makes 0x70 (budget: locals <= 36 bytes).
Named homes in the target: count sp+100 (`sw v1,100(sp)` 0xb60, `lw` 0xb6c), found sp+91 (`sb a1,91(sp)` 0xb5c, `lbu` 0xb74), nodeX/Y/Z sp+84/80/76 (actorGetNodePos args 0xc0c/0xc14/0xbfc). sp+96 and sp+92 are never stored: no role value reaches those homes (no ORIG case under rulings.md).
Budget: 5 words + a 3-byte hole (sp+88..90) beside found; roles count, rider index, bone counter, act (s0), sub (s3), entry need 6 words with separate loop counters; one counter reused by the later bone loop (rulings R7, Q1224) is ordinary C and fits.
Registers: rider index -> s1 as i*4 (`sll s1,zero,0x2` 0xb40, `addiu s1,s1,4` 0xb94); bone counter s0 (`li s0,1` 0xbac, `addiu s0,s0,1` 0xc4c, `bne s0,at` with at=9 0xc54).
cfe homes of the final C: count -4, i -8, entry -12, found -13, id -16, nodeX -20, nodeY -24, nodeZ -28, sub -32, act -36.

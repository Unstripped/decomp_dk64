# bossSpawnerUpdate (boss, src/boss/DAA0.c)

## Sites
- proto-steer fe0889/59a070 (sfxAllocateChannel K&R): FIXED. Shared `void sfxAllocateChannel(s32, f32)` with `1.0` (double literal): built per call `lui a1,0x3f80`; `1.0f` joins the function 1.0f FP web and is passed `mfc1 a1,$f2`.
- proto-steer 4c08f3/3cd67a (sfxPlayOnFreeSlot K&R): FIXED. Shared `s16 sfxPlayOnFreeSlot(s16, s32, f32, f32, u8, u8)` with `63.0, 1.0`: per-call `lui a2,0x427c` / `lui a3,0x3f80`. `63, 1` (int) and `63.0f, 1.0` also match; any `1.0f` fails (Q0354/Q0421). bossFollowerActorUpdate's two calls changed with it.
- other a0a7fe (dx reused for randomFloat): FIXED. `f32 r` own local; frame room comes from the old `s32 pad` slot (0x78) plus sharing one x/z float pair between case 1 (player offset) and the light block.
- other 82a569 (cutsceneId as light level): FIXED. `s32 level` in the old pad slot, used for raw level and the `(i << 4) & 0xFF` intensity.
- dead-if f9b7c2 (`if (D_80035B68 == 0) {}` case 1): FIXED via Q0498: D_80035B68/D_80035B6C become function-local statics (only user). Object differs only in relocations (.data+0x68/+0x6c instead of the two global symbols); `fdiff --reloc-ok` RELOC-EQUIV OK, raw words equal except LO16 addends, .data/.rodata bytes identical.
- dead-if 3e88fe (was 0e256f, `if (level && level) {}`): KEPT tagged. See ledger diagnose.

## Attempts (2026-11-14, HackbossSpawnerUpdate, anthropic/claude-opus-5-5:high)
- int / double literal args for prototyped f32 params -> fdiff 0 (all four proto sites)
- split local replacing the pad (b1: level, b2: r) -> fdiff 0 each; both together need a 4-byte slot: freed by x/z sharing (g2) -> fdiff 0
- both splits with j/r declaration permutations (240 variants) -> j home 0x52 moves (d_10_15 closest)
- block-scoped r / level -> spill homes -4
- k or i as the level variable -> recolouring of k (v0 vs a1)
- function-local statics D_80035B68 (+B6C) without the case-1 dead test -> RELOC-EQUIV OK
- 3e88fe removal: level types u8..u32, spellings i<<4 / i*16 / (u8), statement moves, u8 intensity local in the 3-byte hole -> nonzero (+1..+3 insns)
- permuter on the 3e88fe-removed base: see ledger

## Untried ideas
- intensity as an inline expression per lightAdd call with a different u8 conversion path (6 uses; would need repeated expression)

## Evidence
- frame 0x80: s0/s1/ra 0x34/0x38/0x3c, spills v1 0x48 / v0 0x44, j 0x52, cutsceneId 0x5c (lh 0x5e), s8 locals 0x67-0x6b, i 0x70; unaddressed 4-byte locals fill 0x7c,0x78,0x74,0x6c,0x60,0x58,0x54
- light block: `addiu v0,t9,-16; move t0,v0; bgez v0` (level separate from i), `sll t2,t0,4; andi v0,t2,0xff; sw v0,0x44(sp)` and v0 passed straight to the u8 args

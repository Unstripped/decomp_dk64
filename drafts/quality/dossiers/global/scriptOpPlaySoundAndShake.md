# scriptOpPlaySoundAndShake (global, src/global/19A00.c)
## Sites
global:80616E08:volatile:d3dae3 volatile: `volatile u8 imm2` keeps the 0xFF arm's `lbu t6,77(sp)` out of the `bnez v1` delay slot. Without it, as1 hoists that load (target: `bnezl v1` + `lw t8,88(s0)`).
global:80616E08:warning:be3187 warning: W709 on `scriptReadU8(&imm2)`, caused only by the volatile above (`volatile u8 *` -> `void *`).
global:80616E08:dead-if:704da9 .. 704da9#6 dead-if: six `if (actor && actor && actor) {}` guards between the switch join and `mapActionLookupEntry`. They pad as1's XBB source window (Q0548), so the then-arm's `lh t2,78(sp)` / `li a1,10` are not hoisted above `bne v1,at` (the unk2C0==2 test).
## Attempts
2026-11-09..14 Clean19A00 / ReReview / Rev17M / CleanGlobal19A00 (opus low/xhigh): remove/cond/classify (class 2)/recipe/diagnose/permute/retype/reconstruct on every site, all nohit. Removing the volatile alone gives full=7. Guards 0-4 give full=9, 5 give full=7, 6 give full=0. Permuter best 305 only re-adds the volatile. Natural body full=16. (history file)
2026-11-15 unit U HackscriptOpPlaySoundAndShake2 anthropic/claude-opus-5-5:high: sweep on the copy, 63 checks, 0 hits (twice). Dropped the untagged `(u32)` casts: `imm2 = (u32)imm2 * 0.5` -> `imm2 *= 0.5`, fdiff 0.
2026-11-15 unit U HackscriptOpPlaySoundAndShake2 anthropic/claude-opus-5-5:high: carve_19A00.c defines 19A00's .data (0x80746B80-0x80746E20: sScriptEffectSprites, sScriptEffectCallbacks, sScriptOpcodeTable, sMotionWindowProgress, sScriptChannelIndexTable, sScriptCommandTable[45], sCharacterBehaviorMap[5] at 0x80746E14) in ROM order, with no guards, `u8 imm2`, and `imm2 *= 0.5`. variants try gives full=0. objdump -drz .text is identical to expected except the LO16 addend at 0x4208 (sCharacterBehaviorMap-4 = 0x80746E10). .data equals global.bin 0x14B880-0x14BB20. No cfe warnings. Blocked on the yaml carve (header-request.md).
## Untried ideas
After the lead's carve lands: apply carve_19A00.c's body (u8 imm2, no guards) and record d3dae3/704da9 x6 `diagnose fixed` and be3187 `retype fixed`.
## Evidence
0x80746CE0 (sScriptOpcodeTable[61]) = `.word scriptOpPlaySoundAndShake`. With that word in the same TU, as1 marks the entry label address-taken, and the `switch (actor->actorType)` `jr` gets a CFG edge to it (Q0552, Q0544 "live switch jump"). Without the data (extern table) the stock as1 hoists the then-arm's `lh t2,78(sp)` / `li a1,10` and the 0xFF-arm `lbu t6,77(sp)`, which the guards and the volatile had to block.
sCharacterBehaviorMap: the code indexes `[actorType - 2]`, so the reloc names 0x80746E10 (the last sScriptCommandTable word, scriptCmdCheckSlopePitch). The real table starts at 0x80746E14: {0xD4, 0xA7, 0xD4, 0xD3, 0xD4} + pad.
scriptOpApplyMotionFriction's `(u32)current == imm` FAKE (no switch) is still needed in the carve: full=1 without it.

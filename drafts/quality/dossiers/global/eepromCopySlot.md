# eepromCopySlot (global, src/global/104F0.c)
## Sites
global:8060BA14:noop-arith:57b6f7 noop-arith: stride = stride | 0 extended the stride web past dst (stride v0, quotient t8, original a3, replacement v1) -> FIXED 2026-11-15 (removed with the stride/size locals)
## Attempts
2026-11-10..12 Clean104F0 / CleanGlobal104F0 / Rev16H: traces, permutes (dead stride stores)
2026-11-14 HackeepromClearSlotData opus-5-5:high: src/dst table-base initialisers (16, shape 0: register naming only), size = stride / 8 without reassigning (24), stride >> 3 (27), orders (15-20)
2026-11-15 HackeepromCopySlot anthropic/claude-opus-5-5:high: size = SLOT_SIZE local with src/dst (34), stride copy of size (34), stride = &~7 then size = stride / 8 (33), original * size (35); slot size inline at all three uses in memcpy args (5: addu operand order + extra move v0,t8), src = sEepromSlotBuffer + SIZE * original (2); src = &sEepromSlotBuffer[SIZE * original], dst likewise, memcpy(dst, src, SIZE) -> 0, fdiff exit 0 (applied)
2026-11-21 continue unit 1 Hack104F0 anthropic/claude-opus-5-5: review on the gModelCountTotal body, no edit (fdiff 0, uninit 0, 0 casts; XOR swap = the target's three xor)
## Untried ideas
none (function clean)
## Evidence
0x26c-0x2cc: lh v0 D_807ECEA0, slot-size arithmetic in v0, and t7 / move v0,t7 (the same move eepromClearSlotData 0xfac and eepromGetSectionBuffer 0x2ae4 show for a single slot-size expression), sra t8; multu t8,a3 (original) then t8,v1 (replacement); a2 = t8 (size); addu a1,t0,t9 / addu a0,t0,t1 (buffer base first = array-index address spelling).

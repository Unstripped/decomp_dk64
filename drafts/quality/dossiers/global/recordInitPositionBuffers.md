# recordInitPositionBuffers (global, src/global/10130.c)
## Sites
global:8060B5C0:other:f3495b `byteCount = src + byteCount;` before the last memcpy: REMOVED. It only raised byteCount's colouring priority (adjsave 4.0 vs src 2.75) so byteCount took $s0 and src $s1, and its separate statement put the sum in its own .loc before `la a0,D_807ECE20` (as1 then forwards it as addu a1,s1,s0 at 0x278).
## Attempts
2026-11-10 round 10 Rev10D opus:low: review; u8 *src retype tried.
2026-11-11 round 16 Rev16J opus:low: sweep plain; diagnose (inline src + byteCount schedules the addu after lui a0; src += byteCount swaps the registers); permute 600 s on the inline body, no improvement.
2026-11-14 HackrecordInitPositionBuffers opus:high:
- inline src + byteCount: 2 lines (addu after addiu a0; ugen stream `la $4; addu $5,$17,$16` vs base `addu $16,$17,$16` on its own .loc).
- named end local (s32 / u8 * / void * / PositionRecord *), computed before the D_807ECE90 memcpy, sizeof size, struct assignment: 2 to 17.
- src += byteCount ending: 19 (src adjsave 3.25 > byteCount 3.0, s0/s1 swapped); same with u8 * / void * / char * src retypes (PROTO_SKIP stand-in).
- byteCount assigned the constant 2-byte sizes (first read only, second only, both, sizeof forms) together with the src += byteCount ending: 0. Final form: every chunk is `byteCount = <size>; memcpy(dst, (void *)src, byteCount); src += byteCount;`, sizes by sizeof; fdiff 0, objdump raw words equal; uopt_trace -l 5 byteCount 4.0 ($s0) / src 3.25 ($s1).
## Untried ideas
`u8 *src` retype now that the body is hack-free (needs the 10130 prototype and func_8060B750, whose assetData is s32 with two W712 warnings).
## Evidence
Target 0x190-0x298: src in $s1 (move s1,a0 at 0x1a0), sizes in $s0 (sll a2,s0,2; move s0,a2 at 0x224/0x228), last source addu a1,s1,s0 at 0x278 between lui a0 and addiu a0 of D_807ECE20, li a2,112 in the delay slot.

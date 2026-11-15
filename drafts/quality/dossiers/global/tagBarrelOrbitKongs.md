# tagBarrelOrbitKongs (global, src/global/80150.c)

## Sites
global:80682AB4:dead-store:d45e68 dead-store: first def of the dead u8 `u` chain; without it u is live-in (lbu v1,107(sp), adjsave 1.0 -> 3.0); with it the chain is emitted by ugen in $3 and deleted by as1.
global:80682AB4:other:b38837 other: chain line 2; the chain burns 15 ugen ring allocations ($9..$13,$14,$15,$24,$25,$8..$13) so the loop's trunc scratch is $14 and `mfc1 t7,$f16` at 0x77c4.
global:80682AB4:other:1cc068 other: chain line 3 (same role).
global:80682AB4:other:c2023d other: chain line 4; the final store (`u = u` also works) is what stops uopt deleting the chain.
global:80682AB4:other:8074ea other: REMOVED (byte-pointer walk) by retyping the definition and a for loop over arg->kongs[i].

## Attempts
2026-11-15 HacktagBarrelOrbitKongs2 HacktagBarrelOrbitKongs2 anthropic/claude-opus-5-5:high: definition `void tagBarrelOrbitKongs(TagBarrelData *arg)` + `s32 pad;` first + `for (i = 0; i < 5; i++) { kong = arg->kongs[i]; ... }` (no cursor, no mid-loop i++) -> stand-in fdiff exit 0 (8074ea fixed).
2026-11-15 same: `TagBarrelData *arg = data;` kept + `((TagBarrelData *)data)->kongs[i]` in a for loop -> full=0 but a re-read through another pointer (hidden steer), not used.
2026-11-15 same: param retype without the pad -> centerX at 0x74(sp) not 0x70 (frame).
2026-11-15 same: `Actor **row = arg->kongs; kong = *row; row++` -> addiu s3,s4,8 / lw 0(s3), full=2; `Actor **row = (Actor **)data; row[2]` full=0 but a pun.
2026-11-15 same: each chain line removed alone, pairs, all three, all four (+u) -> full=33 every time (uopt deletes the whole chain: 15 pre-loop ring allocations, loop mfc1 t2).
2026-11-15 same: u declared u8/s8/u16/s16/s32/u32 -> only u8/u16 full=0; greedy cast/mask minimisation (u8, u16) drops only d45e68's (s32), 1cc068's outer (s32) and c2023d -> `u = u`; no line removable.
2026-11-15 same: single dead stores (40 forms), 2..6-line simple-mask or `u = u + 1` chains, 2/3-line versions of the real chain + `u = u` -> all deleted by uopt (full=33).
2026-11-15 same: ~1400 stage-form variants without the chain (baseYaw s16/s32/u16/s8/u32; init merged into stage 1; (s16)(s32)/(s32)/(u16)/(s16)(u16) casts; `baseYaw &= 0xFFF` split; s16 tmp stage locals) -> best full=9 (s32 baseYaw, tmp stage 2: loop ring right, post-mask sll/sra into s5 lost).
2026-11-15 same: variants.py scan of the chain-free retyped body (47 variants) -> no zero.

## Untried ideas
A natural source of exactly 5 (mod 10) invisible ugen ring allocations before the loop (as1-deleted sll/sra or and pairs); stage cast stacks only move it by even counts (own measurement).
A different blend/timer conversion that keeps `lhu t6 / bgez` (own idea).

## Evidence
Target .text 0x7774-0x777c `andi t1,t0,0xfff; sll t2,t1,16; sra s5,t2,16` and 0x77a0-0x77a8 `andi t8,t7,0xfff; sll t9,t8,16; sra s5,t9,16`: both baseYaw stages store an s16 after the mask.
Target loop 0x77c4 `mfc1 t7,$f16`, 0x77cc `addu t9,t7,s5`, 0x77e0 `sra t3,a0,16`: ugen ring here is a pure round robin $14 $15 $24 $25 $8..$13 starting at $14 per function; the base listing has 30 ring allocations before label $32 (last $13), the chain-free one 15 (last $8).
Target 0x7748 `move s3,s4`, 0x77b0 `lw s2,8(s3)`, 0x7814 `addiu s3,s3,4`: uopt's strength-reduced arg->kongs[i] walk with s4 = the TagBarrelData * parameter.
Target 0x76b8 `swc1 $f4,0x70(sp)`: centerX's slot needs one 4-byte local declared before it.

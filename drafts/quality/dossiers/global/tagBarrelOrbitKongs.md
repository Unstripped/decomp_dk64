# tagBarrelOrbitKongs (global, src/global/80150.c)

## Sites
global:80682AB4:dead-store:d45e68 dead-store: REMOVED 2026-11-18 with the whole chain (see Attempts): first def of the dead u8 `u` chain; it kept uopt from deleting the chain, whose 15 ugen ring allocations as1 then deleted.
global:80682AB4:other:b38837 other: REMOVED 2026-11-18 (chain line 2): the chain's 15 pre-loop ring allocations shifted the loop's trunc scratch to $14 and `mfc1 t7,$f16` at 0x77c4; the real source shifts it inside the loop instead.
global:80682AB4:other:1cc068 other: REMOVED 2026-11-18 (chain line 3, same role).
global:80682AB4:other:c2023d other: REMOVED 2026-11-18 (chain line 4, the `u = (u32)u` self-copy that kept the dead tree alive in uopt).
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
2026-11-17 CleantagBarrelOrbitKongs CleantagBarrelOrbitKongs anthropic/claude-opus-5-5: ring pinning from the target's visible ring registers (see Evidence): allocations #1-#14 are fixed mod 10, the 5 (mod 10) missing ones must sit between stage 2's `sll t9` (0x77a4) and the loop trunc, where the target has no ring instruction -> only as1-deleted dead code can supply them; natural narrowings/reloads of baseYaw, arg fields or yaw land before 0x77a4 or after the loop trunc (lever a refuted).
2026-11-17 same: lever (b) identities on stage 2 (`^ 0`, `| 0`, `& -1`, `* 1`, `+ 0`, `- 0`) -> all 15 allocations, full=33; `^ 0` survives uopt (t.O `ldc 0; xor`) but ugen emits no xor and allocates nothing.
2026-11-17 same: natural dead stores in the window (chained `u = baseYaw = <stage 2>` with u u8/s8/s16/s32, `yaw = baseYaw = <stage 2>`, `yaw = baseYaw;`, s16 `u = baseYaw; u = u;`) -> deleted by uopt (15, full=33).
2026-11-17 same: survival rule of the dead tree: `u = E; u = u;` with E = k nested `(u8)(x & m)` levels: k=2..5 deleted (15), k=6 26, k=7 28, k=8 30 (full=0), k=9 32; k=10 without the self-copy deleted; `v = u`, `u &= 0xFF` as the second statement deleted; `u = (u8)u` works; a flat 15-shift sum or 7 non-nested (u8) terms + `u = u` deleted.
2026-11-17 same: one-statement forms `u = u = E8;` / `u = (u8)(u = E8);` / `u = u = <the real 3-line chain merged>;` -> full=0 (alt copy alt_compact_80150.c, one FAKE line instead of four; not applied: not plausible original code, needs a director ruling).
2026-11-17 same: 150-body stage grid (baseYaw s16/s32 x stage casts (s16)(s32)/(s32)/(u16)(s32)/(s16)/(u16) x stage-2 tmp none/s16/s32) -> best full=9 (s32 baseYaw, (s16)(s32) stage 1, (u16)(s32) stage 2); hack-free-weights permuter from it (-j 2, 900 s, ~21k iterations): base 444, best 225 = baseYaw back to s16 with the (u16) stage-2 cast (full=37, 14 pre-loop allocs), no zero.
2026-11-17 same: review cleanups kept (fdiff 0): `(f32)` on the timer quotient, both stages' `(s32)`, both `(f64)glow` and the `(u32)` on the unk15F store dropped (casts 18 -> 12), `glow -= 0.6; glow *= 2.5;`; not kept: ternary clamp instead of `clamped` full=83, loop yaw without `(s16)` full=32, `glow < 0.0f` full=39.
2026-11-18 cleanup CleantagBarrelOrbitKongsb CleantagBarrelOrbitKongsb anthropic/claude-opus-5-5: FIXED all 4 sites. The chain-free loop's narrowings of the slot angle: inner `(s16)(s32)`/`(s16)(double)` or an `s16 offset` local -> mfc1 renamed t4 (2 deleted allocations), `(u16)(s32)` -> t3 (1), `(u16)(double)` / u16 local -> unsigned cvt sequence (full=65), `(u16)baseYaw` -> uopt hoists the mask and as1 drops stage 2's sll/sra (full=46), `(u16)(sum)` -> addu one register short (full=33), nested `(s16)(((s16)(...) & 0xFFF) + baseYaw)` -> 3 deleted (full=33).
2026-11-18 same: the slot angle normalised like both baseYaw stages, `x = (s16)(4096.0 - (i * 819.2)) & 0xFFF;` into an s16 then `yaw = (s16)(x + baseYaw) & 0xFFF;` -> full=0 three ways: reusing `yaw` (pad kept), an `s16 offset` local after the others (pad kept), `s16 slotYaw` declared first replacing `s32 pad` (kept: whole-file fdiff 0). Not used: `s32` offset (addu operands swap, full=33), `yaw = (s16)(baseYaw + yaw)` (full=1), dropping the pad with no new local (frame, full=6).
2026-11-18 same: variants.py scan of the fixed body: zeros only for comparison mirrors, `4096.0f`, `0.0`, yaw u16/s32 and declaration swaps (no hack-relevant variant).

## Untried ideas
None needed: no hack sites left.

## Evidence
Target .text 0x7774-0x777c `andi t1,t0,0xfff; sll t2,t1,16; sra s5,t2,16` and 0x77a0-0x77a8 `andi t8,t7,0xfff; sll t9,t8,16; sra s5,t9,16`: both baseYaw stages store an s16 after the mask.
Target loop 0x77c4 `mfc1 t7,$f16`, 0x77cc `addu t9,t7,s5`, 0x77e0 `sra t3,a0,16`: ugen ring here is a pure round robin $14 $15 $24 $25 $8..$13 starting at $14 per function; the base listing has 30 ring allocations before label $32 (last $13), the chain-free one 15 (last $8).
Ring pinning: lhu t6 0x76dc = alloc #1, lb t7 0x7700 = #2, stage-1 trunc scratch #3, deleted (s16) sll/sra #4/#5 (mfc1 renamed t0 at 0x776c), andi t1 #6, sll t2 #7, sra->s5 #8, lb t4 0x7714 = #9, trunc #10, deleted sll/sra #11/#12 (mfc1 renamed t7 at 0x7798), andi t8 #13, sll t9 #14, sra->s5 #15; loop trunc must be #31 (or #21/#41).
Window 0x77a8-0x77c4 (and the preheader 0x7744-0x774c `move s1,zero; move s3,s4; li s6,5`): no ring register written; FP literals go through $at.
Target 0x7748 `move s3,s4`, 0x77b0 `lw s2,8(s3)`, 0x7814 `addiu s3,s3,4`: uopt's strength-reduced arg->kongs[i] walk with s4 = the TagBarrelData * parameter.
Target 0x76b8 `swc1 $f4,0x70(sp)`: centerX's slot needs one 4-byte local declared before it.
Target 0x76e4 `bgez t6`: the timer conversion is unsigned (u32 -> f32), so `(u32)arg->timer` is behaviour.
2026-11-18 ugen listing of the fixed body (as1probe keep): pre-loop 15 ring allocations (unchanged); loop `trunc.w.d $f16,$f8,$9` (#16), `mfc1 $10`, `sll $11`, `sra $12`, `and $13,4095`, `sll $14`, `sra $15` (#22), `addu $16,$15,$21`, `sll $24`/`sra $25` (the sum's `(s16)`), `and $8`, `sll $9`, `sra $10` -> s0. as1 deletes #18-#22 (the sum's `& 0xFFF` demands 12 bits, through addu) and renames mfc1 to $15 (t7, 0x77c4), then deletes #23/#24 and renames addu to $25 (t9, 0x77cc).
Correction of the 2026-11-17 ring pinning: a visible register that is an as1 rename target (Q0374) pins the LAST deleted allocation of its chain, not its own; the loop mfc1 t7 pins #22 (of 16..22), so the window 0x77a8-0x77c4 needed no hidden code.
`s16 slotYaw` declared first takes the 0x74 word `s32 pad` reproduced (centerX stays at 0x70).

# camPathCommandDispatch (global, src/global/2C910.c)

## Sites
- global:80627F04:dead-store:50a878 dead-store: `p = (Actor *)((u32)params01 >> 16);` gives E_u (`srl a1,t8,0x10` at 0x338, coloured a1, used by case 0x11 `andi a0,a1,0xff` at 0x8fc) its spilltemps bit before T1 = `(s16)arg1`, so T1 sits at 0x44 (`sw t1,68(sp)` at 0x37c); without it T1 lands at 0x40.
- global:80627F04:other:cfb83e other: unreachable `if ((u32)d < 0U) sfxSetMode(d);` precolours the T3 = `(s16)arg2` item (spilled `sw t7,56(sp)` at 0x38c) to a0; only needed while the first case-0x2F call wraps d in a cast.
- global:80627F04:other:9fec01 other: `(s16)(u16)d` at the first case-0x2F call (0x136c, arg `lh a1,58(sp)` at 0x1370) keeps that narrowing distinct from the `(s16)d` of calls 2/3 (0x1384, 0x139c), which would otherwise share one cvtl (in s0, `move a1,s0`).

## Attempts
2026-11-14 HackcamPathCommandDispatch HackcamPathCommandDispatch anthropic/claude-opus-5-5:high: sweep (remove/cond/recipe/plain) 0 hits.
2026-11-14 HackcamPathCommandDispatch HackcamPathCommandDispatch anthropic/claude-opus-5-5:high: 50a878 spellings with guard + (s16)(u16) kept: `params[0] = (u32)params01 >> 16` first 705; chained `params[1] = b = ...; params[0] = a = ...` 61; a-first 43; chained a-first 43; `(s16)(u16)` hi half 47; hi `& 0xFFFF` 442.
2026-11-14 HackcamPathCommandDispatch HackcamPathCommandDispatch anthropic/claude-opus-5-5:high: 9fec01 first-call arg: `params[3]` 1 (lh a1,166); `(s16)(params23 & 0xFFFF)` 1 (lw a1,56); `(u16)d` 1 (lhu a1,58; value change); bare d 1 (lw a1,56); `(s16)(u32)d` 5; `(s16)(d & 0xFFFF)` 28; `(s16)params23` 21; plain + `if (b)`/`if (c)` 5; `s16 d` local with bare uses 516 (431 without guard).
2026-11-14 HackcamPathCommandDispatch HackcamPathCommandDispatch anthropic/claude-opus-5-5:high: cfb83e coupled with 9fec01: no guard + bare d (C13) full=1, only `lw a1,56(sp)` vs `lh a1,58(sp)` at 0x1370; no guard + `(s16)(params23 & 0xFFFF)` 1; no guard + `params[3]` / `(u16)d` 411; no guard + `(s16)params23` 416; no guard + plain `(s16)d` 403.
2026-11-14 HackcamPathCommandDispatch HackcamPathCommandDispatch anthropic/claude-opus-5-5:high: reconstruct hack-free (a-first decode, no p, no guard, bare d at call 1) full=44: T1 slot 0x40 vs 0x44 everywhere (43 lines) + lw/lh at 0x1370; same body with b-first decode 48; with plain `(s16)d` at call 1 445-449.

## Untried ideas
- A spelling of the first case-0x2F argument that keeps T3 a bare (precoloured) item yet loads it with `lh` at +2 (cvtl not CSEd); every single-cast spelling either becomes the shared cvtl or the bare `lw` (this dossier).
- A natural statement before `b = ...` whose ushr is a real use (only the case-0x11 `screenWipeStart` use exists; this dossier).
- uopt_trace of R1 (hack-free, 44) to name which extra item takes the 0x44 bit before T1 (Q0553 says E_a).

## Evidence
- Frame 0xA8; s0 = a (sign-extended high half of arg1, `move s0,t7` at 0x354); T1 @0x44, T2 @0x3C, T3 @0x38 spilltemps, stored at 0x37c/0x384/0x38c; E_u in a1 (0x338) used at 0x8fc.
- Case 0x2F: call 1 `(s16)a` via `sll a0,s0,16; sra t8,a0,16; move a0,t8` (0x1360-0x1368), arg2 `lh a1,58(sp)` at 0x1370; call 2 `lw a0,68(sp)` (unconverted b, 0x1374) + `lh a1,58(sp)` 0x1384; call 3 `lh a0,62(sp)` 0x138c + `lh a1,58(sp)` 0x139c.
- Case 0xB `zoneEntrySpawnEffect` narrows T3 as `lh a3,58(sp)` at 0x8ec (separate block, no CSE).

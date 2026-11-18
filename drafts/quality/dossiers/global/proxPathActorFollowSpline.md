# proxPathActorFollowSpline (global, src/global/133A90.c)
## Sites
global:80730408:other:be5097 other (FIXED 2026-11-17): `f32 one;` value-named 1.0f local (FAKE). Its only load-bearing effect: `state->unk148 = one;` before the actor position lerp stops uopt folding `(p2[i] - unk13C) * unk148` to a plain add (mul.s $f4,$f10,$f18 at 0x1820 kept); its slot was the unused frame word sp+0x284. Replaced by `state->unk148 = 1.0;` (double literal) + `pad1[21]`.
## Attempts
2026-11-11 round 16 CleanGlobal133A90 (opus-5-5:low): removal fdiff=1; uopt_trace frame 0x288->0x280; permute best=0 only via alias temp (steer).
2026-11-11 round 16 Rev16F (opus-5-5:xhigh): 1.0f at all five uses + pad0: copy colours the one web uopt 29 ($f18); permute best 120 (volatile pad + double cast).
2026-11-12 round 20 Rev20C (opus-5-5:low): no one: frame -8; pad1[21]: 1.0 literal pair $f19/$f18 -> $f5/$f4; permute best=0 re-inserts the local.
2026-11-12 round 23 Rev23B (opus-5-5:low): inlining 1.0f rematerialises per store, text -16, locals shift 4; permute still rematerialises.
2026-11-17 2026-11-17: cleanup CleanproxPathActorFollowSpline CleanproxPathActorFollowSpline (anthropic/claude-opus-5-5): per-use measurement: local only at the first unk148 store -> full 0; local only at the clamp store or only at the guRotateF axes -> full 138; one at every f32 1.0f use incl. `b = 1.0f` -> fdiff 0 (lead question). Literal type at the first store: `1.0f` -> 138 (mul.s at 0x1820 folded away), `1.0` -> fdiff 0, `1` -> full 0; every f32 1.0f written `1.0` -> fdiff 0; additionally 0.0f -> 0.0 -> full 0; without the frame word (no pad) -> full 76. Kept fix: `state->unk148 = 1.0;` at both unk148 stores, guRotateF axes/b `1.0f`, `pad1[21]`: fdiff 0, uninit 0, warnings 0. FAKE 1 -> 0.
2026-11-17 same unit: review: `a = a + 1.0` / `b = b - 1.0` -> `+=` / `-=` (fdiff 0); dropping the `(s16)` casts of the pathYaw lerps is neutral (full 0, kept); cast `(f32 (*)[4])state->unk15C` retires with PlayerState.unk15C `u8[0x40]` -> `f32[4][4]` (shadow-header compile equal to expected, `.scratch/CleanproxPathActorFollowSpline/hdr/`).
## Untried ideas
none for the removed site. Header request PlayerState.unk15C -> f32[4][4] (hdr/actor_unk15C.patch) retires the last cast.
Field names (session close): PlayerState.unk13C/unk140/unk144 -> attachX/attachY/attachZ, unk148 -> attachBlend, unk15C -> attachMtx (proxPathAttachToSegment stores the actor position, 0.0f and memcpy of modelMtx; this function ramps unk148 by 0.1 to 1.0 and lerps prevMtx(unk15C)->curMtx by 1.0 - unk148).
## Evidence
- Frame 0x288; a0 home 0x288, a2 0x290, a3 0x294, t 0x298; p0 sp+0x210, p1 sp+0x21C, p2 sp+0x228, pad1 sp+0x234..0x287 (was pad1[20] at 0x234..0x283 + one at 0x284, never accessed).
- 0x17f4-0x1808: lwc1 $f6,0x148(s1) (savedScale, spilled to 0xD0(sp)); lui at,0x3f80; mtc1 at,$f18; swc1 $f18,0x148(s1).
- 0x181c-0x1828: sub.s $f10,$f8,$f0; mul.s $f4,$f10,$f18; add.s $f6,$f4,$f0; swc1 $f6,0x7C(v0): actor->x lerp multiplies by the forwarded stored value; y and z reload 0x148(s1) (0x1834, 0x1850) after the actor->x / actor->y stores.
- 1.0f is rematerialised at every use: 0x17a4 (b, lui at + mtc1 $f14), 0x1930/0x19f8 (lui a3,0x3f80 guRotateF y axis), 0x1970 (lui a2,0x3f80), 0x1ba0/0x1bc4 (clamp store). No register-held 1.0f across calls.
- Double 1.0 constants (lui 0x3ff0 pairs): 0x16f0 (a + 1.0), 0x1734 (b > 1.0, b - 1.0), 0x1b04 (savedScale < 1.0), 0x1b44 (1.0 - unk148), 0x1b90 (unk148 > 1.0).

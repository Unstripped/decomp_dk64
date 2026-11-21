# tagBarrelCheckProximityAndFall (global, src/global/80150.c)
## Sites
global:8067BF84:volatile:de1b02 volatile: `volatile u8 spawn` keeps a byte home at sp+0x47 with per-use sb/lbu.
## Attempts
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: target read only (no new compile): the store-then-reload of a known constant rules out non-volatile spellings -> nohit
2026-11-18 2026-11-18: cleanup CleantagBarrelActorUpdate CleantagBarrelActorUpdate anthropic/claude-opus-5-5 (variants.py try): memory-resident non-volatile storage. `u8 spawn[1]` (all uses spawn[0]) -> full=57; `u8 spawn[8]` in place of spawn and `s32 pad[2]`, uses spawn[7] at sp+71 -> full=55: the store-then-reload `sb t2,71(sp)` / `lbu ..,71(sp)` at 0xbf8/0xbfc survives (uopt does not forward a store to a local array element into the next load), but the reload is coloured v0 instead of t3 so `beqzl t3` at 0xc00 becomes `beqz v0` + nop, the t ring shifts by one (t3..t6 -> t2..t5) and the loop counter's spill home moves 59(sp) -> 63(sp); `struct { u8 v; } spawn` -> full=74, the same as plain `u8 spawn` (a one-member struct is promoted like a scalar).
2026-11-20 2026-11-20: cleanup CleantagBarrelCheckProximityAndFallc CleantagBarrelCheckProximityAndFallc anthropic/claude-opus-5-5 (re-measure after Part H2 `extern s32 D_8071FE08` -> `extern EffectGridAsset D_8071FE08`, base 6064fcc9; fdiff + uopt_trace -l 6): plain `u8 spawn` -> frame 0x48 -> 0x68, text +16, cand 0 piece 126 = $s0 (spill sw s0,0x3c(sp)), join folds to `li s0,1`; `s32 spawn` stays uncoloured at 0x44(sp) and differs only in width (9 sw/lw vs sb/lbu lines). Unchanged from the 2026-11-11/12 measures; the extern only reaches the `&D_8071FE08` argument at 0xde0-0xdf8 -> nohit
## Untried ideas
dead `if (0) { f(&spawn); }` address escape (Q0300) would be another hack: not worth trying.
## Evidence
0xb64 sb zero,0x47(sp); 0xbf8 sb t2,0x47(sp) (=1) then 0xbfc lbu t3,0x47(sp) on a join whose predecessors both store 1; 0xce0/0xce8 sb; 0xd3c lbu; 0xe50 lbu v0,0x47(sp) return.
0xb90 lw s0,0x54(sp): `triggered` (a3 home) lives in $s0, so `spawn` cannot take $s0 (a coloured spawn displaces it). `s32 spawn` reproduces every op at word width (sw/lw 0x44(sp) at 0xb64 0xbf0 0xbf8 0xbfc 0xc04 0xce0 0xce8 0xd3c 0xe50): only the byte width needs the volatile.

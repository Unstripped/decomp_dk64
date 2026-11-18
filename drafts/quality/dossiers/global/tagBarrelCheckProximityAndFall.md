# tagBarrelCheckProximityAndFall (global, src/global/80150.c)
## Sites
global:8067BF84:volatile:de1b02 volatile: `volatile u8 spawn` keeps a byte home at sp+0x47 with per-use sb/lbu.
## Attempts
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: target read only (no new compile): the store-then-reload of a known constant rules out non-volatile spellings -> nohit
2026-11-18 2026-11-18: cleanup CleantagBarrelActorUpdate CleantagBarrelActorUpdate anthropic/claude-opus-5-5 (variants.py try): memory-resident non-volatile storage. `u8 spawn[1]` (all uses spawn[0]) -> full=57; `u8 spawn[8]` in place of spawn and `s32 pad[2]`, uses spawn[7] at sp+71 -> full=55: the store-then-reload `sb t2,71(sp)` / `lbu ..,71(sp)` at 0xbf8/0xbfc survives (uopt does not forward a store to a local array element into the next load), but the reload is coloured v0 instead of t3 so `beqzl t3` at 0xc00 becomes `beqz v0` + nop, the t ring shifts by one (t3..t6 -> t2..t5) and the loop counter's spill home moves 59(sp) -> 63(sp); `struct { u8 v; } spawn` -> full=74, the same as plain `u8 spawn` (a one-member struct is promoted like a scalar).
## Untried ideas
dead `if (0) { f(&spawn); }` address escape (Q0300) would be another hack: not worth trying.
## Evidence
0xb64 sb zero,0x47(sp); 0xbf8 sb t2,0x47(sp) (=1) then 0xbfc lbu t3,0x47(sp) on a join whose predecessors both store 1; 0xce0/0xce8 sb; 0xd3c lbu; 0xe50 lbu v0,0x47(sp) return.

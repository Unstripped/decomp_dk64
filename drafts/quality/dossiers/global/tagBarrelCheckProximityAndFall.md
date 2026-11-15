# tagBarrelCheckProximityAndFall (global, src/global/80150.c)
## Sites
global:8067BF84:volatile:de1b02 volatile: `volatile u8 spawn` keeps a byte home at sp+0x47 with per-use sb/lbu.
## Attempts
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: target read only (no new compile): the store-then-reload of a known constant rules out non-volatile spellings -> nohit
## Untried ideas
dead `if (0) { f(&spawn); }` address escape (Q0300) would be another hack: not worth trying.
## Evidence
0xb64 sb zero,0x47(sp); 0xbf8 sb t2,0x47(sp) (=1) then 0xbfc lbu t3,0x47(sp) on a join whose predecessors both store 1; 0xce0/0xce8 sb; 0xd3c lbu; 0xe50 lbu v0,0x47(sp) return.

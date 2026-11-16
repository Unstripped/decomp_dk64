# __n_sndpPostPitch (global, src/global/13A7A0.c)
## Sites
global:80737028:punned-cast:639fc8 punned-cast: `ev.arg8.i = *(s32 *)&pitch` steers the store of pitch's bits into ev.arg8 through an int register (addiu &pitch + lw 0(t2) + sw), instead of lwc1/swc1.
## Attempts
2026-11-11 CleanGlobal13A7A0 anthropic/claude-opus-5-5:low: `ev.arg8.f = pitch` -> lwc1/swc1, fdiff 1; permute: best only duplicates ev.state store.
2026-11-11 Rev16C/Rev16F anthropic/claude-opus-5-5:xhigh: diagnose nohit (IDO 7.1 -g, no uopt_trace); permute best 324; review: pun is the original spelling (Q0628).
2026-11-12 Rev18A anthropic/claude-opus-5-5:low: same diagnosis; permute best only folds temp, still float store.
2026-11-14 OwnerSndpLibaudioTypes: keyMap->pitchFine -> detune; FAKE text kept.
2026-11-16 Hack__n_sndpPostPitch anthropic/claude-opus-5-5:high: retagged `// ORIG:` with object offsets 0x15c8/0x15cc/0x15d0 -> fdiff 0, sweep: no sites. Alternatives (variants try, full score): union-local read 3, s32* local 4, f32* local + .f 4, `.f = *(f32 *)&pitch` 2, `.f = pitch` 3, `*(u32 *)&pitch` 0 (same pun).
## Untried ideas
none open; site closed as ORIG.
## Evidence
expected/build/src/global/13A7A0.o (function at 0x1588, -g, IDO 7.1): 0x15b4 swc1 $f6,0x1c(sp) (pitch home); 0x15c8 addiu t2,sp,0x1c; 0x15cc lw t3,0(t2); 0x15d0 sw t3,0x28(sp) (ev at 0x20, arg8 at +8). At -g the unfolded addiu+lw 0(reg) is only produced by taking the local's address (Q0628).

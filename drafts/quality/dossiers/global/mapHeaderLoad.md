# mapHeaderLoad (global, src/global/2F550.c)
## Sites
global:8062F050:other:a01a33 `mapTreeRelocate((MapBspNode *)(s32)(D_807F5DE0 + off30), (s32)(D_807F5DE0 + off30), ...)`: REMOVED. Now `mapTreeRelocate((MapBspNode *)((s32)D_807F5DE0 + off30), (s32)D_807F5DE0 + off30, (s32)D_807F5DE0 + off34);`.
## Attempts
2026-11-09 CleanD5E10: views/names/review. Rounds 9/10: retype work on warning lines (other owners). 2026-11-13 round 35 CleanGlobal55B20: diagnose (the hop is a ucvt web colouring a1), D_807F5DE4 argument, permute (best 15, loads reformatted).
2026-11-14 HackmapHeaderLoad opus:high: plain pointer sums 2 lines (addu a0 / move a1,a0); D_807F5DE4 argument 66; MapBspNode * root snapshot local for D_807F5DE4 and the call 72, with pad[4] 71; s32 root local 72/71; local only at the call 16, with pad[4] 5; callee base retyped u8 * (both relocation spellings) or MapBspNode * with PROTO_SKIP stand-in: 2; integer address arithmetic at the call: 0 (also with the dl argument left as (s32)(D_807F5DE0 + off34), and with off30 + (s32)D_807F5DE0).
## Untried ideas
none.
## Evidence
0x4a08 addu a1,v0,t8 (base = header + off30); 0x4a0c move a0,a1 (node).

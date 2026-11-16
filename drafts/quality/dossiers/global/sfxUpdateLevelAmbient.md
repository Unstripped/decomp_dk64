# sfxUpdateLevelAmbient (global, src/global/7130.c)
## Sites
global:80603450:dead-if:e3f7b2 dead-if: FIXED (HacksfxUpdateLevelAmbient3). Case-7 `if (D_8077058C[0] == 0) {}` steered the &D_8077058C/&D_8077058D address webs; gone once D_8077058D/E are spelled D_8077058C[1]/[2].
global:80603450:dead-if:019582 dead-if: FIXED (same lever). `if (D_8077058D && D_8077058D) {}` in the pitch-step loop kept &D_8077058D out of $s4 (lui s4/addiu s4 at 0x1908); the target uses lui t6 at 0x1914 + lbu t6,0(t6) at 0x1924.
global:80603450:dead-store:93489e dead-store: FIXED. `k = 4` before seqSetVolumeInstant(0, 1.0f) stopped the `k = 0` init of the 4-trip gSeqPlayers loop hoisting (move s0,zero at 0x19e0); a dedicated `s16 seq` index declared beside `s16 sfxId` (they share one 4-byte slot, frame stays 0xe8) does the same (Q0983).
global:80603450:other:417de3 other: `for (k = 0, n = emitterCount; k < n; k++)`. Target: emitterCount in $s1 (li s1,N per switch arm 0x1088..0x1194), `move s3,s1` at 0x1254 (bnez delay slot), guard blez s1 at 0x1268, loop bound $s3. `k < emitterCount` colours emitterCount $s3 everywhere (text 17).
global:80603450:other:1ce947 other: `&emitters[0] + k` keeps base-first addu (lw t4,192(sp) emitters; k*14 in t5) at 0x129c-0x12ac; `&emitters[k]` swaps t4/t5 (text 4).
global:80603450:dead-if:ac34ba dead-if: `if (D_80770DE8 && D_80770DE8) {}` after the ambient block keeps the spilled &D_80770EB8[group] (v0 = s3 + t0 at 0x1e44) at 0x9c(sp) (sw 0x1e5c, lw t0 0x1ffc/0x2014/0x2024); without it 0xa0(sp) (text 4).
global:80603450:other:81cded other (key changes with the D_8077058C[2] spelling, see keymap.txt): `count = D_8077058C[2]` reuses the u32 emitter-count local for the reverb level; a dedicated u32 level local is code-identical except the frame 0xe8 -> 0xf0 (all byte locals +8).
global:80603450:dead-if:70c91e dead-if: `if (D_80770DC8) {}` in the pause arm (adds two blocks); without it &D_80770DC8 (uopt candidate 589) is coloured $s2 (lui s2/addiu s2 at 0x15ac/0x15c0/0x15ec); target stores through lui at per access (0x15ac/0x15bc/0x1670).
## Attempts
2026-11-15 HacksfxUpdateLevelAmbient2 opus-5-5:high: see history (function-local static D_8077058D/D_80770DC8 text-identical; separate level local; loop shapes; Q0816 member form; permuter 22734 iterations) -> fdiff 1.
2026-11-16 HacksfxUpdateLevelAmbient3 opus-5-5:high: Q0908 classify of 019582/70c91e (operand -> 1/live local/other global/same global): only the same global matches (class 2) -> nohit.
2026-11-16 HacksfxUpdateLevelAmbient3: D_8077058D -> D_8077058C[1] (+ D_8077058E -> D_8077058C[2]) -> e3f7b2 + 019582 unnecessary; leftover beq v0,t6 vs beq t6,v0 at 0x1928 fixed by `D_8077058C[1] != D_8077058C[2]` (Q0860) -> fdiff --reloc-ok 0.
2026-11-16 HacksfxUpdateLevelAmbient3: seq-player loop index candidates: group text 19, sfxId reuse 0 (reused local), fresh s16 seq beside sfxId 0 (kept), at pad/first/last 50, other widths 2..219 -> 93489e fixed.
2026-11-16 HacksfxUpdateLevelAmbient3: level local placements (pad, after pad, after count/sfxId/seq/volume, first, last, n's slot, block scopes) x widths -> best u32 (frame +8) / u8 (andi) -> nohit.
2026-11-16 HacksfxUpdateLevelAmbient3: D_80770DC8/DCA/DCB as u8 array -> text 82..127; D_80770DE8/DEC as f32 array -> text 140 -> rejected.
2026-11-16 HacksfxUpdateLevelAmbient3: reconstruct (no dead tests, k < emitterCount, &emitters[k], u32 level in n's slot, seq, array spelling) text 39; + function-local static D_80770DC8 text 25 -> fdiff 1.
## Untried ideas
7130 .bss carve (pending.md, Lead6): 7130 owns 0x80770560-0x80770DF0; D_80770DC8 as a function-local static retires 70c91e (still text-identical under the array spelling, only .bss offsets differ). D_8077058D is no longer part of that request.
Retire the D_8077058E split label in the other 7130 users (sfxPlayWithRandomPan, sfxPlayAtPosition, sfxPlayAtPositionForPlayer, seqLoadAndPlayWithReverb) as D_8077058C[2] (polish item; each needs its own fdiff --reloc-ok).
## Evidence
0x31b8-0x31d4 (audioResetAll): lui/addiu v0,D_8077058C once, sb zero,0(v0)/1(v0)/2(v0) (0x31c8/0x31cc/0x31d4): D_8077058C is a u8[3] array, D_8077058D/E are its elements 1/2.
0x1914/0x1924: lui t6 + lbu t6,0(t6) for D_8077058C[1]; beq t6,v0 at 0x1928 (lower-numbered [1] on the left).
0x1254: move s3,s1 (n = emitterCount copy) in the bnez delay slot; 0x19e0: move s0,zero (seq loop init after the map 0xE calls).

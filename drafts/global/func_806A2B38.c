// func_806A2B38 (src/global/A7710.c): TEXT-IDENTICAL when the TU defines 'u64 D_807FC7D0;' (extern gives lo-first 2x lui). Needs .bss carve for A7710 at 0x807FC7D0 (+ u8 D_807FC7D8 used by func_806A2E30); only .bss size differs
/* func_806A2B38 (src/global/A7710.c): TEXT-IDENTICAL once this TU DEFINES the u64 (bss carve needed).
 * With `extern u64 D_807FC7D0;` IDO emits lui at twice (hi-first); with the object defined in the
 * same translation unit it emits the target's single `lui at,%hi(D_807FC7D0)`, `sw t1,4(at)`,
 * `sw t0,0(at)` in the jr delay slot. fdiff: TEXT OK, only ".bss size mismatch (built 16, expected 0)".
 * Needs a `.bss` split entry for A7710 at 0x807FC7D0 (16 bytes: u64 D_807FC7D0 + u8 D_807FC7D8, the
 * latter used only by func_806A2E30 as `lbu/sb`), next carve at 0x807FC7E0 (ACDC0's D_807FC7E0).
 */
u64 D_807FC7D0;

void func_806A2B38(Actor *actor) {
    D_807FC7D0 = osGetTime() - *(u64 *)actor->unk174;
}

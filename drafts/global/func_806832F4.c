// func_806832F4 (src/global/80150.c): Stage 5 (W2Webs): 6-line diff at return only (frame ok, 15 diff lines incl. rodata reloc noise). Target: T=&&-result web is v0 (sltu t3 ring temp; beqz t3; move v0,t3; lw v0,0x24; sltiu t4; move v0,t4), ours T coloured v1 + beqzl + trailing move v0,v1 (uopt -l 5: T temp cand forbidden v0, compare cand 27 'uneq(sp28,0)' = redundant with the first if test). Tried: first-test spellings (!=0, bare, 0!=, !!, ==0 else, !x else) x 10 tail spellings (70), ret locals replacing pad (tmp/two-def/x0/f/g/h/a-e; ret=sp28!=0; ret=ret&&(sp24==0) makes the first leg a ring temp t3 like the target but adds an extra sltu v1 and T stays v1; promoted ret drops the pad slot -> frame 0x28), temp r = call result (copy-propagated away), decl order perms (24). permuter setup fails on the jump table.
s32 func_805FEF10(void *);

s32 func_806832F4(s32 arg0, s32 arg1) {
    s32 pad;
    s32 sp28;
    s32 sp24 = 0;
    struct {
        char unk0[2];
        s16 unk2;
    } sp20;

    switch (D_8076A0A8) {
    default:
        return 0;
    case 7:
    case 26:
    case 30:
    case 38:
    case 42:
    case 48:
        sp28 = func_805FEF10(&sp20);
        if (sp28 != 0) {
            sp24 = flagGet(sp20.unk2, 0);
            if (arg1 != 0 && sp24 == 0) {
                flagSet(sp20.unk2, 1, 0);
                camStartPath(D_807FBB4C, 0x19, 4);
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk155[0] = 0xB;
            }
        }
        return (sp28 != 0) && (sp24 == 0);
    }
}

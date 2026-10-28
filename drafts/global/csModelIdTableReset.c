// func_8063D930 (src/global/42630.c): CsNM1 stage 6 (text identical, deadsweep text=0): matches ONLY when the TU DEFINES 'u8 D_807F66F0[0x212];' (bss owned by this TU): as1 then shares one 'lui at' for the two peeled sb stores (extern symbol gives 'lui at; sb; lui at; ... sb' and peels before the preheader). Remaining diff is reloc-only (expected names D_807F66F1/D_807F66F2/D_807F6902 vs D_807F66F0+off) + bss definition clash with asm/global/data/165D50_807F5D30.bss.s (needs a bss split for this TU before it can be merged). Loop 2 must be on ONE source line. Tried: all loop forms, pointer forms, deadsweep (+array forms), permuter 600s (permuter drops the one-line form, no gain).
extern s16 D_807F6240[];
u8 D_807F66F0[0x212];

void func_8063D930(void) {
    s32 i = 0;
    s32 j;

    do {
        D_807F6240[i] = -1;
        i++;
    } while (&D_807F6240[i] < (s16 *)D_807F66F0);
    for (j = 0; j < 0x212; j++) { D_807F66F0[j] = 0; }
}

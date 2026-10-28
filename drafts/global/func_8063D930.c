// func_8063D930 (src/global/42630.c): stage 5: same frame (leaf, none). Loop 1 (do-while, &D_807F6240[i] < (s16*)D_807F66F0, 's32 i = 0' decl) matches exactly, loop 2 body matches only with the whole 'for' on ONE source line (multi-line gives delay-slot sb -4 instead of sb -1). Remaining: peeled stores sb 0/sb 1 of D_807F66F0 are emitted BEFORE the loop-2 preheader (lui at; sb; lui at; lui v1; lui v0; addiu; addiu; sb) instead of target 'lui at; lui v1; lui v0; addiu v0 (D_807F6902); addiu v1 (D_807F66F2); sb 0(at); sb 1(at)' (1 insn bigger). Tried: explicit [0]/[1] stores (CSE with loop-1 end la -> sb 0(a0)), separate symbols D_807F66F1/D_807F66F2 (13 diff lines, sb via a0), pointer loops (runtime remainder), manual unroll (unrolled 4x again), deadsweep (no gain).
extern s16 D_807F6240[];
extern u8 D_807F66F0[];

void func_8063D930(void) {
    s32 i = 0;
    s32 j;

    do {
        D_807F6240[i] = -1;
        i++;
    } while (&D_807F6240[i] < (s16 *)D_807F66F0);
    for (j = 0; j < 0x212; j++) { D_807F66F0[j] = 0; }
}

// faultDrawRegs (src/global/136820.c): faultDrawRegs (src/global/136820.c): stage 6, 113 insns, frame matches, diff 5 (park 14 -> 5 with FAKE 'if (D_807563B8 && D_807563B8) {}' in loop). Left: guard load of D_807563B8 takes v0 (target t0 with t9 burned before) and D_807FF018 loads t9/t3 vs t1/t2. Tried: self-assign/narrowing-chain defs, ctx spellings, decl/store/hdr permutations (54), ent pointer local for D_807FEF88, cast spellings of pc/ra, 20k-eval dead-test hill-climb
typedef struct {
    s32 unk0;
    s32 unk4;
} Ga136820Entry;

extern s32 D_807FF018;
extern Ga136820Entry D_807FEF88[];
extern s32 D_807563B8;
extern u8 D_807FF01C;
extern s32 D_807FF020;
extern s32 D_807FF024;
extern s32 D_807FF028;
extern char *D_80756360[];
void faultUnwindStack(OSThread *a0);

void faultDrawRegs(OSThread *a0) {
    s32 y;
    s32 x;
    s32 j;
    __OSThreadContext *ctx;

    D_807FEF78 = 2;
    D_807FEF84 = 0xFFFF;
    D_807FEF86 = 1;
    ctx = &a0->context;
    for (y = 0, x = 0; y != 24; y += 6, x += 18) {
        D_807FEF7C = x;
        D_807FEF70 = x;
        D_807FEF74 = y;
        faultPrintf("DK 64\n");
        faultPrintf("%X\n", (s32)ctx->pc);
        faultPrintf("%X\n", (s32)ctx->ra);
        if (D_807563B8 && D_807563B8) {}  // FAKE: steers uopt/ugen temp ring of the guard load (deadsweep)
        if (D_807563B8 >= 4) {
            for (j = 0; j < D_807FF018; j++) {
                faultPrintf("%X\n", D_807FEF88[j].unk0);
            }
        }
    }
    if (D_807FF01C != 0) {
        faultPrintf("%s %x %x %x", D_80756360[D_807FF01C], D_807FF020, D_807FF024, D_807FF028);
    }
    if (D_807563B8 < 4) {
        D_807563B8++;
    }
    if (D_807563B8 == 4) {
        faultUnwindStack(a0);
    }
}

// func_80731E68 (src/global/136820.c): stage 6: identical except temp register numbering (first lw D_807563B8 uses t9, expected t0; later temps shifted); loops/stores/s-regs/frame all match; tried x/y vs i*18, chain stores, ctx casts, j-loop forms, permuter 4+10min
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
void func_80732158(OSThread *a0);

void func_80731E68(OSThread *a0) {
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
        func_80731D20("DK 64\n");
        func_80731D20("%X\n", (s32)ctx->pc);
        func_80731D20("%X\n", (s32)ctx->ra);
        if (D_807563B8 >= 4) {
            for (j = 0; j < D_807FF018; j++) {
                func_80731D20("%X\n", D_807FEF88[j].unk0);
            }
        }
    }
    if (D_807FF01C != 0) {
        func_80731D20("%s %x %x %x", D_80756360[D_807FF01C], D_807FF020, D_807FF024, D_807FF028);
    }
    if (D_807563B8 < 4) {
        D_807563B8++;
    }
    if (D_807563B8 == 4) {
        func_80732158(a0);
    }
}

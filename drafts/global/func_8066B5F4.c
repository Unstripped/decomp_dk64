// func_8066B5F4 (src/global/6AD90.c): DMA asset loader and sparse switch (4/7/14/25); all logic and switch matched, IDO hoisted arg0 << 2 into $s0 instead of stack spill
extern s32 D_8000DDCC;
extern u32 *D_807F9520;
extern void *D_807F9528[];

void func_8066B5F4(arg0)
s32 arg0;
{
    u64 sp48;
    u32 sp40;
    u32 sp3C;

    if (D_807F9528[arg0] != NULL) {
        return;
    }
    sp3C = 8;
    func_8060B140(D_8000DDCC + D_807F9520[arg0], &sp48, &sp3C, 0, 0, 0, 0);
    sp40 = (sp48 >> 32) - D_807F9520[arg0];
    D_807F9528[arg0] = func_80610FE8(sp40);
    func_8060B140(D_8000DDCC + D_807F9520[arg0], D_807F9528[arg0], &sp40, 0, 0, 0, 0);
    switch (arg0) {
        case 4:
        case 7:
        case 14:
        case 25: {
            u32 i;
            D_807F95A8[arg0] = func_80610FE8(sp40);
            for (i = 0; i < (u32)(sp40 / 4); i++) {
                D_807F95A8[arg0][i] = 0;
            }
            break;
        }
        default:
            D_807F95A8[arg0] = NULL;
            break;
    }
}

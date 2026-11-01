// func_80731030 (src/global/135D30.c): stage 6: text-identical (15/15 insns) when D_807FDD90 is TU BSS; relocs D_807FDD90+off vs splat labels D_807FDD91/2/E
u8 D_807FDD90[14];

void func_80731030(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        D_807FDD90[i] = 0;
    }
}

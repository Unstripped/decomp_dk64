// func_80731030 (src/global/135D30.c): text 22/22 insns; target keeps lui at shared for the two prologue sb's + D_807FDD92 loop, mine hoists D_807FDD90 base into a0 (3 uses); reloc names D_807FDD91/D_807FDD9E are labels (reloc-only anyway)
extern u8 D_807FDD90[14];
extern u8 D_807FDD92[12];

void func_80731030(void) {
    s32 i;

    D_807FDD90[0] = 0;
    D_807FDD90[1] = 0;
    for (i = 0; i < 12; i++) {
        D_807FDD92[i] = 0;
    }
}

// func_8063C390 (src/global/41090.c): text-identical, reloc only: C unrolled loop matches instruction-for-instruction; expected relocates end bound as D_80747E00 (splat symbol) vs ours D_80747D80+0x80. Stage 6 done; ROM-identical, orchestrator to paste.
typedef struct {
    void (*unk0)();
    void (*unk4)();
    void (*unk8)();
    u8 unkC;
} R41090aEntry;

extern R41090aEntry D_80747D80[8];

void func_8063C390(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_80747D80[i].unkC = 0;
    }
}

// func_8063C450 (src/global/41090.c): text-identical, reloc only: expected end bound D_80747E00 vs ours D_80747D80+0x80 (pointer-bound loop with extern D_80747E00 changes codegen, tried). ROM-identical, orchestrator to paste.
typedef struct {
    void (*unk0)();
    void (*unk4)();
    void (*unk8)();
    u8 unkC;
} R41090aEntry;

extern R41090aEntry D_80747D80[8];

void func_8063C450(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_80747D80[i].unkC != 0) {
            D_80747D80[i].unk8();
        }
    }
}

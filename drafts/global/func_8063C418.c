// func_8063C418 (src/global/41090.c): text-identical, reloc only: expected relocates lw as D_80747D84 offset 0, ours D_80747D80+4. ROM-identical, orchestrator to paste.
typedef struct {
    void (*unk0)();
    void (*unk4)();
    void (*unk8)();
    u8 unkC;
} R41090aEntry;

extern R41090aEntry D_80747D80[8];

void func_8063C418(s32 arg0, s16 arg1) {
    D_80747D80[arg1].unk4(arg0);
}

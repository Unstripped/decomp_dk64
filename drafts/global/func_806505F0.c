// func_806505F0 (src/global/54150.c): ModelA 2026-10-29: text-identical, reloc only. Counted index loop over D_807F6960[i] (unk0 != 0 && unk8 == arg0) matches the unroll-by-4 and registers; end pointer relocs as D_807F6960+0x280, expected D_807F6BE0.
typedef struct MtxCopyRequest {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[3];
} MtxCopyRequest;

extern MtxCopyRequest D_807F6960[];

void func_806505F0(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 != 0 && D_807F6960[i].unk8 == arg0) {
            D_807F6960[i].unk0 = 0;
        }
    }
}

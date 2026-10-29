// func_806506E8 (src/global/54150.c): ModelA 2026-10-29: text-identical, reloc only. Counted index loop over D_807F6960[i] reproduces the hoisted-address order; end pointer relocs as D_807F6960+0x280, expected D_807F6BE0.
typedef struct MtxCopyRequest {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[3];
} MtxCopyRequest;

extern MtxCopyRequest D_807F6960[];

extern u8 D_807444FC;
extern u8 D_807F6BEC;
void *memcpy(void *, const void *, unsigned int);

void func_806506E8(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 == arg0 && D_807F6960[i].unkC == D_807444FC) {
            memcpy((void *)D_807F6960[i].unk8, (void *)D_807F6960[i].unk4, 0x40);
            D_807F6960[i].unk0 = 0;
            D_807F6BEC = 1;
        }
    }
}

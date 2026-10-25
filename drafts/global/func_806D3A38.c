// func_806D3A38 (src/global/D5E10.c): text-identical, reloc only: 0.2f literal (lwc1 from D_8075CD10) is .rodata+0x20 vs symbol in expected; rest identical
typedef struct G10Actor {
    /* 0x000 */ u8 pad0[0x155];
    /* 0x155 */ u8 unk155;
} G10Actor;

typedef struct G10Player {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
} G10Player;

#define G10_A ((G10Actor *)D_807FBB40)
#define G10_P ((G10Player *)D_807FD580)

void func_8061C464(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_806D38AC();

void func_806D3A38(void) {
    if (G10_A->unk155 == 0) {
        func_8061C464(G10_P->unk104, D_807FBB40, 4, 0x800, 0x32, 0, 5, 0x32, 0x14, 0, 0.2f);
        G10_A->unk155++;
    }
    func_806D38AC(0x3D);
}

// func_806915B0 (src/global/936B0.c): regalloc/hoisting: loop preheader move s1,zero ordering
u32 func_806119A0(void);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714950(s32);
void func_80714998(s32);
void func_8071498C(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
extern u8 D_80750AD0;
extern s32 D_8071FFA0;
void func_80717D4C(void);

void func_806915B0(void) {
    s32 count;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 spSpawnerArg;

    if (D_80750AD0 != 0) {
        count = 3;
    } else {
        count = 6;
    }
    for (spSpawnerArg = 0, i = 0; i < count; i++, spSpawnerArg -= 0x14) {
        dx = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        dy = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        dz = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        func_807149B8(1);
        func_807149C8(0x8C, 0x8C, 0x8C, 0x64);
        func_80714950(spSpawnerArg);
        func_80714998(3);
        func_8071498C(func_80717D4C);
        func_80714CC0(&D_8071FFA0, 2.0f, D_807FBB40->unk7C + dx, D_807FBB40->unk80 + 42.0f + dy, D_807FBB40->unk84 + dz);
    }
}

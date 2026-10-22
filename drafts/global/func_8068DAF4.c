// func_8068DAF4 (src/global/90D80.c): matches in C; held back due to shared rodata order with func_8068D9DC and func_8068DBA4
Gfx *func_806FC530(Gfx *, s32, s16, s16, void *, s32);
int _sprintf();

extern Gfx D_1000118;

Gfx *func_8068DAF4(Gfx *arg0, u8 *arg1) {
    char sp38[8];

    Act90A_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Act90A_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    Act90A_WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFF96);
    _sprintf(sp38, "%d", *arg1);
    return func_806FC530(arg0, 3, 0x104, 0x50, sp38, 1);
}

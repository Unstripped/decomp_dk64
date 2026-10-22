// func_8068D9DC (src/global/90D80.c): regalloc difference on stack arg 1: t4/t5 vs t6/t8; nested func_806FC530
typedef struct Act90A_D9DC {
    char pad[0x14];
    /* 0x14 */ s32 unk14;
    char pad18[4];
    /* 0x1C */ s32 unk1C;
} Act90A_D9DC;

Gfx *func_806FC530(Gfx *, s32, s16, s16, void *, s32);
int _sprintf();

extern Gfx D_1000118;

Gfx *func_8068D9DC(Gfx *arg0, Act90A_D9DC *arg1) {
    char sp3C[12];
    char sp38[4];

    Act90A_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Act90A_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    Act90A_WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFF96);
    _sprintf(sp3C, "%d", arg1->unk14);
    arg0 = func_806FC530(func_806FC530(arg0, 3, 0x424, 0x50, sp3C, 1), 1, 0x50, 0x50, "HIT", 1);
    _sprintf(sp38, "%d", arg1->unk1C);
    return func_806FC530(arg0, 3, 0x50, 0xB0, sp38, 1);
}

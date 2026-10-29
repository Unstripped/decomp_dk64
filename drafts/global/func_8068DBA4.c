// func_8068DBA4 (src/global/90D80.c): 1 insn regalloc diff: li t4, 1 vs li t6, 1 on stack arg 1
typedef struct Act90A_D9DC {
    char pad[0x14];
    /* 0x14 */ s32 unk14;
    char pad18[4];
    /* 0x1C */ s32 unk1C;
} Act90A_D9DC;

Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, void *, s32);
int _sprintf(char *, const char *, ...);

extern Gfx D_1000118;

Gfx *func_8068DBA4(Gfx *arg0, Act90A_D9DC *arg1) {
    char sp34[12];

    Act90A_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Act90A_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    Act90A_WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFF96);
    _sprintf(sp34, "%d", arg1->unk14);
    return textDrawStringVtx(arg0, 3, 0x370, 0x50, sp34, 1);
}

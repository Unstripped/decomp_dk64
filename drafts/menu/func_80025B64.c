// func_80025B64 (src/menu/1AF0.c): TEXT-IDENTICAL, reloc only: string literals give .rodata+0x30/0x38 vs expected D_80033A80/D_80033A88. Needs 'Gfx *func_806FC530();' unprototyped (change the later decl at menuDrawTransformedWidgets too) and unused 's32 step;' + inlined ternary (permuter find) to get arg1 in s1. Orchestrator: check ROM hash.
typedef struct {
    char pad0[0x15F];
    u8 unk15F;
    char pad160[0x178 - 0x160];
    Struct_80025D14 *unk178;
} MenuM1_Wnd;
extern Gfx D_1000118[];
extern Mtx D_20000C0;
Gfx *func_806FC530();
char *func_8070E750(s32, s32, s32);
s32 _sprintf(char *, const char *, ...);

Gfx *func_80025B64(Gfx *dl, MenuM1_Wnd *arg1) {
    Struct_80025D14 *st = arg1->unk178;
    char buf[0x28];

    if (st->unkD == 1) {
        gSPDisplayList(dl++, D_1000118);
        gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gDPPipeSync(dl++);
        gDPSetCombineLERP(dl++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0);
        switch (st->unkE) {
        case 1:
            arg1->unk15F = 0;
            st->unkE = 5;
        case 5: {
            s32 diff = 0xFF - arg1->unk15F;
            s32 step;

            arg1->unk15F += diff >= 9 ? 8 : diff;
            gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, arg1->unk15F);
            _sprintf(buf, "q %s", func_8070E750(0x24, 0x10, 1));
            dl = func_806FC530(dl, 1, 0x1F4, 0x190, buf, 1);
            _sprintf(buf, "b %s", func_8070E750(0x24, 0x11, 1));
            dl = func_806FC530(dl, 1, 0x1F4, 0x1F4, buf, 1);
            break;
        }
        }
    }
    return dl;
}

// func_806F5CE4 (src/global/F9450.c): TEXT-IDENTICAL, reloc only: K&R def 'for (i=0;i<6;i++) if (arg0==D_80754264[i]) return 1; return 0;' (K&R needed: file has 's32 func_806F5CE4();' decl for the caller; cfe warning 630 at that no-arg call is harmless). Relocs differ only as D_80754264+4 vs D_80754268 label. Paste + ROM gate.
extern s32 D_80754264[];

s32 func_806F5CE4(arg0)
s32 arg0;
{
    s32 i;

    for (i = 0; i < 6; i++) {
        if (arg0 == D_80754264[i]) {
            return 1;
        }
    }
    return 0;
}

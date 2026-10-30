// func_806F5C30 (src/global/F9450.c): TEXT-IDENTICAL, reloc only (stage 6 done): 'for (i=0;i<7;i++) if (arg0==D_80754248[i]) return 1; return 0;' emits identical bytes; only relocs differ (D_80754248+4/+8 vs splat's D_8075424C/D_80754250 labels). Paste via drafts.py paste + ROM gate.
extern s32 D_80754248[];

s32 func_806F5C30(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (arg0 == D_80754248[i]) {
            return 1;
        }
    }
    return 0;
}

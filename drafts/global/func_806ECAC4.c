// func_806ECAC4 (src/global/EFDC0.c): stage 1 m2c starter; player/camera views and callee prototypes unresolved
? func_80614D90(void *);                            /* extern */
? func_80614E78(void *, ?, void **, void **);       /* extern */
extern ? D_80753D70;
extern ? D_80753D8C;
extern void *D_807FBB48;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806ECAC4(void) {
    f32 var_fv0;

    if ((D_807FC924 + (D_807FC929 * 0x2F0))->unk2C0 == 1) {
        var_fv0 = *(&D_80753D70 + (D_807FD584 * 4));
    } else {
        var_fv0 = *(&D_80753D8C + (D_807FD584 * 4));
    }
    D_807FBB48->unk154 = 0x5B;
    D_807FBB48->unk155 = 0;
    D_807FD580->unk10C = (s8) (s32) var_fv0;
    D_807FBB48->unk80 = (f32) (D_807FD580->unkF0 - (f32) D_807FD580->unk10C);
    D_807FBB48->unkEE = (s16) (D_807FBB48->unkF4 + 0x14);
    D_807FBB48->unkC0 = 0.0f;
    func_80614E78(D_807FBB48, 0x75, &D_807FBB48, &D_807FD580);
    func_80614D90(D_807FBB48);
}

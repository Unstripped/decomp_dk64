// func_806EC708 (src/global/EFDC0.c): stage 1 m2c starter; player/actor views and call prototypes unresolved
? func_80614D00(s32, ?, ?);                         /* extern */
? func_80614E78(void *, ?, void **);                /* extern */
extern ? D_807531FC;
extern ? D_80753908;
extern ? D_80753924;
extern ? D_80753940;
extern s32 D_80767CC0;
extern s32 D_807FBB40;
extern void *D_807FBB48;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806EC708(void) {
    D_807FBB48->unk154 = 0x51;
    D_807FBB48->unk155 = 0;
    D_807FD580->unk54 = (f32) *(&D_80753908 + (D_807FD584 * 4));
    D_807FD580->unk50 = 0;
    D_807FD580->unk38 = (f32) *(&D_807531FC + (D_807FD584 * 4));
    D_807FD580->unk2C = (f32) *(&D_80753924 + (D_807FD584 * 4));
    D_807FD580->unk30 = (f32) *(&D_80753940 + (D_807FD584 * 4));
    func_80614E78(D_807FBB48, 0x3E, &D_807FBB48);
    func_80614D00(D_807FBB40, 0x3F800000, 0);
    D_807FD580->unk58 = (s32) (D_80767CC0 - 0x1E);
}

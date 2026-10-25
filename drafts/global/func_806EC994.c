// func_806EC994 (src/global/EFDC0.c): stage 1 m2c starter; table types and float call prototypes unresolved
? func_80613AF8(void *, ?, ?, ?);                   /* extern */
? func_80614D00(void *, ?, ?);                      /* extern */
? func_80614E78(void *, ?);                         /* extern */
extern ? D_807534E4;
extern ? D_80753500;
extern ? D_8075351C;
extern void *D_807FBB48;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806EC994(void) {
    func_80614E78(D_807FBB48, 8);
    func_80614D00(D_807FBB48, 0x3F800000, 0);
    func_80613AF8(D_807FBB48, 0x2E, 0, 0x40C00000);
    D_807FBB48->unk154 = 0x46;
    D_807FBB48->unk155 = 0;
    D_807FD580->unk38 = (f32) *(&D_807534E4 + (D_807FD584 * 4));
    D_807FD580->unk2C = (f32) *(&D_80753500 + (D_807FD584 * 4));
    D_807FD580->unk48 = (s16) *(&D_8075351C + (D_807FD584 * 2));
    D_807FD580->unk4C = -1;
}

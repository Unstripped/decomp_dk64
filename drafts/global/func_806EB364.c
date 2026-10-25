// func_806EB364 (src/global/EFDC0.c): m2c starter; straight control flow
? func_80614E78(void *, ?);                         /* extern */
? func_80614EBC(void *, ?);                         /* extern */
? func_806CFF9C(s32);                               /* extern */
extern ? D_8074E77C;
extern void *D_807FBB40;
extern s32 D_807FBB48;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806EB364(void) {
    if (*(&D_8074E77C + D_807FC929) == 6) {
        func_806CFF9C(D_807FBB48);
        return;
    }
    D_807FBB40->unk154 = 0x3D;
    D_807FBB40->unk155 = 0;
    if (D_807FD580->unk4E == 0x22) {
        func_80614EBC(D_807FBB40, 0x131);
        return;
    }
    func_80614E78(D_807FBB40, 0xD);
}

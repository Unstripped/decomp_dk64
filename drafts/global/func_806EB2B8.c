// func_806EB2B8 (src/global/EFDC0.c): m2c starter; player state view needed
? func_80614EBC(void *, ?);                         /* extern */
? func_806CD424(s16, s32, s32, void **);            /* extern */
? func_806CFECC();                                  /* extern */
extern void *D_807FBB40;
extern void *D_807FD580;

void func_806EB2B8(void) {
    void *temp_v0;

    func_806CFECC();
    D_807FBB40->unk154 = 0x22;
    D_807FBB40->unk155 = 0;
    D_807FBB40->unkC0 = 100.0f;
    D_807FD580->unk50 = 0;
    D_807FD580->unk2C = 100.0f;
    temp_v0 = D_807FD580;
    if (temp_v0->unk3C == 0) {
        func_806CD424(temp_v0->unkA, temp_v0->unk4, temp_v0->unk38, &D_807FBB40);
    }
    temp_v0->unk2C = 10.0f;
    func_80614EBC(D_807FBB40, 0x17B);
}

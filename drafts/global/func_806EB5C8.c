// func_806EB5C8 (src/global/EFDC0.c): m2c starter; switch and player field widths
? func_80614E78(void *, ?);                         /* extern */
extern ? D_8074E77C;
extern void *D_807FBB40;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806EB5C8(void) {
    u8 temp_t7;

    temp_t7 = *(&D_8074E77C + D_807FC929);
    switch (temp_t7) {
    case 0:
    case 1:
    case 2:
        D_807FBB40->unkC0 = 50.0f;
        D_807FBB40->unkC4 = -2.5f;
        break;
    case 3:
        D_807FBB40->unkC0 = 140.0f;
        D_807FBB40->unkC4 = -20.0f;
        break;
    case 4:
    case 5:
        D_807FBB40->unkC0 = 40.0f;
        D_807FBB40->unkC4 = -7.0f;
        break;
    }
    D_807FBB40->unk154 = 0x2A;
    D_807FBB40->unk155 = 0;
    func_80614E78(D_807FBB40, 0x43);
    D_807FD580->unk64 = 0;
    D_807FD580->unkC8 = 0x32;
}

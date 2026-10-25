// func_806ED050 (src/global/EFDC0.c): stage 1: m2c reconstruction of conditional state change; needs player-state view and s16 table declarations
? func_80614E78(void *, ?);                         /* extern */
extern ? D_8074E77C;
extern ? D_8075380C;
extern void *D_807FBB40;
extern u8 D_807FC929;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806ED050(void) {
    if ((D_807FBB40->unk154 != 2) && (*(&D_8074E77C + D_807FC929) == 6)) {
        D_807FBB40->unk154 = 0x29U;
        D_807FBB40->unk155 = 0;
        func_80614E78(D_807FBB40, 0x3F);
        D_807FD580->unk64 = 0;
        D_807FD580->unk68 = (f32) *(&D_8075380C + (D_807FD584 * 2));
    }
}

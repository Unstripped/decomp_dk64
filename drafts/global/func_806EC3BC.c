// func_806EC3BC (src/global/EFDC0.c): stage 1 m2c starter; player/actor fields and table declarations unresolved
? func_80613AF8(void *, ?, ?, ?);                   /* extern */
? func_80614D00(void *, ?, ?);                      /* extern */
? func_80614E78(void *, ?);                         /* extern */
extern ? D_807539DC;
extern ? D_807539EC;
extern void *D_807FBB40;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806EC3BC(void) {
    D_807FD580->unk12 = (s16) *(&D_807539EC + (D_807FD584 * 2));
    D_807FD580->unk14 = (s16) D_807FBB40->unkE6;
    D_807FD580->unk10 = (s16) *(&D_807539DC + (D_807FD584 * 2));
    D_807FBB40->unk154 = 0x4F;
    D_807FBB40->unk155 = 1;
    if (D_807FBB40->unkC0 > 0.0f) {
        D_807FBB40->unkC0 = 0.0f;
    }
    func_80614E78(D_807FBB40, 0x36);
    func_80613AF8(D_807FBB40, 0x31, 0, 0x41000000);
    func_80614D00(D_807FBB40, 0x3F000000, 0);
}

// func_806EC800 (src/global/EFDC0.c): stage 1 m2c starter; local player/actor views and callee prototypes unresolved
? func_80614E78(void *, ?, void **, s16 *);         /* extern */
extern ? D_807531C4;
extern ? D_807531FC;
extern void *D_807FBB40;
extern void *D_807FBB48;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806EC800(void) {
    f32 temp_fv0;
    f32 temp_fv1;

    D_807FBB48->unk154 = 0x50;
    D_807FBB48->unk155 = 0;
    D_807FBB40->unkC0 = -10.0f;
    D_807FD580->unk50 = 0;
    temp_fv1 = *(&D_807531C4 + (D_807FD584 * 4));
    temp_fv0 = D_807FBB40->unkB8;
    if (temp_fv0 < temp_fv1) {
        D_807FBB40->unkB8 = temp_fv0;
    } else {
        D_807FBB40->unkB8 = temp_fv1;
    }
    D_807FD580->unk38 = (f32) *(&D_807531FC + (D_807FD584 * 4));
    func_80614E78(D_807FBB48, 0x3C, &D_807FD580, &D_807FD584);
}

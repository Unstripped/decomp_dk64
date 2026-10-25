// func_806EC2CC (src/global/EFDC0.c): stage 1 m2c starter; nested actor view and callee prototypes unresolved
? func_80613C48(void *, ?, ?, ?);                   /* extern */
? func_80614EBC(void *, ?);                         /* extern */
? func_8067B238(void *, void *, s32, void **);      /* extern */
extern void *D_807FBB48;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806EC2CC(void) {
    void *temp_a1;

    D_807FBB48->unk154 = 0x75;
    D_807FBB48->unk155 = 0;
    func_80614EBC(D_807FBB48, 0);
    D_807FD580->unk50 = 0;
    D_807FD580->unk4C = -1;
    D_807FBB48->unk60 = (s32) (D_807FBB48->unk60 & ~1);
    D_807FD580->unk88 = (void *) (D_807FC924 + (D_807FC929 * 0x2F0))->unk2A0;
    temp_a1 = D_807FD580->unk88;
    func_8067B238(D_807FBB48, temp_a1, temp_a1->unk4->unk34, &D_807FD580);
    D_807FBB48->unk144 = 1;
    func_80613C48(D_807FBB48, 0x22A, 0, 0);
}

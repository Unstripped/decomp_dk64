// func_806EC1A8 (src/global/EFDC0.c): stage 1 m2c starter; actor/player views and callee declarations not reconciled
? func_80613C48(void *, s16, ?, ?);                 /* extern */
? func_80614EBC(void *, ?, void **);                /* extern */
extern s32 D_8076A0A8;
extern void *D_807FBB48;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806EC1A8(void) {
    s16 var_v0;
    void *temp_v0;

    temp_v0 = D_807FD580->unk104->unk174;
    temp_v0->unkAC = (s32) (temp_v0->unkAC | 4);
    D_807FBB48->unk154 = 0x6D;
    D_807FBB48->unk155 = 0;
    func_80614EBC(D_807FBB48, 0, &D_807FD580);
    D_807FD580->unk50 = 0;
    D_807FD580->unk4C = -1;
    D_807FBB48->unk60 = (s32) (D_807FBB48->unk60 & ~1);
    var_v0 = 0x1C7;
    if (D_8076A0A8 == 0x27) {
        D_807FBB48->unk144 = 1;
    }
    D_807FD580->unk88 = (s32) (D_807FC924 + (D_807FC929 * 0x2F0))->unk2A0;
    if (D_807FBB48->unk58 == 2) {
        var_v0 = 0x53;
    }
    func_80613C48(D_807FBB48, var_v0, 0, 0);
}

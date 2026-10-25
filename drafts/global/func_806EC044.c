// func_806EC044 (src/global/EFDC0.c): stage 1 m2c starter; control flow and declarations not reconciled
? actorClearMovementFlags(void *);                  /* extern */
? func_80614D00(void *, ?32, ?);                    /* extern */
? func_80614EBC(void *, ?);                         /* extern */
? func_8061CC40(void *, ?, ?);                      /* extern */
? func_806F0C18(s32);                               /* extern */
? func_806F8BC4(?, ?, ?);                           /* extern */
s32 hashTableLookup(s16);                           /* extern */
extern u8 D_8074E77C;
extern s32 D_807F6000;
extern s32 D_807FBB40;
extern void *D_807FBB48;

void func_806EC044(void) {
    ?32 sp24;

    sp24 = 0x3F800000;
    func_806F0C18(D_807FBB40);
    D_807FBB48->unk154 = 0x6C;
    D_807FBB48->unk155 = 0;
    func_80614EBC(D_807FBB48, 0x3B);
    if (D_8074E77C == 0) {
        sp24 = 0x3F000000;
    }
    func_80614D00(D_807FBB48, sp24, 0);
    actorClearMovementFlags(D_807FBB48);
    D_807FBB48->unk7C = (f32) *(D_807F6000 + (hashTableLookup(D_807FBB48->unk10C) * 0x90));
    D_807FBB48->unk80 = (f32) ((D_807F6000 + (hashTableLookup(D_807FBB48->unk10C) * 0x90))->unk4 + 5.0f);
    D_807FBB48->unk84 = (f32) (D_807F6000 + (hashTableLookup(D_807FBB48->unk10C) * 0x90))->unk8;
    D_807FBB48->unkE4 = 0;
    D_807FBB48->unkE8 = 0;
    func_8061CC40(D_807FBB48, 0, 1);
    func_806F8BC4(0, 1, 0);
}

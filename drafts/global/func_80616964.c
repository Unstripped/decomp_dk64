// func_80616964 (src/global/19A00.c): stage 4: behavior recovered; remaining diff is frame and state-pointer stack layout
? func_80614EBC(u16);                               /* extern */
extern s32 D_807F5AF0;

s32 func_80616964(void *arg0) {
    s32 sp1C;
    void *sp18;
    void *temp_v0;

    temp_v0 = arg0->unk4;
    sp1C = temp_v0->unk88;
    sp18 = temp_v0;
    func_80614EBC(temp_v0->unk5C);
    D_807F5AF0 = sp18->unk68 + sp18->unk60;
    sp18->unk5C = 0;
    sp18->unk60 = 0;
    sp18->unk88 = sp1C;
    return 1;
}

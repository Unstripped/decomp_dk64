// func_806EC1A8 (src/global/EFDC0.c): Stage 5: redundant else produces non-likely final animation branch; scheduling remains.
void func_806EC1A8(void) {
    s32 animation;

    *(u32 *)((u8 *)EfA_P->unk104->unk174 + 0xAC) |= 4;
    D_807FBB48->unk154 = 0x6D;
    D_807FBB48->unk155[0] = 0;
    func_80614EBC(D_807FBB48, 0);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    D_807FBB48->unk60 &= ~1;
    if (D_8076A0A8 == 0x27) {
        D_807FBB48->unk144 = 1;
    }
    EFB_P->unk88 = (EfBActor *)EFB_C[D_807FC929].unk2A0;
    if (D_807FBB48->unk58 == 2) {
        animation = 0x53;
    } else {
        animation = 0x1C7;
    }
    func_80613C48(D_807FBB48, (s16)animation, 0.0f, 0.0f);
}

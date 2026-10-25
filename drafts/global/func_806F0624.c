// func_806F0624 (src/global/EFDC0.c): identical displayed instruction stream but fdiff reported text/relocation mismatch; needs isolated investigation
void func_806E9964(EfEPlayerState *);

void func_806F0624(void) {
    EfEPS->unk1F4 |= 0x10;
    func_806E9964(EfEPS);
    D_807FBB48->unk154 = 0x83;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unk60 |= 0x40000004;
    D_807FBB48->unk60 &= ~1;
}

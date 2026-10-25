// func_806ECC48 (src/global/EFDC0.c): stage 1: m2c reconstruction; requires local player-state view for 0x104->0x174 callback and exact call prototypes
? func_80614D90(void *);                            /* extern */
? func_80614E78(void *, ?);                         /* extern */
? func_8061F164(s32, ?);                            /* extern */
extern void *D_807FBB48;
extern void *D_807FD580;

void func_806ECC48(void) {
    s32 sp1C;

    sp1C = D_807FD580->unk104->unk174;
    D_807FBB48->unk6A = (u16) (D_807FBB48->unk6A | 0x40);
    D_807FBB48->unk64 = (s32) (D_807FBB48->unk64 & ~0x2000);
    D_807FBB48->unk154 = 0x59;
    D_807FBB48->unk155 = 0;
    func_80614E78(D_807FBB48, 0x70);
    func_80614D90(D_807FBB48);
    func_8061F164(sp1C, 0x14);
}

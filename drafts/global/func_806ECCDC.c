// func_806ECCDC (src/global/EFDC0.c): stage 1: m2c reconstruction of player setup; needs local player and callback views
? func_80614E78(void *, ?, s32);                    /* extern */
? func_8061F164(s32, ?);                            /* extern */
extern ? D_807535CC;
extern void *D_807FBB40;
extern void *D_807FBB48;
extern s32 D_807FBB68;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806ECCDC(void) {
    s32 sp1C;
    s32 temp_a2;

    temp_a2 = D_807FD580->unk104->unk174;
    D_807FBB40->unk154 = 0x17;
    D_807FBB40->unk155 = 0;
    if (D_807FBB68 & 2) {
        D_807FD580->unk54 = (f32) ((f64) *(&D_807535CC + (D_807FD584 * 4)) * 1.3);
    } else {
        D_807FD580->unk54 = (f32) *(&D_807535CC + (D_807FD584 * 4));
    }
    D_807FBB48->unkB8 = (f32) D_807FD580->unk124;
    D_807FD580->unk50 = 0;
    D_807FD580->unk3C = 0xA;
    sp1C = temp_a2;
    func_80614E78(D_807FBB40, 0x10, temp_a2);
    func_8061F164(sp1C, 0x14);
}

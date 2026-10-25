// func_806EC8C4 (src/global/EFDC0.c): stage 1 m2c starter; actor/player views and call prototypes unresolved
? func_80614E78(void *, ?);                         /* extern */
? func_80614EBC(void *, ?);                         /* extern */
extern void *D_807FBB48;
extern void *D_807FBB90;
extern void *D_807FD580;

void func_806EC8C4(void) {
    u32 temp_v1;

    D_807FD580->unk1B0 = (void *) D_807FBB90;
    D_807FD580->unk1B4 = (s32) D_807FD580->unk1B0->unk54;
    temp_v1 = D_807FD580->unk1B0->unk58;
    switch (temp_v1) {                              /* irregular */
    case 0x3D:
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x55:
    case 0x82:
        func_80614EBC(D_807FBB48, 0x1C8);
        break;
    default:
        func_80614E78(D_807FBB48, 0x2B);
        break;
    }
    D_807FBB48->unk154 = 0x47;
    D_807FBB48->unk155 = 0;
}

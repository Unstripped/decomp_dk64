// func_806F03C4 (src/global/EFDC0.c): Semantic switch candidate; IDO retains D_807FBB48 in s0 and expands the frame, unlike target's repeated global loads.
void func_806F03C4(void) {
    s32 sp1C;
    s32 var_a3;
    void *camera;

    switch (D_807FBB48->unk58) {
    case 2:
        sp1C = 7;
        camera = (u8 *)D_807FC924 + (D_807FC929 * 0x2F0);
        break;
    case 3:
        sp1C = 0;
        camera = (u8 *)D_807FC924 + (D_807FC929 * 0x2F0);
        break;
    case 4:
        EfEPS->unk1F0 |= 0x100;
        sp1C = 4;
        camera = (u8 *)D_807FC924 + (D_807FC929 * 0x2F0);
        break;
    case 5:
        camera = (u8 *)D_807FC924 + (D_807FC929 * 0x2F0);
        var_a3 = 0x1F;
        if (((EfECamBlock *)camera)->unk2C0 == 1) {
            var_a3 = 8;
        }
        sp1C = var_a3;
        break;
    case 6:
        sp1C = 9;
        camera = (u8 *)D_807FC924 + (D_807FC929 * 0x2F0);
        break;
    default:
        camera = (u8 *)D_807FC924 + (D_807FC929 * 0x2F0);
        break;
    }
    D_807FBB48->unkE6 = mathAngleBetweenPoints2D(((EfECamBlock *)camera)->unk210,
                                                  ((EfECamBlock *)camera)->unk218,
                                                  D_807FBB48->unk7C, D_807FBB48->unk84);
    if (D_807FBB68 & 2) {
        EfEPS->unk1F0 &= ~0x100;
        func_80614EBC(D_807FBB48, 0x165);
    } else {
        if (D_807FBB48->unk154 != 0x56) {
            func_8061CC40(D_807FBB48, (s16)sp1C, 5);
        }
        func_80614E78(D_807FBB48, 0x5A);
    }
    D_807FBB48->unk154 = 0x67;
    D_807FBB48->unk155[0] = 0;
}

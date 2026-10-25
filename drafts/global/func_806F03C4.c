// func_806F03C4 (src/global/EFDC0.c): Stage 3: actor-local switch attempt; target requires global reload allocation.
void func_806F03C4(void) {
    s32 sp1C;
    s32 var_a3;
    Actor *actor;
    EfECamBlock *camera;

    actor = D_807FBB48;
    switch (actor->unk58) {
    case 2:
        sp1C = 7;
        camera = &EfECam[D_807FC929];
        break;
    case 3:
        sp1C = 0;
        camera = &EfECam[D_807FC929];
        break;
    case 4:
        EfEPS->unk1F0 |= 0x100;
        sp1C = 4;
        camera = &EfECam[D_807FC929];
        break;
    case 5:
        camera = &EfECam[D_807FC929];
        var_a3 = 0x1F;
        if (camera->unk2C0 == 1) {
            var_a3 = 8;
        }
        sp1C = var_a3;
        break;
    case 6:
        sp1C = 9;
        camera = &EfECam[D_807FC929];
        break;
    default:
        camera = &EfECam[D_807FC929];
        break;
    }
    D_807FBB48->unkE6 = mathAngleBetweenPoints2D(camera->unk210, camera->unk218,
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

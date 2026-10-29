// func_806871DC (src/global/89250.c): stage 5: regalloc/branch diff in loop condition (v0 vs s0, bnel)
void func_806871DC(u8 arg0) {
    s32 var_s2;
    s32 temp_s3;
    s16 var_s4;
    s16 var_v0;

    var_s2 = (((D_8076A064 & 3) * 4) + 3) & 0xFF;
    temp_s3 = arg0 & 0xFF;
    var_s4 = 0;
    do {
        var_v0 = var_s2;
        if (var_s2 == 0x10) {
            var_v0 = 0x14;
        } else if (var_v0 == 0x11) {
            var_v0 = 0x15;
        } else {
            var_v0 = var_s2 & 0xFF;
        }

        switch (temp_s3) {
        case 3:
            if (var_v0 < 10) {
                break;
            }
            /* fallthrough */
        case 1:
            func_80714998(1);
            func_807149C8(0xB4, 0xB4, 0xB4, 0xC8);
            effectSpawnBoneDefault(D_807FBB40, var_v0, 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
            break;

        case 2:
            if (var_v0 < 10) {
                break;
            }
            /* fallthrough */
        case 0:
            func_807149B8(1);
            func_8071498C(func_80717D4C);
            func_80714950(-0x3E8);
            func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
            func_80714C08(&D_80720120, (f32)(((f64)((randomNonNegative() >> 15) % 100) / 30.0) + 1.0), D_807FBB40, var_v0, 0);
            break;
        }
        var_s4++;
        var_s2 = (var_s2 + 1) & 0xFF;
    } while (var_s4 < 4);
}

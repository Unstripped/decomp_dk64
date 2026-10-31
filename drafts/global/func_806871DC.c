// func_806871DC (src/global/89250.c): Stage 5 (BnelOps2): frame/saved regs match; remaining ~19 diff lines. Target: chain var web A in v0 (move v0,s2 in slot of bne s6,s2; bnel v0,at,.. reads v0; case-2/3 tests slti v0) + separate web B s0 = copy at each case-body entry (move s0,v0); ours copy-propagates var_v0=var_s2 and colours everything s0. bne s6,s2 (const first) vs ours bne s2,s6; prologue andi s3 after move s4. Tried: per-case x=var_v0 copies (types s32/u8/s16/u32, pre-init x=0, post copies), switch(var_s2) chain, switch(var_v0), compare spellings (0x10==x), self-assigns (var_v0 = var_v0, +=0, (s16)/(u8) casts) at case labels/top, var_v0 typed u8/u32/s16, deadsweep (1008 variants, no gain), permuter 500 s (no gain below baseline 1055).
void func_806871DC(u8 arg0) {
    s32 var_s2;
    u32 temp_s3;
    s16 var_s4;
    s32 var_v0;

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

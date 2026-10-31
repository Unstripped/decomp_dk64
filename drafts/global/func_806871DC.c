// func_806871DC (src/global/89250.c): Stage 5 (W2Webs): frame/saved regs match; 14 diff lines (improved scorer). Target: chain web in v0 (move v0,s2 in slot of bne s6,s2; bnel v0,at reads v0; case-2/3 slti read v0) then move s0,v0 at case entry (live-range split of var_v0: chain piece v0, call-crossing piece s0); ours colours whole var_v0 s0 (cand 20 has top priority adjsave 11.7 in uopt -l 5, target needs it below the consts/others or split). Also bne s6,s2 const-first vs ours bne s2,s6; prologue move s4/andi s3 order. Tried (W2Webs+BnelOps2): per-case/pre-switch x=var_v0 copies (all type/placement/use grids), x=0;if(x){} dup, self-assigns, casts, var_s2/temp_s3/var_v0 types (6x3x2), switch(var_s2)/(var_v0) chains, compare spellings, deadsweep 1008 variants, permuter 500s: no change.
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

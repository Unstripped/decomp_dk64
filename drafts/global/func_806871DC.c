// func_806871DC (src/global/89250.c): W4A stage 5: 10 diff lines, frame/regs/insn count match. Structure now = target: chain var in v0 (separate web w takes s0, copies at case-1/case-0 entry), '(var_s2|0)==0x10' gives bne s6,s2, '(var_v0|0)==0x11' keeps copy compare, for(var_s4=0;..;var_s4++) with var_s2 update first fixes tail. Remaining: andi s3,a0,0xff hoisted early in target (we keep it after addiu s5), and as1 order of 'move s0,v0' vs 'li a0,1' in delay slots of beqz s3 / jal (swapped in both groups). u32 temp_s3 required (s32 merges const-1 web -> move a0,s7).
void func_806871DC(u8 arg0) {
    s32 var_s2;
    u32 temp_s3;
    s16 var_s4;
    s32 var_v0;
    s32 w;  // FAKE: separate post-dispatch web (chain var stays in v0, w takes s0)

    var_s2 = (((D_8076A064 & 3) * 4) + 3) & 0xFF;
    temp_s3 = arg0 & 0xFF;
    for (var_s4 = 0; var_s4 < 4; var_s4++) {
        var_v0 = var_s2;
        if ((var_s2 | 0) == 0x10) {  // FAKE: |0 keeps the constant-first operand order (bne s6,s2)
            var_v0 = 0x14;
        } else if ((var_v0 | 0) == 0x11) {  // FAKE: |0 blocks copy propagation so the compare reads the copy
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
            w = var_v0;
            func_80714998(1);
            func_807149C8(0xB4, 0xB4, 0xB4, 0xC8);
            effectSpawnBoneDefault(D_807FBB40, (w | 0), 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
            break;

        case 2:
            if (var_v0 < 10) {
                break;
            }
            /* fallthrough */
        case 0:
            w = var_v0;
            func_807149B8(1);
            func_8071498C(func_80717D4C);
            func_80714950(-0x3E8);
            func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
            func_80714C08(&D_80720120, (f32)(((f64)((randomNonNegative() >> 15) % 100) / 30.0) + 1.0), D_807FBB40, (w | 0), 0);
            break;
        }
        var_s2 = (var_s2 + 1) & 0xFF;
    }
}

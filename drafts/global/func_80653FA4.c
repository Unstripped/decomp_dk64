// func_80653FA4 (src/global/55B20.c): stage 2: full body from m2c; stack layout differs (built 0xD8 vs 0xA8); needs flags u8[0x34] at 0x5C, s8[0x10] at 0x90, sp4C at 0x4C, spA4 at 0xA4 with (s8)spA4 read as lb 0xA7(sp)
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[5];
    /* 0x07 */ u8 unk7;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[0x14];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 pad2C[0x3C];
    /* 0x68 */ s32 unk68;
    /* 0x78 */ u8 pad78[0x1C8 - 0x78];
} M55P3EffectBuf;
extern M55P3EffectBuf *D_807F6C18;
extern s32 D_8076A064;
extern s32 D_807FBB68;
extern s32 D_807F6C28;
extern s16 func_80658B08(s8, s8 *, s32);
void *func_80653DF0(void *, void *, s16);
void func_80653EA8(u8 *, u8 *);

void func_80653FA4(void) {
    s32 spA4;
    s8 sp90[0x10];
    u8 sp5C[0x34];
    s32 sp4C;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_t2;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;
    s8 *temp_s6;
    s8 *var_s2;
    s8 temp_v0_3;
    u8 *temp_s3;
    u8 *temp_v1;
    u8 *var_s1;
    u8 *var_s1_2;
    u8 temp_t9;
    u8 temp_v0_4;
    M55P3EffectBuf *temp_s0;

    if (!(D_807FBB68 & 0x100)) {
        temp_v0 = D_807F6C28;
        var_s1 = sp5C;
        spA4 = 0;
        temp_v1 = &var_s1[temp_v0];
        if (temp_v0 > 0) {
            do {
                var_s1 += 1;
                *(var_s1 - 1) = 0;
            } while ((u32)var_s1 < (u32)temp_v1);
            spA4 = 0;
        }
        var_v1 = 0;
        if (temp_v0 > 0) {
            do {
                temp_s0 = (M55P3EffectBuf *)((u8 *)D_807F6C18 + var_v1);
                if (temp_s0->unk1 != 0) {
                    sp5C[spA4] = 1;
                    temp_s0->unk28 = D_8076A064;
                    if (!(temp_s0->unk7 & 4)) {
                        sp4C = var_v1;
                        temp_s0->unk8 = (s32)func_80653DF0((void *)temp_s0->unk8, (void *)temp_s0->unk10, 0x270F);
                        temp_s0->unk7 |= 4;
                        temp_s0->unk7 &= 0xFFFC;
                    }
                    sp4C = var_v1;
                    temp_v0_2 = func_80658B08((s8)spA4, sp90, 0x10);
                    var_v1 = sp4C;
                    if (temp_v0_2 > 0) {
                        var_s2 = sp90;
                        temp_s6 = &var_s2[temp_v0_2];
                        do {
                            temp_v0_3 = *var_s2;
                            temp_s3 = &sp5C[temp_v0_3];
                            if (*temp_s3 == 0) {
                                temp_s1 = temp_v0_3 * 0x1C8;
                                temp_s0 = (M55P3EffectBuf *)((u8 *)D_807F6C18 + temp_s1);
                                if (temp_s0->unk1 == 0) {
                                    if (!(temp_s0->unk7 & 4)) {
                                        sp4C = var_v1;
                                        temp_s0->unk8 = (s32)func_80653DF0((void *)temp_s0->unk8, (void *)temp_s0->unk10, 5);
                                        if (temp_s0->unk8 == temp_s0->unk10) {
                                            temp_s0->unk7 &= 0xFFFD;
                                            temp_s0->unk7 |= 4;
                                        } else {
                                            temp_s0->unk7 |= 2;
                                        }
                                        temp_s0->unk7 &= 0xFFFE;
                                    }
                                    *temp_s3 = 1;
                                }
                            }
                            var_s2 += 1;
                        } while ((u32)var_s2 < (u32)temp_s6);
                    }
                }
                temp_t8 = spA4 + 1;
                spA4 = temp_t8;
                var_v1 += 0x1C8;
            } while (temp_t8 < D_807F6C28);
            spA4 = 0;
        }
        if (temp_v0 > 0) {
            var_s1_2 = sp5C;
            var_v1_2 = 0;
            do {
                temp_a0 = (s32)D_807F6C18;
                temp_s0 = (M55P3EffectBuf *)((u8 *)temp_a0 + var_v1_2);
                if (*var_s1_2 == 0) {
                    temp_v0_4 = temp_s0->unk7;
                    if (temp_v0_4 & 8) {
                        if (!(temp_v0_4 & 4)) {
                            sp4C = var_v1_2;
                            temp_s0->unk8 = (s32)func_80653DF0((void *)temp_s0->unk8, (void *)temp_s0->unk10, 5);
                            if (temp_s0->unk8 == temp_s0->unk10) {
                                temp_s0->unk7 &= 0xFFFD;
                                temp_s0->unk7 |= 4;
                            } else {
                                temp_s0->unk7 |= 2;
                            }
                            temp_s0->unk7 &= 0xFFFE;
                        }
                    } else if (!(temp_v0_4 & 1) && ((u32)(D_8076A064 - temp_s0->unk28) >= 3U)) {
                        sp4C = var_v1_2;
                        func_80653EA8((u8 *)temp_s0->unkC, (u8 *)temp_s0->unk8);
                        temp_s0->unk8 = temp_s0->unkC;
                        temp_s0->unk7 |= 1;
                        temp_s0->unk7 &= ~6;
                    }
                }
                temp_t9 = temp_s0->unk7;
                var_v1_2 += 0x1C8;
                temp_s0->unk7 = temp_t9 & ~8;
                var_s1_2 += 1;
                temp_t2 = spA4 + 1;
                spA4 = temp_t2;
            } while (temp_t2 < D_807F6C28);
        }
    }
}

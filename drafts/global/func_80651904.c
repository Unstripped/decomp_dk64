// func_80651904 (src/global/55B20.c): near miss; regalloc/scheduling stage
typedef struct M55P1_Unk807F6C18 {
    u8 unk0; u8 unk1; u8 unk2; u8 unk3; u8 unk4; u8 pad5[0xF];
    s32 unk14; u8 pad18[0x4]; s32 unk1C; u8 pad20[0x48];
    s32 unk68; s32 unk6C; s32 unk70; s32 unk74; u8 pad78[0x150];
} M55P1_Unk807F6C18;

extern u8 D_807F7078[];
extern s32 D_807F6C28;
extern M55P1_Unk807F6C18 *D_807F6C18;
extern u8 *D_807F6C1C;
extern s32 D_807F6C20;
extern u8 *D_807F6C2C;
extern s32 D_807F70AC;

void func_80651904(M55P1_Unk80651904_Node *var_a0, s32 var_a1, u8 *arg2, s32 *arg3, u8 arg4, s32 arg5) {
    s32 temp_s1;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_t4;
    s32 var_s0;
    s32 var_s3;
    s32 var_s4;
    s32 var_t5;
    u8 *temp_t4_2;
    u8 *var_s2;
    u8 *var_s2_2;

    if (var_a1 != 0) {
        do {
            var_t5 = 0;
            var_s0 = 0;
            var_a1 -= 8;
            if (((u32)var_a0->unk0 >> 0x18) == 0) {
                temp_s1 = *arg3;
                temp_t4 = var_a0->unk4;
                temp_s7 = arg5 * 0x1C8;
                var_s3 = 0;
                var_s4 = 0;
                temp_s5 = arg4 * 4;
                temp_s6 = arg4 * 2;
                if (temp_s1 > 0) {
                    var_s2 = arg2;
                    do {
                        if (temp_t4 == *(s16 *)(var_s2 + 0)) {
                            var_s0 = 1;
                        } else {
                            var_t5 += 1;
                            var_s2 += 0x24;
                        }
                        if (!((var_t5 < temp_s1) && (var_s0 == 0))) {
                            break;
                        }
                    } while (1);
                }
                var_s2_2 = (u8 *)D_807F70B0;
                do {
                    if (temp_t4 == *(s16 *)(var_s2_2 + 2)) {
                        var_s4 = 1;
                    } else {
                        var_s3 += 1;
                        var_s2_2 += 0x1C;
                    }
                } while (var_s4 == 0);
                if (var_s0 == 0) {
                    *(s16 *)(arg2 + temp_s1 * 0x24) = (s16)temp_t4;
                    *(s32 *)(arg2 + *arg3 * 0x24 + 4) = -1;
                    *(s32 *)(arg2 + *arg3 * 0x24 + 8) = -1;
                    *(s32 *)(arg2 + *arg3 * 0x24 + 0xC) = -1;
                    *(s32 *)(arg2 + *arg3 * 0x24 + 0x10) = -1;
                    temp_t4_2 = arg2 + (*arg3 * 0x24) + temp_s5;
                    *(s32 *)(temp_t4_2 + 4) = (s32)((u8 *)var_a0 + 8);
                    *(s32 *)(temp_t4_2 + 0x14) = (*(s16 *)((u8 *)D_807F70B0 + var_s3 * 0x1C + temp_s6 + 8) << 4) + *(s32 *)((u8 *)D_807F6C18 + temp_s7 + 0x58);
                    *arg3 += 1;
                } else {
                    temp_t4_2 = arg2 + (var_t5 * 0x24) + temp_s5;
                    *(s32 *)(temp_t4_2 + 4) = (s32)((u8 *)var_a0 + 8);
                    *(s32 *)(temp_t4_2 + 0x14) = (*(s16 *)((u8 *)D_807F70B0 + var_s3 * 0x1C + temp_s6 + 8) << 4) + *(s32 *)((u8 *)D_807F6C18 + temp_s7 + 0x58);
                }
            }
            var_a0 += 1;
        } while (var_a1 != 0);
    }
}

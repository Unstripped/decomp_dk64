// func_80651708 (src/global/55B20.c): near miss; regalloc/scheduling stage
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

void func_80651708(s32 arg0) {
    u8 *temp_t3;
    M55P1_Unk807F70B8 *var_v1;
    s16 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 temp_lo;
    s32 var_a1_2;
    u8 *var_a0_2;

    var_v1 = D_807F70B8[arg0];
    if (var_v1->unk8 != 0) {
        heapFree(var_v1->unk8);
    }
    var_a0 = var_v1->unk4;
    var_a1 = var_a0 - 2;
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    if (var_a1 != 0) {
        var_a3 = 1;
        var_a2 = 2;
        var_v1->unk8 = func_80610FE8(var_a1 * 0x12);
        var_v1->unkC = var_a1;
        if (var_a0 >= 3) {
            var_v0 = 0x24;
            var_a1_2 = 0xC;
            do {
                temp_lo = var_a3 * 6;
                var_a3 = var_a2;
                *(s16 *)(var_v1->unk8 + var_v0 - 0x24) = *(s16 *)(var_v1->unk0 + 0);
                var_a2 += 1;
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1E) = *(s16 *)(var_v1->unk0 + 2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x18) = *(s16 *)(var_v1->unk0 + 4);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x22) = *(s16 *)(var_v1->unk0 + temp_lo);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1C) = *(s16 *)(var_v1->unk0 + temp_lo + 2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x16) = *(s16 *)(var_v1->unk0 + temp_lo + 4);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x20) = *(s16 *)(var_v1->unk0 + var_a1_2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1A) = *(s16 *)(var_v1->unk0 + var_a1_2 + 2);
                temp_t3 = var_v1->unk8 + var_v0;
                var_v0 += 0x12;
                *(s16 *)(temp_t3 - 0x14) = *(s16 *)(var_v1->unk0 + var_a1_2 + 4);
                var_a0 = var_v1->unk4;
                var_a1_2 += 6;
            } while (var_a2 < var_a0);
        }
    }
    var_v1->unk12 = -0x8000;
    var_v1->unk10 = 0x7FFF;
    var_a2 = 0;
    if (var_a0 > 0) {
        var_a0_2 = var_v1->unk0;
        do {
            if (var_v1->unk12 < *(s16 *)(var_a0_2 + 2)) {
                var_v1->unk12 = *(s16 *)(var_a0_2 + 2);
            }
            if (*(s16 *)(var_a0_2 + 2) < var_v1->unk10) {
                var_v1->unk10 = *(s16 *)(var_a0_2 + 2);
            }
            var_a2 += 1;
            var_a0_2 += 6;
        } while (var_a2 < var_v1->unk4);
    }
}

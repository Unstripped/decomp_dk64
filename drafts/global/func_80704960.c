// func_80704960 (src/global/109660.c): stage 3 candidate; correct display-list behavior, pointer/register scheduling differs
typedef struct {
    s8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R1F109660aRect;

extern s8 D_80750840;
extern u8 D_80750AB8;
extern u8 D_80750ABC;
extern u8 D_8074450C;

Gfx *func_80704960(Gfx *arg0) {
    R1F109660aRect *var_a1;
    s8 var_a2;
    Gfx *temp_a2;

    arg0->words.w0 = 0xE7000000;
    arg0->words.w1 = 0;
    arg0++;
    arg0->words.w0 = 0xE200001C;
    arg0->words.w1 = 0;
    arg0++;
    arg0->words.w1 = 0x300000;
    arg0->words.w0 = 0xE3000A01;
    arg0++;
    arg0->words.w0 = 0xF7000000;
    arg0->words.w1 = 0x10001;
    arg0++;
    if (D_80750840 != -1) {
        var_a1 = (R1F109660aRect *)&D_80750840;
        var_a2 = D_80750840;
        do {
            if (((var_a2 == 2) && ((s32)D_807FC928 >= 2) && (var_a1->unk2 & D_80750ABC)) || ((D_807FC928 == var_a2) && (D_80750AB8 == var_a1->unk1) && (var_a1->unk2 & D_80750ABC))) {
                temp_a2 = arg0;
                arg0++;
                temp_a2->words.w0 = (((((var_a1->unkA + 1) * D_8074450C) - 1) & 0x3FF) * 4) | 0xF6000000 | (((((var_a1->unk8 + 1) * D_8074450C) - 1) & 0x3FF) << 14);
                temp_a2->words.w1 = (((var_a1->unk6 * D_8074450C) & 0x3FF) * 4) | (((var_a1->unk4 * D_8074450C) & 0x3FF) << 14);
            }
            var_a2 = ((R1F109660aRect *)((u8 *)var_a1 + 0xC))->unk0;
            var_a1 = (R1F109660aRect *)((u8 *)var_a1 + 0xC);
        } while (var_a2 != -1);
    }
    arg0->words.w0 = 0xE7000000;
    arg0->words.w1 = 0;
    return arg0 + 1;
}

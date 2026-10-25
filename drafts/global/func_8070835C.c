// func_8070835C (src/global/109660.c): Stage 2 compiled display-list reconstruction; raw Gfx writes expose pointer/register allocation differences.
void *func_80706F90(s32 *);                         /* extern */
void *func_80707980(s32, s32, s32, s32);            /* extern */
extern u8 D_807444FC;
extern s32 D_807552EC;
extern s32 D_8076A0A8;
extern s32 D_807FBB60;
extern s32 D_807FC924;
extern u8 D_807FC928;

void *func_8070835C(void *arg0, s16 arg1) {
    s32 temp_t1;
    s32 var_a1;
    s32 var_v0_2;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *var_a0;
    void *var_v0;

    var_a0 = arg0;
    if (((s32) D_807FC928 >= 2) || !(D_807FBB60 & 0x10)) {
        if (D_8076A0A8 == 0x50) {
            var_v0 = func_80706F90(&D_807FBB60);
            goto block_12;
        }
        var_a1 = (D_807FBB60 & 2) == 0;
        if ((s32) D_807FC928 >= 2) {
            var_v0_2 = 1;
            if (D_8076A0A8 == 0xBE) {
                var_v0_2 = 0;
            }
            var_a1 |= var_v0_2 | (D_807552EC >= 2);
        }
        if (var_a1 == 0) {

        } else {
            temp_a0 = var_a0 + 8;
            var_a0->unk0 = 0xE7000000;
            var_a0->unk4 = 0;
            temp_a0_2 = temp_a0 + 8;
            var_a0->unk8 = 0xE200001C;
            temp_a0->unk4 = 0;
            temp_a0_3 = temp_a0_2 + 8;
            temp_a0->unk8 = 0xF7000000;
            temp_a0_2->unk4 = 0x10001;
            temp_a0_3->unk4 = 0x300000;
            temp_a0_2->unk8 = 0xE3000A01;
            temp_t1 = arg1 * 0x2F0;
            temp_v0 = D_807FC924 + temp_t1;
            temp_a0_4 = temp_a0_3 + 8;
            temp_a0_3->unk8 = (s32) ((((temp_v0->unk276 - 1) & 0x3FF) * 4) | 0xF6000000 | (((temp_v0->unk274 - 1) & 0x3FF) << 0xE));
            temp_a0_5 = temp_a0_4 + 8;
            temp_v0_2 = D_807FC924 + temp_t1;
            temp_a0_6 = temp_a0_5 + 8;
            temp_a0_4->unk4 = (s32) (((temp_v0_2->unk272 & 0x3FF) * 4) | ((temp_v0_2->unk270 & 0x3FF) << 0xE));
            temp_a0_5->unk4 = 0;
            temp_a0_4->unk8 = 0xE7000000;
            temp_a0_6->unk4 = 0;
            temp_a0_5->unk8 = 0xE3000A01;
            var_a0 = temp_a0_6 + 8;
        }
    } else {
        temp_v0_3 = D_807FC924 + (arg1 * 0x2F0);
        var_v0 = func_80707980(temp_v0_3->unk2D4, temp_v0_3->unk2D8, temp_v0_3 + (D_807444FC << 6) + 0x108, (s32) arg1);
block_12:
        var_a0 = var_v0;
    }
    return var_a0;
}

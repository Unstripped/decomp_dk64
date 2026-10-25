// func_807007B8 (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
void *func_8070068C(void *);                        /* extern */
void *func_80701098(void *, s32, s32, s32, s32, s32); /* extern */
extern ? D_2000180;
extern u8 D_807444FC;
extern u8 D_80754BC0;
extern ? D_807FD808;
extern ? D_807FD838;

void *func_807007B8(void *arg0) {
    s16 var_s0;
    u8 *temp_v1;
    u8 temp_v0_2;
    void *temp_s1;
    void *temp_t2;
    void *temp_v0;
    void *var_s1;
    void *var_s1_2;

    var_s1 = arg0;
    if (D_80754BC0 != 0) {
        arg0->unk0 = 0xE7000000;
        arg0->unk4 = 0;
        temp_v0 = func_8070068C(arg0 + 8);
        temp_v0->unk0 = 0xDA380003;
        temp_v0->unk4 = &D_2000180;
        temp_v0->unk10 = 0xD9000000;
        temp_v0->unk18 = 0xD9FFFFFF;
        temp_v0->unk1C = 0x200004;
        temp_v0->unk20 = 0xE3000A01;
        temp_v0->unk28 = 0xE3000C00;
        temp_v0->unk30 = 0xE3001201;
        temp_v0->unk2C = 0x80000;
        temp_v0->unk34 = 0x2000;
        temp_v0->unk8 = 0xE7000000;
        temp_v0->unkC = 0;
        temp_v0->unk14 = 0;
        temp_v0->unk24 = 0;
        temp_v0->unk3C = 0x80008000;
        temp_v0->unk38 = 0xD7000002;
        temp_v0->unk44 = 0xFF2FFFFF;
        temp_v0->unk40 = 0xFC119623;
        temp_v0->unk4C = 0x504340;
        temp_v0->unk48 = 0xE200001C;
        temp_v0->unk54 = 0xC0;
        temp_v0->unk50 = 0xE3001801;
        temp_v0->unk5C = 0x30;
        temp_v0->unk58 = 0xE3001A01;
        var_s1_2 = temp_v0 + 0x60;
        var_s0 = 0;
        if ((s32) D_80754BC0 > 0) {
            do {
                temp_t2 = &D_807FD808 + (var_s0 * 0x10);
                temp_v1 = &D_807FD838 + ((D_807444FC ^ 1) * 3) + var_s0;
                temp_v0_2 = *temp_v1;
                if (temp_v0_2 != 0) {
                    *temp_v1 = temp_v0_2 - 1;
                    var_s1_2 = func_80701098(var_s1_2, subroutine_arg1, subroutine_arg2, temp_t2->unk8, temp_t2->unkC, (s32) temp_v0_2);
                }
                var_s0 += 1;
            } while (var_s0 < (s32) D_80754BC0);
        }
        temp_s1 = var_s1_2 + 8;
        var_s1_2->unk0 = 0xE3001801;
        var_s1_2->unk4 = 0;
        var_s1_2->unk8 = 0xE3001A01;
        temp_s1->unk4 = 0;
        var_s1 = temp_s1 + 8;
    }
    return var_s1;
}

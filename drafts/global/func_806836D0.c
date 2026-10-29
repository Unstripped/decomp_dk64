// func_806836D0 (src/global/80150.c): from .scratch/R2G/func_806836D0_best.c
s32 func_805FCA64();                                /* extern */
? func_80602B60(?, ?);                              /* extern */
? func_80602CE0(?, s32, ?, s32);                    /* extern */
? func_80609140(?, ?, ?, ?, s32, s32);              /* extern */
? func_8061EB04(void *, ?);                         /* extern */
? func_80627888(s32);                               /* extern */
s32 screenWipeGetState();                                /* extern */
? screenWipeStart(?);                                 /* extern */
? func_80659670(f32, f32, ?, s32, s16);             /* extern */
? func_806782C0(s32);                               /* extern */
? func_80682AB4();                                  /* extern */
? func_80682DF4(void *, s32, ?, s32);               /* extern */
? func_806C8E58(s16);                               /* extern */
? func_806F09F0(void *, s32);                       /* extern */
? healthRefill(?);                                 /* extern */
extern ? D_8074E816;
extern ? D_8074E848;
extern void *D_807FBB40;
extern s32 D_807FBB60;
extern void *D_807FC924;
extern ? D_807FD610;

void func_806836D0(void *arg0) {
    u16 sp4A;
    void *sp34;
    void *sp30;
    s32 sp28;
    s16 temp_s0_2;
    s16 var_v0;
    s32 temp_a3;
    s32 temp_s0;
    s32 temp_t3;
    s32 var_v1;
    s8 temp_v0;
    u16 var_s0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_v1;
    void *var_s0_2;

    var_s0 = arg0->unk4;
    sp4A = var_s0;
    if (var_s0 != 0) {
        arg0->unk4 = (u16) (var_s0 - 1);
        func_80682AB4();
        var_s0 = arg0->unk4;
    }
    arg0->unk3C = (u32) (arg0->unk3C + 1);
    if ((var_s0 == 0) && (func_805FCA64() != 0)) {
        temp_a3 = arg0->unk6 * 4;
        temp_a1 = arg0 + temp_a3;
        temp_t3 = (u32) arg0->unk3C >= 0x2329U;
        temp_s0 = temp_a1->unk8->unk58 == 0x13C;
        if ((((s32) D_807FD610.unk30 >= 0x29) && (temp_t3 == 0)) || (temp_s0 == 0)) {
            arg0->unk4 = 0x14U;
            temp_a0 = temp_a1->unk8;
            if (temp_a0->unk58 == 0x13C) {
                func_80682DF4(temp_a0, temp_a0->unk174, 0x8C, temp_a3);
            }
            arg0->unk7 = arg0->unk6;
            if (temp_s0 != 0) {
                if (D_807FD610.unk2E >= 0) {
                    arg0->unk20 = 1;
                } else {
                    arg0->unk20 = -1;
                }
            }
            arg0->unk6 = (s8) (arg0->unk6 + arg0->unk20);
            temp_v0 = arg0->unk6;
            if (temp_v0 < 0) {
                arg0->unk6 = 4;
            } else if (temp_v0 >= 5) {
                arg0->unk6 = 0;
            }
            temp_a0_2 = (arg0 + (arg0->unk6 * 4))->unk8;
            if (temp_a0_2->unk58 == 0x13C) {
                func_80682DF4(temp_a0_2, temp_a0_2->unk174, 0x8B);
            }
        } else {
            if ((temp_t3 == 0) && (sp4A != 0)) {
                func_80602CE0(0x65, 0x7E - *(&D_8074E848 + temp_a3), 3, temp_a3);
                func_80602CE0(0x65, *(&D_8074E848 + (arg0->unk6 * 4)), 2);
                return;
            }
            if ((((temp_t3 != 0) && (temp_s0 != 0)) || (D_807FD610.unk2C & 0xE000)) && (screenWipeGetState() == 0)) {
                if (temp_s0 != 0) {
                    temp_v1 = arg0->unk0;
                    sp30 = temp_v1->unk174;
                    var_v0 = temp_v1->unk12C;
                    if (var_v0 == -1) {
                        var_v0 = 0;
                    }
                    sp34 = temp_v1;
                    func_80659670(arg0->unk2C, arg0->unk30, 0x98, arg0->unk34, var_v0);
                    D_807FBB60 |= 0x30030;
                    func_80602B60(0x48, 0);
                    func_80602B60(0x6B, 0);
                    func_80602B60(0x49, 0);
                    func_80602B60(0x47, 0);
                    func_80602B60(0x65, 0);
                    func_806782C0(arg0->unk1C);
                    arg0->unk1C = 0;
                    var_v1 = 0;
                    var_s0_2 = arg0;
                    do {
                        sp28 = var_v1;
                        func_806782C0(var_s0_2->unk8);
                        var_s0_2 += 4;
                        var_v1 += 1;
                        var_s0_2->unk4 = 0;
                    } while (var_v1 != 5);
                    D_807FBB40->unk154 = 2;
                    D_807FBB40->unk155 = 0;
                    arg0->unk4 = 0x1EU;
                    sp30->unk1F0 = (s32) (sp30->unk1F0 & 0xDFFFFFFF);
                    temp_s0_2 = *(&D_8074E816 + (arg0->unk6 * 6));
                    func_806C8E58(temp_s0_2);
                    func_806F09F0(sp34, temp_s0_2 & 0xFFFF);
                    sp30->unk8C = 0;
                    sp34->unkE6 = (s16) arg0->unk38;
                    func_80627888(sp30->unk104);
                    func_8061EB04(sp34, 0);
                    screenWipeStart(3);
                    healthRefill(0);
                    D_807FC924->unk2E2 = (u16) (D_807FC924->unk2E2 | 0x11);
                    return;
                }
                func_80609140(0x98, 0x7FFF, 0x427C0000, 0x3F800000, 0, 0);
            }
        }
    }
}

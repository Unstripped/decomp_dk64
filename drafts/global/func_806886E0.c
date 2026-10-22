// func_806886E0 (src/global/8D3E0.c): m2c baseline draft; map/level actor setup logic
s32 func_805FF030(u8, ?);                           /* extern */
s32 func_80600080(s32);                             /* extern */
u16 func_80631D8C(u8);                              /* extern */
? func_80631F58(s32, s32 *, s32 *);                 /* extern */
? func_80632084(s32, s32, s32, u16, s32);           /* extern */
? func_8063BF34(s32, s32);                          /* extern */
? func_8063DBD8(s16);                               /* extern */
? func_80659670(f32, f32, f32, s16);                /* extern */
? func_80688A6C();                                  /* extern */
? func_80688FC0(s32);                               /* extern */
s32 func_806C7B34();                                /* extern */
extern s32 D_8076A0A8;
extern s16 D_8076A0AA;
extern u8 D_8076A0AB;
extern ? D_8076A160;
extern ? D_8076A178;
extern s32 D_807F6010;
extern s32 D_807F6C28;

void func_806886E0(s32 arg0, s32 arg1, u8 arg2) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    u16 sp4E;
    f64 var_ft1;
    f64 var_ft3;
    f64 var_ft5;
    s16 var_s1_2;
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    u8 temp_t3;
    u8 temp_t4;
    u8 temp_t5;
    void *temp_v0_2;
    void *var_s0_3;

    var_s0 = arg0;
    temp_s2 = arg1 & 0xFF;
    var_s1 = 0;
    func_80688A6C();
    temp_v0 = func_80600080(D_8076A0A8);
    sp54 = temp_v0;
    if (temp_v0 == -1) {
        switch (temp_s2) {                          /* irregular */
        case 0:
            D_807F6010 = var_s0;
            sp4E = func_80631D8C(D_8076A0AB);
            var_s1 = 1;
            break;
        case 1:
            var_s0 = D_807F6010;
            break;
        }
    } else {
        D_807F6010 = var_s0;
        var_s0 = *(&D_8076A178 + (temp_v0 * 0xC0));
    }
    func_80631F58(var_s0, &sp5C, &sp58);
    if (arg2 != 0) {
        var_s0_2 = 0;
    } else {
        var_s0_2 = func_806C7B34();
    }
    func_80632084(sp5C, var_s0_2, var_s1 & 0xFF, sp4E, func_805FF030(D_8076A0AB, 1));
    func_8063DBD8(D_8076A0AA);
    func_80688FC0(sp58);
    if (sp54 != -1) {
        temp_v0_2 = (sp54 * 0xC0) + &D_8076A160;
        temp_a0 = temp_v0_2->unk20;
        if (temp_a0 != 0) {
            func_8063BF34(temp_a0, temp_v0_2->unk1C);
        }
        var_s1_2 = 0;
        if (D_807F6C28 > 0) {
            var_s0_3 = (sp54 * 0xC0) + &D_8076A160;
            do {
                temp_t3 = var_s0_3->unk24;
                var_ft1 = (f64) temp_t3;
                if ((s32) temp_t3 < 0) {
                    var_ft1 += 4294967296.0;
                }
                temp_t4 = var_s0_3->unk25;
                var_ft5 = (f64) temp_t4;
                if ((s32) temp_t4 < 0) {
                    var_ft5 += 4294967296.0;
                }
                temp_t5 = var_s0_3->unk26;
                var_ft3 = (f64) temp_t5;
                if ((s32) temp_t5 < 0) {
                    var_ft3 += 4294967296.0;
                }
                func_80659670((f32) (var_ft1 / 255.0), (f32) (var_ft5 / 255.0), (f32) (var_ft3 / 255.0), var_s1_2);
                var_s1_2 += 1;
                var_s0_3 += 3;
            } while (var_s1_2 < D_807F6C28);
        }
    }
}

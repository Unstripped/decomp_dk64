// func_806F69A8 (src/global/F9450.c): Stage 1 m2c starter; reviewed 300-instruction target update flow.
? func_8062FF10(f32 (*)[4], f32 (*)[4]);            /* extern */
? func_806355DC(s16, ?);                            /* extern */
? func_806357F8(s16, f32 *, f32 *, f32 *, ? *, ? *, ? *, ? *, ? *, s32); /* extern */
? func_806358E8(s16, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32); /* extern */
? func_806398E4(s16, ?, ?);                         /* extern */
s16 func_8063D990(s16);                             /* extern */
s32 func_806F4E74(s16);                             /* extern */
s32 func_806F544C(s8, s16, u8);                     /* extern */
? func_806F54E0(s32, s16, u8);                      /* extern */
? func_806F6554(s32, void *);                       /* extern */
? func_806F70FC(f32, f32, f32, ?, f32, s32);        /* extern */
? func_806F73A0(s32);                               /* extern */
? func_806F79E0(s16, s32);                          /* extern */
? func_806F8170(s8, f32 *, f32 *, f32 *);           /* extern */
? func_806F8BC4(s32, ?, ?);                         /* extern */
? func_807314F4(s16, s16);                          /* extern */
? heapFree(void *);                                 /* extern */
extern u8 D_807444FC;
extern ? D_80753EF0;
extern s16 D_8076A0AA;
extern s32 D_807FBB64;
extern s32 D_807FC924;
extern u8 D_807FC928;
extern void *D_807FD730;
extern s32 D_807FD734;
extern ? D_807FD740;
extern ? D_807FD780;
extern ? D_807FD790;
extern u8 D_807FD798;

void func_806F69A8(s32 arg0) {
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    ? spB0;
    ? spAC;
    ? spA8;
    ? spA4;
    ? spA0;
    Mtx *sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    Mtx *temp_a1;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_s4;
    s32 temp_v0_2;
    s8 temp_s1;
    u8 temp_v0;
    void *temp_s1_2;
    void *temp_v0_5;
    void *var_s0;
    void *var_s0_2;
    void *var_s2;

    temp_s4 = arg0 & 0xFF;
    D_807FD798 = 0;
    func_806F73A0(temp_s4 & 0xFF);
    D_807FD734 = 0;
    func_806F6554(temp_s4 & 0xFF, (temp_s4 * 0x10) + &D_807FD740);
    var_s0 = *(&D_807FD780 + (temp_s4 * 4));
    if (var_s0 != NULL) {
        do {
            func_806F6554(temp_s4 & 0xFF, var_s0);
            var_s0 = var_s0->unk10;
        } while (var_s0 != NULL);
    }
    if ((D_807FD730 != NULL) && (D_807FC928 == 1)) {
        temp_a1 = D_807FC924 + (temp_s4 * 0x2F0) + (D_807444FC << 6) + 8;
        sp90 = temp_a1;
        guMtxL2F((f32 (*)[4]) &sp118[0], temp_a1);
        func_8062FF10((f32 (*)[4]) &spD8[0], (f32 (*)[4]) &sp118[0]);
        var_s0_2 = D_807FD730;
        var_s2 = NULL;
        if (var_s0_2 != NULL) {
            do {
                temp_v0 = var_s0_2->unk18;
                if (temp_v0 != 0) {
                    var_s0_2->unk18 = (u8) (temp_v0 - 1);
                    var_s2 = var_s0_2;
                    var_s0_2 = var_s0_2->unk1C;
                } else {
                    temp_v0_2 = func_806F4E74(var_s0_2->unk2);
                    temp_s1 = (&D_80753EF0 + (temp_v0_2 * 0x14))->unk2;
                    if (var_s0_2->unk10 == 0) {
                        func_806357F8(var_s0_2->unk0, &spBC, &spB8, &spB4, &spB0, &spAC, &spA8, &spA4, &spA0, 1);
                        guMtxXFML(sp90, spBC, spB8, spB4, var_s0_2 + 4, var_s0_2 + 8, var_s0_2 + 0xC);
                        var_s0_2->unk10 = 1U;
                        func_806398E4(var_s0_2->unk0, 1, 0);
                        if (var_s0_2->unk19 != 0) {
                            func_806F79E0(var_s0_2->unk2, temp_s4 & 0xFF);
                        }
                        if ((temp_s1 >= 0) && !(D_807FBB64 & 0x4000) && ((temp_s1 != 0xB) || !(D_807FBB64 & 0x10000000))) {
                            func_806F8BC4(func_806F544C(temp_s1, var_s0_2->unk2, var_s0_2->unk1A), 0, 0);
                        }
                        temp_v0_3 = var_s0_2->unk2;
                        switch (temp_v0_3) {        /* irregular */
                        case 0xEC:
                            func_806F70FC(spBC, spB8, spB4, 0x3DCCCCCD, 200.0f, 0xA);
                            break;
                        case 0x18D:
                            func_806F70FC(spBC, spB8, spB4, 0x3E99999A, 20.0f, 0x14);
                            break;
                        }
                        if (D_807FD798 != 4) {
                            temp_v0_4 = func_8063D990(var_s0_2->unk0);
                            *(&D_807FD790 + (D_807FD798 * 2)) = temp_v0_4;
                            D_807FD798 += 1;
                            func_807314F4(D_8076A0AA, temp_v0_4);
                        }
                    }
                    func_806F8170(temp_s1, &sp84, &sp88, &sp8C);
                    temp_fv1 = var_s0_2->unk4;
                    temp_fv0 = var_s0_2->unk14;
                    temp_fa0 = var_s0_2->unk8;
                    temp_fa1 = var_s0_2->unkC;
                    guMtxXFMF((f32 (*)[4]) &spD8[0], ((sp84 - temp_fv1) * temp_fv0) + temp_fv1, ((sp88 - temp_fa0) * temp_fv0) + temp_fa0, ((sp8C - temp_fa1) * temp_fv0) + temp_fa1, &spD4, &spD0, &spCC);
                    temp_s1_2 = var_s0_2->unk1C;
                    temp_v0_5 = &D_80753EF0 + (temp_v0_2 * 0x14);
                    var_s0_2->unk14 = (f32) (var_s0_2->unk14 + temp_v0_5->unk4);
                    if ((temp_v0_5->unk8 < var_s0_2->unk14) || (temp_v0_5->unk2 == -2)) {
                        func_806F54E0(temp_s4 & 0xFF, var_s0_2->unk2, var_s0_2->unk1A);
                        func_806355DC(var_s0_2->unk0, 1);
                        if (var_s2 != NULL) {
                            var_s2->unk1C = (void *) var_s0_2->unk1C;
                        } else {
                            D_807FD730 = var_s0_2->unk1C;
                        }
                        heapFree(var_s0_2);
                    } else {
                        func_806358E8(var_s0_2->unk0, spD4, spD0, spCC, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0, 1);
                        var_s2 = var_s0_2;
                    }
                    var_s0_2 = temp_s1_2;
                }
            } while (var_s0_2 != NULL);
        }
    }
}

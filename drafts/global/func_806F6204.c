// func_806F6204 (src/global/F9450.c): Stage 1 m2c starter; reviewed 212-instruction target, including frame and saved-register structure.
s32 func_805FF030(u8, ?);                           /* extern */
? func_8060E430(u16, ?, s32);                       /* extern */
s32 func_80626BC8(s16, s32, s16, s32, s32, s32);    /* extern */
? func_806355DC(s16, ?);                            /* extern */
? func_806362C4(s16, ?);                            /* extern */
s32 func_8063C2A8(s16);                             /* extern */
void *func_806F53EC(void *);                        /* extern */
? func_806F54E0(s32, s16, u8);                      /* extern */
? func_806F58A0(s32, s16, void *);                  /* extern */
? func_806F5A48(s32, s16, void *, s32);             /* extern */
? func_806F5FE8(s16, s16, s16, s16, s32);           /* extern */
s32 func_806F6644(s16, s32, u16);                   /* extern */
? func_806F79E0(s16, s32);                          /* extern */
extern ? D_80753EF0;
extern u8 D_8076A0AB;
extern s32 D_807FBB64;
extern s32 D_807FC924;
extern u8 D_807FC928;
extern void *D_807FD730;
extern void *D_807FD734;

void func_806F6204(void *arg0, s32 arg1, void *arg2) {
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_v0_2;
    s32 temp_s3;
    s32 temp_v0;
    u8 var_v0_2;
    void *temp_s5;
    void *temp_v0_3;
    void *var_s0;
    void *var_v0;

    temp_s3 = arg1 & 0xFF;
    var_s0 = arg0;
    temp_s5 = (D_807FC924 + (temp_s3 * 0x2F0))->unk4;
    if (arg0 != NULL) {
        do {
            temp_v0 = func_80626BC8(var_s0->unk8, (&D_80753EF0 + (var_s0->unk14 * 0x14))->unk10 + var_s0->unkA, var_s0->unkC, (s32) arg2->unk0, (s32) arg2->unk4, (s32) arg2->unk8);
            if ((var_s0->unkE == 0) && ((f32) temp_v0 < ((f32) (&D_80753EF0 + (var_s0->unk14 * 0x14))->unk12 + arg2->unkC)) && ((temp_v0_2 = var_s0->unk4, (temp_v0_2 == 0)) || (temp_v0_2 == temp_s5->unk58)) && (func_8063C2A8(var_s0->unk0) != 0) && (func_806F6644(var_s0->unk0, temp_s3 & 0xFF, var_s0->unk2) != 0)) {
                var_s0->unkE = 1U;
                func_806362C4(var_s0->unk0, 1);
                if (var_s0->unk6 != -1) {
                    func_8060E430((u16) var_s0->unk6, 1, func_805FF030(D_8076A0AB, 1) & 0xFF);
                }
                if (D_807FC928 == 1) {
                    if (D_807FD734 == NULL) {
                        var_v0 = D_807FD730;
                        D_807FD734 = var_v0;
                        if (var_v0 != NULL) {
                            do {
                                D_807FD734 = var_v0;
                                var_v0 = var_v0->unk1C;
                            } while (var_v0 != NULL);
                        }
                    }
                    temp_v0_3 = func_806F53EC(var_s0);
                    temp_v0_3->unk1C = 0;
                    if (D_807FD730 != NULL) {
                        D_807FD734->unk1C = temp_v0_3;
                    } else {
                        D_807FD730 = temp_v0_3;
                    }
                    D_807FD734 = temp_v0_3;
                }
                temp_s1 = (s16) var_s0->unk2;
                switch (temp_s1) {                  /* irregular */
                default:
                    var_v0_2 = D_807FC928;
                    if ((s32) var_v0_2 >= 2) {
                        func_806F54E0(temp_s3 & 0xFF, temp_s1, var_s0->unk13);
block_30:
                        var_v0_2 = D_807FC928;
                    }
                    break;
                case 0x2B:
                case 0x205:
                case 0x206:
                case 0x207:
                case 0x208:
                    func_806F58A0(temp_s3 & 0xFF, var_s0->unk0, temp_s5);
                    goto block_30;
                case 0x11:
                case 0x8F:
                    func_806F5A48(temp_s3 & 0xFF, var_s0->unk0, temp_s5, temp_s1 & 0xFFFF);
                    goto block_30;
                }
                if ((s32) var_v0_2 >= 2) {
                    func_806F79E0((s16) var_s0->unk2, temp_s3 & 0xFF);
                    func_806355DC(var_s0->unk0, 1);
                }
                if (D_807FBB64 & 0x10000) {
                    temp_s1_2 = (s16) var_s0->unk2;
                    if (temp_s1_2 != 0x1D2) {
                        func_806F5FE8(temp_s1_2, var_s0->unk8, var_s0->unkA, var_s0->unkC, 0x258);
                    }
                }
            }
            var_s0 = var_s0->unk18;
        } while (var_s0 != NULL);
    }
}

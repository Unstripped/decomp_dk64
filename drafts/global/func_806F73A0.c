// func_806F73A0 (src/global/F9450.c): stage 3: m2c behavior and switch recovered; typed private probe corrected D_807FD740 base stride to 0x10 but retained a 0x60 frame versus target 0x98 and colored found in s1 rather than v1; retained m2c draft needs type recovery
? actorDespawn(void *);                             /* extern */
s32 func_80626BC8(s32, s32, s32, s32, s32, s32);    /* extern */
s16 func_80632630(s16, f32, f32, f32, f32, s32);    /* extern */
? func_80632E74(s16, s16, s32);                     /* extern */
s16 func_8063D990(s16);                             /* extern */
? func_806CFF9C(void *);                            /* extern */
? func_806F0D68(void *);                            /* extern */
? func_806F50C8(s16, s16, ?, ?, s32, s32);          /* extern */
? func_806F54E0(s32, ?, ?);                         /* extern */
s32 func_806F5C30(u32);                             /* extern */
? func_806F5F2C(u32, ?, s16, s16, s32);             /* extern */
f32 func_806F7378(u32);                             /* extern */
? func_806F79E0(?, s32);                            /* extern */
s32 func_80714608(?);                               /* extern */
? func_80731410(s16, s16, s16, s32);                /* extern */
s32 func_8073198C(s16);                             /* extern */
s32 hashTableLookup(s16);                           /* extern */
extern ? D_80753EF0;
extern ? D_80754238;
extern s16 D_8076A0AA;
extern s32 D_807F6000;
extern s32 D_807FBB60;
extern s32 D_807FBB64;
extern s32 D_807FC924;
extern u8 D_807FC928;
extern ? D_807FCC4B;
extern ? D_807FD740;
extern ? D_807FD780;
extern u16 gActiveActorCount;
extern void *gActiveActors;

void func_806F73A0(s32 arg0) {
    s32 sp90;
    void **sp58;
    ? *var_s3;
    s16 temp_s0;
    s16 temp_s0_2;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_s6;
    s32 temp_t3;
    s32 var_s5;
    s32 var_v1;
    u32 temp_a0;
    u32 temp_v0_2;
    void *temp_fp;
    void *temp_s1;
    void *temp_s2;
    void *temp_s4;
    void *temp_s7;
    void *var_s0;

    temp_s6 = arg0 & 0xFF;
    temp_fp = (D_807FC924 + (temp_s6 * 0x2F0))->unk4;
    temp_s7 = temp_fp->unk174;
    if (*(&D_807FCC4B + (temp_s6 * 0x306)) > 0) {
        var_s3 = &D_80753EF0;
        do {
            if (var_s3->unkE != 0) {
                sp90 = 0;
                if ((s32) gActiveActorCount > 0) {
                    sp58 = &gActiveActors;
                    do {
                        temp_s2 = *sp58;
                        if ((D_807FBB60 & 0x10000) && (temp_s2->unk58 == var_s3->unkE) && ((temp_v0 = var_s3->unkC, (temp_v0 == 0)) || (temp_fp->unk58 == temp_v0))) {
                            temp_s1 = (temp_s6 * 0x10) + &D_807FD740;
                            var_s0 = *(&D_807FD780 + (temp_s6 * 4));
                            var_v1 = 0;
                            if ((f32) func_80626BC8((s32) temp_s2->unk7C, (s32) ((f32) var_s3->unk10 + temp_s2->unk80), (s32) temp_s2->unk84, (s32) temp_s1->unk0, (s32) temp_s1->unk4, (s32) temp_s1->unk8) < (((f32) var_s3->unk12 + temp_s1->unkC) - 1.0f)) {
                                var_v1 = 1;
                            }
                            if ((var_v1 == 0) && (var_s0 != NULL)) {
loop_13:
                                var_v1 = 0;
                                if ((f32) func_80626BC8((s32) temp_s2->unk7C, (s32) ((f32) var_s3->unk10 + temp_s2->unk80), (s32) temp_s2->unk84, (s32) var_s0->unk0, (s32) var_s0->unk4, (s32) var_s0->unk8) < (((f32) var_s3->unk12 + var_s0->unkC) - 1.0f)) {
                                    var_v1 = 1;
                                }
                                var_s0 = var_s0->unk10;
                                if ((var_v1 == 0) && (var_s0 != NULL)) {
                                    goto loop_13;
                                }
                            }
                            if ((temp_s2->unk154 == 0x64) || (var_v1 != 0)) {
                                if ((D_807FBB64 & 0x10000) && (func_806F5C30(temp_s2->unk58) != 0)) {
                                    func_806F5F2C(temp_s2->unk58, 0x258, (s16) (s32) temp_s2->unk7C, (s16) (s32) temp_s2->unk80, (s32) temp_s2->unk84);
                                }
                                temp_s4 = temp_s2->unk174;
                                if (temp_s4->unk1 != 0) {
                                    if ((s32) D_807FC928 >= 2) {
                                        temp_v0_2 = temp_s2->unk58;
                                        switch (temp_v0_2) { /* irregular */
                                        case 0x7A:
                                            func_806F79E0(0x1D2, temp_s6 & 0xFF);
                                            func_806F54E0(temp_s6 & 0xFF, 0x1D2, 0);
                                            break;
                                        case 0x79:
                                            func_806F79E0(0x8E, temp_s6 & 0xFF);
                                            temp_s7->unk264 = 0;
                                            break;
                                        case 0x2F:
                                            func_806F79E0(0x57, temp_s6 & 0xFF);
                                            func_806F54E0(temp_s6 & 0xFF, 0x57, 0);
                                            break;
                                        case 0x77:
                                            func_806F79E0(0x1D0, temp_s6 & 0xFF);
                                            temp_s7->unk264 = 1;
                                            break;
                                        case 0x78:
                                            func_806F79E0(0x1CF, temp_s6 & 0xFF);
                                            temp_s7->unk264 = 2;
                                            break;
                                        case 0x33:
                                            func_806F79E0(0x8F, temp_s6 & 0xFF);
                                            if ((func_80714608(0) != 0) && (temp_fp->unk174->unk8C == 0)) {
                                                func_806F0D68(temp_fp);
                                                func_806CFF9C(temp_fp);
                                            }
                                            break;
                                        case 0x34:
                                            func_806F79E0(0x56, temp_s6 & 0xFF);
                                            temp_s7->unk264 = 3;
                                            break;
                                        case 0x76:
                                            func_806F79E0(0x1D1, temp_s6 & 0xFF);
                                            temp_s7->unk264 = 4;
                                            break;
                                        }
                                    } else {
                                        temp_a0 = temp_s2->unk58;
                                        var_s5 = 1;
                                        if ((temp_a0 != 0x2F) && (temp_a0 != 0x48) && (temp_a0 != 0x56)) {
                                            var_s5 = 0;
                                        }
                                        temp_v0_3 = func_80632630(var_s3->unk0, temp_s2->unk7C, func_806F7378(temp_a0) + temp_s2->unk80, temp_s2->unk84, 0.0f, 0);
                                        temp_s0 = func_8063D990(temp_v0_3);
                                        func_80731410(D_8076A0AA, temp_s0, temp_s4->unkA, func_8073198C(temp_s4->unkA) & 0xFF);
                                        temp_s0_2 = func_8063D990(temp_v0_3);
                                        func_80632E74(D_8076A0AA, temp_s0_2, (hashTableLookup(temp_v0_3) * 0x90) + D_807F6000 + 0x8C);
                                        func_806F50C8(temp_v0_3, var_s3->unk0, 0, 1, 0, var_s5);
                                        temp_s2->unk11C = 0;
                                    }
                                    actorDespawn(temp_s2);
                                }
                            }
                        }
                        temp_t3 = sp90 + 1;
                        sp58 += 8;
                        sp90 = temp_t3;
                    } while (temp_t3 < (s32) gActiveActorCount);
                }
            }
            var_s3 += 0x14;
        } while (var_s3 != &D_80754238);
    }
}

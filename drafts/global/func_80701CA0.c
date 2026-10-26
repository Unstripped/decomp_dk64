// func_80701CA0 (src/global/103AB0.c): Stage 2 m2c reconstruction; behavior decoded from local asm, but frame/register allocation and typed local views still need work.
void *func_805FCFD8(s32);                           /* extern */
void *func_80610FE8(?);                             /* extern */
s32 flagGet(?, ?);                            /* extern */
? heapFreeDeferred(void *);                         /* extern */
extern ? D_2000000;
extern ? D_2000080;
extern ? D_2000180;
extern ? D_2000200;
extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;
extern s32 D_8076A0A8;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FD890;

void *func_80701CA0(void *arg0) {
    u8 spC3;
    u8 spBA;
    ? *sp6C;
    ? *sp68;
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv1;
    s16 temp_v0_3;
    s32 temp_s2;
    s32 temp_t2;
    s32 temp_t3;
    s32 var_fp;
    s32 var_s5;
    s32 var_t6;
    void *temp_a2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s1_6;
    void *temp_s1_7;
    void *temp_s1_8;
    void *temp_s3;
    void *temp_s7;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *var_s1;
    void *var_v1;

    var_s1 = arg0;
    spC3 = 0;
    var_fp = 0x64;
    spBA = 0;
    switch (D_8076A0A8) {                           /* switch 1; irregular */
    case 0x2D:                                      /* switch 1 */
        spBA = 1;
    default:                                        /* switch 1 */
block_12:
        var_s5 = 0;
        if ((s32) D_807FC928 > 0) {
            do {
                temp_s2 = var_s5 * 0x2F0;
                var_v1 = D_807FC924 + temp_s2;
                if (var_v1->unk0 != 0) {
                    temp_s3 = var_v1->unk4->unk174;
                    temp_s7 = temp_s3->unk104->unk174;
                    if (spBA == 0) {
                        if (var_v1->unk2E8 != 0) {
                            if (var_v1->unk220 < (var_v1->unk24C + 3.0f)) {
                                goto block_20;
                            }
                        }
                    } else {
block_20:
                        spC3 = 1;
                        sp68 = &D_2000180;
                        sp6C = &D_2000080;
                        temp_v0 = func_80610FE8(0x40);
                        heapFreeDeferred(temp_v0);
                        temp_v0->unk0 = (s16) (D_807FC924 + temp_s2)->unk270;
                        temp_v0->unk4 = -0xA;
                        temp_v0->unk2 = (s16) (D_807FC924 + temp_s2)->unk272;
                        temp_v0->unk10 = (s16) (D_807FC924 + temp_s2)->unk274;
                        temp_v0->unk14 = -0xA;
                        temp_v0->unk12 = (s16) (D_807FC924 + temp_s2)->unk272;
                        temp_v0->unk20 = (s16) (D_807FC924 + temp_s2)->unk274;
                        temp_v0->unk24 = -0xA;
                        temp_v0->unk22 = (s16) (D_807FC924 + temp_s2)->unk276;
                        temp_v0->unk30 = (s16) (D_807FC924 + temp_s2)->unk270;
                        temp_v0->unk34 = -0xA;
                        temp_v0->unk32 = (s16) (D_807FC924 + temp_s2)->unk276;
                        var_s1->unk4 = 0;
                        var_s1->unk0 = 0xE7000000;
                        temp_v0_2 = func_805FCFD8(var_s1 + 8);
                        temp_a2 = temp_v0_2 + 0x18;
                        temp_v0_2->unk0 = (s32) ((((s32) ((f32) D_80744498 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32) ((f32) D_8074449C * 4.0f) & 0xFFF));
                        temp_v0_2->unkC = 0x504340;
                        temp_v0_2->unk8 = 0xE200001C;
                        temp_v0_2->unk4 = (s32) ((((s32) ((f32) D_807444A0 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) D_807444A4 * 4.0f) & 0xFFF));
                        temp_v0_2->unk14 = 0xFFFDF6FB;
                        temp_v0_2->unk10 = 0xFCFFFFFF;
                        temp_v1 = D_807FC924 + temp_s2;
                        temp_fv1 = temp_v1->unk24C - temp_v1->unk220;
                        switch (D_8076A0A8) {       /* switch 2; irregular */
                        default:                    /* switch 2 */
                            var_fa0 = (f32) var_fp;
                            if (var_fp < 0) {
                                var_fa0 += 4294967296.0f;
                            }
block_29:
                            var_fv1 = (f32) ((f64) temp_fv1 * 0.4);
                            break;
                        case 0x1E:                  /* switch 2 */
                            var_fa0 = (f32) var_fp;
                            var_fv1 = (f32) ((f64) temp_fv1 * 0.07);
                            if (var_fp < 0) {
                                var_fa0 += 4294967296.0f;
                            }
                            break;
                        case 0x2C:                  /* switch 2 */
                            var_fp = 0x32;
                            var_fa0 = (f32) 0x32;
                            var_fv1 = (f32) ((f64) temp_fv1 * 0.07);
                            break;
                        case 0x6F:                  /* switch 2 */
                            var_fp = 0x32;
                            var_fa0 = (f32) 0x32;
                            goto block_29;
                        }
                        if (var_fv1 > 80.0f) {
                            var_fv1 = 80.0f;
                        }
                        if (D_807FD890 != 0) {
                            temp_s3->unk1E8 = var_fv1;
                        } else {
                            temp_fv0 = temp_s3->unk1E8;
                            temp_s3->unk1E8 = (f32) ((f64) temp_fv0 + ((f64) (var_fv1 - temp_fv0) * 0.05));
                            temp_t3 = (u32) temp_s3->unk1E8 & 0xFF;
                            var_fv1 = (f32) temp_t3;
                            if (temp_t3 < 0) {
                                var_fv1 += 4294967296.0f;
                            }
                        }
                        temp_ft0 = var_fa0 + var_fv1;
                        temp_s1 = temp_a2 + 8;
                        temp_s1_2 = temp_s1 + 8;
                        temp_v0_2->unk18 = 0xFA000000;
                        temp_s1_3 = temp_s1_2 + 8;
                        if (M2C_ERROR(/* cfc1 */) & 0x78) {
                            if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                                var_t6 = (s32) (temp_ft0 - 2.1474836e9f) | 0x80000000;
                            } else {
                                goto block_39;
                            }
                        } else {
                            var_t6 = (s32) temp_ft0;
                            if (var_t6 < 0) {
block_39:
                                var_t6 = -1;
                            }
                        }
                        temp_a2->unk4 = (s32) ((var_t6 & 0xFF) | 0x3C00);
                        temp_s1->unk4 = 0;
                        temp_a2->unk8 = 0xE3000A01;
                        temp_s1->unk8 = 0xDA380007;
                        temp_s1_2->unk4 = sp6C;
                        temp_s1_2->unk8 = 0xDA380003;
                        temp_s1_4 = temp_s1_3 + 8;
                        temp_s1_3->unk4 = sp68;
                        temp_s1_3->unk8 = 0x01004008;
                        temp_s1_5 = temp_s1_4 + 8;
                        temp_s1_4->unk4 = osVirtualToPhysical(temp_v0);
                        temp_s1_6 = temp_s1_5 + 8;
                        temp_s1_5->unk4 = 0x406;
                        temp_s1_4->unk8 = 0x06000204;
                        temp_s1_5->unk8 = 0xE7000000;
                        temp_s1_6->unk4 = 0;
                        var_s1 = temp_s1_6 + 8;
                        var_v1 = D_807FC924 + temp_s2;
                    }
                    var_v1->unk2E8 = (u8) temp_s7->unkFA;
                    (D_807FC924 + temp_s2)->unk24C = (f32) temp_s7->unk90;
                }
                temp_t2 = (var_s5 + 1) & 0xFF;
                var_s5 = temp_t2;
            } while (temp_t2 < (s32) D_807FC928);
        }
        if (spC3 != 0) {
            temp_s1_7 = var_s1 + 8;
            var_s1->unk0 = 0xDA380007;
            var_s1->unk4 = &D_2000000;
            temp_s1_8 = temp_s1_7 + 8;
            var_s1->unk8 = 0xDA380005;
            temp_s1_7->unk4 = &D_2000200;
            temp_s1_7->unk8 = 0xDA380003;
            temp_s1_8->unk4 = &D_2000180;
            var_s1 = temp_s1_8 + 8;
            D_807FD890 = 0;
        } else {
            D_807FD890 = 1;
        }
        break;
    case 0x2B:                                      /* switch 1 */
    case 0x2E:                                      /* switch 1 */
    case 0x2F:                                      /* switch 1 */
    case 0xB3:                                      /* switch 1 */
        break;
    case 0x1E:                                      /* switch 1 */
        temp_v0_3 = D_807FC924->unk290;
        if (((temp_v0_3 == 9) || (temp_v0_3 == 0xA)) && (flagGet(0x9C, 0) != 0)) {

        } else {
        case 0x1F:                                  /* switch 1 */
        case 0x20:                                  /* switch 1 */
        case 0x21:                                  /* switch 1 */
        case 0x22:                                  /* switch 1 */
        case 0x23:                                  /* switch 1 */
        case 0x24:                                  /* switch 1 */
        case 0x25:                                  /* switch 1 */
        case 0x26:                                  /* switch 1 */
        case 0x27:                                  /* switch 1 */
        case 0x28:                                  /* switch 1 */
        case 0x29:                                  /* switch 1 */
        case 0x2A:                                  /* switch 1 */
        case 0x2C:                                  /* switch 1 */
            goto block_12;
        }
        break;
    }
    return var_s1;
}

// func_806FB914 (src/global/100180.c): Stage 1 m2c draft saved; glyph mapping helper remains.
s32 _strchr(? *, u8);                               /* extern */
extern ? D_80754A64;
extern ? D_80754AA0;
extern ? D_8075DC20;

s8 func_806FB914(s16 arg0, u8 *arg1) {
    s8 spDF;
    ? spA4;
    ? sp74;
    ? sp38;
    ? sp28;
    ? *temp_t9;
    u8 temp_v1;
    u8 temp_v1_2;
    void *temp_t3;
    void *temp_t3_2;
    void *temp_t6;
    void *temp_t8;

    spDF = 0;
    switch (arg0) {                                 /* switch 1 */
    case 0:                                         /* switch 1 */
        temp_v1 = *arg1;
        if ((s32) temp_v1 >= 0x2F) {
            switch (temp_v1) {                      /* switch 2 */
            case 0x61:                              /* switch 2 */
            case 0x79:                              /* switch 2 */
                spDF = 1;
                break;
            }
        } else if (temp_v1 == 0x2E) {
        case 0x67:                                  /* switch 2 */
        case 0x70:                                  /* switch 2 */
        case 0x71:                                  /* switch 2 */
        case 0x80:                                  /* switch 2 */
            spDF = 2;
        }
        *arg1 = temp_v1 - 0x21;
        break;
    case 1:                                         /* switch 1 */
        M2C_MEMCPY_ALIGNED(&spA4, &D_80754A64, 0x30);
        temp_t6 = &spA4 + 0x30;
        temp_t3 = &D_80754A64 + 0x30;
        spA4.unk30 = (s32) D_80754A64.unk30;
        temp_t6->unk4 = (s32) temp_t3->unk4;
        temp_t6->unk8 = (u8) temp_t3->unk8;
        *arg1 = _strchr(&spA4, *arg1) - &spA4;
        break;
    case 6:                                         /* switch 1 */
        M2C_MEMCPY_ALIGNED(&sp74, &D_80754AA0, 0x30);
        *arg1 = _strchr(&sp74, *arg1) - &sp74;
        break;
    case 2:                                         /* switch 1 */
        M2C_MEMCPY_ALIGNED(&sp38, &D_8075DC20, 0x30);
        temp_t8 = &sp38 + 0x30;
        temp_t3_2 = &D_8075DC20 + 0x30;
        sp38.unk30 = (s32) D_8075DC20.unk30;
        temp_t8->unk4 = (s32) temp_t3_2->unk4;
        temp_t8->unk8 = (u16) temp_t3_2->unk8;
        *arg1 = _strchr(&sp38, *arg1) - &sp38;
        break;
    case 3:                                         /* switch 1 */
    case 7:                                         /* switch 1 */
        temp_t9 = "0123456789%/";
        sp28.unk0 = (s32) temp_t9->unk0;
        sp28.unk4 = (s32) temp_t9->unk4;
        sp28.unk8 = (s32) temp_t9->unk8;
        sp28.unkC = (u8) temp_t9->unkC;
        *arg1 = _strchr(&sp28, *arg1) - &sp28;
        break;
    case 4:                                         /* switch 1 */
        temp_v1_2 = *arg1;
        if (temp_v1_2 == 0x40) {
            *arg1 = 0x60;
        } else {
            *arg1 = temp_v1_2 - 0x21;
        }
        break;
    case 5:                                         /* switch 1 */
        *arg1 -= 0x21;
        break;
    }
    return spDF;
}

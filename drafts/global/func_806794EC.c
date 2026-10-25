// func_806794EC (src/global/7CA80.c): from .scratch/R3C/func_806794EC_best.c
s32 func_80672328(void *, ?32, ?32);                /* extern */
? func_80675810(void *, void *);                    /* extern */
? func_80678F9C(void *, void *);                    /* extern */
? func_80679DC4(void *, void *, s32);               /* extern */
void *func_8067A09C(void *);                        /* extern */
? func_8067AC38();                                  /* extern */
s32 func_8067AF44(void *);                          /* extern */
? playerStateQueueCallback(?, void *, u8);                     /* extern */
? memcpy(? *, void *, ?);                           /* extern */
extern s32 D_807FBB48;
extern ? D_807FBB70;
extern ? D_807FBC08;
extern ? D_807FBC14;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806794EC(void *arg0) {
    s32 sp50;
    ?32 sp4C;
    ?32 sp48;
    ?32 sp44;
    s32 sp40;
    u8 sp3E;
    f32 var_ft0;
    s32 temp_a0;
    s8 var_s7;
    u8 temp_t7;
    u8 temp_v0_2;
    u8 temp_v1_2;
    u8 temp_v1_3;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_v0;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    void *temp_v1;
    void *var_s2;

    var_s7 = -1;
    func_8067AC38();
    temp_v0 = func_8067A09C(arg0->unk13C);
    arg0->unk13C = temp_v0;
    var_s2 = temp_v0;
    sp50 = arg0->unk138;
    if (temp_v0 != NULL) {
        do {
            temp_a0 = var_s2->unk0;
            if (temp_a0 & sp50) {
                switch (temp_a0) {                  /* switch 1; irregular */
                case 0x8000:                        /* switch 1 */
                    func_80675810(arg0, var_s2);
                    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk200 == 0xA)) && (arg0->unk5C & 1)) {
                        func_80679DC4(arg0, D_807FBB70.unk1FC, (D_807FBB70.unk200 == 0xA) & 0xFF);
                    }
                    break;
                case 0x2:                           /* switch 1 */
                    temp_v0_2 = var_s2->unk4;
                    switch (temp_v0_2) {            /* switch 2 */
                    case 0:                         /* switch 2 */
                        D_807FBB70.unk16 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x10, NULL, D_807FC929);
                        }
                        break;
                    case 1:                         /* switch 2 */
                        D_807FBB70.unk17 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0xE, var_s2->unk8, D_807FC929);
                        }
                        break;
                    case 2:                         /* switch 2 */
                        D_807FBB70.unk18 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x12, NULL, D_807FC929);
                        }
                        break;
                    case 3:                         /* switch 2 */
                        D_807FBB70.unk19 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x13, NULL, D_807FC929);
                        }
                        break;
                    case 6:                         /* switch 2 */
                        D_807FBB70.unk1B = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x36, var_s2->unk8, D_807FC929);
                        }
                        break;
                    case 4:                         /* switch 2 */
                    case 5:                         /* switch 2 */
                        if (arg0 == D_807FBB48) {
                            if (temp_v0_2 == 4) {
                                playerStateQueueCallback(0x2B, var_s2->unk8, D_807FC929);
                            } else {
                                playerStateQueueCallback(0x32, var_s2->unk8, D_807FC929);
                            }
                            temp_v1 = var_s2->unk8;
                            if ((temp_v1 != NULL) && (temp_v1->unk5C & 2)) {
                                temp_v0_3 = temp_v1->unk174;
                                temp_v0_3->unk1A = (u16) (temp_v0_3->unk1A | 0x100);
                            }
                        }
                        break;
                    }
                    break;
                case 0x8:                           /* switch 1 */
                    func_80679DC4(arg0, var_s2->unk8, 0);
                    break;
                case 0x4:                           /* switch 1 */
                    func_80679DC4(arg0, var_s2->unk8, 1 & 0xFF);
                    break;
                case 0x800:                         /* switch 1 */
                    arg0->unk144 = (u8) var_s2->unk4;
                    D_807FBB70.unk90 = 1;
                    break;
                case 0x400:                         /* switch 1 */
                    temp_v0_4 = var_s2->unk10;
                    D_807FD580->unk70 = (s16) temp_v0_4->unk0;
                    D_807FD580->unk74 = (?32) temp_v0_4->unk4;
                    D_807FD580->unk6C = (f32) (s16) temp_v0_4->unk8;
                    D_807FBB70.unk1A = 1;
                    if (arg0 == D_807FBB48) {
                        playerStateQueueCallback(0x17, var_s2->unk8, D_807FC929);
                    }
                    break;
                case 0x10:                          /* switch 1 */
                    temp_v0_5 = var_s2->unk10;
                    temp_v1_2 = (u8) temp_v0_5->unk8;
                    if (var_s7 < (s32) temp_v1_2) {
                        sp4C = temp_v0_5->unk0;
                        sp40 = temp_a0;
                        var_s7 = (s8) temp_v1_2;
                        sp44 = temp_v0_5->unk4;
                        sp3E = temp_v0_5->unk9;
                    }
                    break;
                case 0x20:                          /* switch 1 */
                    temp_v0_6 = var_s2->unk10;
                    temp_v1_3 = (u8) temp_v0_6->unkC;
                    if (var_s7 < (s32) temp_v1_3) {
                        sp4C = temp_v0_6->unk0;
                        var_s7 = (s8) temp_v1_3;
                        sp48 = temp_v0_6->unk4;
                        sp40 = temp_a0;
                        sp44 = temp_v0_6->unk8;
                        sp3E = temp_v0_6->unkD;
                    }
                    break;
                case 0x100000:                      /* switch 1 */
                    temp_v0_7 = var_s2->unk10;
                    D_807FBB70.unkD8 = (?32) temp_v0_7->unk0;
                    D_807FBB70.unkDC = (?32) temp_v0_7->unk4;
                    D_807FBB70.unkE4 = 1;
                    D_807FBB70.unkE0 = (?32) temp_v0_7->unk8;
                    D_807FBB70.unkEC = (void *) var_s2->unk8;
                    break;
                case 0x1000:                        /* switch 1 */
                    D_807FBB70.unk1C = 1;
                    D_807FBB70.unk20 = (void *) var_s2->unk8;
                    break;
                case 0x4000:                        /* switch 1 */
                    temp_v0_8 = var_s2->unk10;
                    D_807FBB70.unk2C = 1;
                    D_807FBB70.unk30 = (?32) temp_v0_8->unk4;
                    D_807FBB70.unk34 = (s16) temp_v0_8->unk8;
                    D_807FBB70.unk36 = (s16) temp_v0_8->unk0;
                    break;
                case 0x2000:                        /* switch 1 */
                    if (var_s2->unk4 != 0) {
                        D_807FBB70.unk24 = 1;
                    } else {
                        D_807FBB70.unk25 = 1;
                    }
                    D_807FBB70.unk28 = (void *) var_s2->unk8;
                    break;
                case 0x80:                          /* switch 1 */
                    arg0->unk60 = (s32) (arg0->unk60 | 8);
                    if (arg0 == D_807FBB48) {
                        playerStateQueueCallback(0x16, var_s2->unk8, D_807FC929);
                    }
                    break;
                case 0x40:                          /* switch 1 */
                    if (var_s2->unk4 != 0) {
                        arg0->unk60 = (s32) (arg0->unk60 | 4);
                    } else {
                        arg0->unk60 = (s32) (arg0->unk60 & ~4);
                    }
                    break;
                case 0x1:                           /* switch 1 */
                    temp_s0 = var_s2->unk10;
                    if ((func_8067AF44(var_s2->unk8) != 0) && (D_807FBB70.unk39 != 4)) {
                        (&D_807FBB70 + (D_807FBB70.unk39 * 0xC))->unk3C = (f32) temp_s0->unk0;
                        (&D_807FBB70 + (D_807FBB70.unk39 * 0xC))->unk40 = (f32) temp_s0->unk4;
                        (&D_807FBB70 + (D_807FBB70.unk39 * 0xC))->unk44 = (f32) temp_s0->unk8;
                        (&D_807FBB70 + (D_807FBB70.unk39 * 4))->unk6C = (s32) temp_s0->unkC;
                        (&D_807FBB70 + (D_807FBB70.unk39 * 4))->unk7C = (void *) var_s2->unk8;
                        (&D_807FBB70 + D_807FBB70.unk39)->unk8C = (u8) temp_s0->unk10;
                        D_807FBB70.unk39 = (u8) (D_807FBB70.unk39 + 1);
                        func_80678F9C(arg0, var_s2->unk8);
                    }
                    break;
                case 0x20000:                       /* switch 1 */
                    temp_s0_2 = var_s2->unk10;
                    if (D_807FBB70.unk1F8 != 4) {
                        memcpy(&D_807FBB70 + (D_807FBB70.unk1F8 << 6) + 0xF8, temp_s0_2, 0xC);
                        memcpy(&D_807FBB70 + (D_807FBB70.unk1F8 << 6) + 0x104, temp_s0_2 + 0xC, 0x24);
                        (&D_807FBB70 + (D_807FBB70.unk1F8 << 6))->unk128 = (s32) temp_s0_2->unk30;
                        (&D_807FBB70 + (D_807FBB70.unk1F8 << 6))->unk12C = (s32) temp_s0_2->unk34;
                        (&D_807FBB70 + (D_807FBB70.unk1F8 << 6))->unk130 = (s32) temp_s0_2->unk38;
                        (&D_807FBB70 + (D_807FBB70.unk1F8 << 6))->unk134 = (void *) var_s2->unk8;
                        D_807FBB70.unk1F8 = (s32) (D_807FBB70.unk1F8 + 1);
                    }
                    break;
                case 0x10000:                       /* switch 1 */
                    temp_s0_3 = var_s2->unk10;
                    D_807FBB70.unk91 = 1;
                    D_807FBB70.unk92 = (s16) temp_s0_3->unk0;
                    D_807FBB70.unk94 = (s16) temp_s0_3->unk2;
                    memcpy(&D_807FBC08, temp_s0_3 + 4, 0xC);
                    memcpy(&D_807FBC14, temp_s0_3 + 0x10, 0x24);
                    D_807FBB70.unkC8 = (s32) temp_s0_3->unk34;
                    D_807FBB70.unkCC = (void *) var_s2->unk8;
                    D_807FBB70.unkD0 = (s32) temp_s0_3->unk38;
                    D_807FBB70.unkD4 = (s32) temp_s0_3->unk3C;
                    break;
                case 0x40000:                       /* switch 1 */
                    temp_v0_9 = arg0->unk140;
                    if (temp_v0_9 != NULL) {
                        temp_v0_9->unk68 = (?32) var_s2->unk10->unk0;
                    }
                    break;
                case 0x80000:                       /* switch 1 */
                    D_807FBB70.unk38 = 1;
                    break;
                case 0x200000:                      /* switch 1 */
                    temp_v0_10 = var_s2->unk10;
                    D_807FBB70.unkF0 = (?32) temp_v0_10->unk0;
                    D_807FBB70.unkF4 = (?32) temp_v0_10->unk4;
                    break;
                case 0x400000:                      /* switch 1 */
                    temp_t7 = var_s2->unk4;
                    var_ft0 = (f32) temp_t7;
                    if ((s32) temp_t7 < 0) {
                        var_ft0 += 4294967296.0f;
                    }
                    D_807FBB70.unkE8 = var_ft0;
                    D_807FBB70.unkE5 = 1;
                    break;
                case 0x1000000:                     /* switch 1 */
                    if ((s32) D_807FBB70.unk254 < 8) {
                        (&D_807FBB70 + (D_807FBB70.unk254 * 4))->unk258 = (s32) var_s2->unk4;
                        (&D_807FBB70 + (D_807FBB70.unk254 * 4))->unk278 = (void *) var_s2->unk10;
                        D_807FBB70.unk254 = (u8) (D_807FBB70.unk254 + 1);
                    }
                    break;
                case 0x800000:                      /* switch 1 */
                    temp_v0_11 = var_s2->unk10;
                    D_807FBB70.unk4 = (?32) temp_v0_11->unk0;
                    D_807FBB70.unk8 = (?32) temp_v0_11->unk4;
                    D_807FBB70.unkC = (?32) temp_v0_11->unk8;
                    D_807FBB70.unk10 = (s16) temp_v0_11->unkC;
                    D_807FBB70.unk2 = 1;
                    D_807FBB70.unk12 = (s16) temp_v0_11->unkE;
                    D_807FBB70.unk14 = (u8) var_s2->unk4;
                    break;
                case 0x2000000:                     /* switch 1 */
                    D_807FBB70.unk0 = 1;
                    D_807FBB70.unk1 = (u8) var_s2->unk4;
                    break;
                }
            }
            var_s2 = var_s2->unk14;
        } while (var_s2 != NULL);
    }
    if ((var_s7 != -1) && ((sp3E == 1) || (func_80672328(arg0, sp4C, sp44) != 0))) {
        switch (sp40) {                             /* switch 3; irregular */
        case 16:                                    /* switch 3 */
            arg0->unk7C = sp4C;
            arg0->unk84 = sp44;
            return;
        case 32:                                    /* switch 3 */
            arg0->unk7C = sp4C;
            arg0->unk80 = sp48;
            arg0->unk84 = sp44;
            break;
        }
    }
}

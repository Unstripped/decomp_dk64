// func_80715270 (src/global/119370.c): Stage 1: m2c reconstruction retained for the large display-list/effect update; target inspection confirms 0x80 frame and s0-s7 state traversal. It needs concrete runtime view/prototype recovery before a meaningful compiler attempt.
? actorGetNodePos(void *, u8, void *, void *, void *); /* extern */
? assetFreeBuffer(s32, ?, ?);                       /* extern */
? func_806303C4(?, ?, void *, ?32, f32, ?32, s32, s32, s32, s32, s32); /* extern */
? func_806335B0(s16, ?, u8, void *, void *, void *); /* extern */
s8 func_806531B8(?32, f32, ?, ?, ?32, ?);           /* extern */
? effectFreeAndUnlink(void *);                       /* extern */
? func_80715A3C(s32, u8, s32, s32, s32, void *);    /* extern */
? func_80715B30(void *, u8, s32, s32, f32, f32, f32, ?32, f32, ?32, s32); /* extern */
? memcpy(void *, void *, ?);                        /* extern */
extern u8 D_807444FC;
extern u8 D_80750AB4;
extern s32 D_8076A064;
extern s32 D_807FC924;
extern void *D_807FDB00;
extern void *D_807FDB04;

void func_80715270(s32 arg0) {
    u8 sp7B;
    ? (*temp_v0_3)(void *, u8 *);
    s16 temp_v0;
    s32 temp_s7;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_v0_5;
    s32 temp_v0_9;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s2_2;
    s32 var_v1;
    u16 temp_v0_7;
    u8 temp_t6;
    u8 temp_v0_2;
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0_10;
    void *temp_v0_4;
    void *temp_v0_6;
    void *temp_v0_8;
    void *var_s1_4;
    void *var_s2;
    s32 phi_v1;
    s32 phi_v1_2;

    var_s2 = D_807FDB04;
    temp_s7 = arg0 & 0xFF;
    if (var_s2 != NULL) {
        do {
            temp_v0 = var_s2->unk368;
            if (temp_v0 == 0) {
                var_s2->unk32C = 0U;
                var_s2->unk32D = 0U;
                var_s2->unk21 = 0;
                var_s2->unk330->unk18 = (s32) D_8076A064;
                temp_v0_2 = var_s2->unk334;
                var_s2->unk38C = (u16) (var_s2->unk38C & 0xFFEF);
                switch (temp_v0_2) {                /* irregular */
                case 1:
                    func_806335B0(var_s2->unk33C, 1, var_s2->unk33E, var_s2 + 0x340, var_s2 + 0x344, var_s2 + 0x348);
                    break;
                case 2:
                    temp_a0 = var_s2->unk338;
                    if ((temp_a0->unk60 & 0x200) || (temp_a0->unk4 == 0)) {
                        actorGetNodePos(temp_a0, var_s2->unk33E, var_s2 + 0x340, var_s2 + 0x344, var_s2 + 0x348);
                    } else {
                        var_s2->unk38C = (u16) (var_s2->unk38C | 0x10);
                    }
                    break;
                }
                sp7B = 0;
                if ((temp_s7 == 0) || (var_s2->unk38C & 1)) {
                    temp_v0_3 = var_s2->unk328;
                    if (temp_v0_3 != NULL) {
                        temp_v0_3(var_s2, &sp7B);
                    }
                } else if (var_s2->unk328 != NULL) {
                    var_s0 = 0;
                    var_s1 = 0;
                    if ((s32) D_80750AB4 > 0) {
                        do {
                            if (*(D_807FC924 + var_s1) != 0) {
                                temp_v0_4 = var_s2 + (var_s0 << 7);
                                memcpy(temp_v0_4 + (D_807444FC << 6) + 0x128, temp_v0_4 + ((D_807444FC ^ 1) << 6) + 0x128, 0x40);
                            }
                            var_s0 += 1;
                            var_s1 += 0x2F0;
                        } while (var_s0 < (s32) D_80750AB4);
                    }
                    var_s2->unk32C = 3U;
                }
                if (var_s2->unk330->unk16 == var_s2->unk34E) {
                    temp_v0_5 = var_s2->unk354;
                    var_s2->unk34E = 0;
                    temp_t3 = var_s2->unk358 + 1;
                    var_s2->unk358 = temp_t3;
                    if ((temp_v0_5 == temp_t3) && (temp_v0_5 != -1)) {
                        var_s2->unk32D = 1U;
                    }
                }
                if (sp7B != 0) {
                    var_s2->unk32D = 1U;
                }
                if (var_s2->unk32D != 0) {
                    effectFreeAndUnlink(var_s2);
                } else {
                    temp_v1 = D_80750AB4;
                    var_s0_2 = 1;
                    var_s1_2 = 0x2F0;
                    phi_v1 = (s32) temp_v1;
                    phi_v1_2 = (s32) temp_v1;
                    if ((s32) temp_v1 >= 2) {
                        do {
                            if (*(D_807FC924 + var_s1_2) != 0) {
                                temp_t2 = D_807444FC << 6;
                                memcpy(var_s2 + (var_s0_2 << 7) + temp_t2 + 0x128, var_s2 + temp_t2 + 0x128, 0x40);
                                phi_v1 = (s32) D_80750AB4;
                            }
                            var_s0_2 += 1;
                            var_s1_2 += 0x2F0;
                        } while (var_s0_2 < phi_v1);
                    }
                    if (var_s2->unk32C != 3) {
                        var_s0_3 = 0;
                        if ((s32) temp_v1 > 0) {
                            var_s1_3 = 0;
                            do {
                                temp_v0_6 = D_807FC924 + var_s1_3;
                                if (temp_v0_6->unk0 != 0) {
                                    func_80715B30(var_s2 + (var_s0_3 << 7) + (D_807444FC << 6) + 0x128, var_s2->unk32C, var_s2->unk360, var_s2->unk364, temp_v0_6->unk21C, temp_v0_6->unk220, temp_v0_6->unk224, var_s2->unk340, var_s2->unk344, var_s2->unk348, (s32) var_s2->unk36F);
                                    phi_v1_2 = (s32) D_80750AB4;
                                }
                                var_s0_3 += 1;
                                var_s1_3 += 0x2F0;
                            } while (var_s0_3 < phi_v1_2);
                        }
                        var_s2->unk32C = 3U;
                    }
                    if (var_s2->unk36F == 0) {
                        temp_v0_7 = var_s2->unk38C;
                        var_s0_4 = 1;
                        if (temp_v0_7 & 4) {
                            var_s0_4 = 4;
                            if (!(temp_v0_7 & 8)) {
                                var_s2->unk38A = func_806531B8(var_s2->unk340, var_s2->unk344, 0, 5, var_s2->unk348, 0);
                            }
                        }
                        func_806303C4(0, 5, var_s2, var_s2->unk340, var_s2->unk344, var_s2->unk348, (s32) var_s2->unk34C, 0, 1, -1, var_s0_4);
                    } else {
                        func_806303C4(0, 5, var_s2, var_s2->unk340, var_s2->unk344, var_s2->unk348, 0, 0, 1, -1, 3);
                    }
                    temp_v0_8 = var_s2->unk330;
                    func_80715A3C(temp_v0_8->unk20, temp_v0_8->unk15, temp_v0_8->unk1C, var_s2->unk380, (s32) var_s2->unk34E, var_s2 + 0x370);
                    if ((temp_s7 == 0) || (var_s2->unk38C & 1)) {
                        temp_t6 = var_s2->unk351 + 1;
                        var_s2->unk351 = temp_t6;
                        if (var_s2->unk350 == (temp_t6 & 0xFF)) {
                            var_s2->unk351 = 0U;
                            var_s2->unk34E = (s16) (var_s2->unk34E + 1);
                        }
                    }
                }
                var_s2->unk38C = (u16) (var_s2->unk38C | 8);
            } else if ((temp_s7 == 0) || (var_s2->unk38C & 1)) {
                var_s2->unk368 = (s16) (temp_v0 - 1);
            }
            var_s2 = var_s2->unk39C;
        } while (var_s2 != NULL);
    }
    var_s1_4 = D_807FDB00;
    if (var_s1_4 != NULL) {
        do {
            temp_v0_9 = var_s1_4->unk18;
            if (((u32) (D_8076A064 - temp_v0_9) < 0xBU) && (temp_v0_9 != -1)) {
                var_s0_5 = 0;
                var_s2_2 = 0;
                var_v1 = var_s1_4->unk16 * var_s1_4->unk8 * var_s1_4->unk9;
                if (var_v1 > 0) {
                    do {
                        temp_v0_10 = var_s1_4->unk1C + var_s2_2;
                        if ((temp_v0_10->unk4 != -1) && ((D_8076A064 - var_s1_4->unk18) == 0xA)) {
                            assetFreeBuffer(temp_v0_10->unk0, 0x319, 0x1F);
                            (var_s1_4->unk1C + var_s2_2)->unk4 = -1;
                            var_v1 = var_s1_4->unk16 * var_s1_4->unk8 * var_s1_4->unk9;
                        }
                        var_s0_5 += 1;
                        var_s2_2 += 8;
                    } while (var_s0_5 < var_v1);
                }
            }
            var_s1_4 = var_s1_4->unk24;
        } while (var_s1_4 != NULL);
    }
}

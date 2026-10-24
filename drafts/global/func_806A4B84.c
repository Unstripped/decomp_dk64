// func_806A4B84 (src/global/A8400.c): stage 4/5: double math, 0x96*0.5 trunc and loop match; if/else min form needed. Remaining: arg1 wants s7 (mine s5) and the 0.5 double pair f16/f17 (mine f22/f23); 3 instructions short.
typedef struct M7Node2 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x94];
    /* 0xA0 */ struct M7Node2 *unkA0;
} M7Node2;

typedef struct M7State {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13[0xA];
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 pad1E[0x37];
    /* 0x55 */ u8 unk55;
} M7State;

typedef struct M7Holder {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[7];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ M7Node2 *unkC;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 unk14;
} M7Holder;

typedef struct M7Player {
    /* 0x000 */ u8 pad0[0x154];
    /* 0x154 */ u8 unk154;
} M7Player;

void func_806A4B84(f32 arg0, M7Player *arg1, M7State *arg2, M7Holder *arg3, u8 arg4, u8 *arg5) {
    f32 var_fs0;
    s32 var_a0;
    s32 var_s3;
    s16 temp16;
    u8 var_a0_2;
    u8 temp;
    M7Node2 *node;

    node = arg3->unkC;
    var_s3 = 0;
    var_fs0 = ((f64) 136.8f - arg3->unk14) * 0.5;
    while (node != NULL && *arg5 == 0) {
        if (arg4 != 0 && var_s3 == arg2->unk11) {
            if (!(arg2->unk55 & 4)) {
                *arg5 = 1;
            }
            if (arg1->unk154 == 1) {
                if (var_s3 == 0 && node->unk2 == 0) {
                    func_806A3700(arg2->unk4, arg3->unk8);
                }
                temp = node->unk2;
                if (temp != 0xFF) {
                    var_a0 = 0x96;
                    if (arg2->unk55 & 2) {
                        var_a0 = (s32) (var_a0 * 0.5);
                    }
                    if (!(arg2->unk55 & 4) && (var_a0 < (0xFF - temp))) {
                        node->unk2 = temp + var_a0;
                    } else {
                        node->unk2 = 0xFF;
                        if (node->unkA0 != NULL) {
                            arg2->unk11++;
                        } else {
                            arg2->unk11 = 0;
                            arg2->unk10++;
                            *arg5 = 1;
                            if (arg3->unk10 != 0) {
                                arg1->unk154 = 3;
                                arg2->unk12 = arg3->unk10;
                            }
                        }
                    }
                }
            }
        }
        if (arg2->unk1D < node->unk2) {
            var_a0_2 = arg2->unk1D;
        } else {
            var_a0_2 = node->unk2;
        }
        node->unk4 = var_fs0;
        node->unk8 = arg0;
        node->unk3 = var_a0_2;
        if (arg3->unk0 & 2) {
            func_806A495C((M7Sprite *) node, (M7Vector *) arg3, (M7Vector *) arg2);
        }
        temp16 = node->unk0;
        node = node->unkA0;
        var_s3++;
        var_fs0 += (f32) temp16;
    }
}

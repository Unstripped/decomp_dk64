// func_806672B8 (src/global/6AD90.c): stage 6: only final-test load: target 'lbu t4,159(sp)' (test) + separate 'lbu v0,159(sp)' (return), ours lb/lbu with s8 sp9F. u8 sp9F gets enregistered (extra candidate coloured v0, constant 1 hoisted to s8, 'lbu v1;move v0,v1'). Tried (u8) casts on test/return in all combos, u8/s8/u32 return type, volatile u8 (allocation shifts), u8 sp9C[4] array, struct{u8} (frame shrinks), address-taken (&sp9F) (allocation shifts 90 rows): none.
typedef struct Col6A2SubNode {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 pad4E[0x60 - 0x4E];
    /* 0x60 */ u8 unk60;
} Col6A2SubNode;
typedef struct Col6A2Node {
    /* 0x00 */ Col6A2SubNode *unk0;
    /* 0x04 */ u8 pad4[0x2C - 0x04];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[0x4A - 0x2E];
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B[0x50 - 0x4B];
    /* 0x50 */ struct Col6A2Node *next;
} Col6A2Node;

extern Col6A2Node *D_807F93C0;
u8 effectGetTableFlag(Col6A2Node *);
f32 func_806608FC(Col6A2Node *, s32, s32, u8);
s32 func_80668C30(s16 *, f32, f32);
f32 func_8066785C(s16 *, f32, f32);
s32 mathCheckCloserFloatThreshold(f32, f32, f32, u8);

s32 func_806672B8(f32 arg0, f32 arg1, f32 *arg2, s32 arg3) {
    f32 temp_fs1;
    u8 temp_s0;
    f32 pad[2]; // pad: reproduces frame 0xF8 (unused)
    f32 x[4];
    f32 y[4];
    f32 z[4];
    s16 spA0[12]; // 12 not 9: slot size so arrays start at 0xB8
    s8 sp9F; // FAKE: s8 (not u8) keeps sp9F in memory like the original (final lbu then only differs: lb)
    f32 var_fs5;
    Col6A2Node *var_s3;
    f32 var_fs0;
    f32 sp8C;
    s32 cell_x;
    s32 cell_z;

    sp9F = 0;
    var_fs5 = 999999.0f;
    var_s3 = D_807F93C0;
    sp8C = (f32)((f64)*arg2 + 4.0);
    if (var_s3 != NULL) {
        do {
            if (var_s3->unk0->unk46 <= arg0 && var_s3->unk0->unk48 <= arg1 && arg0 <= var_s3->unk0->unk4A && arg1 <= var_s3->unk0->unk4C) {
                var_fs0 = arg0 * 6.0f;
                temp_fs1 = arg1 * 6.0f;
                temp_s0 = effectGetTableFlag(var_s3);
                cell_x = (arg0 - var_s3->unk0->unk46) / (f32)var_s3->unk2C;
                cell_z = (arg1 - var_s3->unk0->unk48) / (f32)var_s3->unk2C;

                x[0] = var_s3->unk2C * cell_x + var_s3->unk0->unk46;
                z[0] = var_s3->unk2C * cell_z + var_s3->unk0->unk48;
                y[0] = func_806608FC(var_s3, x[0], z[0], temp_s0);

                x[1] = (cell_x + 1) * var_s3->unk2C + var_s3->unk0->unk46;
                z[1] = z[0];
                y[1] = func_806608FC(var_s3, x[1], z[1], temp_s0);
                x[2] = x[0];
                z[2] = (cell_z + 1) * var_s3->unk2C + var_s3->unk0->unk48;
                y[2] = func_806608FC(var_s3, x[2], z[2], temp_s0);

                x[3] = x[1];
                z[3] = z[2];
                y[3] = func_806608FC(var_s3, x[3], z[3], temp_s0);

                spA0[0] = x[0] * 6.0f;
                spA0[3] = y[0] * 6.0f;
                spA0[6] = z[0] * 6.0f;

                spA0[1] = x[1] * 6.0f;
                spA0[4] = y[1] * 6.0f;
                spA0[7] = z[1] * 6.0f;

                spA0[2] = x[3] * 6.0f;
                spA0[5] = y[3] * 6.0f;
                spA0[8] = z[3] * 6.0f;

                if (func_80668C30(spA0, var_fs0, temp_fs1) != 0) {
                    var_fs0 = func_8066785C(spA0, var_fs0, temp_fs1) / 6.0f;
                } else {
                    spA0[1] = x[2] * 6.0f;
                    spA0[4] = y[2] * 6.0f;
                    spA0[7] = z[2] * 6.0f;
                    var_fs0 = func_8066785C(spA0, var_fs0, temp_fs1) / 6.0f;
                }

                switch (var_s3->unk0->unk60) {
                case 0:
                case 2:
                case 3:
                    sp9F = 1;
                    if (var_s3->unk0->unk60 == 2 || var_s3->unk0->unk60 == 3) {
                        if ((var_fs0 < *arg2 ? *arg2 - var_fs0 : -(*arg2 - var_fs0)) < 6.0f) {
                            switch (var_s3->unk0->unk60) {
                            case 2:
                                D_807F94AF = 2;
                                break;
                            case 3:
                                D_807F94AF = 1;
                                break;
                            }
                        }
                    }
                    if (mathCheckCloserFloatThreshold(var_fs5, var_fs0, sp8C, 0) != 0) {
                        var_fs5 = var_fs0;
                    }
                    break;
                case 1:
                    if (arg3 != 0) {
                        if (((Actor *)arg3)->unk80 < var_fs0) {
                            ((Actor *)arg3)->unk6A |= 4;
                            *(s8 *)&((Actor *)arg3)->unkB0[0] = -1; // FAKE: s8 view makes the store constant -1 (u8 field folds to 0xFF)
                            if (var_s3->unk4A & 1) {
                                D_807F94B0 = 1;
                            }
                        }
                        ((Actor *)arg3)->unkAC = var_fs0;
                        ((Actor *)arg3)->unk6A |= 2;
                    }
                    D_807F9484 = 1;
                    D_807F9488 = var_fs0;
                    break;
                }
            }
            var_s3 = var_s3->next;
        } while (var_s3 != NULL);
    }
    if (sp9F != 0) {
        *arg2 = var_fs5;
    }
    return (u8)sp9F;
}

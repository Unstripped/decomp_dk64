// func_80690C60 (src/global/936B0.c): actor targeting/aiming logic with path following
s16 func_80665DE0(f32, f32, f32, f32);
s32 func_80690F30(u16, void **, void *, s32, s32, s32, f32 *, f32 *, f32 *);
s16 mathAngleDistance(s16, s16);
void func_80714950(s32);
void func_8071498C(void *);
void func_80714CC0(s32, f32, f32, f32, f32);
void func_800268C0(f32, s32);
extern Actor *D_807FBB40;
extern s32 D_807FBB64;
extern void func_8071D260(void);

void func_80690C60(u16 arg0, Actor *arg1, s32 arg2, u8 arg3) {
    Actor *sp78;
    s16 sp76;
    s16 sp70;
    s16 sp6E;
    s16 sp6C;
    f32 sp60;
    void *sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fv0;
    f64 var_ft2;
    s16 temp_t0;
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_lo;
    u8 temp_t4;

    sp50 = arg1->unk174;
    if (!((f64)arg1->unkB8 < 0.1)) {
        if ((arg2 != 0) && (*(u8 *)((u8 *)((Actor *)arg1->unk11C)->unk174 + 0xF3) == 3)) {
            func_8071498C(func_8071D260);
            func_80714950(0x32);
            func_80714CC0(arg2, *(f32 *)((u8 *)sp50 + 0x14), D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
        if (func_80690F30(arg0, (void **)&sp78, arg1, 0, (s32)arg3, arg3 == 0, &sp4C, &sp48, &sp44) != 0) {
            temp_v0 = func_80665DE0(sp4C, sp44, arg1->unk7C, arg1->unk84);
            sp76 = temp_v0;
            temp_lo = mathAngleDistance(temp_v0, arg1->unkEE) / 10;
            temp_v1 = arg1->unkEE;
            temp_t0 = (temp_v1 + temp_lo) & 0xFFF;
            sp6E = (temp_v1 - temp_lo) & 0xFFF;
            sp70 = temp_t0;
            sp6C = mathAngleDistance(temp_t0, sp76);
            if (sp6C < mathAngleDistance(sp6E, sp76)) {
                arg1->unkEE = sp70;
            } else {
                arg1->unkEE = sp6E;
            }
            if (arg3 == 0) {
                temp_fv0 = sp4C - arg1->unk7C;
                temp_fv1 = sp44 - arg1->unk84;
                temp_fv0_2 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
                if (temp_fv0_2 < 100.0f) {
                    *(Actor **)((u8 *)sp50 + 0x1C) = sp78;
                    if ((sp78 != NULL) && (D_807FBB64 & 0x04000000)) {
                        sp60 = temp_fv0_2;
                        func_800268C0(temp_fv0_2, 0x80);
                    }
                }
                if (sp78 != NULL) {
                    temp_t4 = sp78->unk15E;
                    var_ft2 = (f64)temp_t4;
                    if ((s32)temp_t4 < 0) {
                        var_ft2 += 4294967296.0;
                    }
                    var_fv0 = (f32)(var_ft2 * 0.5);
                } else {
                    var_fv0 = 0.0f;
                }
                *(f32 *)((u8 *)arg1 + 0xC0) = (f32)((((sp48 + var_fv0) - arg1->unk80) / (temp_fv0_2 / (arg1->unkB8 * 0.025f))) / 0.025f);
            }
        } else if (*(void **)((u8 *)sp50 + 0x1C) != NULL) {
            if (D_807FBB64 & 0x04000000) {
                func_800268C0(6e-45f, 0);
            }
            *(void **)((u8 *)sp50 + 0x1C) = NULL;
        }
    }
}

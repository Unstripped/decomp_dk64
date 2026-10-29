// func_8067BF84 (src/global/80150.c): from .scratch/R2G/func_8067BF84_best.c
extern void *D_807FBB40;
extern u8 D_807FBBA8;
extern s32 D_807FC924;
extern u8 D_807FC928;
extern u8 D_8071FE08;
void func_80688370(void *, s32, f32);
void func_806883C8(void *, s32, s32);
void func_8068839C(void *, s32, s32);
void func_8068842C(void *, s32, s32);
void func_806651FC(void *);
void actorUpdateFloorContactAndTilt(void *, f32);
s32 func_80672BD4(void *);
void func_80689114(s32, f32, f32, f32, s32, f32, void *);
void func_80608528(void *, s32, s32, s32, s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void actorUpdateModelMatrix(void *, s32);

u8 func_8067BF84(s16 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 sp47;
    u8 sp3B;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fs0;
    s32 temp_t8;
    u8 var_a0;
    BehAActor *temp_s0;
    void *temp_v0;
    void *temp_v1;

    sp47 = 0;
    var_fs0 = 99999.0f;
    if (D_807FBB40->unk60 & 0x10) {
        func_80688370(D_807FBB40, 0, 0.5f);
        func_806883C8(D_807FBB40, 0, 0);
        func_8068839C(D_807FBB40, 0, 0);
        func_8068842C(D_807FBB40, 0, -1);
        if ((D_807FBBA8 != 0) || (*arg1 != 0) || (*arg3 != 0)) {
            *arg3 = 0;
            sp47 = 1;
        }
        if (sp47 != 0) {
            var_a0 = 0;
            if ((s32) D_807FC928 > 0) {
                do {
                    temp_v1 = (void *)(D_807FC924 + (var_a0 * 0x2F0));
                    if (*(u8 *)temp_v1 != 0) {
                        temp_v0 = *(void **)((u8 *)temp_v1 + 4);
                        temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0x84) - D_807FBB40->unk84;
                        sp3B = var_a0;
                        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x7C) - D_807FBB40->unk7C;
                        temp_fv0_2 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
                        if (temp_fv0_2 < var_fs0) {
                            var_fs0 = temp_fv0_2;
                        }
                    }
                    temp_t8 = (var_a0 + 1) & 0xFF;
                    var_a0 = (u8) temp_t8;
                } while (temp_t8 < (s32) D_807FC928);
            }
            if ((f64) var_fs0 > 12.0) {
                *arg1 = 0;
            } else {
                *arg1 = 1;
                sp47 = 0;
            }
        }
    } else {
        sp47 = 1;
        *arg1 = 0;
        D_807FBB40->unk80 = -10.0f;
        func_806651FC(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        if (func_80672BD4(D_807FBB40) != 0) {
            *arg2 = 1;
        } else {
            *arg2 = 0;
        }
    }
    if (sp47 != 0) {
        func_80689114(arg0, D_807FBB40->unk7C, (f32) ((f64) D_807FBB40->unk80 + 8.3), D_807FBB40->unk84, 0, 1.0f, D_807FBB40);
        if (D_807FBB40->unk60 & 0x10) {
            func_80608528(D_807FBB40, 0x31, 0xFF, 0x7F, 1);
            func_807149B8(0);
            func_807149FC(1);
            func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
        }
    }
    temp_s0 = D_807FBB40;
    if (*arg2 != 0) {
        temp_s0->unk80 = -10.0f;
        func_806651FC(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
    }
    actorUpdateModelMatrix(temp_s0, 0);
    return sp47;
}

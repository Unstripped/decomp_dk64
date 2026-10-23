// func_80666D88 (src/global/699B0.c): starter m2c, leaf collision check against player/actor
extern ? D_80752F7C;
extern ? D_80752F98;
extern ? D_80752FB4;
extern ? D_80752FD0;
extern ? D_80752FEC;
extern ? D_80753008;
extern f32 D_807F9460;
extern s8 D_807F9464;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern s16 D_807FD584;

void func_80666D88(f32 arg0, f32 arg1, s32 arg2, void *arg3, u8 arg4) {
    ? *var_v0;
    ? *var_v1;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_t3;
    s32 temp_t6;
    u8 temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (arg0 < arg1) {
        if ((arg3 != NULL) && (arg3->unk5C & 1)) {
            temp_v0 = (D_807FC924 + (D_807FC929 * 0x2F0))->unk2C0;
            var_v1 = &D_80752FB4;
            if (temp_v0 != 0) {
                if (temp_v0 != 2) {
                    var_v1 = &D_80752F7C;
                    var_v0 = &D_80752F98;
                } else {
                    var_v0 = &D_80753008;
                    var_v1 = &D_80752FEC;
                }
            } else {
                var_v0 = &D_80752FD0;
            }
            temp_t3 = D_807FD584 * 4;
            var_fv0 = *(var_v0 + temp_t3);
            var_fv1 = *(var_v1 + temp_t3);
        } else {
            var_fv0 = 10.0f;
            var_fv1 = 20.0f;
        }
        if (arg4 != 0) {
            var_fv0 /= 2.0f;
        }
        if (temp_t6 == 1) {
            var_ft4 = var_fv0 * 6.0f;
        } else {
            var_ft4 = var_fv0;
        }
        temp_fv0 = arg1 - arg0;
        if (var_ft4 < temp_fv0) {
            if (temp_t6 == 1) {
                var_fa0 = var_fv1 * 6.0f;
            } else {
                var_fa0 = var_fv1;
            }
            if (temp_fv0 < var_fa0) {
                D_807F9464 = 1;
                D_807F9460 = arg1 - var_fa0;
                if (temp_t6 != 0) {
                    D_807F9460 /= 6.0f;
                }
            }
        }
    }
}

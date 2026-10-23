// func_80666D88 (src/global/6AD90.c): 8 diffs in v0/v1 table pointers and branch arrangement
extern f32 D_80752F7C[];
extern f32 D_80752F98[];
extern f32 D_80752FB4[];
extern f32 D_80752FD0[];
extern f32 D_80752FEC[];
extern f32 D_80753008[];

extern f32 D_807F9460;
extern s8 D_807F9464;

void func_80666D88(f32 arg0, f32 arg1, u8 arg2, Actor *arg3, u8 arg4) {
    f32 *var_v1;
    f32 *var_v0;
    f32 var_fa0;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    f32 diff;
    s32 temp;
    s32 flag;
    u8 temp_v0;

    flag = 1;
    if (arg0 < arg1) {
        if ((arg3 != NULL) && (arg3->unk5C & 1)) {
            temp_v0 = D_807FC924[D_807FC929].unk2C0;
            if (temp_v0 != 0) {
                if (temp_v0 != 2) {
                    var_v1 = D_80752F7C;
                    var_v0 = D_80752F98;
                } else {
                    var_v0 = D_80753008;
                    var_v1 = D_80752FEC;
                }
            } else {
                var_v1 = D_80752FB4;
                var_v0 = D_80752FD0;
            }
            var_fv0 = var_v0[D_807FD584];
            var_fv1 = var_v1[D_807FD584];
        } else {
            var_fv0 = 10.0f;
            var_fv1 = 20.0f;
        }
        if (arg4 != 0) {
            var_fv0 /= (f32)2;
        }
        temp = arg2;
        if (arg2 == 1) {
            var_ft4 = var_fv0 * 6.0f;
        } else {
            var_ft4 = var_fv0;
        }
        diff = arg1 - arg0;
        if (var_ft4 < diff) {
            if (temp == 1) {
                var_fa0 = var_fv1 * 6.0f;
            } else {
                var_fa0 = var_fv1;
            }
            if (diff < var_fa0) {
                D_807F9464 = flag;
                D_807F9460 = arg1 - var_fa0;
                if (arg2 != 0) {
                    D_807F9460 /= 6.0f;
                }
            }
        }
    }
}

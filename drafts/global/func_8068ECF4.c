// func_8068ECF4 (src/global/936B0.c): unattempted starter draft from m2c
f32 func_80611BB4(f32, f32);
void func_80671C0C(void *, s32, f32 *, f32 *, f32 *);
void func_807149C8(f32, f32, s32, s32, s32, s32);
void func_80714C08(void *, f32, void *, s32, s32);
extern u8 D_80720054;
extern Actor *D_807FBB40;

typedef struct M93A_C924 {
    u8 pad0[0x210];
    f32 unk210;
    f32 pad214;
    f32 unk218;
} M93A_C924;
extern M93A_C924 *D_807FC924;

void func_8068ECF4(s32 arg0, u8 arg1) {
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp30;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_ft1;
    f32 var_fv0;
    f32 var_fv1;
    s16 var_v0;
    s32 temp_t4;
    void *temp_v0;

    func_80671C0C(D_807FBB40, arg0, &sp48, &sp44, &sp40);
    temp_fa0 = (f32) D_807FBB40->unkE6;
    temp_fv1 = (f32) ((s32) ((func_80611BB4(D_807FC924->unk218 - sp40, sp48 - D_807FC924->unk210) * 651.8986f) + 1024.0f) & 0xFFF);
    if (temp_fa0 < temp_fv1) {
        var_v0 = (s16) (s32) (temp_fv1 - temp_fa0);
    } else {
        var_v0 = (s16) (s32) (temp_fa0 - temp_fv1);
    }
    if (var_v0 >= 0x801) {
        var_v0 = 0x1000 - var_v0;
    }
    if (var_v0 < 0x384) {
        temp_fv0 = (1024.0f - (f32) var_v0) * 0.0014285714f;
        if (temp_fv0 < 1.0f) {
            var_fv1 = temp_fv0;
        } else {
            var_fv1 = 1.0f;
        }
        var_ft1 = (f32) arg1;
        if ((s32) arg1 < 0) {
            var_ft1 += 4294967296.0f;
        }
        temp_t4 = (u32) (var_fv1 * var_ft1) & 0xFF;
        if (temp_t4 != 0) {
            temp_v0 = D_807FBB40->unk4;
            var_fv0 = 3.3f;
            if (temp_v0 != NULL) {
                var_fv0 = 3.3f * ((ActorSub4 *)temp_v0)->unk38;
            }
            sp30 = var_fv0;
            func_807149C8(1.0f, 256.0f, 0xFF, 0xFF, 0xFF, temp_t4);
            func_80714C08(&D_80720054, var_fv0, D_807FBB40, arg0, 2);
        }
    }
}

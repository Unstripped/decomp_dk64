// func_80683AD8 (src/global/80150.c): from .scratch/R2H/func_80683AD8_best.c
typedef struct R2H_TagBarrelState {
    u8 pad0[4];
    u16 unk4;
    s8 unk6;
    s8 unk7;
    Actor *unk8[5];
    u8 pad1C[4];
    s32 unk20;
} R2H_TagBarrelState;

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern s16 D_80744490;
extern s16 D_80744494;
extern u32 D_8076A064;

Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, s32);
s32 func_806FD894(s32);

Gfx *func_80683AD8(Gfx *arg0, Actor *arg1) {
    f32 spF8;
    f32 spF0;
    s32 sp6C;
    s32 sp44;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_ft1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_ft3;
    s32 temp_v0;
    u16 temp_t9;
    R2H_TagBarrelState *temp_s1;
    Gfx *dlist;

    temp_s1 = (R2H_TagBarrelState *)arg1->unk174;
    dlist = arg0;
    temp_fa0 = (f32) ((f64) (D_80744494 - 0x1E) * 4.0);
    if (arg1->unk154 != 1) {
        return arg0;
    }
    dlist[0].words.w0 = 0xDE000000;
    dlist[0].words.w1 = (u32)&D_1000118;
    dlist[1].words.w0 = 0xFCFFFFFF;
    dlist[1].words.w1 = 0xFFFCF279;
    dlist[2].words.w0 = 0xDA380007;
    dlist[2].words.w1 = (u32)&D_20000C0;
    dlist[3].words.w0 = 0xDA380003;
    dlist[3].words.w1 = (u32)&D_2000180;
    dlist += 4;
    temp_ft3 = (s32) temp_fa0;
    sp44 = (s16) temp_ft3;
    spF0 = temp_fa0;
    temp_t9 = temp_s1->unk4;
    dlist = func_8068C5A8(dlist, (((u32)(D_8076A064 >> 1) % 12) + 0x83) & 0xFFFF, 0, 2, 0x20, 0x10, 0xA0, (s16)temp_ft3, 5.0f, 5.0f, 0, 0.0f);
    dlist = func_8068C5A8(dlist, (((u32)(D_8076A064 >> 1) % 12) + 0x83) & 0xFFFF, 0, 2, 0x20, 0x10, (s32)((f64)(D_80744490 - 0x28) * 4.0), sp44, 5.0f, 5.0f, 0xB4, 0.0f);
    var_ft1 = (f32) temp_t9;
    if ((s32) temp_t9 < 0) {
        var_ft1 += 4294967296.0f;
    }
    spF8 = var_ft1 * 0.05f;
    sp6C = func_80683A80((ActorGroup5 *)temp_s1, temp_s1->unk6);
    spF0 -= (f32) func_806FD894(1) * 1.2f;
    dlist[0].words.w0 = 0xFCFF97FF;
    dlist[0].words.w1 = 0xFF2CFE7F;
    dlist++;
    if (sp6C != 0) {
        temp_fv0 = 1.0f - spF8;
        temp_fv1 = temp_fv0 * 0.5f;
        var_fa0 = temp_fv1;
        if (temp_s1->unk20 < 0) {
            var_fa0 = 1.0f - temp_fv1;
        }
        temp_fv1_2 = 2.0f * temp_fv0;
        temp_fa0_2 = var_fa0 * ((f32) D_80744490 * 4.0f);
        if (temp_fv1_2 < 1.0f) {
            var_fv0 = 0.0f;
        } else {
            temp_fv0_2 = temp_fv1_2 - 1.0f;
            if (temp_fv0_2 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = temp_fv0_2;
            }
            var_fv0 = var_fv1;
        }
        dlist[0].words.w0 = 0xFA000000;
        dlist[0].words.w1 = (s32) (((u32) (var_fv0 * 255.0f) & 0xFF) | ~0xFF);
        dlist++;
        dlist = hudDrawScaledText(dlist, (s16) (s32) temp_fa0_2, (s16) (s32) spF0, 0.15f, sp6C);
    }
    if (temp_s1->unk4 != 0) {
        temp_v0 = func_80683A80((ActorGroup5 *)temp_s1, temp_s1->unk7);
        if (temp_v0 != 0) {
            temp_fv0_3 = 0.5f * spF8;
            var_fa0_2 = temp_fv0_3;
            if (temp_s1->unk20 > 0) {
                var_fa0_2 = 1.0f - temp_fv0_3;
            }
            temp_fv0_4 = 2.0f * spF8;
            temp_fa0_3 = var_fa0_2 * ((f32) D_80744490 * 4.0f);
            if (temp_fv0_4 < 1.0f) {
                var_fv0_2 = 0.0f;
            } else {
                temp_fa1 = temp_fv0_4 - 1.0f;
                if (temp_fa1 > 1.0f) {
                    var_fv1_2 = 1.0f;
                } else {
                    var_fv1_2 = temp_fa1;
                }
                var_fv0_2 = var_fv1_2;
            }
            dlist[0].words.w0 = 0xFA000000;
            dlist[0].words.w1 = (s32) (((u32) (var_fv0_2 * 255.0f) & 0xFF) | ~0xFF);
            dlist++;
            dlist = hudDrawScaledText(dlist, (s16) (s32) temp_fa0_3, (s16) (s32) spF0, 0.15f, temp_v0);
        }
    }
    return dlist;
}

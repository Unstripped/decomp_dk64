// func_8002C2E8 (src/race/7BD0.c): stage 5: text size equal, frame/locals ok (5 survivors before sp70), int-literal '2 * fv0' gives the mul.s; reuse fs0/fs2 for cvt.s.d results avoids dup cvts. remaining: fs2($f24)/4.0f($f26) swapped, FP temp ring phase ($f4 vs $f8 at second jal), commutative operand order of add.s fs1+(f32)var
u32 func_806FD894(s32);

Gfx *func_8002C2E8(Gfx *arg0, RaceUnknown174 *arg1) {
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv0;
    Struct806C7C94 *temp_s0;
    f32 sp70;
    f32 temp_t1;
    f32 temp_t2;
    s16 temp_s3;
    s32 var_s0;
    s32 var_s1;
    void *temp_v0_2;

    temp_s0 = arg1->unk48;
    temp_fv0 = (f32)func_806FD894(1) * 0.5f;
    sp70 = temp_fv0;
    temp_fs0 = (f32)(temp_s0->unk4 + 8);
    temp_fs2 = (f32)(temp_s0->unkA - 0x10);
    temp_fs2 -= 2 * temp_fv0;
    temp_v0_2 = func_8070E750(0x26, 0xA, 1);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFFF);
    arg0 = func_806FC530(arg0, 1, (s16)(s32)(2.0f * (temp_fs0 * 4.0f)), (s16)(s32)(2.0f * (temp_fs2 * 4.0f)), temp_v0_2, 4);
    WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
    WRITE_GFX(arg0++, 0xDA380005, (u32)((u8 *)arg1 + (D_807444FC << 6) + 0x50));
    temp_fs0 = temp_fs0 + ((f32)func_806FBD5C(1, temp_v0_2) * 0.5f);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFF00FF);
    temp_fs0 = (f32)((f64)temp_fs0 + 8.0);
    temp_fs1 = temp_fs0 + temp_fs0;
    temp_fs2 = (f32)((f64)temp_fs2 + (0.4 * (f64)sp70));
    temp_s3 = (s16)(s32)((temp_fs2 + temp_fs2) * 4.0f);
    var_s0 = 0;
    do {
        arg0 = func_8068C5A8(arg0, 0x4B, 3, 1, 0x40, 0x40, (s32)(((f32)var_s0 + temp_fs1) * 4.0f), temp_s3, 1.5f, 1.5f, 0, 0.0f);
        var_s0 += 0x18;
    } while (var_s0 < 0x78);
    WRITE_GFX(arg0++, 0xFA000000, 0xFF0000FF);
    var_s1 = 0;
    if ((5 - *((u8 *)arg1 + 0x44)) > 0) {
        var_s0 = 0;
        do {
            arg0 = func_8068C5A8(arg0, 0x45, 3, 1, 0x40, 0x40, (s32)(((f32)var_s0 + temp_fs1) * 4.0f), temp_s3, 1.5f, 1.5f, 0, 0.0f);
            var_s1 += 1;
            var_s0 += 0x18;
        } while (var_s1 < (5 - *((u8 *)arg1 + 0x44)));
    }
    WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
    return arg0;
}

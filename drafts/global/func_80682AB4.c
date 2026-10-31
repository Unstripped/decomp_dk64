// func_80682AB4 (src/global/80150.c): LgC71b stage 4 draft kept (17 diff lines / 12 text). W2Ring: cast-first chain without dir (matches lines 1-88 incl mfc1 t0/t1/t2, lb t4) leaves loop-start ring 5 slots off (mfc1 t2 vs t7) = 70 lines; tried 729 wrapper combos around both chains, 320 spellings of the loop-top expression, var_s1 types, loop forms (for/while/do), unk8[i] indexed IV (gives right s3 IV shape but s3/s4 swapped), dead (s16) burners before the loop: none moves the ring. Moving 'var_s3 += 4' after the second call (target puts addiu s3 after jal 2) is correct (-2 lines). The dir-FAKE form keeps the loop ring right but mfc1 coalesces into s5.
typedef struct TagBarrelOrbitKong {
    u8 pad0[4];
    u16 unk4;
    s8 unk6;
    s8 unk7;
    Actor *unk8[5];
    Actor *unk1C;
    s8 unk20;
} TagBarrelOrbitKong;


void func_80682AB4(void *arg0) {
    TagBarrelOrbitKong *arg = (TagBarrelOrbitKong *)arg0;
    f32 sp70 = D_807FBB40->unk7C;
    f32 sp6C = D_807FBB40->unk80 - 10.0f;
    f32 sp68 = D_807FBB40->unk84;
    s32 var_s1;
    f32 temp_fs1;
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_s5;
    s16 temp_t0;
    u8 *var_s3;
    Actor *temp_s2;
    s32 dir;

    temp_fs1 = (f32)(u32)arg->unk4 / 20.0f;
    temp_s5 = D_807FBB40->unkE6;
    temp_s5 = (s16)((s32)(temp_s5 + (819.2 * arg->unk6)) & 0xFFF);
    dir = arg->unk20; // FAKE: local copy of unk20 steers register allocation
    temp_s5 = (s16)((s32)(temp_s5 - (819.2 * temp_fs1) * dir) & 0xFFF);
    var_s1 = 0;
    var_s3 = (u8 *)arg0;
    do {
        temp_s2 = *(Actor **)(var_s3 + 8);
        temp_t0 = (s16)((s32)(4096.0 - (var_s1 * 819.2)) + temp_s5) & 0xFFF;
        temp_s2->unk7C = (func_80612794(temp_t0) * 45.0f) + sp70;
        var_s3 += 4;
        temp_s2->unk84 = (func_80612790(temp_t0) * 45.0f) + sp68;
        temp_s2->unk80 = sp6C;
        if (var_s1 == arg->unk6) {
            var_fv0 = 1.0f - temp_fs1;
        } else if (var_s1 == arg->unk7) {
            var_fv0 = temp_fs1;
        } else {
            var_fv0 = 0;
        }
        var_fv0 = (f64)var_fv0 - 0.6;
        var_s1++;
        var_fv0 = (f64)var_fv0 * 2.5;
        if (var_fv0 < 0) {
            var_fv0 = 0.0f;
        } else {
            if (var_fv0 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = var_fv0;
            }
            var_fv0 = var_fv1;
        }
        temp_s2->unk15F = (u32)((12.0f * var_fv0) + 3.0f);
    } while (var_s1 != 5);
}

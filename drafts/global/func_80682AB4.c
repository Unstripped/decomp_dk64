// func_80682AB4 (src/global/80150.c): W5A stage 5, 3 diff lines (unchanged): chain2 andi/sll temps t3/t4 vs target t8/t9; everything else (loop ring mfc1 t7 etc.) matches. Raw 'cc -S' analysis: ugen ring slots are consumed by redundant sll/sra pairs that as1 later deletes; survivors take the regs of the LAST and/sll nodes, so any FAKE merged after chain 2 (5 raw nodes: sll,sra,and,sll,sra) lands the loop right but takes chain 2's survivors (t3/t4); target needs 5 raw ring nodes AFTER chain 2's final sra that do not feed s5 (loop trunc helper is t6, mfc1 t7). Tried this round: ~25k probes (hill-climb over chain forms/FAKE forms/loop kind/bound/types/ang temp/dead ifs/IV forms; 960 temp_s5 wrappers; while/for loop forms; arg->unk8[i] index forms; zero-valued terms) all stuck at 3. while/for loop form does not change ring.
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

    temp_fs1 = (f32)(u32)arg->unk4 / 20.0f;
    temp_s5 = D_807FBB40->unkE6;
    temp_s5 = (s16)(s32)(temp_s5 + (819.2 * arg->unk6)) & 0xFFF;
    temp_s5 = (s16)(s32)(temp_s5 - (819.2 * temp_fs1) * arg->unk20) & 0xFFF;
    temp_s5 = (s16)(s32)temp_s5 & 0xFFFF; // FAKE: redundant narrowing burns ugen ring temps (loop-start register ring)
    var_s1 = 0;
    var_s3 = (u8 *)arg0;
    do {
        temp_s2 = *(Actor **)(var_s3 + 8);
        temp_t0 = (s16)((s32)(4096.0 - (var_s1 * 819.2)) + temp_s5) & 0xFFF;
        temp_s2->unk7C = (func_80612794(temp_t0) * 45.0f) + sp70;
        temp_s2->unk84 = (func_80612790(temp_t0) * 45.0f) + sp68;
        var_s3 += 4;
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

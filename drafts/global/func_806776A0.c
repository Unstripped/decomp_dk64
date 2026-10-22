// func_806776A0 (src/global/7BBD0.c): from .scratch/Beh7BB2/func_806776A0_best.c
void func_806776A0(Actor *arg0, Actor *arg1, void *arg2, void *arg3, s8 arg4, s32 arg5, s32 arg6, u8 arg7) {
    Beh7BB_MtxF spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_v1;
    s32 var_a2;
    s32 var_s0;
    s32 var_v0;
    Beh7BB_ActorSub140 *temp_s5;
    Beh7BB_ActorSub140 *temp_s6;
    void *temp_v0;
    void *var_s0_2;
    Beh7BB_Node *var_s0_3;

    temp_s5 = (Beh7BB_ActorSub140 *)arg0->unk140;
    temp_s6 = (Beh7BB_ActorSub140 *)arg1->unk140;
    D_807FB603 = temp_s5->unkAC;
    D_807FB5FD = 1;
    D_807FB600 = 1;
    D_807FB547 = 0;
    func_80672E90(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8);
    func_80672C70(arg1->unk58);
    if (arg7 != 0) {
        var_v0 = func_80673708(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8, (u8 *)arg1 + 0xF4, (u8 *)arg1 + 0xF6);
    } else {
        func_80670F04((void *)(temp_s5->unkA4 + (temp_s6->unk58 * 0x58)));
        if (!(*(u32 *)&arg0->unk64 & 0x10)) {
            var_v0 = func_806738D0(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8);
        } else {
            var_v0 = func_80673708(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8, (u8 *)arg1 + 0xF4, (u8 *)arg1 + 0xF6);
        }
    }
    var_s0 = var_v0 & 0xFF;
    if ((arg7 != 0) && ((f64) *(&D_807FD614 + (func_8067B1E0(arg1) * 0x34)) > 30.0)) {
        var_s0 = 1;
    }
    if (var_s0 != 0) {
        func_8067760C((Beh7BB_Struct_760C *)temp_s5, spEC, arg4);
        guMtxXFMF(spEC, *(f32 *)arg2, *((f32 *)arg2 + 1), *((f32 *)arg2 + 2), &spE8, &spE4, &spE0);
        var_fv0 = spE8;
        var_s0_2 = arg3;
        var_s2 = &spD4;
        var_s3 = &spC8;
        var_s1 = &spBC;
        if (*(u32 *)&arg0->unk64 & 0x10) {
            var_fv1 = spE0;
        } else {
            do {
                guMtxXFMF(spEC, *(f32 *)var_s0_2, *((f32 *)var_s0_2 + 1), *((f32 *)var_s0_2 + 2), var_s2, var_s3, var_s1);
                var_s1 += 4;
                var_s0_2 = (u8 *)var_s0_2 + 0xC;
                var_s2 += 4;
                var_s3 += 4;
            } while (var_s1 != &spC8);
            temp_fv0 = spDC - spD4;
            temp_fv1 = spD0 - spC8;
            spB0 = temp_fv0;
            temp_fa1 = spC4 - spBC;
            spB4 = temp_fv1;
            temp_ft4 = spD8 - spD4;
            spB8 = temp_fa1;
            temp_ft5 = spCC - spC8;
            spA4 = temp_ft4;
            temp_ft3 = spC0 - spBC;
            spA8 = temp_ft5;
            spAC = temp_ft3;
            temp_ft0 = (temp_fv1 * temp_ft3) - (temp_ft5 * temp_fa1);
            sp98 = temp_ft0;
            temp_ft0_2 = (temp_fa1 * temp_ft4) - (temp_ft3 * temp_fv0);
            sp9C = temp_ft0_2;
            spA0 = (temp_fv0 * temp_ft5) - (temp_ft4 * temp_fv1);
            temp_fv0_2 = sqrtf((spA0 * spA0) + ((temp_ft0 * sp98) + (sp9C * temp_ft0_2)));
            sp8C = temp_ft0 / temp_fv0_2;
            sp90 = sp9C / temp_fv0_2;
            sp94 = spA0 / temp_fv0_2;
            if (arg1->unk5C & 1) {
                if (*(u8 *)(*(s32 *)&D_807FC924 + (D_807FC929 * 0x2F0) + 0x2C0) == 1) {
                    var_fv1_2 = (f32) *(&D_80753D50 + (D_807FD584 * 2));
                } else {
                    var_fv1_2 = (f32) *(&D_80753D60 + (D_807FD584 * 2));
                }
                temp_fv0_3 = var_fv1_2 / 8.0f;
                temp_v0 = (u8 *)arg1->unk174;
                temp_ft3_2 = sp8C * temp_fv0_3;
                sp70 = temp_ft3_2;
                sp74 = sp90 * temp_fv0_3;
                sp78 = sp94 * temp_fv0_3;
                *(f32 *)((u8 *)temp_v0 + 0xE0) = (f32) (spE8 - temp_ft3_2);
                *(f32 *)((u8 *)temp_v0 + 0xE4) = (f32) (spE0 - sp78);
            }
            temp_v1 = temp_s6->unk68;
            var_a2 = arg5;
            if (temp_v1 != 0) {
                var_a2 = temp_v1 + 5;
                D_807FB5D0 = var_a2;
                if (arg6 < var_a2) {
                    D_807FB5D0 = arg6;
                    goto block_24;
                }
            } else {
                D_807FB5D0 = var_a2;
                if (var_a2 < 0xF) {
                    var_a2 = 0xF;
                    D_807FB5D0 = 0xF;
                }
                if (arg6 < var_a2) {
                    D_807FB5D0 = arg6;
block_24:
                    var_a2 = arg6;
                }
            }
            temp_fv0_4 = (f32) var_a2 / 8.0f;
            temp_fa0 = sp8C * temp_fv0_4;
            temp_fa1_2 = sp94 * temp_fv0_4;
            sp8C = temp_fa0;
            temp_fv0_5 = spE8 - temp_fa0;
            sp90 *= temp_fv0_4;
            sp68 = temp_fv0_5;
            temp_fv1_2 = spE0 - temp_fa1_2;
            sp94 = temp_fa1_2;
            sp64 = temp_fv1_2;
            func_8067A99C(temp_fa0, temp_fa1_2, arg0, arg1, var_a2);
            var_fv0 = temp_fv0_5;
            var_fv1 = temp_fv1_2;
        }
        func_8067A69C(arg0, arg1, var_fv0, var_fv1, 1, 1);
        var_s0_3 = temp_s6->unk8C;
        while (var_s0_3 != NULL) {
            if (var_s0_3->unk26 != 0) {
                arg1->unkFC |= func_80673708(var_s0_3->unk10, var_s0_3->unk14, var_s0_3->unk18, var_s0_3->unk1C, temp_s5->unkA4, temp_s5->unkA8, (u8 *)arg1 + 0xF4, (u8 *)arg1 + 0xF6);
            }
            var_s0_3 = var_s0_3->unk28;
        }
    } else {
        var_s0_3 = temp_s6->unk8C;
        while (var_s0_3 != NULL) {
            if (var_s0_3->unk26 != 0) {
                arg1->unkFC |= func_80673708(var_s0_3->unk10, var_s0_3->unk14, var_s0_3->unk18, var_s0_3->unk1C, temp_s5->unkA4, temp_s5->unkA8, (u8 *)arg1 + 0xF4, (u8 *)arg1 + 0xF6);
            }
            var_s0_3 = var_s0_3->unk28;
        }
    }
    *(u8 *)((u8 *)arg1 + 0xFD) = D_807FB547;
}

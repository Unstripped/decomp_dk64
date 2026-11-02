// func_8066FE08 (src/global/70FD0.c): func_8066FE08 (src/global/70FD0.c): W4FpA unchanged park, still 6 rows (subu v0 vs a0 x2 = 4 rows; sin/cos spill slot 0x3C vs 0x44 = 2 rows). NEW tried: first-def theory (target subu a0 = var_a0/s32 temp_a0 first def): 40+ spellings of var_a0/temp_a0 (s16/s32 temp_a0, explicit (s16) casts, aliases sA, dead tests after def/copy/reassign, 4x3x3x4 grid of FAKE use counts at 4 positions): all identical code (6) when the first def folds away or a 53-130 cascade (var_a0 outranks the &D_807FB5D8 pointer web: a1/a0 swap); sp44 home theory: dead tests/compares/self-assign/extra defs (sp44 = 0.0f at top / case 2, sp44 = sp148, guScaleF(mtx, sp44..)) never keep sp44 as a variable (slot stays 0x3C); hill-climb 28k evals + deadsweep sweep 5824 variants with field expressions (D_807FB5D8->unk4C etc): floor 6. ugen picks a0 for the sub temp in the target and v0 in ours with identical surrounding code: unexplained.
typedef struct R2Aud2_HitInfo {
    u8 pad0[0x50];
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 pad53[0x88 - 0x53];
    s16 unk88;
    s16 unk8A;
    f32 unk8C;
    f32 unk90;
} R2Aud2_HitInfo;

extern Actor *D_807FBB40;
f32 sinApprox(f32);
f32 cosApprox(f32);
s32 camDistance3D(s32, s32, s32, s32, s32, s32);

void func_8066FE08(s32 arg0) {
    s16 var_v1;
    s16 temp_a1;
    s32 var_a3;
    s32 temp_v0;
    R2Aud2_HitInfo *sub;
    s32 var_a0; // FAKE: s32 so `var_a0 = temp_a0` needs no re-extension; the (s16) casts below re-narrow
    f32 sp160;
    f32 sp15C;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 sp14C;
    f32 sp148;
    s32 sp144;
    f32 mtx[4][4];
    f32 tmp[4][4];
    f32 inv[4][4];
    f32 px;
    f32 py;
    f32 pz;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s16 temp_a2;
    s16 temp_v0b;
    s16 temp_a0;
    s16 padW; // FAKE: unused filler word, keeps the frame layout
    f32 sp44;

    var_a3 = 0;
    if (D_807F6000[arg0].unk7C != NULL && D_807FB5D8->unk4D != 0) {
        sub = (R2Aud2_HitInfo *)D_807F6000[arg0].unk7C;
        temp_v0 = sub->unk50;
        if (temp_v0 != 0)
        switch (temp_v0) {
        case 1:
            sub->unk51 = 1;
            var_v1 = D_807FB5D8->unk48;
            if (D_807FB5D8->unk4C != 0) {
                var_v1 -= 0x800;
            }
            if (var_v1 < 0) {
                var_v1 += 0x1000;
            }
            temp_a1 = D_807FBB40->unkE6;
            temp_a0 = var_v1 - temp_a1;
            var_a0 = temp_a0;
            if (temp_a0 < 0) {
                var_a0 = (s16)-temp_a0;
            }
            if (var_a0 >= 0x801) {
                var_a0 = (s16)(0xFFF - var_a0);
            }
            temp_a2 = sub->unk8A;
            if (var_a0 && var_a0 && var_a0) {} // FAKE: dead uses raise var_a0 adjsave so it is coloured before temp_a1/temp_a2
            temp_v0b = sub->unk88;
            if (temp_a2 >= temp_v0b) {
                if (temp_a1 >= temp_v0b && temp_a2 >= temp_a1) {
                    var_a3 = 1;
                }
            } else if (temp_a1 >= temp_v0b || temp_a2 >= temp_a1) {
                var_a3 = 1;
            }
            if (var_a0 < 0x258 && var_a3 != 0) {
                sp44 = (f32)(((f64)var_v1 / 4095.0) * 6.2831854820251465);
                sub->unk8C = sinApprox(sp44);
                sub->unk90 = cosApprox(sp44);
                sub->unk52 = 1;
                return;
            }
            break;
        case 2:
            sub->unk51 = 1;
            var_v1 = D_807FB5D8->unk48;
            if (D_807FB5D8->unk4C != 0) {
                var_v1 -= 0x800;
            }
            if (var_v1 < 0) {
                var_v1 += 0x1000;
            }
            temp_a1 = D_807FBB40->unkE6;
            temp_a0 = var_v1 - temp_a1;
            var_a0 = temp_a0;
            if (temp_a0 < 0) {
                var_a0 = (s16)-temp_a0;
            }
            if (var_a0 >= 0x801) {
                var_a0 = (s16)(0xFFF - var_a0);
            }
            temp_a2 = sub->unk8A;
            if (var_a0 && var_a0 && var_a0) {} // FAKE: dead uses raise var_a0 adjsave so it is coloured before temp_a1/temp_a2
            temp_v0b = sub->unk88;
            if (temp_a2 >= temp_v0b) {
                if (temp_a1 >= temp_v0b && temp_a2 >= temp_a1) {
                    var_a3 = 1;
                }
            } else if (temp_a1 >= temp_v0b || temp_a2 >= temp_a1) {
                var_a3 = 1;
            }
            if (var_a0 < 0x258 && var_a3 != 0) {
                modelSlotGetTransformVectors(arg0, &sp160, &sp15C, &sp158, &sp154, &sp150, &sp14C, &sp148, &sp144, 0);
                guScaleF(mtx, sp148, sp148, sp148);
                guRotateF(tmp, sp154, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp150, 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp14C, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, sp160, sp15C, sp158);
                guMtxCatF(mtx, tmp, mtx);
                matrix4Invert(inv, mtx);
                px = (f32)D_807FB5C4 / 8;
                py = (f32)D_807FB5C8 / 8;
                pz = (f32)D_807FB5CC / 8;
                guMtxXFMF(inv, px, py, pz, &sp74, &sp70, &sp6C);
                guScaleF(mtx, sp148, sp148, sp148);
                guRotateF(tmp, sp154, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, (f32)((f64)sp150 + 1.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp14C, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, sp160, sp15C, sp158);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, sp74, sp70, sp6C, &sp5C, &sp58, &sp54);
                guScaleF(mtx, sp148, sp148, sp148);
                guRotateF(tmp, sp154, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, (f32)((f64)sp150 - 1.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp14C, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, sp160, sp15C, sp158);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, sp74, sp70, sp6C, &sp68, &sp64, &sp60);
                sp50 = (f32)camDistance3D((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk80, (s32)D_807FBB40->unk84, (s32)sp68, (s32)sp64, (s32)sp60);
                if (sp50 < (f32)camDistance3D((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk80, (s32)D_807FBB40->unk84, (s32)sp5C, (s32)sp58, (s32)sp54)) {
                    sub->unk52 = 1;
                    return;
                }
                sub->unk52 = 2;
            }
            break;
        }
    }
}

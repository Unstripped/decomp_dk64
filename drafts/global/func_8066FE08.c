// func_8066FE08 (src/global/70FD0.c): NM11 stage 5, 6 insn rows left: E temp subu v0 vs target a0 (x and sub temp share a0 => in target E does not interfere with x, in ours cand ucvtl interferes with x because x is assigned before the abs branch; if/else or ternary form of the abs makes it worse 566-791 even with 0-5 dead terms), and sin/cos spill slot 0x3C vs target 0x44. R2Aud2 analysis: the target 0x44 slot is the declared sp44 home (variable stays in memory, un-propagated, not address-taken: &sp44/array keeps as1 order [swc1 f0][lwc1 f12] wrong); every pad/decl-order/if-chain/inline variant keeps spill at 0x3C (removing sp44 or the switch shrinks frame 0x170). Tried init sp44=0, F1-F5 assignment forms: no effect. Untried: make sp44 survive copy-prop without address-taking.
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

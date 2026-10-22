// func_80677148 (src/global/7BBD0.c): from .scratch/Beh7BB2/func_80677148_best.c
u8 func_80677148(Actor *arg0, Actor *arg1) {
    s32 pad160[2];
    u8 sp15F;
    Beh7BB_MtxF sp11C;
    Beh7BB_MtxF spDC;
    f32 padD0[3];
    f32 spC4[3];
    f32 spB8[3];
    f32 spAC[3];
    f32 spA0[3];
    f32 sp7C[3][3];
    s32 i;
    f32 var_fv1;
    f32 var_fa0;
    f32 var_fa1;
    Beh7BB_ActorSub140 *temp_s6;
    Beh7BB_ActorSub140 *temp_s0;

    sp15F = 0;
    temp_s6 = (Beh7BB_ActorSub140 *)arg0->unk140;
    temp_s0 = (Beh7BB_ActorSub140 *)arg1->unk140;
    if (func_806744A8(D_807FB5D8, temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, temp_s6->unkC) == 0) {
        return 0;
    }
    if ((((Beh7BB_ActorFull *)arg0)->unk68 & 2) && (((Beh7BB_ActorFull *)arg1)->unk68 & 4)) {
        sp15F = 1;
    }
    if (func_80677D58(arg0) == 0) {
        sp15F = 0;
    }
    if (((Beh7BB_ActorFull *)arg1)->unk68 & 8) {
        sp15F = 2;
    }
    temp_s6->unk58 = (s32)((u8 *)D_807FB5D8 - (u8 *)temp_s0->unkA4) / 88;
    func_8067760C((Beh7BB_Struct_760C *)temp_s0, sp11C, D_807FB5D8->unk4E);
    func_8062FF10(spDC, sp11C);
    if (((Beh7BB_ActorFull *)arg1)->unk64 & 0x10) {
        var_fv1 = arg0->unk7C;
        var_fa0 = arg0->unk80;
        var_fa1 = arg0->unk84;
    } else {
        var_fv1 = (f32)D_807FB5C4 / (f32)8;
        var_fa0 = (f32)D_807FB5C8 / (f32)8;
        var_fa1 = (f32)D_807FB5CC / (f32)8;
    }
    if (!(arg0->unk60 & 0x800)) {
        guMtxXFMF(spDC, var_fv1, var_fa0, var_fa1, &spC4[0], &spC4[1], &spC4[2]);
    } else {
        spC4[0] = temp_s6->unkB8;
        spC4[1] = temp_s6->unkBC;
        spC4[2] = temp_s6->unkC0;
    }
    temp_s6->unkB8 = spC4[0];
    temp_s6->unkBC = spC4[1];
    temp_s6->unkC0 = spC4[2];

    spB8[0] = (f32)D_807FB5D8->unk24 / (f32)8;
    spAC[0] = (f32)D_807FB5D8->unk28 / (f32)8;
    spA0[0] = (f32)D_807FB5D8->unk2C / (f32)8;
    spB8[1] = (f32)D_807FB5D8->unk30 / (f32)8;
    spAC[1] = (f32)D_807FB5D8->unk34 / (f32)8;
    spA0[1] = (f32)D_807FB5D8->unk38 / (f32)8;
    spB8[2] = (f32)D_807FB5D8->unk3C / (f32)8;
    spAC[2] = (f32)D_807FB5D8->unk40 / (f32)8;
    spA0[2] = (f32)D_807FB5D8->unk44 / (f32)8;

    for (i = 0; i < 3; i++) {
        guMtxXFMF(spDC, spB8[i], spAC[i], spA0[i], &sp7C[i][0], &sp7C[i][1], &sp7C[i][2]);
    }

    temp_s6->unk66 = D_807FB5D8->unk48;
    if (D_807FB5D8->unk4C != 0) {
        temp_s6->unk66 -= 0x800;
    }
    if (temp_s6->unk66 < 0) {
        temp_s6->unk66 += 0x1000;
    }

    if (sp15F == 1) {
        func_8067A864(arg0, arg1, ((Beh7BB_ActorFull *)arg0)->unkE6, (s16)(s32)((Beh7BB_ActorFull *)arg0)->unkB8, &spC4[0], &sp7C[0][0], D_807FB5D8->unk4E, D_807FB5D0, func_8066FD6C(arg0));
        if (func_80677CAC(D_807FD610.unk28, 400) && (f64)D_807FD610.unk4 > 30.0) {
            ((Beh7BB_ActorFull *)arg0)->unkE6 = temp_s6->unk66;
        }
    } else {
        if (sp15F == 2) {
            if (((Beh7BB_ActorFull *)arg0)->unk5C & 1) {
                func_8066FC0C(arg0, D_807FB5D8, temp_s6);
            }
        }
        func_8067A908(arg0, arg1, &spC4[0], &sp7C[0][0], D_807FB5D8->unk4E, D_807FB5D0, func_8066FD6C(arg0));
    }
    return sp15F == 1;
}

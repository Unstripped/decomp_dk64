// func_8002A010 (src/bonus/2690.c): from .scratch/BonusC/func_8002A010_best.c
void func_8002A010(void) {
    f32 scale;
    Struct_Sp50 *sp50;
    Actor_BB44 *v;
    Struct_T0 *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 *p;
    s8 var_a3;
    s8 flags;
    Struct_4 *u4;

    sp50 = (Struct_Sp50 *)D_807FBB40->unk174;
    v = sp50->unk0;
    sp48 = (Struct_T0 *)v->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (sp50->unk4 != 5) {
            actorClearAllNodeFlags(D_807FBB40);
            actorAppendModelNode(D_807FBB40, 0.0f, 50.0f, 0.0f, 80.0f, -1);
        }
        D_807FBB40->unk144 = 0x24;
    }
    p = (f32 *)((u8 *)*D_807F5FD4 + (sp48->unk8[sp50->unk4] & 0x7F) * 12) + 3;
    D_807FBB40->unk7C = p[0];
    D_807FBB40->unk80 = p[1];
    D_807FBB40->unk84 = p[2];
    lightGetColor(&sp44, &sp40, &sp3C, 0);
    if (sp44 < 0.1f) {
        D_807FBB40->unk144 = 0;
    } else {
        D_807FBB40->unk144 = 0x24;
    }
    var_a3 = 0;
    if (D_807FBB85 == 1 && sp48->unk0 >= -9) {
        var_a3 = 1;
    }
    if (sp50->unk4 != 5) {
        flags = sp48->unk8[sp50->unk4];
        if (flags & 0x80) {
            sp48->unk8[sp50->unk4] = flags & 0x7F;
            actorScriptStart(D_807FBB40, D_8002D8D4[sp50->unk4]);
        } else if (sp44 < 0.05f && D_807FBB40->unk4->unk68 != 0) {
            actorScriptStart(D_807FBB40, 0);
        }
        if (var_a3 != 0) {
            actorScriptStart(D_807FBB40, D_8002D8E0[sp50->unk4]);
            func_80609140(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
            if (sp48->unk16 != 0) {
                sp48->unk16 += 1;
            }
        }
        func_806BF920();
    } else {
        D_807FBB40->unk60 |= 0x1000;
        D_807FBB40->unkE6 += 0x12C;
        if (sp48->unk0 < -0x1C) {
            D_807FBB40->unk154 = 0;
        }
        u4 = D_807FBB40->unk4;
        scale = u4->unk34;
        if (D_807FBB40->unk154 == 1) {
            scale = scale - 0.005;
            if (scale < 0.0) {
                scale = 0.0f;
            }
        } else {
            scale = 0.04f;
        }
        u4->unk34 = scale;
        D_807FBB40->unk4->unk38 = scale;
        D_807FBB40->unk4->unk3C = scale;
        if (var_a3 != 0) {
            func_80609140(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
            sp48->unk0 = 0;
            sp48->unk16 -= 1;
            D_807FBB40->unk154 = 1;
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

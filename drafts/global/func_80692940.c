// func_80692940 (src/global/936B0.c): closest diff: 2 instructions (v0 vs a0 in condition evaluation); frame 0x48 and late_rodata match
void func_80692940(void) {
    M93C_ActorExtra *sp44;
    u8 var_a0;
    s32 sp3C;

    sp44 = (M93C_ActorExtra *)M93C_ACTOR->unk174;
    if (!(M93C_ACTOR->unk60 & 0x10)) {
        M93C_ACTOR->unk6A &= 0xFFFE;
        M93C_ACTOR->unkEE = (s16)((M93C_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93C_ACTOR->unkB8 = M93C_ACTOR->unk124->unk4;
        M93C_ACTOR->unkC0 = M93C_ACTOR->unk124->unk8;
        M93C_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 50.0f);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        func_8066E854(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714A28(4);
        func_80714C08(&D_807200A0, M93C_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp44->unk14 = M93C_ACTOR->unk124->unkC;
        sp44->unk0 = D_8076A068;
        M93C_ACTOR->unk60 |= 0x01080000;
        M93C_ACTOR->unk16E = 0x3C;
        M93C_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)M93C_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_80750350;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (D_807FC928 >= 2) {
            var_a0 = 3;
        }
        func_80690C60(var_a0, D_807FBB40, &D_807200A0, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_80750364;
    }
    func_8067ACB4(D_807FBB40);
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    if (D_8076A0A8 == 0xCC) {
        M93C_ACTOR->unkFA = 0x2328;
        var_a0 = (M93C_ACTOR->unkFC != 0 && func_806725A0(D_807FBB40, M93C_ACTOR->unkEE) == 0);
    } else {
        var_a0 = M93C_ACTOR->unkFD;
    }
    if (var_a0 != 0 ||
        func_80665558() != 0 ||
        ((M93C_ACTOR->unk6A & 1) && func_8066641C() == 1) ||
        D_807FBB85 != 0 ||
        (M93C_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < D_8076A068)) {
        func_807149B8(1);
        func_80714950(0x1006E);
        func_8071498C(func_8071A8B0);
        func_80714CC0(&D_8071FB34, 0.45f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        func_80608528(D_807FBB40, 0x8D, 0xFF, 0x7F, 0x1E);
        actorDespawn(D_807FBB40);
        if (D_80750AD0 == 0) {
            s32 var_s1;
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                func_807149B8(1);
                func_80714950(0x0B000000 + var_s1);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_807200EC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            }
        }
    }
    if (D_807FC928 >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if (D_8076A0A8 == 0x10) {
        sp3C = (s32)((f64)sp3C * 1.2);
    }
    if ((u32)(sp44->unk0 + sp3C) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

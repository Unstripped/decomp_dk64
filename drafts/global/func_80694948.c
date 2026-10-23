// func_80694948 (src/global/936B0.c): diff: xori v0 vs addiu t5 ordering in unk154 block
void func_80694948(void) {
    M93D_ActorExtra *sp34;
    s32 pad30;
    s32 sp2C;
    u8 sp2B;
    u8 temp_v1;

    sp34 = (M93D_ActorExtra *)M93D_ACTOR->unk174;
    sp2B = 0;
    if (!(M93D_ACTOR->unk60 & 0x10)) {
        M93D_ACTOR->unk6A &= 0xFFFE;
        M93D_ACTOR->unkEE = (s16)((M93D_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93D_ACTOR->unkB8 = M93D_ACTOR->unk124->unk4;
        M93D_ACTOR->unkC0 = M93D_ACTOR->unk124->unk8;
        M93D_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 60.0f);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        func_8066E854(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714A28(4);
        func_80714C08(&D_80720268, M93D_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp34->unk14 = M93D_ACTOR->unk124->unkC;
        sp34->unk0 = D_8076A068;
        M93D_ACTOR->unk60 |= 0x01080000;
        M93D_ACTOR->unk16E = 0x3C;
        M93D_ACTOR->unk16F = 0x3C;
        sp34->unk13 = (u8)(u32)M93D_ACTOR->unk124->unk10;
        sp34->unk1C = 0;
    }
    sp2C = D_80750358;
    if (sp34->unk13 & 2) {
        if (D_807FC928 >= 2) {
            func_80690C60(3, D_807FBB40, &D_80720268, 0);
        } else {
            func_80690C60(2, D_807FBB40, &D_80720268, 0);
        }
    }
    if (sp34->unk13 & 4) {
        sp2C = D_8075036C;
    }
    func_8067ACB4(D_807FBB40);
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    temp_v1 = M93D_ACTOR->unk154;
    if (temp_v1 == 0 && (M93D_ACTOR->unkFD != 0 || (M93D_ACTOR->unk6A & 1) || D_807FBB85 != 0)) {
        sp2B = 1;
    } else if (temp_v1 != 0) {
        M93D_ACTOR->unk154 = temp_v1 + 1;
        if ((temp_v1 ^ 2) == 0) {
            actorDespawn(D_807FBB40);
        }
    }
    if (D_807FC928 >= 2) {
        sp2C = (s32)((f32)sp2C * 1.4f);
    }
    if ((u32)(sp34->unk0 + sp2C) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
    if (sp2B != 0) {
        func_8069329C();
        func_8066EB40(D_807FBB40, 250.0f);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 250.0f, -1);
        M93D_ACTOR->unk154 = 1;
    }
}

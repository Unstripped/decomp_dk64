// func_80693EC0 (src/global/936B0.c): diff: register rotation (+3) starting from angle calculation
void func_80693EC0(void) {
    M93D_ActorExtra *sp4C;
    s32 pad48;
    u8 sp47;
    s32 pad40;
    s32 temp_v0;
    f32 temp_fv0;

    sp4C = (M93D_ActorExtra *)M93D_ACTOR->unk174;
    sp47 = 0;
    if (!(M93D_ACTOR->unk60 & 0x10)) {
        func_80608528(D_807FBB40, 0xF4, 0xFF, 0x7F, 5);
        M93D_ACTOR->unk6A &= 0xFFFE;
        M93D_ACTOR->unkEE = (s16)((M93D_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93D_ACTOR->unkB8 = (f32)((f64)(M93D_ACTOR->unk124->unk4 / (f32)4) * 2.6);
        M93D_ACTOR->unkC0 = M93D_ACTOR->unk124->unk8;
        M93D_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 60.0f);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        func_8066E854(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_807149C8(0, 0xFF, 0, 0xFF);
        func_80714C08(&D_80720268, M93D_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp4C->unk0 = D_8076A068;
        sp4C->unk4 = 0;
        M93D_ACTOR->unk60 |= 0x80000;
        M93D_ACTOR->unkFA = 0x2328;
        sp4C->unk13 = (u8)(u32)M93D_ACTOR->unk124->unk10;
        if (sp4C->unk13 == 0x63) {
            sp4C->unk4 = 2;
        }
        sp4C->unk1C = 0;
    }
    if ((u32)(sp4C->unk0 + 10) < D_8076A068) {
        M93D_ACTOR->unk60 &= 0xFFF7FFFF;
    }
    func_80690C60(1, D_807FBB40, 0, 1);
    func_8067ACB4(D_807FBB40);
    if (M93D_ACTOR->unkFC != 0 && func_806725A0(D_807FBB40, M93D_ACTOR->unkEE) == 0) {
        s32 angle;
        s32 diff;
        func_80608528(D_807FBB40, 0xF5, 0xFF, 0x7F, 0x1E);
        temp_v0 = func_80672A70(M93D_ACTOR->unkF4, M93D_ACTOR->unkF6);
        angle = M93D_ACTOR->unkEE;
        angle += 0x800;
        diff = temp_v0 - (angle & 0xFFF);
        M93D_ACTOR->unkEE = temp_v0 + diff;
        if (M93D_ACTOR->unkEE < 0) {
            M93D_ACTOR->unkEE += 0xFFF;
        }
        if (M93D_ACTOR->unkEE >= 0x1000) {
            M93D_ACTOR->unkEE -= 0xFFF;
        }
        if (func_806725A0(D_807FBB40, M93D_ACTOR->unkEE) == 0) {
            sp47 = 1;
        }
    }
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x4B, 0x78, 0, 1.0f);
    M93D_ACTOR->unkC0 += D_807502E4;
    temp_fv0 = (f32)D_807502D0;
    if (M93D_ACTOR->unkC0 < temp_fv0) {
        M93D_ACTOR->unkC0 = temp_fv0;
    }
    if ((M93D_ACTOR->unk6A & 1) && !(M93D_ACTOR->unk6C & 1)) {
        switch (sp4C->unk4) {
            case 0:
                M93D_ACTOR->unkC0 = 200.0f;
                break;
            case 1:
                M93D_ACTOR->unkC0 = 150.0f;
                break;
            case 2:
                M93D_ACTOR->unkC0 = 100.0f;
                func_8066EB40(D_807FBB40, 200.0f);
                func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 180.0f, -1);
                break;
            case 3:
                M93D_ACTOR->unkC0 = 80.0f;
                break;
        }
        func_80608528(D_807FBB40, 0xF5, 0xFF, 0x7F, 0x1E);
        sp4C->unk4++;
        D_807FBB40->unkB8 = (f32)(((f64)D_807FBB40->unkB8 / 3.0) * 2.5);
    }
    if ((M93D_ACTOR->unk64 & 0x100) || sp47 != 0) {
        D_807FBB85 = 1;
    }
    if (((M93D_ACTOR->unk6A & 1) && sp4C->unk4 == 4) || D_807FBB85 != 0) {
        func_8069329C();
        actorDespawn(D_807FBB40);
    }
    if ((u32)(sp4C->unk0 + D_80750344) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

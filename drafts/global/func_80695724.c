// func_80695724 (src/global/936B0.c): Near-match: correct 0xA0 frame and control flow, diff in regalloc (temp_s2 spilled vs cached in ) and stack offset of RGB temporaries.
void func_80695724(f32 arg0, u8 arg1) {
    M93F_ActorExtra *temp_s2;
    u8 pad94;
    u8 sp95;
    u8 sp96;
    u8 sp97;
    f32 sp8C[2];
    f32 sp4C[4][4];
    s32 sp48;
    u8 temp_t7;
    u8 temp_v0_4;
    ActorSub4 *temp_v0;

    temp_s2 = M93F_ACTOR->unk174;
    if (!(M93F_ACTOR->unk60 & 0x10)) {
        if (arg1 == 1) {
            func_806086CC(M93F_ACTOR->unk7C, M93F_ACTOR->unk80, M93F_ACTOR->unk84, 0x306, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        M93F_ACTOR->unk6A &= 0xFFFE;
        M93F_ACTOR->unkEE = (s16)((M93F_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93F_ACTOR->unkE6 = (s16)M93F_ACTOR->unkEE;
        M93F_ACTOR->unkB8 = M93F_ACTOR->unk124->unk4;
        M93F_ACTOR->unkC0 = M93F_ACTOR->unk124->unk8;
        M93F_ACTOR->unk132 = (u8)(u32)M93F_ACTOR->unk124->unk10;
        temp_v0 = M93F_ACTOR->unk4;
        temp_v0->unk34 = 2.0 * temp_v0->unk34;
        temp_v0 = M93F_ACTOR->unk4;
        temp_v0->unk38 = 2.0 * temp_v0->unk38;
        temp_v0 = M93F_ACTOR->unk4;
        temp_v0->unk3C = 2.0 * temp_v0->unk3C;
        temp_s2->unk8 = -(func_80611BB4(M93F_ACTOR->unkC0, M93F_ACTOR->unkB8) * 57.295776f);
        M93F_ACTOR->unk144 = 0x3C;
        temp_s2->unk12 = 0;
        temp_s2->unk0 = D_8076A068;
        M93F_ACTOR->unk60 |= 0x80000;
        temp_s2->unk10 = 0;
    }
    sp48 = arg1;
    func_8067ACB4(D_807FBB40);
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, arg0);
    if (sp48 != 0) {
        if (sp48 == 1) {
            sp97 = 0xFF;
            sp96 = 0;
            sp95 = 0;
        }
    } else {
        sp97 = 0xFF;
        sp96 = 0xFF;
        sp95 = 0xFF;
    }
    func_806595F0(1);
    func_8065A708(M93F_ACTOR->unk7C, M93F_ACTOR->unk80, M93F_ACTOR->unk84, 0.0f, 0.0f, 0.0f, 80.0f, 0, sp97, sp96, sp95);
    if (sp48 == 1) {
        temp_v0_4 = temp_s2->unk12;
        if (temp_v0_4 == 0 && ((M93F_ACTOR->unk6A & 1) || M93F_ACTOR->unkFD != 0 || D_807FBB85 != 0)) {
            func_80714950(0x1006E);
            func_8071498C(func_8071A8B0);
            func_80714CC0(&D_8072006C, 1.2f, M93F_ACTOR->unk7C, M93F_ACTOR->unk80, M93F_ACTOR->unk84);
            effectSpawnBoneWhite(0, 0, 0.8f, M93F_ACTOR->unk7C, M93F_ACTOR->unk80, M93F_ACTOR->unk84, -0x50);
            func_80608528(D_807FBB40, 0xF6, 0xFF, 0x3F, 0x14);
            temp_s2->unk12 = 2;
        } else {
            temp_t7 = temp_v0_4 - 1;
            if (temp_v0_4 != 0) {
                temp_s2->unk12 = temp_t7;
                if (!(temp_t7 & 0xFF)) {
                    actorDespawn(D_807FBB40);
                }
            }
        }
        if ((u32)(temp_s2->unk0 + D_80750344) < D_8076A068) {
            actorDespawn(D_807FBB40);
        }
    }
}

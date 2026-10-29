// func_8068412C (src/global/80150.c): from .scratch/R3D/func_8068412C_best.c
void func_8068412C(void) {
    Actor *actor = D_807FBB40;
    R2G_TagBarrelData *sub = actor->unk174;

    if (!(actor->unk60 & 0x10)) {
        sub->unk22 = actor->unkE6;
        sub->unk24 = D_807FBB40->unk80;
        ((R2G_Actor *)D_807FBB40)->unk146 = 0;
        D_807FBB40->unk15E = 0;
        func_80714998(2);
        func_807149FC(-1);
        func_807149B8(1);
        func_807149A8(0x3E8);
        func_80714A28(4);
        actor = D_807FBB40;
        func_80714CC0(&D_8071FC8C, 1.3f, actor->unk7C, (f32)((f64)actor->unk80 + 13.0), actor->unk84);
        if (func_80689F2C()) {
            D_807FBB40->unk12A = 0x7D0;
        } else {
            D_807FBB40->unk12A = 0x15E;
        }
        actor = D_807FBB40;
        actor->unkA4 = actor->unk80;
        func_80665564(D_807FBB40, 0.0f);
        D_807FBB40->unk110 = 0;
        actor = D_807FBB40;
        actor->unk60 |= 2;
        actor = D_807FBB40;
    }
    func_8068408C(actor);
    func_80680774();
    func_8067ACB4(D_807FBB40);
    actor = D_807FBB40;
    switch (actor->unk154) {
    case 0:
        if (sub->unk4 != 0) {
            sub->unk4--;
            if (sub->unk4 == 0) {
                D_807FBB40->unk144 = 2;
            }
        } else {
            func_806833DC(sub);
        }
        actor = D_807FBB40;
        if (actor->unk155[0] == 0xA) {
            if (((Actor *)D_807FBB4C)->unk6A & 4 || func_806C9D7C() != 0) {
                actor = D_807FBB40;
                actor->unk155[0] = 0;
            } else if (((Actor *)D_807FBB4C)->unk110 != 1 && (((Actor *)D_807FBB4C)->unk6A & ((Actor *)D_807FBB4C)->unk6C & 1)) {
                func_806832F4(((Actor *)D_807FBB4C)->unk58, 1);
            }
        }
        actor = D_807FBB40;
        break;
    case 1:
        func_806836D0(sub);
        func_8068C350(func_80683AD8, D_807FBB40, 3);
        actor = D_807FBB40;
        break;
    case 2:
        if (sub->unk4 != 0) {
            sub->unk4--;
        } else {
            func_8067AAB8(actor, sub->unk0, sub->unk38, 180.0f, 0x46);
            func_80679200(sub->unk0, D_807FBB40, 0x40, 1, 0, 0);
            slotQueuePopActiveMask();
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk155[0] = 0;
            if (func_806832F4(((Actor *)D_807FBB4C)->unk58, 0) != 0) {
                D_807FBB40->unk155[0] = 0xA;
            }
            sub->unk4 = 0x1E;
        }
        actor = D_807FBB40;
        break;
    }
    func_8065D254(actor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x64, 0x78, 0, 1.0f);
    actor = D_807FBB40;
    if (actor->unk154 != 1) {
        actor->unkE6 += 0x32;
        actor = D_807FBB40;
        actor->unkE6 &= 0xFFF;
        D_807FBB40->unk80 = func_80612794(sub->unk28) * 5.0f + sub->unk24;
        sub->unk28 += 0x32;
        sub->unk28 &= 0xFFF;
        actor = D_807FBB40;
    }
    actorUpdateModelMatrix(actor, 0);
}

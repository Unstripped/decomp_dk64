// func_806833DC (src/global/80150.c): from .scratch/R2G/func_806833DC_best.c
void func_806833DC(R2G_TagBarrelData *arg0) {
    Actor *sp34;
    R2G_KongSub *sp30;
    s32 sp28;
    s32 sp20;

    switch (D_807FBB40->unk155[0]) {
    case 0xB:
        if (func_8061CB50() == 0) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk155[0] = 0;
        }
        break;
    case 0:
    case 0xA:
        if (D_807FBB70.unk200 == 4) {
            arg0->unk0 = (Actor *)D_807FBB70.unk1FC;
            arg0->unk0->unk144 = 1;
            ((R2G_KongSub *)arg0->unk0->unk174)->unk1F0 |= 0x20000000;
            D_807FBB40->unk155[0] = 1;
            arg0->unk4 = 2;
            arg0->unk3C = 0;
        }
        break;
    case 1:
        if (arg0->unk4 != 0) {
            arg0->unk4--;
        } else {
            sp34 = arg0->unk0;
            sp28 = ((R2G_ActorKong *)sp34)->unk12C;
            sp30 = sp34->unk174;
            if (sp28 == -1) {
                sp28 = 0;
            }
            func_806C93E4(sp34, sp30);
            func_806C9304(arg0->unk0, sp30);
            sp20 = (s16)sp28;
            func_80659620(&arg0->unk2C, &arg0->unk30, &arg0->unk34, (s16)sp28);
            func_80659670(1.0f, 1.0f, 1.0f, sp20);
            D_807FBB40->unkE6 = arg0->unk22;
            D_807FBB40->unk144 = 1;
            D_807FBB60 &= 0xFFFCFFCF;
            arg0->unk6 = 0;
            if (((R2G_ActorKong *)sp34)->unk5A != ((R2G_ActorKongAction *)D_8074E814)[arg0->unk6].unk2) {
                do {
                    arg0->unk6++;
                } while (((R2G_ActorKong *)sp34)->unk5A != ((R2G_ActorKongAction *)D_8074E814)[arg0->unk6].unk2);
            }
            arg0->unk7 = arg0->unk6;
            if (D_8076A0A8 != 0x11) {
                func_80602A94(0x65, 1.0f);
                func_80602CE0(0x65, 0x7E - D_8074E848[arg0->unk6], 1);
            }
            flagSet(func_805FF018(D_807FBB40->unk58, arg0->unk6), 1, 0);
            func_80682E38(arg0);
            func_80627878(sp30->unk104);
            arg0->unk38 = sp34->unkE6;
            sp34->unkE6 = D_807FBB40->unkE6;
            func_8060DEC8();
            func_8061CC40(D_807FBB40, 0xE, 0xC);
            func_8061B650(sp30->unk104);
            func_806FB218();
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155[0] = 0;
        }
        break;
    }
}

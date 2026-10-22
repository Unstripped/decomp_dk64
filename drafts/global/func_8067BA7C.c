// func_8067BA7C (src/global/80150.c): from .scratch/R2G/func_8067BA7C_best.c
void func_8067BA7C(s32 arg0) {
    Actor *actor = D_807FBB40;

    if (!(actor->unk60 & 0x10) && arg0 == 0x13) {
        func_80688370(actor, 0, 0.5f);
        func_806883C8(D_807FBB40, 0, 0);
        func_8068839C(D_807FBB40, 0, 0);
        func_8068842C(D_807FBB40, 0, -1);
        actor = D_807FBB40;
    }
    switch (actor->unk154) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 10:
        func_80608528(actor, 0x31, 0xFF, 0x7F, 1);
        func_807149B8(0);
        func_807149FC(1);
        actor = D_807FBB40;
        func_80714CC0(&D_8071FE08, 0.5f, actor->unk7C, actor->unk80 + 7.0f, actor->unk84);
        actor = D_807FBB40;
        func_80689114((s16)arg0, actor->unk7C, (f32)((f64)actor->unk80 + 8.3), actor->unk84, 0, 1.0f, actor);
        actor = D_807FBB40;
        actor->unk154++;
        break;
    case 11:
        if (D_807FBBA8 != 0) {
            actor->unk154 = 0x14;
        }
        break;
    case 20:
        if (arg0 == 0x95) {
            actor = D_807FBB40;
            actor->unk168 = 0x1E;
            actor = D_807FBB40;
            actor->unk154 = 0x15;
        }
        break;
    case 21:
        if (actor->unk168 != 0) {
            actor->unk168--;
        } else {
            actor->unk154 = 0xA;
        }
        break;
    }
    if (arg0 == 0x13) {
        func_806319C4(D_807FBB40, 0);
    }
}

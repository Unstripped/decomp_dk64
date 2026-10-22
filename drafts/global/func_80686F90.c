// func_80686F90 (src/global/89250.c): from .scratch/Beh8923A/func_80686F90_best.c
void func_80686F90(arg0, arg1, arg2)
u8 arg0;
s16 arg1;
s16 arg2;
{
    u8 temp;
    actorSpawn(0x109, 0xC0);
    temp = arg0;
    if (temp != 0) {
        func_80671C0C(D_807FBB40, temp, &D_807FBB44->unk7C, &D_807FBB44->unk80, &D_807FBB44->unk84);
    } else {
        D_807FBB44->unk7C = D_807FBB40->unk7C;
        D_807FBB44->unk80 = D_807FBB40->unk80;
        D_807FBB44->unk84 = D_807FBB40->unk84;
    }
    D_807FBB44->unkE6 = arg1;
    *(s16 *)D_807FBB44->unkE8 = arg2;
    D_807FBB44->unk4->unk38 = (f32)(D_807FBB44->unk4->unk38 * 0.01);
}

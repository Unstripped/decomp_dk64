// func_80685708 (src/global/89250.c): from .scratch/Beh8923A/func_80685708_best.c
typedef struct Beh8923A_Struct16 {
    s32 a[4];
} Beh8923A_Struct16;

extern Beh8923A_Struct16 D_8074E898;

void func_80685708(arg0, arg1)
Actor *arg0;
u8 arg1;
{
    s32 pad;
    Beh8923A_Struct16 sp34;
    f32 temp_scale;

    temp_scale = (f64)arg0->unk4->unk38 / 0.15;
    sp34 = D_8074E898;
    if (arg1 != 0) {
        func_80685520((f64)temp_scale * 0.36, arg1, arg0->unk7C, arg0->unk80 + 4.0f, arg0->unk84);
        actorSpawn(0x145, sp34.a[arg1]);
        func_8067B238(D_807FBB44, arg0, arg0->unk4->unk38 * 0.5f);
        ((Actor174_5390 *)D_807FBB44->unk174)->unk6 = arg1 - 1;
    }
}

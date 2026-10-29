// func_80685708 (src/global/89250.c): stage 5: 1 regalloc spill diff (sw t6, 44(sp) vs lbu t7, 79(sp))
typedef struct KaD_Struct16 {
    s32 a[4];
} KaD_Struct16;

extern KaD_Struct16 D_8074E898;

void func_80685708(arg0, arg1)
Actor *arg0;
u8 arg1;
{
    s32 pad;
    KaD_Struct16 sp34;
    f32 temp_scale;

    temp_scale = (f32)((f64)arg0->unk4->unk38 / 0.15);
    sp34 = D_8074E898;
    if (arg1 != 0) {
        effectSpawnMultiTierRing((f32)((f64)temp_scale * 0.36), arg1, arg0->unk7C, arg0->unk80 + 4.0f, arg0->unk84);
        actorSpawn(0x145, sp34.a[arg1]);
        func_8067B238(D_807FBB44, arg0, arg0->unk4->unk38 * 0.5f);
        ((Actor174_5390 *)D_807FBB44->unk174)->unk6 = arg1 - 1;
    }
}

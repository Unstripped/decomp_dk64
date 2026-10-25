// func_806EFA3C (src/global/EFDC0.c): stage 4: recovered spawn, height scaling, parameter selection, attachment flags, and transition; preserves standalone D_8075D380 asm
extern u16 D_8075D380[];
extern Actor *actorSpawn(s32, s32, f32);
extern void func_8067B238(Actor *, f32);
extern void func_80614EBC(Actor *, s32);
extern void func_80614E78(Actor *, s32);

void func_806EFA3C(void) {
    u16 spawnParams[5] = { D_8075D380[0], D_8075D380[1], D_8075D380[2], D_8075D380[3], D_8075D380[4] };
    f32 height = D_807FBB48->unk4->unk34;

    actorSpawn(0x140, 0xB9, height);
    if (D_807FBB48->unk58 == 2) {
        height *= 1.25f;
    }
    func_8067B238(D_807FBB44, height);
    func_80614EBC(D_807FBB44, spawnParams[D_8074E77C[((u8 *)D_807FD580)[0x1A4]]]);
    D_807FBB44->unk60 |= 0x40000000;
    func_80614E78(D_807FBB48, 0x88);
    D_807FBB40->unk154 = 0x79;
    D_807FBB40->unk155[0] = 0;
}

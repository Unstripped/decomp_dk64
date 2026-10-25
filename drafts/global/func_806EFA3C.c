// func_806EFA3C (src/global/EFDC0.c): Stage 4 retained: target frame and saved-ra set match. Uses actual two-argument actorSpawn call, three-argument func_8067B238 call, raw 10-byte parameter copy, and double 1.25 scale; remaining mismatch is copy scheduling and register allocation.
typedef struct EfN7SpawnParams {
    u16 values[5];
} EfN7SpawnParams;

extern u16 D_8075D380[];
extern void actorSpawn(s32, s32);

void func_806EFA3C(void) {
    EfN7SpawnParams spawnParams;
    f32 height = D_807FBB48->unk4->unk34;

    *(u32 *)&spawnParams.values[0] = *(u32 *)&D_8075D380[0];
    *(u32 *)&spawnParams.values[2] = *(u32 *)&D_8075D380[2];
    spawnParams.values[4] = D_8075D380[4];
    actorSpawn(0x140, 0xB9);
    if (D_807FBB48->unk58 == 2) {
        height *= 1.25;
    }
    func_8067B238(D_807FBB44, D_807FBB48, height);
    func_80614EBC(D_807FBB44, ((u16 *)&spawnParams)[D_8074E77C[((u8 *)D_807FD580)[0x1A4]]]);
    D_807FBB44->unk60 |= 0x40000000;
    func_80614E78(D_807FBB48, 0x88);
    D_807FBB40->unk154 = 0x79;
    D_807FBB40->unk155[0] = 0;
}

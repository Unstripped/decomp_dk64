// func_80670C5C (src/global/70FD0.c): logic 100% matched, frame 0x110 matched; 12-byte scalar stack offset shift from unused norm[1] store and C0/60 padding
typedef struct {
    u8 pad0[0x28];
    f32 unk28[3];
    f32 unk34[3];
    f32 unk40[3];
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    u8 pad58[2];
    s8 unk5A;
} M70D_Struct70C5C_2;

extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern u8 D_807FC929;
extern s16 D_807FD584;

void func_8066C610(s16, s8, f32 [4][4]);

void func_80670C5C(M70D_Actor *arg0, s16 arg1, M70D_Struct70C5C_2 *arg2) {
    f32 mtx[4][4];
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spB4[3];
    f32 spA8[3];
    f32 sp9C[3];
    f32 normal[3];
    f32 v1[3];
    f32 v2[3];
    f32 norm[3];
    f32 sp64;
    f32 sp5C;
    M70D_ActorSub174 *sub;
    f32 sp54;
    s32 i;
    f32 inv_len;
    f32 scale;

    sub = arg0->unk174;
    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        sp54 = D_80753D50[D_807FD584];
    } else {
        sp54 = D_80753D60[D_807FD584];
    }

    func_8066C610(arg1, arg2->unk5A, mtx);
    guMtxXFMF(mtx, arg2->unk4C, arg2->unk50, arg2->unk54, &spCC, &spC8, &spC4);

    for (i = 0; i < 3; i++) {
        guMtxXFMF(mtx, arg2->unk28[i], arg2->unk34[i], arg2->unk40[i], &spB4[i], &spA8[i], &sp9C[i]);
    }

    v1[0] = spB4[2] - spB4[0];
    v1[1] = spA8[2] - spA8[0];
    v1[2] = sp9C[2] - sp9C[0];

    v2[0] = spB4[1] - spB4[0];
    v2[1] = spA8[1] - spA8[0];
    v2[2] = sp9C[1] - sp9C[0];

    normal[0] = (v1[1] * v2[2]) - (v2[1] * v1[2]);
    normal[1] = (v1[2] * v2[0]) - (v2[2] * v1[0]);
    normal[2] = (v1[0] * v2[1]) - (v2[0] * v1[1]);

    inv_len = 1.0f / sqrtf((normal[0] * normal[0]) + (normal[1] * normal[1]) + (normal[2] * normal[2]));
    norm[0] = normal[0] * inv_len;
    norm[1] = normal[1] * inv_len;
    norm[2] = normal[2] * inv_len;

    scale = sp54 / 8;
    sp5C = norm[0] * scale;
    sp64 = norm[2] * scale;

    sub->unkE0 = spCC - sp5C;
    sub->unkE8 = 1;
    sub->unkE4 = spC4 - sp64;
}

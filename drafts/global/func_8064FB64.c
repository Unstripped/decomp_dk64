// func_8064FB64 (src/global/54150.c): stage 5: target computes arg3+arg0*0x24 twice (v1 and a1) with the 0x24 folded into the loads; IDO CSEs to one base. Target spills all 9 floats to slots 0xD8..0xF8 and saves only s0; here 2 stay in f20/f22 and mtx addr in s1 (frame layout shifted 0x10). Target .rodata has 9 distinct doubles, ours 7 (duplicate -180 not materialised)
typedef struct M54C_Track {
    u8 *unk0;
    u8 *unk4;
} M54C_Track;

typedef struct M54C_Key {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} M54C_Key; /* 0x24 */

void func_80612BC0(void *, f32);
void func_80612C30(void *, f32);
void func_80612CA0(void *, f32);

void func_8064FB64(arg0, arg1, arg2raw, arg3, arg4)
u8 arg0;
u32 arg1;
void *arg2raw;
u8 *arg3;
u8 arg4;
{
    u32 off;
    M54C_Track *arg2;
    M54C_Key *k0;
    f32 *kf;
    f32 x;
    f32 y;
    f32 z;
    f32 c6;
    f32 c7;
    f32 c8;
    f32 c0;
    f32 c1;
    f32 c2;
    float work[4][4];
    float mtx[4][4];

    arg2 = arg2raw;
    off = D_807F6BE0;
    k0 = (M54C_Key *)(arg3 + arg0 * 0x24);
    kf = (f32 *)(arg3 + arg0 * 0x24);
    x = kf[12] - k0->unkC;
    if (x < -180.0) {
        x += 360.0;
    } else if (x > 180.0) {
        x -= 360.0;
    }
    x *= (*(f32 *)&arg1);
    x += k0->unkC;
    y = kf[13] - k0->unk10;
    if (y < -180.0) {
        y += 360.0;
    } else if (y > 180.0) {
        y -= 360.0;
    }
    y *= (*(f32 *)&arg1);
    y += k0->unk10;
    z = kf[14] - k0->unk14;
    if (z < -180.0) {
        z += 360.0;
    } else if (z > 180.0) {
        z -= 360.0;
    }
    z *= (*(f32 *)&arg1);
    z += k0->unk14;
    c7 = (kf[16] - k0->unk1C) * (*(f32 *)&arg1) + k0->unk1C;
    c8 = (kf[17] - k0->unk20) * (*(f32 *)&arg1);
    c8 = c8 + k0->unk20;
    c6 = (kf[15] - k0->unk18) * (*(f32 *)&arg1) + k0->unk18;
    c0 = (kf[9] - k0->unk0) * (*(f32 *)&arg1) + k0->unk0;
    c2 = (kf[11] - k0->unk8) * (*(f32 *)&arg1);
    c2 = c2 + k0->unk8;
    c1 = (kf[10] - k0->unk4) * (*(f32 *)&arg1);
    c1 = c1 + k0->unk4;
    switch (arg4 & 0xF) {
    case 1:
        c6 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 2:
        c7 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 3:
        c8 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 4:
        x *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 6:
        z *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 7:
        c0 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 8:
        c1 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 9:
        c2 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    }
    memcpy(work, arg2->unk4 + off, 0x40);
    guScaleF(mtx, c0, c1, c2);
    guMtxCatF(work, mtx, work);
    func_80612CA0(mtx, z);
    guMtxCatF(work, mtx, work);
    func_80612C30(mtx, y);
    guMtxCatF(work, mtx, work);
    func_80612BC0(mtx, x);
    guMtxCatF(work, mtx, work);
    guTranslateF(mtx, c6, c7, c8);
    guMtxCatF(work, mtx, work);
    memcpy(mtx, arg2->unk4 + off + 0x40, 0x40);
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(arg2->unk0 + off));
}

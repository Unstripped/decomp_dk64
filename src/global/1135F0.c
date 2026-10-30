#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;

#pragma GLOBAL_ASM("asm/global/nonmatchings/1135F0/func_8070E8F0.s")

extern s16 D_807FD9D0;
extern s16 D_807FD9D2;
extern u8 D_807FD9D4;
extern u8 D_807FD9D5;

void func_8070F2C8(s16 arg0, s16 arg1, s8 arg2, s8 arg3) {
    D_807FD9D0 = arg0;
    D_807FD9D2 = arg1;
    D_807FD9D4 = arg2;
    D_807FD9D5 = arg3;
}

typedef struct R1135bTexture {
    s32 image;
    u8 pad4[4];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
} R1135bTexture;

extern R1135bTexture *D_807550D0;

void func_8070F2FC(Gfx **arg0, s16 arg1, s16 arg2) {
    Gfx *dl;
    f32 fx;
    f32 fy;
    f32 sx;
    f32 sy;
    s32 ix;
    s32 iy;
    s32 s;
    s32 t;
    s16 x1;
    s16 y1;
    s16 dsdx;
    s16 dtdy;

    dl = *arg0;
    if (D_807550D0 != NULL) {
        fx = (f32)arg1 * 0.25f;
        fy = (f32)arg2 * 0.25f;
        ix = (s32)fx;
        s = (s32)(((f32)D_807550D0->unk10 - (fx - (f32)ix)) * 32.0f);
        iy = (s32)fy;
        t = (s32)(((f32)D_807550D0->unk12 - (fy - (f32)iy)) * 32.0f);
        sx = 1024.0f / (f32)D_807FD9D0;
        sy = 1024.0f / (f32)D_807FD9D2;
        x1 = (s32)(((f32)ix + ((f32)D_807550D0->unkA * sx)) * 4.0f);
        y1 = (s32)(((f32)iy + ((f32)D_807550D0->unkC * sy)) * 4.0f);
        if (D_807FD9D4 != 0) {
            s += (D_807550D0->unkA << 5) - 0x20;
            dsdx = -D_807FD9D0;
        } else {
            dsdx = D_807FD9D0;
        }
        if (D_807FD9D5 != 0) {
            t += (D_807550D0->unkC << 5) - 0x20;
            dtdy = -D_807FD9D2;
        } else {
            dtdy = D_807FD9D2;
        }
        gSPTextureRectangle(dl++, ix * 4, iy * 4, x1, y1, G_TX_RENDERTILE, s, t, dsdx, dtdy);
        *arg0 = dl;
    }
}

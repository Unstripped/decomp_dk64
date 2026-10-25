// func_80704B20 (src/global/109660.c): stage 4: frame 0x148 + s0 match; color-interpolation expression order, local slots, DL store scheduling differ
typedef struct {
    u8 unk0[0x90];
    f32 unk90;
    u8 unk94[0xFA - 0x94];
    u8 unkFA;
} R1F109660bLightView;

typedef struct {
    u8 unk0[0x174];
    R1F109660bLightView *unk174;
} R1F109660bLightState;

typedef struct {
    u8 unk0[0x220];
    f32 unk220;
    u8 unk224[0x270 - 0x224];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 unk278[0x2CA - 0x278];
    s16 unk2CA;
    s16 unk2CC;
} R1F109660bPlayerView;

extern R1F109660bLightState *D_807F5D10;
extern u8 D_80754EF8[];
extern void *D_80754ED8[];
extern u8 D_2000080[];
extern u8 D_2000180[];
f32 func_80612D10(f32);
void func_80612CA0(f32 (*)[4], f32);
void lightGetColor(f32 *, f32 *, f32 *, s16);

#define R1F109660B_COLOR(dst, src, off, red, green, blue, alpha) \
    (((u32)((red) * ((f32)dst[off] + (alpha) * ((f32)src[off] - (f32)dst[off]))) << 24) | \
    (((u32)((green) * ((f32)dst[(off) + 1] + (alpha) * ((f32)src[(off) + 1] - (f32)dst[(off) + 1]))) & 0xFF) << 16) | \
    (((u32)((blue) * ((f32)dst[(off) + 2] + (alpha) * ((f32)src[(off) + 2] - (f32)dst[(off) + 2]))) & 0xFF) << 8) | 0xFF)
#define R1F109660B_PLAYER ((R1F109660bPlayerView *)D_807FC924)

Gfx *func_80704B20(Gfx *gdl, s32 arg1, f32 angle, Mtx *mtx, u8 arg4, u8 arg5, u8 arg6, s8 arg7, f32 alpha) {
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    f32 red;
    f32 green;
    f32 blue;
    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    f32 y;
    s16 offset;
    void **table;
    R1F109660bLightView *light;
    u8 *dst;
    u8 *src;
    volatile u8 framePad[0x50];

    y = -(256.0f - (func_80612D10(angle) * 300.0f)) - 80.0f;
    framePad[0] = 0;
    light = D_807F5D10->unk174;
    if (arg4 == 5) {
        y = (f32)((f64)y + ((f64)R1F109660B_PLAYER->unk2CA * 0.08 - 75.0));
    }

    switch (arg6) {
    case 0:
        blue = 1.0f;
        green = 1.0f;
        red = 1.0f;
        break;
    case 1:
        if (D_807FD968 >= 0.0f) {
            red = D_807FD968;
            green = D_807FD96C;
            blue = D_807FD970;
        } else {
            if (arg7 == -1) {
                arg7 = *((s8 *)D_807FBB4C + 0x12D);
            }
            lightGetColor(&red, &green, &blue, arg7);
        }
        break;
    }
    if ((light->unkFA != 0) && (R1F109660B_PLAYER->unk220 < (light->unk90 + 3.0f))) {
        red = (f32)((f64)red * 0.1);
        green = (f32)((f64)green * 0.1);
        blue = (f32)((f64)blue * 0.3);
    }

    src = &D_80754EF8[arg5 * 12];
    dst = &D_80754EF8[arg4 * 12];
    color0 = R1F109660B_COLOR(dst, src, 0, red, green, blue, alpha);
    color1 = R1F109660B_COLOR(dst, src, 3, red, green, blue, alpha);
    color2 = R1F109660B_COLOR(dst, src, 6, red, green, blue, alpha);
    color3 = R1F109660B_COLOR(dst, src, 9, red, green, blue, alpha);

    gdl->words.w0 = 0xE7000000; gdl++->words.w1 = 0;
    gdl->words.w0 = 0xE200001C; gdl++->words.w1 = 0x00552048;
    gdl->words.w0 = 0xFCFFFFFF; gdl++->words.w1 = 0xFFFE793C;
    gdl->words.w0 = 0xE3000A01; gdl++->words.w1 = 0;
    gdl->words.w0 = 0xD9000000; gdl++->words.w1 = 0;
    gdl->words.w0 = 0xD9FFFFFF; gdl++->words.w1 = 0x00200004;
    gdl->words.w0 = 0xDA380007; gdl++->words.w1 = (u32)D_2000080;
    gdl->words.w0 = 0xDA380003; gdl++->words.w1 = (u32)D_2000180;
    gdl->words.w0 = 0xDC080008;
    gdl++->words.w1 = osVirtualToPhysical((u8 *)R1F109660B_PLAYER + (D_807444FC << 4) + 0x250);
    gdl->words.w0 = 0xED000000 | (((s32)((f32)R1F109660B_PLAYER->unk270 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)R1F109660B_PLAYER->unk272 * 4.0f) & 0xFFF);
    gdl++->words.w1 = (((s32)((f32)R1F109660B_PLAYER->unk274 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)R1F109660B_PLAYER->unk276 * 4.0f) & 0xFFF);

    table = &D_80754ED8[arg4];
    offset = *(s16 *)((u8 *)*table + 0x22);
    guTranslateF(mtxA, 0.0f, (f32)-offset, 0.0f);
    func_80612CA0(mtxB, (f32)((s32)(((0x1000 - R1F109660B_PLAYER->unk2CC) & 0xFFF) * 0x168) / 0x1000));
    guMtxCatF(mtxA, mtxB, mtxA);
    guTranslateF(mtxB, 160.0f, (f32)offset + y, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, mtx);

    gdl->words.w0 = 0xDA380003; gdl++->words.w1 = (u32)mtx;
    gdl->words.w0 = 0x01008010; gdl++->words.w1 = osVirtualToPhysical(*table);
    gdl->words.w0 = 0x02100000; gdl++->words.w1 = color0;
    gdl->words.w0 = 0x02100002; gdl++->words.w1 = color0;
    gdl->words.w0 = 0x02100004; gdl++->words.w1 = color1;
    gdl->words.w0 = 0x02100006; gdl++->words.w1 = color1;
    gdl->words.w0 = 0x02100008; gdl++->words.w1 = color2;
    gdl->words.w0 = 0x0210000A; gdl++->words.w1 = color2;
    gdl->words.w0 = 0x0210000C; gdl++->words.w1 = color3;
    gdl->words.w0 = 0x0210000E; gdl++->words.w1 = color3;
    gdl->words.w0 = 0x06000206; gdl++->words.w1 = 0x604;
    gdl->words.w0 = 0x06040608; gdl++->words.w1 = 0x4080A;
    gdl->words.w0 = 0x060A080C; gdl++->words.w1 = 0xA0C0E;
    gdl->words.w0 = 0xE7000000; gdl++->words.w1 = 0;
    return gdl;
}

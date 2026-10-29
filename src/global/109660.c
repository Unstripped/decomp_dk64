#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

typedef struct {
    s8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} FillRectEntry;

extern FillRectEntry D_80750840[];
extern u8 D_80750AB8;
extern u8 D_80750ABC;
extern u8 D_8074450C;

Gfx *func_80704960(Gfx *dl) {
    s32 i;

    i = 0;
    gDPPipeSync(dl++);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
    gDPSetCycleType(dl++, G_CYC_FILL);
    gDPSetFillColor(dl++, 0x10001);
    for (; D_80750840[i].unk0 != -1; i++) {
        if (((D_80750840[i].unk0 == 2) && ((s32)D_807FC928 >= 2) && (D_80750840[i].unk2 & D_80750ABC)) || ((D_807FC928 == D_80750840[i].unk0) && (D_80750AB8 == D_80750840[i].unk1) && (D_80750840[i].unk2 & D_80750ABC))) {
            Gfx *_g = (Gfx *)(dl++);
            _g->words.w0 = 0xF6000000 | (((((D_80750840[i].unk8 + 1) * D_8074450C) - 1) & 0x3FF) << 14) | (((((D_80750840[i].unkA + 1) * D_8074450C) - 1) & 0x3FF) << 2);
            _g->words.w1 = ((((D_80750840[i].unk4 * D_8074450C) & 0x3FF)) << 14) | ((((D_80750840[i].unk6 * D_8074450C) & 0x3FF)) << 2);
        }
    }
    gDPPipeSync(dl++);
    return dl;
}


extern f32 D_807FD968;
extern f32 D_807FD96C;
extern f32 D_807FD970;

void lightSetOverrideColor(f32 arg0, f32 arg1, f32 arg2) {
    D_807FD968 = arg0;
    D_807FD96C = arg1;
    D_807FD970 = arg2;
}

typedef struct {
    u8 unk0[0x90];
    f32 unk90;
    u8 unk94[0xFA - 0x94];
    u8 unkFA;
} LightActorState;

typedef struct {
    u8 unk0[0x174];
    LightActorState *unk174;
} LightActor;

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
} BackgroundPlayerView;

extern LightActor *gCamActor;
extern u8 D_80754EF8[];
extern void *D_80754ED8[];
extern Mtx D_2000080;
extern Gfx D_2000180;
f32 cosApprox(f32);
void matrixMakeRotationZ(f32 (*)[4], f32);
void lightGetColor(f32 *, f32 *, f32 *, s16);

#define BG_BLEND_B(off, mul) \
    ((u32)((mul) * ((f32)D_80754EF8[arg4 * 12 + (off)] + ((f32)(D_80754EF8[arg5 * 12 + (off)] - D_80754EF8[arg4 * 12 + (off)]) * alpha))))
#define BG_BLEND_C(off, mul) \
    ((u32)((mul) * ((f32)D_80754EF8[arg4 * 12 + (off)] + (alpha * (f32)(D_80754EF8[arg5 * 12 + (off)] - D_80754EF8[arg4 * 12 + (off)])))))
#define BG_PLAYER_VIEW ((BackgroundPlayerView *)D_807FC924)

Gfx *gfxDrawBackgroundQuad(Gfx *gdl, void *arg1, f32 angle, void *mtx, u8 arg4, u8 arg5, u8 arg6, s8 arg7, f32 alpha) {
    f32 y;
    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    f32 red;
    f32 green;
    f32 blue;
    void **table;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    s32 offset;
    LightActorState *light;

    y = -(256.0f - (cosApprox(angle) * 300.0f)) - 80.0f;
    light = gCamActor->unk174;
    if ((u32)arg4 == 5) {
        y = (f32)((f64)y + (0.08 * (f64)BG_PLAYER_VIEW->unk2CA - 75.0));
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
    if ((light->unkFA != 0) && (BG_PLAYER_VIEW->unk220 < (light->unk90 + 3.0f))) {
        red = (f32)((f64)red * 0.1);
        green = (f32)((f64)green * 0.1);
        blue = (f32)((f64)blue * 0.3);
    }

    color0 = ((BG_BLEND_C(0, red) & 0xFF) << 24) | ((BG_BLEND_C(1, green) & 0xFF) << 16) | (BG_BLEND_B(2, blue) & 0xFF) << 8 | 0xFF;
    color1 = ((BG_BLEND_C(3, red) & 0xFF) << 24) | ((BG_BLEND_C(4, green) & 0xFF) << 16) | (BG_BLEND_B(5, blue) & 0xFF) << 8 | 0xFF;
    color2 = ((BG_BLEND_C(6, red) & 0xFF) << 24) | ((BG_BLEND_C(7, green) & 0xFF) << 16) | (BG_BLEND_B(8, blue) & 0xFF) << 8 | 0xFF;
    color3 = ((BG_BLEND_C(9, red) & 0xFF) << 24) | ((BG_BLEND_C(10, green) & 0xFF) << 16) | (BG_BLEND_B(11, blue) & 0xFF) << 8 | 0xFF;

    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x552048);
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0xFCFFFFFF; _g->words.w1 = 0xFFFE793C; }
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, 0xFFFFFF);
    gSPSetGeometryMode(gdl++, 0x200004);
    gSPMatrix(gdl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0xDC080008; _g->words.w1 = osVirtualToPhysical((u8 *)BG_PLAYER_VIEW + (D_807444FC << 4) + 0x250); }
    {
        Gfx *_g = (Gfx *)(gdl++);
        _g->words.w0 = ((s32)((f32)BG_PLAYER_VIEW->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)BG_PLAYER_VIEW->unk270 * 4.0f) & 0xFFF) << 12);
        _g->words.w1 = ((s32)((f32)BG_PLAYER_VIEW->unk276 * 4.0f) & 0xFFF) | (((s32)((f32)BG_PLAYER_VIEW->unk274 * 4.0f) & 0xFFF) << 12);
    }

    offset = *(s16 *)((u8 *)D_80754ED8[arg4] + 0x22);
    table = &D_80754ED8[arg4];
    guTranslateF(mtxA, 0.0f, (f32)-offset, 0.0f);
    matrixMakeRotationZ(mtxB, (f32)((s32)(((0x1000 - BG_PLAYER_VIEW->unk2CC) & 0xFFF) * 0x168) / 0x1000));
    guMtxCatF(mtxA, mtxB, mtxA);
    guTranslateF(mtxB, 160.0f, (f32)offset + y, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, mtx);

    gSPMatrix(gdl++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x01008010; _g->words.w1 = osVirtualToPhysical(*table); }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100000; _g->words.w1 = color0; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100002; _g->words.w1 = color0; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100004; _g->words.w1 = color1; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100006; _g->words.w1 = color1; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100008; _g->words.w1 = color2; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x0210000A; _g->words.w1 = color2; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x0210000C; _g->words.w1 = color3; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x0210000E; _g->words.w1 = color3; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x06000206; _g->words.w1 = 0x604; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x06040608; _g->words.w1 = 0x4080A; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x060A080C; _g->words.w1 = 0xA0C0E; }
    gDPPipeSync(gdl++);
    return gdl;
}

typedef struct {
    u8 unk0[0xC];
    s8 unkC;
    s8 unkD;
    s8 unkE;
} ColorBytesView;

void func_80705B14(ColorBytesView *arg0, s8 arg1, s8 arg2, s8 arg3) {
    arg0->unkC = arg1;
    arg0->unkD = arg2;
    arg0->unkE = arg3;
}

extern s32 D_807FD8A0;
extern Mtx D_807FD928;
extern s32 D_807FD978;

void gfxBackgroundReset(void) {
    D_807FD8A0 = 0;
    guOrtho(&D_807FD928, 0.0f, (f32)((f64)((f32)D_80744490 * 16.0f) - 1.0), (f32)((f64)((f32)D_80744494 * 16.0f) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    D_807FD968 = -1.0f;
    D_807FD978 = 0;
}

typedef struct {
    u8 unk0[0x2CA];
    s16 unk2CA;
} PlayerViewCamRoll;

f32 func_80612790(s16);
f32 func_80612794(s16);
void lensFlareAddSource(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32);

void lensFlareAddFromAngle(s16 arg0, s16 arg1, u8 arg2) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s16 sp42;
    s16 sp40;
    s16 sp3E;
    s32 unused;

    sp42 = (s16)(s32)((f64)func_80612794(arg0) * 32767.0);
    sp3E = (s16)(s32)((f64)func_80612790(arg0) * 32767.0);
    sp40 = (s16)(s32)((f64)arg1 - (8.0 * (f64)((PlayerViewCamRoll *)D_807FC924)->unk2CA));
    if (arg2 != 0) {
        if (arg2 == 1) {
            lightGetColor(&sp4C, &sp48, &sp44, *(s16 *)D_807FBB4C->unk12C);
            if ((f64)sp4C > 0.5) {
                lensFlareAddSource((f32)sp42, (f32)sp40, (f32)sp3E, 0.0f, 0.0f, 0.0f, 0.0f, (u32)(sp4C * 255.0f), (u32)(sp48 * 255.0f), (u32)(sp44 * 255.0f));
            }
        }
    } else {
        lensFlareAddSource((f32)sp42, (f32)sp40, (f32)sp3E, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    }
}

extern f32 gBackgroundBlend;
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *playerViewGfxSetup(Gfx *, u8);
extern u8 D_2000100[];

Gfx *gfxDrawSkySprite(Gfx *dl, s16 arg1, s16 arg2, u8 mode) {
    s16 sp76;
    Gfx *g;
    f32 sp6C, sp68;
    u8 alpha;
    f32 sp60, sp5C, sp58;
    s16 b;
    s16 c;

    alpha = 0xFF;
    if (mode == 1) {
        lightGetColor(&sp60, &sp5C, &sp58, *(s16 *)D_807FBB4C->unk12C);
        sp60 = (f32)(1.0 < ((1.0 - (f64)sp5C) / 0.7) ? 1.0 : ((1.0 - (f64)sp5C) / 0.7));
        alpha = (u32)((f64)sp60 * 255.0);
    } else if (mode == 2) {
        sp60 = (f32)((f64)gBackgroundBlend - 0.5);
        if (sp60 < 0.0) {
            sp60 = 0.0f;
        }
        sp60 = (f32)((f64)sp60 * 512.0);
        if (sp60 > 255.0) {
            sp60 = 255.0f;
        }
        alpha = (u32)sp60;
    }
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    sp76 = (s16)(s32)((f64)func_80612794(arg1) * 32767.0);
    c = (s16)(s32)((f64)func_80612790(arg1) * 32767.0);
    b = (s16)(s32)((f64)arg2 - (8.0 * (f64)((PlayerViewCamRoll *)D_807FC924)->unk2CA));
    camProjectToScreen((f32)sp76, (f32)b, (f32)c, &sp6C, &sp68, 0, 4.0f, 0);
    if ((sp6C > -320.0f) && (sp6C < 1600.0f) && (sp68 > -240.0f) && (sp68 < 1200.0f)) {
        g = playerViewGfxSetup(dl, 0);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
        g->words.w0 = 0xDA380007; g->words.w1 = (u32)&D_2000100; dl = func_8068C5A8(g + 1, 0x35, 3, 1, 0x40, 0x40, (s32)sp6C, (s32)sp68, 4.0f, 4.0f, 0, 0.0f);
    }
    return dl;
}

typedef struct {
    f32 v[3][2];
} RectSpan;

void func_807063B8(RectSpan *arg0, u8 *arg1, u8 arg2, f32 arg3) {
    RectSpan temp[4];
    s32 i;
    u8 o;
    f32 f;
    f32 g;

    o = 0;
    for (i = 0; i < *arg1; i++) {
        temp[i] = arg0[i];
    }
    for (i = 0; i < *arg1; i++) {
        if ((temp[i].v[0][arg2] < 0.0f) || (arg3 < temp[i].v[1][arg2])) {
            f = (temp[i].v[0][arg2] < 0.0f) ? temp[i].v[0][arg2] + arg3 : temp[i].v[0][arg2];
            arg0[o].v[0][arg2] = f;
            arg0[o].v[0][arg2 ^ 1] = temp[i].v[0][arg2 ^ 1];
            arg0[o].v[1][arg2] = arg3;
            arg0[o].v[1][arg2 ^ 1] = temp[i].v[1][arg2 ^ 1];
            arg0[o].v[2][arg2] = temp[i].v[2][arg2];
            arg0[o].v[2][arg2 ^ 1] = temp[i].v[2][arg2 ^ 1];
            g = arg0[o].v[2][arg2] + (arg3 - f);
            o++;
            f = (temp[i].v[0][arg2] < 0.0f) ? temp[i].v[1][arg2] : temp[i].v[1][arg2] - arg3;
            arg0[o].v[0][arg2] = 0.0f;
            arg0[o].v[0][arg2 ^ 1] = temp[i].v[0][arg2 ^ 1];
            arg0[o].v[1][arg2] = f;
            arg0[o].v[1][arg2 ^ 1] = temp[i].v[1][arg2 ^ 1];
            arg0[o].v[2][arg2] = g;
            arg0[o].v[2][arg2 ^ 1] = temp[i].v[2][arg2 ^ 1];
            o++;
        } else {
            arg0[o] = temp[i];
            o++;
        }
    }
    *arg1 = o;
}

typedef struct {
    s16 pos;
    u8 r;
    u8 g;
    u8 b;
    u8 pad;
} TintKeyframe;

extern TintKeyframe D_80754F58[];

void gfxGetBackgroundTint(s16 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 idx;
    TintKeyframe *p;
    f32 t;

    switch (D_8076A0A8) {
        case 0xE:
            idx = 0;
            if (arg0 < D_80754F58[1].pos) {
                do {
                    idx++;
                } while (arg0 < D_80754F58[idx + 1].pos);
            }
            p = &D_80754F58[idx];
            t = (f32)(arg0 - D_80754F58[idx + 1].pos) / (f32)(p->pos - D_80754F58[idx + 1].pos);
            *arg1 = D_80754F58[idx + 1].r + (f32)(p->r - D_80754F58[idx + 1].r) * t;
            *arg2 = D_80754F58[idx + 1].g + (f32)(p->g - D_80754F58[idx + 1].g) * t;
            *arg3 = D_80754F58[idx + 1].b + (f32)(p->b - D_80754F58[idx + 1].b) * t;
            return;
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x4A:
        case 0x4B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
        case 0x80:
            *arg1 = 0x3F;
            *arg2 = 0x3F;
            *arg3 = 0x3F;
            return;
        default:
            *arg1 = 0xFF;
            *arg2 = 0xFF;
            *arg3 = 0xFF;
            return;
    }
}

typedef struct {
    u8 unk0[0xE4];
    s16 unkE4;
} CameraRoll;

typedef struct {
    u8 unk0[0x104];
    CameraRoll *unk104;
} CameraLink;

typedef struct {
    u8 unk0[0x80];
    f32 unk80;
    u8 unk84[0xF0];
    CameraLink *unk174;
} CameraActorView;

typedef struct {
    u8 unk0[4];
    CameraActorView *unk4;
} PlayerCamEntry;

extern Mtx D_807FD8A8[];
extern f32 D_80754CE4;
s32 func_8066B0F8(s32, s32, s32, s32);
void func_807063B8(RectSpan *, u8 *, u8, f32);
void gfxGetBackgroundTint(s16, u8 *, u8 *, u8 *);
void func_80702464(Gfx **, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, u8, u8);

Gfx *gfxDrawRotatedTiledBackground(Gfx *arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    f32 lo;
    f32 hi;
    s32 i;
    f32 rect[30];
    u8 count;
    CameraActorView *cam;
    CameraLink *cam2;
    f32 inv;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    u8 r;
    u8 g;
    u8 b;
    f32 scale;

    scale = 5.6f / D_80754CE4;
    cam = ((PlayerCamEntry *)D_807FC924)->unk4;
    cam2 = cam->unk174;
    guScaleF(mtxA, scale, scale, scale);
    guTranslateF(mtxB, -2560.0f, -1920.0f, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    inv = (f32)((0x1000 - cam2->unk104->unkE4) & 0xFFF);
    inv = inv * 0.087890625f;
    guRotateF(mtxB, inv, 0, 0, 1);
    guMtxCatF(mtxA, mtxB, mtxA);
    guTranslateF(mtxB, 2560.0f, 1920.0f, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, &D_807FD8A8[D_807444FC]);
    arg1 = 6.2831855f - arg1;
    arg2 = (arg4 / arg5) * (6.2831855f - arg2);
    if (D_807FD8A0 == 0) {
        D_807FD8A0 = func_8066B0F8(0xE, arg3, 0, 0);
    }
    gSPMatrix(arg0++, &D_807FD8A8[D_807444FC], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(arg0++, &D_807FD928, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(arg0++);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, 3, 29, 0x404240);
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xFC11FE23; _g->words.w1 = 0xFFFFF7FB; }
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_H, 20, 2, 0);
    gfxGetBackgroundTint((s16)(s32)cam->unk80, &r, &g, &b);
    gDPSetPrimColor(arg0++, 0, 0, r, g, b, 0xFF);
    gSPClearGeometryMode(arg0++, 0xFFFFFF);
    gSPSetGeometryMode(arg0++, 0x200004);
    lo = arg1 * 0.15915494f * D_80754CE4;
    hi = arg2 * 0.15915494f * D_80754CE4;
    inv = 1.0f / scale;
    while (lo > 1.0f) {
        lo -= 1.0f;
    }
    while (hi > 1.0f) {
        hi -= 1.0f;
    }
    lo = lo * arg4;
    hi = hi * arg5;
    rect[0] = lo - 460.0f * inv * 0.5f;
    rect[2] = 460.0f * inv * 0.5f + lo;
    count = 1;
    rect[1] = hi - 380.0f * inv * 0.5f;
    rect[2] = 460.0f * inv * 0.5f + lo;
    rect[3] = 380.0f * inv * 0.5f + hi;
    rect[5] = rect[4] = -70.0f * inv;
    func_807063B8((RectSpan *)rect, &count, 0, arg4);
    func_807063B8((RectSpan *)rect, &count, 1, arg5);
    for (i = 0; i < count; i++) {
        func_80702464(&arg0, D_807FD8A0, 0, (u32)arg4, (u32)arg5, 0x20, 0x20, rect[i * 6], rect[i * 6 + 1], rect[i * 6 + 2], rect[i * 6 + 3], rect[i * 6 + 4], rect[i * 6 + 5], 0x10, 0x10);
    }
    return arg0;
}

extern s16 D_80754CE0;
extern s16 D_80754CEC[];
extern s16 D_80754F70;
extern s16 D_80754F74;

Gfx *gfxBuildScrollingBackground(Gfx *dl) {
    s32 x;
    s32 i;
    s32 j;
    s32 n;
    s32 y;
    s32 y2;
    u16 k;
    s16 scroll;

    gSPClearGeometryMode(dl++, 0xFFFFFF);
    gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    { Gfx *_g = (Gfx *)(dl++); _g->words.w0 = 0xFC11FE23; _g->words.w1 = 0xFFFFF3F9; }
    gDPSetTexturePersp(dl++, G_TP_NONE);
    gDPSetTextureFilter(dl++, G_TF_POINT);
    gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPPipeSync(dl++);
    scroll = D_80754F74 + D_80754CE0;
    if (scroll < 0) {
        scroll += 0x200;
    }
    if (scroll >= 0x200) {
        scroll -= 0x200;
    }
    if (D_807FD978 == 0) {
        for (n = 0; n < 8; n++) {
            (&D_807FD978)[n] = func_8066B0F8(0x19, D_80754CEC[n], 0, 0);
        }
    }
    k = 0;
    j = 0x40;
    do {
        i = 0;
        y = (j << 2) - scroll;
        do {
            gDPPipeSync(dl++);
            { s32 tv = (&D_807FD978)[k];
            gDPLoadTextureBlock(dl++, (u32)tv + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD); }
            x = (i << 2) - D_80754F70;
            for (n = 0; n != 4; n++) {
                y2 = y;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                x += 0x200;
            }
            k++;
            i += 0x20;
        } while (i != 0x80);
        j -= 0x40;
    } while (j >= 0);
    /* the stores go through other base symbols: with D_80754F70 spelled directly IDO hoists its address into v1 */
    i = (s16)(D_80754F70 + 4);
    D_80754F74 += 4;
    *(s16 *)((u8 *)D_80754F58 + 0x18) = i;
    if (i >= 0x200) {
        *(s16 *)(D_80754EF8 + 0x78) = 0;
    }
    if (D_80754F74 >= 0x200) {
        D_80754F74 = 0;
    }
    gDPPipeSync(dl++);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    return dl;
}

typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} PlayerViewScissor;

extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;

Gfx *gfxClearScreenSetViewportScissor(Gfx *glist) {
    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
    gDPSetFillColor(glist++, 0x00010001);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_80744498, D_8074449C, D_807444A0, D_807444A4);
    gDPFillRectangle(glist++, D_80744498, D_8074449C, D_807444A0 - 1, D_807444A4 - 1);
    gDPPipeSync(glist++);
    {
        Gfx *_g = (Gfx *)(glist++);
        _g->words.w0 = ((s32)((f32)((PlayerViewScissor *)D_807FC924)->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)((PlayerViewScissor *)D_807FC924)->unk270 * 4.0f) & 0xFFF) << 12);
        _g->words.w1 = ((s32)((f32)((PlayerViewScissor *)D_807FC924)->unk276 * 4.0f) & 0xFFF) | (((s32)((f32)((PlayerViewScissor *)D_807FC924)->unk274 * 4.0f) & 0xFFF) << 12);
    }
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
    return glist;
}

s32 camIsCutsceneActive(void);
void func_8068B830(s16, s16, s16);
void func_8068B8A4(f32);
void func_8068B8FC(void);
extern f32 gScreenFadeRate;
extern u8 D_8076AEE0;
extern s16 D_807FD800;

typedef struct {
    u8 pad0[0x210];
    f32 unk210;
    u8 pad214[4];
    f32 unk218;
    u8 pad21C[0x270 - 0x21C];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 pad278[0x290 - 0x278];
    u16 unk290;
} PlayerViewBackdrop;

#define PLAYER_VIEW_MODE (*(s16 *)&((PlayerViewBackdrop *)D_807FC924)->unk290)

Gfx *gfxDrawMapBackground(Gfx *dl, void *arg1, void *arg2, void *arg3, s32 arg4) {
    f32 x;
    f32 r;
    f32 z;
    gDPPipeSync(dl++);
    if ((gScreenFadeRate != 0.0f) && (D_8076AEE0 == 3)) {
        dl = gfxClearScreenSetViewportScissor(dl);
    }
    switch (D_8076A0A8) {
    case 0x53:
    case 0x9A:
    case 0xC5:
    case 0xC6:
        return dl;
    case 0xE:
        dl = gfxDrawRotatedTiledBackground(dl, *(f32 *)&arg1, *(f32 *)&arg2, 0x2D, 320.0f, 240.0f);
        break;
    case 0x3:
    case 0xB:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x4A:
    case 0x4B:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
    case 0x80:
        dl = gfxDrawRotatedTiledBackground(dl, *(f32 *)&arg1, *(f32 *)&arg2, 0x2E, 320.0f, 240.0f);
        break;
    case 0x26:
        switch (((PlayerViewBackdrop *)D_807FC924)->unk290) {
        case 0:
        case 1:
        case 3:
        case 6:
        case 8:
        case 10:
            dl = gfxClearScreenSetViewportScissor(dl);
            break;
        default:
            lensFlareAddFromAngle(0x3E8, 0x4E20, 0);
            dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 0, 0, 0, -1, 0.0f);
            break;
        }
        break;
    case 0x1E:
        if (((PLAYER_VIEW_MODE != 7) && (PLAYER_VIEW_MODE != 6) && (PLAYER_VIEW_MODE != 8) && (PLAYER_VIEW_MODE != 0)) || (D_807FD800 != 0)) {
            dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 0, 0, ((*(s16 *)D_807FBB4C->unk12C == 9) || (*(s16 *)D_807FBB4C->unk12C == 0xB) || (*(s16 *)D_807FBB4C->unk12C == 3)) ? 1 : 0, 9, 0.0f);
        }
        break;
    case 0x27:
        lensFlareAddFromAngle(0xBB8, 0x2328, 0);
        dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 0, 0, 0, -1, 0.0f);
        break;
    case 0x4:
        dl = gfxClearScreenSetViewportScissor(dl);
        break;
    case 0xB0:
        dl = gfxClearScreenSetViewportScissor(dl);
        break;
    case 0x7:
        switch ((s16)((PlayerViewBackdrop *)D_807FC924)->unk290) {
        case 8:
        case 9:
        case 12:
        case 16:
            dl = gfxClearScreenSetViewportScissor(dl);
            break;
        case 11:
        case 14:
            lensFlareAddFromAngle(0, 0x7530, 1);
            dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 4, 4, 1, -1, 0.0f);
            break;
        default:
            lensFlareAddFromAngle(0, 0x7530, 0);
            dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 4, 4, 0, -1, 0.0f);
            break;
        }
        break;
    case 0x8:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 3, 3, 1, -1, 0.0f), 0, 0x7D00, 0);
        break;
    case 0x30:
        if ((PLAYER_VIEW_MODE >= 0xC) && (PLAYER_VIEW_MODE < 0x12)) {
            dl = gfxClearScreenSetViewportScissor(dl);
        } else {
            lensFlareAddFromAngle(0, 0x5DC0, 1);
            dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 2, 2, 1, -1, 0.0f), 0, 0x5DC0, 1);
        }
        break;
    case 0x37:
        dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 1, 1, 1, -1, 0.0f);
        break;
    case 0x22:
        if (camIsCutsceneActive() != 0) {
            x = ((PlayerViewBackdrop *)D_807FC924)->unk210;
            z = ((PlayerViewBackdrop *)D_807FC924)->unk218;
        } else {
            x = D_807FBB4C->unk7C;
            z = D_807FBB4C->unk84;
        }
        x = sqrtf(((x - 3000.0f) * (x - 3000.0f)) + ((z - 5000.0f) * (z - 5000.0f)));
        if (x < 2500.0f) {
            r = (f32)((f64)((2500.0f - x) / 1000.0f) > 1.0 ? 1.0 : (f64)((2500.0f - x) / 1000.0f));
            func_8068B830((s16)(s32)(2.0f + r), (s16)(s32)(r * 400.0f), (s16)(s32)(r * 30.0f));
            func_8068B8A4((f32)(((f64)r * -0.6) + 1.0));
        } else {
            func_8068B8FC();
            func_8068B8A4(1.0f);
        }
        lensFlareAddFromAngle(0xBB8, 0x4E20, 0);
        dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 5, 6, 1, -1, 0.0f);
        break;
    case 0x99:
    case 0xAC:
        lensFlareAddFromAngle(0xBB8, 0x4E20, 0);
        dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 5, 5, 1, -1, 0.0f);
        break;
    case 0x6F:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 6, 6, 1, -1, 0.0f), 0xC8, 0x4268, 0);
        break;
    case 0x57:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 6, 6, 1, -1, 0.0f), 0x3E8, 0x2EE0, 0);
        break;
    case 0xD5:
        lensFlareAddFromAngle(0x8FC, 0x1388, 0);
        dl = gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 7, 7, 0, -1, 0.0f);
        break;
    case 0xD0:
        gDPSetFillColor(dl++, 0xFFFFFFFF);
        goto fill;
    case 0x36:
        gDPSetFillColor(dl++, 0xFFC1FFC1);
        goto fill;
    case 0x50:
        lensFlareAddFromAngle(0x8FC, 0x1388, 1);
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, arg1, *(f32 *)&arg2, arg3, 7, 6, 0, -1, gBackgroundBlend), 0xC8, 0x2EE0, 2);
        break;
    default:
        gDPSetFillColor(dl++, 0x10001);
    fill:
        gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
        gDPSetCycleType(dl++, G_CYC_FILL);
        {
            Gfx *_g = (Gfx *)(dl++); _g->words.w0 = (((((PlayerViewBackdrop *)((u8 *)D_807FC924 + (s16)arg4 * 0x2F0))->unk276 - 1) & 0x3FF) << 2) | 0xF6000000 | (((((PlayerViewBackdrop *)((u8 *)D_807FC924 + (s16)arg4 * 0x2F0))->unk274 - 1) & 0x3FF) << 14);
            _g->words.w1 = (((((PlayerViewBackdrop *)((u8 *)D_807FC924 + (s16)arg4 * 0x2F0))->unk272) & 0x3FF) << 2) | (((((PlayerViewBackdrop *)((u8 *)D_807FC924 + (s16)arg4 * 0x2F0))->unk270) & 0x3FF) << 14);
        }
        gDPPipeSync(dl++);
        gDPSetCycleType(dl++, G_CYC_1CYCLE);
        break;
    }
    gBackgroundBlend = 0.0f;
    gDPPipeSync(dl++);
    return dl;
}


typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 unk278[0x5C];
    void *unk2D4;
    void *unk2D8;
    u8 unk2DC[0x14];
} PlayerViewWithBg;

Gfx *gfxBuildScrollingBackground(Gfx *);
Gfx *gfxDrawMapBackground(Gfx *, void *, void *, void *, s32);
extern s32 D_807FBB60;
extern s32 D_807552EC;

Gfx *gfxDrawPlayerViewBackground(Gfx *glist, s16 player) {
    s32 draw_black;

    if ((D_807FC928 >= 2) || !(D_807FBB60 & 0x10)) {
        if (D_8076A0A8 == 0x50) {
            glist = gfxBuildScrollingBackground(glist);
        } else {
            draw_black = !(D_807FBB60 & 2);
            if (D_807FC928 >= 2) {
                s32 tmp;
                if (D_807444FC == 0) {}
                if (D_8076A0A8 == 0xBE) {
                    tmp = 0;
                } else {
                    tmp = 1;
                }
                tmp |= (D_807552EC >= 2);
                draw_black |= tmp;
            }
            if (draw_black == 0) {
                return glist;
            }
            gDPPipeSync(glist++);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
            gDPSetFillColor(glist++, 0x00010001);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
            { Gfx *_g = (Gfx *)(glist++); _g->words.w0 = 0xF6000000 | ((((PlayerViewWithBg *)D_807FC924 + player)->unk276 - 1) & 0x3FF) * 4 | ((((PlayerViewWithBg *)D_807FC924 + player)->unk274 - 1) & 0x3FF) << 14; _g->words.w1 = ((((PlayerViewWithBg *)D_807FC924 + player)->unk272 & 0x3FF) * 4) | ((((PlayerViewWithBg *)D_807FC924 + player)->unk270 & 0x3FF) << 14); }
            gDPPipeSync(glist++);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
        }
    } else {
        glist = gfxDrawMapBackground(glist, ((PlayerViewWithBg *)D_807FC924 + player)->unk2D4, ((PlayerViewWithBg *)D_807FC924 + player)->unk2D8,
            (u8 *)((PlayerViewWithBg *)D_807FC924 + player) + (D_807444FC << 6) + 0x108, player);
    }
    return glist;
}


void gfxSetBackgroundBlend(f32 arg0) {
    f64 var_fv0;

    var_fv0 = (f64)arg0;
    if (var_fv0 < 0.0) {
        arg0 = 0.0f;
        var_fv0 = (f64)arg0;
    }
    if (var_fv0 > 1.0) {
        arg0 = 1.0f;
    }
    gBackgroundBlend = arg0;
}

#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 gPlayerInventoryTable[][0x5E];
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gNextGameMode;
extern u8 gGfxBufferIndex;

extern Gfx D_1000118;
extern Mtx D_2000080;

typedef struct {
    u8 unk0[0x250];
    u8 unk250[2][0x10];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 unk278[0x78];
} PlayerViewport;

#define PLAYER_VIEWPORT(i) ((PlayerViewport *)((u8 *)gPlayerSlots + (i) * 0x2F0))

Gfx *playerViewGfxSetup(Gfx *dl, u8 playerIndex) {
    gDPPipeSync(dl++);
    gSPViewport(dl++, osVirtualToPhysical(((PlayerViewport *)gPlayerSlots)[playerIndex].unk250[gGfxBufferIndex]));
    {
        Gfx *_g = (Gfx *)(dl++);
        _g->words.w0 = ((s32)((f32)PLAYER_VIEWPORT(playerIndex)->unk272 * 4.0f) & 0xFFF) | 0xED000000 |
                       (((s32)((f32)PLAYER_VIEWPORT(playerIndex)->unk270 * 4.0f) & 0xFFF) << 12);
        _g->words.w1 = ((s32)((f32)PLAYER_VIEWPORT(playerIndex)->unk276 * 4.0f) & 0xFFF) |
                       (((s32)((f32)PLAYER_VIEWPORT(playerIndex)->unk274 * 4.0f) & 0xFFF) << 12);
    }
    gSPDisplayList(dl++, &D_1000118);
    gDPSetCombineMode(dl++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    return dl;
}

typedef struct {
    u8 unk0[0x1A4];
    u8 unk1A4;
} ActorPlayerState;

Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_806FEF7C(Gfx *arg0, Actor *arg1) {
    arg0 = playerViewGfxSetup(arg0, ((ActorPlayerState *)arg1->customState)->unk1A4);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    return renderRotatedSprite(arg0, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, 0.001f);
}

extern u8 *D_807FD568;
s32 slotQueueGetValue(s32, u8);
s32 projectileFindHomingTarget(s32, void *, Actor *, s32, s32, s32, void *, void *, void *);

Gfx *func_806FF01C(Gfx *arg0, Actor *arg1) {
    u8 player;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    Gfx *dl;

    player = ((ActorPlayerState *)arg1->customState)->unk1A4;
    dl = playerViewGfxSetup(arg0, player);
    if ((D_807FD568[2] & 2) && slotQueueGetValue(3, player) &&
        projectileFindHomingTarget(2, &sp58, arg1, 1, 0, 0, &sp54, &sp50, &sp4C)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

Gfx *func_806FF144(Gfx *arg0) {
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(arg0++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    arg0 = renderRotatedSprite(arg0, 0x3A, 3, 1, 0x40, 0x40, 0x3E, 0x3E, 2.0f, 2.0f, 0, 0.0f);
    arg0 = renderRotatedSprite(arg0, 0x3A, 3, 1, 0x40, 0x40, gScreenWidth - 0x3E, 0x3E, 2.0f, 2.0f, 0x5A, 0.0f);
    arg0 = renderRotatedSprite(arg0, 0x3A, 3, 1, 0x40, 0x40, gScreenWidth - 0x3E, gScreenHeight - 0x3E, 2.0f, 2.0f, 0xB4, 0.0f);
    return renderRotatedSprite(arg0, 0x3A, 3, 1, 0x40, 0x40, 0x3E, gScreenHeight - 0x3E, 2.0f, 2.0f, 0x10E, 0.0f);
}

void func_806FF32C(s32 arg0, Actor *arg1) {
    func_806FF144(playerViewGfxSetup(arg0, ((ActorPlayerState *)arg1->customState)->unk1A4));
}

typedef struct {
    u8 unk0[0x1EC];
    u8 unk1EC;
    u8 unk1ED[3];
    s32 unk1F0;
} ActorHudState;

Gfx *func_806FF358(Gfx *arg0, Actor *arg1) {
    ActorHudState *state;

    state = (ActorHudState *)((Actor **)gPlayerSlots)[1]->customState;
    gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0xFF, 0xFF, 0xC8);
    arg0 = renderRotatedSprite(arg0, 0x39, 3, 1, 0x40, 0x40, 0x50, 0x50, 0.5f, 0.5f, 0, 0.0f);
    arg0 = renderRotatedSprite(arg0, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0x50, 0.5f, 0.5f, 0x5A, 0.0f);
    arg0 = renderRotatedSprite(arg0, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0xA0, 0.5f, 0.5f, 0xB4, 0.0f);
    arg0 = renderRotatedSprite(arg0, 0x39, 3, 1, 0x40, 0x40, 0x50, 0xA0, 0.5f, 0.5f, 0x10E, 0.0f);
    arg0 = renderRotatedSprite(arg0, 0x3B, 3, 1, 0x30, 0x30, 0xA0, 0x78, 1.0f, 1.0f, 0, 0.0f);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    if (!(state->unk1F0 & 0x8000)) {
        if (state->unk1EC == 2) {
            gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0, 0, 0xFF);
            arg0 = renderRotatedSprite(arg0, 0x43, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        } else if (state->unk1EC == 1) {
            gDPSetPrimColor(arg0++, 0, 0, 0, 0xFF, 0, 0xFF);
            arg0 = renderRotatedSprite(arg0, 0x2F, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        }
    }
    return arg0;
}

Gfx *func_806FF628(Gfx *arg0, Actor *arg1) {
    ActorHudState *state;

    state = (ActorHudState *)((Actor **)gPlayerSlots)[1]->customState;
    arg0 = playerViewGfxSetup(arg0, ((ActorPlayerState *)state)->unk1A4);
    if (state->unk1EC == 2) {
        gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0, 0, 0x64);
        arg0 = renderRotatedSprite(arg0, 0x45, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    } else if (state->unk1EC == 1) {
        gDPSetPrimColor(arg0++, 0, 0, 0, 0xFF, 0, 0x64);
        arg0 = renderRotatedSprite(arg0, 0x44, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    }
    return arg0;
}


Gfx *func_806FF75C(Gfx *dl, Actor *arg1) {
    u8 sp77;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;

    sp6C = 2;
    sp77 = ((ActorPlayerState *)arg1->customState)->unk1A4;
    if (gPlayerCount >= 2) {
        sp6C = 3;
    }
    dl = (Gfx *)playerViewGfxSetup((s32)dl, sp77);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0x40, 3.0f, 2.0f, 0, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0x40, 2.0f, 3.0f, 0x5A, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0xB0, 2.0f, 3.0f, 0x10E, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0xB0, 3.0f, 2.0f, 0xB4, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x60, 3.0f, 3.0f, 0, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x60, 3.0f, 3.0f, 0x5A, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x90, 3.0f, 3.0f, 0xB4, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x90, 3.0f, 3.0f, 0x10E, 0.0f);
    if (slotQueueGetValue(3, sp77) && projectileFindHomingTarget((u16)sp6C, &sp70, arg1, 1, 0, 0, &sp68, &sp64, &sp60)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

void func_806FFB2C(s32 arg0, Actor *arg1) {
    f32 sp3C;
    Gfx *dl;

    sp3C = arg1->unk155[0] * 1.4;
    dl = (Gfx *)playerViewGfxSetup(arg0, ((ActorPlayerState *)arg1->customState)->unk1A4);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    renderRotatedSprite(dl, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, sp3C);
}

u16 color5551ToSepia(u16 arg0) {
    u16 sum;
    u8 a;
    f32 f;
    u8 lsb;

    sum = (u8)((arg0 & 0xF800) >> 11) + (u8)((arg0 & 0x7C0) >> 6) + (u8)((arg0 & 0x3E) >> 1);
    lsb = arg0 & 1;
    if (sum >= 0x30) {
        a = (sum - 0x30) / 45.0 * 18.0;
    } else {
        a = 0;
    }
    f = sum / 93.0;
    return ((u8)(28.0f * f + 3.0f) << 11) + ((u8)(19.0f * f + 3.0f) << 6) + (a << 1) + lsb;
}

s16 *func_806FFEAC(s16 *arg0, s32 arg1) {
    s16 i;
    s16 j;

    for (i = 0; i < 0x40; i++) {
        for (j = 0; j < 0x20; j++) {
            *arg0++ = color5551ToSepia(((u16 *)arg1)[j + i * gScreenWidth]);
        }
    }
    return arg0;
}

s32 assetLoad();

void func_806FFF5C(void) {
    assetLoad(0x19, 0x138B, 1, 1);
}

extern void *gFramebuffers[];
s32 heapAlloc(s32);

s32 func_806FFF88(void) {
    s32 sp34;
    s16 var_s0;
    s16 var_s3;
    s32 var_s1;
    s32 var_s2;

    if (gCurrentActor->actorType == 0xD9) {
        func_806FFF5C();
        return;
    }
    sp34 = heapAlloc(0xA000);
    var_s1 = sp34;
    var_s2 = (s32)gFramebuffers[gGfxBufferIndex] + (gScreenWidth * 7 << 4) + 0xA0;
    var_s3 = 0;
    do {
        var_s0 = 0;
        do {
            var_s1 = (s32)func_806FFEAC((s16 *)var_s1, ((var_s0 << 2) << 4) + var_s2);
            var_s0++;
        } while (var_s0 < 5);
        var_s2 += (gScreenWidth << 3) << 4;
        var_s3++;
    } while (var_s3 < 2);
    return sp34;
}

u16 color5551LerpToWhite(f32 arg0, u16 arg1) {
    u8 lsb;

    lsb = arg1 & 1;
    return ((u8)((((arg1 & 0xF800) >> 11) - 0x1F) * arg0 + 31.0f) << 11) + ((u8)((((arg1 & 0x7C0) >> 6) - 0x1F) * arg0 + 31.0f) << 6) + ((u8)((((arg1 & 0x3E) >> 1) - 0x1F) * arg0 + 31.0f) << 1) + lsb;
}

s32 heapAlloc(s32);
void heapFreeDeferred(void *);

void color5551CopyLerpToWhite(u16 *arg0, s16 **arg1, f32 arg2) {
    s16 *var_s0;
    s16 var_s1;

    *arg1 = (s16 *)heapAlloc(0xA000);
    heapFreeDeferred(*arg1);
    var_s0 = *arg1;
    for (var_s1 = 0; var_s1 < 0x5000; var_s1++) {
        *var_s0++ = color5551LerpToWhite(arg2, *arg0++);
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
} LensFlarePoint;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct {
    u8 unk0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
} LensFlareCamView;

extern u8 D_80754BC0;
extern LensFlarePoint D_807FD808[2];
extern f32 D_807FD840[2][3][3];
extern f32 D_807FD848[2][3][3];
void vec3fNormalize(f32 *, Vec3f);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

#define LENS_FLARE_CAM ((LensFlareCamView *)gPlayerSlots)
#define LENS_FLARE_DIST2 ((LENS_FLARE_CAM->unk224 - arg2) * (LENS_FLARE_CAM->unk224 - arg2)) + (((LENS_FLARE_CAM->unk21C - arg0) * (LENS_FLARE_CAM->unk21C - arg0)) + ((LENS_FLARE_CAM->unk220 - arg1) * (LENS_FLARE_CAM->unk220 - arg1)))

void lensFlareAddSource(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9) {
    f32 sp84;
    f32 sp80;
    u8 var_v1;
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    f32 temp_fv1;
    f32 pad0;
    f32 pad1;

    if (D_80754BC0 < 2) {
        var_v1 = 1;
        if (arg6 != 0.0f) {
            sp70.x = arg3 - arg0;
            sp70.y = arg4 - arg1;
            sp70.z = arg5 - arg2;
            vec3fNormalize(&sp58.x, sp70);
            sp70.x = LENS_FLARE_CAM->unk210 - arg0;
            sp70.y = LENS_FLARE_CAM->unk214 - arg1;
            sp70.z = LENS_FLARE_CAM->unk218 - arg2;
            vec3fNormalize(&sp64.x, sp70);
            temp_fv1 = (sp64.x * sp58.x) + (sp64.y * sp58.y) + (sp64.z * sp58.z);
            if ((f64)temp_fv1 < 0.0) {
                temp_fv1 = 0.0f;
            }
            if (temp_fv1 < arg6) {
                var_v1 = 0;
            }
        }
        if (var_v1 != 0) {
            D_807FD848[gGfxBufferIndex][D_80754BC0][0] = sqrtf(LENS_FLARE_DIST2) > 995.0f ? 995.0f : sqrtf(LENS_FLARE_DIST2);
            camProjectToScreen(arg0, arg1, arg2, &sp84, &sp80, 0, 4.0f, 0);
            D_807FD840[gGfxBufferIndex][D_80754BC0][0] = (f32)((f64)sp84 * 0.25);
            D_807FD840[gGfxBufferIndex][D_80754BC0][1] = (f32)((f64)sp80 * 0.25);
            D_807FD808[D_80754BC0].unk0 = arg0;
            D_807FD808[D_80754BC0].unk4 = arg1;
            D_807FD808[D_80754BC0].unk8 = arg2;
            D_807FD808[D_80754BC0].unkC = arg7;
            D_807FD808[D_80754BC0].unkD = arg8;
            D_807FD808[D_80754BC0].unkE = arg9;
            D_80754BC0 += 1;
        }
    }
}

extern u8 D_2000100[];
u32 osVirtualToPhysical(void *);

typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} ViewportBounds;

#define GFX_PKT(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *func_8070068C(Gfx *arg0) {
    GFX_PKT(arg0++, 0xDA380007, &D_2000100);
    GFX_PKT(arg0++, 0xDC080008, osVirtualToPhysical((u8 *)gPlayerSlots + (gGfxBufferIndex * 0x10) + 0x250));
    GFX_PKT(arg0++, ((s32)((f32)((ViewportBounds *)gPlayerSlots)->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)((ViewportBounds *)gPlayerSlots)->unk270 * 4.0f) & 0xFFF) << 12), ((s32)((f32)((ViewportBounds *)gPlayerSlots)->unk276 * 4.0f) & 0xFFF) | (((s32)((f32)((ViewportBounds *)gPlayerSlots)->unk274 * 4.0f) & 0xFFF) << 12));
    return arg0;
}

extern u8 D_807FD838[2][3];
extern u8 D_2000180;
Gfx *lensFlareDrawSource();

Gfx *lensFlareBuildDisplayList(Gfx *arg0) {
    s16 i;

    if (D_80754BC0 != 0) {
        GFX_PKT(arg0++, 0xE7000000, 0);
        arg0 = func_8070068C(arg0);
        GFX_PKT(arg0++, 0xDA380003, (u32)&D_2000180);
        GFX_PKT(arg0++, 0xE7000000, 0);
        GFX_PKT(arg0++, 0xD9000000, 0);
        GFX_PKT(arg0++, 0xD9FFFFFF, 0x200004);
        GFX_PKT(arg0++, 0xE3000A01, 0);
        GFX_PKT(arg0++, 0xE3000C00, 0x80000);
        GFX_PKT(arg0++, 0xE3001201, 0x2000);
        GFX_PKT(arg0++, 0xD7000002, 0x80008000);
        GFX_PKT(arg0++, 0xFC119623, 0xFF2FFFFF);
        GFX_PKT(arg0++, 0xE200001C, 0x504340);
        GFX_PKT(arg0++, 0xE3001801, 0xC0);
        GFX_PKT(arg0++, 0xE3001A01, 0x30);
        for (i = 0; i < D_80754BC0; i++) {
            if (D_807FD838[gGfxBufferIndex ^ 1][i] != 0) {
                arg0 = lensFlareDrawSource(arg0, D_807FD808[i], (u32)(D_807FD838[gGfxBufferIndex ^ 1][i]--));
            }
        }
        GFX_PKT(arg0++, 0xE3001801, 0);
        GFX_PKT(arg0++, 0xE3001A01, 0);
    }
    return arg0;
}

extern s16 *D_8076A0A0;

s16 zbufferDepthToDistance(s16 arg0) {
    s16 lo;
    s16 hi;
    s16 mid;
    s32 ret;
    s32 t;

    lo = 0;
    mid = -1;
    hi = 0x1FE;
    if (arg0 == mid) {
        return 0;
    }
    do {
        mid = (lo + hi) / 2;
        if (arg0 < D_8076A0A0[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
        if (arg0 >= D_8076A0A0[mid] && arg0 < D_8076A0A0[mid + 1]) {
            return mid + 8;
        }
    } while (hi >= lo);
    t = arg0 - 0x7C1B;
    ret = t < 0 ? 0 : t;
    return ret;
}

typedef struct {
    s32 unk0;
    u32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} ZbufferDecodeTable;
typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} ZbufferViewBounds;
extern ZbufferDecodeTable D_80754BC4;
extern s32 gGfxDepthBuffer;
#define ZBUFFER_VIEW ((ZbufferViewBounds *)gPlayerSlots)

s32 zbufferReadDepth(s16 arg0, s16 arg1) {
    ZbufferDecodeTable tileCopy;
    u16 tile;
    u16 new_var;
    s32 *tileInfo;
    u16 *map;
    s32 result;
    ZbufferDecodeTable *tileCopyPtr;

    tileCopy = D_80754BC4;
    tileCopyPtr = &tileCopy;
    map = (u16 *)gGfxDepthBuffer;
    if ((arg0 < ZBUFFER_VIEW->unk270) || (ZBUFFER_VIEW->unk274 < arg0) || (arg1 < ZBUFFER_VIEW->unk272) || (ZBUFFER_VIEW->unk276 < arg1)) return 0xFFFF;
    map = (u16 *)((u8 *)map + (((gScreenWidth * arg1) + arg0) * 2));
    tile = *map;
    tileInfo = (s32 *)tileCopyPtr + (((tile >> 0xD) & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 7) * 2);
    new_var = tile >> 2;
    result = ((new_var & 0x7FF) << tileInfo[0]) + tileInfo[1];
    return ((u32)result >> 3) & 0xFFFF;
}

typedef struct {
    u8 pad0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    s16 unk278;
    s16 unk27A;
    u8 pad27C[4];
    f32 unk280;
} ViewportRectInfo;

#define VIEWPORT_INFO ((ViewportRectInfo *)gPlayerSlots)

extern s32 gGlobalPauseFlags;
extern s16 D_807FD800;
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} ScreenPoint;

#define FLARE_SCREEN_POINTS ((ScreenPoint (*)[3])D_807FD840)

typedef struct {
    u8 pad0[0x2E];
    s8 unk2E;
    u8 pad2F;
    u8 unk30;
    u8 pad31[3];
} PlayerSampleInfo;

extern PlayerSampleInfo gPlayerPadState[];

typedef struct {
    u8 pad0[0x10E];
    s16 unk10E;
    s16 unk110;
    s16 unk112;
    s16 unk114;
    s16 unk116;
    s16 unk118;
    s16 unk11A;
} PlayerStateDepth;

typedef struct {
    u8 unk0;
    u8 pad1[3];
    Actor *unk4;
    u8 pad8[0x2F0 - 8];
} PlayerViewSlot;

typedef struct {
    u8 pad0[0x174];
    PlayerStateDepth *unk174;
} ActorWithPlayerState;

s32 zbufferReadDepth(s16, s16);

void func_80700BF4(void) {
    u8 i;
    PlayerStateDepth *st;
    s16 x;
    s16 y;
    u16 w;
    s32 base;
    PlayerSampleInfo *p;
    s32 r;
    s32 flag;
    s32 bad = 0x7FFF;

    if (D_80754BC0 != 0) {
        do {
            D_80754BC0--;
            if ((f32)VIEWPORT_INFO->unk270 < FLARE_SCREEN_POINTS[gGfxBufferIndex][D_80754BC0].unk0 &&
                FLARE_SCREEN_POINTS[gGfxBufferIndex][D_80754BC0].unk0 < (f32)VIEWPORT_INFO->unk274 &&
                (f32)VIEWPORT_INFO->unk272 < FLARE_SCREEN_POINTS[gGfxBufferIndex][D_80754BC0].unk4 &&
                FLARE_SCREEN_POINTS[gGfxBufferIndex][D_80754BC0].unk4 < (f32)VIEWPORT_INFO->unk276 &&
                !(gGlobalPauseFlags & 2)) {
                if (FLARE_SCREEN_POINTS[gGfxBufferIndex][D_80754BC0].unk8 <
                    (f32)zbufferDepthToDistance(zbufferReadDepth((s16)FLARE_SCREEN_POINTS[gGfxBufferIndex][D_80754BC0].unk0,
                                                     (s16)FLARE_SCREEN_POINTS[gGfxBufferIndex][D_80754BC0].unk4))) {
                    D_807FD838[gGfxBufferIndex][D_80754BC0] = 5;
                }
            }
        } while (D_80754BC0 != 0);
    }
    r = zbufferReadDepth(0xA0, 0xDC);
    flag = bad == r;
    if (flag == 0) {
        r = zbufferReadDepth(0xC, 0x78);
        flag = bad == r;
        if (flag == 0) {
            r = zbufferReadDepth(0x134, 0x78);
            flag = bad == r;
        }
    }
    D_807FD800 = flag;
    D_807FD802 = zbufferDepthToDistance(zbufferReadDepth(D_807FD804, D_807FD806));
    base = 0x28;
    for (i = 0; i < gPlayerCount; i++) {
        if (((PlayerViewSlot *)gPlayerSlots)[i].unk0 != 0) {
            st = ((ActorWithPlayerState *)((PlayerViewSlot *)gPlayerSlots)[i].unk4)->unk174;
            p = &gPlayerPadState[i];
            x = st->unk10E;
            y = st->unk110 - 0x14;
            x += p->unk2E;
            w = (u32)(base + p->unk30 / 1.5);
            st->unk114 = zbufferDepthToDistance(zbufferReadDepth(x, y));
            st->unk116 = zbufferDepthToDistance(zbufferReadDepth(x, st->unk112));
            st->unk118 = zbufferDepthToDistance(zbufferReadDepth(x - w, y));
            st->unk11A = zbufferDepthToDistance(zbufferReadDepth(x + w, y));
        }
    }
}

typedef struct {
    u8 unk0[0x21C];
    Vec3f unk21C;
    u8 unk228[0xC];
    Vec3f unk234;
} CameraAxes;

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    s8 unkC;
    u8 pad[3];
} LensFlareSprite;

extern LensFlareSprite D_80754AF0[];
void vec3fSet(f32 *, f32, f32, f32);
Vec3f vec3fSub(Vec3f, Vec3f);
Vec3f vec3fAdd(Vec3f, Vec3f);
Vec3f vec3fScale(Vec3f, f32);
f32 vec3fDot(Vec3f, Vec3f);
Gfx *gfxFillScreenColor(Gfx *, u8, u8, u8, u8);

/* K&R: `i` is a 4th (unused input) parameter, the loop counter has no frame home; callers pass 3 args. */
/* padX/padY are unused locals that keep the original frame layout. */
Gfx *lensFlareDrawSource(dl, pt, arg2, i)
Gfx *dl;
LensFlarePoint pt;
u8 arg2;
s16 i;
{
    Vec3f sp1B4;
    Vec3f sp1A8;
    Vec3f sp19C;
    Vec3f sp190;
    Vec3f sp184;
    Vec3f sp178;
    Vec3f sp16C;
    Vec3f sp160;
    Vec3f padX[7];
    f32 sp108;
    f32 padY[4];
    f32 spF4;
    f32 spF0;
    f32 fs0;
    f32 fs2;
    f32 fs3;

    spF0 = (f32)((f64)arg2 / 5.0);
    vec3fSet(&sp160.x, pt.unk0, pt.unk4, pt.unk8);
    vec3fSet(&sp178.x, ((CameraAxes *)gPlayerSlots)->unk21C.x, ((CameraAxes *)gPlayerSlots)->unk21C.y, ((CameraAxes *)gPlayerSlots)->unk21C.z);
    vec3fSet(&sp16C.x, ((CameraAxes *)gPlayerSlots)->unk234.x, ((CameraAxes *)gPlayerSlots)->unk234.y, ((CameraAxes *)gPlayerSlots)->unk234.z);
    vec3fNormalize(&sp19C.x, vec3fSub(sp16C, sp178));
    sp1B4 = vec3fAdd(sp178, vec3fScale(sp19C, 5000.0f));
    vec3fNormalize(&sp190.x, vec3fSub(sp160, sp178));
    fs0 = (f64)vec3fDot(sp190, sp19C) < 1e-05 ? 1e-05 : vec3fDot(sp190, sp19C);
    sp160 = vec3fAdd(sp178, vec3fScale(vec3fScale(sp190, 5000.0f), 1.0f / fs0));
    sp1A8 = vec3fSub(sp160, sp1B4);
    if (fs0 < 0.0f) {
        return dl;
    }
    for (i = 0; i < 12; i++) {
        fs3 = ((f64)fs0 < 0.75 ? 0.0 : (f64)fs0 - 0.75) * 4.0;
        fs2 = (f64)fs3 < 0.85 ? 0.85 : (f64)fs3;
        switch (i) {
        case 11:
            sp108 = 640.0f;
            spF4 = 480.0f;
            fs3 = ((f64)fs0 < 0.9 ? 0.0 : (f64)fs0 - 0.9) * 10.0;
            fs2 = (f64)fs3 < 0.85 ? 0.85 : (f64)fs3;
            break;
        case 0:
        case 12:
            fs3 = ((f64)fs0 < 0.25 ? 0.0 : (f64)fs0 - 0.25) * 1.333;
            fs2 = (f64)fs3 < 0.85 ? 0.85 : (f64)fs3;
            camProjectToScreen(sp160.x, sp160.y, sp160.z, &sp108, &spF4, 0, 4.0f, 0);
            break;
        default:
            sp184 = vec3fAdd(sp1B4, vec3fScale(sp1A8, D_80754AF0[i].unk4));
            camProjectToScreen(sp184.x, sp184.y, sp184.z, &sp108, &spF4, 0, 4.0f, 0);
            break;
        }
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, (u32)(((f64)pt.unkC / 255.0) * D_80754AF0[i].unk8 * fs2), (u32)(((f64)pt.unkD / 255.0) * D_80754AF0[i].unk9 * fs2), (u32)(((f64)pt.unkE / 255.0) * D_80754AF0[i].unkA * fs2), (u32)((f32)D_80754AF0[i].unkB * fs3 * spF0));
        dl = renderRotatedSprite(dl, (D_80754AF0[i].unkC + 0x4D) & 0xFFFF, 3, 1, 0x40, 0x40, (s32)sp108, (s32)spF4, D_80754AF0[i].unk0 * 4.0f * spF0, D_80754AF0[i].unk0 * 4.0f * spF0, 0, 0.0f);
    }
    dl->words.w0 = 0xE7000000; dl->words.w1 = 0;
    dl++;
    if ((f64)fs0 > 0.97) {
        dl = gfxFillScreenColor(dl, pt.unkC, pt.unkD, pt.unkE, (u32)(((f64)fs0 - 0.97) * 33.0 * 128.0));
        dl->words.w0 = 0xD7000002; dl->words.w1 = 0x80008000;
        dl[1].words.w0 = 0xFC119623; dl[1].words.w1 = 0xFF2FFFFF;
        dl += 2;
    }
    return dl;
}

extern s8 D_807FD890;

void func_80701C90(void) {
    D_807FD890 = 1;
}

extern Mtx D_2000000;
extern Mtx D_2000200;
Gfx *gfxSetViewportDisplayList(Gfx *);
s32 flagGet(s32, s32);

typedef struct {
    u8 unk0;
    u8 pad1[3];
    Actor *unk4;
    u8 unk8[0x218];
    f32 unk220;
    u8 pad224[0x28];
    f32 unk24C;
    u8 pad250[0x20];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 pad278[0x18];
    s16 unk290;
    u8 pad292[0x56];
    u8 unk2E8;
    u8 pad2E9[7];
} PlayerViewBlock;

typedef struct {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0xE0];
    f32 unk1E8;
} PlayerOverlayState;

typedef struct {
    u8 pad0[0x90];
    f32 unk90;
    u8 pad94[0x66];
    u8 unkFA;
} CameraActorState;

#define PLAYER_VIEW_BLOCK(i) (&((PlayerViewBlock *)gPlayerSlots)[i])
#define OVERLAY_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_80701CA0(Gfx *dl) {
    extern s16 D_80744498;
    extern s16 D_8074449C;
    extern s16 D_807444A0;
    extern s16 D_807444A4;
    PlayerOverlayState *a;
    CameraActorState *b;
    Vtx *vtx;
    u8 *pf;
    f32 v;
    u8 drew;
    u32 fp;
    u8 i;
    u8 force;

    drew = 0;
    fp = 100;
    force = 0;
    /* dead address-taken: keeps the flag memory-resident (no promoted ucvt web) */
    pf = &force;
    switch (gCurrentMap) {
    case 0x2D:
        force = 1;
        break;
    case 0x2B:
    case 0x2E:
    case 0x2F:
    case 0xB3:
        return dl;
    case 0x1E:
        if ((PLAYER_VIEW_BLOCK(0)->unk290 == 9 || PLAYER_VIEW_BLOCK(0)->unk290 == 0xA) && flagGet(0x9C, 0) != 0) {
            return dl;
        }
    default:
        break;
    }
    for (i = 0; i < gPlayerCount; i++) {
        if (PLAYER_VIEW_BLOCK(i)->unk0 != 0) {
            a = (PlayerOverlayState *)PLAYER_VIEW_BLOCK(i)->unk4->customState;
            /* dead check: makes a->unk104 a shared load candidate (temp register order) */
            if (a->unk104 == 0) {}
            b = (CameraActorState *)a->unk104->customState;
            if (force != 0 || (PLAYER_VIEW_BLOCK(i)->unk2E8 != 0 && PLAYER_VIEW_BLOCK(i)->unk220 < PLAYER_VIEW_BLOCK(i)->unk24C + 3.0f)) {
                vtx = (Vtx *)heapAlloc(0x40);
                heapFreeDeferred(vtx);
                vtx[0].v.ob[0] = PLAYER_VIEW_BLOCK(i)->unk270;
                vtx[0].v.ob[1] = PLAYER_VIEW_BLOCK(i)->unk272;
                vtx[0].v.ob[2] = -10;
                vtx[1].v.ob[0] = PLAYER_VIEW_BLOCK(i)->unk274;
                vtx[1].v.ob[1] = PLAYER_VIEW_BLOCK(i)->unk272;
                vtx[1].v.ob[2] = -10;
                vtx[2].v.ob[0] = PLAYER_VIEW_BLOCK(i)->unk274;
                vtx[2].v.ob[1] = PLAYER_VIEW_BLOCK(i)->unk276;
                vtx[2].v.ob[2] = -10;
                vtx[3].v.ob[0] = PLAYER_VIEW_BLOCK(i)->unk270;
                vtx[3].v.ob[1] = PLAYER_VIEW_BLOCK(i)->unk276;
                vtx[3].v.ob[2] = -10;
                gDPPipeSync(dl++);
                dl = gfxSetViewportDisplayList(dl);
                OVERLAY_GFX(dl++, (((s32)((f32)D_80744498 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32)((f32)D_8074449C * 4.0f) & 0xFFF),
                      (((s32)((f32)D_807444A0 * 4.0f) & 0xFFF) << 0xC) | ((s32)((f32)D_807444A4 * 4.0f) & 0xFFF));
                gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
                OVERLAY_GFX(dl++, 0xFCFFFFFF, 0xFFFDF6FB);
                v = PLAYER_VIEW_BLOCK(i)->unk24C - PLAYER_VIEW_BLOCK(i)->unk220;
                switch (gCurrentMap) {
                case 0x1E:
                    v = (f32)((f64)v * 0.07);
                    break;
                case 0x2C:
                    fp = 0x32;
                    v = (f32)((f64)v * 0.07);
                    break;
                case 0x6F:
                    fp = 0x32;
                default:
                    v = (f32)((f64)v * 0.4);
                    break;
                }
                if (v > 80.0f) {
                    v = 80.0f;
                    /* dead use of D_2000180: shifts uopt priorities (s5/s6 pairing) */
                    if (D_2000180 == 0) {}
                }
                if (*(u8 *)&D_807FD890 != 0) {
                    a->unk1E8 = v;
                } else {
                    a->unk1E8 = (f32)((f64)a->unk1E8 + (f64)(v - a->unk1E8) * 0.05);
                    v = (f32)((u32)a->unk1E8 & 0xFF);
                }
                gDPSetPrimColor(dl++, 0, 0, 0, 0, 0x3C, (u32)((f32)fp + v));
                OVERLAY_GFX(dl++, 0xE3000A01, 0);
                gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPVertex(dl++, osVirtualToPhysical(vtx), 4, 0);
                gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
                drew = 1;
                gDPPipeSync(dl++);
            }
            PLAYER_VIEW_BLOCK(i)->unk2E8 = b->unkFA;
            PLAYER_VIEW_BLOCK(i)->unk24C = b->unk90;
        }
    }
    if (drew != 0) {
        gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(dl++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        D_807FD890 = 0;
    } else {
        D_807FD890 = 1;
    }
    return dl;
}

void gfxDrawTexturedTileGrid(Gfx **, s32, s32, u32, s32, u32, u32, f32, f32, f32, f32, f32, f32, u8, u8, u8, void (*)());

void gfxDrawTexturedTileGridDefault(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    gfxDrawTexturedTileGrid(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, 1, 0x10, 0, 0);
}

void gfxDrawTexturedTileGridSimple(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14) {
    gfxDrawTexturedTileGrid(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, 0, 0);
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6[2];
    s16 unk8;
    s16 unkA;
    s8 unkC;
    s8 unkD;
    s8 unkE;
    u8 unkF;
} VtxColorView;


void vtxSetColor(VtxColorView *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);
void vtxSetPosTex(s16 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8 arg5);
void gfxDrawTexturedTileGrid(Gfx **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, u32 arg5, u32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14, u8 arg15, void (*arg16)()) {
    Gfx *dl;
    s32 y;
    VtxColorView *vtx;
    s32 u;
    s32 v;
    u32 ustep;
    s16 xa;
    s32 uls;
    s32 vb;
    s32 vc;
    s32 x;
    s32 lrs;
    f32 xf;
    u32 xs;
    s32 ua;
    u32 ys;
    s32 pad1;
    s32 lrt;
    u32 xe;
    s32 ult;
    u32 ye;
    u8 flag;
    s32 ylo;
    f32 fsc;
    u32 tw;
    f32 twf;
    u32 th;
    u32 vstep;

    ustep = arg13 * arg5;
    dl = *arg0;
    flag = 1;
    vstep = arg13 * arg6;
    xs = (u32)(arg7 * 32.0f);
    xe = (u32)(arg9 * 32.0f);
    ye = (u32)(arg10 * 32.0f);
    th = arg6 << 5;
    tw = arg5 << 5;
    if (arg3 > 0x200) {
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        flag = 0;
    } else {
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    ys = (u32)(arg8 * 32.0f);
    vtx = (VtxColorView *)heapAlloc((((((xe) - (xs)) / tw) + 1) * ((((ye) - (ys)) / th) + 1)) << 6);
    heapFreeDeferred(vtx);
    gDPPipeSync(dl++);
    for (y = ys, v = (s32)((f32)arg13 * arg12); y < ye; y += th, v += vstep) {
        u = ((s32)((f32)arg13 * arg11));
        pad1 = v;  // FAKE: copy of v for the vertex args (spill-chain bit order)
        vc = y;  // FAKE: copy of y for the vertex y positions (spill-chain bit order)
        for (x = xs; x < xe; x += tw, u += ustep) {
            ylo = u;  // FAKE: copy of u for the vertex args (spill-chain bit order)
            uls = ((x >> 5) - 1) > 0 ? ((x >> 5) - 1) : 0;
            xf = (f32)x - 16.0;
            ua = (s16)(u + ustep);
            lrs = (((x >> 5) + arg5) < ((xe >> 5) - 1) ? ((x >> 5) + arg5) : ((xe >> 5) - 1));
            ult = ((y >> 5) - 1) > 0 ? ((y >> 5) - 1) : 0;
            lrt = ((((y >> 5) + arg6) < ((ye >> 5) - 1)) ? ((y >> 5) + arg6) : ((ye >> 5) - 1));
            if (arg14 == 8) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_8b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (arg14 == 0x10) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_16b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (arg14 == 0x20) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_32b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (arg14 == 4) {
                gDPLoadTextureTile_4b(dl++, arg1, arg2, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            }
            fsc = (f32)y - 16.0;  // FAKE: creates the f64 (f32)y - 16.0 chain before (f32)tw (CM emission and spill-slot order)
            twf = (f32)(arg5 << 5);  // FAKE: f32 local keeps `xf + twf` operand order, creates (f32)tw after the f64 chain
            vb = (s16)(v + vstep);
            if (arg15) {
                if (x == xs && arg15 == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(u, v, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, ylo, pad1, xf, (s16)(f32)((f32)vc - 16.0), flag);
            if (arg15) {
                if ((x + (arg5 << 5)) >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16((s16)(u + ustep), v, vtx);
            }
            xa = xf + twf;
            vtxSetPosTex((s16 *)vtx++, ua, pad1, xa, (s16)(f32)((f32)vc - 16.0), flag);
            if (arg15) {
                if ((x + (arg5 << 5)) >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(ua, vb, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, ua, vb, xa, (s16)((f32)(f32)((f32)vc - 16.0) + (f32)th), flag);
            if (arg15) {
                if (x == xs && arg15 == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(u, vb, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, ylo, vb, xf, (s16)((f32)(f32)((f32)vc - 16.0) + (f32)th), flag);
            gSPVertex(dl++, osVirtualToPhysical(vtx - 4), 4, 0);
            gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(dl++);
        }
    }
    *arg0 = dl;
}

extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *gfxFillScreenColor(Gfx *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    if (arg4 != 0) {
        WRITE_GFX(arg0++, 0xD9000000, 0);
        WRITE_GFX(arg0++, 0xD9FFFFFF, 0x200004);
        WRITE_GFX(arg0++, 0xD7000000, 0xFFFFFFFF);
        WRITE_GFX(arg0++, 0xE7000000, 0);
        WRITE_GFX(arg0++, 0xE200001C, 0x504340);
        gDPSetPrimColor(arg0++, 0, 0, arg1, arg2, arg3, arg4);
        WRITE_GFX(arg0++, 0xE3000A01, 0);
        WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFDF6FB);
        WRITE_GFX(arg0++, (((s32)((f32)D_80744498 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32)((f32)D_8074449C * 4.0f) & 0xFFF),
                  (((s32)((f32)D_807444A0 * 4.0f) & 0xFFF) << 0xC) | ((s32)((f32)D_807444A4 * 4.0f) & 0xFFF));
        WRITE_GFX(arg0++, ((D_807444A0 & 0x3FF) << 0xE) | 0xF6000000 | ((D_807444A4 & 0x3FF) * 4),
                  ((D_80744498 & 0x3FF) << 0xE) | ((D_8074449C & 0x3FF) * 4));
    }
    WRITE_GFX(arg0++, 0xE7000000, 0);
    return arg0;
}

s32 randomNonNegative(void);

Gfx *gfxBuildScanlineNoise(Gfx *arg0, s32 arg1) {
    s16 i;
    s16 y;
    s32 r;
    s16 y2;

    gDPPipeSync(arg0++);
    WRITE_GFX(arg0++, 0xE200001C, 0x504340);
    WRITE_GFX(arg0++, 0xD7000000, 0xFFFFFFFF);
    gDPSetPrimColor(arg0++, 0, 0, 0xC8, 0xC8, 0xC8, 0x80);
    WRITE_GFX(arg0++, 0xE3000A01, 0);
    WRITE_GFX(arg0++, 0xFC71FEE3, 0xFFFFF7FB);
    WRITE_GFX(arg0++, 0xED028028, 0x4D4394);
    gDPFillRectangle(arg0++, 10, VIEWPORT_INFO->unk272, 0x135, VIEWPORT_INFO->unk276);
    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(arg0++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    for (i = 0; i < 10; i++) {
        r = randomNonNegative() >> 15;
        y = VIEWPORT_INFO->unk272 + r % (VIEWPORT_INFO->unk276 - VIEWPORT_INFO->unk272);
        r = randomNonNegative() >> 15;
        y2 = r % 10 + 2;
        gDPFillRectangle(arg0++, 10, y, 0x135, y + y2);
    }
    gDPPipeSync(arg0++);
    return arg0;
}

extern s16 D_807444AC;
extern s16 D_807444B0;
s32 hudCanRender();

void viewportShrinkToCenter(u8 arg0) {
    f32 scale;

    scale = (f32)((f64)(f32)(u32)arg0 / 255.0);
    if (hudCanRender() != 0) {
        VIEWPORT_INFO->unk272 = (s32)((f32)D_8074449C + ((f32)((gScreenHeight >> 1) - D_8074449C - 1) * scale));
        VIEWPORT_INFO->unk276 = (s32)((f32)D_807444A4 + ((f32)((gScreenHeight >> 1) - D_807444A4) * scale));
    } else {
        VIEWPORT_INFO->unk272 = (s32)((f32)D_807444AC + ((f32)((gScreenHeight >> 1) - D_807444AC - 1) * scale));
        VIEWPORT_INFO->unk276 = (s32)((f32)D_807444B0 + ((f32)((gScreenHeight >> 1) - D_807444B0) * scale));
    }
    VIEWPORT_INFO->unk270 = (s32)((f32)D_80744498 + ((f32)((gScreenWidth >> 1) - D_80744498 - 1) * scale));
    VIEWPORT_INFO->unk274 = (s32)((f32)D_807444A0 + ((f32)((gScreenWidth >> 1) - D_807444A0) * scale));
    VIEWPORT_INFO->unk27A = VIEWPORT_INFO->unk276 - VIEWPORT_INFO->unk272;
    VIEWPORT_INFO->unk278 = VIEWPORT_INFO->unk274 - VIEWPORT_INFO->unk270;
    VIEWPORT_INFO->unk280 = (f32)VIEWPORT_INFO->unk278 / (f32)VIEWPORT_INFO->unk27A;
}

typedef struct {
    s16 x0, y0;
    u8 pad0[0xB];
    u8 a0;
    s16 x1, y1;
    u8 pad1[0xB];
    u8 a1;
    s16 x2, y2;
    u8 pad2[0xB];
    u8 a2;
    s16 x3, y3;
    u8 pad3[0xB];
    u8 a3;
} ScreenQuadVtx;

extern ScreenQuadVtx D_80754C48[];

Gfx *screenFadeDrawGradient(Gfx *arg0, u8 arg1) {
    gSPDisplayList(arg0++, &D_1000118);
    gSPMatrix(arg0++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
    WRITE_GFX(arg0++, 0xD9000000, 0);
    WRITE_GFX(arg0++, 0xD9FFFFFF, 0x200004);
    WRITE_GFX(arg0++, 0xD7000000, 0xFFFFFFFF);
    gDPPipeSync(arg0++);
    WRITE_GFX(arg0++, 0xE3000A01, 0);
    WRITE_GFX(arg0++, 0xE3000C00, 0);
    WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFE793C);
    D_80754C48[gGfxBufferIndex].a0 = (arg1 * 2 >= 0x100) ? 0xFF : arg1 * 2;
    D_80754C48[gGfxBufferIndex].a1 = arg1;
    D_80754C48[gGfxBufferIndex].a2 = (arg1 * 2 >= 0x100) ? 0xFF : arg1 * 2;
    D_80754C48[gGfxBufferIndex].a3 = arg1;
    D_80754C48[gGfxBufferIndex].x1 = gScreenWidth;
    D_80754C48[gGfxBufferIndex].x2 = gScreenWidth;
    D_80754C48[gGfxBufferIndex].y2 = gScreenHeight;
    D_80754C48[gGfxBufferIndex].y3 = gScreenHeight;
    gSPVertex(arg0++, osVirtualToPhysical(&D_80754C48[gGfxBufferIndex]), 4, 0);
    gSP2Triangles(arg0++, 0, 1, 2, 0, 0, 2, 3, 0);
    gDPPipeSync(arg0++);
    return arg0;
}


extern u8 gHiResScale;
extern u8 D_80754C08[];
void assetFreeBuffer(s32, s32, s32);
f32 sinApprox(f32);
void matrixMakeRotationZ(f32 (*)[4], f32);

Gfx *screenFadeDrawSpinTexture(Gfx *arg0, u8 arg1) {
    Mtx *mtx;
    f32 sp_bc[4][4];
    f32 sp_7c[4][4];
    s32 h;
    f32 s;
    f32 q;

    if (arg1 != 0) {
        h = assetLoad(0xE, 0x5F, 0, 0);
        assetFreeBuffer(h, 0x540, 0x2F);
        mtx = (Mtx *)heapAlloc(0x40);
        heapFreeDeferred(mtx);
        gSPDisplayList(arg0++, &D_1000118);
        gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
        WRITE_GFX(arg0++, 0xFC121624, 0xFF2FFFFF);
        gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
        gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureFilter(arg0++, G_TF_BILERP);
        gDPLoadTextureBlock_4b(arg0++, h + 0x80000000, G_IM_FMT_I, 64, 64, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPMatrix(arg0++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        q = (f32)(sinApprox((f32)((u32)arg1 / 255.0 * 1.57079637050628662 + 3.14159274101257324)) + 1.0);
        s = (f32)(q * 40.0f + 1.4) * (u32)gHiResScale;
        guScaleF(sp_bc, s, s, s);
        matrixMakeRotationZ(sp_7c, (f32)((u32)arg1 / 255.0 * 360.0 * 1.5));
        guMtxCatF(sp_bc, sp_7c, sp_bc);
        guTranslateF(sp_7c, gScreenWidth >> 1, gScreenHeight >> 1, 0);
        guMtxCatF(sp_bc, sp_7c, sp_bc);
        guMtxF2L(sp_bc, mtx);
        gSPMatrix(arg0++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPVertex(arg0++, osVirtualToPhysical(&D_80754C08), 4, 0);
        gSP2Triangles(arg0++, 0, 1, 2, 0, 0, 2, 3, 0);
        gDPPipeSync(arg0++);
    }
    return arg0;
}


extern s16 D_807FD892;

void vtxGradientSetPosition(s16 arg0) {
    D_807FD892 = arg0;
}

extern s8 D_807FD894;
extern s8 D_807FD895;
extern s8 D_807FD896;

void vtxGradientSetColorA(s8 arg0, s8 arg1, s8 arg2) {
    D_807FD894 = arg0;
    D_807FD895 = arg1;
    D_807FD896 = arg2;
}

extern s8 D_807FD897;
extern s8 D_807FD898;
extern s8 D_807FD899;

void vtxGradientSetColorB(s8 arg0, s8 arg1, s8 arg2) {
    D_807FD897 = arg0;
    D_807FD898 = arg1;
    D_807FD899 = arg2;
}


f32 mathSinF(s16);

void vtxSetColor(VtxColorView *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    arg0->unkC = arg1;
    arg0->unkD = arg2;
    arg0->unkE = arg3;
    arg0->unkF = arg4;
    if (arg5 & 0x10) {
        f32 s;
        if (arg5 & 0x40) {
            s = mathSinF((s16)(s32)(((f64)arg4 * 12.05) + 1024.0));
            arg0->unk2 = (s16)(s32)((f32)arg0->unk2 + 64.0f * s);
        } else {
            s = mathSinF((s16)(s32)(((f64)arg4 * 12.05) + 1024.0));
            arg0->unk2 = (s16)(s32)((f32)arg0->unk2 - 64.0f * s);
        }
    }
}

#define AS_U8(sym) (*(u8 *)&(sym))

void vtxSetQuadGradientColors(VtxColorView *arg0, u8 arg1, u8 arg2) {
    s16 lo;
    s16 hi;
    s32 t;

    if (D_807FD892 >= 0x4000) {
        t = D_807FD892 - 0x4200;
        lo = t;
        lo += arg1 * 20;
        hi = t;
        hi += arg1 * 20 + 10;
    } else {
        lo = D_807FD892 - arg1 * 20;
        hi = D_807FD892 - arg1 * 20 - 10;
    }
    if (lo < 0) {
        lo = 0;
    }
    if (lo >= 0x100) {
        lo = 0xFF;
    }
    if (hi < 0) {
        hi = 0;
    }
    if (hi >= 0x100) {
        hi = 0xFF;
    }
    vtxSetColor(arg0++, AS_U8(D_807FD894), AS_U8(D_807FD895), AS_U8(D_807FD896), lo, arg2);
    vtxSetColor(arg0++, AS_U8(D_807FD894), AS_U8(D_807FD895), AS_U8(D_807FD896), hi, arg2);
    vtxSetColor(arg0++, AS_U8(D_807FD897), AS_U8(D_807FD898), AS_U8(D_807FD899), hi, arg2 | 0x40);
    vtxSetColor(arg0, AS_U8(D_807FD897), AS_U8(D_807FD898), AS_U8(D_807FD899), lo, arg2 | 0x40);
}

void vtxSetPosTex(s16 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8 arg5) {
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[2] = 0x3E8;
    arg0[4] = (arg3 << arg5) & 0xFFFF;
    arg0[5] = (arg4 << arg5) & 0xFFFF;
}


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ScreenFadeChannels;

extern f32 gScreenFadeProgress;
extern f32 gScreenFadeRate;
extern s16 gCurrentLevelIndex;
extern u8 gActivePlayerCount;
extern ScreenFadeChannels D_80754CC8;

u8 mapGetWorldIndex(u8);
u8 func_80600454(s16, u8 *);
s32 textTableGetString(s32, s32, s32);
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
void sfxStopChannel(s32, s32);
s32 transitionGetState(void);
void transitionSetState(s32);
void osViBlack(u8);
void transitionSetAudioVolume(f32, s32, void *);

Gfx *screenFadeUpdate(Gfx *arg0, u8 arg1) {
    s32 p0;
    u8 sp5B;
    f32 sp54;
    s32 p1;
    ScreenFadeChannels sp44;
    f32 val;
    f32 x;
    u16 alpha;

    if (gScreenFadeRate != 0.0f) {
        gScreenFadeProgress += gScreenFadeRate * (arg1 == 2 ? 2 : 1);
        if (gScreenFadeProgress < 0.0f) {
            mapGetWorldIndex(gCurrentWorldId);
            if (!(gScreenRenderFlags & 0x20) && func_80600454(gCurrentLevelIndex, &sp5B)) {
                textSpawnMarkerChecked(1, 0, 0x64, textTableGetString(0x23, sp5B, 1), 0, 0x28, 6, 8);
                gScreenRenderFlags |= 0x20;
            }
            sfxStopChannel(0x2B, 0);
            if (transitionGetState() == 2) {
                transitionSetState(0);
            }
            gScreenFadeRate = 0.0f;
            gScreenFadeProgress = 0.0f;
            gScreenRenderFlags &= 0xFFBF;
        } else if (gScreenFadeProgress > 31.0f) {
            if (gScreenRenderFlags & 1) {
                sfxStopChannel(0x2C, 0);
            }
            gScreenFadeRate = 0.0f;
            gScreenFadeProgress = 31.0f;
            osViBlack(1);
            gScreenRenderFlags |= 0xC;
        } else {
            sp54 = gScreenFadeProgress * 0.03225806355f;
            val = gScreenFadeProgress * 255.0f / 28.0f;
            if (val < 0.0f) {
                x = 0.0f;
                alpha = (u32)x;
            } else {
                if (val > 255.0f) {
                    x = 255.0f;
                } else {
                    x = val;
                }
                alpha = (u32)x;
            }
            if (gScreenFadeProgress < gScreenFadeRate * 2 + 31.0f && (gScreenRenderFlags & 4)) {
                gScreenRenderFlags ^= 6;
            }
            if (gScreenFadeProgress > 28.0f && arg1 != 3) {
                arg0 = gfxFillScreenColor(arg0, 0, 0, 0, 0xFF);
            } else {
                switch (arg1) {
                    case 3:
                        if (gActivePlayerCount == 1) {
                            viewportShrinkToCenter(alpha);
                            break;
                        }
                    case 2:
                        arg0 = screenFadeDrawGradient(arg0, alpha);
                        break;
                    case 1:
                        arg0 = screenFadeDrawSpinTexture(arg0, alpha);
                        break;
                    default:
                        arg0 = gfxFillScreenColor(arg0, 0, 0, 0, alpha);
                        break;
                }
            }
            if ((gScreenRenderFlags & 0x41) || !(gScreenRenderFlags & 0x20)) {
                sp44 = D_80754CC8;
                transitionSetAudioVolume(1.0f - sp54, gScreenFadeRate >= 0.0f, &sp44);
            }
        }
    }
    return arg0;
}


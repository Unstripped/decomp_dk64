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
} AaView;

#define AA_VIEW(i) ((AaView *)((u8 *)D_807FC924 + (i) * 0x2F0))

Gfx *func_806FEDB0(Gfx *arg0, u8 arg1) {
    gDPPipeSync(arg0++);
    gSPViewport(arg0++, osVirtualToPhysical(((AaView *)D_807FC924)[arg1].unk250[D_807444FC]));
    {
        Gfx *_g = (Gfx *)(arg0++);
        _g->words.w0 = ((s32)((f32)AA_VIEW(arg1)->unk272 * 4.0f) & 0xFFF) | 0xED000000 |
                       (((s32)((f32)AA_VIEW(arg1)->unk270 * 4.0f) & 0xFFF) << 12);
        _g->words.w1 = ((s32)((f32)AA_VIEW(arg1)->unk276 * 4.0f) & 0xFFF) |
                       (((s32)((f32)AA_VIEW(arg1)->unk274 * 4.0f) & 0xFFF) << 12);
    }
    gSPDisplayList(arg0++, &D_1000118);
    gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(arg0++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    return arg0;
}

typedef struct {
    u8 unk0[0x1A4];
    u8 unk1A4;
} R1F103AB0aState;

Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_806FEF7C(Gfx *arg0, Actor *arg1) {
    arg0 = func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    return func_8068C5A8(arg0, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, 0.001f);
}

extern u8 *D_807FD568;
s32 func_806F8AD4(s32, u8);
s32 func_80690F30(s32, void *, Actor *, s32, s32, s32, void *, void *, void *);

Gfx *func_806FF01C(Gfx *arg0, Actor *arg1) {
    u8 player;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    Gfx *dl;

    player = ((R1F103AB0aState *)arg1->unk174)->unk1A4;
    dl = func_806FEDB0(arg0, player);
    if ((D_807FD568[2] & 2) && func_806F8AD4(3, player) &&
        func_80690F30(2, &sp58, arg1, 1, 0, 0, &sp54, &sp50, &sp4C)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    return func_8068C5A8(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

Gfx *func_806FF144(Gfx *arg0) {
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(arg0++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    arg0 = func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, 0x3E, 0x3E, 2.0f, 2.0f, 0, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, D_80744490 - 0x3E, 0x3E, 2.0f, 2.0f, 0x5A, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, D_80744490 - 0x3E, D_80744494 - 0x3E, 2.0f, 2.0f, 0xB4, 0.0f);
    return func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, 0x3E, D_80744494 - 0x3E, 2.0f, 2.0f, 0x10E, 0.0f);
}

void func_806FF32C(s32 arg0, Actor *arg1) {
    func_806FF144(func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4));
}

typedef struct {
    u8 unk0[0x1EC];
    u8 unk1EC;
    u8 unk1ED[3];
    s32 unk1F0;
} AaFF358State;

Gfx *func_806FF358(Gfx *arg0, Actor *arg1) {
    AaFF358State *state;

    state = (AaFF358State *)((Actor **)D_807FC924)[1]->unk174;
    gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0xFF, 0xFF, 0xC8);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0x50, 0x50, 0.5f, 0.5f, 0, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0x50, 0.5f, 0.5f, 0x5A, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0xA0, 0.5f, 0.5f, 0xB4, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0x50, 0xA0, 0.5f, 0.5f, 0x10E, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x3B, 3, 1, 0x30, 0x30, 0xA0, 0x78, 1.0f, 1.0f, 0, 0.0f);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    if (!(state->unk1F0 & 0x8000)) {
        if (state->unk1EC == 2) {
            gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0, 0, 0xFF);
            arg0 = func_8068C5A8(arg0, 0x43, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        } else if (state->unk1EC == 1) {
            gDPSetPrimColor(arg0++, 0, 0, 0, 0xFF, 0, 0xFF);
            arg0 = func_8068C5A8(arg0, 0x2F, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        }
    }
    return arg0;
}

Gfx *func_806FF628(Gfx *arg0, Actor *arg1) {
    AaFF358State *state;

    state = (AaFF358State *)((Actor **)D_807FC924)[1]->unk174;
    arg0 = func_806FEDB0(arg0, ((R1F103AB0aState *)state)->unk1A4);
    if (state->unk1EC == 2) {
        gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0, 0, 0x64);
        arg0 = func_8068C5A8(arg0, 0x45, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    } else if (state->unk1EC == 1) {
        gDPSetPrimColor(arg0++, 0, 0, 0, 0xFF, 0, 0x64);
        arg0 = func_8068C5A8(arg0, 0x44, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
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
    sp77 = ((R1F103AB0aState *)arg1->unk174)->unk1A4;
    if (D_807FC928 >= 2) {
        sp6C = 3;
    }
    dl = (Gfx *)func_806FEDB0((s32)dl, sp77);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0x40, 3.0f, 2.0f, 0, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0x40, 2.0f, 3.0f, 0x5A, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0xB0, 2.0f, 3.0f, 0x10E, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0xB0, 3.0f, 2.0f, 0xB4, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x60, 3.0f, 3.0f, 0, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x60, 3.0f, 3.0f, 0x5A, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x90, 3.0f, 3.0f, 0xB4, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x90, 3.0f, 3.0f, 0x10E, 0.0f);
    if (func_806F8AD4(3, sp77) && func_80690F30((u16)sp6C, &sp70, arg1, 1, 0, 0, &sp68, &sp64, &sp60)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    return func_8068C5A8(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

void func_806FFB2C(s32 arg0, Actor *arg1) {
    f32 sp3C;
    Gfx *dl;

    sp3C = arg1->unk155[0] * 1.4;
    dl = (Gfx *)func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    func_8068C5A8(dl, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, sp3C);
}

u16 func_806FFC04(u16 arg0) {
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
            *arg0++ = func_806FFC04(((u16 *)arg1)[j + i * D_80744490]);
        }
    }
    return arg0;
}

s32 func_8066B0F8();

void func_806FFF5C(void) {
    func_8066B0F8(0x19, 0x138B, 1, 1);
}

#ifdef NON_MATCHING
extern void *D_80744470[];
s32 func_80610FE8(s32);

s32 func_806FFF88(void) {
    s32 sp34;
    s16 var_s0;
    s16 var_s3;
    s32 var_s1;
    s32 var_s2;

    if (D_807FBB40->unk58 == 0xD9) {
        func_806FFF5C();
        return;
    }
    sp34 = func_80610FE8(0xA000);
    var_s1 = sp34;
    var_s2 = (s32)D_80744470[D_807444FC] + (D_80744490 * 7 << 4) + 0xA0;
    var_s3 = 0;
    do {
        var_s0 = 0;
        do {
            var_s1 = (s32)func_806FFEAC((s16 *)var_s1, (var_s0 << 6) + var_s2);
            var_s0++;
        } while (var_s0 < 5);
        var_s3++;
        var_s2 += D_80744490 << 7;
    } while (var_s3 < 2);
    return sp34;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_806FFF88.s")
#endif

u16 func_80700088(f32 arg0, u16 arg1) {
    u8 lsb;

    lsb = arg1 & 1;
    return ((u8)((((arg1 & 0xF800) >> 11) - 0x1F) * arg0 + 31.0f) << 11) + ((u8)((((arg1 & 0x7C0) >> 6) - 0x1F) * arg0 + 31.0f) << 6) + ((u8)((((arg1 & 0x3E) >> 1) - 0x1F) * arg0 + 31.0f) << 1) + lsb;
}

s32 func_80610FE8(s32);
void heapFreeDeferred(void *);

void func_807002AC(u16 *arg0, s16 **arg1, f32 arg2) {
    s16 *var_s0;
    s16 var_s1;

    *arg1 = (s16 *)func_80610FE8(0xA000);
    heapFreeDeferred(*arg1);
    var_s0 = *arg1;
    for (var_s1 = 0; var_s1 < 0x5000; var_s1++) {
        *var_s0++ = func_80700088(arg2, *arg0++);
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
} Ab2TrailPoint;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Ab2Vec3;

typedef struct {
    u8 unk0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
} Ab2P8070033C;

extern u8 D_80754BC0;
extern Ab2TrailPoint D_807FD808[2];
extern f32 D_807FD840[2][3][3];
extern f32 D_807FD848[2][3][3];
void vec3fNormalize(f32 *, Ab2Vec3);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

#define Ab2PL ((Ab2P8070033C *)D_807FC924)
#define Ab2DIST ((Ab2PL->unk224 - arg2) * (Ab2PL->unk224 - arg2)) + (((Ab2PL->unk21C - arg0) * (Ab2PL->unk21C - arg0)) + ((Ab2PL->unk220 - arg1) * (Ab2PL->unk220 - arg1)))

void func_8070033C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9) {
    f32 sp84;
    f32 sp80;
    u8 var_v1;
    Ab2Vec3 sp70;
    Ab2Vec3 sp64;
    Ab2Vec3 sp58;
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
            sp70.x = Ab2PL->unk210 - arg0;
            sp70.y = Ab2PL->unk214 - arg1;
            sp70.z = Ab2PL->unk218 - arg2;
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
            D_807FD848[D_807444FC][D_80754BC0][0] = sqrtf(Ab2DIST) > 995.0f ? 995.0f : sqrtf(Ab2DIST);
            camProjectToScreen(arg0, arg1, arg2, &sp84, &sp80, 0, 4.0f, 0);
            D_807FD840[D_807444FC][D_80754BC0][0] = (f32)((f64)sp84 * 0.25);
            D_807FD840[D_807444FC][D_80754BC0][1] = (f32)((f64)sp80 * 0.25);
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
} Ab2P8070068C;

#define Ab2GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *func_8070068C(Gfx *arg0) {
    Ab2GFX(arg0++, 0xDA380007, &D_2000100);
    Ab2GFX(arg0++, 0xDC080008, osVirtualToPhysical((u8 *)D_807FC924 + (D_807444FC * 0x10) + 0x250));
    Ab2GFX(arg0++, ((s32)((f32)((Ab2P8070068C *)D_807FC924)->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)((Ab2P8070068C *)D_807FC924)->unk270 * 4.0f) & 0xFFF) << 12), ((s32)((f32)((Ab2P8070068C *)D_807FC924)->unk276 * 4.0f) & 0xFFF) | (((s32)((f32)((Ab2P8070068C *)D_807FC924)->unk274 * 4.0f) & 0xFFF) << 12));
    return arg0;
}

extern u8 D_807FD838[2][3];
extern u8 D_2000180;
Gfx *func_80701098(Gfx *, Ab2TrailPoint, u8);

Gfx *func_807007B8(Gfx *arg0) {
    s16 i;

    if (D_80754BC0 != 0) {
        Ab2GFX(arg0++, 0xE7000000, 0);
        arg0 = func_8070068C(arg0);
        Ab2GFX(arg0++, 0xDA380003, (u32)&D_2000180);
        Ab2GFX(arg0++, 0xE7000000, 0);
        Ab2GFX(arg0++, 0xD9000000, 0);
        Ab2GFX(arg0++, 0xD9FFFFFF, 0x200004);
        Ab2GFX(arg0++, 0xE3000A01, 0);
        Ab2GFX(arg0++, 0xE3000C00, 0x80000);
        Ab2GFX(arg0++, 0xE3001201, 0x2000);
        Ab2GFX(arg0++, 0xD7000002, 0x80008000);
        Ab2GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
        Ab2GFX(arg0++, 0xE200001C, 0x504340);
        Ab2GFX(arg0++, 0xE3001801, 0xC0);
        Ab2GFX(arg0++, 0xE3001A01, 0x30);
        for (i = 0; i < D_80754BC0; i++) {
            if (D_807FD838[D_807444FC ^ 1][i] != 0) {
                arg0 = func_80701098(arg0, D_807FD808[i], D_807FD838[D_807444FC ^ 1][i]--);
            }
        }
        Ab2GFX(arg0++, 0xE3001801, 0);
        Ab2GFX(arg0++, 0xE3001A01, 0);
    }
    return arg0;
}

#ifdef NON_MATCHING
extern s16 *D_8076A0A0;

s16 func_807009F4(s16 arg0) {
    s16 lo;
    s16 hi;
    s16 mid;
    s32 ret;
    s32 t;

    lo = 0;
    hi = 0x1FE;
    if (arg0 == -1) {
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807009F4.s")
#endif

// func_80700AE4 (src/global/103AB0.c): stage 6; 600-second permuter best score 66 uses tile-copy pointer and result temporary but expands frame to 0x60 instead of target 0x58
#ifdef NON_MATCHING
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
} R2F103AB0dTileCopy;
typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} R2F103AB0dPlayerView;
extern R2F103AB0dTileCopy D_80754BC4;
extern s32 D_8076A060;
#define R2F103AB0dPlayer ((R2F103AB0dPlayerView *)D_807FC924)

s32 func_80700AE4(s16 arg0, s16 arg1) {
    R2F103AB0dTileCopy tileCopy;
    u16 tile;
    s32 *tileInfo;
    u16 *map;
    s32 result;
    R2F103AB0dTileCopy *tileCopyPtr;

    tileCopy = D_80754BC4;
    tileCopyPtr = &tileCopy;
    map = (u16 *)D_8076A060;
    if ((arg0 < R2F103AB0dPlayer->unk270) || (R2F103AB0dPlayer->unk274 < arg0) || (arg1 < R2F103AB0dPlayer->unk272) || (R2F103AB0dPlayer->unk276 < arg1)) return 0xFFFF;
    map = (u16 *)((u8 *)map + (((D_80744490 * arg1) + arg0) * 2));
    tile = *map;
    tileInfo = (s32 *)tileCopyPtr + (((tile >> 0xD) & 7) * 2);
    result = (((tile >> 2) & 0x7FF) << tileInfo[0]) + tileInfo[1];
    return ((u32)result >> 3) & 0xFFFF;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80700AE4.s")
#endif

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
} AdViewport;

#define ADVP ((AdViewport *)D_807FC924)

#ifdef NON_MATCHING
extern s32 D_807FBB60;
extern s16 D_807FD800;
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} AdPoint;

#define AD_840 ((AdPoint (*)[3])D_807FD840)

typedef struct {
    u8 pad0[0x2E];
    s8 unk2E;
    u8 pad2F;
    u8 unk30;
    u8 pad31[3];
} AdD610;

extern AdD610 D_807FD610[];

typedef struct {
    u8 pad0[0x10E];
    s16 unk10E;
    s16 unk110;
    s16 unk112;
    s16 unk114;
    s16 unk116;
    s16 unk118;
    s16 unk11A;
} AdPlayerState;

typedef struct {
    u8 unk0;
    u8 pad1[3];
    Actor *unk4;
    u8 pad8[0x2F0 - 8];
} AdView2F0;

typedef struct {
    u8 pad0[0x174];
    AdPlayerState *unk174;
} AdActor174;

s32 func_80700AE4(s16, s16);

void func_80700BF4(void) {
    u8 i;
    AdPlayerState *st;
    s16 x;
    s16 y;
    u16 w;
    s32 base;
    AdD610 *p;
    s32 r;
    s32 flag;
    s32 bad = 0x7FFF;

    if (D_80754BC0 != 0) {
        do {
            D_80754BC0--;
            if ((f32)ADVP->unk270 < AD_840[D_807444FC][D_80754BC0].unk0 &&
                AD_840[D_807444FC][D_80754BC0].unk0 < (f32)ADVP->unk274 &&
                (f32)ADVP->unk272 < AD_840[D_807444FC][D_80754BC0].unk4 &&
                AD_840[D_807444FC][D_80754BC0].unk4 < (f32)ADVP->unk276 &&
                !(D_807FBB60 & 2)) {
                if (AD_840[D_807444FC][D_80754BC0].unk8 <
                    (f32)func_807009F4(func_80700AE4((s16)AD_840[D_807444FC][D_80754BC0].unk0,
                                                     (s16)AD_840[D_807444FC][D_80754BC0].unk4))) {
                    D_807FD838[D_807444FC][D_80754BC0] = 5;
                }
            }
        } while (D_80754BC0 != 0);
    }
    r = func_80700AE4(0xA0, 0xDC);
    flag = bad == r;
    if (flag == 0) {
        r = func_80700AE4(0xC, 0x78);
        flag = bad == r;
        if (flag == 0) {
            r = func_80700AE4(0x134, 0x78);
            flag = bad == r;
        }
    }
    D_807FD800 = flag;
    D_807FD802 = func_807009F4(func_80700AE4(D_807FD804, D_807FD806));
    base = 0x28;
    for (i = 0; i < D_807FC928; i++) {
        if (((AdView2F0 *)D_807FC924)[i].unk0 != 0) {
            st = ((AdActor174 *)((AdView2F0 *)D_807FC924)[i].unk4)->unk174;
            p = &D_807FD610[i];
            x = st->unk10E;
            y = st->unk110;
            x += p->unk2E;
            y -= 0x14;
            w = (u32)(base + p->unk30 / 1.5);
            st->unk114 = func_807009F4(func_80700AE4(x, y));
            st->unk116 = func_807009F4(func_80700AE4(x, st->unk112));
            st->unk118 = func_807009F4(func_80700AE4(x - w, y));
            st->unk11A = func_807009F4(func_80700AE4(x + w, y));
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80700BF4.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80701098.s")

extern s8 D_807FD890;

void func_80701C90(void) {
    D_807FD890 = 1;
}

extern Mtx D_2000000;
extern Mtx D_2000200;
Gfx *func_805FCFD8(Gfx *);
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
} L6Blk;

typedef struct {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0xE0];
    f32 unk1E8;
} L6A;

typedef struct {
    u8 pad0[0x90];
    f32 unk90;
    u8 pad94[0x66];
    u8 unkFA;
} L6B;

#define L6P(i) (&((L6Blk *)D_807FC924)[i])
#define L6GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_80701CA0(Gfx *dl) {
    extern s16 D_80744498;
    extern s16 D_8074449C;
    extern s16 D_807444A0;
    extern s16 D_807444A4;
    L6A *a;
    L6B *b;
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
    switch (D_8076A0A8) {
    case 0x2D:
        force = 1;
        break;
    case 0x2B:
    case 0x2E:
    case 0x2F:
    case 0xB3:
        return dl;
    case 0x1E:
        if ((L6P(0)->unk290 == 9 || L6P(0)->unk290 == 0xA) && flagGet(0x9C, 0) != 0) {
            return dl;
        }
    default:
        break;
    }
    for (i = 0; i < D_807FC928; i++) {
        if (L6P(i)->unk0 != 0) {
            a = (L6A *)L6P(i)->unk4->unk174;
            /* dead check: makes a->unk104 a shared load candidate (temp register order) */
            if (a->unk104 == 0) {}
            b = (L6B *)a->unk104->unk174;
            if (force != 0 || (L6P(i)->unk2E8 != 0 && L6P(i)->unk220 < L6P(i)->unk24C + 3.0f)) {
                vtx = (Vtx *)func_80610FE8(0x40);
                heapFreeDeferred(vtx);
                vtx[0].v.ob[0] = L6P(i)->unk270;
                vtx[0].v.ob[1] = L6P(i)->unk272;
                vtx[0].v.ob[2] = -10;
                vtx[1].v.ob[0] = L6P(i)->unk274;
                vtx[1].v.ob[1] = L6P(i)->unk272;
                vtx[1].v.ob[2] = -10;
                vtx[2].v.ob[0] = L6P(i)->unk274;
                vtx[2].v.ob[1] = L6P(i)->unk276;
                vtx[2].v.ob[2] = -10;
                vtx[3].v.ob[0] = L6P(i)->unk270;
                vtx[3].v.ob[1] = L6P(i)->unk276;
                vtx[3].v.ob[2] = -10;
                gDPPipeSync(dl++);
                dl = func_805FCFD8(dl);
                L6GFX(dl++, (((s32)((f32)D_80744498 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32)((f32)D_8074449C * 4.0f) & 0xFFF),
                      (((s32)((f32)D_807444A0 * 4.0f) & 0xFFF) << 0xC) | ((s32)((f32)D_807444A4 * 4.0f) & 0xFFF));
                gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
                L6GFX(dl++, 0xFCFFFFFF, 0xFFFDF6FB);
                v = L6P(i)->unk24C - L6P(i)->unk220;
                switch (D_8076A0A8) {
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
                L6GFX(dl++, 0xE3000A01, 0);
                gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPVertex(dl++, osVirtualToPhysical(vtx), 4, 0);
                gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
                drew = 1;
                gDPPipeSync(dl++);
            }
            L6P(i)->unk2E8 = b->unkFA;
            L6P(i)->unk24C = b->unk90;
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

void func_807024E0(Gfx **, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_807023E8(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    func_807024E0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, 1, 0x10, 0, 0);
}

void func_80702464(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14) {
    func_807024E0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, 0, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807024E0.s")

extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_80703374(Gfx *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
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

Gfx *func_807035C4(Gfx *arg0, s32 arg1) {
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
    gDPFillRectangle(arg0++, 10, ADVP->unk272, 0x135, ADVP->unk276);
    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(arg0++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    for (i = 0; i < 10; i++) {
        r = randomNonNegative() >> 15;
        y = ADVP->unk272 + r % (ADVP->unk276 - ADVP->unk272);
        r = randomNonNegative() >> 15;
        y2 = r % 10 + 2;
        gDPFillRectangle(arg0++, 10, y, 0x135, y + y2);
    }
    gDPPipeSync(arg0++);
    return arg0;
}

extern s16 D_807444AC;
extern s16 D_807444B0;
s32 func_805FCA64();

void func_80703850(u8 arg0) {
    f32 scale;

    scale = (f32)((f64)(f32)(u32)arg0 / 255.0);
    if (func_805FCA64() != 0) {
        ADVP->unk272 = (s32)((f32)D_8074449C + ((f32)((D_80744494 >> 1) - D_8074449C - 1) * scale));
        ADVP->unk276 = (s32)((f32)D_807444A4 + ((f32)((D_80744494 >> 1) - D_807444A4) * scale));
    } else {
        ADVP->unk272 = (s32)((f32)D_807444AC + ((f32)((D_80744494 >> 1) - D_807444AC - 1) * scale));
        ADVP->unk276 = (s32)((f32)D_807444B0 + ((f32)((D_80744494 >> 1) - D_807444B0) * scale));
    }
    ADVP->unk270 = (s32)((f32)D_80744498 + ((f32)((D_80744490 >> 1) - D_80744498 - 1) * scale));
    ADVP->unk274 = (s32)((f32)D_807444A0 + ((f32)((D_80744490 >> 1) - D_807444A0) * scale));
    ADVP->unk27A = ADVP->unk276 - ADVP->unk272;
    ADVP->unk278 = ADVP->unk274 - ADVP->unk270;
    ADVP->unk280 = (f32)ADVP->unk278 / (f32)ADVP->unk27A;
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
} AeRectVtx;

extern AeRectVtx D_80754C48[];

Gfx *func_80703AB0(Gfx *arg0, u8 arg1) {
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
    D_80754C48[D_807444FC].a0 = (arg1 * 2 >= 0x100) ? 0xFF : arg1 * 2;
    D_80754C48[D_807444FC].a1 = arg1;
    D_80754C48[D_807444FC].a2 = (arg1 * 2 >= 0x100) ? 0xFF : arg1 * 2;
    D_80754C48[D_807444FC].a3 = arg1;
    D_80754C48[D_807444FC].x1 = D_80744490;
    D_80754C48[D_807444FC].x2 = D_80744490;
    D_80754C48[D_807444FC].y2 = D_80744494;
    D_80754C48[D_807444FC].y3 = D_80744494;
    gSPVertex(arg0++, osVirtualToPhysical(&D_80754C48[D_807444FC]), 4, 0);
    gSP2Triangles(arg0++, 0, 1, 2, 0, 0, 2, 3, 0);
    gDPPipeSync(arg0++);
    return arg0;
}


extern u8 D_8074450C;
extern u8 D_80754C08[];
void assetFreeBuffer(s32, s32, s32);
f32 sinApprox(f32);
void matrixMakeRotationZ(f32 (*)[4], f32);

Gfx *func_80703CF8(Gfx *arg0, u8 arg1) {
    Mtx *mtx;
    f32 sp_bc[4][4];
    f32 sp_7c[4][4];
    s32 h;
    f32 s;
    f32 q;

    if (arg1 != 0) {
        h = func_8066B0F8(0xE, 0x5F, 0, 0);
        assetFreeBuffer(h, 0x540, 0x2F);
        mtx = (Mtx *)func_80610FE8(0x40);
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
        s = (f32)(q * 40.0f + 1.4) * (u32)D_8074450C;
        guScaleF(sp_bc, s, s, s);
        matrixMakeRotationZ(sp_7c, (f32)((u32)arg1 / 255.0 * 360.0 * 1.5));
        guMtxCatF(sp_bc, sp_7c, sp_bc);
        guTranslateF(sp_7c, D_80744490 >> 1, D_80744494 >> 1, 0);
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

void func_807040D0(s16 arg0) {
    D_807FD892 = arg0;
}

extern s8 D_807FD894;
extern s8 D_807FD895;
extern s8 D_807FD896;

void func_807040E0(s8 arg0, s8 arg1, s8 arg2) {
    D_807FD894 = arg0;
    D_807FD895 = arg1;
    D_807FD896 = arg2;
}

extern s8 D_807FD897;
extern s8 D_807FD898;
extern s8 D_807FD899;

void func_80704108(s8 arg0, s8 arg1, s8 arg2) {
    D_807FD897 = arg0;
    D_807FD898 = arg1;
    D_807FD899 = arg2;
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
} R1F103AB0cTransformView;

f32 func_80612794(s16);

void func_80704130(R1F103AB0cTransformView *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    arg0->unkC = arg1;
    arg0->unkD = arg2;
    arg0->unkE = arg3;
    arg0->unkF = arg4;
    if (arg5 & 0x10) {
        f32 s;
        if (arg5 & 0x40) {
            s = func_80612794((s16)(s32)(((f64)arg4 * 12.05) + 1024.0));
            arg0->unk2 = (s16)(s32)((f32)arg0->unk2 + 64.0f * s);
        } else {
            s = func_80612794((s16)(s32)(((f64)arg4 * 12.05) + 1024.0));
            arg0->unk2 = (s16)(s32)((f32)arg0->unk2 - 64.0f * s);
        }
    }
}

#define AE_U8(sym) (*(u8 *)&(sym))

void func_80704298(R1F103AB0cTransformView *arg0, u8 arg1, u8 arg2) {
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
    func_80704130(arg0++, AE_U8(D_807FD894), AE_U8(D_807FD895), AE_U8(D_807FD896), lo, arg2);
    func_80704130(arg0++, AE_U8(D_807FD894), AE_U8(D_807FD895), AE_U8(D_807FD896), hi, arg2);
    func_80704130(arg0++, AE_U8(D_807FD897), AE_U8(D_807FD898), AE_U8(D_807FD899), hi, arg2 | 0x40);
    func_80704130(arg0, AE_U8(D_807FD897), AE_U8(D_807FD898), AE_U8(D_807FD899), lo, arg2 | 0x40);
}

void func_80704444(s16 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8 arg5) {
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
} AeTransitionStruct;

extern f32 D_807FD888;
extern f32 D_807FD88C;
extern s16 D_8076A0AA;
extern u8 D_80750AC0;
extern AeTransitionStruct D_80754CC8;

u8 func_805FF000(u8);
u8 func_80600454(s16, u8 *);
s32 func_8070E750(s32, s32, s32);
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
void sfxStopChannel(s32, s32);
s32 func_8070B318(void);
void func_8070B308(s32);
void osViBlack(u8);
void func_8070B324(f32, s32, void *);

Gfx *func_80704484(Gfx *arg0, u8 arg1) {
    s32 p0;
    u8 sp5B;
    f32 sp54;
    s32 p1;
    AeTransitionStruct sp44;
    f32 val;
    f32 x;
    u16 alpha;

    if (D_807FD88C != 0.0f) {
        D_807FD888 += D_807FD88C * (arg1 == 2 ? 2 : 1);
        if (D_807FD888 < 0.0f) {
            func_805FF000(D_8076A0AB);
            if (!(D_8076A0B1 & 0x20) && func_80600454(D_8076A0AA, &sp5B)) {
                textSpawnMarkerChecked(1, 0, 0x64, func_8070E750(0x23, sp5B, 1), 0, 0x28, 6, 8);
                D_8076A0B1 |= 0x20;
            }
            sfxStopChannel(0x2B, 0);
            if (func_8070B318() == 2) {
                func_8070B308(0);
            }
            D_807FD88C = 0.0f;
            D_807FD888 = 0.0f;
            D_8076A0B1 &= 0xFFBF;
        } else if (D_807FD888 > 31.0f) {
            if (D_8076A0B1 & 1) {
                sfxStopChannel(0x2C, 0);
            }
            D_807FD88C = 0.0f;
            D_807FD888 = 31.0f;
            osViBlack(1);
            D_8076A0B1 |= 0xC;
        } else {
            sp54 = D_807FD888 * 0.03225806355f;
            val = D_807FD888 * 255.0f / 28.0f;
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
            if (D_807FD888 < D_807FD88C * 2 + 31.0f && (D_8076A0B1 & 4)) {
                D_8076A0B1 ^= 6;
            }
            if (D_807FD888 > 28.0f && arg1 != 3) {
                arg0 = func_80703374(arg0, 0, 0, 0, 0xFF);
            } else {
                switch (arg1) {
                    case 3:
                        if (D_80750AC0 == 1) {
                            func_80703850(alpha);
                            break;
                        }
                    case 2:
                        arg0 = func_80703AB0(arg0, alpha);
                        break;
                    case 1:
                        arg0 = func_80703CF8(arg0, alpha);
                        break;
                    default:
                        arg0 = func_80703374(arg0, 0, 0, 0, alpha);
                        break;
                }
            }
            if ((D_8076A0B1 & 0x41) || !(D_8076A0B1 & 0x20)) {
                sp44 = D_80754CC8;
                func_8070B324(1.0f - sp54, D_807FD88C >= 0.0f, &sp44);
            }
        }
    }
    return arg0;
}


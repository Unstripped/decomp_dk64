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

void func_8066B0F8();

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80700BF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80701098.s")

extern s8 D_807FD890;

void func_80701C90(void) {
    D_807FD890 = 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80701CA0.s")

void func_807024E0(Gfx **, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_807023E8(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    func_807024E0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, 1, 0x10, 0, 0);
}

void func_80702464(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14) {
    func_807024E0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, 0, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807024E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703374.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807035C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703850.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703AB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703CF8.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704130.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704298.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704444.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704484.s")

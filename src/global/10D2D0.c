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

typedef struct DaF10D2D0_Player {
    u8 pad0[0x2E0];
    u16 unk2E0;
    u8 unk2E2;
    u8 unk2E3;
    u8 unk2E4;
    u8 unk2E5;
} DaF10D2D0_Player;

#define DaF10D2D0_FLAGS(p) (*(u16 *)&(p)->unk2E2)

typedef struct DaF10D2D0_Hud {
    u8 pad0[0x2FB];
    s8 unk2FB;
    u8 unk2FC;
} DaF10D2D0_Hud;

Gfx *func_807085D0();

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern s32 D_8076A064;
extern s32 D_807FBB60;
f32 func_80612794(s16);
s32 func_80714464();
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_807085D0(Gfx *arg0, DaF10D2D0_Hud *arg1, void *arg2, DaF10D2D0_Player *arg3) {
    s16 i;
    s8 pips;
    u32 amp;
    s16 phase;
    s32 raw;
    f32 fs0;
    f32 sp94[22]; /* only [0] [3] [4] [21] are used: a non-volatile array keeps them memory-resident with IDO's reload pattern */
    f32 fs1;
    f32 fs2;
    f32 fs0b;
    f32 wv;
    s16 y;
    s16 x;

    pips = arg1->unk2FB;
    if (pips - 1 > 3) {} /* dead: stops IDO hoisting pips - 1 above the PrimColor select */
    fs0 = (f32)((f64)(u32)arg3->unk2E0 / 65535.0);
    amp = ((arg1->unk2FC * 0x46) - 0x46) & 0xFF;
    if ((D_807FBB60 & 3) || (func_80714464() != 0)) {
        return arg0;
    }
    gSPDisplayList(arg0++, &D_1000118);
    gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gSPMatrix(arg0++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    i = 0;
    if (arg1->unk2FC > 0) {
        sp94[4] = fs0 * 511.0f;
        sp94[3] = (f32)amp;
        sp94[0] = (f32)(s16)(s32)((f64)fs0 * 200.0);
        do {
            raw = (i << 10) + (D_8076A064 * 0xC8);
            phase = raw;
            sp94[21] = (f32)(((f64)func_80612794(phase) * 0.3) + 3.0);
            fs2 = (f32)(((f64)func_80612794((s16)(raw + 0x800)) * 0.3) + 3.0);
            fs0b = (f32)((f64)func_80612794((s16)((raw >> 1) + 0x200)) * 10.0);
            wv = (f32)(((f64)func_80612794(phase) * 0.5 + 0.5) * 30.0);
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)((sp94[4] > 80.0f) ? (f32)80 : sp94[4]));
            arg0 = func_8068C5A8(arg0, 0x5D, 0, (0, 2), 0x30, 0x2A, y = (s32)(((f32)((i * 0x8C) + 0x280) + fs0b) - sp94[3]), x = (s32)(sp94[0] + wv), sp94[21], fs1 = -fs2, 0, 0.0f);
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)((sp94[4] > 255.0f) ? 255.0f : sp94[4]));
            if (pips > 0) {
                arg0 = func_8068C5A8(arg0, ((pips - 1 < 3 ? pips - 1 : 3) + 0x5A) & 0xFFFF, 0, 2, 0x30, 0x2A, y, x, sp94[21], fs1, 0, 0.0f);
            }
            if (pips - 4 < 0) {
                pips = 0;
            } else {
                pips = pips - 4;
            }
            i += 1;
        } while (i < arg1->unk2FC);
    }
    gDPPipeSync(arg0++);
    return arg0;
}


typedef struct R1F10D2D0_InitData {
    f32 unk0;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} R1F10D2D0_InitData;

extern s32 D_807FBB64;
extern s32 func_807142D8();

void func_80708BB8(R1F10D2D0_InitData *arg0) {
    if (D_807FBB64 & 0x800) {
        arg0->unk6 = 0x20;
    } else {
        arg0->unk6 = 1;
    }
    if (func_807142D8() != 0) {
        arg0->unk6 = 0x20;
    }
    arg0->unkA = 0;
    arg0->unk8 = 0;
    arg0->unk4 = 0;
    arg0->unk0 = 4.0f;
}



typedef struct NmF10D2D0_PlayerState {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
    u8 unk2E5;
    u8 unk2E6;
    u8 pad2E7[9];
    s8 unk2F0[0xB];
    s8 unk2FB;
    u8 unk2FC;
    s8 unk2FD;
} NmF10D2D0_PlayerState;

void func_80026B0C(s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
s32 func_805FCA64(void);
s32 func_8071432C(void);
s32 func_8071441C(void);
s32 func_8070943C(void);

void func_80708C24(s32 arg0, NmF10D2D0_PlayerState *arg1, NmF10D2D0_PlayerState *arg2, s32 arg3) {
    u8 state;
    s32 limit;

    state = arg1->unk2E2;
    if (state & 0x10) {
        arg1->unk2E2 ^= 0x10;
        if (arg2->unk2FD > 0) {
            limit = func_8070943C();
            arg3 = arg2->unk2FB + arg2->unk2FD;
            limit = arg2->unk2FC * limit;
            if (arg3 < limit) {
                arg2->unk2FB = arg3;
            } else {
                arg2->unk2FB = limit;
            }
        } else if (arg2->unk2FD < 0) {
            if ((func_8071432C() != 0) || (func_8071441C() != 0)) {
                arg2->unk2FB += arg2->unk2FD;
            }
            if (arg2->unk2FB <= 0) {
                arg2->unk2FB = 0;
                arg1->unk2E6 = 0xC;
                if ((s32)D_807FC928 >= 2) {
                    func_80026B0C(arg0);
                }
            } else {
                func_80609140(0x24B, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
        arg2->unk2FD = 0;
    }
    if ((!(D_807FBB60 & 2) && (func_805FCA64() != 0)) || (state & 0x80)) {
        arg1->unk2E5--;
        if (!arg1->unk2E5) {
            arg1->unk2E5 = 0x11;
            arg1->unk2E4 = 3;
        }
    }
}

s32 func_806C8DE0(s32);
f32 sinApprox(f32);

s32 func_80708DA4(arg0, arg1, arg2)
s32 arg0;
s16 arg1;
DaF10D2D0_Player *arg2;
{
    s32 idx;
    f32 angle;
    u8 *hud;
    u8 *elem;
    u8 mode;
    u8 bits;
    s32 single;

    hud = (u8 *)(arg1 * 0x306 + (s32)D_807FC950);
    idx = func_806C8DE0(arg1);
    elem = (u8 *)((s32)hud + idx * 0x5E);
    mode = arg2->unk2E4;
    bits = arg2->unk2E3;
    single = D_807FC928 == 1;
    if (single == 0) {
        mode = 0;
    }
    if (single == 0) {
        func_80708C24(arg1, (NmF10D2D0_PlayerState *)arg2, (NmF10D2D0_PlayerState *)hud, (s32)elem);
        DaF10D2D0_FLAGS(arg2) &= 0xFFEA;
        bits = arg2->unk2E3;
    }
    if (bits & 0x10) {
        switch (mode) {
        case 2:
            arg2->unk2E5 = 50;
            break;
        case 3:
            arg2->unk2E5 = 18.0 - arg2->unk2E5;
            arg2->unk2E4 = 1;
            break;
        }
    }
    if (bits & 1) {
        DaF10D2D0_FLAGS(arg2) ^= 1;
        switch (mode) {
        case 0:
            arg2->unk2E5 = 18;
            arg2->unk2E4 = 1;
            break;
        case 1:
            break;
        case 3:
            arg2->unk2E5 = 18.0 - arg2->unk2E5;
            arg2->unk2E4 = 1;
            break;
        }
    } else if (bits & 4) {
        arg2->unk2E5 = 1;
        DaF10D2D0_FLAGS(arg2) ^= 4;
        arg2->unk2E4 = 2;
        DaF10D2D0_FLAGS(arg2) &= 8;
    } else {
        switch (mode) {
        case 1:
            angle = arg2->unk2E5 / 18.0 * 1.5707963705062866 + 1.5707963705062866;
            arg2->unk2E0 = sinApprox(angle) * 65535.0;
            if (arg2->unk2E5-- == 0) {
                arg2->unk2E4 = 2;
                arg2->unk2E5 = 50;
            }
            break;
        case 2:
            func_80708C24(arg1, (NmF10D2D0_PlayerState *)arg2, (NmF10D2D0_PlayerState *)hud, (s32)elem);
            break;
        case 3:
            angle = 1.5707963705062866 - arg2->unk2E5 / 18.0 * 1.5707963705062866 + 1.5707963705062866;
            arg2->unk2E0 = sinApprox(angle) * 65535.0;
            if (arg2->unk2E5-- == 0) {
                arg2->unk2E4 = 0;
            }
            break;
        }
    }
    if (func_805FCA64() != 0 || (bits & 0x80)) {
        if (arg2->unk2E4 != 0 || DaF10D2D0_FLAGS(arg2) != 0) {
            arg0 = (s32)func_807085D0((Gfx *)arg0, (DaF10D2D0_Hud *)hud, elem, arg2);
        }
    }
    return arg0;
}


typedef struct NmF10D2D0b_PlayerState {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
} NmF10D2D0b_PlayerState;

extern s8 D_80744504;
s32 func_80708DA4();

s32 func_80709344(s32 arg0) {
    s16 var_s0;
    s32 temp_lo;
    u16 temp_v1;
    s32 temp_v0;

    arg0 = arg0;
    var_s0 = 0;
    if ((s32)D_807FC928 > 0) {
        do {
            temp_lo = var_s0 * 0x2F0;
            temp_v0 = (s32)D_807FC924 + temp_lo;
            if (((NmF10D2D0b_PlayerState *)temp_v0)->unk0 != 0) {
                temp_v1 = ((NmF10D2D0b_PlayerState *)temp_v0)->unk2E2;
                if (!(temp_v1 & 0x20) && (((((NmF10D2D0b_PlayerState *)temp_v0)->unk2E4 != 0 || temp_v1 != 0) &&
                                           D_80744504 == 0) ||
                                          temp_v1 & 0x10)) {
                    arg0 = func_80708DA4(arg0, (s16)(var_s0 + 0), (temp_lo ^ 0) + (s32)D_807FC924, (s32)D_807FC924);
                }
            }
            var_s0 += 1;
        } while (var_s0 < (s32)D_807FC928);
    }
    return arg0;
}


s32 func_8070943C(void) {
    s32 ret;

    ret = 4;
    return ((s32) D_807FC928 >= 2) ? 0xA : ret;
}



void func_80709464(u8 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 product_factor;

    temp_v0 = func_8070943C();
    temp_v1 = (arg0 * 0x306) + (s32)D_807FC950;
    *(u8 *)(temp_v1 + 0x2FD) = 0;
    *(s8 *)(temp_v1 + 0x2FB) = (s8)(*(u8 *)(temp_v1 + 0x2FC) * (product_factor = temp_v0));
}



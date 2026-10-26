#include "common.h"

extern s8 D_807F5D84;

void func_80629190(void) {
    D_807F5D84 = 0;
}

u8 func_8062919C(void) {
    return (u8)D_807F5D84;
}

extern u8 D_80747B20;

u8 func_806291A8(void) {
    return D_80747B20;
}

extern s32 D_80744470[];
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444FC;
extern u8 D_807F5D85;
extern s16 D_807F5D86;
extern s16 D_807F5D88;
extern f32 D_807F5D8C;
extern f32 D_807F5D94;
extern u16 *D_807F5D80;
void *func_80610FE8(s32);
void func_8062A348(void);
void func_8070A848(void *, s32);

void func_806291B4(arg0)
u8 arg0;
{
    s32 sel = arg0;

    if ((D_807F5D84 == 0) || (arg0 == 7)) {
        if (D_807F5D84 == 0) {
            D_807F5D80 = func_80610FE8(D_80744490 * D_80744494 * 2);
        }
        func_8070A848(D_807F5D80, D_80744470[D_807444FC]);
        D_807F5D84 = 1;
        D_80747B20 = 5;
        switch (sel) {
            case 1:
                D_807F5D86 = 0xFF;
                break;
            case 2:
                D_807F5D86 = 0;
                break;
            case 0:
                D_807F5D86 = 0x136;
                break;
            case 3:
                D_807F5D86 = 0xA0;
                D_807F5D88 = 0xA0;
                break;
            case 4:
            case 5:
                D_807F5D8C = -5.0f;
                break;
            case 6:
                D_807F5D94 = 0.0f;
                break;
            case 7:
                func_8062A348();
                break;
        }
        D_807F5D85 = sel;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2DE90/func_80629300.s")

f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void func_80704130(s32, s32, s32, s32, s32, s32);

void func_8062A130(s32 arg0, s32 arg1, s32 arg2) {
    f32 ang;
    s16 alpha;

    ang = mathAngleBetweenPointsDeg(0xA0, 0x78, arg0, arg1);
    if (D_807F5D94 < 20.0) {
        func_80704130(arg2, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        return;
    }
    alpha = 0;
    if (D_807F5D94 < ang) {
        f64 diff = ang - D_807F5D94;
        if (diff < 25.0) {
            alpha = (s16)((diff / 25.0) * 255.0);
        } else {
            alpha = 0xFF;
        }
    } else {
        alpha = 0;
    }
    func_80704130(arg2, 0xFF, 0xFF, 0xFF, alpha, 0);
}

extern f32 D_807F5D90;
f32 sqrtf(f32);

void func_8062A274(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_8062A228(s32 arg0, s32 arg1, s32 arg2) {
    func_8062A274(arg0, arg1, arg2, 0, 0);
}

void func_8062A24C(s32 arg0, s32 arg1, s32 arg2) {
    func_8062A274(arg0, arg1, arg2, 0xA0, 0x78);
}

void func_8062A274(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 dx;
    s32 dy;
    f32 dist;
    s16 alpha;

    dx = arg0 - arg3;
    dy = arg1 - arg4;
    dist = sqrtf(dx * dx + dy * dy);
    if (dist < D_807F5D8C) {
        alpha = 0;
    } else if (D_807F5D90 < dist) {
        alpha = 0xFF;
    } else {
        alpha = (s16)(((dist - D_807F5D8C) / (D_807F5D90 - D_807F5D8C)) * 255.0f);
    }
    func_80704130(arg2, 0xFF, 0xFF, 0xFF, alpha, 0);
}

extern s32 D_80747B28;
extern u8 *D_80747B2C;
extern s32 D_80747B38;

void func_8062A348(void) {
    s32 i;

    D_80747B2C = func_80610FE8((D_80747B28 << 5) + 1);
    for (i = 0; i <= (D_80747B28 << 5); i++) {
        D_80747B2C[i] = i / D_80747B28;
    }
    D_80747B38 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2DE90/func_8062A3F0.s")

extern u8 D_80747B40;
extern u8 *D_807F5DD8;
void *_memset(u8 *, s32, u32);
void heapFreeDeferred(void *);

void func_8062A774(void) {
    if (D_80747B40 == 0) {
        D_807F5DD8 = func_80610FE8(0x25800);
        _memset(D_807F5DD8, 0, 0x25800);
        D_80747B40 = 1;
    }
}

void func_8062A7D0(void) {
    if (D_80747B40 != 0) {
        heapFreeDeferred(D_807F5DD8);
        D_80747B40 = 0;
    }
}

extern f32 D_80747B44;
extern f32 D_80747B48;
extern f32 D_80747B4C;
extern f32 D_80747B50;

void func_8062A808(s32 arg0, s32 arg1) {
    D_80747B4C = 2.0f;
    D_80747B50 = 2.0f;
    D_80747B44 = arg0;
    D_80747B48 = arg1;
}

s32 func_8062A844(s32 arg0) {
    return arg0;
}

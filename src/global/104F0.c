#include "common.h"
#include "actor.h"

extern s16 D_807ECEA0[];
extern u8 D_807467C8;

extern s32 func_80631C20(s32);

void func_8060B7F0(void) {
    s32 temp_v0;
    s32 var_s0;

    D_807ECEA0[0] = 0;
    var_s0 = 0;
    do {
        temp_v0 = func_80631C20(var_s0 & 0xFF);
        var_s0 += 1;
        D_807ECEA0[0] += temp_v0;
    } while (var_s0 != 8);
}

extern s8 D_80746834;
extern OSMesgQueue D_807EE0D0;

void func_8060B84C(f32 arg0) {
    OSTimer timer;
    u64 padding;
    OSMesg timerMsg;
    OSMesg received;
    u64 duration;

    duration = (u64)(arg0 * 1000.0f);
    duration = (duration * 3000) / 64;
    osSetTimer(&timer, duration, 0, &D_807EE0D0, timerMsg);
    D_80746834 = 1;
    osRecvMesg(&D_807EE0D0, &received, 1);
    D_80746834 = 0;
}

extern s8 D_80744460;
extern void (*D_807467D0[])(void);
extern OSMesgQueue D_807F02B8;

void func_8060B8F8(s32 arg0) {
    if (osGetThreadId(NULL) == 9) {
        D_807467D0[arg0]();
        return;
    }
    if (D_80744460 == 0) {
        osSendMesg(&D_807F02B8, (void *)arg0, 0);
    }
}



#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060B968.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060B9D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BA14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BB18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BBE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BCA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BEA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BF84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C2C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C340.s")

extern s32 _strchr(u8 *);
extern u8 *D_80746800;

s32 func_8060C430(s32 arg0, u32 arg1, s32 arg2) {
    f32 temp_ft4;
    f32 temp_ft4_2;
    f32 var_fv0;
    f32 var_fv0_2;

    switch (arg0) {
    case 17:
        var_fv0 = 5.0f;
        if (arg2 != 0) {
            var_fv0 = 1.0f / var_fv0;
        }
        temp_ft4 = (f32) arg1 * var_fv0;
        arg1 = (u32) temp_ft4;
        break;
    case 21:
        var_fv0_2 = 50.0f;
        if (arg2 != 0) {
            var_fv0_2 = 1.0f / var_fv0_2;
        }
        temp_ft4_2 = (f32) arg1 * var_fv0_2;
        arg1 = (u32) temp_ft4_2;
        break;
    case 18:
    case 19:
    case 20:
    case 22:
    case 23:
    case 24:
    case 26:
    case 27:
    case 28:
        if (arg2 != 0) {
            arg1 = _strchr(D_80746800) - (s32) D_80746800;
        } else {
            arg1 = D_80746800[arg1];
        }
        break;
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C648.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C6B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C724.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C8AC.s")

extern void flagsClearAllBank1(void);
extern void func_8060C8AC(s32);

void func_8060CB74(void) {
    flagsClearAllBank1();
    func_8060C8AC(0xFF);
}

extern void func_8060B8F8(s32);

void func_8060CB9C(void) {
    func_8060B8F8(3);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060CBBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D0A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D14C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D2C8.s")

extern void func_8060D2C8(s32);

void func_8060D768(void) {
    func_8060D2C8(0);
}

void func_8060D788(void) {
    func_8060D2C8(1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D7A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DC3C.s")

void func_8060DEA8(void) {
    func_8060B8F8(2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DEC8.s")

void func_8060E128(void *arg0) {
    OSMesg msg;

    while (TRUE) {
        osRecvMesg(&D_807F02B8, &msg, 1);
        D_807467D0[(s32)msg]();
    }
}

extern OSMesgQueue D_807ECCF0;
extern s32 D_807EDEAC;
extern OSMesg D_807EE0B0[];
extern OSThread D_807EE0E8;
extern u64 D_807F0298[];
extern s8 D_807467E0;

void func_8060E1A8(void) {
    func_8060B7F0();
    D_807EDEAC = osEepromProbe(&D_807ECCF0);
    osCreateMesgQueue(&D_807EE0D0, D_807EE0B0, 8);
    osCreateMesgQueue(&D_807F02B8, D_807F0298, 8);
    osCreateThread(&D_807EE0E8, 9, func_8060E128, NULL, D_807F0298, 0xC);
    osStartThread(&D_807EE0E8);
    D_807467E0 = 1;
    func_8060B8F8(0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E25C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E3B0.s")

extern s32 func_8060B9D0(u8);
extern void func_8060BB18(u8, s32, s32);
extern void func_8060C340();
extern s32 func_8071432C(void);

void func_8060E430(u16 arg0, u8 arg1, u8 arg2) {
    u16 value;
    u8 unk;

    if (func_8071432C() != 0) {
        func_8060C340(&value, &unk, 0, 0, arg2, func_8060B9D0(D_807467C8));
        func_8060BB18(arg1, (value + arg0) & 0xFFFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757020.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757024.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757064.s")

#include "common.h"
#include "actor.h"

extern s16 D_807ECEA0[];
extern u8 D_807467C8;

extern s32 modelTypeCountGet(s32);

void func_8060B7F0(void) {
    s32 temp_v0;
    s32 var_s0;

    D_807ECEA0[0] = 0;
    var_s0 = 0;
    do {
        temp_v0 = modelTypeCountGet(var_s0 & 0xFF);
        var_s0 += 1;
        D_807ECEA0[0] += temp_v0;
    } while (var_s0 != 8);
}

extern s8 D_80746834;
extern OSMesgQueue D_807EE0D0;

void sleepMilliseconds(f32 arg0) {
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

void eepromDispatchCommand(s32 arg0) {
    if (osGetThreadId(NULL) == 9) {
        D_807467D0[arg0]();
        return;
    }
    if (D_80744460 == 0) {
        osSendMesg(&D_807F02B8, (void *)arg0, 0);
    }
}




#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060B968.s")

extern u8 D_807EDEA8[];

s32 func_8060B9D0(s32 arg0) {
    s32 temp_t8;
    s32 var_v1;

    if (D_807EDEA8) {
    }
    var_v1 = 0;
loop_1:
    if (arg0 == D_807EDEA8[var_v1]) {
        return var_v1;
    }
    temp_t8 = (var_v1 = (var_v1 + 1) & 0xFF);
    if (temp_t8 >= 4) {
        return 0;
    }
    goto loop_1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BA14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BB18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BBE0.s")

void func_8060BCA0(s32 arg0, u8 arg1, u8 arg2, u16 *arg3, u8 *arg4) {
    *arg3 = D_807ECEA0[0] + *arg3 + (arg1 * 0xA1) + 0x320;
    *arg4 = 0;
    switch (arg0) {
    case 11:
        if (*arg4 == 0) *arg4 = 1;
        *arg3 += 3;
    case 10:
        if (*arg4 == 0) *arg4 = 3;
        *arg3 += 8;
    case 9:
        if (*arg4 == 0) *arg4 = 8;
        *arg3 += 4;
    case 8:
        if (*arg4 == 0) *arg4 = 4;
        *arg3 += 2;
    case 7:
        if (*arg4 == 0) *arg4 = 2;
        *arg3 += 3;
    case 6:
        if (*arg4 == 0) *arg4 = 3;
        *arg3 += 2;
    case 5:
        if (*arg4 == 0) *arg4 = 2;
        *arg3 += 2;
    case 4:
        if (*arg4 == 0) *arg4 = 2;
        *arg3 += 0x18;
    case 3:
        if (*arg4 == 0) {
            *arg4 = 3;
            *arg3 += arg2 * 3;
        }
        *arg3 += 0x38;
    case 2:
        if (*arg4 == 0) {
            *arg4 = 7;
            *arg3 += arg2 * 7;
        }
        *arg3 += 0x38;
    case 1:
        if (*arg4 == 0) {
            *arg4 = 7;
            *arg3 += arg2 * 7;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BEA8.s")

void func_8060BF84(s32 arg0, u8 arg1, u16 *arg2, u8 *arg3) {
    *arg2 = (((((((D_807ECEA0[0] + 0x6B7) & 0xFFC0) + 0x27) & 0xFFF8) * 4) + 0x3F) & 0xFFC0) + 0x40;
    *arg3 = 0;
    switch (arg0) {
    case 32: if (*arg3 == 0) *arg3 = 1; *arg2 += 3;
    case 31: if (*arg3 == 0) *arg3 = 3; *arg2 += 2;
    case 30: if (*arg3 == 0) *arg3 = 2; *arg2 += 0x2D;
    case 29: if (*arg3 == 0) { *arg3 = 9; *arg2 += arg1 * 9; } *arg2 += 0x19;
    case 28: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x19;
    case 27: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x19;
    case 26: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x2D;
    case 25: if (*arg3 == 0) { *arg3 = 9; *arg2 += arg1 * 9; } *arg2 += 0x19;
    case 24: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x19;
    case 23: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x19;
    case 22: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x4B;
    case 21: if (*arg3 == 0) { *arg3 = 0xF; *arg2 += arg1 * 0xF; } *arg2 += 0x19;
    case 20: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x19;
    case 19: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x19;
    case 18: if (*arg3 == 0) { *arg3 = 5; *arg2 += arg1 * 5; } *arg2 += 0x11;
    case 17: if (*arg3 == 0) *arg3 = 0x12;
    }
}

void func_8060C2C4(s32 arg0, s32 arg1, u8 arg2, u16 *arg3, s8 *arg4) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s0;

    temp_s2 = arg2 & 0xFF;
    *arg3 += 0x320;
    var_s0 = 0;
    if (temp_s2 > 0) {
        do {
            temp_v0 = modelTypeCountGet(var_s0 & 0xFF);
            var_s0 += 1;
            *arg3 += temp_v0;
        } while (var_s0 != temp_s2);
    }
    *arg4 = 1;
}

#ifdef NON_MATCHING
extern void func_8060BEA8(s32, u8, u16 *, u8 *);

void func_8060C340(arg0, arg1, arg2, arg3, arg4, arg5)
u16 *arg0;
u8 *arg1;
s32 arg2;
unsigned char arg3;
unsigned char arg4;
unsigned char arg5;
{
    *arg0 = arg5 * ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7);
    if (arg2 >= 0x11) {
        func_8060BF84(arg2, arg4, arg0, arg1);
        return;
    }
    if (arg2 >= 0xC) {
        func_8060BEA8(arg2, arg4, arg0, arg1);
        return;
    }
    if (arg2 > 0) {
        func_8060BCA0(arg2, arg3, arg4, arg0, arg1);
        return;
    }
    func_8060C2C4(arg2, arg3, arg4, arg0, (s8 *)arg1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C340.s")
#endif

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

extern s32 func_8060B9D0();
extern void func_8060BB18();
extern void func_8060C340();

void func_8060C648(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    u16 sp26;
    u8 sp25;

    func_8060C340(&sp26, &sp25, arg0, arg1, (s32)arg2, func_8060B9D0(arg3));
    func_8060BB18(func_8060C430(arg0, arg4, 1), sp26, sp25);
}

extern s32 func_8060BBE0();

s32 func_8060C6B8(s32 arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 new_var;
    u16 sp22;
    u8 sp21;

    new_var = func_8060B9D0(arg3);
    func_8060C340(&sp22, &sp21, arg0, arg1, arg2, new_var);
    new_var = func_8060BBE0(sp22, sp21);
    func_8060C430(arg0, new_var, 0);
}

extern s32 func_8060C6B8(s32, u8, u8, u8);

s32 func_8060C724(u8 arg0) {
    return func_8060C6B8(0x10, 0, 0, arg0) + 1;
}

extern u8 D_807ECEA8[];
void func_8060C758();

void func_8060C758(arg0, arg1)
unsigned char arg0;
int arg1;
{
    u8 *new_var;
    s32 s0;
    s32 new_var2;
    s32 size;
    s32 offset;

    do {
        s0 = arg0;
        offset = func_8060B9D0(s0);
        size = ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        new_var = D_807ECEA8 + (offset * size);
    } while (0); // FAKE: schedules addiu t0 before lui at
    D_807467C8 = s0;
    bzero(new_var, size);
    new_var2 = s0;
    func_8060C648(0xC, 0, 0, new_var2, 1);
    func_8060C648(0xF, 0, 0, s0 ^ 0, new_var2); // FAKE: prevents a3 CSE spill
    if (arg1 != 0) {
        eepromDispatchCommand(1);
    }
}

void func_8060C830(arg0, arg1)
unsigned char arg0;
int arg1;
{
    u32 temp = arg0;

    D_807467C8 = temp;
    arg0 = temp;
    func_8060C758(temp, 0);
    if (func_8060C6B8(0xF, 0, 0, 3) == arg0) {
        func_8060C758(3, 0);
    }
    if (arg1 != 0) {
        eepromDispatchCommand(1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C8AC.s")

extern void flagsClearAllBank1(void);
extern void func_8060C8AC(s32);

void func_8060CB74(void) {
    flagsClearAllBank1();
    func_8060C8AC(0xFF);
}

extern void eepromDispatchCommand(s32);

void func_8060CB9C(void) {
    eepromDispatchCommand(3);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060CBBC.s")

extern void func_8060C758();
extern void func_8060CB74(void);

void func_8060D0A8(void) {
    s32 unused;
    s32 sp28;
    s8 *var_v0;
    s32 var_s0;

    var_v0 = (s8 *)D_807EDEA8;
    var_s0 = 0;
    sp28 = (s32) D_807467C8;
    do {
        *var_v0 = var_s0;
        var_s0 += 1;
        var_v0 += 1;
    } while (var_s0 < 4);
    bzero(D_807ECEA8, 0x800);
    func_8060CB74();
    var_s0 = 0;
    do {
        func_8060C758(var_s0 & 0xFF, var_s0 == 3);
        var_s0 += 1;
    } while (var_s0 != 4);
    D_807467C8 = (u8) sp28;
}

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
    eepromDispatchCommand(2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DEC8.s")

void eepromThreadMain(void *arg0) {
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

void eepromInit(void) {
    func_8060B7F0();
    D_807EDEAC = osEepromProbe(&D_807ECCF0);
    osCreateMesgQueue(&D_807EE0D0, D_807EE0B0, 8);
    osCreateMesgQueue(&D_807F02B8, D_807F0298, 8);
    osCreateThread(&D_807EE0E8, 9, eepromThreadMain, NULL, D_807F0298, 0xC);
    osStartThread(&D_807EE0E8);
    D_807467E0 = 1;
    eepromDispatchCommand(0);
}

extern s32 func_8060B9D0();
extern s32 func_807142D8(void);
extern void func_80731030(void);
extern u8 D_807EDEB0[];
extern u8 D_807FC928;

u8 *func_8060E25C(s32 arg0) {
    u8 *result;
    s32 selector;

    selector = arg0 & 0xFF;
    result = NULL;
    switch (selector) {
    case 0:
        if ((func_807142D8() != 0) || (D_807FC928 >= 2)) {
            func_80731030();
            if (arg0) {
            }
            bzero(D_807EDEB0, ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8);
            result = D_807EDEB0;
        } else {
            result = D_807ECEA8 + ((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8) * func_8060B9D0(D_807467C8));
        }
        break;
    case 1:
        result = ((s32) (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8) + D_807ECEA8;
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E3B0.s")

extern s32 func_8060B9D0();
extern void func_8060BB18();
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




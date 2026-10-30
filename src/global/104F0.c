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




extern u32 D_807463C0[];

u32 func_8060B968(u8 *arg0, u16 arg1) {
    u32 crc = ~0;

    while (arg1--) {
        crc = D_807463C0[(*arg0++ ^ crc) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ -1;
}

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

extern u8 D_807ECEA8[];

#ifdef NON_MATCHING
extern s32 func_8071432C(void);
extern s32 func_80714394(void);

void func_8060BA14(void) {
    u8 original;
    u8 replacement;
    s32 size;
    s16 unk0;

    original = func_8060B9D0(D_807467C8);
    replacement = func_8060B9D0(3);
    if (((func_8071432C() != 0) || (func_80714394() != 0)) && (replacement != original)) {
        unk0 = D_807ECEA0[0];
        size = ((((unk0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        memcpy(D_807ECEA8 + (size * replacement), D_807ECEA8 + (size * original), size);
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
        D_807EDEA8[original] ^= D_807EDEA8[replacement];
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BA14.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BB18.s")

#ifdef NON_MATCHING
s32 func_8060BBE0(arg0, arg1)
unsigned short arg0;
unsigned char arg1;
{
    u32 *ptr;
    u32 data;
    u32 result;
    u8 start;
    u8 bit;
    u8 shift;
    u8 rem;

    result = 0;
    start = arg0 & 0x1F;
    shift = 0;
    bit = arg0 & 0x1F;
    data = 0;
    rem = arg1;
    ptr = (u32 *)D_807ECEA8 + (arg0 >> 5);
    if (rem) {
        do {
            data |= 1 << bit;
            bit++;
            rem--;
            if ((bit >= 0x20) || !rem) {
                result |= ((*ptr & data) >> start) << shift;
                bit = 0;
                ptr++;
                data = 0;
                start = 0;
                shift = -(rem - arg1);
            }
        } while (rem);
    }
    return result;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BBE0.s")
#endif

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

void func_8060BEA8(s32 arg0, u8 arg1, u16 *arg2, u8 *arg3) {
    *arg2 = D_807ECEA0[0] + *arg2 + 0x645;
    *arg3 = 0;
    switch (arg0) {
    case 15:
        if (*arg3 == 0) {
            *arg3 = 2;
        }
        *arg2 += 0x18;
    case 16:
        if (*arg3 == 0) {
            *arg3 = 0x18;
        }
        *arg2 += 0x16;
    case 14:
        if (*arg3 == 0) {
            *arg3 = 0x16;
        }
        *arg2 += 1;
    case 13:
        if (*arg3 == 0) {
            *arg3 = 1;
        }
        *arg2 += 2;
    case 12:
        if (*arg3 == 0) {
            *arg3 = 2;
        }
    }
}

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

typedef struct RvB2Config {
    s16 value;
    u8 byte2;
    u8 byte3;
    u8 byte4;
    u8 byte5;
} RvB2Config;

extern s32 D_807467EC[];
extern RvB2Config D_80744548[];
extern RvB2Config D_80744568[];

extern const u8 D_80757044[];
extern const u8 D_80757064[];

void func_8060C8AC(u8 arg0) {
    s32 i;

    if (arg0 & 1) {
        func_8060C648(0x11, 0, 0, 0, 0);
    }
    if (arg0 & 2) {
        for (i = 0; i != 5; i++) {
            func_8060C648(0x15, 0, i, 0, D_807467EC[i]);
            func_8060C648(0x12, 0, i, 0, 0x20);
            func_8060C648(0x13, 0, i, 0, 0x20);
            func_8060C648(0x14, 0, i, 0, 0x20);
        }
    }
    if (arg0 & 4) {
        for (i = 0; i != 5; i++) {
            func_8060C648(0x19, 0, i, 0, ((RvB2Config *)D_80757044)[i].value);
            func_8060C648(0x16, 0, i, 0, ((RvB2Config *)D_80757044)[i].byte2);
            func_8060C648(0x17, 0, i, 0, ((RvB2Config *)D_80757044)[i].byte3);
            func_8060C648(0x18, 0, i, 0, ((RvB2Config *)D_80757044)[i].byte4);
            D_80744548[i] = ((RvB2Config *)D_80757044)[i];
        }
    }
    if (arg0 & 8) {
        for (i = 0; i != 5; i++) {
            func_8060C648(0x1D, 0, i, 0, ((RvB2Config *)D_80757064)[i].value);
            func_8060C648(0x1A, 0, i, 0, ((RvB2Config *)D_80757064)[i].byte2);
            func_8060C648(0x1B, 0, i, 0, ((RvB2Config *)D_80757064)[i].byte3);
            func_8060C648(0x1C, 0, i, 0, ((RvB2Config *)D_80757064)[i].byte4);
            D_80744568[i] = ((RvB2Config *)D_80757064)[i];
        }
    }
    if (arg0 & 0x10) {
        func_8060C648(0x1E, 0, 0, 0, 0);
    }
    if (arg0 & 0x20) {
        func_8060C648(0x1F, 0, 0, 0, 0);
    }
}

extern void flagsClearAllBank1(void);
extern void func_8060C8AC(u8);

void func_8060CB74(void) {
    flagsClearAllBank1();
    func_8060C8AC(0xFF);
}

extern void eepromDispatchCommand(s32);

void func_8060CB9C(void) {
    eepromDispatchCommand(3);
}

extern void func_8060C758();
extern s32 func_8060C6B8(s32, u8, u8, u8);
extern void func_8060CB74(void);
extern u8 D_807ED6A8[];
extern u8 D_807550C8;
extern u8 D_80744530;

#ifdef NON_MATCHING
void func_8060CBBC(void) {
    s32 i;
    s32 j;
    s32 version;
    s32 found;
    s32 height;
    s32 checksumIndex;
    u8 valid[4];
    u8 sectorOrder[4];
    u32 pad[4];
    u8 failed;
    failed = 0;
    memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    i = 0;
    do {
        D_807EDEA8[i] = i;
        sectorOrder[i] = 0xFF;
        i++;
    } while (i < 4);
    height = (((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7;
    height /= 8;
    for (i = 0; i < 4; i++) {
        checksumIndex = (((i + 1) * height) / 4) - 1;
        valid[i] = 1;
        if (((u32 *)D_807ED6A8)[checksumIndex] != func_8060B968(D_807ED6A8 + ((i * height) & 0xFFFF), (height - 4) & 0xFFFF)) {
            valid[i] = 0;
            func_8060C758(i & 0xFF, 0);
            func_8060C648(0xF, 0, 0, i & 0xFF, 0xFF);
        }
        failed |= (valid[i] == 0);
    }
    for (i = 0; i < 4; i++) {

        if (valid[i] == 0 || func_8060C6B8(0xD, 0, 0, i & 0xFF) == 0) continue;
        version = func_8060C6B8(0xF, 0, 0, i & 0xFF);
        sectorOrder[i] = version;
        for (j = 0; j < 4 && sectorOrder[i] == version; j++) {
            if (j != i && valid[j] != 0 && func_8060C6B8(0xD, 0, 0, j & 0xFF) != 0 && func_8060C6B8(0xF, 0, 0, j & 0xFF) == version && func_8060C6B8(0x10, 0, 0, j & 0xFF) >= func_8060C6B8(0x10, 0, 0, i & 0xFF)) {
                sectorOrder[i] = 0xFF;
                func_8060C758(i & 0xFF, 0);
                func_8060C648(0xF, 0, 0, i & 0xFF, 0xFF);
                failed |= 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        found = 0;
        for (j = 0; j < 4; j++) if (sectorOrder[j] == i) found = 1;
        if (found == 0) for (j = 0; j < 4 && found == 0; j++) if (sectorOrder[j] == 0xFF) {
            sectorOrder[j] = i;
            found = 1;
            func_8060C648(0xF, 0, 0, j & 0xFF, i);
        }
    }
    D_807EDEA8[1] = sectorOrder[1];
    D_807EDEA8[2] = sectorOrder[2];
    D_807EDEA8[3] = sectorOrder[3];
    D_807EDEA8[0] = sectorOrder[0];
    height = (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F;
    height /= 8;
    checksumIndex = ((height + 0x40) / 4) - 1;
    if (((u32 *)D_807ED6A8)[checksumIndex] != func_8060B968(D_807ED6A8 + (height & 0xFFFF), 0x3C)) {
        func_8060CB74();
        failed |= 1;
    }
    D_807550C8 = func_8060C6B8(0x1F, 0, 0, 0);
    D_80744530 = func_8060C6B8(0x20, 0, 0, 0);
    if (D_807550C8 > 0) {
        D_807550C8 = 0;
        func_8060C648(0x1F, 0, 0, 0, 0);
    }
    if (failed != 0) eepromDispatchCommand(1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060CBBC.s")
#endif

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

#ifdef NON_MATCHING
extern OSMesgQueue D_807ECCF0;
extern s32 D_807EDEAC;
extern s32 _strcasecmp(char *, char *);
extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467CC;
extern u8 D_807ED6A8[];

void func_8060D14C(void) {
    s32 var_s2;
    u8 *var_s1;
    s32 var_s0;

    var_s2 = 0;
    var_s1 = D_807ED6A8;
    if (D_807EDEAC != 2) {
        func_8060D0A8();
        D_807467CC = 1;
        return;
    }
    D_807467C4 = 1;
    var_s0 = 0;
    do {
        var_s2 |= osEepromRead(&D_807ECCF0, (u8)var_s0, var_s1);
        sleepMilliseconds(15.0f);
        var_s0 += 1;
        if (D_80744460 != 0) {
            D_807467C4 = 0;
            return;
        }
        var_s1 += 8;
    } while ((var_s0 < 0x100) && (var_s2 == 0));
    D_807467C4 = 0;
    D_807467CC = 1;
    if (var_s2 == 0) {
        var_s2 = _strcasecmp((char *)D_807ED6A8 + ((((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
    }
    if (var_s2 != 0) {
        func_8060D0A8();
    }
    func_8060CB9C();
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D14C.s")
#endif

#ifdef NON_MATCHING
extern s32 _sprintf();
extern void func_8060BA14(void);
extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467E4;
extern f32 D_807467E8;
extern u8 D_807ECD08[];
extern s32 D_807EDEAC;
extern OSMesgQueue D_807ECCF0;
extern u8 D_807ED6A8[];

void func_8060D2C8(s32 arg0) {
    s32 i;
    s32 textOffset;
    s32 offset;
    s32 sector;
    s32 dataLength;
    s32 height;
    u8 savedData[0x800];
    u8 workingData[0x800];
    u8 *sp5C;
    s32 after_1;
    s32 after_2;

    if (D_807EDEAC != 2) return;
    textOffset = (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F;
    textOffset = (textOffset + 0x207) & ~7;
    textOffset /= 8;
    _sprintf((char *)D_807ECEA8 + textOffset, D_807467C0);
    memcpy(workingData, D_807ECEA8, 0x800);
    memcpy(savedData, D_807ED6A8, 0x800);
    offset = (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F;
    offset /= 8;
    if (arg0 == 0) {
        func_8060BA14();
        height = (((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7;
        height /= 8;
        for (i = 0; i < 4; i++) {
            ((u32 *)workingData)[(((i + 1) * height) / 4) - 1] = func_8060B968(workingData + ((i * height) & 0xFFFF), (height - 4) & 0xFFFF);
        }
        sector = 0;
    } else sector = offset & 0xFFFF;
    ((u32 *)workingData)[((offset + 0x40) / 4) - 1] = func_8060B968(workingData + (offset & 0xFFFF), 0x3C);
    dataLength = strlen(D_807467C0);
    bzero(workingData + dataLength + offset + 0x40, 0x800 - offset - dataLength - 0x40);
    osWritebackDCacheAll();
    memcpy(D_807ED6A8 + sector * 8, workingData + sector * 8, 0x800 - sector * 8);
    if (D_807ECD08[0] != 0) do sleepMilliseconds(1.0f); while (D_807ECD08[0] != 0);
    if (D_80744460 == 0) {
        D_807467C4 = 1;
        for (sector &= 0xFFFF; sector < 0x100; sector += 2) {
            D_807467E4 = 0x1E;
            D_807467E8 = (f32)sector * 0.00390625f;
            if (((u32 *)(savedData + sector * 8))[0] != ((u32 *)(workingData + sector * 8))[0] || ((u32 *)(savedData + sector * 8))[1] != ((u32 *)(workingData + sector * 8))[1]) {
                for (i = 0; i < 2; i++) {
                    if (D_80744460 != 0) break;
                    osEepromWrite(&D_807ECCF0, (sector + i) & 0xFF, workingData + (sector + i) * 8);
                    sleepMilliseconds(15.0f);
                }
            }
        }
        D_807467C4 = 0;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D2C8.s")
#endif

extern void func_8060D2C8(s32);

void func_8060D768(void) {
    func_8060D2C8(0);
}

void func_8060D788(void) {
    func_8060D2C8(1);
}

extern s32 flagGet(s32, s32);
extern s32 func_806F6EDC(void);
extern s32 slotQueueGetMaxValue(s32, s32);
extern u8 D_807FC950[];
extern u8 D_807FC952;
extern u8 D_8074E77C;

#ifdef NON_MATCHING
void func_8060D7A8(void) {
    s32 i;
    u8 *entry;

    if (func_806F6EDC() != 0) {
        s32 v = slotQueueGetMaxValue(5, 0);
        *(s16 *)(D_807FC950 + 0x2F6) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    if (flagGet(0x184, 0) != 0) {
        s32 v = slotQueueGetMaxValue(4, 0);
        *(s16 *)(D_807FC950 + 0x2F4) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    if (flagGet(0x179, 0) != 0) {
        s32 v = slotQueueGetMaxValue(6, 0);
        *(s16 *)(D_807FC950 + 0x2F8) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    if (D_807FC952 != 0) {
        s32 v = slotQueueGetMaxValue(2, 0);
        *(s16 *)(D_807FC950 + 0x2F0) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    if (D_8074E77C && D_8074E77C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    entry = D_807FC950;
    i = 0;
    do {
        D_8074E77C = i;
        if (entry[4] != 0) {
            s32 v = slotQueueGetMaxValue(7, 0);
            *(s16 *)(entry + 8) = (s16)(u32)((f64)(u32)v * 0.5);
        }
        i++;
        entry += 0x5E;
    } while (i != 5);
    D_8074E77C = 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D7A8.s")
#endif

extern void collectibleCountsClear(void);
extern void func_8060BA14(void);
extern void func_806C9AE0(void);
extern void healthRefill(s32);
extern u8 D_80750AC0;
extern s32 D_80750AB0;
extern u16 D_807FC930[];
extern u8 D_807FC928;

#ifdef NON_MATCHING
void func_8060DC3C(s32 arg0, s32 arg1) {
    s32 i;
    u8 selector;
    u8 *base;
    u8 *entry;
    u8 *field;
    u16 *sum;
    s32 j;
    s32 value;

    base = D_807FC950;
    if (base && base) {} // FAKE: keep base in register
    selector = arg0;
    if (selector && selector) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    entry = base;
    D_80750AC0 = 1;
    func_806C9AE0();
    if (D_807FC950) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    D_807467C8 = selector;
    D_8074E77C = 0;
    if (func_8060C6B8(0xD, 0, 0, selector) == 0) {
        func_8060C758(selector, 0);
    }
    if (arg1 != 0) {
        func_8060BA14();
    }
    D_807FC928 = 0;
    base[0x2FC] = func_8060C6B8(0xC, 0, 0, selector);
    healthRefill(0);
    collectibleCountsClear();
    D_80750AB0 = func_8060C6B8(0xE, 0, 0, selector);
    i = 0;
    if (D_807FC930) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    do {
        j = 0;
        field = entry;
        do {
            *field++ = func_8060C6B8(j + 4, i, 0, selector);
            j++;
        } while (j != 5);
        *(s16 *)(entry + 6) = func_8060C6B8(9, i, 0, selector);
        entry[5] = func_8060C6B8(0xA, i, 0, selector);
        if (func_8060C6B8(0xB, i, 0, selector) != 0) {
            entry[5] |= 0x80;
        }
        if (D_807FC930) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        field = entry;
        j = 0;
        sum = D_807FC930;
        do {
            *(s16 *)(field + 0xA) = func_8060C6B8(1, i, j, selector);
            value = func_8060C6B8(2, i, j, selector);
            *(s16 *)(field + 0x26) = value;
            *sum += value;
            *(s16 *)(field + 0x42) = func_8060C6B8(3, i, j, selector);
            j++;
            field += 2;
            sum++;
        } while (j != 8);
        i++;
        if (D_807467C8 && D_807467C8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        entry += 0x5E;
    } while (i != 5);
    if (arg1 != 0) {
        func_8060D7A8();
    }
    D_8074E77C = 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DC3C.s")
#endif

void func_8060DEA8(void) {
    eepromDispatchCommand(2);
}

extern u32 func_805FC98C(void);
extern s32 func_80714394(void);
extern s32 func_8071432C(void);

#ifdef NON_MATCHING
void func_8060DEC8(void) {
    u8 *entry;
    u8 *base;
    u32 total;
    u32 value;
    s32 i;
    s32 j;
    u8 *field;

    if (D_807FC928 == 1) {
        if (func_80714394() != 0 || func_8071432C() != 0) {
            base = D_807FC950;
            entry = base;
            total = func_805FC98C();
            value = func_8060C724(D_807467C8);
            if (D_807FC950) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (total >= 0x400000U) {
                total = -1;
            }
            func_8060C648(0xD, 0, 0, D_807467C8, 1);
            func_8060C648(0xE, 0, 0, D_807467C8, total);
            func_8060C648(0xC, 0, 0, D_807467C8, base[0x2FC]);
            func_8060C648(0xF, 0, 0, D_807467C8, D_807467C8);
            func_8060C648(0x10, 0, 0, D_807467C8, value);
            i = 0;
            do {
                u8 row_idx = i;
                j = 0;
                if (D_807467C8 && D_807467C8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                field = entry;
                do {
                    func_8060C648(j + 4, row_idx, 0, D_807467C8, *field);
                    j++;
                    field++;
                } while (j != 5);
                func_8060C648(9, row_idx, 0, D_807467C8, *(u16 *)(entry + 6));
                func_8060C648(0xA, row_idx, 0, D_807467C8, entry[5] & 0x7F);
                func_8060C648(0xB, row_idx, 0, D_807467C8, ((s32)entry[5] >> 7) & 1);
                j = 0;
                field = entry;
                do {
                    func_8060C648(1, row_idx, (u8)j, D_807467C8, *(u16 *)(field + 0xA));
                    func_8060C648(2, row_idx, (u8)j, D_807467C8, *(u16 *)(field + 0x26));
                    func_8060C648(3, row_idx, (u8)j, D_807467C8, *(u16 *)(field + 0x42));
                    j++;
                    field += 2;
                } while (j != 8);
                i++;
                entry += 0x5E;
            } while (i != 5);
            eepromDispatchCommand(1);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DEC8.s")
#endif

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

#ifdef NON_MATCHING
u8 func_8060E3B0(u16 arg0, u8 arg1) {
    u8 result;
    u16 value;
    u8 output;

    result = 0;
    if (func_8071432C() != 0) {
        func_8060C340(&value, &output, 0, 0, arg1, func_8060B9D0(D_807467C8));
        result = func_8060BBE0((value + arg0) & 0xFFFF, 1);
    }
    return result;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E3B0.s")
#endif

extern s32 func_8060B9D0();
extern void func_8060BB18();
extern void func_8060C340();

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




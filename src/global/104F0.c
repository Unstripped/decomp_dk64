#include "common.h"
#include "actor.h"

s16 D_807ECEA0[4];
u8 D_807ECEA8[0x800];
u8 D_807ED6A8[0x800];
u8 D_807EDEA8[4];
s32 D_807EDEAC;
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

u32 eepromCalculateCrc32(u8 *arg0, u16 arg1) {
    u32 crc = ~0;

    while (arg1--) {
        crc = D_807463C0[(*arg0++ ^ crc) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ -1;
}


u8 eepromGetSectorForSlot(s32 arg0) {
    u8 i;

    for (i = 0; i < 4; i++) {
        if (arg0 == D_807EDEA8[i]) {
            return i;
        }
    }
    return 0;
}


#ifdef NON_MATCHING
extern s32 func_8071432C(void);
extern s32 func_80714394(void);

void eepromCopySlot(void) {
    u8 original;
    u8 replacement;
    s16 unk0;
    s32 size;
    u8 *src;
    u8 *dst;

    original = eepromGetSectorForSlot(D_807467C8);
    replacement = eepromGetSectorForSlot(3);
    if (((func_8071432C() != 0) || (func_80714394() != 0)) && (original != replacement)) {
        unk0 = D_807ECEA0[0];
        size = ((((unk0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        src = D_807ECEA8 + (size * original);
        if (src) {} // FAKE: pins src before dst (evaluation order and colouring of the mask temps)
        dst = D_807ECEA8 + (size * replacement);
        memcpy(dst, src, size);
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
        D_807EDEA8[original] ^= D_807EDEA8[replacement];
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/eepromCopySlot.s")
#endif

void eepromWriteBitfield(arg0, arg1, arg2)
u32 arg0;
unsigned short arg1;
unsigned char arg2;
{
    u32 mask;
    u32 val;
    u8 bit;
    u32 *ptr;

    mask = -1;
    val = 0;
    bit = arg1 & 0x1F;
    ptr = (u32 *)D_807ECEA8 + (arg1 >> 5);
    if (arg2) {
        do {
            mask ^= 1 << bit;
            val |= (arg0 & 1) << bit;
            arg0 >>= 1;
            bit++;
            arg2--;
            if ((bit >= 0x20) || !arg2) {
                *ptr = (*ptr & mask) | val;
                ptr++;
                bit = 0;
                val = 0;
                mask = -1;
            }
        } while (arg2);
    }
}

s32 eepromReadBitfield(arg0, arg1)
unsigned short arg0;
unsigned char arg1;
{
    u32 *ptr;
    u32 data;
    u32 result;
    u8 start;
    u8 bit;
    u8 shift;
    u8 orig;

    result = 0;
    start = arg0 & 0x1F;
    shift = 0;
    bit = arg0 & 0x1F;
    data = 0;
    orig = arg1;
    ptr = (u32 *)D_807ECEA8 + (arg0 >> 5);
    if (arg1) {
        do {
            data |= 1 << bit;
            bit++;
            arg1--;
            if ((bit >= 0x20) || !arg1) {
                result |= ((*ptr & data) >> start) << shift;
                bit = 0;
                ptr++;
                data = 0;
                start = 0;
                shift = -(arg1 - orig);
            }
        } while (arg1);
    }
    return result;
}

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

void eepromGetSaveDataSectionOffset(s32 arg0, u8 arg1, u16 *arg2, u8 *arg3) {
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

void eepromCalculateTotalModelCount(s32 arg0, s32 arg1, u8 arg2, u16 *arg3, s8 *arg4) {
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

void eepromGetSectorOffset(arg0, arg1, arg2, arg3, arg4, arg5)
u16 *arg0;
u8 *arg1;
s32 arg2;
unsigned char arg3;
unsigned char arg4;
unsigned char arg5;
{
    u16 m;
    m = arg5;
    m *= ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7);
    *arg0 = m;
    if (arg2 >= 0x11) {
        func_8060BF84(arg2, arg4, arg0, arg1);
        return;
    }
    if (arg2 >= 0xC) {
        eepromGetSaveDataSectionOffset(arg2, arg4, arg0, arg1);
        return;
    }
    if (arg2 > 0) {
        func_8060BCA0(arg2, arg3, arg4, arg0, arg1);
        return;
    }
    eepromCalculateTotalModelCount(arg2, arg3, arg4, arg0, (s8 *)arg1);
}

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

extern u8 eepromGetSectorForSlot();
extern void eepromWriteBitfield();
extern void eepromGetSectorOffset();

void eepromSetField(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    u16 sp26;
    u8 sp25;

    eepromGetSectorOffset(&sp26, &sp25, arg0, arg1, (s32)arg2, eepromGetSectorForSlot(arg3));
    eepromWriteBitfield(func_8060C430(arg0, arg4, 1), sp26, sp25);
}

extern s32 eepromReadBitfield();

s32 eepromGetField(s32 arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 new_var;
    u16 sp22;
    u8 sp21;

    new_var = eepromGetSectorForSlot(arg3);
    eepromGetSectorOffset(&sp22, &sp21, arg0, arg1, arg2, new_var);
    new_var = eepromReadBitfield(sp22, sp21);
    func_8060C430(arg0, new_var, 0);
}

extern s32 eepromGetField(s32, u8, u8, u8);

s32 func_8060C724(u8 arg0) {
    return eepromGetField(0x10, 0, 0, arg0) + 1;
}

void eepromClearSlotData();

void eepromClearSlotData(arg0, arg1)
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
        offset = eepromGetSectorForSlot(s0);
        size = ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        new_var = D_807ECEA8 + (offset * size);
    } while (0); // FAKE: schedules addiu t0 before lui at
    D_807467C8 = s0;
    bzero(new_var, size);
    new_var2 = s0;
    eepromSetField(0xC, 0, 0, new_var2, 1);
    eepromSetField(0xF, 0, 0, s0 ^ 0, new_var2); // FAKE: prevents a3 CSE spill
    if (arg1 != 0) {
        eepromDispatchCommand(1);
    }
}

void eepromSetCurrentSlot(arg0, arg1)
unsigned char arg0;
int arg1;
{
    u32 temp = arg0;

    D_807467C8 = temp;
    arg0 = temp;
    eepromClearSlotData(temp, 0);
    if (eepromGetField(0xF, 0, 0, 3) == arg0) {
        eepromClearSlotData(3, 0);
    }
    if (arg1 != 0) {
        eepromDispatchCommand(1);
    }
}

typedef struct EepromConfig {
    s16 value;
    u8 byte2;
    u8 byte3;
    u8 byte4;
    u8 byte5;
} EepromConfig;

extern s32 D_807467EC[];
extern EepromConfig D_80744548[];
extern EepromConfig D_80744568[];

extern const u8 D_80757044[];
extern const u8 D_80757064[];

void eepromInitConfigs(u8 arg0) {
    s32 i;

    if (arg0 & 1) {
        eepromSetField(0x11, 0, 0, 0, 0);
    }
    if (arg0 & 2) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x15, 0, i, 0, D_807467EC[i]);
            eepromSetField(0x12, 0, i, 0, 0x20);
            eepromSetField(0x13, 0, i, 0, 0x20);
            eepromSetField(0x14, 0, i, 0, 0x20);
        }
    }
    if (arg0 & 4) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x19, 0, i, 0, ((EepromConfig *)D_80757044)[i].value);
            eepromSetField(0x16, 0, i, 0, ((EepromConfig *)D_80757044)[i].byte2);
            eepromSetField(0x17, 0, i, 0, ((EepromConfig *)D_80757044)[i].byte3);
            eepromSetField(0x18, 0, i, 0, ((EepromConfig *)D_80757044)[i].byte4);
            D_80744548[i] = ((EepromConfig *)D_80757044)[i];
        }
    }
    if (arg0 & 8) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x1D, 0, i, 0, ((EepromConfig *)D_80757064)[i].value);
            eepromSetField(0x1A, 0, i, 0, ((EepromConfig *)D_80757064)[i].byte2);
            eepromSetField(0x1B, 0, i, 0, ((EepromConfig *)D_80757064)[i].byte3);
            eepromSetField(0x1C, 0, i, 0, ((EepromConfig *)D_80757064)[i].byte4);
            D_80744568[i] = ((EepromConfig *)D_80757064)[i];
        }
    }
    if (arg0 & 0x10) {
        eepromSetField(0x1E, 0, 0, 0, 0);
    }
    if (arg0 & 0x20) {
        eepromSetField(0x1F, 0, 0, 0, 0);
    }
}

extern void flagsClearAllBank1(void);
extern void eepromInitConfigs(u8);

void func_8060CB74(void) {
    flagsClearAllBank1();
    eepromInitConfigs(0xFF);
}

extern void eepromDispatchCommand(s32);

void func_8060CB9C(void) {
    eepromDispatchCommand(3);
}

extern void eepromClearSlotData();
extern s32 eepromGetField(s32, u8, u8, u8);
extern void func_8060CB74(void);
extern u8 D_807550C8;
extern u8 D_80744530;


#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/eepromValidateSaveSlots.s")

extern void eepromClearSlotData();
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
        eepromClearSlotData(var_s0 & 0xFF, var_s0 == 3);
        var_s0 += 1;
    } while (var_s0 != 4);
    D_807467C8 = (u8) sp28;
}

extern OSMesgQueue D_807ECCF0;
extern s32 _strcasecmp(char *, char *);
extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467CC;

void eepromReadAllSectors(void) {
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
    for (var_s0 = 0; (var_s0 < 0x100) && (var_s2 == 0); var_s0++, var_s1 += 8) {
        var_s2 |= osEepromRead(&D_807ECCF0, (u8)var_s0, var_s1);
        sleepMilliseconds(15.0f);
        if (D_80744460 != 0) {
            D_807467C4 = 0;
            return;
        }
    }
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

extern s32 _sprintf();
extern void eepromCopySlot(void);
extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467E4;
extern f32 D_807467E8;
extern u8 D_807ECD08[];
extern OSMesgQueue D_807ECCF0;


#ifdef NON_MATCHING
void eepromSaveRecords(s32 arg0) {
    s32 j;
    s32 sector;
    s32 offset;
    s32 height;
    u16 idx;
    u16 a;
    u16 b;
    u8 i;
    u8 workingData[0x800];
    u8 savedData[0x800];
    u8 *p;
    p = D_807ECD08;
    if (D_807EDEAC == 2) {
        _sprintf((char *)D_807ECEA8 + ((((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
        memcpy(workingData, D_807ECEA8, 0x800);
        memcpy(savedData, D_807ED6A8, 0x800);
        if (arg0 == 0) {
            eepromCopySlot();
            for (i = 0; i < 4; i++) {
                height = ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7);
                height /= 8;

                a = i * height;
                if (a) {}  // FAKE: live range / colouring of the narrowed index temp
                b = (((i + 1) * height) / 4) - 1;
                ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, height - 4);
            }
            sector = 0;
            offset = D_807ECEA0[0];
            offset += 0x6B7;
            offset = ((u16)offset & ~0x3F) + 0x27;
            offset = ((s32)(offset & ~7U) * 4) + 0x3F;
            offset = (s32)(offset & ~0x3FU);
            offset /= 8;
        } else {
            offset = (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F);
            offset /= 8;
            sector = (offset / 8) & 0xFFFF;
        }
        a = offset;
        if (a) {}  // FAKE: live range / colouring of the narrowed index temp
        b = ((offset + 0x40) / 4) - 1;
        if (b) {}  // FAKE: live range / colouring of the narrowed index temp
        ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, 0x3C);
        bzero(strlen(D_807467C0) - (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) + workingData + 0x840, (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) - strlen(D_807467C0) - 0x40);
        if (D_807ECEA0) {}  // FAKE: deadsweep dead statement (steers uopt)
        osWritebackDCacheAll();
        memcpy(D_807ED6A8 + sector * 8, workingData + sector * 8, 0x800 - (sector << 3));
        if (D_807ECD08[0] != 0) do sleepMilliseconds(1.0f); while (*p != 0);
        if (D_807ECD08 && D_807ECD08) {}  // FAKE: colours the polled D_807ECD08 address candidate
        if (D_80744460 != 0) {
            D_807467C4 = 0;
        } else {
            D_807467C4 = 1;
            for (idx = sector; idx < 0x100; idx += 2) {
                D_807467E4 = 0x1E;
                D_807467E8 = (f32)(u32)idx * 0.00390625f;
                if (((u64 *)savedData)[idx] != ((u64 *)workingData)[idx] ||
                    ((u64 *)savedData)[idx + 1] != ((u64 *)workingData)[idx + 1]) {
                    for (j = 0; j < 2; j++) {
                        if (D_80744460 != 0) {
                            D_807467C4 = 0;
                            return;
                        }
                        osEepromWrite(&D_807ECCF0, idx + j, workingData + idx * 8 + j * 8);
                        sleepMilliseconds(15.0f);
                    }
                }
            }
            D_807467C4 = 0;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/eepromSaveRecords.s")
#endif

extern void eepromSaveRecords(s32);

void eepromSaveRecordsAll(void) {
    eepromSaveRecords(0);
}

void eepromSaveRecordsOffset(void) {
    eepromSaveRecords(1);
}

extern s32 flagGet(s32, s32);
extern s32 func_806F6EDC(void);
extern s32 slotQueueGetMaxValue(s32, s32);
extern u8 D_807FC950[];
extern u8 D_807FC952;
extern u8 gPlayerCharacterId;

void eepromHalveRecords(void) {
    s32 i;

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
    for (i = 0; i != 5; i++) {
        gPlayerCharacterId = i;
        if (D_807FC950[i * 0x5E + 4] != 0) {
            s32 v = slotQueueGetMaxValue(7, 0);
            *(s16 *)(&D_807FC950[i * 0x5E + 8]) = (s16)(u32)((f64)(u32)v * 0.5);
        }
    }
    gPlayerCharacterId = 0;
}

extern void collectibleCountsClear(void);
extern void eepromCopySlot(void);
extern void func_806C9AE0(void);
extern void healthRefill(s32);
extern u8 D_80750AC0;
extern s32 D_80750AB0;
extern u16 D_807FC930[];
extern u8 gPlayerCount;

void eepromLoadPlayerData(u8 arg0, s32 arg1) { u8 *base; s32 i; u8 *entry; s32 j; s32 k; base = (u8 *)((u32)D_807FC950 | 0); if (base) {} // LAYOUT: entry stmts on { line schedule addiu after lui; FAKE: `| 0` blocks address copy-propagation, dead if (base)
    entry = base;
    D_80750AC0 = 1;
    func_806C9AE0();
    memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    D_807467C8 = arg0;
    gPlayerCharacterId = 0;
    if (eepromGetField(0xD, 0, 0, arg0) == 0) {
        eepromClearSlotData(arg0 & 0xFF, 0);
    }
    if (arg1 != 0) {
        eepromCopySlot();
    }
    gPlayerCount = 0;
    base[0x2FC] = eepromGetField(0xC, 0, 0, arg0);
    healthRefill(0);
    collectibleCountsClear();
    D_80750AB0 = eepromGetField(0xE, 0, 0, arg0);
    i = 0;
    do {
        for (j = 0; j != 5; j++)
            entry[j] = eepromGetField(j + 4, (u8)i, 0, arg0);
        *(s16 *)(entry + 6) = eepromGetField(9, (u8)i, 0, arg0);
        entry[5] = eepromGetField(0xA, (u8)i, 0, arg0);
        if (eepromGetField(0xB, (u8)i, 0, arg0) != 0) {
            entry[5] |= 0x80;
        }
        for (k = 0; k != 8; k++) {
            ((u16 *)(entry + 0xA))[k] = eepromGetField(1, (u8)i, (u8)k, arg0);
            D_807FC930[k] += ((u16 *)(entry + 0x26))[k] = eepromGetField(2, (u8)i, (u8)k, arg0);
            ((u16 *)(entry + 0x42))[k] = eepromGetField(3, (u8)i, (u8)k, arg0);
        }
        i++;
        entry += 0x5E;
    } while (i != 5);
    if (arg1 != 0) {
        eepromHalveRecords();
    }
    gPlayerCharacterId = 0;
}

void func_8060DEA8(void) {
    eepromDispatchCommand(2);
}

extern u32 func_805FC98C(void);
extern s32 func_80714394(void);
extern s32 func_8071432C(void);

void eepromSavePlayerData(void) {
    u8 *entry;
    u8 *base;
    u32 total;
    u32 value;
    s32 i;
    s32 j;
    s32 k;

    if (gPlayerCount == 1) {
        if (func_80714394() != 0 || func_8071432C() != 0) {
            base = (u8 *)((u32)D_807FC950 | 0); // FAKE: `| 0` keeps the base in a saved reg (blocks copy-propagation into @sym+off)
            entry = base;
            total = func_805FC98C();
            value = func_8060C724(D_807467C8);
            if (total >= 0x400000U) {
                total = -1;
            }
            eepromSetField(0xD, 0, 0, D_807467C8, 1);
            eepromSetField(0xE, 0, 0, D_807467C8, total);
            eepromSetField(0xC, 0, 0, D_807467C8, base[0x2FC]);
            eepromSetField(0xF, 0, 0, D_807467C8, D_807467C8);
            eepromSetField(0x10, 0, 0, D_807467C8, value);
            i = 0;
            if (value && value) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            do {
                j = 0;
                do {
                    eepromSetField(j + 4, (u8)i, 0, D_807467C8, entry[j]);
                    j++;
                } while (j != 5);
                eepromSetField(9, (u8)i, 0, D_807467C8, *(u16 *)(entry + 6));
                eepromSetField(0xA, (u8)i, 0, D_807467C8, entry[5] & 0x7F);
                eepromSetField(0xB, (u8)i, 0, D_807467C8, ((s32)entry[5] >> 7) & 1);
                k = 0;
                do {
                    u8 col_idx = k;
                    eepromSetField(1, (u8)i, col_idx, D_807467C8, ((u16 *)(entry + 0xA))[k]);
                    eepromSetField(2, (u8)i, col_idx, D_807467C8, ((u16 *)(entry + 0x26))[k]);
                    eepromSetField(3, (u8)i, col_idx, D_807467C8, ((u16 *)(entry + 0x42))[k]);
                    k++;
                } while (k != 8);
                i++;
                entry += 0x5E;
            } while (i != 5);
            eepromDispatchCommand(1);
        }
    }
}

void eepromThreadMain(void *arg0) {
    OSMesg msg;

    while (TRUE) {
        osRecvMesg(&D_807F02B8, &msg, 1);
        D_807467D0[(s32)msg]();
    }
}

extern OSMesgQueue D_807ECCF0;
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

extern u8 eepromGetSectorForSlot();
extern s32 func_807142D8(void);
extern void flagsClearAllBank2(void);
extern u8 D_807EDEB0[];

u8 *func_8060E25C(s32 arg0) {
    u8 *result;
    s32 selector;

    selector = arg0 & 0xFF;
    result = NULL;
    switch (selector) {
    case 0:
        if ((func_807142D8() != 0) || (gPlayerCount >= 2)) {
            flagsClearAllBank2();
            if (arg0) {
            }
            bzero(D_807EDEB0, ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8);
            result = D_807EDEB0;
        } else {
            result = D_807ECEA8 + ((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8) * eepromGetSectorForSlot(D_807467C8));
        }
        break;
    case 1:
        result = ((s32) (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8) + D_807ECEA8;
        break;
    }
    return result;
}

u8 eepromReadChecksumBit(u16 arg0, u8 arg1) {
    u8 result;
    u16 value;
    u8 output;

    result = 0;
    if (func_8071432C() != 0) {
        eepromGetSectorOffset(&value, &output, 0, 0, arg1, eepromGetSectorForSlot(D_807467C8));
        result = eepromReadBitfield((value + arg0) & 0xFFFF, 1);
    }
    return result;
}

extern u8 eepromGetSectorForSlot();
extern void eepromWriteBitfield();
extern void eepromGetSectorOffset();

void func_8060E430(u16 arg0, u8 arg1, u8 arg2) {
    u16 value;
    u8 unk;

    if (func_8071432C() != 0) {
        eepromGetSectorOffset(&value, &unk, 0, 0, arg2, eepromGetSectorForSlot(D_807467C8));
        eepromWriteBitfield(arg1, (value + arg0) & 0xFFFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757020.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757024.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757064.s")




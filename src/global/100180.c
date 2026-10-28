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

void func_806FB480(void) {
}

void func_806FB488(void) {
}

s32 func_806FB490(u8, s32, s32, s16, u8, s8 *, u8);

#ifdef NON_MATCHING
s32 func_806FB490(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *src;
    u8 *srcRow;
    u8 *dst;
    s32 w2;
    s32 phase;
    s32 odd;
    s16 row;
    s16 j;
    u8 *dstRow;
    u8 lead;
    u8 *p5;

    p5 = (u8 *)arg5;
    srcRow = (u8 *)arg2 + (arg3 >> 1);
    dst = (u8 *)(arg6 * 16 + arg1 + arg6 * arg4);
    src = (u8 *)arg2;
    dstRow = dst;
    phase = (*p5 & 1) != 0;
    *p5 += arg0;
    odd = (arg0 & 1) != 0;
    arg0 = arg0 >> 1;
    w2 = arg0;
    row = 0;
    do {
        j = 0;
        if (w2 > 0) {
            lead = arg3 & 1;
            do {
                if (lead && phase == 0) {
                    *dst |= *src++ << 4;
                    *dst++ |= (*src & 0xF0) >> 4;
                } else if (lead && phase != 0) {
                    *dst |= *src++ & 0xF;
                    *++dst |= *src & 0xF0;
                } else if (lead == 0 && phase != 0) {
                    *dst++ |= (*src & 0xF0) >> 4;
                    *dst |= *src++ << 4;
                } else {
                    *dst++ |= *src++;
                }
                j++;
            } while (j < w2);
        }
        srcRow += 0x100;
        if (odd != 0) {
            lead = arg3 & 1;
            if (lead && phase == 0) {
                *dst |= *src << 4;
            } else if (lead && phase != 0) {
                *dst |= *src << 4;
            } else if (lead == 0 && phase != 0) {
                *dst |= (*src & 0xF0) >> 4;
            } else {
                *dst |= *src;
            }
        }
        row++;
        dstRow -= arg6;
        src = srcRow;
        dst = dstRow;
    } while (row < 0x10);
    if (phase != 0) {
        phase = odd;
    }
    return phase + arg1 + arg0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FB490.s")
#endif





typedef struct FcDGlyph {
    s16 unk0;
    u8 unk2;
    u8 unk3;
} FcDGlyph;

typedef struct {
    u8 unk0[0x17C];
    s16 unk17C;
    u8 unk17E;
} R1F100180_Entry;

s8 func_806FB914(s16, u8 *);
void *func_806FBB9C(s16);
extern R1F100180_Entry *D_80754A18[];
extern void *D_807FD7F0;
extern u8 D_80754A35;
extern u8 *D_807549FC[];

void func_806FB714(s32 arg0, u8 arg1, u8 *arg2) {
    s32 i;
    u8 sp63;
    u8 sp3;
    u8 sp61;

    sp61 = 0;
    sp63 = *arg2++;
    while (sp63) {
        if (sp63 != 32) {
            sp3 = func_806FB914(0, &sp63);
            for (i = 1; i < D_80754A35 + 1; i++) {
                if (sp63 >= D_807549FC[0][i - 1] && sp63 < D_807549FC[0][i]) {
                    func_806FBB9C(i - 1);
                    arg0 = func_806FB490(((FcDGlyph *)D_80754A18[0])[sp63].unk2, arg0, ((s32 *)D_807FD7F0)[i - 1], ((FcDGlyph *)D_80754A18[0])[sp63].unk0, sp3, (s8 *)&sp61, arg1);
                }
            }
        } else {
            arg0 += 3;
            sp61 += 6;
        }
        sp63 = *arg2;
        arg2++;
    }
}



typedef struct {
    u8 unk0[8];
    s32 unk8;
} R1F100180_Heap;

void func_806FB8B0(s32 arg0) {
    s8 sp2F;

    sp2F = 0;
    func_806FBB9C(2);
    func_806FB490(D_80754A18[0]->unk17E, arg0, ((R1F100180_Heap *) D_807FD7F0)->unk8, D_80754A18[0]->unk17C, 2,
                  &sp2F, 0x30);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/D_8075DC20.s")

typedef struct { u8 b[0x39]; } FcDStr39;
typedef struct { u8 b[0x30]; } FcDStr30;
typedef struct { u8 b[0x3A]; } FcDStr3A;

extern FcDStr39 D_80754A64;
extern FcDStr30 D_80754AA0;
extern FcDStr3A D_8075DC20;
u8 *_strchr(u8 *, s32);

s8 func_806FB914(s16 arg0, u8 *arg1) {
    s8 spDF;
    FcDStr39 spA4;
    FcDStr30 sp74;
    FcDStr3A sp38;

    spDF = 0;
    switch (arg0) {
    case 0:
        switch (*arg1) {
        case 0x2E:
        case 0x67:
        case 0x70:
        case 0x71:
        case 0x80:
            spDF = 2;
            break;
        case 0x61:
        case 0x79:
            spDF = 1;
            break;
        }
        *arg1 -= 0x21;
        break;
    case 1:
        spA4 = D_80754A64;
        *arg1 = _strchr((u8 *)&spA4, *arg1) - (u8 *)&spA4;
        break;
    case 6:
        sp74 = D_80754AA0;
        *arg1 = _strchr((u8 *)&sp74, *arg1) - (u8 *)&sp74;
        break;
    case 2:
        sp38 = D_8075DC20;
        *arg1 = _strchr((u8 *)&sp38, *arg1) - (u8 *)&sp38;
        break;
    case 3:
    case 7: {
        u8 sp28[] = "0123456789%/";

        *arg1 = _strchr(sp28, *arg1) - sp28;
        break;
    }
    case 4:
        if (*arg1 == 0x40) {
            *arg1 = 0x60;
        } else {
            *arg1 -= 0x21;
        }
        break;
    case 5:
        *arg1 -= 0x21;
        break;
    }
    return spDF;
}

s32 func_80610FE8(s32);
void heapClearBlock(s32);
extern u8 *D_807FD7F4;

void func_806FBB58(void) {
    s32 allocation;
    s32 *allocation_slot;
    s32 temp_v0;
    u8 **heap_buffer;

    D_807FD7F0 = func_80610FE8(0xAC);
    temp_v0 = func_80610FE8(0x2B);
    heap_buffer = &D_807FD7F4;
    allocation_slot = (s32 *)heap_buffer;
    allocation = (*allocation_slot = temp_v0);
    heapClearBlock(allocation);
}

void *func_8066B0F8(s32, s16, u8, s32);


void *func_806FBB9C(s16 arg0) {
    s16 temp_a1;
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = arg0 + D_807FD7F4;
    temp_a1 = arg0;
    var_v1 = temp_a1 * 4;
    if (*temp_v0 == 0) {
        arg0 = arg0;
        var_v1 = arg0 * 4;
        *(void **)((u8 *) D_807FD7F0 + var_v1) = func_8066B0F8(0xE, temp_a1, 1, 1);
        *(D_807FD7F4 + arg0) = 3;
    } else {
        *temp_v0 = 3;
    }
    return *(void **)((u8 *) D_807FD7F0 + var_v1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FBC34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FBD5C.s")

s16 func_806FBEAC(u8 *arg0) {
    s16 var_v1;
    u8 temp_v0;

    temp_v0 = *arg0;
    var_v1 = 0;
    arg0 += 1;
    if (temp_v0 != 0) {
        do {
            if (arg0[-1] != 0x20) {
                var_v1 += 1;
            }
            temp_v0 = arg0[0];
            arg0 += 1;
        } while (temp_v0 != 0);
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FBEF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FC530.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FCC88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FD094.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FD490.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FD7A8.s")

extern u8 D_80754A36[];

u8 func_806FD894(s16 arg0) {
    if (arg0 & 0x80) {
        arg0 ^= 0x80;
    }
    return D_80754A36[arg0 * 6];
}
